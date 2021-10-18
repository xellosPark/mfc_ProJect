#include "StdAfx.h"
#include "Serialcomm.h"


// 	ThreadWatchComm
DWORD	WINAPI	ThreadWatchComm(LPVOID lpParam)
{
	OVERLAPPED	os;
	memset(&os, 0, sizeof(OVERLAPPED));
	if (!(os.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) return FALSE;

	SerialComm	*pComm = (SerialComm*)lpParam;
	if (!SetCommMask(pComm->m_hComm, EV_RXCHAR)) {
		CloseHandle(os.hEvent);
		return FALSE;
	}

	DWORD	dwEvent = 0;
	while (pComm->m_bConnected) {
		dwEvent = 0;
		WaitCommEvent(pComm->m_hComm, &dwEvent, NULL);
		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR) pComm->OnReceive();
	}

	CloseHandle(os.hEvent);
	pComm->m_hThread = 0;
	return TRUE;
}
// 	ThreadWatchComm


SerialComm::SerialComm ()
{
	m_hComm = 0;
	m_bConnected = FALSE;
	memset (&m_osRead, 0, sizeof (OVERLAPPED));
	memset (&m_osWrite, 0, sizeof (OVERLAPPED));
	m_hThread = 0;

	memset (m_queue, 0, 4096);
	m_nReadLen = 0;
	m_delim = _T("\r");
	m_cTail = _T('\n');
	m_nMustReadBytes = 0;
	m_bPurgeBeforeWrite = TRUE;
}

SerialComm::~SerialComm ()
{
	if (m_bConnected) ClosePort ();
}

BOOL SerialComm::initOpenPort(CString strPortName,int nBaud, int nBSize /*= 8*/, int nStop /*= 1*/, TCHAR cParitybit /*=0*/)
{
	CString	strPort(_T(""));
	strPort = strPortName;

 	if (strPort == "" || strPort.IsEmpty()) return FALSE;

	int		nBaudRate = nBaud;
	TCHAR	cParity   = cParitybit;
	int		nByteSize = nBSize;
	int		nStopBits = nStop;
	//swscanf (string.Mid (nPos+1), _T("%d,%c,%d,%d"), &nBaudRate, &cParity, &nByteSize, &nStopBits);
	return OpenPort (strPort, nBaudRate, cParity, nByteSize, nStopBits);
}

BOOL SerialComm::OpenPort (CString portName, int baudRate, TCHAR cParity, int nByteSize, int nStopBits)
{
	m_bConnected = FALSE;
	if (portName.GetLength () > 4) portName = _T("\\\\.\\") + portName;

	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	if (!(m_osRead.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL)))	return FALSE;

	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	if (!(m_osWrite.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL))) return FALSE;
	
	m_hComm = CreateFile (portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 
						  FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if (m_hComm == (HANDLE) -1) return FALSE;

	SetCommMask (m_hComm, EV_RXCHAR);	
	SetupComm (m_hComm, 4096, 4096);	
	PurgeComm (m_hComm, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	COMMTIMEOUTS	timeouts;
	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 1000;
	SetCommTimeouts (m_hComm, &timeouts);

	DCB		dcb;
	dcb.DCBlength = sizeof (DCB);
	GetCommState (m_hComm, &dcb);
	dcb.BaudRate = baudRate;
	if		(cParity == 'e') dcb.Parity = EVENPARITY;
	else if (cParity == 'o') dcb.Parity = ODDPARITY;
	else					 dcb.Parity = NOPARITY;
	dcb.ByteSize = nByteSize;
	if		(nStopBits == 1) dcb.StopBits = ONESTOPBIT;
	else if (nStopBits == 2) dcb.StopBits = TWOSTOPBITS;
	else					 dcb.StopBits = ONE5STOPBITS;

	if (!SetCommState (m_hComm, &dcb)) return FALSE;
	else {
		m_bConnected = TRUE;
		m_hThread = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)ThreadWatchComm, this, 0, 0);
		if (!m_hThread) {
			ClosePort ();
			return FALSE;
		}
	}

	return TRUE;
}
	
void	SerialComm::ClosePort ()
{
	if (m_hThread) {
		DWORD dwExitCode;
		::GetExitCodeThread (m_hThread, &dwExitCode);
		if (dwExitCode == STILL_ACTIVE) {
			::TerminateThread (m_hThread, dwExitCode);
			CloseHandle (m_hThread);
		}
		m_hThread = NULL;	
	}

	m_bConnected = FALSE;
	SetCommMask (m_hComm, 0);
	PurgeComm (m_hComm, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
	CloseHandle (m_hComm);
	CloseHandle (m_osRead.hEvent);
	CloseHandle (m_osWrite.hEvent);
}

DWORD	SerialComm::ReadComm (LPVOID pBuf, DWORD dwBytesToRead)
{
	DWORD	dwRead = 0, dwErrorFlags = 0;
	COMSTAT	comstat;

	ClearCommError (m_hComm, &dwErrorFlags, &comstat);
	if (comstat.cbInQue == 0) return 0;

	dwRead = comstat.cbInQue;
	if (dwBytesToRead > dwRead) dwBytesToRead = dwRead;
	
	if (!ReadFile (m_hComm, pBuf, dwBytesToRead, &dwRead, &m_osRead)) {
		if (GetLastError () == ERROR_IO_PENDING)	{
			while (!GetOverlappedResult (m_hComm, &m_osRead, &dwRead, TRUE)) {
				if (GetLastError () != ERROR_IO_INCOMPLETE)	{
					ClearCommError (m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		} else {
			dwRead = 0;
			ClearCommError (m_hComm, &dwErrorFlags, &comstat);
		}
	}
	return dwRead;
}

DWORD	SerialComm::WriteComm (TCHAR ch)
{
#ifdef _UNICODE
	char	mbBuf[2];
	wctomb (mbBuf, ch);
	return WriteComm (mbBuf, 1);
#else
	return WriteComm (&ch, 1);
#endif
}

DWORD	SerialComm::WriteComm (LPVOID pBuf, DWORD dwBytesToWrite)
{
	DWORD	dwWritten = 0;
	BOOL	bWrite = WriteFile (m_hComm, pBuf, dwBytesToWrite, &dwWritten, &m_osWrite);

	if (!bWrite) {
		DWORD	dwErrorFlags = 0;
		COMSTAT	comstat;
		if (GetLastError () == ERROR_IO_PENDING) {
			while (!GetOverlappedResult (m_hComm, &m_osWrite, &dwWritten, TRUE)) {
				if (GetLastError () != ERROR_IO_INCOMPLETE) {
					ClearCommError (m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		} else {
			dwWritten = 0;
			ClearCommError (m_hComm, &dwErrorFlags, &comstat);
		}
	}
	return dwWritten;
}

DWORD	SerialComm::WriteComm (CString string)
{
	string += m_delim;

#ifdef _UNICODE
	char	mbBuf[COMM_QUEUE_SIZE];
	wcstombs (mbBuf, (LPCTSTR)string, string.GetLength ());
	return WriteComm (mbBuf, string.GetLength ());
#else
	return WriteComm ((LPTSTR)(LPCTSTR)string, string.GetLength ());
#endif
}

void	SerialComm::OnReceive ()
{
	static	char	buf[4096];
	DWORD	dwRead = 0;

	while (dwRead = ReadComm (buf, 4096)) {
		for (DWORD i = 0; i < dwRead; i++) {
			if (m_nMustReadBytes > 0 && m_nReadLen == m_nMustReadBytes) {
				m_queue[m_nReadLen] = 0;
				m_nReadLen = 0;
				ReceiveCode (m_queue);
			} else if (m_nMustReadBytes == 0 && (buf[i] == '\r' || buf[i] == '\n')) {
				m_queue[m_nReadLen] = 0;
				m_nReadLen = 0;
				ReceiveCode (m_queue);
			} else {
#ifdef _UNICODE
				mbtowc (&m_queue[m_nReadLen++], &buf[i], 1);
#else
				m_queue[m_nReadLen++] = buf[i];
#endif
			}
		}
		buf[0] = 0;
	}
}



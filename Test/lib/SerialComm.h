#pragma once
#include <afxmt.h>
class	SerialComm 
{
	public:
		SerialComm();
		virtual	~SerialComm();
		
	public:
		HANDLE		m_hComm;
		BOOL		m_bConnected;
		OVERLAPPED	m_osRead, m_osWrite;
		HANDLE		m_hThread;

	public:
		TCHAR	m_queue[4096] = { 0, };
		int		m_nReadLen;
		CString	m_delim;
		TCHAR	m_cTail = 0;
		int		m_nMustReadBytes;
		BOOL	m_bPurgeBeforeWrite;
		CString	m_section;
	
	public:
		/*BOOL	OpenPort() (CString section, CString key)*/;
		BOOL    initOpenPort(CString strPortName, int nBaud, int nBSize = 8, int nStop = 1, TCHAR cParitybit = 0);
		BOOL	OpenPort (CString portName, int baudRate, TCHAR cParity, int nByteSize, int nStopBits);
		void	ClosePort();

	protected:
		DWORD	ReadComm (LPVOID pBuf, DWORD dwBytesToRead);
		DWORD	WriteComm (TCHAR ch);
		DWORD	WriteComm (LPVOID pBuf, DWORD dwBytesToWrite);
		virtual DWORD	WriteComm (CString string);

 	public:
 		virtual	void	OnReceive ();
 		virtual	void	ReceiveCode (TCHAR *pBuf) = 0;
};
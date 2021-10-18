#include "stdafx.h"
#include "UnitSerial.h"
#define	COMM_QUEUE_SIZE				4096

CUnitSerial::CUnitSerial()
{
	if (GetIsConnect() == FALSE){
		Connect();
	} else {
		AfxMessageBox(_T("--- 이미 연결중 ---"));
	}
}


CUnitSerial::~CUnitSerial()
{
}

void CUnitSerial::ReceiveCode(TCHAR *pBuf)
{
	CString str("");
	str.Format("%s", pBuf);
	AfxMessageBox(str);
	switch (pBuf[0]) {
	case '&': break;
/*	case '%': ReceivePos(pBuf); break;*/
	default: break;
	}
}

void CUnitSerial::SendData(CString str)
{
	//WriteComm(MsgStr(_T("!DEV=%d"), nDEV));
	WriteComm(MsgStr(str));
	Sleep(50);
}


BOOL CUnitSerial::Connect()
{
	BOOL bok = initOpenPort("COM1",9600);

	if (bok == TRUE) {
		SetIsConnect(TRUE);
	} else {
		SetIsConnect(FALSE);
		AfxMessageBox(_T("--- 연결 실패 ---"));
		return FALSE;
	}	

	return TRUE;
}

void CUnitSerial::Disconnect()
{
	ClosePort();
}

CString	MsgStr(LPCTSTR fmt, ...)
{
	CString	string;
	if (fmt != 0) {
		va_list	argptr;
		va_start(argptr, fmt);
		string.FormatV(fmt, argptr);
		va_end(argptr);
	}
	return string;
}
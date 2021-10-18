#pragma once
#include "./lib/Serialcomm.h"

class CUnitSerial : public SerialComm
{
public:
	CUnitSerial();
	virtual ~CUnitSerial();

	BOOL GetIsConnect() const { return m_bIsConnect; }
	void SetIsConnect(BOOL val) { m_bIsConnect = val; }
public:
	virtual void ReceiveCode(TCHAR *pBuf);
	void SendData(CString str);

	BOOL Connect();
	void Disconnect();

protected:
	BOOL m_bIsConnect = FALSE;
};
CString MsgStr(LPCTSTR fmt, ...);

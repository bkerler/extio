#pragma once

#include "socketClient.h"

class CthreadWait;

class CsocketClientWaitable : public CsocketClient
{
DECLARE_DYNCREATE(CsocketClientWaitable)
public:
	//CsocketClientWaitable();
	CsocketClientWaitable(ClientSocketCallback* pCallback = NULL);
	~CsocketClientWaitable();
public:
	HANDLE m_hWaitEvent;
	CthreadWait* m_pWaitThread;
public:
	BOOL ConnectHelper(const SOCKADDR* lpSockAddr, int nSockAddrLen);
	BOOL PumpMessages(UINT uStopFlag);
};

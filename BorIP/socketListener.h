#pragma once

class Server;

// CsocketListener command target

class CsocketListener : public CSocket
{
public:
	CsocketListener(Server* pServer);
	virtual ~CsocketListener();
public:
	Server* m_pServer;
public:
	virtual void OnAccept(int nErrorCode);
};

#pragma once

class CsocketClient;

class ClientSocketCallback
{
public:
	virtual void OnCommand(CsocketClient* pSocket, const CString& str)
	{ }
	virtual void OnClose(CsocketClient* pSocket)
	{ }
};

// CsocketClient command target

class CsocketClient : public CSocket
{
public:
	//CsocketClient();
	CsocketClient(ClientSocketCallback* pCallback = NULL);
	virtual ~CsocketClient();
public:
	ClientSocketCallback* m_pCallback;
	CString m_strBuffer;
public:
	bool _Send(const CString& str);
	bool _IsDataAvailable();
public:
	inline void _SetCallback(ClientSocketCallback* pCallback)
	{ m_pCallback = pCallback; }
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

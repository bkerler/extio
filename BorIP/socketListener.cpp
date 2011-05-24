// socketListener.cpp : implementation file
//

#include "stdafx.h"
#include "BorIPApp.h"
#include "socketListener.h"

// CsocketListener

CsocketListener::CsocketListener(Server* pServer)
	: m_pServer(pServer)
{
}

CsocketListener::~CsocketListener()
{
}

// CsocketListener member functions

void CsocketListener::OnAccept(int nErrorCode)
{
	m_pServer->OnAccept();

	CSocket::OnAccept(nErrorCode);
}

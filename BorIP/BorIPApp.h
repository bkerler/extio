
// BorIP.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Server.h"
#include "CommandLineInfo.h"

// CappMain:
// See BorIP.cpp for the implementation of this class
//

class CappMain : public CWinAppEx
{
public:
	CappMain();
// Overrides
public:
	virtual BOOL InitInstance();
// Implementation
	DECLARE_MESSAGE_MAP()
public:
	Server m_server;
	CommandLineInfo m_cli;
};

extern CappMain theApp;

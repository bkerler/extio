// WinradUSRP.h : main header file for the WinradUSRP DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

//class CdialogExtIO;
//class USRP;
class ExtIO_USRP;

// CWinradUSRPApp
// See WinradUSRP.cpp for the implementation of this class
//

class CWinradUSRPApp : public CWinApp
{
public:
	CWinradUSRPApp();
	~CWinradUSRPApp();
// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	DECLARE_MESSAGE_MAP()
public:
	bool _Open();
	void _Close();
private:
	//USRP* m_pUSRP;
	ExtIO_USRP* m_pUSRP;
	//CdialogExtIO* m_pDialog;
	//long m_iLO;
public:
	ExtIO_USRP* _GetUSRP()
	{ return m_pUSRP; }
//	USRP* _GetUSRP()
//	{ return m_pUSRP; }
//	CdialogExtIO* _GetDialog()
//	{ return m_pDialog; }
};

//extern CWinradUSRPApp theApp;

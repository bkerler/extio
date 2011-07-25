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
	void _Close(bool bAll = false);
private:
	//USRP* m_pUSRP;
	ExtIO_USRP* m_pUSRP;
	//CdialogExtIO* m_pDialog;
	//long m_iLO;
	Teh::MemoryContainer m_memPlayback;
	bool m_bPlayback;
public:
	inline ExtIO_USRP* _GetUSRP()
	{ return m_pUSRP; }
	inline Teh::MemoryContainer& _GetPlaybackMemory()
	{ return m_memPlayback; }
	inline bool _IsPlayingBack() const
	{ return m_bPlayback; }
//	USRP* _GetUSRP()
//	{ return m_pUSRP; }
//	CdialogExtIO* _GetDialog()
//	{ return m_pDialog; }
};

//extern CWinradUSRPApp theApp;

class PTMRC : public Teh::RefCounter, public CNoTrackObject
{
/*public:
	int i;
	UINT n;
	//std::set<MSG> pre;
	TLSInside()
		: i(0)
		, n(0)
	{
	}*/
};

THREAD_LOCAL(PTMRC, _ptmrc);

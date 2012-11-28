/* (C) 2011-2012 by Balint Seeber <balint256@gmail.com>
 *
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*&*/

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
//	Teh::MemoryContainer m_memPlayback;
	bool m_bPlayback;
public:
	short* m_pPlaybackMemory;
	UINT m_nPlaybackMemoryLength;
public:
	inline ExtIO_USRP* _GetUSRP()
	{ return m_pUSRP; }
//	inline Teh::MemoryContainer& _GetPlaybackMemory()
//	{ return m_memPlayback; }
	inline bool _IsPlayingBack() const
	{ return m_bPlayback; }
//	USRP* _GetUSRP()
//	{ return m_pUSRP; }
//	CdialogExtIO* _GetDialog()
//	{ return m_pDialog; }
};

//extern CWinradUSRPApp theApp;

class PTMRC : /*public Teh::RefCounter, */public CNoTrackObject
{
private:
	int m_i;
public:
	PTMRC()
		: m_i(0)
	{ }
	int RefIncCount()
	{ ++m_i; return m_i; }
	int RefDecCount()
	{ --m_i; return m_i; }
	int RefGetCount()
	{ return m_i; }
};

class ScopedPTMRC
{
private:
	PTMRC* m_p;
public:
	ScopedPTMRC(PTMRC* p)
	{ p->RefIncCount(); m_p = p; }
	~ScopedPTMRC()
	{ m_p->RefDecCount(); }
};

THREAD_LOCAL(PTMRC, _ptmrc);

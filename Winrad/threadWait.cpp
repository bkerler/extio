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

// threadWait.cpp : implementation file
//

#include "stdafx.h"
#include "WinradUSRP.h"
#include "threadWait.h"

#include "dialogWait.h"

// CthreadWait

IMPLEMENT_DYNCREATE(CthreadWait, CWinThread)

CthreadWait::CthreadWait()
	: m_hEvent(NULL)
	, m_pDialog(NULL)
	, m_hWnd(NULL)
	, m_hCreatedEvent(NULL)
{
	m_hCreatedEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	ASSERT(m_hCreatedEvent);
}

CthreadWait::~CthreadWait()
{
	if (m_hCreatedEvent)
		CloseHandle(m_hCreatedEvent);
}

BOOL CthreadWait::InitInstance()
{
	/*m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (m_hEvent == NULL)
		return FALSE;*/

	m_pDialog = new CdialogWait(this, /*CWnd::FromHandle(m_hWnd)*/NULL);
	if (m_pDialog->Create(CdialogWait::IDD, /*CWnd::FromHandle(m_hWnd)*/NULL) == FALSE)
		return FALSE;

	m_pMainWnd = m_pActiveWnd = m_pDialog;

	m_pDialog->SetForegroundWindow();
	//m_pDialog->Activate();

	//Teh::Utils::PumpMessageLoop();	// FIXME: Necessary to pump messages?

	SetEvent(m_hCreatedEvent);

	return TRUE;
}

int CthreadWait::ExitInstance()
{
	if (m_pDialog)
	{
		m_pDialog->DestroyWindow();
		SAFE_DELETE(m_pDialog);

		m_pMainWnd = m_pActiveWnd = NULL;
	}

	/*if (m_hEvent)
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}*/

	AfxTrace(_T("Wait thread 0x%04x exiting...\n"), GetCurrentThreadId());

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CthreadWait, CWinThread)
END_MESSAGE_MAP()

// CthreadWait message handlers

CthreadWait* CthreadWait::_Create(HANDLE hEvent, HWND hWnd /*= NULL*/, LPCTSTR strMessage /*= NULL*/)
{
	CthreadWait* pThread = (CthreadWait*)AfxBeginThread(RUNTIME_CLASS(CthreadWait), 0, 0, CREATE_SUSPENDED, NULL);
	if (pThread == NULL)
		return NULL;

	pThread->m_hWnd = hWnd;
	pThread->m_hEvent = hEvent;
	pThread->m_strMessage = strMessage;
	pThread->m_bAutoDelete = TRUE;

	pThread->ResumeThread();

	WaitForSingleObject(pThread->m_hCreatedEvent, INFINITE);

	return pThread;
}

void CthreadWait::_Close(bool bResetEvent /*= true*/)
{
	ResetEvent(m_hEvent);

	PostThreadMessage(WM_QUIT, 0, 0);
}

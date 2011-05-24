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
{
}

CthreadWait::~CthreadWait()
{
}

BOOL CthreadWait::InitInstance()
{
	//m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	//if (m_hEvent == NULL)
	//	return FALSE;

	m_pDialog = new CdialogWait(this, /*CWnd::FromHandle(m_hWnd)*/NULL);
	if (m_pDialog->Create(CdialogWait::IDD, /*CWnd::FromHandle(m_hWnd)*/NULL) == FALSE)
		return FALSE;

	m_pMainWnd = m_pActiveWnd = m_pDialog;

	m_pDialog->SetForegroundWindow();
	//m_pDialog->Activate();

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

	return pThread;
}

void CthreadWait::_Close()
{
	PostThreadMessage(WM_QUIT, 0, 0);
}

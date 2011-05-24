// dialogWait.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "dialogWait.h"

#include "threadWait.h"

// CdialogWait dialog

IMPLEMENT_DYNAMIC(CdialogWait, CDialog)

CdialogWait::CdialogWait(CthreadWait* pThread, CWnd* pParent /*=NULL*/)
	: CDialog(CdialogWait::IDD, pParent)
	, m_pThread(pThread)
{
}

CdialogWait::~CdialogWait()
{
}

void CdialogWait::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CdialogWait, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CdialogWait::OnBnClickedCancel)
END_MESSAGE_MAP()


// CdialogWait message handlers

void CdialogWait::OnBnClickedCancel()
{
	SetEvent(m_pThread->m_hEvent);

	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	OnCancel();

	//m_pThread->_Close();
}

BOOL CdialogWait::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_pThread->m_strMessage.IsEmpty() == false)
		SetDlgItemText(IDC_STATIC_INFO, m_pThread->m_strMessage);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

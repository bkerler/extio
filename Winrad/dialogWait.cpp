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

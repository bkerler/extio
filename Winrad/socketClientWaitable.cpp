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

#include "StdAfx.h"
#include "socketClientWaitable.h"

#include "threadWait.h"

IMPLEMENT_DYNCREATE(CsocketClientWaitable, CsocketClient)
/*
CsocketClientWaitable::CsocketClientWaitable()
{
}
*/
CsocketClientWaitable::CsocketClientWaitable(ClientSocketCallback* pCallback /*= NULL*/)
	: CsocketClient(pCallback)
	, m_pWaitThread(NULL)
{
	m_hWaitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	ASSERT(m_hWaitEvent);
}

CsocketClientWaitable::~CsocketClientWaitable()
{
	if (m_hWaitEvent)
		CloseHandle(m_hWaitEvent);
}

BOOL CsocketClientWaitable::ConnectHelper(const SOCKADDR* lpSockAddr, int nSockAddrLen)
{
	if (m_pbBlocking != NULL)
	{
		WSASetLastError(WSAEINPROGRESS);
		return  FALSE;
	}

	m_nConnectError = -1;

	if (!CAsyncSocket::ConnectHelper(lpSockAddr, nSockAddrLen))
	{
		if (GetLastError() == WSAEWOULDBLOCK)
		{
			////////////////////////////////////////////////

			CWnd* pWnd = AfxGetApp()->GetMainWnd();
			m_pWaitThread = CthreadWait::_Create(m_hWaitEvent, (pWnd ? pWnd->GetSafeHwnd() : NULL), _T("Connecting..."));

			////////////////////////////////////////////////

			while (PumpMessages(FD_CONNECT))
			{
				if (m_nConnectError != -1)
				{
					m_pWaitThread->_Close();
					m_pWaitThread = NULL;

					WSASetLastError(m_nConnectError);
					return (m_nConnectError == 0);
				}
			}

			m_pWaitThread->_Close();
			m_pWaitThread = NULL;
		}

		return FALSE;
	}

	return TRUE;
}

#define _afxSockThreadState AfxGetModuleThreadState()
#define _AFX_SOCK_THREAD_STATE AFX_MODULE_THREAD_STATE

BOOL CsocketClientWaitable::PumpMessages(UINT uStopFlag)
{
	// The same socket better not be blocking in more than one place.
	ASSERT(m_pbBlocking == NULL);

	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;

	ASSERT(pState->m_hSocketWindow != NULL);

	BOOL bBlocking = TRUE;
	m_pbBlocking = &bBlocking;
	CWinThread* pThread = AfxGetThread();

	// This is not a timeout in the WinSock sense, but more
	// like a WM_KICKIDLE to keep message pumping alive
	UINT_PTR nTimerID = ::SetTimer(pState->m_hSocketWindow, 1, m_nTimeOut, NULL);

	if (nTimerID == 0)
		AfxThrowResourceException();

	BOOL bPeek = TRUE;

	while (bBlocking)
	{
		TRY
		{
			MSG msg;
			if (::PeekMessage(&msg, pState->m_hSocketWindow,
				WM_SOCKET_NOTIFY, WM_SOCKET_DEAD, PM_REMOVE))
			{
				if (msg.message == WM_SOCKET_NOTIFY && (SOCKET)msg.wParam == m_hSocket)
				{
					if (WSAGETSELECTEVENT(msg.lParam) == FD_CLOSE)
					{
						break;
					}
					if (WSAGETSELECTEVENT(msg.lParam) == uStopFlag)
					{
						if (uStopFlag == FD_CONNECT)
							m_nConnectError = WSAGETSELECTERROR(msg.lParam);
						break;
					}
				}
				if (msg.wParam != 0 || msg.lParam != 0)
					CSocket::AuxQueueAdd(msg.message, msg.wParam, msg.lParam);

				bPeek = TRUE;
			}
			else if (::PeekMessage(&msg, pState->m_hSocketWindow,
						WM_TIMER, WM_TIMER, PM_REMOVE))
			{
			break;
			}

			if (bPeek && ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				if (OnMessagePending())
				{
					// allow user-interface updates
					ASSERT(pThread);
					pThread->OnIdle(-1);
				}
				else
				{
					bPeek = FALSE;
				}
			}
			else
			{
				// no work to do -- allow CPU to sleep
				if (m_pWaitThread)
				{
					DWORD dw = MsgWaitForMultipleObjects(1, &m_hWaitEvent, FALSE, INFINITE, QS_ALLINPUT);
					if (dw == WAIT_OBJECT_0)
					{
						bBlocking = FALSE;
						m_nConnectError = WSAEINTR;
						break;
					}
				}
				else
				{
					WaitMessage();
				}

				bPeek = TRUE;
			}
		}
		CATCH_ALL(e)
		{
			TRACE(traceSocket, 0, "Error: caught exception in PumpMessage - continuing.\n");
			//DELETE_EXCEPTION(e);
			e->Delete();
			bPeek = TRUE;
		}
		END_CATCH_ALL
	}

	::KillTimer(pState->m_hSocketWindow, nTimerID);

	if (!bBlocking)
	{
		WSASetLastError(WSAEINTR);
		return FALSE;
	}
	m_pbBlocking = NULL;

	::PostMessage(pState->m_hSocketWindow, WM_SOCKET_NOTIFY, 0, 0);

	return TRUE;
}

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

// socketClient.cpp : implementation file
//

#include "stdafx.h"
#include "socketClient.h"

// CsocketClient
/*
CsocketClient::CsocketClient()
	: m_pCallback(NULL)
{
}
*/
CsocketClient::CsocketClient(ClientSocketCallback* pCallback /*= NULL*/)
	: m_pCallback(pCallback)
{
}

CsocketClient::~CsocketClient()
{
}

// CsocketClient member functions

bool CsocketClient::_Send(const CString& str)
{
	CStringA strBuf(str);
	strBuf = strBuf.Trim();
	strBuf += "\n";

	int iLength = strBuf.GetLength();
	LPSTR p = strBuf.GetBuffer();
	int iSent = Send(p, iLength);
	strBuf.ReleaseBuffer();

	if (iSent == SOCKET_ERROR)
	{
		//

		return false;
	}
	else if (iSent != iLength)
	{
		//
	}

	return true;
}

void CsocketClient::OnReceive(int nErrorCode)
{
	const int iBufferSize = 16384;
	char strBuf[iBufferSize + 1];

	while (_IsDataAvailable())
	{
		int iReceived = Receive(strBuf, iBufferSize);
		if ((iReceived == SOCKET_ERROR) || (iReceived == 0))	// Disconnect (BUSY) causes 0 to be returned?
		{
			break;
		}

		strBuf[iReceived] = '\0';

		CString str(strBuf);

		m_strBuffer += str;

		int iIndexCR = m_strBuffer.Find(_T('\r'));
		int iIndexLF = m_strBuffer.Find(_T('\n'));

		int iIndex = -1, iIndexLast = -1;

		if ((iIndexLF > -1) && (iIndexCR > -1))
		{
			iIndex = min(iIndexLF, iIndexCR);
			iIndexLast = max(iIndexLF, iIndexCR);
		}
		else if ((iIndexCR > -1) || (iIndexLF > -1))
		{
			iIndex = iIndexLast = max(iIndexCR, iIndexLF);
		}

		if (iIndex == -1)
			continue;

		CString strCommand(m_strBuffer.Left(iIndex));

		if (m_pCallback)
			m_pCallback->OnCommand(this, strCommand);

		m_strBuffer = m_strBuffer.Mid(iIndexLast + 1);
	}

	CSocket::OnReceive(nErrorCode);
}

void CsocketClient::OnClose(int nErrorCode)
{
	if (m_pCallback)
		m_pCallback->OnClose(this);

	CSocket::OnClose(nErrorCode);
}

bool CsocketClient::_IsDataAvailable()
{
	timeval timeout;
	timeout.tv_usec = 0;
	timeout.tv_sec = 0;

	fd_set rx;

	FD_ZERO(&rx);
	FD_SET(m_hSocket, &rx);

	int iResult = select(((int)m_hSocket) + 1, &rx, NULL, NULL, &timeout);
	if (iResult == SOCKET_ERROR)
	{
		return false;
	}

	return (iResult == 1);
}

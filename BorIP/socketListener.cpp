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

// socketListener.cpp : implementation file
//

#include "stdafx.h"
#include "BorIPApp.h"
#include "socketListener.h"

// CsocketListener

CsocketListener::CsocketListener(Server* pServer)
	: m_pServer(pServer)
{
}

CsocketListener::~CsocketListener()
{
}

// CsocketListener member functions

void CsocketListener::OnAccept(int nErrorCode)
{
	m_pServer->OnAccept();

	CSocket::OnAccept(nErrorCode);
}

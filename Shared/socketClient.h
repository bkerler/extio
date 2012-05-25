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

#pragma once

class CsocketClient;

class ClientSocketCallback
{
public:
	virtual void OnCommand(CsocketClient* pSocket, const CString& str)
	{ }
	virtual void OnClose(CsocketClient* pSocket)
	{ }
};

// CsocketClient command target

class CsocketClient : public CSocket
{
public:
	//CsocketClient();
	CsocketClient(ClientSocketCallback* pCallback = NULL);
	virtual ~CsocketClient();
public:
	ClientSocketCallback* m_pCallback;
	CString m_strBuffer;
public:
	bool _Send(const CString& str);
	bool _IsDataAvailable();
public:
	inline void _SetCallback(ClientSocketCallback* pCallback)
	{ m_pCallback = pCallback; }
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

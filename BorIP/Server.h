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

#include "socketClient.h"

class CsocketListener;
class IUSRP;

class ServerCallback
{
public:
	enum EventCode
	{
		EC_UNKNOWN = -1,
		EC_LOG,
		EC_CREATED,
		EC_CLOSED,
		EC_CONNECTED,
		EC_DISCONNECTED,
		EC_START,
		EC_STOP,
		EC_COMMAND
	};
	typedef struct Event
	{
		EventCode code;
		LPCTSTR message;
	} EVENT;
public:
	virtual int OnServerEvent(const EVENT& event)
	{ return 0; }
};

class Server : public ClientSocketCallback
{
public:
	Server();
	~Server();
public:
	CsocketListener* m_pListener;
	CsocketClient* m_pClient;
	IUSRP* m_pUSRP;
	//CAsyncSocket* m_pDataStream;
	int m_iDefaultPort;
	SOCKET m_hDataSocket;
	HANDLE m_hEvent;
	DWORD m_dwWorkerID;
	HANDLE m_hWorker;
	CCriticalSection m_cs;
	SOCKADDR_IN m_addrDest;
	UINT m_nMaxPacketSize;
	ServerCallback* m_pCallback;
	bool m_bHeaderless;
	CString m_strLastError;
	CFile m_fileDump;
	CTime m_timeDeviceReset;
	CString m_strLastDeviceHint;
public:
	UINT m_nReadFailures;
	UINT m_nShortReads;
	UINT m_nOverruns;
	UINT m_nBlockingErrors;
	UINT m_nBlockingWaits;
	UINT m_nSocketErrors;
	UINT m_nShortSends;
	UINT m_nPacketsReceived;
	UINT m_nPacketsSent;
	UINT m_nBlockingSends;
public:
	void SetCallback(ServerCallback* pCallback)
	{ m_pCallback = pCallback; }
public:
	bool Initialise(ServerCallback* pCallback = NULL, int iListenerPort = 0);
	void Destroy();
	void Reset();
	void OnAccept();
	void OnCommand(CsocketClient* pClient, const CString& str);
	void OnClose(CsocketClient* pClient);
	bool Start();
	void Stop();
	bool CreateDevice(LPCTSTR strHint = NULL);
	void CloseDevice();
	CString FormatDevice();
	DWORD Worker();
	void Log(const CString& str);
	CString FormatError(LPCTSTR strError = NULL, bool bPad = true);
	void RunPeriodicTasks();
	void SetResetTime(const CTime* pResetTime);
};

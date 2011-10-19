// BandwidthTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BandwidthTest.h"

#include "BorIP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ZERO_MEMORY(s)	ZeroMemory(&s, sizeof(s))

// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		return 1;
	}

	if (!AfxSocketInit())
	{
		_tprintf(_T("Failed to initialise sockets\n"));
		return 1;
	}

	///////////////////////////////////////////////////////////////////////////

	const int iReceiveBufferSize = 1024 * 1024;
	const DWORD dwExpectedPacketSize = 4096 * 2 * 2 + (sizeof(BOR_PACKET) - 1);

	_tprintf(_T("Initialising...\n"));

	const int iBufferSize = 65536;
	PCHAR pBuffer = new CHAR[iBufferSize];
	HANDLE hDataEvent = NULL;
	SOCKET hDataSocket = INVALID_SOCKET;

	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	ASSERT(hConsole);
	DWORD dwMode = 0;
	if (GetConsoleMode(hConsole, &dwMode) == FALSE)
	{
		_tprintf(_T("GetConsoleMode\n"));
		goto shutdown;
	}
	dwMode &= ~(ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	//dwMode = 0;
	if (SetConsoleMode(hConsole, dwMode) == FALSE)
	{
		_tprintf(_T("SetConsoleMode\n"));
		goto shutdown;
	}

	hDataEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hDataEvent == NULL)
	{
		_tprintf(_T("CreateEvent\n"));
		goto shutdown;
	}

	hDataSocket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (hDataSocket == INVALID_SOCKET)
	{
		_tprintf(_T("SetConsoleMode\n"));
		goto shutdown;
	}

	SOCKADDR_IN addr;
	ZERO_MEMORY(addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_port = htons(BOR_PORT);
	int iResult = bind(hDataSocket, (sockaddr*)&addr, sizeof(addr));
	if (iResult == SOCKET_ERROR)
	{
		_tprintf(_T("bind\n"));
		goto shutdown;
	}

	int iOptLen = sizeof(int);
	if (setsockopt(hDataSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&iReceiveBufferSize, iOptLen) != 0)
	{
		_tprintf(_T("Failed to set socket receive buffer size\n"));
	}

	if (getsockopt(hDataSocket, SOL_SOCKET, SO_RCVBUF, (char*)&iReceiveBufferSize, &iOptLen) == 0)
	{
		_tprintf(_T("Socket receive buffer size: %i\n"), iReceiveBufferSize);
	}
	else
	{
		_tprintf(_T("Failed to get socket receive buffer size\n"));
	}

	WSAOVERLAPPED wsaOverlapped;
	ZERO_MEMORY(wsaOverlapped);
	wsaOverlapped.hEvent = hDataEvent;

	HANDLE hHandles[] = { hDataEvent, hConsole };

	USHORT usCounter = 0;

	//BYTE pConsoleBuf[16384];
	CONSOLE_READCONSOLE_CONTROL ctl;
	ZERO_MEMORY(ctl);
	DWORD dwConsoleRead = 0;

	/*if (WaitForSingleObject(hConsole, 0) == WAIT_OBJECT_0)
	{
		DWORD dw = 0;
		GetNumberOfConsoleInputEvents(hConsole, &dw);
		_tprintf(_T("%lu events outstanding\n"), dw);

		_tprintf(_T("Reading from console...\n"));

		if (ReadConsole(hConsole, pConsoleBuf, sizeof(pConsoleBuf), &dwConsoleRead, &ctl))
		{
			AfxTrace(_T("Read first %lu bytes from console\n"), dwConsoleRead);
		}
	}*/

	//ResetEvent(hConsole);
	FlushConsoleInputBuffer(hConsole);

	SetPriorityClass(GetCurrentProcess(), /*HIGH_PRIORITY_CLASS*/REALTIME_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	_tprintf(_T("Waiting...\n"));

	bool bOn = false;

	while (true)
	{
		WSABUF buf;
		buf.buf = pBuffer;
		buf.len = iBufferSize;

		DWORD dwReceived = 0;
		DWORD dwFlags = 0;

		int iResult = WSARecv(hDataSocket, &buf, 1, &dwReceived, &dwFlags, &wsaOverlapped, NULL);

		ASSERT(dwFlags == 0);

		if (iResult == SOCKET_ERROR)
		{
			DWORD dwError = WSAGetLastError();

			if (dwError != WSA_IO_PENDING)
			{
				ASSERT(FALSE);

				break;
			}

			DWORD dw = WaitForMultipleObjects(sizeof(hHandles)/sizeof(hHandles[0]), hHandles, FALSE, INFINITE);
			if (dw == (WAIT_OBJECT_0 + 1))
			{
				DWORD dwTotal = 0;
				GetNumberOfConsoleInputEvents(hConsole, &dwTotal);
				//_tprintf(_T("Exiting... (%lu events)\n"), dwTotal);

				bool bQuit = false;

				INPUT_RECORD rec;
				for (DWORD dw = 0; dw < dwTotal; ++dw)
				{
					ZERO_MEMORY(rec);
					DWORD dwEventsRead = 0;
					if (ReadConsoleInput(hConsole, &rec, sizeof(rec), &dwEventsRead) == FALSE)
					{
						_tprintf(_T("Failed to read console\n"));
						break;
					}

					if (rec.EventType == KEY_EVENT)
					{
						if (bQuit == false)
							_tprintf(_T("Keypress - exiting...\n"));

						bQuit = true;
						//break;
					}
				}
				
				/*ZERO_MEMORY(ctl);
				if (ReadConsole(hConsole, pConsoleBuf, sizeof(pConsoleBuf), &dwConsoleRead, &ctl) == FALSE)
				{
					_tprintf(_T("Failed to read console\n"));
				}
				else
				{
					//_tprintf(_T("Read %lu bytes from console\n"), dwConsoleRead);
				}*/

				if (bQuit)
					break;
				else
					continue;
			}
			else if (dw == (WAIT_OBJECT_0 + 0))
			{
				dwReceived = 0;
				dwFlags = 0;
				BOOL bResult = WSAGetOverlappedResult(hDataSocket, &wsaOverlapped, &dwReceived, FALSE, &dwFlags);

				ASSERT(dwFlags == 0);

				if (bResult == FALSE)
				{
					DWORD dwError = WSAGetLastError();

					if (dwError == 10040)
					{
						_tprintf(_T("Receive buffer too small\n"));
					}
					else
					{
						ASSERT(FALSE);
					}

					continue;
				}

				iResult = 0;
			}
			else
			{
				ASSERT(FALSE);

				break;
			}
		}

		ASSERT(iResult == 0);

		if (dwReceived == 0)
		{
			ASSERT(FALSE);
			
			continue;
		}
		else if (dwReceived != dwExpectedPacketSize)
		{
			_tprintf(_T("Incorrect packet size: %lu (expected %lu)\n"), dwReceived, dwExpectedPacketSize);

			continue;
		}

		PBOR_PACKET pPacket = (PBOR_PACKET)pBuffer;

		if (pPacket->flags & BF_STREAM_START)
		{
			_tprintf(_T("Stream start (%hu)\n"), pPacket->idx);

			usCounter = pPacket->idx;
			bOn = true;
		}
		else if (pPacket->flags & BF_STREAM_END)
		{
			_tprintf(_T("Stream end (%hu)\n"), pPacket->idx);

			bOn = false;
		}
		else if (bOn == false)
		{
			_tprintf(_T("Caught mid-stream (%hu)\n"), pPacket->idx);

			usCounter = pPacket->idx;
			bOn = true;
		}

		//if (/*(usCounter > 0) && */(pPacket->idx == 0))
		{
			//_tprintf(_T("Starting\n"));

			//usCounter = 0;
		}
		/*else */if (pPacket->idx != usCounter)
		{
			//AfxTrace(_T("Ignoring out-of-sequence packet of %lu bytes (expecting %hu, got %hu, start: %lu, %lu items)\n"), dwReceived, m_usCounter, pPacket->idx, nIndex, m_nNetworkBufferItems);

			//pPacket->flags |= BF_NETWORK_OVERRUN;

			USHORT usLastSkip = pPacket->idx - usCounter;

			_tprintf(_T("Skipped %hu (%hu -> %hu)\n"), usLastSkip, usCounter, pPacket->idx);

			usCounter = pPacket->idx;
		}

		++usCounter;
	}
shutdown:
	if (pBuffer)
		delete [] pBuffer;

	if (hDataSocket != INVALID_SOCKET)
		closesocket(hDataSocket);

	if (hConsole)
		CloseHandle(hConsole);	// FIXME: Necessary?

	if (hDataEvent)
		CloseHandle(hDataEvent);

	return 0;
}

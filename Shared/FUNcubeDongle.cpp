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
/*&
 * This file uses FCD control code from the FCHID006 'Windows fully functional front end'
 * by Howard Long (http://www.funcubedongle.com/)
 */

#include "StdAfx.h"
#include "FUNcubeDongle.h"

#include "PluginFactory.h"
#include "Utils.h"

#define FCD_SAMPLE_RATE	96000
#define BUFFER_LENGTH	1

#ifndef AfxTrace

static void AFX_CDECL _AfxTrace(LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vstprintf_s(szBuffer, _countof(szBuffer), lpszFormat, args); 

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);

	//afxDump << szBuffer;
	OutputDebugString(szBuffer);

	va_end(args);
}

#ifndef _DEBUG
#define AfxTrace	_AfxTrace
#endif // _DEBUG

#endif // _AfxTrace

IMPLEMENT_PF(FUNcubeDongle)

FUNcubeDongle::FUNcubeDongle()
	: m_iDeviceIndex(-1)
	, m_pCaptureDevice(NULL)
	, m_pCaptureBuffer(NULL)
	, m_pNotifications(NULL)
	, m_hNotificationEvent(INVALID_HANDLE_VALUE)
	, m_hQuitEvent(INVALID_HANDLE_VALUE)
	, m_iCaptureNotificationCount(10*2)
	, m_dwReadCursorPosition(0)
	, m_pCaptureThread(NULL)
	, m_nItemSize(0)
	, m_hStopEvent(INVALID_HANDLE_VALUE)
	, m_hPacketEvent(INVALID_HANDLE_VALUE)
	, m_nBufferItems(0)
	, m_pAudioBuffer(NULL)
	, m_nBufferStart(0)
	, m_nBufferSize(0)
	, m_nBufferLockCount(0)
	, m_bSkipNextBlock(false)
	, m_hHIDWrite(INVALID_HANDLE_VALUE)
	, m_hHIDRead(INVALID_HANDLE_VALUE)
{
	m_fpga_master_clock_freq = FCD_SAMPLE_RATE;
	//m_recv_samples_per_packet = FCD_SAMPLE_RATE / m_iCaptureNotificationCount;
	m_dSampleRate = FCD_SAMPLE_RATE;
	m_strAntenna = _T("(Default)");

	m_guidCaptureDevice = GUID_NULL;
	ZeroMemory(&m_descBuffer, sizeof(m_descBuffer));

	m_gainRange = uhd::gain_range_t(-5, 30, 0.5);
}

FUNcubeDongle::~FUNcubeDongle()
{
	Destroy();
}

void FUNcubeDongle::Destroy()
{
	Stop();

	if (m_pCaptureThread)
	{
		if (m_hQuitEvent != INVALID_HANDLE_VALUE)
			SetEvent(m_hQuitEvent);

		WaitForSingleObject(m_pCaptureThread->m_hThread, INFINITE);

		//m_pCaptureThread->Delete();
		delete m_pCaptureThread;
		m_pCaptureThread = NULL;
	}
	
	if (m_pNotifications)
	{
		m_pNotifications->Release();
		m_pNotifications = NULL;
	}

	if (m_pCaptureBuffer)
	{
		m_pCaptureBuffer->Release();
		m_pCaptureBuffer = NULL;
	}

	if (m_pCaptureDevice)
	{
		m_pCaptureDevice->Release();
		m_pCaptureDevice = NULL;
	}

	if (m_hNotificationEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hNotificationEvent);
		m_hNotificationEvent = INVALID_HANDLE_VALUE;
	}

	if (m_hQuitEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hQuitEvent);
		m_hQuitEvent = INVALID_HANDLE_VALUE;
	}

	if (m_hStopEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hStopEvent);
		m_hStopEvent = INVALID_HANDLE_VALUE;
	}

	if (m_hPacketEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hPacketEvent);
		m_hPacketEvent = INVALID_HANDLE_VALUE;
	}

	if (m_hHIDRead != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hHIDRead);
		m_hHIDRead = INVALID_HANDLE_VALUE;
	}

	if (m_hHIDWrite != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hHIDWrite);
		m_hHIDWrite = INVALID_HANDLE_VALUE;
	}

	if (m_pAudioBuffer)
	{
		delete [] m_pAudioBuffer;
		m_pAudioBuffer = NULL;
	}

	if (m_pBuffer)
	{
		delete [] m_pBuffer;
		m_pBuffer = NULL;
	}
}

static BOOL CALLBACK _DSEnumCallback(LPGUID lpGuid, LPCTSTR lpcstrDescription, LPCTSTR lpcstrModule, LPVOID lpContext)
{
	FUNcubeDongle* p = (FUNcubeDongle*)lpContext;
	return p->DSEnumCallback(lpGuid, lpcstrDescription, lpcstrModule);
}

BOOL FUNcubeDongle::DSEnumCallback(LPGUID lpGuid, LPCTSTR lpcstrDescription, LPCTSTR lpcstrModule)
{
	CString str(lpcstrDescription);
	str.MakeLower();

	if (m_iCaptureDeviceIndex == -1)
	{
		
		// FIXME: By name (need to update index for HID)
		//m_strName
	}
	else
	{
		if (str.Find(_T("funcube dongle")) == -1)
			return TRUE;

		if (m_iCaptureDeviceIndex == 0)
		{
			m_guidCaptureDevice = (*lpGuid);
			m_strName = lpcstrDescription;
			m_strSerial = lpcstrDescription;
			return FALSE;
		}
		else
			--m_iCaptureDeviceIndex;
	}

	return TRUE;
}

static UINT _cdecl _CaptureThreadProc(LPVOID pPrivate)
{
	FUNcubeDongle* p = (FUNcubeDongle*)pPrivate;
	
	return p->CaptureThreadProc();
}

bool FUNcubeDongle::Create(LPCTSTR strHint /*= NULL*/)
{
	Destroy();

	m_strLastError.Empty();

	m_hNotificationEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	//ResetEvent(m_hNotificationEvent);
	m_hQuitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hStopEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hPacketEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	m_iDeviceIndex = -1;
	m_strName = _T("(No name)");

	float fIOffset = 0, fQOffset = 0, fGain = 1.0f, fPhase = 0;
	bool bSetDCOffset = false, bSetIQOffset = false;
	float fMixerGain = 0.0f, fIFGain1 = 0.0f;
	bool bSetMixerGain = false, bSetIFGain1 = false;

	CString str(strHint);
	if ((str.GetLength() >= 3) && (str.Left(3).CompareNoCase(_T("fcd")) == 0))
		str = str.Mid(3).Trim();

	CStringArray array;
	if (Teh::Utils::Tokenise(str, array, _T(' ')))
	{
		int iArgIndex = 0;
		for (INT_PTR i = 0; i < array.GetCount(); ++i)
		{
			CString strPart(array[i]);
			int iIndex = strPart.Find(_T('='));
			if (iIndex == -1)
			{
				if (iArgIndex == 0)
				{
					m_iDeviceIndex = _tstoi(strPart);
					if ((m_iDeviceIndex == 0) && (strPart != _T("0")))
					{
						m_iDeviceIndex = -1;
						// FIXME: By name
					}
				}

				if (iArgIndex == 1)
				{
					bSetDCOffset = true;
					fIOffset = (float)_tstof(strPart);
				}
				if (iArgIndex == 2)
					fQOffset = (float)_tstof(strPart);
				if (iArgIndex == 3)
				{
					bSetIQOffset = true;
					fGain = (float)_tstof(strPart);
				}
				if (iArgIndex == 4)
					fPhase = (float)_tstof(strPart);

				++iArgIndex;
			}
			else
			{
				if ((iIndex + 1) == strPart.GetLength())
					continue;

				CString strArg(strPart.Mid(iIndex + 1));
				strPart = strPart.Left(iIndex).MakeLower();
				float f = (float)_tstof(strArg);
				if (strPart == _T("i"))
				{
					bSetDCOffset = true;
					fIOffset = f;
				}
				else if (strPart == _T("q"))
				{
					bSetDCOffset = true;
					fQOffset = f;
				}
				else if (strPart == _T("gain"))
				{
					bSetIQOffset = true;
					fGain = f;
				}
				else if (strPart == _T("phase"))
				{
					bSetIQOffset = true;
					fPhase = f;
				}
				else if (strPart == _T("ifgain1"))
				{
					bSetIFGain1 = true;
					fIFGain1 = f;
				}
				else if (strPart == _T("mixergain"))
				{
					bSetMixerGain = true;
					fMixerGain = f;
				}
				else
				{
					AfxTrace(_T("Unknown FCD parameter key: ") + strPart);
				}
			}
		}
	}

	if (true && (m_iDeviceIndex == -1))	// FIXME: By name
		m_iDeviceIndex = 0;

	m_iCaptureDeviceIndex = m_iDeviceIndex;
	m_guidCaptureDevice = GUID_NULL;
	if (FAILED(DirectSoundCaptureEnumerate(_DSEnumCallback, this)))
	{
		m_strLastError = _T("Failed to enumerate capture devices");
		return false;
	}

	if (m_guidCaptureDevice == GUID_NULL)
	{
		m_strLastError = _T("Failed to find a FUNcube Dongle capture device");
		return false;
	}

	if (FAILED(DirectSoundCaptureCreate8(&m_guidCaptureDevice, &m_pCaptureDevice, NULL)))
	{
		m_strLastError = _T("Failed to create capture device");
		return false;
	}

	WAVEFORMATEX wfx;
	ZeroMemory(&wfx, sizeof(wfx));

	wfx.cbSize = sizeof(wfx);
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 2;
	wfx.nSamplesPerSec = FCD_SAMPLE_RATE;
	wfx.wBitsPerSample = 16;
	wfx.nBlockAlign = wfx.nChannels * (wfx.wBitsPerSample / 8);
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

	ZeroMemory(&m_descBuffer, sizeof(m_descBuffer));

	m_descBuffer.dwSize = sizeof(m_descBuffer);
	m_descBuffer.lpwfxFormat = &wfx;
	m_descBuffer.dwBufferBytes = wfx.nAvgBytesPerSec * BUFFER_LENGTH;

	HRESULT hr = m_pCaptureDevice->CreateCaptureBuffer(&m_descBuffer, &m_pCaptureBuffer, NULL);
	if (FAILED(hr))
	{
		m_strLastError = _T("Failed to create capture buffer");
		return false;
	}

	if (FAILED(m_pCaptureBuffer->QueryInterface(IID_IDirectSoundNotify, (LPVOID*)&m_pNotifications)))
	{
		m_strLastError = _T("Failed to query notification interface");
		return false;
	}

	DSBPOSITIONNOTIFY* pNotifications = new DSBPOSITIONNOTIFY[m_iCaptureNotificationCount];

	DWORD dwSeparation = m_descBuffer.dwBufferBytes / m_iCaptureNotificationCount;
	ASSERT((m_descBuffer.dwBufferBytes % m_iCaptureNotificationCount) == 0);

	for (int i = 1; i <= m_iCaptureNotificationCount; ++i)
	{
		pNotifications[i-1].dwOffset = (dwSeparation * i) - 1;
		pNotifications[i-1].hEventNotify = m_hNotificationEvent;
	}

	hr = m_pNotifications->SetNotificationPositions(m_iCaptureNotificationCount, pNotifications);
	delete [] pNotifications;
	if (FAILED(hr))
	{
		m_strLastError = _T("Failed to set notifications");
		return false;
	}

	m_dwReadCursorPosition = 0;

	///////////////////////////////////////////////////////////////////////////

	static GUID guidInterfaceClass = {0x4d1e55b2, 0xf16f, 0x11cf, 0x88, 0xcb, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30}; 
	static TCHAR _szVIDPID[] = _T("Vid_04d8&Pid_fb56");

	CString strDevSearchID(_szVIDPID);
	strDevSearchID.MakeLower();

	HDEVINFO hDevInfo = SetupDiGetClassDevs(&guidInterfaceClass, 0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);	// Create a HDEVINFO with all present devices
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		m_strLastError = _T("Failed to begin HID enumeration");
		return false;
	}

	m_iCaptureDeviceIndex = m_iDeviceIndex;

	SP_DEVINFO_DATA DeviceInfoData;
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);	// Enumerate through all devices in Set.
	for (DWORD dwDeviceIndex = 0; SetupDiEnumDeviceInfo(hDevInfo, dwDeviceIndex, &DeviceInfoData); dwDeviceIndex++)
	{
		DWORD DataType;
		LPTSTR buffer = NULL;
		DWORD buffersize = 0;

		while (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_HARDWAREID, &DataType, (PBYTE)buffer, buffersize, &buffersize))
		{
			DWORD dwError = ::GetLastError();
			if (dwError == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)	// Change the buffer size
					LocalFree(buffer);
				buffer = (LPTSTR)LocalAlloc(LPTR, buffersize * 2);	// Double the size to avoid problems on W2k MBCS systems per KB 888609
				if (buffer == NULL)
					break;
			}
			else
			{
				break;
			}
		}

		if (buffer == NULL)
			continue;

		CString strHWID(buffer);
		LocalFree(buffer);

		strHWID.MakeLower();

		if ((strHWID.Find(strDevSearchID) > -1) && (m_iCaptureDeviceIndex-- == 0))	// We have found the device, now lets try to open a handles to it
		{
			SP_DEVICE_INTERFACE_DATA dids;
			dids.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

			if (!SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &guidInterfaceClass, dwDeviceIndex, &dids))
			{
				m_strLastError = _T("Failed to enumerate device interfaces");
				break;
			}

			SetupDiGetDeviceInterfaceDetail(hDevInfo, &dids, NULL, 0, &buffersize, NULL);

			PSP_DEVICE_INTERFACE_DETAIL_DATA pdidds = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(buffersize);
			if (pdidds == NULL)
			{
				m_strLastError = _T("Failed to allocate memory for device interface detail data");
				break;
			}

			pdidds->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
			SetupDiGetDeviceInterfaceDetail(hDevInfo, &dids, pdidds, buffersize, NULL, NULL);

			m_hHIDWrite = CreateFile(pdidds->DevicePath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
			m_hHIDRead = CreateFile(pdidds->DevicePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);

			free(pdidds);

			if ((m_hHIDRead != INVALID_HANDLE_VALUE) && (m_hHIDWrite != INVALID_HANDLE_VALUE))
				break;
			else
			{
				if (m_hHIDRead != INVALID_HANDLE_VALUE)
					CloseHandle(m_hHIDRead);
				if (m_hHIDWrite != INVALID_HANDLE_VALUE)
					CloseHandle(m_hHIDWrite);
			}
		}
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);

	if ((m_hHIDRead == INVALID_HANDLE_VALUE) || (m_hHIDWrite == INVALID_HANDLE_VALUE))
	{
		m_strLastError = _T("Failed to open HID");
		return false;
	}

// Send with 2 byte unsigned I DC correction followed by 2 byte unsigned Q DC correction. 32768 is the default centre value.
#define FCD_HID_CMD_SET_DC_CORR      106
// Send with 2 byte signed phase correction followed by 2 byte unsigned gain correction. 0 is the default centre value for phase correction, 32768 is the default centre value for gain.
#define FCD_HID_CMD_SET_IQ_CORR      108
#define FCD_HID_CMD_SET_MIXER_GAIN   114
#define FCD_HID_CMD_SET_IF_GAIN1     117

typedef enum
{
	TMGE_P4_0DB		= 0,
	TMGE_P12_0DB	= 1
} TUNERMIXERGAINENUM;

typedef enum
{
	TIG1E_N3_0DB	= 0,
	TIG1E_P6_0DB	= 1
} TUNERIFGAIN1ENUM;

	if (bSetDCOffset)
	{
		/*unsigned */short iq[] = { min(32767, (short)(fIOffset * 32768.0f)), min(32767, (short)(fQOffset * 32768.0f)) };	// Matching FCHid
		HIDWriteCommand(FCD_HID_CMD_SET_DC_CORR, (unsigned char*)iq, sizeof(iq));
	}

	if (bSetIQOffset)
	{
		/*unsigned */short pg[] = { min(32767, (short)(fPhase * 32768.0f)), (unsigned short)min(65535, (unsigned short)(fGain * 32768.0f)) };
		HIDWriteCommand(FCD_HID_CMD_SET_IQ_CORR, (unsigned char*)pg, sizeof(pg));
	}

	if (bSetMixerGain)
	{
		const static int map[] = {
			04, TMGE_P4_0DB,
			12, TMGE_P12_0DB
		};
		
		int iCount = sizeof(map)/sizeof(map[0]) / 2;
		int i = GetMapIndex(CLAMP(4, (int)fMixerGain, 12), map, iCount);
		if ((i >= 0) && (i < iCount))
		{
			unsigned char u = (unsigned char)map[i + 1];
			HIDWriteCommand(FCD_HID_CMD_SET_MIXER_GAIN, &u, 1);
		}
	}

	if (bSetIFGain1)
	{
		const static int map[] = {
			-3, TIG1E_N3_0DB,
			+6, TIG1E_P6_0DB
		};
		
		int iCount = sizeof(map)/sizeof(map[0]) / 2;
		int i = GetMapIndex(CLAMP(-3, (int)fIFGain1, 6), map, iCount);
		if ((i >= 0) && (i < iCount))
		{
			unsigned char u = (unsigned char)map[i + 1];
			HIDWriteCommand(FCD_HID_CMD_SET_IF_GAIN1, &u, 1);
		}
	}

	///////////////////////////////////////////////////////////////////////////

	m_nBufferLockCount = 0;
	m_bSkipNextBlock = false;

	m_recv_samples_per_packet = ((BUFFER_LENGTH * wfx.nSamplesPerSec) / m_iCaptureNotificationCount);
	m_recv_samples_per_packet -= (m_recv_samples_per_packet % 512);

	m_nItemSize = wfx.nBlockAlign * m_recv_samples_per_packet;
	m_nBufferSize = BUFFER_LENGTH * wfx.nSamplesPerSec;
	ASSERT(m_nBufferSize * wfx.nBlockAlign == m_descBuffer.dwBufferBytes);
	m_pAudioBuffer = new BYTE[m_descBuffer.dwBufferBytes];
	ZeroMemory(m_pAudioBuffer, m_descBuffer.dwBufferBytes);
	m_nBufferStart = 0;
	m_nBufferItems = 0;

	m_pBuffer = (short*)new BYTE[m_nItemSize];

	m_pCaptureThread = AfxBeginThread(_CaptureThreadProc, this, /*THREAD_PRIORITY_NORMAL*/THREAD_PRIORITY_HIGHEST, 0, CREATE_SUSPENDED);
	m_pCaptureThread->m_bAutoDelete = FALSE;
	m_pCaptureThread->ResumeThread();

	//WaitForSingleObject(m_hCaptureThreadReady, INFINITE);

	if (m_fileDump.m_hFile != CFile::hFileNull)
		m_fileDump.Close();

	//m_fileDump.Open(_T("W:\\fcd.pcm"), CFile::modeCreate | CFile::modeWrite);

	return true;
}

bool FUNcubeDongle::Start()
{
	m_strLastError.Empty();

	CSingleLock lock(&m_cs);

	if (m_pCaptureBuffer == NULL)
	{
		m_strLastError = _T("Capture device not yet created");
		return false;
	}

	DWORD dwStatus = 0;
	m_pCaptureBuffer->GetStatus(&dwStatus);
	if (dwStatus & DSCBSTATUS_CAPTURING)
		return true;

	ResetEvent(m_hStopEvent);
	ResetEvent(m_hPacketEvent);

	m_nBufferStart = 0;
	m_nBufferItems = 0;

	DWORD dwCaptureCursor;
AfxTrace(_T("Start: Old read: %lu\n"), m_dwReadCursorPosition);
	m_pCaptureBuffer->GetCurrentPosition(/*NULL*/&dwCaptureCursor, &m_dwReadCursorPosition);
AfxTrace(_T("Start: Capture cursor: %lu, read cursor: %lu\n"), dwCaptureCursor, m_dwReadCursorPosition);
	if (FAILED(m_pCaptureBuffer->Start(DSCBSTART_LOOPING)))
	{
		m_strLastError = _T("Failed to start capture buffer");

		return false;
	}

	m_bRunning = true;

	return true;
}

void FUNcubeDongle::Stop()
{
	CSingleLock lock(&m_cs);

	if (m_pCaptureBuffer == NULL)
		return;

	m_pCaptureBuffer->Stop();

	//m_bSkipNextBlock = true;

	SetEvent(m_hStopEvent);

	m_bRunning = false;
}

typedef enum
{
	TLGE_N5_0DB=0,
	TLGE_N2_5DB=1,
	TLGE_P0_0DB=4,
	TLGE_P2_5DB=5,
	TLGE_P5_0DB=6,
	TLGE_P7_5DB=7,
	TLGE_P10_0DB=8,
	TLGE_P12_5DB=9,
	TLGE_P15_0DB=10,
	TLGE_P17_5DB=11,
	TLGE_P20_0DB=12,
	TLGE_P25_0DB=13,
	TLGE_P30_0DB=14
} TUNERLNAGAINENUM;

BOOL FUNcubeDongle::HIDWriteCommand(unsigned __int8 u8Cmd, unsigned __int8 *pu8Data, unsigned __int8 u8Len)
{
	DWORD dwBytesWritten = 0;
	DWORD dwBytesRead = 0;

	unsigned char au8BufOut[65];	// endpoint size + 1
	unsigned char au8BufIn[65];		// endpoint size + 1

	// Clean out any outstanding reads
	au8BufOut[0] = 0; // First byte is report ID. Ignored by HID Class firmware as only config'd for one report
	au8BufOut[1] = u8Cmd;
	memcpy(au8BufOut + 2, pu8Data, u8Len);
	//Sleep(10);

	WriteFile(m_hHIDWrite, au8BufOut, 65, &dwBytesWritten, 0);
	ReadFile(m_hHIDRead, au8BufIn, 65, &dwBytesRead, 0);

	return au8BufIn[2];
}


bool FUNcubeDongle::SetGain(double dGain)
{
	static int mapGains[] = {
		-50,	TLGE_N5_0DB,
		-25,	TLGE_N2_5DB,
		0,		TLGE_P0_0DB,
		25,		TLGE_P2_5DB,
		50,		TLGE_P5_0DB,
		75,		TLGE_P7_5DB,
		100,	TLGE_P10_0DB,
		125,	TLGE_P12_5DB,
		150,	TLGE_P15_0DB,
		175,	TLGE_P17_5DB,
		200,	TLGE_P20_0DB,
		250,	TLGE_P25_0DB,
		300,	TLGE_P30_0DB
	};

	int iGain = (int)(dGain * 10.0);
	//int i = 0;
	int iCount = (sizeof(mapGains)/sizeof(mapGains[0])) / 2;
	/*for (; i < iCount; i++)
	{
		if (mapGains[i*2 + 0] >= iGain)
		{
			if (mapGains[i*2 + 0] > iGain)
				--i;

			break;
		}
	}*/
	int i = GetMapIndex(iGain, mapGains, iCount);

	if ((i == -1) || (i == iCount))
		return false;

	unsigned __int8 u8Write = mapGains[i + 1];

	if (HIDWriteCommand(110, &u8Write, 1) == FALSE)
		return false;

	m_dGain = (double)mapGains[i] / 10.0;

	return true;
}

bool FUNcubeDongle::SetAntenna(int iIndex)
{
	return true;
}

bool FUNcubeDongle::SetAntenna(LPCTSTR strAntenna)
{
	return true;
}

double FUNcubeDongle::SetFreq(double dFreq)
{
	m_strLastError.Empty();

	if ((m_hHIDRead == INVALID_HANDLE_VALUE) || (m_hHIDWrite == INVALID_HANDLE_VALUE))
	{
		m_strLastError = _T("Invalid HID handle");
		return -1;
	}

	DWORD dwBytesWritten = 0;
	DWORD dwBytesRead = 0;
	const int iSize = 64 + 1;	// endpoint size + 1
	unsigned char au8BufOut[iSize];
	unsigned char au8BufIn[iSize];

	int nFreq = (int)(dFreq/* / 1000.0*/);

	au8BufOut[0] = 0;	// First byte is report ID. Ignored by HID Class firmware as only config'd for one report
	au8BufOut[1] = /*100*/101;
	au8BufOut[2] = (unsigned char)nFreq;
	au8BufOut[3] = (unsigned char)(nFreq >> 8);
	au8BufOut[4] = (unsigned char)(nFreq >> 16);
	au8BufOut[5] = (unsigned char)(nFreq >> 24);

	if ((WriteFile(m_hHIDWrite, au8BufOut, iSize, &dwBytesWritten, 0) == 0) ||
		(ReadFile(m_hHIDRead, au8BufIn, iSize, &dwBytesRead, 0) == 0))
	{
		m_strLastError = _T("HID communication failure");
		return -1;
	}

	if (au8BufIn[2] != 1)
	{
		m_strLastError = _T("Failure response");
		return -1;
	}

	//return dFreq;

	memcpy(&nFreq, &au8BufIn[3], sizeof(int));

	m_tuneResult./*target_inter_freq*/target_rf_freq = dFreq;
	m_tuneResult./*actual_inter_freq*/actual_rf_freq = nFreq;

	return (m_dFreq = nFreq);
}

double FUNcubeDongle::SetSampleRate(double dSampleRate)
{
	return FCD_SAMPLE_RATE;
}

std::vector<std::string> FUNcubeDongle::GetAntennas() const
{
	std::vector<std::string> array;
	array.push_back(/*"(Default)"*/(LPCSTR)CStringA(m_strAntenna));
	return array;
}

int FUNcubeDongle::ReadPacket()
{
	CSingleLock lock(&m_cs, TRUE);

	if (m_pCaptureBuffer == NULL)
		return -1;

	//DWORD dwStatus = 0;
	//m_pCaptureBuffer->GetStatus(&dwStatus);
	//if ((dwStatus & DSCBSTATUS_CAPTURING) == 0)
	//	return -1;

	if (m_nBufferItems < m_recv_samples_per_packet)
	{
		lock.Unlock();

		HANDLE hHandles[] = { m_hStopEvent, m_hPacketEvent/*, m_bAbortEvent*/ };

		//AfxTrace(_T("Waiting for packet\n"));

		DWORD dw = WaitForMultipleObjects(sizeof(hHandles)/sizeof(hHandles[0]), hHandles, FALSE, INFINITE);
		if (dw == (WAIT_OBJECT_0 + 0))
		{
			return 0;
		}
		else if (dw == (WAIT_OBJECT_0 + 1))
		{
			lock.Lock();
		}
		/*else if (dw == (WAIT_OBJECT_0 + 2))
		{
			return -1;
		}*/
		else
		{
			ASSERT(FALSE);

			return 0;
		}
	}

	if (m_nBufferItems < m_recv_samples_per_packet)
	{
AfxTrace(_T("Reading packet after signal, but no items in buffer (start now %lu)\n"), m_nBufferStart);	// FIXME: Why does this happen?
		return 0;
	}

	UINT nPart1 = min(m_recv_samples_per_packet, m_nBufferSize - m_nBufferStart);
	memcpy(m_pBuffer, (m_pAudioBuffer + ((2 * sizeof(short)) * m_nBufferStart)), nPart1 * 2 * sizeof(short));
	UINT nResidual = m_recv_samples_per_packet - nPart1;
	if (nResidual > 0)
		memcpy(m_pBuffer + (nPart1 * 2), m_pAudioBuffer, nResidual * 2 * sizeof(short));	// short* pointer, so "* sizeof(short)" not necessary in pointer offset

	m_nSamplesReceived += m_recv_samples_per_packet;

	if (false)	// FIXME: Flag
	{
		++m_nOverflows;

		m_metadata.error_code = uhd::rx_metadata_t::ERROR_CODE_OVERFLOW;
	}
	else
		m_metadata.error_code = uhd::rx_metadata_t::ERROR_CODE_NONE;

	m_nBufferItems -= m_recv_samples_per_packet;

	//ASSERT(m_nBufferItems != -1);

	if (m_nBufferItems > 0)
		m_nBufferStart = (m_nBufferStart + m_recv_samples_per_packet) % m_nBufferSize;

	//AfxTrace(_T("Read packet: start=%lu, items=%lu\n"), m_nBufferStart, m_nBufferItems);

	if (m_fileDump.m_hFile != CFile::hFileNull)
		m_fileDump.Write(m_pBuffer, m_recv_samples_per_packet * 2 * sizeof(short));

	return m_recv_samples_per_packet;
}

UINT FUNcubeDongle::CaptureThreadProc()
{
	AfxTrace(_T("Capture threading %04x starting...\n"), GetCurrentThreadId());

	//WAVEFORMATEX wfx;
	//m_pCaptureBuffer->GetFormat();

	DWORD dwSeparation = m_descBuffer.dwBufferBytes / m_iCaptureNotificationCount;

	CSingleLock lock(&m_cs, FALSE);

	LPBYTE pBuffer = new BYTE[/*dwSeparation*/m_descBuffer.dwBufferBytes];

	//while (((nCount == 0) && (SignalObjectAndWait(m_hCaptureThreadReady, m_hNotificationEvent, INFINITE, FALSE) == WAIT_OBJECT_0)) ||
	//		((nCount > 0) && (WaitForSingleObject(m_hNotificationEvent, INFINITE) == WAIT_OBJECT_0)))
	while (true)
	{
		HANDLE hHandles[] = { m_hNotificationEvent, m_hQuitEvent };

		DWORD dw = WaitForMultipleObjects(sizeof(hHandles)/sizeof(hHandles[0]), hHandles, FALSE, INFINITE);
		if (dw == (WAIT_OBJECT_0 + 0))
		{
			//
		}
		else if (dw == (WAIT_OBJECT_0 + 1))
		{
			break;
		}
		else
		{
			ASSERT(FALSE);
			break;
		}

		lock.Lock();

		DWORD dwStatus = 0;
		m_pCaptureBuffer->GetStatus(&dwStatus);
		if ((dwStatus & DSCBSTATUS_CAPTURING) == 0)
		{
			lock.Unlock();
			continue;
		}

		////////////////

		DWORD dwCapturePos, dwReadPos;
		if (FAILED(m_pCaptureBuffer->GetCurrentPosition(&dwCapturePos, &dwReadPos)))
		{
			lock.Unlock();
			ASSERT(FALSE);
			break;
		}

		LONG lLockSize = dwReadPos - m_dwReadCursorPosition;
		if (lLockSize < 0)
			lLockSize += m_descBuffer.dwBufferBytes;

		lLockSize -= (lLockSize % dwSeparation);

		if (lLockSize == 0)
		{
			lock.Unlock();
//AfxTrace(_T("Zero lock size: capture: %lu, read: %lu, last read: %lu\n"), dwCapturePos, dwReadPos, m_dwReadCursorPosition);
			continue;
		}
if (lLockSize % (2 * sizeof(short)))
{
	AfxTrace(_T("Lock size not divisible by sample size: %lu, cap: %lu, read: %lu, pos: %lu\n"), lLockSize, dwCapturePos, dwReadPos, m_dwReadCursorPosition);
}
		////////////////

		LPVOID p1, p2;
		DWORD dw1, dw2;

		++m_nBufferLockCount;
DWORD dwEnd = (m_dwReadCursorPosition + lLockSize) % m_descBuffer.dwBufferBytes;
if (dwCapturePos == m_dwReadCursorPosition)
{
	AfxTrace(_T("Error 3: cap: %lu, read: %lu, pos: %lu, len: %lu\n"), dwCapturePos, dwReadPos, m_dwReadCursorPosition, lLockSize);
}
else if (dwReadPos > m_dwReadCursorPosition)
{
	if ((dwEnd > dwReadPos) || (dwEnd < m_dwReadCursorPosition))
	{
		AfxTrace(_T("Error 1: cap: %lu, read: %lu, pos: %lu, len: %lu\n"), dwCapturePos, dwReadPos, m_dwReadCursorPosition, lLockSize);
	}
}
else if (dwReadPos < m_dwReadCursorPosition)
{
	if ((dwEnd > dwReadPos) && (dwEnd < m_dwReadCursorPosition))
	{
		AfxTrace(_T("Error 2: cap: %lu, read: %lu, pos: %lu, len: %lu\n"), dwCapturePos, dwReadPos, m_dwReadCursorPosition, lLockSize);
	}
}
		if (//(m_bSkipNextBlock == false) &&
			SUCCEEDED(m_pCaptureBuffer->Lock(m_dwReadCursorPosition/* + *//*dwSeparation * (m_nBufferLockCount - 1)) % m_descBuffer.dwBufferBytes*/, /*dwSeparation*/lLockSize, &p1, &dw1, &p2, &dw2, 0)))
		{
			memcpy(pBuffer, p1, dw1);
			m_dwReadCursorPosition = (m_dwReadCursorPosition + dw1) % m_descBuffer.dwBufferBytes;

			if (dw2)
			{
//AfxTrace(_T("Double lock: cap: %lu, read: %lu, pos: %lu, len: %lu -> %lu + %lu\n"), dwCapturePos, dwReadPos, m_dwReadCursorPosition, lLockSize, dw1, dw2);
				memcpy(pBuffer + dw1, p2, dw2);
				m_dwReadCursorPosition = (m_dwReadCursorPosition + dw2) % m_descBuffer.dwBufferBytes;
			}

			m_pCaptureBuffer->Unlock(p1, dw1, p2, dw2);
if ((dw1 + dw2) != lLockSize)
{
AfxTrace(_T("Lock size error: cap: %lu, read: %lu, pos: %lu, len: %lu -> %lu + %lu\n"), dwCapturePos, dwReadPos, m_dwReadCursorPosition, lLockSize, dw1, dw2);
}
			//if (m_fileDump.m_hFile != CFile::hFileNull)
			//	m_fileDump.Write(pBuffer, (dw1 + dw2));

			UINT nRemaining = min(m_nBufferSize - m_nBufferItems, /*dwSeparation*/lLockSize / (2 * sizeof(short)));

			if ((m_bSkipNextBlock == false) && (nRemaining > 0))
			{
				//AfxTrace(_T("Notification: count=%lu, start=%lu, items=%lu\n"), nCount, m_nBufferStart, m_nBufferItems);

				LPBYTE p = m_pAudioBuffer + (((m_nBufferStart + m_nBufferItems) % m_nBufferSize) * (2 * sizeof(short)));
				//DWORD dwToCopy = nRemaining * 2 * sizeof(short);
				//DWORD dwCopied = 0;

				UINT nPart1 = (m_nBufferStart + m_nBufferItems) % m_nBufferSize;
				UINT nSize1 = min(nRemaining, m_nBufferSize - nPart1);

				memcpy(p, pBuffer, nSize1 * 2 * sizeof(short));

				//if (m_fileDump.m_hFile != CFile::hFileNull)
				//	m_fileDump.Write(pBuffer, nSize1 * 2 * sizeof(short));

				UINT nResidual = nRemaining - nSize1;
				if (nResidual > 0)
				{
					memcpy(m_pAudioBuffer, pBuffer + (nSize1 * 2 * sizeof(short)), nResidual * 2 * sizeof(short));

					//if (m_fileDump.m_hFile != CFile::hFileNull)
					//	m_fileDump.Write(pBuffer + (nSize1 * 2 * sizeof(short)), nResidual * 2 * sizeof(short));
				}

				m_nBufferItems += nRemaining;
			}
			else if (m_bSkipNextBlock)
			{
AfxTrace(_T("Skipping block: cap: %lu, read: %lu, pos: %lu, len: %lu -> %lu + %lu\n"), dwCapturePos, dwReadPos, m_dwReadCursorPosition, lLockSize, dw1, dw2);
				m_bSkipNextBlock = false;
			}
			else// if (nRemaining == 0)
			{
AfxTrace(_T("OVERRUN: Remaining: %lu\n"), nRemaining);	// FIXME: Overrun
			}

			lock.Unlock();

			SetEvent(m_hPacketEvent);
		}
		else
		{
			//m_bSkipNextBlock = false;
AfxTrace(_T("Failed to lock\n"));
			lock.Unlock();
		}
	}

	delete [] pBuffer;

	AfxTrace(_T("Capture threading %04x exiting\n"), GetCurrentThreadId());

	return 0;
}

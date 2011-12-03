#include "StdAfx.h"
#include "FUNcubeDongle.h"

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

FUNcubeDongle::FUNcubeDongle()
	: m_iDeviceIndex(-1)
	, m_pCaptureDevice(NULL)
	, m_pCaptureBuffer(NULL)
	, m_pNotifications(NULL)
	, m_hNotificationEvent(INVALID_HANDLE_VALUE)
	, m_hQuitEvent(INVALID_HANDLE_VALUE)
	, m_iCaptureNotificationCount(10)
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

	CString str(strHint);
	if ((str.GetLength() >= 3) && (str.Left(3).CompareNoCase(_T("fcd")) == 0))
		str = str.Mid(3).Trim();

	CStringArray array;
	if (Teh::Utils::Tokenise(str, array, _T(' ')))
	{
		m_iDeviceIndex = _tstoi(array[0]);
		if ((m_iDeviceIndex == 0) && (array[0] != _T("0")))
		{
			m_iDeviceIndex = -1;
			// FIXME: By name
		}

		if (array.GetCount() > 1)
		{
			bSetDCOffset = true;
			fIOffset = _tstof(array[1]);
		}
		if (array.GetCount() > 2)
			fQOffset = _tstof(array[2]);
		if (array.GetCount() > 3)
		{
			bSetIQOffset = true;
			fGain = _tstof(array[3]);
		}
		if (array.GetCount() > 4)
			fPhase = _tstof(array[4]);
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

	if (bSetDCOffset)
	{
		/*unsigned */short iq[] = { min(32767, (fIOffset * 32768)), min(32767, (fQOffset * 32768)) };	// Matching FCHid
		HIDWriteCommand(FCD_HID_CMD_SET_DC_CORR, (unsigned char*)iq, sizeof(iq));
	}
	
	if (bSetIQOffset)
	{
		/*unsigned */short pg[] = { min(32767, (fPhase * 32768)), (unsigned short)min(65535, (fGain * 32768)) };
		HIDWriteCommand(FCD_HID_CMD_SET_IQ_CORR, (unsigned char*)pg, sizeof(pg));
	}

	///////////////////////////////////////////////////////////////////////////

	m_nBufferLockCount = 0;
	m_bSkipNextBlock = false;

	m_recv_samples_per_packet = ((BUFFER_LENGTH * wfx.nSamplesPerSec) / m_iCaptureNotificationCount);
	m_recv_samples_per_packet -= (m_recv_samples_per_packet % 512);

	m_nItemSize = wfx.nBlockAlign * m_recv_samples_per_packet;
	m_nBufferSize = BUFFER_LENGTH *  wfx.nSamplesPerSec;
	m_pAudioBuffer = new BYTE[m_descBuffer.dwBufferBytes];
	ZeroMemory(m_pAudioBuffer, m_descBuffer.dwBufferBytes);
	m_nBufferStart = 0;
	m_nBufferItems = 0;

	m_pBuffer = (short*)new BYTE[m_nItemSize];

	m_pCaptureThread = AfxBeginThread(_CaptureThreadProc, this, /*THREAD_PRIORITY_NORMAL*/THREAD_PRIORITY_HIGHEST, 0, CREATE_SUSPENDED);
	m_pCaptureThread->m_bAutoDelete = FALSE;
	m_pCaptureThread->ResumeThread();

	//WaitForSingleObject(m_hCaptureThreadReady, INFINITE);

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

	m_pCaptureBuffer->GetCurrentPosition(NULL, &m_dwReadCursorPosition);

	if (FAILED(m_pCaptureBuffer->Start(DSCBSTART_LOOPING)))
	{
		m_strLastError = _T("Failed to start capture buffer");

		return false;
	}

	return true;
}

void FUNcubeDongle::Stop()
{
	CSingleLock lock(&m_cs);

	if (m_pCaptureBuffer == NULL)
		return;

	m_pCaptureBuffer->Stop();

	m_bSkipNextBlock = true;

	SetEvent(m_hStopEvent);
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
	int i = 0;
	int iCount = (sizeof(mapGains)/sizeof(mapGains[0])) / 2;
	for (; i < iCount; i++)
	{
		if (mapGains[i*2 + 0] >= iGain)
		{
			if (mapGains[i*2 + 0] > iGain)
				--i;

			break;
		}
	}

	if (i == iCount)
		return false;

	unsigned __int8 u8Write = mapGains[i*2 + 1];

	return I2B(HIDWriteCommand(110, &u8Write, 1));
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

	return nFreq;
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
		else if (dw == (WAIT_OBJECT_0 + 2))
		{
			return -1;
		}
		else
		{
			ASSERT(FALSE);

			return 0;
		}
	}

	if (m_nBufferItems < m_recv_samples_per_packet)
	{
		//AfxTrace(_T("Reading packet after signal, but no items in buffer (start now %lu)\n"), m_nBufferStart);	// FIXME: Why does this happen?

		return 0;
	}

	UINT nPart1 = min(m_recv_samples_per_packet, m_nBufferSize - m_nBufferStart);
	memcpy(m_pBuffer, (m_pAudioBuffer + ((2 * sizeof(short)) * m_nBufferStart)), nPart1 * 2 * sizeof(short));
	UINT nResidual = m_recv_samples_per_packet - nPart1;
	if (nResidual > 0)
		memcpy(m_pBuffer + (2 * nPart1), m_pAudioBuffer, nResidual * 2 * sizeof(short));

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

	return m_recv_samples_per_packet;
}

UINT FUNcubeDongle::CaptureThreadProc()
{
	AfxTrace(_T("Capture threading %04x starting...\n"), GetCurrentThreadId());

	//WAVEFORMATEX wfx;
	//m_pCaptureBuffer->GetFormat();

	DWORD dwSeparation = m_descBuffer.dwBufferBytes / m_iCaptureNotificationCount;

	CSingleLock lock(&m_cs, FALSE);

	LPBYTE pBuffer = new BYTE[dwSeparation];

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

		LPVOID p1, p2;
		DWORD dw1, dw2;

		++m_nBufferLockCount;

		if ((m_bSkipNextBlock == false) &&
			SUCCEEDED(m_pCaptureBuffer->Lock((/*m_dwReadCursorPosition + */dwSeparation * (m_nBufferLockCount - 1)) % m_descBuffer.dwBufferBytes, dwSeparation, &p1, &dw1, &p2, &dw2, 0)))
		{
			memcpy(pBuffer, p1, dw1);
			if (dw2)
				memcpy(pBuffer + dw1, p2, dw2);

			m_pCaptureBuffer->Unlock(p1, dw1, p2, dw2);

			UINT nRemaining = min(m_nBufferSize - m_nBufferItems, dwSeparation / (2 * sizeof(short)));

			if (nRemaining > 0)
			{
				//AfxTrace(_T("Notification: count=%lu, start=%lu, items=%lu\n"), nCount, m_nBufferStart, m_nBufferItems);

				LPBYTE p = m_pAudioBuffer + (((m_nBufferStart + m_nBufferItems) % m_nBufferSize) * (2 * sizeof(short)));
				//DWORD dwToCopy = nRemaining * 2 * sizeof(short);
				//DWORD dwCopied = 0;

				UINT nPart1 = (m_nBufferStart + m_nBufferItems) % m_nBufferSize;
				UINT nSize1 = min(nRemaining, m_nBufferSize - nPart1);

				memcpy(p, pBuffer, nSize1 * 2 * sizeof(short));

				UINT nResidual = nRemaining - nSize1;
				if (nResidual > 0)
					memcpy(m_pAudioBuffer, pBuffer + nSize1 * 2 * sizeof(short), nResidual * 2 * sizeof(short));

				m_nBufferItems += nRemaining;
			}
			else
			{
				//AfxTrace(_T("OVERRUN\n"));	// FIXME: Overrun
			}

			lock.Unlock();

			SetEvent(m_hPacketEvent);
		}
		else
		{
			m_bSkipNextBlock = false;

			lock.Unlock();
		}
	}

	delete [] pBuffer;

	AfxTrace(_T("Capture threading %04x exiting\n"), GetCurrentThreadId());

	return 0;
}

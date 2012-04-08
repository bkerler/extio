#include "StdAfx.h"
#include "rtl2832-extio.h"

#include "PluginFactory.h"
#include "Utils.h"

#define DEFAULT_READLEN			(/*16 * */16384 * 2)	// This is good compromise between maintaining a good buffer level and immediate response to parameter adjustment
#define DEFAULT_BUFFER_MUL		(4*2)
#define DEFAULT_BUFFER_LEVEL	0.5f
#define WAIT_FUDGE				(1.2+0.3)
#define RAW_SAMPLE_SIZE			(1+1)

IMPLEMENT_PF(RTL2832)

RTL2832::RTL2832()
	: m_pCaptureThread(NULL)
	, m_nItemSize(0)
	, m_hStopEvent(INVALID_HANDLE_VALUE)
	, m_hPacketEvent(INVALID_HANDLE_VALUE)
	, m_hAbortEvent(INVALID_HANDLE_VALUE)
	, m_nBufferItems(0)
	, m_pUSBBuffer(NULL)
	, m_nBufferStart(0)
	, m_nBufferSize(0)
	, m_bBuffering(false)
	, m_pConversionBuffer(NULL)
	, m_nReadLength(DEFAULT_READLEN)
	, m_nBufferMultiplier(DEFAULT_BUFFER_MUL)
	, m_bUseBuffer(true)
	, m_fBufferLevel(DEFAULT_BUFFER_LEVEL)
	, m_nReadPacketCount(0)
	, m_nBufferOverflowCount(0)
	, m_nBufferUnderrunCount(0)
	, m_dwReadPacketWait(0)
	, m_bExternalCall(false)
{
	ZERO_MEMORY(m_demod_params);

	m_strAntenna = _T("(Default)");
	m_recv_samples_per_packet = /*READLEN / RAW_SAMPLE_SIZE*/4096;	// Already on 512-byte boundary (after converting to shorts, will still be)
	m_dSampleRate = 1000000;

	QueryPerformanceFrequency(&m_liFreq);
}

RTL2832::~RTL2832()
{
	Destroy();
}

///////////////////////////////////////////////////////////////////////////////

void RTL2832::on_log_message_va(int level, const char* msg, va_list args)
{
	CHAR szBuffer[512];
	int nBuf = vsprintf_s(szBuffer, _countof(szBuffer), msg, args);
	ASSERT(nBuf >= 0);	// was there an error? was the expanded string too long?
	OutputDebugStringA(szBuffer);
	va_end(args);

	if ((m_bExternalCall)/* && (level <= rtl2832::log_sink::LOG_LEVEL_ERROR)*/)
		m_strLastError = CStringA(szBuffer).Trim();
}

bool RTL2832::Create(LPCTSTR strHint /*= NULL*/)
{
	Destroy();

	m_strLastError.Empty();

	m_nReadLength			= DEFAULT_READLEN;
	m_nBufferMultiplier		= DEFAULT_BUFFER_MUL;
	m_fBufferLevel			= DEFAULT_BUFFER_LEVEL;
	m_bUseBuffer			= true;

	memset(&m_demod_params, 0x00, sizeof(m_demod_params));

	m_demod_params.message_output = this;
	m_demod_params.verbose = true;

	/////////////////////////

	CString str(strHint);
	if ((str.GetLength() >= 3) && (str.Left(3).CompareNoCase(_T("rtl")) == 0))
		str = str.Mid(3).Trim();

	bool bAutoGainMode = false;
	CString strGainMode;

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
/*				if (iArgIndex == 0)
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
					//
				}
*/
				++iArgIndex;
			}
			else
			{
				if ((iIndex + 1) == strPart.GetLength())
					continue;

				CString strArg(strPart.Mid(iIndex + 1));
				strPart = strPart.Left(iIndex).MakeLower();
				float f = (float)_tstof(strArg);
				int i = _tstoi(strArg);
				if (strPart == _T("readlen"))
				{
					i = i - (i % 512);
					if (i > 0)
						m_nReadLength = i;
				}
				else if (strPart == _T("bufmul"))
				{
					if (i > 0)
						m_nBufferMultiplier = i;
				}
/*				else if (strPart == _T("spp"))
				{
					i = i - (i % 512);
					if (i > 0)
						m_recv_samples_per_packet = i;
				}
*/				else if (strPart == _T("buf"))
				{
					m_bUseBuffer = (i != 0);
				}
				else if (strPart == _T("buflvl"))
				{
					if ((f >= 0) && (f <= 100))
						m_fBufferLevel = f / 100.0f;
				}
				else if (strPart == _T("xtalfreq"))
				{
					m_demod_params.crystal_frequency = i;
				}
				else if (strPart == _T("timeout"))
				{
					m_demod_params.default_timeout = i;
				}
				else if (strPart == _T("vid"))
				{
					if (i == 0)
					{
						int iIndex = strArg.Find(_T('x'));
						if (iIndex > -1)
							strArg = strArg.Mid(iIndex + 1);
						_stscanf_s(strArg, _T("%x"), &i);
					}

					m_demod_params.vid = i;
				}
				else if (strPart == _T("pid"))
				{
					if (i == 0)
					{
						int iIndex = strArg.Find(_T('x'));
						if (iIndex > -1)
							strArg = strArg.Mid(iIndex + 1);
						_stscanf_s(strArg, _T("%x"), &i);
					}

					m_demod_params.pid = i;
				}
				else if (strPart == _T("tuner"))
				{
					strcpy_s(m_demod_params.tuner_name, rtl2832::demod::TUNER_NAME_LEN, CStringA(strArg));
				}
				else if (strPart == _T("autogainmode"))
				{
					bAutoGainMode = (i != 0);
				}
				else if (strPart == _T("gainmode"))
				{
					strGainMode = strArg;
				}
				else
				{
					AfxTrace(_T("Unknown RTL parameter key: ") + strPart);
				}
			}
		}
	}

	m_recv_samples_per_packet = m_nReadLength / RAW_SAMPLE_SIZE;	// Must be the same since rate is determined by the libusb reads!

	/////////////////////////

	m_hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hPacketEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hAbortEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	m_nBufferSize = (m_nReadLength / RAW_SAMPLE_SIZE) * m_nBufferMultiplier;
	m_pUSBBuffer = new BYTE[m_nBufferSize * RAW_SAMPLE_SIZE];
	ZeroMemory(m_pUSBBuffer, m_nBufferSize * RAW_SAMPLE_SIZE);

	m_nItemSize = m_recv_samples_per_packet * 2 * sizeof(short);
	m_pBuffer = (short*)new BYTE[m_nItemSize];

	m_pConversionBuffer = new BYTE[m_nReadLength];

	AfxTrace(_T("Configuration:\n")
		_T("\tRead length (bytes): %lu\n")
		_T("\tBuffer enabled: %s\n")
		_T("\tBuffer multiplier: %lu\n")
		_T("\tBuffer size (samples): %lu\n")
		_T("\tSPP (samples): %lu\n")
		_T("\tBuffer level: %.1f%%\n"),
		m_nReadLength,
		(m_bUseBuffer ? _T("yes") : _T("no")),
		m_nBufferMultiplier,
		m_nBufferSize,
		m_recv_samples_per_packet,
		(100.0f * m_fBufferLevel)
	);

	/////////////////////////

	{ SCOPED_LOG_MONITOR(m_bExternalCall);
	if (m_demod.initialise(&m_demod_params) != RTL2832_NAMESPACE::SUCCESS)
		return false;
	}

	m_strName = CStringA(m_demod.name());
	rtl2832::range_t gr = m_demod.active_tuner()->gain_range();
	rtl2832::values_t listGains = m_demod.active_tuner()->gain_values();
	double dGainStep = 1.0;
	for (rtl2832::values_t::iterator it = listGains.begin(); it != listGains.end(); ++it)
	{
		double d = (*it);
		if (d < 0)
			d = -d;
		d = d - floor(d);
		if (d > 1e-3)
			dGainStep = min(dGainStep, d);
	}

	m_gainRange =  uhd::gain_range_t(gr.first, gr.second, dGainStep);

	m_fpga_master_clock_freq = /*m_demod.crystal_frequency()*/3200000;

	if (bAutoGainMode)
	{
		{ SCOPED_LOG_MONITOR(m_bExternalCall);
		if (m_demod.active_tuner()->set_auto_gain_mode() != RTL2832_NAMESPACE::SUCCESS)
			return false;
		}
	}

	if (strGainMode.IsEmpty() == false)
	{
		int iMode;
		bool bFound = false;

		RTL2832_NAMESPACE::num_name_map_t map = m_demod.active_tuner()->gain_modes();
		for (RTL2832_NAMESPACE::num_name_map_t::iterator it = map.begin(); it != map.end(); ++it)
		{
			if (CStringA(strGainMode).CompareNoCase(it->second.c_str()) == 0)
			{
				iMode = it->first;
				bFound = true;
				break;
			}
		}

		if (bFound == false)
		{
			m_strLastError.Format(_T("Specified gain mode \"%s\" not supported by \"%s\" tuner"), strGainMode, CString(m_demod.active_tuner()->name()));
			return false;
		}

		{ SCOPED_LOG_MONITOR(m_bExternalCall);
		if (m_demod.active_tuner()->set_gain_mode(iMode) != RTL2832_NAMESPACE::SUCCESS)
			return false;
		}
	}

	return true;
}

void RTL2832::Destroy()
{
	Stop();

	m_demod.destroy();

	SAFE_DELETE_ARRAY(m_pBuffer);
	SAFE_DELETE_ARRAY(m_pUSBBuffer);
	SAFE_DELETE_ARRAY(m_pConversionBuffer);

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

	if (m_hAbortEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hAbortEvent);
		m_hAbortEvent = INVALID_HANDLE_VALUE;
	}
}

static UINT _cdecl _CaptureThreadProc(LPVOID pPrivate)
{
	RTL2832* p = (RTL2832*)pPrivate;
	
	return p->CaptureThreadProc();
}

void RTL2832::Reset()
{
	CSingleLock lock(&m_cs, TRUE);

	m_nBufferStart = 0;
	m_nBufferItems = 0;
	m_nSamplesReceived = 0;
	m_nOverflows = 0;

	m_nReadPacketCount = 0;
	m_nBufferOverflowCount = 0;
	m_nBufferUnderrunCount = 0;

	if (m_bRunning)
		return;

	ResetEvent(m_hStopEvent);
	ResetEvent(m_hPacketEvent);
	ResetEvent(m_hAbortEvent);
}

bool RTL2832::Start()
{
	m_strLastError.Empty();

	CSingleLock lock(&m_cs, TRUE);

	if (m_bRunning)
		return true;

	Reset();

	{ SCOPED_LOG_MONITOR(m_bExternalCall);
	if (m_demod.reset() != RTL2832_NAMESPACE::SUCCESS)
		return false;
	}

	m_bBuffering = true;

	if (m_bUseBuffer)
	{
		m_pCaptureThread = AfxBeginThread(_CaptureThreadProc, this, /*THREAD_PRIORITY_NORMAL*/THREAD_PRIORITY_HIGHEST, 0, CREATE_SUSPENDED);
		m_pCaptureThread->m_bAutoDelete = FALSE;
		m_pCaptureThread->ResumeThread();
	}

	m_bRunning = true;

	return true;
}

void RTL2832::Stop()
{
	CSingleLock lock(&m_cs, TRUE);

	if (m_bRunning == false)
		return;

	if (m_pCaptureThread == NULL)
	{
		m_bRunning = false;
		return;
	}

	lock.Unlock();

	SetEvent(m_hStopEvent);

	if (m_pCaptureThread)
	{
		WaitForSingleObject(m_pCaptureThread->m_hThread, INFINITE);
		SAFE_DELETE(m_pCaptureThread);
	}

	m_bRunning = false;
}

bool RTL2832::SetGain(double dGain)
{
	m_strLastError.Empty();

	//CSingleLock lock(&m_cs, TRUE);	// Switched off to improve responsiveness (just don't call this from different threads!)

	{ SCOPED_LOG_MONITOR(m_bExternalCall);
	if (m_demod.active_tuner()->set_gain(dGain) != RTL2832_NAMESPACE::SUCCESS)
		return false;
	}

	m_dGain = m_demod.active_tuner()->gain();

	return true;
}

bool RTL2832::SetAntenna(int iIndex)
{
	return true;
}

bool RTL2832::SetAntenna(LPCTSTR strAntenna)
{
	return true;
}

double RTL2832::SetFreq(double dFreq)
{
	m_strLastError.Empty();

	//CSingleLock lock(&m_cs, TRUE);	// Switched off to improve responsiveness (just don't call this from different threads!)

	{ SCOPED_LOG_MONITOR(m_bExternalCall);
	if (m_demod.active_tuner()->set_frequency(dFreq) != RTL2832_NAMESPACE::SUCCESS)
		return -1;

	m_tuneResult.actual_rf_freq = m_demod.active_tuner()->frequency();
	if (m_tuneResult.actual_rf_freq <= 0)
		return -1;
	}

	m_tuneResult.target_rf_freq = dFreq;

	return (m_dFreq = m_tuneResult.actual_rf_freq);
}

double RTL2832::SetSampleRate(double dSampleRate)
{
	m_strLastError.Empty();

	if (dSampleRate <= 0)
		return -1;

	CSingleLock lock(&m_cs, TRUE);

	double d = -1;

	{ SCOPED_LOG_MONITOR(m_bExternalCall);
	if (m_demod.set_sample_rate((uint32_t)dSampleRate, &d) != RTL2832_NAMESPACE::SUCCESS)
	{
		if (d == 0)
			m_strLastError.Format(_T("Hardware sample rate could not be calculated from give rate: %f"), dSampleRate);
		else if (d == -1)
			m_strLastError.Format(_T("Supplied sample rate outside valid range [%.1f - %.1f]"), m_demod.sample_rate_range().first, m_demod.sample_rate_range().second);

		return -1;
	}
	}
 
	m_dwReadPacketWait = (m_bBuffering ? INFINITE : (DWORD)ceil(WAIT_FUDGE * 1000.0f / (float)((d * RAW_SAMPLE_SIZE) / (double)m_nReadLength)));
	AfxTrace(_T("Read packet wait time: %lu ms\n"), m_dwReadPacketWait);

	return (m_dSampleRate = d);
}

std::vector<std::string> RTL2832::GetAntennas() const
{
	std::vector<std::string> array;
	array.push_back(/*"(Default)"*/(LPCSTR)CStringA(m_strAntenna));
	return array;
}

static short _char_to_float_lut[256] = { -128, -127, -126, -125, -124, -123, -122, -121, -120, -119, -118, -117, -116, -115, -114, -113, -112, -111, -110, -109, -108, -107, -106, -105, -104, -103, -102, -101, -100, -99, -98, -97, -96, -95, -94, -93, -92, -91, -90, -89, -88, -87, -86, -85, -84, -83, -82, -81, -80, -79, -78, -77, -76, -75, -74, -73, -72, -71, -70, -69, -68, -67, -66, -65, -64, -63, -62, -61, -60, -59, -58, -57, -56, -55, -54, -53, -52, -51, -50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37, -36, -35, -34, -33, -32, -31, -30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127 };

int RTL2832::ReadPacket()
{
	CSingleLock lock(&m_cs, TRUE);

	if (m_bRunning == false)
		return -1;

	if (m_pCaptureThread == NULL)
	{	
		int iRead = 0;
		int res = m_demod.read_samples(m_pConversionBuffer, m_nReadLength, &iRead);
		if ((res != 0) && (res != LIBUSB_ERROR_OVERFLOW))
			return -1;

		if ((UINT)iRead < m_nReadLength)
		{
			AfxTrace(_T("Short bulk read: %i < %lu\n"), iRead, m_nReadLength);
		}

		m_nSamplesReceived += (iRead / RAW_SAMPLE_SIZE);

		UINT iSize = min((m_recv_samples_per_packet * RAW_SAMPLE_SIZE), (UINT)iRead);
		for (UINT n = 0; n < iSize; n++)
		{
			//short i = m_pConversionBuffer[n];
			//m_pBuffer[n] = i - 127;
			m_pBuffer[n] = _char_to_float_lut[m_pConversionBuffer[n]];
		}

		if (res == LIBUSB_ERROR_OVERFLOW)
		{
			++m_nOverflows;

			m_metadata.error_code = uhd::rx_metadata_t::ERROR_CODE_OVERFLOW;
		}
		else
			m_metadata.error_code = uhd::rx_metadata_t::ERROR_CODE_NONE;

		++m_nReadPacketCount;

		return m_recv_samples_per_packet;
	}

	///////////////////////////////////////////////////////////////////////////

	/*if*/while ((m_bBuffering) || /*(m_nBufferItems < m_recv_samples_per_packet)*/(m_nBufferItems <= ((UINT)(m_fBufferLevel * (float)m_nBufferSize) + m_recv_samples_per_packet)))	// [Always wait for packet - this is called ASAP by Worker thread] If getting too full, send them all through
	{
		lock.Unlock();

		HANDLE hHandles[] = { m_hStopEvent, m_hPacketEvent, m_hAbortEvent };

		//AfxTrace(_T("Waiting for packet\n"));

		LARGE_INTEGER li, liNow;
		QueryPerformanceCounter(&li);

		DWORD dw = WaitForMultipleObjects(sizeof(hHandles)/sizeof(hHandles[0]), hHandles, FALSE, /*INFINITE*/m_dwReadPacketWait);
		if (dw == (WAIT_OBJECT_0 + 0))
		{
			return 0;
		}
		else if (dw == (WAIT_OBJECT_0 + 1))
		{
			lock.Lock();

			if (m_bBuffering == false)
				break;

			AfxTrace(_T("Caught packet signal while buffering!\n"));
		}
		else if (dw == (WAIT_OBJECT_0 + 2))
		{
			return -1;
		}
		else if (dw == WAIT_TIMEOUT)
		{
			QueryPerformanceCounter(&liNow);
			UINT nDelay = (UINT)(liNow.QuadPart - li.QuadPart);
			AfxTrace(_T("Wait time-out elapsed (%lu ms, %.1f ms), getting next portion of buffer... [#%lu]\n"), m_dwReadPacketWait, (float)(1000.0 * (double)nDelay / (double)m_liFreq.QuadPart), m_nReadPacketCount);
			break;
		}
		else
		{
			ASSERT(FALSE);

			return 0;
		}
	}

	if (m_nBufferItems < m_recv_samples_per_packet)
	{
		AfxTrace(_T("Reading packet after signal, but not enough items in buffer (only %lu, need at least: %lu, start now %lu) [#%lu]\n"), m_nBufferItems, m_recv_samples_per_packet, m_nBufferStart, m_nReadPacketCount);
		m_bBuffering = true;
		++m_nBufferUnderrunCount;
		return 0;
	}

	++m_nReadPacketCount;

	UINT nPart1 = min(m_recv_samples_per_packet, m_nBufferSize - m_nBufferStart);
	LPBYTE p = m_pUSBBuffer + (m_nBufferStart * RAW_SAMPLE_SIZE);
	for (UINT n = 0; n < nPart1; n++)
	{
		//short i = p[n*2+0];
		//short q = p[n*2+1];
		//m_pBuffer[n*2+0] = i - 127;
		m_pBuffer[n*2+0] = _char_to_float_lut[p[n*2+0]];
		//m_pBuffer[n*2+1] = q - 127;
		m_pBuffer[n*2+1] = _char_to_float_lut[p[n*2+1]];
	}

	UINT nResidual = m_recv_samples_per_packet - nPart1;
	if (nResidual > 0)
	{
		for (UINT n = 0; n < nResidual; n++)
		{
			//short i = m_pUSBBuffer[n*2+0];
			//short q = m_pUSBBuffer[n*2+1];
			//m_pBuffer[n*2+0] = i - 127;
			m_pBuffer[n*2+0] = _char_to_float_lut[m_pUSBBuffer[n*2+0]];
			//m_pBuffer[n*2+1] = q - 127;
			m_pBuffer[n*2+1] = _char_to_float_lut[m_pUSBBuffer[n*2+1]];
		}
	}

	m_nSamplesReceived += m_recv_samples_per_packet;

/*	if (false)	// FIXME: Flag
	{
		++m_nOverflows;

		m_metadata.error_code = uhd::rx_metadata_t::ERROR_CODE_OVERFLOW;
	}
	else
		m_metadata.error_code = uhd::rx_metadata_t::ERROR_CODE_NONE;
*/
	m_nBufferItems -= m_recv_samples_per_packet;

	//ASSERT(m_nBufferItems != -1);

	if (m_nBufferItems > 0)
		m_nBufferStart = (m_nBufferStart + m_recv_samples_per_packet) % m_nBufferSize;

	//AfxTrace(_T("Read packet: start=%lu, items=%lu\n"), m_nBufferStart, m_nBufferItems);

	return m_recv_samples_per_packet;
}

///////////////////////////////////////////////////////////////////////////////

CString RTL2832::GetExtraInfo() const
{
	CSingleLock lock(const_cast<CCriticalSection*>(&m_cs), TRUE);

	CString str;

	if (m_bUseBuffer)
	{
		str.Format(_T("Buffer: %.1f%% (overruns: %lu, underruns: %lu)"),
			(100.0f * (float)m_nBufferItems / (float)m_nBufferSize),
			m_nBufferOverflowCount,
			m_nBufferUnderrunCount);
	}

	return str;
}

UINT RTL2832::CaptureThreadProc()
{
	CSingleLock lock(&m_cs, FALSE);

	if ((m_nReadLength == 0) ||
		(m_pUSBBuffer == NULL) ||
		(m_nBufferSize == 0) ||
		(m_fBufferLevel < 0))
	{
		//lock.lock();
		//m_bRunning = false;
		SetEvent(m_hAbortEvent);
		//lock.unlock();

		AfxTrace(_T("Capture threading %04x NOT starting due to state error\n"), GetCurrentThreadId());

		return 0;
	}

	DWORD dwTime = GetTickCount();

	AfxTrace(_T("Capture thread %04x starting...\n"), GetCurrentThreadId());

	LPBYTE pBuffer = new BYTE[m_nReadLength];
UINT nTransfers = 0;
	while (true)
	{
		DWORD dw = WaitForSingleObject(m_hStopEvent, 0);
		if (dw == (WAIT_OBJECT_0))
		{
			break;
		}

		int lLockSize = 0;
		int res = m_demod.read_samples(pBuffer, m_nReadLength, &lLockSize);
		if (res == LIBUSB_ERROR_OVERFLOW)
		{
			AfxTrace(_T("USB overrun\n"));

			lock.Lock();
			++m_nOverflows;
			lock.Unlock();
		}
		else if (res != 0)
		{
AfxTrace(_T("USB error: %i [#%lu]\n"), res, nTransfers);
			SetEvent(m_hAbortEvent);
			break;	//continue;
		}
++nTransfers;
		if ((UINT)lLockSize < m_nReadLength)
		{
			AfxTrace(_T("Short bulk read: %i < %lu\n"), lLockSize, m_nReadLength);
		}

		lock.Lock();

		UINT nRemaining = min(m_nBufferSize - m_nBufferItems, (UINT)lLockSize / RAW_SAMPLE_SIZE);

		bool bSignal = true;

		if (nRemaining > 0)
		{
			//AfxTrace(_T("Notification: count=%lu, start=%lu, items=%lu\n"), nCount, m_nBufferStart, m_nBufferItems);

			LPBYTE p = m_pUSBBuffer + (((m_nBufferStart + m_nBufferItems) % m_nBufferSize) * RAW_SAMPLE_SIZE);

			UINT nPart1 = (m_nBufferStart + m_nBufferItems) % m_nBufferSize;
			UINT nSize1 = min(nRemaining, m_nBufferSize - nPart1);

			memcpy(p, pBuffer, nSize1 * RAW_SAMPLE_SIZE);

			UINT nResidual = nRemaining - nSize1;
			if (nResidual > 0)
				memcpy(m_pUSBBuffer, pBuffer + (nSize1 * 2), nResidual * RAW_SAMPLE_SIZE);

			m_nBufferItems += nRemaining;

			if ((m_bBuffering) && (m_nBufferItems >= (UINT)(m_recv_samples_per_packet + (float)m_nBufferSize * m_fBufferLevel)))	// Add additional amount that is about to be read back out in ReadPacket
			{
				AfxTrace(_T("Finished buffering (%lu/%lu) [#%lu]\n"), m_nBufferItems, m_nBufferSize, m_nReadPacketCount);
				m_bBuffering = false;
			}

			bSignal = !m_bBuffering;
		}
		else// if (nRemaining == 0)
		{
AfxTrace(_T("OVERRUN: Remaining: %lu\n"), nRemaining);	// FIXME: Overrun
			++m_nBufferOverflowCount;
		}

		//////////////////////////
		/*DWORD dwNow = GetTickCount();
		if ((dwNow - dwTime) >= 1000)
		{
			AfxTrace(_T("Buffer at %.1f%%\n"), (100.0f * (float)m_nBufferItems / (float)m_nBufferSize));
			dwTime = dwNow;
		}*/

		lock.Unlock();

		if (bSignal)
			SetEvent(m_hPacketEvent);
	}

	SAFE_DELETE_ARRAY(pBuffer);

	AfxTrace(_T("Capture thread %04x exiting\n"), GetCurrentThreadId());

	return 0;
}

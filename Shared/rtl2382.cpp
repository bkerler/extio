#include "StdAfx.h"
#include "rtl2832.h"

#include "PluginFactory.h"
#include "Utils.h"

#include "rtl2832-tuner_e4000.h"
#include "rtl2832-tuner_fc0013.h"

#define DEFAULT_READLEN			(/*16 * */16384 * 2)	// This is good compromise between maintaining a good buffer level and immediate response to parameter adjustment
#define DEFAULT_BUFFER_MUL		(4*2)
#define DEFAULT_BUFFER_LEVEL	0.5f
#define WAIT_FUDGE				1.2f
#define RAW_SAMPLE_SIZE			(1+1)
#define LIBUSB_TIMEOUT			3000

#define CTRL_IN		(LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN)
#define CTRL_OUT	(LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT)

/* ezcap USB 2.0 DVB-T/DAB/FM stick */
#define EZCAP_VID		0x0bda
#define EZCAP_PID		0x2838

#define HAMA_VID		0x0bda
#define HAMA_PID		0x2832

#define BANDWIDTH		8000000
#define MAX_RATE		3200000

/* Terratec NOXON DAB/DAB+ USB-Stick */
#define NOXON_VID		0x0ccd
#define NOXON_PID		0x00b3
#define NOXON_V2_PID	0x00e0

/* Dexatek Technology Ltd. DK DVB-T Dongle */
#define DEXATEK_VID		0x1d19
#define DEXATEK_PID		0x1101

#define CRYSTAL_FREQ	28800000

enum usb_reg {
	USB_SYSCTL		= 0x2000,
	USB_CTRL		= 0x2010,
	USB_STAT		= 0x2014,
	USB_EPA_CFG		= 0x2144,
	USB_EPA_CTL		= 0x2148,
	USB_EPA_MAXPKT		= 0x2158,
	USB_EPA_MAXPKT_2	= 0x215a,
	USB_EPA_FIFO_CFG	= 0x2160,
};

enum sys_reg {
	DEMOD_CTL		= 0x3000,
	GPO			= 0x3001,
	GPI			= 0x3002,
	GPOE			= 0x3003,
	GPD			= 0x3004,
	SYSINTE			= 0x3005,
	SYSINTS			= 0x3006,
	GP_CFG0			= 0x3007,
	GP_CFG1			= 0x3008,
	SYSINTE_1		= 0x3009,
	SYSINTS_1		= 0x300a,
	DEMOD_CTL_1		= 0x300b,
	IR_SUSPEND		= 0x300c,
};

enum blocks {
	DEMODB			= 0,
	USBB			= 1,
	SYSB			= 2,
	TUNB			= 3,
	ROMB			= 4,
	IRB				= 5,
	IICB			= 6,
};

IMPLEMENT_PF(rtl2832)

rtl2832::rtl2832()
	: devh(NULL)
	, m_pCaptureThread(NULL)
	, m_nItemSize(0)
	, m_hStopEvent(INVALID_HANDLE_VALUE)
	, m_hPacketEvent(INVALID_HANDLE_VALUE)
	, m_hAbortEvent(INVALID_HANDLE_VALUE)
	, m_nBufferItems(0)
	, m_pUSBBuffer(NULL)
	, m_nBufferStart(0)
	, m_nBufferSize(0)
	, tuner_type(TUNER_UNKNOWN)
	, m_bBuffering(false)
	, m_pConversionBuffer(NULL)
	, m_iTunerGainMode(RTL2832_E4000_TUNER_GAIN_NORMAL)
	, m_bUSBInitDone(false)
	, m_nReadLength(DEFAULT_READLEN)
	, m_nBufferMultiplier(DEFAULT_BUFFER_MUL)
	, m_bUseBuffer(true)
	, m_fBufferLevel(DEFAULT_BUFFER_LEVEL)
	, m_nReadPacketCount(0)
	, m_nBufferOverflowCount(0)
	, m_nBufferUnderrunCount(0)
{
	m_strAntenna = _T("(Default)");
	m_recv_samples_per_packet = /*READLEN / RAW_SAMPLE_SIZE*/4096;	// Already on 512-byte boundary (after converting to shorts, will still be)
	m_fpga_master_clock_freq = MAX_RATE;
	//m_dSampleRate = m_fpga_master_clock_freq;1000000;	// Use ExtIO default instead

	QueryPerformanceFrequency(&m_liFreq);
}

rtl2832::~rtl2832()
{
	Destroy();
}

int rtl2832::find_device()
{
	if (devh != NULL)
		return 0;

	devh = libusb_open_device_with_vid_pid(NULL, EZCAP_VID, EZCAP_PID);
	if (devh > 0) {
		tuner_type = TUNER_E4000;
		m_gainRange = uhd::gain_range_t(-5, 30, 0.5);
		m_strName = _T("ezcap EzTV");
		AfxTrace(_T("Found ezcap stick with E4000 tuner\n"));
		return 0;
	}

	devh = libusb_open_device_with_vid_pid(NULL, HAMA_VID, HAMA_PID);
	if (devh > 0) {
		tuner_type = TUNER_E4000;
		m_gainRange = uhd::gain_range_t(-5, 30, 0.5);
		m_strName = _T("Hama nano");
		AfxTrace(_T("Found Hama nano stick with E4000 tuner\n"));
		return 0;
	}

	devh = libusb_open_device_with_vid_pid(NULL, DEXATEK_VID, DEXATEK_PID);
	if (devh > 0) {
		tuner_type = TUNER_FC0013;
		m_gainRange = uhd::gain_range_t(-6.3, 19.7, 0.1);
		m_strName = _T("Dexatek Technology");
		AfxTrace(_T("Found Dexatek Technology stick with FC0013 tuner\n"));
		return 0;
	}

	devh = libusb_open_device_with_vid_pid(NULL, NOXON_VID, NOXON_PID);
	if (devh > 0) {
		tuner_type = TUNER_FC0013;
		m_gainRange = uhd::gain_range_t(-6.3, 19.7, 0.1);
		m_strName = _T("Terratec NOXON");
		AfxTrace(_T("Found Terratec NOXON (revision 1) stick with FC0013 tuner\n"));
		return 0;
	}

	devh = libusb_open_device_with_vid_pid(NULL, NOXON_VID, NOXON_V2_PID);
	if (devh > 0) {
		tuner_type = TUNER_E4000;
		m_gainRange = uhd::gain_range_t(-5, 30, 0.5);
		m_strName = _T("Terratec NOXON (rev 2)");
		AfxTrace(_T("Found Terratec NOXON (revision 2) stick with E4000 tuner\n"));
		return 0;
	}

	return -EIO;
}

int rtl2832::rtl_read_array(uint8_t block, uint16_t addr, uint8_t *array, uint8_t len)
{
	int r;
	uint16_t index = (block << 8);

	r = libusb_control_transfer(devh, CTRL_IN, 0, addr, index, array, len, 0);

	return r;
}

int rtl2832::rtl_write_array(uint8_t block, uint16_t addr, uint8_t *array, uint8_t len)
{
	int r;
	uint16_t index = (block << 8) | 0x10;

	r = libusb_control_transfer(devh, CTRL_OUT, 0, addr, index, array, len, 0);
	if (r == 0)
	{
		AfxTrace(_T("No bytes xfered\n"));
	}
	else if (r < 0)
	{
/* \returns on success, the number of bytes actually transferred
 * \returns LIBUSB_ERROR_TIMEOUT if the transfer timed out
 * \returns LIBUSB_ERROR_PIPE if the control request was not supported by the
 * device
 * \returns LIBUSB_ERROR_NO_DEVICE if the device has been disconnected
 * \returns another LIBUSB_ERROR code on other failures
*/
		if (r == LIBUSB_ERROR_PIPE)
			AfxTrace(_T("USB control request not supported\n"));
		else
			AfxTrace(_T("Error writing control: %i\n"), r);
	}

	return r;
}

int rtl2832::rtl_i2c_write(uint8_t i2c_addr, uint8_t *buffer, int len)
{
	uint16_t addr = i2c_addr;
	return rtl_write_array(IICB, addr, buffer, len);
}

int rtl2832::rtl_i2c_read(uint8_t i2c_addr, uint8_t *buffer, int len)
{
	uint16_t addr = i2c_addr;
	return rtl_read_array(IICB, addr, buffer, len);
}

uint16_t rtl2832::rtl_read_reg(uint8_t block, uint16_t addr, uint8_t len)
{
	int r;
	unsigned char data[2];
	uint16_t index = (block << 8);
	uint16_t reg;

	r = libusb_control_transfer(devh, CTRL_IN, 0, addr, index, data, len, 0);

	if (r < 0)
		AfxTrace(_T("%s failed\n"), __FUNCTION__);

	reg = (data[1] << 8) | data[0];

	return reg;
}

void rtl2832::rtl_write_reg(uint8_t block, uint16_t addr, uint16_t val, uint8_t len)
{
	int r;
	unsigned char data[2];

	uint16_t index = (block << 8) | 0x10;

	if (len == 1)
		data[0] = val & 0xff;
	else
		data[0] = val >> 8;

	data[1] = val & 0xff;

	r = libusb_control_transfer(devh, CTRL_OUT, 0, addr, index, data, len, 0);

	if (r < 0)
		AfxTrace(_T("%s failed\n"), __FUNCTION__);
}

uint16_t rtl2832::demod_read_reg(uint8_t page, uint8_t addr, uint8_t len)
{
	int r;
	unsigned char data[2];

	uint16_t index = page;
	uint16_t reg;
	addr = (addr << 8) | 0x20;

	r = libusb_control_transfer(devh, CTRL_IN, 0, addr, index, data, len, 0);

	if (r < 0)
		AfxTrace(_T("%s failed\n"), __FUNCTION__);

	reg = (data[1] << 8) | data[0];

	return reg;
}

void rtl2832::demod_write_reg(uint8_t page, uint16_t addr, uint16_t val, uint8_t len)
{
	int r;
	unsigned char data[2];
	uint16_t index = 0x10 | page;
	addr = (addr << 8) | 0x20;

	if (len == 1)
		data[0] = val & 0xff;
	else
		data[0] = val >> 8;

	data[1] = val & 0xff;

	r = libusb_control_transfer(devh, CTRL_OUT, 0, addr, index, data, len, 0);

	if (r < 0)
		AfxTrace(_T("%s failed\n"), __FUNCTION__);

	demod_read_reg(0x0a, 0x01, 1);
}

bool rtl2832::set_samp_rate(uint32_t samp_rate)
{
	uint16_t tmp;
	uint32_t rsamp_ratio;
	double real_rate;

	/* check for the maximum rate the resampler supports */
	if (samp_rate > MAX_RATE)
		samp_rate = MAX_RATE;

	rsamp_ratio = ((UINT64)CRYSTAL_FREQ * (UINT64)pow((float)2, 22)) / (UINT64)samp_rate;	// CHANGE
	rsamp_ratio &= ~3;

	if (rsamp_ratio == 0)
		return false;

	real_rate = (CRYSTAL_FREQ * pow((float)2, 22)) / rsamp_ratio;	// CHANGE

	AfxTrace(_T("Setting sample rate: %.3f Hz\n"), real_rate);

	m_dSampleRate = real_rate;

	tmp = (rsamp_ratio >> 16);
	demod_write_reg(1, 0x9f, tmp, 2);
	tmp = rsamp_ratio & 0xffff;
	demod_write_reg(1, 0xa1, tmp, 2);

	return true;
}

void rtl2832::set_i2c_repeater(int on)
{
	demod_write_reg(1, 0x01, on ? 0x18 : 0x10, 1);
}

void rtl2832::rtl_init(void)
{
	unsigned int i;

	/* default FIR coefficients used for DAB/FM by the Windows driver,
	 * the DVB driver uses different ones */
	uint8_t fir_coeff[] = {
		0xca, 0xdc, 0xd7, 0xd8, 0xe0, 0xf2, 0x0e, 0x35, 0x06, 0x50,
		0x9c, 0x0d, 0x71, 0x11, 0x14, 0x71, 0x74, 0x19, 0x41, 0x00,
	};

	/* initialize USB */
	rtl_write_reg(USBB, USB_SYSCTL, 0x09, 1);
	rtl_write_reg(USBB, USB_EPA_MAXPKT, 0x0002, 2);
	rtl_write_reg(USBB, USB_EPA_CTL, 0x1002, 2);

	/* poweron demod */
	rtl_write_reg(SYSB, DEMOD_CTL_1, 0x22, 1);
	rtl_write_reg(SYSB, DEMOD_CTL, 0xe8, 1);

	/* reset demod (bit 3, soft_rst) */
	demod_write_reg(1, 0x01, 0x14, 1);
	demod_write_reg(1, 0x01, 0x10, 1);

	/* disable spectrum inversion and adjacent channel rejection */
	demod_write_reg(1, 0x15, 0x00, 1);
	demod_write_reg(1, 0x16, 0x0000, 2);

	/* set IF-frequency to 0 Hz */
	demod_write_reg(1, 0x19, 0x0000, 2);

	/* set FIR coefficients */
	for (i = 0; i < sizeof (fir_coeff); i++)
		demod_write_reg(1, 0x1c + i, fir_coeff[i], 1);

	demod_write_reg(0, 0x19, 0x25, 1);

	/* init FSM state-holding register */
	demod_write_reg(1, 0x93, 0xf0, 1);

	/* disable AGC (en_dagc, bit 0) */
	demod_write_reg(1, 0x11, 0x00, 1);

	/* disable PID filter (enable_PID = 0) */
	demod_write_reg(0, 0x61, 0x60, 1);

	/* opt_adc_iq = 0, default ADC_I/ADC_Q datapath */
	demod_write_reg(0, 0x06, 0x80, 1);

	/* Enable Zero-IF mode (en_bbin bit), DC cancellation (en_dc_est),
	 * IQ estimation/compensation (en_iq_comp, en_iq_est) */
	demod_write_reg(1, 0xb1, 0x1b, 1);
}

bool rtl2832::tuner_init()
{
	bool bReturn = false;

	set_i2c_repeater(1);

	switch (tuner_type) {
	case TUNER_E4000:
		if (e4000_Initialize(this) != 0)
		{
			AfxTrace(_T("e4000_Initialize failed\n"));
			goto tuner_init_error;
		}
		if (e4000_SetBandwidthHz(this, BANDWIDTH) != 0)
		{
			AfxTrace(_T("e4000_SetBandwidthHz failed\n"));
			goto tuner_init_error;
		}
		break;
	case TUNER_FC0013:
		if (FC0013_Open(this) != 0)
		{
			AfxTrace(_T("FC0013_Open failed\n"));
			goto tuner_init_error;
		}
		break;
	default:
		AfxTrace(_T("No valid tuner available!\n"));
		break;
	}

	bReturn = true;
tuner_init_error:
	set_i2c_repeater(0);
	return bReturn;
}

///////////////////////////////////////////////////////////////////////////////

bool rtl2832::Create(LPCTSTR strHint /*= NULL*/)
{
	Destroy();

	m_strLastError.Empty();

	m_nReadLength = DEFAULT_READLEN;
	m_nBufferMultiplier = DEFAULT_BUFFER_MUL;
	m_fBufferLevel = DEFAULT_BUFFER_LEVEL;

	/////////////////////////

	CString str(strHint);
	if ((str.GetLength() >= 3) && (str.Left(3).CompareNoCase(_T("rtl")) == 0))
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

	// FIXME: Delay

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

	int r;

	if (m_bUSBInitDone == false)
	{
		r = libusb_init(NULL);
		if (r < 0) {
			m_strLastError = _T("Failed to initialise libusb");
			AfxTrace(_T("Failed to initialise libusb\n"));
			return false;
		}

		m_bUSBInitDone = true;
	}

	r = find_device();
	if (r < 0) {
		m_strLastError = _T("Could not find/open device");
		AfxTrace(_T("Could not find/open device\n"));
		Destroy();
		return false;
	}

	r = libusb_claim_interface(devh, 0);
	if (r < 0) {
		m_strLastError = _T("usb_claim_interface error: ") + Teh::Utils::ToString(r);
		AfxTrace(_T("usb_claim_interface error: %d\n"), r);
		Destroy();
		return false;
	}

	rtl_init();
	if (tuner_init() == false)
		return false;

	return true;
}

void rtl2832::Destroy()
{
	Stop();

	if (devh != NULL)
	{
		libusb_release_interface(devh, 0);
		libusb_close(devh);
		devh = NULL;
	}

	if (m_bUSBInitDone)
	{
		libusb_exit(NULL);
		m_bUSBInitDone = false;
	}

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
	rtl2832* p = (rtl2832*)pPrivate;
	
	return p->CaptureThreadProc();
}

void rtl2832::Reset()
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

bool rtl2832::Start()
{
	CSingleLock lock(&m_cs, TRUE);

	if (m_bRunning)
		return true;

	Reset();

	/* reset endpoint before we start reading */
	rtl_write_reg(USBB, USB_EPA_CTL, 0x1002, 2);
	rtl_write_reg(USBB, USB_EPA_CTL, 0x0000, 2);

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

void rtl2832::Stop()
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

bool rtl2832::SetGain(double dGain)
{
	m_strLastError.Empty();

	static int mapGainsE4000[] = {	// rtl2832: nim_rtl2832_e4000.c
		-50,	2,
		-25,	3,
		0,		4,
		25,		5,
		50,		6,
		75,		7,
		100,	8,
		125,	9,
		150,	10,
		175,	11,
		200,	12,
		225,	13,
		250,	14,
		300,	15,	// Apparently still 250
	};

  /*enum FC0013_LNA_GAIN_VALUE
  {
	  FC0013_LNA_GAIN_LOW     = 0x00,	// -6.3dB
	  FC0013_LNA_GAIN_MIDDLE  = 0x08,	//  7.1dB
	  FC0013_LNA_GAIN_HIGH_17 = 0x11,	// 19.1dB
	  FC0013_LNA_GAIN_HIGH_19 = 0x10,	// 19.7dB
  };*/
	
	static int mapGainsFC0013[] = {	// rtl2832: nim_rtl2832_fc0013.c
	  -63, 0x00,
	  +71, 0x08,
	  191, 0x11,
	  197, 0x10
	};
	
	int* mapGains = NULL;
	int iCount = 0;
	
	switch (tuner_type) {
	  case TUNER_E4000:
		mapGains = mapGainsE4000;
		iCount = (sizeof(mapGainsE4000)/sizeof(mapGainsE4000[0])) / 2;
		break;
	  case TUNER_FC0013:
		mapGains = mapGainsFC0013;
		iCount = (sizeof(mapGainsFC0013)/sizeof(mapGainsFC0013[0])) / 2;
		break;
	  default:
		return false;
	}

	int iGain = (int)(dGain * 10.0);
	int i = GetMapIndex(iGain, mapGains, iCount);

	if ((i == -1) || (i == iCount))
		return false;

	unsigned char u8Write = mapGains[i + 1];

	//CSingleLock lock(&m_cs, TRUE);	// Switched off to improve responsiveness (just don't call this from different threads!)

	set_i2c_repeater(1);

	if (tuner_type == TUNER_E4000)
	{
	  unsigned char u8Read = 0;
	  if (I2CReadByte(this, 0, RTL2832_E4000_LNA_GAIN_ADDR, &u8Read) != E4000_I2C_SUCCESS)
	  {
		  goto gain_failure;
	  }

	  u8Write |= (u8Read & ~RTL2832_E4000_LNA_GAIN_MASK);

	  if (I2CWriteByte(this, 0, RTL2832_E4000_LNA_GAIN_ADDR, u8Write) != E4000_I2C_SUCCESS)
	  {
		  goto gain_failure;
	  }
	}
	else if (tuner_type == TUNER_FC0013)
	{
/* FIXME: Also really should be handling:
	int boolVhfFlag;      // 0:false,  1:true
	int boolEnInChgFlag;  // 0:false,  1:true
	int intGainShift;
*/
		if (fc0013_SetRegMaskBits(this, 0x14, 4, 0, u8Write) != FC0013_I2C_SUCCESS)
		{
			goto gain_failure;
		}
	}

	m_dGain = (double)mapGains[i] / 10.0;

	set_i2c_repeater(0);

	/////////////////////////
	//if (m_auto_tuner_mode)
		SetTunerMode();
	/////////////////////////

	return true;
gain_failure:
	set_i2c_repeater(0);
	AfxTrace(_T("I2C write failed\n"));
	return false;
}

bool rtl2832::SetAntenna(int iIndex)
{
	return true;
}

bool rtl2832::SetAntenna(LPCTSTR strAntenna)
{
	return true;
}

double rtl2832::SetFreq(double dFreq)
{
	m_strLastError.Empty();

	//CSingleLock lock(&m_cs, TRUE);	// Switched off to improve responsiveness (just don't call this from different threads!)

	set_i2c_repeater(1);

	switch (tuner_type) {
	case TUNER_E4000:
		if (e4000_SetRfFreqHz(this, (unsigned long)dFreq) != 0)
		{
			goto freq_failure;
		}
		break;
	case TUNER_FC0013:
		if (FC0013_SetFrequency(this, (unsigned long)(dFreq/1000.0), 8) == 0)
		{
			goto freq_failure;
		}
		break;
	default:
		//break;
		set_i2c_repeater(0);
		return dFreq;
	}

	set_i2c_repeater(0);

	m_tuneResult.target_rf_freq = dFreq;
	m_tuneResult.actual_rf_freq = ((dFreq + 500.0) / 1000.0);

	m_dFreq = dFreq;

	return dFreq;
freq_failure:
	set_i2c_repeater(0);
	if (m_strLastError.IsEmpty())
		m_strLastError = _T("I2C write failed");
	AfxTrace(_T("I2C write failed\n"));
	return -1;
}

double rtl2832::SetSampleRate(double dSampleRate)
{
	CSingleLock lock(&m_cs, TRUE);

	if (devh == NULL)
		return -1;

	if (set_samp_rate((uint32_t)dSampleRate) == false)
		return -1;

	return dSampleRate;
}

std::vector<std::string> rtl2832::GetAntennas() const
{
	std::vector<std::string> array;
	array.push_back(/*"(Default)"*/(LPCSTR)CStringA(m_strAntenna));
	return array;
}

static short _char_to_float_lut[256] = { -128, -127, -126, -125, -124, -123, -122, -121, -120, -119, -118, -117, -116, -115, -114, -113, -112, -111, -110, -109, -108, -107, -106, -105, -104, -103, -102, -101, -100, -99, -98, -97, -96, -95, -94, -93, -92, -91, -90, -89, -88, -87, -86, -85, -84, -83, -82, -81, -80, -79, -78, -77, -76, -75, -74, -73, -72, -71, -70, -69, -68, -67, -66, -65, -64, -63, -62, -61, -60, -59, -58, -57, -56, -55, -54, -53, -52, -51, -50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37, -36, -35, -34, -33, -32, -31, -30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127 };

int rtl2832::ReadPacket()
{
	CSingleLock lock(&m_cs, TRUE);

	if ((m_bRunning == false) || (devh == NULL))
		return -1;

	if (m_pCaptureThread == NULL)
	{	
		int iRead = 0;
		int res = libusb_bulk_transfer(devh, 0x81, m_pConversionBuffer, m_nReadLength, &iRead, LIBUSB_TIMEOUT);
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

		DWORD dwWait = (m_bBuffering ? INFINITE : (DWORD)ceil(WAIT_FUDGE * 1000.0f / (float)((m_dSampleRate * RAW_SAMPLE_SIZE) / (double)m_nReadLength)));
		DWORD dw = WaitForMultipleObjects(sizeof(hHandles)/sizeof(hHandles[0]), hHandles, FALSE, /*INFINITE*/dwWait);
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
			AfxTrace(_T("Wait time-out elapsed (%lu ms, %.1f ms), getting next portion of buffer... [#%lu]\n"), dwWait, (float)(1000.0 * (double)nDelay / (double)m_liFreq.QuadPart), m_nReadPacketCount);
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

CString rtl2832::GetExtraInfo() const
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

UINT rtl2832::CaptureThreadProc()
{
	DWORD dwTime = GetTickCount();

	AfxTrace(_T("Capture thread %04x starting...\n"), GetCurrentThreadId());

	CSingleLock lock(&m_cs, FALSE);

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
		int res = libusb_bulk_transfer(devh, 0x81, pBuffer, m_nReadLength, &lLockSize, LIBUSB_TIMEOUT);
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
		DWORD dwNow = GetTickCount();
		if ((dwNow - dwTime) >= 1000)
		{
			AfxTrace(_T("Buffer at %.1f%%\n"), (100.0f * (float)m_nBufferItems / (float)m_nBufferSize));
			dwTime = dwNow;
		}

		lock.Unlock();

		if (bSignal)
			SetEvent(m_hPacketEvent);
	}

	SAFE_DELETE_ARRAY(pBuffer);

	AfxTrace(_T("Capture thread %04x exiting\n"), GetCurrentThreadId());

	return 0;
}

#define NO_USE 0

int rtl2832::SetTunerMode()
{
	if (tuner_type != TUNER_E4000)
		return m_iTunerGainMode;

	static const long LnaGainTable[RTL2832_E4000_LNA_GAIN_TABLE_LEN][RTL2832_E4000_LNA_GAIN_BAND_NUM] =
	{
		// VHF Gain,	UHF Gain,		ReadingByte
		{-50,			-50	},		//	0x0
		{-25,			-25	},		//	0x1
		{-50,			-50	},		//	0x2
		{-25,			-25	},		//	0x3
		{0,				0	},		//	0x4
		{25,			25	},		//	0x5
		{50,			50	},		//	0x6
		{75,			75	},		//	0x7
		{100,			100	},		//	0x8
		{125,			125	},		//	0x9
		{150,			150	},		//	0xa
		{175,			175	},		//	0xb
		{200,			200	},		//	0xc
		{225,			250	},		//	0xd
		{250,			280	},		//	0xe
		{250,			280	},		//	0xf

		// Note: The gain unit is 0.1 dB.
	};

	static const long LnaGainAddTable[RTL2832_E4000_LNA_GAIN_ADD_TABLE_LEN] =
	{
		// Gain,		ReadingByte
		NO_USE,		//	0x0
		NO_USE,		//	0x1
		NO_USE,		//	0x2
		0,			//	0x3
		NO_USE,		//	0x4
		20,			//	0x5
		NO_USE,		//	0x6
		70,			//	0x7

		// Note: The gain unit is 0.1 dB.
	};

	static const long MixerGainTable[RTL2832_E4000_MIXER_GAIN_TABLE_LEN][RTL2832_E4000_MIXER_GAIN_BAND_NUM] =
	{
		// VHF Gain,	UHF Gain,		ReadingByte
		{90,			40	},		//	0x0
		{170,			120	},		//	0x1

		// Note: The gain unit is 0.1 dB.
	};

	static const long IfStage1GainTable[RTL2832_E4000_IF_STAGE_1_GAIN_TABLE_LEN] =
	{
		// Gain,		ReadingByte
		-30,		//	0x0
		60,			//	0x1

		// Note: The gain unit is 0.1 dB.
	};

	static const long IfStage2GainTable[RTL2832_E4000_IF_STAGE_2_GAIN_TABLE_LEN] =
	{
		// Gain,		ReadingByte
		0,			//	0x0
		30,			//	0x1
		60,			//	0x2
		90,			//	0x3

		// Note: The gain unit is 0.1 dB.
	};

	static const long IfStage3GainTable[RTL2832_E4000_IF_STAGE_3_GAIN_TABLE_LEN] =
	{
		// Gain,		ReadingByte
		0,			//	0x0
		30,			//	0x1
		60,			//	0x2
		90,			//	0x3

		// Note: The gain unit is 0.1 dB.
	};

	static const long IfStage4GainTable[RTL2832_E4000_IF_STAGE_4_GAIN_TABLE_LEN] =
	{
		// Gain,		ReadingByte
		0,			//	0x0
		10,			//	0x1
		20,			//	0x2
		20,			//	0x3

		// Note: The gain unit is 0.1 dB.
	};

	static const long IfStage5GainTable[RTL2832_E4000_IF_STAGE_5_GAIN_TABLE_LEN] =
	{
		// Gain,		ReadingByte
		0,			//	0x0
		30,			//	0x1
		60,			//	0x2
		90,			//	0x3
		120,		//	0x4
		120,		//	0x5
		120,		//	0x6
		120,		//	0x7

		// Note: The gain unit is 0.1 dB.
	};

	static const long IfStage6GainTable[RTL2832_E4000_IF_STAGE_6_GAIN_TABLE_LEN] =
	{
		// Gain,		ReadingByte
		0,			//	0x0
		30,			//	0x1
		60,			//	0x2
		90,			//	0x3
		120,		//	0x4
		120,		//	0x5
		120,		//	0x6
		120,		//	0x7

		// Note: The gain unit is 0.1 dB.
	};

	unsigned long RfFreqHz;
	int RfFreqKhz;
	unsigned long BandwidthHz;
	int BandwidthKhz;

	unsigned char ReadingByte;
	int BandIndex;

	unsigned char TunerBitsLna, TunerBitsLnaAdd, TunerBitsMixer;
	unsigned char TunerBitsIfStage1, TunerBitsIfStage2, TunerBitsIfStage3, TunerBitsIfStage4;
	unsigned char TunerBitsIfStage5, TunerBitsIfStage6;

	long TunerGainLna, TunerGainLnaAdd, TunerGainMixer;
	long TunerGainIfStage1, TunerGainIfStage2, TunerGainIfStage3, TunerGainIfStage4;
	long TunerGainIfStage5, TunerGainIfStage6;

	long TunerGainTotal;
	long TunerInputPower;

	/////////////////////////
	int TunerGainMode = -1;
	set_i2c_repeater(1);
	/////////////////////////

	// Get tuner RF frequency in KHz.
	// Note: RfFreqKhz = round(RfFreqHz / 1000)
	//if(this->GetRfFreqHz(this, &RfFreqHz) != E4000_I2C_SUCCESS)
	//	goto error_status_get_tuner_registers;
	RfFreqHz = (unsigned long)GetFreq();

	RfFreqKhz = (int)((RfFreqHz + 500) / 1000);

	// Get tuner bandwidth in KHz.
	// Note: BandwidthKhz = round(BandwidthHz / 1000)
	//if(pTunerExtra->GetBandwidthHz(this, &BandwidthHz) != E4000_I2C_SUCCESS)
	//	goto error_status_get_tuner_registers;
	BandwidthHz = BANDWIDTH;

	BandwidthKhz = (int)((BandwidthHz + 500) / 1000);

	// Determine band index.
	BandIndex = (RfFreqHz < RTL2832_E4000_RF_BAND_BOUNDARY_HZ) ? 0 : 1;

	// Get tuner LNA gain according to reading byte and table.
	if(I2CReadByte(this, NO_USE, RTL2832_E4000_LNA_GAIN_ADDR, &ReadingByte) != E4000_I2C_SUCCESS)
		goto error_status_get_tuner_registers;

	TunerBitsLna = (ReadingByte & RTL2832_E4000_LNA_GAIN_MASK) >> RTL2832_E4000_LNA_GAIN_SHIFT;
	TunerGainLna = LnaGainTable[TunerBitsLna][BandIndex];

	// Get tuner LNA additional gain according to reading byte and table.
	if(I2CReadByte(this, NO_USE, RTL2832_E4000_LNA_GAIN_ADD_ADDR, &ReadingByte) != E4000_I2C_SUCCESS)
		goto error_status_get_tuner_registers;

	TunerBitsLnaAdd = (ReadingByte & RTL2832_E4000_LNA_GAIN_ADD_MASK) >> RTL2832_E4000_LNA_GAIN_ADD_SHIFT;
	TunerGainLnaAdd = LnaGainAddTable[TunerBitsLnaAdd];

	// Get tuner mixer gain according to reading byte and table.
	if(I2CReadByte(this, NO_USE, RTL2832_E4000_MIXER_GAIN_ADDR, &ReadingByte) != E4000_I2C_SUCCESS)
		goto error_status_get_tuner_registers;

	TunerBitsMixer = (ReadingByte & RTL2832_E4000_MIXER_GAIN_MASK) >> RTL2832_E4000_LNA_GAIN_ADD_SHIFT;
	TunerGainMixer = MixerGainTable[TunerBitsMixer][BandIndex];

	// Get tuner IF stage 1 gain according to reading byte and table.
	if(I2CReadByte(this, NO_USE, RTL2832_E4000_IF_STAGE_1_GAIN_ADDR, &ReadingByte) != E4000_I2C_SUCCESS)
		goto error_status_get_tuner_registers;

	TunerBitsIfStage1 = (ReadingByte & RTL2832_E4000_IF_STAGE_1_GAIN_MASK) >> RTL2832_E4000_IF_STAGE_1_GAIN_SHIFT;
	TunerGainIfStage1 = IfStage1GainTable[TunerBitsIfStage1];

	// Get tuner IF stage 2 gain according to reading byte and table.
	if(I2CReadByte(this, NO_USE, RTL2832_E4000_IF_STAGE_2_GAIN_ADDR, &ReadingByte) != E4000_I2C_SUCCESS)
		goto error_status_get_tuner_registers;

	TunerBitsIfStage2 = (ReadingByte & RTL2832_E4000_IF_STAGE_2_GAIN_MASK) >> RTL2832_E4000_IF_STAGE_2_GAIN_SHIFT;
	TunerGainIfStage2 = IfStage2GainTable[TunerBitsIfStage2];

	// Get tuner IF stage 3 gain according to reading byte and table.
	if(I2CReadByte(this, NO_USE, RTL2832_E4000_IF_STAGE_3_GAIN_ADDR, &ReadingByte) != E4000_I2C_SUCCESS)
		goto error_status_get_tuner_registers;

	TunerBitsIfStage3 = (ReadingByte & RTL2832_E4000_IF_STAGE_3_GAIN_MASK) >> RTL2832_E4000_IF_STAGE_3_GAIN_SHIFT;
	TunerGainIfStage3 = IfStage3GainTable[TunerBitsIfStage3];

	// Get tuner IF stage 4 gain according to reading byte and table.
	if(I2CReadByte(this, NO_USE, RTL2832_E4000_IF_STAGE_4_GAIN_ADDR, &ReadingByte) != E4000_I2C_SUCCESS)
		goto error_status_get_tuner_registers;

	TunerBitsIfStage4 = (ReadingByte & RTL2832_E4000_IF_STAGE_4_GAIN_MASK) >> RTL2832_E4000_IF_STAGE_4_GAIN_SHIFT;
	TunerGainIfStage4 = IfStage4GainTable[TunerBitsIfStage4];

	// Get tuner IF stage 5 gain according to reading byte and table.
	if(I2CReadByte(this, NO_USE, RTL2832_E4000_IF_STAGE_5_GAIN_ADDR, &ReadingByte) != E4000_I2C_SUCCESS)
		goto error_status_get_tuner_registers;

	TunerBitsIfStage5 = (ReadingByte & RTL2832_E4000_IF_STAGE_5_GAIN_MASK) >> RTL2832_E4000_IF_STAGE_5_GAIN_SHIFT;
	TunerGainIfStage5 = IfStage5GainTable[TunerBitsIfStage5];

	// Get tuner IF stage 6 gain according to reading byte and table.
	if(I2CReadByte(this, NO_USE, RTL2832_E4000_IF_STAGE_6_GAIN_ADDR, &ReadingByte) != E4000_I2C_SUCCESS)
		goto error_status_get_tuner_registers;

	TunerBitsIfStage6 = (ReadingByte & RTL2832_E4000_IF_STAGE_6_GAIN_MASK) >> RTL2832_E4000_IF_STAGE_6_GAIN_SHIFT;
	TunerGainIfStage6 = IfStage6GainTable[TunerBitsIfStage6];

	// Calculate tuner total gain.
	// Note: The unit of tuner total gain is 0.1 dB.
	TunerGainTotal = TunerGainLna + TunerGainLnaAdd + TunerGainMixer + 
	                 TunerGainIfStage1 + TunerGainIfStage2 + TunerGainIfStage3 + TunerGainIfStage4 +
	                 TunerGainIfStage5 + TunerGainIfStage6;

	// Calculate tuner input power.
	// Note: The unit of tuner input power is 0.1 dBm
	TunerInputPower = RTL2832_E4000_TUNER_OUTPUT_POWER_UNIT_0P1_DBM - TunerGainTotal;

/*	AfxTrace(_T("Current gain state:\n"
		"\tFreq:\t%i kHz\n"
		"\tBW:\t%i kHz\n"
		"\tLNA:\t%.1f dB\n"
		"\tLNA+:\t%.1f dB\n"
		"\tMixer:\t%.1f dB\n"
		"\tIF 1:\t%.1f dB\n"
		"\tIF 2:\t%.1f dB\n"
		"\tIF 3:\t%.1f dB\n"
		"\tIF 4:\t%.1f dB\n"
		"\tIF 5:\t%.1f dB\n"
		"\tIF 6:\t%.1f dB\n"
		"\tTotal:\t%.1f dB\n"
		"\tPower:\t%.1f dBm\n"),
		RfFreqKhz,
		BandwidthKhz,
		(float)TunerGainLna/10.0f,
		(float)TunerGainLnaAdd/10.0f,
		(float)TunerGainMixer/10.0f,
		(float)TunerGainIfStage1/10.0f,
		(float)TunerGainIfStage2/10.0f,
		(float)TunerGainIfStage3/10.0f,
		(float)TunerGainIfStage4/10.0f,
		(float)TunerGainIfStage5/10.0f,
		(float)TunerGainIfStage6/10.0f,
		(float)TunerGainTotal/10.0f,
		(float)TunerInputPower/10.0f);
*/
	// Determine tuner gain mode according to tuner input power.
	// Note: The unit of tuner input power is 0.1 dBm
	switch (m_iTunerGainMode)
	{
		default:
		case RTL2832_E4000_TUNER_GAIN_SENSITIVE:
			if(TunerInputPower > -650)
				TunerGainMode = RTL2832_E4000_TUNER_GAIN_NORMAL;
			break;

		case RTL2832_E4000_TUNER_GAIN_NORMAL:
			if(TunerInputPower < -750)
				TunerGainMode = RTL2832_E4000_TUNER_GAIN_SENSITIVE;
			if(TunerInputPower > -400)
				TunerGainMode = RTL2832_E4000_TUNER_GAIN_LINEAR;
			break;

		case RTL2832_E4000_TUNER_GAIN_LINEAR:
			if(TunerInputPower < -500)
				TunerGainMode = RTL2832_E4000_TUNER_GAIN_NORMAL;
			break;
	}

	if (TunerGainMode == -1)
		TunerGainMode = m_iTunerGainMode;

	if (m_iTunerGainMode != TunerGainMode)
	{
		switch (TunerGainMode)
		{
			case RTL2832_E4000_TUNER_GAIN_SENSITIVE:
				if (E4000_sensitivity(this, (int)(GetFreq()/1000.0), BANDWIDTH/1000) != E4000_I2C_SUCCESS)
					goto error_status_get_tuner_registers;
				AfxTrace(_T("Tuner gain mode: sensitive\n"));
				break;
			case RTL2832_E4000_TUNER_GAIN_LINEAR:
				if (E4000_linearity(this, (int)(GetFreq()/1000.0), BANDWIDTH/1000) != E4000_I2C_SUCCESS)
					goto error_status_get_tuner_registers;
				AfxTrace(_T("Tuner gain mode: linear\n"));
				break;
			case RTL2832_E4000_TUNER_GAIN_NORMAL:
			default:
				if (E4000_nominal(this, (int)(GetFreq()/1000.0), BANDWIDTH/1000) != E4000_I2C_SUCCESS)
					goto error_status_get_tuner_registers;
				AfxTrace(_T("Tuner gain mode: nominal\n"));
				break;
		}

		m_iTunerGainMode = TunerGainMode;
	}

	goto set_tuner_mode_complete;

error_status_get_tuner_registers:
	AfxTrace(_T("Failed to set tuner gain mode\n"));
set_tuner_mode_complete:
	set_i2c_repeater(0);
	return TunerGainMode;
}

#include <StdAfx.h>
#include "USRP.h"

#define DEFAULT_IMAGE	_T("std_2rxhb_2tx.rbf")

LegacyUSRP::LegacyUSRP()
	: m_strImage(DEFAULT_IMAGE)
	, m_nBlockCount(16 * 8)
	, m_nChannel(1)
	, m_iMux(-1)
	, m_nDecimation(16)
{
	m_fpga_master_clock_freq = 64000000.0;
	m_recv_samples_per_packet = /*128*//*512*/4096;
	m_dSampleRate = 4000000.0;
}

LegacyUSRP::~LegacyUSRP()
{
	Destroy();
}

void LegacyUSRP::Destroy()
{
	Stop();

	m_u_rx.reset();
	m_db_rx.reset();
}

bool LegacyUSRP::Create(LPCTSTR strHint /*= NULL*/)
{
	Destroy();

	//if (m_u_rx)
	//	return false;

	unsigned int unit = 0, side = 0, subdev = 0;

	CStringArray array;
	if (Teh::Utils::Tokenise(strHint, array, _T(' ')))
	{
		unit = _tstoi(array[0]);

		if (array.GetCount() > 1)
		{
			CStringA strSide(array[1]);
			strSide.MakeUpper();
			side = atoi(strSide.Left(1));
			if ((side == 0) && (strSide[0] != '0'))
				side = (int)strSide[0] - (int)'A';

			if ((strSide.GetLength() > 2) && (strSide[1] == ':'))
			{
				CStringA strSubDev(strSide.Mid(2));
				subdev = atoi(strSubDev);
				if ((subdev == 0) && (strSubDev != _T("0")))
				{
					if (strSubDev == _T("AB"))
						subdev = 3;
					else if (strSubDev.GetLength() == 1)
						subdev = (int)strSubDev[0] - (int)'A';
				}
			}
		}

		if (array.GetCount() > 2)
		{
			m_strImage = array[2];
		}
	}

	if (m_strImage.IsEmpty())
		m_strImage = DEFAULT_IMAGE;

	usrp_subdev_spec ss(side, subdev);

	m_u_rx = usrp_standard_rx::make(
			unit,
			m_nDecimation,
			m_nChannel,
			m_iMux,
			usrp_standard_rx::FPGA_MODE_NORMAL,
			m_recv_samples_per_packet * 4/* * 2*/,
			/*m_nBlockCount*/0,
			(LPCSTR)CStringA(m_strImage)
	);

	if (!m_u_rx)
	{
		AfxTrace(_T("Failed to create device\n"));
		return false;
	}

	m_strName = CString(CStringA(m_u_rx->serial_number().c_str()));

	//m_u_rx->set_fpga_master_clock_freq(m_fpga_master_clock_freq);
	m_fpga_master_clock_freq = m_u_rx->fpga_master_clock_freq();

	m_recv_samples_per_packet = m_u_rx->block_size() / 4;

	//m_u_rx->stop();

	if(m_u_rx->is_valid(ss) == false)
	{
		AfxTrace(_T("Invalid sub-device specification\n"));
		return false;
	}

	m_db_rx = m_u_rx->selected_subdev(ss);
	if (!m_db_rx)
	{
		AfxTrace(_T("No daughterboard/sub-device found given specification\n"));
		return false;
	}

	m_u_rx->set_mux(m_u_rx->determine_rx_mux_value(ss));

	//set_gain(0.45);
	//m_db_rx->select_rx_antenna(1); // this is a nop for most db

	//float fStep = m_db_rx->gain_db_per_step();
	m_gainRange = uhd::gain_range_t(m_db_rx->gain_min(), m_db_rx->gain_max(), 0.5);	// FIXME: Derive this?

	//m_u_rx->adc_rate();	// 64MHz
	//m_u_rx->rx_freq(0);	// 0
	// Gain unknown
	// Antenna unknown

	SAFE_DELETE_ARRAY(m_pBuffer);

	m_pBuffer = new short[m_recv_samples_per_packet * 2];

	return true;
}

bool LegacyUSRP::Start()
{
	if (!m_db_rx || !m_u_rx)
		return false;

	if (m_bRunning)
		return false;

	CSingleLock lock(&m_cs, TRUE);

	if (m_db_rx->set_enable(1) == false)
		return false;

	if (m_u_rx->start() == false)
		return false;

	m_bRunning = true;

	return true;
}

void LegacyUSRP::Stop()
{
	if (!m_db_rx || !m_u_rx)
		return;

	if (m_bRunning == false)
		return;

	CSingleLock lock(&m_cs, TRUE);

	m_db_rx->set_enable(0);

	m_u_rx->stop();

	m_bRunning = false;
}

bool LegacyUSRP::SetGain(double dGain)
{
	m_dGain = dGain;

	if (!m_db_rx || !m_u_rx)
		return true;

	CSingleLock lock(&m_cs, TRUE);

	if (m_db_rx->set_gain((float)dGain) == false)
		return false;

	return true;
}

bool LegacyUSRP::SetAntenna(int iIndex)
{
	if (iIndex < 0)
		return false;

	if (!m_db_rx || !m_u_rx)
		return true;

	CSingleLock lock(&m_cs, TRUE);

	if (m_db_rx->select_rx_antenna(iIndex) == false)
		return false;

	return true;
}

bool LegacyUSRP::SetAntenna(LPCTSTR strAntenna)
{
	if (IS_EMPTY(strAntenna))
		return false;

	m_strAntenna = strAntenna;

	if (!m_db_rx || !m_u_rx)
		return true;

	CSingleLock lock(&m_cs, TRUE);

	if (m_db_rx->select_rx_antenna((LPCSTR)CStringA(m_strAntenna)) == false)
		return false;

	return true;
}

double LegacyUSRP::SetFreq(double dFreq)
{
	if (dFreq < 0)
		return -1;

	m_dFreq = dFreq;

	if (!m_db_rx || !m_u_rx)
		return 0;

	usrp_tune_result tr;

	CSingleLock lock(&m_cs, TRUE);

	if (m_u_rx->tune(0, m_db_rx, dFreq, &tr) == false)
		return false;

	m_tuneResult.target_inter_freq = dFreq;
	m_tuneResult.actual_inter_freq = tr.baseband_freq;
	m_tuneResult.target_dsp_freq = tr.dxc_freq + tr.residual_freq;	// FIXME: Check this
	m_tuneResult.actual_dsp_freq = tr.dxc_freq;

	return m_tuneResult.actual_inter_freq + m_tuneResult.actual_dsp_freq;
}

double LegacyUSRP::SetSampleRate(double dSampleRate)
{
	if (dSampleRate <= 0)
		return -1.0;

	m_dDesiredSampleRate = dSampleRate;

	if (!m_db_rx || !m_u_rx)
		return 0;

	CSingleLock lock(&m_cs, TRUE);

	m_nDecimation = (UINT)(m_fpga_master_clock_freq / dSampleRate);	// FIXME: Check

	if (m_u_rx->set_decim_rate(m_nDecimation) == false)
		return -1.0;

	m_dSampleRate = m_fpga_master_clock_freq / (double)m_nDecimation;

	return m_dSampleRate;
}

std::vector<std::string> LegacyUSRP::GetAntennas() const
{
	std::vector<std::string> array;

	array.push_back("TX/RX");
	array.push_back("RX2");
	array.push_back("RXA");
	array.push_back("RXB");
	array.push_back("RXAB");

	return array;
}

//LegacyUSRP::SetClock()
//{
//}

int LegacyUSRP::ReadPacket()
{
	bool bOverrun = false;
	int iSize = m_recv_samples_per_packet * 2 * 2;

	CSingleLock lock(&m_cs, TRUE);

	m_metadata.error_code = uhd::rx_metadata_t::ERROR_CODE_NONE;

	int iResult = m_u_rx->read(m_pBuffer, iSize, &bOverrun);

	if (iResult >= 0)
	{
		if (bOverrun)
			m_metadata.error_code = uhd::rx_metadata_t::ERROR_CODE_OVERFLOW;
	}

	if (iResult <= 0)
	{
		if (m_bRunning == false)
			return 0;

		return iResult;
	}

	return (iResult / 4);
}

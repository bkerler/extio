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

#include <StdAfx.h>
#include "USRP.h"

#include "PluginFactory.h"

#define DEFAULT_IMAGE	_T("std_2rxhb_2tx.rbf")

IMPLEMENT_PF(LegacyUSRP)

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
	m_strLastError.Empty();

	Destroy();

	//if (m_u_rx)
	//	return false;

	unsigned int unit = 0, side = 0, subdev = 0;

	m_strImage.Empty();
	m_strFirmware.Empty();

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
			m_strImage = array[2];

		if (array.GetCount() > 3)
			m_strFirmware = array[3];
	}

	//if (m_strImage.IsEmpty())
	//	m_strImage = DEFAULT_IMAGE;

	usrp_subdev_spec ss(side, subdev);

	try
	{
		m_u_rx = usrp_standard_rx::_make(
			unit,
			m_nDecimation,
			m_nChannel,
			m_iMux,
			usrp_standard_rx::FPGA_MODE_NORMAL,
			m_recv_samples_per_packet * 4,// * 2,
			0,	//m_nBlockCount,
			(LPCSTR)CStringA(m_strImage),
			(LPCSTR)CStringA(m_strFirmware)
		);
	}
	catch (const std::runtime_error& e)
	{
		m_strLastError = _T("While creating Legacy device: ") + CString(e.what());
		m_u_rx.reset();
		return false;
	}
	catch (...)
	{
		m_strLastError = _T("Unknown exception while creating Legacy device");
		m_u_rx.reset();
		return false;
	}

	if (!m_u_rx)
	{
		m_strLastError = _T("Failed to create Legacy device");
		return false;
	}

	m_strSerial = CString(CStringA(m_u_rx->serial_number().c_str()));
	m_strName = _T("USRP (") + m_strSerial + _T(")");

	//m_u_rx->set_fpga_master_clock_freq(m_fpga_master_clock_freq);
	m_fpga_master_clock_freq = m_u_rx->fpga_master_clock_freq();

	m_recv_samples_per_packet = m_u_rx->block_size() / 4;

	//m_u_rx->stop();

	if(m_u_rx->is_valid(ss) == false)
	{
		m_strLastError = _T("Invalid Legacy sub-device specification");
		return false;
	}

	m_db_rx = m_u_rx->selected_subdev(ss);	// Shouldn't throw because validity already checked
	if (!m_db_rx)
	{
		m_strLastError = _T("No daughterboard/sub-device found given Legacy specification");
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
	m_strLastError.Empty();

	if (!m_u_rx)
	{
		m_strLastError = _T("No device");
		return false;
	}
	else if (!m_db_rx)
	{
		m_strLastError = _T("No daughterboard");
		return false;
	}

	if (m_bRunning)
	{
		m_strLastError = _T("Already running");
		return false;
	}

	CSingleLock lock(&m_cs, TRUE);

	if (m_db_rx->set_enable(1) == false)
	{
		m_strLastError = _T("Failed to enable RX daughterboard");
		return false;
	}

	if (m_u_rx->start() == false)
	{
		m_strLastError = _T("Failed to start");
		return false;
	}

	m_bRunning = true;

	return true;
}

void LegacyUSRP::Stop()
{
	m_strLastError.Empty();

	if (!m_u_rx)
	{
		m_strLastError = _T("No device");
		return;
	}
	else if (!m_db_rx)
	{
		m_strLastError = _T("No daughterboard");
		return;
	}

	CSingleLock lock(&m_cs, TRUE);

	if (m_bRunning == false)
	{
		m_strLastError = _T("Already stopped");	// This will always be set when it's being Destroyed as no running check
		return;
	}

	m_db_rx->set_enable(0);

	m_u_rx->stop();

	m_bRunning = false;
}

bool LegacyUSRP::SetGain(double dGain)
{
	m_strLastError.Empty();

	m_dGain = dGain;

	if (!m_u_rx)
	{
		m_strLastError = _T("No device");
		return true;
	}
	else if (!m_db_rx)
	{
		m_strLastError = _T("No daughterboard");
		return true;
	}

	CSingleLock lock(&m_cs, TRUE);

	if (m_db_rx->set_gain((float)dGain) == false)
	{
		m_strLastError = _T("Failed to set RX gain");
		return false;
	}

	return true;
}

bool LegacyUSRP::SetAntenna(int iIndex)
{
	m_strLastError.Empty();

	if (iIndex < 0)
		return false;

	if (!m_u_rx)
	{
		m_strLastError = _T("No device");
		return true;
	}
	else if (!m_db_rx)
	{
		m_strLastError = _T("No daughterboard");
		return true;
	}

	CSingleLock lock(&m_cs, TRUE);

	if (m_db_rx->select_rx_antenna(iIndex) == false)
	{
		m_strLastError = _T("Failed to select RX antenna");
		return false;
	}

	return true;
}

bool LegacyUSRP::SetAntenna(LPCTSTR strAntenna)
{
	m_strLastError.Empty();

	if (IS_EMPTY(strAntenna))
		return false;

	m_strAntenna = strAntenna;

	if (!m_u_rx)
	{
		m_strLastError = _T("No device");
		return true;
	}
	else if (!m_db_rx)
	{
		m_strLastError = _T("No daughterboard");
		return true;
	}

	CSingleLock lock(&m_cs, TRUE);

	if (m_db_rx->select_rx_antenna((LPCSTR)CStringA(m_strAntenna)) == false)
	{
		m_strLastError = _T("Failed to select RX antenna");
		return false;
	}

	return true;
}

double LegacyUSRP::SetFreq(double dFreq)
{
	m_strLastError.Empty();

	if (dFreq < 0)
		return -1;

	m_dFreq = dFreq;

	if (!m_u_rx)
	{
		m_strLastError = _T("No device");
		return 0;
	}
	else if (!m_db_rx)
	{
		m_strLastError = _T("No daughterboard");
		return 0;
	}

	usrp_tune_result tr;

	CSingleLock lock(&m_cs, TRUE);

	if (m_u_rx->tune(0, m_db_rx, dFreq, &tr) == false)
	{
		m_strLastError = _T("Failed to tune");
		return false;
	}

	m_tuneResult./*target_inter_freq*/target_rf_freq = dFreq;
	m_tuneResult./*actual_inter_freq*/actual_rf_freq = tr.baseband_freq;
	m_tuneResult.target_dsp_freq = tr.dxc_freq + tr.residual_freq;	// FIXME: Check this
	m_tuneResult.actual_dsp_freq = tr.dxc_freq;

	return (m_dFreq = m_tuneResult./*actual_inter_freq*/actual_rf_freq + m_tuneResult.actual_dsp_freq);
}

int LegacyUSRP::WasTuneSuccessful(/*const uhd::tune_result_t& tuneResult*/)
{
	//AfxTrace(_T("Tune result: %s\n"), m_tuneResult.to_pp_string().c_str());

	double d = USRPConfiguration::GetFreq();
	if (fabs(m_dFreq - d) >= 1.0)
	{
		return ((m_dFreq > d) ? 1 : -1);
	}

	return 0;
}

double LegacyUSRP::SetSampleRate(double dSampleRate)
{
	m_strLastError.Empty();

	if (dSampleRate <= 0)
		return -1.0;

	m_dDesiredSampleRate = dSampleRate;

	if (!m_u_rx)
	{
		m_strLastError = _T("No device");
		return 0;
	}
	else if (!m_db_rx)
	{
		m_strLastError = _T("No daughterboard");
		return 0;
	}

	CSingleLock lock(&m_cs, TRUE);

	m_nDecimation = (UINT)(m_fpga_master_clock_freq / dSampleRate);	// FIXME: Check

	if (m_u_rx->set_decim_rate(m_nDecimation) == false)
	{
		m_strLastError = _T("Failed to set decimation rate");
		return -1.0;
	}

	m_dSampleRate = m_fpga_master_clock_freq / (double)m_nDecimation;

	return m_dSampleRate;
}

std::vector<std::string> LegacyUSRP::GetAntennas() const
{
	const_cast<CString&>(m_strLastError).Empty();

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
	//m_strLastError.Empty();

	if (!m_u_rx)
	{
		m_strLastError = _T("No device");
		return -1;
	}

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

		m_strLastError = _T("Failed to read samples");

		return iResult;
	}

	return (iResult / 4);
}

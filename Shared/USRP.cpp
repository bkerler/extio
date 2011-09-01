#include "StdAfx.h"
#include "USRP.h"

#include <uhd/usrp/mboard_props.hpp>
#include <uhd/usrp/device_props.hpp>

USRPConfiguration::USRPConfiguration()
	: m_dSampleRate(0.0)
	, m_dFreq(0.0)
	, m_dGain(0.0)
{
}

USRPConfiguration::USRPConfiguration(const USRPConfiguration& src)
{
	CopyFrom(&src);
}
/*
USRPConfiguration::~USRPConfiguration()
{
}
*/
void USRPConfiguration::CopyFrom(const IUSRPConfiguration* pOther)
{
	if (pOther == NULL)
		return;

	m_dSampleRate = pOther->GetSampleRate();
	m_dFreq = pOther->GetFreq();
	m_dGain = pOther->GetGain();
	m_strAntenna = pOther->GetAntenna();
}

///////////////////////////////////////////////////////////////////////////////

USRPSkeleton::USRPSkeleton()
	: m_fpga_master_clock_freq(0.0)
	, m_dDesiredSampleRate(0.0)
	, m_recv_samples_per_packet(0)
	, m_bRunning(false)
	, m_pBuffer(NULL)
{
	ZERO_MEMORY(m_tuneResult);
	ZERO_MEMORY(m_metadata);
	//m_gainRange = uhd::gain_range_t(0.0, 0.0, 0.0);

	ResetStats();
}


USRPSkeleton::~USRPSkeleton()
{
	SAFE_DELETE_ARRAY(m_pBuffer);
}

void USRPSkeleton::ResetStats()
{
	m_metadata.error_code = uhd::rx_metadata_t::ERROR_CODE_NONE;

	m_nSamplesReceived = 0;
	m_nOverflows = 0;
}

int USRPSkeleton::WasTuneSuccessful(/*const uhd::tune_result_t& tuneResult*/)
{
	//AfxTrace(_T("Tune result: %s\n"), m_tuneResult.to_pp_string().c_str());

	double d = USRPConfiguration::GetFreq();
	if (fabs(m_dFreq - d) >= 1.0)
	{
		return ((m_dFreq > d) ? 1 : -1);
	}

	return 0;
}

bool USRPSkeleton::CopyState(IUSRP* pOther)
{
	if (pOther == NULL)
		return false;

	if (SetSampleRate(pOther->GetSampleRate()) <= 0)
		return false;

	if (SetGain(pOther->GetGain()) == false)
		return false;

	if (SetAntenna(pOther->GetAntenna()) == false)
		return false;

	if (SetFreq(pOther->GetFreq()) < 0)
		return false;
	
	return true;
}

///////////////////////////////////////////////////////////////////////////////

USRP::USRP()
{
}

USRP::~USRP()
{
	Stop();

	//if (m_dev)
	//	Sleep(1000);	// TODO: Does this fix the libusb-1 hang problem? No.
}

bool USRP::Create(LPCTSTR strHint /*= NULL*//*, double dSampleRate = 0*/)
{
	m_strLastError.Empty();

	if (m_dev)
	{
		m_strLastError = _T("Device already exists");
		return false;
	}

	CString strFilteredHint(strHint);
	CStringArray array;
	CString strSubDevice;
	//uhd::usrp::subdev_spec_t subdev;
	INT_PTR iRemove = -1;
	if (Teh::Utils::Tokenise(strHint, array, _T(',')/*, _T(" "), true*/))	// Keep originals intact	// FIXME: Assumes NO use of "
	{
		for (INT_PTR i = 0; i < array.GetCount(); ++i)
		{
			CString str(array[i]);
			str.Trim();
			if (str.IsEmpty())
				continue;

			int iIndex = str.Find(_T(':'));
			str.MakeUpper();
			if (iIndex == -1)
			{
				if (str.GetLength() == 1)
				{
					if ((str[0] >= _T('A')) && (str[0] <= _T('Z')))
					{
						strSubDevice = str + _T(":0");
						//subdev = uhd::usrp::subdev_spec_t(std::string(CStringA(str)) + ":0");
						iRemove = i;
						break;
					}
				}

				continue;
			}
			else if ((iIndex != 1) || (str.GetLength() < 3))
				continue;

			if ((str[0] < _T('A')) || (str[0] > _T('Z')))
				continue;

			strSubDevice = str;
			//subdev = uhd::usrp::subdev_spec_t(std::string(CStringA(str)));
			iRemove = i;
			break;
		}
	}

	if (iRemove > -1)
	{
		array.RemoveAt(iRemove);
		strFilteredHint = Teh::Utils::ToString(array, _T(","));
	}

	try
	{
		CStringA strHintA(strFilteredHint);
		uhd::device_addr_t dev_addr((LPCSTR)strHintA);

		if (!(m_dev = uhd::usrp::single_usrp::make(dev_addr)))
			return false;
	}
/*	catch (const uhd::exception& e)
	{
		//e->dynamic_clone();
		e.what();
		return false;
	}
*/	catch (const std::runtime_error& e)
	{
		m_strLastError = _T("While creating UHD device: ") + CString(e.what());
		return false;
	}
	catch (...)
	{
		m_strLastError = _T("Unknown while creating UHD device");
		return false;
	}

	//if (subdev.empty() == false)
	if (strSubDevice.IsEmpty() == false)
	{
		try
		{
			m_dev->set_rx_subdev_spec(/*subdev*/uhd::usrp::subdev_spec_t(std::string(CStringA(strSubDevice))));
		}
		catch (const std::runtime_error& e)
		{
			m_strLastError = _T("While setting UHD RX sub-device: ") + CString(e.what());
			return false;
		}
		catch (...)
		{
			//AfxTrace(_T("Failed to set sub-device specification: %s\n"), strHint);
			m_strLastError = _T("Unknown while setting UHD RX sub-device");
			return false;
		}
	}

	size_t nMBs = m_dev->get_num_mboards();

	m_recv_samples_per_packet = m_dev->get_device()->get_max_recv_samps_per_packet();

	try
	{
		m_strName = CString(CStringA(m_dev->get_mboard_name().c_str()));	// This is the fail-safe

		//uhd::usrp::mboard_iface::sptr mboard = m_dev->get_mboard_iface(0);

		//wax::obj wDev = m_dev->get_device();
		std::string mb_name = (*m_dev->get_device())[uhd::usrp::DEVICE_PROP_MBOARD_NAMES].as<uhd::prop_names_t>().at(0);
		wax::obj mb = (*m_dev->get_device())[uhd::named_prop_t(uhd::usrp::DEVICE_PROP_MBOARD, mb_name)];
		//wax::obj eeprom = (mb[uhd::usrp::MBOARD_PROP_EEPROM_MAP]);
		uhd::usrp::mboard_eeprom_t eeprom = (mb[uhd::usrp::MBOARD_PROP_EEPROM_MAP]).as<uhd::usrp::mboard_eeprom_t>();
		//wax::obj eeprom = wax::obj(mboard)[wax::obj(uhd::usrp::MBOARD_PROP_EEPROM_MAP)];
		//std::string strSerial = eeprom[wax::obj(std::string("serial"))].as<std::string>();
		std::string strSerial = eeprom["serial"];
		m_strName = CString(CStringA(strSerial.c_str()));
	}
	catch (...)
	{
		AfxTrace(_T("Exception while getting serial number\n"));
	}

	m_fpga_master_clock_freq = m_dev->get_master_clock_rate();
	m_gainRange = m_dev->get_rx_gain_range();

	m_dSampleRate = m_dev->get_rx_rate();
	m_dFreq = m_dev->get_rx_freq();
	m_dGain = m_dev->get_rx_gain();
	m_strAntenna = m_dev->get_rx_antenna().c_str();

	SAFE_DELETE_ARRAY(m_pBuffer);

	m_pBuffer = new short[m_recv_samples_per_packet * 2];

	return true;
}
/*
bool USRP::SetClock()
{
	uhd::clock_config_t clock_config;
	clock_config.pps_source = uhd::clock_config_t::PPS_SMA;
	clock_config.pps_polarity = uhd::clock_config_t::PPS_NEG;

	if (m_external_ref)
		clock_config.ref_source = uhd::clock_config_t::REF_SMA;
	else
		clock_config.ref_source = uhd::clock_config_t::REF_INT;

	m_dev->set_clock_config(clock_config);
}
*/
double USRP::SetSampleRate(double dSampleRate)
{
	m_strLastError.Empty();

	if (dSampleRate <= 0)
	{
		m_strLastError = _T("Invalid sample rate");
		return -1.0;
	}

	m_dDesiredSampleRate = dSampleRate;

	if (!m_dev)
	{
		m_strLastError = _T("No device");
		return 0.0;
	}

	CSingleLock lock(&m_cs, TRUE);

	try
	{
		m_dev->set_rx_rate(m_dDesiredSampleRate);
	}
	catch (const std::runtime_error& e)
	{
		m_strLastError = _T("While setting RX rate: ") + CString(e.what());
		return -1.0;
	}
	catch (...)
	{
		m_strLastError = _T("Unknown while setting RX rate");
		return -1.0;
	}

	// FIXME: Flush

	m_dSampleRate = m_dev->get_rx_rate();

	return m_dSampleRate;
}

bool USRP::SetGain(double dGain)
{
	m_strLastError.Empty();

	//if ((dGain < 0.0) || (1.0 < dGain))
	//	return false;

	m_dGain = dGain;

	if (!m_dev)
	{
		m_strLastError = _T("No device");
		return true;
	}

	CSingleLock lock(&m_cs, TRUE);

	try
	{
		//m_dev->set_rx_gain(m_gainRange.start() + dGain * (m_gainRange.stop() - m_gainRange.start()));

		m_dev->set_rx_gain(dGain);
	}
	catch (const std::runtime_error& e)
	{
		m_strLastError = _T("While setting gain: ") + CString(e.what());
		return false;
	}
	catch (...)
	{
		m_strLastError = _T("Unknown while setting gain");
		return false;
	}

	return true;
}

std::vector<std::string> USRP::GetAntennas() const
{
	const_cast<CString&>(m_strLastError).Empty();

	std::vector<std::string> array;

	if (m_dev)
	{
		try
		{
			array = m_dev->get_rx_antennas();
		}
		catch (const std::runtime_error& e)
		{
			const_cast<CString&>(m_strLastError) = _T("While getting RX antennas: ") + CString(e.what());
		}
		catch (...)
		{
			const_cast<CString&>(m_strLastError) = _T("Unknown while getting RX antennas");
		}
	}
	else
		const_cast<CString&>(m_strLastError) = _T("No device");

/*	if ((array.empty()) ||
		((array.size() == 1) && (array[0].empty())))
	{
		array.push_back("TX/RX");
		array.push_back("RX2");
		array.push_back("RXA");
		array.push_back("RXB");
		array.push_back("RXAB");
	}
*/
	return array;
}

bool USRP::SetAntenna(int iIndex)
{
	m_strLastError.Empty();

	if (!m_dev)
	{
		m_strLastError = _T("No device");
		return false;
	}
	else if (iIndex < 0)
	{
		m_strLastError = _T("Non-positive index");
		return false;
	}

	std::vector<std::string> antennas = m_dev->get_rx_antennas();
	if (iIndex >= (int)antennas.size())
	{
		m_strLastError = _T("Index outside array");
		return false;
	}

	m_strAntenna = CStringA(antennas[iIndex].c_str());

	CSingleLock lock(&m_cs, TRUE);
	
	try
	{
		m_dev->set_rx_antenna((LPCSTR)CStringA(m_strAntenna));
	}
	catch (const std::runtime_error& e)
	{
		m_strLastError = _T("While setting antenna: ") + CString(e.what());
		return false;
	}
	catch (...)
	{
		m_strLastError = _T("Unknown while setting antenna");
		return false;
	}

	return true;
}

bool USRP::SetAntenna(LPCTSTR strAntenna)
{
	m_strLastError.Empty();

	if (IS_EMPTY(strAntenna))
	{
		m_strLastError = _T("Empty antenna");
		return false;
	}

	m_strAntenna = strAntenna;

	if (!m_dev)
	{
		m_strLastError = _T("No device");
		return true;
	}

	CSingleLock lock(&m_cs, TRUE);

	try
	{
		m_dev->set_rx_antenna((LPCSTR)CStringA(m_strAntenna));
	}
	catch (const std::runtime_error& e)
	{
		m_strLastError = _T("While setting antenna: ") + CString(e.what());
		return false;
	}
	catch (/*std::exception*//*uhd::assertion_error*/...)	// Invalid antenna
	{
		m_strLastError = _T("Unknown while setting antenna");
		return false;
	}

	return true;
}

double USRP::SetFreq(double dFreq)
{
	m_strLastError.Empty();

	if (dFreq < 0)
	{
		m_strLastError = _T("Non-positive frequency");
		return -1;
	}

	m_dFreq = dFreq;

	if (!m_dev)
	{
		m_strLastError = _T("No device");
		return 0;
	}

	CSingleLock lock(&m_cs, TRUE);

	try
	{
		m_tuneResult = m_dev->set_rx_freq(dFreq);
	}
	catch (const std::runtime_error& e)
	{
		m_strLastError = _T("While setting frequency: ") + CString(e.what());
		return -1;
	}
	catch (...)
	{
		m_strLastError = _T("Unknown while setting frequency");
		return -1;
	}

	return m_tuneResult.actual_inter_freq + m_tuneResult.actual_dsp_freq;
}

bool USRP::Start()
{
	m_strLastError.Empty();

	if (!m_dev)
	{
		m_strLastError = _T("No device");
		return false;
	}

	if (m_bRunning)
	{
		m_strLastError = _T("Already running");
		return true;
	}

	uhd::stream_cmd_t cmd =	uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS;

	CSingleLock lock(&m_cs, TRUE);

	try
	{
		m_dev->issue_stream_cmd(cmd);
	}
	catch (const std::runtime_error& e)
	{
		m_strLastError = _T("While starting stream: ") + CString(e.what());
		return false;
	}
	catch (...)
	{
		m_strLastError = _T("Unknown while starting stream");
		return false;
	}

	ResetStats();

	m_bRunning = true;

	return true;
}

void USRP::Stop()
{
	m_strLastError.Empty();

	if (!m_dev)
	{
		m_strLastError = _T("No device");
		return;
	}

	if (m_bRunning == false)
	{
		m_strLastError = _T("Already stopped");
		return;
	}

	uhd::stream_cmd_t cmd = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;

	CSingleLock lock(&m_cs, TRUE);

	try
	{
		m_dev->issue_stream_cmd(cmd);
	}
	catch (const std::runtime_error& e)
	{
		m_strLastError = _T("While stopping stream: ") + CString(e.what());
		//return;
	}
	catch (...)
	{
		m_strLastError = _T("Unknown while stopping stream");
		//return;
	}

	m_bRunning = false;
}

int USRP::ReadPacket()
{
	//m_strLastError.Empty();	// Skipping this here

	if (!m_dev)
	{
		m_strLastError = _T("No device");
		return -1;
	}
	else if (!m_recv_samples_per_packet)
	{
		m_strLastError = _T("Un-calculated samples per packet");
		return -1;
	}
	else if (!m_pBuffer)
	{
		m_strLastError = _T("Un-allocated sample buffer");
		return -1;
	}

	//if (m_bRunning == false)	// FIXME: Does recv block when not yet running? Returns error value?
	//	return;

	CSingleLock lock(&m_cs, TRUE);

	try
	{
		size_t samples_read = m_dev->get_device()->recv(
					(void*)m_pBuffer,
					m_recv_samples_per_packet,
					m_metadata,
					uhd::io_type_t::COMPLEX_INT16,
					uhd::device::RECV_MODE_ONE_PACKET);

		m_nSamplesReceived += samples_read;

		if (m_metadata.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW)
			++m_nOverflows;

		/*if (samples_read != m_recv_samples_per_packet)
		{
			AfxTrace(_T("Only read %lu samples of %lu (missing %lu)\n"), samples_read, m_recv_samples_per_packet, (m_recv_samples_per_packet - samples_read));
		}*/

		return samples_read;
	}
	catch (const std::runtime_error& e)
	{
		if (m_bRunning == false)
			return 0;

		m_strLastError = _T("While reading samples: ") + CString(e.what());

		return -1;
	}
	catch (...)
	{
		if (m_bRunning == false)
			return 0;

		m_strLastError = _T("Unknown while reading samples");

		return -1;
	}
}

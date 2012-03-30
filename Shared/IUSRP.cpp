#include "StdAfx.h"
#include "IUSRP.h"

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
	m_gainRange = uhd::gain_range_t(0.0, 0.0/*, 0.0*/);

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

bool USRPSkeleton::CopyState(IUSRPConfiguration* pOther)
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

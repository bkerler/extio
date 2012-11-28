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

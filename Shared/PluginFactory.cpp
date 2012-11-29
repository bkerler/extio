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
#include "PluginFactory.h"

PluginFactory* PluginFactory::m_pInstance = NULL;

PluginFactory::PluginFactory()
{
}

PluginFactory::~PluginFactory()
{
}

PluginFactory* PluginFactory::Get()
{
	if (m_pInstance == NULL)
		m_pInstance = new PluginFactory();

	return m_pInstance;
}

void PluginFactory::Register(LPCSTR strName, FactoryFn pfn)
{
	std::string str(strName);
	m_map.insert(make_pair(str, pfn));
}

IUSRP* PluginFactory::Create(LPCSTR strName)
{
	FactoryMap::iterator it = m_map.find(std::string(strName));
	if (it == m_map.end())
		return NULL;

	FactoryFn pfn = it->second;

	return (pfn)();
}

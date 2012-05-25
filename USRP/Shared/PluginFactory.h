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

#pragma once

class IUSRP;

class PluginFactory
{
public:
	PluginFactory();
	~PluginFactory();
public:
	typedef IUSRP* (*FactoryFn)();
	typedef std::map<std::string,FactoryFn> FactoryMap;
	FactoryMap m_map;
public:
	static PluginFactory* m_pInstance;
	static PluginFactory* Get();
public:
	void Register(LPCSTR strName, FactoryFn pfn);
	IUSRP* Create(LPCSTR strName);
};

#define g_pf (*PluginFactory::Get())

class PluginRegistrant
{
public:
	PluginRegistrant(LPCSTR strName, PluginFactory::FactoryFn pfn)
	{ g_pf.Register(strName, pfn); }
};

#define IMPLEMENT_PF(class_name) \
	static IUSRP* _create_##class_name() { \
	return new class_name(); } \
	static PluginRegistrant _pr_##class_name((#class_name), _create_##class_name);

#define PF_CREATE(class_name) \
	g_pf.Create((#class_name))

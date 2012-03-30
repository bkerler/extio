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

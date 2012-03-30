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

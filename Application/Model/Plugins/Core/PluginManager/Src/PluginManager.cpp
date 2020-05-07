#include "PreCompile.h"
#include "PluginManager.h"

GENERATE_PLUGIN(PLUGIN_MANAGER_PLUGIN, PluginManager);

// Construct the Engine
PluginManager::PluginManager() :
	m_strPluginConfigureFilePath(_T("")),
	m_bDisposed(false)
{
	Initialize();
}

// Detructe the Engine
PluginManager::~PluginManager()
{
	Destory();
}

// Init the Engine 
None PluginManager::Initialize()
{
	// Init the plugin configuration
	InitPluginConfigure();
}

// Destory the Engine
None PluginManager::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Init the plugin configure file name
None PluginManager::InitPluginConfigure()
{
	// Set the plugin configure filename
	String strPluginDirPath = Directory::AddEnding(Directory::GetExcutableDirectory()) 
		+ _T("Plugin\\Plugin.json");

	SetPluginConfigureFilePath(strPluginDirPath);
}

// Init the plugin name table
None PluginManager::InitPluginNameTable()
{
	if (GetPluginConfigureFilePath().IsEmpty())
	{
		return;
	}

	JsonDocument JsonDoc = JsonDocument::FromJsonFile(GetPluginConfigureFilePath());
	if (JsonDoc.IsNull())
	{
		return;
	}

	JsonDocument JsonObj = JsonDoc.GetKeyValue(_T("Plugin"));
	if (JsonObj.IsArray())
	{
		for (Index iIndex=0; iIndex<(Index)JsonObj.Size();++iIndex)
		{
			GetPluginNameTable().push_back(JsonObj[iIndex].ToString());
		}
	}
}

// Clear the plugin name table
None PluginManager::ClearPluginNameTable()
{
	if (GetPluginNameTable().empty())
	{
		return;
	}

	GetPluginNameTable().clear();

	PluginNameTable().swap(GetPluginNameTable());
}

// Clear the plugin table
None PluginManager::ClearPluginMapTable()
{
	if (m_PluginMapTable.empty())
	{
		LOG_DEBUG(String(_T("Plugin table is None")), _T(""));

		return;
	}

	for (PluginMapTable::iterator ModuleIter = m_PluginMapTable.begin();
		ModuleIter != m_PluginMapTable.end();)
	{
		String strModuleName = (std::string)(ModuleIter->first);

		UnRegisterModule(strModuleName);

		ModuleIter=m_PluginMapTable.erase(ModuleIter);

		LOG_DEBUG(String(_T("Successfully destory plugin:%s")).Arg(strModuleName), _T(""));
	}

	PluginMapTable().swap(m_PluginMapTable);
}

// Is module has been loaded
Boolean PluginManager::IsModuleLoaded(String strModuleName)
{
	if (strModuleName.IsEmpty())
	{
		return false;
	}

	if (m_PluginMapTable.find(strModuleName.ToANSIData())!= m_PluginMapTable.end())
	{
		return true;
	}

	return false;
}

// Create a plugin
PluginManager::Loader PluginManager::CreatePlugin(String strPluginName)
{
	if (strPluginName.IsEmpty())
	{
		return NULL;
	}

	Loader pLoader=new PluginLoader<IPlugin>();

	pLoader->Load(strPluginName);

	return pLoader;
}

// Destory the  plugin
None PluginManager::DestoryPlugin(Loader pLoader)
{
	if (pLoader)
	{
		delete pLoader;

		pLoader = NULL;
	}
}

// Create plugin modules
None PluginManager::CreatePluginModules(PluginNameTable& Table)
{
	if (Table.empty())
	{
		LOG_DEBUG(String(_T("Plugin table is None")), _T(""));

		return;
	}

	for (Index iPluginIndex=0; iPluginIndex<(Index)Table.size();++iPluginIndex)
	{
		String strPluginName = Table[iPluginIndex];

		// Create the module
		Loader pPluginLoader;
		if (!CreateModule(strPluginName, pPluginLoader))
		{
			continue;
		}

		// Add the plugin module
		RegisterModule(strPluginName, pPluginLoader);

		LOG_DEBUG(String(_T("Successfully create plugin:%s")).Arg(strPluginName),_T(""));
	}
}

// Create the module
Boolean PluginManager::CreateModule(String strPluginName, Loader& pLoader)
{
	if (strPluginName.IsEmpty())
	{
		return false;
	}

	// Check wether the module has been loaded
	if (IsModuleLoaded(strPluginName))
	{
		return true;
	}

	// Create the plugin
	pLoader = CreatePlugin(strPluginName);

	return true;
}

// Destory the plugin modules
None PluginManager::DestoryPluginModules()
{
	ClearPluginMapTable();
}

// Create a plugin name table
None PluginManager::CreatePluginNameTable()
{
	InitPluginNameTable();
}

// Destory the plugin name table
None PluginManager::DestoryPluginNameTable()
{
	ClearPluginNameTable();
}

// Add module to the table
Boolean PluginManager::RegisterModule(String strPluginName, Loader pLoader)
{
	if (strPluginName.IsEmpty())
	{
		return false;
	}

	if (pLoader == NULL)
	{
		return false;
	}

	// Find that if the plugin existed in the table
	if (m_PluginMapTable.find(strPluginName.ToANSIData()) != m_PluginMapTable.end())
	{
		return false;
	}

	m_PluginMapTable[strPluginName.ToANSIData()] = pLoader;

	return true;
}

// Remove module from the table
Boolean PluginManager::UnRegisterModule(String strPluginName)
{
	if (strPluginName.IsEmpty())
	{
		return false;
	}

	if (m_PluginMapTable.empty())
	{
		return false;
	}

	PluginMapTable::iterator ModuleIter = m_PluginMapTable.find(strPluginName.ToANSIData());

	if (ModuleIter !=m_PluginMapTable.end())
	{
		Loader pLoader = ModuleIter->second;

		DestoryPlugin(pLoader);
	}

	return true;
}

// Start the plugin Engine
Boolean PluginManager::Start()
{
	LOG_DEBUG(_T("Startup the plugin Engine"), _T(""));

	// Create plugin name table
	CreatePluginNameTable();

	// Create plugin modules 
	CreatePluginModules(GetPluginNameTable());

	return true;
};

// Stop the plugin Engine
Boolean PluginManager::Stop()
{
	LOG_DEBUG(_T("Shutdown the plugin Engine"), _T(""));

	// Destory the plugin modules
	DestoryPluginModules();

	// Destory the plugin name table
	DestoryPluginNameTable();

	return true;
}

// Get the module by name and version
IPlugin* PluginManager::GetPlugin(String strPluginName,
	Int32 iMajorVersion,
	Int32 iMinorVersion,
	Int32 iModifyVersion)
{
	if (strPluginName.IsEmpty())
	{
		return NULL;
	}

	if (iMajorVersion <= 0)
	{
		return NULL;
	}

	if (iMinorVersion < 0)
	{
		return false;
	}

	if (iModifyVersion < 0)
	{
		return NULL;
	}

	if (m_PluginMapTable.empty())
	{
		return NULL;
	}

	PluginMapTable::iterator ModuleIter = m_PluginMapTable.find(strPluginName.ToANSIData());

	if (ModuleIter != m_PluginMapTable.end())
	{
		Loader pLoader = ModuleIter->second;

		return pLoader->Data();
	}

	// Create the module
	Loader pLoader;
	if (!CreateModule(strPluginName, pLoader))
	{
		return NULL;
	}

	// Register the module
	RegisterModule(strPluginName, pLoader);

	return pLoader->Data();
}

// Release the plugin
Boolean PluginManager::ReleasePlugin(IPlugin* pPlugin)
{
	if (pPlugin==NULL)
	{
		return false;
	}

	UnRegisterModule(pPlugin->GetName());

	return true;
}
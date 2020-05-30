#include "PreCompile.h"
#include "EasyJson.h"
#include "PluginManager.h"

GENERATE_PLUGIN(PLUGIN_MANAGER_PLUGIN, PluginManager);

// Construct the Engine
PluginManager::PluginManager() :
	m_strPluginFilePath(""),
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
	// Get exe file path
	String strExeDirPath = Directory::AddEnding(Directory::GetExcutableDirectory());

	// Set the plugin configure file name
	String strPluginFilePath = strExeDirPath + PLUGIN_FILENAME;

	SetPluginFilePath(strPluginFilePath);
}

// Init the plugin name table
None PluginManager::InitPluginNameTable()
{
	if (GetPluginFilePath().IsEmpty())
	{
		LOG_DEBUG_EX("Plugin file path is empty !");

		return;
	}

	JsonDocument JsonDoc;

	EasyJson EasyJsonGetter;

	if (!EasyJsonGetter.GetJsonDoc(GetPluginFilePath(),JsonDoc))
	{
		LOG_DEBUG_EX(EasyJsonGetter.GetErrorMsg());

		return;
	}

	JsonDocument PluginObject = JsonDoc.GetKeyValue(_T("Plugin"));

	JsonDocument FundationObject = PluginObject.GetKeyValue(_T("Fundation"));
	if (FundationObject.IsArray())
	{
		for (Index iIndex = 0; iIndex < (Index)FundationObject.Size(); ++iIndex)
		{
			GetPluginNameTable().push_back(FundationObject[iIndex].ToString());
		}
	}

	JsonDocument BusinessObject = PluginObject.GetKeyValue(_T("Business"));
	if (BusinessObject.IsArray())
	{
		for (Index iIndex = 0; iIndex < (Index)BusinessObject.Size(); ++iIndex)
		{
			GetPluginNameTable().push_back(BusinessObject[iIndex].ToString());
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
		LOG_DEBUG_EX("There is no any plugin to release");

		return;
	}

	for (PluginMapTable::iterator ModuleIter = m_PluginMapTable.begin();
		ModuleIter != m_PluginMapTable.end();)
	{
		String strModuleName = (std::string)(ModuleIter->first);

		UnRegisterModule(strModuleName);

		ModuleIter=m_PluginMapTable.erase(ModuleIter);

		LOG_DEBUG_EX(String(_T("Successfully destory plugin:%s")).Arg(strModuleName));
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

	if (!pLoader->Load(strPluginName))
	{
		String strErrorMsg = String("Failed to create plugin: %s").Arg(strPluginName);

		LOG_ERROR_EX(strErrorMsg);
	}

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
		LOG_ERROR_EX("Plugin table is empty !");

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
		if (!RegisterModule(strPluginName, pPluginLoader))
		{
			DestoryPlugin(pPluginLoader);

			continue;
		}

		LOG_DEBUG_EX(String("Successfully register plugin:%s").Arg(strPluginName));
	}
}

// Create the module
Boolean PluginManager::CreateModule(String strPluginName, Loader& pLoader)
{
	if (strPluginName.IsEmpty())
	{
		LOG_ERROR_EX("Failed to create module owing to plugin name is empty !");

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
		LOG_ERROR_EX("Invalid plugin name when unregistering it !")

		return false;
	}

	if (m_PluginMapTable.empty())
	{
		LOG_ERROR_EX("Plugin table is empty !")

		return false;
	}

	PluginMapTable::iterator ModuleIter = m_PluginMapTable.find(strPluginName.ToANSIData());

	if (ModuleIter !=m_PluginMapTable.end())
	{
		Loader pLoader = ModuleIter->second;

		DestoryPlugin(pLoader);

		m_PluginMapTable.erase(ModuleIter);
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
		LOG_ERROR_EX("Plugin name is empty !");

		return NULL;
	}

	if (iMajorVersion <= 0)
	{
		LOG_ERROR_EX("Invalid major version , iMajorVersion <= 0");

		return NULL;
	}

	if (iMinorVersion < 0)
	{
		LOG_ERROR_EX("Invalid minor version , iMinorVersion < 0");

		return NULL;
	}

	if (iModifyVersion < 0)
	{
		LOG_ERROR_EX("Invalid modify version , iModifyVersion < 0");

		return NULL;
	}

	PluginMapTable::iterator ModuleIter = m_PluginMapTable.find(strPluginName.ToANSIData());

	if (ModuleIter != m_PluginMapTable.end())
	{
		Loader pLoader = ModuleIter->second;

		return pLoader->Data();
	}

	// Create module if it is not configured in the plugin file
	Loader pLoader = NULL;

	if (!CreateModule(strPluginName, pLoader))
	{
		return NULL;
	}

	// Register the module
	if (!RegisterModule(strPluginName, pLoader))
	{
		DestoryPlugin(pLoader);

		return NULL;
	}

	return pLoader->Data();
}

// Release the plugin
Boolean PluginManager::ReleasePlugin(IPlugin* pPlugin)
{
	if (pPlugin==NULL)
	{
		return false;
	}

	// Get plugin name
	String strPluginName = pPlugin->GetName();

	// Get it off from the plugin table and destory it
	return UnRegisterModule(strPluginName);
}

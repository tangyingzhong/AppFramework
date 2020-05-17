///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// This plugin manager dutys for other plugins loading and unloading
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef IPLUGINMANAGER_H
#define IPLUGINMANAGER_H

#include "Common/PluginGenerator.h"

#define PLUGIN_MANAGER_NAME _T("PluginManager")
#define PLUGIN_MANAGER__VERSION 1,0,0
#define PLUGIN_MANAGER_PLUGIN PLUGIN_MANAGER_NAME,PLUGIN_MANAGER__VERSION
#define PLUGIN_FILENAME _T("Plugin\\Plugin.json")

class IPluginManager :public IPlugin
{
public:
	// Virtual detructe the plugin manager
	virtual ~IPluginManager() {	}

public:
	// Get the plugin by name and version
	virtual IPlugin* GetPlugin(String strPluginName,
		Int32 iMajorVersion,
		Int32 iMinorVersion,
		Int32 iModifyVersion)=0;

	// Release the plugin
	virtual Boolean ReleasePlugin(IPlugin* pPlugin) = 0;
};
#endif // IPLUGINMANAGER_H

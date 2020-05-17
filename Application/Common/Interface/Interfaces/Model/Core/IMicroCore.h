///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Core responsible for running the plugin manager and prepare other resources
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef IMICROCORE_H
#define IMICROCORE_H

#include "Common/PluginGenerator.h"

#define  MICRO_CORE _T("MicroCore.dll")
#define MICRO_CORE_NAME _T("MicroCore")
#define MICRO_CORE_VERSION 1,0,0
#define MICRO_CORE_PLUGIN MICRO_CORE_NAME,MICRO_CORE_VERSION

class IMicroCore :public IPlugin
{
public:
	// Virtual detructe the core
	virtual ~IMicroCore() {	}

public:
	// Get the plugin by name and version
	virtual IPlugin* GetPlugin(String strPluginName,
		Int32 iMajorVersion,
		Int32 iMinorVersion,
		Int32 iModifyVersion) = 0;

	// Release the plugin
	virtual Boolean ReleasePlugin(IPlugin* pPlugin) = 0;

	// Auto run the task by core
	virtual bool AutoRun(TaskEntry* pTask) = 0;
};

#endif //IMICROCORE_H

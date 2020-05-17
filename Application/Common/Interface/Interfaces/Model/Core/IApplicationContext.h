///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Application context's interfaces which offering some services for whole app
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef IAPPLICATIONCONTEXT_H
#define IAPPLICATIONCONTEXT_H

#include "Common/PluginGenerator.h"

#define APPLICATION_CONTEXT_NAME _T("ApplicationContext")
#define APPLICATION_CONTEXT_VERSION 1,0,0
#define APPLICATION_CONTEXT_PLUGIN APPLICATION_CONTEXT_NAME,APPLICATION_CONTEXT_VERSION

class IApplicationContext :public IPlugin
{
public:
	// Virtual detructe the app context
	virtual ~IApplicationContext() {	}

public:
	// Get the plugin by name and version
	virtual IPlugin* GetPlugin(String strPluginName,
		Int32 iMajorVersion,
		Int32 iMinorVersion,
		Int32 iModifyVersion) = 0;

	// Release the plugin
	virtual Boolean ReleasePlugin(IPlugin* pPlugin) = 0;

	// Excute the task
	virtual bool Excute(TaskEntry* pTask) = 0;
};

#endif // IAPPLICATIONCONTEXT_H

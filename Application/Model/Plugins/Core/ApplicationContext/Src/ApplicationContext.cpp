#include "PreCompile.h"
#include "ApplicationContext.h"

GENERATE_PLUGIN(APPLICATION_CONTEXT_PLUGIN, ApplicationContext);

// Construct the context
ApplicationContext::ApplicationContext() :
	m_pMicroCoreModule(NULL),
	m_bDisposed(false)
{
	Initialize();
}

// Destory the context
ApplicationContext::~ApplicationContext()
{
	Destory();
}

// Init the context
None ApplicationContext::Initialize()
{
	// Create micro core
	CreateMicroCore();
}

// Destory the context
None ApplicationContext::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Destory the micro core
		DestoryMicroCore();
	}
}

// Create micro core
None ApplicationContext::CreateMicroCore()
{
	if (!m_MicroCoreLoader.IsValid())
	{
		m_MicroCoreLoader.Load(MICRO_CORE);

		if (m_MicroCoreLoader.IsValid())
		{
			SetMicroCoreModule(m_MicroCoreLoader.Data());
		}
		else
		{
			SetMicroCoreModule(NULL);
		}
	}
}

// Destory the micro core
None ApplicationContext::DestoryMicroCore()
{
	if (GetMicroCoreModule())
	{
		delete GetMicroCoreModule();

		SetMicroCoreModule(NULL);
	}
}

// Excute the task
bool ApplicationContext::Excute(TaskEntry* pTask)
{
	if (pTask == NULL)
	{
		LOG_ERROR_EX("Task is invalid !");

		return false;
	}

	if (GetMicroCoreModule() == NULL)
	{
		LOG_ERROR_EX("Micro core hasn't been created !");

		return false;
	}

	return GetMicroCoreModule()->AutoRun(pTask);
}

// Start the micro engine
Boolean ApplicationContext::Start()
{
	LOG_DEBUG_EX("App context is establishing ......");

	if (GetMicroCoreModule()==NULL)
	{
		return false;
	}

	// Start the micro core
	return GetMicroCoreModule()->Start();
}

// Stop the micro engine
Boolean ApplicationContext::Stop()
{
	LOG_DEBUG_EX("App context is destroying ......");

	// Stop the micro core
	if (GetMicroCoreModule())
	{
		GetMicroCoreModule()->Stop();
	}

	return true;
}

// Get the module by name and version
IPlugin* ApplicationContext::GetPlugin(String strPluginName,
	Int32 iMajorVersion,
	Int32 iMinorVersion,
	Int32 iModifyVersion)
{
	if (GetMicroCoreModule())
	{
		return GetMicroCoreModule()->GetPlugin(strPluginName,
			iMajorVersion,
			iMinorVersion,
			iModifyVersion);
	}

	return NULL;
}

// Release the plugin
Boolean ApplicationContext::ReleasePlugin(IPlugin* pPlugin)
{
	if (GetMicroCoreModule())
	{
		GetMicroCoreModule()->ReleasePlugin(pPlugin);
	}

	return false;
}
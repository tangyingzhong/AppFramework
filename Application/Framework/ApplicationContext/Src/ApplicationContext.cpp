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
	
}

// Destory the context
None ApplicationContext::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
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

// Start the micro engine
Boolean ApplicationContext::Start()
{
	LOG_DEBUG(_T("Startup the app context"), _T(""));

	// Create micro core
	CreateMicroCore();

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
	LOG_DEBUG(_T("Shutdown the application's context"), _T(""));

	if (GetMicroCoreModule() == NULL)
	{
		return false;
	}

	// Stop the micro core
	return GetMicroCoreModule()->Stop();
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
#include "PreCompile.h"
#include "MicroCore.h"

GENERATE_PLUGIN(MICRO_CORE_PLUGIN, MicroCore);

// Construct the Kernel
MicroCore::MicroCore() :
	m_pPluginController(NULL),
	m_bDisposed(false)
{
	Initialize();
}

// Detructe the Kernel
MicroCore::~MicroCore()
{
	Destory();
}

// Init the Kernel 
None MicroCore::Initialize()
{
	// Create a plugin controller
	CreatePluginController();
}

// Destory the Kernel
None MicroCore::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Destory the plugin controller
		DestoryPluginController();
	}
}

// Create a plugin controller
None MicroCore::CreatePluginController()
{
	if (m_PluginManagerLoader.Load(PLUGIN_MANAGER_NAME))
	{
		SetPluginController(m_PluginManagerLoader.Data());
	}
	else
	{
		SetPluginController(NULL);
	}
}

// Destory the plugin controller
None MicroCore::DestoryPluginController()
{

}

// Start plugin controller
Boolean MicroCore::StartPluginController()
{
	if (GetPluginController() == NULL)
	{
		return false;
	}

	if (!GetPluginController()->Start())
	{
		return false;
	}

	return true;
}

// Stop plugin controller
Boolean MicroCore::StopPluginController()
{
	if (GetPluginController() == NULL)
	{
		return false;
	}

	if (!GetPluginController()->Stop())
	{
		return false;
	}

	return true;
}

// Start the micro Kernel
Boolean MicroCore::Start()
{
	LOG_DEBUG_EX(_T("Startup the micro core"));

	// Start a thread pool engine

	// Start an event engine

	// Start the plugin manager
	if (!StartPluginController())
	{
		LOG_ERROR_EX(_T("Failed to start plugin controller"));

		return false;
	}

	return true;
}

// Stop the micro Kernel
Boolean MicroCore::Stop()
{
	LOG_DEBUG_EX(_T("Shutdown the micro core"));

	// Stop the plugin center
	if (!StopPluginController())
	{
		LOG_ERROR_EX(_T("Failed to stop plugin controller"));
	}

	// Stop the event engine

	// Stop the thread pool engine
	
	return true;
}

// Get the plugin by name and version
IPlugin* MicroCore::GetPlugin(String strPluginName,
	Int32 iMajorVersion,
	Int32 iMinorVersion,
	Int32 iModifyVersion)
{
	if (GetPluginController())
	{
		return GetPluginController()->GetPlugin(strPluginName,
			iMajorVersion,
			iMinorVersion,
			iModifyVersion);
	}

	return NULL;
}

// Release the plugin
Boolean MicroCore::ReleasePlugin(IPlugin* pPlugin)
{
	if (GetPluginController())
	{
		GetPluginController()->ReleasePlugin(pPlugin);
	}

	return false;
}

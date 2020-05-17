#include "PreCompile.h"
#include "EasyJson.h"
#include "MicroCore.h"

GENERATE_PLUGIN(MICRO_CORE_PLUGIN, MicroCore);

// Construct the Kernel
MicroCore::MicroCore() :
	m_pPluginController(NULL),
	m_pThreadPool(NULL),
	m_iThreadPoolSize(0),
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
	// Load configure file
	LoadConfiguration();

	// Create thread pool
	CreateThreadPool();

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

		// Destory thread pool
		DestoryThreadPool();
	}
}

// Load configure file
Boolean MicroCore::LoadConfiguration()
{
	// Get the file path
	String strExeDirPath = Directory::AddEnding(Directory::GetExcutableDirectory());

	String strPluginFilePath = strExeDirPath + PLUGIN_FILENAME;

	// Read the configuration
	JsonDocument JsonDoc;

	EasyJson EasyJsonGetter;

	if (!EasyJsonGetter.GetJsonDoc(strPluginFilePath, JsonDoc))
	{
		LOG_DEBUG_EX(EasyJsonGetter.GetErrorMsg());

		return false;
	}

	JsonDocument PluginObject = JsonDoc.GetKeyValue(_T("Plugin"));
	if (PluginObject.IsNull())
	{
		LOG_DEBUG_EX(JsonDoc.GetErrorMsg());

		return false;
	}

	JsonDocument CoreObject = PluginObject.GetKeyValue("Core");
	if (CoreObject.IsNull())
	{
		LOG_DEBUG_EX(PluginObject.GetErrorMsg());

		return false;
	}

	Int32 iPoolSize = CoreObject.GetKeyValue("ThreadPoolSize").ToInt();

	SetThreadPoolSize(iPoolSize);

	return true;
}

// Create thread pool
None MicroCore::CreateThreadPool()
{
	if (GetThreadPoolSize() != 0)
	{
		SetThreadPool(new ThreadPool(GetThreadPoolSize()));

		return;
	}
	
	SetThreadPool(new ThreadPool());
}

// Destory the thread pool
None MicroCore::DestoryThreadPool()
{
	if (GetThreadPool())
	{
		delete GetThreadPool();

		SetThreadPool(NULL);
	}
}

// Start thread pool
None MicroCore::StartThreadPool()
{
	if (GetThreadPool())
	{
		GetThreadPool()->Start();
	}
}

// Stop thread pool
None MicroCore::StopThreadPool()
{
	if (GetThreadPool())
	{
		GetThreadPool()->Stop(true);
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

// Auto run the task by core
bool MicroCore::AutoRun(TaskEntry* pTask)
{
	if (pTask == NULL)
	{
		LOG_ERROR_EX("Task is invalid !");

		return false;
	}

	if (GetThreadPool() == NULL)
	{
		LOG_ERROR_EX("Thread pool hasn't been created !");

		return false;
	}

	return GetThreadPool()->AddTask(pTask);
}

// Start the micro Kernel
Boolean MicroCore::Start()
{
	LOG_DEBUG_EX(_T("Micro core is starting ......"));

	// Start a thread pool engine
	StartThreadPool();

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
	LOG_DEBUG_EX(_T("Micro core is shutdowning ......"));

	// Stop the plugin center
	if (!StopPluginController())
	{
		LOG_ERROR_EX(_T("Failed to stop plugin controller"));
	}

	// Stop the thread pool engine
	StopThreadPool();

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

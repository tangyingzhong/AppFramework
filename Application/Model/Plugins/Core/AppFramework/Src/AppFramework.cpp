#include "PreCompile.h"
#include "AppFramework.h"

AppFramework* AppFramework::m_pInstance = NULL;

AppFramework::Lock AppFramework::m_pInstanceLock = new Mutex();

// Get the AppFramework instance
AppFramework* AppFramework::GetInstance()
{
	if (m_pInstance==NULL)
	{
		MutexLocker Locker(m_pInstanceLock);

		if (m_pInstance==NULL)
		{
			AppFramework* pInstance = new AppFramework();

			m_pInstance = pInstance;
		}
	}

	return m_pInstance;
}

// Destory the app instance
None AppFramework::DestoryInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;

		m_pInstance = NULL;
	}
}

// Construct the AppFramework
AppFramework::AppFramework() :m_pAppContext(NULL),
m_bDisposed(false)
{
	Initialize();
}

// Destruct the AppFramework
AppFramework::~AppFramework()
{
	Destory();
}

// Initialize the AppFramework
None AppFramework::Initialize()
{
	// Create app context
	CreateAppContext();
}

// Destory the AppFramework
None AppFramework::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Create app context
None AppFramework::CreateAppContext()
{
	if (!m_PluginLoader.Load(APPLICATION_CONTEXT_NAME))
	{
		SetAppContext(NULL);
	}
	else
	{
		SetAppContext(m_PluginLoader.Data());
	}
}

// Get global AppFramework context
IApplicationContext* AppFramework::GetGlobalContext()
{
	return GetAppContext();
}

///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It duty for loading AppFramework's context
///</describe>
/// <date>2019/11/6</date>
///***********************************************************************
#ifndef APPFRAMEWORK_H
#define APPFRAMEWORK_H

#include "Model/Core/IApplicationContext.h"
#include "PluginLoader.h"

class CLASS_ITEM AppFramework
{
public:
	typedef Mutex* Lock;
	typedef PluginLoader<IApplicationContext>* Loader;

public:
	// Get the AppFramework instance
	static AppFramework* GetInstance();

	// Destory the app instance
	static None DestoryInstance();

private:
	// Construct the AppFramework
	AppFramework();

	// Destruct the AppFramework
	~AppFramework();

	// Forbid the AppFramework's copy
	AppFramework(const AppFramework& other){	}

	// Forbid the AppFramework's assignment
	AppFramework& operator=(const AppFramework& other) { return *this; }

public:
	// Get global AppFramework context
	IApplicationContext* GetGlobalContext();

private:
	// Initialize the AppFramework
	None Initialize();

	// Destory the AppFramework
	None Destory();

	// Create app context
	None CreateAppContext();

	// Destory app context
	None DestoryAppContext();

	// Create plugin loader
	None CreatePluginLoader();

	// Destory the plugin loader
	None DestoryPluginLoader();

	// Start app context
	None StartAppContext();

	// Stop the app context
	None StopAppContext();

private:
	// Get the AppContext
	inline IApplicationContext* GetAppContext() const
	{
		return m_pAppContext;
	}

	// Set the AppContext
	inline None SetAppContext(IApplicationContext* pAppContext)
	{
		m_pAppContext = pAppContext;
	}

	// Get the Disposed
	inline BOOL GetDisposed() const
	{
		return m_bDisposed;
	}

	// Set the Disposed
	inline None SetDisposed(BOOL bDisposed)
	{
		m_bDisposed = bDisposed;
	}

	// Get the PluginLoader
	inline Loader GetPluginLoader() const
	{
		return m_pPluginLoader;
	}

	// Set the PluginLoader
	inline void SetPluginLoader(Loader pPluginLoader)
	{
		m_pPluginLoader = pPluginLoader;
	}

private:
	// AppFramework self
	static AppFramework* m_pInstance;

	// Lock for the instance
	static Lock m_pInstanceLock;

	// AppFramework's context
	IApplicationContext* m_pAppContext;

	// Plugin loader
	Loader m_pPluginLoader;

	// AppFramework close state
	BOOL m_bDisposed;
};

#endif // APPFRAMEWORK_H
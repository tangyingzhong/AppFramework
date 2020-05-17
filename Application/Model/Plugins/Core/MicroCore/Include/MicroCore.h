///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It is duty for running the plugin manager and offering other services such as thread pool control
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef MICROCORE_H
#define MICROCORE_H

#include "Model/Core//IMicroCore.h"
#include "Model/Core//IPluginManager.h"
#include "PluginLoader.h"

class MicroCore :public PluginBase<IMicroCore>
{
public:
	typedef IPluginManager* PluginController;
	typedef PluginLoader<IPluginManager> Loader;
	typedef IThreadPool* ThreadPooller;

public:
	// Construct the kernel
	MicroCore();

	// Detructe the kernel
	virtual ~MicroCore();

private:
	// Forbid the copy kernel
	MicroCore(const MicroCore& other) {	}

	// Forbid the assigment of kernel
	MicroCore& operator=(const MicroCore& other) { return *this; }

public:
	// Start the micro kernel
	virtual Boolean Start();

	// Stop the micro kernel
	virtual Boolean Stop();

	// Get the plugin by name and version
	virtual IPlugin* GetPlugin(String strPluginName,
		Int32 iMajorVersion,
		Int32 iMinorVersion,
		Int32 iModifyVersion);

	// Release the plugin
	virtual Boolean ReleasePlugin(IPlugin* pPlugin);

	// Auto run the task by core
	virtual bool AutoRun(TaskEntry* pTask);

private:
	// Init the kernel 
	None Initialize();

	// Destory the kernel
	None Destory();

	// Load configure file
	Boolean LoadConfiguration();

	// Create a plugin controller
	None CreatePluginController();

	// Destory the plugin controller
	None DestoryPluginController();

	// Start plugin controller
	Boolean StartPluginController();

	// Stop plugin controller
	Boolean StopPluginController();

	// Create thread pool
	None CreateThreadPool();

	// Destory the thread pool
	None DestoryThreadPool();

	// Start thread pool
	None StartThreadPool();

	// Stop thread pool
	None StopThreadPool();

private:
	// Get the PluginController
	inline PluginController GetPluginController() const
	{
		return m_pPluginController;
	}

	// Set the PluginController
	inline None SetPluginController(PluginController pPluginController)
	{
		m_pPluginController = pPluginController;
	}

	// Set the disposed status
	inline None SetDisposed(Boolean bDisposed)
	{
		m_bDisposed = bDisposed;
	}

	// Get the disposed status
	inline Boolean GetDisposed() const
	{
		return m_bDisposed;
	}

	// Get the ThreadPool
	inline ThreadPooller GetThreadPool() const
	{
		return m_pThreadPool;
	}

	// Set the ThreadPool
	inline void SetThreadPool(ThreadPooller pThreadPool)
	{
		m_pThreadPool = pThreadPool;
	}

	// Get the ThreadPoolSize
	inline Int32 GetThreadPoolSize() const
	{
		return m_iThreadPoolSize;
	}

	// Set the ThreadPoolSize
	inline void SetThreadPoolSize(Int32 iThreadPoolSize)
	{
		m_iThreadPoolSize = iThreadPoolSize;
	}

private:
	// Plugin controller
	PluginController m_pPluginController;

	// Plugin manager loader
	Loader m_PluginManagerLoader;

	// Thread pool
	ThreadPooller m_pThreadPool;
	
	// Thread pool count
	Int32 m_iThreadPoolSize;
	
	// Disposed status
	Boolean m_bDisposed;
};

#endif // MICROCORE_H
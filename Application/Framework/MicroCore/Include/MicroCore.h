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

#include "Common/IMicroCore.h"
#include "Common/IPluginManager.h"
#include "PluginLoader.h"

class MicroCore :public PluginBase<IMicroCore>
{
public:
	typedef IPluginManager* PluginController;
	typedef PluginLoader<IPluginManager> Loader;

public:
	// Construct the kernel
	MicroCore();

	// Detructe the kernel
	~MicroCore();

private:
	// Forbid the copy kernel
	MicroCore(const MicroCore& other) {	}

	// Forbid the assigment of kernel
	MicroCore& operator=(const MicroCore& other) {	}

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

private:
	// Init the kernel 
	None Initialize();

	// Destory the kernel
	None Destory();

	// Create a plugin controller
	None CreatePluginController();

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

private:
	// Plugin controller
	PluginController m_pPluginController;

	// Plugin manager loader
	Loader m_PluginManagerLoader;

	// Disposed status
	Boolean m_bDisposed;
};

#endif // MICROCORE_H
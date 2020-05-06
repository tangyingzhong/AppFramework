///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It is the app's context which managing all are global resources
///</describe>
/// <date>2019/11/5</date>
///***********************************************************************
#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include "IApplicationContext.h"
#include "IMicroCore.h"
#include "PluginLoader.h"

class ApplicationContext :public PluginBase<IApplicationContext>
{
public:
	typedef Boolean BOOL;
	typedef Mutex* Lock;
	typedef IMicroCore* MicroCoreModule;
	typedef PluginLoader<IMicroCore> Loader;

public:
	// Construct the context
	ApplicationContext();

	// Destory the context
	~ApplicationContext();

private:
	// Forbid the context's copy
	ApplicationContext(const ApplicationContext& other){	}

	// Forbid the context's assignment
	ApplicationContext& operator=(const ApplicationContext& other){	}

public:
	// Start the micro engine
	virtual Boolean Start();

	// Stop the micro engine
	virtual Boolean Stop();

	// Get the plugin by name and version
	virtual IPlugin* GetPlugin(String strPluginName,
		Int32 iMajorVersion,
		Int32 iMinorVersion,
		Int32 iModifyVersion);

	// Release the plugin
	virtual Boolean ReleasePlugin(IPlugin* pPlugin);

private:
	// Init the context
	None Initialize();

	// Destory the context
	None Destory();

	// Create micro core
	None CreateMicroCore();

private:
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

	// Get the MicroCoreModule
	inline MicroCoreModule GetMicroCoreModule() const
	{
		return m_pMicroCoreModule;
	}

	// Set the MicroCoreModule
	inline None SetMicroCoreModule(MicroCoreModule pMicroCoreModule)
	{
		m_pMicroCoreModule = pMicroCoreModule;
	}

private:
	// Module loader
	Loader m_MicroCoreLoader;

	// Micro core module
	MicroCoreModule m_pMicroCoreModule;

	// Disposed status
	BOOL m_bDisposed;
};

#endif // APPLICATIONCONTEXT_H
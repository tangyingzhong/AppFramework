///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
///  Controlling all the plugins' start and stop dynamically
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "Model/Core/IPluginManager.h"
#include "PluginLoader.h"

class PluginManager :public PluginBase<IPluginManager>
{
public:
	typedef Int32 Index;
	typedef vector<String> PluginNameTable;
	typedef PluginLoader<IPlugin>* Loader;
	typedef std::map<std::string, Loader > PluginMapTable;
	
public:
	// Construct the engine
	PluginManager();

	// Detructe the engine
	virtual ~PluginManager();

private:
	// Forbid the copy engine
	PluginManager(const PluginManager& other) {	}

	// Forbid the assigment of engine
	PluginManager& operator=(const PluginManager& other) { return *this; }

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
	// Init the plugin configure file name
	None InitPluginConfigure();

	// Init the plugin name table
	None InitPluginNameTable();

	// Clear the plugin name table
	None ClearPluginNameTable();

	// Clear the plugin table
	None ClearPluginMapTable();

	// Create the module
	Boolean CreateModule(String strPluginName, Loader& pLoader);

	// Is module has been loaded
	Boolean IsModuleLoaded(String strPluginName);

	// Add module to the table
	Boolean RegisterModule(String strPluginName, Loader pLoader);

	// Remove module from the table
	Boolean UnRegisterModule(String strPluginName);

private:
	// Init the engine 
	None Initialize();

	// Destory the engine
	None Destory();

	// Create a plugin loader
	Loader CreatePlugin(String strPluginName);

	// Destory the  plugin loader
	None DestoryPlugin(Loader pLoader);

	// Create plugin modules
	None CreatePluginModules(PluginNameTable& Table);

	// Destory the plugin modules
	None DestoryPluginModules();

	// Create a plugin name table
	None CreatePluginNameTable();

	// Destory the plugin name table
	None DestoryPluginNameTable();

private:
	// Get the PluginConfigureFilePath
	inline String GetPluginConfigureFilePath() const
	{
		return m_strPluginConfigureFilePath;
	}

	// Set the PluginConfigureFilePath
	inline None SetPluginConfigureFilePath(String strFiilePath)
	{
		m_strPluginConfigureFilePath = strFiilePath;
	}

	// Get the plugin name table
	inline PluginNameTable& GetPluginNameTable()
	{
		return m_PluginNameTable;
	}

	// Set the plugin name table
	inline None SetPluginNameTable(PluginNameTable& Table)
	{
		m_PluginNameTable = Table;
	}

	// Get the disposed status
	inline Boolean GetDisposed() const
	{
		return m_bDisposed;
	}

	// Set the disposed status
	inline None SetDisposed(Boolean bDisposed)
	{
		m_bDisposed = bDisposed;
	}

private:
	// Plugin configure file path
	String m_strPluginConfigureFilePath;

	// Plugin name table
	PluginNameTable m_PluginNameTable;

	// Module table
	PluginMapTable m_PluginMapTable;

	// Lock for the plugins
	Mutex m_Lock;

	// Disposed status
	Boolean m_bDisposed;
};

#endif // PLUGINMANAGER_H
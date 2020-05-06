///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Offering common interface for all plugins
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef IPLUGIN_H
#define IPLUGIN_H

#define WARN_MESSAGEBOX(Title,Content) MessageBox(NULL,Content,Title,0);

class IPlugin
{
public:
	typedef IEventHandler::HandlerFunc HandlerFunc;

public:
	// Virtual detructe the plugin
	virtual ~IPlugin() {		}

public:
	// Start the plugin
	virtual Boolean Start() = 0;

	// Stop the plugin
	virtual Boolean Stop() = 0;

	// Set plugin name
	virtual Boolean SetName(String strName) = 0;

	// Get plugin name
	virtual String GetName() = 0;

	// Set plugin version
	virtual Boolean SetVersion(Int32 iMajorVersion,
		Int32 iMinorVersion,
		Int32 iModifyVersion) = 0;

	// Get plugin version
	virtual Boolean GetVersion(Int32& iMajorVersion,
		Int32& iMinorVersion,
		Int32& iModifyVersion) = 0;

	// Check plugin's compatility
	virtual Boolean CheckCompatible(Int32 iMajorVersion,
		Int32 iMinorVersion,
		Int32 iModifyVersion) = 0;

	// Listen plugins
	virtual None Listen(Object pListener,
		HandlerFunc pListenHandler,
		Int32 iEventID) = 0;
};

#endif //IPLUGIN_H

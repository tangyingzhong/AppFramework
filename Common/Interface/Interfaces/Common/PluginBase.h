///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Plugin base has some funstions that plugin who inherits it can own ,too
///</describe>
/// <date>2019/9/22</date>
///***********************************************************************
#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include "Common/IPlugin.h"

#define BASE_EVENT_ID WM_USER+1

struct PluginInfo
{
	typedef IPlugin* (*FuncCreator)();

	typedef None(*FuncDestory)(IPlugin*);

	// Plugin name
	String strPluginName;

	// Plugin major version
	Int32 iMajorVersion;

	// Plugin minor version
	Int32 iMinorVersion;

	// Plugin modify version
	Int32 iModifyVersion;

	// Plugin self
	IPlugin* pPlugin;

	// Plugin creator
	FuncCreator pCreateFunc;

	// Plugin destoryer
	FuncDestory pDestoryFunc;
};

template<class T1=IPlugin, class T2 = EventArgs>
class PluginBase :public T1
{
public:
	typedef IEventHandler::HandlerFunc HandlerFunc;

public:
	// Construct the plugin base
	PluginBase() :m_bDisposed(false){		}

protected:
	// Destruct the plugin base
	virtual ~PluginBase()
	{
		if (!GetDisposed())
		{
			SetDisposed(true);
		}
	}

public:
	// Start the plugin
	virtual Boolean Start()
	{
		return true;
	}

	// Stop the plugin
	virtual Boolean Stop()
	{
		return true;
	}

	// Get plugin name
	virtual String GetName()
	{
		return GetAddinName();
	}

	// Set plugin name
	virtual Boolean SetName(String strName)
	{
		if (strName.IsEmpty())
		{
			return false;
		}

		SetAddinName(strName);

		return true;
	}

	// Set plugin version
	virtual Boolean SetVersion(Int32 iMajorVersion,
		Int32 iMinorVersion,
		Int32 iModifyVersion)
	{
		if (iMajorVersion == 0
			&& iMinorVersion == 0
			&& iModifyVersion == 0)
		{
			return false;
		}

		SetMajorVersion(iMajorVersion);

		SetMinorVersion(iMinorVersion);

		SetModifyVersion(iModifyVersion);

		return true;
	}

	// Get plugin version
	virtual Boolean GetVersion(Int32& iMajorVersion,
		Int32& iMinorVersion,
		Int32& iModifyVersion)
	{
		if (GetMajorVersion() == 0
			&& GetMinorVersion() == 0
			&& GetModifyVersion() == 0)
		{
			return false;
		}

		iMajorVersion = GetMajorVersion();

		iMinorVersion = GetMinorVersion();

		iModifyVersion = GetModifyVersion();

		return true;
	}

	// Check plugin's compatility
	virtual Boolean CheckCompatible(Int32 iMajorVersion,
		Int32 iMinorVersion,
		Int32 iModifyVersion)
	{
		if (iMajorVersion < GetMajorVersion())  // 2
		{
			return false;
		}

		if (iMajorVersion == GetMajorVersion())
		{
			if (iMinorVersion < GetMinorVersion()) // 5
			{
				return false;
			}

			if (iMinorVersion == GetMinorVersion())
			{
				if (iModifyVersion < GetModifyVersion())  // 1
				{
					return false;
				}

				return true;
			}

			return true;
		}
		
		return true;
	}

	// Listen plugins
	virtual None Listen(Object pListener,
		HandlerFunc pListenHandler,
		Int32 iEventID)
	{
		m_EventHandler.RegisterEvent(pListener, iEventID, pListenHandler);
	}

protected:
	// Notidy all listeners who listening this event id
	None Notify(Object pNotifier, Int32 iEventID, T2* pArgs)
	{
		m_EventHandler.FireEvent(pNotifier, iEventID, pArgs);
	}

	// Set the service info table
	inline None SetPluginInfo(PluginInfo Info)
	{
		m_PluginInfo = Info;
	}

private:
	// Get the Name
	inline String GetAddinName() const
	{
		return m_PluginInfo.strPluginName;
	}

	// Set the Name
	inline None SetAddinName(String strName)
	{
		m_PluginInfo.strPluginName = strName;
	}

	// Get the MajorVersion
	inline Int32 GetMajorVersion() const
	{
		return m_PluginInfo.iMajorVersion;
	}

	// Set the MajorVersion
	inline None SetMajorVersion(Int32 iMajorVersion)
	{
		m_PluginInfo.iMajorVersion = iMajorVersion;
	}

	// Get the MinorVersion
	inline Int32 GetMinorVersion() const
	{
		return m_PluginInfo.iMinorVersion;
	}

	// Set the MinorVersion
	inline None SetMinorVersion(Int32 iMinorVersion)
	{
		m_PluginInfo.iMinorVersion = iMinorVersion;
	}

	// Get the ModifyVersion
	inline Int32 GetModifyVersion() const
	{
		return m_PluginInfo.iModifyVersion;
	}

	// Set the ModifyVersion
	inline None SetModifyVersion(Int32 iModifyVersion)
	{
		m_PluginInfo.iModifyVersion = iModifyVersion;
	}

	// Get the Disposed
	inline Boolean GetDisposed() const
	{
		return m_bDisposed;
	}

	// Set the Disposed
	inline None SetDisposed(Boolean bDisposed)
	{
		m_bDisposed = bDisposed;
	}

private:
	// Service information table
	PluginInfo m_PluginInfo;

	// Event handler container
	EventHandler m_EventHandler;

	// Disposed state
	Boolean m_bDisposed;
};

#endif // PLUGINBASE_H
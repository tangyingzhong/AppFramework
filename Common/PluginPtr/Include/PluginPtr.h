///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It can be used to operate all the plugins
/// Note: it is like a auto pointer which can not manage the object's release
///</describe>
/// <date>2019/11/6</date>
///***********************************************************************
#ifndef PLUGINPTR_H
#define PLUGINPTR_H

#include "Common/IApplicationContext.h"
#include "AppFramework.h"

template <class T>
class PluginPtr
{
public:
	typedef T ValueType;
	typedef ValueType* Pointer;
	typedef ValueType& Reference;

public:
	// Construct the plugin pointer
	PluginPtr() :m_pPointer(NULL), 
		m_strPluginName(_T("")),
		m_iMajorVersion(0),
		m_iMinorVersion(0),
		m_iModifyVersion(0),
		m_pAppContext(AppFramework::GetInstance()->GetGlobalContext()),
		m_bDisposed(false)
	{
		Initialize();
	}

	// Construct the plugin pointer
	PluginPtr(String strPluginName,
		Int32 iMajorVersion,
		Int32 iMinorVersion,
		Int32 iModifyVersion) :m_pPointer(NULL), 
		m_strPluginName(strPluginName),
		m_iMajorVersion(iMajorVersion),
		m_iMinorVersion(iMinorVersion),
		m_iModifyVersion(iModifyVersion),
		m_pAppContext(AppFramework::GetInstance()->GetGlobalContext()),
		m_bDisposed(false)
	{
		Initialize();
	}

	// Destory the plugin pointer
	~PluginPtr()
	{
		if (!GetDisposed())
		{
			SetDisposed(true);

			Destory();
		}
	}

	// Forbid the plugin pointer's copy
	PluginPtr(const PluginPtr& other)
	{
		SetPointer(const_cast<Pointer>(other->GetPointer()));

		other->SetPointer(NULL);
	}

	// Forbid the pointer's assigment
	PluginPtr& operator=(const PluginPtr& other)
	{
		if (this != &other)
		{
			if (GetPointer())
			{
				// Release the plugin at first
				if (GetAppContext())
				{
					GetAppContext()->ReleasePlugin(GetPointer());
				}
			}

			SetPointer(const_cast<Pointer>(other->GetPointer()));

			other->SetPointer(NULL);
		}
		
		return *this;
	}

public:
	// Set the plugin version
	Boolean SetPluginVersion(String strPluginName,
		Int32 iMajorVersion,
		Int32 iMinorVersion,
		Int32 iModifyVersion)
	{
		if (strPluginName.IsEmpty())
		{
			return false;
		}

		if (iMajorVersion<0)
		{
			return false;
		}

		if (iMinorVersion<0)
		{
			return false;
		}

		if (iModifyVersion<0)
		{
			return false;
		}

		SetPluginName(strPluginName);

		SetMajorVersion(iMajorVersion);

		SetMinorVersion(iMinorVersion);

		SetModifyVersion(iModifyVersion);

		// Get the plugin
		return GetPlugin();
	}

	// Get pointer data
	Pointer Data()
	{
		if (GetPointer() == NULL)
		{
			WARN_MESSAGEBOX(_T("Warning"), _T("Pointer==NULL"));

			return NULL;
		}

		return GetPointer();
	}

	// Is valid
	Boolean IsValid()
	{
		return GetPointer() != NULL;
	}

	// Support ->
	Pointer operator->()
	{
		if (GetPointer()==NULL)
		{
			WARN_MESSAGEBOX(_T("Warning"), _T("Pointer==NULL"));

			return NULL;
		}
	
		return GetPointer();
	}

	// Support *
	Reference operator*()
	{
		if (GetPointer() == NULL)
		{
			WARN_MESSAGEBOX(_T("Warning"), _T("Pointer==NULL"));
		}

		return *m_pPointer;
	}

private:
	// Initialize the App
	None Initialize()
	{
		// Get the plugin
		GetPlugin();
	}

	// Destory the App
	None Destory()
	{
		if (!GetDisposed())
		{
			SetDisposed(true);
		}
	}

	// Get the plugin
	Boolean GetPlugin()
	{
		if (GetAppContext()==NULL)
		{
			SetPointer(NULL);

			return false;
		}

		if (GetPluginName().IsNone())
		{
			SetPointer(NULL);

			return false;
		}

		SetPointer(dynamic_cast<Pointer>(GetAppContext()->GetPlugin(GetPluginName(),
			GetMajorVersion(),
			GetMinorVersion(),
			GetModifyVersion())));

		return true;
	}

private:
	// Get the Pointer
	inline Pointer GetPointer() const
	{
		return m_pPointer;
	}

	// Set the Pointer
	inline None SetPointer(Pointer pPointer)
	{
		m_pPointer = pPointer;
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

	// Get the PluginName
	inline String GetPluginName() const
	{
		return m_strPluginName;
	}

	// Set the PluginName
	inline None SetPluginName(String strPluginName)
	{
		m_strPluginName = strPluginName;
	}

	// Get the MajorVersion
	inline Int32 GetMajorVersion() const
	{
		return m_iMajorVersion;
	}

	// Set the MajorVersion
	inline None SetMajorVersion(Int32 iMajorVersion)
	{
		m_iMajorVersion = iMajorVersion;
	}

	// Get the MinorVersion
	inline Int32 GetMinorVersion() const
	{
		return m_iMinorVersion;
	}

	// Set the MinorVersion
	inline None SetMinorVersion(Int32 iMinorVersion)
	{
		m_iMinorVersion = iMinorVersion;
	}

	// Get the ModifyVersion
	inline Int32 GetModifyVersion() const
	{
		return m_iModifyVersion;
	}

	// Set the ModifyVersion
	inline None SetModifyVersion(Int32 iModifyVersion)
	{
		m_iModifyVersion = iModifyVersion;
	}

private:
	// Object pointer
	Pointer m_pPointer;

	// Plugin name
	String m_strPluginName;

	// Plugin's major version
	Int32 m_iMajorVersion;
	
	// Plugin's minor version
	Int32 m_iMinorVersion;
	
	// Plugin's modify version
	Int32 m_iModifyVersion;

	// Application context
	IApplicationContext* m_pAppContext;
	
	// Disposed status
	Boolean m_bDisposed;
};

#endif // PLUGINPTR_H
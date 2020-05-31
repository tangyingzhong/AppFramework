///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It is used to load the plugin that you want
///</describe>
/// <date>2019/11/6</date>
///***********************************************************************
#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

template<class T>
class PluginLoader
{
public:
	typedef ModuleLoader<T> Loader;
	typedef Loader* ConcretLoader;

public:
	// Construct the plugin Loader
	PluginLoader():
		m_pConcretLoader(NULL),
		m_bDisposed(false)
	{	

	}

	// Destory the plugin Loader
	~PluginLoader()
	{
		if (!GetDisposed())
		{
			SetDisposed(true);

			if (GetConcretLoader())
			{
				delete GetConcretLoader();

				SetConcretLoader(NULL);
			}
		}
	}

private:
	// Forbid the plugin Loader's copy
	PluginLoader(const PluginLoader& other){	}

	// Forbid the Loader's assigment
	PluginLoader& operator=(const PluginLoader& other){ return *this; }

public:
	// Load the plugin
	Boolean Load(String strPluginName)
	{
		if (strPluginName.IsEmpty())
		{
			return false;
		}

		String strModulePath = Directory::AddEnding(Directory::GetExcutableDirectory());

		//String strModulePath = String(_T("E:\\tangyingzhong\\Window\\Framework\\Build\\bin_d\\"));

		if (strPluginName.IsContain(_T(".dll")))
		{
			strModulePath = strModulePath + strPluginName;
		}
		else
		{
			strModulePath = strModulePath + strPluginName+ String(".dll");
		}

		SetConcretLoader(new Loader(strModulePath));

		return true;
	}

	// Get pointer data
	T* Data()
	{
		return GetPlugin();
	}

	// Is valid
	Boolean IsValid()
	{
		return IsLoaded();
	}

	// Support ->
	T* operator->()
	{
		return GetPlugin();
	}

private:
	// Is loaded 
	Boolean IsLoaded()
	{
		if (GetConcretLoader() == NULL)
		{
			return false;
		}

		return true;
	}

	// Get the plugin 
	T* GetPlugin()
	{
		if (GetConcretLoader() == NULL)
		{
			return NULL;
		}

		return GetConcretLoader()->GetModuleInterface();
	}

private:
	// Get the ConcretLoader
	inline ConcretLoader GetConcretLoader() const
	{
		return m_pConcretLoader;
	}

	// Set the ConcretLoader
	inline None SetConcretLoader(ConcretLoader pConcretLoader)
	{
		m_pConcretLoader = pConcretLoader;
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
	// Concret loader
	ConcretLoader m_pConcretLoader;
	
	// Disposed status
	Boolean m_bDisposed;
};

#endif // PLUGINLOADER_H
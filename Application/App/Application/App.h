///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Application's entry point to start the service of working
///</describe>
/// <date>2019/7/15</date>
///***********************************************************************
#ifndef	SYSTEM_APP_H
#define SYSTEM_APP_H

#include "IApplicationContext.h"
#include "AppFramework.h"

class App
{
public:
	typedef Bool BOOL;
	typedef Int Index;
	typedef Int32 ParamenterCount;
	typedef SByteArray* ParamenterList;
	typedef void LoginView;
	typedef LoginView* StartView;
	typedef void* Form;
	typedef std::map<std::string, Form> FormContainer;
	
	// It is for libcurl's one time initialize
	struct CurlInit
	{
		CurlInit()
		{
			LibCurl::InitCurl();
		}

		~CurlInit()
		{
			LibCurl::DestoryCurl();
		}
	};

	// App's quit code
	enum APP_CODE_ENUM
	{
		// Support to restart the application 
		RestartCode = 666
	};

public:
	// Get the application instance
	static App* GetInstance();

private:
	// Construct the Client
	App();

	// Destruct the Client
	~App();

	// Forbid the app's copy
	App(App& other){		}

	// Forbid the app's assignment
	App& operator=(App& other){	}

public:
	// Start the application
	None Start(ParamenterCount argc, ParamenterList argv);

	// Stop the application
	None Stop();

	// Restart the application
	None Restart();

	// Clear the form container
	None ClearFormContainer();

	// Get the specify form
	Form GetWindow(String formName);

	// Close all windows
	None CloseOtherWindows();

	// Add the window
	None AddWindow(String formName, QWidget* view);

	// Remove the window
	BOOL RemoveWindow(String formName);

	// Get application path
	String GetApplicationPath();

private:
	// Initialize the application
	None Initialize();

	// Destory the application
	None Destory();

	// Destory the lib curl
	static None DestoryLibCurl();

	// Create the application
	None CreateApplication(ParamenterCount argc, ParamenterList argv);

	// Destory the application
	None DestoryApplication();

	// Set the application environment
	None SetProjectEnvironment(ParamenterCount argc, ParamenterList argv);

	// Enter application loop
	Int EnterLoop();

	// Dispose the app
	None DisposeApplication();

	// Create a start view
	None CreateStartView();

	// Destory the start view
	None DestoryStartView();

	// Destory the app context
	None DestoryAppContext();

private:
	// Get the Application
	inline Program GetApplication() const
	{
		return m_pApplication;
	}

	// Set the Application
	inline None SetApplication(Program pApplication)
	{
		m_pApplication = pApplication;
	}

	// Get the View
	inline StartView GetStartView() const
	{
		return m_pStartView;
	}

	// Set the View
	inline None SetStartView(StartView pStartView)
	{
		m_pStartView = pStartView;
	}

	// Get the Argc
	inline ParamenterCount GetArgc() const
	{
		return m_iArgc;
	}

	// Set the Argc
	inline None SetArgc(ParamenterCount iArgc)
	{
		m_iArgc = iArgc;
	}

	// Get the Argv
	inline ParamenterList GetArgv() const
	{
		return m_pArgv;
	}

	// Set the Argv
	inline None SetArgv(ParamenterList pArgv)
	{
		m_pArgv = pArgv;
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

	// Get the Disposed
	inline BOOL GetDisposed() const
	{
		return m_Disposed;
	}

	// Set the Disposed
	inline None SetDisposed(BOOL bDisposed)
	{
		m_Disposed = bDisposed;
	}

public:
	// The container of the forms
	FormContainer m_FormContainer;

private:
	// The instance of application
	static App* m_pInstance;

	// Libcurl initialize
	static CurlInit* m_pCurIinit;

	// Application
	Program m_pApplication;

	// Paramenter count
	ParamenterCount m_iArgc;

	// Paramenter array
	ParamenterList m_pArgv;

	// Application's context
	IApplicationContext* m_pAppContext;
	
	// Start view
	StartView m_pStartView;

	// Application close state
	BOOL m_Disposed;
};

#endif //!SYSTEM_APP_H_
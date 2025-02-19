#include "PreCompile.h"
#include "App.h"

App* App::m_pInstance = NULL;

// Get the instance of the application
App* App::GetInstance()
{
	if (m_pInstance ==NULL)
	{
		m_pInstance = new App();
	}
	
	return m_pInstance;
}

// Construct the App
App::App() :
	//m_pApplication(NULL),
	m_iArgc(0),
	m_pArgv(NULL),
	m_pAppContext(AppFramework::GetInstance()->GetGlobalContext()),
	m_pStartView(NULL),
	m_Disposed(false)
{
	Initialize();
}

// Destruct the App
App::~App()
{
	Destory();
}

// Initialize the App
None App::Initialize()
{
	// Init the libcurl
}

// Destory the App
None App::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Destory the libcurl
	}
}

// Destory the app context
None App::DestoryAppContext()
{
	AppFramework::DestoryInstance();
}

// Create a start windows
None App::CreateStartView()
{

}

// Destory the main window
None App::DestoryStartView()
{
	if (GetStartView())
	{
		delete GetStartView();

		SetStartView(NULL);
	}
}

// Create the application
None App::CreateApplication(ParamenterCount argc, ParamenterList argv)
{
	
}

// Dispose the app
None App::DisposeApplication()
{
	
}

// Destory the application
None App::DestoryApplication()
{
	
}

// Enter application loop
Int App::EnterLoop()
{
	return -1;
}

// Clear the form container
None App::ClearFormContainer()
{
	for (FormContainer::iterator FormIter = m_FormContainer.begin(); 
		FormIter != m_FormContainer.end();)
	{
		// Remove the form from  the container
		FormIter = m_FormContainer.erase(FormIter);
	}
}

// Search the form
App::Form App::GetWindow(String formName)
{
	for (FormContainer::iterator FormIter = m_FormContainer.begin();
		FormIter != m_FormContainer.end();
		++FormIter)
	{
		String strFormName = static_cast<std::string>(FormIter->first);

		if (strFormName ==formName)
		{
			return FormIter->second;
		}
	}

	return NULL;
}

// Close all windows
None App::CloseOtherWindows()
{
	for (FormContainer::iterator FormIter = m_FormContainer.begin(); 
		FormIter != m_FormContainer.end(); 
		++FormIter)
	{
		String strFormName = static_cast<std::string>(FormIter->first);

		//if (strFormName != String("MainView") 
		//	&& strFormName != String("InitView")
		//	&& strFormName != String("LoginView"))
		//{
		//	// Close the form
		//	(FormIter->second)->close();

		//	// Delete the form
		//	delete FormIter->second;
		//}
	}
}

// Add the window
None App::AddWindow(String formName, Form pView)
{
	m_FormContainer[formName.ToANSIData()] = pView;
}

// Remove the window
App::BOOL App::RemoveWindow(String formName)
{
	if (m_FormContainer.empty()==true)
	{
		return false;
	}

	for (FormContainer::iterator FormIter = m_FormContainer.begin(); 
		FormIter != m_FormContainer.end();)
	{
		String strFormName = static_cast<std::string>(FormIter->first);

		if (strFormName == formName)
		{
			FormIter = m_FormContainer.erase(FormIter);
		}
		else
		{
			++FormIter;
		}
	}

	return true;
}

// Set the project environment
None App::SetProjectEnvironment(ParamenterCount argc, ParamenterList argv)
{
	SetArgc(argc);

	SetArgv(argv);
}

// Start the App
None App::Start(ParamenterCount argc, ParamenterList argv)
{
	LOG_DEBUG(_T("Startup the application"), _T(""));

	// Set the project environment
	SetProjectEnvironment(argc, argv);

	// Create an application now
	/*if (GetApplication()==NULL)
	{		
		CreateApplication(GetArgc(), GetArgv());
	}*/

	// Start the application's context
	if (GetAppContext())
	{
		GetAppContext()->Start();
	}

	if (GetStartView()==nullptr)
	{
		// Create the startup view
		CreateStartView();
	}

	// Start the Index
	//GetStartView()->Start();

	// Enter login view's loop
	if (EnterLoop() == RestartCode)
	{
		// Start another procss 


		return;
	}
}

// Stop the App
None App::Stop()
{
	LOG_DEBUG(_T("Stop the application"), _T(""));

	//// Stop the view
	//if (GetStartView())
	//{
	//	GetStartView()->Stop();
	//}

	// Stop the application;s context
	if (GetAppContext())
	{
		GetAppContext()->Stop();
	}

	// Destory app context
	DestoryAppContext();

	// Destory the start view
	DestoryStartView();

	// Destory application
	DestoryApplication();
}

// Restart the Application
None App::Restart()
{
	// Dispose the application
	DisposeApplication();

	// Make app exit from the gui event loop
	
}
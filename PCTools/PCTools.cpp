
// PCTools.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PCTools.h"
#include "PCToolsDlg.h"
#include "tinyxml2/tinyxml2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPCToolsApp

BEGIN_MESSAGE_MAP(CPCToolsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPCToolsApp construction

CPCToolsApp::CPCToolsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPCToolsApp object

CPCToolsApp theApp;


// CPCToolsApp initialization

BOOL CPCToolsApp::InitInstance()
{
	CWinApp::InitInstance();



	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	std::string configfile = this->m_pszAppName; configfile.append(".xml");
	if (config.LoadFile(configfile.c_str()) == XMLError::XML_SUCCESS)
	{
		if (XMLElement *epctools = config.FirstChildElement("PCTools")) {
			if (XMLElement * eserverurl = epctools->FirstChildElement("ServerURL"))
			{
				m_ServerURL = eserverurl->GetText() ? eserverurl->GetText() : "";
			}

			if (XMLElement * eaddwo = epctools->FirstChildElement("AddWO"))
			{
				m_AddWO = eaddwo->GetText() ? eaddwo->GetText() : "";
			}
			if (XMLElement * eGetWOCategory = epctools->FirstChildElement("GetWOCategory"))
			{
				m_GetWOCategory = eGetWOCategory->GetText() ? eGetWOCategory->GetText() : "";
			}
		}
	}
	
	CPCToolsDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
	}


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


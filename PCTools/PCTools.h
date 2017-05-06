
// PCTools.h : main header file for the PROJECT_NAME application
//

#pragma once

#include <string>
#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPCToolsApp:
// See PCTools.cpp for the implementation of this class
//

class CPCToolsApp : public CWinApp
{
public:
	CPCToolsApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

public:
	std::string m_ServerURL;
	std::string m_AddWO;
	std::string m_GetWOCategory;
};

extern CPCToolsApp theApp;
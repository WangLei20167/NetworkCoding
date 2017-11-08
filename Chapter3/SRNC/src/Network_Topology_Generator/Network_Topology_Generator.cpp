// Network_Topology_Generator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Network_Topology_Generator.h"
#include "Network_Topology_GeneratorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetwork_Topology_GeneratorApp

BEGIN_MESSAGE_MAP(CNetwork_Topology_GeneratorApp, CWinApp)
	//{{AFX_MSG_MAP(CNetwork_Topology_GeneratorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetwork_Topology_GeneratorApp construction

CNetwork_Topology_GeneratorApp::CNetwork_Topology_GeneratorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNetwork_Topology_GeneratorApp object

CNetwork_Topology_GeneratorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNetwork_Topology_GeneratorApp initialization

BOOL CNetwork_Topology_GeneratorApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CNetwork_Topology_GeneratorDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
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

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

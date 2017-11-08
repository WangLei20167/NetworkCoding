// Network_Topology_Generator.h : main header file for the NETWORK_TOPOLOGY_GENERATOR application
//

#if !defined(AFX_NETWORK_TOPOLOGY_GENERATOR_H__827AE256_7B27_4B9D_ADF0_DE7499D07196__INCLUDED_)
#define AFX_NETWORK_TOPOLOGY_GENERATOR_H__827AE256_7B27_4B9D_ADF0_DE7499D07196__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNetwork_Topology_GeneratorApp:
// See Network_Topology_Generator.cpp for the implementation of this class
//

class CNetwork_Topology_GeneratorApp : public CWinApp
{
public:
	CNetwork_Topology_GeneratorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetwork_Topology_GeneratorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNetwork_Topology_GeneratorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWORK_TOPOLOGY_GENERATOR_H__827AE256_7B27_4B9D_ADF0_DE7499D07196__INCLUDED_)

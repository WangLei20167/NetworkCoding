// SRNC_Constructor.h : main header file for the SRNC_CONSTRUCTOR application
//

#if !defined(AFX_SRNC_CONSTRUCTOR_H__9788526A_2EEB_4F6E_A7B0_961A5F4EEA0D__INCLUDED_)
#define AFX_SRNC_CONSTRUCTOR_H__9788526A_2EEB_4F6E_A7B0_961A5F4EEA0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSRNC_ConstructorApp:
// See SRNC_Constructor.cpp for the implementation of this class
//

class CSRNC_ConstructorApp : public CWinApp
{
public:
	CSRNC_ConstructorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSRNC_ConstructorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSRNC_ConstructorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRNC_CONSTRUCTOR_H__9788526A_2EEB_4F6E_A7B0_961A5F4EEA0D__INCLUDED_)

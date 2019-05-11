// Application.h : main header file for the APPLICATION application
//

#if !defined(AFX_APPLICATION_H__121F028F_1AF2_473B_A714_8068B47A6036__INCLUDED_)
#define AFX_APPLICATION_H__121F028F_1AF2_473B_A714_8068B47A6036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CApplicationApp:
// See Application.cpp for the implementation of this class
//

class CApplicationApp : public CWinApp
{
public:
	CApplicationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApplicationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CApplicationApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLICATION_H__121F028F_1AF2_473B_A714_8068B47A6036__INCLUDED_)

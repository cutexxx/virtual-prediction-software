#include "Statium.h"
#if !defined(AFX_ADSELECTDLG_H__C2C6C341_3C8F_4E72_B3F5_825A000CDC6A__INCLUDED_)
#define AFX_ADSELECTDLG_H__C2C6C341_3C8F_4E72_B3F5_825A000CDC6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdSelectDlg dialog

class CAdSelectDlg : public CDialog 
{
// Construction
public:
	CAdSelectDlg(CWnd* pParent = NULL);   // standard constructor

	CStatium *m_Statium;
	int m_Select;
// Dialog Data
	//{{AFX_DATA(CAdSelectDlg)
	enum { IDD = IDD_DIALOG_AD_SELECT };
	CComboBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdSelectDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADSELECTDLG_H__C2C6C341_3C8F_4E72_B3F5_825A000CDC6A__INCLUDED_)

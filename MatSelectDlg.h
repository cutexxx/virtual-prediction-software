#if !defined(AFX_MATSELECTDLG_H__E3522E43_DC00_4165_AE36_BDC987BE24D6__INCLUDED_)
#define AFX_MATSELECTDLG_H__E3522E43_DC00_4165_AE36_BDC987BE24D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatSelectDlg dialog

class CMatSelectDlg : public CDialog 
{
// Construction
public:
	CMatSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMatSelectDlg)
	enum { IDD = IDD_DIALOG_MAT_SELECT };
	int		m_Select;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatSelectDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATSELECTDLG_H__E3522E43_DC00_4165_AE36_BDC987BE24D6__INCLUDED_)

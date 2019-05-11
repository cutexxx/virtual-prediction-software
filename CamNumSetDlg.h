#if !defined(AFX_CAMNUMSETDLG_H__E189D98C_3144_4AC0_8E6F_CECB3DFC9382__INCLUDED_)
#define AFX_CAMNUMSETDLG_H__E189D98C_3144_4AC0_8E6F_CECB3DFC9382__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CamNumSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCamNumSetDlg dialog
 
class CCamNumSetDlg : public CDialog
{
// Construction
public:
	CCamNumSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCamNumSetDlg)
	enum { IDD = IDD_DIALOG_SET_CAMERA_NUM };
	int		m_Num;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamNumSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCamNumSetDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMNUMSETDLG_H__E189D98C_3144_4AC0_8E6F_CECB3DFC9382__INCLUDED_)

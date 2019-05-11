#if !defined(AFX_CAMSELECTDLG_H__F548EF58_BBDF_47F2_AB59_16732270DF23__INCLUDED_)
#define AFX_CAMSELECTDLG_H__F548EF58_BBDF_47F2_AB59_16732270DF23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CamSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCamSelectDlg dialog
 
class CCamSelectDlg : public CDialog
{
// Construction
public:
	CCamSelectDlg(CWnd* pParent = NULL);   // standard constructor
	int m_Select;

// Dialog Data
	//{{AFX_DATA(CCamSelectDlg)
	enum { IDD = IDD_DIALOG_CAM_SELECT };
	CComboBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCamSelectDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMSELECTDLG_H__F548EF58_BBDF_47F2_AB59_16732270DF23__INCLUDED_)

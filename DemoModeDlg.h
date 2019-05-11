#if !defined(AFX_DEMOMODEDLG_H__0E587948_44E2_4562_9E9E_64618A934FD7__INCLUDED_)
#define AFX_DEMOMODEDLG_H__0E587948_44E2_4562_9E9E_64618A934FD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DemoModeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDemoModeDlg dialog

class CDemoModeDlg : public CDialog
{
// Construction
public:
	CDemoModeDlg(CWnd* pParent = NULL);   // standard constructor
	
	int m_DemoMode;
// Dialog Data
	//{{AFX_DATA(CDemoModeDlg)
	enum { IDD = IDD_DEMO_MODE_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoModeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDemoModeDlg)
	afx_msg void OnAllGround();
	afx_msg void OnCameraPos();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOMODEDLG_H__0E587948_44E2_4562_9E9E_64618A934FD7__INCLUDED_)

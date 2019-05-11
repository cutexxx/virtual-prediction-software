#if !defined(AFX_CAMERATIMEDLG_H__8777C8C0_FFAB_4D8A_8B75_1C4F3EFBCEF4__INCLUDED_)
#define AFX_CAMERATIMEDLG_H__8777C8C0_FFAB_4D8A_8B75_1C4F3EFBCEF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CameraTimeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCameraTimeDlg dialog

class CCameraTimeDlg : public CDialog
{
// Construction
public:
/*	void ModFar(int n);
	void ModMid(int n);
	void ModNear(int n);
	void SetFar(int n);
	void SetMid(int n);
	void SetNear(int n);
*/
	CCameraTimeDlg(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CCameraTimeDlg)
	enum { IDD = IDD_DIALOG_CAMERA_TIME };
	int		m_nNear;
	int		m_nMid;
	int		m_nFar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCameraTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCameraTimeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERATIMEDLG_H__8777C8C0_FFAB_4D8A_8B75_1C4F3EFBCEF4__INCLUDED_)

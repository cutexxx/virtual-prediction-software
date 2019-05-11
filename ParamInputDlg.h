#if !defined(AFX_PARAMINPUTDLG_H__14B45F5C_0790_4C59_A0F3_5FC9CD9F9BE0__INCLUDED_)
#define AFX_PARAMINPUTDLG_H__14B45F5C_0790_4C59_A0F3_5FC9CD9F9BE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamInputDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParamInputDlg dialog

class CParamInputDlg : public CDialog
{
// Construction
public:
	CParamInputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParamInputDlg)
	enum { IDD = IDD_PARAMINPUT_DLG };
	UINT	m_Shoot;
	UINT	m_FreeKick;
	UINT	m_CornerKick;
	UINT	m_Attack;
	UINT	m_Offside;
	UINT	m_Warn;
	UINT	m_Goal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParamInputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParamInputDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMINPUTDLG_H__14B45F5C_0790_4C59_A0F3_5FC9CD9F9BE0__INCLUDED_)

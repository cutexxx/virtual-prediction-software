// CamSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "CamSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCamSelectDlg dialog


CCamSelectDlg::CCamSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCamSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCamSelectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCamSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamSelectDlg)
	DDX_Control(pDX, IDC_COMBO_LIST, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CCamSelectDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamSelectDlg message handlers

void CCamSelectDlg::OnOK() 
{
	m_Select = m_List.GetCurSel();
	CDialog::OnOK();
}

BOOL CCamSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	for (int i=0;i<Global::ROAM_CAMERA;i++)
	{
		CString str;
		str.Format("%d",i+1);
		m_List.AddString(str);
	}

	m_List.SetCurSel(m_Select);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

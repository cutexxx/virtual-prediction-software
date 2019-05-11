// AdSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "AdSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdSelectDlg dialog


CAdSelectDlg::CAdSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdSelectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAdSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdSelectDlg)
	DDX_Control(pDX, IDC_COMBO_LIST, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CAdSelectDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdSelectDlg message handlers

void CAdSelectDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_Select = m_List.GetCurSel();

	CDialog::OnOK();
}

BOOL CAdSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	for (int i=0;i<m_Statium->Ads.size();i++)
	{
		CString str;
		str.Format("%d#",i+1);
		m_List.AddString(str);
	}

	m_List.SetCurSel(m_Select);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

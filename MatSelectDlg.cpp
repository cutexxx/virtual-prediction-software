// MatSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "MatSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatSelectDlg dialog


CMatSelectDlg::CMatSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMatSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatSelectDlg)
	m_Select = -1;
	//}}AFX_DATA_INIT
}


void CMatSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatSelectDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_Select);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CMatSelectDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatSelectDlg message handlers

void CMatSelectDlg::OnOK() 
{
	UpdateData(true);
	
	CDialog::OnOK();
}

BOOL CMatSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

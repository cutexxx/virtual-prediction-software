// CamNumSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "CamNumSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCamNumSetDlg dialog


CCamNumSetDlg::CCamNumSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCamNumSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCamNumSetDlg)
	m_Num = 0;
	//}}AFX_DATA_INIT
}


void CCamNumSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamNumSetDlg)
	DDX_Text(pDX, IDC_EDIT_NUM, m_Num);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamNumSetDlg, CDialog)
	//{{AFX_MSG_MAP(CCamNumSetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamNumSetDlg message handlers

void CCamNumSetDlg::OnOK() 
{
	UpdateData();

	if ((m_Num > MAX_CAMERA)||(m_Num < 13))
	{
		MessageBox("机位数必须在13 ~ 30 之间");
		return;
	}
	
	Global::ROAM_CAMERA = m_Num;
	
	CDialog::OnOK();
}

BOOL CCamNumSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_Num = Global::ROAM_CAMERA;
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

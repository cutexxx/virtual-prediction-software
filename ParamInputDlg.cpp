// ParamInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "ParamInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParamInputDlg dialog


CParamInputDlg::CParamInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParamInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParamInputDlg)
	m_Shoot = 1;
	m_FreeKick = 1;
	m_CornerKick = 1;
	m_Attack = 1;
	m_Offside = 1;
	m_Warn = 1;
	m_Goal = 1;
	//}}AFX_DATA_INIT
}


void CParamInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParamInputDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Shoot);
	DDV_MinMaxUInt(pDX, m_Shoot, 0, 99);
	DDX_Text(pDX, IDC_EDIT2, m_FreeKick);
	DDV_MinMaxUInt(pDX, m_FreeKick, 0, 99);
	DDX_Text(pDX, IDC_EDIT3, m_CornerKick);
	DDV_MinMaxUInt(pDX, m_CornerKick, 0, 99);
	DDX_Text(pDX, IDC_EDIT4, m_Attack);
	DDV_MinMaxUInt(pDX, m_Attack, 0, 99);
	DDX_Text(pDX, IDC_EDIT5, m_Offside);
	DDV_MinMaxUInt(pDX, m_Offside, 0, 99);
	DDX_Text(pDX, IDC_EDIT6, m_Warn);
	DDV_MinMaxUInt(pDX, m_Warn, 0, 99);
	DDX_Text(pDX, IDC_EDIT7, m_Goal);
	DDV_MinMaxUInt(pDX, m_Goal, 0, 99);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParamInputDlg, CDialog)
	//{{AFX_MSG_MAP(CParamInputDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamInputDlg message handlers

void CParamInputDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	CDialog::OnOK();
}

BOOL CParamInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UpdateData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

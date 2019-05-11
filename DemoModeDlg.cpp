// DemoModeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "DemoModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoModeDlg dialog


CDemoModeDlg::CDemoModeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoModeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoModeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDemoModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoModeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDemoModeDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoModeDlg)
	ON_BN_CLICKED(IDC_ALL_GROUND, OnAllGround)
	ON_BN_CLICKED(IDC_CAMERA_POS, OnCameraPos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoModeDlg message handlers

void CDemoModeDlg::OnAllGround() 
{
	// TODO: Add your control notification handler code here
	m_DemoMode = 0;
	CDialog::OnOK();
}

void CDemoModeDlg::OnCameraPos() 
{
	// TODO: Add your control notification handler code here
	m_DemoMode = 1;
	CDialog::OnOK();
}

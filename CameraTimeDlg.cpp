// CameraTimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "CameraTimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCameraTimeDlg dialog


CCameraTimeDlg::CCameraTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCameraTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCameraTimeDlg)
	m_nNear = 20;
	m_nMid = 60;
	m_nFar = 20;
	//}}AFX_DATA_INIT

}


void CCameraTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCameraTimeDlg)
	DDX_Text(pDX, IDC_EDIT_NEAR, m_nNear);
	DDV_MinMaxInt(pDX, m_nNear, 0, 100);
	DDX_Text(pDX, IDC_EDIT_MID, m_nMid);
	DDV_MinMaxInt(pDX, m_nMid, 0, 100);
	DDX_Text(pDX, IDC_EDIT_FAR, m_nFar);
	DDV_MinMaxInt(pDX, m_nFar, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCameraTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CCameraTimeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameraTimeDlg message handlers



BOOL CCameraTimeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
// Function name	: CCameraTimeDlg::SetNear
// Description	    : 设置近镜头的时间比例
// Return type		: void 
// Argument         : int n
void CCameraTimeDlg::SetNear(int n)
{
	m_nNear = n;
	m_Near.Format("%d%%",n);
	if (m_NearSlider.m_hWnd) 
	{
		m_NearSlider.SetPos(n);
		UpdateData(FALSE);
	}
}


// Function name	: CCameraTimeDlg::SetMid
// Description	    : 设置近镜头的时间比例
// Return type		: void 
// Argument         : int n
void CCameraTimeDlg::SetMid(int n)
{
	m_nMid = n;
	m_Mid.Format("%d%%",n);
	if (m_MidSlider.m_hWnd) 
	{
		m_MidSlider.SetPos(n);
		UpdateData(FALSE);
	}
}


// Function name	: CCameraTimeDlg::SetFar
// Description	    : 设置近镜头的时间比例
// Return type		: void 
// Argument         : int n
void CCameraTimeDlg::SetFar(int n)
{
	m_nFar = n;
	m_Far.Format("%d%%",n);
	if (m_MidSlider.m_hWnd) 
	{
		m_FarSlider.SetPos(n);
		UpdateData(FALSE);
	}
}


// Function name	: CCameraTimeDlg::ModNear
// Description	    : 更改近镜头后，相应变化其他两个时间比例，应该在调用SetNear之前调用本函数
// Return type		: void 
// Argument         : int n 将近镜头变化为
void CCameraTimeDlg::ModNear(int n)
{
	int old = m_nNear;
	int offset = n - old;
	int olda;
	olda = m_nMid;
	SetMid(olda-offset);
}

void CCameraTimeDlg::ModMid(int n)
{
	int old = m_nMid;
	int offset = n - old;
	int olda;
	olda = m_nNear;
	SetNear(olda-offset);
}

void CCameraTimeDlg::ModFar(int n)
{
	int old = m_nFar;
	int offset = n - old;
	int olda;
	olda = m_nMid;
	SetMid(olda-offset);
}
*/

void CCameraTimeDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	if ((m_nMid + m_nNear + m_nFar) != 100)
	{
		AfxMessageBox("请保持总和等于100");
		return;
	}

	CDialog::OnOK();
}

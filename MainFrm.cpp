// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Application.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "ParamView.h"
#include "ApplicationView.h"
#include "Afxpriv.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WIDTH 300
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CApplicationView *mainView = 0;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (!m_wndSplitterH.CreateStatic(this, 2, 1))
	{
		TRACE0("Failed to Splitter window\n");
		return FALSE;
	}
	if (!m_wndSplitterV.CreateStatic(&m_wndSplitterH, 1, 2,WS_CHILD | WS_VISIBLE,m_wndSplitterH.IdFromRowCol(0,0)))
	{
		TRACE0("Failed to Splitter window\n");
		return FALSE;
	}
	m_wndSplitterH.SetRowInfo(0,WIDTH,0);
	m_wndSplitterV.SetColumnInfo(1,640,0);
	
	//左边是参数选择窗口
	if (!m_wndSplitterV.CreateView(0, 0,
		RUNTIME_CLASS(CLeftView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}
	
	//右边上边是默认的绘制窗口
	if (!m_wndSplitterV.CreateView(0, 1,
		pContext->m_pNewViewClass, CSize(640, 480), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}
	
	//下方是信息显示
	if (!m_wndSplitterH.CreateView(1, 0,
		RUNTIME_CLASS(CParamView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}	
	
	// activate the input view
	SetActiveView((CView*)m_wndSplitterV.GetPane(0,1));

	mainView = (CApplicationView*)m_wndSplitterV.GetPane(0,1);

	((CApplicationView*)m_wndSplitterV.GetPane(0,1))->m_pParamView = (CParamView*)m_wndSplitterH.GetPane(1,0);
	((CApplicationView*)m_wndSplitterV.GetPane(0,1))->m_pLeftView = (CLeftView*)m_wndSplitterH.GetPane(0,0);
	((CLeftView*)m_wndSplitterV.GetPane(0,0))->m_MainView = (CParamView*)m_wndSplitterV.GetPane(0,1);

	return TRUE;
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message   ==WM_LBUTTONDOWN)
	{
		//不让调整分割条   
		if ((pMsg->hwnd==m_wndSplitterH.m_hWnd)||(pMsg->hwnd==m_wndSplitterV.m_hWnd))
			return   TRUE;   
	}
	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	HWND       hWnd1       =       m_wndSplitterH.GetSafeHwnd();       
	HWND       hWnd2       =       m_wndSplitterV.GetSafeHwnd();       
	if(       hWnd1==NULL       ||       !IsWindow(hWnd1)       ||       hWnd2==NULL       ||       !IsWindow(hWnd2)       )       
		return;       

	m_wndSplitterH.SetRowInfo(0,480,0);
	m_wndSplitterV.SetColumnInfo(0,WIDTH,0);
	m_wndSplitterV.SetColumnInfo(1,640,0);

}



BOOL CMainFrame::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);
	
	// if there is a top level routing frame then let it handle the message
//	if (GetRoutingFrame() != NULL) return FALSE;
	
	// to be thorough we will need to handle UNICODE versions of the message also !!
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	TCHAR szFullText[512];
	CString strTipText;
	UINT nID = pNMHDR->idFrom;
	
	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom is actually the HWND of the tool 
		nID = ::GetDlgCtrlID((HWND)nID);
	}
	
	if (nID != 0) // will be zero on a separator
	{
		AfxLoadString(nID, szFullText);
		strTipText=szFullText;
		
#ifndef _UNICODE
		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
		}
		else
		{
			_mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
		}
#else
		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			_wcstombsz(pTTTA->szText, strTipText,sizeof(pTTTA->szText));
		}
		else
		{
			lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
		}
#endif
		
		*pResult = 0;
		
		// bring the tooltip window above other popup windows
		::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,SWP_NOACTIVATE|
			SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER); return TRUE;
	}
} 
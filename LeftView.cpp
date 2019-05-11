// LeftView.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WIDTH 300
#define HALFWIDTH 150
/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

CLeftView::CLeftView()
{
	m_Bmp.LoadBitmap(IDB_STATIUM);
}

CLeftView::~CLeftView()
{
}


BEGIN_MESSAGE_MAP(CLeftView, CView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CApplicationDoc* pDoc = GetDocument();
	// TODO: add draw code here
	CRect rect;
	this->GetClientRect(&rect);
//	ClientToScreen(&rect);

	CDC dc;
	CDC backSurface;
	backSurface.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	backSurface.SelectObject(bmp);
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&m_Bmp);
	CBrush blackBrush;
	blackBrush.CreateSolidBrush(RGB(0,0,0));
	backSurface.FillRect(rect,&blackBrush);
	backSurface.SetStretchBltMode(HALFTONE);
	backSurface.StretchBlt(0,0,WIDTH,WIDTH,&dc,0,0,480,480,SRCCOPY);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&backSurface,0,0,SRCCOPY);
	dc.DeleteDC();
	backSurface.DeleteDC();


	for (int i=0;i<Global::ROAM_CAMERA;i++)
	{
		CPen pen;
		if (i!=pDoc->m_iCurrentCameraID)
		{
			pen.CreatePen(PS_SOLID,1,RGB(0,255,0));
		}
		else
		{
			pen.CreatePen(PS_SOLID,1,RGB(255,0,0));
		}
		CPen *oldpen = pDC->SelectObject(&pen);
		CPoint p1 = ConvertTo2D(pDoc->m_Camera[i].m_vecEyePos);		
		CPoint p2 = ConvertTo2D(pDoc->m_Camera[i].m_vecLookAt);
		p2 = (p2 - p1);
		p2.x = p2.x*15;
		p2.y = p2.y*15;
		p2 = p1 + p2;
//		pDC->MoveTo(p1);
//		pDC->LineTo(p2);
		p1.x -= 5;
		p1.y -= 5;
		CRect rect(p1,CSize(10,10));
		pDC->Ellipse(rect);

		pDC->SelectObject(oldpen);
		if (i!=pDoc->m_iCurrentCameraID)
		{
			pDC->SetTextColor(RGB(255,255,255));
		}
		else
		{
			pDC->SetTextColor(RGB(255,0,0));
		}
		pDC->SetBkMode(TRANSPARENT);
		CString str;
		str.Format("%d",i+1);
		pDC->TextOut(p1.x-5,p1.y+10,str);
	}

	pDC->SetTextColor(RGB(255,255,255));
	CString str;

	switch (pDoc->m_iCurrentCameraID)
	{
	case 0:
		str.Format("机位编号：%d 大型摄像机 全景",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在球场中央的高点位置";
		pDC->TextOut(0,WIDTH+20,str);
		str = "球场中线的延长线";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离50米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:30米，机位高度夹角:约31度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 1:
		str.Format("机位编号：%d 大型摄像机 全景",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在球场中央的高点位置";
		pDC->TextOut(0,WIDTH+20,str);
		str = "与1号机并排";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离50米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:30米，机位高度夹角:约31度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 2:
		str.Format("机位编号：%d 坐地炮 近景",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在跑道正中的低机位";
		pDC->TextOut(0,WIDTH+20,str);
		str = "与1号机并排";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离45米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:1.5米，机位高度夹角:约0度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 3:
		str.Format("机位编号：%d 小型摄像机 近景",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在跑道场地边替补席和角球区之间";
		pDC->TextOut(0,WIDTH+20,str);
		str = "不能挡住球员休息区域的观察角度";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离35米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:1.2米，机位高度夹角:约0度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 4:
		str.Format("机位编号：%d 斯坦尼康 中景、近景",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在跑道场地边替补席和角球区之间";
		pDC->TextOut(0,WIDTH+20,str);
		str = "不能挡住球员休息区域的观察角度";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离35米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:1.2米，机位高度夹角:约0度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 5:
		str.Format("机位编号：%d 大型摄像机 小全景、中景、近景",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在1号机左侧禁区边缘平行的高点处";
		pDC->TextOut(0,WIDTH+20,str);
		str = "";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离45米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:15米，机位高度夹角:约18.4度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 6:
		str.Format("机位编号：%d 大型摄像机 小全景、中景、近景",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在1号机右侧禁区边缘平行的高点处";
		pDC->TextOut(0,WIDTH+20,str);
		str = "";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离45米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:15米，机位高度夹角:约18.4度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 7:
		str.Format("机位编号：%d 小型摄像机 小全、特写",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在左侧球门后";
		pDC->TextOut(0,WIDTH+20,str);
		str = "";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离51米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:1.2米，机位高度夹角:约0度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 8:
		str.Format("机位编号：%d 小型摄像机 小全、特写",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在右侧球门后";
		pDC->TextOut(0,WIDTH+20,str);
		str = "";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离51米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:1.2米，机位高度夹角:约0度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 9:
		str.Format("机位编号：%d 小型摄像机 小全、特写",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在左侧球门后高架平台上";
		pDC->TextOut(0,WIDTH+20,str);
		str = "";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离60米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:20米，机位高度夹角:约18.4度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 10:
		str.Format("机位编号：%d 摇臂广角 小全",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在右侧球门后";
		pDC->TextOut(0,WIDTH+20,str);
		str = "";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离50米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:3米，机位高度夹角:约3.4度。";
		pDC->TextOut(0,WIDTH+80,str);
	break;
	case 11:
		str.Format("机位编号：%d 大型摄像机 个人全景、特写",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在主看台的对面";
		pDC->TextOut(0,WIDTH+20,str);
		str = "";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离45米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:1.5米，机位高度夹角:约0度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 12:
		str.Format("机位编号：%d 微型摄像机 远景",pDoc->m_iCurrentCameraID+1);
		pDC->TextOut(0,WIDTH,str);
		str = "设置在空中移动";
		pDC->TextOut(0,WIDTH+20,str);
		str = "";
		pDC->TextOut(0,WIDTH+40,str);
		str = "距离球场横向中轴线直线距离62米";
		pDC->TextOut(0,WIDTH+60,str);
		str = "高度:38米，机位高度夹角:约31.5度。";
		pDC->TextOut(0,WIDTH+80,str);
		break;
	case 13:
		//漫游相机
		break;
	}

}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CApplicationDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApplicationDoc)));
	return (CApplicationDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
}

void CLeftView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CApplicationDoc *pDoc = GetDocument();
	if (pDoc->m_bClickToSelectCam)
	{
		int max = 25;
		for (int i=0;i<Global::ROAM_CAMERA;i++)
		{
			CPoint p1 = ConvertTo2D(pDoc->m_Camera[i].m_vecEyePos);
			p1 = p1-point;
			if ((p1.x*p1.x + p1.y*p1.y) < max)
			{
				pDoc->SelectCamera(i);
			}
		}
	}
	else
	{
		CPoint p = point - CPoint(HALFWIDTH,HALFWIDTH);
		
		CVECTOR v;
		v = ConvertTo3D(point,pDoc->m_Camera[pDoc->m_iCurrentCameraID].m_vecEyePos[2]);
		
		pDoc->m_Camera[pDoc->m_iCurrentCameraID].SetPosition(v.m_fVec[0],v.m_fVec[1],v.m_fVec[2]);
		pDoc->m_Camera[pDoc->m_iCurrentCameraID].ComputeViewMatrix();
	}

	Invalidate();
	m_MainView->Invalidate();
	
	CView::OnLButtonUp(nFlags, point);
}

void CLeftView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonDown(nFlags, point);
}


CPoint CLeftView::ConvertTo2D(CVECTOR v)
{
	CPoint p;
	p.x = HALFWIDTH+45*v.m_fVec[0]/27.0;
	p.y = HALFWIDTH-30*v.m_fVec[1]/17.0;

	return p;
}

CVECTOR CLeftView::ConvertTo3D(CPoint p,float z)
{
	p = p - CPoint(HALFWIDTH,HALFWIDTH);
	float x,y;
	x = 27.0*(float)p.x/45.0;
	y = -17.0*(float)p.y/30.0;

	CVECTOR v;
	v.m_fVec[0] = x;
	v.m_fVec[1] = y;
	v.m_fVec[2] = z;

	return v;
}

BOOL CLeftView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return false;
	
	return CView::OnEraseBkgnd(pDC);
}


// ParamView.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "ParamView.h"
#include "ApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParamView
extern CApplicationView *mainView;

IMPLEMENT_DYNCREATE(CParamView, CView)

CParamView::CParamView()
{
}

CParamView::~CParamView()
{
}


BEGIN_MESSAGE_MAP(CParamView, CView)
	//{{AFX_MSG_MAP(CParamView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamView drawing

void CParamView::OnDraw(CDC* pDC)
{
	CApplicationDoc* pDoc = GetDocument();
	// TODO: add draw code here
	CFont font;
	CFont *oldFont;
	font.CreateFont(20,0,0,0,1,0,0,0,0,0,0,0,0,"宋体");

	oldFont = pDC->SelectObject(&font);

	CString str;
	int CurrentCamera = pDoc->m_iCurrentCameraID;
	str.Format("机位 #%d x=%.1f y=%.1f z=%.1f",CurrentCamera+1,pDoc->m_Camera[CurrentCamera].m_vecEyePos.m_fVec[0],pDoc->m_Camera[CurrentCamera].m_vecEyePos.m_fVec[1],pDoc->m_Camera[CurrentCamera].m_vecEyePos.m_fVec[2]);
	pDC->TextOut(30,20,str);

	float x,y,z;
	pDoc->m_StatiumGL.GetAdPos(pDoc->m_AdId,x,y,z);
	str.Format("广告 #%d (%.2f,%.2f,%.2f)",pDoc->m_AdId+1,x,y,z);
	pDC->TextOut(30,60,str);


	pDC->TextOut(30,90,pDoc->m_DemoDesc);

	pDC->SelectObject(oldFont);

	int width = 40;
	int sx=360;
	int sy=0;

	if (pDoc->m_bSeeAdInfo)
	{
		for (int x=0;x<4;x++)
		{
			for (int y=0;y<4;y++)
			{
				CRect rect(sx+width*x,sy+width*y,sx+width+width*x,sy+width+width*y);
				pDC->SelectObject(GetStockObject(NULL_BRUSH));
				pDC->Rectangle(rect);
				str.Format("%0.2f",1000*(float)pDoc->m_AdInfo.scale[y*4+x]/(float)pDoc->m_AdInfo.all);
				pDC->TextOut(sx+width*x+2,sy+width*y+width/2,str);
			}
		}
	}

	oldFont = pDC->SelectObject(&font);

	str.Format("机位#%d 总时间：%.0f",CurrentCamera+1,pDoc->m_CameraTime[CurrentCamera]);
	pDC->TextOut(630,20+0,str);
	str.Format("远镜头时间:%.1f%%",(pDoc->m_CameraScaleTimePercent[CurrentCamera][SCALE_CAMERA_FAR]*100));
	pDC->TextOut(630,20+25,str);
	str.Format("中镜头时间:%.1f%%",(pDoc->m_CameraScaleTimePercent[CurrentCamera][SCALE_CAMERA_MID]*100));
	pDC->TextOut(630,20+50,str);
	str.Format("近镜头时间:%.1f%%",(pDoc->m_CameraScaleTimePercent[CurrentCamera][SCALE_CAMERA_NEAR]*100));
	pDC->TextOut(630,20+75,str);
/*
	str.Format("射门:%d",mainView->m_Param[0]);
	pDC->TextOut(600,20+60+10,str);
	str.Format("任意球:%d",mainView->m_Param[1]);
	pDC->TextOut(600,20+75+10,str);
	str.Format("角球:%d",mainView->m_Param[2]);
	pDC->TextOut(600,20+90+10,str);
	str.Format("越位:%d",mainView->m_Param[4]);
	pDC->TextOut(700,20+60+10,str);
	str.Format("警告:%d",mainView->m_Param[5]);
	pDC->TextOut(700,20+75+10,str);
	str.Format("点球:%d",mainView->m_Param[6]);
	pDC->TextOut(700,20+90+10,str);
	str.Format("攻入前场30米:%d",mainView->m_Param[3]);
	pDC->TextOut(700,20+105+10,str);
*/
	pDC->SelectObject(oldFont);
}

/////////////////////////////////////////////////////////////////////////////
// CParamView diagnostics

#ifdef _DEBUG
void CParamView::AssertValid() const
{
	CView::AssertValid();
}

void CParamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CApplicationDoc* CParamView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApplicationDoc)));
	return (CApplicationDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CParamView message handlers

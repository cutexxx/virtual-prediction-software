// ApplicationView.cpp : implementation of the CApplicationView class
//

#include "stdafx.h"
#include "Application.h"

#include "ApplicationDoc.h"
#include "ApplicationView.h"

#include "DemoModeDlg.h"
#include "ParamInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEMO_KICK 1981
#define INTERVAL 100
#define SLOW_LEVEL 2.0
/////////////////////////////////////////////////////////////////////////////
// CApplicationView


IMPLEMENT_DYNCREATE(CApplicationView, CView)

BEGIN_MESSAGE_MAP(CApplicationView, CView)
	//{{AFX_MSG_MAP(CApplicationView)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_MENUITEM_STOPDEMO, OnMenuitemStopdemo)
	ON_COMMAND(ID_CAMERA_DEMO, OnCameraDemo)
	ON_COMMAND(ID_ALLGROUND_DEMO, OnAllgroundDemo)
	ON_COMMAND(ID_ROAMING, OnRoaming)
	ON_UPDATE_COMMAND_UI(ID_ROAMING, OnUpdateRoaming)
	ON_COMMAND(ID_MENUITEM_CONER, OnConerKick)
	ON_COMMAND(ID_MENUITEM_POS, OnFreeKick)
	ON_COMMAND(ID_MENUITEM_PENALTY, OnPenaltyKick)
	ON_COMMAND(ID_INPUT_PARAM, OnInputParam)
	ON_COMMAND(ID_MOVE_AD, OnMoveAd)
	ON_UPDATE_COMMAND_UI(ID_MOVE_AD, OnUpdateMoveAd)
	ON_COMMAND(ID_NEAR, OnNear)
	ON_COMMAND(ID_MID, OnMid)
	ON_COMMAND(ID_FAR, OnFar)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_START_COMPUTE_DEMO, OnStartComputeDemo)
	ON_COMMAND(ID_MENUITEM_DEMO_ALL, OnMenuitemDemoAll)
	ON_UPDATE_COMMAND_UI(ID_NEAR, OnUpdateNear)
	ON_UPDATE_COMMAND_UI(ID_MID, OnUpdateMid)
	ON_UPDATE_COMMAND_UI(ID_FAR, OnUpdateFar)
	ON_COMMAND(ID_MENUITEM32797, OnSelectCameraFile)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApplicationView construction/destruction

CApplicationView::CApplicationView()
{
	// TODO: add construction code here
	m_lastMousePos = CPoint(0,0);
	m_Demo[FREE_KICK] = 0;
	m_Demo[PENALTY_KICK] = 0;
	m_Demo[CORNER_KICK] = 0;
	for (int i=0;i<7;i++)
	{
		m_Param[i] = 0;
	}
	m_StatusDlg = 0;
	m_bEditAd = false;
}

CApplicationView::~CApplicationView()
{
}

BOOL CApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CApplicationView drawing

void CApplicationView::OnDraw(CDC* pDC)
{
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDoc->m_StatiumGL.Render();
	DrawCameras();
	DrawGates();
	DrawBall();
	DrawPlayers();

	pDoc->m_StatiumGL.SwapBuffer();
/*	if (pDoc->m_bSeeAdInfo)
	{
		pDoc->CaculateAdInfo();
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////
// CApplicationView printing

BOOL CApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CApplicationView diagnostics

#ifdef _DEBUG
void CApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CApplicationDoc* CApplicationView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApplicationDoc)));
	return (CApplicationDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CApplicationView message handlers

void CApplicationView::OnInitialUpdate() 
{

	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class	
	SetCurrentDirectory("./model/");
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_StatiumGL.Init(this->GetSafeHwnd());
	pDoc->m_Statium = new CStatium;
	pDoc->m_Statium->Import("./default.sef");
	pDoc->m_StatiumGL.SetData(pDoc->m_Statium,&pDoc->m_Camera[pDoc->m_iCurrentCameraID]);
	pDoc->m_Statium->ImportAds("./default.ads");

	m_Camera.LoadFromFile("./camera.3dvcc");
	m_Gate.LoadFromFile("./gate.3dvcc");
	m_BallModel.LoadFromFile("./ball.3dvcc");
	m_Player.LoadFromFile("./p.3dvcc");
	ResetPlayers();
/*
	//读入相机
	FILE *fp;
	fp = fopen("./camera.dat","rb");
	if (fp)
	{
		for (int i=0;i<ROAM_CAMERA;i++)
		{
			fread(pDoc->m_Camera[i].m_vecEyePos.m_fVec,3,sizeof(float),fp);
			fread(&pDoc->m_Camera[i].m_fPitch,1,sizeof(float),fp);
			fread(&pDoc->m_Camera[i].m_fYaw,1,sizeof(float),fp);
			fread(&pDoc->m_CameraScale[i][0],1,sizeof(float),fp);
			fread(&pDoc->m_CameraScale[i][1],1,sizeof(float),fp);
			fread(&pDoc->m_CameraScale[i][2],1,sizeof(float),fp);
			fread(&pDoc->m_CameraScaleTimePercent[i][0],1,sizeof(float),fp);
			fread(&pDoc->m_CameraScaleTimePercent[i][1],1,sizeof(float),fp);
			fread(&pDoc->m_CameraScaleTimePercent[i][2],1,sizeof(float),fp);
			pDoc->m_Camera[i].ComputeViewMatrix();
		}
		fclose(fp);
	}
*/
	//设置默认的相机位置
	for (int i=0;i<MAX_CAMERA;i++)
	{
		pDoc->m_Camera[i].m_vecEyePos.m_fVec[0] = 0;
		pDoc->m_Camera[i].m_vecEyePos.m_fVec[1] = 22;
		pDoc->m_Camera[i].m_vecEyePos.m_fVec[2] = 2;

		pDoc->m_CameraScale[i][0] = 1.0;
		pDoc->m_CameraScale[i][1] = 1.0;
		pDoc->m_CameraScale[i][2] = 1.0;
	}
	pDoc->SelectCamera(0);

	//开始演示
	m_DemoCount = 0;
	m_DemoStatus = 0;
/*	pDoc->m_Camera[0].Yaw(2);
	CDemoModeDlg dlg;
	if (dlg.DoModal()==IDOK)
	{
		if (dlg.m_DemoMode==0)
		{
			//全场演示
			SetTimer(8183,INTERVAL,NULL);
		}

		if (dlg.m_DemoMode == 1)
		{
			//机位演示
			SetTimer(1209,INTERVAL,NULL);
		}
	}
*/

	CRect rect;
	this->GetClientRect(&rect);
	this->OnSize(0,rect.Width(),rect.Height());

	m_StatusDlg = new CStatusDlg;
	m_StatusDlg->Create(CStatusDlg::IDD,this);

	m_Param[0] = 1;
	m_Param[1] =1;
	m_Demo[0] = 1;
	m_Param[2] = 1;
	m_Demo[2] = 1;
	m_Param[3] = 1;
	m_Param[4] = 1;
	m_Param[5] = 1;
	m_Param[6] = 1;
	m_Demo[1] = 1;
	
	SetTimer(9999,200,NULL);
}

void CApplicationView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your message handler code here
	pDoc->m_StatiumGL.OnResize(cx,cy);
}

void CApplicationView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_lastMousePos = point;
	CRect rect;
	this->GetClientRect(rect);
	point.y = rect.Height() - point.y;
	Get3D(point,lastX,lastY,lastZ);
	
	CView::OnLButtonDown(nFlags, point);
}

void CApplicationView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (!m_bEditAd)
	{
		CApplicationDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		int viewport[4];
		glGetIntegerv(GL_VIEWPORT,viewport);

		CRect rect;
		GetClientRect(&rect);
		int width = rect.Width();
		int height = rect.Height();

		glSelectBuffer( PICK_BUFFER_SIZE, PickBuffer );
		glRenderMode( GL_SELECT );
		glInitNames();
		glPushName(0);
		glMatrixMode(GL_PROJECTION);  
		glPushMatrix();
		glLoadIdentity( );  
		gluPickMatrix(point.x,viewport[3]-point.y,5,5,viewport);
		gluPerspective(pDoc->m_CameraScale[pDoc->m_iCurrentCameraID][pDoc->m_ScaleCameraType]*45.0f,(GLfloat)width/(GLfloat)height,1.0f,1500.0f);
		glMatrixMode(GL_MODELVIEW); 
		pDoc->m_StatiumGL.RenderSelectScene();
		int Nhits = glRenderMode( GL_RENDER );
		glMatrixMode(GL_PROJECTION);  
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW); 

		if (Nhits > 0)
		{
			pDoc->m_AdId = PickBuffer[3];
			pDoc->m_Statium->m_AdNeedToBeDraw = PickBuffer[3];
//			pDoc->LookAtCurrentCamera();
			Invalidate();
		}
	}


	CView::OnLButtonUp(nFlags, point);
}

void CApplicationView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int CurrentCamera;
	if (pDoc->m_bClickToSelectCam)
	{
		CurrentCamera = Global::ROAM_CAMERA;
	}
	else
	{
		CurrentCamera = pDoc->m_iCurrentCameraID;
	}
	
	if (nFlags&MK_RBUTTON)
	{
		CPoint offset = point - m_lastMousePos;
		float x = offset.x/10.0f;
		float y = offset.y/10.0f;
		pDoc->m_Camera[CurrentCamera].Yaw(-x);
		pDoc->m_Camera[CurrentCamera].Pitch(-y);
		m_lastMousePos = point;
		Invalidate();
//		m_pParamView->Invalidate();
//		m_pLeftView->Invalidate();
	}
	else if (nFlags&MK_LBUTTON)
	{
		if (m_bEditAd)
		{
			if (nFlags&MK_CONTROL)
			{
				CPoint offset = point - m_lastMousePos;
				pDoc->RotateAd(pDoc->m_AdId,offset.x);
				m_lastMousePos = point;
			}
			else if (nFlags&MK_SHIFT)
			{
				CPoint offset = point - m_lastMousePos;
				pDoc->MoveAd(pDoc->m_AdId,0,0,-offset.y/50.0);
				m_lastMousePos = point;
			}
			else
			{
				double x,y,z;
				CRect rect;
				this->GetClientRect(rect);
				point.y = rect.Height() - point.y;
				Get3D(point,x,y,z);
				double dx = x - lastX;
				double dy = y - lastY;
				pDoc->MoveAd(pDoc->m_AdId,dx,dy,0);		
				m_lastMousePos = point;
				lastX = x;
				lastY = y;
				lastZ = z;
			}
			Invalidate();
		}
	}


	CView::OnMouseMove(nFlags, point);
}

BOOL CApplicationView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return false;

	return CView::OnEraseBkgnd(pDC);
}

void CApplicationView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_lastMousePos = point;
	
	CView::OnRButtonDown(nFlags, point);
}

void CApplicationView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int CurrentCamera;

	if (pDoc->m_bClickToSelectCam)
	{
		CurrentCamera = Global::ROAM_CAMERA;
	}
	else
	{
		CurrentCamera = pDoc->m_iCurrentCameraID;
	}
	if (!m_bEditAd)
	{
		return;
	}

	switch (nChar)
	{
		case 'Q':
		case 'q':
			pDoc->MoveAd(pDoc->m_AdId,0,0,0.5);
			break;
		case 'e':
		case 'E':
			pDoc->MoveAd(pDoc->m_AdId,0,0,-0.5);
			break;
		case 'a':
		case 'A':
			pDoc->MoveAd(pDoc->m_AdId,-0.5,0,0);
			break;
		case 'd':
		case 'D':
			pDoc->MoveAd(pDoc->m_AdId,+0.5,0,0);
			break;
		case 'w':
		case 'W':
			pDoc->MoveAd(pDoc->m_AdId,0,0.5,0);
			break;
		case 's':
		case 'S':
			pDoc->MoveAd(pDoc->m_AdId,0,-0.5,0);
			break;
	}

	Invalidate();

	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CApplicationView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//漫游
	if (!m_bEditAd)
	{
		int CurrentCamera;
		if (pDoc->m_bClickToSelectCam)
		{
			CurrentCamera = Global::ROAM_CAMERA;
		}
		else
		{
			CurrentCamera = pDoc->m_iCurrentCameraID;
		}

		// TODO: Add your message handler code here and/or call default
		switch (nChar)
		{
		case VK_PRIOR:
			pDoc->m_Camera[CurrentCamera].m_vecEyePos += CVECTOR(0,0,0.5);
			break;
		case VK_NEXT:
			pDoc->m_Camera[CurrentCamera].m_vecEyePos -= CVECTOR(0,0,0.5);
			break;
		case VK_UP:
			pDoc->m_Camera[CurrentCamera].MoveForward(0.5);
			break;
		case VK_DOWN:
			pDoc->m_Camera[CurrentCamera].MoveForward(-0.5);
			break;
		case VK_LEFT:
			pDoc->m_Camera[CurrentCamera].MoveSlide(-0.5);
			break;
		case VK_RIGHT:
			pDoc->m_Camera[CurrentCamera].MoveSlide(0.5);
			break;
/*		case VK_LEFT:
			m_Ball.pos.x --;
			break;
		case VK_RIGHT:
			m_Ball.pos.x ++;
			break;
		case VK_UP:
			m_Ball.pos.y ++;
			break;
		case VK_DOWN:
			m_Ball.pos.y --;
			break;
*/		}
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CApplicationView::OnTimer(UINT nIDEvent) 
{
	//刷新画面
	if (nIDEvent == 9999)
	{
		Invalidate();
	}

	//定位球演示
	if (nIDEvent == DEMO_KICK)
	{
		static int tick = 0;
		tick ++;
		CApplicationDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		//更新球位置
		m_Ball.Update();
		//更新球员位置
		for (int i=0;i<11;i++)
		{
			px[i] += sx[i];
			if (abs(px[i])>20)
			{
				sx[i] = -sx[i];
			}
			if (abs(py[i])>10)
			{
				sy[i] = -sy[i];
			}
			py[i] += sy[i];
		}

		//点球，固定球员位置
		if (m_KickDemoType == KICK_TYPE::FREE_KICK)
		{
			px[1] = -20;
			py[1] = 0;
		}

		int CurrentCamera;
		if (pDoc->m_bClickToSelectCam)
		{
			CurrentCamera = Global::ROAM_CAMERA;
		}
		else
		{
			CurrentCamera = pDoc->m_iCurrentCameraID;
		}

		//镜头跟踪球
		pDoc->m_Camera[CurrentCamera].LookAt(m_Ball.pos.x,m_Ball.pos.y,m_Ball.pos.z);
		//球超出球场，重置
		if ((abs(m_Ball.pos.x)>30)||(abs(m_Ball.pos.y)>20))
		{
			m_Demo[m_KickDemoType] --;
			if (m_KickDemoType == FREE_KICK)
			{
				if (m_Demo[m_KickDemoType] >0)
				{
					OnFreeKick();
				}
				else
				{
					OnPenaltyKick();
				}
			}
			else if (m_KickDemoType == PENALTY_KICK)
			{
				if (m_Demo[m_KickDemoType] >0)
				{
					OnPenaltyKick();
				}
				else
				{
					OnConerKick();
				}
			}
			else if (m_KickDemoType == CORNER_KICK)
			{
				if (m_Demo[m_KickDemoType] >0)
				{
					OnConerKick();
				}
				else
				{
					EndDemo();
				}
			}
		}
		Invalidate();

		//20帧后切换镜头
		if (tick>20)
		{
			int cam = rand()%Global::ROAM_CAMERA;
			while (cam==11)
			{
				cam = rand()%Global::ROAM_CAMERA;
			}
			pDoc->SelectCamera(cam);
			tick = 0;
		}
	}
	//机位演示
	if (nIDEvent == 1209)
	{
		CApplicationDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		int CurrentCamera;
		if (pDoc->m_bClickToSelectCam)
		{
			CurrentCamera = Global::ROAM_CAMERA;
		}
		else
		{
			CurrentCamera = pDoc->m_iCurrentCameraID;
		}
		//演示
		//自左向右
		if (m_DemoStatus == 0)
		{
			pDoc->m_Camera[CurrentCamera].Yaw(-m_DemoCount/100.0);
		}
		if (m_DemoStatus == 1)
		{
			pDoc->m_Camera[CurrentCamera].Yaw(m_DemoCount/100.0);
		}

		m_DemoCount++;

		if (m_DemoCount>100)
		{
			if (m_DemoStatus==0)
			{
				m_DemoCount = 0;
				m_DemoStatus = 1;
			}
			else if (m_DemoStatus==1)
			{
				m_DemoCount = 0;
				m_DemoStatus = 0;
			}
		}
		Invalidate();
	}

	//全场演示
	if (nIDEvent == 8183)
	{
		CApplicationDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		int CurrentCamera;
		if (pDoc->m_bClickToSelectCam)
		{
			CurrentCamera = Global::ROAM_CAMERA;
		}
		else
		{
			CurrentCamera = pDoc->m_iCurrentCameraID;
		}
		//演示
		//自左向右
		if (m_DemoStatus == 0)
		{
			pDoc->m_Camera[CurrentCamera].Yaw(-m_DemoCount/100.0);
		}
		//自右向左
		else if (m_DemoStatus == 1)
		{
			pDoc->m_Camera[CurrentCamera].Yaw(m_DemoCount/100.0);
		}
		//自下向上
		else if (m_DemoStatus == 2)
		{
			pDoc->m_Camera[CurrentCamera].Pitch(m_DemoCount/100.0);
		}
		//自上向下
		else if (m_DemoStatus == 3)
		{
			pDoc->m_Camera[CurrentCamera].Pitch(-m_DemoCount/100.0);
		}
		else if (m_DemoStatus == 4)
		{
			pDoc->m_Camera[CurrentCamera].Yaw(-m_DemoCount/100.0);
		}
		else if (m_DemoStatus == 5)
		{
			pDoc->m_Camera[CurrentCamera].Yaw(m_DemoCount/100.0);
		}


		m_DemoCount ++;
		if (m_DemoCount>100)
		{
			if (m_DemoStatus==0)
			{
				m_DemoCount = 0;
				m_DemoStatus = 1;
			}
			else if (m_DemoStatus==1)
			{
				m_DemoStatus = 2;
				m_DemoCount = 0;
				//选择俯视相机
				pDoc->SelectCamera(1);
			}
			else if (m_DemoStatus == 2)
			{
				m_DemoStatus = 3;
				m_DemoCount = 0;
			}
			else if (m_DemoStatus == 3)
			{
				//选择俯视相机
				pDoc->SelectCamera(0);
				m_DemoStatus = 4;
				m_DemoCount = 0;
			}
			else if (m_DemoStatus == 4)
			{
				m_DemoStatus = 5;
				m_DemoCount = 0;
			}
			else if (m_DemoStatus == 5)
			{
				KillTimer(nIDEvent);
			}
		}
		Invalidate();
	}
	
	CView::OnTimer(nIDEvent);
}


void CApplicationView::OnMenuitemStopdemo() 
{
	// TODO: Add your command handler code here
	KillTimer(8183);
	KillTimer(1209);
	KillTimer(DEMO_KICK);
	EndDemo();
}

void CApplicationView::DrawCameras()
{
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (int i=0;i<10;i++)
	{
		glPushMatrix();
		glColor3f(0.0,0.0,0.0);
		float v[3];
		memcpy(v,pDoc->m_Camera[i].m_vecEyePos.m_fVec,sizeof(float)*3);
		glTranslatef(v[0],v[1],0);
		m_Camera.draw();

		glPopMatrix();
	}
}

void CApplicationView::OnCameraDemo() 
{
	//机位演示
	m_DemoStatus = 0;
	m_DemoCount = 0;
	KillTimer(8183);
	SetTimer(1209,INTERVAL,NULL);
}

void CApplicationView::OnAllgroundDemo() 
{
	//全场演示
	//选择俯视相机
	m_DemoStatus = 0;
	m_DemoCount = 0;
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SelectCamera(9);
	KillTimer(1209);
	SetTimer(8183,INTERVAL,NULL);
}

void CApplicationView::DrawGates()
{
	glColor3f(0.85,0.85,0.85);
	glPushMatrix();
	glTranslatef(27,0,0);
	m_Gate.draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-27,0,0);
	m_Gate.draw();
	glPopMatrix();
}

void CApplicationView::OnRoaming() 
{
	// TODO: Add your command handler code here
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_bClickToSelectCam = !pDoc->m_bClickToSelectCam;
	pDoc->SelectCamera(pDoc->m_iCurrentCameraID);
}

void CApplicationView::OnUpdateRoaming(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pCmdUI->SetCheck(pDoc->m_bClickToSelectCam);
}


bool CApplicationView::IsRoaming()
{
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	return pDoc->m_bClickToSelectCam;
}

void CApplicationView::OnConerKick() 
{
	// TODO: Add your command handler code here
	m_KickDemoType = KICK_TYPE::CORNER_KICK;
	float r = -1.0f + (float)(rand()%200)/100.0f;
	m_Ball.pos.x = 25;
	m_Ball.pos.y = 20;
	m_Ball.speed = CVector3(-1.0,(0.0 - m_Ball.pos.y)+2*r,4+4*r)/SLOW_LEVEL;
	m_Ball.Start();
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_StatiumGL.m_bTracking = true;
	RandSpeed();
	pDoc->SelectCamera(4);
	int CurrentCamera;
	if (pDoc->m_bClickToSelectCam)
	{
		CurrentCamera = Global::ROAM_CAMERA;
	}
	else
	{
		CurrentCamera = pDoc->m_iCurrentCameraID;
	}
	SetTimer(DEMO_KICK,200,NULL);
	pDoc->m_DemoDesc.Format("正在演示角球，还有%d个",m_Demo[KICK_TYPE::CORNER_KICK]);
	m_pParamView->Invalidate();
}

void CApplicationView::OnFreeKick() 
{
	// TODO: Add your command handler code here
	float r = -1.0f + (float)(rand()%200)/100.0f;
	m_Ball.pos.x = rand()%20;
	m_Ball.pos.y = rand()%20;
	m_Ball.speed = CVector3(3.0,(0.0 - m_Ball.pos.y)/3+2*r,4+4*r)/SLOW_LEVEL;
	m_KickDemoType = KICK_TYPE::FREE_KICK;
	m_Ball.Start();
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SelectCamera(0);
	pDoc->m_StatiumGL.m_bTracking = true;
	RandSpeed();
	SetTimer(DEMO_KICK,200,NULL);
	pDoc->m_DemoDesc.Format("正在演示任意球，还有%d个",m_Demo[KICK_TYPE::FREE_KICK]);
	m_pParamView->Invalidate();
}

void CApplicationView::OnPenaltyKick() 
{
	// TODO: Add your command handler code here
	m_KickDemoType = KICK_TYPE::PENALTY_KICK;

	float r = -1.0f + (float)(rand()%200)/100.0f;
	m_Ball.pos.x = 22;
	m_Ball.pos.y = 0;
	m_Ball.speed = CVector3(4.0,(0.0 - m_Ball.pos.y)+2*r,4+4*r)/SLOW_LEVEL;
	m_Ball.Start();
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_StatiumGL.m_bTracking = true;
	RandSpeed();
	pDoc->SelectCamera(4);
	int CurrentCamera;
	if (pDoc->m_bClickToSelectCam)
	{
		CurrentCamera = Global::ROAM_CAMERA;
	}
	else
	{
		CurrentCamera = pDoc->m_iCurrentCameraID;
	}

	//镜头跟踪球
	pDoc->m_Camera[CurrentCamera].LookAt(m_Ball.pos.x,m_Ball.pos.y,m_Ball.pos.z);
	SetTimer(DEMO_KICK,200,NULL);
	pDoc->m_DemoDesc.Format("正在演示点球，还有%d个",m_Demo[KICK_TYPE::PENALTY_KICK]);
	m_pParamView->Invalidate();
}

void CApplicationView::DrawBall()
{
	glColor3f(0.85,0.85,0.85);
	glPushMatrix();
	glTranslatef(m_Ball.pos.x,m_Ball.pos.y,m_Ball.pos.z);
	m_BallModel.draw();
	glPopMatrix();
}

void CBall::Update()
{
	float t = (float)(GetTickCount() - lastTick)/1000.0f;

	speed.z = speed.z - 1.0*9.8*t;
	CVector3 s;
	s.x = speed.x*t;
	s.y = speed.y*t;
	s.z = speed.z*t;
	pos.x = pos.x + s.x;
	pos.y = pos.y + s.y;
	pos.z = pos.z + s.z;
	if (pos.z < 0.0)
	{
		pos.z = 0;
		speed.z = -speed.z;
	}
	lastTick = GetTickCount();
}

void CBall::Start()
{
	lastTick = GetTickCount();
}

void CApplicationView::DrawPlayers()
{
	//绘制22个球员
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_COLOR);
	glColor3f(0.7,0.0,0.0);
	for (int i=0;i<11;i++)
	{
		glPushMatrix();
		glTranslatef(px[i],py[i],pz[i]);
		m_Player.draw();
		glPopMatrix();
	}
	
	glColor3f(0.0,0.0,0.7);
	for (i=0;i<11;i++)
	{
		glPushMatrix();
		glTranslatef(-px[i],py[i],pz[i]);
		m_Player.draw();
		glPopMatrix();
	}

}

void CApplicationView::ResetPlayers()
{
	float x[] = {3,3,3,10,10,10,10,17,17,17,24};
	float y[] = {0,3,-3,8,2,-2,-8,3,0,-3,0};
	float z[] = {0,0,0,0,0,0,0,0,0,0,0};
	
	for (int i=0;i<11;i++)
	{
		px[i] = x[i];
		py[i] = y[i];
		pz[i] = z[i];
	}

}

void CApplicationView::RandSpeed()
{
	float r;
	for (int i=0;i<11;i++)
	{
		r = -1.0 + 2*(float)(rand()%100)/100.0;
		sx[i] = r;
		r = -1.0 + 2*(float)(rand()%100)/100.0;
		sy[i] = r;
		sz[i] = 0;
	}
}

//设置技战术参数
void CApplicationView::OnInputParam() 
{
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CParamInputDlg dlg;
	dlg.m_Shoot = m_Param[0];
	dlg.m_FreeKick = m_Param[1];
	dlg.m_CornerKick = m_Param[2];
	dlg.m_Attack = m_Param[3];
	dlg.m_Offside = m_Param[4];
	dlg.m_Warn = m_Param[5];
	dlg.m_Goal = m_Param[6];
	if (dlg.DoModal() == IDOK)
	{
		m_Param[0] = dlg.m_Shoot;
		m_Param[1] = dlg.m_FreeKick;
		m_Demo[0] = dlg.m_FreeKick;
		m_Param[2] = dlg.m_CornerKick;
		m_Demo[2] = dlg.m_CornerKick;
		m_Param[3] = dlg.m_Attack;
		m_Param[4] = dlg.m_Offside;
		m_Param[5] = dlg.m_Warn;
		m_Param[6] = dlg.m_Goal;
		m_Demo[1] = dlg.m_Goal;

		ComputeCameraTime();

		for (int i=0;i<Global::ROAM_CAMERA;i++)
		{
			pDoc->m_CameraTime[i] = m_CameraTime[i];
		}

		m_pParamView->Invalidate();
	}
}

//停止演示
void CApplicationView::EndDemo()
{
	CApplicationDoc* pDoc = GetDocument();
	m_Ball.pos = CVector3(0,0,0);
	ResetPlayers();
	KillTimer(DEMO_KICK);
	pDoc->m_StatiumGL.m_bTracking = false;
	m_KickDemoType = NONE;
	pDoc->m_DemoDesc = "";
	m_pParamView->Invalidate();
}

//根据参数计算相机时间
void CApplicationView::ComputeCameraTime()
{
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (int i=0;i<Global::ROAM_CAMERA;i++)
	{
		m_CameraTime[i] = 0;
	}

	//射门
	m_CameraTime[5] += exp(5.89-15.49/m_Param[0]);
	m_CameraTime[6] += exp(6.03-13.75/m_Param[0]);

	//任意球
	m_CameraTime[1] += -2702.49+1238.68*m_Param[1]-127.01*m_Param[1]*m_Param[1]+4.03*m_Param[1]*m_Param[1]*m_Param[1];
	m_CameraTime[2] += 137.55-6.12*m_Param[1]+0.80*m_Param[1]*m_Param[1];

	//角球
	m_CameraTime[0] += 4459.56+0.00*m_Param[2]-49.01*m_Param[2]*m_Param[2]+3.81*m_Param[2]*m_Param[2]*m_Param[2];
	m_CameraTime[2] += exp(7.23-9.94/m_Param[2]);
	m_CameraTime[3] += exp(6.87-12.05/m_Param[2]);

	//攻入前场30米
	m_CameraTime[0] += 5634.21*pow(0.99,m_Param[3]);
	m_CameraTime[6] += 483.77-4.56*m_Param[3];
	m_CameraTime[7] += 1220.53+0.95/m_Param[3];
	m_CameraTime[11] += 294.90-3.67*m_Param[3];

	//越位
	m_CameraTime[10] += 620.29-244.13*m_Param[4]+24.64*m_Param[4]*m_Param[4];

	//警告
	m_CameraTime[1] += 1820.23-472.73*m_Param[5]+53.86*m_Param[5]*m_Param[5];
	m_CameraTime[5] += 238.57-49.55*m_Param[5]+6.09*m_Param[5]*m_Param[5];
	m_CameraTime[11] += 118.03*pow(0.74,m_Param[5]);

	//进球
	m_CameraTime[0] += 3183.28+1116.23*m_Param[6]-684.92*m_Param[6]*m_Param[6]+104.34*m_Param[6]*m_Param[6]*m_Param[6];
	m_CameraTime[4] += 146.56*pow(1.20,m_Param[6]);
	m_CameraTime[6] += 177.49-57.46*m_Param[6]+18.63*m_Param[6]*m_Param[6];

	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		if (m_CameraTime[i] <0 )
			m_CameraTime[i] = 0;
	}

	WriteCameraTimeFile();
}


void CApplicationView::StartDemo()
{
	OnFreeKick();
}


// Function name	: CApplicationView::OnMoveAd
// Description	    : 移动广告牌
// Return type		: void 
void CApplicationView::OnMoveAd() 
{
	// TODO: Add your command handler code here
	m_bEditAd = !m_bEditAd;
}

void CApplicationView::OnUpdateMoveAd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bEditAd);
}


// Function name	: CApplicationView::OnNear
// Description	    : 设置近镜头
// Return type		: void 
void CApplicationView::OnNear() 
{
	// TODO: Add your command handler code here
	int CurrentCamera;
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_ScaleCameraType = SCALE_CAMERA_NEAR;
	CurrentCamera = pDoc->m_iCurrentCameraID;
	pDoc->m_StatiumGL.ScaleCamera(pDoc->m_CameraScale[pDoc->m_iCurrentCameraID][pDoc->m_ScaleCameraType]);
	Invalidate();
}


// Function name	: CApplicationView::OnMid
// Description	    : 设置中景镜头
// Return type		: void 
void CApplicationView::OnMid() 
{
	// TODO: Add your command handler code here
	int CurrentCamera;
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_ScaleCameraType = SCALE_CAMERA_MID;
	CurrentCamera = pDoc->m_iCurrentCameraID;
	pDoc->m_StatiumGL.ScaleCamera(pDoc->m_CameraScale[pDoc->m_iCurrentCameraID][pDoc->m_ScaleCameraType]);
	Invalidate();
}


// Function name	: CApplicationView::OnFar
// Description	    : 设置远景镜头
// Return type		: void 
void CApplicationView::OnFar() 
{
	// TODO: Add your command handler code here
	int CurrentCamera;
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_ScaleCameraType = SCALE_CAMERA_FAR;
	CurrentCamera = pDoc->m_iCurrentCameraID;
	pDoc->m_StatiumGL.ScaleCamera(pDoc->m_CameraScale[pDoc->m_iCurrentCameraID][pDoc->m_ScaleCameraType]);
	Invalidate();
}


// Function name	: CApplicationView::OnMouseWheel
// Description	    : 鼠标滚轮
// Return type		: BOOL 
// Argument         : UINT nFlags
// Argument         : short zDelta
// Argument         : CPoint pt
BOOL CApplicationView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_CameraScale[pDoc->m_iCurrentCameraID][pDoc->m_ScaleCameraType] -= zDelta/1000.0;
	if (pDoc->m_CameraScale[pDoc->m_iCurrentCameraID][pDoc->m_ScaleCameraType] > 4.0) 
	{
		pDoc->m_CameraScale[pDoc->m_iCurrentCameraID][pDoc->m_ScaleCameraType] = 4.0;
	}
	if (pDoc->m_CameraScale[pDoc->m_iCurrentCameraID][pDoc->m_ScaleCameraType] < 0.2) 
	{
		pDoc->m_CameraScale[pDoc->m_iCurrentCameraID][pDoc->m_ScaleCameraType] = 0.2;
	}
	pDoc->m_StatiumGL.ScaleCamera(pDoc->m_CameraScale[pDoc->m_iCurrentCameraID][pDoc->m_ScaleCameraType]);
	Invalidate();
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}



// Function name	: CApplicationView::OnStartComputeDemo
// Description	    : 根据设置的技战术参数，开始演示并计算广告曝光
// Return type		: void 
void CApplicationView::OnStartComputeDemo() 
{
	DoCompute();
}

void CApplicationView::OnMenuitemDemoAll() 
{
	// TODO: Add your command handler code here
	StartDemo();
	
}

void CApplicationView::Get3D(CPoint p, double &x, double &y,double &z)
{
	float depth;
	double model[16],proj[16];
	int view[4];
	double winx,winy,winz;
	winx = p.x;
	winy = p.y;

	glBegin(GL_POLYGON);
	glVertex3f(-9999.0,-9999.0,0);
	glVertex3f(-9999.0,9999.0,0);
	glVertex3f(9999.0,9999.0,0);
	glVertex3f(9999.0,-9999.0,0);
	glEnd();	
	glReadPixels(p.x,p.y,1,1,GL_DEPTH_COMPONENT ,GL_FLOAT,&depth);

	winz = depth;
	
	glGetDoublev(GL_MODELVIEW_MATRIX,model);
	glGetDoublev(GL_PROJECTION_MATRIX,proj);
	glGetIntegerv(GL_VIEWPORT ,view);
	gluUnProject(winx,winy,winz,model,proj,view,&x,&y,&z);
}

void CApplicationView::OnUpdateNear(CCmdUI* pCmdUI) 
{
	CApplicationDoc *pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->m_ScaleCameraType == SCALE_CAMERA_NEAR);
}

void CApplicationView::OnUpdateMid(CCmdUI* pCmdUI) 
{
	CApplicationDoc *pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->m_ScaleCameraType == SCALE_CAMERA_MID);
	
}

void CApplicationView::OnUpdateFar(CCmdUI* pCmdUI) 
{
	CApplicationDoc *pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->m_ScaleCameraType == SCALE_CAMERA_FAR);
	
}


//获得镜头表中的最大镜头数
int GetMaxCam(FILE *fp_cam)
{
	int max_cam = 1;
	int res;
	int id;
	float t1;
	res = fscanf(fp_cam,"%d,%f",&id,&t1);
	while (res > 0)
	{
		res = fscanf(fp_cam,"%d,%f",&id,&t1);
		if (res>0)
		{
			max_cam++;
		}
	}
	
	return max_cam;
}


void CApplicationView::OnSelectCameraFile() 
{
	FILE *fp_cam;
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CFileDialog   dlg(TRUE,"csv","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"镜头表文件 (*.csv)|*.csv||",NULL);
	if (dlg.DoModal()==IDOK)
	{
		fp_cam = fopen(dlg.GetPathName(),"rt");
		if (fp_cam)
		{
			int max_cam = GetMaxCam(fp_cam);
			fseek(fp_cam,0,SEEK_SET);
			for (int cam=0;cam<max_cam;cam++)
			{
				int id;
				float t1;
				fscanf(fp_cam,"%d,%f",&id,&t1);
				pDoc->m_CameraTime[cam] = m_CameraTime[cam] = t1;
			}
			
			fclose(fp_cam);

			//默认为0
			for (int i=0;i<7;i++)
			{
				m_Param[i] = 0;
			}

			WriteCameraTimeFile();
			
			//计算
			DoCompute();
		}
	}
}

void CApplicationView::DoCompute()
{
	//计算...
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	m_StatusDlg->m_OK.ShowWindow(SW_HIDE);
	m_StatusDlg->ShowWindow(SW_SHOW);
	m_StatusDlg->CenterWindow();
	m_StatusDlg->SetDlgItemText(IDC_STATUS,"计算中...");
	m_StatusDlg->SetWindowText("计算中...");
	
	pDoc->ComputeAdExpose(m_StatusDlg);
	pDoc->ComputeGridExpose(m_StatusDlg);
	
	m_StatusDlg->SetDlgItemText(IDC_STATUS,"计算完毕");
	m_StatusDlg->SetWindowText("计算完毕");
	m_StatusDlg->m_OK.ShowWindow(SW_SHOW);
	
//	StartDemo();

}

void CApplicationView::WriteCameraTimeFile()
{
	int k;
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CApplicationDoc::SetCurrentDir("\\result");

	//射门
	float CameraTime[MAX_CAMERA];
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[5] += exp(5.89-15.49/m_Param[0]);
	CameraTime[6] += exp(6.03-13.75/m_Param[0]);
	
	//任意球
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[1] += -2702.49+1238.68*m_Param[1]-127.01*m_Param[1]*m_Param[1]+4.03*m_Param[1]*m_Param[1]*m_Param[1];
	CameraTime[2] += 137.55-6.12*m_Param[1]+0.80*m_Param[1]*m_Param[1];
	
	//角球
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[0] += 4459.56+0.00*m_Param[2]-49.01*m_Param[2]*m_Param[2]+3.81*m_Param[2]*m_Param[2]*m_Param[2];
	CameraTime[2] += exp(7.23-9.94/m_Param[2]);
	CameraTime[3] += exp(6.87-12.05/m_Param[2]);
	
	//攻入前场30米
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[0] += 5634.21*pow(0.99,m_Param[3]);
	CameraTime[6] += 483.77-4.56*m_Param[3];
	CameraTime[7] += 1220.53+0.95/m_Param[3];
	CameraTime[11] += 294.90-3.67*m_Param[3];
	
	//越位
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[10] += 620.29-244.13*m_Param[4]+24.64*m_Param[4]*m_Param[4];
	
	//警告
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[1] += 1820.23-472.73*m_Param[5]+53.86*m_Param[5]*m_Param[5];
	CameraTime[5] += 238.57-49.55*m_Param[5]+6.09*m_Param[5]*m_Param[5];
	CameraTime[11] += 118.03*pow(0.74,m_Param[5]);
	
	//进球
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[0] += 3183.28+1116.23*m_Param[6]-684.92*m_Param[6]*m_Param[6]+104.34*m_Param[6]*m_Param[6]*m_Param[6];
	CameraTime[4] += 146.56*pow(1.20,m_Param[6]);
	CameraTime[6] += 177.49-57.46*m_Param[6]+18.63*m_Param[6]*m_Param[6];
	

	//技术参数与机位转播时长
	FILE *fp;
	fp = fopen("技术参数与机位转播时长.csv","wt");
	fprintf(fp,"技术参数名称,数值（个）");
	for (int i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,",%d",i+1);
	}
	fprintf(fp,"\n射门,%d",m_Param[0]);
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[5] += exp(5.89-15.49/m_Param[0]);
	CameraTime[6] += exp(6.03-13.75/m_Param[0]);
	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,",%.1f",CameraTime[i]);
	}

	fprintf(fp,"\n任意球,%d",m_Param[1]);
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[1] += -2702.49+1238.68*m_Param[1]-127.01*m_Param[1]*m_Param[1]+4.03*m_Param[1]*m_Param[1]*m_Param[1];
	CameraTime[2] += 137.55-6.12*m_Param[1]+0.80*m_Param[1]*m_Param[1];
	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,",%.1f",CameraTime[i]);
	}
	fprintf(fp,"\n角球,%d",m_Param[2]);
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[0] += 4459.56+0.00*m_Param[2]-49.01*m_Param[2]*m_Param[2]+3.81*m_Param[2]*m_Param[2]*m_Param[2];
	CameraTime[2] += exp(7.23-9.94/m_Param[2]);
	CameraTime[3] += exp(6.87-12.05/m_Param[2]);
	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,",%.1f",CameraTime[i]);
	}
	fprintf(fp,"\n越位,%d",m_Param[4]);
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[10] += 620.29-244.13*m_Param[4]+24.64*m_Param[4]*m_Param[4];
	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,",%.1f",CameraTime[i]);
	}
	fprintf(fp,"\n警告,%d",m_Param[5]);
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[1] += 1820.23-472.73*m_Param[5]+53.86*m_Param[5]*m_Param[5];
	CameraTime[5] += 238.57-49.55*m_Param[5]+6.09*m_Param[5]*m_Param[5];
	CameraTime[11] += 118.03*pow(0.74,m_Param[5]);
	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,",%.1f",CameraTime[i]);
	}
	fprintf(fp,"\n点球,%d",m_Param[6]);
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[0] += 3183.28+1116.23*m_Param[6]-684.92*m_Param[6]*m_Param[6]+104.34*m_Param[6]*m_Param[6]*m_Param[6];
	CameraTime[4] += 146.56*pow(1.20,m_Param[6]);
	CameraTime[6] += 177.49-57.46*m_Param[6]+18.63*m_Param[6]*m_Param[6];
	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,",%.1f",CameraTime[i]);
	}
	fprintf(fp,"\n攻入前场30米,%d",m_Param[3]);
	for (k=0;k<MAX_CAMERA;k++)
	{
		CameraTime[k] = 0;
	}
	CameraTime[0] += 5634.21*pow(0.99,m_Param[3]);
	CameraTime[6] += 483.77-4.56*m_Param[3];
	CameraTime[7] += 1220.53+0.95/m_Param[3];
	CameraTime[11] += 294.90-3.67*m_Param[3];
	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,",%.1f",CameraTime[i]);
	}

	fprintf(fp,"\n机位,");
	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,",%d",i+1);
	}
	fprintf(fp,"\n时间,");
	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,",%.1f",m_CameraTime[i]);
	}
	fprintf(fp,"\n");
	fclose(fp);

	//机位百分比设置
	fp = fopen("转播机位时间百分比设置结果.csv","wt");
	fprintf(fp,"机位,近,中,远\n");
	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,"%d,%.1f%%,%.1f%%,%.1f%%\n",i+1,100.0*pDoc->m_CameraScaleTimePercent[i][SCALE_CAMERA_NEAR]
			,100.0*pDoc->m_CameraScaleTimePercent[i][SCALE_CAMERA_MID]
			,100.0*pDoc->m_CameraScaleTimePercent[i][SCALE_CAMERA_FAR]);
	}
	fclose(fp);

	//机位时间明细表
	fp = fopen("机位时间明细表.csv","wt");
	fprintf(fp,"机位,总时间,近,中,远\n");
	for (i=0;i<Global::ROAM_CAMERA;i++)
	{
		fprintf(fp,"%d,%0.3f,%0.3f,%0.3f,%0.3f\n",i+1,m_CameraTime[i],
			m_CameraTime[i]*pDoc->m_CameraScaleTimePercent[i][SCALE_CAMERA_NEAR],
			m_CameraTime[i]*pDoc->m_CameraScaleTimePercent[i][SCALE_CAMERA_MID],
			m_CameraTime[i]*pDoc->m_CameraScaleTimePercent[i][SCALE_CAMERA_FAR]);
	}
	fclose(fp);

}

void CApplicationView::SaveParameter()
{

}

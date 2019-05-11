// ApplicationDoc.cpp : implementation of the CApplicationDoc class
//

#include "stdafx.h"
#include "Application.h"
#include "MainFrm.h"
#include "ApplicationView.h"
#include "ApplicationDoc.h"
#include "CameraTimeDlg.h"
#include "CamNumSetDlg.h"
#include "AdSelectDlg.h"
#include "CamSelectDlg.h"
#include "MatSelectDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CApplicationDoc

IMPLEMENT_DYNCREATE(CApplicationDoc, CDocument)

BEGIN_MESSAGE_MAP(CApplicationDoc, CDocument)
	//{{AFX_MSG_MAP(CApplicationDoc)
	ON_COMMAND(ID_AD_OPEN, OnAdOpen)
	ON_COMMAND(ID_SELECT_CAM1, OnSelectCam1)
	ON_COMMAND(ID_SELECT_CAM2, OnSelectCam2)
	ON_COMMAND(ID_SELECT_CAM10, OnSelectCam10)
	ON_COMMAND(ID_SELECT_CAM3, OnSelectCam3)
	ON_COMMAND(ID_SELECT_CAM4, OnSelectCam4)
	ON_COMMAND(ID_SELECT_CAM5, OnSelectCam5)
	ON_COMMAND(ID_SELECT_CAM6, OnSelectCam6)
	ON_COMMAND(ID_SELECT_CAM7, OnSelectCam7)
	ON_COMMAND(ID_SELECT_CAM8, OnSelectCam8)
	ON_COMMAND(ID_SELECT_CAM9, OnSelectCam9)
	ON_COMMAND(ID_SAVE_CAMERAS, OnSaveCameras)
	ON_COMMAND(ID_LOAD_CAMERAS, OnLoadCameras)
	ON_COMMAND(ID_PRIOR_AD, OnPriorAd)
	ON_COMMAND(ID_NEXT_AD, OnNextAd)
	ON_COMMAND(ID_CACULATE_AD, OnCaculateAd)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_SEE_GRID, OnSeeGrid)
	ON_UPDATE_COMMAND_UI(ID_SEE_GRID, OnUpdateSeeGrid)
	ON_COMMAND(ID_MENUITEM32797, OnSelectCameraList)
	ON_COMMAND(ID_MENUITEM_SETTIME, OnSetCameraTime)
	ON_COMMAND(ID_CAL_SELECT_AD, OnCalSelectAd)
	ON_COMMAND(ID_SAVE_ADS, OnSaveAds)
	ON_COMMAND(ID_ADD_AD, OnAddAd)
	ON_COMMAND(ID_MENUITEM_SET_NUM, OnMenuitemSetNum)
	ON_COMMAND(ID_MENUITEM_SELECT_AD, OnMenuitemSelectAd)
	ON_COMMAND(ID_MENUITEM_CAM_SEL, OnMenuitemCamSel)
	ON_COMMAND(ID_MENUITEM_MAT_SEL, OnMenuitemMatSel)
	ON_COMMAND(ID_DELETE_AD, OnDeleteAd)
	ON_COMMAND(ID_SHOW_BORDER, OnShowBorder)
	ON_UPDATE_COMMAND_UI(ID_SHOW_BORDER, OnUpdateShowBorder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApplicationDoc construction/destruction
extern CApplicationView *mainView;

CApplicationDoc::CApplicationDoc()
{
	// TODO: add one-time construction code here
	m_Statium = 0;
	m_iCurrentCameraID = 0;
	m_bClickToSelectCam = true;
}

CApplicationDoc::~CApplicationDoc()
{
}

BOOL CApplicationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	if (m_Statium)
		delete m_Statium;
	m_Statium = 0;
	m_iCurrentCameraID = 0;
	for (int i=0;i<MAX_CAMERA;i++)
	{
		m_Camera[i].m_vecEye2ForUp.Set(0,0,1);
		m_Camera[i].m_vecEye2Side.Set(1,0,0);
		m_Camera[i].m_vecEye2Under.Set(0,0,-1);
		m_Camera[i].m_fPitch = m_Camera[i].m_fYaw = 0.0f;
		m_Camera[i].SetPosition(10,10,50);
		m_Camera[i].ComputeViewMatrix();
		m_CameraScale[i][0] = 0.7f;
		m_CameraScale[i][1] = 1.0f;
		m_CameraScale[i][2] = 1.3f;
		m_CameraScaleTimePercent[i][0] = 0.2;
		m_CameraScaleTimePercent[i][1] = 0.6;
		m_CameraScaleTimePercent[i][2] = 0.2;
	}

	m_AdId = 0;
	m_bSeeAdInfo = true;
	m_ScaleCameraType = SCALE_CAMERA_NEAR;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CApplicationDoc serialization

void CApplicationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CApplicationDoc diagnostics

#ifdef _DEBUG
void CApplicationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CApplicationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CApplicationDoc commands

BOOL CApplicationDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized creation code here
	
	return TRUE;
}

void CApplicationDoc::OnAdOpen() 
{
	// TODO: Add your command handler code here
	CFileDialog   dlg(TRUE,"ads","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"广告文件 (*.ads)|*.ads||",NULL);
	if (dlg.DoModal()==IDOK)
	{
		if (m_Statium)
		{
			m_Statium->ImportAds(dlg.GetPathName());
		}
	}
}

void CApplicationDoc::OnSelectCam1() 
{
	// TODO: Add your command handler code here
	SelectCamera(0);
}

void CApplicationDoc::OnSelectCam2() 
{
	SelectCamera(1);
}

void CApplicationDoc::OnSelectCam3() 
{
	// TODO: Add your command handler code here
	SelectCamera(2);
}

void CApplicationDoc::OnSelectCam4() 
{
	// TODO: Add your command handler code here
	SelectCamera(3);
}

void CApplicationDoc::OnSelectCam5() 
{
	// TODO: Add your command handler code here
	SelectCamera(4);
}

void CApplicationDoc::OnSelectCam6() 
{
	// TODO: Add your command handler code here
	SelectCamera(5);
}

void CApplicationDoc::OnSelectCam7() 
{
	// TODO: Add your command handler code here
	SelectCamera(6);
}

void CApplicationDoc::OnSelectCam8() 
{
	// TODO: Add your command handler code here
	SelectCamera(7);
}

void CApplicationDoc::OnSelectCam9() 
{
	// TODO: Add your command handler code here
	SelectCamera(8);
}

void CApplicationDoc::OnSelectCam10() 
{
	// TODO: Add your command handler code here
	SelectCamera(9);
}

void CApplicationDoc::OnSaveCameras() 
{
	// TODO: Add your command handler code here
	CFileDialog   dlg(false,"dat","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"相机位置文件 (*.dat)|*.dat||",NULL);
	if (dlg.DoModal()==IDOK)
	{

		FILE *fp;
		fp = fopen(dlg.GetPathName(),"wb");
		if (fp)
		{
			for (int i=0;i<MAX_CAMERA;i++)
			{
				fwrite(m_Camera[i].m_vecEyePos.m_fVec,3,sizeof(float),fp);
				fwrite(&m_Camera[i].m_fPitch,1,sizeof(float),fp);
				fwrite(&m_Camera[i].m_fYaw,1,sizeof(float),fp);
				fwrite(&m_CameraScale[i][0],1,sizeof(float),fp);
				fwrite(&m_CameraScale[i][1],1,sizeof(float),fp);
				fwrite(&m_CameraScale[i][2],1,sizeof(float),fp);
				fwrite(&m_CameraScaleTimePercent[i][0],1,sizeof(float),fp);
				fwrite(&m_CameraScaleTimePercent[i][1],1,sizeof(float),fp);
				fwrite(&m_CameraScaleTimePercent[i][2],1,sizeof(float),fp);
			}
			fclose(fp);
		}
	}
}

void CApplicationDoc::OnLoadCameras() 
{
	// TODO: Add your command handler code here
	CFileDialog   dlg(TRUE,"dat","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"相机位置文件 (*.dat)|*.dat||",NULL);
	if (dlg.DoModal()==IDOK)
	{
		FILE *fp;
		fp = fopen(dlg.GetPathName(),"rb");
		if (fp)
		{
			for (int i=0;i<Global::ROAM_CAMERA;i++)
			{
				fread(m_Camera[i].m_vecEyePos.m_fVec,3,sizeof(float),fp);
				fread(&m_Camera[i].m_fPitch,1,sizeof(float),fp);
				fread(&m_Camera[i].m_fYaw,1,sizeof(float),fp);

				fread(&m_CameraScale[i][0],1,sizeof(float),fp);
				fread(&m_CameraScale[i][1],1,sizeof(float),fp);
				fread(&m_CameraScale[i][2],1,sizeof(float),fp);
				fread(&m_CameraScaleTimePercent[i][0],1,sizeof(float),fp);
				fread(&m_CameraScaleTimePercent[i][1],1,sizeof(float),fp);
				fread(&m_CameraScaleTimePercent[i][2],1,sizeof(float),fp);
				m_Camera[i].ComputeViewMatrix();
			}
			fclose(fp);

			SelectCamera(0);
		}
	}
}

void CApplicationDoc::OnPriorAd() 
{
	// TODO: Add your command handler code here
	m_AdId--;
	if (m_AdId<0)
	{
		m_AdId = m_Statium->Ads.size()-1;
	}
	m_Statium->m_AdNeedToBeDraw = m_AdId;
	LookAtCurrentCamera();
	mainView->m_pParamView->Invalidate();
}

void CApplicationDoc::OnNextAd() 
{
	// TODO: Add your command handler code here
	m_AdId++;
	if (m_AdId>(m_Statium->Ads.size()-1))
	{
		m_AdId = 0;
	}
	m_Statium->m_AdNeedToBeDraw = m_AdId;
	LookAtCurrentCamera();
	mainView->m_pParamView->Invalidate();
}

void CApplicationDoc::CaculateAdInfo()
{
	m_AdInfo =  m_StatiumGL.CaculateAd(m_AdId);
	m_Statium->m_AdNeedToBeDraw = m_AdId;
}

void CApplicationDoc::OnCaculateAd() 
{
	// TODO: Add your command handler code here
	CaculateAdInfo();
	m_bSeeAdInfo = true;
	m_Statium->m_AdNeedToBeDraw = m_AdId;
	mainView->m_pParamView->Invalidate();
}

void CApplicationDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CFileDialog   dlg(TRUE,"sef","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"场景文件 (*.sef)|*.sef||",NULL);
	if (dlg.DoModal()==IDOK)
	{
		m_Statium = new CStatium;
		m_Statium->Import(dlg.GetPathName());
		SelectCamera(0);
	}
}

void CApplicationDoc::OnSeeGrid() 
{
	// TODO: Add your command handler code here
	m_StatiumGL.m_bDrawGrid = !m_StatiumGL.m_bDrawGrid;
}

void CApplicationDoc::OnUpdateSeeGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_StatiumGL.m_bDrawGrid);
}

void CApplicationDoc::SelectCamera(int id)
{
	CMainFrame   *pMainFrame=(CMainFrame   *)AfxGetMainWnd();   
	m_iCurrentCameraID = id;
	CString str;
	str.Format("Camera: %d#",m_iCurrentCameraID+1);
	this->SetTitle(str);
	//漫游相机
	m_Camera[Global::ROAM_CAMERA].SetPosition(m_Camera[m_iCurrentCameraID].m_vecEyePos.m_fVec[0],m_Camera[m_iCurrentCameraID].m_vecEyePos.m_fVec[1],m_Camera[m_iCurrentCameraID].m_vecEyePos.m_fVec[2]);
	m_Camera[Global::ROAM_CAMERA].m_fYaw = m_Camera[m_iCurrentCameraID].m_fYaw;
	m_Camera[Global::ROAM_CAMERA].m_fPitch = m_Camera[m_iCurrentCameraID].m_fPitch;
	m_Camera[Global::ROAM_CAMERA].ComputeViewMatrix();

	if (m_bClickToSelectCam)
	{
		m_StatiumGL.SetData(m_Statium,&m_Camera[Global::ROAM_CAMERA]);
	}
	else
	{
		m_StatiumGL.SetData(m_Statium,&m_Camera[m_iCurrentCameraID]);
	}

	m_StatiumGL.ScaleCamera(m_CameraScale[m_iCurrentCameraID][m_ScaleCameraType]);

	if (mainView)
	{
		mainView->m_pParamView->Invalidate();
		mainView->m_pLeftView->Invalidate();
	}
}

//点击菜单 选择镜头表
//计算所有广告的曝光参数
void CApplicationDoc::OnSelectCameraList() 
{
/*	FILE *fp_cam;
	FILE *fp;
	float scale[16];

	for (int i=0;i<16;i++)
	{
		scale[i] = 0;
	}
	
	CFileDialog   dlg(TRUE,"csv","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"镜头表文件 (*.csv)|*.csv||",NULL);
	if (dlg.DoModal()==IDOK)
	{
		fp_cam = fopen(dlg.GetPathName(),"rt");
		if (fp_cam)
		{
			int max_cam = GetMaxCam(fp_cam);

			fp = fopen("result.csv","wt");
			fprintf(fp,"广告id,在4x4网格中所占千分比x时间\n");
			//计算每一个广告
			for (int i=0;i<m_Statium->Ads.size();i++)
			{
				fprintf(fp,"%d,",i);
				fseek(fp_cam,0,SEEK_SET);
				for (int cam=0;cam<max_cam;cam++)
				{
					int id,t1,t2;
					fscanf(fp_cam,"%d,%d,%d\n",&id,&t1,&t2);
					m_CameraTime[cam] = t1;

					SelectCamera(cam);
					m_AdInfo =  m_StatiumGL.CaculateAd(i);
					for (int j=0;j<16;j++)
					{
						scale[j] += t1*1000*(float)m_AdInfo.scale[j]/(float)m_AdInfo.all;
					}
				}

				//输出16个网格的千分比*时间
				for (int j=0;j<16;j++)
				{
					if (j<15)
						fprintf(fp,"%f,",scale[j]);
					else
						fprintf(fp,"%f",scale[j]);
				}

				fprintf(fp,"\n");

			}
			fclose(fp_cam);
			fclose(fp);
		}
	}
*/
}

//计算广告曝光程度
void CApplicationDoc::ComputeAdExpose(CStatusDlg *dlg)
{
	unsigned long nID;
	for (int i=0;i<m_Statium->Ads.size();i++)
	{
		float scale[16];
		ComputeOneAd(i,scale);
		CString str;
		str.Format("正在计算广告%d...\n%.2f,%.2f,%.2f,%.2f\n%.2f,%.2f,%.2f,%.2f\n%.2f,%.2f,%.2f,%.2f\n%.2f,%.2f,%.2f,%.2f\n",
			i+1,scale[0],scale[1],scale[2],scale[3],scale[4],scale[5],scale[6],scale[7],
			scale[8],scale[9],scale[10],scale[11],scale[12],scale[13],scale[14],scale[15]);
		dlg->SetDlgItemText(IDC_STATUS,str);
	}
}

void CApplicationDoc::ComputeOneAd(int i,float *scale)
{

	for (int k=0;k<16;k++)
	{
		scale[k] = 0;
	}

	SetCurrentDir("\\result");
	
	FILE *fp;
	FILE *fpt;
	CString filename;
	filename.Format("画面曝光比例.csv");
	if (i==0)
	{
		fp = fopen(filename,"wt");
		fprintf(fp,"画面曝光比例\n");
		fprintf(fp,"广告牌名称,机位,镜头,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16\n");
	}
	else
	{
		fp = fopen(filename,"at");
	}

	filename.Format("画面曝光时间.csv");
	if (i==0)
	{
		fpt = fopen(filename,"wt");
		fprintf(fpt,"广告牌名称,机位,镜头,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16\n");
	}
	else
	{
		fpt = fopen(filename,"at");
	}

	if ((fp==0)||(fpt==0))
	{
		MessageBox(NULL,"请关闭文件再进行计算...","",MB_OK);
		return;
	}

	for (int cam=0;cam<Global::ROAM_CAMERA;cam++)
	{
		SelectCamera(cam);
		//近镜头
		fprintf(fp,"%d,%d,近镜头,",i+1,cam+1);
		fprintf(fpt,"%d,%d,近镜头,",i+1,cam+1);
		m_StatiumGL.ScaleCamera(m_CameraScale[cam][SCALE_CAMERA_NEAR]);
		m_AdInfo =  m_StatiumGL.CaculateAd(i);
		for (int j=0;j<16;j++)
		{
			if (m_AdInfo.scale[j] > 0.0)
			{
				scale[j] += m_CameraTime[cam]*m_CameraScaleTimePercent[cam][SCALE_CAMERA_NEAR];
				fprintf(fpt,"%f,",m_CameraTime[cam]*m_CameraScaleTimePercent[cam][SCALE_CAMERA_NEAR]);
			}
			else
			{
				fprintf(fpt,"%f,",0);
			}
			fprintf(fp,"%f,",1000*(float)m_AdInfo.scale[j]/(float)m_AdInfo.all);
		}
		//中镜头
		fprintf(fp,"\n%d,%d,中镜头,",i+1,cam+1);
		fprintf(fpt,"\n%d,%d,中镜头,",i+1,cam+1);
		m_StatiumGL.ScaleCamera(m_CameraScale[cam][SCALE_CAMERA_MID]);
		m_AdInfo =  m_StatiumGL.CaculateAd(i);
		for (j=0;j<16;j++)
		{
			if (m_AdInfo.scale[j] > 0.0)
			{
				scale[j] += m_CameraTime[cam]*m_CameraScaleTimePercent[cam][SCALE_CAMERA_MID];
				fprintf(fpt,"%f,",m_CameraTime[cam]*m_CameraScaleTimePercent[cam][SCALE_CAMERA_MID]);
			}
			else
			{
				fprintf(fpt,"%f,",0);
			}
			fprintf(fp,"%f,",1000*(float)m_AdInfo.scale[j]/(float)m_AdInfo.all);
		}
		//远镜头
		fprintf(fp,"\n%d,%d,远镜头,",i+1,cam+1);
		fprintf(fpt,"\n%d,%d,远镜头,",i+1,cam+1);
		m_StatiumGL.ScaleCamera(m_CameraScale[cam][SCALE_CAMERA_FAR]);
		m_AdInfo =  m_StatiumGL.CaculateAd(i);
		for (j=0;j<16;j++)
		{
			if (m_AdInfo.scale[j] > 0.0)
			{
				scale[j] += m_CameraTime[cam]*m_CameraScaleTimePercent[cam][SCALE_CAMERA_FAR];
				fprintf(fpt,"%f,",m_CameraTime[cam]*m_CameraScaleTimePercent[cam][SCALE_CAMERA_FAR]);
			}
			else
			{
				fprintf(fpt,"%f,",0);
			}
			fprintf(fp,"%f,",1000*(float)m_AdInfo.scale[j]/(float)m_AdInfo.all);
		}
		fprintf(fp,"\n");
		fprintf(fpt,"\n");
	}
	fclose(fp);
/*
	fprintf(fpt,"%d,总和,",i+1);
	//输出16个网格的时间
	for (int j=0;j<16;j++)
	{
		fprintf(fpt,"%f,",scale[j]);
	}
	fprintf(fpt,"\n\n");
*/
	fclose(fpt);
}

void CApplicationDoc::ComputeGridExpose(CStatusDlg *dlg)
{
	float scale[16];
	int j;

	for (int k=0;k<16;k++)
	{
		scale[k] = 0;
	}
	SetCurrentDir("\\result");

	FILE *fp;
	fp = fopen("网格曝光时间.csv","wt");

	fprintf(fp,"网格,广告曝光时间\n");

	for (int cam=0;cam<Global::ROAM_CAMERA;cam++)
	{
		SelectCamera(cam);
		bool flag[16];
		for (j=0;j<16;j++)
		{
			flag[j] = false;
		}

		//近镜头
		m_StatiumGL.ScaleCamera(m_CameraScale[cam][SCALE_CAMERA_NEAR]);
		//计算每一个广告
		for (int i=0;i<m_Statium->Ads.size();i++)
		{
			m_AdInfo =  m_StatiumGL.CaculateAd(i);
			for (j=0;j<16;j++)
			{
				if (m_AdInfo.scale[j]>0)
				{
					flag[j] = true;
				}
			}
		}
		for (j=0;j<16;j++)
		{
			if (flag[j])
			{
				scale[j] += m_CameraTime[cam]*m_CameraScaleTimePercent[cam][SCALE_CAMERA_NEAR];
			}
		}

		for (j=0;j<16;j++)
		{
			flag[j] = false;
		}
		//中镜头
		m_StatiumGL.ScaleCamera(m_CameraScale[cam][SCALE_CAMERA_MID]);
		//计算每一个广告
		for (i=0;i<m_Statium->Ads.size();i++)
		{
			m_AdInfo =  m_StatiumGL.CaculateAd(i);
			for (j=0;j<16;j++)
			{
				if (m_AdInfo.scale[j]>0)
				{
					flag[j] = true;
				}
			}
		}
		for (j=0;j<16;j++)
		{
			if (flag[j])
			{
				scale[j] += m_CameraTime[cam]*m_CameraScaleTimePercent[cam][SCALE_CAMERA_MID];
			}
		}

		for (j=0;j<16;j++)
		{
			flag[j] = false;
		}
		//远镜头
		m_StatiumGL.ScaleCamera(m_CameraScale[cam][SCALE_CAMERA_FAR]);
		//计算每一个广告
		for (i=0;i<m_Statium->Ads.size();i++)
		{
			m_AdInfo =  m_StatiumGL.CaculateAd(i);
			for (j=0;j<16;j++)
			{
				if (m_AdInfo.scale[j]>0)
				{
					flag[j] = true;
				}
			}
		}
		for (j=0;j<16;j++)
		{
			if (flag[j])
			{
				scale[j] += m_CameraTime[cam]*m_CameraScaleTimePercent[cam][SCALE_CAMERA_FAR];
			}
		}
		CString str;
		str.Format("正在计算...\n机位%d...\n%.1f,%.1f,%.1f,%.1f\n%.1f,%.1f,%.1f,%.1f\n%.1f,%.1f,%.1f,%.1f\n%.1f,%.1f,%.1f,%.1f\n",
			cam+1,scale[0],scale[1],scale[2],scale[3],scale[4],scale[5],scale[6],scale[7],
			scale[8],scale[9],scale[10],scale[11],scale[12],scale[13],scale[14],scale[15]);
		dlg->SetDlgItemText(IDC_STATUS,str);
	}

	for (j=0;j<16;j++)
	{
		fprintf(fp,"%d,%.2f\n",j+1,scale[j]);
	}

	fclose(fp);
}


// Function name	: CApplicationDoc::MoveAd
// Description	    : 移动广告牌
// Return type		: void 
// Argument         : int i 广告牌id
// Argument         : float x 移动的距离
// Argument         : float y 移动的距离
// Argument         : float z 移动的距离
void CApplicationDoc::MoveAd(int i, float x, float y, float z)
{
	for (int v=0;v<4;v++)
	{
		m_Statium->Ads[i].v[v].x += x;
		m_Statium->Ads[i].v[v].y += y;
		m_Statium->Ads[i].v[v].z += z;
	}

	for (v=0;v<4;v++)
	{
		if ((fabs(m_Statium->Ads[i].v[0].x + 30.2) < 1.0)&&(fabs(m_Statium->Ads[i].v[1].x + 30.2) < 1.0)
			&&(fabs(m_Statium->Ads[i].v[2].x + 30.2) < 1.0)&&(fabs(m_Statium->Ads[i].v[3].x + 30.2) < 1.0))
		{
			m_Statium->Ads[i].v[v].x = -30.2;
		}
		else if ((fabs(m_Statium->Ads[i].v[0].x - 30.2) < 1.0)&&(fabs(m_Statium->Ads[i].v[1].x - 30.2) < 1.0)
			&&(fabs(m_Statium->Ads[i].v[2].x - 30.2) < 1.0)&&(fabs(m_Statium->Ads[i].v[3].x - 30.2) < 1.0))
		{
			m_Statium->Ads[i].v[v].x = 30.2;
		}
		else if ((fabs(m_Statium->Ads[i].v[0].y + 17.94) < 1.0)&&(fabs(m_Statium->Ads[i].v[1].y + 17.94) < 1.0)
			&&(fabs(m_Statium->Ads[i].v[2].y + 17.94) < 1.0)&&(fabs(m_Statium->Ads[i].v[3].y + 17.94) < 1.0))
		{
			m_Statium->Ads[i].v[v].y = -17.94;
		}
		else if ((fabs(m_Statium->Ads[i].v[0].y - 19.94) < 1.0)&&(fabs(m_Statium->Ads[i].v[1].y - 19.94) < 1.0)
			&&(fabs(m_Statium->Ads[i].v[2].y - 19.94) < 1.0)&&(fabs(m_Statium->Ads[i].v[3].y - 19.94) < 1.0))
		{
			m_Statium->Ads[i].v[v].y = 19.94;
		}
	}

}


// Function name	: CApplicationDoc::OnSetCameraTime
// Description	    : 设置近、中、远镜头的时间比例
// Return type		: void 
void CApplicationDoc::OnSetCameraTime() 
{
	// TODO: Add your command handler code here
	CCameraTimeDlg dlg;
	dlg.m_nNear = (100*m_CameraScaleTimePercent[m_iCurrentCameraID][SCALE_CAMERA_NEAR]);
	dlg.m_nMid = (100*m_CameraScaleTimePercent[m_iCurrentCameraID][SCALE_CAMERA_MID]);
	dlg.m_nFar = (100*m_CameraScaleTimePercent[m_iCurrentCameraID][SCALE_CAMERA_FAR]);
	if (dlg.DoModal() == IDOK) 
	{
		m_CameraScaleTimePercent[m_iCurrentCameraID][SCALE_CAMERA_NEAR] = (float)dlg.m_nNear/100.0f;
		m_CameraScaleTimePercent[m_iCurrentCameraID][SCALE_CAMERA_MID] = (float)dlg.m_nMid/100.0f;
		m_CameraScaleTimePercent[m_iCurrentCameraID][SCALE_CAMERA_FAR] = (float)dlg.m_nFar/100.0f;
	}
}


// Function name	: CApplicationDoc::OnCalSelectAd
// Description	    : 计算单独选中的广告牌
// Return type		: void 
void CApplicationDoc::OnCalSelectAd() 
{
	// TODO: Add your command handler code here
	float scale[16];
	ComputeOneAd(m_AdId,scale);
	CString mes;
	mes.Format("结果已输出到 result/*.csv",m_AdId);
	AfxMessageBox(mes);
}

void CApplicationDoc::OnSaveAds() 
{
	// TODO: Add your command handler code here
	CFileDialog   dlg(FALSE,"ads","", OFN_OVERWRITEPROMPT,"广告文件 (*.ads)|*.ads||",NULL);
	if (dlg.DoModal()==IDOK)
	{
		m_Statium->ExportAds(dlg.GetPathName());
	}
}


// Function name	: CApplicationDoc::OnAddAd
// Description	    : 
// Return type		: void 
void CApplicationDoc::OnAddAd() 
{
	// TODO: Add your command handler code here
	Ad tmp;
	for (int i =0 ;i<4;i++) 
	{
		tmp.v[i].x = m_Statium->Ads[m_AdId].v[i].x+1.0;
		tmp.v[i].y = m_Statium->Ads[m_AdId].v[i].y+1.0;
		tmp.v[i].z = m_Statium->Ads[m_AdId].v[i].z;
		tmp.mat = m_Statium->Ads[m_AdId].mat;
		tmp.rot = m_Statium->Ads[m_AdId].rot;
	}
	m_Statium->Ads.push_back(tmp);

	m_AdId = m_Statium->Ads.size()-1;
	m_Statium->m_AdNeedToBeDraw = m_AdId;

	if (mainView)
	{
		mainView->Invalidate();
		mainView->m_pParamView->Invalidate();
		mainView->m_pLeftView->Invalidate();
	}
}

void CApplicationDoc::OnMenuitemSetNum() 
{
	CCamNumSetDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		Global::ROAM_CAMERA = dlg.m_Num;
	}
}

void CApplicationDoc::OnMenuitemSelectAd() 
{
	CAdSelectDlg dlg;
	dlg.m_Statium = m_Statium;
	dlg.m_Select = m_AdId;
	if (dlg.DoModal() == IDOK)
	{
		m_AdId = dlg.m_Select;
		m_Statium->m_AdNeedToBeDraw = m_AdId;
		LookAtCurrentCamera();

	}
}

void CApplicationDoc::LookAtCurrentCamera()
{
	int CurrentCamera;
	if (m_bClickToSelectCam)
	{
		CurrentCamera = Global::ROAM_CAMERA;
	}
	else
	{
		CurrentCamera = m_iCurrentCameraID;
	}
	
	float x,y,z;
	float ex,ey,ez;
	m_StatiumGL.GetAdPos(m_AdId,x,y,z);
	ex = m_Camera[CurrentCamera].m_vecEyePos.m_fVec[0];
	ey = m_Camera[CurrentCamera].m_vecEyePos.m_fVec[1];
	ez = m_Camera[CurrentCamera].m_vecEyePos.m_fVec[2];
	
	float dist = sqrt((ex -x)*(ex-x)+(ey-y)*(ey-y)+(ez-z)*(ez-z));
	
	float pitch = 180.0*asin((z-ez)/dist)/PI;
	float yaw;
	if (x<ex)
	{
			yaw = 180+180.0*atan((y-ey)/(x-ex))/PI;
	}
	else
	{
			yaw = 180.0*atan((y-ey)/(x-ex))/PI;	
	}
	
	m_Camera[CurrentCamera].m_fYaw = yaw;
	m_Camera[CurrentCamera].m_fPitch = pitch;
	if (mainView)
	{
		mainView->Invalidate();
	}
}

void CApplicationDoc::OnMenuitemCamSel() 
{
	CCamSelectDlg	dlg;
	dlg.m_Select = m_iCurrentCameraID;
	if (dlg.DoModal()==IDOK)
	{
		SelectCamera(dlg.m_Select);
	}
}

void CApplicationDoc::OnMenuitemMatSel() 
{
	CMatSelectDlg dlg;
	dlg.m_Select = m_StatiumGL.GetAdMat(m_AdId);
	if (dlg.DoModal()==IDOK)
	{
		m_StatiumGL.SetAdMat(m_AdId,dlg.m_Select);
	}
}

void CApplicationDoc::SetAdPos(int i, float x, float y, float z)
{
	for (int v=0;v<4;v++)
	{
		m_Statium->Ads[i].v[v].x = x;
		m_Statium->Ads[i].v[v].y = y;
		m_Statium->Ads[i].v[v].z = z;
	}
}

void CApplicationDoc::OnDeleteAd() 
{
	if ((m_AdId>=0)&&m_AdId<m_Statium->Ads.size())
	{
		m_Statium->Ads.erase(&m_Statium->Ads[m_AdId]);
		m_AdId = m_AdId-1;
		if (m_AdId<0)
		{
			m_AdId = 0;
		}
	}
	
	m_Statium->m_AdNeedToBeDraw = m_AdId;
	
	if (mainView)
	{
		mainView->Invalidate();
		mainView->m_pParamView->Invalidate();
		mainView->m_pLeftView->Invalidate();
	}
}

void CApplicationDoc::RotateAd(int id, int offset)
{
	if ((id >=0)&&(id<m_Statium->Ads.size()))
	{
		m_Statium->Ads[id].rot += offset/2.0;
	}
}

void CApplicationDoc::SetCurrentDir(CString dir)
{
	char   szPathTemp[512];
	CString path; 
	int len;
	len = GetModuleFileName(NULL,   szPathTemp,   512);
	if   (len  ==   0)
	{   
		return;   
	}
	else
	{   
		//取出文件路径   
		for   (int   i=len;i>=0;i--)
		{   
			if   (szPathTemp[i]   ==   '\\')  
			{   
				szPathTemp[i]   =   '\0';   
				break;   
			}   
		}   
	}   
	path = szPathTemp;
	path += dir;
	SetCurrentDirectory(path);
}

void CApplicationDoc::OnShowBorder() 
{
	if (m_Statium)
	{
		m_Statium->m_bDrawBorder = !m_Statium->m_bDrawBorder;
	}
}

void CApplicationDoc::OnUpdateShowBorder(CCmdUI* pCmdUI) 
{
	if (m_Statium)
	{
		pCmdUI->SetCheck(m_Statium->m_bDrawBorder);
	}	
}

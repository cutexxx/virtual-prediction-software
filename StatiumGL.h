// StatiumGL.h: interface for the CStatiumGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATIUMGL_H__20AF9768_4686_4D38_A827_82DCA6000EBA__INCLUDED_)
#define AFX_STATIUMGL_H__20AF9768_4686_4D38_A827_82DCA6000EBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpenGL.h"
#include "Statium.h"
#include "Camera.h"
#include "t3dmodel.h"

class AdPosition
{
public:
	AdPosition()
	{
		for (int i=0;i<16;i++)
		{
			scale[i]=0;
		}
		all = 640*480;
	}
	int scale[16];			//广告所占的像素数，在16个格子里
	int all;				//画面总大小
};

class CStatiumGL : public COpenGL  
{
protected:
	CStatium *m_Statium;
public:
	void RenderSelectScene();
	void SetAdMat(int id,int mat);
	int GetAdMat(int id);
	void ComputeCamera();
	void GetAdPos(int id,float &x,float &y,float &z);
	bool m_bDrawGrid;
	AdPosition CaculateAd(int i);
	CCamera *m_Camera;
	void SetData(CStatium *statium,CCamera *cam);
	virtual void Render();
	CStatiumGL();
	virtual ~CStatiumGL();
	bool m_bTracking;
};

#endif // !defined(AFX_STATIUMGL_H__20AF9768_4686_4D38_A827_82DCA6000EBA__INCLUDED_)






















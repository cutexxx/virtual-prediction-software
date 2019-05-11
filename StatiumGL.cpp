// StatiumGL.cpp: implementation of the CStatiumGL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "StatiumGL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatiumGL::CStatiumGL()
{
	m_Statium = 0;
	m_bDrawGrid = false;
	m_bTracking = false;
}

CStatiumGL::~CStatiumGL()
{

}

void CStatiumGL::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer


	if (m_Statium)
	{
		glLoadIdentity();									// Reset The View

		if (!m_bTracking)
		{
			m_Camera->ComputeViewMatrix();
		}
		else
		{
			m_Camera->m_vecUp.m_fVec[0] = 0;
			m_Camera->m_vecUp.m_fVec[1] = 0;
			m_Camera->m_vecUp.m_fVec[2] = 1;
		}
		m_Camera->SetViewMatrix();

		glEnable(GL_TEXTURE_2D);
		m_Statium->Draw();
	}

	if (m_bDrawGrid)
	{
		glViewport(0,0,m_iWidth,m_iHeight);
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPushMatrix();
		
		// Calculate The Aspect Ratio Of The Window
		glLoadIdentity();
		glOrtho(0,m_iWidth,m_iHeight,0,-1.0,1.0);

		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPushMatrix();
		glLoadIdentity();									// Reset The Modelview Matrix

		glColor3f(0,0,1);

		for (int i=0;i<4;i++)
		{
			glBegin(GL_LINES);
			glVertex2f(0,i*(m_iHeight/4));
			glVertex2f(m_iWidth,i*(m_iHeight/4));
			glEnd();
		}
		for (i=0;i<4;i++)
		{
			glBegin(GL_LINES);
			glVertex2d(i*m_iWidth/4.0,0);
			glVertex2d(i*m_iWidth/4.0,m_iHeight);
			glEnd();
		}
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPopMatrix();
	}
}

void CStatiumGL::SetData(CStatium *statium,CCamera *cam)
{
	ASSERT(statium);
	ASSERT(cam);

	m_Statium = statium;
	m_Camera = cam;
}

AdPosition CStatiumGL::CaculateAd(int i)
{
	AdPosition result;
	if (!m_Statium) return result;

	if (i>=m_Statium->Ads.size()) return result;
	GLubyte *pixels;
	int num=0;

	pixels = new GLubyte[m_iHeight*m_iWidth*4]; 


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
	
	m_Camera->SetViewMatrix();

	glColor4f(1.0,0.0,0.0,1.0);
	m_Statium->DrawAds(i);
//	SwapBuffer();

	glPixelStorei( GL_PACK_ALIGNMENT, 4 ); 
	glPixelStorei( GL_PACK_ROW_LENGTH, 0 ); 
	glPixelStorei( GL_PACK_SKIP_ROWS, 0 ); 
	glPixelStorei( GL_PACK_SKIP_PIXELS, 0 ); 
	glReadBuffer(GL_BACK);
	glReadPixels(0,0,m_iWidth,m_iHeight,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
	for (int x=0;x<m_iWidth;x++)
	{
		for (int y=0;y<m_iHeight;y++)
		{
			if (pixels[4*(y*m_iWidth + x)]>0)
			{
				result.scale[((m_iHeight-1-y)/(m_iHeight/4))*4 + x/(m_iWidth/4)]++;
			}
		}
	}

	result.all = m_iWidth*m_iHeight;

	delete [] pixels;

	return result;
}

void CStatiumGL::GetAdPos(int id,float &x, float &y,float &z)
{
	if ((id <0)||(id>=m_Statium->Ads.size()))
	{
		x = y = z = 0;
		return;
	}
	x = m_Statium->Ads[id].v[0].x;
	y = m_Statium->Ads[id].v[0].y;
	z = m_Statium->Ads[id].v[0].z;
}

void CStatiumGL::ComputeCamera()
{
	m_Camera->ComputeViewMatrix();
}

int CStatiumGL::GetAdMat(int id)
{
	return m_Statium->Ads[id].mat;
}

void CStatiumGL::SetAdMat(int id, int mat)
{
	m_Statium->Ads[id].mat = mat;
}

void CStatiumGL::RenderSelectScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	
	
	if (m_Statium)
	{
		glLoadIdentity();									// Reset The View
		
		if (!m_bTracking)
		{
			m_Camera->ComputeViewMatrix();
		}
		else
		{
			m_Camera->m_vecUp.m_fVec[0] = 0;
			m_Camera->m_vecUp.m_fVec[1] = 0;
			m_Camera->m_vecUp.m_fVec[2] = 1;
		}
		m_Camera->SetViewMatrix();
		
		glEnable(GL_TEXTURE_2D);
		m_Statium->DrawSelectAds();
	}
}

// OpenGL.h: interface for the COpenGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGL_H__2699A284_D2F5_4106_B9E1_73CE95A74E0D__INCLUDED_)
#define AFX_OPENGL_H__2699A284_D2F5_4106_B9E1_73CE95A74E0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library

class COpenGL  
{
protected:
	bool m_bInited;
	HDC m_hDC;
	HGLRC	m_hRC;
public:
	void ScaleCamera(float scale);
	void SwapBuffer();
	int m_iHeight;
	int m_iWidth;
	virtual void OnResize(int width,int height);
	void _InitGL();
	virtual void Render()=0;
	virtual bool Init(HWND hWnd);
	COpenGL();
	virtual ~COpenGL();
};

#endif // !defined(AFX_OPENGL_H__2699A284_D2F5_4106_B9E1_73CE95A74E0D__INCLUDED_)

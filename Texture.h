// Texture.h: interface for the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURE_H__3D33F0A9_1430_42E7_BD60_175BED46F584__INCLUDED_)
#define AFX_TEXTURE_H__3D33F0A9_1430_42E7_BD60_175BED46F584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#include <stdio.h>

class CTexture  
{
public:
	AUX_RGBImageRec * LoadPNG(const char *Filename);
	AUX_RGBImageRec * LoadBMP(const char *Filename);
	bool Load(const char *filename);
	void Bind();
	CTexture();
	virtual ~CTexture();
private:
	GLuint texture;

};

#endif // !defined(AFX_TEXTURE_H__3D33F0A9_1430_42E7_BD60_175BED46F584__INCLUDED_)

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__03882CD6_8430_4A10_AAD4_7A9F7CD65EEA__INCLUDED_)
#define AFX_STDAFX_H__03882CD6_8430_4A10_AAD4_7A9F7CD65EEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//编辑镜头推进程度，近镜头
#define SCALE_CAMERA_NEAR 0
//中镜头
#define SCALE_CAMERA_MID 1
//远镜头
#define SCALE_CAMERA_FAR 2

#define MAX_CAMERA 30

class Global
{
public:
static int ROAM_CAMERA;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__03882CD6_8430_4A10_AAD4_7A9F7CD65EEA__INCLUDED_)

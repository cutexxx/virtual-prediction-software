// Camera.h: interface for the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __CAMERA_H__
#define __CAMERA_H__


#include <math.h>

#include "math_ops.h"
#include "gl/gl.h"
#include "gl/glu.h"


//--------------------------------------------------------------
//--------------------------------------------------------------
//- CONSTANTS --------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
#define FRUSTUM_RIGHT  0
#define FRUSTUM_LEFT   1
#define FRUSTUM_BOTTOM 2
#define FRUSTUM_TOP    3
#define FRUSTUM_FAR    4
#define FRUSTUM_NEAR   5


class CCamera  
{
public:
	void MoveUp(float u);
	void Yaw(float y);
	void Pitch(float p);
	void MoveSlide(float dist);
	void MoveForward(float dist);

	void LookAt(float x,float y,float z);
	CVECTOR m_vecEyePos;			//position of camera
	CVECTOR m_vecLookAt;			//lookat vector

	//up, forward, right vectors
	CVECTOR m_vecUp;
	CVECTOR m_vecForward;
	CVECTOR m_vecSide;
	CVECTOR m_vecForUp;

	//the camera's yaw and pitch
	float m_fYaw;
	float m_fPitch;

	//µ„Œª÷√ new coordinate
	CVECTOR m_vecNorthPole;
	CVECTOR m_vecEye2ForUp;
	CVECTOR m_vecEye2Side;
	CVECTOR m_vecEye2Under;

	float m_viewFrustum[6][4];

	void ComputeViewMatrix( float fTimeDelta= 1.0f );
	void CalculateViewFrustum( void );

	//--------------------------------------------------------------
	// Name:			CCAMERA::ComputeInfo - public
	// Description:		Compute the information for the camera
	// Arguments:		-fTimeDelta: amount to interpolate from last frame
	// Return Value:	None
	//--------------------------------------------------------------
	inline void SetPosition( float fX, float fY, float fZ )
	{	m_vecEyePos.Set( fX, fY, fZ );	}

	//--------------------------------------------------------------
	// Name:			CCAMERA::SetViewMatrix - public
	// Description:		Set the view matrix using the gluLookAt
	//					utility function, and the calculations from
	//					ComputeViewMatrix
	// Arguments:		None
	// Return Value:	None
	//--------------------------------------------------------------
	inline void SetViewMatrix( void )
	{
		//have OpenGL calculate the viewing matrix
		gluLookAt(m_vecEyePos[0], m_vecEyePos[1], m_vecEyePos[2],
			m_vecLookAt[0], m_vecLookAt[1], m_vecLookAt[2],
			m_vecUp[0], m_vecUp[1], m_vecUp[2]);
	}

	bool VertexFrustumTest( float x, float y, float z, bool bTestLR= true, bool bTestTB= true, bool bTestNF= true );
	bool CubeFrustumTest( float x, float y, float z, float size );
	bool SphereInFrustum( float x, float y, float z, float fRadius );

	CCamera( void );	
	~CCamera( void );
};

#endif // !defined(AFX_CAMERA_H__4F0516B0_49CF_445F_8087_1C71503CB618__INCLUDED_)

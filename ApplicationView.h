// ApplicationView.h : interface of the CApplicationView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPLICATIONVIEW_H__1D78764A_8B98_4D47_86D2_A8957E8ECE11__INCLUDED_)
#define AFX_APPLICATIONVIEW_H__1D78764A_8B98_4D47_86D2_A8957E8ECE11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StatiumGL.h"
#include "ParamView.h"
#include "LeftView.h"
#include "t3dmodel.h"
#include "StatusDlg.h"

class CBall
{
public:
	CVector3 pos;
	CVector3 speed;
	void Update();
	void Start();
private:
	unsigned long lastTick;
};
 
#define PICK_BUFFER_SIZE 16
 

class CApplicationView : public CView
{
protected: // create from serialization only
	CApplicationView();
	DECLARE_DYNCREATE(CApplicationView)

// Attributes
public:
	CApplicationDoc* GetDocument();
	CParamView *m_pParamView;
	CLeftView *m_pLeftView;
	CStatusDlg *m_StatusDlg;
	int m_DemoCount;
	int m_DemoStatus;
	t3DModel m_Camera;
	t3DModel m_Gate;
	t3DModel m_BallModel;
	t3DModel m_Player;
	CBall m_Ball;
	float px[11],py[11],pz[11];				//球员位置
	float sx[11],sy[11],sz[11];				//球员速度
	enum KICK_TYPE
	{
		FREE_KICK =  0,
		PENALTY_KICK = 1,
		CORNER_KICK = 2,
		NONE = 3,
	} m_KickDemoType;

	int m_Param[7];					//参数		
	int m_Demo[3];					//参数，定位球，点球和角球的个数
	float m_CameraTime[MAX_CAMERA];

	unsigned int PickBuffer[PICK_BUFFER_SIZE];
	
	int RenderMode;

// Operations
public:
	void DrawBall();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApplicationView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SaveParameter();
	void WriteCameraTimeFile();
	void DoCompute();
	void Get3D(CPoint p,double &x,double &y,double &z);
	bool m_bEditAd;						//是否 编辑 广告牌 
	void StartDemo();
	void ComputeCameraTime();
	void EndDemo();
	void RandSpeed();
	void ResetPlayers();
	void DrawPlayers();
	bool IsRoaming();
	void DrawCameras();
	void DrawGates();
	CPoint m_lastMousePos;
	double lastX,lastY,lastZ;
	virtual ~CApplicationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected: 
	//{{AFX_MSG(CApplicationView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuitemStopdemo();
	afx_msg void OnCameraDemo();
	afx_msg void OnAllgroundDemo();
	afx_msg void OnRoaming();
	afx_msg void OnUpdateRoaming(CCmdUI* pCmdUI);
	afx_msg void OnConerKick();
	afx_msg void OnFreeKick();
	afx_msg void OnPenaltyKick();
	afx_msg void OnInputParam();
	afx_msg void OnMoveAd();
	afx_msg void OnUpdateMoveAd(CCmdUI* pCmdUI);
	afx_msg void OnNear();
	afx_msg void OnMid();
	afx_msg void OnFar();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnStartComputeDemo();
	afx_msg void OnMenuitemDemoAll();
	afx_msg void OnUpdateNear(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFar(CCmdUI* pCmdUI);
	afx_msg void OnSelectCameraFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ApplicationView.cpp
inline CApplicationDoc* CApplicationView::GetDocument()
   { return (CApplicationDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLICATIONVIEW_H__1D78764A_8B98_4D47_86D2_A8957E8ECE11__INCLUDED_)

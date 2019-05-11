// ApplicationDoc.h : interface of the CApplicationDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPLICATIONDOC_H__69F8A0B4_9157_4D53_A540_E4567F151B2A__INCLUDED_)
#define AFX_APPLICATIONDOC_H__69F8A0B4_9157_4D53_A540_E4567F151B2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Statium.h"
#include "Camera.h"
#include "StatiumGL.h"
#include "StatusDlg.h"



class CApplicationDoc : public CDocument
{ 
protected: // create from serialization only
	CApplicationDoc();
	DECLARE_DYNCREATE(CApplicationDoc)

// Attributes
public:
	CString m_DemoDesc;				//定位球演示的描述文字
	int m_ScaleCameraType;			//远近中镜头编辑
	CStatium *m_Statium;
	CCamera m_Camera[MAX_CAMERA+1];
	CStatiumGL m_StatiumGL;
	float m_CameraTime[MAX_CAMERA];
	float m_CameraScale[MAX_CAMERA][3];
	float m_CameraScaleTimePercent[MAX_CAMERA][3];		//近中远镜头所占时间比例

	int m_iCurrentCameraID;
	AdPosition	m_AdInfo;
	bool m_bSeeAdInfo;
	bool m_bClickToSelectCam;
// Operations
public:
	void LookAtCurrentCamera();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApplicationDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	static void SetCurrentDir(CString dir);
	void RotateAd(int id,int offset);
	void SetAdPos(int i,float x,float y,float z);
	void MoveAd(int i,float x,float y,float z);
	void ComputeGridExpose(CStatusDlg *dlg);
	void ComputeOneAd(int i,float *scale);
	void ComputeAdExpose(CStatusDlg *dlg);
	void SelectCamera(int id);
	void CaculateAdInfo();
	int m_AdId;
	virtual ~CApplicationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CApplicationDoc)
	afx_msg void OnAdOpen();
	afx_msg void OnSelectCam1();
	afx_msg void OnSelectCam2();
	afx_msg void OnSelectCam10();
	afx_msg void OnSelectCam3();
	afx_msg void OnSelectCam4();
	afx_msg void OnSelectCam5();
	afx_msg void OnSelectCam6();
	afx_msg void OnSelectCam7();
	afx_msg void OnSelectCam8();
	afx_msg void OnSelectCam9();
	afx_msg void OnSaveCameras();
	afx_msg void OnLoadCameras();
	afx_msg void OnPriorAd();
	afx_msg void OnNextAd();
	afx_msg void OnCaculateAd();
	afx_msg void OnFileOpen();
	afx_msg void OnSeeGrid();
	afx_msg void OnUpdateSeeGrid(CCmdUI* pCmdUI);
	afx_msg void OnSelectCameraList();
	afx_msg void OnSetCameraTime();
	afx_msg void OnCalSelectAd();
	afx_msg void OnSaveAds();
	afx_msg void OnAddAd();
	afx_msg void OnMenuitemSetNum();
	afx_msg void OnMenuitemSelectAd();
	afx_msg void OnMenuitemCamSel();
	afx_msg void OnMenuitemMatSel();
	afx_msg void OnDeleteAd();
	afx_msg void OnShowBorder();
	afx_msg void OnUpdateShowBorder(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLICATIONDOC_H__69F8A0B4_9157_4D53_A540_E4567F151B2A__INCLUDED_)

#if !defined(AFX_LEFTVIEW_H__99F2B0BD_2716_4C4B_A709_B1D062EFD482__INCLUDED_)
#define AFX_LEFTVIEW_H__99F2B0BD_2716_4C4B_A709_B1D062EFD482__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeftView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeftView view
#include "ApplicationDoc.h"
#include "math_ops.h"	// Added by ClassView

class CLeftView : public CView
{
protected:
	CLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CBitmap m_Bmp;
	CView *m_MainView;

// Operations
public:
	CVECTOR ConvertTo3D(CPoint p,float z);
	CPoint ConvertTo2D(CVECTOR v);
	CApplicationDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in ApplicationView.cpp
inline CApplicationDoc* CLeftView::GetDocument()
{ return (CApplicationDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__99F2B0BD_2716_4C4B_A709_B1D062EFD482__INCLUDED_)

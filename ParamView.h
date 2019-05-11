#if !defined(AFX_PARAMVIEW_H__9F460418_4346_4A5D_80C9_64F45476661B__INCLUDED_)
#define AFX_PARAMVIEW_H__9F460418_4346_4A5D_80C9_64F45476661B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParamView view
#include "ApplicationDoc.h"

class CParamView : public CView
{
protected:
	CParamView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CParamView)

// Attributes
public:

// Operations
public:
	CApplicationDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParamView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CParamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CParamView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in ApplicationView.cpp
inline CApplicationDoc* CParamView::GetDocument()
{ return (CApplicationDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMVIEW_H__9F460418_4346_4A5D_80C9_64F45476661B__INCLUDED_)

#if !defined(AFX_DESKTOPVIEW_H__613392C9_65CC_45D4_9198_29F33B33CE06__INCLUDED_)
#define AFX_DESKTOPVIEW_H__613392C9_65CC_45D4_9198_29F33B33CE06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DesktopView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDesktopView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDesktopView : public CFormView
{
protected:
	CDesktopView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDesktopView)

// Form Data
public:
	//{{AFX_DATA(CDesktopView)
	enum { IDD = IDD_FORMVIEW_DESKTOP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesktopView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDesktopView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDesktopView)
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESKTOPVIEW_H__613392C9_65CC_45D4_9198_29F33B33CE06__INCLUDED_)

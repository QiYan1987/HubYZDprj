#if !defined(AFX_PAGEFILTER_H__AEDD4E52_2F13_446D_ACF1_4E6325CC854C__INCLUDED_)
#define AFX_PAGEFILTER_H__AEDD4E52_2F13_446D_ACF1_4E6325CC854C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageFilter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageFilter dialog

class CPageFilter : public CDialog
{
// Construction
public:
	CPageFilter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageFilter)
	enum { IDD = IDD_PAGEFILTER };
	int		m_IntFilter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageFilter)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEFILTER_H__AEDD4E52_2F13_446D_ACF1_4E6325CC854C__INCLUDED_)

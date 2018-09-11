#if !defined(AFX_PAGETIMES_H__44C19EB2_823B_4B81_BDE0_ED77D3A25B4A__INCLUDED_)
#define AFX_PAGETIMES_H__44C19EB2_823B_4B81_BDE0_ED77D3A25B4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTimes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageTimes dialog

class CPageTimes : public CDialog
{
// Construction
public:
	CPageTimes(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageTimes)
	enum { IDD = IDD_PAGETIMES };
	int		m_intTimes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageTimes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageTimes)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETIMES_H__44C19EB2_823B_4B81_BDE0_ED77D3A25B4A__INCLUDED_)

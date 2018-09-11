#if !defined(AFX_PAGEINOROUT_H__78B91884_9A93_4464_839C_631829424565__INCLUDED_)
#define AFX_PAGEINOROUT_H__78B91884_9A93_4464_839C_631829424565__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageInorOut.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageInorOut dialog

class CPageInorOut : public CDialog
{
// Construction
public:
	CPageInorOut(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageInorOut)
	enum { IDD = IDD_PAGEINOROUTCIRCLE };
	int		m_IntInOrOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageInorOut)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageInorOut)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEINOROUT_H__78B91884_9A93_4464_839C_631829424565__INCLUDED_)

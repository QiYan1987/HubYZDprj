#if !defined(AFX_DLGZUOBIAO_H__9354DEA9_95E2_4CC0_A077_96FC40796865__INCLUDED_)
#define AFX_DLGZUOBIAO_H__9354DEA9_95E2_4CC0_A077_96FC40796865__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgZuobiao.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgZuobiao dialog

class CDlgZuobiao : public CDialog
{
// Construction
public:
	CDlgZuobiao(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgZuobiao)
	enum { IDD = IDD_DIALOG_zuobiao };
	float	m_fdaogui;
	float	m_flizhu;
	double	m_dgxishu;
	double	m_lzxishu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgZuobiao)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgZuobiao)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGZUOBIAO_H__9354DEA9_95E2_4CC0_A077_96FC40796865__INCLUDED_)

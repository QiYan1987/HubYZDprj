#if !defined(AFX_DLGCHGQBIAODING_H__44076D8E_2E1A_48C0_8851_B8D6497B2240__INCLUDED_)
#define AFX_DLGCHGQBIAODING_H__44076D8E_2E1A_48C0_8851_B8D6497B2240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCHGQBiaoDing.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCHGQBiaoDing dialog

class CDlgCHGQBiaoDing : public CDialog
{
// Construction
public:
	CDlgCHGQBiaoDing(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCHGQBiaoDing)
	enum { IDD = IDD_DIALOG_BiaoDing };
	double	m_dMeaValue;
	double	m_dStdValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCHGQBiaoDing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCHGQBiaoDing)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHGQBIAODING_H__44076D8E_2E1A_48C0_8851_B8D6497B2240__INCLUDED_)

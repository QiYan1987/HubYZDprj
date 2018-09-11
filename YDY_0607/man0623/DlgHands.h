#if !defined(AFX_DLGHANDS_H__9011A7C8_DACF_482F_AA12_C0D9E2AD595C__INCLUDED_)
#define AFX_DLGHANDS_H__9011A7C8_DACF_482F_AA12_C0D9E2AD595C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHands.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHands dialog

class CDlgHands : public CDialog
{
// Construction
public:
	int m_cursel;
	float	m_dVelocity;
	CDlgHands(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CDlgHands)
	enum { IDD = IDD_DIALOG_HANDS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHands)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHands)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHANDS_H__9011A7C8_DACF_482F_AA12_C0D9E2AD595C__INCLUDED_)

#if !defined(AFX_DLGAJUSTCENTER_H__8D5E698D_4CE0_4CC5_A45C_52422EFDE17D__INCLUDED_)
#define AFX_DLGAJUSTCENTER_H__8D5E698D_4CE0_4CC5_A45C_52422EFDE17D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAjustCenter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAjustCenter dialog

class CDlgAjustCenter : public CDialog
{
// Construction
public:

	CDlgAjustCenter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAjustCenter)
	enum { IDD = IDD_DIALOG_AdjustCenter };
	double	m_dFastMoveDistance;
	double	m_dTargetEccentricity;
	UINT	m_intTimes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAjustCenter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAjustCenter)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAJUSTCENTER_H__8D5E698D_4CE0_4CC5_A45C_52422EFDE17D__INCLUDED_)

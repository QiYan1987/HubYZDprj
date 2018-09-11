#if !defined(AFX_DLG_PMPXD_H__7A18953F_239E_41E5_A8BE_8FBC44DCBD6A__INCLUDED_)
#define AFX_DLG_PMPXD_H__7A18953F_239E_41E5_A8BE_8FBC44DCBD6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_pmPXD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_pmPXD dialog

class CDlg_pmPXD : public CDialog
{
// Construction
public:
	CDlg_pmPXD(CWnd* pParent = NULL);   // standard constructor
	int m_fG11cursel;//µµÎ»Ñ¡Ôñ
	CTime m_time;
// Dialog Data
	//{{AFX_DATA(CDlg_pmPXD)
	enum { IDD = IDD_DIALOG_pmPXD };
	BOOL	m_bPre;
	CString	m_name1;
	float	m_PositionAway;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_pmPXD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_pmPXD)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_PMPXD_H__7A18953F_239E_41E5_A8BE_8FBC44DCBD6A__INCLUDED_)

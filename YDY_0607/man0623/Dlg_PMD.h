#if !defined(AFX_DLG_PMD_H__1865E5A3_23B5_4BF7_AD35_B6CFF3EB2693__INCLUDED_)
#define AFX_DLG_PMD_H__1865E5A3_23B5_4BF7_AD35_B6CFF3EB2693__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_PMD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_PMD dialog

class CDlg_PMD : public CDialog
{
// Construction
public:
	CDlg_PMD(CWnd* pParent = NULL);   // standard constructor
	int m_fG11cursel;//µµÎ»Ñ¡Ôñ
	CTime m_time;
// Dialog Data
	//{{AFX_DATA(CDlg_PMD)
	enum { IDD = IDD_DIALOG_PMD };
	CString	m_name1;
	//CString m_name;
	float	m_PositionAway;
	BOOL	m_bPre;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_PMD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_PMD)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_PMD_H__1865E5A3_23B5_4BF7_AD35_B6CFF3EB2693__INCLUDED_)

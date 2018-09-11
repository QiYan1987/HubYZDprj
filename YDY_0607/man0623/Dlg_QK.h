#if !defined(AFX_DLG_QK_H__808A9257_B953_4ED2_977B_A7DE365504BB__INCLUDED_)
#define AFX_DLG_QK_H__808A9257_B953_4ED2_977B_A7DE365504BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_QK.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_QK dialog

class CDlg_QK : public CDialog
{
// Construction
public:
	CDlg_QK(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_QK)
	enum { IDD = IDD_DIALOG_QK };
	float	m_fQK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_QK)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_QK)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_QK_H__808A9257_B953_4ED2_977B_A7DE365504BB__INCLUDED_)

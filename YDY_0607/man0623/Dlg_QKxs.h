#if !defined(AFX_DLG_QKXS_H__1F832320_5B04_46EF_B948_CE9247F033A5__INCLUDED_)
#define AFX_DLG_QKXS_H__1F832320_5B04_46EF_B948_CE9247F033A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_QKxs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_QKxs dialog

class CDlg_QKxs : public CDialog
{
// Construction
public:
	CDlg_QKxs(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_QKxs)
	enum { IDD = IDD_DIALOG_QKxs };
	float	m_fQKxs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_QKxs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_QKxs)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_QKXS_H__1F832320_5B04_46EF_B948_CE9247F033A5__INCLUDED_)

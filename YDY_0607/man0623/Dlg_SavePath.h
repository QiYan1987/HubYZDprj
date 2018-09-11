#if !defined(AFX_DLG_SAVEPATH_H__881EBE2C_44A8_466A_B6D4_DD611B8B3F41__INCLUDED_)
#define AFX_DLG_SAVEPATH_H__881EBE2C_44A8_466A_B6D4_DD611B8B3F41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_SavePath.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_SavePath dialog

class CDlg_SavePath : public CDialog
{
// Construction
public:
	CDlg_SavePath(CWnd* pParent = NULL);   // standard constructor
	CString	m_strPath;
// Dialog Data
	//{{AFX_DATA(CDlg_SavePath)
	enum { IDD = IDD_DIALOG_SavePath };
	CComboBox	m_ctrlComBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_SavePath)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_SavePath)
	afx_msg void OnButtonChange();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SAVEPATH_H__881EBE2C_44A8_466A_B6D4_DD611B8B3F41__INCLUDED_)

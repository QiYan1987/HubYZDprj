#if !defined(AFX_DLGUSERMANAGEMENT_H__32C24301_1293_480C_B429_5749DC00D950__INCLUDED_)
#define AFX_DLGUSERMANAGEMENT_H__32C24301_1293_480C_B429_5749DC00D950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUserManagement.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUserManagement dialog

class CDlgUserManagement : public CDialog
{
// Construction
public:
	CDlgUserManagement(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUserManagement)
	enum { IDD = IDD_DIALOG_USERMANAGEMENT };
	CString	m_strNewName;
	CString	m_strNewPwd;
	CString	m_strOldPwd;
	CString	m_strOldName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUserManagement)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUserManagement)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSERMANAGEMENT_H__32C24301_1293_480C_B429_5749DC00D950__INCLUDED_)

#if !defined(AFX_LOGIN_H__0601B11C_397F_40C5_B501_390B0A09DFDE__INCLUDED_)
#define AFX_LOGIN_H__0601B11C_397F_40C5_B501_390B0A09DFDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LOGIN.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLOGIN dialog

class CLOGIN : public CDialog
{
// Construction
public:
	CLOGIN(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLOGIN)
	enum { IDD = IDD_DIALOG_PWD };
	CString	m_userName;
	CString	m_userPwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLOGIN)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLOGIN)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_H__0601B11C_397F_40C5_B501_390B0A09DFDE__INCLUDED_)

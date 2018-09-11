#if !defined(AFX_PAGEEDIT_H__5B02784C_29AC_41A3_8146_DF36FD94B788__INCLUDED_)
#define AFX_PAGEEDIT_H__5B02784C_29AC_41A3_8146_DF36FD94B788__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageEdit dialog

class CPageEdit : public CDialog
{
// Construction
public:
	CPageEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageEdit)
	enum { IDD = IDD_PAGEEDIT };
	double	m_dEdit;
	CString	m_unitText;
	CString	m_nameText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageEdit)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEEDIT_H__5B02784C_29AC_41A3_8146_DF36FD94B788__INCLUDED_)

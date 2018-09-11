#if !defined(AFX_DLGEXTENDCIRCLE_H__94AF224F_743E_4489_BA57_ED909AD60E8F__INCLUDED_)
#define AFX_DLGEXTENDCIRCLE_H__94AF224F_743E_4489_BA57_ED909AD60E8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgextendCircle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgextendCircle dialog

class CDlgextendCircle : public CDialog
{
// Construction
public:
	CDlgextendCircle(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgextendCircle)
	enum { IDD = IDD_DIALOG_EXTEND };
	int		m_endposition;
	int		m_splitnumber;
	int		m_startposition;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgextendCircle)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgextendCircle)
	afx_msg void OnOkSave();
	afx_msg void OnQuit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXTENDCIRCLE_H__94AF224F_743E_4489_BA57_ED909AD60E8F__INCLUDED_)

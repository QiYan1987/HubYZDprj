#if !defined(AFX_DLGONEAXISPARA_H__91F1083B_F395_4F0C_914A_206608D865ED__INCLUDED_)
#define AFX_DLGONEAXISPARA_H__91F1083B_F395_4F0C_914A_206608D865ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOneAxisPara.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOneAxisPara dialog
#include "PageEdit.h"
#include "PageSelect.h"
class CDlgOneAxisPara : public CDialog
{
// Construction
public:
	void UpdateData(BOOL m_b);
	int m_dVelocity;
	double m_dPosition;
	CDlgOneAxisPara(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOneAxisPara)
	enum { IDD = IDD_DIALOGONEAXISPARA };
	CTabCtrl	m_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOneAxisPara)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOneAxisPara)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPageSelect	m_pgVelocity;
	CPageEdit  m_pgPosition;
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGONEAXISPARA_H__91F1083B_F395_4F0C_914A_206608D865ED__INCLUDED_)

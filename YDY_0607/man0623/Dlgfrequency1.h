#if !defined(AFX_DLGFREQUENCY1_H__AEC6D960_F30B_47AD_B443_AF92449F9902__INCLUDED_)
#define AFX_DLGFREQUENCY1_H__AEC6D960_F30B_47AD_B443_AF92449F9902__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlgfrequency1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgfrequency1 dialog

class CDlgfrequency1 : public CDialog
{
// Construction
public:
	CDlgfrequency1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgfrequency1)
	enum { IDD = IDD_DIALOG_Frequency };
	CComboBox	m_endfrequency;
	CComboBox	m_startfrequency;
		int  m_Intstart;
	int  m_Intend;
	BOOL onok;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgfrequency1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgfrequency1)
	afx_msg void OnOkSave();
	afx_msg void OnQuit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFREQUENCY1_H__AEC6D960_F30B_47AD_B443_AF92449F9902__INCLUDED_)

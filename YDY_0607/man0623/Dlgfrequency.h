#if !defined(AFX_DLGFREQUENCY_H__2904FCC5_2AEC_49B0_AAB1_54C8AEA45930__INCLUDED_)
#define AFX_DLGFREQUENCY_H__2904FCC5_2AEC_49B0_AAB1_54C8AEA45930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlgfrequency.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgfrequency dialog

class CDlgfrequency : public CDialog
{
// Construction
public:
	int m_Intstart;
	int  m_Intend;
	BOOL onok;
	CDlgfrequency(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgfrequency)
	enum { IDD = IDD_DIALOG_Frequency };
	CComboBox	m_endfrequency;
	CComboBox	m_startfrequency;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgfrequency)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgfrequency)
	afx_msg void OnOkSave();
	afx_msg void OnQuit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFREQUENCY_H__2904FCC5_2AEC_49B0_AAB1_54C8AEA45930__INCLUDED_)

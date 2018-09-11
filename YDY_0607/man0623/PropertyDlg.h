#if !defined(AFX_PROPERTYDLG_H__02916626_A4DB_46C8_9B03_39874714F8B6__INCLUDED_)
#define AFX_PROPERTYDLG_H__02916626_A4DB_46C8_9B03_39874714F8B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertyDlg dialog

class CPropertyDlg : public CDialog
{
// Construction
public:

	int		m_IntAlg;

	
	CPropertyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropertyDlg)
	enum { IDD = IDD_PROPERTY_DIALOG };
	CComboBox	m_ComboAlg;
	int		m_IntFilter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	afx_msg void OnCancel();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYDLG_H__02916626_A4DB_46C8_9B03_39874714F8B6__INCLUDED_)

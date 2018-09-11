#if !defined(AFX_MOTORCORRECTION_H__CB558DC5_EB53_4AF2_B3DE_49EE6C048D0E__INCLUDED_)
#define AFX_MOTORCORRECTION_H__CB558DC5_EB53_4AF2_B3DE_49EE6C048D0E__INCLUDED_

#define WM_DIALOG WM_USER+100////////////封学真定义对话框消息
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MotorCorrection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMotorCorrection dialog

class CMotorCorrection : public CDialog
{
// Construction
public:
	int nInde;
	CMotorCorrection(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMotorCorrection)
	enum { IDD = IDD_MOTORCORRECTION };
	CComboBox	m_combox;
	double	m_correctfactor1;
	double	m_correctfactor2;
	double	m_correctfactor3;
	double	m_correctfactor4;
	double	m_pingjing_factor1;
	double	m_pingjing_factor2;
	double	m_pingjing_factor3;
	double	m_pingjing_factor4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotorCorrection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMotorCorrection)
	afx_msg void OnMotorCorrect();
	afx_msg void OnSelchangeCombo1();
	afx_msg void Onapply();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTORCORRECTION_H__CB558DC5_EB53_4AF2_B3DE_49EE6C048D0E__INCLUDED_)

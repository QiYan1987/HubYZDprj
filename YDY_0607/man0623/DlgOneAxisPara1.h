#if !defined(AFX_DLGONEAXISPARA1_H__5FD68AB5_EAEE_4095_B6A2_7A5880CBBAFA__INCLUDED_)
#define AFX_DLGONEAXISPARA1_H__5FD68AB5_EAEE_4095_B6A2_7A5880CBBAFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOneAxisPara1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOneAxisPara1 dialog

class CDlgOneAxisPara1 : public CDialog
{
// Construction
public:
	CDlgOneAxisPara1(CWnd* pParent = NULL);   // standard constructor
	float m_dVelocity;//�ٶ�
	int m_cursel;//�ٶȵ�λ
// Dialog Data
	//{{AFX_DATA(CDlgOneAxisPara1)
	enum { IDD = IDD_DIALOG_ONEAXISPARA1 };
	double	m_dPosition;//λ��
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOneAxisPara1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOneAxisPara1)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGONEAXISPARA1_H__5FD68AB5_EAEE_4095_B6A2_7A5880CBBAFA__INCLUDED_)

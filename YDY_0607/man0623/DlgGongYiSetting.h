#if !defined(AFX_DLGGONGYISETTING_H__D7596AE3_40EB_4C6C_8BD6_F07C1D71E8D2__INCLUDED_)
#define AFX_DLGGONGYISETTING_H__D7596AE3_40EB_4C6C_8BD6_F07C1D71E8D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGongYiSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGongYiSetting dialog

class CDlgGongYiSetting : public CDialog
{
// Construction
public:
	CDlgGongYiSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGongYiSetting)
	enum { IDD = IDD_DIALOG_GONGYISETTING };
	double	m_dCZD;
	double	m_dPMD;
	double	m_dPXD;
	double	m_dTZD;
	double	m_dYD;
	double	m_dYZD;
	double	m_dZXD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGongYiSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGongYiSetting)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGONGYISETTING_H__D7596AE3_40EB_4C6C_8BD6_F07C1D71E8D2__INCLUDED_)

#if !defined(AFX_DLG_ZXD_H__15072F1D_9B19_439D_B701_DDD10D118C3E__INCLUDED_)
#define AFX_DLG_ZXD_H__15072F1D_9B19_439D_B701_DDD10D118C3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_ZXD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_ZXD dialog

class CDlg_ZXD : public CDialog
{
// Construction
public:
	CDlg_ZXD(CWnd* pParent = NULL);   // standard constructor
	int m_fG11cursel;//档位选择
	float m_Velocity;//速度
	int m_cursel;
// Dialog Data
	//{{AFX_DATA(CDlg_ZXD)
	enum { IDD = IDD_DIALOG_ZXD };
	float	m_high1;
	CTime m_time;
	CString	m_name1;
	float	m_PositionAway;
	BOOL	m_bPre;
	BOOL	m_bBack0;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_ZXD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_ZXD)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_ZXD_H__15072F1D_9B19_439D_B701_DDD10D118C3E__INCLUDED_)

#if !defined(AFX_DLG_PXD_H__DCFA556D_6495_486C_B668_02FED1E3962E__INCLUDED_)
#define AFX_DLG_PXD_H__DCFA556D_6495_486C_B668_02FED1E3962E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_PXD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_PXD dialog

class CDlg_PXD : public CDialog
{
// Construction
public:
	CDlg_PXD(CWnd* pParent = NULL);   // standard constructor
	int m_fG11cursel;//档位选择
	float m_Velocity;//速度
	int m_cursel;
// Dialog Data
	//{{AFX_DATA(CDlg_PXD)
	enum { IDD = IDD_DIALOG_PXD };
	CString	m_name1;
	CTime m_time;
	float	m_high1;
	BOOL	m_bPre;
	float	m_PositionAway;
	BOOL	m_bBack0;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_PXD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_PXD)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_PXD_H__DCFA556D_6495_486C_B668_02FED1E3962E__INCLUDED_)

#if !defined(AFX_DLG_TZD_H__97A1AC93_EA55_4658_8DC3_7B51427B0D1D__INCLUDED_)
#define AFX_DLG_TZD_H__97A1AC93_EA55_4658_8DC3_7B51427B0D1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_TZD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_TZD dialog
#define MAXJIEMIANSHU 14
class CDlg_TZD : public CDialog
{
// Construction
public:
	CDlg_TZD(CWnd* pParent = NULL);   // standard constructor
	
	void UpdataHeightList();//等间距更新函数
	int m_SumCount;//截面数
	float m_height[MAXJIEMIANSHU];//每层界面高度
	int m_fG11cursel;//档位选择
	// Dialog Data
	//{{AFX_DATA(CDlg_TZD)
	enum { IDD = IDD_DIALOG_TZD };
	CListCtrl	m_ctrListHeight;
	CString	m_name1;
	float	m_high1;
	CTime m_time;
	BOOL	m_bPre;
	float	m_PositionAway;
	BOOL	m_bBack0;
	float	m_dHeight;
	int		m_num1;
	int		m_intSelect;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_TZD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RefreshHeightList();
	// Generated message map functions
	//{{AFX_MSG(CDlg_TZD)
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnRadio2();
	afx_msg void OnRadioSelect();
	afx_msg void OnChangeEditTzdH();
	afx_msg void OnChangeEDITTZDNum();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_TZD_H__97A1AC93_EA55_4658_8DC3_7B51427B0D1D__INCLUDED_)

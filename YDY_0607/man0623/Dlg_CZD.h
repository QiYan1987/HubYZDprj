#if !defined(AFX_DLG_CZD_H__7A0EAFBC_3EE9_4703_BC09_67F4275C634C__INCLUDED_)
#define AFX_DLG_CZD_H__7A0EAFBC_3EE9_4703_BC09_67F4275C634C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_CZD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_CZD dialog
#define MAXJIEMIANSHU 14
class CDlg_CZD : public CDialog
{
// Construction
public:
	CDlg_CZD(CWnd* pParent = NULL);   // standard constructor
	void UpdataHeightList();//等间距更新函数
	int m_SumCount;//截面数
	float m_height[MAXJIEMIANSHU];//每层界面高度
	int m_fG11cursel;//档位选择
// Dialog Data
	//{{AFX_DATA(CDlg_CZD)
	enum { IDD = IDD_DIALOG_CZD };
	CListCtrl	m_ctrListHeight;
	CString	m_name1;
	float	m_high1;
	CTime m_time;
	float	m_PositionAway;//离开距离
	BOOL	m_bPre;//
	BOOL	m_bBack0;
	int		m_num1;
	float	m_dHeight;
	int		m_intSelect;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_CZD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RefreshHeightList();
	// Generated message map functions
	//{{AFX_MSG(CDlg_CZD)
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelete();
	afx_msg void OnChangeEditCzdH();
	afx_msg void OnRadioSelect();
	afx_msg void OnRadio2();
	afx_msg void OnChangeEDITCZDNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_CZD_H__7A0EAFBC_3EE9_4703_BC09_67F4275C634C__INCLUDED_)

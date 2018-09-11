#if !defined(AFX_DLG_YZD_H__597EE2D1_A33A_4EE3_AB74_2B10D0EEA16F__INCLUDED_)
#define AFX_DLG_YZD_H__597EE2D1_A33A_4EE3_AB74_2B10D0EEA16F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_YZD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_YZD dialog
class CDlg_YZD : public CDialog
{
// Construction
public:
	CDlg_YZD(CWnd* pParent = NULL);   // standard constructor


	void UpdataHeightList();//等间距更新函数
	int m_SumCount;//截面数
	float m_height[JMNum];//每层界面高度
	int m_fG11cursel;//档位选择
// Dialog Data
	//{{AFX_DATA(CDlg_YZD)
	enum { IDD = IDD_DIALOG_YZD };
	CListCtrl	m_ctrListHeight;
	CString	m_name1;//文件名
	float	m_high1;//测量高度
	int		m_num1;//测量层数
	CTime m_time;//测量时间
	BOOL	m_bPre;//测量前接触
	float	m_PositionAway;//离开距离
	int		m_intSelect;//等间距和非等间距选择
	float	m_dHeight;//添加的高度
	BOOL	m_bBack0;
	//}}AFX_DATA
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_YZD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RefreshHeightList();

	// Generated message map functions
	//{{AFX_MSG(CDlg_YZD)
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnRadioSelect();//等间隔
	afx_msg void OnRadio2();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelete();
	afx_msg void OnChangeEditYzdH();
	afx_msg void OnChangeEDITYZDNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_YZD_H__597EE2D1_A33A_4EE3_AB74_2B10D0EEA16F__INCLUDED_)

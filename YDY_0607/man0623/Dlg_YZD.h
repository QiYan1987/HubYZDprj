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


	void UpdataHeightList();//�ȼ����º���
	int m_SumCount;//������
	float m_height[JMNum];//ÿ�����߶�
	int m_fG11cursel;//��λѡ��
// Dialog Data
	//{{AFX_DATA(CDlg_YZD)
	enum { IDD = IDD_DIALOG_YZD };
	CListCtrl	m_ctrListHeight;
	CString	m_name1;//�ļ���
	float	m_high1;//�����߶�
	int		m_num1;//��������
	CTime m_time;//����ʱ��
	BOOL	m_bPre;//����ǰ�Ӵ�
	float	m_PositionAway;//�뿪����
	int		m_intSelect;//�ȼ��ͷǵȼ��ѡ��
	float	m_dHeight;//��ӵĸ߶�
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

	afx_msg void OnRadioSelect();//�ȼ��
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

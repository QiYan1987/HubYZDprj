#if !defined(AFX_DODYNAMICDISPLAY_H__BB435B01_7F8B_4374_B7A9_A60C254130AD__INCLUDED_)
#define AFX_DODYNAMICDISPLAY_H__BB435B01_7F8B_4374_B7A9_A60C254130AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoDynamicDisplay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoDynamicDisplay form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDoDynamicDisplay : public CFormView
{
protected:
	CDoDynamicDisplay();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoDynamicDisplay)

// Form Data
public:
	//{{AFX_DATA(CDoDynamicDisplay)
	enum { IDD = IDD_FORMVIEW_DYNAMICDISPLAY };
	CButton	m_ctrlBtnOpen;
	CButton	m_ctrlBtnStop;
	CStatic	m_editDynamicDisplay;
	int		m_dangwei;
	//}}AFX_DATA

// Attributes
public:
	CRect		rect;              // 存储绘图控件的绘图区域
	CDC			*pDC;                 // 控件的屏幕绘图设备指针
	CDC			memDC;                // 内存绘图设备
	CBitmap		memBitmap;        // 用于内存绘图的位图  
	CBitmap		*pOldBmp;         // 备份旧的位图指针 
	CWnd		*pWnd1;              // 绘图控件的
	double		m_G1;
	double		m_G2;
	UINT		mesData[3600];
	CRect		m_rect;
	double		m_Middle;
	double		m_OutIn;
	UINT		m_count;
	UINT		m_oldpos;
	BOOL		m_bCalFlag;
	double		dresult[2];
	double      m_flag;
	long mes[2];
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoDynamicDisplay)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DynamicDrawCircle();
	virtual ~CDoDynamicDisplay();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoDynamicDisplay)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOpendyn();
	afx_msg void OnStopdyn();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DODYNAMICDISPLAY_H__BB435B01_7F8B_4374_B7A9_A60C254130AD__INCLUDED_)

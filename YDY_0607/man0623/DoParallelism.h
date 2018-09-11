#if !defined(AFX_DOPARALLELISM_H__275652C7_5F69_433B_BAC2_96AE849A1C47__INCLUDED_)
#define AFX_DOPARALLELISM_H__275652C7_5F69_433B_BAC2_96AE849A1C47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoParallelism.h : header file
//平行度类

/////////////////////////////////////////////////////////////////////////////
// CDoParallelism form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDoParallelism : public CFormView
{
protected:
	CDoParallelism();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoParallelism)

// Form Data
public:
	//{{AFX_DATA(CDoParallelism)
	enum { IDD = IDD_FORMVIEW4 };
	CStatic	m_editParallelism;
	//}}AFX_DATA

// Attributes
public:
  shuju m_data[7200];

// Operations
public:
	void Parallelalgorithm();
	void ChangeValueOfSelect(CString path, int startPosition, int endPosition, BOOL isSelected);
	BOOL m_lineselect;
	void DrawingCleanAndReset(CString path, BOOL isSelected);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoParallelism)
	public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnDraw(CDC* pDC);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ReadDataFromFile();
	BOOL  m_bDrawStartFigeure1;
	BOOL  m_bDrawMoveFigeure1;
	BOOL  m_bDrawEndFigeure1;
	BOOL  m_bDrawStartFigeure2;
	BOOL  m_bDrawMoveFigeure2;
	BOOL  m_bDrawEndFigeure2;
	BOOL   m_bDraw1;
	BOOL   m_bDraw2;
	CPoint m_StartPoint;
	CPoint m_LastEndPoint;
	CPoint m_MovePoint;
	int	m_penScale;

	CPoint m_mouseOrigin;
	CPoint m_mouseFinish; 

	double m_max;
	double m_min; 
	double m_max2;
	double m_min2; 
	double sum[3607];
	double pointer[3600];
	double pointer0[7200];
	double pointer2[3600];
	double m_startPosition;
	double m_endPosition;
	BOOL m_lineanalysis;

	double m_pmax;
	double m_pmin;
	double m_pmax2;
	double m_pmin2;
	double G1;
	double G2;
	float m_Height;
	CTime m_time;
	int m_paverage;
	int m_paverage2;
	double xL1[3400];
	double GResult;
	virtual ~CDoParallelism();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoParallelism)
	afx_msg void OnDestroy();
	afx_msg void OnSelectbutton();
	afx_msg void OnAnalysisbutton();
	afx_msg void Onresetpxd();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnresetdeal();
	afx_msg void OnPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect rect;
	CBitmap   *pOldBmp;
	CDC       *pDC;                 // 控件的屏幕绘图设备指针
	CDC       mDC;                // 内存绘图设备
	CBitmap   memBitmap;        // 用于内存绘图的位图  
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOPARALLELISM_H__275652C7_5F69_433B_BAC2_96AE849A1C47__INCLUDED_)

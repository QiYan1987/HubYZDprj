#if !defined(AFX_DOADJUSTORITATION_H__F046B402_3077_4C9F_902E_1A330463D652__INCLUDED_)
#define AFX_DOADJUSTORITATION_H__F046B402_3077_4C9F_902E_1A330463D652__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxext.h>
#include <afxext.h>
#include "const.h"
#include "math.h"
#include "3dPoint.h"
#endif // _MSC_VER > 1000
// DoAdjustOritation.h : header file
//调心调平绘图类

/////////////////////////////////////////////////////////////////////////////
// CDoAdjustOritation form view
#ifndef __AFXEXT_H__
#endif

class CDoAdjustOritation : public CFormView
{
protected:
	CDoAdjustOritation();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoAdjustOritation)

// Form Data
public:
	//{{AFX_DATA(CDoAdjustOritation)
	enum { IDD = IDD_FORMVIEW_AdjustOritation };
	CStatic	m_AdjustOritation;
	//}}AFX_DATA
 shuju0 m_datayzd[8000];
// Attributes
private:
	int        m_IntJM,m_IntPoint,m_FullData;
	double     G1,G2;
	CString    m_CYLT;
	CString    m_CYLP;
	CString    m_CYLV;
	int        FilterMode;
	double     Rr[10][3600],r[10][3600];
	double     pem[10][3600];
	double     m_dfls[10][3600];
	double     xp[10][3600],yp[10][3600];
	double     dis1[10][3600], cutE[10][3600];
	double     xi[10][3600],yi[10][3600];
	C3dPoint   Z3DRondness[10][3600];
	CPoint     Z2DRondness[10][3600];
	double     XJM[10][3600];
	double     YJM[10][3600];

	double     m_down_YZdEcc;
    double     m_down_YZdEccPos;
	double     m_up_YZdEcc;
    double     m_up_YZdEccPos;

	
public:
	CWnd *pWndPicture; 
    CRect rect; 
    CDC *pDCPicture;
    CDC memDC;               //取当前窗口的CDC 	
	CBitmap* pOldBmp;  // 获得对话框上的picture的设备指针
	CBitmap memBitmap;
	double      AngleZ;



// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoAdjustOritation)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDoAdjustOritation();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoAdjustOritation)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnBtntleft();
	afx_msg void OnBtntright();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtntbegin();
	afx_msg void OnBtntstop();
	//}}AFX_MSG
    void DrawCylinder();
    void Rotate(double &x, double &y, double &z);
	void  WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata);
	void  SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOADJUSTORITATION_H__F046B402_3077_4C9F_902E_1A330463D652__INCLUDED_)

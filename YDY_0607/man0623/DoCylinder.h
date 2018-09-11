#if !defined(AFX_DOCYLINDER_H__F91D6EBA_90F9_4402_B24B_573B2B7FBC1A__INCLUDED_)
#define AFX_DOCYLINDER_H__F91D6EBA_90F9_4402_B24B_573B2B7FBC1A__INCLUDED_
#include "const.h"
#include "math.h"
#include "3dPoint.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoCylinder.h : header file
//圆柱度类
/////////////////////////////////////////////////////////////////////////////
// CDoCylinder form view
//圆柱度
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDoCylinder : public CFormView
{
protected:
	CDoCylinder();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoCylinder)

// Form Data
public:
	//{{AFX_DATA(CDoCylinder)
	enum { IDD = IDD_FORMVIEW2 };
	CStatic	m_editCylinder;
	//}}AFX_DATA
	shuju0 m_datayzd[JMNum*RecCount];
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoCylinder)
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

private:
	CRect rect1;
	int        m_IntJM,m_IntPoint,LenData;
	double     G1,G2;
	CString    m_CYLT;
	CString    m_CYLP;
	CString    m_CYLV;
	CString    m_Seeangle;
	int        FilterMode;
	double     Rr[JMNum][3600],r[JMNum][3600];
	double     pem[JMNum][3600];
	double     DRAWpem[JMNum][3600];
	double     m_dfls[JMNum][3600];
	double     xp[JMNum][3600],yp[JMNum][3600];
	double     dis1[JMNum][3600], cutE[JMNum][3600];
	double     xi[JMNum][3600],yi[JMNum][3600];
	C3dPoint   Z3DRondness[JMNum][3600];
	CPoint     Z2DRondness[JMNum][3600];
	double     XJM[JMNum][3600];
	double     YJM[JMNum][3600];
	double     jmdata[3600];
	double     Resdata[3600];
	double     zz[JMNum];
	CTime	   m_time;
	int      SeeAngle;
    int      AngleZ;
    double   AngleX,AngleY;
	CString   m_Wa;	//波纹度显示
	CString   m_Wc;	//波纹度显
	CString   m_Wp;	//波纹度显
	CString   m_Wv;	//波纹度显示
	CString   m_Wt;	//波纹度显
	CString   m_Wq;	//波纹度显
    CString   m_Wwm;	//波纹度显
public:
	double vect_norm(double vect[], int n);
	CWnd *pWndPicture; 
    CRect rect; 
    CDC *pDCPicture;
    CDC memDC;               //取当前窗口的CDC 	
	CBitmap* pOldBmp;  // 获得对话框上的picture的设备指针
	CBitmap memBitmap;
	double dx;
	C3dPoint meanup;

	int m_AmpScale;
	int m_ModeChoose;
	int flagAmpscale;
	int ratio1;
	int ratio;

protected:
	void PrintCylinder();
	int m_penScale;
	void ReadDataFromFile();
	virtual ~CDoCylinder();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoCylinder)
	afx_msg void OnDestroy();
    afx_msg void OnPaint();
	afx_msg void OnTRight();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTLeft();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPrint();
	afx_msg void OnBtntbegin();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtntstop();
	afx_msg void OnAmplifyScale();
	//}}AFX_MSG
    void  DrawCylinder();//画圆柱
	void  WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata);
	void  SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr);
	void  Rotate(double &x, double &y, double &z)  ;
    void  SubQKDataChuli(CString path,int Number,int JM, BOOL AutoOrManChuli, double *Soudata, double *Resdata);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCYLINDER_H__F91D6EBA_90F9_4402_B24B_573B2B7FBC1A__INCLUDED_)

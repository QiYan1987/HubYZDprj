#if !defined(AFX_DOCOAXIALITY_H__FF7E179E_79F9_4099_A1BF_5DE2983C97D3__INCLUDED_)
#define AFX_DOCOAXIALITY_H__FF7E179E_79F9_4099_A1BF_5DE2983C97D3__INCLUDED_
#include "const.h"
#include "math.h"
#include "3dPoint.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoCoaxiality.h : header file
//同轴度作图类

/////////////////////////////////////////////////////////////////////////////
// CDoCoaxiality form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDoCoaxiality : public CFormView
{
protected:
	CDoCoaxiality();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoCoaxiality)

// Form Data
public:
	//{{AFX_DATA(CDoCoaxiality)
	enum { IDD = IDD_FORMVIEW7 };
	CStatic	m_editCylinder;
	//}}AFX_DATA
	shuju0 m_datayzd[JMNum*RecCount];
	int m_AmpScale;
	int m_ModeChoose;
	int flagAmpscale;
	int ratio1;
// Attributes
private:
		CRect rect1;
		int        m_IntJM,m_IntPoint,LenData;//截面数，点数，数据长度
		double     G1,G2;
		CString    m_CYLT;
		CString    m_CYLP;
		CString    m_CYLV;
	    CString    m_tzd;
	    CString    m_Seeangle;
	    int ratio;

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
	double     PrintAdata[JMNum][3600];

		CTime	   m_time;
		double     tzd;
		BOOL       BTCHUL;//鼠标双击的截面
	
		int        AngleZ;
		int        SeeAngle;
		CString   m_Wa;	//波纹度显示
		CString   m_Wc;	//波纹度显
		CString   m_Wp;	//波纹度显
		CString   m_Wv;	//波纹度显示
		CString   m_Wt;	//波纹度显
		CString   m_Wq;	//波纹度显
        CString   m_Wwm;	//波纹度显
	//public:
		int scale;
		CWnd   *pWnd; 
		CRect   rect; 
		CDC    *pDC;
		CDC     memDC;               //取当前窗口的CDC 	
		CBitmap* pOldBmp;  // 获得对话框上的picture的设备指针
		CBitmap memBitmap;
	  

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoCoaxiality)
	public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_penScale;
	void PrintCoaxiality();
	void ReadDataFromFile();
	virtual ~CDoCoaxiality();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoCoaxiality)
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnToLeft();
	afx_msg void OnToRight();
	afx_msg void OnPrint();
	afx_msg void OnBtntbegin();
	afx_msg void OnBtntstop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAmplifyScale();
	//}}AFX_MSG
	void  Rotate(double &x, double &y, double &z);
    void  DrawCoaxiality();
	void  WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata);
	void  SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr);
    void  SubQKDataChuli(CString path,int Number, double *Resdata,BOOL GManCuliQkFlag,int JM,int Totaldot);
    void  CalCoaxiality();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCOAXIALITY_H__FF7E179E_79F9_4099_A1BF_5DE2983C97D3__INCLUDED_)

#if !defined(AFX_DOVERTICALITY_H__4BC85FB3_83A5_4994_9583_E62C91049B85__INCLUDED_)
#define AFX_DOVERTICALITY_H__4BC85FB3_83A5_4994_9583_E62C91049B85__INCLUDED_
#include "const.h"
#include "math.h"
#include "3dPoint.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoVerticality.h : header file
//垂直度类

/////////////////////////////////////////////////////////////////////////////
// CDoVerticality form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDoVerticality : public CFormView
{
protected:
	CDoVerticality();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoVerticality)

// Form Data
public:
	//{{AFX_DATA(CDoVerticality)
	enum { IDD = IDD_FORMVIEW8 };
	CStatic	m_EditVerticality;
	//}}AFX_DATA
    shuju0 m_dataczd[JMNum*RecCount];
// Attributes
// Operations
private:
	CRect rect1;
	int        m_IntJM,m_IntPoint,LenData;
	double     G1,G2;
	double     Rr[JMNum][3600],r[JMNum][3600];
	double     pem[JMNum][3600];
	double     m_dfls[JMNum][3600];
	double     xp[JMNum][3600],yp[JMNum][3600];
	double     dis1[JMNum][3600], cutE[JMNum][3600];
	double     xi[JMNum][3600],yi[JMNum][3600];
	C3dPoint   Z3DRondness[JMNum][3600];
	CPoint     Z2DRondness[JMNum][3600];
	double     XJM[JMNum][3600];
	double     YJM[JMNum][3600];
	double     PrintAdata[JMNum][3600];
	CPoint	   pt2Start;
	CPoint     pt2End;
	CTime      m_time;
	int        SeeAngle;
    int        AngleZ;
	CString    m_Seeangle;
     
	CString   m_Wa;	//波纹度显示
	CString   m_Wc;	//波纹度显
	CString   m_Wp;	//波纹度显
	CString   m_Wv;	//波纹度显示
	CString   m_Wt;	//波纹度显
	CString   m_Wq;	//波纹度显
    CString   m_Wwm;	//波纹度显
public:
	CWnd    *pWndPicture; 
    CRect    rect; 
    CDC     *pDCPicture;
    CDC      memDC;               //取当前窗口的CDC 	
	CBitmap *pOldBmp;  // 获得对话框上的picture的设备指针
	CBitmap  memBitmap;
	 double  czd;
	 CString m_czd;

	 int m_AmpScale;
	 int m_ModeChoose;
	 int flagAmpscale;
	int ratio1;
	int ratio;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoVerticality)
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
	void PrintCzd();
	void ReadDataFromFile();
	void DrawPLM();
	virtual ~CDoVerticality();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoVerticality)
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnBtntleft();
	afx_msg void OnBtntright();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPrint();
	afx_msg void OnBtntbegin();
	afx_msg void OnBtntstop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAmplifyScale();
	//}}AFX_MSG
	void  DrawCzd();//画圆柱
    void  CalVerticality();//计算同轴度
	void  WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata);
	void  SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr);
	void  Rotate(double &x, double &y, double &z)  ;
    void SubQKDataChuli(CString path,int Number, double *Resdata,BOOL GManCuliQkFlag,int JM,int Totaldot);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOVERTICALITY_H__4BC85FB3_83A5_4994_9583_E62C91049B85__INCLUDED_)

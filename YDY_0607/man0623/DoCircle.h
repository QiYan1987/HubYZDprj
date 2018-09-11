#if !defined(AFX_DOCIRCLE_H__B928713B_30D8_417E_9298_DA4B69034DC8__INCLUDED_)
#define AFX_DOCIRCLE_H__B928713B_30D8_417E_9298_DA4B69034DC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoCircle.h : header file
//圆度类
/////////////////////////////////////////////////////////////////////////////
// CDoCircle form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "ListCtrlCl.h"
#include "PropertyDlg.h"	// Added by ClassView
class CDoCircle : public CFormView
{
protected:
	CDoCircle();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoCircle)

// Form Data
public:
	//{{AFX_DATA(CDoCircle)
	enum { IDD = IDD_FORMVIEW };
	CStatic	m_editCircle;
	CPoint m_zancun1;
    CPoint m_zancun2;
	//}}AFX_DATA
	shuju m_data[3600];
// Attributes

// Operations


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoCircle)
	public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnDraw(CDC* pDC);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
	private:
		int flag_bg;
		BOOL m_bIsAutoQK;//自动去缺口

		int       m_Flagcircle;
		CString   m_strFilterMode;
		CString   m_strdRONT;
		CString   m_strdEcc;
		CString   m_strdEccPos;
		CString	  m_strlvbo;
		CString	  m_strMethod;
		CTime	  m_time;
		CPoint    m_ptEnd;
		BOOL      m_bDraw;
		CPoint    m_ptOrigin;
		double    fpdata[3600];
        double    dataafterfilter[3600];
		double    drawdata[3600];
       	double    Resdata[3600];
	
		CRect     rect1;              // 存储绘图控件的绘图区域
		CDC       *pDC;                 // 控件的屏幕绘图设备指针
		CDC       memDC;                // 内存绘图设备
		CBitmap   memBitmap;        // 用于内存绘图的位图  
		CBitmap   *pOldBmp;         // 备份旧的位图指针 
		CWnd     *pWnd1;              // 绘图控件的
        CRect    rect_ctr;
		BOOL m_LpDraw;
      	
		double DispMaxdirecMZC;     //最小区域法评定圆度误差的参数信息
		double DispMindirecMZC;
		double MZCDX;
		double MZCDY;
		double MZCEcc;
        double MZCEccPos;
		CString m_MZCRONT;

		double DispMaxdirecMCC;
		double DispMindirecMCC;
		double  MCCDX;
		double  MCCDY;
		double MCCEcc;
        double MCCEccPos;
        CString m_MCCRONT;
		
		double DispMaxdirecMIC;
		double DispMindirecMIC;
		double  MICDX;
		double  MICDY;
		double MICEcc;
        double MICEccPos;
        CString m_MICRONT;

	
        double    Direc[3600];
		double    TempJgBWD[8];
        double    m_BWD[7];
        CString   m_Wa;	//波纹度显示
        CString   m_Wc;	//波纹度显
        CString   m_Wp;	//波纹度显
        CString   m_Wv;	//波纹度显示
        CString   m_Wt;	//波纹度显
        CString   m_Wq;	//波纹度显
        CString   m_Wwm;	//波纹度显
		
	protected:
		CRect m_rect;
		double m_Middle;
	    double m_OutIn;
		int	m_penScale;

	public:		
		void OnLpxianshi();
		void FindQkMaxMin();
		void OnLpDraw(CDC *pDC);
		double ratio;
		int ratio1;
		int m_AmpScale;
		int m_ModeChoose;
		int flagAmpscale;
	
		double m_AmplifyScale;
		double RectScale;
		double DrawrectWidth;
		double DrawrectHeight;
		void DrawBaogao();
		void DrawGrid3Frequency();
		void DrawFrequency();
		void DrawGrid2();
		void DrawGride1();
		BOOL m_BOOLSegmentprocess;
		int   CirEvalue;
		int   FilterMode;
		int   m_Intstep;
		BOOL  m_bIsEnable;
		double G2;
		double G1;
		CBrush m_brush;
		CPoint m_zancunOrigin;
		CPoint m_zancunfinish;
        double dRONT;
		double dEcc;
		double dEccPos;
		double GResult[10];
        int m_IndexStart;
	    int m_IndexEnd;
		//int	m_endposition; //qy 2018-6-14
		double  m_endposition;
		int	m_splitnumber;
		//int	m_startposition;//qy 2018-6-14
		double m_startposition;
        double theta1;
		double theta2;
		double alpha1;
		double alpha2;
		BOOL   flagmanchuli;
		int    FlagMove;
		BOOL   Flagxzhou;

		double m_maxsplit[100];
		double m_minsplit[100];
		double m_PV[100];

		int  m_Intstart;
	    int  m_Intend;
		BOOL FlagFrequency;

		double XRf4[3601];
		int Frepointi;
		double Frepointx;
		double Frepointy;
		BOOL BoolButtondown;
		double bogao[3600];
		double weizhi[3600];
		int DispTempFnumber;
		BOOL FlagBogao;

		double GQkWStart[100],GQkWEnd[100],GQkNMaxValue[100],GQkNMinValue[100],GQKqsValue[100],GQKzzValue[100];
		int TempStart,TempEnd;
		int TempNA,TempNB,GQkNumber,QkNumber,jLeft;



// Implementation
protected:
	void PrintCircleMZC();//最小区域
	void PrintCircleMIC();//最大内切圆
	void PrintCircleMCC();//最小外接圆
	void PrintCircle();
	void canshu();
	void PrintSegmentationprocess();
	CFont newFont;
	void ReadDataFromFile();
	virtual ~CDoCircle();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// Generated message map functions
	//{{AFX_MSG(CDoCircle)
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnProperty();//滤波参数设置的对话框
	afx_msg void OnEnAbleSelect();
	afx_msg void OnReset();
	afx_msg void OnFenDuanChuli();
	afx_msg void OnYuanDuChuLi();
	afx_msg void OnBtnbgfx();
	afx_msg void OnBtnppfx();
	afx_msg void OnPrint();
	afx_msg void OnBtnAmplifyScale();
	afx_msg void OnPaint();
	afx_msg void OnLpPrint();
	//}}AFX_MSG
protected:
    void DrawCircle();
    void MZCyuandu(double *Soudata);//最小区域计算
    void MCCyuandu(double *Soudata);//最小外接圆计算
    void MICyuandu(double *Soudata);//最大内切圆计算
    void DrawCircleMZC();//最小区域
    void DrawCircleMIC(); //最小外接圆
    void DrawCircleMCC();//最大内切圆
    void BWDANA(double *Direc);
    void Segmentationprocess();
    void DynamicDrawCircle( int startPosition, int endPosition);
    void SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr);
    void DrawFilter (int  FilterMode ,double *pMem,double*drawdata);
    void WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata);
    void ChangeValueOfSelect(CString path,int startPosition, int endPosition, BOOL isSelected);
    void DrawingCleanAndReset(CString path, BOOL isSelected);
    void SubQKDataChuli(CString path,int Number, BOOL AutoOrManChuli,double *Soudata, double *Resdata,int m_IndexStart, int m_IndexEnd);
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_DOCIRCLE_H__B928713B_30D8_417E_9298_DA4B69034DC8__INCLUDED_)

#if !defined(AFX_JMANALYSE_H__9072811D_FE78_4457_AFB8_9A0464B69F85__INCLUDED_)
#define AFX_JMANALYSE_H__9072811D_FE78_4457_AFB8_9A0464B69F85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JMAnalyse.h : header file
//截面分析类

/////////////////////////////////////////////////////////////////////////////
// CJMAnalyse form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CJMAnalyse : public CFormView
{
protected:
	CJMAnalyse();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CJMAnalyse)

// Form Data
public:
	//{{AFX_DATA(CJMAnalyse)
	enum { IDD = IDD_FORMVIEW_JMANALYSE };
	CStatic	m_JManalyse;
	//}}AFX_DATA
	shuju0 m_dataJM[36001];

// Attributes
public:
	CRect     rectJM;              // 存储绘图控件的绘图区域
	CDC       *pDCJM;                 // 控件的屏幕绘图设备指针
	CDC       memDCJM;                // 内存绘图设备
	CBitmap   memBitmapJM;        // 用于内存绘图的位图  
	CBitmap   *pOldBmpJM;         // 备份旧的位图指针 
	CWnd     *pWndJM;              // 绘图控件的
// Operations
public:
	int       CirEvalue;//算法
	int     FilterMode;//滤波
    int       m_Intstep;
    BOOL      m_bIsEnable;
	CString	  m_strlvbo;
	CString	  m_strMethod;
	CString   m_strFilterMode;
	CString   m_strdRONT;
	CString   m_strdEcc;
	CString   m_strdEccPos;
	BOOL      m_bDraw;
    CPoint    m_zancunOrigin;
    CPoint    m_zancunfinish;

	int       fpdata[3600];
    double    dataafterfilter[3600];
    double    drawdata[3600];
	double    Resdata[3600];
	double    m_CirCal[3600];
	double    GResult[4];
    double    GG1;
	double    GG2;
    BOOL      BtnChuliDwon;

    double    Direc[3600];
	double    TempJgBWD[8];
private:
	BOOL m_bIsAutoQK;//自动去缺口
	int ratio1;
	CRect rect1;
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

	double DispMaxdirecMZC;     //最小区域法评定圆度误差的参数信息
	double DispMindirecMZC;
	double MZCDX;
	double MZCDY;
	double MZCEcc;
	double MZCEccPos;
	CString m_MZCRONT;

	double    m_BWD[7];
	CString   m_Wa;	//波纹度显示
	CString   m_Wc;	//波纹度显
	CString   m_Wp;	//波纹度显
	CString   m_Wv;	//波纹度显示
	CString   m_Wt;	//波纹度显
	CString   m_Wq;	//波纹度显
    CString   m_Wwm;	//波纹度显

protected:
	CRect      m_rect;
	double     m_Middle;
	double     m_OutIn;

public:
	double  dRONT;
	double  dEcc;
	double  dEccPos;
	int	    m_endposition;
	int	    m_splitnumber;
	int	    m_startposition;
	double  theta1;
	double  theta2;
	double  alpha1;
	double  alpha2;
	BOOL    flagmanchuli;
	int     FlagMove;
	BOOL    Flagxzhou;
	int     m_IndexStart;
	int     m_IndexEnd;
	int     m_Flagcircle;

	CTime   m_time;

public:
	void canshu();
	void DrawCircleMZC();
	void MZCyuandu(double *Soudata);
	void DrawCircleMIC();
	void MCCyuandu(double *Soudata);
	void MICyuandu(double *Soudata);
	void DrawCircleMCC();
	double ratio;
	double flagAmpscale;
	double m_AmpScale;
	double m_ModeChoose;
	CBitmap memBitmap;
	CBitmap* pOldBmp;
	void DrawGrid3Frequency();
	void DrawBaogao();
	void DrawFrequency();
	int     LenDataJM;
	int     m_LBtnJM;
	int     m_Dot;
	CString pathJM;
	BOOL m_BOOLSegmentprocess;

	double m_maxsplit[100];
	double m_minsplit[100];
	double m_PV[100];
	double XRf4[3601];
	int Frepointi;
	double Frepointx;
	double Frepointy;
	BOOL BoolButtondown;
	int  m_Intstart;
	int  m_Intend;
	BOOL FlagFrequency;

	double bogao[RecCount];
	double weizhi[RecCount];
	int DispTempFnumber;
	BOOL FlagBogao;
	CPoint    m_ptEnd;
	CPoint    m_ptOrigin;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJMAnalyse)
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
	void PrintCircleMZC();
	void PrintCircleMIC();
	void PrintCircleMCC();
	
	void PrintJMofYZD();
	void PrintDrawGrid3Frequency();
	void PrintSegmentationprocess();
	CFont newFont;
	int m_penScale;
	void ReadDataFromFile();
	virtual ~CJMAnalyse();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CJMAnalyse)
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBtnchuli();
	afx_msg void OnBtnenable();
	afx_msg void OnBtnresetdeal();
	afx_msg void OnBtnfenduanchuli();
	afx_msg void OnBtnyuanduchuli();
	afx_msg void OnBtndelete();
	afx_msg void OnBtnbgfx();
	afx_msg void OnBtnppfx();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPrint();
	afx_msg void OnAmplifyScale();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    void DrawJMofYZD();
	void DrawGrid2();
	void DrawGride1();
    void BWDANA(double *Direc);
	void Segmentationprocess();
    void DynamicDrawCircleJM( int startPosition, int endPosition);
	void SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr);
	void DrawFilter (int  FilterMode ,double *pMem,double *drawdata);
	void WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata);
	void ChangeValueOfSelectJM(CString path,int startPosition, int endPosition, BOOL isSelected);
	void DrawingCleanAndResetJM(CString path, BOOL isSelected);
	int  DeletePartOfFile(CString path, int NumOfCircle,BOOL isSaveTheFormer);
    void SubQKDataChuli(CString path,int JM,int Number, BOOL AutoOrManChuli, double *Soudata, double *Resdata,int m_IndexStart, int m_IndexEnd);
 };

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JMANALYSE_H__9072811D_FE78_4457_AFB8_9A0464B69F85__INCLUDED_)

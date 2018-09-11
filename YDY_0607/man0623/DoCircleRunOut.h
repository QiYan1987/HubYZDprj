#if !defined(AFX_DOCIRCLERUNOUT_H__845532B9_1CBB_4FBD_925D_91DF2E39983B__INCLUDED_)
#define AFX_DOCIRCLERUNOUT_H__845532B9_1CBB_4FBD_925D_91DF2E39983B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoCircleRunOut.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoCircleRunOut form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#include "ListCtrlCl.h"
#include "PropertyDlg.h"	// Added by ClassView
#endif

class CDoCircleRunOut : public CFormView
{
protected:
	CDoCircleRunOut();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoCircleRunOut)

// Form Data
public:
	//{{AFX_DATA(CDoCircleRunOut)
	enum { IDD = IDD_FORMVIEW_CircleRunOut };
	CStatic	m_Edit_CircleRunOut;
	//}}AFX_DATA
	shuju m_data[3600];
// Attributes
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoCircleRunOut)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL
private:
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
	
		CRect     rect1;              // �洢��ͼ�ؼ��Ļ�ͼ����
		CDC       *pDC;                 // �ؼ�����Ļ��ͼ�豸ָ��
		CDC       memDC;                // �ڴ��ͼ�豸
		CBitmap   memBitmap;        // �����ڴ��ͼ��λͼ  
		CBitmap   *pOldBmp;         // ���ݾɵ�λͼָ�� 
		CWnd     *pWnd1;              // ��ͼ�ؼ���
        CRect    rect_ctr; 
      	
		double DispMaxdirecMZC;     //��С��������Բ�����Ĳ�����Ϣ
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
        CString   m_Wa;	//���ƶ���ʾ
        CString   m_Wc;	//���ƶ���
        CString   m_Wp;	//���ƶ���
        CString   m_Wv;	//���ƶ���ʾ
        CString   m_Wt;	//���ƶ���
        CString   m_Wq;	//���ƶ���
        CString   m_Wwm;	//���ƶ���
		int      flag_bg;
	protected:
		CRect m_rect;
		double m_Middle;
	    double m_OutIn;
		int	m_penScale;

	public:
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
		int	m_endposition;
		int	m_splitnumber;
		int	m_startposition;
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

// Implementation
protected:
	virtual ~CDoCircleRunOut();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoCircleRunOut)
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtndisable();
	afx_msg void OnBtnenable();
	afx_msg void OnBtnfenduanchuli();
	afx_msg void OnBtnppfx();
	afx_msg void OnBtnresetdeal();
	afx_msg void OnBtnyuanduchuli();
	afx_msg void OnBtnchuli();
	afx_msg void OnBtnbgfx();
	//}}AFX_MSG
	void DrawCircle();
	void MZCyuandu();
    void MCCyuandu();
    void MICyuandu();
    void ReadDataFromFile();
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

#endif // !defined(AFX_DOCIRCLERUNOUT_H__845532B9_1CBB_4FBD_925D_91DF2E39983B__INCLUDED_)

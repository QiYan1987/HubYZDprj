#if !defined(AFX_DOSTRAIGHTNESS_H__AA4DA221_4BC7_4613_AD2C_280DB3D80EE1__INCLUDED_)
#define AFX_DOSTRAIGHTNESS_H__AA4DA221_4BC7_4613_AD2C_280DB3D80EE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoStraightness.h : header file
//直线度类

/////////////////////////////////////////////////////////////////////////////
// CDoStraightness form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDoStraightness : public CFormView
{
protected:
	CDoStraightness();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoStraightness)

// Form Data
public:
	//{{AFX_DATA(CDoStraightness)
	enum { IDD = IDD_FORMVIEW3 };
	CStatic	m_editStraightness;
	//}}AFX_DATA

// Attributes
public:
	shuju m_data[3600];
	
// Operations
public:
	CBitmap memBitmap;
	CBitmap* pOldBmp;
	CDC mDC;
	
	void Straightalgorithm();
	void DrawingCleanAndReset(CString path, BOOL isSelected);
	void ChangeValueOfSelect(CString path, int startPosition, int endPosition, BOOL isSelected);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoStraightness)
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
	int m_penScale;
	void ReadDataFromFile();
	void SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr);
	virtual ~CDoStraightness();
	void WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoStraightness)
	afx_msg void OnDestroy();
	afx_msg void OnSelectbutton();
	afx_msg void OnAnalysisbutton();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void Onresetzxd();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect rect;
	BOOL   m_bDraw;
	CPoint m_StartPoint;
	CPoint m_LastEndPoint;
	CPoint m_MovePoint;
	CPoint m_mouseOrigin;
	CPoint m_mouseFinish;
	double m_max;
	double m_min;  
	double sum[3607];
	double pointer[3600];
	int m_startPosition;
	int m_endPosition;
	BOOL m_lineselect;
	BOOL m_lineanalysis;
	double m_pmax;
	double m_pmin;
	int m_paverage;
    double GResult;
	BOOL m_LButtonUp;
	double m_extendzxd;
	double G1;
	double G2;
	double m_Height;
	CTime  m_time;
	double xL1[3600];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOSTRAIGHTNESS_H__AA4DA221_4BC7_4613_AD2C_280DB3D80EE1__INCLUDED_)

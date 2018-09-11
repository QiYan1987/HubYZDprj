#if !defined(AFX_DOPLANENESS_H__419DC6F7_7C76_41E2_9BF4_4DEBD9A95E77__INCLUDED_)
#define AFX_DOPLANENESS_H__419DC6F7_7C76_41E2_9BF4_4DEBD9A95E77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoPlaneness.h : header file
//平面度类


/////////////////////////////////////////////////////////////////////////////
// CDoPlaneness form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif



class CDoPlaneness : public CFormView
{
protected:
	CDoPlaneness();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoPlaneness)

// Form Data
public:
	//{{AFX_DATA(CDoPlaneness)
	enum { IDD = IDD_FORMVIEW5 };
	CStatic	m_editPlaness;
	//}}AFX_DATA

// Attributes
public:
	CPoint  pt2Start;
	CPoint  pt2End;

	double  G1;
	double  G2;
	CTime	m_t;
    CString m_strpmd;
	CString m_strlvbo;
	CString m_strMethod;
	double  m_pmd;
	double  GResult[3];
	double  Resdata[3600];

// Operations
public:
	int	CirEvalue;//评定算法
	int m_intNumOfPlaneness;
	int       m_Flagcircle;
	int  FilterMode; 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoPlaneness)
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
	virtual ~CDoPlaneness();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoPlaneness)
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChuli();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPrint();
	//}}AFX_MSG
	void  WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata);
	void  SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr);
    void SubQKDataChuli(CString path,int Number, double *Resdata,BOOL GManCuliQkFlag,int JM,int Totaldot);
	DECLARE_MESSAGE_MAP()
private:
	shuju0 m_data[3601];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOPLANENESS_H__419DC6F7_7C76_41E2_9BF4_4DEBD9A95E77__INCLUDED_)

#if !defined(AFX_DOADJUSTPOSITION_H__DA9008CC_860B_45E1_987C_193CE4B5EF17__INCLUDED_)
#define AFX_DOADJUSTPOSITION_H__DA9008CC_860B_45E1_987C_193CE4B5EF17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoAdjustPosition.h : header file
//�Զ����Ļ��Զ���ƽ��ͼ��

/////////////////////////////////////////////////////////////////////////////
// CDoAdjustPosition form view

#ifndef __AFXEXT_H__
#include "PropertyDlg.h"	// Added by ClassView
#include <afxext.h>
#endif

class CDoAdjustPosition : public CFormView
{
protected:
	CDoAdjustPosition();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoAdjustPosition)

// Form Data
public:
	//{{AFX_DATA(CDoAdjustPosition)
	enum { IDD = IDD_FORMVIEW_AdjustPosition };
	CStatic	m_StaticAdjustPosition;
	//}}AFX_DATA
// Attributes
private:
	CString   m_strdEcc;
	CString   m_strdEccPos;
	int      fpdata[3600];
	double   datacir[3600];
	
	CRect     rect1;              // �洢��ͼ�ؼ��Ļ�ͼ����
	CDC       *pDC;                 // �ؼ�����Ļ��ͼ�豸ָ��
	CDC       memDC;                // �ڴ��ͼ�豸
	CBitmap   memBitmap;        // �����ڴ��ͼ��λͼ  
	CBitmap   *pOldBmp;         // ���ݾɵ�λͼָ�� 
	CWnd     *pWnd1;              // ��ͼ�ؼ���
protected:
	double m_Middle;
	double m_OutIn;
	
public:
	void DrawGride1();
	int   CirEvalue;
	int   m_Intstep;
	double G2;
	double G1;
	CBrush m_brush;
	double dEcc;
	double dEccPos;
	int	m_endposition;
	int	m_splitnumber;
	int	m_startposition;
	
	double m_maxsplit[100];
	double m_minsplit[100];
	double m_PV[100];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoAdjustPosition)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDoAdjustPosition();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoAdjustPosition)
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	void DrawCircle();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOADJUSTPOSITION_H__DA9008CC_860B_45E1_987C_193CE4B5EF17__INCLUDED_)

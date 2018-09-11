#if !defined(AFX_LISTCTRLCL_H__428927AC_AF9C_4044_BD7D_98546EF6E83C__INCLUDED_)
#define AFX_LISTCTRLCL_H__428927AC_AF9C_4044_BD7D_98546EF6E83C__INCLUDED_

#include "HeaderCtrlCl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlCl.h : header file
//
#include "HeaderCtrlCl.h"
/////////////////////////////////////////////////////////////////////////////
// CListCtrlCl window

class CListCtrlCl : public CListCtrl
{
// Construction
public:
	CListCtrlCl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlCl)
	//}}AFX_VIRTUAL

// Implementation
public:
	CPtrList m_ptrListItem;
	CPtrList m_ptrListCol;
	int m_nRowHeight;
	CPtrList m_ItemTextColor;
	CHeaderCtrlCl m_Header;
	int m_fontWith;
	int m_fontHeight;
	CPtrList m_colTextColor;
	COLORREF m_color;
	BOOL SetTextColor(COLORREF cr);
	void SetRowHeigt(int nHeight);
	void SetItemTextColor(int col,int row,COLORREF color);
	void SetItemColor(int col,int row,COLORREF color);
	void SetHeaderTextColor(COLORREF color);
	void SetHeaderHeight(float Height);
	void SetHeaderFontHW(int nHeight,int nWith);
	void SetHeaderBKColor(int R, int G, int B, int Gradient);
	void SetFontHW(int nHeight,int nWith);
	void SetColTextColor(int col,COLORREF color);
	void SetColColor(int col,COLORREF color);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	bool FindItemTextColor(int col,int row,COLORREF &color);
	bool FindItemColor(int col,int row,COLORREF &color);
	bool FindColTextColor(int col,COLORREF &color);
	bool FindColColor(int col ,COLORREF &color);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual ~CListCtrlCl();

	// Generated message map functions
protected:
	virtual void PreSubclassWindow();
	//{{AFX_MSG(CListCtrlCl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLCL_H__428927AC_AF9C_4044_BD7D_98546EF6E83C__INCLUDED_)

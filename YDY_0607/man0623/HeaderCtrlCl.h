#if !defined(AFX_HEADERCTRLCL_H__3DB34CA0_C7B1_43FC_B795_29775760044B__INCLUDED_)
#define AFX_HEADERCTRLCL_H__3DB34CA0_C7B1_43FC_B795_29775760044B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HeaderCtrlCl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlCl window

class CHeaderCtrlCl : public CHeaderCtrl
{
// Construction
public:
	CHeaderCtrlCl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderCtrlCl)
	//}}AFX_VIRTUAL

// Implementation
public:
	CStringArray m_HChar;
	CString m_Format;
	int m_R;
	int m_G;
	int m_B;
	int m_Gradient;	// 画立体背景，渐变系数
	float m_Height;  //表头高度，这是倍数,
	int m_fontHeight; //字体高度
	int m_fontWith;   //字体宽度
	COLORREF m_color;
	afx_msg void OnPaint();
	virtual ~CHeaderCtrlCl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHeaderCtrlCl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEADERCTRLCL_H__3DB34CA0_C7B1_43FC_B795_29775760044B__INCLUDED_)

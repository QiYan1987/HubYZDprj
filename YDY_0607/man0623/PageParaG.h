#if !defined(AFX_PAGEPARAG_H__D2235E96_A849_46A9_906F_7DA309267567__INCLUDED_)
#define AFX_PAGEPARAG_H__D2235E96_A849_46A9_906F_7DA309267567__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageParaG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageParaG dialog

class CPageParaG : public CDialog
{
// Construction
public:
	CPageParaG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageParaG)
	enum { IDD = IDD_PAGEPARA_G };
	double	m_DG1;
	double	m_DG2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageParaG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageParaG)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEPARAG_H__D2235E96_A849_46A9_906F_7DA309267567__INCLUDED_)

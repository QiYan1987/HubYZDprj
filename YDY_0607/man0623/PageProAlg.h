#if !defined(AFX_PAGEPROALG_H__FE4E94E5_506B_4FBE_AB24_72F31BC772C2__INCLUDED_)
#define AFX_PAGEPROALG_H__FE4E94E5_506B_4FBE_AB24_72F31BC772C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageProAlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageProAlg dialog

class CPageProAlg : public CDialog
{
// Construction
public:
	CPageProAlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageProAlg)
	enum { IDD = IDD_PAGEPROALG };
	CComboBox	m_ComboAlg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageProAlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageProAlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEPROALG_H__FE4E94E5_506B_4FBE_AB24_72F31BC772C2__INCLUDED_)

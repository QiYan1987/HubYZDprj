// Wilson6.h : main header file for the WILSON6 application
//

#if !defined(AFX_WILSON6_H__C8312CFD_C322_4F4C_B06B_E621E3C1D1D4__INCLUDED_)
#define AFX_WILSON6_H__C8312CFD_C322_4F4C_B06B_E621E3C1D1D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWilson6App:
// See Wilson6.cpp for the implementation of this class
//
class CWilson6App : public CWinApp
{
public:
	CWilson6App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWilson6App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HMENU m_hMDIMenu;
	HMENU m_hMenu;
	HACCEL m_hMDIAccel;

public:

	void OnPrint();
	//{{AFX_MSG(CWilson6App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WILSON6_H__C8312CFD_C322_4F4C_B06B_E621E3C1D1D4__INCLUDED_)

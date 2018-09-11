#if !defined(AFX_DLGAJUSTPINGJING_H__360972CE_B195_4E81_9486_7449C5F43597__INCLUDED_)
#define AFX_DLGAJUSTPINGJING_H__360972CE_B195_4E81_9486_7449C5F43597__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAjustPingjing.h : header file
//
#include "PageTargetEccentricity.h"
#include "PageTimes.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgAjustPingjing dialog

class CDlgAjustPingjing : public CDialog
{
// Construction
public:

	CDlgAjustPingjing(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAjustPingjing)
	enum { IDD = IDD_DIALOG_AdjustPingjing };
	double	m_dDistance;
	double	m_dFastMoveDistance;
	UINT	m_intTimes;
	double	m_dTargetEccentricity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAjustPingjing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAjustPingjing)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAJUSTPINGJING_H__360972CE_B195_4E81_9486_7449C5F43597__INCLUDED_)

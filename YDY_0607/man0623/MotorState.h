#if !defined(AFX_MOTORSTATE_H__995A2E27_CCD7_4E9B_B6F6_D03D93A4C05C__INCLUDED_)
#define AFX_MOTORSTATE_H__995A2E27_CCD7_4E9B_B6F6_D03D93A4C05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MotorState.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMotorState dialog

class CMotorState : public CDialog
{
// Construction
public:
	CBitmap m_cBmp;
	CMotorState(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMotorState)
	enum { IDD = IDD_MOTORSTATE };
	CStatic	m_ctrBmp12;
	CStatic	m_ctrBmp11;
	CStatic	m_ctrBmp10;
	CStatic	m_ctrBmp9;
	CStatic	m_ctrBmp8;
	CStatic	m_ctrBmp7;
	CStatic	m_ctrBmp6;
	CStatic	m_ctrBmp5;
	CStatic	m_ctrBmp4;
	CStatic	m_ctrBmp3;
	CStatic	m_ctrBmp2;
	CStatic	m_ctrBmp1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotorState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMotorState)
	afx_msg void OnCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTORSTATE_H__995A2E27_CCD7_4E9B_B6F6_D03D93A4C05C__INCLUDED_)

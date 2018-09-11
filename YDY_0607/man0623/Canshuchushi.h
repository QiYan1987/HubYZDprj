#if !defined(AFX_CANSHUCHUSHI_H__9C7F1DDA_74D7_4C07_8BB7_8816482290CB__INCLUDED_)
#define AFX_CANSHUCHUSHI_H__9C7F1DDA_74D7_4C07_8BB7_8816482290CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Canshuchushi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCanshuchushi dialog

class CCanshuchushi : public CDialog
{
// Construction
public:
	CCanshuchushi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCanshuchushi)
	enum { IDD = IDD_DIALOG_CanShuChuLi };
	double	m_B1x;
	double	m_P1x;
	double	m_P1y;
	double	m_P1z;
	double	m_x0;
	double	m_y0;
	double	m_H0;
	double	m_Angle;
	double	m_LIMIT;
	double	m_B1y;
	double	m_B1z;
	double	m_B2x;
	double	m_B2y;
	double	m_B2z;
	double	m_B3x;
	double	m_B3y;
	double	m_B3z;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCanshuchushi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCanshuchushi)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CANSHUCHUSHI_H__9C7F1DDA_74D7_4C07_8BB7_8816482290CB__INCLUDED_)

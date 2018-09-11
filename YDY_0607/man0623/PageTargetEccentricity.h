#if !defined(AFX_PAGETARGETECCENTRICITY_H__1DBEA2D3_D1DC_40AA_9C32_2873C21BA5B3__INCLUDED_)
#define AFX_PAGETARGETECCENTRICITY_H__1DBEA2D3_D1DC_40AA_9C32_2873C21BA5B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTargetEccentricity.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageTargetEccentricity dialog

class CPageTargetEccentricity : public CDialog
{
// Construction
public:
	CPageTargetEccentricity(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageTargetEccentricity)
	enum { IDD = IDD_PAGETARGETECCENTRICITY };
	double	m_dTargetEccentricity;
	CString	m_unitText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageTargetEccentricity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageTargetEccentricity)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETARGETECCENTRICITY_H__1DBEA2D3_D1DC_40AA_9C32_2873C21BA5B3__INCLUDED_)

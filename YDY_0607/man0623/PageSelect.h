#if !defined(AFX_PAGESELECT_H__143DAB6B_2057_472C_9AF4_7216F5BC1EA6__INCLUDED_)
#define AFX_PAGESELECT_H__143DAB6B_2057_472C_9AF4_7216F5BC1EA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageSelect dialog

class CPageSelect : public CDialog
{
// Construction
public:
	CPageSelect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageSelect)
	enum { IDD = IDD_PAGESELECT };
	CString	m_unitText;
	CString	m_strVelocity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageSelect)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESELECT_H__143DAB6B_2057_472C_9AF4_7216F5BC1EA6__INCLUDED_)

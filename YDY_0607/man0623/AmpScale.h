#if !defined(AFX_AMPSCALE_H__4DD382C0_1F61_4F4B_B544_E7238A5A6C13__INCLUDED_)
#define AFX_AMPSCALE_H__4DD382C0_1F61_4F4B_B544_E7238A5A6C13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AmpScale.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAmpScale dialog

class CAmpScale : public CDialog
{
// Construction
public:		
	int m_AmpScale;
	CAmpScale(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAmpScale)
	enum { IDD = IDD_DIALOG_AmpScale };
	CEdit	m_ControlEdit2;
	CEdit	m_ControlEdit;
	int		m_ModeChoose;
	int		m_DefaultAmpscale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAmpScale)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAmpScale)
	virtual void OnOK();
	afx_msg void OnRadio1();
	afx_msg void OnRadio3();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMPSCALE_H__4DD382C0_1F61_4F4B_B544_E7238A5A6C13__INCLUDED_)

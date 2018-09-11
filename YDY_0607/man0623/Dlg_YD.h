#if !defined(AFX_DLG_YD_H__4E6F738D_4824_4FCE_B6A4_83EA49D99B58__INCLUDED_)
#define AFX_DLG_YD_H__4E6F738D_4824_4FCE_B6A4_83EA49D99B58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_YD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_YD dialog

class CDlg_YD : public CDialog
{
// Construction
public:

	CDlg_YD(CWnd* pParent = NULL);   // standard constructor
	int m_fG11cursel;//µµÎ»Ñ¡Ôñ
	// Dialog Data
	//{{AFX_DATA(CDlg_YD)
	enum { IDD = IDD_DIALOG_YD };
	CString	m_name1;
	//CString m_name;
	CTime m_time;
	BOOL	m_bPre;
	float	m_PositionAway;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_YD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_YD)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_YD_H__4E6F738D_4824_4FCE_B6A4_83EA49D99B58__INCLUDED_)

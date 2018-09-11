#if !defined(AFX_DLGMACHINEINF_H__F6D0CA96_8C1E_4657_8C89_69C37C684137__INCLUDED_)
#define AFX_DLGMACHINEINF_H__F6D0CA96_8C1E_4657_8C89_69C37C684137__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMachineInf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMachineInf dialog

class CDlgMachineInf : public CDialog
{
// Construction
public:
	CDlgMachineInf(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMachineInf)
	enum { IDD = IDD_DIALOG_MACHINEINF };
	CString	m_strMachineModel;
	CString	m_strIndent;
	CString	m_strInspector;
	CString	m_strMachineName;
	CString	m_strOperatorName;
	CString	m_strProcess;
	CString	m_strWorkpieceModel;
	CString	m_strWorkpieceNum;
	CString	m_strCompanyName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMachineInf)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMachineInf)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMACHINEINF_H__F6D0CA96_8C1E_4657_8C89_69C37C684137__INCLUDED_)

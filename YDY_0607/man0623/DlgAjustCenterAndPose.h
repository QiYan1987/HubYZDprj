#if !defined(AFX_DLGAJUSTCENTERANDPOSE_H__C8D90835_9A80_4733_BDEC_E6EA2500B752__INCLUDED_)
#define AFX_DLGAJUSTCENTERANDPOSE_H__C8D90835_9A80_4733_BDEC_E6EA2500B752__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAjustCenterAndPose.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAjustCenterAndPose dialog

class CDlgAjustCenterAndPose : public CDialog
{
// Construction
public:

	CDlgAjustCenterAndPose(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAjustCenterAndPose)
	enum { IDD = IDD_DIALOG_AdjustCenterAndPose };
	double	m_dDistance;
	double	m_dFastMoveDistance;
	double	m_dHeight;
	double	m_dHTargetEccentricity;
	UINT	m_intTimes;
	double	m_dLTargetEccentricity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAjustCenterAndPose)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAjustCenterAndPose)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAJUSTCENTERANDPOSE_H__C8D90835_9A80_4733_BDEC_E6EA2500B752__INCLUDED_)

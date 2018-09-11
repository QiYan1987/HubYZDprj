// Dlg_QK.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "Dlg_QK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_QK dialog


CDlg_QK::CDlg_QK(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_QK::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_QK)
	m_fQK = 0.12;
	//}}AFX_DATA_INIT
}


void CDlg_QK::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_QK)
	DDX_Text(pDX, IDC_EDIT1, m_fQK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_QK, CDialog)
	//{{AFX_MSG_MAP(CDlg_QK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_QK message handlers

void CDlg_QK::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}

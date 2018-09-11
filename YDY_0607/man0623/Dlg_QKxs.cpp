// Dlg_QKxs.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "Dlg_QKxs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_QKxs dialog


CDlg_QKxs::CDlg_QKxs(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_QKxs::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_QKxs)
	m_fQKxs = 0.12;
	//}}AFX_DATA_INIT
}


void CDlg_QKxs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_QKxs)
	DDX_Text(pDX, IDC_EDIT1, m_fQKxs);
	DDV_MinMaxFloat(pDX, m_fQKxs, 0.f, 1.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_QKxs, CDialog)
	//{{AFX_MSG_MAP(CDlg_QKxs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_QKxs message handlers

void CDlg_QKxs::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}

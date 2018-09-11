// DlgHands.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DlgHands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHands dialog


CDlgHands::CDlgHands(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHands::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHands)
	//}}AFX_DATA_INIT
	m_cursel=1;
	m_dVelocity=0;
}


void CDlgHands::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHands)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHands, CDialog)
	//{{AFX_MSG_MAP(CDlgHands)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHands message handlers

void CDlgHands::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CComboBox*m_pCombox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	m_cursel= m_pCombox->GetCurSel();
	switch(m_cursel)
	{
	case 0: m_dVelocity=1.0;	break;
	case 1: m_dVelocity=3.0;	break;
	case 2: m_dVelocity=6.0;	break;

	}
	CDialog::OnOK();
}

BOOL CDlgHands::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CComboBox*m_pCombox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	m_pCombox->AddString("1.0mm/s");
	m_pCombox->AddString("3.0mm/s");
	m_pCombox->AddString("6.0mm/s");
	m_pCombox->SetCurSel(m_cursel);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// DlgGongYiSetting.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DlgGongYiSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGongYiSetting dialog


CDlgGongYiSetting::CDlgGongYiSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGongYiSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGongYiSetting)
	m_dCZD = 0.0;
	m_dPMD = 0.0;
	m_dPXD = 0.0;
	m_dTZD = 0.0;
	m_dYD = 0.0;
	m_dYZD = 0.0;
	m_dZXD = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgGongYiSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGongYiSetting)
	DDX_Text(pDX, IDC_EDIT_CZD, m_dCZD);
	DDX_Text(pDX, IDC_EDIT_PMD, m_dPMD);
	DDX_Text(pDX, IDC_EDIT_PXD, m_dPXD);
	DDX_Text(pDX, IDC_EDIT_TZD, m_dTZD);
	DDX_Text(pDX, IDC_EDIT_YD, m_dYD);
	DDX_Text(pDX, IDC_EDIT_YZD, m_dYZD);
	DDX_Text(pDX, IDC_EDIT_ZXD, m_dZXD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGongYiSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgGongYiSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGongYiSetting message handlers

BOOL CDlgGongYiSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGongYiSetting::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}

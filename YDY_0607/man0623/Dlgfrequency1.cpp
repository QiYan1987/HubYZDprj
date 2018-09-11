// Dlgfrequency1.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "Dlgfrequency1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgfrequency1 dialog


CDlgfrequency1::CDlgfrequency1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgfrequency1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgfrequency1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgfrequency1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgfrequency1)
	DDX_Control(pDX, IDC_COMBO2, m_endfrequency);
	DDX_Control(pDX, IDC_COMBO1, m_startfrequency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgfrequency1, CDialog)
	//{{AFX_MSG_MAP(CDlgfrequency1)
	ON_BN_CLICKED(IDC_OK_SAVE, OnOkSave)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgfrequency1 message handlers

void CDlgfrequency1::OnOkSave() 
{
	// TODO: Add your control notification handler code here
	m_Intstart=m_startfrequency.GetCurSel()+2;
	m_Intend=m_endfrequency.GetCurSel()+2;

	CDialog::OnOK();
}

void CDlgfrequency1::OnQuit() 
{
	// TODO: Add your control notification handler code here
		CDialog::OnCancel();
}

BOOL CDlgfrequency1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	 CString strTemp1;
	 int i;
	 for (i=2;i<=500;i++)
	 {
	    strTemp1.Format("%d",i);
		m_startfrequency.InsertString(i-2,strTemp1);
		m_endfrequency.InsertString(i-2,strTemp1);
	 }
	 m_startfrequency.SetCurSel(0);
	 m_endfrequency.SetCurSel(48);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

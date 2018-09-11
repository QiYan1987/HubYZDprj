// Dlgfrequency.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "Dlgfrequency.h"
#include "DoCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgfrequency dialog


CDlgfrequency::CDlgfrequency(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgfrequency::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgfrequency)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgfrequency::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgfrequency)
	DDX_Control(pDX, IDC_COMBO2, m_endfrequency);
	DDX_Control(pDX, IDC_COMBO1, m_startfrequency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgfrequency, CDialog)
	//{{AFX_MSG_MAP(CDlgfrequency)
	ON_BN_CLICKED(IDC_OK_SAVE, OnOkSave)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgfrequency message handlers

void CDlgfrequency::OnOkSave() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	m_Intstart=m_startfrequency.GetCurSel()+2;
	m_Intend=m_endfrequency.GetCurSel()+2;
	CDialog::OnOK();

}

void CDlgfrequency::OnQuit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

BOOL CDlgfrequency::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
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
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

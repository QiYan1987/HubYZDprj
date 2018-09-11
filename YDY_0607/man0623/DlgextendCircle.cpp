// DlgextendCircle.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DlgextendCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgextendCircle dialog


CDlgextendCircle::CDlgextendCircle(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgextendCircle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgextendCircle)
	m_endposition = 0;
	m_splitnumber = 0;
	m_startposition = 0;
	//}}AFX_DATA_INIT
}


void CDlgextendCircle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgextendCircle)
	DDX_Text(pDX, IDC_ENDPOSITION, m_endposition);
	DDV_MinMaxInt(pDX, m_endposition, 0, 360);
	DDX_Text(pDX, IDC_SPLITNUMBER, m_splitnumber);
	DDV_MinMaxInt(pDX, m_splitnumber, 1, 12);
	DDX_Text(pDX, IDC_STARTPOSITION, m_startposition);
	DDV_MinMaxInt(pDX, m_startposition, 0, 360);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgextendCircle, CDialog)
	//{{AFX_MSG_MAP(CDlgextendCircle)
	ON_BN_CLICKED(IDC_OK_SAVE, OnOkSave)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgextendCircle message handlers

void CDlgextendCircle::OnOkSave() 
{
	// TODO: Add your control notification handler code here
	m_startposition=GetDlgItemInt(IDC_STARTPOSITION);
	m_endposition=GetDlgItemInt(IDC_ENDPOSITION);
	m_splitnumber=GetDlgItemInt(IDC_SPLITNUMBER);
	CDialog::OnOK();
}

void CDlgextendCircle::OnQuit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

int CDlgextendCircle::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DoModal();
}



// PageProAlg.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "PageProAlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageProAlg dialog


CPageProAlg::CPageProAlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPageProAlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageProAlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageProAlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageProAlg)
	DDX_Control(pDX, IDC_COMBO1, m_ComboAlg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageProAlg, CDialog)
	//{{AFX_MSG_MAP(CPageProAlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageProAlg message handlers

BOOL CPageProAlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ComboAlg.InsertString(0,"��С���˷�");
	m_ComboAlg.InsertString(1,"��С����");
	m_ComboAlg.InsertString(2,"������Բ");
	m_ComboAlg.InsertString(3,"��С����Բ");
	m_ComboAlg.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



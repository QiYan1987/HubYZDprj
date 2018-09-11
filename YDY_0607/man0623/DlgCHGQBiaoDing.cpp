// DlgCHGQBiaoDing.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DlgCHGQBiaoDing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCHGQBiaoDing dialog


CDlgCHGQBiaoDing::CDlgCHGQBiaoDing(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCHGQBiaoDing::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCHGQBiaoDing)
	m_dMeaValue = 0.0;
	m_dStdValue = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgCHGQBiaoDing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCHGQBiaoDing)
	DDX_Text(pDX, IDC_EDIT_MEAVALUE, m_dMeaValue);
	DDX_Text(pDX, IDC_EDIT_STDVALUE, m_dStdValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCHGQBiaoDing, CDialog)
	//{{AFX_MSG_MAP(CDlgCHGQBiaoDing)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCHGQBiaoDing message handlers

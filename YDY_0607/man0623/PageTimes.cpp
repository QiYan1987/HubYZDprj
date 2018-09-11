// PageTimes.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "PageTimes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageTimes dialog


CPageTimes::CPageTimes(CWnd* pParent /*=NULL*/)
	: CDialog(CPageTimes::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageTimes)
	m_intTimes = 0;
	//}}AFX_DATA_INIT
}


void CPageTimes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageTimes)
	DDX_Text(pDX, IDC_EDIT1, m_intTimes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageTimes, CDialog)
	//{{AFX_MSG_MAP(CPageTimes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageTimes message handlers



// PageInorOut.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "PageInorOut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageInorOut dialog


CPageInorOut::CPageInorOut(CWnd* pParent /*=NULL*/)
	: CDialog(CPageInorOut::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageInorOut)
	m_IntInOrOut = -1;
	//}}AFX_DATA_INIT
}


void CPageInorOut::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageInorOut)
	DDX_Radio(pDX, IDC_RADIO1, m_IntInOrOut);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageInorOut, CDialog)
	//{{AFX_MSG_MAP(CPageInorOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageInorOut message handlers



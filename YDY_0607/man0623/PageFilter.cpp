// PageFilter.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "PageFilter.h"
#include "DoCircle.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageFilter dialog


CPageFilter::CPageFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CPageFilter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageFilter)
	
	m_IntFilter =1;
	//}}AFX_DATA_INIT

}


void CPageFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageFilter)
	DDX_Radio(pDX, IDC_RADIO1, m_IntFilter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageFilter, CDialog)
	//{{AFX_MSG_MAP(CPageFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageFilter message handlers





































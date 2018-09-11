// PageParaG.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "PageParaG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageParaG dialog


CPageParaG::CPageParaG(CWnd* pParent /*=NULL*/)
	: CDialog(CPageParaG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageParaG)
	m_DG1 = 0.0;
	m_DG2 = 0.0;
	//}}AFX_DATA_INIT
}


void CPageParaG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageParaG)
	DDX_Text(pDX, IDC_EDIT1, m_DG1);
	DDX_Text(pDX, IDC_EDIT2, m_DG2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageParaG, CDialog)
	//{{AFX_MSG_MAP(CPageParaG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageParaG message handlers




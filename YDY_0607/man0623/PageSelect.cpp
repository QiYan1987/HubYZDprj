// PageSelect.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "PageSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSelect dialog


CPageSelect::CPageSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CPageSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageSelect)
	m_unitText = _T("");
	m_strVelocity = _T("");
	//}}AFX_DATA_INIT
}


void CPageSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSelect)
	DDX_Text(pDX, IDC_UNITTEXT, m_unitText);
	DDX_CBString(pDX, IDC_COMBO1, m_strVelocity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSelect, CDialog)
	//{{AFX_MSG_MAP(CPageSelect)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSelect message handlers

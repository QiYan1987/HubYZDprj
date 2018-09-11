// PageEdit.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "PageEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageEdit dialog


CPageEdit::CPageEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CPageEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageEdit)
	m_dEdit = 0.0;
	m_unitText = _T("");
	m_nameText = _T("");
	//}}AFX_DATA_INIT
}


void CPageEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageEdit)
	DDX_Text(pDX, IDC_EDIT1, m_dEdit);
	DDX_Text(pDX, IDC_UNITTEXT, m_unitText);
	DDX_Text(pDX, IDC_NAMETEXT, m_nameText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageEdit, CDialog)
	//{{AFX_MSG_MAP(CPageEdit)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageEdit message handlers

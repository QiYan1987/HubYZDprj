// DlgZuobiao.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DlgZuobiao.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgZuobiao dialog


CDlgZuobiao::CDlgZuobiao(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZuobiao::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgZuobiao)
	m_fdaogui = 0.0f;
	m_flizhu = 0.0f;
	m_dgxishu = 0.0f;
	m_lzxishu = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgZuobiao::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgZuobiao)
	DDX_Text(pDX, IDC_EDIT_Daogui, m_fdaogui);
	DDX_Text(pDX, IDC_EDIT_Lizhu, m_flizhu);
	DDX_Text(pDX, IDC_DGXISHU, m_dgxishu);
	DDX_Text(pDX, IDC_LZXISHU, m_lzxishu);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgZuobiao, CDialog)
	//{{AFX_MSG_MAP(CDlgZuobiao)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgZuobiao message handlers

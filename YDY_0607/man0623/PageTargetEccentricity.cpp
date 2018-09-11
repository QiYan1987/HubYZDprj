// PageTargetEccentricity.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "PageTargetEccentricity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageTargetEccentricity dialog


CPageTargetEccentricity::CPageTargetEccentricity(CWnd* pParent /*=NULL*/)
	: CDialog(CPageTargetEccentricity::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageTargetEccentricity)
	m_dTargetEccentricity = 0.0;
	m_unitText = _T("");
	//}}AFX_DATA_INIT
}


void CPageTargetEccentricity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageTargetEccentricity)
	DDX_Text(pDX, IDC_EDIT1, m_dTargetEccentricity);
	DDX_Text(pDX, IDC_UNITTEXT, m_unitText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageTargetEccentricity, CDialog)
	//{{AFX_MSG_MAP(CPageTargetEccentricity)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageTargetEccentricity message handlers



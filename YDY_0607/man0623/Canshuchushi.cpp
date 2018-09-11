// Canshuchushi.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "Canshuchushi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCanshuchushi dialog


CCanshuchushi::CCanshuchushi(CWnd* pParent /*=NULL*/)
	: CDialog(CCanshuchushi::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCanshuchushi)
	m_B1x = 0.0;
	m_P1x = 0.0;
	m_P1y = 0.0;
	m_P1z = 0.0;
	m_x0 = 0.0;
	m_y0 = 0.0;
	m_H0 = 0.0;
	m_Angle = 0.0;
	m_LIMIT = 0.0;
	m_B1y = 0.0;
	m_B1z = 0.0;
	m_B2x = 0.0;
	m_B2y = 0.0;
	m_B2z = 0.0;
	m_B3x = 0.0;
	m_B3y = 0.0;
	m_B3z = 0.0;
	//}}AFX_DATA_INIT
}


void CCanshuchushi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCanshuchushi)
	DDX_Text(pDX, IDC_EDIT1, m_B1x);
	DDX_Text(pDX, IDC_EDIT10, m_P1x);
	DDX_Text(pDX, IDC_EDIT11, m_P1y);
	DDX_Text(pDX, IDC_EDIT12, m_P1z);
	DDX_Text(pDX, IDC_EDIT13, m_x0);
	DDX_Text(pDX, IDC_EDIT14, m_y0);
	DDX_Text(pDX, IDC_EDIT15, m_H0);
	DDX_Text(pDX, IDC_EDIT18, m_Angle);
	DDX_Text(pDX, IDC_EDIT19, m_LIMIT);
	DDX_Text(pDX, IDC_EDIT2, m_B1y);
	DDX_Text(pDX, IDC_EDIT3, m_B1z);
	DDX_Text(pDX, IDC_EDIT4, m_B2x);
	DDX_Text(pDX, IDC_EDIT5, m_B2y);
	DDX_Text(pDX, IDC_EDIT6, m_B2z);
	DDX_Text(pDX, IDC_EDIT7, m_B3x);
	DDX_Text(pDX, IDC_EDIT8, m_B3y);
	DDX_Text(pDX, IDC_EDIT9, m_B3z);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCanshuchushi, CDialog)
	//{{AFX_MSG_MAP(CCanshuchushi)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCanshuchushi message handlers

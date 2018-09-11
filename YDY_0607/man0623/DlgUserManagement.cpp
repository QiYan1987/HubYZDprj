// DlgUserManagement.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DlgUserManagement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUserManagement dialog


CDlgUserManagement::CDlgUserManagement(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUserManagement::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUserManagement)
	m_strNewName = _T("");
	m_strNewPwd = _T("");
	m_strOldPwd = _T("");
	m_strOldName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgUserManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUserManagement)
	DDX_Text(pDX, IDC_EDITNEWNAME, m_strNewName);
	DDX_Text(pDX, IDC_EDITNEWPWD, m_strNewPwd);
	DDV_MaxChars(pDX, m_strNewPwd, 6);
	DDX_Text(pDX, IDC_EDITOLDPWD, m_strOldPwd);
	DDV_MaxChars(pDX, m_strOldPwd, 6);
	DDX_Text(pDX, IDC_EDITOLDUSENAME, m_strOldName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUserManagement, CDialog)
	//{{AFX_MSG_MAP(CDlgUserManagement)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUserManagement message handlers

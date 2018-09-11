// DlgOneAxisPara1.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DlgOneAxisPara1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOneAxisPara1 dialog


CDlgOneAxisPara1::CDlgOneAxisPara1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOneAxisPara1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOneAxisPara1)
	m_dPosition = 0;
	//}}AFX_DATA_INIT
}


void CDlgOneAxisPara1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOneAxisPara1)
	DDX_Text(pDX, IDC_EDITPOSITION, m_dPosition);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOneAxisPara1, CDialog)
	//{{AFX_MSG_MAP(CDlgOneAxisPara1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOneAxisPara1 message handlers
BOOL CDlgOneAxisPara1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="canshu.ini";
	CString a;
	::GetPrivateProfileString("调整测量","m_cursel","lisi",a.GetBuffer(100),100,strPath);
	m_cursel=atoi(a);
	::GetPrivateProfileString("调整测量","m_dPosition","lisi",a.GetBuffer(100),100,strPath);
	m_dPosition=atof(a);
	CComboBox*m_pCombox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	m_pCombox->AddString("1.0mm/s");
	m_pCombox->AddString("2.0mm/s");
	m_pCombox->AddString("3.0mm/s");
	m_pCombox->SetCurSel(m_cursel);
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgOneAxisPara1::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CComboBox*m_pCombox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	m_cursel= m_pCombox->GetCurSel();
	switch(m_cursel)
	{
	case 0: m_dVelocity=1.0;	break;
	case 1: m_dVelocity=2.0;	break;
	case 2: m_dVelocity=3.0;	break;
	}
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="canshu.ini";
	CString A;
	A.Format("%d",m_cursel);//写到配置文件中
	:: WritePrivateProfileString("调整测量","m_cursel",A,strPath);	
	A.Format("%.3f",m_dPosition);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_dPosition",A,strPath);	
	CDialog::OnOK();
}



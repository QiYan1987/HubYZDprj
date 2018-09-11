// Dlg_pmPXD.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "Dlg_pmPXD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_pmPXD dialog


CDlg_pmPXD::CDlg_pmPXD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_pmPXD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_pmPXD)
	m_bPre = FALSE;
	m_name1 = _T("");
	m_PositionAway = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlg_pmPXD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_pmPXD)
	DDX_Check(pDX, IDC_CHECK1, m_bPre);
	DDX_Text(pDX, IDC_EDIT_pmPXD_Name, m_name1);
	DDX_Text(pDX, IDC_EDIT2, m_PositionAway);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_pmPXD, CDialog)
	//{{AFX_MSG_MAP(CDlg_pmPXD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_pmPXD message handlers

BOOL CDlg_pmPXD::OnInitDialog() 
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
	::GetPrivateProfileString("调整测量","m_fG11cursel_pmPXD","lisi",a.GetBuffer(100),100,strPath);
	m_fG11cursel=atoi(a);
	::GetPrivateProfileString("调整测量","m_bPre_pmPXD","lisi",a.GetBuffer(100),100,strPath);
	m_bPre=atoi(a);
	::GetPrivateProfileString("调整测量","m_PositionAway_pmPXD","lisi",a.GetBuffer(100),100,strPath);
	m_PositionAway=atof(a);


	CComboBox*m_pCombox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	m_pCombox->AddString("1");
	m_pCombox->AddString("2");
	m_pCombox->AddString("3");
	m_pCombox->AddString("4");
	m_pCombox->AddString("5");
	m_pCombox->AddString("6");
	m_pCombox->AddString("7");
	m_pCombox->AddString("8");
	m_pCombox->SetCurSel(m_fG11cursel);
	// TODO: Add extra initialization here
	m_time=CTime::GetCurrentTime();
	//time.GetYear(),time.GetMonth(),time.GetDay()
	CString str;
	str=m_time.Format("%m-%d-%H-%M-%S");
	m_name1+=str;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_pmPXD::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CComboBox*m_pCombox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	m_fG11cursel= m_pCombox->GetCurSel();
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="canshu.ini";
	CString A;
	A.Format("%d",m_fG11cursel);//写到配置文件中
	:: WritePrivateProfileString("调整测量","m_fG11cursel_pmPXD",A,strPath);	
	A.Format("%f",m_PositionAway);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_PositionAway_pmPXD",A,strPath);
	A.Format("%d",m_bPre);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_bPre_pmPXD",A,strPath);
	CDialog::OnOK();
}

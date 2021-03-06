// Dlg_ZXD.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "Dlg_ZXD.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_ZXD dialog


CDlg_ZXD::CDlg_ZXD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_ZXD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_ZXD)
	m_high1 = 0.0f;
	m_name1 = _T("");
	m_PositionAway = 0.0f;
	m_bPre = FALSE;
	m_bBack0 = FALSE;
	//}}AFX_DATA_INIT
}


void CDlg_ZXD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_ZXD)
	DDX_Text(pDX, IDC_EDIT_ZXD_H, m_high1);
	DDV_MinMaxFloat(pDX, m_high1, 1.e-002f, 500.f);
	DDX_Text(pDX, IDC_EDIT_ZXD_Name2, m_name1);
	DDX_Text(pDX, IDC_EDIT2, m_PositionAway);
	DDX_Check(pDX, IDC_CHECK1, m_bPre);
	DDX_Check(pDX, IDC_CHECKBACK, m_bBack0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_ZXD, CDialog)
	//{{AFX_MSG_MAP(CDlg_ZXD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_ZXD message handlers

BOOL CDlg_ZXD::OnInitDialog() 
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
	::GetPrivateProfileString("调整测量","m_fG11cursel_ZXD","lisi",a.GetBuffer(100),100,strPath);
	m_fG11cursel=atoi(a);
	::GetPrivateProfileString("调整测量","m_bPre_ZXD","lisi",a.GetBuffer(100),100,strPath);
	m_bPre=atoi(a);
	::GetPrivateProfileString("调整测量","m_PositionAway_ZXD","lisi",a.GetBuffer(100),100,strPath);
	m_PositionAway=atof(a);
	::GetPrivateProfileString("调整测量","m_bBack0_ZXD","lisi",a.GetBuffer(100),100,strPath);
	m_bBack0=atoi(a);
	::GetPrivateProfileString("调整测量","m_high1_ZXD","lisi",a.GetBuffer(100),100,strPath);
	m_high1=atof(a);
	::GetPrivateProfileString("调整测量","m_cursel_ZXD","lisi",a.GetBuffer(100),100,strPath);
	m_cursel=atoi(a);

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
	
	m_pCombox=(CComboBox*)GetDlgItem(IDC_COMBO2);
	m_pCombox->AddString("0.1mm/s");
	m_pCombox->AddString("0.2mm/s");
//	m_pCombox->AddString("0.5mm/s");
	/*m_pCombox->AddString("4mm/s");*/
	m_pCombox->SetCurSel(m_cursel);
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

void CDlg_ZXD::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
// 	m_name=m_name1;
// 	m_high=m_high1;
	CComboBox*m_pCombox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	m_fG11cursel= m_pCombox->GetCurSel();
	m_pCombox=(CComboBox*)GetDlgItem(IDC_COMBO2);
	m_cursel= m_pCombox->GetCurSel();
	switch(m_cursel)
	{
	case 0: m_Velocity=0.1;	break;
	case 1: m_Velocity=0.2;	break;
	case 2: m_Velocity=0.5;	break;
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
	A.Format("%d",m_fG11cursel);//写到配置文件中
	:: WritePrivateProfileString("调整测量","m_fG11cursel_ZXD",A,strPath);	
	A.Format("%f",m_PositionAway);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_PositionAway_ZXD",A,strPath);
	A.Format("%d",m_bPre);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_bPre_ZXD",A,strPath);
	A.Format("%d",m_bBack0);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_bBack0_ZXD",A,strPath);
	A.Format("%f",m_high1);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_high1_ZXD",A,strPath);
	A.Format("%d",m_cursel);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_cursel_ZXD",A,strPath);
	CDialog::OnOK();
}

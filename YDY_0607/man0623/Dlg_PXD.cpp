// Dlg_PXD.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "Dlg_PXD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_PXD dialog


CDlg_PXD::CDlg_PXD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_PXD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_PXD)
	m_name1 = _T("");
	m_high1 = 0.0f;
	m_bPre = FALSE;
	m_PositionAway = 0.0f;
	m_bBack0 = FALSE;
	//}}AFX_DATA_INIT
}


void CDlg_PXD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_PXD)
	DDX_Text(pDX, IDC_EDIT_PXD_Name, m_name1);
	DDX_Text(pDX, IDC_EDIT_PXD_H, m_high1);
	DDX_Check(pDX, IDC_CHECK1, m_bPre);
	DDX_Text(pDX, IDC_EDIT2, m_PositionAway);
	DDX_Check(pDX, IDC_CHECKBACK, m_bBack0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_PXD, CDialog)
	//{{AFX_MSG_MAP(CDlg_PXD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_PXD message handlers

BOOL CDlg_PXD::OnInitDialog() 
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
	::GetPrivateProfileString("调整测量","m_fG11cursel_PXD","lisi",a.GetBuffer(100),100,strPath);
	m_fG11cursel=atoi(a);
	::GetPrivateProfileString("调整测量","m_bPre_PXD","lisi",a.GetBuffer(100),100,strPath);
	m_bPre=atoi(a);
	::GetPrivateProfileString("调整测量","m_PositionAway_PXD","lisi",a.GetBuffer(100),100,strPath);
	m_PositionAway=atof(a);
	::GetPrivateProfileString("调整测量","m_bBack0_PXD","lisi",a.GetBuffer(100),100,strPath);
	m_bBack0=atoi(a);
	::GetPrivateProfileString("调整测量","m_high1_PXD","lisi",a.GetBuffer(100),100,strPath);
	m_high1=atof(a);
	::GetPrivateProfileString("调整测量","m_cursel_PXD","lisi",a.GetBuffer(100),100,strPath);
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
	m_pCombox->AddString("0.5mm/s");
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

void CDlg_PXD::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
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
	:: WritePrivateProfileString("调整测量","m_fG11cursel_PXD",A,strPath);	
	A.Format("%f",m_PositionAway);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_PositionAway_PXD",A,strPath);
	A.Format("%d",m_bPre);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_bPre_PXD",A,strPath);
	A.Format("%d",m_bBack0);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_bBack0_PXD",A,strPath);
	A.Format("%f",m_high1);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_high1_PXD",A,strPath);
	A.Format("%d",m_cursel);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_cursel_PXD",A,strPath);
	CDialog::OnOK();
}



// DlgAjustCenterAndPose.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DlgAjustCenterAndPose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAjustCenterAndPose dialog


CDlgAjustCenterAndPose::CDlgAjustCenterAndPose(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAjustCenterAndPose::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAjustCenterAndPose)
	m_dDistance = 0.0;
	m_dFastMoveDistance = 0.0;
	m_dHeight = 0.0;
	m_dHTargetEccentricity = 0.0;
	m_intTimes = 0;
	m_dLTargetEccentricity = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgAjustCenterAndPose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAjustCenterAndPose)
	DDX_Text(pDX, IDC_EDIT_DISTANCE, m_dDistance);
	DDX_Text(pDX, IDC_EDIT_FASTMOVEDISTANCE, m_dFastMoveDistance);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_dHeight);
	DDX_Text(pDX, IDC_EDIT_HTARGETECCENTRICITY, m_dHTargetEccentricity);
	DDX_Text(pDX, IDC_EDIT_TIMES, m_intTimes);
	DDX_Text(pDX, IDC_EDIT_LTARGETECCENTRICITY, m_dLTargetEccentricity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAjustCenterAndPose, CDialog)
	//{{AFX_MSG_MAP(CDlgAjustCenterAndPose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAjustCenterAndPose message handlers

BOOL CDlgAjustCenterAndPose::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="canshu.ini";
	CString a;//����CMainframe�����ֵ
	::GetPrivateProfileString("����","m_dFastMoveDistance","lisi",a.GetBuffer(100),100,strPath);
	m_dFastMoveDistance=atof(a);
	::GetPrivateProfileString("����","m_intTimes","lisi",a.GetBuffer(100),100,strPath);
	m_intTimes=atoi(a);
	::GetPrivateProfileString("����","m_dHTargetEccentricity","lisi",a.GetBuffer(100),100,strPath);
	m_dHTargetEccentricity=atof(a);
	::GetPrivateProfileString("����","m_dLTargetEccentricity","lisi",a.GetBuffer(100),100,strPath);
	m_dLTargetEccentricity=atof(a);
	::GetPrivateProfileString("����","m_dDistance","lisi",a.GetBuffer(100),100,strPath);
	m_dDistance=atof(a);
	::GetPrivateProfileString("����","m_dHeight","lisi",a.GetBuffer(100),100,strPath);
	m_dHeight=atof(a);
    UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgAjustCenterAndPose::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="canshu.ini";
	CString A1;                // �����º��ֵת�����ַ�����ʽд��INI�ļ�����
	A1.Format("%f",m_dFastMoveDistance);
	:: WritePrivateProfileString("����","m_dFastMoveDistance",A1,strPath);
	A1.Format("%d",m_intTimes);
	:: WritePrivateProfileString("����","m_intTimes",A1,strPath);
	A1.Format("%f",m_dHTargetEccentricity);
	:: WritePrivateProfileString("����","m_dHTargetEccentricity",A1,strPath);
	A1.Format("%f",m_dLTargetEccentricity);
	:: WritePrivateProfileString("����","m_dLTargetEccentricity",A1,strPath);
	A1.Format("%f",m_dHeight);
	:: WritePrivateProfileString("����","m_dHeight",A1,strPath);
	A1.Format("%f",m_dDistance);
	:: WritePrivateProfileString("����","m_dDistance",A1,strPath);

	CDialog::OnOK();
}


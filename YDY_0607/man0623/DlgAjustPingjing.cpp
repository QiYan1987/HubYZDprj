// DlgAjustPingjing.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DlgAjustPingjing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAjustPingjing dialog


CDlgAjustPingjing::CDlgAjustPingjing(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAjustPingjing::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAjustPingjing)
	m_dDistance = 0.0;
	m_dFastMoveDistance = 0.0;
	m_intTimes = 0;
	m_dTargetEccentricity = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgAjustPingjing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAjustPingjing)
	DDX_Text(pDX, IDC_EDIT_DISTANCE, m_dDistance);
	DDX_Text(pDX, IDC_EDIT_FASTMOVEDISTANCE, m_dFastMoveDistance);
	DDX_Text(pDX, IDC_EDIT_TIMES, m_intTimes);
	DDX_Text(pDX, IDC_EDIT_TARGETECCENTRICITY, m_dTargetEccentricity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAjustPingjing, CDialog)
	//{{AFX_MSG_MAP(CDlgAjustPingjing)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAjustPingjing message handlers



BOOL CDlgAjustPingjing::OnInitDialog() 
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
	CString a;//更新CMainframe里面的值
	::GetPrivateProfileString("参数","m_dFastMoveDistance","lisi",a.GetBuffer(100),100,strPath);
	m_dFastMoveDistance=atof(a);
	::GetPrivateProfileString("参数","m_intTimes","lisi",a.GetBuffer(100),100,strPath);
	m_intTimes=atoi(a);
	::GetPrivateProfileString("参数","m_dDistance1","lisi",a.GetBuffer(100),100,strPath);
	m_dDistance=atof(a);
	::GetPrivateProfileString("参数","m_dTargetEccentricity","lisi",a.GetBuffer(100),100,strPath);
	m_dTargetEccentricity=atof(a);
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgAjustPingjing::OnOK() 
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
	CString A1;                // 将更新后的值转换成字符串形式写进INI文件里面
	A1.Format("%f",m_dFastMoveDistance);
	:: WritePrivateProfileString("参数","m_dFastMoveDistance",A1,strPath);
	A1.Format("%f",m_dTargetEccentricity);
	:: WritePrivateProfileString("参数","m_dTargetEccentricity",A1,strPath);
	A1.Format("%d",m_intTimes);
	:: WritePrivateProfileString("参数","m_intTimes",A1,strPath);
	A1.Format("%f",m_dDistance);//离心距离
	:: WritePrivateProfileString("参数","m_dDistance1",A1,strPath);
	CDialog::OnOK();
}

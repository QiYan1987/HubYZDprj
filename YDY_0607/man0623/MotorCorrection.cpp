// MotorCorrection.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "MotorCorrection.h"
#include "MainFrm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMotorCorrection dialog


CMotorCorrection::CMotorCorrection(CWnd* pParent /*=NULL*/)
	: CDialog(CMotorCorrection::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMotorCorrection)
	m_correctfactor1 = 0.0;
	m_correctfactor2 = 0.0;
	m_correctfactor3 = 0.0;
	m_correctfactor4 = 0.0;
	m_pingjing_factor1 = 0.0;
	m_pingjing_factor2 = 0.0;
	m_pingjing_factor3 = 0.0;
	m_pingjing_factor4 = 0.0;
	nInde=0;
	//}}AFX_DATA_INIT
}


void CMotorCorrection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMotorCorrection)
	DDX_Control(pDX, IDC_COMBO1, m_combox);
	DDX_Text(pDX, IDC_EDIT1, m_correctfactor1);
	DDX_Text(pDX, IDC_EDIT2, m_correctfactor2);
	DDX_Text(pDX, IDC_EDIT3, m_correctfactor3);
	DDX_Text(pDX, IDC_EDIT4, m_correctfactor4);
	DDX_Text(pDX, IDC_EDIT5, m_pingjing_factor1);
	DDX_Text(pDX, IDC_EDIT6, m_pingjing_factor2);
	DDX_Text(pDX, IDC_EDIT7, m_pingjing_factor3);
	DDX_Text(pDX, IDC_EDIT8, m_pingjing_factor4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMotorCorrection, CDialog)
	//{{AFX_MSG_MAP(CMotorCorrection)
	ON_COMMAND(ID_MotorCorrect, OnMotorCorrect)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_apply, Onapply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMotorCorrection message handlers

void CMotorCorrection::OnMotorCorrect() 
{
	// TODO: Add your command handler code here
	
}

void CMotorCorrection::OnSelchangeCombo1() 
{	

	nInde=m_combox.GetCurSel();

	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index);
	index =strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
	//strPath+=".\\canshu.ini";


	if (nInde==0)
	{
		CString a;
		::GetPrivateProfileString("参数","cf[0]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor1=atof(a);// 使对话框显示原来的值
		::GetPrivateProfileString("参数","cf[1]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor2=atof(a);
		::GetPrivateProfileString("参数","cf[2]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor3=atof(a);
		::GetPrivateProfileString("参数","cf[3]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor4=atof(a);
		UpdateData(FALSE);
	}
	else if (nInde==1)
	{
		CString a;
		::GetPrivateProfileString("参数","cf[4]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor1=atof(a);// 使对话框显示原来的值
		::GetPrivateProfileString("参数","cf[5]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor2=atof(a);
		::GetPrivateProfileString("参数","cf[6]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor3=atof(a);
		::GetPrivateProfileString("参数","cf[7]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor4=atof(a);
		UpdateData(FALSE);
	}
	else if (nInde==2)
	{
		CString a;
		::GetPrivateProfileString("参数","cf[8]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor1=atof(a);// 使对话框显示原来的值
		::GetPrivateProfileString("参数","cf[9]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor2=atof(a);
		::GetPrivateProfileString("参数","cf[10]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor3=atof(a);
		::GetPrivateProfileString("参数","cf[11]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor4=atof(a);
		UpdateData(FALSE);
	}
	else if (nInde==3)
	{
		CString a;
		::GetPrivateProfileString("参数","cf[12]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor1=atof(a);// 使对话框显示原来的值
		::GetPrivateProfileString("参数","cf[13]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor2=atof(a);
		::GetPrivateProfileString("参数","cf[14]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor3=atof(a);
		::GetPrivateProfileString("参数","cf[15]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
	m_correctfactor4=atof(a);
		UpdateData(FALSE);
	}
	
	else if (nInde==4)
	{
		CString a;
		::GetPrivateProfileString("参数","cf[16]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor1=atof(a);// 使对话框显示原来的值
		::GetPrivateProfileString("参数","cf[17]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor2=atof(a);
		::GetPrivateProfileString("参数","cf[18]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor3=atof(a);
		::GetPrivateProfileString("参数","cf[19]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor4=atof(a);
		UpdateData(FALSE);
	}
	else if (nInde==5)
	{
		CString a;
		::GetPrivateProfileString("参数","cf[20]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor1=atof(a);// 使对话框显示原来的值
		::GetPrivateProfileString("参数","cf[21]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor2=atof(a);
		::GetPrivateProfileString("参数","cf[22]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor3=atof(a);
		::GetPrivateProfileString("参数","cf[23]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor4=atof(a);
		UpdateData(FALSE);
	}
	else if (nInde==6)
	{
		CString a;
		::GetPrivateProfileString("参数","cf[24]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor1=atof(a);// 使对话框显示原来的值
		::GetPrivateProfileString("参数","cf[25]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor2=atof(a);
		::GetPrivateProfileString("参数","cf[26]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor3=atof(a);
		::GetPrivateProfileString("参数","cf[27]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor4=atof(a);
		UpdateData(FALSE);
	}
	else if (nInde==7)
	{
		CString a;
		::GetPrivateProfileString("参数","cf[28]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor1=atof(a);// 使对话框显示原来的值
		::GetPrivateProfileString("参数","cf[29]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor2=atof(a);
		::GetPrivateProfileString("参数","cf[30]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor3=atof(a);
		::GetPrivateProfileString("参数","cf[31]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor4=atof(a);
		UpdateData(FALSE);
	}
	else if (nInde==8)
	{
		CString a;
		::GetPrivateProfileString("参数","cf[32]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor1=atof(a);// 使对话框显示原来的值
		::GetPrivateProfileString("参数","cf[33]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor2=atof(a);
		::GetPrivateProfileString("参数","cf[34]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor3=atof(a);
		::GetPrivateProfileString("参数","cf[35]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		m_correctfactor4=atof(a);
		UpdateData(FALSE);
	}
}

void CMotorCorrection::Onapply() 
{
// 	TODO: Add your control notification handler code here
// 		CMainFrame *pFrame=GetParentFrame();
		//CView *pView=pFrame->GetActiveView();
// 		pFrame->PostMessage(WM_DIALOG,IDC_apply);
	UpdateData(TRUE);
	
	(CMainFrame*)AfxGetMainWnd()->PostMessage(WM_DIALOG,IDC_apply);
}

void CMotorCorrection::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData(TRUE);
	(CMainFrame*)AfxGetMainWnd()->PostMessage(WM_DIALOG,IDOK);

	
	CDialog::OnOK();
}

void CMotorCorrection::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	(CMainFrame*)AfxGetMainWnd()->PostMessage(WM_DIALOG,IDCANCEL);
	CDialog::OnCancel();
}

BOOL CMotorCorrection::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index);
	index =strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
	//strPath+=".\\canshu.ini";
	m_combox.SetCurSel(0);//////////////////////////////////添加初始化
	CString a;
	::GetPrivateProfileString("参数","cf[0]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
	m_correctfactor1=atof(a);// 使对话框显示原来的值
	::GetPrivateProfileString("参数","cf[1]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
	m_correctfactor2=atof(a);
	::GetPrivateProfileString("参数","cf[2]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
	m_correctfactor3=atof(a);
	::GetPrivateProfileString("参数","cf[3]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
	m_correctfactor4=atof(a);

		::GetPrivateProfileString("参数","m_pingjing_cf[0]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
	 	 m_pingjing_factor1=atof(a);
		 ::GetPrivateProfileString("参数","m_pingjing_cf[1]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
		  m_pingjing_factor2=atof(a);
	 	 ::GetPrivateProfileString("参数","m_pingjing_cf[2]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
	 	 m_pingjing_factor3=atof(a);
	 	 ::GetPrivateProfileString("参数","m_pingjing_cf[3]","lisi",a.GetBuffer(100),100,strPath+".\\canshu.ini");
	     m_pingjing_factor4=atof(a);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

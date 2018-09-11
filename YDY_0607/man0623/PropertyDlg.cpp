// PropertyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "PropertyDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyDlg dialog


CPropertyDlg::CPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertyDlg)
	m_IntFilter = -1;
	//}}AFX_DATA_INIT
}


void CPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyDlg)
	DDX_Control(pDX, IDC_COMBO1, m_ComboAlg);
	DDX_Radio(pDX, IDC_RADIO1, m_IntFilter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyDlg, CDialog)
	//{{AFX_MSG_MAP(CPropertyDlg)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyDlg message handlers

BOOL CPropertyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index);
	index =strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
	strPath+=".\\Test_ini.ini";
	char inBuf[10];
	GetPrivateProfileString ("滤波","参数1",NULL,inBuf,10,strPath);
	m_IntFilter=atoi(inBuf);
	GetPrivateProfileString ("评定算法","参数2",NULL,inBuf,10,strPath);
    m_IntAlg=atoi(inBuf);

	// TODO: Add extra initialization here
	m_ComboAlg.InsertString(0,"最小二乘法");
	m_ComboAlg.InsertString(1,"最小区域法");
	m_ComboAlg.InsertString(2,"最小外接圆");
	m_ComboAlg.InsertString(3,"最大内切圆");
	m_ComboAlg.SetCurSel(m_IntAlg);
	if(m_IntAlg!=0)
	{
		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyDlg::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_IntAlg=m_ComboAlg.GetCurSel();
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index);
	index =strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
	strPath+=".\\Test_ini.ini";
	CString A;
	A.Format("%d",m_IntFilter);		
	WritePrivateProfileString ("滤波","参数1", A, strPath);
	A.Format("%d",m_IntAlg);
	WritePrivateProfileString ("评定算法","参数2",A,strPath);
	CDialog::OnOK();
}

void CPropertyDlg::OnCancel() 
{
	// TODO: Add your control notification handler code here

	CDialog::OnCancel();
}



void CPropertyDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_IntAlg=m_ComboAlg.GetCurSel();
	if(m_IntAlg!=0)
	{
		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		if(m_IntFilter==0||m_IntFilter==1)
			m_IntFilter=4;
		UpdateData(FALSE);
	}
	else
	{
		GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
	}
}

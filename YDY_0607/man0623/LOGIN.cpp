// LOGIN.cpp : implementation file
//

#include "stdafx.h"
#include "Wilson6.h"
#include "LOGIN.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CLOGIN dialog


CLOGIN::CLOGIN(CWnd* pParent /*=NULL*/)
	: CDialog(CLOGIN::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLOGIN)
	m_userName = _T("");
	m_userPwd = _T("111");
	//}}AFX_DATA_INIT
}


void CLOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLOGIN)
	DDX_Text(pDX, IDC_EDIT1, m_userName);
	DDX_Text(pDX, IDC_EDIT2, m_userPwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLOGIN, CDialog)
	//{{AFX_MSG_MAP(CLOGIN)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLOGIN message handlers

BOOL CLOGIN::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowPos(&wndTopMost,-1,-1,-1,-1,SWP_NOMOVE|SWP_NOSIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLOGIN::OnOK() 
{
	// TODO: Add extra validation here
	CString usernewpwd="111";
	CString usernewname;
	std::ofstream fout("userinf.pwd", std::ios::binary);
	fout.write((char*)&usernewname,6*sizeof(char));
	fout.write((char*)&usernewpwd,6*sizeof(char));
	fout.close();
	UpdateData();
	if (!(m_userPwd==usernewpwd&&m_userName==usernewname))
	{	
		MessageBox("信息错误");
		m_userPwd="";
		UpdateData(FALSE);
	}

//     if(!(m_userPwd=="111"))
//     {
// 		MessageBox("信息错误");
// 		m_userPwd="";
// 		UpdateData(FALSE);
// 	}
	else
	CDialog::OnOK();
}

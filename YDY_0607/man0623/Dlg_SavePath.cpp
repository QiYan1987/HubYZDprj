// Dlg_SavePath.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "Dlg_SavePath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_SavePath dialog


CDlg_SavePath::CDlg_SavePath(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_SavePath::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_SavePath)
	m_strPath = _T("");
	//}}AFX_DATA_INIT
}


void CDlg_SavePath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SavePath)
	DDX_Control(pDX, IDC_COMBO1, m_ctrlComBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_SavePath, CDialog)
	//{{AFX_MSG_MAP(CDlg_SavePath)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_SavePath message handlers

void CDlg_SavePath::OnButtonChange() 
{
	// TODO: Add your control notification handler code here
	BROWSEINFO bi;
	char szPathName[MAX_PATH];
	char szTitle[] = "ѡ��·��";
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = GetSafeHwnd();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPathName;
	bi.lpszTitle = szTitle;
	bi.ulFlags = 0x0040 ; 
	CString str;
	CString strDir;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if(idl == NULL)
	{
		strDir= "";
		return;
	}
	SHGetPathFromIDList(idl, str.GetBuffer(MAX_PATH * 2));
	str.ReleaseBuffer();
	if(str != "" && str.GetAt(str.GetLength() - 1) != '\\')
		str += "\\";
	strDir=str;
	m_ctrlComBox.GetWindowText(str);
	if(strDir!=str)
	{
		m_ctrlComBox.InsertString(0,strDir);
		m_ctrlComBox.DeleteString(2);
		m_ctrlComBox.SetCurSel(0);
		UpdateData(FALSE);
	}
}

void CDlg_SavePath::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_ctrlComBox.GetWindowText(m_strPath);
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="config.ini";
	CString str;
	m_ctrlComBox.GetLBText(0,str);
	if(str==m_strPath)
	{
		WritePrivateProfileString("Wilison","FileSavePath",str,strPath);
		m_ctrlComBox.GetLBText(1,str);
		WritePrivateProfileString("Wilison","FileSavePath1",str,strPath);
	}
	else
	{
		WritePrivateProfileString("Wilison","FileSavePath1",str,strPath);
		m_ctrlComBox.GetLBText(1,str);
		WritePrivateProfileString("Wilison","FileSavePath",str,strPath);
	}

	CDialog::OnOK();
}

BOOL CDlg_SavePath::OnInitDialog() 
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
	strPath+="config.ini";
	char inBuf[50];
	m_ctrlComBox.ResetContent();
	GetPrivateProfileString ("Wilison","FileSavePath",NULL,inBuf,50,strPath);
	m_ctrlComBox.InsertString(0,inBuf);
	GetPrivateProfileString ("Wilison","FileSavePath1",NULL,inBuf,50,strPath);
	m_ctrlComBox.InsertString(1,inBuf);
	m_ctrlComBox.SetCurSel(0);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
// DlgOneAxisPara.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DlgOneAxisPara.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOneAxisPara dialog


CDlgOneAxisPara::CDlgOneAxisPara(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOneAxisPara::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOneAxisPara)
		// NOTE: the ClassWizard will add member initialization here
	m_dPosition=0;
	m_dVelocity=0;
	//}}AFX_DATA_INIT
}


void CDlgOneAxisPara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOneAxisPara)
	DDX_Control(pDX, IDC_TAB1, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOneAxisPara, CDialog)
	//{{AFX_MSG_MAP(CDlgOneAxisPara)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOneAxisPara message handlers

BOOL CDlgOneAxisPara::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_tab.InsertItem(0,"位置");
	m_tab.InsertItem(1,"速度");
	
	m_pgPosition.Create(IDD_PAGEEDIT,GetDlgItem(IDC_TAB1));
	m_pgVelocity.Create(IDD_PAGESELECT,GetDlgItem(IDC_TAB1));

	m_pgPosition.m_dEdit=m_dPosition;
	m_pgPosition.m_unitText="mm";
	m_pgPosition.m_nameText="";
	CString str;
	switch(m_dVelocity)
	{
	case 1:
		str.Format("1");break;
	case 2:
		str.Format("2");break;
	case 3:break;
	default:
		break;
	}
	m_pgVelocity.m_strVelocity=str;
	m_pgVelocity.m_unitText="mm/s";


	UpdateData(FALSE);
	CRect rs;
	m_tab.GetClientRect(&rs);
	//调整子对话框在父窗口中的位置
	rs.top+=30; 
	rs.bottom-=37; 
	rs.left+=1; 
	rs.right-=1;
	m_pgPosition.MoveWindow(&rs);
	m_pgVelocity.MoveWindow(&rs);

	m_pgPosition.ShowWindow(TRUE);
	m_pgVelocity.ShowWindow(FALSE);

	m_tab.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgOneAxisPara::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int CurSel = m_tab.GetCurSel();
	switch(CurSel) 
	{
	case 0:
		m_pgPosition.ShowWindow(TRUE);
		m_pgVelocity.ShowWindow(FALSE);
		break;
	case 1:
		m_pgPosition.ShowWindow(FALSE);
		m_pgVelocity.ShowWindow(TRUE);
	default:
		;
	}
	*pResult = 0;
}

void CDlgOneAxisPara::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_dPosition=m_pgPosition.m_dEdit;
	m_dVelocity=atoi(m_pgVelocity.m_strVelocity);
	CDialog::OnOK();
}

void CDlgOneAxisPara::UpdateData(BOOL m_b)
{
	m_pgPosition.UpdateData(m_b);
	m_pgVelocity.UpdateData(m_b);

}

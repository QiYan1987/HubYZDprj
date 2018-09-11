// Dlg_YZD.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "Dlg_YZD.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_YZD dialog


CDlg_YZD::CDlg_YZD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_YZD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_YZD)
	m_name1 = _T("");
	m_high1 = 0.0f;
	m_num1 = 0;
	m_bPre = FALSE;
	m_PositionAway = 0.0f;
	m_intSelect = 0;
	m_dHeight = 0.0;
	m_bBack0 = TRUE;

	//}}AFX_DATA_INIT
	m_fG11cursel=0;
	memset(m_height,0,sizeof(m_height));
}


void CDlg_YZD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_YZD)
	DDX_Control(pDX, IDC_LIST_HEIGHT, m_ctrListHeight);
	DDX_Text(pDX, IDC_EDIT_YZD_Name, m_name1);
	DDX_Text(pDX, IDC_EDIT_YZD_H, m_high1);
	DDV_MinMaxFloat(pDX, m_high1, 1.e-002f, 500.f);
	DDX_Text(pDX, IDC_EDIT_YZD_Num, m_num1);
	DDV_MinMaxInt(pDX, m_num1, 2, 1000);
	DDX_Check(pDX, IDC_CHECK1, m_bPre);
	DDX_Text(pDX, IDC_EDIT2, m_PositionAway);
	DDX_Radio(pDX, IDC_RADIO_SELECT, m_intSelect);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_dHeight);
	DDV_MinMaxFloat(pDX, m_dHeight, 0.f, 500.f);
	DDX_Check(pDX, IDC_CHECKBACK, m_bBack0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_YZD, CDialog)
	//{{AFX_MSG_MAP(CDlg_YZD)
	ON_BN_CLICKED(IDC_RADIO_SELECT, OnRadioSelect)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_EN_CHANGE(IDC_EDIT_YZD_H, OnChangeEditYzdH)
	ON_EN_CHANGE(IDC_EDIT_YZD_Num, OnChangeEDITYZDNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_YZD message handlers

BOOL CDlg_YZD::OnInitDialog() 
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
	::GetPrivateProfileString("调整测量","m_fG11cursel_YZD","lisi",a.GetBuffer(100),100,strPath);
	m_fG11cursel=atoi(a);
	::GetPrivateProfileString("调整测量","m_bPre_YZD","lisi",a.GetBuffer(100),100,strPath);
	m_bPre=atoi(a);
	::GetPrivateProfileString("调整测量","m_PositionAway_YZD","lisi",a.GetBuffer(100),100,strPath);
	m_PositionAway=atof(a);
	::GetPrivateProfileString("调整测量","m_bBack0_YZD","lisi",a.GetBuffer(100),100,strPath);
	m_bBack0=atoi(a);
	::GetPrivateProfileString("调整测量","m_intSelect_YZD","lisi",a.GetBuffer(100),100,strPath);
	m_intSelect=atoi(a);
	::GetPrivateProfileString("调整测量","m_high1_YZD","lisi",a.GetBuffer(100),100,strPath);
	m_high1=atof(a);
	::GetPrivateProfileString("调整测量","m_num1_YZD","lisi",a.GetBuffer(100),100,strPath);
	m_num1=atoi(a);
	int i;
	for(i=0;i<m_num1;i++)
	{
		CString name;
		name.Format("m_height[%d]_YZD",i);
		::GetPrivateProfileString("调整测量",name,"lisi",a.GetBuffer(100),100,strPath);
		m_height[i]=atof(a);
	}

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
	m_time=CTime::GetCurrentTime();
	CString str;
	str=m_time.Format("%m-%d-%H-%M-%S");
	m_name1+=str;

	m_SumCount=m_num1;
	char *szColumn[]={"序号","高度值(mm)"};
	int widths[]={55,100};
	LV_COLUMN lvc;
	lvc.mask=LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
	lvc.fmt=LVCFMT_LEFT;
	for(i=0;i<2;i++) 
	{//插入各列
		lvc.pszText=szColumn[i];
		lvc.cx=widths[i];
		lvc.iSubItem=i;
		m_ctrListHeight.InsertColumn(i,&lvc);
	}
	m_ctrListHeight.SetExtendedStyle(m_ctrListHeight.GetExtendedStyle()|LVS_EX_GRIDLINES); 
	m_ctrListHeight.SetExtendedStyle(m_ctrListHeight.GetExtendedStyle()|LVS_EX_FULLROWSELECT); 

	if(m_intSelect==0)//等间距测量
	{
		(CEdit*)GetDlgItem(IDC_EDIT_YZD_H)->EnableWindow(TRUE);
		(CEdit*)GetDlgItem(IDC_EDIT_YZD_Num)->EnableWindow(TRUE);
		(CEdit*)GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_BTN_DELETE)->EnableWindow(FALSE);
	}
	else//非等间隔
	{
		(CEdit*)GetDlgItem(IDC_EDIT_YZD_H)->EnableWindow(FALSE);
		(CEdit*)GetDlgItem(IDC_EDIT_YZD_Num)->EnableWindow(FALSE);
		(CEdit*)GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_BTN_DELETE)->EnableWindow(TRUE);
	}
	m_ctrListHeight.DeleteAllItems();	
	char* data;
	data=new char;
	for ( i=0;i<m_num1;i++)
	{
		//m_height[i]=((CMainFrame*)AfxGetMainWnd())->m_fPerHeight[i];
		str.Format("%d",i);
		data=str.GetBuffer(5);		
		LV_ITEM lvi;
		lvi.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
		lvi.iSubItem=0;
		lvi.pszText=data;
		lvi.iImage = 0;
		lvi.iItem=i;
		m_ctrListHeight.InsertItem(&lvi);
		
		str.Format("%d",i+1);
		data=str.GetBuffer(5);
		m_ctrListHeight.SetItemText(i,0,data);
		str.Format("%.2lf",m_height[i]);
		data=str.GetBuffer(5);
		m_ctrListHeight.SetItemText(i,1,data);
	}
		UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_YZD::OnRadioSelect() //等间隔
{
	// TODO: Add your control notification handler code here
	(CEdit*)GetDlgItem(IDC_EDIT_YZD_H)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_YZD_Num)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_BTN_DELETE)->EnableWindow(FALSE);
	UpdateData(TRUE);
	m_SumCount=m_num1;
	UpdataHeightList();
}

void CDlg_YZD::OnRadio2() //非等间隔
{
	// TODO: Add your control notification handler code here
	(CEdit*)GetDlgItem(IDC_EDIT_YZD_H)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_YZD_Num)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(TRUE);
	(CButton*)GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);
	(CButton*)GetDlgItem(IDC_BTN_DELETE)->EnableWindow(TRUE);
}
void CDlg_YZD::OnChangeEditYzdH() 
{
	UpdateData(TRUE);	
	UpdataHeightList();
	
}
void CDlg_YZD::OnChangeEDITYZDNum() 
{
	UpdateData(TRUE);	
	UpdataHeightList();	
}
void CDlg_YZD::UpdataHeightList()
{
	m_ctrListHeight.DeleteAllItems();	
	CString str;
	char* data;
	data=new char;
	for (int i=0;i<m_num1;i++)
	{
		m_height[i]=0+i*(m_high1)/(m_num1-1);
		str.Format("%d",i);
		data=str.GetBuffer(5);		
		LV_ITEM lvi;
		lvi.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
		lvi.iSubItem=0;
		lvi.pszText=data;
		lvi.iImage = 0;
		lvi.iItem=i;
		m_ctrListHeight.InsertItem(&lvi);
		
		str.Format("%d",i+1);
		data=str.GetBuffer(5);
		m_ctrListHeight.SetItemText(i,0,data);
		str.Format("%.2lf",m_height[i]);
		data=str.GetBuffer(5);
		m_ctrListHeight.SetItemText(i,1,data);
	}
}

void CDlg_YZD::RefreshHeightList()
{
	//高度位置排序
	m_ctrListHeight.DeleteAllItems();	
	if (m_SumCount>1)
	{
		int i,j,k;
		double temp;
		for (i=0;i<m_SumCount-1;i++)
		{
			k=i;
			for (j=i+1;j<m_SumCount;j++)
			{
				if (m_height[j]<m_height[k])
				{
					k=j;
				}
			}
			if (k!=i)
			{
				temp=m_height[i];
				m_height[i]=m_height[k];
				m_height[k]=temp;
			}
		}
	}
	//显示数据
	CString str;
	char* data;
	data=new char;
	int index=1;
	while(index<=m_SumCount)
	{
		LV_ITEM lvi;
		lvi.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
		lvi.iSubItem=0;
		lvi.pszText=data;
		lvi.iImage = 0;
		lvi.iItem=index-1;
		m_ctrListHeight.InsertItem(&lvi);
		str.Format("%d",index);
		data=str.GetBuffer(5);
		m_ctrListHeight.SetItemText(index-1,0,data);
		str.Format("%.2lf",m_height[index-1]);
		data=str.GetBuffer(5);
		m_ctrListHeight.SetItemText(index-1,1,data);
		index++;
	}
}

void CDlg_YZD::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_SumCount++;
	m_num1=m_SumCount;
	UpdateData(FALSE);
	if (m_SumCount>20)
	{
		AfxMessageBox("错误，最多只能添加20个测量位置！");
		return;
	}
	//判断是否有高度重复
/*	if (m_SumCount>1)
	{	
		for (int i=0;i<m_SumCount-1;i++)
		{
			if (m_dHeight==m_height[i])
			{
				AfxMessageBox("不能添加相同高度的值！");
				m_SumCount--;
				m_num1=m_SumCount;
				UpdateData(FALSE);
				return;
			}
		}
	}
*/	m_height[m_SumCount-1]=m_dHeight;
	RefreshHeightList();
}

void CDlg_YZD::OnBtnDelete() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	int nIndex;
	pos= m_ctrListHeight.GetFirstSelectedItemPosition();
	nIndex = m_ctrListHeight.GetNextSelectedItem(pos);
	m_ctrListHeight.DeleteItem(nIndex);
	do 
	{	
		m_height[nIndex]=m_height[nIndex+1];
		nIndex++;
	} while(nIndex<(m_SumCount-1));
	m_SumCount--;
	m_num1=m_SumCount;
	UpdateData(FALSE);
	RefreshHeightList();
}
void CDlg_YZD::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
//	m_num1=m_SumCount;
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
	:: WritePrivateProfileString("调整测量","m_fG11cursel_YZD",A,strPath);	
	A.Format("%f",m_PositionAway);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_PositionAway_YZD",A,strPath);
	A.Format("%d",m_bPre);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_bPre_YZD",A,strPath);
	A.Format("%d",m_bBack0);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_bBack0_YZD",A,strPath);
	A.Format("%d",m_intSelect);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_intSelect_YZD",A,strPath);
	A.Format("%f",m_high1);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_high1_YZD",A,strPath);
	A.Format("%d",m_num1);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_num1_YZD",A,strPath);
	for(int i=0;i<m_num1;i++)
	{
		A.Format("%f",m_height[i]);//写到配置文件中
		CString name;
		name.Format("m_height[%d]_YZD",i);
		:: WritePrivateProfileString("调整测量",name,A,strPath);
	}
	CDialog::OnOK();
}

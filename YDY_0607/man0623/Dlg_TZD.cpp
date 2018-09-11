// Dlg_TZD.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "Dlg_TZD.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_TZD dialog


CDlg_TZD::CDlg_TZD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_TZD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_TZD)
	m_name1 = _T("");
	m_high1 = 0.0f;
	m_bPre = FALSE;
	m_PositionAway = 0.0f;
	m_bBack0 = TRUE;
	m_dHeight = 0.0;
	m_num1 = 0;
	m_intSelect = 0;
	//}}AFX_DATA_INIT
}


void CDlg_TZD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_TZD)
	DDX_Control(pDX, IDC_LIST_HEIGHT, m_ctrListHeight);
	DDX_Text(pDX, IDC_EDIT_TZD_Name, m_name1);
	DDX_Text(pDX, IDC_EDIT_TZD_H, m_high1);
	DDV_MinMaxFloat(pDX, m_high1, 1.e-002f, 500.f);
	DDX_Check(pDX, IDC_CHECK1, m_bPre);
	DDX_Text(pDX, IDC_EDIT2, m_PositionAway);
	DDX_Check(pDX, IDC_CHECKBACK, m_bBack0);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_dHeight);
	DDX_Text(pDX, IDC_EDIT_TZD_Num, m_num1);
	DDX_Radio(pDX, IDC_RADIO_SELECT, m_intSelect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_TZD, CDialog)
	//{{AFX_MSG_MAP(CDlg_TZD)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO_SELECT, OnRadioSelect)
	ON_EN_CHANGE(IDC_EDIT_TZD_H, OnChangeEditTzdH)
	ON_EN_CHANGE(IDC_EDIT_TZD_Num, OnChangeEDITTZDNum)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_TZD message handlers

BOOL CDlg_TZD::OnInitDialog() 
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
	::GetPrivateProfileString("调整测量","m_fG11cursel_TZD","lisi",a.GetBuffer(100),100,strPath);
	m_fG11cursel=atoi(a);
	::GetPrivateProfileString("调整测量","m_bPre_TZD","lisi",a.GetBuffer(100),100,strPath);
	m_bPre=atoi(a);
	::GetPrivateProfileString("调整测量","m_PositionAway_TZD","lisi",a.GetBuffer(100),100,strPath);
	m_PositionAway=atof(a);
	::GetPrivateProfileString("调整测量","m_bBack0_TZD","lisi",a.GetBuffer(100),100,strPath);
	m_bBack0=atoi(a);
	::GetPrivateProfileString("调整测量","m_intSelect_TZD","lisi",a.GetBuffer(100),100,strPath);
	m_intSelect=atoi(a);
	::GetPrivateProfileString("调整测量","m_high1_TZD","lisi",a.GetBuffer(100),100,strPath);
	m_high1=atof(a);
	::GetPrivateProfileString("调整测量","m_num1_TZD","lisi",a.GetBuffer(100),100,strPath);
	m_num1=atoi(a);
	int i;
	for(i=0;i<m_num1;i++)
	{
		CString name;
		name.Format("m_height[%d]_TZD",i);
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
	for( i=0;i<2;i++) 
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
		(CEdit*)GetDlgItem(IDC_EDIT_TZD_H)->EnableWindow(TRUE);
		(CEdit*)GetDlgItem(IDC_EDIT_TZD_Num)->EnableWindow(TRUE);
		(CEdit*)GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_BTN_DELETE)->EnableWindow(FALSE);
	}
	else//非等间隔
	{
		(CEdit*)GetDlgItem(IDC_EDIT_TZD_H)->EnableWindow(FALSE);
		(CEdit*)GetDlgItem(IDC_EDIT_TZD_Num)->EnableWindow(FALSE);
		(CEdit*)GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_BTN_DELETE)->EnableWindow(TRUE);
	}
	m_ctrListHeight.DeleteAllItems();	
	char* data;
	data=new char;
	for ( i=0;i<m_num1;i++)
	{
		m_height[i]=((CMainFrame*)AfxGetMainWnd())->m_fPerHeight[i];
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

void CDlg_TZD::OnRadioSelect() //等间隔
{
	// TODO: Add your control notification handler code here
	(CEdit*)GetDlgItem(IDC_EDIT_TZD_H)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_TZD_Num)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_BTN_DELETE)->EnableWindow(FALSE);
	UpdateData(TRUE);
	m_SumCount=m_num1;
	UpdataHeightList();
}

void CDlg_TZD::OnRadio2() //非等间隔
{
	// TODO: Add your control notification handler code here
	(CEdit*)GetDlgItem(IDC_EDIT_TZD_H)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_TZD_Num)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(TRUE);
	(CButton*)GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);
	(CButton*)GetDlgItem(IDC_BTN_DELETE)->EnableWindow(TRUE);
}
void CDlg_TZD::OnChangeEditTzdH() 
{
	UpdateData(TRUE);	
	UpdataHeightList();
	
}
void CDlg_TZD::OnChangeEDITTZDNum() 
{
	UpdateData(TRUE);	
	UpdataHeightList();	
}
void CDlg_TZD::UpdataHeightList()
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

void CDlg_TZD::RefreshHeightList()
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

void CDlg_TZD::OnBtnAdd() 
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
	if (m_SumCount>1)
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
	m_height[m_SumCount-1]=m_dHeight;
	RefreshHeightList();
}

void CDlg_TZD::OnBtnDelete() 
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
void CDlg_TZD::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
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
	:: WritePrivateProfileString("调整测量","m_fG11cursel_TZD",A,strPath);	
	A.Format("%f",m_PositionAway);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_PositionAway_TZD",A,strPath);
	A.Format("%d",m_bPre);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_bPre_TZD",A,strPath);
	A.Format("%d",m_bBack0);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_bBack0_TZD",A,strPath);
	A.Format("%d",m_intSelect);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_intSelect_TZD",A,strPath);
	A.Format("%f",m_high1);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_high1_TZD",A,strPath);
	A.Format("%d",m_num1);//写到配置文件中
    :: WritePrivateProfileString("调整测量","m_num1_TZD",A,strPath);
	for(int i=0;i<m_num1;i++)
	{
		A.Format("%f",m_height[i]);//写到配置文件中
		CString name;
		name.Format("m_height[%d]_TZD",i);
		:: WritePrivateProfileString("调整测量",name,A,strPath);
	}
	CDialog::OnOK();
}

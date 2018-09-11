// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Wilson6.h"
#include "DoCircle.h"
#include "DlgOneAxisPara.h"
#include "DoCylinder.h"
#include "ComboToolBar1.h"
#include "DoStraightness.h"
#include "DoParallelism.h"
#include "DoPlaneness.h"
#include "DoCoaxiality.h"
#include "DoVerticality.h"
#include "DlgHands.h"
#include "JMAnalyse.h"
#include "DoAdjustPosition.h"
#include "DoAdjustOritation.h"
#include "DoDynamicDisplay.h"
#include "LOGIN.h"
#include <fstream>
#include "Canshuchushi.h"
#include "biaoding.h"
#include "MotorState.h"
#include "MotorCorrection.h"
#include "DlgUserManagement.h"
#include "DlgGongYiSetting.h"
#include "DlgCHGQBiaoDing.h"
#include "DlgMachineInf.h"
#include  <io.h>
#include "MainFrm.h" 
#include "AmpScale.h"
#include "DlgZuobiao.h"
#include "DesktopView.h"
#include "iphlpapi.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_DoCircle, OnDoCircle)
	ON_BN_CLICKED(IDC_STOPALL,OnStopAll)
	ON_BN_CLICKED(IDC_AjustCenter,OnAjustCenter)
	ON_BN_CLICKED(IDC_AjustLevel,OnAjustLevel)
	ON_BN_CLICKED(IDC_AjustCenterAndLevel,OnAjustCenterandLevel)
	ON_BN_CLICKED(IDC_HReset,OnHReset)
	ON_COMMAND(ID_RESOURCEMANAGEMENT, OnResourcemanagement)
	ON_WM_TIMER()
	ON_COMMAND(ID_DAOGUI_LEFT, OnDaoguiLeft)
	ON_COMMAND(ID_DAOGUI_RIGHT, OnDaoguiRight)
	ON_COMMAND(ID_LIZHU_DOWN, OnLizhuDown)
	ON_COMMAND(ID_LIZHU_UP, OnLizhuUp)
	ON_COMMAND(ID_SENSOR_SIDE, OnSensorSide)
	ON_COMMAND(IDC_GOWORK, OnGowork)
	ON_COMMAND(ID_DoCylinder,OnDoCylinder)
	ON_COMMAND(ID_SENSOR_DOWN, OnSensorDown)
	ON_COMMAND(ID_DoStraightness, OnDoStraightness)
	ON_COMMAND(ID_DoParallelism, OnDoParallelism)
	ON_COMMAND(ID_DoPlaneness, OnDoPlaneness)
	ON_COMMAND(ID_DOCOAXIALITY, OnDocoaxiality)
	ON_COMMAND(ID_DOVERTICALITY, OnDoverticality)
	ON_COMMAND(ID_ZHITUIDIANJISECOND_U, OnZhituidianjisecondU)
	ON_COMMAND(ID_ZHITUIDIANJISECOND_D, OnZhituidianjisecondD)
	ON_COMMAND(ID_ZHITUIDIANJIFIRST_U, OnZhituidianjifirstU)
	ON_COMMAND(ID_ZHITUIDIANJIFIRST_D, OnZhituidianjifirstD)
	ON_COMMAND(ID_PINGTAI_XB, OnPingtaiXb)
	ON_COMMAND(ID_PINGTAI_XF, OnPingtaiXf)
	ON_COMMAND(ID_PINGTAI_YL, OnPingtaiYl)
	ON_COMMAND(ID_PINGTAI_YR, OnPingtaiYr)
	ON_COMMAND(ID_CANSHUCHUSHI, OnCanshuchushi)
	ON_COMMAND(ID_MOTORSTATE, OnMotorstate)
	ON_COMMAND(ID_MotorCorrect, OnMotorCorrect)
	ON_MESSAGE(WM_DIALOG,OnMotorDialog)/////////////////////////fengxuezhen
	ON_COMMAND(ID_SET_FILE_SAVE_PATH, OnSetFileSavePath)
	ON_COMMAND(ID_USERSETTING, OnUsersetting)
	ON_COMMAND(ID_CHUGANQI_BIAODING, OnChuganqiBiaoding)
	ON_COMMAND(ID_DAQ_AXIALITY, OnDaqAxiality)
	ON_COMMAND(ID_DAQ_CIRCLE_SEMIAU, OnDaqCircleSemiau)
	ON_COMMAND(ID_DAQ_CYD_SEMIAU, OnDaqCydSemiau)
	ON_COMMAND(ID_DAQ_PARA, OnDaqPara)
	ON_COMMAND(ID_DAQ_pmPLANENESS, OnDAQpmPLANENESS)
	ON_COMMAND(ID_DAQ_PLANENESS, OnDaqPlaneness)
	ON_COMMAND(ID_DAQ_SQUARENESS, OnDaqSquareness)
	ON_COMMAND(ID_DAQ_STRAIGHTNESS, OnDaqStraightness)
	ON_COMMAND(ID_GONGYI_SETTING, OnGongyiSetting)
	ON_COMMAND(ID_HandVelocitySet, OnHandVelocitySet)
	ON_COMMAND(ID_DYNAMICDIPLAY, OnDynamicdiplay)
	ON_COMMAND(ID_MACHINE_INF, OnMachineInf)
	ON_COMMAND(ID_shujucanshu, Onshujucanshu)
	ON_COMMAND(ID_ZUOBIAO_SET, OnZuobiaoSet)
	ON_COMMAND(ID_OUT, OnOut)
	ON_UPDATE_COMMAND_UI(ID_OUT, OnUpdateOut)
	ON_COMMAND(ID_AUTODELQK, OnAutodelqk)
	ON_UPDATE_COMMAND_UI(ID_AUTODELQK, OnUpdateAutodelqk)
	ON_COMMAND(ID_AUTOQKXS, OnAutoqkxs)
	ON_UPDATE_COMMAND_UI(ID_DYNAMICDIPLAY, OnUpdateDynamicdiplay)
	ON_UPDATE_COMMAND_UI(ID_CHUGANQI_BIAODING, OnUpdateChuganqiBiaoding)
	ON_NOTIFY(NM_DBLCLK,IDC_MYTREECTRL,OnDoubleClick)
	ON_COMMAND(ID_Connect,OnConnect)
	ON_COMMAND(ID_UnConnect,OnDisConnect)
	ON_COMMAND(ID_MENU_Lpxianshi, OnMENULpxianshi)
	ON_UPDATE_COMMAND_UI(ID_MENU_Lpxianshi, OnUpdateMENULpxianshi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR, 
	ID_fSTATE,// status line indicator״̬��Ϣ
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_DoCircle=NULL;
	m_DoCylinder=NULL;
	m_DoStraightness=NULL;
	m_DoParallelism=NULL;
	m_DoPlaneness=NULL;
	m_DoCoaxiality=NULL;
	m_DoVerticality=NULL;	
	m_DoCircleRunOut=NULL;
	m_DoJMAnalyse=NULL;
    m_DoAdjustPosition=NULL;
    m_DoAdjustOritation=NULL;
	m_DoDynamicDisplay=NULL;

	m_desktopview=NULL;
	//��ʼ������źͷ�����������
	m_lzhu_n=1;
	m_lzhu_enn=1;
	m_dg_n=2;
	m_dg_enn=2;
	m_zhuzhou_enn=4;
	m_pingtaix_n=3;
	m_pingtaiy_n=4;
	m_zhituifir_n=1;
	m_zhituisec_n=2;
	//��ʼ�������ʼλ��ֵ
	m_old_dgpulse=0;
	m_old_lzhupulse=0;
	m_old_ptxpulse=0;
	m_old_ptypulse=0;
	m_old_zhituifirpulse=0;
	m_old_zhituisecpulse=0;

	G11=0.25,G22=1.206548825 ; 
    m_MotorPara=NULL;
	m_distancePulse=0;
	/////////////////////////////��ѧ��
	m_fname="";
	m_fheight=20;m_fJiemianNum=5;
	m_fn=0;m_fbParallelism=false;
	m_fGainNum=0;
	m_fChannel=0;
	m_fStateMessage="״̬��Ϣ";
	m_fHandVelocity=0;
	m_fintTimes=0;
	m_fbPre=TRUE;
	m_fPositionAway=0;
	m_fVelocityCurSel=1;
	m_intTimes=5;
	m_intTimes2=0;
	m_dHTargetEccentricity=1;
	m_dLTargetEccentricity=1;
	m_dDistance=0;
	m_dDistance2=100;
	m_dFastMoveDistance=0;
	m_dHeight=10;
	m_fVelocity2=0;
	m_fVCurSel=1;
	memset(m_fPerHeight,0,15);
	for (int i=0;i<m_fJiemianNum;i++)
	{
		m_fPerHeight[i]=m_fheight/(m_fJiemianNum-1)*i;
	}
	m_fDengJianGe=0;
	m_fG11CurSel=0;

	m_analog_input1=0;
	m_fbBack0=TRUE;
	m_fbBack0=TRUE;
	m_breset1=TRUE;
	m_breset2=TRUE;
	m_breset3=TRUE;
	m_breset4=TRUE;

	m_lDaogui=0;
	m_lLizhu=0;

	m_OutIn=1;
	m_bAutoQK=FALSE;
	FilterMode=0;
	CirEvalue=0;
	VIEW_No=0;
	m_lx=0;
	m_bDongTai=TRUE;
	 FILE *fp2;
  	fp2=fopen("LZXISHU.txt","rt");
	fscanf(fp2,"%lf",&m_dgxishu);
	fscanf(fp2,"%lf",&m_lzxishu);
	fclose(fp2);
	//0050C224729C
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(1,ID_fSTATE,SBPS_NORMAL,200);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if (!m_ToolBar2.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBar2.LoadToolBar(IDR_TOOLBAR5))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    m_ToolBar2.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBar2);
		CString strMac,strMac1;
	GetMacAddress(strMac);
	strMac1="0050C228629A";
//	if(strMac1!=strMac)
//	{ MessageBox("�Ƿ��û�������Ȩ��ʹ��!");
//		return -1;
//	}
	CRect   rect;   
	//������Ͽ�ؿ�ȣ��ĸ���������Ϊ��������ؼ��ڹ������е������š�ID�š���񡢿��   
	m_ToolBar2.SetButtonInfo(0,   IDC_D,   TBBS_SEPARATOR  , 180  );   
	//�õ���Ͽ��λ��   
	m_ToolBar2.GetItemRect(0,   &rect);   
	//������Ͽ�ظ߶�   
	rect.bottom+=200;   //COMBO   HEIGHT;   
	//������Ͽ��ĸ���������Ϊ���ڷ����Ͽ�λ�á������ڡ�ID��   
	if(!m_ToolBar2.m_combobox.Create   (CBS_DROPDOWN|WS_VISIBLE|WS_TABSTOP|CBS_AUTOHSCROLL,rect,   &m_ToolBar2,   IDC_D))   
		return   -1;   
	//����Ͽ��м����ַ���   
	m_ToolBar2.m_combobox.AddString("Բ�Ȳ���"); 
	m_ToolBar2.m_combobox.AddString("Բ���Ȳ���"); 
	m_ToolBar2.m_combobox.AddString("ֱ�߶Ȳ���");
	m_ToolBar2.m_combobox.AddString("ƽ��Ȳ���");
	m_ToolBar2.m_combobox.AddString("��ֱƽ�жȲ���");
	m_ToolBar2.m_combobox.AddString("ƽ��ƽ�жȲ���");
	m_ToolBar2.m_combobox.AddString("ͬ��Ȳ���");
	m_ToolBar2.m_combobox.AddString("��ֱ�Ȳ���");
	
    m_ToolBar2.m_combobox.SetCurSel(0);  
	
    m_img2.Create(32,32,TRUE|ILC_COLOR32,4,0);
	HICON hIcon=NULL;
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICONGO), IMAGE_ICON, 32, 32, 0);
	m_img2.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICONGO), IMAGE_ICON, 32, 32, 0);
	m_img2.Add(hIcon);
    m_ToolBar2.GetToolBarCtrl().SetImageList(&m_img2);
	 //=========================================�ڹ���������ʾ�Զ����ͼƬ
	 //�ҵ�Ҫͣ���Ĵ���
	CControlBar* pDoockedBar = &m_wndToolBar;
	CFrameWnd* pFrame = pDoockedBar->GetDockingFrame();

	 //����ͣ����������λ��
	pFrame->RecalcLayout();
	 
	 //�����Ѿ�ͣ���������ľ���
	CRect rcDock;
	pDoockedBar->GetWindowRect(&rcDock);
	 //��������X,y��ƫ��һ����λ�������µĿ������Ϳ���ͣ�����Ѿ��еĿ��������ұ߻����±���
	rcDock.OffsetRect(1,1);
	pFrame->DockControlBar(&m_ToolBar2,AFX_IDW_DOCKBAR_TOP,&rcDock);

//����ToolBar��ͼ���б�

	m_imageList.Create(32,32,TRUE|ILC_COLOR32,6,0);
	//HICON hIcon=NULL;
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//1
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//2
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//3
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_chuli), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//4
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_Disable), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//5
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_Enable), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//6
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_SETORIGIN), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//7
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_SETOTHERS), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//8
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_tleft), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//9
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_tright), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//10
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_FenDuanChuLi), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//11
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_yuanduchuli), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//12
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ResetDeal), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//13
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_BGFX), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//14
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_PPFX), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//15
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_DELETE), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//15
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_AmplifyScale), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//1
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_BTNTBEGIN), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//1
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_BTNTSTOP), IMAGE_ICON, 32, 32, 0);
	m_imageList.Add(hIcon);//1
	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_imageList);


	if(!m_wndToolBar2.Create(this,IDD_DLGBAR,WS_CHILD|WS_VISIBLE|
		CBRS_ALIGN_BOTTOM |CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | 
		CBRS_SIZE_DYNAMIC|CBRS_BORDER_3D,IDD_DLGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;      // fail to create
	}
	//���´���ʵ�־�̬���б༭����
    CEdit *m_temp;
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_STATIC1);
	m_temp->SetWindowText("140.3");
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_STATIC2);
	m_temp->SetWindowText("1000");
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_STATIC3);
	m_temp->SetWindowText("1100");
// 	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_STATIC6);
// 	m_temp->SetWindowText("10.5");

	if (!m_wndToolBar3.Create(_T("�ҵĿ�����"),this,123)) 
	{ 
		TRACE0("Failed to create mybar\n"); 
		return -1; 
	} 
	

	if (!m_wndTree.Create(WS_CHILD|WS_VISIBLE|
		TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
		CRect(0, 0, 0, 0), &m_wndToolBar3, IDC_MYTREECTRL))
	{
		TRACE0("Failed to create instant bar child\n");
		return -1;
	}
	m_wndTree.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	m_wndTree.SetImageList(&m_imageList,TVSIL_NORMAL);

    //-----------------------------------�ұ߹�����
    if (!m_ToolBar1.CreateEx(this, TBSTYLE_AUTOSIZE, WS_CHILD | WS_VISIBLE | CBRS_RIGHT
	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	!m_ToolBar1.LoadToolBar(IDR_TOOLBAR3))
	{
	TRACE0("Failed to create toolbar\n");
	return -1;      // fail to create
	}


    //����ToolBar��ͼ���б�
	
    m_img1.Create(48, 48, TRUE | ILC_COLOR24, 9, 0);
    hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON4), IMAGE_ICON, 48, 48, 0);
    m_img1.Add(hIcon);
    hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON5), IMAGE_ICON, 48, 48, 0);
    m_img1.Add(hIcon);
    hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON8), IMAGE_ICON, 48, 48, 0);
    m_img1.Add(hIcon);
    hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON10), IMAGE_ICON, 48, 48, 0);
    m_img1.Add(hIcon);
    hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON6), IMAGE_ICON, 48, 48, 0);
    m_img1.Add(hIcon);
    hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON7), IMAGE_ICON, 48, 48, 0);
    m_img1.Add(hIcon);

	m_ToolBar1.GetToolBarCtrl().SetImageList(&m_img1);
    m_ToolBar1.SetWindowText ( "������1");  

    // TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable



    CButton *pBtn;
    pBtn= (CButton *)m_wndToolBar2.GetDlgItem(IDC_BUTTON1);
    CBitmap bitMap;
    HBITMAP hBit ;
    if(bitMap.LoadBitmap(IDB_STOP))
	{
    hBit = (HBITMAP)bitMap.Detach();
     pBtn->SetBitmap(hBit);
	}
	pBtn= (CButton *)m_wndToolBar2.GetDlgItem(IDC_AjustCenter);
    if(bitMap.LoadBitmap(IDB_TIAOXIN))
	{
    hBit = (HBITMAP)bitMap.Detach();
    pBtn->SetBitmap(hBit);
	}
	pBtn= (CButton *)m_wndToolBar2.GetDlgItem(IDC_AjustLevel);
    if(bitMap.LoadBitmap(IDB_TIAOPING))
	{
    hBit = (HBITMAP)bitMap.Detach();
    pBtn->SetBitmap(hBit);
	}
	pBtn= (CButton *)m_wndToolBar2.GetDlgItem(IDC_HReset);
    if(bitMap.LoadBitmap(IDB_RESET))
	{
    hBit = (HBITMAP)bitMap.Detach();
    pBtn->SetBitmap(hBit);
	}
	pBtn= (CButton *)m_wndToolBar2.GetDlgItem(IDC_AjustCenterAndLevel);
    if(bitMap.LoadBitmap(IDB_TIAOPINGXIN))
	{
    hBit = (HBITMAP)bitMap.Detach();
    pBtn->SetBitmap(hBit);
	}

    m_ToolBar1.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar2.EnableDocking(CBRS_ALIGN_BOTTOM);
	m_wndToolBar3.SetBarStyle(m_wndToolBar3.GetBarStyle() | CBRS_TOOLTIPS | 
		CBRS_FLYBY | CBRS_SIZE_DYNAMIC); 
	m_wndToolBar3.EnableDocking(CBRS_ALIGN_ANY);	
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar2);
    DockControlBar(&m_ToolBar1);
    DockControlBar(&m_ToolBar2);
	DockControlBar(&m_wndToolBar3, AFX_IDW_DOCKBAR_LEFT);///ͣ�������

	////�����Ϳؼ��������///

	m_iImageList123.Create(24, 24, TRUE,1, 0);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_FOLDER), IMAGE_ICON, 24, 24, 0);
 	m_iImageList123.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_PIST), IMAGE_ICON, 24, 24, 0);
 	m_iImageList123.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_RDS), IMAGE_ICON, 24, 24, 0);
 	m_iImageList123.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_CYD), IMAGE_ICON, 24, 24, 0);
 	m_iImageList123.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_ZXD),IMAGE_ICON,24,24,0);
	m_iImageList123.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_PXD),IMAGE_ICON,24,24,0);
	m_iImageList123.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_PMD),IMAGE_ICON,24,24,0);
	m_iImageList123.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_TXD),IMAGE_ICON,24,24,0);
	m_iImageList123.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_TZD),IMAGE_ICON,24,24,0);
	m_iImageList123.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_CZD),IMAGE_ICON,24,24,0);
	m_iImageList123.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_CRT),IMAGE_ICON,24,24,0);
	m_iImageList123.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_TRT),IMAGE_ICON,24,24,0);
	m_iImageList123.Add(hIcon);
 	m_wndTree.SetImageList ( &m_iImageList123,TVSIL_NORMAL );
//	BrowseFile(0,"��������");//����"��������"�ļ����ڵ�����Ŀ¼
	m_wndTree.SetBkColor(RGB(200,200,255));//�������οؼ��ı���ɫ
	m_wndTree.SetTextColor(RGB(127,0,0));//�����ı�����ɫ

	SetToolBarHide();
	//��ȡ�洢·��
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="config.ini";
	
	CString path = _T("");
	::GetPrivateProfileString("Wilison","FileSavePath","",
		path.GetBuffer(MAX_PATH), MAX_PATH,strPath); 
	path.ReleaseBuffer();
	m_strFileSavePath = path; //
	////�޸�Ϊ��ʼ���˶��忨�����ݲɼ��忨
	InitBoard();
	InitdianjiPra();
	InitMotorcorrection();
	InitMachineInf();
	
	//������
	HINSTANCE hInst = AfxGetResourceHandle();	
	HMENU m_hMenu;
	m_hMenu=::LoadMenu(hInst,MAKEINTRESOURCE(IDR_WILSONTYPE));
	::SetMenu(AfxGetMainWnd()->m_hWnd,m_hMenu);
	
	SetToolBarShow();
	SetWindowText("Wilson������");	
	CLOGIN dlg;
	if (dlg.DoModal()==IDOK)
	{
		HINSTANCE hInst = AfxGetResourceHandle();	
		HMENU m_hMenu;
		m_hMenu=::LoadMenu(hInst,MAKEINTRESOURCE(IDR_WILSONTYPE));
		::SetMenu(AfxGetMainWnd()->m_hWnd,m_hMenu);
		SetToolBarShow();
		SetWindowText("Wilson������");	
			SetTimer(12,50,NULL);
			//SetTimer(70,1,NULL);
		//�������ļ��ж�ȡ����
// 		CString usernewpwd="111";
//         CString usernewname;
// 		std::ofstream fout("userinf.pwd", std::ios::binary);
// 		fout.write((char*)&usernewname,6*sizeof(char));
// 		fout.write((char*)&usernewpwd,6*sizeof(char));
// 		fout.close();
// 
// 		if (dlg.m_userPwd==usernewpwd&&dlg.m_userName==usernewname)
// 		{	
// 			HINSTANCE hInst = AfxGetResourceHandle();	
// 			HMENU m_hMenu;
// 			m_hMenu=::LoadMenu(hInst,MAKEINTRESOURCE(IDR_WILSONTYPE));
// 			::SetMenu(AfxGetMainWnd()->m_hWnd,m_hMenu);
// 			SetToolBarShow();
//   			SetWindowText("Wilson������");	
// 			SetTimer(12,1,NULL);
// 		}
// 		else
// 		{
// 			//AfxMessageBox("��Ϣ����!");
// 			//PostMessage(WM_CLOSE);
// 		}	
	}
	else
	{
		PostMessage(WM_CLOSE);
	}

	Desktop();
	m_wndStatusBar.SetPaneText(3,"��Բ");
	//OnResourcemanagement();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT 
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::SetToolBarHide()
{
		m_wndToolBar.GetToolBarCtrl().SetState(ID_UnConnect,TBSTATE_HIDDEN);		
		m_wndToolBar.GetToolBarCtrl().SetState(ID_Connect,TBSTATE_ENABLED);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_Print,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNCHULI,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNDISABLE,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNENABLE,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNSETORIGIN,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNSETOTHERS,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTLEFT,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTRIGHT,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTBEGIN,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTSTOP,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNFENDUANCHULI,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNYUANDUCHULI,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNRESETDEAL,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNBGFX,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNPPFX,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNDELETE,TBSTATE_HIDDEN);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_AmplifyScale,TBSTATE_HIDDEN);
		m_wndToolBar2.ShowWindow(SW_HIDE);
		m_wndToolBar3.ShowWindow(SW_HIDE);
		m_ToolBar1.ShowWindow(SW_HIDE);
		m_ToolBar2.ShowWindow(SW_HIDE);
		RecalcLayout( );
}

void CMainFrame::SetToolBarShow()
{	
	m_wndToolBar.GetToolBarCtrl().SetState(ID_UnConnect,TBSTATE_ENABLED);
 	m_wndToolBar.GetToolBarCtrl().SetState(ID_Connect,TBSTATE_HIDDEN);
 	m_wndToolBar.GetToolBarCtrl().SetState(ID_Print,TBSTATE_ENABLED);	
 	m_wndToolBar2.ShowWindow(SW_SHOW);
	m_ToolBar1.ShowWindow(SW_SHOW);
	m_ToolBar1.GetToolBarCtrl().SetState(ID_SETTING,TBSTATE_HIDDEN);
  	m_ToolBar1.GetToolBarCtrl().SetState(ID_MAINSHAFT_ANTICLOCKWISE,TBSTATE_HIDDEN);
 	m_ToolBar1.GetToolBarCtrl().SetState(ID_MAINSHAFT_CLOCKWISE,TBSTATE_HIDDEN);
  	m_ToolBar2.ShowWindow(SW_SHOW);
	RecalcLayout( );

}

void CMainFrame::OnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	AfxMessageBox(m_wndTree.GetItemText(pNMTreeView->itemNew.hItem));

  pResult=0;
}

void CMainFrame::BrowseFile(int CallNum, CString strFile)
{
	CallNum++;
	CFileFind ff;
	CString szDir = strFile;
	
	if(szDir.Right(1) != "\\")
		szDir += "\\";
	//ÿ��Ŀ¼�¶���ȱʡ������Ŀ¼�����Ʒֱ�Ϊ '. '�� '.. '���ֱ������һ��Ŀ¼�ͱ���Ŀ¼��
	//��ˣ��������ڱ���Ŀ¼���ļ�ʱ����Ҫ���˵�������ȱʡĿ¼�� 
	szDir += "*.*";
	
	BOOL res = ff.FindFile(szDir);  //Call this member function to open a file search
	while(res)
	{
		res = ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots())//IsDirectory() :���szDir��ʾ����һ��Ŀ¼,�򷵻�true
                                             //��CFileFind��������IsDots����˼�ǣ�����һ��Ŀ¼���Ҳ������Ŀ¼��������ϲ�Ŀ¼�� 
		{
			//�����һ����Ŀ¼���õݹ��������һ����
			CString strPath = ff.GetFilePath();         //��ȡ��ǰĿ¼
			CString strTitle = ff.GetFileTitle();       //�ú���������IpszFile������ʶ���ļ���
			int i =0;
			switch(CallNum)
			{
				case 1:
					strHTFir = m_wndTree.InsertItem(strTitle,0,0,NULL);						
					break;
				case 2:
					strHTSec = m_wndTree.InsertItem(strTitle,0,0,strHTFir);											
					break;
				case 3:
					strHtThi = m_wndTree.InsertItem(strTitle,0,0,strHTSec);					
					break;
				case 4:
					strHtFor = m_wndTree.InsertItem(strTitle,0,0,strHtThi);					
					break;
				default:
					strHtFif = m_wndTree.InsertItem(strTitle,0,0,strHtFor);
					break;					
			}
			BrowseFile(CallNum,strPath);
		}
		else if(!ff.IsDirectory() && !ff.IsDots())
		{
			//��ʾ��ǰ���ʵ��ļ�
			CString strPath;
			CString strTitle;
			CString strTitle1;
			int   nPos;
			CString   szExt;
			strPath = ff.GetFilePath();
			strTitle = ff.GetFileTitle();
			strTitle1 = ff.GetFileName();
			nPos=strTitle1.ReverseFind('.'); 
			szExt=strTitle1.Right(strTitle1.GetLength()-nPos-1); 
			switch(CallNum)
			{
			case 1:
				if (szExt=="pist")
				{
					strRoot = m_wndTree.InsertItem(strTitle,1,1,NULL);
				}
				else if (szExt=="rds")
				{
					strRoot = m_wndTree.InsertItem(strTitle,2,2,NULL);
				}
				else if (szExt=="cyd")
				{
					strRoot = m_wndTree.InsertItem(strTitle,3,3,NULL);
				}
				else if (szExt=="zxd")
				{
					strRoot = m_wndTree.InsertItem(strTitle,4,4,NULL);
				}
				else if (szExt=="pxd")
				{
					strRoot = m_wndTree.InsertItem(strTitle,5,5,NULL);
				}
				else if (szExt=="pmd")
				{
					strRoot = m_wndTree.InsertItem(strTitle,6,6,NULL);
				}
				else if (szExt=="txd")
				{
					strRoot = m_wndTree.InsertItem(strTitle,7,7,NULL);
				}
				else if (szExt=="tzd")
				{
					strRoot = m_wndTree.InsertItem(strTitle,8,8,NULL);
				}
				else if (szExt=="czd")
				{
					strRoot = m_wndTree.InsertItem(strTitle,9,9,NULL);
				}
				else if (szExt=="rnt")
				{
					strRoot = m_wndTree.InsertItem(strTitle,10,10,NULL);
				}
				else if (szExt=="trt")
				{
					strRoot = m_wndTree.InsertItem(strTitle,11,11,NULL);
				}
				break;
			case 2:
				if (szExt=="pist")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,1,1,strHTFir);
				}
				else if (szExt=="rds")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,2,2,strHTFir);
				}
				else if (szExt=="cyd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,3,3,strHTFir);
				}
				else if (szExt=="zxd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,4,4,strHTFir);
				}
				else if (szExt=="pxd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,5,5,strHTFir);
				}
				else if (szExt=="pmd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,6,6,strHTFir);
				}
				else if (szExt=="txd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,7,7,strHTFir);
				}
				else if (szExt=="tzd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,8,8,strHTFir);
				}
				else if (szExt=="czd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,9,9,strHTFir);
				}
				else if (szExt=="rnt")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,10,10,strHTFir);
				}
				else if (szExt=="trt")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,11,11,strHTFir);
				}
				break;
			case 3:
				if (szExt=="pist")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,1,1,strHTSec);
				}
				else if (szExt=="rds")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,2,2,strHTSec);
				}
				else if (szExt=="cyd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,3,3,strHTSec);
				}
				else if (szExt=="zxd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,4,4,strHTSec);
				}
				else if (szExt=="pxd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,5,5,strHTSec);
				}
				else if (szExt=="pmd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,6,6,strHTSec);
				}
				else if (szExt=="txd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,7,7,strHTSec);
				}
				else if (szExt=="tzd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,8,8,strHTSec);
				}
				else if (szExt=="czd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,9,9,strHTSec);
				}
				else if (szExt=="rnt")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,10,10,strHTSec);
				}
				else if (szExt=="trt")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,11,11,strHTSec);
				}
				break;
			case 4:
				if (szExt=="pist")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,1,1,strHtThi);
				}
				else if (szExt=="rds")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,2,2,strHtThi);
				}
				else if (szExt=="cyd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,3,3,strHtThi);
				}
				else if (szExt=="zxd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,4,4,strHtThi);
				}
				else if (szExt=="pxd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,5,5,strHtThi);
				}
				else if (szExt=="pmd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,6,6,strHtThi);
				}
				else if (szExt=="txd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,7,7,strHtThi);
				}
				else if (szExt=="tzd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,8,8,strHtThi);
				}
				else if (szExt=="czd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,9,9,strHtThi);
				}
				else if (szExt=="rnt")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,10,10,strHtThi);
				}
				else if (szExt=="trt")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,11,11,strHtThi);
				}
				break;
			case 5:
				if (szExt=="pist")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,1,1,strHtFor);
				}
				else if (szExt=="rds")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,2,2,strHtFor);
				}
				else if (szExt=="cyd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,3,3,strHtFor);
				}
				else if (szExt=="zxd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,4,4,strHtFor);
				}
				else if (szExt=="pxd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,5,5,strHtFor);
				}
				else if (szExt=="pmd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,6,6,strHtFor);
				}
				else if (szExt=="txd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,7,7,strHtFor);
				}
				else if (szExt=="tzd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,8,8,strHtFor);
				}
				else if (szExt=="czd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,9,9,strHtFor);
				}
				else if (szExt=="rnt")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,10,10,strHtFor);
				}
				else if (szExt=="trt")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,11,11,strHtFor);
				}
				break;
			default:
				if (szExt=="pist")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,1,1,strHtFif);
				}
				else if (szExt=="rds")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,2,2,strHtFif);
				}
				else if (szExt=="cyd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,3,3,strHtFif);
				}
				else if (szExt=="zxd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,4,4,strHtFif);
				}
				else if (szExt=="pxd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,5,5,strHtFif);
				}
				else if (szExt=="pmd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,6,6,strHtFif);
				}
				else if (szExt=="txd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,7,7,strHtFif);
				}
				else if (szExt=="tzd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,8,8,strHtFif);
				}
				else if (szExt=="czd")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,9,9,strHtFif);
				}
				else if (szExt=="rnt")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,10,10,strHtFif);
				}
				else if (szExt=="trt")
				{
					strHtEnd = m_wndTree.InsertItem(strTitle,11,11,strHtFif);
				}
				break;
			}
		}
	}
	ff.Close();//�ر�

}


void CMainFrame::OnDoubleClick(NMHDR* pnmhdr, LRESULT *plr)
{

	HTREEITEM hItem = m_wndTree.GetSelectedItem();//ȡ�ñ�ѡ�е�����
	int ret=0;
	int nImage;
	int nSelectedImage ;
	ret=m_wndTree.GetItemImage(hItem,nImage,nSelectedImage);
	if (nImage==2)
	{	
		m_fullPath=GetFullPath(hItem);
		m_fullPath+=".rds";
		if (m_DoCircle!=NULL)
		{
			m_DoCircle->MDIActivate();
			m_DoCircle->RedrawWindow();
			return;
		}
		m_DoCircle=new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoCircle);
		if (!m_DoCircle->LoadFrame(IDI_ICON17,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoCircle);
		m_DoCircle->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoCircle->InitialUpdateFrame(NULL,TRUE);
	}
	else if (nImage==3)
	{
		m_fullPath2=GetFullPath(hItem);
		m_fullPath2+=".cyd";
		if (m_DoCylinder!=NULL)
		{
			m_DoCylinder->MDIActivate();
			m_DoCylinder->RedrawWindow();
			return;
		}
		m_DoCylinder=new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoCylinder);
		if (!m_DoCylinder->LoadFrame(IDI_CYD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoCylinder);
		m_DoCylinder->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoCylinder->InitialUpdateFrame(NULL,TRUE);
	//	AfxMessageBox("�����Բ�����ļ�");
	}
	else if (nImage==4)
	{
		m_fullPath3=GetFullPath(hItem);
		m_fullPath3+=".zxd";
		if (m_DoStraightness!=NULL)
		{
			m_DoStraightness->MDIActivate();
			m_DoStraightness->RedrawWindow();
			return;
		}
		m_DoStraightness = new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoStraightness);
		if (!m_DoStraightness->LoadFrame(IDI_ZXD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoStraightness);
		m_DoStraightness->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoStraightness->InitialUpdateFrame(NULL,TRUE);

	}
	else if (nImage==5)
	{
		m_fullPath4=GetFullPath(hItem);
		m_fullPath4+=".pxd";
		if (m_DoParallelism!=NULL)
		{
			m_DoParallelism->MDIActivate();
			m_DoParallelism->RedrawWindow();
			return;
		}
		m_DoParallelism = new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoParallelism);
		if (!m_DoParallelism->LoadFrame(IDI_PXD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoParallelism);
		m_DoParallelism->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoParallelism->InitialUpdateFrame(NULL,TRUE);

	}
	else if (nImage==6)
	{
		m_fullPath5=GetFullPath(hItem);
		m_fullPath5+=".pmd";
		if (m_DoPlaneness!=NULL)
		{
			m_DoPlaneness->MDIActivate();
			m_DoPlaneness->RedrawWindow();
			return;
		}
		m_DoPlaneness = new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoPlaneness);
		if (!m_DoPlaneness->LoadFrame(IDI_PMD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoPlaneness);
		m_DoPlaneness->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoPlaneness->InitialUpdateFrame(NULL,TRUE);
	}
	else if (nImage==8)
	{
		m_fullPath7=GetFullPath(hItem);
		m_fullPath7+=".tzd";
		if (m_DoCoaxiality!=NULL)
		{
			m_DoCoaxiality->MDIActivate();
			m_DoCoaxiality->RedrawWindow();
			return;
		}
		m_DoCoaxiality = new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoCoaxiality);
		if (!m_DoCoaxiality->LoadFrame(IDI_TZD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoCoaxiality);
		m_DoCoaxiality->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoCoaxiality->InitialUpdateFrame(NULL,TRUE);
		
	}
	else if (nImage==9)
	{
		m_fullPath8=GetFullPath(hItem);
		m_fullPath8+=".czd";
		if (m_DoVerticality!=NULL)
		{
			m_DoVerticality->MDIActivate();
			m_DoVerticality->RedrawWindow();
			return;
		}
		m_DoVerticality = new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoVerticality);
		if (!m_DoVerticality->LoadFrame(IDI_CZD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoVerticality);
		m_DoVerticality->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoVerticality->InitialUpdateFrame(NULL,TRUE);
	}
	else
	{
		return ;
	}
}


void CMainFrame::OnConnect()
{
	//�޸�Ϊ��ʼ���˶��忨�����ݲɼ��忨
	InitBoard();
	//������

	CLOGIN dlg;
	if (dlg.DoModal()==IDOK)
	{
		//�������ļ��ж�ȡ����
		CString str_pwd="111";
		if (dlg.m_userPwd==str_pwd)
		{	
			HINSTANCE hInst = AfxGetResourceHandle();	
			HMENU m_hMenu;
			m_hMenu=::LoadMenu(hInst,MAKEINTRESOURCE(IDR_WILSONTYPE));
			::SetMenu(AfxGetMainWnd()->m_hWnd,m_hMenu);
			SetToolBarShow();
  			SetWindowText("Wilson������");	
		}
		else
		{
			PostMessage(WM_CLOSE);
		}	
	}
	else
	{
		PostMessage(WM_CLOSE);
	}	
}

void CMainFrame::OnDisConnect()
{
	HINSTANCE hInst = AfxGetResourceHandle();	
	HMENU m_hMenu;
	m_hMenu=::LoadMenu(hInst,MAKEINTRESOURCE(IDR_MAINFRAME));
	::SetMenu(AfxGetMainWnd()->m_hWnd,m_hMenu);
	SetToolBarHide();
	SetWindowText("Wilsonδ����");

}


void CMainFrame::OnResourcemanagement() 
{
	// TODO: Add your command handler code here
	m_wndTree.DeleteAllItems();
	BrowseFile(0,m_strFileSavePath);//����"��������"�ļ����ڵ�����Ŀ¼
	m_wndToolBar3.ShowWindow(SW_SHOW);
	RecalcLayout();
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//write by wu lei
	switch(nIDEvent)
	{
	case 1: Timer1();	break;
	case 2: Timer2();	break;
	case 3: Timer3(); break;
	case 4: Timer4(); break;
	case 5: Timer5(); break;
	case 6:	Timer6();	break;
	case 7: Timer7(); break;
	case 8: Timer8(); break;
	case 9: Timer9(); break;
	case 10: Timer10(); break;
	case 11: Timer11(); break;
	case 12: Timer12(); break;
	case 13: Timer13(); break;
	case 14: Timer14(); break;
	case 15: Timer15(); break;
	case 16: Timer16(); break;
	case 17: Timer17(); break;
	case 18: Timer18(); break;
	case 19: Timer19(); break;
	case 20: Timer20(); break;
	case 21: Timer21(); break;
	case 22: Timer22(); break;
	case 23: Timer23(); break;

    case 30:Timer30();break;
	case 31:Timer31();break;

	case 32:Timer32();break;
	case 33:Timer33();break;

	case 34:Timer34();break;
	case 35:Timer35();break;
	case 36:Timer36();break;
	case 37:Timer37();break;

	case 38:Timer38();break;
	case 39:Timer39();break;

	case 40:Timer40();break;
	case 41:Timer41();break;
	case 42:Timer42();break;

	case 43:Timer43();break;

	case 44:Timer44();break;
	case 45:Timer45();break;
	case 46:Timer46();break;

	case 47:Timer47();break;

	case 48:Timer48();break;
	case 49:Timer49();break;
	case 50:Timer50();break;
	case 51:Timer51();break;
	case 52:Timer52();break;

	case 53:Timer53();break;
	case 54:Timer54();break;
	case 55:Timer55();break;
	case 56:Timer56();break;

	case 57:Timer57();break;

	case 58:Timer58();break;
	case 59:Timer59();break;
	case 60:Timer60();break;
	case 61:Timer61();break;


	case 62:Timer62();break;
	case 63:Timer63();break;
	case 70:Timer70();break;
	case 71:Timer71();break;
	case 72:Timer72();break;
	case 99:Timer99();break;
	default: break;
	}	
	CMDIFrameWnd::OnTimer(nIDEvent);
}


CString CMainFrame::GetFullPath(HTREEITEM hCurrent)
{  	
	CString strTemp;
	CString strReturn = ""; 
	strTemp = m_wndTree.GetItemText(hCurrent);
	while(hCurrent != NULL)
	{		
		strReturn = strTemp  + strReturn;
		hCurrent = m_wndTree.GetParentItem(hCurrent);
		strTemp = m_wndTree.GetItemText(hCurrent);
		if(strTemp.Right(1) != "\\")
			strTemp += "\\";
	}
	strReturn=m_strFileSavePath+strReturn;
	return strReturn;
}

void CMainFrame::OnDaoguiLeft() 
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	long vel=0;	
	if(dlg.DoModal()==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
	    vel=dlg.m_dVelocity;
	
	}
	else
	{
		return;
	}
	UpdataDisplayBar();
	get_abs_pos(m_dg_enn,&m_old_dgpulse);

	set_profile(m_dg_n,100,vel*1000/0.075,110000/6);
	fast_pmove(m_dg_n,-m_distancePulse*1000000);

	m_stop_flag=1;
	m_fStateMessage="��������";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
   SetTimer(9,10,NULL);// TODO: Add your command handler code here



}

void CMainFrame::OnDaoguiRight() 
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	long vel=0;
	if(dlg.DoModal()==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
		vel=dlg.m_dVelocity;
	}
	else
	{
		return;
	}
	get_abs_pos(m_dg_enn,&m_old_dgpulse);
	
	set_profile(m_dg_n,100,vel*1000/0.075,110000/6);
	fast_pmove(m_dg_n,m_distancePulse*10000000);
	
	m_stop_flag=1;
	m_fStateMessage="��������";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	SetTimer(9,10,NULL);// TODO: Add your command handler code here
	// TODO: Add your command handler code here	
}

void CMainFrame::OnLizhuDown() 
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	double vel=0;
	double distance=0;
	if(dlg.DoModal()==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
		vel=dlg.m_dVelocity;
	}
	else
	{
		return;
	}
	get_abs_pos(m_lzhu_enn,&m_old_lzhupulse);
	
	set_profile(m_lzhu_n,3000,vel*1000/0.075,110000/6);
	fast_pmove(m_lzhu_n,-m_distancePulse*1000000);
	
	m_stop_flag=0;
	m_fStateMessage="�����½�";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	SetTimer(99,10,NULL);// TODO: Add your command handler code here
	
}

void CMainFrame::OnLizhuUp() 
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	double vel=0;
	double distance=0;
	if(dlg.DoModal()==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
		vel=dlg.m_dVelocity;
	}
	else
	{
		return;
	}
	//��ʾԭ���ı�������ֵ����û��fast_pmove  m_old_dgpulse��
	get_abs_pos(m_lzhu_enn,&m_old_lzhupulse);
	
	set_profile(m_lzhu_n,3000,vel*1000/0.075,110000/6);
	fast_pmove(m_lzhu_n,m_distancePulse*10000000);
	
	m_stop_flag=0;
	m_fStateMessage="��������";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	SetTimer(99,10,NULL);// TODO: Add your command handler code here
	
}

void CMainFrame::OnSensorSide() 
{
	KillTimer(70);
	KillTimer(12);
	::AfxMessageBox("��ȷ�ϴ���������");
	set_profile(m_dg_n,500,3500,2000);
	fast_vmove(m_dg_n,-1);
	m_fStateMessage="����������";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	SetTimer(10,10,NULL);
	
}
void CMainFrame::OnSensorDown() 
{
	KillTimer(70);
	KillTimer(12);
	::AfxMessageBox("��ȷ�ϴ���������");
	set_profile(m_lzhu_n,500,3500,3000);
	fast_vmove(m_lzhu_n,-1);
	m_fStateMessage="����������";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	SetTimer(11,10,NULL);
	
}
void CMainFrame::Timer9()
{
	long com1;
	long com2;
	CEdit *m_temp;
	CString m_encoder;
	get_abs_pos(m_dg_enn,&com1);
//	m_encoder.Format("%.2f",com1);
//	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_Daogui);
 //   m_temp->SetWindowText(m_encoder);	
	
	
	UpdataDisplayBar();

		if((abs((com1-m_old_dgpulse)*m_dgxishu))>abs(m_distancePulse-1))
		{
			KillTimer(9);
			sudden_stop(m_dg_n);
			m_fStateMessage="�˶����";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			SetTimer(12,10,NULL);
		}


}
void CMainFrame::Timer99()
{
	long com1;
	long com2;
	CEdit *m_temp;
	CString m_encoder;
	
	get_abs_pos(m_lzhu_enn,&com2);
//	m_encoder.Format("%.2f",com2);
//	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_Lizhu);
   // m_temp->SetWindowText(m_encoder);	
	UpdataDisplayBar();

	
		if(abs(((com2-m_old_lzhupulse)*m_lzxishu))>abs(m_distancePulse-1))
		{
			KillTimer(99);
			sudden_stop(m_lzhu_n);
			m_fStateMessage="�˶����";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			SetTimer(12,10,NULL);
		}		
	
}
void CMainFrame::Timer10()
{
	int analog_input1=0;
	double analog_input=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input=((analog_input1-2048)*10)/(G11*G22*4096);
	CString m_signal;
    m_signal.Format("%.2f",analog_input);
	CEdit *m_temp;
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_Chuanganqi);
    m_temp->SetWindowText(m_signal);
    if(analog_input>-50)
	{
		KillTimer(10);
		sudden_stop(m_dg_n);
		m_fStateMessage="�˶����";
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);
		SetTimer(12,10,NULL);
	}
	long com;
	CString m_encoder;
	get_abs_pos(m_dg_enn,&com);
    m_encoder.Format("%.2f",com*m_dgxishu);
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_Daogui);
    m_temp->SetWindowText(m_encoder);
	
	get_abs_pos(m_lzhu_enn,&com);
	m_encoder.Format("%.2f",com*m_lzxishu);
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_Lizhu);
    m_temp->SetWindowText(m_encoder);

}

void CMainFrame::Timer11()
{
	int analog_input1=0;
	double analog_input=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input=((analog_input1-2048)*10)/(G11*G22*4096);
	CString m_signal;
    m_signal.Format("%.4f",analog_input);
	CEdit *m_temp;
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_Chuanganqi);
    m_temp->SetWindowText(m_signal);
	if(analog_input>-50)
	{
		KillTimer(11);
		sudden_stop(m_lzhu_n);
		m_fStateMessage="�˶����";
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);
		SetTimer(12,10,NULL);
	}
	long com;
	CString m_encoder;
	get_abs_pos(m_dg_enn,&com);
    m_encoder.Format("%.2f",com*m_dgxishu);
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_Daogui);
    m_temp->SetWindowText(m_encoder);
	
	get_abs_pos(m_lzhu_enn,&com);
	m_encoder.Format("%.2f",com*m_lzxishu);
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_Lizhu);
    m_temp->SetWindowText(m_encoder);
	
}

void CMainFrame::Timer12()
{
	m_bDongTai=TRUE;
	int ret1=999;
	int ret2=999;
	int ret3=999;
	int ret4=999;
	int mask=0;
	int upf=0;
	int downf=0;
	int lf=0;
	int rf=0;
// 	set_profile(m_dg_n,5000,25000,100000);
// 	set_profile(m_lzhu_n,5000,25000,200000);
	set_profile(m_dg_n,5000,m_fHandVelocity,100000);
	set_profile(m_lzhu_n,5000,m_fHandVelocity,100000);

	mask = check_SFR(1);
	ret1=mask&4;
	ret2=mask&8;
	ret3=mask&1;
	ret4=mask&2;
	
	  
				if(0==ret1)
				{
					fast_vmove(m_dg_n,-10000); 
				}else{
					lf=1;
				}		
		
				if(0==ret2)
				{
						fast_vmove(m_dg_n,10000); 
				}else{
		        rf=1;
				}
				if(0==ret3)
				{
					fast_vmove(m_lzhu_n,1000); 
				}else{
				upf=1;
				}
			
		
				if(0==ret4)
				{
					fast_vmove(m_lzhu_n,-1000); 
				}else{
				downf=1; 
				}
		if(( 1==lf )&&(1== rf)){
         sudden_stop(m_dg_n);
        }
		if(( 1==upf)&&(1== downf)){
         sudden_stop(m_lzhu_n);
        }
		UpdataDisplayBar();
		
}
void CMainFrame::OnStopAll()
{
//	AfxMessageBox("ֹͣһ��");
	int i;
	for(i=0;i<75;i++)
	{
		if(i!=12)
			KillTimer(i);
	}
	for( i=1;i<=8;i++)
	{
		sudden_stop(i);
	}
	////��ѧ��
	//m_fheight=0;
	m_breset1=true;
	m_breset2=true;
	m_breset3=true;
	m_breset4=true;
	m_fn=0;
	m_fname="";
	m_ftime=0;
	//m_fJiemianNum=0;
	m_fStateMessage="״̬��Ϣ";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	m_fbParallelism=false;
	SetTimer(12,10,NULL);

}

void CMainFrame::OnAjustCenter()
{

    //���Ĺ��ܿ�
	CDlgAjustCenter dlg;
	if (IDOK == dlg.DoModal())
	{
		W_812_AD_Set_Gain(0);
		W_812_AD_Set_Channel(0);
		G11=0.25;
		m_dLTargetEccentricity = dlg.m_dTargetEccentricity;
		m_dFastMoveDistance = dlg.m_dFastMoveDistance;
		m_intTimes = dlg.m_intTimes;
		m_intTimes2=m_intTimes;
		//m_fintTimes=dlg.m_intTimes;
		KillTimer(12);//�ر��ֶ���
		m_bDongTai=FALSE;
		//���������������˶�
		long lPulse;
		lPulse = m_dFastMoveDistance*1000/0.048;
		set_profile(m_dg_n,1000,8000,4000);//mpc08
		fast_pmove(m_dg_n,lPulse);		
		//������ʱ��1����ʼ���Ĺ��̣�
		m_fStateMessage="�Զ�����";
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);
		SetTimer(1,10,NULL);
	}
}
void CMainFrame::OnAjustLevel()
{

	CDlgAjustPingjing dlg;
	if (IDOK == dlg.DoModal())
	{
		W_812_AD_Set_Gain(0);
		W_812_AD_Set_Channel(0);
		G11=0.25;
		m_dLTargetEccentricity = dlg.m_dTargetEccentricity;
		m_dFastMoveDistance = dlg.m_dFastMoveDistance;
		m_intTimes = dlg.m_intTimes;
		m_intTimes2=m_intTimes;
		m_dDistance2 = dlg.m_dDistance;
		if (IDOK == MessageBox("ȷ������������!",NULL,MB_ICONASTERISK|MB_OKCANCEL))
		{
			KillTimer(12);
				m_bDongTai=FALSE;
			long lPulse;
			lPulse = -m_dFastMoveDistance*1000/0.078;
			set_profile(m_lzhu_n,1000,5000,1000);
			fast_pmove(m_lzhu_n,lPulse);
			m_fStateMessage="�Զ���ƽ";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			SetTimer(20,10,NULL);
		}
	}
	
}
void CMainFrame::OnAjustCenterandLevel()
{

	CDlgAjustCenterAndPose dlg;
	if (IDOK==dlg.DoModal())
	{
		W_812_AD_Set_Gain(0);
		W_812_AD_Set_Channel(0);
		G11=0.25;
		m_dHTargetEccentricity=dlg.m_dHTargetEccentricity;
		m_dLTargetEccentricity=dlg.m_dLTargetEccentricity;
		m_dHeight=dlg.m_dHeight;
		m_dDistance=dlg.m_dDistance;
		m_dFastMoveDistance=dlg.m_dFastMoveDistance;
		m_intTimes=dlg.m_intTimes;
		m_intTimes2=m_intTimes;
		//m_fintTimes=dlg.m_intTimes;
		
		KillTimer(12);//�ر��ֶ���
		m_bDongTai=FALSE;
		//���������������˶�
		long lPulse;
		lPulse=m_dFastMoveDistance*1000/0.048;
		set_profile(m_dg_n,1000,8000,4000);//mpc08
		fast_pmove(m_dg_n,lPulse);		
		//������ʱ��5����ʼ���Ĺ��̣�
		m_fStateMessage="�Զ���ƽ����";
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);
		SetTimer(5,10,NULL);
	}
//	OnAdjustOritation();
}
void CMainFrame::OnHReset()
{
	m_fStateMessage="ƽ̨��λ��";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	if(enable_el(1,1)==-1)
		AfxMessageBox("1�����λʹ��ʧ��");
	if(enable_org(1,1)==-1)
		AfxMessageBox("1���ԭ��ʹ��ʧ��");
	if(enable_el(2,1)==-1)
		AfxMessageBox("2�����λʹ��ʧ��");
	if(enable_org(2,1)==-1)
		AfxMessageBox("2���ԭ��ʹ��ʧ��");
	if(enable_el(3,1)==-1)
		AfxMessageBox("3�����λʹ��ʧ��");
	if(enable_org(3,1)==-1)
		AfxMessageBox("3���ԭ��ʹ��ʧ��");
	if(enable_el(4,1)==-1)
		AfxMessageBox("4�����λʹ��ʧ��");
	if(enable_org(4,1)==-1)
		AfxMessageBox("4���ԭ��ʹ��ʧ��");
		set_home_mode(1,0);
	set_home_mode(2,0);
	set_home_mode(3,0);
	set_home_mode(4,0);
	
	set_conspeed(1,50000);
	set_conspeed(2,50000);
	set_conspeed(3,50000);
	set_conspeed(4,50000);
	con_vmove2(1,-1,2,-1);
	con_vmove2(3,-1,4,-1);
	SetTimer(71,10,NULL);
}

void CMainFrame::Timer71()
{
	if(m_breset1&&(check_limit(1)==-1))
	{
		set_conspeed(1,50000);
		con_hmove(1,1);
		m_breset1=false;
	}
	if(m_breset2&&(check_limit(2)==-1))
	{
		set_conspeed(2,50000);
		con_hmove(2,1);
		m_breset2=false;
	}
	if(m_breset3&&(check_limit(3)==-1))
	{
		set_conspeed(3,50000);
		con_hmove(3,1);
		m_breset3=false;
	}
	if(m_breset4&&(check_limit(4)==-1))
	{
		set_conspeed(4,50000);
		con_hmove(4,1);
		m_breset4=false;
	}
	if(!(m_breset1||m_breset2||m_breset3||m_breset4))
	{
		KillTimer(71);
		SetTimer(72,10,NULL);
	}
}
void CMainFrame::Timer72()
{
	if((check_home(1)==1))
		m_breset1=true;
	if((check_home(2)==1))
		m_breset2=true;
	if((check_home(3)==1))
		m_breset3=true;
	if((check_home(4)==1))
		m_breset4=true;
	if(m_breset1&&m_breset2&&m_breset3&&m_breset4)
	{
		KillTimer(72);
		m_fStateMessage="ƽ̨��λ���";
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	}
}


/////////////////////////=================//////////////////=======///////===========///////////==========////////////
void CMainFrame::OnDoCircle() 
{
	// TODO: Add your command handler code here
	char BASED_CODE szFilter[] = "Բ���ļ�(*.rds)|*.rds";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if (IDOK!=dlg.DoModal())
	{
		return;
	}
	m_fullPath="";
	m_fullPath=dlg.GetPathName();
	
	if (m_fullPath!="")	
	{	
		if (m_DoCircle!=NULL)
		{
			m_DoCircle->MDIActivate();
			m_DoCircle->RedrawWindow();
			return;
		}
		m_DoCircle=new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoCircle);
		if (!m_DoCircle->LoadFrame(IDI_ICON17,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,
			this,&context))
		{
			return;
		}
		AddVIEW(m_DoCircle);
		m_DoCircle->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoCircle->InitialUpdateFrame(NULL,TRUE);
	}
	
}

void CMainFrame::OnDoCylinder()
{
	char BASED_CODE szFilter[] = "Բ�����ļ�(*.cyd)|*.cyd";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if (IDOK!=dlg.DoModal())
	{
		return;
	}
	m_fullPath2=dlg.GetPathName();
	if (m_fullPath2!="")
	{	
		if (m_DoCylinder!=NULL)
		{
			m_DoCylinder->MDIActivate();
			m_DoCylinder->RedrawWindow();
			return;
		}
		m_DoCylinder=new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoCylinder);
		if (!m_DoCylinder->LoadFrame(IDI_PIST,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoCylinder);
		m_DoCylinder->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoCylinder->InitialUpdateFrame(NULL,TRUE);
	}

}

void CMainFrame::OnDoStraightness() 
{
	// TODO: Add your command handler code here
	char BASED_CODE szFilter[] = "ֱ�߶��ļ�(*.zxd)|*.zxd";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if (IDOK!=dlg.DoModal())
	{
		return;
	}
	m_fullPath3=dlg.GetPathName();
	if (m_fullPath3!="")
	{	
		if (m_DoStraightness!=NULL)
		{
			m_DoStraightness->MDIActivate();
			m_DoStraightness->RedrawWindow();
			return;
		}
		m_DoStraightness=new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoStraightness);
		if (!m_DoStraightness->LoadFrame(IDI_PIST,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoStraightness);
		m_DoStraightness->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoStraightness->InitialUpdateFrame(NULL,TRUE);
	}
}

void CMainFrame::OnDoParallelism() 
{
	// TODO: Add your command handler code here
	char BASED_CODE szFilter[] = "ƽ�ж��ļ�(*.pxd)|*.pxd";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if (IDOK!=dlg.DoModal())
	{
		return;
	}
	m_fullPath4="";
	m_fullPath4=dlg.GetPathName();
	
	if (m_fullPath4!="")
	{	
		if (m_DoParallelism!=NULL)
		{
			m_DoParallelism->MDIActivate();
			m_DoParallelism->RedrawWindow();
			return;
		}
		m_DoParallelism=new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoParallelism);
		if (!m_DoParallelism->LoadFrame(IDI_PXD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,
									this,&context))
		{
			return;
		}
		AddVIEW(m_DoParallelism);
		m_DoParallelism->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoParallelism->InitialUpdateFrame(NULL,TRUE);
	}
}

void CMainFrame::OnDoPlaneness() 
{
	// TODO: Add your command handler code here
	char BASED_CODE szFilter[] = "ƽ����ļ�(*.pmd)|*.pmd";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if (IDOK!=dlg.DoModal())
	{
		return;
	}
	m_fullPath5="";
	m_fullPath5=dlg.GetPathName();
	if (m_fullPath5!="")
	{	
		if (m_DoPlaneness!=NULL)
		{
			m_DoPlaneness->MDIActivate();
			m_DoPlaneness->RedrawWindow();
			return;
		}
		m_DoPlaneness = new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoPlaneness);
		if (!m_DoPlaneness->LoadFrame(IDI_PMD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoPlaneness);
		m_DoPlaneness->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoPlaneness->InitialUpdateFrame(NULL,TRUE);
	}
}
//�˵�����ͬ���
void CMainFrame::OnDocoaxiality() 
{
	char BASED_CODE szFilter[] = "ͬ����ļ�(*.tzd)|*.tzd";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if (IDOK!=dlg.DoModal())
	{
		return;
	}
	m_fullPath7=dlg.GetPathName();
	if (m_fullPath7!="")
	{	
		if (m_DoCoaxiality!=NULL)
		{
			m_DoCoaxiality->MDIActivate();
			m_DoCoaxiality->RedrawWindow();
			return;
		}
		m_DoCoaxiality = new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoCoaxiality);
		if (!m_DoCoaxiality->LoadFrame(IDI_TZD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoCoaxiality);
		m_DoCoaxiality->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoCoaxiality->InitialUpdateFrame(NULL,TRUE);
	}
}
void CMainFrame::OnDoverticality() 
{
	// TODO: Add your command handler code here
	char BASED_CODE szFilter[] = "��ֱ���ļ�(*.czd)|*.czd";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if (IDOK!=dlg.DoModal())
	{
		return;
	}
	m_fullPath8="";
	m_fullPath8=dlg.GetPathName();
	if (m_fullPath8!="")
	{	
		if (m_DoVerticality!=NULL)
		{
			m_DoVerticality->MDIActivate();
			m_DoVerticality->RedrawWindow();
			return;
		}
		m_DoVerticality = new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoVerticality);
		if (!m_DoVerticality->LoadFrame(IDI_TZD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		{
			return;
		}
		AddVIEW(m_DoVerticality);
		m_DoVerticality->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoVerticality->InitialUpdateFrame(NULL,TRUE);
	}
}
void CMainFrame::DoJMAnalyse()
{
	if (m_fullJMPath!="")
	{	
		if (m_DoJMAnalyse!=NULL)
		{
			m_DoJMAnalyse->MDIActivate();
			m_DoJMAnalyse->RedrawWindow();
			return;
		}
		m_DoJMAnalyse=new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CJMAnalyse);
		if (!m_DoJMAnalyse->LoadFrame(IDI_ICON17,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,
			this,&context))
		{
			return;
		}
		AddVIEW(m_DoJMAnalyse);
		m_DoJMAnalyse->ShowWindow(SW_SHOWMAXIMIZED);
		m_DoJMAnalyse->InitialUpdateFrame(NULL,TRUE);
	}
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMainFrame::SetToolBarState(int index,BOOL bstate)
{
	switch(index) {
	case 1: 
		if(bstate) 
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNCHULI,TBSTATE_ENABLED);
		else 
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNCHULI,TBSTATE_HIDDEN);
		break;
	case 2: 
		if(bstate) 
		{
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNDISABLE,TBSTATE_ENABLED);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNENABLE,TBSTATE_HIDDEN);
		}
		else
		{
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNDISABLE,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNENABLE,TBSTATE_ENABLED);
		}
		break;
	case 3:
		if (bstate)
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNSETORIGIN,TBSTATE_ENABLED);
		else
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNSETORIGIN,TBSTATE_ENABLED);
		break;
	case 4:
		if (bstate)
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNSETOTHERS,TBSTATE_ENABLED);
		else
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNSETOTHERS,TBSTATE_HIDDEN);
		break;
	case 5:
		if (bstate)
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTLEFT,TBSTATE_ENABLED);
		else
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTLEFT,TBSTATE_HIDDEN);
		break;
	case 6:
		if(bstate)
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTRIGHT,TBSTATE_ENABLED);
		else
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTRIGHT,TBSTATE_HIDDEN);
		break;
	case 7:
		if (bstate)
		{ 
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNFENDUANCHULI,TBSTATE_ENABLED);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNYUANDUCHULI,TBSTATE_HIDDEN);
		}
		else
		{
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNFENDUANCHULI,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNYUANDUCHULI,TBSTATE_ENABLED);
		}
		break;
	case 8:
		if (bstate)
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNRESETDEAL,TBSTATE_ENABLED);
		else
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNRESETDEAL,TBSTATE_HIDDEN);
		break;
	case 9:
		if (bstate)
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNBGFX,TBSTATE_ENABLED);
		else
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNBGFX,TBSTATE_HIDDEN);
		break;
	case 10:
		if (bstate)
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNPPFX,TBSTATE_ENABLED);
		else
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNPPFX,TBSTATE_HIDDEN);
		break;
	case 11:
		if (bstate)
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNDELETE,TBSTATE_ENABLED);
		else
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNDELETE,TBSTATE_HIDDEN);
		break;	
	case 12:
		if (bstate)
			m_wndToolBar.GetToolBarCtrl().SetState(ID_AmplifyScale,TBSTATE_ENABLED);
		else
			m_wndToolBar.GetToolBarCtrl().SetState(ID_AmplifyScale,TBSTATE_HIDDEN);
		break;	
	case 13:
		if(bstate)
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTBEGIN,TBSTATE_ENABLED);
		else
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTBEGIN,TBSTATE_HIDDEN);
		break;
	case 14:
		if(bstate)
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTSTOP,TBSTATE_ENABLED);
		else
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTSTOP,TBSTATE_HIDDEN);
		break;
	default:		
		{
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNCHULI,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNDISABLE,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNENABLE,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNSETORIGIN,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNSETOTHERS,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTLEFT,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTRIGHT,TBSTATE_HIDDEN);
            m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTBEGIN,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNTSTOP,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNFENDUANCHULI,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNYUANDUCHULI,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNRESETDEAL,TBSTATE_HIDDEN);	
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNBGFX,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNPPFX,TBSTATE_HIDDEN);
			m_wndToolBar.GetToolBarCtrl().SetState(ID_BTNDELETE,TBSTATE_HIDDEN);
            m_wndToolBar.GetToolBarCtrl().SetState(ID_AmplifyScale,TBSTATE_HIDDEN);
		}
	}
	RecalcLayout();
}

int CMainFrame::InitBoard()//��ʼ��MPC08�忨
{
	int Rtn;//,i;
	CString str;

	//��ʼ���忨
	Rtn=auto_set();		//�Զ�����
	if(Rtn<=0)
	{   
		if(Rtn==-1)
		AfxMessageBox("��ⲻ����!",MB_OK);
		if(Rtn==-10)
		AfxMessageBox("ʹ�ö࿨���䲻��!",MB_OK);
	}
	
/*	glTotalAxes = Rtn;/ *��Rtn��ֵ��glTotalAxes* /*/

	Rtn=init_board();
	//��ʼ��
	if(Rtn<=0)
	{
		if(Rtn == -5)
		{
			AfxMessageBox("��̬���ӿ����������İ汾����",MB_OK);
		}
		else if(Rtn == -6)
		{
			AfxMessageBox("Ӳ���汾����",MB_OK);
		}
		else
		{
			AfxMessageBox("��ʼ������!",MB_OK);
		}
	}
	else
	{
	//	str.Format("����=%d",Rtn);
		//AfxMessageBox(str);
	}

	//�����������ĳ�ʼ��
	for (int i=1;i<9;i++)
	{
		
		set_getpos_mode(i,1);
		set_encoder_mode(i,0,1,0);
		set_el_logic(i,0);
		enable_el(i,0);
		enable_sd(i,0);
		enable_org(i,0);
	}
	set_maxspeed(m_pingtaix_n,3000);
	set_maxspeed(m_pingtaiy_n,3000);
	set_maxspeed(m_zhituifir_n,3000);
	set_maxspeed(m_zhituisec_n,3000);
	set_maxspeed(m_dg_n,40000);
	set_maxspeed(m_lzhu_n,60000);

// 	���ݲɼ��忨�ĳ�ʼ��
// 
     W_812_Initial(0,0x220);//��ʼ�����ݲɼ��忨
   	W_812_AD_Set_Channel (0);//��̽ͷ������ͨ��
 	W_812_AD_Set_Gain(0);//���÷Ŵ���,��ѹ�ķ�Χ
     W_812_AD_Set_Mode (A8112_AD_MODE_4);// // 
	return 0;
}

void CMainFrame::OnZhituidianjisecondU() 
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	double vel=0;
	double distance=0;
	int ret;
	ret=dlg.DoModal();
	if(ret==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
		vel=dlg.m_dVelocity;
	}
	else
	{
		return;
	}
	m_fStateMessage="֧��2�����˶�";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	long com;
	CString m_encoder;
	get_abs_pos(m_pingtaix_enn,&com);
	m_old_ptxpulse=com;
	get_abs_pos(m_pingtaiy_enn,&com);
	m_old_ptypulse=com;	
	get_abs_pos(m_zhituifir_enn,&com);
	m_old_zhituifirpulse=com;
	get_abs_pos(m_zhituisec_enn,&com);
	m_old_zhituisecpulse=com;
	set_profile(m_zhituisec_n,500,vel/0.00003,110000/6);
	fast_pmove(m_zhituisec_n,m_distancePulse*1000/0.075);    
	m_stop_flag1=3;
	SetTimer(13,10,NULL);	// TODO: Add your command h// TODO: Add your command handler code here
	
}

void CMainFrame::OnZhituidianjisecondD() 
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	double vel=0;
	double distance=0;
	int ret;
	ret=dlg.DoModal();
	if(ret==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
		vel=dlg.m_dVelocity;
	}
	else
	{
		return;
	}
	m_fStateMessage="֧��2�����˶�";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	long com;
	CString m_encoder;
	get_abs_pos(m_pingtaix_enn,&com);
	m_old_ptxpulse=com;
	get_abs_pos(m_pingtaiy_enn,&com);
	m_old_ptypulse=com;	
	get_abs_pos(m_zhituifir_enn,&com);
	m_old_zhituifirpulse=com;
	get_abs_pos(m_zhituisec_enn,&com);
	m_old_zhituisecpulse=com;
	set_profile(m_zhituifir_n,500,vel/0.00003,110000/6);
	fast_pmove(m_zhituifir_n,-m_distancePulse*1000/0.075);    
	m_stop_flag1=3;
	SetTimer(13,10,NULL);	// TODO: Add your command h// TODO: Add your command handler code here
	
}

void CMainFrame::OnZhituidianjifirstU() 
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	double vel=0;
	double distance=0;
	int ret;
	ret=dlg.DoModal();
	if(ret==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
		vel=dlg.m_dVelocity;
	}
	else
	{
		return;
	}
	m_fStateMessage="֧��1�����˶�";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	long com;
	CString m_encoder;
	get_abs_pos(m_pingtaix_enn,&com);
	m_old_ptxpulse=com;
	get_abs_pos(m_pingtaiy_enn,&com);
	m_old_ptypulse=com;	
	get_abs_pos(m_zhituifir_enn,&com);
	m_old_zhituifirpulse=com;
	get_abs_pos(m_zhituisec_enn,&com);
	m_old_zhituisecpulse=com;
	set_profile(m_zhituifir_n,500,vel/0.00003,110000/6);
	fast_pmove(m_zhituifir_n,m_distancePulse*1000/0.075);    
	m_stop_flag1=2;
	SetTimer(13,10,NULL);// TODO: Add your command handler code here

}

void CMainFrame::OnZhituidianjifirstD() 
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	double vel=0;
	double distance=0;
	int ret;
	ret=dlg.DoModal();
	if(ret==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
		vel=dlg.m_dVelocity;
	}
	else
	{
		return;
	}
	m_fStateMessage="֧��1�����˶�";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	long com;
	CString m_encoder;
	get_abs_pos(m_pingtaix_enn,&com);
	m_old_ptxpulse=com;
	get_abs_pos(m_pingtaiy_enn,&com);
	m_old_ptypulse=com;	
	get_abs_pos(m_zhituifir_enn,&com);
	m_old_zhituifirpulse=com;
	get_abs_pos(m_zhituisec_enn,&com);
	m_old_zhituisecpulse=com;
	set_profile(m_zhituifir_n,500,vel/0.00003,110000/6);
	fast_pmove(m_zhituifir_n,-m_distancePulse*1000/0.075);    
	m_stop_flag1=2;
	SetTimer(13,10,NULL);// TODO: Add your command handler code here
	
}

void CMainFrame::OnPingtaiXb() //����
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	double vel=0;
	double distance=0;
	int ret;
	ret=dlg.DoModal();
	if(ret==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
		vel=dlg.m_dVelocity;
	}
	else
	{
         return;
	}
	m_fStateMessage="X���˶�";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	long com;
	CString m_encoder;
	get_abs_pos(m_pingtaix_enn,&com);
	m_old_ptxpulse=com;
	get_abs_pos(m_pingtaiy_enn,&com);
	m_old_ptypulse=com;	
	get_abs_pos(m_zhituifir_enn,&com);
	m_old_zhituifirpulse=com;
	get_abs_pos(m_zhituisec_enn,&com);
	m_old_zhituisecpulse=com;
	set_profile(m_pingtaix_n,500,vel/0.00003,110000/6);
	fast_pmove(m_pingtaix_n,-m_distancePulse*1000/0.075);    
	m_stop_flag1=0;
	SetTimer(13,10,NULL);// TODO: Add your command handler code here
	
}

void CMainFrame::OnPingtaiXf() //ǰ��
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	double vel=0;
	double distance=0;
	int ret;
	ret=dlg.DoModal();
	if(ret==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
		vel=dlg.m_dVelocity;
	}
	else
	{
		return;
	}
	m_fStateMessage="X���˶�";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	long com;
	CString m_encoder;
	get_abs_pos(m_pingtaix_enn,&com);
	m_old_ptxpulse=com;
	get_abs_pos(m_pingtaiy_enn,&com);
	m_old_ptypulse=com;	
	get_abs_pos(m_zhituifir_enn,&com);
	m_old_zhituifirpulse=com;
	get_abs_pos(m_zhituisec_enn,&com);
	m_old_zhituisecpulse=com;
	set_profile(m_pingtaix_n,500,vel/0.00003,110000/6);
	fast_pmove(m_pingtaix_n,m_distancePulse*1000/0.075);    
	m_stop_flag1=0;
	SetTimer(13,10,NULL);///// TODO: Add your command handler code here
	
}

void CMainFrame::OnPingtaiYl() 
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	double vel=0;
	double distance=0;
	int ret;
	ret=dlg.DoModal();
	if(ret==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
		vel=dlg.m_dVelocity;
	}
	else
	{
		return;
	}
	m_fStateMessage="Y���˶�";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	long com;
	CString m_encoder;
	get_abs_pos(m_pingtaix_enn,&com);
	m_old_ptxpulse=com;
	get_abs_pos(m_pingtaiy_enn,&com);
	m_old_ptypulse=com;	
	get_abs_pos(m_zhituifir_enn,&com);
	m_old_zhituifirpulse=com;
	get_abs_pos(m_zhituisec_enn,&com);
	m_old_zhituisecpulse=com;
	set_profile(m_pingtaiy_n,500,vel/0.00003,110000/6);
	fast_pmove(m_pingtaiy_n,m_distancePulse*1000/0.075);    
	m_stop_flag1=1;
	SetTimer(13,10,NULL);// TODO: Add your command handler code here
	
}

void CMainFrame::OnPingtaiYr() 
{
	KillTimer(70);
	CDlgOneAxisPara1 dlg;// TODO: Add your command handler code here
	double vel=0;
	double distance=0;
	int ret;
	ret=dlg.DoModal();
	if(ret==IDOK)
	{
		KillTimer(12);
		m_distancePulse=dlg.m_dPosition;
		m_fVelocityCurSel=dlg.m_cursel;
		vel=dlg.m_dVelocity;
	}
	else
	{
		return;
	}
	m_fStateMessage="Y���˶�";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	long com;
	CString m_encoder;
	get_abs_pos(m_pingtaix_enn,&com);
	m_old_ptxpulse=com;
	get_abs_pos(m_pingtaiy_enn,&com);
	m_old_ptypulse=com;	
	get_abs_pos(m_zhituifir_enn,&com);
	m_old_zhituifirpulse=com;
	get_abs_pos(m_zhituisec_enn,&com);
	m_old_zhituisecpulse=com;
	set_profile(m_pingtaiy_n,500,vel/0.00003,110000/6);
	fast_pmove(m_pingtaiy_n,-m_distancePulse*1000/0.075);    
	m_stop_flag1=1;
	SetTimer(13,10,NULL);	// TODO: Add your command handler code here
	
}

void CMainFrame::Timer13()
{
	if (m_stop_flag1==0)
	{
		if (0 == check_done(m_pingtaix_n) )
		{
			KillTimer(13);
			m_fStateMessage="�˶����";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			sudden_stop(m_pingtaix_n);
		}
	}
	else if(m_stop_flag1==1)
	{
		if (0 == check_done(m_pingtaiy_n) )
		{
			KillTimer(13);
			m_fStateMessage="�˶����";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			sudden_stop(m_pingtaiy_n);
		}	
	}
	else if (m_stop_flag1==2)
	{
		if (0 == check_done(m_zhituifir_n) )
		{
			KillTimer(13);
			m_fStateMessage="�˶����";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			sudden_stop(m_zhituifir_n);
		}	
	}
	else if (m_stop_flag1==3)
	{
		if (0 == check_done(m_zhituisec_n) )
		{
			KillTimer(13);
			m_fStateMessage="�˶����";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			sudden_stop(m_zhituisec_n);
		}	
	}	
}

void CMainFrame::OnCanshuchushi() 
{
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="canshu.ini";
	CCanshuchushi dlg;	    
	CString a;
    ::GetPrivateProfileString("����","B1x","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_B1x=atof(a);// ʹ�Ի�����ʾԭ����ֵ
    ::GetPrivateProfileString("����","B1y","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_B1y=atof(a);
    ::GetPrivateProfileString("����","B1z","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_B1z=atof(a);
    ::GetPrivateProfileString("����","B2x","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_B2x=atof(a);
    ::GetPrivateProfileString("����","B2y","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_B2y=atof(a);
    ::GetPrivateProfileString("����","B2z","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_B2z=atof(a);
    ::GetPrivateProfileString("����","B3x","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_B3x=atof(a);
	::GetPrivateProfileString("����","B3y","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_B3y=atof(a);
	::GetPrivateProfileString("����","B3z","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_B3z=atof(a);
    ::GetPrivateProfileString("����","P1x","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_P1x=atof(a);
    ::GetPrivateProfileString("����","P1y","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_P1y=atof(a);
    ::GetPrivateProfileString("����","P1z","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_P1z=atof(a);
    ::GetPrivateProfileString("����","x0","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_x0=atof(a);
    ::GetPrivateProfileString("����","y0","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_y0=atof(a);
    ::GetPrivateProfileString("����","H0","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_H0=atof(a);
    ::GetPrivateProfileString("����","Angle","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_Angle=atof(a);
    ::GetPrivateProfileString("����","LIMIT","lisi",a.GetBuffer(100),100,strPath);
    dlg.m_LIMIT=atof(a);
    ::GetPrivateProfileString("����","G11","lisi",a.GetBuffer(100),100,strPath);
   // dlg.m_G11=atof(a);
    ::GetPrivateProfileString("����","G22","lisi",a.GetBuffer(100),100,strPath);
  // dlg.m_G22=atof(a);
	
 
	if(IDOK==dlg.DoModal())
	{	
		m_Adjustment.B1x=dlg.m_B1x;// ��CMainframe������ֵ�ĸ���
		CString A1;                // �����º��ֵת�����ַ�����ʽд��INI�ļ�����
		A1.Format("%.20f",dlg.m_B1x);
		:: WritePrivateProfileString("����","B1x",A1,strPath);
		m_Adjustment.B1y=dlg.m_B1y;               
		A1.Format("%.20f",dlg.m_B1y);
		:: WritePrivateProfileString("����","B1y",A1,strPath);
		m_Adjustment.B1z=dlg.m_B1z;		           
		A1.Format("%.20f",dlg.m_B1z);
		:: WritePrivateProfileString("����","B1z",A1,strPath);
		m_Adjustment.B2x=dlg.m_B2x;		             
		A1.Format("%.20f",dlg.m_B2x);
		:: WritePrivateProfileString("����","B2x",A1,strPath);
		m_Adjustment.B2y=dlg.m_B2y;	                
		A1.Format("%.20f",dlg.m_B2y);
		:: WritePrivateProfileString("����","B2y",A1,strPath);
		m_Adjustment.B2z=dlg.m_B2z;	                
		A1.Format("%.20f",dlg.m_B2z);
		:: WritePrivateProfileString("����","B2z",A1,strPath);
		m_Adjustment.B3x=dlg.m_B3x;		              
		A1.Format("%.20f",dlg.m_B3x);
		:: WritePrivateProfileString("����","B3x",A1,strPath);
		m_Adjustment.B3y=dlg.m_B3y;	              
		A1.Format("%.20f",dlg.m_B3y);
		:: WritePrivateProfileString("����","B3y",A1,strPath);
		m_Adjustment.B3z=dlg.m_B3z;	               
		A1.Format("%.20f",dlg.m_B3z);
		:: WritePrivateProfileString("����","B3z",A1,strPath);
		m_Adjustment.P1x=dlg.m_P1x;	                
		A1.Format("%.20f",dlg.m_P1x);
		:: WritePrivateProfileString("����","P1x",A1,strPath);
		m_Adjustment.P1y=dlg.m_P1y;		                
		A1.Format("%.20f",dlg.m_P1y);
		:: WritePrivateProfileString("����","P1y",A1,strPath);
		m_Adjustment.P1z=dlg.m_P1z;	               
		A1.Format("%.20f",dlg.m_P1z);
		:: WritePrivateProfileString("����","P1z",A1,strPath);
		m_Adjustment.x0=dlg.m_x0;	                
		A1.Format("%.20f",dlg.m_x0);
		:: WritePrivateProfileString("����","x0",A1,strPath);
		m_Adjustment.y0=dlg.m_y0;	                
		A1.Format("%.20f",dlg.m_y0);
		:: WritePrivateProfileString("����","y0",A1,strPath);
		m_Adjustment.H0=dlg.m_H0;	                
		A1.Format("%.20f",dlg.m_H0);
		:: WritePrivateProfileString("����","H0",A1,strPath);
		m_Adjustment.Angle=dlg.m_Angle;		               
		A1.Format("%.20f",dlg.m_Angle);
		:: WritePrivateProfileString("����","Angle",A1,strPath);		
		m_Adjustment.LIMIT=dlg.m_LIMIT;		                
		A1.Format("%.20f",dlg.m_LIMIT);
		:: WritePrivateProfileString("����","LIMIT",A1,strPath);			
	}
	else
	{
		return;
	}
}

void CMainFrame::InitdianjiPra()//��ʼ���������
{
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);

	CString a;//����CMainframe�����ֵ
	::GetPrivateProfileString("����","B1x","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.B1x=atof(a);
	::GetPrivateProfileString("����","B1y","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.B1y=atof(a);
	::GetPrivateProfileString("����","B1z","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.B1z=atof(a);
	::GetPrivateProfileString("����","B2x","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.B2x=atof(a);
	::GetPrivateProfileString("����","B2y","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.B2y=atof(a);
	::GetPrivateProfileString("����","B2z","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.B2z=atof(a);
	::GetPrivateProfileString("����","B3x","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.B3x=atof(a);
	::GetPrivateProfileString("����","B3y","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.B3y=atof(a);
	::GetPrivateProfileString("����","B3z","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.B3z=atof(a);
	::GetPrivateProfileString("����","P1x","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.P1x=atof(a);
	::GetPrivateProfileString("����","P1y","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.P1y=atof(a);
	::GetPrivateProfileString("����","P1z","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.P1z=atof(a);
	::GetPrivateProfileString("����","x0","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.x0=atof(a);
	::GetPrivateProfileString("����","y0","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.y0=atof(a);
	::GetPrivateProfileString("����","H0","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_Adjustment.H0=atof(a);
    ::GetPrivateProfileString("����","Angle","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
    m_Adjustment.Angle=atof(a);
    ::GetPrivateProfileString("����","LIMIT","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
    m_Adjustment.LIMIT=atof(a);
	::GetPrivateProfileString("����","G11","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
    G11=atof(a);
	::GetPrivateProfileString("����","G22","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	G22=atof(a);
    ::GetPrivateProfileString("����","m_cursel","",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_fHandVelocity=(atoi(a)*0.5+4.0)*1000/0.075;///////////////////////bilu 
	for(int i=0;i<36;i++)
	{
		::GetPrivateProfileString("����","cf[i]","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
		cf[i]=atof(a);
	}

	::GetPrivateProfileString("����","m_fQKxs","lisi",a.GetBuffer(100),100,strPath+"canshu.ini");
	m_fQKxs=atof(a);

	//strPath+="config.ini";
    ::GetPrivateProfileString("����","YD","",a.GetBuffer(100),100,strPath+"config.ini");
    m_dGongyiPara[0]=atof(a);
	::GetPrivateProfileString("����","YZD","",a.GetBuffer(100),100,strPath+"config.ini");
    m_dGongyiPara[1]=atof(a);
	::GetPrivateProfileString("����","ZXD","",a.GetBuffer(100),100,strPath+"config.ini");
    m_dGongyiPara[2]=atof(a);
	::GetPrivateProfileString("����","PXD","",a.GetBuffer(100),100,strPath+"config.ini");
    m_dGongyiPara[3]=atof(a);
	::GetPrivateProfileString("����","PMD","",a.GetBuffer(100),100,strPath+"config.ini");
    m_dGongyiPara[4]=atof(a);
	::GetPrivateProfileString("����","TZD","",a.GetBuffer(100),100,strPath+"config.ini");
    m_dGongyiPara[5]=atof(a);	
	::GetPrivateProfileString("����","CZD","",a.GetBuffer(100),100,strPath+"config.ini");
    m_dGongyiPara[6]=atof(a);

	char inBuf[10];
	GetPrivateProfileString ("�˲�","����1",NULL,inBuf,10,strPath+".\\Test_ini.ini");
	FilterMode=atoi(inBuf);
	GetPrivateProfileString ("�����㷨","����2",NULL,inBuf,10,strPath+".\\Test_ini.ini");
    CirEvalue=atoi(inBuf);

}

void CMainFrame::OnAdjustPosition() //���Ļ��ƽ
{
	// TODO: Add your command handler code here
	if (m_DoAdjustPosition!=NULL)
	{
		m_DoAdjustPosition->MDIActivate();
		m_DoAdjustPosition->RedrawWindow();
	}
	else
	{
		m_DoAdjustPosition=new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoAdjustPosition);
		if (!m_DoAdjustPosition->LoadFrame(IDI_ICON17,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,
			this,&context))
		{
			return;
		}
		AddVIEW(m_DoAdjustPosition);
		m_DoAdjustPosition->ShowWindow(SW_SHOWMAXIMIZED);
	m_DoAdjustPosition->InitialUpdateFrame(NULL,TRUE);
	}

}


void CMainFrame::OnAdjustOritation() //���ĵ�ƽ
{
	// TODO: Add your command handler code here
	if(m_DoAdjustOritation!=NULL)
	{
		m_DoAdjustOritation->MDIActivate();
		m_DoAdjustOritation->RedrawWindow();
	}
	else
	{
		m_DoAdjustOritation=new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDoAdjustOritation);
		if (!m_DoAdjustOritation->LoadFrame(IDI_CYD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,
			this,&context))
		{
			return;
		}
		AddVIEW(m_DoAdjustOritation);
		m_DoAdjustOritation->ShowWindow(SW_SHOWMAXIMIZED);
		 m_DoAdjustOritation->InitialUpdateFrame(NULL,TRUE);
	}

}

//////////////////////////////////////////////////////////////////////////
/*
   ��ʱ��1-4������Զ����ĵ�����  write by wulei
*/
//////////////////////////////////////////////////////////////////////////
/*
  ��ʱ��1��ʱ�̼������˶��Ƿ���ɣ������ϸ��µ����λ�á�
  �������Ĵ�С���Լ�������λ�á�
*/
void CMainFrame::Timer1()
{
	
	if (0 != check_done(m_dg_n) )
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(1);
		//�������Զ�������������ʱ��2����ɴ������Զ�����
		set_profile(m_dg_n,100,3000,2000);
		fast_vmove(m_dg_n,1);
		SetTimer(2,10,NULL);
	}
}
/*
	��ʱ��2����ȡ��������ֵ���жϴ�������ֵ�Ƿ������ɣ�
	û�е�����ɣ��������ʾ���ݣ�������ɣ�������һ���̡�
*/
void CMainFrame::Timer2()
{
	int		analog_input1=0;
	double	analog_input=0;
	long	com=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -m_Adjustment.LIMIT*0.1)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(2); 
		sudden_stop(m_dg_n);
		//������������㡢��ʾ
		KillTimer(2); 
		sudden_stop(m_dg_n);
		//������������㡢��ʾ
		SetTimer(3,10,NULL);
	}
}
/*
   ��ʱ��3�����Բ�����ݵĲ���������ƫ��������ʾ
*/
void CMainFrame::Timer3()
{
	KillTimer(3);
	int ret=666;		 
	unsigned short pMem[3600];
	double pMem2[3600];
	double temp[2];
	double templimit;
	
	memset(pMem, 0, sizeof(pMem));
	//��������

    ret=WLS_8112PG_WaitZeroMinus_dlg();
	if(ret==-1)
	{
		AfxMessageBox("����λʧ��");
		return;
	}
    ret=WLS_8112PG_AD_INT_Sampling_dlg(0,0,3600, pMem, 2, 100, 45);
	//���ݴ���
	for(int i=0;i<3600;i++)
	{
		pMem2[i]=pMem[i];
		m_down_circledata[i]=pMem[i];
		pMem2[i]=((pMem2[i]-2048)*10)/(G11*G22*4096)*0.001;
	}	  
	templimit=((4096-2048)*10)/(G11*G22*4096)*0.001;
	ret=100;
	ret=m_Adjustment.Celiang(pMem2,templimit,temp);
	m_down_pxin=temp[0];//��λ����
	m_down_angle=temp[1];
	if(-1==ret)
	{
		AfxMessageBox("������Ч���ݹ��٣������°�װ�����!",MB_ICONWARNING);
		//����ʧ�ܺ������ֶ�����
		m_fStateMessage="״̬��Ϣ";
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);
		SetTimer(12,10,NULL);
	}
	else
	{
		//��ʾ�������
		m_fintTimes=m_intTimes-m_intTimes2;
		OnAdjustPosition();
		//�ж�ƫ���Ƿ������趨Ҫ���������Ҫ���ٵ���
		//�����������
		if (m_down_pxin*1000<m_dLTargetEccentricity)
		{
			m_fStateMessage="�������";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			AfxMessageBox("�������!");
			//������ɺ������ֶ�����
			SetTimer(12,10,NULL);
		}
		else	
		{
			//�жϵ��������Ѿ����
			if (m_intTimes2<=0)
			{
				m_fStateMessage="��������";
				m_wndStatusBar.SetPaneText(1,m_fStateMessage);
				AfxMessageBox("������ɣ�δ�ﵽĿ��Ҫ�������µ���",MB_ICONWARNING);
				//������ɺ������ֶ�����
				SetTimer(12,10,NULL);
			} 
			else
			{	
				//����֧���˶���
				double CenterLow[3] = {m_down_pxin*cos(-3.14*m_down_angle/180),
					m_down_pxin*sin(-3.14*m_down_angle/180),0};
				double LegMov[4] = {0, 0, 0, 0};
				int rtn=-1;
				rtn=m_Adjustment.UAdjustPositin(CenterLow,LegMov);
				if(rtn!=0)
				{
					m_fStateMessage="ERROR";
					m_wndStatusBar.SetPaneText(1,m_fStateMessage);
					MessageBox("ERROR!");
					//����ʧ�ܣ������ֶ�����
					SetTimer(12,10,NULL);
				}
				else
				{				
					set_profile(m_dg_n,100,1000,1000);
					fast_pmove(m_dg_n,-2000);
					PlatformMoveAll(m_down_pxin,cf,LegMov);
					m_intTimes2--;
					SetTimer(4,10,NULL);
				}				
			}
		}
	}
	
}
/*
	��ʱ��4�����ƽ̨���������״̬��������������λ�ˣ�
	���˳��������������������У��������һ��ѭ����
*/
void CMainFrame::Timer4()
{
	//����Ƿ�����λ
	int status[4] = {0,0,0,0};
	status[0] = check_limit(m_zhituifir_n);
	status[1] = check_limit(m_zhituisec_n);
	status[2] = check_limit(m_pingtaix_n);
	status[3] = check_limit(m_pingtaiy_n);
	if ((status[0]==0) && (status[1]==0) && (status[2]==0) && (status[3]==0))
	{
		//����Ƿ����еĵ��������˶�
		if((0==check_done(m_zhituifir_n))&&(0==check_done(m_zhituisec_n))&&
			(0==check_done(m_pingtaix_n))&&(0==check_done(m_pingtaiy_n))&&
			(0==check_done(m_dg_n)))
		{
			//���������ɣ���ֹͣ��ʱ��4
			KillTimer(4);
			set_profile(m_dg_n,100,3000,2000);
			fast_vmove(m_dg_n,1);
			SetTimer(2,10,NULL);
		}
	} 
	else
	{
		//������λ��������ֹͣ���е��������
		KillTimer(4);
		sudden_stop(m_zhituifir_n);
		sudden_stop(m_zhituisec_n);
		sudden_stop(m_pingtaix_n);
		sudden_stop(m_pingtaiy_n);
		CheckDianji(status);
	}
	UpdataDisplayBar();
}
//////////////////////////////////////////////////////////////////////////
/*
    ��ʱ��5-8,14-19��ɵ�ƽ���Ĺ���            write by wulei 
*/
//////////////////////////////////////////////////////////////////////////

//��ʱ��5����ɿ��ٿ�������
void CMainFrame::Timer5()
{
	
	if (0 != check_done(m_dg_n))
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(5);
		//�������Զ�������������ʱ��6����ɴ������Զ�����
		set_profile(m_dg_n,100,3000,2000);
		fast_vmove(m_dg_n,1);
		SetTimer(6,10,NULL);
	}
}
//��ʱ��6����ɴ������Զ���������
void CMainFrame::Timer6()
{
	int		analog_input1=0;
	double	analog_input=0;
	long	com=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -m_Adjustment.LIMIT*0.3)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(6);
		sudden_stop(m_dg_n);
		//������������㡢��ʾ
		SetTimer(7,10,NULL);
	}
}
//��ʱ��7 ����²����ݵĲ���
void CMainFrame::Timer7()
{
	KillTimer(7);
	int ret=666;		 
	unsigned short pMem[3600];
	double pMem2[3600];
	double temp[2];
	double templimit;
	
	memset(pMem, 0, sizeof(pMem));
	//��������
    ret=WLS_8112PG_WaitZeroMinus_dlg();
	if(ret==-1)
	{
		AfxMessageBox("����λʧ��");
		return;
	}
    ret=WLS_8112PG_AD_INT_Sampling_dlg(0,0,3600, pMem, 2, 100, 45);
	//���ݴ���
	for(int i=0;i<3600;i++)
	{
		pMem2[i]=pMem[i];
		m_down_circledata[i]=pMem[i];
		pMem2[i]=((pMem2[i]-2048)*10)/(G11*G22*4096)*0.001;
	}	  
	templimit=((4096-2048)*10)/(G11*G22*4096)*0.001;
	ret=100;
	ret=m_Adjustment.Celiang(pMem2,templimit,temp);
	m_down_pxin=temp[0];
	m_down_angle=temp[1];
	if(-1==ret)
	{
		AfxMessageBox("������Ч���ݹ��٣������°�װ�����!",MB_ICONWARNING);
		//����ʧ�ܺ������ֶ�����
		m_fStateMessage="״̬��Ϣ";
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);
		SetTimer(12,10,NULL);
	}
	else
	{		
		long lPulse;
		lPulse=-m_dDistance*1000/0.024;
		set_profile(m_dg_n,100,5000,4000);//mpc08
		fast_pmove(m_dg_n,lPulse);//////////////////����ĺ���	
		SetTimer(8,10,NULL);
	}			
}
//��ʱ8 ����ɵ���ĺ���
void CMainFrame::Timer8()
{
	if (0 != check_done(m_dg_n))
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(8);
		long lPulse;
		long com;
		get_abs_pos(m_lzhu_enn,&com);
		m_old_lzhupulse = com;
		lPulse = 1.1*m_dHeight*1000/0.078;
		set_profile(m_lzhu_n,3000,70000,15000);
		fast_pmove(m_lzhu_n,lPulse);//��������
        SetTimer(14,10,NULL);
	}
}
//��ʱ��14������������������
void CMainFrame::Timer14()
{
	UpdataDisplayBar();
	long com;
	get_abs_pos(m_lzhu_enn,&com);
	double ht;
	ht = (com-m_old_lzhupulse)*m_lzxishu;
	if (ht >= (m_dHeight ))
	{
		KillTimer(14);
		sudden_stop(m_lzhu_n);
		long lPulse;//������ٿ���
		lPulse = m_dDistance*1000*0.95/0.024;//�뿪����
		set_profile(m_dg_n,100,5000,4000);//mpc08
		fast_pmove(m_dg_n,lPulse);
		SetTimer(15,10,NULL);
	}

}
//��ʱ��15����ɵ�������ǰ��
void CMainFrame::Timer15()
{
	if (0 != check_done(m_dg_n))
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(15);
		//������ʱ��16����ɵ���Զ������϶���
		set_profile(m_dg_n,100,3000,2000);
		fast_vmove(m_dg_n,1);
		SetTimer(16,10,NULL);
	}
}
//��ʱ��16������϶��洫�����Զ�����
void CMainFrame::Timer16()
{
	int		analog_input1 = 0;
	double	analog_input = 0;
	long	com=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -m_Adjustment.LIMIT*0.3)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(16); 
		sudden_stop(m_dg_n);
		//������������㡢��ʾ
		SetTimer(17,10,NULL);
	}
}
//��ʱ��17������϶�����������������ʾ������
void CMainFrame::Timer17()
{
	KillTimer(17);
	int ret=666;		 
	unsigned short pMem[3600];
	double pMem2[3600];
	double temp[2];
	double templimit;
	
	memset(pMem, 0, sizeof(pMem));
	//��������
    ret=WLS_8112PG_WaitZeroMinus_dlg();
	if(ret==-1)
	{
		AfxMessageBox("����λʧ��");
		return;
	}
    ret=WLS_8112PG_AD_INT_Sampling_dlg(0,0,3600, pMem, 2, 100, 45);
	//���ݴ���
	for(int i=0;i<3600;i++)
	{
		pMem2[i]=pMem[i];
		m_up_circledata[i]=pMem[i];
		pMem2[i]=((pMem2[i]-2048)*10)/(G11*G22*4096)*0.001;
	}	  
	templimit=((4096-2048)*10)/(G11*G22*4096)*0.001;
	ret=100;
	ret=m_Adjustment.Celiang(pMem2,templimit,temp);
	m_up_pxin=temp[0];
	m_up_angle=temp[1];
	if(-1==ret)
	{
		AfxMessageBox("������Ч���ݹ��٣������°�װ�����!",MB_ICONWARNING);
		//����ʧ�ܺ������ֶ�����
		m_fStateMessage="״̬��Ϣ";
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);
		SetTimer(12,10,NULL);
	}
	else
	{	
		//��ʾ�������
		m_fintTimes=m_intTimes-m_intTimes2;
		OnAdjustOritation();
		if ((m_down_pxin*1000 < m_dLTargetEccentricity) && 
			(m_up_pxin*1000 < m_dHTargetEccentricity))
		{
			
			m_fStateMessage="�������";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			//������ɺ������ֶ�����
			SetTimer(12,10,NULL);
			AfxMessageBox("�������!");
		}
		else	
		{
			//�жϵ��������Ѿ����
			if (m_intTimes2<=0)
			{
				AfxMessageBox("������ɣ�δ�ﵽĿ��Ҫ�������µ���",MB_ICONWARNING);
				//������ɺ������ֶ�����
				m_fStateMessage="��������";
				m_wndStatusBar.SetPaneText(1,m_fStateMessage);
				SetTimer(12,10,NULL);
			} 
			else
			{	
				//����֧���˶���
				double CenterLow[3] = {m_down_pxin*cos(-3.14*m_down_angle/180),
					m_down_pxin*sin(-3.14*m_down_angle/180),0};
				long com=0;
				get_abs_pos(m_lzhu_enn,&com);
				double CenterHigh[3] = {m_up_pxin*cos(-3.14*m_up_angle/180),
					m_up_pxin*sin(-3.14*m_up_angle/180),(com-m_old_lzhupulse)*0.004};///////
				double LegMov[4] = {0, 0, 0, 0};
				int rtn=-1;
				rtn=m_Adjustment.UMotionComput(CenterLow,CenterHigh,LegMov);//////////��ѧ��
				if(rtn!=0)
				{					
					m_fStateMessage="ERROR";
					m_wndStatusBar.SetPaneText(1,m_fStateMessage);
					MessageBox("ERROR!");
					//����ʧ�ܣ������ֶ�����
					SetTimer(12,10,NULL);
				}
				else
				{
					//��ʼִ���˶�����������һ����
					double cf[36];
					for (int i=0;i<36;i++)
					{
						cf[i]=1;
					}
					long lPulse;
					lPulse=m_dDistance*1000*0.95/0.024;//tiaozheng 
					set_profile(m_dg_n,100,1000,1000);
					fast_pmove(m_dg_n,-lPulse);
					PlatformMoveAll(m_down_pxin,cf,LegMov);
					m_intTimes2--;
					SetTimer(18,10,NULL);
				}				
			}
		}
	}		
}
//  ��ʱ��18�����ƽ̨���������״̬��������������λ�ˣ�
//	���˳��������������������У��������һ��ѭ����
void CMainFrame::Timer18()
{
	//����Ƿ�����λ
	int status[4] = {0,0,0,0};
	status[0] = check_limit(m_zhituifir_n);
	status[1] = check_limit(m_zhituisec_n);
	status[2] = check_limit(m_pingtaix_n);
	status[3] = check_limit(m_pingtaiy_n);
	if ((status[0]==0) && (status[1]==0) 
		&& (status[2]==0) && (status[3]==0))
	{
		//����Ƿ����еĵ��������˶�
		if((0==check_done(m_zhituifir_n))&&(0==check_done(m_zhituisec_n))&&
			(0==check_done(m_pingtaix_n))&&(0==check_done(m_pingtaiy_n))&&
			(0==check_done(m_dg_n)))
		{
			//���������ɣ���ֹͣ��ʱ��18������������ƣ�������һ�εĵ�������
			KillTimer(18);	
			long lPulse;
			long com;
			get_abs_pos(m_lzhu_enn,&com);
			m_old_lzhupulse = com;
			lPulse = -m_dHeight*1000/0.078;
			set_profile(m_lzhu_n,3000,70000,15000);
			fast_pmove(m_lzhu_n,lPulse);
			SetTimer(19,10,NULL);
		}
	} 
	else
	{
		//������λ��������ֹͣ���е��������
		KillTimer(18);
		sudden_stop(m_zhituifir_n);
		sudden_stop(m_zhituisec_n);
		sudden_stop(m_pingtaix_n);
		sudden_stop(m_pingtaiy_n);
		CheckDianji(status);
	}
	UpdataDisplayBar();
}
//��ʱ��19����ɵ������
void CMainFrame::Timer19()
{
	UpdataDisplayBar();
	long com;
	get_abs_pos(m_lzhu_enn,&com);
	double ht;
	ht = -(com-m_old_lzhupulse)*m_lzxishu;
	if (ht >= (m_dHeight * 0.999))
	{
		KillTimer(19);
		sudden_stop(m_lzhu_n);
		//������ʱ��5����ʼ��һ�εĵ��������׶�
		long lPulse;
		lPulse = m_dDistance*1000*0.95/0.024;
		set_profile(m_dg_n,100,5000,4000);//mpc08
		fast_pmove(m_dg_n,lPulse);
		SetTimer(5,10,NULL);
	}
}

/*
	��ʱ��20-�����ƽ̨�ĵ�ƽ���̣� write by wulei
*/
//��ʱ��20 ��ɵ�ƽ���̵Ŀ����ƶ�����
void CMainFrame::Timer20()
{
	
	if (0 != check_done(m_lzhu_n))
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(20);
		//�������Զ�������������ʱ��21����ɴ������Զ�����
		set_profile(m_lzhu_n,100,1500,1000);
		fast_vmove(m_lzhu_n,-1);
		SetTimer(21,10,NULL);
	}
}

//��ʱ��21 ��ɵ�ƽ���̵Ĵ������Զ���������
void CMainFrame::Timer21()
{

	int		analog_input1=0;
	double	analog_input=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -m_Adjustment.LIMIT*0.3)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(21); 
		sudden_stop(m_lzhu_n);  
		//������������㡢��ʾ
		SetTimer(22,10,NULL);
	}
}
//��ʱ��22 ��ɵ�ƽ���̵Ĳ������������ʾ
void CMainFrame::Timer22()
{
	KillTimer(22);
	int ret=666;		 
	unsigned short pMem[3600];
	double pMem2[3600];
	double temp[2];
	double templimit;
	
	memset(pMem, 0, sizeof(pMem));
	//��������

    ret=WLS_8112PG_WaitZeroMinus_dlg();
	if(ret==-1)
	{
		AfxMessageBox("����λʧ��");
		return;
	}
    ret=WLS_8112PG_AD_INT_Sampling_dlg(0,0,3600, pMem, 2, 100, 45);
	//���ݴ���
	for(int i=0;i<3600;i++)
	{
		pMem2[i]=pMem[i];
		m_down_circledata[i]=pMem[i];
		pMem2[i]=((pMem2[i]-2048)*10)/(G11*G22*4096)*0.001;
	}	  
	templimit=((4096-2048)*10)/(G11*G22*4096)*0.001;
		ret=100;
		ret=m_Adjustment.Celiang(pMem2,templimit,temp);
		m_down_pxin=temp[0];
		m_down_angle=temp[1];
		if(-1==ret)
		{
			AfxMessageBox("������Ч���ݹ��٣������°�װ�����!",MB_ICONWARNING);
			//����ʧ�ܺ������ֶ�����
			m_fStateMessage="״̬��Ϣ";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			SetTimer(12,10,NULL);
		}
		else
		{
			//��ʾ�������
			m_fintTimes=m_intTimes-m_intTimes2;
			OnAdjustPosition();
			//�ж�ƫ���Ƿ������趨Ҫ���������Ҫ���ٵ���
			//�����������
			if (m_down_pxin*1000<m_dLTargetEccentricity)
			{
				//������ɺ������ֶ�����
				m_fStateMessage="�������";
				m_wndStatusBar.SetPaneText(1,m_fStateMessage);
				SetTimer(12,10,NULL);
				AfxMessageBox("�������!");
			}
			else	
			{
				//�жϵ��������Ѿ����
				if (m_intTimes2<=0)
				{
					m_fStateMessage="��������";
					m_wndStatusBar.SetPaneText(1,m_fStateMessage);
					AfxMessageBox("������ɣ�δ�ﵽĿ��Ҫ�������µ���",MB_ICONWARNING);
					//������ɺ������ֶ�����
					SetTimer(12,10,NULL);
				} 
				else
				{	
					//����֧���˶���
					double LegMov[4] = {0, 0, 0, 0};
					int rtn=-1;
					rtn=m_Adjustment.AdjustPlatOritation(pMem2,m_dDistance2,LegMov);
					if(rtn!=0)
					{
						m_fStateMessage="ERROR";
						m_wndStatusBar.SetPaneText(1,m_fStateMessage);
						MessageBox("ERROR!");
						//����ʧ�ܣ������ֶ�����
						SetTimer(12,10,NULL);
					}
					else
					{
						//��ʼִ���˶�����������һ����
						/*double cf[36];
						for (int i=0;i<36;i++)
						{
							cf[i]=1;
						}*/					
						set_profile(m_lzhu_n,100,2000,1000);
						fast_pmove(m_lzhu_n,1000);
						PlatformMoveAll(m_down_pxin,m_pingjing_cf,LegMov);
						m_intTimes2--;
						SetTimer(23,10,NULL);
					}				
				}
			}
		}		
	
}
//  ��ʱ��23�����ƽ̨���������״̬��������������λ�ˣ�
//	���˳��������������������У��������һ��ѭ����
void CMainFrame::Timer23()
{
	int status[4] = {0,0,0,0};
	status[0] = check_limit(m_zhituifir_n);
	status[1] = check_limit(m_zhituisec_n);
	status[2] = check_limit(m_pingtaix_n);
	status[3] = check_limit(m_pingtaiy_n);
	if ((status[0]==0) && (status[1]==0) 
		&& (status[2]==0) && (status[3]==0))
	{
		//����Ƿ����еĵ��������˶�
		if((0==check_done(m_zhituifir_n))&&(0==check_done(m_zhituisec_n))&&
			(0==check_done(m_pingtaix_n))&&(0==check_done(m_pingtaiy_n))&&
			(0==check_done(m_dg_n)))
		{
			//���������ɣ���ֹͣ��ʱ��4
			KillTimer(23);
			set_profile(m_lzhu_n,100,1500,1000);
			fast_vmove(m_lzhu_n,-1);
			SetTimer(21,10,NULL);
		}
	} 
	else
	{
		//������λ��������ֹͣ���е��������
		KillTimer(23);
		sudden_stop(m_zhituifir_n);
		sudden_stop(m_zhituisec_n);
		sudden_stop(m_pingtaix_n);
		sudden_stop(m_pingtaiy_n);
		CheckDianji(status);
	}
	UpdataDisplayBar();
}

//��ȡ�������������������ֵ����ʾ����Ӧ�Ŀؼ���/wulei
void CMainFrame::UpdataDisplayBar()
{
	//int analog_input1=0;
	double analog_input=0;
	//W_812_AD_Aquire(&analog_input1);
	W_812_AD_Aquire(&m_analog_input1);
	get_encoder(m_zhuzhou_enn,&m_com);
	analog_input=((m_analog_input1-2048)*10)/(G11*G22*4096);
	CString m_signal;
	m_signal.Format("%.2f",analog_input);
	CEdit *m_temp;
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_Chuanganqi);
	m_temp->SetWindowText(m_signal);
	
	long com;
	CString m_encoder;
	get_abs_pos(m_dg_enn,&com);
	//get_abs_pos(m_dg_enn,&com);
	//m_old_dgpulse=com;
	m_encoder.Format("%.2f",com*m_dgxishu+m_lDaogui);
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_Daogui);
	m_temp->SetWindowText(m_encoder);
	
	get_abs_pos(m_lzhu_enn,&com);
	m_encoder.Format("%.2f",com*m_lzxishu+m_lLizhu);
	m_temp=(CEdit*)m_wndToolBar2.GetDlgItem(IDC_Lizhu);
	m_temp->SetWindowText(m_encoder);
}
/*
	ƽ̨�˶�������ʵ���ĸ�֧�ȵ��˶���
	��ڲ���Ϊ:
		ƫ����			pxin
		������������	correctionfactor[]:36
		֧�ȵ��˶���	legmov
	���ڲ�������
	write by wulei
*/
void CMainFrame::PlatformMoveAll(double pxin,
								 double correctionfactor[],
								 double legmov[])
{
	long	dist[4]={0,0,0,0};

	if(m_down_pxin>=0.075)
	{
		set_profile(m_zhituifir_n,100,3000,1500);
		set_profile(m_zhituisec_n,100,3000,1500);
		set_profile(m_pingtaix_n,100,3000,1500);
		set_profile(m_pingtaiy_n,100,3000,1500);
		dist[0] = legmov[2]*correctionfactor[0]/pulseeq;
		dist[1] = legmov[3]*correctionfactor[1]/pulseeq;
		dist[2] = legmov[0]*correctionfactor[2]/pulseeq;
		dist[3] = -legmov[1]*correctionfactor[3]/pulseeq;//0.95
	}
	else if((m_down_pxin<=0.075)&&(m_down_pxin>0.045))
	{
		set_profile(m_zhituifir_n,100,1500,250);
		set_profile(m_zhituisec_n,100,1500,250);
		set_profile(m_pingtaix_n,100,1500,250);
		set_profile(m_pingtaiy_n,100,1500,250);
		dist[0] = legmov[2]*correctionfactor[4]/pulseeq;
		dist[1] = legmov[3]*correctionfactor[5]/pulseeq;
		dist[2] = legmov[0]*correctionfactor[6]/pulseeq;
		dist[3] = -legmov[1]*correctionfactor[7]/pulseeq;//1.05
	}
	else if((m_down_pxin<=0.045)&&(m_down_pxin>0.030))
	{
		set_profile(m_zhituifir_n,10,300,50);
		set_profile(m_zhituisec_n,10,300,50);
		set_profile(m_pingtaix_n,10,300,50);
		set_profile(m_pingtaiy_n,10,300,50);
		dist[0] = legmov[2]*correctionfactor[8]/pulseeq;
		dist[1] = legmov[3]*correctionfactor[9]/pulseeq;
		dist[2] = legmov[0]*correctionfactor[10]/pulseeq;
		dist[3] = -legmov[1]*correctionfactor[11]/pulseeq;	

	}
	else if((m_down_pxin<=0.030)&&(m_down_pxin>0.020))//1.43				
	{
		set_profile(m_zhituifir_n,10,300,50);				
		set_profile(m_zhituisec_n,10,300,50);			 
		set_profile(m_pingtaix_n,10,300,50);			 
		set_profile(m_pingtaiy_n,10,300,50);			 
		dist[0] = legmov[2]*correctionfactor[12]/pulseeq;			 
		dist[1] = legmov[3]*correctionfactor[13]/pulseeq;			 
		dist[2] = legmov[0]*correctionfactor[14]/pulseeq;
		dist[3] = -legmov[1]*correctionfactor[15]/pulseeq;//1.1853756

	}
	else if((m_down_pxin<=0.020)&&(m_down_pxin>0.015))//1.159
	{
		set_profile(m_zhituifir_n,10,300,50);
		set_profile(m_zhituisec_n,10,300,50);
		set_profile(m_pingtaix_n,10,300,50);
		set_profile(m_pingtaiy_n,10,300,50);
		dist[0] = legmov[2]*correctionfactor[16]/pulseeq;
		dist[1] = legmov[3]*correctionfactor[17]/pulseeq;
		dist[2] = legmov[0]*correctionfactor[18]/pulseeq;
		dist[3] = -legmov[1]*correctionfactor[19]/pulseeq;//1.27

	}
	else if((m_down_pxin<=0.015)&&(m_down_pxin>0.010))//1.159
	{
		set_profile(m_zhituifir_n,10,300,50);
		set_profile(m_zhituisec_n,10,300,50);
		set_profile(m_pingtaix_n,10,300,50);
		set_profile(m_pingtaiy_n,10,300,50);
		dist[0] = legmov[2]*correctionfactor[20]/pulseeq;
		dist[1] = legmov[3]*correctionfactor[21]/pulseeq;
		dist[2] = legmov[0]*correctionfactor[22]/pulseeq;
		dist[3] = -legmov[1]*correctionfactor[23]/pulseeq;//1.514
	}
	else if((m_down_pxin<=0.010)&&(m_down_pxin>0.005))
	{
		set_profile(m_zhituifir_n,10,80,30);
		set_profile(m_zhituisec_n,10,80,30);
		set_profile(m_pingtaix_n,10,80,30);
		set_profile(m_pingtaiy_n,10,80,30);				 
		dist[0] = legmov[2]*correctionfactor[24]/pulseeq;
		dist[1] = legmov[3]*correctionfactor[25]/pulseeq;
		dist[2] = legmov[0]*correctionfactor[26]/pulseeq;
		dist[3] = -legmov[1]*correctionfactor[27]/pulseeq;//1.85			 
	}
	else if((m_down_pxin<=0.005)&&(m_down_pxin>0.0025))
	{
		set_profile(m_zhituifir_n,10,80,30);
		set_profile(m_zhituisec_n,10,80,30);
		set_profile(m_pingtaix_n,10,80,30);
		set_profile(m_pingtaiy_n,10,80,30);			 					 
		dist[0] = legmov[2]*correctionfactor[28]/pulseeq;
		dist[1] = legmov[3]*correctionfactor[29]/pulseeq;
		dist[2] = legmov[0]*correctionfactor[30]/pulseeq;
		dist[3] = -legmov[1]*correctionfactor[31]/pulseeq;	//1.891759					 		 
	}
	else
	{
		set_profile(m_zhituifir_n,10,30,10);
		set_profile(m_zhituisec_n,10,30,10);
		set_profile(m_pingtaix_n,10,30,10);
		set_profile(m_pingtaiy_n,10,30,10);
		dist[0] = legmov[2]*correctionfactor[32]/pulseeq;
		dist[1] = legmov[3]*correctionfactor[33]/pulseeq;
		dist[2] = legmov[0]*correctionfactor[34]/pulseeq;
		dist[3] = -legmov[1]*correctionfactor[35]/pulseeq;//2.35
	}
	//ִ�е���˶�
	fast_pmove(m_zhituifir_n,dist[0]);
	fast_pmove(m_zhituisec_n,dist[1]);
	fast_pmove(m_pingtaix_n,dist[2]);
	fast_pmove(m_pingtaiy_n,dist[3]);
}

void CMainFrame::OnMotorstate() 
{
	CMotorState dlg;
	dlg.DoModal();// TODO: Add your command handler code here
	
}
LRESULT CMainFrame::OnMotorDialog(WPARAM wParam,LPARAM lParam)////////////////////////////////////fengxuezhen 
{
	
	switch(wParam)
	{
		case IDOK:
		
		    MotorPara();
			m_MotorPara->DestroyWindow();
			delete m_MotorPara;
			m_MotorPara=NULL;
			break;
		case IDCANCEL:
			m_MotorPara->DestroyWindow();
			delete m_MotorPara;
			m_MotorPara=NULL;
			
			break;
		case IDC_apply:
			
            MotorPara();
			break;
	}
	
	return 0;
}
void CMainFrame::MotorPara()///////////////////////chandibing jilu shuju 
{
	CString A;

   	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="canshu.ini";
		 m_pingjing_cf[0]=m_MotorPara->m_pingjing_factor1;//����
		 m_pingjing_cf[1]=m_MotorPara->m_pingjing_factor2;
		 m_pingjing_cf[2]=m_MotorPara->m_pingjing_factor3;
		 m_pingjing_cf[3]=m_MotorPara->m_pingjing_factor4;		 
		 //CString A;
		 A.Format("%.20f",m_MotorPara->m_pingjing_factor1);//д�������ļ���
		 :: WritePrivateProfileString("����","m_pingjing_cf[0]",A,strPath);	
		 A.Format("%.20f",m_MotorPara->m_pingjing_factor2);
		 :: WritePrivateProfileString("����","m_pingjing_cf[1]",A,strPath);	
		 A.Format("%.20f",m_MotorPara->m_pingjing_factor3);
		 :: WritePrivateProfileString("����","m_pingjing_cf[2]",A,strPath);	
		 A.Format("%.20f",m_MotorPara->m_pingjing_factor4);
		 :: WritePrivateProfileString("����","m_pingjing_cf[3]",A,strPath);
		 for (int j=0;j<4;j++)
		 {
			 for(int i=j;i<36;i+=4)
			 {
				 m_pingjing_cf[i]=m_pingjing_cf[j];				 	
			 }
		 }
		 if (m_MotorPara->nInde==0)
		{
			cf[0]=m_MotorPara->m_correctfactor1;
			cf[1]=m_MotorPara->m_correctfactor2;
			cf[2]=m_MotorPara->m_correctfactor3;
			cf[3]=m_MotorPara->m_correctfactor4;
			CString A;
			A.Format("%.20f",m_MotorPara->m_correctfactor1);
			::WritePrivateProfileString("����","cf[0]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor2);
			::WritePrivateProfileString("����","cf[1]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor3);
			::WritePrivateProfileString("����","cf[2]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor4);
			::WritePrivateProfileString("����","cf[3]",A,strPath);			
		}
		else if (m_MotorPara->nInde==1)
		{
			cf[4]=m_MotorPara->m_correctfactor1;
			cf[5]=m_MotorPara->m_correctfactor2;
			cf[6]=m_MotorPara->m_correctfactor3;
			cf[7]=m_MotorPara->m_correctfactor4;
			CString A;
			A.Format("%.20f",m_MotorPara->m_correctfactor1);
			::WritePrivateProfileString("����","cf[4]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor2);
			::WritePrivateProfileString("����","cf[5]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor3);
			::WritePrivateProfileString("����","cf[6]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor4);
			::WritePrivateProfileString("����","cf[7]",A,strPath);			
		}
		else if (m_MotorPara->nInde==2)
		{
			cf[8]=m_MotorPara->m_correctfactor1;
			cf[9]=m_MotorPara->m_correctfactor2;
			cf[10]=m_MotorPara->m_correctfactor3;
			cf[11]=m_MotorPara->m_correctfactor4;
			CString A;
			A.Format("%.20f",m_MotorPara->m_correctfactor1);
			::WritePrivateProfileString("����","cf[8]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor2);
			::WritePrivateProfileString("����","cf[9]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor3);
			::WritePrivateProfileString("����","cf[10]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor4);
			::WritePrivateProfileString("����","cf[11]",A,strPath);			
		}
		else if (m_MotorPara->nInde==3)
		{
			cf[12]=m_MotorPara->m_correctfactor1;
			cf[13]=m_MotorPara->m_correctfactor2;
			cf[14]=m_MotorPara->m_correctfactor3;
			cf[15]=m_MotorPara->m_correctfactor4;
			CString A;
			A.Format("%.20f",m_MotorPara->m_correctfactor1);
			::WritePrivateProfileString("����","cf[12]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor2);
			::WritePrivateProfileString("����","cf[13]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor3);
			::WritePrivateProfileString("����","cf[14]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor4);
			::WritePrivateProfileString("����","cf[15]",A,strPath);			
		}
		else if (m_MotorPara->nInde==4)
		{
			cf[16]=m_MotorPara->m_correctfactor1;
			cf[17]=m_MotorPara->m_correctfactor2;
			cf[18]=m_MotorPara->m_correctfactor3;
			cf[19]=m_MotorPara->m_correctfactor4;
			CString A;
			A.Format("%.20f",m_MotorPara->m_correctfactor1);
			::WritePrivateProfileString("����","cf[16]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor2);
			::WritePrivateProfileString("����","cf[17]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor3);
			::WritePrivateProfileString("����","cf[18]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor4);
			::WritePrivateProfileString("����","cf[19]",A,strPath);			
		}
		else if (m_MotorPara->nInde==5)
		{
			cf[20]=m_MotorPara->m_correctfactor1;
			cf[21]=m_MotorPara->m_correctfactor2;
			cf[22]=m_MotorPara->m_correctfactor3;
			cf[23]=m_MotorPara->m_correctfactor4;
			CString A;
			A.Format("%.20f",m_MotorPara->m_correctfactor1);
			::WritePrivateProfileString("����","cf[20]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor2);
			::WritePrivateProfileString("����","cf[21]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor3);
			::WritePrivateProfileString("����","cf[22]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor4);
			::WritePrivateProfileString("����","cf[23]",A,strPath);			
		}
		else if (m_MotorPara->nInde==6)
		{
			cf[24]=m_MotorPara->m_correctfactor1;
			cf[25]=m_MotorPara->m_correctfactor2;
			cf[26]=m_MotorPara->m_correctfactor3;
			cf[27]=m_MotorPara->m_correctfactor4;
			CString A;
			A.Format("%.20f",m_MotorPara->m_correctfactor1);
			::WritePrivateProfileString("����","cf[24]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor2);
			::WritePrivateProfileString("����","cf[25]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor3);
			::WritePrivateProfileString("����","cf[26]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor4);
			::WritePrivateProfileString("����","cf[7]",A,strPath);			
		}
		else if (m_MotorPara->nInde==7)
		{
			cf[28]=m_MotorPara->m_correctfactor1;
			cf[29]=m_MotorPara->m_correctfactor2;
			cf[30]=m_MotorPara->m_correctfactor3;
			cf[31]=m_MotorPara->m_correctfactor4;
			CString A;
			A.Format("%.20f",m_MotorPara->m_correctfactor1);
			::WritePrivateProfileString("����","cf[28]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor2);
			::WritePrivateProfileString("����","cf[29]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor3);
			::WritePrivateProfileString("����","cf[30]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor4);
			::WritePrivateProfileString("����","cf[31]",A,strPath);			
		}
		else if (m_MotorPara->nInde==8)
		{
			cf[32]=m_MotorPara->m_correctfactor1;
			cf[33]=m_MotorPara->m_correctfactor2;
			cf[34]=m_MotorPara->m_correctfactor3;
			cf[35]=m_MotorPara->m_correctfactor4;
			CString A;
			A.Format("%.20f",m_MotorPara->m_correctfactor1);
			::WritePrivateProfileString("����","cf[32]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor2);
			::WritePrivateProfileString("����","cf[33]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor3);
			::WritePrivateProfileString("����","cf[34]",A,strPath);
			A.Format("%.20f",m_MotorPara->m_correctfactor4);
			::WritePrivateProfileString("����","cf[35]",A,strPath);			
		}	
}

void CMainFrame::OnMotorCorrect()//��Ӧ���� ��ģ̬�Ի���
{

	if(m_MotorPara==NULL)
	{
		m_MotorPara=new CMotorCorrection;
        m_MotorPara->Create(IDD_MOTORCORRECTION,NULL);
		m_MotorPara->ShowWindow(SW_SHOW);
	}
	else
	{
		m_MotorPara->SetActiveWindow();

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
  	::GetPrivateProfileString("����","m_pingjing_cf[0]","lisi",A.GetBuffer(100),100,strPath);
  	m_MotorPara->m_pingjing_factor1=atof(A);
  	::GetPrivateProfileString("����","m_pingjing_cf[1]","lisi",A.GetBuffer(100),100,strPath);
  	m_MotorPara->m_pingjing_factor2=atof(A);
  	::GetPrivateProfileString("����","m_pingjing_cf[2]","lisi",A.GetBuffer(100),100,strPath);
  	m_MotorPara->m_pingjing_factor3=atof(A);
  	::GetPrivateProfileString("����","m_pingjing_cf[3]","lisi",A.GetBuffer(100),100,strPath);
  	 m_MotorPara->m_pingjing_factor4=atof(A);
	 UpdateData(FALSE);
       
}

void CMainFrame::InitMotorcorrection()//��ʼ�����������ϵ��
{
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="canshu.ini";
   CString a;//����CMainframe�����ֵ
   ::GetPrivateProfileString("����","cf[0]","lisi",a.GetBuffer(100),100,strPath);
   cf[0]=atof(a);
   ::GetPrivateProfileString("����","cf[1]","lisi",a.GetBuffer(100),100,strPath);
   cf[1]=atof(a);
   ::GetPrivateProfileString("����","cf[2]","lisi",a.GetBuffer(100),100,strPath);
   cf[2]=atof(a);
   ::GetPrivateProfileString("����","cf[3]","lisi",a.GetBuffer(100),100,strPath);
   cf[3]=atof(a);
   ::GetPrivateProfileString("����","cf[4]","lisi",a.GetBuffer(100),100,strPath);
   cf[4]=atof(a);
   ::GetPrivateProfileString("����","cf[5]","lisi",a.GetBuffer(100),100,strPath);
   cf[5]=atof(a);
   ::GetPrivateProfileString("����","cf[6]","lisi",a.GetBuffer(100),100,strPath);
   cf[6]=atof(a);
   ::GetPrivateProfileString("����","cf[7]","lisi",a.GetBuffer(100),100,strPath);
   cf[7]=atof(a);
   ::GetPrivateProfileString("����","cf[8]","lisi",a.GetBuffer(100),100,strPath);
   cf[8]=atof(a);
   ::GetPrivateProfileString("����","cf[9]","lisi",a.GetBuffer(100),100,strPath);
   cf[9]=atof(a);
   ::GetPrivateProfileString("����","cf[10]","lisi",a.GetBuffer(100),100,strPath);
   cf[10]=atof(a);
   ::GetPrivateProfileString("����","cf[11]","lisi",a.GetBuffer(100),100,strPath);
   cf[11]=atof(a);
   ::GetPrivateProfileString("����","cf[12]","lisi",a.GetBuffer(100),100,strPath);
   cf[12]=atof(a);
   ::GetPrivateProfileString("����","cf[13]","lisi",a.GetBuffer(100),100,strPath);
   cf[13]=atof(a);
   ::GetPrivateProfileString("����","cf[14]","lisi",a.GetBuffer(100),100,strPath);
   cf[14]=atof(a);
   ::GetPrivateProfileString("����","cf[15]","lisi",a.GetBuffer(100),100,strPath);
   cf[15]=atof(a);
   ::GetPrivateProfileString("����","cf[16]","lisi",a.GetBuffer(100),100,strPath);
   cf[16]=atof(a);
   ::GetPrivateProfileString("����","cf[17]","lisi",a.GetBuffer(100),100,strPath);
   cf[17]=atof(a);
   ::GetPrivateProfileString("����","cf[18]","lisi",a.GetBuffer(100),100,strPath);
   cf[18]=atof(a);
   ::GetPrivateProfileString("����","cf[19]","lisi",a.GetBuffer(100),100,strPath);
   cf[19]=atof(a);
   ::GetPrivateProfileString("����","cf[20]","lisi",a.GetBuffer(100),100,strPath);
   cf[20]=atof(a);
   ::GetPrivateProfileString("����","cf[21]","lisi",a.GetBuffer(100),100,strPath);
   cf[21]=atof(a);
   ::GetPrivateProfileString("����","cf[22]","lisi",a.GetBuffer(100),100,strPath);
   cf[22]=atof(a);
   ::GetPrivateProfileString("����","cf[23]","lisi",a.GetBuffer(100),100,strPath);
   cf[23]=atof(a);
   ::GetPrivateProfileString("����","cf[24]","lisi",a.GetBuffer(100),100,strPath);
   cf[24]=atof(a);
   ::GetPrivateProfileString("����","cf[25]","lisi",a.GetBuffer(100),100,strPath);
   cf[25]=atof(a);
   ::GetPrivateProfileString("����","cf[26]","lisi",a.GetBuffer(100),100,strPath);
   cf[26]=atof(a);
   ::GetPrivateProfileString("����","cf[27]","lisi",a.GetBuffer(100),100,strPath);
   cf[27]=atof(a);
   ::GetPrivateProfileString("����","cf[28]","lisi",a.GetBuffer(100),100,strPath);
   cf[28]=atof(a);
   ::GetPrivateProfileString("����","cf[29]","lisi",a.GetBuffer(100),100,strPath);
   cf[29]=atof(a);
   ::GetPrivateProfileString("����","cf[30]","lisi",a.GetBuffer(100),100,strPath);
   cf[30]=atof(a);
   ::GetPrivateProfileString("����","cf[31]","lisi",a.GetBuffer(100),100,strPath);
   cf[31]=atof(a);
   ::GetPrivateProfileString("����","cf[32]","lisi",a.GetBuffer(100),100,strPath);
   cf[32]=atof(a);
   ::GetPrivateProfileString("����","cf[33]","lisi",a.GetBuffer(100),100,strPath);
   cf[33]=atof(a);
   ::GetPrivateProfileString("����","cf[34]","lisi",a.GetBuffer(100),100,strPath);
   cf[34]=atof(a);
   ::GetPrivateProfileString("����","cf[35]","lisi",a.GetBuffer(100),100,strPath);
   cf[35]=atof(a); 
   ::GetPrivateProfileString("����","m_pingjing_cf[0]","lisi",a.GetBuffer(100),100,strPath);
   m_pingjing_cf[0]=atof(a);
   ::GetPrivateProfileString("����","m_pingjing_cf[1]","lisi",a.GetBuffer(100),100,strPath);
   m_pingjing_cf[1]=atof(a);
   ::GetPrivateProfileString("����","m_pingjing_cf[2]","lisi",a.GetBuffer(100),100,strPath);
   m_pingjing_cf[2]=atof(a);
   ::GetPrivateProfileString("����","m_pingjing_cf[3]","lisi",a.GetBuffer(100),100,strPath);
   m_pingjing_cf[3]=atof(a);
   for (int j=0;j<4;j++)
	{
	   for(int i=j;i<36;i+=4)
	   {
		   m_pingjing_cf[i]=m_pingjing_cf[j];				 	
	   }
	 }
}


/////////=====================================================
////////======================================================
void CMainFrame::OnGowork() 
{
	int nIndex=m_ToolBar2.m_combobox.GetCurSel();
	if(nIndex==0) OnDaqCircleSemiau();
    if(nIndex==1) OnDaqCydSemiau();
	if(nIndex==2) OnDaqStraightness();
	if(nIndex==3) OnDaqPlaneness();
	if(nIndex==4) OnDaqPara();
	if(nIndex==5) OnDAQpmPLANENESS();
	if(nIndex==6) OnDaqAxiality();
	if(nIndex==7) OnDaqSquareness();
	//if(nIndex==2)
}
void CMainFrame::OnDaqCircleSemiau() //Բ��1111111
{

	// TODO: Add your command handler code here
	if(_access(m_strFileSavePath,00))
	{
		AfxMessageBox("���ݴ洢·������");
		return;
	}
	CDlg_YD m_dlg;
	if(IDOK==m_dlg.DoModal())
	{

		m_fname=m_strFileSavePath+m_dlg.m_name1;//�ļ���
		m_fname+=".rds";
		//����ļ��Ƿ��Ѿ�����
		if (_access(m_fname,0))
		{
			KillTimer(12);//�ر��ֶ���
			m_bDongTai=FALSE;
			m_fG11CurSel=m_dlg.m_fG11cursel;
			SwitchG11(m_fG11CurSel);
			m_ftime=m_dlg.m_time;
			m_fPositionAway=m_dlg.m_PositionAway;
			m_fbPre=m_dlg.m_bPre;

			m_fStateMessage="Բ�Ȳ���";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			if(m_dlg.m_bPre)
			{
				set_profile(m_dg_n,1000,3000,5000);
				fast_vmove(m_dg_n,-1);
 				SetTimer(30,10,NULL);
			}
			else
			{
				SetTimer(31,10,NULL);//��������߳�
			}
		} 
		else
		{
			AfxMessageBox("�ļ��Ѵ��ڣ�����������");
			OnDaqCircleSemiau();
		}
	}
}
void CMainFrame::OnDaqCydSemiau() //Բ����2222222
{

	// TODO: Add your command handler code here
	if(_access(m_strFileSavePath,00))
	{
		AfxMessageBox("���ݴ洢·������");
		return;
	}
	CDlg_YZD m_dlg;
	if(IDOK==m_dlg.DoModal())
	{

		m_fname=m_strFileSavePath+m_dlg.m_name1;//�ļ���
		m_fname+=".cyd";
		//����ļ��Ƿ��Ѿ�����
		if (_access(m_fname,0))
		{
			//���ݴ���
			KillTimer(12);
			m_bDongTai=FALSE;
			m_fG11CurSel=m_dlg.m_fG11cursel;//��λ
			SwitchG11(m_fG11CurSel);//��������
			m_ftime=m_dlg.m_time;//����ʱ��
//			m_fheight=m_dlg.m_high1;//�����߶�
			m_fJiemianNum=m_dlg.m_num1;//��������
			m_fbPre=m_dlg.m_bPre;
			m_fPositionAway=m_dlg.m_PositionAway;//�뿪����
			for(int i=0;i<m_fJiemianNum;i++)//����߶�
			{
				m_fPerHeight[i]=m_dlg.m_height[i];
			}
			m_fheight=m_fPerHeight[m_fJiemianNum-1];
			m_fbBack0=m_dlg.m_bBack0;//�Ƿ��ԭλ

			get_abs_pos(m_lzhu_enn,&m_old_lzhupulse);
			m_fn=0;//��������
			m_data0[0].data=m_fJiemianNum;
			m_data0[0].height=0;
			m_data0[0].selected=0;
			std::ofstream fin(m_fname,std::ios::binary);
			fin.write((char*)&m_data0[0],sizeof(shuju0));//д�����Ĳ���
			fin.close();
			m_fStateMessage="Բ���Ȳ���";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);

			if(m_dlg.m_bPre)
			{
				set_profile(m_dg_n,1000,3000,5000);
				fast_vmove(m_dg_n,-1);
				SetTimer(34,10,NULL);
			}
			else
			{
				SetTimer(35,10,NULL);//��������߳�
			}
		} 
		else
		{
			AfxMessageBox("�ļ��Ѵ��ڣ�����������");
			OnDaqCydSemiau();
		}
	}
}
void CMainFrame::OnDaqStraightness() //ֱ�߶�3333
{

	// TODO: Add your command handler code here
	if(_access(m_strFileSavePath,00))
	{
		AfxMessageBox("���ݴ洢·������");
		return;
	}
	AfxMessageBox("ȷ������ֹͣ��ת��������ʽ��ȷ");
	CDlg_ZXD m_dlg;
	if(IDOK==m_dlg.DoModal())
	{

		m_fname=m_strFileSavePath+m_dlg.m_name1;//�ļ���
		m_fname+=".zxd";
		//����ļ��Ƿ��Ѿ�����
		if (_access(m_fname,0))
		{
			KillTimer(12);
			m_bDongTai=FALSE;
			m_fG11CurSel=m_dlg.m_fG11cursel;
			SwitchG11(m_fG11CurSel);
			m_ftime=m_dlg.m_time;
			m_fheight=m_dlg.m_high1;//�����߶�
			m_fPositionAway=m_dlg.m_PositionAway;
			m_fVCurSel=m_dlg.m_cursel;
			m_fVelocity2=m_dlg.m_Velocity;
			m_fbBack0=m_dlg.m_bBack0;
			m_fbPre=m_dlg.m_bPre;

			m_fn=0;
			m_fStateMessage="ֱ�߶Ȳ���";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			if(m_dlg.m_bPre)
			{
				set_profile(m_dg_n,1000,3000,5000);
				fast_vmove(m_dg_n,-1);
				SetTimer(40,10,NULL);
			}
			else
				Timer41();
		} 
		else
		{
			AfxMessageBox("�ļ��Ѵ��ڣ�����������");
			OnDaqStraightness();
		}
	}
}

void CMainFrame::OnDaqPlaneness() //ƽ���4444444444444

{

	// TODO: Add your command handler code here
	if(_access(m_strFileSavePath,00))
	{
		AfxMessageBox("���ݴ洢·������");
		return;
	}
	CDlg_PMD m_dlg;
	if(IDOK==m_dlg.DoModal())
	{

		m_fname=m_strFileSavePath+m_dlg.m_name1;//�ļ���
		m_fname+=".pmd";
		//����ļ��Ƿ��Ѿ�����
		if (_access(m_fname,0))
		{
			KillTimer(12);
			m_bDongTai=FALSE;
			m_fG11CurSel=m_dlg.m_fG11cursel;
			SwitchG11(m_fG11CurSel);
			m_ftime=m_dlg.m_time;
			m_fPositionAway=m_dlg.m_PositionAway;
			m_fbPre=m_dlg.m_bPre;
			m_fStateMessage="ƽ��Ȳ���";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);

			m_data0[0].data=1;
			m_data0[0].height=0;
			m_data0[0].selected=0;
			std::ofstream fin(m_fname,std::ios::binary);
			fin.write((char*)&m_data0[0],sizeof(shuju0));//д�����Ĳ���
			fin.close();
			if(m_dlg.m_bPre)
			{
				set_profile(m_lzhu_n,1000,3000,5000);
				fast_vmove(m_lzhu_n,-1);;
				SetTimer(44,10,NULL);
			}
			else
			{
				SetTimer(45,10,NULL);
			}
				
		} 
		else
		{
			AfxMessageBox("�ļ��Ѵ��ڣ�����������");
			OnDaqPlaneness();
		}
	}
}

void CMainFrame::OnDaqPara() //ƽ�ж�555555555555555
{

	// TODO: Add your command handler code here
	if(_access(m_strFileSavePath,00))
	{
		AfxMessageBox("���ݴ洢·������");
		return;
	}
	AfxMessageBox("ȷ������ֹͣ��ת��������ʽ��ȷ");
	CDlg_PXD m_dlg;
	if(IDOK==m_dlg.DoModal())
	{

		m_fname=m_strFileSavePath+m_dlg.m_name1;//�ļ���
		m_fname+=".pxd";
		//����ļ��Ƿ��Ѿ�����
		if (_access(m_fname,0))
		{
			KillTimer(12);
			m_bDongTai=FALSE;
			m_fG11CurSel=m_dlg.m_fG11cursel;
			SwitchG11(m_fG11CurSel);
			m_ftime=m_dlg.m_time;
			m_fheight=m_dlg.m_high1;
			m_fPositionAway=m_dlg.m_PositionAway;
			m_fVelocity2=m_dlg.m_Velocity;
			m_fbBack0=m_dlg.m_bBack0;
			m_fbPre=m_dlg.m_bPre;


			m_fbParallelism=FALSE;
			m_fn=0;
			m_fStateMessage="ƽ�жȲ���";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			if(m_dlg.m_bPre)
			{
				set_profile(m_dg_n,1000,3000,5000);
				fast_vmove(m_dg_n,1);
				SetTimer(48,10,NULL);
			}
			else
				Timer49();
		} 
		else
		{
			AfxMessageBox("�ļ��Ѵ��ڣ�����������");
			OnDaqPara();
		}
	}
}
void CMainFrame::OnDAQpmPLANENESS() //ƽ��ƽ�ж�6666666
{

	// TODO: Add your command handler code here
	if(_access(m_strFileSavePath,00))
	{
		AfxMessageBox("���ݴ洢·������");
		return;
	}
	CDlg_pmPXD m_dlg;
	if(IDOK==m_dlg.DoModal())
	{

		m_fname=m_strFileSavePath+m_dlg.m_name1;//�ļ���
		m_fname+=".pxd";
		//����ļ��Ƿ��Ѿ�����
		if (_access(m_fname,0))
		{
			KillTimer(12);
			m_bDongTai=FALSE;
			m_fG11CurSel=m_dlg.m_fG11cursel;
			SwitchG11(m_fG11CurSel);
			m_ftime=m_dlg.m_time;
			m_fPositionAway=m_dlg.m_PositionAway;
			m_fbPre=m_dlg.m_bPre;
		
			m_fn=0;
			m_fStateMessage="ƽ��ƽ�жȲ���";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			if(m_fbPre)
			{
				set_profile(m_lzhu_n,1000,3000,5000);
				fast_vmove(m_lzhu_n,-1);;
				SetTimer(62,10,NULL);
			}
			else
				m_fStateMessage.Format("ƽ��ƽ�жȲ�����%d����",m_fn+1);
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			
			SetTimer(63,10,NULL);
		} 
		else
		{
			AfxMessageBox("�ļ��Ѵ��ڣ�����������");
			OnDAQpmPLANENESS();
		}
	}
}
void CMainFrame::OnDaqAxiality() //ͬ��7777777
{

	// TODO: Add your command handler code here
	if(_access(m_strFileSavePath,00))
	{
		AfxMessageBox("���ݴ洢·������");
		return;
	}
	CDlg_TZD m_dlg;
	if(IDOK==m_dlg.DoModal())
	{

		m_fname=m_strFileSavePath+m_dlg.m_name1;//�ļ���
		m_fname+=".tzd";
		//����ļ��Ƿ��Ѿ�����
		if (_access(m_fname,0))
		{
			KillTimer(12);
			m_bDongTai=FALSE;
			//���ݴ���
			m_fG11CurSel=m_dlg.m_fG11cursel;//��λ
			SwitchG11(m_fG11CurSel);//��������
			m_ftime=m_dlg.m_time;//����ʱ��
			m_fheight=m_dlg.m_high1;//�����߶�
			m_fJiemianNum=m_dlg.m_num1;//��������
			m_fPositionAway=m_dlg.m_PositionAway;//�뿪����
			for(int i=0;i<m_fJiemianNum;i++)//����߶�
			{
				m_fPerHeight[i]=m_dlg.m_height[i];
			}
			//m_fDengJianGe=m_dlg.m_intSelect;//�ȼ��Ͳ��ȼ��ѡ��
			m_fbBack0=m_dlg.m_bBack0;//�Ƿ��ԭλ
			m_fbPre=m_dlg.m_bPre;
			
			get_abs_pos(m_lzhu_enn,&m_old_lzhupulse);
			m_fn=0;//��������
			m_data0[0].data=m_fJiemianNum;
			m_data0[0].height=0;
			m_data0[0].selected=0;
			std::ofstream fin(m_fname,std::ios::binary);
			fin.write((char*)&m_data0[0],sizeof(shuju0));//д�����Ĳ���
			fin.close();

			m_fStateMessage="ͬ��Ȳ���";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			if(m_dlg.m_bPre)
			{
				set_profile(m_dg_n,1000,3000,5000);
				fast_vmove(m_dg_n,-1);
				SetTimer(53,10,NULL);
			}
			
			else
				Timer54();
		} 
		else
		{
			AfxMessageBox("�ļ��Ѵ��ڣ�����������");
		}

	}
}

void CMainFrame::OnDaqSquareness() //��ֱ��888888
{

	// TODO: Add your command handler code here
	if(_access(m_strFileSavePath,00))
	{
		AfxMessageBox("���ݴ洢·������");
		return;
	}
	CDlg_CZD m_dlg;
	if(IDOK==m_dlg.DoModal())
	{

		m_fname=m_strFileSavePath+m_dlg.m_name1;//�ļ���
		m_fname+=".czd";
		//����ļ��Ƿ��Ѿ�����
		if (_access(m_fname,0))
		{
			KillTimer(12);
			m_bDongTai=FALSE;
			//���ݴ���
			m_fG11CurSel=m_dlg.m_fG11cursel;//��λ
			SwitchG11(m_fG11CurSel);//��������
			m_ftime=m_dlg.m_time;//����ʱ��
			m_fheight=m_dlg.m_high1;//�����߶�
			m_fJiemianNum=m_dlg.m_num1;//��������
			m_fPositionAway=m_dlg.m_PositionAway;//�뿪����
			for(int i=0;i<m_fJiemianNum;i++)//����߶�
			{
				m_fPerHeight[i]=m_dlg.m_height[i];
			}
		//	m_fDengJianGe=m_dlg.m_intSelect;//�ȼ��Ͳ��ȼ��ѡ��
			m_fbBack0=m_dlg.m_bBack0;//�Ƿ��ԭλ
			m_fbPre=m_dlg.m_bPre;
			
			get_abs_pos(m_lzhu_enn,&m_old_lzhupulse);
			m_fn=0;//��������
			m_data0[0].data=m_fJiemianNum;
			m_data0[0].height=0;
			m_data0[0].selected=0;
			std::ofstream fin(m_fname,std::ios::binary);
			fin.write((char*)&m_data0[0],sizeof(shuju0));//д�����Ĳ���
			fin.close();

			m_fStateMessage="��ֱ�Ȳ���";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			if(m_dlg.m_bPre)
				SetTimer(58,10,NULL);
			else
				SetTimer(60,10,NULL);
		} 
		else
		{
			AfxMessageBox("�ļ��Ѵ��ڣ�����������");
		}
	}
}
//=============================================
/*  Բ�Ȳ��� time 30-33  ��ѧ��*/

//=============================================

void CMainFrame::Timer30()//����
{
	int		analog_input1=0;
	double	analog_input=0;
	long	com=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -5.0/(G11*G22)*0.1)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(30); 
		sudden_stop(m_dg_n); 

		SetTimer(31,10,NULL);//��������߳�
	}
}

void CMainFrame::Timer31()
{
	KillTimer(31);
	int ret=666;		 
	unsigned short  pMem[3600];
	memset(pMem, 0, sizeof(pMem));

     ret=WLS_8112PG_WaitZeroMinus_dlg();	//��������
	 if(ret==-1)
	 {
		 AfxMessageBox("����λʧ��");
		 return;
	}
    ret=WLS_8112PG_AD_INT_Sampling_dlg(m_fChannel,m_fGainNum,3600, pMem, 2, 100, 45);	//��������
	int i;
	for(i=0;i<3600;i++)	//���ݴ���
	{
		m_data[i].data=pMem[i];//////////////��¼��������
		m_data[i].selected=0;
	}
	m_fStateMessage="Բ�Ȳ������";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	std::ofstream fin(m_fname,std::ios::binary);
	for ( i=0;i<3600;i++)
	{	
		fin.write((char*)&m_data[i], sizeof(shuju));
	}
	fin.write((char*)&G11,sizeof(double));
	fin.write((char*)&G22,sizeof(double));
	fin.write((char*)&m_ftime,sizeof(CTime));////��Ϊ�ĸ��ֽ�
	fin.close();
	//��ȡ�ļ�����ͼ��
	m_fullPath=m_fname;///////////////////�ļ�·��	
	if (m_fullPath!="")
	{	
		if (m_DoCircle!=NULL)
		{
			m_DoCircle->MDIActivate();
			m_DoCircle->RedrawWindow();
		}
		else
		{
			m_DoCircle=new CWilsonFrame();
			CCreateContext context;
			context.m_pNewViewClass=RUNTIME_CLASS(CDoCircle);
			if (!m_DoCircle->LoadFrame(IDI_ICON17,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
			{
				return;
			}
			AddVIEW(m_DoCircle);
			m_DoCircle->ShowWindow(SW_SHOWMAXIMIZED);
			m_DoCircle->InitialUpdateFrame(NULL,TRUE);
		}
		Timer32();
	}
   
	m_lx=1;
}
void CMainFrame::Timer32()
{
	KillTimer(32);
	if(m_fPositionAway==0){
	//	SetTimer(12,10,NULL);//�����ֶ�
	   
}else
	{
		get_abs_pos(m_dg_enn,&m_old_dgpulse);
		set_profile(m_dg_n,3000,30000,10000);
		fast_pmove(m_dg_n,1000000);//����һ���Զ�����
		SetTimer(33,10,NULL);
	}
}
void CMainFrame::Timer33()//ֹͣ���� �����ֶ�
{
	UpdataDisplayBar();
	long com;
	get_abs_pos(m_dg_enn,&com);
	double ht;
	ht = abs(com-m_old_dgpulse)*m_dgxishu;
	if (ht >= m_fPositionAway)
	{   
		KillTimer(33);
		sudden_stop(m_dg_n);
	//	SetTimer(12,10,NULL);
		if(2==m_lx){
		 Timer38();
		 }
	}
}
//=============================================
/*  Բ���Ȳ���  34-39 ��ѧ��*/

//=============================================

void CMainFrame::Timer34()//�������
{
	int		analog_input1=0;
	double	analog_input=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -5.0/(G11*G22)*0.1)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(34);
		sudden_stop(m_dg_n);
		Timer35();
	}	
}
void CMainFrame::Timer35()//��������
{
	KillTimer(35);
	long lPulse;
	if(m_fn==0)
		lPulse = m_fPerHeight[m_fn]/m_lzxishu;//����������㣿����1.1
	else
		lPulse=(m_fPerHeight[m_fn]-m_fPerHeight[m_fn-1])/m_lzxishu;
	m_wndStatusBar.SetPaneText(1,"Բ���Ȳ�����������");
	set_profile(m_lzhu_n,10000,50000,15000);
	fast_pmove(m_lzhu_n,10000000);//��������
	SetTimer(36,10,NULL);
}
void CMainFrame::Timer36()//�����������
{
	UpdataDisplayBar();
	long com;
	get_abs_pos(m_lzhu_enn,&com);
	double ht;
	ht = abs(com-m_old_lzhupulse)*m_lzxishu;
	if (ht >= (m_fPerHeight[m_fn] ))
	{
		KillTimer(36);
		sudden_stop(m_lzhu_n);
		m_fStateMessage.Format("Բ���Ȳ�����%d����",m_fn+1);
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);

		SetTimer(37,10,NULL);
	}
}
void CMainFrame::Timer37()//��ʼ����
{
    m_lx=2;
	KillTimer(37);
	int ret=666;		 
	unsigned short  pMem[3600];
	memset(pMem, 0, sizeof(pMem));
	

	ret=WLS_8112PG_WaitZeroMinus_dlg();	//��������
	if(ret==-1)
	{
		AfxMessageBox("����λʧ��");
		return;
	}
    ret=WLS_8112PG_AD_INT_Sampling_dlg(m_fChannel,m_fGainNum,3600, pMem, 2, 100, 45);	//��������
	int i;
	for(i=0;i<3600;i++)	//���ݴ���
	{
		m_data0[i].data=pMem[i];//////////////��¼��������
		m_data0[i].selected=0;
		m_data0[i].height=m_fPerHeight[m_fn];//
	}	
	std::ofstream fin(m_fname,std::ios::binary|std::ios::app);
	for ( i=0;i<3600;i++)
	{	
		fin.write((char*)&m_data0[i], sizeof(shuju0));
	}
	fin.close();
	m_fn++;
	
	if(m_fn<m_fJiemianNum)//����û���
		Timer35();
	else
	{
		m_fStateMessage="Բ���Ȳ������";
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);
		std::ofstream fin(m_fname,std::ios::binary|std::ios::app);//�ļ���
		fin.write((char*)&G11,sizeof(double));
		fin.write((char*)&G22,sizeof(double));
		fin.write((char*)&m_ftime,sizeof(CTime));////��Ϊ�ĸ��ֽ�
		fin.close();
		
		m_fullPath2=m_fname;///·��
		if (m_fullPath2!="")
		{	
			if (m_DoCylinder!=NULL)
			{
				m_DoCylinder->MDIActivate();
				m_DoCylinder->RedrawWindow();
			}
			else
			{
				m_DoCylinder=new CWilsonFrame();
				CCreateContext context;
				context.m_pNewViewClass=RUNTIME_CLASS(CDoCylinder);
				if (!m_DoCylinder->LoadFrame(IDI_PIST,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
				{
					return;
				}
				AddVIEW(m_DoCylinder);
				m_DoCylinder->ShowWindow(SW_SHOWMAXIMIZED);
				m_DoCylinder->InitialUpdateFrame(NULL,TRUE);
			}
			
	//	set_profile(m_dg_n,3000,30000,10000);
	//	fast_pmove(m_dg_n,m_fPositionAway/m_dgxishu);//����һ���Զ�����
		Timer32();
		//	
		}
	}		
}
void CMainFrame::Timer38()
{
	KillTimer(38);


	if(m_fbBack0)//�������ԭλ
	{
		m_fStateMessage="������ԭλ";
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);
		long lPulse;
		get_abs_pos(m_lzhu_enn,&m_old_lzhupulse);
		lPulse = m_fheight*1000/0.078;//�����������
		set_profile(m_lzhu_n,8000,5000,15000);
		fast_pmove(m_lzhu_n,-10000000);//�����½�
		SetTimer(39,10,NULL);
	}
//	else
//		Timer32();
}
void CMainFrame::Timer39()
{
	UpdataDisplayBar();
	long com;
	get_abs_pos(m_lzhu_enn,&com);
	double ht;
	ht = abs(com-m_old_lzhupulse)*m_lzxishu;
	if (ht >= (m_fheight))
	{
		KillTimer(39);
		sudden_stop(m_lzhu_n);
		m_fStateMessage="��ԭλ���";
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);

	}
}
//=============================================
/*  ֱ�߶Ȳ���  40-44 ��ѧ��*///��Ҫ�ڴ���

//=============================================

void CMainFrame::Timer40()
{
	int		analog_input1=0;
	double	analog_input=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -5.0/(G11*G22)*0.1)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(40);
		sudden_stop(m_dg_n); 
		Timer41();//������������㡢��ʾ
	}	
}
void CMainFrame::Timer41()
{
	KillTimer(41);
	long lpulse;
	get_abs_pos(m_lzhu_enn,&m_old_lzhupulse);
	lpulse=1.1*m_fheight*1000/0.078;
	set_profile(m_lzhu_n,500,m_fVelocity2*1500/0.075,10000);
	fast_pmove(m_lzhu_n,m_fheight/m_lzxishu*2.);//��������
    SetTimer(42,5,NULL);
//	reset_pos(m_lzhu_enn);
}
void CMainFrame::Timer42()
{     m_lx=2;
	UpdataDisplayBar();
	long com;
	double aa;
	aa=m_fheight/m_lzxishu;
	get_abs_pos(m_lzhu_enn,&com);

	if (com-m_old_lzhupulse >= aa/3600.*m_fn)
	{
	//	KillTimer(42);
        int analog_input1=0;
		W_812_AD_Aquire(&analog_input1);
		m_data[m_fn].data=analog_input1;//////////////��¼��������
		m_data[m_fn].selected=0;
		if(m_fn>=3599)////������� ��¼����
		{
			KillTimer(42);
			sudden_stop(m_lzhu_n);
			m_fStateMessage="ֱ�߶Ȳ������";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			std::ofstream fin(m_fname,std::ios::binary);
			for (int i=0;i<3600;i++)
			{	
				fin.write((char*)&m_data[i], sizeof(shuju));
			}	
			fin.write((char*)&G11,sizeof(double));
			fin.write((char*)&G22,sizeof(double));
            fin.write((char*)&m_fheight,sizeof(float));///////////////////////////
			fin.write((char*)&m_ftime,sizeof(CTime));////��Ϊ�ĸ��ֽ�
			fin.close();
			m_fullPath3=m_fname;
			if (m_fullPath3!="")
			{	
				if (m_DoStraightness!=NULL)
				{
					m_DoStraightness->MDIActivate();
					m_DoStraightness->RedrawWindow();
				}
				else
				{
					m_DoStraightness=new CWilsonFrame();
					CCreateContext context;
					context.m_pNewViewClass=RUNTIME_CLASS(CDoStraightness);
					if (!m_DoStraightness->LoadFrame(IDI_PIST,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
					{
						return;
					}
					AddVIEW(m_DoStraightness);
					m_DoStraightness->ShowWindow(SW_SHOWMAXIMIZED);
					m_DoStraightness->InitialUpdateFrame(NULL,TRUE);
				}
			Timer32();
			}
		}
		else
		{
		//	if(0==check_done(m_lzhu_n))
		//	{
		//		AfxMessageBox("�������ݲ���");	
		//	}
			m_fn++;
		//	SetTimer(42,10,NULL);
		}
	}
}
//=============================================
/*  ƽ��Ȳ���  43-45 ��ѧ��*/

//=============================================
void CMainFrame::Timer43()
{

}
void CMainFrame::Timer44()
{
	int		analog_input1=0;
	double	analog_input=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -5.0/(G11*G22)*0.1)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(44); 
		sudden_stop(m_lzhu_n); 

		SetTimer(45,10,NULL);
	}
}
void CMainFrame::Timer45()
{
	KillTimer(45);
	int ret=666;		 
	unsigned short  pMem[3600];
	memset(pMem, 0, sizeof(pMem));
	//��������

	ret=WLS_8112PG_WaitZeroMinus_dlg();	//��������
	if(ret==-1)
	{
		AfxMessageBox("����λʧ��");
		return;
	}
    ret=WLS_8112PG_AD_INT_Sampling_dlg(m_fChannel,m_fGainNum,3600, pMem, 2, 100, 45);	//��������
	//���ݴ���
	int i;
	for(i=0;i<3600;i++)
	{
		m_data0[i].data=pMem[i];//////////////��¼��������
		m_data0[i].height=0;
		m_data0[i].selected=0;
	}
	m_fStateMessage="ƽ��Ȳ������";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	std::ofstream fin(m_fname,std::ios::binary|std::ios::app);
	for ( i=0;i<3600;i++)
	{	
		fin.write((char*)&m_data0[i], sizeof(shuju0));
	}
	fin.write((char*)&G11,sizeof(double));
	fin.write((char*)&G22,sizeof(double));
	fin.write((char*)&m_ftime,sizeof(CTime));////��Ϊ�ĸ��ֽ�
	fin.close();
	m_fullPath5=m_fname;
	if (m_fullPath5!="")
	{	
		if (m_DoPlaneness!=NULL)
		{
			m_DoPlaneness->MDIActivate();
			m_DoPlaneness->RedrawWindow();
		}
		else
		{
			m_DoPlaneness = new CWilsonFrame();
			CCreateContext context;
			context.m_pNewViewClass=RUNTIME_CLASS(CDoPlaneness);
			if (!m_DoPlaneness->LoadFrame(IDI_PMD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
			{
				return;
			}
			AddVIEW(m_DoPlaneness);
			m_DoPlaneness->ShowWindow(SW_SHOWMAXIMIZED);
			m_DoPlaneness->InitialUpdateFrame(NULL,TRUE);
		}
		Timer46();
	}
	
}
void CMainFrame::Timer46()/////��������
{
	KillTimer(46);
	get_abs_pos(m_lzhu_enn,&m_old_lzhupulse);
	set_profile(m_lzhu_n,3000,30000,10000);
	fast_pmove(m_lzhu_n,-m_fPositionAway*m_lzxishu*100);//�Զ�����
	SetTimer(47,10,NULL);
}
void CMainFrame::Timer47()
{
	UpdataDisplayBar();
	long com;
	get_abs_pos(m_lzhu_enn,&com);
	double ht;
	ht = abs(com-m_old_lzhupulse)*m_lzxishu;
	if (ht >= (m_fPositionAway))
	{
		KillTimer(47);
		SetTimer(12,10,NULL);
	}
}
//=============================================
/*  ƽ�жȲ���  48- 52 ��ѧ��*/

//=============================================

void CMainFrame::Timer48()
{
	int		analog_input1=0;
	double	analog_input=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -5.0/(G11*G22)*0.1)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(48);
		sudden_stop(m_dg_n);  
		//������������㡢��ʾ
		Timer49();
	}
}
void CMainFrame::Timer49()
{   

	KillTimer(49);
	if(!m_fbParallelism)
		m_fStateMessage="ƽ�жȲ�����1��ֱ��";
	else
		m_fStateMessage="ƽ�жȲ�����2��ֱ��";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);

	long lpulse;
	get_abs_pos(m_lzhu_enn,&m_old_lzhupulse);
	lpulse=m_fheight*1000/0.078;
	set_profile(m_lzhu_n,500,m_fVelocity2*1500/0.075,10000);
	fast_pmove(m_lzhu_n,lpulse*2.);//��������
    SetTimer(50,10,NULL);
}
void CMainFrame::Timer50()
{   	m_lx=2;
	UpdataDisplayBar();
	long com;
	get_abs_pos(m_lzhu_enn,&com);
	double ht;
	ht = abs(com-m_old_lzhupulse)*m_lzxishu;
	if (ht >= (m_fheight/3600)*m_fn)
	{
		//KillTimer(50);
        int analog_input1=0;
		W_812_AD_Aquire(&analog_input1);
		m_data[m_fn].data=analog_input1;//////////////��¼��������
		m_data[m_fn].selected=0;
		if(m_fn==3599)////������� ��¼����
		{
			KillTimer(50);
			sudden_stop(m_lzhu_n);
			std::ofstream fin(m_fname,std::ios::binary|std::ios::app);
			for (int i=0;i<3600;i++)
			{	
				fin.write((char*)&m_data[i], sizeof(shuju));
			}
			fin.close();
			m_fn=0;
			if(!m_fbParallelism)//����Ƿ�������
				Timer51();
			else
			{
				m_fbParallelism=false;
				m_fStateMessage="ƽ�жȲ������";
				m_wndStatusBar.SetPaneText(1,m_fStateMessage);
				std::ofstream fin(m_fname,std::ios::binary|std::ios::app);
				fin.write((char*)&G11,sizeof(double));
				fin.write((char*)&G22,sizeof(double));
				fin.write((char*)&m_fheight,sizeof(float));
				fin.write((char*)&m_ftime,sizeof(CTime));////��Ϊ�ĸ��ֽ�
				fin.close();
				m_fullPath4=m_fname;//////////////////////////////////////////////////�ļ�û���Ŀ��ܻ��д�
				if (m_fullPath4!="")
				{	
					if (m_DoParallelism!=NULL)
					{
						m_DoParallelism->MDIActivate();
						m_DoParallelism->RedrawWindow();
					}
					else
					{
						m_DoParallelism=new CWilsonFrame();
						CCreateContext context;
						context.m_pNewViewClass=RUNTIME_CLASS(CDoParallelism);
						if (!m_DoParallelism->LoadFrame(IDI_PXD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,
							this,&context))
						{
							return;
						}
						AddVIEW(m_DoParallelism);
						m_DoParallelism->ShowWindow(SW_SHOWMAXIMIZED);
						m_DoParallelism->InitialUpdateFrame(NULL,TRUE);
					}
					Timer32();
				}//if (m_fullPath4!="")
			}//if(!m_fbParallelism)
		}
		else
		{
			if(0==check_done(m_lzhu_n))
			{
				m_fn=0;
				KillTimer(50);
				AfxMessageBox("�������ݲ���");	
				return;
			}
			m_fn++;
		}
	}
}
void CMainFrame::Timer51()
{
	KillTimer(51);
	get_abs_pos(m_lzhu_enn,&m_old_lzhupulse);
	long lpulse;
	lpulse=m_fheight*1000/0.078;
	set_profile(m_lzhu_n,5000,30000,10000);
	fast_pmove(m_lzhu_n,-lpulse*2.);//�����½�
	SetTimer(52,10,NULL);
}
void CMainFrame::Timer52()
{
	UpdataDisplayBar();
	long com;
	get_abs_pos(m_lzhu_enn,&com);
	double ht;
	ht = abs(com-m_old_lzhupulse)*m_lzxishu;
	if (ht >= (m_fheight * 0.999))
	{   
		KillTimer(52);
		sudden_stop(m_lzhu_n);
		if(!m_fbParallelism)
		{
			m_fbParallelism=true;
			AfxMessageBox("��ת�Ƕ�!",MB_ICONWARNING);
			AfxMessageBox("ת�Ƕ���ɣ�",MB_ICONWARNING);
			Timer49();//////////////ֱ�Ӳ���
		}
	}	
}
//=============================================
/*  ͬ��Ȳ���  53-56  ��ѧ��*/

//=============================================

void CMainFrame::Timer53()//�������
{
	int		analog_input1=0;
	double	analog_input=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -5.0/(G11*G22)*0.1)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(53);
		sudden_stop(m_dg_n);
		Timer54();
	}	
}
void CMainFrame::Timer54()//��������
{
	KillTimer(54);
		long lPulse;
		if(m_fn==0)
			lPulse = m_fPerHeight[m_fn]*1000/0.078;//����������㣿����1.1
		else
			lPulse=(m_fPerHeight[m_fn]-m_fPerHeight[m_fn-1])*1000/0.078;
		m_wndStatusBar.SetPaneText(1,"ͬ��Ȳ�����������");
		set_profile(m_lzhu_n,10000,50000,15000);
		fast_pmove(m_lzhu_n,lPulse*5.);//��������
		SetTimer(55,10,NULL);
}
void CMainFrame::Timer55()//�����������
{
	UpdataDisplayBar();
	long com;
	get_abs_pos(m_lzhu_enn,&com);
	double ht;
	ht = abs(com-m_old_lzhupulse)*m_lzxishu;
	if (ht >= (m_fPerHeight[m_fn]))
	{
		KillTimer(55);
		sudden_stop(m_lzhu_n);
		m_fStateMessage.Format("ͬ��Ȳ�����%d����",m_fn+1);
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);

		SetTimer(56,10,NULL);
	}
}
void CMainFrame::Timer56()//��ʼ����
{
    m_lx=2;
	KillTimer(56);
	int ret=666;		 
	unsigned short  pMem[3600];
	memset(pMem, 0, sizeof(pMem));


	ret=WLS_8112PG_WaitZeroMinus_dlg();	//��������
	if(ret==-1)
	{
		AfxMessageBox("����λʧ��");
		return;
	}
    ret=WLS_8112PG_AD_INT_Sampling_dlg(m_fChannel,m_fGainNum,3600, pMem, 2, 100, 45);	//��������
	int i;
	for(i=0;i<3600;i++)	//���ݴ���
	{
		m_data0[i].data=pMem[i];//////////////��¼��������
		m_data0[i].selected=0;
		m_data0[i].height=m_fPerHeight[m_fn];//
	}	
		std::ofstream fin(m_fname,std::ios::binary|std::ios::app);
		for ( i=0;i<3600;i++)
		{	
			fin.write((char*)&m_data0[i], sizeof(shuju0));
		}
		fin.close();
		m_fn++;
		
		if(m_fn<m_fJiemianNum)//����û���
			Timer54();
		else
		{
			m_fStateMessage="ͬ��Ȳ������";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			std::ofstream fin(m_fname,std::ios::binary|std::ios::app);//�ļ���
			fin.write((char*)&G11,sizeof(double));
			fin.write((char*)&G22,sizeof(double));
			fin.write((char*)&m_ftime,sizeof(CTime));////��Ϊ�ĸ��ֽ�
			fin.close();
			
			m_fullPath7=m_fname;//·��
			if (m_fullPath7!="")
			{	
				if (m_DoCoaxiality!=NULL)
				{
					m_DoCoaxiality->MDIActivate();
					m_DoCoaxiality->RedrawWindow();
				}
				m_DoCoaxiality = new CWilsonFrame();
				CCreateContext context;
				context.m_pNewViewClass=RUNTIME_CLASS(CDoCoaxiality);
				if (!m_DoCoaxiality->LoadFrame(IDI_TZD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
				{
					return;
				}
				AddVIEW(m_DoCoaxiality);
				m_DoCoaxiality->ShowWindow(SW_SHOWMAXIMIZED);
				m_DoCoaxiality->InitialUpdateFrame(NULL,TRUE);
			}
			Timer32();
		}	
	}
void CMainFrame::Timer57()
{
}


//=============================================
/*  ��ֱ�Ȳ���  58- 61 ��ѧ��*/

//=============================================
void CMainFrame::Timer58()//�������
{
	int		analog_input1=0;
	double	analog_input=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -5.0/(G11*G22)*0.1)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(58);
		sudden_stop(m_dg_n);
		Timer59();
	}	
}
void CMainFrame::Timer59()//��������
{
	KillTimer(59);
		long lPulse;
		//get_abs_pos(m_lzhu_enn,&m_old_lzhupulse);
		if(m_fn==0)
			lPulse = m_fPerHeight[m_fn]*1000/0.078;//����������㣿����1.1
		else
			lPulse=(m_fPerHeight[m_fn]-m_fPerHeight[m_fn-1])*1000/0.078;
		m_wndStatusBar.SetPaneText(1,"��ֱ�Ȳ�����������");
		set_profile(m_lzhu_n,10000,50000,15000);
		fast_pmove(m_lzhu_n,lPulse*5.);//��������
		SetTimer(60,10,NULL);
}
void CMainFrame::Timer60()//�����������
{
	UpdataDisplayBar();
	long com;
	get_abs_pos(m_lzhu_enn,&com);
	double ht;
	ht = abs(com-m_old_lzhupulse)*m_lzxishu;
	if (ht >= (m_fPerHeight[m_fn]))
	{
		KillTimer(60);
		sudden_stop(m_lzhu_n);	

		m_fStateMessage.Format("��ֱ�Ȳ�����%d����",m_fn+1);
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);

		SetTimer(61,10,NULL);
	}
}
void CMainFrame::Timer61()//��ʼ����
{
	m_lx=2;
	KillTimer(61);
	int ret=666;		 
	unsigned short  pMem[3600];
	memset(pMem, 0, sizeof(pMem));


	ret=WLS_8112PG_WaitZeroMinus_dlg();	//��������

    ret=WLS_8112PG_AD_INT_Sampling_dlg(m_fChannel,m_fGainNum,3600, pMem, 2, 100, 45);	//��������
	if(ret==-1)
	{
		AfxMessageBox("����λʧ��");
		return;
	}
	int i;
	for(i=0;i<3600;i++)	//���ݴ���
	{
		m_data0[i].data=pMem[i];//////////////��¼��������
		m_data0[i].selected=0;
		m_data0[i].height=m_fPerHeight[m_fn];//
	}	
		std::ofstream fin(m_fname,std::ios::binary|std::ios::app);
		for ( i=0;i<3600;i++)
		{	
			fin.write((char*)&m_data0[i], sizeof(shuju0));
		}
		fin.close();
		m_fn++;
		
		if(m_fn<m_fJiemianNum)//����û���
			Timer59();
		else
		{
			m_fStateMessage="��ֱ�Ȳ������";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			std::ofstream fin(m_fname,std::ios::binary|std::ios::app);//�ļ���
			fin.write((char*)&G11,sizeof(double));
			fin.write((char*)&G22,sizeof(double));
			fin.write((char*)&m_ftime,sizeof(CTime));////��Ϊ�ĸ��ֽ�
			fin.close();
			
			m_fullPath8=m_fname;
			if (m_fullPath8!="")
			{	
				if (m_DoVerticality!=NULL)
				{
					m_DoVerticality->MDIActivate();
					m_DoVerticality->RedrawWindow();
				}
				m_DoVerticality = new CWilsonFrame();
				CCreateContext context;
				context.m_pNewViewClass=RUNTIME_CLASS(CDoVerticality);
				if (!m_DoVerticality->LoadFrame(IDI_TZD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
				{
					return;
				}
				AddVIEW(m_DoVerticality);
				m_DoVerticality->ShowWindow(SW_SHOWMAXIMIZED);
				m_DoVerticality->InitialUpdateFrame(NULL,TRUE);
			}
			Timer32();
	}	
}

//=============================================
/*  ƽ��ƽ�жȲ���  62- 61 ��ѧ��*/

//=============================================
void CMainFrame::Timer62()
{
	int		analog_input1=0;
	double	analog_input=0;
	W_812_AD_Aquire(&analog_input1);
	analog_input = ((analog_input1-2048)*10)/(G11*G22*4096);
	if(analog_input < -5.0/(G11*G22)*0.1)
	{
		UpdataDisplayBar();
	}
	else
	{
		KillTimer(62); 
		sudden_stop(m_lzhu_n); 
	
		m_fStateMessage.Format("ƽ��ƽ�жȲ�����%d����",m_fn+1);
		m_wndStatusBar.SetPaneText(1,m_fStateMessage);

		SetTimer(63,10,NULL);
	}
}
void CMainFrame::Timer63()
{

		KillTimer(63);
	int ret=666;		 
	unsigned short  pMem[3600];
	memset(pMem, 0, sizeof(pMem));
	

	ret=WLS_8112PG_WaitZeroMinus_dlg();	//��������
	if(ret==-1)
	{
		AfxMessageBox("����λʧ��");
		return;
	}
    ret=WLS_8112PG_AD_INT_Sampling_dlg(m_fChannel,m_fGainNum,3600, pMem, 2, 100, 45);	//��������
	int i;
	for(i=0;i<3600;i++)	//���ݴ���
	{
		m_data[i].data=pMem[i];//////////////��¼��������
		m_data[i].selected=0;
	}	
		std::ofstream fin(m_fname,std::ios::binary|std::ios::app);
		for ( i=0;i<3600;i++)
		{	
			fin.write((char*)&m_data[i], sizeof(shuju));
		}
		fin.close();
		m_fn++;
		
		if(m_fn<2)//����û���
		{
			SetTimer(12,10,NULL);
			AfxMessageBox("�ֶ��ƶ����ڶ�����");
			AfxMessageBox("�ƶ���ɣ���ʼ�Ӵ�����");
			KillTimer(12);
			set_profile(m_lzhu_n,1000,3000,5000);
			fast_vmove(m_lzhu_n,-1);;
			SetTimer(62,10,NULL);
		}
		else
		{
			m_fStateMessage="ƽ��ƽ�жȲ������";
			m_wndStatusBar.SetPaneText(1,m_fStateMessage);
			std::ofstream fin(m_fname,std::ios::binary|std::ios::app);//�ļ���
			fin.write((char*)&G11,sizeof(double));
			fin.write((char*)&G22,sizeof(double));
			fin.write((char*)&m_fheight,sizeof(float));
			fin.write((char*)&m_ftime,sizeof(CTime));////��Ϊ�ĸ��ֽ�
			fin.close();
			
			m_fullPath4=m_fname;
			if (m_fullPath4!="")
			{	
				if (m_DoParallelism!=NULL)
				{
					m_DoParallelism->MDIActivate();
					m_DoParallelism->RedrawWindow();
					Timer46();
				}
				m_DoParallelism=new CWilsonFrame();
				CCreateContext context;
				context.m_pNewViewClass=RUNTIME_CLASS(CDoParallelism);
				if (!m_DoParallelism->LoadFrame(IDI_PXD,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,
					this,&context))
				{
					return;
				}
				AddVIEW(m_DoParallelism);
				m_DoParallelism->ShowWindow(SW_SHOWMAXIMIZED);
				m_DoParallelism->InitialUpdateFrame(NULL,TRUE);
			}
			Timer46();
	}	
}

void CMainFrame::SwitchG11(int k)
{
	switch(k)
	{
	case 0: G11=0.25; m_fGainNum=0;m_fChannel=0;	break;
	case 1: G11=0.5;  m_fGainNum=1;m_fChannel=0;	break;
	case 2: G11=1;	  m_fGainNum=2;m_fChannel=0;	break;
	case 3: G11=2;	  m_fGainNum=3;m_fChannel=0;	break;
	case 4: G11=4;	  m_fGainNum=0;m_fChannel=1;	break;
	case 5: G11=8;	  m_fGainNum=1;m_fChannel=1;	break;
	case 6: G11=16;	  m_fGainNum=2;m_fChannel=1;	break;
	case 7: G11=32;	  m_fGainNum=3;m_fChannel=1;	break;
	}
	W_812_AD_Set_Gain(m_fGainNum);
	W_812_AD_Set_Channel(m_fChannel);
}

///////////////////////////////////////////////////
void CMainFrame::OnSetFileSavePath() 
{
	// TODO: Add your command handler code here
	CDlg_SavePath dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_strFileSavePath=dlg.m_strPath;
		OnResourcemanagement();
	}
}
//�û�����
void CMainFrame::OnUsersetting() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CDlgUserManagement dlg;
	if (dlg.DoModal()==IDOK)
	{
		char useroldname[6];
		char useroldpwd[6];
		
		std::ifstream fin("userinf.pwd", std::ios::binary);
		fin.read((char*)&useroldname,6*sizeof(char));
		fin.read((char*)&useroldpwd,6*sizeof(char));
		fin.close();
		//����
		useroldname[0]=useroldname[0]-41;
		useroldname[1]=useroldname[1]+22;
		useroldname[2]=useroldname[2]+9;
		useroldname[3]=useroldname[3]-4;
		useroldname[4]=useroldname[4]+15;
		useroldname[5]=useroldname[5]-6;
		
		useroldpwd[0]=useroldpwd[0]+100;
		useroldpwd[1]=useroldpwd[1]-21;
		useroldpwd[2]=useroldpwd[2]+6;
		useroldpwd[3]=useroldpwd[3]+7;
		useroldpwd[4]=useroldpwd[4]-18;
		useroldpwd[5]=useroldpwd[5]+51;
		int i;
		BOOL bcorrect=TRUE;
		for (i=0;i<6;i++)
		{ 
			if (i<dlg.m_strOldName.GetLength())
			{			
				if (useroldname[i]!=dlg.m_strOldName.GetAt(i))
				{
					bcorrect=FALSE;
					break;
				}
			} 
			else
			{ 
				if (useroldname[i]!=0x00)
				{
					bcorrect=FALSE;
					break;
				}
			}
			if (i<dlg.m_strOldPwd.GetLength())
			{			
				if (useroldpwd[i]!=dlg.m_strOldPwd.GetAt(i))
				{
					bcorrect=FALSE;
					break;
				}
			} 
			else
			{ 
				if (useroldpwd[i]!=0x00)
				{
					bcorrect=FALSE;
					break;
				}
			}

		}
		if (bcorrect)
		{
			char usernewname[6];
			char usernewpwd[6];
			//����
			for( i=0;i<6;i++)
			{
				if (i<dlg.m_strNewName.GetLength())
				{
					usernewname[i]=dlg.m_strNewName.GetAt(i);
				}
				else
				{
					usernewname[i]=0x00;
				}
				if (i<dlg.m_strNewPwd.GetLength())
				{
					usernewpwd[i]=dlg.m_strNewPwd.GetAt(i);
				}
				else
				{
					usernewpwd[i]=0x00;
				}
			}
			usernewname[0]=usernewname[0]+41;
			usernewname[1]=usernewname[1]-22;
			usernewname[2]=usernewname[2]-9;
			usernewname[3]=usernewname[3]+4;
			usernewname[4]=usernewname[4]-15;
			usernewname[5]=usernewname[5]+6;
			
			usernewpwd[0]=usernewpwd[0]-100;
			usernewpwd[1]=usernewpwd[1]+21;
			usernewpwd[2]=usernewpwd[2]-6;
			usernewpwd[3]=usernewpwd[3]-7;
			usernewpwd[4]=usernewpwd[4]+18;
			usernewpwd[5]=usernewpwd[5]-51;
			std::ofstream fout("userinf.pwd", std::ios::binary);
			fout.write((char*)&usernewname,6*sizeof(char));
			fout.write((char*)&usernewpwd,6*sizeof(char));
			fout.close();
		}
		else
		{
			AfxMessageBox("��������ȷ��ԭ�û�������ԭ����");	
		}
	}
}
///�������궨
void CMainFrame::OnChuganqiBiaoding() 
{
	// TODO: Add your command handler code here
	if(m_DoCircle!=NULL)
		m_DoCircle->ShowWindow(SW_SHOWMAXIMIZED);
	else
	{
		AfxMessageBox("δ����");
		return;
	}
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="canshu.ini";
	CDlgCHGQBiaoDing dlg;
	CString a;
    ::GetPrivateProfileString("����","m_dStdValue","",a.GetBuffer(100),100,strPath);
    dlg.m_dStdValue=atof(a);
	dlg.m_dMeaValue=atof(m_fMeaValue);
	if (dlg.DoModal()==IDOK)
	{
		//�������������m_G2;
		CString str;
		G22=WLS_CalcSensorRatior(dlg.m_dStdValue,dlg.m_dMeaValue,G22);	                
		str.Format("%.20f",G22);
		:: WritePrivateProfileString("����","G22",str,strPath);	
		str.Format("%.3f",dlg.m_dStdValue);
		:: WritePrivateProfileString("����","m_dStdValue",str,strPath);	
	}	
}
void CMainFrame::OnUpdateChuganqiBiaoding(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_DoCircle==NULL)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
//�������궨����
double CMainFrame::WLS_CalcSensorRatior(double stdvalue, double measuredvalue, double oldratio)
{
	//#define WLS_EPSELLON 0.0001
	double newratio;
	if (fabs(stdvalue) <WLS_EPSELLON) 
	{
		newratio=oldratio;
		TRACE("stdvalue abnormall. stdvalue=%f.\n", stdvalue);
	} 
	else 
	{
		newratio=(measuredvalue/stdvalue)*oldratio;
	}
	if (fabs(newratio)<WLS_EPSELLON) 
	{
		TRACE("newratio too small.\n");
		newratio=WLS_EPSELLON;
	}
	return newratio;
}
//���ղ������ù���
void CMainFrame::OnGongyiSetting() 
{
	// TODO: Add your command handler code here
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="config.ini";
	
	CDlgGongYiSetting dlg;
	CString a;
    ::GetPrivateProfileString("����","YD","",a.GetBuffer(100),100,strPath);
    dlg.m_dYD=atof(a);
	::GetPrivateProfileString("����","YZD","",a.GetBuffer(100),100,strPath);
    dlg.m_dYZD=atof(a);
	::GetPrivateProfileString("����","ZXD","",a.GetBuffer(100),100,strPath);
    dlg.m_dZXD=atof(a);
	::GetPrivateProfileString("����","PXD","",a.GetBuffer(100),100,strPath);
    dlg.m_dPXD=atof(a);
	::GetPrivateProfileString("����","PMD","",a.GetBuffer(100),100,strPath);
    dlg.m_dPMD=atof(a);
	::GetPrivateProfileString("����","TZD","",a.GetBuffer(100),100,strPath);
    dlg.m_dTZD=atof(a);
	::GetPrivateProfileString("����","CZD","",a.GetBuffer(100),100,strPath);
    dlg.m_dCZD=atof(a);
	if (dlg.DoModal()==IDOK)
	{
	//	if(IDOK==AfxMessageBox("ȷ�������趨ϵͳ������",MB_OKCANCEL))
	//	{
			CString A1;                // �����º��ֵת�����ַ�����ʽд��INI�ļ�����
			A1.Format("%.3f",dlg.m_dYD);
			:: WritePrivateProfileString("����","YD",A1,strPath);
			m_dGongyiPara[0]=dlg.m_dYD;

			A1.Format("%.3f",dlg.m_dYZD);
			:: WritePrivateProfileString("����","YZD",A1,strPath);
			m_dGongyiPara[1]=dlg.m_dYZD;

			A1.Format("%.3f",dlg.m_dZXD);
			:: WritePrivateProfileString("����","ZXD",A1,strPath);
			m_dGongyiPara[2]=dlg.m_dZXD;

			A1.Format("%.3f",dlg.m_dPXD);
			:: WritePrivateProfileString("����","PXD",A1,strPath);
			m_dGongyiPara[3]=dlg.m_dPXD;

			A1.Format("%.3f",dlg.m_dPMD);
			:: WritePrivateProfileString("����","PMD",A1,strPath);
			m_dGongyiPara[4]=dlg.m_dPMD;

			A1.Format("%.3f",dlg.m_dTZD);
			:: WritePrivateProfileString("����","TZD",A1,strPath);
			m_dGongyiPara[5]=dlg.m_dTZD;

			A1.Format("%.3f",dlg.m_dCZD);
			:: WritePrivateProfileString("����","CZD",A1,strPath);
			m_dGongyiPara[6]=dlg.m_dCZD;
	//	}
	}
}
//�趨�ֶ��ٶ�
void CMainFrame::OnHandVelocitySet() 
{
	// TODO: Add your command handler code here
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="canshu.ini";

	CDlgHands dlg;
	CString a;
    ::GetPrivateProfileString("����","m_cursel","",a.GetBuffer(100),100,strPath);
    dlg.m_cursel=atoi(a);
	if(dlg.DoModal()==IDOK)
	{
		m_fHandVelocity=dlg.m_dVelocity*1000/0.075;///////////////////////bilu 
		CString str;              
		str.Format("%d",dlg.m_cursel);
		:: WritePrivateProfileString("����","m_cursel",str,strPath);
	}
}

////////////////////=========================================
////////////////////=========================================
//������̬��ʾ����
void CMainFrame::OnDynamicdiplay() 
{
	// TODO: Add your command handler code here
	//����λ
	m_fStateMessage="��̬ɨ��";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	//�򿪶�̬��ʾ����
	if (m_DoDynamicDisplay!=NULL)
	{
		m_DoDynamicDisplay->MDIActivate();
		m_DoDynamicDisplay->RedrawWindow();
		return;
	}
	m_DoDynamicDisplay=new CWilsonFrame();
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CDoDynamicDisplay);
	if (!m_DoDynamicDisplay->LoadFrame(IDI_ICON17,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
	{
		return;
	}
	m_DoDynamicDisplay->ShowWindow(SW_SHOWMAXIMIZED);
	m_DoDynamicDisplay->InitialUpdateFrame(NULL,TRUE);

}
void CMainFrame::OnOpendyn() 
{
	//TODO: Add your control notification handler code here
	int ret=WLS_8112PG_WaitZeroMinus_dlg();
	if(ret==-1)
	{
		AfxMessageBox("����λʧ��");
		return;
	}
	reset_pos(m_zhuzhou_enn);
	m_fStateMessage="��̬ɨ���С���";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	//SetTimer(70,10,NULL);
}

void CMainFrame::OnStopdyn() 
{
	// TODO: Add your control notification handler code here
	m_fStateMessage="״̬��Ϣ";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
}
//��ȡλ�úʹ���������
void CMainFrame::GetMesData(long mes[2])
{
	mes[0]=abs(m_com)%3600;	
	mes[1]=m_analog_input1;	
}
void CMainFrame::Timer70()
{

}


///////////////////==============================================
/////////////==========================================================
void CMainFrame::OnMachineInf() 
{
	// TODO: Add your command handler code here
	//��ȡ������Ϣ
	CDlgMachineInf dlg;
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="config.ini";
 	CString a;	
	dlg.m_strCompanyName=m_strCompanyName;
	dlg.m_strOperatorName=m_strOperatorName;
	dlg.m_strMachineModel=m_strMachineModel;
	dlg.m_strMachineName=m_strMachineName;
	dlg.m_strProcess=m_strProcess;
	dlg.m_strWorkpieceModel=m_strWorkpieceModel;
	dlg.m_strWorkpieceNum=m_strWorkpieceNum;
	dlg.m_strInspector=m_strInspector;
	dlg.m_strIndent=m_strIndent;
	if (IDOK==dlg.DoModal())
	{
		a=dlg.m_strCompanyName;
		m_strCompanyName=a;
		::WritePrivateProfileString("����","CompanyName",a,strPath);
		a=dlg.m_strOperatorName;
		m_strOperatorName=a;
		::WritePrivateProfileString("����","OperatorName",a,strPath);
		a=dlg.m_strMachineModel;
		m_strMachineModel=a;
		::WritePrivateProfileString("����","MachineModel",a,strPath);
		a=dlg.m_strMachineName;
		m_strMachineName=a;
		::WritePrivateProfileString("����","MachineName",a,strPath);
		a=dlg.m_strProcess;
		m_strProcess=a;
		::WritePrivateProfileString("����","Process",a,strPath);
		a=dlg.m_strWorkpieceModel;
		m_strWorkpieceModel=a;
		::WritePrivateProfileString("����","WorkpieceModel",a,strPath);
		a=dlg.m_strWorkpieceNum;
		m_strWorkpieceNum=a;
		::WritePrivateProfileString("����","WorkpieceNum",a,strPath);
		a=dlg.m_strIndent;
		m_strIndent=a;
		::WritePrivateProfileString("����","Indent",a,strPath);
		a=dlg.m_strInspector;
		m_strInspector=a;
		::WritePrivateProfileString("����","Inspector",a,strPath);
	}
}

void CMainFrame::InitMachineInf()
{
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="config.ini";
	CString a;
	::GetPrivateProfileString("����","CompanyName","",a.GetBuffer(100),100,strPath);
	m_strCompanyName=a;
	::GetPrivateProfileString("����","OperatorName","",a.GetBuffer(100),100,strPath);
	m_strOperatorName=a;
	::GetPrivateProfileString("����","MachineModel","",a.GetBuffer(100),100,strPath);
	m_strMachineModel=a;
	::GetPrivateProfileString("����","MachineName","",a.GetBuffer(100),100,strPath);
	m_strMachineName=a;
	::GetPrivateProfileString("����","Process","",a.GetBuffer(100),100,strPath);
	m_strProcess=a;
	::GetPrivateProfileString("����","WorkpieceModel","",a.GetBuffer(100),100,strPath);
	m_strWorkpieceModel=a;
	::GetPrivateProfileString("����","WorkpieceNum","",a.GetBuffer(100),100,strPath);
	m_strWorkpieceNum=a;
	::GetPrivateProfileString("����","Indent","",a.GetBuffer(100),100,strPath);
	m_strIndent=a;
	::GetPrivateProfileString("����","Inspector","",a.GetBuffer(100),100,strPath);
	m_strInspector=a;
}

void CMainFrame::Onshujucanshu() 
{
	// TODO: Add your command handler code here
	CPropertyDlg prop;
    if(IDOK==prop.DoModal())
	{
		FilterMode=prop.m_IntFilter; //�õ��˲�ѡ���ѡ������
		CirEvalue=prop.m_IntAlg;  //�õ�Բ����������ѡ�񷽷��ı��
		freshView();
	}

}
//��������
void CMainFrame::OnZuobiaoSet() 
{
	// TODO: Add your command handler code here
	CDlgZuobiao dlg;
    FILE *fp2;
  	fp2=fopen("LZXISHU.txt","rt");
	fscanf(fp2,"%lf",&dlg.m_dgxishu);
	fscanf(fp2,"%lf",&dlg.m_lzxishu);
	fclose(fp2);

	if(dlg.DoModal()==IDOK)
	{
	m_lDaogui=dlg.m_fdaogui;
	m_lLizhu=dlg.m_flizhu;
	m_dgxishu=dlg.m_dgxishu;
	m_lzxishu=dlg.m_lzxishu;
	reset_pos(m_dg_enn);
	reset_pos(m_lzhu_enn);
	FILE *fp1;
  	fp1=fopen("LZXISHU.txt","w");
	fprintf(fp1,"%.9f \n",dlg.m_dgxishu);
	fprintf(fp1,"%.9f \n",dlg.m_lzxishu);
	fclose(fp1);
	}
}

void CMainFrame::Desktop()
{
	if ((m_DoCircle==NULL)&&(m_DoStraightness==NULL)&&(m_DoParallelism==NULL)&&
		(m_DoPlaneness==NULL)&&(m_DoCoaxiality==NULL)&&(m_DoVerticality==NULL)&&
		(m_DoCircleRunOut==NULL)&&(m_DoJMAnalyse==NULL)&&(m_DoAdjustPosition==NULL)&&
		(m_DoAdjustOritation==NULL)&&(m_DoDynamicDisplay==NULL)&&(m_DoCylinder==NULL))
	{	
		if (m_desktopview!=NULL)
		{
			m_desktopview->MDIActivate();
			m_desktopview->RedrawWindow();
			return;
		}
		m_desktopview=new CWilsonFrame();
		CCreateContext context;
		context.m_pNewViewClass=RUNTIME_CLASS(CDesktopView);
		if (!m_desktopview->LoadFrame(IDI_ICON17,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,
			this,&context))
		{
			return;
		}
		m_desktopview->ShowWindow(SW_SHOWMAXIMIZED);
		m_desktopview->InitialUpdateFrame(NULL,TRUE);
	}
}

void CMainFrame::OnOut() //��Բ
{
	// TODO: Add your command handler code here
	if(m_OutIn==1)
	{
		m_OutIn=-1;
		m_wndStatusBar.SetPaneText(3,"��Բ");
	}
	else
	{
		m_OutIn=1;
		m_wndStatusBar.SetPaneText(3,"��Բ");
	}
	freshView();
}

void CMainFrame::OnUpdateOut(CCmdUI* pCmdUI) //��Բ
{
	// TODO: Add your command update UI handler code here
	if(m_OutIn==1)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CMainFrame::OnAutodelqk() 
{
	// TODO: Add your command handler code here
	m_bAutoQK=!m_bAutoQK;
	freshView();
}

void CMainFrame::OnUpdateAutodelqk(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bAutoQK);
}

void CMainFrame::OnAutoqkxs() 
{
	// TODO: Add your command handler code here
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="canshu.ini";
	CDlg_QKxs dlg;
	dlg.m_fQKxs=m_fQKxs;
	if(dlg.DoModal()==IDOK)
	{
		m_fQKxs=dlg.m_fQKxs;
		CString A;
		A.Format("%.2f",m_fQKxs);//д�������ļ���
		 :: WritePrivateProfileString("����","m_fQKxs",A,strPath);	
		 freshView();
	}
		
}
void CMainFrame::freshView()
{
	if(m_DoCircle!=NULL)
	{
		m_DoCircle->RedrawWindow();
	}
	if(m_DoCoaxiality!=NULL)
	{
		m_DoCoaxiality->Invalidate();
	}
	if(m_DoCylinder!=NULL)
	{
		m_DoCylinder->Invalidate();
	}
	if(m_DoJMAnalyse!=NULL)
	{
		m_DoJMAnalyse->Invalidate();
	}
	if(m_DoPlaneness!=NULL)
	{
		m_DoPlaneness->Invalidate();
	}
	if(m_DoVerticality!=NULL)
	{
		m_DoVerticality->Invalidate();
	}
	if(m_DoCircleRunOut!=NULL)
	{
		m_DoCircleRunOut->Invalidate();
	}
}

void CMainFrame::CheckDianji(int *stat)
{
	if (stat[0]==1)
	{
		MessageBox("���1������λ,�븴λ������װ�й�����","WILSON",MB_ICONEXCLAMATION|MB_OK);
	} 
	else if(stat[0]==-1)
	{
		MessageBox("���1������λ,�븴λ������װ�й�����","WILSON",MB_ICONEXCLAMATION|MB_OK);
	}
	else
	{
		MessageBox("����������","WILSON",MB_ICONEXCLAMATION|MB_OK);
	}
	if (stat[1]==1)
	{
		MessageBox("���2������λ,�븴λ������װ�й�����","WILSON",MB_ICONEXCLAMATION|MB_OK);
	} 
	else if(stat[1]==-1)
	{
		MessageBox("���2������λ,�븴λ������װ�й�����","WILSON",MB_ICONEXCLAMATION|MB_OK);
	}
	else
	{
		MessageBox("����������","WILSON",MB_ICONEXCLAMATION|MB_OK);
	}
	if (stat[2]==1)
	{
		MessageBox("���3������λ,�븴λ������װ�й�����","WILSON",MB_ICONEXCLAMATION|MB_OK);
	} 
	else if(stat[2]==-1)
	{
		MessageBox("���3������λ,�븴λ������װ�й�����","WILSON",MB_ICONEXCLAMATION|MB_OK);
	}
	else
	{
		MessageBox("����������","WILSON",MB_ICONEXCLAMATION|MB_OK);
	}
	if (stat[3]==1)
	{
		MessageBox("���4������λ,�븴λ������װ�й�����","WILSON",MB_ICONEXCLAMATION|MB_OK);
	} 
	else if(stat[3]==-1)
	{
		MessageBox("���4������λ,�븴λ������װ�й�����","WILSON",MB_ICONEXCLAMATION|MB_OK);
	}
	else
	{
		MessageBox("����������","WILSON",MB_ICONEXCLAMATION|MB_OK);
	}
	m_fStateMessage="״̬��Ϣ";
	m_wndStatusBar.SetPaneText(1,m_fStateMessage);
	SetTimer(12,10,NULL);
}

void CMainFrame::OnUpdateDynamicdiplay(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bDongTai);
}
int CMainFrame::WLS_8112PG_WaitZeroMinus_dlg()
{
	CString strTemp;
	strTemp.Format("%s����λ..",m_fStateMessage);
	m_wndStatusBar.SetPaneText(1,strTemp);
	int ret;
	unsigned int zero=0;
    //CTimeSpan( LONG lDays, int nHours, int nMins, int nSecs );//
	CTimeSpan timeout_max(0,0,0,WLS_ZERO_TIMEOUT); //timeout max//
	CTimeSpan deltatime;
	
	CTime begintime = CTime::GetCurrentTime();
	CTime currtime;
	
	//Initialize status//
	while(zero==0)
	{
		ret=W_812_DI_Channel(0 ,&zero );		
		currtime=CTime::GetCurrentTime();
		deltatime=currtime-begintime;		
		if (deltatime>=timeout_max) 
		{
			goto errexit;
		}
		Sleep(0);
	}
    while(zero==1)
	{
		ret=W_812_DI_Channel(0,&zero );
		if (ret) 
		{
			goto errexit;
		}
		currtime=CTime::GetCurrentTime();
		deltatime=currtime-begintime;
		
		if (deltatime>=timeout_max) 
		{
			goto errexit;
		}
		Sleep(0);
	}
	
	return 0;
errexit:
	return -1;
}

int CMainFrame:: WLS_8112PG_AD_INT_Sampling_dlg(int ad_ch_no, int ad_gain,int count, 
											   unsigned short *ad_buffer, 
											   unsigned int c1, unsigned int c2, 
											   int tmout)
{
	CString strTemp;
	strTemp.Format("%s�ɼ���..",m_fStateMessage);
	m_wndStatusBar.SetPaneText(1,strTemp);
	int ret;
	CTimeSpan timeout_max(0,0,0,tmout); //timeout max//
	CTimeSpan deltatime;
	
	CTime begintime = CTime::GetCurrentTime();
	CTime currtime;
	int status=0;
	int adinput;
	int i, adcount;	
	// begin AD conversion//
	ret=W_812_AD_INT_Start(ad_ch_no, ad_gain, 5, 3600, ad_buffer,c1,c2);
	if (ret)
	{
		goto errexit;
	}
	ret=W_812_AD_INT_Status(&status ,&adcount);
	if (ret) 
	{
		goto errexit;
	}
	while (status != AD_INT_STOP )
	{
		ret=W_812_AD_INT_Status(&status ,&adcount);
		if (ret) 
		{
			goto errexit;
		}	
		currtime=CTime::GetCurrentTime();
		deltatime=currtime-begintime;	
		if (deltatime>=timeout_max)
		{
			goto errexit;
		}	
	}
	ret=W_812_AD_INT_Stop(&adcount );
	if (ret) 
	{
		goto errexit;
	}
	FILE *fp1;
	fp1=fopen("2.txt","w");
	for (i=0; i<adcount; i++) {
		adinput=ad_buffer[i]&0xfff;
		ad_buffer[i]=adinput;
		fprintf(fp1,"%d \n",adinput);
	}
	
	fclose(fp1);
	strTemp.Format("%s�ɼ����",m_fStateMessage);
	m_wndStatusBar.SetPaneText(1,strTemp);
	return 0;
errexit:
   return -1;
}
/*----------------------------------------------
*
*
*
----------------------------------------------*/
void CMainFrame::AddVIEW(CWilsonFrame *m_view)
{
	if(VIEW_No>=(MAXVIEWNo-1))
	{
		VIEW[0]->SendMessage(WM_CLOSE,0,0);
		for(int i=0;i<4;i++)
			VIEW[i]=VIEW[i+1];
		VIEW[4]=m_view;
	}
	else
	{
		VIEW[VIEW_No]=m_view;
		VIEW_No++;
	}
}
void CMainFrame::DestroyVIEW(CWilsonFrame *m_view)
{
	if(VIEW_No==0)
		return;
	for(int i=0;i<=VIEW_No;i++)
	{
		if(VIEW[i]==m_view)
		{
			if(i==(MAXVIEWNo-1))
				VIEW[(MAXVIEWNo-1)]=NULL;
			else
			{
				for(int j=i;j<VIEW_No;j++)
				VIEW[j]=VIEW[j+1];
				VIEW[VIEW_No]=NULL;
			}
			VIEW_No--;
		}
	}
}



void CMainFrame::OnMENULpxianshi() 
{
	// TODO: Add your command handler code here
	m_Lpxianshi=!m_Lpxianshi;
	freshView();
}

void CMainFrame::OnUpdateMENULpxianshi(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(m_Lpxianshi);
}
BOOL CMainFrame:: GetMacAddress(CString &strMac)
{
    PIP_ADAPTER_INFO pAdapterInfo;  
    DWORD AdapterInfoSize;  
    TCHAR szMac[32] = {0};  
    DWORD Err;  
     
    AdapterInfoSize = 0;  
    Err = GetAdaptersInfo(NULL, &AdapterInfoSize);  
     
    if((Err != 0) && (Err != ERROR_BUFFER_OVERFLOW))
        {  
        TRACE("���������Ϣʧ�ܣ�");  
        return   FALSE;  
    }  
     
    //   ����������Ϣ�ڴ�  
    pAdapterInfo = (PIP_ADAPTER_INFO)GlobalAlloc(GPTR, AdapterInfoSize);  
    if(pAdapterInfo == NULL)
        {  
        TRACE("����������Ϣ�ڴ�ʧ��");  
        return   FALSE;  
    }  
     
    if(GetAdaptersInfo(pAdapterInfo, &AdapterInfoSize) != 0)
        {  
        TRACE(_T("���������Ϣʧ�ܣ�\n"));  
        GlobalFree(pAdapterInfo);  
        return   FALSE;  
    }  
     
    strMac.Format(_T("%02X%02X%02X%02X%02X%02X"),    
        pAdapterInfo->Address[0],  
        pAdapterInfo->Address[1],  
        pAdapterInfo->Address[2],  
        pAdapterInfo->Address[3],  
        pAdapterInfo->Address[4],  
        pAdapterInfo->Address[5]);  
     
    GlobalFree(pAdapterInfo);  
    return   TRUE;  
 
}
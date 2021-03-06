// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__BAE7218A_A42A_472A_B4DF_E4C7B84CDE1B__INCLUDED_)
#define AFX_MAINFRM_H__BAE7218A_A42A_472A_B4DF_E4C7B84CDE1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "WilsonFrame.h"
#include "ComboToolBar1.h"
#include "DlgAjustCenter.h"
#include "DlgAjustCenterAndPose.h"
#include "DlgAjustPingjing.h"

#include "DoCircle.h"
#include "DlgOneAxisPara1.h"
#include "Mpc.h"
#include "WLS8112PG.h"
#include "DLL2.H"

#include "biaoding.h"	// Added by ClassView
#include "MotorCorrection.h"	// Added by ClassView

#include "Dlg_YD.h"
#include "Dlg_YZD.h"
#include "Dlg_ZXD.h"
#include "Dlg_PMD.h"
#include "Dlg_PXD.h"
#include "Dlg_TZD.h"
#include "Dlg_CZD.h"
#include "Dlg_pmPXD.h"
#include "Dlg_QKxs.h"
#include "Dlg_SavePath.h"
#define		pulseeq		0.00003    //电机的脉冲当量，单位为毫米
#define  MAXVIEWNo    5
////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes	
private:
	HANDLE hThread;
	DWORD ThreadID;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
//轴运动变量及过程控制函数
protected:
	//单轴运动模块，write by little snow
	int		m_pingtaix_enn;	
	int		m_pingtaiy_enn;
	int		m_zhituifir_enn;
	int		m_zhituisec_enn;
	int		m_dg_enn;
	int		m_lzhu_enn;
	int     m_zhuzhou_enn;

	long	m_old_zhituisecpulse;
	long	m_old_zhituifirpulse;
	long	m_old_ptypulse;
	long	m_old_ptxpulse;
	long	m_old_dgpulse;
	

	int		m_pingtaiy_n;
	int		m_pingtaix_n;
	int		m_zhituifir_n;
	int		m_zhituisec_n;
	int		m_dg_n;
	int		m_lzhu_n;
	int     m_lx;

	int		m_movechanged2;
	int		m_movechanged; 
	int		m_stop_flag1;
	int		m_stop_flag;
	CString strip;

	void	Timer9();
	void	Timer99();
	void	Timer10();
	void	Timer11();
	void	Timer12();
	void	Timer13();
	int		InitBoard();
//自动调整模块变量   write by wulei
	double	m_dFastMoveDistance;		//快速移动距离
	double	m_dLTargetEccentricity;		//目标偏心量（下）
	double	m_dHTargetEccentricity;		//目标偏心量（上）
	double	m_dDistance;				//测量后退距离（调心调平）
	double  m_dDistance2;               //离心距离（调平）
	
	//调心过程
	void	Timer1();
	void    Timer2();
	void    Timer3();
	void    Timer4();
	//调心调平过程
	void    Timer5();
	void    Timer6();
	void    Timer7();
	void    Timer8();
	void    Timer14();
	void    Timer15();
	void    Timer16();
	void    Timer17();
	void    Timer18();
	void    Timer19();
	//调平过程
	void	Timer20();
	void	Timer21();
	void    Timer22();
	void    Timer23();
public:
	BOOL  GetMacAddress(CString &strMac);
	void    UpdataDisplayBar();//更新工具条
	double WLS_CalcSensorRatior(double stdvalue, double measuredvalue, double oldratio);
public:
	int		m_down_circledata[3600];      //下圆周数据
	double	m_down_pxin;
	double  m_down_angle;
	int		m_up_circledata[3600];		  //上圆周数据
	double	m_up_pxin;
	double  m_up_angle;
	long	m_old_lzhupulse;
	double  m_distancePulse;//移动距离
	double	m_dHeight;					//调整高度
	int		m_intTimes;	
	int     m_intTimes2;			//迭代次数
	double   m_dgxishu;
	double   m_lzxishu;
	//double cf[36];
/////=======================================================================/////////////////////
public:
	//测圆度
	void Timer30();
	void Timer31();
	void Timer32();//自动撤离
	void Timer33();
		//测圆柱度
    void Timer34();
	void Timer35();
	void Timer36();
	void Timer37();
	void Timer38();//测量后会原位
	void Timer39();
		//直线度
	void Timer40();
	void Timer41();
	void Timer42();
	void Timer43();
		//平面度
	void Timer44();
	void Timer45();
	void Timer46();//平面度测量自动撤离
	void Timer47();
		//平行度
	void Timer48();
	void Timer49();
	void Timer50();
	void Timer51();
	void Timer52();
		//同轴度
	void Timer53();
	void Timer54();
	void Timer55();
	void Timer56();
	void Timer57();
		//垂直度
	void Timer58();
	void Timer59();
	void Timer60();
	void Timer61();
	void Timer62();
	void Timer63();
	//动态扫描
	void Timer70();
	void Timer71();
	void Timer72();
	void OnOpendyn();//开启动态扫描
	void OnStopdyn();//关闭动态扫描
	void CheckDianji(int *status);

	void SwitchG11(int k);//档位参数设置
	void freshView();     //刷新视图
	void Desktop();//首页显示
	//坐标调整
	float m_lDaogui;
	float m_lLizhu;
///复位变量
	CString m_fMeaValue;//传感器参数计算时测量值
	BOOL m_bDongTai;
	bool m_breset1;//复位
	bool m_breset2;
	bool m_breset3;
	bool m_breset4;//复位
	//
	int FilterMode;//滤波选择
	int CirEvalue;//评定算法
	int m_OutIn;//内外园选项
	BOOL m_bAutoQK;//自动去缺口
	BOOL m_Lpxianshi;//邻片显示
	float m_fQKxs;//缺口平滑系数
	long m_com;//记录主轴的旋转//动态显示
	int m_analog_input1;//传感器的读值//动态显示
	
	BOOL m_fbBack0;//测量后回原位
	int m_fDengJianGe;//是否等间隔测量
	float m_fPerHeight[15];//每层的高度//圆柱度
	int	m_fJiemianNum;//需要测量层数//圆柱度
	float m_fheight;//测量高度
	
	CTime m_ftime;//采样时间//测量变量
	CString m_fname; //文件名//测量变量
	bool m_fbPre;//传感器自动靠近工件//测量变量
	float m_fPositionAway;//离开距离//测量变量
    
	int m_fVCurSel;//直线度测量sudu档位
	float m_fVelocity2;//测量速度直线度和平行度
	int m_fn;//已经测量次数
	bool m_fbParallelism;//用来检测平行度测量完成度
	
	int m_fVelocityCurSel;//速度档位
	double   m_fHandVelocity;//手动挡速度
	int  m_fintTimes;//记录调整过程中的测量次数
	CString  m_fStateMessage;//状态信息
	int m_fGainNum;//测量档位
	int m_fChannel;//传感器通道
	int m_fG11CurSel;//测量档位           
/////=====================================================================////////////////////////////封学真
	shuju m_data[3600];//圆度，直线度，平行度；
	shuju0 m_data0[3600];////圆柱度，平面度，垂直度，同轴度
	void MotorPara();
	void GetMesData(long mes[2]);//动态扫描
	CMotorCorrection *m_MotorPara;
	
	double m_pingjing_cf[36];
	double cf[36];
	void InitMotorcorrection();
	void PlatformMoveAll(double pxin,double correctionfactor[],double legmov[]);
	void InitdianjiPra();
	Cbiaoding m_Adjustment;
	CString m_strFileSavePath;
	void	DoJMAnalyse();
	void	SetToolBarState(int index,BOOL bstate);
	
	CString m_fullPath;
	CString m_fullPath1;
	CString m_fullPath2;
	CString m_fullPath3;
	CString m_fullPath4;
	CString m_fullPath5;
	CString m_fullPath6;
	CString m_fullPath7;
	CString m_fullPath8;
	CString m_fullPath9;
	CString m_fullPath10;
	double	m_dGongyiPara[10];
	//界面分析变量
	CString m_fullJMPath;
	int     m_fullJMNum;
	int     m_fullJMType;
	int     m_SelectJM;
	double  G11;
	double  G22;
	BOOL  JMCL;
	
	CString m_strCompanyName;
	CString m_strOperatorName;
	CString m_strMachineModel;
	CString m_strMachineName;
	CString m_strProcess;
	CString m_strWorkpieceModel;
	CString m_strWorkpieceNum;
	CString m_strIndent;
	CString m_strInspector;


	CWilsonFrame *m_DoCircle;
	CWilsonFrame *m_DoCylinder;
	CWilsonFrame *m_DoStraightness;
	CWilsonFrame *m_DoParallelism;
	CWilsonFrame *m_DoPlaneness;
	CWilsonFrame *m_DoCoaxiality;
	CWilsonFrame *m_DoVerticality;
	CWilsonFrame *m_DoCircleRunOut;
	CWilsonFrame *m_DoJMAnalyse;
	CWilsonFrame *m_DoDynamicDisplay;
    CWilsonFrame *m_DoAdjustPosition;
    CWilsonFrame *m_DoAdjustOritation;
	CWilsonFrame *m_desktopview;
	CWilsonFrame *VIEW[MAXVIEWNo];
	int VIEW_No;//视图数量
	void AddVIEW(CWilsonFrame *m_view);//添加视图
	void DestroyVIEW(CWilsonFrame *m_view);//关闭视图
	void SetToolBarShow();
	void SetToolBarHide();
	void OnAdjustPosition();
	void OnAdjustOritation();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
		CStatusBar  m_wndStatusBar;
protected:  // control bar embedded members

	CToolBar    m_wndToolBar;
	CDialogBar	m_wndToolBar2;
	CCoolBar    m_wndToolBar3;
    CToolBar    m_ToolBar1;
    CComboToolBar  m_ToolBar2;

// Generated message map functions
protected:
	void InitMachineInf();
	int WLS_8112PG_WaitZeroMinus_dlg();
	int WLS_8112PG_AD_INT_Sampling_dlg(int ad_ch_no, int ad_gain,int count, unsigned short *ad_buffer, unsigned int c1, unsigned int c2, int tmout);
    CComboBox m_wndZoom;	
	CTreeCtrl   m_wndTree;
	CImageList m_imageList;
    CImageList m_img1;
    CImageList m_img2;
	CImageList m_iImageList123;//图标链

	HTREEITEM strRoot;     //HTREEITEM是树中节点的句柄，也就是一个DWORD值。可以通过它找到一个节点，从而取得节点的属性
	                       //GetItemText(HTREEITEM hItem);或对节点进行某些操作，如删除DeleteItem(   HTREEITEM   hItem   );
	HTREEITEM strHTFir;
	HTREEITEM strHTSec;
	HTREEITEM strHtThi;
	HTREEITEM strHtFor;
	HTREEITEM strHtFif;
	HTREEITEM strHtEnd;	
	
	CString GetFullPath(HTREEITEM hCurrent);
	void BrowseFile(int CallNum, CString strFile);
	void OnDisConnect();
	void OnConnect();	
	void OnDoubleClick(NMHDR* pnmhdr, LRESULT *plr);
	void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDoCircle();
	afx_msg void OnStopAll();
	afx_msg void OnAjustCenter();
	afx_msg void OnAjustLevel();
	afx_msg void OnAjustCenterandLevel();
	afx_msg void OnHReset();
	afx_msg void OnResourcemanagement();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDaoguiLeft();
	afx_msg void OnDaoguiRight();
	afx_msg void OnLizhuDown();
	afx_msg void OnLizhuUp();
	afx_msg void OnSensorSide();
	afx_msg void OnGowork();
	afx_msg void OnDoCylinder();
	afx_msg void OnSensorDown();
	afx_msg void OnDoStraightness();
	afx_msg void OnDoParallelism();
	afx_msg void OnDoPlaneness();
	afx_msg void OnDocoaxiality();
	afx_msg void OnDoverticality();
	afx_msg void OnZhituidianjisecondU();
	afx_msg void OnZhituidianjisecondD();
	afx_msg void OnZhituidianjifirstU();
	afx_msg void OnZhituidianjifirstD();
	afx_msg void OnPingtaiXb();
	afx_msg void OnPingtaiXf();
	afx_msg void OnPingtaiYl();
	afx_msg void OnPingtaiYr();
	afx_msg void OnCanshuchushi();
	afx_msg void OnMotorstate();
	afx_msg void OnMotorCorrect();
	afx_msg LRESULT OnMotorDialog(WPARAM wParam,LPARAM lParam);///////////////////fengxuezhen
	afx_msg void OnSetFileSavePath();
	afx_msg void OnUsersetting();
	afx_msg void OnChuganqiBiaoding();
	afx_msg void OnDaqAxiality();//同轴度
	afx_msg void OnDaqCircleSemiau();//圆度
	afx_msg void OnDaqCydSemiau();//圆柱度
	afx_msg void OnDaqPara();//平行度
	afx_msg void OnDAQpmPLANENESS();//平面平行度
	afx_msg void OnDaqPlaneness();//平面度
	afx_msg void OnDaqSquareness();//垂直度
	afx_msg void OnDaqStraightness();//直线度
	afx_msg void OnGongyiSetting();
	afx_msg void OnHandVelocitySet();
	afx_msg void OnDynamicdiplay();
	afx_msg void OnMachineInf();
	afx_msg void Onshujucanshu();
	afx_msg void OnZuobiaoSet();
	afx_msg void OnOut();
	afx_msg void OnUpdateOut(CCmdUI* pCmdUI);
	afx_msg void OnAutodelqk();
	afx_msg void OnUpdateAutodelqk(CCmdUI* pCmdUI);
	afx_msg void OnAutoqkxs();
	afx_msg void OnUpdateDynamicdiplay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateChuganqiBiaoding(CCmdUI* pCmdUI);
	afx_msg void OnMENULpxianshi();
	afx_msg void OnUpdateMENULpxianshi(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__BAE7218A_A42A_472A_B4DF_E4C7B84CDE1B__INCLUDED_)

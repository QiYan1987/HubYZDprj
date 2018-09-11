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
#define		pulseeq		0.00003    //��������嵱������λΪ����
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
//���˶����������̿��ƺ���
protected:
	//�����˶�ģ�飬write by little snow
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
//�Զ�����ģ�����   write by wulei
	double	m_dFastMoveDistance;		//�����ƶ�����
	double	m_dLTargetEccentricity;		//Ŀ��ƫ�������£�
	double	m_dHTargetEccentricity;		//Ŀ��ƫ�������ϣ�
	double	m_dDistance;				//�������˾��루���ĵ�ƽ��
	double  m_dDistance2;               //���ľ��루��ƽ��
	
	//���Ĺ���
	void	Timer1();
	void    Timer2();
	void    Timer3();
	void    Timer4();
	//���ĵ�ƽ����
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
	//��ƽ����
	void	Timer20();
	void	Timer21();
	void    Timer22();
	void    Timer23();
public:
	BOOL  GetMacAddress(CString &strMac);
	void    UpdataDisplayBar();//���¹�����
	double WLS_CalcSensorRatior(double stdvalue, double measuredvalue, double oldratio);
public:
	int		m_down_circledata[3600];      //��Բ������
	double	m_down_pxin;
	double  m_down_angle;
	int		m_up_circledata[3600];		  //��Բ������
	double	m_up_pxin;
	double  m_up_angle;
	long	m_old_lzhupulse;
	double  m_distancePulse;//�ƶ�����
	double	m_dHeight;					//�����߶�
	int		m_intTimes;	
	int     m_intTimes2;			//��������
	double   m_dgxishu;
	double   m_lzxishu;
	//double cf[36];
/////=======================================================================/////////////////////
public:
	//��Բ��
	void Timer30();
	void Timer31();
	void Timer32();//�Զ�����
	void Timer33();
		//��Բ����
    void Timer34();
	void Timer35();
	void Timer36();
	void Timer37();
	void Timer38();//�������ԭλ
	void Timer39();
		//ֱ�߶�
	void Timer40();
	void Timer41();
	void Timer42();
	void Timer43();
		//ƽ���
	void Timer44();
	void Timer45();
	void Timer46();//ƽ��Ȳ����Զ�����
	void Timer47();
		//ƽ�ж�
	void Timer48();
	void Timer49();
	void Timer50();
	void Timer51();
	void Timer52();
		//ͬ���
	void Timer53();
	void Timer54();
	void Timer55();
	void Timer56();
	void Timer57();
		//��ֱ��
	void Timer58();
	void Timer59();
	void Timer60();
	void Timer61();
	void Timer62();
	void Timer63();
	//��̬ɨ��
	void Timer70();
	void Timer71();
	void Timer72();
	void OnOpendyn();//������̬ɨ��
	void OnStopdyn();//�رն�̬ɨ��
	void CheckDianji(int *status);

	void SwitchG11(int k);//��λ��������
	void freshView();     //ˢ����ͼ
	void Desktop();//��ҳ��ʾ
	//�������
	float m_lDaogui;
	float m_lLizhu;
///��λ����
	CString m_fMeaValue;//��������������ʱ����ֵ
	BOOL m_bDongTai;
	bool m_breset1;//��λ
	bool m_breset2;
	bool m_breset3;
	bool m_breset4;//��λ
	//
	int FilterMode;//�˲�ѡ��
	int CirEvalue;//�����㷨
	int m_OutIn;//����԰ѡ��
	BOOL m_bAutoQK;//�Զ�ȥȱ��
	BOOL m_Lpxianshi;//��Ƭ��ʾ
	float m_fQKxs;//ȱ��ƽ��ϵ��
	long m_com;//��¼�������ת//��̬��ʾ
	int m_analog_input1;//�������Ķ�ֵ//��̬��ʾ
	
	BOOL m_fbBack0;//�������ԭλ
	int m_fDengJianGe;//�Ƿ�ȼ������
	float m_fPerHeight[15];//ÿ��ĸ߶�//Բ����
	int	m_fJiemianNum;//��Ҫ��������//Բ����
	float m_fheight;//�����߶�
	
	CTime m_ftime;//����ʱ��//��������
	CString m_fname; //�ļ���//��������
	bool m_fbPre;//�������Զ���������//��������
	float m_fPositionAway;//�뿪����//��������
    
	int m_fVCurSel;//ֱ�߶Ȳ���sudu��λ
	float m_fVelocity2;//�����ٶ�ֱ�߶Ⱥ�ƽ�ж�
	int m_fn;//�Ѿ���������
	bool m_fbParallelism;//�������ƽ�жȲ�����ɶ�
	
	int m_fVelocityCurSel;//�ٶȵ�λ
	double   m_fHandVelocity;//�ֶ����ٶ�
	int  m_fintTimes;//��¼���������еĲ�������
	CString  m_fStateMessage;//״̬��Ϣ
	int m_fGainNum;//������λ
	int m_fChannel;//������ͨ��
	int m_fG11CurSel;//������λ           
/////=====================================================================////////////////////////////��ѧ��
	shuju m_data[3600];//Բ�ȣ�ֱ�߶ȣ�ƽ�жȣ�
	shuju0 m_data0[3600];////Բ���ȣ�ƽ��ȣ���ֱ�ȣ�ͬ���
	void MotorPara();
	void GetMesData(long mes[2]);//��̬ɨ��
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
	//�����������
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
	int VIEW_No;//��ͼ����
	void AddVIEW(CWilsonFrame *m_view);//������ͼ
	void DestroyVIEW(CWilsonFrame *m_view);//�ر���ͼ
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
	CImageList m_iImageList123;//ͼ����

	HTREEITEM strRoot;     //HTREEITEM�����нڵ�ľ����Ҳ����һ��DWORDֵ������ͨ�����ҵ�һ���ڵ㣬�Ӷ�ȡ�ýڵ������
	                       //GetItemText(HTREEITEM hItem);��Խڵ����ĳЩ��������ɾ��DeleteItem(   HTREEITEM   hItem   );
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
	afx_msg void OnDaqAxiality();//ͬ���
	afx_msg void OnDaqCircleSemiau();//Բ��
	afx_msg void OnDaqCydSemiau();//Բ����
	afx_msg void OnDaqPara();//ƽ�ж�
	afx_msg void OnDAQpmPLANENESS();//ƽ��ƽ�ж�
	afx_msg void OnDaqPlaneness();//ƽ���
	afx_msg void OnDaqSquareness();//��ֱ��
	afx_msg void OnDaqStraightness();//ֱ�߶�
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
// MotorState.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "MotorState.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMotorState dialog


CMotorState::CMotorState(CWnd* pParent /*=NULL*/)
	: CDialog(CMotorState::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMotorState)
	//}}AFX_DATA_INIT
}


void CMotorState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMotorState)
	DDX_Control(pDX, IDC_STATIC18, m_ctrBmp12);
	DDX_Control(pDX, IDC_STATIC17, m_ctrBmp11);
	DDX_Control(pDX, IDC_STATIC16, m_ctrBmp10);
	DDX_Control(pDX, IDC_STATIC15, m_ctrBmp9);
	DDX_Control(pDX, IDC_STATIC14, m_ctrBmp8);
	DDX_Control(pDX, IDC_STATIC13, m_ctrBmp7);
	DDX_Control(pDX, IDC_STATIC12, m_ctrBmp6);
	DDX_Control(pDX, IDC_STATIC11, m_ctrBmp5);
	DDX_Control(pDX, IDC_STATIC10, m_ctrBmp4);
	DDX_Control(pDX, IDC_STATIC9, m_ctrBmp3);
	DDX_Control(pDX, IDC_STATIC8, m_ctrBmp2);
	DDX_Control(pDX, IDC_STATIC7, m_ctrBmp1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMotorState, CDialog)
	//{{AFX_MSG_MAP(CMotorState)
	ON_BN_CLICKED(IDCHECK, OnCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMotorState message handlers

void CMotorState::OnCheck() 
{
	int ret1=10;
	int ret2=10;
	int ret3=10;
	int ret4=10;
	int ret5=10;
	int ret6=10;
	CMainFrame dlg;
	ret1=1;//check_limit(dlg.m_dg_n);
	ret2=-1;//check_limit(dlg.m_lzhu_n);
	ret3=-1;//check_limit(dlg.m_pingtaix_n);
	ret4=-1;//check_limit(dlg.m_pingtaiy_n);
	ret5=-1;//check_limit(dlg.m_zhituifir_n);
	ret6=-1;//check_limit(dlg.m_zhituisec_n);
	//if ((ret1!=-3)&(ret2!=-3)&(ret3!=-3)&(ret4!=-3)&(ret5!=-3)&(ret6!=-3))
	//{
	if (ret1==1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp1.SetBitmap(HBITMAP(m_cBmp));
	}
	else if (ret1==-1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp7.SetBitmap(HBITMAP(m_cBmp));
	}		
	if (ret2==1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp2.SetBitmap(HBITMAP(m_cBmp));
	}
	else if (ret2==-1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp8.SetBitmap(HBITMAP(m_cBmp));
	}
	if (ret3==1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp3.SetBitmap(HBITMAP(m_cBmp));
	}
	else if (ret3==-1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp9.SetBitmap(HBITMAP(m_cBmp));
	}
	if (ret4==1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp4.SetBitmap(HBITMAP(m_cBmp));
	}
	else if (ret4==-1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp10.SetBitmap(HBITMAP(m_cBmp));
	}
	if (ret5==1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp5.SetBitmap(HBITMAP(m_cBmp));
	}
	else if (ret5==-1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp11.SetBitmap(HBITMAP(m_cBmp));
	}
	if (ret6==1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp6.SetBitmap(HBITMAP(m_cBmp));
	}
	else if (ret6==-1)
	{
		m_cBmp.DeleteObject();
		m_cBmp.LoadBitmap(IDB_BITMAP21);
		m_ctrBmp12.SetBitmap(HBITMAP(m_cBmp));
	}
	//} 	// TODO: Add your control notification handler code here
	
}

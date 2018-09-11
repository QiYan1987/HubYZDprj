// DoPlaneness.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DoPlaneness.h"
#include "MainFrm.h"
#include "ColorMap.h"
#include "3dPoint.h"
#include "const.h"
#include "math.h"
#include "PropertyDlg.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoPlaneness

IMPLEMENT_DYNCREATE(CDoPlaneness, CFormView)

CDoPlaneness::CDoPlaneness()
	: CFormView(CDoPlaneness::IDD)
{
	//{{AFX_DATA_INIT(CDoPlaneness)
	m_strlvbo="2-500";
	m_strMethod="最小二乘法";
	FilterMode=3;
	m_intNumOfPlaneness=1;
	//}}AFX_DATA_INIT
	CirEvalue=0;//评定算法
}

CDoPlaneness::~CDoPlaneness()
{
}

void CDoPlaneness::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoPlaneness)
	DDX_Control(pDX, IDC_Planeness, m_editPlaness);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoPlaneness, CFormView)
	//{{AFX_MSG_MAP(CDoPlaneness)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_BTNCHULI, OnChuli)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_Print, OnPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoPlaneness diagnostics

#ifdef _DEBUG
void CDoPlaneness::AssertValid() const
{
	CFormView::AssertValid();
}

void CDoPlaneness::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoPlaneness message handlers

void CDoPlaneness::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->DestroyVIEW(((CMainFrame*)AfxGetMainWnd())->m_DoPlaneness);
	((CMainFrame*)AfxGetMainWnd())->m_DoPlaneness=NULL;
	((CMainFrame*)AfxGetMainWnd())->Desktop();
}

void CDoPlaneness::OnPaint() 
{
	CPaintDC dc(this); 
 	CRect rectback;
    GetClientRect(rectback);
    dc.FillSolidRect(rectback,RGB(255,255,255));  //设置为白色背景

    CWnd *pWnd; 
    CRect rect; 
    CDC *pDC;
    CDC mDC;                      
	pWnd = GetDlgItem(IDC_Planeness);      
	pWnd->GetClientRect(&rect); 
	pDC = pWnd->GetDC();

	CBitmap* pOldBmp= NULL;     
	CBitmap memBitmap;                                  
	mDC.CreateCompatibleDC(pDC);             
	memBitmap.CreateCompatibleBitmap(pDC,rect.right,rect.bottom);
	pOldBmp = mDC.SelectObject(&memBitmap);
    mDC.FillSolidRect(rect.left,rect.top,rect.right,rect.bottom,RGB(255,255,255));   
	//////////////////////////////////////////////////////////////////////

	double fw1=2*rect.Width()/3;
	double f1=rect.Width();
	double f2=rect.Height();                                            	                             
    double fw2=1*rect.Width()/3;	
    //////////////////////表格///////////////////////////////
	mDC.SetBkMode(TRANSPARENT); 
    double l1=rect.left,l2=rect.top,l3=rect.right,l4=rect.bottom;
	int gridxnums=1;
	int gridynums=22;
    double fwgx=fw2,fwgy=f2;
	double dx=fw2/gridxnums;
	double dy=f2/gridynums;
	CRect gridRect(l1+fw1,l2,l3,l4);
	mDC.FillSolidRect(l1+fw1,l2,fw2,l4,RGB(255,255,255));
    
	CPen gridPen(PS_SOLID,1,RGB(0,0,20));
    CPen *oldpen2=mDC.SelectObject(&gridPen);
	mDC.FillSolidRect(l1+fw1,l2,fw2,dy,RGB(232,232,232));//给头行填充颜色
 	mDC.FillSolidRect(l1+fw1,l2+dy*5,fw2,dy,RGB(232,232,232));//给指定行填充颜色
 	mDC.FillSolidRect(l1+fw1,l2+dy*9,fw2,dy,RGB(232,232,232));//给指定行填充颜色

	for(int m=0;m<=gridxnums;m++) //画出gridxnums条竖线                      
	{
		mDC.MoveTo(l1+fw1+m*dx,gridRect.bottom);
		mDC.LineTo(l1+fw1+m*dx,0);
	}

	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
	{
		mDC.MoveTo(l1+fw1,n*dy);
		mDC.LineTo(l1+fw1+fw2,n*dy);
	}
	int i;
	//读取数据
	std::ifstream fin(((CMainFrame*)AfxGetMainWnd())->m_fullPath5, std::ios::binary);
	int maxValue=0;
	int minValue=4096;
	fin.read((char*)&m_data[0], sizeof(shuju0));
	for (i=0;i<3600;i++)
	{	
		fin.read((char*)&m_data[i], sizeof(shuju0));
		if (m_data[i].data>maxValue)
		{
			maxValue=m_data[i].data;
		}
		if (m_data[i].data<minValue)
		{
			minValue=m_data[i].data;
		}
	}
	fin.read((char*)&G1,sizeof(double));
	fin.read((char*)&G2,sizeof(double));
	fin.read((char*)&m_t,sizeof(CTime));
	fin.close();

	//////////////////////////////////////////////////////////////////////////
	//绘制报表
   	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
	CFont*   pOldFont=(CFont*)mDC.SelectObject(&font); 
   
    mDC.SetBkMode(TRANSPARENT); 
	int meter=dy/10;
	int m1=l1+fw1+fw2/30;
	double m2=l1+fw1+dx*0.45;
	double m3=l1+fw1+dx*0.66;
	double mid=l1+fw1+dx*0.4;

    mDC.TextOut(mid ,l2+meter,"平面度测量结果");

	mDC.TextOut(mid,l2+dy*5+meter,"规格要求");
	mDC.TextOut(mid,l2+dy*9+meter,"测量参数");

    mDC.TextOut(m1,l2+dy+meter,"文件名");
	mDC.TextOut(m1,l2+dy*2+meter,"测量时间");
	mDC.TextOut(m1,l2+dy*6+meter,"参考类型");                                       
	mDC.TextOut(m1,l2+dy*7+meter,"滤波器种类");                                              
	mDC.TextOut(m1,l2+dy*8+meter,"滤波范围");    
                                                 
                     	
	mDC.TextOut(m1,l2+dy*10+meter,"工艺要求");
	mDC.TextOut(m1,l2+dy*11+meter,"平面度");
 
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath5;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	mDC.TextOut(m2,dy*1+meter,str);
	//显示测量时间
	CString strText=m_t.Format("%Y-%m-%d %H:%M");
	mDC.TextOut(m2,dy*2+meter,strText);

	mDC.TextOut(m2,dy*6+meter,m_strMethod);
	mDC.TextOut(m2,dy*7+meter,"Gaussian");
	mDC.TextOut(m2,dy*8+meter,m_strlvbo);
	strText.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[4]);
	mDC.TextOut(m2,dy*10+meter,strText);
	mDC.TextOut(m3,dy*10+meter,"um");
	mDC.TextOut(m3,dy*11+meter,"um");
 	//绘制图形
	C3dPoint pt3[4]; 
	CPoint pts[4];
	CPoint centerPoint(rect.Width()*0.667/2,rect.Height()*3/5);
	BYTE r3; 
	BYTE g3; 
	BYTE b3;
	int endNum=0;
 	//定义高度和画图的间隔
	int intHeight=rect.Height()*0.2;
	int dwidth=4;
	int intMinRadius=rect.Width()*0.6/5;
	int intMaxRadius=rect.Width()*0.6/2;

	//定义视点
	int VPOINT_x=0;
	int VPOINT_y=1000;
	int VPOINT_z=1300;
 	
 	int cool;
	int colorLength=maxValue-minValue+1;
	CColorMap campObject(150);
	int campx[4096][3];
	campObject.Jet();
	for ( i=0;i<4096;i++)
	{
		campx[i][0]=campObject.camp[i][0];
		campx[i][1]=campObject.camp[i][1];
		campx[i][2]=campObject.camp[i][2];
	}
 	int R=0;
 	R=rect.Width()*0.6/2.2;
 	endNum=0;
	for (int j=0;j<3600;j=j+dwidth)
	{
				
		pt3[0].x=R*cos((j)*2*PI/3600);
		pt3[0].y=R*sin((j)*2*PI/3600);
		pt3[0].z=-((m_data[j].data-minValue)*intHeight/(maxValue-minValue+1));

		pts[0]=pt3[0].Change(VPOINT_x,VPOINT_y,VPOINT_z);
		pts[0]=pts[0]+centerPoint;
			
		endNum=j+dwidth;
		if (endNum>=3600)
		{

			endNum=0;
			pt3[1].x=R*cos((endNum)*2*PI/3600);
			pt3[1].y=R*sin((endNum)*2*PI/3600);
			pt3[1].z=-((m_data[0].data-minValue)*intHeight/(maxValue-minValue+1));
			
			pts[1]=pt3[1].Change(VPOINT_x,VPOINT_y,VPOINT_z);
			pts[1]=pts[1]+centerPoint;

			pt3[2].x=R*cos((endNum)*2*PI/3600);
			pt3[2].y=R*sin((endNum)*2*PI/3600);	
			pt3[2].z=0;
			pts[2]=pt3[2].Change(VPOINT_x,VPOINT_y,VPOINT_z);
			pts[2]=pts[2]+centerPoint;
		}
		else
		{
			pt3[1].x=R*cos((j+dwidth)*2*PI/3600);
			pt3[1].y=R*sin((j+dwidth)*2*PI/3600);
			pt3[1].z=-((m_data[j+dwidth].data-minValue)*intHeight/(maxValue-minValue+1));
				
			pts[1]=pt3[1].Change(VPOINT_x,VPOINT_y,VPOINT_z);
			pts[1]=pts[1]+centerPoint;

			pt3[2].x=R*cos((j+dwidth)*2*PI/3600);
			pt3[2].y=R*sin((j+dwidth)*2*PI/3600);
			pt3[2].z=0;

			pts[2]=pt3[2].Change(VPOINT_x,VPOINT_y,VPOINT_z);
			pts[2]=pts[2]+centerPoint;
		}  
		pt3[3].x=R*cos((j)*2*PI/3600);
		pt3[3].y=R*sin((j)*2*PI/3600);
		pt3[3].z=0;

		pts[3]=pt3[3].Change(VPOINT_x,VPOINT_y,VPOINT_z);
		pts[3]=pts[3]+centerPoint;
		if (!m_data[j].selected)
		{
			cool=(int)((m_data[j].data-minValue)*150/colorLength);
			r3 =campx[cool][0];  
			g3=campx[cool][1];
			b3 = campx[cool][2]; 
		}
		else
		{
			r3=0;
			g3=0;
			b3=0;
		}
		CBrush brushRed(RGB(r3, g3, b3));
		CPen penBlue(PS_SOLID, 1, RGB(r3, g3, b3));
		CPen* pOldPen = mDC.SelectObject(&penBlue);
		CBrush* pOldBrush = mDC.SelectObject(&brushRed);
		mDC.Polygon(pts, 4);
		mDC.SelectObject(pOldBrush);
		mDC.SelectObject(pOldPen);
		CPen penBlue2(PS_SOLID, 1, RGB(0, 50, 220));
		pOldPen = mDC.SelectObject(&penBlue2);
		mDC.MoveTo(pts[0]);
		mDC.LineTo(pts[1]);		    
		mDC.SelectObject(pOldPen);
		brushRed.DeleteObject();
		penBlue.DeleteObject();
		pOldPen->DeleteObject();
		pOldBrush->DeleteObject();
			
	}
	//建立垂直坐标系
	for (i=0;i<=10;i++)
	{
		if (i%5==0)
		{
			pt2Start.x=-10;
			pt2Start.y=-i*intHeight/10;
			pt2End.x=10;
			pt2End.y=-i*intHeight/10;
			pt2Start+=centerPoint;
			pt2End+=centerPoint;
			mDC.MoveTo(pt2Start);
			mDC.LineTo(pt2End);
		}
		else
		{
			pt2Start.x=-5;
			pt2Start.y=-i*intHeight/10;
			pt2End.x=5;
			pt2End.y=-i*intHeight/10;
			pt2Start+=centerPoint;
			pt2End+=centerPoint;
			mDC.MoveTo(pt2Start);
			mDC.LineTo(pt2End);
		}

	}
	str.Format("%.2f",((maxValue-2048)*10.0/(G1*G2*4096)-(minValue-2048)*10.0/(G1*G2*4096))/10.0);
	str+="um/每格";
//	mDC.TextOut(centerPoint.x,centerPoint.y-rect.Height()*0.55,str);
	mDC.TextOut(centerPoint.x+rect.Height()/3,rect.bottom-rect.Height()/30,str);
	mDC.TextOut(centerPoint.x-R,centerPoint.y-rect.Height()*0.55,"截面分析");

	//绘制标识图
	int dwidth1=rect.Width()*0.6*0.3/20;
	int dheight=rect.Height()/30;
	CPoint startPoint(rect.left+rect.Width()*0.6*0.15,rect.bottom-rect.Height()/30);
	for (i=0;i<20;i++)
	{
		pts[0].x=startPoint.x+dwidth*i;
		pts[0].y=startPoint.y;
		pts[1].x=startPoint.x+dwidth*(i+1);
		pts[1].y=startPoint.y;
		pts[2].x=startPoint.x+dwidth*(i+1);
		pts[2].y=startPoint.y+dheight;
		pts[3].x=startPoint.x+dwidth*i;
		pts[3].y=startPoint.y+dheight;
			
		cool=(int)(i*150/20);
		r3 =campx[cool][0];  
		g3=campx[cool][1];
 		b3 = campx[cool][2]; 
		CBrush brushRed(RGB(r3, g3, b3));
		CPen penBlue(PS_SOLID, 1, RGB(r3, g3, b3));
		CPen* pOldPen = mDC.SelectObject(&penBlue);
		CBrush* pOldBrush = mDC.SelectObject(&brushRed);
		mDC.Polygon(pts, 4);
		mDC.SelectObject(pOldBrush);
		mDC.SelectObject(pOldPen);
		brushRed.DeleteObject();
		penBlue.DeleteObject();
		pOldPen->DeleteObject();
		pOldBrush->DeleteObject();
	}
	str.Format("%.2fum",(minValue-2048)*10/(G1*G2*4096));
	mDC.TextOut(rect.left+rect.Width()*0.6*0.01,rect.bottom-rect.Height()/30,str);
	str.Format("%.2fum",(maxValue-2048)*10/(G1*G2*4096));
	mDC.TextOut(rect.left+rect.Width()*0.6*0.32,rect.bottom-rect.Height()/30,str);

	SubQKDataChuli(((CMainFrame*)AfxGetMainWnd())->m_fullPath5,3600, Resdata,!((CMainFrame*)AfxGetMainWnd())->m_bAutoQK,0, 3600);
	SubAnaData (3, Resdata,GResult,G1,G2);	//圆度
	m_strpmd.Format("%.3f",GResult[1]); //将数据结果转换成字符串的形式，便于显示在表格中

	mDC.SetTextColor(RGB(0,0,0));//红色字体      
    mDC.TextOut(m2,dy*11+meter,m_strpmd);//界面显示平面度

 	pDC->BitBlt(rect.left,rect.top,rect.right,rect.bottom,&mDC,0,0,SRCCOPY); //把已经绘好的图显示在制定位置上
    mDC.SelectObject(pOldBmp);
    mDC.DeleteDC();
    memBitmap.DeleteObject();//释放内存设备
	// Do not call CFormView::OnPaint() for painting messages
}

void CDoPlaneness::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	TCHAR   szPath[1024];
    ::GetModuleFileName(NULL,szPath,1024);
	CString   strPath   =   szPath; 
	int index=strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index+1);
//	index =strPath.ReverseFind(_T('\\'));
//	strPath = strPath.Left(index+1);
	strPath+="Test_ini.ini";
	char inBuf[10];
	GetPrivateProfileString ("滤波","参数1",NULL,inBuf,10,strPath);
	FilterMode=atoi(inBuf);
	GetPrivateProfileString ("评定算法","参数2",NULL,inBuf,10,strPath);
	CirEvalue=atoi(inBuf);
	switch(FilterMode)
	{
	case 0: m_strlvbo="无"; break;
	case 1: m_strlvbo="一次波"; break;
	case 2: m_strlvbo="跳动"; break;
	case 3: m_strlvbo="1-500"; break;
	case 4: m_strlvbo="1-15"; break;
	case 5: m_strlvbo="1-50"; break;
	case 6: m_strlvbo="1-150"; break;
	case 7: m_strlvbo="15-500"; break;
	case 8: m_strlvbo="3-16"; break;
	case 9: m_strlvbo="17-100"; break;
	default: break;
	}
	switch(CirEvalue)
	{
	case 0: m_strMethod="最小二乘法";break;
	case 1: m_strMethod="最小区域法";break;
	case 2: m_strMethod="最小外接圆";break;
	case 3: m_strMethod="最大内切圆";break;
	default: break;
	}
	HICON  hIcon=AfxGetApp()->LoadIcon(IDI_chuli);
	CRect rect;
	int x,y;
	GetClientRect(rect);
	x=rect.left+rect.Width()/40;
	y=rect.top+rect.Height()/40;
	if (rect.Width()<5*rect.Height()/3)
	{
		y=rect.top+(rect.Height()-rect.Width()*3/5)/2;
		rect.bottom=rect.top+rect.Width()*3/5;	
	}
	else
	{
		x=rect.left+(rect.Width()-rect.Height()*5/3)/2;
		rect.right=rect.left+rect.Height()*5/3;
	}
	m_editPlaness.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);

}

void CDoPlaneness::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_editPlaness.GetSafeHwnd())
	{
		CRect rect;
		int x,y;
		GetClientRect(rect);
		x=rect.left+rect.Width()/40;
		y=rect.top+rect.Height()/40;
		if (rect.Width()<5*rect.Height()/3)
		{
			y=rect.top+(rect.Height()-rect.Width()*3/5)/2;
			rect.bottom=rect.top+rect.Width()*3/5;	
		}
		else
		{
			x=rect.left+(rect.Width()-rect.Height()*5/3)/2;
			rect.right=rect.left+rect.Height()*5/3;
		}
		m_editPlaness.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}

}

void CDoPlaneness::OnChuli() 
{
	// TODO: Add your control notification handler code here
	//读取配置文件
	m_Flagcircle=1;
	CPropertyDlg prop;
    if(IDOK==prop.DoModal())
	{
		FilterMode=prop.m_IntFilter; //得到滤波选择的选择项标号
		CirEvalue=prop.m_IntAlg;  //得到圆度评定方法选择方法的标号
		switch(FilterMode)
		{
	//	case 0: m_strlvbo="不滤波"; break;
		case 1: m_strlvbo="一次波"; break;
		case 2: m_strlvbo="跳动"; break;
		case 3: m_strlvbo="1-500"; break;
		case 4: m_strlvbo="1-15"; break;
		case 5: m_strlvbo="1-50"; break;
		case 6: m_strlvbo="1-150"; break;
		case 7: m_strlvbo="15-500"; break;
		case 8: m_strlvbo="3-16"; break;
		case 9: m_strlvbo="17-100"; break;
		default: break;
		}
		switch(CirEvalue)
		{
		case 0: m_strMethod="最小二乘法";break;
		case 1: m_strMethod="最小区域法";break;
		case 2: m_strMethod="最小外接圆";break;
		case 3: m_strMethod="最大内切圆";break;
		default: break;
		}
		OnPaint();
	}
}

void CDoPlaneness::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pActivateView==this)
	{
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(-1,FALSE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(1,FALSE);

	}
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CDoPlaneness::SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr)
{
	double TsQ[3600],TsH[3600],a1=0.0,b1=0.0;
    double SumTs=0.0 ,SumTcos=0.0, SumTsin=0.0, SumT2cos=0.0, SumT2sin=0.0 ;
    double dw=0.0  ,no=0.0   ,PVA=0.0, PVB=0.0, PVB0=0.0, A0=0.0 , A1=0.0, A2=0.0, B1=0.0 ,B2=0.0,D=0.0 ,D1=0.0 , D2=0.0,DispR=0.0;
    double U00=0.0 , U10=0.0 , U20=0.0 ,Zc1=0.0, Zc2=0.0 , Temp1=0.0;
    int ScanT=0 , TempK=0, M=0 , k=0, L=0, j=0, NV2=0, NM1=0,FTR=0 , FTI=0, FPI=0,FLE=0, FLE1=0 ,FUR=0 , FUR1=0,i=0; 
    double FUI=0.0 , FUI1=0.0 , FWR=0.0 ,FWI=0.0;
	double  Maxdirec =0.0, Mindirec =0.0;

	for( i = 0;i< 3600 ;i++)
	{
       Temp1 = ((pMem[i] - 2048) * 10) / (m_Tr*m_Yd * 4096);
       TsQ[i] = Temp1;
	}
    dw = 2 * 3.1415926 / 3600.;// '每一次采样对应的角度间隔，弧度
	switch (FilterMode)
	 {	
	case 0 ://'不滤波
		   for( i = 0;i<3600 ;i++)
		   {
			   TsH[i] = TsQ[i];
		   }
			break;
   case 1: //'考虑一次谐波
		 SumTcos = 0; 
		 SumTsin = 0;
		 for( i = 0;i<3600 ;i++)
		 {
		   SumTcos = SumTcos + TsQ[i] * cos(dw * i);
		   SumTsin = SumTsin + TsQ[i] * sin(dw * i);
		 }
		 A1 = 2 * SumTcos / 3600;
		 B1 = 2 * SumTsin / 3600;
	   //'----
		 for( i = 0 ;i< 3600 ;i++)
		 {
		   TsH[i] = A1 * cos(dw * i) + B1 * sin(dw * i);
		 }
		 break;
   case 2: //'考虑1-500次谐波
		 WLS_Filter(2, 3600, TsQ, TsH);
		// '6阶巴特沃斯滤波器 pMem(i) to TsH(i)
		 //'----去除直流分量---
		 SumTs = 0.0;
		 for( i = 0 ;i< 3600;i++)
		 {
		   SumTs = SumTs + TsH[i];
		 }
		 A0 = SumTs / 3600;
		 for( i = 0; i<3600 ;i++)
		 {
		   TsH[i] = TsH[i] - A0;
		 }
		 break;
   case 3: //'考虑2-500次谐波
		   WLS_Filter(3, 3600, TsQ, TsH);
		   //'6阶巴特沃斯滤波器 TsQ(i) to TsH(i)
		   //'----去除直流分量和1次谐波 ---
		   SumTs = 0;
		   SumTcos = 0; 
		   SumTsin = 0;
		   for( i = 0;i<3600;i++)
		   {
			   SumTs = SumTs + TsH[i];
			   SumTcos = SumTcos + TsH[i] * cos(dw * i);
			   SumTsin = SumTsin + TsH[i] * sin(dw * i);
		   }
		   A0 = SumTs / 3600;
		   A1 = 2 * SumTcos /3600;
		   B1 = 2 * SumTsin / 3600;
		   
		   for( i = 0 ; i<3600;i++)
		   {
			   TsH[i] = TsH[i] - A0 - A1 * cos(dw * i) - B1 * sin(dw * i);
		   } 		
		   break;
   case 4: //'考虑2-15次谐波
		   WLS_Filter(4, 3600, TsQ, TsH);
		   //'6阶巴特沃斯滤波器 TsQ(i) to TsH(i)
		   //'----去除直流分量和1次谐波 ---
		   SumTs = 0;
		   SumTcos = 0;
		   SumTsin = 0;
		   for( i = 0; i<3600;i++)
		   {
			   SumTs = SumTs + TsH[i];
			   SumTcos = SumTcos + TsH[i] * cos(dw * i);
			   SumTsin = SumTsin + TsH[i] * sin(dw * i);
		   }
		   A0 = SumTs / 3600;
		   A1 = 2 * SumTcos /3600;
		   B1 = 2 * SumTsin / 3600;
		   //'----
		   for( i = 0;i< 3600;i++)
		   {
			   TsH[i] = TsH[i] - A0 - A1 * cos(dw * i) - B1 * sin(dw * i);
		   }
		   break;
   case 5: //'滤除2-50次谐波
		   WLS_Filter(5, 3600, TsQ, TsH);
		   SumTs = 0;
		   SumTcos = 0;
		   SumTsin = 0; 
		   //'6阶巴特沃斯滤波器 TsQ(i) to TsH(i)
		   //   '----去除直流分量和1次谐波 ---
		  	for (i=0;i<3600;i++)
			{
				SumTs = SumTs + TsH[i];
				SumTcos = SumTcos + TsH[i] * cos(dw * i);
		        SumTsin = SumTsin + TsH[i] * sin(dw * i);
			}   
		   A0 = SumTs /3600;
		   a1 = 2 * SumTcos /3600;
		   b1 = 2 * SumTsin /3600;	 
		   for (i=0;i<3600;i++)
		   {
			   TsH[i] = TsH[i] - A0 - a1 * cos(dw * i) - b1 * sin(dw * i);
		   }
		  
			break;
   case 6: //'滤除2-150次谐波
		   WLS_Filter(6, 3600, TsQ, TsH);
		   //'6阶巴特沃斯滤波器 TsQ(i) to TsH(i)
		   //'----去除直流分量和1次谐波 ---
		   SumTs = 0; 
		   SumTcos = 0;
		   SumTsin = 0;
		   for( i = 0 ;i<3600 ;i++)
		   {
			   SumTs = SumTs + TsH[i];
			   SumTcos = SumTcos + TsH[i] * cos(dw * i);
			   SumTsin = SumTsin + TsH[i] * sin(dw * i);
		   }
		   A0 = SumTs /3600;
		   A1 = 2 * SumTcos /3600;
		   B1 = 2 * SumTsin /3600;
		   
		   for( i = 0;i<3600;i++)
		   {
			   TsH[i] = TsH[i] - A0 - A1 * cos(dw * i) - B1 * sin(dw * i);
		   }
		  break;
   case 7:// '滤除15-500次谐波
		   WLS_Filter(7, 3600, TsQ, TsH);
		 //'6阶巴特沃斯滤波器 TsQ(i) to TsH(i)
		   break;
   case 8:// '滤除3-16次谐波
		   WLS_Filter(8,3600, TsQ, TsH);
		   //'6阶巴特沃斯滤波器 TsQ(i) to TsH(i)
		   //'----去除直流分量和1次谐波,2次谐波 ---
		   SumTs = 0; 
		   SumTcos = 0; 
		   SumTsin = 0;
		   SumT2cos = 0; 
		   SumT2sin = 0;
		   for (i = 0 ;i<3600;i++)
		   {
			   SumTs = SumTs + TsH[i];
			   SumTcos = SumTcos + TsH[i] * cos(dw * i);
			   SumTsin = SumTsin + TsH[i] * sin(dw * i);
			   SumT2cos = SumT2cos + TsH[i] * cos(2 * dw * i);
			   SumT2sin = SumT2sin + TsH[i] * sin(2 * dw * i);
		   }
		   A0 = SumTs / 3600;
		   A1 = 2 * SumTcos /3600;
		   B1 = 2 * SumTsin /3600;
		   A2 = 2 * SumT2cos /3600;
		   B2 = 2 * SumT2sin /3600;
		   
		   for( i = 0 ;i<3600;i++)
		   {
			   TsH[i] = TsH[i] - A0 - A1 * cos(dw * i) - B1 * sin(dw * i)- A2 * cos(2 * dw * i) - B2 * sin(2 * dw * i);
		   }
			break;
   case 9:// '滤除17-100次谐波
			WLS_Filter(9, 3600, TsQ, TsH);
			//'6阶巴特沃斯滤波器 TsQ(i) to TsH(i)
			break;
	}
	  SumTs = 0;
	  SumTcos = 0;
	  SumTsin = 0;
	  for( i = 0;i< 3600 ;i++)
	  {
		SumTs = SumTs + TsH[i];
		SumTcos = SumTcos + TsH[i] * cos(dw * i);
		SumTsin = SumTsin + TsH[i] * sin(dw * i);
	  }
	  A0 = SumTs / 3600;
	  A1 = 2 * SumTcos / 3600;
	  B1 = 2 * SumTsin / 3600;
	  //'---------------
	  double Direc[3600];
	  for( i = 0;i<3600 ;i++)
	  {
		  if ((FilterMode == 1) | (FilterMode == 2) )
		  {
		  // '考虑一次谐波 ,考虑1-500次谐波
			  Direc[i] = TsH[i] - A0;
		  }
		  else
		  {
				Direc[i] = TsH[i] - A0 - A1 * cos(dw * i) - B1 * sin(dw * i);
		  }
	  }
	  Maxdirec = 0.0; 
	  Mindirec = 0.0;
	 for( i = 0 ;i< 3600;i++)
	 {
		  if( Direc[i] > Maxdirec)
		  { 
			  Maxdirec = Direc[i];
		  }
		  if (Direc[i] < Mindirec) 
		  { 
			  Mindirec = Direc[i];
		  }
	 }
  	GResult[1] = fabs(Maxdirec) + fabs(Mindirec);
	if( FilterMode = 1)
	{ 
		GResult[2] = sqrt(A1 * A1 + B1 * B1);
	}//偏心  
    GResult[3] = (atan(fabs(B1 / A1)) * 180) / (3.1415926);
     // 'Atn (Number) 返回一个 Double，指定一个数的反正切值。
     // 'A1为最小二乘圆X坐标,B1为最小二乘圆Y坐标
    if( (A1 < 0) &(B1 >= 0))
	{  //'第二象限	
		GResult[3] = 180 - GResult[3];
	}
	else if( (A1 < 0) & (B1 < 0)) 
	{//'第三象限
		GResult[3] = -(180 - GResult[3]);
	}
	 else if((A1 >= 0) & (B1 < 0))
	 {//'第四象限
		GResult[3] = -GResult[3];
	 }
}


/*
  函数功能：自动和手动缺口处理
  自动处理缺口；
  手动处理缺口。
  -----------------参数说明-------------------------
  整流子缺口数据处理
  Number     数据个数
  Soudata()  处理前数组
  Resdata()  处理后数组
  MaxIndex() 缺口右终点的位置
  MinIndex() 缺口左起始点的位置

  ConstMaxQkNumber=100------轮廓最大缺口个数
  QkZdnumber----------------缺口重叠次数
  TempFLAGIndex-------------缺口点的趋势
  QkNumber------------------缺口个数
  WZIndexP()----------------上缺口左右起始点的位置
  WZIndexU()----------------下缺口左右起始点的位置
  TempWZIndexPP()-----------该下半轮廓的标示序号
  TempWZPL()----------------该下半轮廓与当前上半轮廓的左距离
  TempWZPR()----------------该下半轮廓与当前上半轮廓的右距离
  FLAGIndexU()--------------上缺口点的趋势
  FLAGIndexP()--------------下缺口点的趋势
  YDQKdata()----------------带缺口的圆度数据
  KMaxValue-----------------缺口左起始点位置判定值
  KMinValue-----------------缺口右起始点位置判定值
  QKWzFlag------------------判断缺口性质
*/
void CDoPlaneness::SubQKDataChuli(CString path,int Number, double *Resdata,BOOL GManCuliQkFlag,int JM,int Totaldot)
{ 
	//定义变量
	int     i,j,X,LX, LLX,TempStart,TempEnd;
	int     Y, NY, NNY,iE,jE,QkNumber,GQkNumber ;
    int      MinLI, MinRI;
	int     TempN ,TempNA,TempNB;
    int     MaxIndex[100],MinIndex[100],GQkorgWStart[100], GQkorgWEnd[100];
	int     QkZdnumber,TempQKNumberU,TempQKNumberP,TempQknumber;
	int     TempWZIndex[3600],WZIndexU[3600],WZIndexP[3600],TempWZIndexPP[3600];
	int     TempWZPL[3600],TempWZPR[3600];
	int     TempWz1,TempWz2,TempWz3,TempWz4,GBzDot;//缺口点的位置1,2,3,4
    BOOL    TempFLAGIndex[3600],FLAGIndexU[3600],FLAGIndexP[3600],EndFlag,QKWzFlag,GLxLkFlag;
	double  TempValueA,TempValueB,TempK,TempValueC;
    double  TempBHVdataX, TempBHVdataY,GQkAngle;
	double  YDQKdata[3600],KMaxValue,KMinValue,BHVdata[3600];
	double TransData[3600],ConstMaxQkNumber=100,GQkWStart[100],GQkWEnd[100];
	double  GPVBBH,GPHWidthK=0.2;
	double  TempAngle;
    double ConstMinQkPHValue=0.4,ConstMinQkBZ=8;
    double  ConstKXS1=1.5,ConstKXS2=0.5;
	double Max, Min,Soudata[3600];
	int     QKnumberL[100],QKnumberR[100],QKnumberr[100];//左右缺口的下标

	//给数组赋初值
	for (i=0;i<Number;i++)
	{	
		TempWZIndex[i]=0;
		WZIndexU[i]=0;
		WZIndexP[i]=0;
		TempWZIndexPP[i]=0;
        TempWZPL[i]=0;
		TempWZPR[i]=0;
        TempFLAGIndex[i]=0;
		FLAGIndexU[i]=0;
		FLAGIndexP[i]=0;
	}
	///////////////手工剔除//////////////////////////////
    // if( Number==0) 
    //	Exit Sub;

    //	将文件名传过来，进行缺口个数的统计

	shuju0 ManDeal[3600];//定时结构体数据
	std::ifstream fin(path,std::ios::binary);
	fin.read((char*)&m_data[0], sizeof(shuju0));
	for ( i=1;i<3601;i++)
	{	
		fin.read((char*)&m_data[i], sizeof(shuju0)); //读取数据
	}
	fin.read((char*)&G1,sizeof(double));
	fin.read((char*)&G2,sizeof(double));
	fin.read((char*)&m_t,sizeof(CTime));
	fin.close();  
	for (i=0;i<Number;i++)
	{
    	ManDeal[i].data=m_data[i+1].data;
        ManDeal[i].selected=m_data[i+1].selected;
		Soudata[i]=ManDeal[i].data;
	}
	
	//分别统计缺口的个数和缺口左边和缺口右边的数据下标
    int jLeft=0,jRight=0;
	for (i=0;i<Number-1;i++)
	{
		if (ManDeal[i].selected==0 && ManDeal[i+1].selected==1 )//手动去除区域的起始点
		{
			QKnumberL[jLeft]=i; //各个缺口的起始点下标
			jLeft=jLeft+1;
		}
		if (ManDeal[i].selected==1 && ManDeal[i+1].selected==0 )//手动去除区域的终止点
		{
			QKnumberr[jRight]=i;//各个缺口的终止点的下标
            jRight=jRight+1;
		}
	}
    if (ManDeal[3599].selected==1 && ManDeal[0].selected==1 && jLeft>1)
	{
        for (i=0;i<jLeft-1;i++)
        {
             QKnumberR[i]=QKnumberr[i+1];
        }
       QKnumberR[jLeft-1]=QKnumberr[0];
	}
	else 
	{
		for (i=0;i<jLeft;i++)
		{
	    	QKnumberR[i]=QKnumberr[i];
        }
	}
	 
	if (jLeft==0 && jRight==0  )
	  {
		goto Automode;
	  }
	  
    else /*(GManCuliQkFlag==true ) */
	 {
    	goto  ManMode; //手工剔除
	 }

Automode:
	GLxLkFlag = true;//'连续轮廓标志	
	QkNumber = 0;
    Number=3600;	  ////////////自设
	TempAngle = 360.0/Number;
    TempN = 0; 
	//zpg2012-06-07
   for (i=0;i<Number;i++)
   {
	   TransData[i] = Soudata[i];//采样数据
   }
  //---计算数据变化率-------
   for (i=0;i<Number;i++)
   {
	   YDQKdata[i]=((Soudata[i]-2048)*10)/(G1*G2*4096); //将数据转换成位移
	   if(i== Number - 1) //如果数据为最后一个数
		   BHVdata[i]=((Soudata[0]-2048)*10)/(G1*G2*4096)-((Soudata[i]-2048)*10)/(G1*G2*4096);//用第一个数减去最后一个数
	   else
		   BHVdata[i]=((Soudata[i+1]-2048)*10)/(G1*G2*4096)-((Soudata[i]-2048)*10)/(G1*G2*4096);//否则的话用下一个数减去上一个数	
   }
   //---计算平均数据变化率和最大值最小值---
   TempValueA=0,TempValueB=0, TempValueC=0,TempNA=0,TempNB=0;
   for (i=0;i<Number;i++)
   {
	    TempValueC = TempValueC + YDQKdata[i];
	   if (BHVdata[i] >=0) //若变化大于0，和记录在TempValueA中，数据个数记录在TempNA中
	   { 
		   TempNA=TempNA+1;
		   TempValueA=TempValueA+BHVdata[i];
	   }	
	   else if (BHVdata[i]<0) //若变化小于0，和记录在TempValueB中，数据个数记录在TempNB中
	   {
		   TempNB=TempNB+1;
		   TempValueB=TempValueB+BHVdata[i];
	   }
   }
   //-----------------------------------------/////////////////////以上代码与VB实现调试，正确
   Max = BHVdata[0]; //求出变化率中的最大和最小的数
   Min = BHVdata[0];
   for (i=0;i<Number;i++)
   {
	   if (Max<BHVdata[i])
	   {
          Max = BHVdata[i];
          TempWz1 = i;  //最大变化率所对应数的下标
	   }
	   if (Min > BHVdata[i])
       {
		   Min = BHVdata[i];
           TempWz2 = i;//最小变化率所对应数的下标
	   }
  }
   //-------------------------------------
  TempValueC = TempValueC / Number;
  TempValueA = TempValueA / TempNA;
  if (TempNB != 0 ) 
  {
	   TempValueB = TempValueB / TempNB;
  }
   if (TempValueA != 0 )
   {
	  TempValueA = Max / TempValueA;
   }	 
	if (TempNB!=0 )
	{
	  TempValueB = Min / TempValueB;
	}
	//以上代码于2012.6.28.8:25与VB校对正确

  if((fabs(Max) >= ConstMinQkPHValue) && (fabs(Min) >= ConstMinQkPHValue) && (fabs(TempValueA) + (fabs(TempValueB)) >= ConstMinQkBZ) )
  {
	//'缺口必须满足以下两个条件
	//	'1. 正负最大变化率  大于  ConstMinQkPHValue(为0.4)
	//	'2. 正负最大变化率与平均变化值的比值  大于  ConstMinQkBZ(为8)
   }
   else
   { 
	   GLxLkFlag =true;
      // QkNumber = 0;
	  goto QuitA;
   }
    
  //--------------------------------------------
    //'以上为连续轮廓 以下为非连续轮廓的数据处理
   // '判断缺口性质
   // '以正负最大变化率作为参考(比例)来判定缺口左右起始点位置
   // '1A---查找缺口左右起始点的位置(速度曲线的凸起部分)

   if ((fabs(TempValueC) > fabs(YDQKdata[TempWz1])) && (fabs(TempValueC) > fabs(YDQKdata[TempWz2])))
   {
          KMaxValue = ConstKXS1 * YDQKdata[TempWz1];
          KMinValue = ConstKXS1 * YDQKdata[TempWz2];// '缺口左右起始点位置判定值
          if( YDQKdata[TempWz1] > 0) 
		  {
             QKWzFlag = true;
		  }else
		  {
             QKWzFlag = false;
		  }
   }
   else
   {
          KMaxValue = ConstKXS2 * YDQKdata[TempWz1];
          KMinValue = ConstKXS2 * YDQKdata[TempWz2]; //'缺口左右起始点位置判定值
          if( YDQKdata[TempWz1] > 0)
		  { 
            QKWzFlag = false;
          }
		  else
		  {
            QKWzFlag = true;
			
		  }
		  
   }
    
   EndFlag = false;
   TempQKNumberU =0;
  for (i=0;i<Number;i++)
  {
	  if (i==0)
	  {
	    X = Number-1;
   	   LX = Number-2;
	  //  LLX = Number-3;
	  }
	  else if (i==1 )
	  {
	    X =0;
	   LX =Number-1;
	   // LLX =Number-2;
	  }
	  else if (i==2) 
	  {
	 	 X =1;
	    LX =0;
	   //  LLX =Number-1;
	  }
	   else
	   {
	      X =i-1;
	     LX =X-1;
	    //  LLX =LX-1;
	   }
       //==============================================//
	  if (i==Number-1) 
	  {
	     EndFlag=true;
	        Y=1;
	       NY=2;
       //NNY=2;
	  }
    else if (i==Number-2) 
	{
	   Y = Number-1;
	   NY=0;
      //NNY=1;
	 }
	else if (i==Number-3) 
	{
	   Y = Number-2;
	   NY = Number-1;
        // NNY = 0;
	 }
	else
	{
	   Y = i + 1;
	   NY = Y + 1;
       //NNY = Y + 2;
	}
    //  '-----
	if ((YDQKdata[X] <= KMaxValue) && (YDQKdata[Y] > KMaxValue) && (YDQKdata[LX] <= KMaxValue) && (YDQKdata[NY] > KMaxValue)) 
	{
           //  '由负变正
             if (YDQKdata[i] <= KMaxValue) 
			 {
                i = Y;
			 }
             TempQKNumberU = TempQKNumberU + 1;
             WZIndexU[TempQKNumberU] = i;
             if (QKWzFlag == true) 
			 {
               FLAGIndexU[TempQKNumberU] =true;
			 }
			 else
			 {
               FLAGIndexU[TempQKNumberU] =false;
				
			 }
	}
	else if ((YDQKdata[X] >= KMaxValue)&&(YDQKdata[Y] < KMaxValue)&&(YDQKdata[LX] >= KMaxValue)&&(YDQKdata[NY] < KMaxValue))
	{
                 //'由正变负
				 if (YDQKdata[i] >= KMaxValue)
				 {
					 i = Y;
				 }
                TempQKNumberU = TempQKNumberU + 1;
                WZIndexU[TempQKNumberU] = i;
                if(QKWzFlag == true)
				{
                  FLAGIndexU[TempQKNumberU] = false;//原来为false
				 }
				else
				{
                  FLAGIndexU[TempQKNumberU] = true;//原来为ture
				 }			
	}
	if (EndFlag == true)
	{
		goto  CONA1A;
	}   
 }
 /////////////////////////////////////////////////////////////////////// 
  CONA1A: //'分析相邻点
 if ((TempQKNumberU % 2) == 0 )
 {
 }
 else
 {      // '分析过零点特殊情况
	 if(FLAGIndexU[1] == FLAGIndexU[TempQKNumberU])
	 {
             TempQKNumberU = TempQKNumberU - 1;
	 }
 }
    TempQknumber =0;		
	//分析后上缺口个数为  " & TempQKNumberU
	//'1B---查找缺口左右起始点的位置(速度曲线的凹下部分)
	EndFlag =false;
    TempQKNumberP=0;
  for (i=0;i<Number;i++)
  {
     if (i ==0)
	 {
		   X = Number - 1;
		  LX = Number - 2;
	   //LLX = Number - 3;
	 }	
	 else if (i== 1) 
	  {
		  X = 0;
		  LX = Number - 1;
	//	  LLX = Number - 2;
	  }
	 else if (i==2 )
	   {
		   X = 1;
		  LX = 0;
	//	  LLX = Number - 1;
	   }
	 else
	   {
		  X = i - 1;
		  LX = X - 1;
	//	  LLX = LX - 1;
	   }

	//--------------------------------------------------//
     if ( i == Number - 1) 
	  {
		  EndFlag =true;
		  Y = 1;
		  NY = 2;
	//	  NNY = 2;
	  }
    else if (i==Number - 2)
	 {
		  Y = Number - 1;
		  NY = 0;
	//	  NNY = 1;
	 }
	 else if (i==Number - 3)
	 {
		  Y = Number - 2;
		  NY = Number - 1;
	//	  NNY = 0;
	 }
	else
	{
		  Y = i + 1;
		  NY = Y + 1;
    //	  NNY = Y + 2;
	}		     
	if ((YDQKdata[X] <= KMinValue)&&(YDQKdata[Y] > KMinValue)&&(YDQKdata[LX] <= KMinValue)&&(YDQKdata[NY] > KMinValue)) 
	{
            // '由负变正
			if (YDQKdata[i] <= KMinValue)
			{
                i = Y;
			}
             TempQKNumberP = TempQKNumberP + 1;
             WZIndexP[TempQKNumberP] = i;
             if (QKWzFlag == true) {
               FLAGIndexP[TempQKNumberP] = 1;
			 }else{
               FLAGIndexP[TempQKNumberP] = 0;
             }
			}else{
             if ((YDQKdata[X] >= KMinValue)&&(YDQKdata[Y] < KMinValue)&&(YDQKdata[LX] >= KMinValue)&&(YDQKdata[NY] < KMinValue)) {
              //   '由正变负
			  if (YDQKdata[i] >= KMinValue) {
                  i = Y;
			  }
                TempQKNumberP = TempQKNumberP + 1;
                WZIndexP[TempQKNumberP] = i;
                if (QKWzFlag == true) {
                  FLAGIndexP[TempQKNumberP] = false;
				}else{
                  FLAGIndexP[TempQKNumberP] = true;
                }
             }
			 }
    if (EndFlag==true) 
    {
	   goto  CONA2;
	}
}
 //----------------------------------6.29.15:54程序核对  
CONA2:// '分析相邻点
    if( (TempQKNumberP % 2) == 0) 
	{
	}
	else
	{ 
	  if( FLAGIndexP[1] = FLAGIndexP[TempQKNumberP]) //'分析过零点特殊情况
	  {
         TempQKNumberP = TempQKNumberP - 1;
		
	  }
	}
   
   QkNumber = 0;
  // '--------------------------------------------
  for(i=1;i<=TempQKNumberU;i++)
  {
      if (i==TempQKNumberU)
	  {
         iE = 1;
	  }
	  else
	  {
	     iE=i+1;
	  }
      //  '以先出现凸起为先导条件，寻找与凸起轮廓最靠近的凹下轮廓
      if((FLAGIndexU[i]==false) && (FLAGIndexU[iE]==true ) )
		{
           TempWz3 = WZIndexU[i];
           TempWz4 = WZIndexU[iE];
           TempNA = 0;
          for (j=1;j<=TempQKNumberP;j++)
		  {
		  if (j==TempQKNumberP)
              jE=1;
		  else
              jE=j+1;
		  if ( FLAGIndexP[j]==false && FLAGIndexP[jE]==true  )
		  {
                        // '下半轮廓
                     TempNA = TempNA + 1;
                     TempWZIndexPP[TempNA]=j;
                     TempWz1 = WZIndexP[j];
                     TempWz2 = WZIndexP[jE];
                        //  '----A1得到该下半轮廓与当前上半轮廓的左距离
                     TempWZPL[TempNA]=TempWz3 - TempWz1;
                  if (TempWZPL[TempNA]>=0 )
				  {
					if(TempWZPL[TempNA]>Number/2)
					{
                     TempWZPL[TempNA]=(Number-1)-TempWZPL[TempNA];
					}
				  }
				  else
				  {
					if( abs(TempWZPL[TempNA]) > Number / 2) 
					{
                     TempWZPL[TempNA] = TempWZPL[TempNA] - (Number - 1);
					}
				  }
               // '----B1得到该下半轮廓与当前上半轮廓的右距离
                TempWZPR[TempNA] = TempWz2 - TempWz4;
                if (TempWZPR[TempNA] >= 0)
				{
					if(TempWZPR[TempNA]>Number/2)
					{
                     TempWZPR[TempNA] =(Number-1)-TempWZPR[TempNA];
					}
				}
				else
				{
					if (abs(TempWZPR[TempNA])>Number/2)
					{
                     TempWZPR[TempNA] = TempWZPR[TempNA] - (Number - 1);	
					}
				}
			}
		 
	  }
      // '---A2得到与当前上半轮廓的左距离最小的下半轮廓
      Min=TempWZPL[1];
      MinLI=1;
	  for (j=1;j<=TempNA;j++)
		{
		   if (abs(TempWZPL[j])<fabs(Min) )
			   {
                   MinLI = j;
                   Min = TempWZPL[j];
			   }
         }
         //'---B2得到与当前上半轮廓的右距离最小的下半轮廓///////////2012.6.28.22:30校对程序正确
         Max=TempWZPR[1];
         MinRI=1;
         for (j=1;j<=TempNA;j++)
		 {
             if (abs(TempWZPR[j])<fabs(Max))
			 {
               MinRI = j;
               Max = TempWZPR[j];
			}
		 }
          // '--得到结论----------  
		  j=TempWZIndexPP[MinLI]; 
		  if (j==TempQKNumberP)
		  {
             jE = 1;
		  }
		  else
		  {
             jE = j + 1;	 
		  }
           TempWz1 = TempWz3 - Min;
           TempWz2 = Max + TempWz4;
           QkNumber = QkNumber + 1;
          if (QkNumber > ConstMaxQkNumber) 
		  {
              return;
          }
           if (Min >= 0 )
		   {
              MinIndex[QkNumber] = TempWz1;
		   }else
		   {
              MinIndex[QkNumber] = TempWz3;	  
		   }
           if (Max >= 0)
		   {
              MaxIndex[QkNumber] = TempWz2;
           }
		   else
		   {
              MaxIndex[QkNumber] = TempWz4;
           } 
	}
  }//next i

  //========================================
 // ------------------------------------------------------
 	if((QkNumber==TempQKNumberU/2) && (QkNumber==TempQKNumberP/2)) //原来是等号
	{
      
	}
	else
	{
         GLxLkFlag = true;
         goto QuitA;
     }
    //  '---Step-2   根据缺口个数处理数据--
	if( (QkNumber > 0) && (QkNumber <= ConstMaxQkNumber) )
	{
		GLxLkFlag = false;
		GQkAngle = 0;
		for(i=1;i<=QkNumber;i++)
		{
		   if ((MaxIndex[i]-MinIndex[i]) < 0)
		   {
			   GQkAngle = GQkAngle+(Number + MaxIndex[i] - MinIndex[i]) * TempAngle;
		   }
		   else
		   {
			   GQkAngle = GQkAngle + (MaxIndex[i] - MinIndex[i]) * TempAngle;
		   }
		}
		GBzDot =(int)(GPHWidthK*((360-GQkAngle)/QkNumber)*(Number/360)+0.5);//四舍五入保留整数
		// '非连续轮廓补值点范围
		// 'GPHWidthK ---缺口之间平滑区域宽度比例
		if(GBzDot > Number/16)
		 GBzDot = Number/16;
		//'该条语句保证仅去除变化大的区域，缓慢变化区域不处理
		 // '-----------
		 for(i=1;i<=QkNumber;i++)
		  {
		   GQkAngle = (MaxIndex[i] - MinIndex[i]) * TempAngle;
			
	    	//	 'SJChuli.List1.AddItem "缺口角度= " & (MaxIndex(i) - MinIndex(i)) * TempAngle
			//	 '----根据缺口位置补值---
			//	 '-左缺口计算--自动剔除
				 TempValueA = 0;
				 TempN = 0;
				 TempStart = MinIndex[i]-(GBzDot+5);
				 TempEnd = MinIndex[i]-(GBzDot-5);
				 if(TempStart<0) 
					TempStart = TempStart + Number;
				 if(TempEnd<0) 
					TempEnd = TempEnd + Number;
				 if (TempEnd > TempStart) 
				 {
				   for(j=TempStart;j<=TempEnd;j++)
					{
                        TempValueA=TempValueA + Soudata[j];
                        TempN=TempN + 1;
					}
				   TempValueA=TempValueA/ TempN;
				 }
				 else
				 {
				   for (j=TempStart;j<Number;j++)
					 {
                         TempValueA = TempValueA + Soudata[j];
                         TempN = TempN + 1;
					 }
				    for(j=0;j<=TempEnd;j++)
					{
                        TempValueA = TempValueA + Soudata[j];
                        TempN = TempN + 1;
					}
	
				 TempValueA=TempValueA/TempN;
				}
			//	 '-右缺口计算--自动剔除
				 TempValueB = 0;
				 TempN = 0;
				 TempStart = MaxIndex[i]+(GBzDot-5);
				 TempEnd = MaxIndex[i]+(GBzDot+5);
			//	 'GBzDot = 20 '非连续轮廓补值点范围
				if (TempStart>Number-1) 
					TempStart=TempStart-(Number-1);  
		    	if (TempEnd>Number-1)
					TempEnd=TempEnd-(Number-1);
				 
		          if(TempEnd > TempStart)
				  {
                     for(j=TempStart;j<=TempEnd;j++)
					 {
                         TempValueB = TempValueB + Soudata[j];
                         TempN = TempN + 1;
					 } 
			    	 TempValueB = TempValueB / TempN;
				  }
				  else
				  {
				     for (j=TempStart;j<Number;j++)
					 {
                         TempValueB = TempValueB + Soudata[j];
                         TempN = TempN + 1;
					 }
				     for(j=0;j<=TempEnd;j++)
					 {
                        TempValueB = TempValueB + Soudata[j];
                        TempN = TempN + 1;
					 }
				    TempValueB = TempValueB / TempN;
				  }
				  //'SJChuli.List1.AddItem "补值A= " & TempValueA
                  //'SJChuli.List1.AddItem "补值B= " & TempValueB
					TempStart = MinIndex[i] - GBzDot;
					TempEnd = MaxIndex[i] + GBzDot;
					if (TempStart < 0) 
					{
				    	TempStart = TempStart + Number;
					}
					else
					{
					   if (TempStart>Number-1)
						   TempStart = TempStart - (Number - 1);
					}
			
					if (TempEnd < 0) 
					{
				    	TempEnd = TempEnd + Number;
					}
					else
					{
				    	if(TempEnd>Number-1)
						TempEnd = TempEnd-(Number - 1);
					}
	                
					TempN = 0;
				   if (TempEnd>TempStart)
				   {
				       TempN = TempEnd - TempStart + 1;
				   }
				   else
				   {
					   for (j=TempStart;j<Number;j++)
					   {
					      TempN = TempN + 1;
					   }
					   for (j=0;j<=TempEnd;j++)
					   {
                         TempN = TempN + 1;
					   }
					}
					TempK = (TempValueB-TempValueA)/TempN;

			   	    //'--采用线性补值-自动剔除
					if(TempEnd > TempStart) 
					{
						for(j=TempStart;j<=TempEnd;j++)
						{
							Soudata[j] = Soudata[TempStart]+TempK*(j - TempStart);
                            ManDeal[j].selected=1;//添加
						}
					}
					else 
					{
					  for(j=TempStart;j<Number;j++)
					  {	
						Soudata[j]=Soudata[TempStart]+TempK*(j-TempStart);
                        ManDeal[j].selected=1;//添加
					  }
					for (j=0;j<=TempEnd;j++)
					{
	                    Soudata[j]=Soudata[TempStart]+TempK*(j + Number - TempStart);
                        ManDeal[j].selected=1;//添加
					}
				}
			}
					//'-自动剔除--得到第i个片(缺口间)的起始位置,终止位置----
   for( i=1;i<=QkNumber;i++)
	{
		  if( i==QkNumber) 
		  {
           TempStart = MaxIndex[i] + GBzDot;
           TempEnd = MinIndex[1] - GBzDot;
		  }
		  else
		  {
            TempStart = MaxIndex[i] + GBzDot;
            TempEnd = MinIndex[i + 1] - GBzDot;
		  }

		  if( TempStart < 0)
		  {
              TempStart = TempStart + Number;
		  }
		  else if (TempStart > Number - 1) 
				TempStart = TempStart - (Number - 1);
		
		   if( TempEnd < 0) 
		   {
               TempEnd = TempEnd + Number;
		   }
		   else  if (TempEnd > Number - 1)
			   TempEnd = TempEnd - (Number - 1);

        GQkWStart[i] = TempStart; //'对应第几个片（缺口内外）的起始位置
        GQkWEnd[i] = TempEnd; //'对应第几个片（缺口内外）的终止位置 
     }		
    }
	else
	{
			GLxLkFlag =true;
		    QkNumber = 0;
	}
	
	int Starti,Endi;//本小段程序实现在自动去缺口以后反映在图形界面上的变化
    for( i=1;i<=QkNumber;i++)
	{
       Starti=MinIndex[i]-GBzDot;
       Endi=MaxIndex[i]+ GBzDot;
   //    ChangeValueOfSelect(path,Starti,Endi,1);
	}


  		//'---Step-3   得到结果数据--
QuitA:
		 double dataauto[3600];
		 for(i = 0 ;i<Number;i++)
		 {
		    Resdata[i]=Soudata[i];
            dataauto[i]=Resdata[i];
		 }
         GQkNumber = QkNumber;
		 return;
				

 //-----------------------------------------------------//	
 //  --------------------以上为自动剔除缺口----------------
 //  ------------------- 以下实现手动剔除------------------
 /*
   Soudata()----------------------------------------- 处理前数组
   Resdata()----------------------------------------- 处理后数组
   QkNumber------------------------------------------'缺口个数
   TempValueA-----------------------------------------补值A 变化率大于0的平均数
   TempValueB-----------------------------------------补值B 变化率小于0的平均数
   TempN ---------------------------------------------补值个数
   GLxLkFlag = True-----------------------------------连续轮廓标志
   ConstMaxQkNumber=100-------------------------------轮廓最大缺口个数
   BHVdata(Number)------------------------------------计算数据变化率
   YDQKdata( Number)----------------------------------带缺口的圆度数据
   TempStart & " ** " & TempEnd ----------------------补值范围
   (MaxIndex(i) - MinIndex(i)) * TempAngle------------缺口角度
   MaxIndex(ConstMaxQkNumber) ------------------------缺口右终点的位置
   MinIndex(ConstMaxQkNumber)-------------------------缺口左起始点的位置
   TempValueA = TempValueA + Soudata(j)---------------缺口内的数据和
   TempValueA = TempValueA / TempN--------------------补值指去掉的数据求其平均值
*/

ManMode:
	  
		TempAngle=360.0/Number;       //0.1°采一个点
		TempN=0;                  //补值个数
		for(i=0;i<Number;i++)
		{
		   TransData[i] = Soudata[i];//	'采样数据
		   YDQKdata[i] = ((Soudata[i]-2048)*10)/(G1*G2*4096);
		}			
       //非连续轮廓的数据处理
       //Step-2   根据缺口个数处理数据--
       //1D---优化缺口位置 '手动剔除
       QkNumber = GQkNumber=jLeft; //缺口个数
       if(QkNumber>=1)
           GLxLkFlag =false;    //非连续轮廓     
       for(i=1;i<=QkNumber;i++)
	   {
           MinIndex[i] =QKnumberL[i-1];// GQkorgWStart[i];//缺口左起始点的位置,手动去除缺口时的按下点
           MaxIndex[i] =QKnumberR[i-1];//GQkorgWEnd[i];//缺口右终点的位置，手动去除缺口时的抬起点
	   }
       for(i=1;i<=QkNumber;i++)
	   {
           TempStart=MinIndex[i]; //对应一个缺口的左起始点
           TempEnd=MaxIndex[i];   //对应一个缺口的右终止点
           if (TempEnd>=TempStart) 
		   {
		  	   TempNA=TempEnd-TempStart;// '正方向计算
               TempNB=Number+TempStart-TempEnd;// '反方向计算
		   }
           else
		   {
              TempNA=Number+TempEnd-TempStart;// '正方向计算
              TempNB=TempStart-TempEnd;// '反方向计算
		   }
          /* if(TempNA >= TempNB) //此条语句判断每次处理只处理相对角度旋转比较小的那边
		   {
              // '位置标反
              MinIndex[i]=TempEnd;
              MaxIndex[i]=TempStart;
		   }
        */
	   }
       GQkAngle = 0;
       for(i=1;i<=QkNumber;i++)
	   {
          if((MaxIndex[i]- MinIndex[i]) < 0)
              GQkAngle = GQkAngle + (Number + MaxIndex[i] - MinIndex[i]) * TempAngle; //得到缺口包含的角度
          else
              GQkAngle = GQkAngle + (MaxIndex[i] - MinIndex[i]) * TempAngle;
	   }

       //GBzDot=GPHWidthK*((360-GQkAngle)/QkNumber)*(Number/360);//由硬件中读取
       GBzDot=0;
       // '非连续轮廓补值点范围
       // 'GPHWidthK ---缺口之间平滑区域宽度比例
       if(GBzDot>Number/16) 
		  GBzDot = Number/16;
       //'该条语句保证仅去除变化大的区域，缓慢变化区域不处理
       // if(QkNumber == 0 )
	   //  goto  Automode;
      for (i=1;i<=QkNumber;i++)//'手工剔除
	  {
		   TempValueA=0;
           TempN=0;
           TempStart=MinIndex[i]-(GBzDot+5);
           TempEnd=MinIndex[i]-(GBzDot-5);
           GQkAngle=(MaxIndex[i]- MinIndex[i]) * TempAngle;
           // ''手工剔除--左缺口计算
           if(TempStart < 0) 
              TempStart = TempStart + Number;
		   if (TempEnd < 0)
               TempEnd = TempEnd + Number;
           
		   if(TempEnd > TempStart) 
		   {
			   for(j=TempStart;j<=TempEnd;j++)
			   {
				   TempValueA = TempValueA + Soudata[j];
			       TempN = TempN + 1;
			   }
			   TempValueA = TempValueA / TempN;
		   }
		   else
		   {
			   for(j=TempStart;j<Number;j++)
			   {
				   TempValueA = TempValueA + Soudata[j];
			       TempN = TempN + 1;
			   }
			   for(j=0;j<=TempEnd;j++) 
			   {
				   TempValueA = TempValueA + Soudata[j];
			       TempN = TempN + 1;
			   }
			   TempValueA = TempValueA / TempN;
		   }
          //TempK = (TempValueB - TempValueA) / TempN;  //求取平均值
          //'-右缺口计算--'手工剔除
			   TempValueB = 0;
			   TempN = 0;
			   TempStart = MaxIndex[i] + (GBzDot - 5);
			   TempEnd = MaxIndex[i] + (GBzDot + 5);
			   // 'GBzDot = 20 '非连续轮廓补值点范围
			   if(TempStart > Number - 1) 
			   TempStart = TempStart - (Number - 1);
			
			   if(TempEnd > Number - 1)
			   TempEnd = TempEnd - (Number - 1);
		
			   if(TempEnd > TempStart) 
			   { 
				   for(j=TempStart;j<=TempEnd;j++)
				   {
			          TempValueB=TempValueB + Soudata[j];
			           TempN=TempN+1;
				   }
                   TempValueB=TempValueB/TempN;
			   }
			   else
			   {
				  for(j=TempStart;j<Number;j++)
				  {
					  TempValueB=TempValueB+Soudata[j];
                      TempN=TempN+1;
				  }
				  for(j=0;j<=TempEnd;j++)
				  {
					 TempValueB = TempValueB + Soudata[j];
					 TempN = TempN + 1;
				  }
			      TempValueB = TempValueB / TempN;
			   }

			   TempStart = MinIndex[i]- GBzDot;
			   TempEnd = MaxIndex[i]+ GBzDot;
				// ''手工剔除--
			   if(TempStart < 0)
			   {
				  TempStart = TempStart + Number;
			   }
			    else
				{
				  if(TempStart > Number - 1) 
				   TempStart = TempStart - (Number - 1);
				}
				//  '----
				if(TempEnd < 0)  
				{
				   TempEnd = TempEnd + Number;
				}
				 else
				 {
				   if(TempEnd > Number - 1)
				     TempEnd = TempEnd - (Number - 1);
				 }
				 // '---
				 TempN = 0;
				 if(TempEnd > TempStart)
				 {
				   TempN = TempEnd - TempStart + 1;
				 }
				  else
				  {
				    for(j=TempStart;j< Number;j++)
					{
				       TempN = TempN + 1;
					}
				    for(j=0 ;j<=TempEnd;j++)
					{
				      TempN = TempN + 1;
					}
			
				  }

	      //'SJChuli.List1.AddItem "补值个数= " & TempN
          //'SJChuli.List1.AddItem "补值范围: " & TempStart & " ** " & TempEnd
          TempK = (TempValueB - TempValueA) / TempN;
         if (TempEnd > TempStart) 
		  {
            for (j = TempStart;j<=TempEnd;j++)
			{
                Soudata[j]= Soudata[TempStart] + TempK * (j - TempStart); //给缺口处填充平均值
			}
		  }
         else
		  {
            for (j = TempStart;j<Number;j++)
		   {
               Soudata[j]= Soudata[TempStart] + TempK * (j - TempStart);
		   }
           for(j = 0 ;j<= TempEnd;j++)
		   {
               Soudata[j]= Soudata[TempStart]+ TempK * (j + Number - TempStart);
		   }
		 }
		 //  '-'手工剔除--得到第i个片(缺口间)的起始位置,终止位置----
		 GQkWStart[i] = TempStart;// '对应第几个片（缺口内外）的起始位置
		 GQkWEnd[i] = TempEnd;// '对应第几个片（缺口内外）的终止位
}	 

      double DH[3600];
       for (i = 0 ;i< Number;i++)
	   {
			 Resdata[i]= Soudata[i];
			 DH[i]=Soudata[i];
	   } 
       GQkNumber = QkNumber;

	  //  '---Step-3   得到结果数据--
QuitB:
      for (i = 0 ;i< Number;i++)
	  {
          Resdata[i]=Soudata[i];
              DH[i]=Soudata[i];
	  }     
}

void CDoPlaneness:: WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata)
{
 double  FB0=0.0,FB11=0.0,FB12=0.0,FB21=0.0,FB22=0.0,FB31=0.0,FB32=0.0;
 double  FA11=0.0,FA12=0.0,FA21=0.0,FA22=0.0,FA31=0.0 , FA32=0.0;
 double  FC10=0.0,FC11=0.0,FC20=0.0,FC12=0.0,FC21=0.0,FC22=0.0,FC30=0.0,FC31=0.0,FC32=0.0;
 double  FY=0.0,FY10=0.0,FY11=0.0,FY12=0.0,FY20=0.0,FY21=0.0,FY22=0.0,FY30=0.0,FY31=0.0,FY32=0.0;
 double  FX10=0.0,FX11=0.0,FX12=0.0,FX20=0.0,FX21=0.0,FX22=0.0,FX30=0.0,FX31=0.0,FX32=0.0;
 int  i;
  switch ( ModeIndex)
  {
	case 2: //'考虑1-500次谐波,考虑2-500次谐波
     FB0 = 0.9715407;
     FA11 = 0.3625683;
     FA12 = 0.1418361;
     FA21 = -0.1800023;
     FA22 = 0.04712104;
     FA31 = -0.3279947;
     FA32 = 0.03096972;
     goto JSA;
    break;
	case  3: //'考虑1-500次谐波,考虑2-500次谐波
	 FB0 = 0.9715407;
	 FA11 = 0.3625683;
	 FA12 = 0.1418361;
	 FA21 = -0.1800023;
	 FA22 = 0.04712104;
	 FA31 = -0.3279947;
     FA32 = 0.03096972;
     goto JSA;
   	break;
  case 4: //'考虑2-15次谐波
	  FB0 = 0.00790757;
	  FA11 = -1.945375;
	  FA12 = 0.9534476;
	  FA21 = -1.870021;
	  FA22 = 0.877953;
	  FA31 = -1.829474;
	  FA32 = 0.8371969;
      goto JSA;  
	 break;
  case 5: //考虑2-50次谐波
     FB0 = 0.07668238;
     FA11 = -1.766026;
     FA12 = 0.8522346;
     FA21 = -1.572835;
     FA22 = 0.6480164;
     FA31 = -1.485485;
     FA32 = 0.5550557;
     goto JSA;
	break;
 case 6: //'考虑2-150次谐波
	 FB0 = 0.4420209;
     FA11 = -0.9900672;
     FA12 = 0.602457;
     FA21 = -0.8610914;
     FA22 = 0.2743281;
     FA31 = -0.8458274;
     FA32 = 0.1871002;
     goto JSA; 
	break;
 case 7: //'考虑15-500次谐波
     FB0 = 0.9715407;
     FA11 = 0.3625683;
     FA12 = 0.1418361;
     FA21 = -0.1800023;
     FA22 = 0.04712104;
     FA31 = -0.3279947;
     FA32 = 0.03096972;
     //'-----
     FY11 = Soudata[Number - 1];
     FY12 = FY11;
     FY21 = FY11;
     FY22 = FY11;
     FY31 = FY11;
     FY32 = FY11;
     for( i = 0 ;i< Number ;i++){
		 FY = Soudata[i];
		 FY = FB0 * FY - FA11 * FY11 - FA12 * FY12;
		 FY12 = FY11;
		 FY11 = FY;
		 FY = FB0 * FY - FA21 * FY21 - FA22 * FY22;
		 FY22 = FY21;
		 FY21 = FY;
		 FY = FB0 * FY - FA31 * FY31 - FA32 * FY32;
		 FY32 = FY31;
		 FY31 = FY;
	 }
     for( i = 0;i< Number ;i++)
	 { FY = Soudata[i];
	 FY = FB0 * FY - FA11 * FY11 - FA12 * FY12;
	 FY12 = FY11;
	 FY11 = FY;
	 FY = FB0 * FY - FA21 * FY21 - FA22 * FY22;
	 FY22 = FY21;
	 FY21 = FY;
	 FY = FB0 * FY - FA31 * FY31 - FA32 * FY32;
	 FY32 = FY31;
	 FY31 = FY;
	 Resdata[i] = FY;
     }
     //'-----
     FC10 = 0.958185;
     FC11 = -1.908259;
     FC12 = 0.950091;
     FC20 = 0.937995;
     FC21 = -1.86805;
     FC22 = 0.930072;
     FC30 = 0.942067;
     FC31 = -1.876159;
     FC32 = 0.934109;
     FB11 = -1.943874;
     FB12 = 0.95235;
     FB21 = -1.869731;
     FB22 = 0.877708;
     FB31 = -1.828324;
     FB32 = 0.836162;
     goto JSB;
	break;
//'---------------------
case 8: //'考虑3-16次谐波
	FB0 = 0.00903713;
	FA11 = -1.940933;
	FA12 = 0.9504167;
	FA21 = -1.861476;
	FA22 = 0.8703692;
	FA31 = -1.8186;
	FA32 = 0.8273507;
     goto JSA;  
    break;
case 9: //'考虑17-100次谐波
	FB0 = 0.2467169;
	FA11 = -1.411618;
	FA12 = 0.7215067;
	FA21 = -1.183828;
	FA22 = 0.4203676;
	FA31 = -1.110474;
	FA32 = 0.3153477;
	//'-----
	FY11 = Soudata[Number - 1],
		FY12 = FY11;
	FY21 = FY11;
	FY22 = FY11;
	FY31 = FY11;
	FY32 = FY11;
	for( i = 0;i<  Number ;i++){
		FY = Soudata[i];
		FY = FB0 * FY - FA11 * FY11 - FA12 * FY12;
		FY12 = FY11;
		FY11 = FY;
		FY = FB0 * FY - FA21 * FY21 - FA22 * FY22;
		FY22 = FY21;
		FY21 = FY;
		FY = FB0 * FY - FA31 * FY31 - FA32 * FY32;
		FY32 = FY31;
		FY31 = FY;
	}
	for (i = 0;i <Number ;i++){
		FY = Soudata[i];
		FY = FB0 * FY - FA11 * FY11 - FA12 * FY12;
		FY12 = FY11;
		FY11 = FY;
		FY = FB0 * FY - FA21 * FY21 - FA22 * FY22;
		FY22 = FY21;
		FY21 = FY;
		FY = FB0 * FY - FA31 * FY31 - FA32 * FY32;
		FY32 = FY31;
		FY31 = FY;
		Resdata[i] = FY;
	}
	//'-----
	FC10 = 0.945494;
	FC11 = -1.880709;
	FC12 = 0.935243;
	FC20 = 0.934633;
	FC21 = -1.859106;
	FC22 = 0.924501;
	FC30 = 0.939649;
	FC31 = -1.869084;
	FC32 = 0.929462;
	FB11 = -1.936118;
	FB12 = 0.946826;
	FB21 = -1.852825;
	FB22 = 0.862949;
	FB31 = -1.806849;
	FB32 = 0.816781;
	goto JSB;
  break;
}//'---------------------------
JSA: 
     FY11 = Soudata[Number - 1];
     FY12 = FY11;
     FY21 = FY11;
     FY22 = FY11;
     FY31 = FY11;
     FY32 = FY11;
     for( i = 0; i< Number ;i++){
       FY = Soudata[i];
       FY = FB0 * FY - FA11 * FY11 - FA12 * FY12;
       FY12 = FY11;
       FY11 = FY;
       FY = FB0 * FY - FA21 * FY21 - FA22 * FY22;
       FY22 = FY21;
       FY21 = FY;
       FY = FB0 * FY - FA31 * FY31 - FA32 * FY32;
       FY32 = FY31;
       FY31 = FY;
     }
     for( i = 0 ;i< Number ;i++){
       FY = Soudata[i];
       FY = FB0 * FY - FA11 * FY11 - FA12 * FY12;
       FY12 = FY11;
       FY11 = FY;
       FY = FB0 * FY - FA21 * FY21 - FA22 * FY22;
       FY22 = FY21;
       FY21 = FY;
       FY = FB0 * FY - FA31 * FY31 - FA32 * FY32;
       FY32 = FY31;
       FY31 = FY;
       Resdata[i] = FY;
     }
	 TRACE("jsa\n");
     return;
//'---------------------
JSB: 
     FY11 = Resdata[Number - 1];
     FY12 = FY11;
     FY21 = FY11;
     FY22 = FY11;
     FY31 = FY11;
     FY32 = FY11;
     FX11 = Resdata[Number - 1];
     FX12 = FX11;
     FX21 = FX11;
     FX22 = FX11;
     FX31 = FX11;
     FX32 = FX11;
     for( i = 0;i< Number ;i++){
       FX10 = Resdata[i];
       FY10 = FC10 * FX10 + FC11 * FX11 + FC12 * FX12 - FB11 * FY11 - FB12 * FY12;
       FY12 = FY11;
       FY11 = FY10;
       FX12 = FX11;
       FX11 = FX10;
       FX20 = FY10;
       FY20 = FC20 * FX20 + FC21 * FX21 + FC22 * FX22 - FB21 * FY21 - FB22 * FY22;
       FY22 = FY21;
       FY21 = FY20;
       FX22 = FX21;
       FX21 = FX20;
       FX30 = FY20;
       FY30 = FC30 * FX30 + FC31 * FX31 + FC32 * FX32 - FB31 * FY31 - FB32 * FY32;
       FY32 = FY31;
       FY31 = FY30;
       FX32 = FX31;
       FX31 = FX30;
     }
     for( i = 0 ;i< Number ;i++){
       FX10 = Resdata[i];
       FY10 = FC10 * FX10 + FC11 * FX11 + FC12 * FX12 - FB11 * FY11 - FB12 * FY12;
       FY12 = FY11;
       FY11 = FY10;
       FX12 = FX11;
       FX11 = FX10;
       FX20 = FY10;
       FY20 = FC20 * FX20 + FC21 * FX21 + FC22 * FX22 - FB21 * FY21 - FB22 * FY22;
       FY22 = FY21;
       FY21 = FY20;
       FX22 = FX21;
       FX21 = FX20;
       FX30 = FY20;
       FY30 = FC30 * FX30 + FC31 * FX31 + FC32 * FX32 - FB31 * FY31 - FB32 * FY32;
       FY32 = FY31;
       FY31 = FY30;
       FX32 = FX31;
       FX31 = FX30;
       Resdata[i] = FY30;
     }
	 TRACE("jsb\n");
    return;
}

// TODO: Add your message handler code here and/or call default
void CDoPlaneness::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
		// TODO: Add your message handler code here and/or call default
	CWnd *pWndCy; 
	CRect rectP; 
	CDC *pDCP;          
	pWndCy = GetDlgItem(IDC_Planeness);      
	pWndCy->GetClientRect(&rectP); 
	pWndCy->ClientToScreen(rectP);       //转换到屏幕坐标,左上角坐标为文本框在屏幕的坐标
	pDCP = pWndCy->GetDC();
	this->ClientToScreen(&point);          //转换为屏幕坐标
		
	point.x=point.x-rectP.left;         //把point坐标由相对于屏幕坐标转换为相对于静态框坐标，静态框左上角是(0,0)
	point.y=point.y-rectP.top;
	
	CPoint centerPoint;
	centerPoint.x=(rectP.right-rectP.left)*0.667/2;
	centerPoint.y=(rectP.bottom-rectP.top)*3/5;//就是绘制圆柱的z[0]的中心点。
	int R=rectP.Width()*0.6/2.2;

	//绘制图形
	if ( point.x>=(centerPoint.x-R) && point.x<=(centerPoint.x-0.2*R)
		&&point.y>= (centerPoint.y-rectP.Height()*0.55) && point.y<=(centerPoint.y-rectP.Height()*0.45))
	{	
		((CMainFrame*)AfxGetMainWnd())->m_fullJMPath=((CMainFrame*)AfxGetMainWnd())->m_fullPath5;//获取圆柱度的路径
		((CMainFrame*)AfxGetMainWnd())->m_fullJMType=1;    //类型区分
		((CMainFrame*)AfxGetMainWnd())->m_fullJMNum=3600; 
		((CMainFrame*)AfxGetMainWnd())->m_SelectJM=0;//鼠标单击的截面
		((CMainFrame*)AfxGetMainWnd())->G11=G1;
		((CMainFrame*)AfxGetMainWnd())->G22=G2;
		((CMainFrame*)AfxGetMainWnd())->DoJMAnalyse();
	}	
	CFormView::OnLButtonDblClk(nFlags, point);
}




void CDoPlaneness::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	CBitmap* pOldBmp= NULL;     
	CBitmap memBitmap; 
	CDC memDC;

	int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);
    int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);
	int xLogPixPerMM=xLogPixPerInch/25.4;
	int yLogPixPerMM=yLogPixPerInch/25.4;
	int m_penScale=xLogPixPerInch/96;
	
	CRect rect1;
	//打印框的尺寸为150*250(mm)
	CPoint pt(0,0);
	CSize  sz(270*xLogPixPerMM,200*yLogPixPerMM);
	CRect  tRect(pt,sz);
	rect1.top=tRect.top+25*yLogPixPerMM;
	rect1.right=tRect.right;
	rect1.left=tRect.left+20*xLogPixPerMM;
	rect1.bottom=tRect.bottom-25*yLogPixPerMM;
	
	pOldBmp = NULL;                           // 将旧的位图指针置空	
	memDC.CreateCompatibleDC(pDC);             // 创建内存绘图设备，使内存位图的DC与控件的DC关联
	memBitmap.CreateCompatibleBitmap(pDC,tRect.right,tRect.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap);
    memDC.FillSolidRect(tRect.left,tRect.top,tRect.right,tRect.bottom,RGB(255,255,255));//给矩形框填充白色
	
	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDC.SelectObject(&RectPen);               
	memDC.Rectangle(rect1.left,rect1.top,rect1.right,rect1.bottom); //静态框加上 颜色 边框
	
	//修改打印字体大小
	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
		DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
	CFont*   pOldFont=(CFont*)memDC.SelectObject(&font); 
	
	// 取当前字体大小
	CFont *curFont = pDC->GetCurrentFont();
	LOGFONT curLogFont;
	LOGFONT newLogFont;
	
	curFont->GetLogFont( &curLogFont );
	long NewFontWidth = curLogFont.lfWidth;
	long NewFontHeight = curLogFont.lfHeight;
	newLogFont = curLogFont;
	
	//计算新的字体大小--缩小一倍
	newLogFont.lfWidth =(long)((float)NewFontWidth
		* ((float)xLogPixPerInch / 96.0));
	newLogFont.lfHeight =(long)((float)NewFontHeight
		* ((float)yLogPixPerInch / 96.0)); 
	
	//创建并设置新的字体，保留以前的字体
	CFont newFont;
	CFont *oldFont;
	
	newFont.CreateFontIndirect(&newLogFont);
	oldFont = memDC.SelectObject(&newFont );
	
	//绘制上栏
	memDC.MoveTo(rect1.left,rect1.top);
	memDC.LineTo(rect1.left,rect1.top-10*xLogPixPerMM);
	memDC.MoveTo(rect1.left,rect1.top-10*xLogPixPerMM);
	memDC.LineTo(rect1.right,rect1.top-10*xLogPixPerMM);
	memDC.MoveTo(rect1.right,rect1.top-10*xLogPixPerMM);
	memDC.LineTo(rect1.right,rect1.top);
	//绘制下栏
	memDC.MoveTo(rect1.left,rect1.bottom);
	memDC.LineTo(rect1.left,rect1.bottom+10*xLogPixPerMM);
	memDC.MoveTo(rect1.left,rect1.bottom+10*xLogPixPerMM);
	memDC.LineTo(rect1.right,rect1.bottom+10*xLogPixPerMM);
	memDC.MoveTo(rect1.right,rect1.bottom+10*xLogPixPerMM);
	memDC.LineTo(rect1.right,rect1.bottom);
	RectPen.DeleteObject();
	
	//写入信息
    memDC.TextOut(0.8*rect1.left+200*xLogPixPerMM,rect1.bottom+11*yLogPixPerMM,
		"广州威而信精密仪器有限公司");
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_strOperatorName;
	str.Format("操作员:%s",str);
	memDC.TextOut(rect1.left+75*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineModel;
	str.Format("机床型号:%s",str);
	memDC.TextOut(rect1.left+115*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineName;
	str.Format("机床:%s",str);
	memDC.TextOut(rect1.left+155*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strProcess;
	str.Format("工序:%s",str);
	memDC.TextOut(rect1.left+195*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceModel;
	str.Format("工件型号:%s",str);
	memDC.TextOut(rect1.left+15*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceNum;
	str.Format("工件编号:%s",str);
	memDC.TextOut(rect1.left+75*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strIndent;
	str.Format("订单:%s",str);
	memDC.TextOut(rect1.left+135*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strInspector;
	str.Format("检测员:%s",str);
	memDC.TextOut(rect1.left+195*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);

	
	double fw1=2*rect1.Width()/3;
	double f1=rect1.Width();
	double f2=rect1.Height();                                            	                             
    double fw2=1*rect1.Width()/3;	
    //////////////////////表格///////////////////////////////
	memDC.SetBkMode(TRANSPARENT); 
    double l1=rect1.left,l2=rect1.top,l3=rect1.right,l4=rect1.bottom;
	int gridxnums=1;
	int gridynums=22;
    double fwgx=fw2,fwgy=f2;
	double dx=fw2/gridxnums;
	double dy=f2/gridynums;
	CRect gridRect(l1+fw1,l2,l3,l4);
	memDC.FillSolidRect(l1+fw1,l2,fw2,f2,RGB(255,255,255));
    
	CPen gridPen(PS_SOLID,1*m_penScale,RGB(0,0,20));
    CPen *oldpen2=memDC.SelectObject(&gridPen);
	memDC.FillSolidRect(l1+fw1,l2,fw2,dy,RGB(232,232,232));//给头行填充颜色
 	memDC.FillSolidRect(l1+fw1,l2+dy*5,fw2,dy,RGB(232,232,232));//给指定行填充颜色
 	memDC.FillSolidRect(l1+fw1,l2+dy*9,fw2,dy,RGB(232,232,232));//给指定行填充颜色

	for(int m=0;m<=gridxnums;m++) //画出gridxnums条竖线                      
	{
		memDC.MoveTo(l1+fw1+m*dx,gridRect.bottom);
		memDC.LineTo(l1+fw1+m*dx,gridRect.top);
	}

	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
	{
		memDC.MoveTo(l1+fw1,l2+n*dy);
		memDC.LineTo(l1+fw1+fw2,l2+n*dy);
	}
	int i;
	//读取数据
	std::ifstream fin(((CMainFrame*)AfxGetMainWnd())->m_fullPath5, std::ios::binary);
	int maxValue=0;
	int minValue=4096;
	fin.read((char*)&m_data[0], sizeof(shuju0));
	for (i=0;i<3600;i++)
	{	
		fin.read((char*)&m_data[i], sizeof(shuju0));
		if (m_data[i].data>maxValue)
		{
			maxValue=m_data[i].data;
		}
		if (m_data[i].data<minValue)
		{
			minValue=m_data[i].data;
		}
	}
	fin.read((char*)&G1,sizeof(double));
	fin.read((char*)&G2,sizeof(double));
	fin.read((char*)&m_t,sizeof(CTime));
	fin.close();

	//////////////////////////////////////////////////////////////////////////
	//绘制报表
  
    memDC.SetBkMode(TRANSPARENT); 
	int meter=dy/10;
	int m1=l1+fw1+fw2/30;
	double m2=l1+fw1+dx*0.45;
	double m3=l1+fw1+dx*0.66;
	double mid=l1+fw1+dx*0.4;

    memDC.TextOut(mid ,l2+meter,"平面度测量结果");

	memDC.TextOut(mid,l2+dy*5+meter,"规格要求");
	memDC.TextOut(mid,l2+dy*9+meter,"测量参数");

    memDC.TextOut(m1,l2+dy+meter,"文件名");
	memDC.TextOut(m1,l2+dy*2+meter,"测量时间");
	memDC.TextOut(m1,l2+dy*6+meter,"参考类型");                                       
	memDC.TextOut(m1,l2+dy*7+meter,"滤波器种类");                                              
	memDC.TextOut(m1,l2+dy*8+meter,"滤波范围");    
                                                 
                     	
	memDC.TextOut(m1,l2+dy*10+meter,"工艺要求");
	memDC.TextOut(m1,l2+dy*11+meter,"平面度");
 
	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath5;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDC.TextOut(m2,l2+dy*1+meter,str);
	//显示测量时间
	CString strText=m_t.Format("%Y-%m-%d %H:%M");
	memDC.TextOut(m2,l2+dy*2+meter,strText);

	memDC.TextOut(m2,l2+dy*6+meter,m_strMethod);
	memDC.TextOut(m2,l2+dy*7+meter,"Gaussian");
	memDC.TextOut(m2,l2+dy*8+meter,m_strlvbo);
	strText.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[4]);
	memDC.TextOut(m2,l2+dy*10+meter,strText);
	memDC.TextOut(m3,l2+dy*10+meter,"um");
	memDC.TextOut(m3,l2+dy*11+meter,"um");
	//绘制图形
	C3dPoint pt3[4]; 
	CPoint pts[4];
	CPoint centerPoint(rect1.left+rect1.Width()*0.667/2,rect1.top+rect1.Height()*3/5);
	BYTE r3; 
	BYTE g3; 
	BYTE b3;
	int endNum=0;
	//定义高度和画图的间隔
	int intHeight=rect1.Height()*0.2;
	int dwidth=4;
	int intMinRadius=rect1.Width()*0.6/5;
	int intMaxRadius=rect1.Width()*0.6/2;

	//定义视点
	int VPOINT_x=0;
	int VPOINT_y=1000;
	int VPOINT_z=1300;
	
 	int cool;
	int colorLength=maxValue-minValue+1;
	CColorMap campObject(150);
	int campx[4096][3];
	campObject.Jet();
	for (i=0;i<4096;i++)
	{
		campx[i][0]=campObject.camp[i][0];
		campx[i][1]=campObject.camp[i][1];
		campx[i][2]=campObject.camp[i][2];
	}
	int R=0;
	R=rect1.Width()*0.6/2.2;
	endNum=0;
	for (int j=0;j<3600;j=j+dwidth)
	{
				
		pt3[0].x=R*cos((j)*2*PI/3600);
		pt3[0].y=R*sin((j)*2*PI/3600);
		pt3[0].z=-((m_data[j].data-minValue)*intHeight/(maxValue-minValue+1));

		pts[0]=pt3[0].Change(VPOINT_x,VPOINT_y,VPOINT_z);
		pts[0]=pts[0]+centerPoint;
			
		endNum=j+dwidth;
		if (endNum>=3600)
		{

			endNum=0;
			pt3[1].x=R*cos((endNum)*2*PI/3600);
			pt3[1].y=R*sin((endNum)*2*PI/3600);
			pt3[1].z=-((m_data[0].data-minValue)*intHeight/(maxValue-minValue+1));
			
			pts[1]=pt3[1].Change(VPOINT_x,VPOINT_y,VPOINT_z);
			pts[1]=pts[1]+centerPoint;

			pt3[2].x=R*cos((endNum)*2*PI/3600);
			pt3[2].y=R*sin((endNum)*2*PI/3600);	
			pt3[2].z=0;
			pts[2]=pt3[2].Change(VPOINT_x,VPOINT_y,VPOINT_z);
			pts[2]=pts[2]+centerPoint;
		}
		else
		{
			pt3[1].x=R*cos((j+dwidth)*2*PI/3600);
			pt3[1].y=R*sin((j+dwidth)*2*PI/3600);
			pt3[1].z=-((m_data[j+dwidth].data-minValue)*intHeight/(maxValue-minValue+1));
				
			pts[1]=pt3[1].Change(VPOINT_x,VPOINT_y,VPOINT_z);
			pts[1]=pts[1]+centerPoint;

			pt3[2].x=R*cos((j+dwidth)*2*PI/3600);
			pt3[2].y=R*sin((j+dwidth)*2*PI/3600);
			pt3[2].z=0;

			pts[2]=pt3[2].Change(VPOINT_x,VPOINT_y,VPOINT_z);
			pts[2]=pts[2]+centerPoint;
		}  
		pt3[3].x=R*cos((j)*2*PI/3600);
		pt3[3].y=R*sin((j)*2*PI/3600);
		pt3[3].z=0;

		pts[3]=pt3[3].Change(VPOINT_x,VPOINT_y,VPOINT_z);
		pts[3]=pts[3]+centerPoint;
		if (!m_data[j].selected)
		{
			cool=(int)((m_data[j].data-minValue)*150/colorLength);
			r3 =campx[cool][0];  
			g3=campx[cool][1];
			b3 = campx[cool][2]; 
		}
		else
		{
			r3=0;
			g3=0;
			b3=0;
		}
		CBrush brushRed(RGB(r3, g3, b3));
		CPen penBlue(PS_SOLID, 1*m_penScale, RGB(r3, g3, b3));
		CPen* pOldPen = memDC.SelectObject(&penBlue);
		CBrush* pOldBrush = memDC.SelectObject(&brushRed);
		memDC.Polygon(pts, 4);
		memDC.SelectObject(pOldBrush);
		memDC.SelectObject(pOldPen);
		CPen penBlue2(PS_SOLID, 1*m_penScale, RGB(0, 50, 220));
		pOldPen = memDC.SelectObject(&penBlue2);
		memDC.MoveTo(pts[0]);
		memDC.LineTo(pts[1]);		    
		memDC.SelectObject(pOldPen);
		brushRed.DeleteObject();
		penBlue.DeleteObject();
		pOldPen->DeleteObject();
		pOldBrush->DeleteObject();
			
	}
	//建立垂直坐标系
	for (i=0;i<=10;i++)
	{
		if (i%5==0)
		{
			pt2Start.x=-rect1.Width()/80;
			pt2Start.y=-i*intHeight/10;
			pt2End.x=rect1.Width()/80;
			pt2End.y=-i*intHeight/10;
			pt2Start+=centerPoint;
			pt2End+=centerPoint;
			memDC.MoveTo(pt2Start);
			memDC.LineTo(pt2End);
		}
		else
		{
			pt2Start.x=-rect1.Width()/140;
			pt2Start.y=-i*intHeight/10;
			pt2End.x=rect1.Width()/140;
			pt2End.y=-i*intHeight/10;
			pt2Start+=centerPoint;
			pt2End+=centerPoint;
			memDC.MoveTo(pt2Start);
			memDC.LineTo(pt2End);
		}

	}
	str.Format("%.2f",((maxValue-2048)*10.0/(G1*G2*4096)-(minValue-2048)*10.0/(G1*G2*4096))/10.0);
	str+="um/每格";
//	memDC.TextOut(centerPoint.x,centerPoint.y-rect1.Height()*0.55,str);
	memDC.TextOut(centerPoint.x+rect1.Height()/3,rect1.bottom-rect1.Height()/30,str);
	memDC.TextOut(centerPoint.x-R,centerPoint.y-rect1.Height()*0.55,"截面分析");

	//绘制标识图
	int dwidth1=rect1.Width()*0.6/30;
	int dheight=rect1.Height()/30;
	CPoint startPoint(rect1.left+rect1.Width()*0.6*0.15,rect1.bottom-rect1.Height()/30);
	for (i=0;i<30;i++)
	{
		pts[0].x=startPoint.x+dwidth*i;
		pts[0].y=startPoint.y;
		
		cool=(int)(i*150/30);
		r3 =campx[cool][0];  
		g3=campx[cool][1];
 		b3 = campx[cool][2]; 
		memDC.FillSolidRect(pts[0].x,pts[0].y,dwidth1,dheight,RGB(r3,g3,b3));

	}
	str.Format("%.2fum",(minValue-2048)*10/(G1*G2*4096));
	memDC.TextOut(rect1.left+rect1.Width()*0.6*0.01,rect1.bottom-rect1.Height()/30,str);
	str.Format("%.2fum",(maxValue-2048)*10/(G1*G2*4096));
	memDC.TextOut(rect1.left+rect1.Width()*0.6*0.32,rect1.bottom-rect1.Height()/30,str);

	SubQKDataChuli(((CMainFrame*)AfxGetMainWnd())->m_fullPath5,3600, Resdata,!((CMainFrame*)AfxGetMainWnd())->m_bAutoQK,0, 3600);
	SubAnaData (3, Resdata,GResult,G1,G2);	//圆度
	m_strpmd.Format("%.3f",GResult[1]); //将数据结果转换成字符串的形式，便于显示在表格中

	memDC.SetTextColor(RGB(0,0,0));//红色字体      
    memDC.TextOut(m2,l2+dy*11+meter,m_strpmd);//界面显示平面度

	pDC->BitBlt(tRect.left,tRect.top,tRect.right,tRect.bottom,&memDC,0,0,SRCCOPY);  //把已经绘好的图显示在制定位置上
    memDC.SelectObject(pOldBmp);
    memDC.DeleteDC();
    memBitmap.DeleteObject();//释放内存设备


	
}

void CDoPlaneness::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFormView::OnPrepareDC(pDC, pInfo);

	pDC->SetMapMode(MM_ANISOTROPIC);
}

BOOL CDoPlaneness::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	CWinApp*   pApp   =   AfxGetApp(); 
	if(pApp-> GetPrinterDeviceDefaults(&pInfo-> m_pPD-> m_pd)) 
	{ 
		LPDEVMODE   lpDevmode   =   pInfo-> m_pPD-> GetDevMode(); 
		lpDevmode-> dmOrientation   =   DMORIENT_LANDSCAPE; 
	} 
	return CFormView::DoPreparePrinting(pInfo);
}

void CDoPlaneness::OnPrint() 
{
	// TODO: Add your command handler code here
	CFormView::OnFilePrint();
}



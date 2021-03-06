// DoCoaxiality.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DoCoaxiality.h"
#include "MainFrm.h"
#include "const.h"
#include "math.h"
#include "3dPoint.h"
#include "Line.h"
#include <fstream>
#include "AmpScale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoCoaxiality

IMPLEMENT_DYNCREATE(CDoCoaxiality, CFormView)

CDoCoaxiality::CDoCoaxiality()
	: CFormView(CDoCoaxiality::IDD)
{
	//{{AFX_DATA_INIT(CDoCoaxiality)
	//}}AFX_DATA_INIT
	m_ModeChoose=0;
	flagAmpscale=0;
	m_AmpScale=1;
	ratio1=0;

      AngleZ=0;
      SeeAngle=0;
      BTCHUL=0;
	  m_Wa="";	//波纹度显示
	  m_Wc="";	//波纹度显
	  m_Wp="";	//波纹度显
	  m_Wv="";	//波纹度显示
	  m_Wt="";	//波纹度显
	  m_Wq="";	//波纹度显
      m_Wwm="";	//波纹度显
	  
}

CDoCoaxiality::~CDoCoaxiality()
{
}

void CDoCoaxiality::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoCoaxiality)
	DDX_Control(pDX, IDC_STATIC_Coaxiality, m_editCylinder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoCoaxiality, CFormView)
	//{{AFX_MSG_MAP(CDoCoaxiality)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_ToLeft, OnToLeft)
	ON_BN_CLICKED(IDC_ToRight, OnToRight)
	ON_COMMAND(ID_Print, OnPrint)
	ON_COMMAND(ID_BTNTBEGIN, OnBtntbegin)
	ON_COMMAND(ID_BTNTSTOP, OnBtntstop)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_BTNTLEFT,OnToLeft)
    ON_BN_CLICKED(ID_BTNTRIGHT,OnToRight)
	ON_COMMAND(ID_AmplifyScale, OnAmplifyScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoCoaxiality diagnostics

#ifdef _DEBUG
void CDoCoaxiality::AssertValid() const
{
	CFormView::AssertValid();
}

void CDoCoaxiality::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoCoaxiality message handlers

void CDoCoaxiality::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->DestroyVIEW(((CMainFrame*)AfxGetMainWnd())->m_DoCoaxiality);
	((CMainFrame*)AfxGetMainWnd())->m_DoCoaxiality=NULL;
	((CMainFrame*)AfxGetMainWnd())->Desktop();
}

void CDoCoaxiality::OnPaint() 
{
	
	CPaintDC dc(this); // device context for painting 
	CRect rectFill;
    GetClientRect(rectFill);
    dc.FillSolidRect(rectFill,RGB(255,255,255));  //设置为白色背景 

   	pWnd = GetDlgItem(IDC_STATIC_Coaxiality);      // 获得对话框上的picture的窗口句柄
	pWnd->GetClientRect(&rect);             // 获取绘制坐标的文本框
	pDC = pWnd->GetDC();                     // 获得对话框上的picture的设备指针

	pOldBmp= NULL;  // 获得对话框上的picture的设备指针
	memDC.CreateCompatibleDC(pDC);             // 创建内存绘图设备，使内存位图的DC与控件的DC关联
	memBitmap.CreateCompatibleBitmap(pDC ,rect.right,rect.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap); 

 
	CPen CyPen(PS_SOLID,1,RGB(0,0,0));
	memDC.SelectObject(&CyPen);               
	memDC.Rectangle(rect.left,rect.top,rect.right,rect.bottom); //静态框加上颜色边框
	memDC.MoveTo(rect.right*2/3,rect.top);
    memDC.LineTo(rect.right*2/3,rect.bottom);
    CyPen.DeleteObject();

    ///////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
	double gridleft=rect.Width()*2/3;
	int gridxnums=1;int gridynums=22;
	double dx= (rect.Width()-gridleft)/gridxnums;
	double dy=rect.Height()/gridynums;
    CRect gridRect(gridleft,rect.top,rect.left+dx*gridxnums,rect.top+dy*gridynums);
	CPen gridPen(0,0,RGB(0,0,20));
	//mDC.FillSolidRect(dx*3,dy*12,dx,dy,RGB(139,216,224));//给指定格子填充颜色
   //------------------------------------------------------------
// 	memDC.FillSolidRect(gridleft,0,gridRect.right-1,dy,RGB(232,232,232));//给头行填充颜色
// 	memDC.FillSolidRect(gridleft,dy*5,gridRect.right-1,dy,RGB(232,232,232));//给指定行填充颜色
// 	memDC.FillSolidRect(gridleft,dy*13,gridRect.right-1,dy,RGB(232,232,232));//给指定行填充颜色

// 	CPen *oldpen=memDC.SelectObject(&gridPen);
// 
// 	for( int m0=0;m0<=gridxnums;m0++) //画出gridxnums条竖线                      
// 	{
// 		memDC.MoveTo(gridleft+m0*dx,gridRect.bottom);
// 		memDC.LineTo(gridleft+m0*dx,0);
// 	}
// 	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
// 	{
// 		memDC.MoveTo(rect.left+gridleft,n*dy);
// 		memDC.LineTo(rect.left+rect.Width(),n*dy);
// 	}
	//------------------------------------------------------------
	//----------数据写入字体及大小

	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
	CFont*   pOldFont=(CFont*)memDC.SelectObject(&font); 

	DrawCoaxiality();//调用画圆柱的函数  
    CalCoaxiality();//计算同轴度

	memDC.FillSolidRect(gridleft,0,gridRect.right-1,dy,RGB(232,232,232));//给头行填充颜色
	memDC.FillSolidRect(gridleft,dy*5,gridRect.right-1,dy,RGB(232,232,232));//给指定行填充颜色
	memDC.FillSolidRect(gridleft,dy*13,gridRect.right-1,dy,RGB(232,232,232));//给指定行填充颜色
	
	CPen *oldpen=memDC.SelectObject(&gridPen);
	
	for( int m0=0;m0<=gridxnums;m0++) //画出gridxnums条竖线                      
	{
		memDC.MoveTo(gridleft+m0*dx,gridRect.bottom);
		memDC.LineTo(gridleft+m0*dx,0);
	}
	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
	{
		memDC.MoveTo(rect.left+gridleft,n*dy);
		memDC.LineTo(rect.left+rect.Width(),n*dy);
	}

	memDC.SetBkMode(TRANSPARENT); 
	int meter=4;
	int m1=gridleft+4;
	double m2=gridleft+dx/2;
	double m3=gridleft+dx-80;
	double mid=gridleft+dx/2-30;
 //角度显示
// 	if (AngleZ%360>0)
// 	{
// 		SeeAngle=AngleZ%360-10;
// 	}
// 	else
// 	{
// 		SeeAngle=AngleZ%360+350;
// 	}

	if (AngleZ%360>0)
	{
		SeeAngle=AngleZ%360;
	}
	else
	{
		SeeAngle=AngleZ%360;
	}

	m_Seeangle.Format("%d",SeeAngle);

    memDC.TextOut(mid ,meter,"同轴度测量结果");

	memDC.TextOut(mid+20,dy*5+meter,"规格要求");
	memDC.TextOut(mid+20,dy*13+meter,"测量参数");

    memDC.TextOut(m1,dy+meter,"文件名");
	memDC.TextOut(m1,dy*2+meter,"测量时间");
	memDC.TextOut(m1,dy*6+meter,"参考类型");                                       
	memDC.TextOut(m1,dy*7+meter,"滤波器种类");                                              
	memDC.TextOut(m1,dy*8+meter,"滤波范围");    
	memDC.TextOut(m1,dy*9+meter,"截面个数");     
	memDC.TextOut(m1,dy*10+meter,"当前观测角度"); 
                     	
	memDC.TextOut(m1,dy*14+meter,"工艺要求");
	memDC.TextOut(m1,dy*16+meter,"同轴度");
// 	memDC.TextOut(m1,dy*17+meter,"波峰");
// 	memDC.TextOut(m1,dy*18+meter,"波谷");
                                                                               
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath7;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDC.TextOut((m1+m2)/2,dy*1+meter,str);
	str=m_time.Format("%Y-%m-%d %H:%M");
	memDC.TextOut((m2+m1)/2,dy*2+meter,str);
	str.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[5]);
	memDC.TextOut(m2,dy*14+meter,str);
	memDC.TextOut(m2,dy*15+meter,"  ");
	memDC.TextOut(m2,dy*6+meter,"最小二乘法");
	memDC.TextOut(m2,dy*7+meter,"Gaussian");
	memDC.TextOut(m2,dy*8+meter,"1-50");
	str.Format("%d",m_IntJM);
	memDC.TextOut(m2,dy*9+meter,str);
	memDC.TextOut(m3,dy*14+meter,"um");

	memDC.TextOut(m3,dy*16+meter,"um");
// 	memDC.TextOut(m3,dy*17+meter,"um");
// 	memDC.TextOut(m3,dy*18+meter,"um");
//	memDC.SetTextColor(RGB(0,0,0));//红色字体 
	memDC.TextOut(m2,dy*16+meter,m_tzd);
// 	memDC.TextOut(m2,dy*17+meter,m_CYLP);
//  	memDC.TextOut(m2,dy*18+meter,m_CYLV);	
	memDC.TextOut(m2,dy*10+meter,m_Seeangle+"°");

	pDC->BitBlt(rect.left,rect.top,rect.right,rect.bottom,&memDC,0,0,SRCCOPY); 
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
	memBitmap.DeleteObject();
}

/*
函数功能：计算同轴度
*/
void CDoCoaxiality::CalCoaxiality()//计算同轴度
{
	int i,j,DaNumberA,SelectATestGn,CurrentTestGN;
	double Pi=3.1415926,SampleDATA[3600],DispAdata[3600],GZJFXJG[11];
	double GResult[3],fpdata[3600],Resdata[3600];
	double X1,X2,Y1,Y2,TempA,TempB,DValue;

    DaNumberA=3600;
    CurrentTestGN=m_IntJM;
	for (SelectATestGn=1;SelectATestGn<=CurrentTestGN;SelectATestGn++)//-2-1先取第一个截面数据 DispAdata  
	{
                    
       SubQKDataChuli(((CMainFrame*)AfxGetMainWnd())->m_fullPath7,3600, Resdata,!((CMainFrame*)AfxGetMainWnd())->m_bAutoQK,SelectATestGn-1, LenData);
	   SubAnaData (1,Resdata,GResult,G1,G2);	//Call SubAnaData          	  
	   //多组数据计算时的中间结果
	   GZJFXJG[2 * SelectATestGn - 1]=GResult[2];
	   GZJFXJG[2 * SelectATestGn]=GResult[3];
       for (j=0;j<DaNumberA;j++) //	For j = 0 To DaNumberA - 1
	   {
		    DispAdata[j]= Resdata[j];// DispAdata(j) = Direc(j)
	 	    PrintAdata[SelectATestGn-1][j] = DispAdata[j];
	   }
	}
	//计算同轴度
    GZJFXJG[5]= 0;
	if(CurrentTestGN==4) //	'---以两端点计算平均值---
	{
		X1 = GZJFXJG[1] * cos(GZJFXJG[2]*Pi/180);
		Y1 = GZJFXJG[1] * sin(GZJFXJG[2]*Pi/180);
	    X2 = GZJFXJG[3] * cos(GZJFXJG[4]*Pi/180);
		Y2 = GZJFXJG[3] * sin(GZJFXJG[4]*Pi/180);
	    TempA = (GZJFXJG[1] + GZJFXJG[3])/2;
	    TempB = (GZJFXJG[2] + GZJFXJG[4])/2;
	    //	'---计算中间点对该平均值的距离---
		for(i=5;i<=7;i+=2)
		{
		    X1 = GZJFXJG[i]*cos(GZJFXJG[i+1]*Pi/180);
		    Y1 = GZJFXJG[i]*sin(GZJFXJG[i+1] * Pi/180);
			DValue =sqrt(TempA*TempA+GZJFXJG[i]*GZJFXJG[i]-2*TempA*GZJFXJG[i]*cos((TempB-GZJFXJG[i+1])*Pi/180));
		    if(DValue>GZJFXJG[5]) 
			{
		         GZJFXJG[5] = DValue;
			}
		}
	}
	else 
	{
		 if(GZJFXJG[1]> GZJFXJG[3])
		 {
			GZJFXJG[5]=GZJFXJG[1];
		 }	
		 else
		 {
			 GZJFXJG[5]= GZJFXJG[3];
		 }
		 GZJFXJG[5]=sqrt(GZJFXJG[1]* GZJFXJG[1]+GZJFXJG[3]* GZJFXJG[3]-2*GZJFXJG[1]*GZJFXJG[3]* cos((GZJFXJG[2]-GZJFXJG[4])*Pi/180));
	}
    GZJFXJG[5] = GZJFXJG[5]*2;
	tzd=GZJFXJG[5];
    m_tzd.Format("%.3f",tzd);
}


void CDoCoaxiality::DrawCoaxiality()//画圆柱
{
	// 获得对话框上的picture的设备指针	
	//求出画图的中心点
	CPoint centerPoint=0;
	centerPoint.x=rect.right*3/5/2;
	centerPoint.y=rect.bottom/8;//就是绘制圆柱的z[0]的中心点。

	memDC.TextOut(rect.Width()*3/5-20,centerPoint.y-30,"Z(mm)");
    memDC.TextOut(rect.left+5,centerPoint.y-30,"截面");

	CPen CyPe1(PS_SOLID,1,RGB(0,0,0));
	memDC.SelectObject(&CyPe1);  
	memDC.MoveTo(centerPoint.x,centerPoint.y+5);
    memDC.LineTo(centerPoint.x,rect.top+20);
    CyPe1.DeleteObject();


	//以下代码实现圆柱各个截面上圆度信息的计算和最终圆柱度的计算
	int     i=0,j=0,jmbtn;
	double  dis=0,z[JMNum],zz[JMNum],t[3600],bcondata[3600],acondata[3600],SumTs = 0.0,m_dCirMax,m_dCirMin;
	double  a=0,b=0,l=0,g=0,DR=0,p=0,CYLt,m_dCymax,m_dCymin,aa11[JMNum],bb11[JMNum],A0[JMNum],SumTss=0.0 ,a3=0.0,bb3=0.0,fls[JMNum];
    double  Gdw=0.0,diss=0.0;
    BOOL    BTCHUL=0;
	ReadDataFromFile();

    ////////////////////////////////////////////////////
    diss=(rect.bottom-centerPoint.y*3/2)/(m_IntJM-1);      //画图的高度截面
    Gdw=2 * PI /m_IntPoint;

	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)	
		{  
			t[j]=3.1415926*j/1800;
			pem[i][j]=m_datayzd[j+1+i*m_IntPoint].data;
            DRAWpem[i][j]=m_datayzd[j+1+i*m_IntPoint].data;
			bcondata[j]=((pem[i][j]-2048)*10)/(G1*G2*4096);//每3600个数据进行2-50波滤波，便于用滤波之后的数据进行相应计算
            zz[i]=m_datayzd[j+1+i*m_IntPoint].height;        //读取截面高度数值
		}
		z[m_IntJM-1-i]=i*diss;
		WLS_Filter(5, m_IntPoint, bcondata, acondata);     //调用滤波函数
		for (j=0;j<m_IntPoint;j++)	
		{  
	    	Rr[i][j]=acondata[j];                          //滤波之后的数据
		}
	    a3=0 ,	bb3 = 0,SumTss = 0;
		for (j=0;j<m_IntPoint;j++)	
		{
		     a3 = a3+ Rr[i][j] * cos(j * Gdw);
		     bb3 =bb3 + Rr[i][j] * sin(j * Gdw);
			 SumTss= SumTss + Rr[i][j];
		}
		aa11[i]= 2 * a3/m_IntPoint;
		bb11[i] = 2 * bb3/m_IntPoint  ;                    //此式算出来的是各个截面的最小二乘圆心和半径
		A0[i] = SumTss/m_IntPoint;
	}
	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)	
		{  	
		m_dfls[i][j] = Rr[i][j]-(aa11[i] * cos(j * Gdw) + bb11[i] * sin(j * Gdw)) - A0[i] ; //2-50滤波之后的圆度
		cutE[i][j] = Rr[i][j]-(aa11[i] * cos(j * Gdw) + bb11[i] * sin(j * Gdw)) ;//- A0[i] ; 
		xp[i][j]=cutE[i][j]*cos(j * Gdw);
	    yp[i][j]=cutE[i][j]*sin(j * Gdw);
		}
	}		
	for (i=0;i<m_IntJM;i++)
	{    
		m_dCirMax=m_dfls[i][1];
    	m_dCirMin=m_dfls[i][1];
		for (j=0;j<m_IntPoint;j++)
		{
			if (m_dCirMax<m_dfls[i][j])
			{
				m_dCirMax=m_dfls[i][j];
			}

			if (m_dCirMin>=m_dfls[i][j])
			{
				m_dCirMin=m_dfls[i][j];
			}	 
		}
       fls[i]=m_dCirMax-m_dCirMin;    //各个截面的圆度值
	}
	
   
	/////////////////求取最大最小值便于绘图/////////////////////////////////
    double m_Middle=0.0,m_m_OutIn=0.0,rout=rect.Width()*0.25,rin=rect.Width()*0.15,m_OutIn=0.0,RSLC=200;
	double m_datamin=0.0, m_datamax=0.0;
	m_datamin=pem[0][0];
    m_datamax=pem[0][0];  
	for (i=0;i<m_IntJM;i++)
	{    
		for (j=0;j<m_IntPoint;j++)	
		{  
	       if (m_datamax<pem[i][j])
		   {
			   m_datamax=pem[i][j];
		   }
		   if (m_datamin>pem[i][j])
		   {
			   m_datamin=pem[i][j];
		   }
		}
	}
     m_Middle=(m_datamax+m_datamin)/2;
     m_OutIn=m_datamax-m_datamin;
// 	 for (i=0;i<m_IntJM;i++)   
// 	 {	
// 		 for (j=0;j<m_IntPoint;j++)
// 		 {
// 			 r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*(rout-rin)/m_OutIn+RSLC; //绘制圆度打点时按比例显示
// 			 
// 		 }
// 	}
    ////////////////////////////////////////////////////////////
    //////////以下实现高斯解线性方程组求解圆柱度/////////////////////////////////////////////
    //生成求解矩阵
	double suma11 = 0,suma12 = 0, suma13 = 0,suma14 = 0,suma15 = 0,suma16 = 0,a111 = 0,a122 = 0, a13 = 0,a14 = 0,a15 = 0,a16 = 0;
    double suma22 = 0, suma23 = 0,suma24 = 0,suma25 = 0,suma26 = 0,a211 = 0,a222 = 0, a23 = 0,a24 = 0,a25 = 0,a26 = 0;
    double suma33 = 0,suma34 = 0,suma35 = 0,suma36 = 0,a31 = 0,a32 = 0, a33 = 0,a34 = 0,a35 = 0,a36 = 0;
    double suma44 = 0,suma45 = 0,suma46 = 0,a41 = 0,a42 = 0, a43 = 0,a44 = 0,a45 = 0,a46 = 0;                          
	double suma55 = 0,suma56 = 0,a51 = 0,a52 = 0, a53 = 0,a54 = 0,a55 = 0,a56 = 0;                        
	double  suma66 = 0,a61 = 0,a62 = 0, a63 = 0,a64 = 0,a65 = 0,a66 = 0;                       
    double yyi = m_IntJM * m_IntPoint;
    double sumb1 = 0,sumb2 = 0,sumb3 = 0, sumb4 = 0,sumb5 = 0,sumb6 = 0;
	double BB11=0,BB22=0,BB33=0,BB44=0,BB55=0,BB66=0;
	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)
		{
		suma11 = suma11 + cos(j * Gdw) * cos(j* Gdw);
		suma12 = suma12 + sin(j * Gdw) * cos(j* Gdw);
		suma13 = suma13 + zz[i] * cos(j * Gdw) * cos(j * Gdw);
		suma14 = suma14 + zz[i]  * sin(j * Gdw) * cos(j * Gdw);
		suma15 = suma15 + cos(j * Gdw);
		suma16 = suma16 + zz[i]  * cos(j * Gdw);
        
		suma22 = suma22 + sin(j * Gdw) * sin(j * Gdw);
		suma23 = suma23 + zz[i] * sin(j * Gdw) * cos(j * Gdw);
		suma24 = suma24 + zz[i]  * sin(j * Gdw) * sin(j * Gdw);
		suma25 = suma25 + sin(j * Gdw);
		suma26 = suma26 + zz[i]  * sin(j * Gdw);
        
		suma33 = suma33 + zz[i]  * zz[i]  * cos(j* Gdw) * cos(j * Gdw);
		suma34 = suma34 + zz[i]  * zz[i]  * cos(j * Gdw) * sin(j * Gdw);
		suma35 = suma35 + zz[i]  * cos(j * Gdw);
		suma36 = suma36 + zz[i]  * zz[i]  * cos(j * Gdw);
        
		suma44 = suma44 + zz[i]  * zz[i]  * sin(j* Gdw) * sin(j * Gdw);
		suma45 = suma45 + zz[i] * sin(j * Gdw);
		suma46 = suma46 + zz[i]  * zz[i]  * sin(j* Gdw);
        
        
		suma56 = suma56 + zz[i] ;
        
		suma66 = suma66 + zz[i]  * zz[i] ;
        
		sumb1 = sumb1 +  cutE[i][j] * cos(j * Gdw);
		sumb2 = sumb2 +  cutE[i][j]  * sin(j * Gdw);
		sumb3 = sumb3 +  cutE[i][j]  * zz[i] * cos(j * Gdw);
		sumb4 = sumb4 +  cutE[i][j]  * zz[i] * sin(j * Gdw);
		sumb5 = sumb5 +  cutE[i][j] ;
		sumb6 = sumb6 +  cutE[i][j] * zz[i];
		}
	}
             
   	suma55 = yyi;
	a111 = suma11,a122 = suma12,a13 = suma13,a14 = suma14,a15 = suma15,a16 = suma16;
  	a211 = a122,a222 = suma22,a23 = suma23,a24 = suma24,a25 = suma25,a26 = suma26;
    a31 = a13,a32 = a23,a33 = suma33,a34 = suma34,a35 = suma35,a36 = suma36;
    a41 = a14,a42 = a24,a43 = a34,a44 = suma44,a45 = suma45,a46 = suma46;
   	a51 = a15,a52 = a25,a53 = a35,a54 = a45,a55 = suma55,a56 = suma56;
    a61 = a16,a62 = a26,a63 = a36,a64 = a46,a65 = a56,a66 = suma66;
        
    BB11 = sumb1,BB22 = sumb2,BB33 = sumb3,BB44 = sumb4,BB55= sumb5,BB66 = sumb6;
	//' 矩阵：		
    double AA[6][6]={ {a111, a122, a13, a14, a15, a16},{a211, a222, a23, a24, a25, a26},{a31, a32, a33, a34, a35, a36},{a41, a42, a43, a44, a45, a46},{a51, a52, a53, a54, a55, a56},{a61, a62, a63, a64, a65, a66}};
    double AAB[6]={BB11,BB22,BB33,BB44,BB55,BB66};
    double X0[6]={1,1,1,1,1,1};
    double XA[6]={0,0,0,0,0,0};
    double delx=100;
	int timecalcute=0;

	//以上代码实现线性方程组的构造，AA*XA=AAB
   while (delx >=0.0000000001)
	
   {
	      XA[0]  = (1 / AA[0][0]) * (AAB[0] - (AA[0][1] * X0[1] +  AA[0][2] * X0[2] +   AA[0][3] * X0[3] +   AA[0][4] * X0[4]  +  AA[0][5] * X0[5]));
          XA[1]  = (1 / AA[1][1]) * (AAB[1] -  AA[1][0] * XA[0] - (AA[1][2] * X0[2] +   AA[1][3] * X0[3] +   AA[1][4] * X0[4]  +  AA[1][5] * X0[5]));
          XA[2]  = (1 / AA[2][2]) * (AAB[2] - (AA[2][0] * XA[0] +  AA[2][1] * XA[1]) - (AA[2][3] * X0[3] +   AA[2][4] * X0[4]  +  AA[2][5] * X0[5]));
          XA[3]  = (1 / AA[3][3]) * (AAB[3] - (AA[3][0] * XA[0] +  AA[3][1] * XA[1] +   AA[3][2]*  XA[2]) - (AA[3][4] * X0[4]  +  AA[3][5] * X0[5]));
          XA[4]  = (1 / AA[4][4]) * (AAB[4] - (AA[4][0] * XA[0] +  AA[4][1] * XA[1] +   AA[4][2] * XA[2] +   AA[4][3] * XA[3]) -  AA[4][5] * X0[5]);
          XA[5]  = (1 / AA[5][5]) * (AAB[5] - (AA[5][0] * XA[0] +  AA[5][1] * XA[1] +   AA[5][2] * XA[2] +   AA[5][3] * XA[3]  +  AA[5][4] * XA[4]));
          timecalcute=timecalcute+1;

		  for (i=0;i<5;i++)
		  {  
			  if ( fabs(XA[i + 1] - X0[i + 1]) <= fabs(XA[i] - X0[i]) )
			  {
				  delx = fabs(XA[i] - X0[i]);
			  }
			  else
			  {
				  delx = fabs(XA[i + 1] - X0[i + 1]);
			  } 
		  }		 
		  for (i=0;i<6;i++)
		  {
           X0[i] = XA[i];
		  }
	}
	//' Gauss_Seidel solve X
    //    '  解出已知参数。
	double XX0=0.0,YY0=0.0,ZZ0=0.0,AA0=0.0,BB0=0.0,CC0=0.0,Rc=0.0,Kc=0.0;
   	XX0 = XA[0],YY0= XA[1],ZZ0 = 0,AA0= XA[2],BB0 = XA[3],CC0 = 1,Rc = XA[4],Kc = XA[5];//六个参数值

	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)
		{
			//测量点到理想轴线的距离
	        dis1[i][j] = sqrt( ( ((yp[i][j] - YY0) * CC0 - (zz[i] - ZZ0) * BB0)* ((yp[i][j] - YY0) * CC0 - (zz[i] - ZZ0) * BB0) +((zz[i] - ZZ0) * AA0 - (xp[i][j] - XX0) * CC0)* ((zz[i] - ZZ0) * AA0 - (xp[i][j] - XX0) * CC0)+ ((xp[i][j] - XX0) * BB0 - (yp[i][j]- YY0) * AA0)*((xp[i][j] - XX0) * BB0 - (yp[i][j]- YY0) * AA0)  ) / ( AA0*AA0 + BB0* BB0 + CC0*CC0 ));
	    	xi[i][j] = XX0 +  AA0* zz[i];
	    	yi[i][j] = YY0 + BB0* zz[i];
            //算出的Rij，需要从中减去e和kz的影响。
		    dis1[i][j] = dis1[i][j] - xi[i][j] * cos(j * Gdw) - yi[i][j] * sin(j * Gdw) - Rc - Kc * zz[i];
		}
	}	
    m_dCymin =dis1[1][1];
    m_dCymax =dis1[1][1];
	for (i=0;i<m_IntJM;i++)   
	{	
    	for (j=0;j<m_IntPoint;j++)
		{
		   if(  m_dCymin >= dis1[i][j] )   
		    	m_dCymin= dis1[i][j];
		   if(  m_dCymax<=dis1[i][j] )	
	        	m_dCymax= dis1[i][j];
		}
	}
    m_dCymin=-m_dCymin; 
   	CYLt=m_dCymax +m_dCymin; //圆柱度误差
    m_CYLT.Format("%.2f",CYLt);
    m_CYLP.Format("%.2f",m_dCymax);
    m_CYLV.Format("%.2f",m_dCymin);
    /////////////////以上代码实现圆柱度误差的计算///////////////////////
	double PV=tzd;	 
	if (flagAmpscale==1)
	{
		if (m_ModeChoose==1)
		{
			ratio=m_AmpScale/5;
			
		}
		else if (m_ModeChoose==0)
		{
			if( PV <= 0.15)
				ratio = 200;
			else if( PV <= 0.3)
				ratio = 100;
			else if( PV <= 0.75 )
				ratio = 40 ; 
			else if( PV <= 1.5)
				ratio = 20 ;
			else if( PV <= 3)
				ratio = 10 ;
			else if( PV <= 7.5)
				ratio = 4 ;
			else if( PV <= 15)
				ratio = 2 ;
			else if( PV <= 30)
				ratio = 1 ;
			else if( PV <= 60)
				ratio = 0.5 ;
			else if( PV <= 120)
				ratio = 0.25 ;
			else if( PV <= 240)
				ratio = 0.125 ;
			
			else
				ratio = 0.0635;
			ratio*=1000;
			ratio1=ratio;
			ratio=ratio/5; 			
		}
	}
	else if(flagAmpscale==0)
	{
		
		if( PV <= 0.15)
			ratio = 200;
		else if( PV <= 0.3)
			ratio = 100;
		else if( PV <= 0.75 )
			ratio= 40 ; 
		else if( PV <= 1.5)
			ratio = 20 ;
		else if( PV <= 3)
			ratio = 10 ;
		else if( PV <= 7.5)
			ratio = 4 ;
		else if( PV <= 15)
			ratio = 2 ;
		else if( PV <= 30)
			ratio = 1 ;
		else if( PV <= 60)
			ratio = 0.5 ;
		else if( PV <= 120)
			ratio = 0.25 ;
		else if( PV <= 240)
			ratio = 0.125 ;	
		else
			ratio = 0.0635;
		ratio*=1000;
		ratio1=ratio;
		ratio=ratio/5; 
	}
	
	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)
		{
			//r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*(rout-rin)/m_OutIn*ratio*0.001+RSLC;
			//		r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*ratio*(rout-rin)/m_OutIn+RSLC; //绘制圆度打点时按比例显示
			//r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*ratio*0.014/(rect.Height()*0.8/10)*(rout-rin)/m_OutIn+RSLC; 
	//		r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*(rout-rin)/m_OutIn/30*ratio*0.001+RSLC; 

			r[i][j]=(((CMainFrame*)AfxGetMainWnd())->m_OutIn*((DRAWpem[i][j]-m_Middle))*ratio*0.01*(rout-rin)/(rect.Height()*m_OutIn))+RSLC;///ok
		}
	}

	
	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)
		{
			r[i][j]=0.85*r[i][j];
		}
	}

    /////////////////以下代码实现圆柱立体图形的显示//////////////////////
	C3dPoint TPoint[4],p3;
    CLine    a1,a2,b1,b2;
    int      m_IStep=10;
	double   Rz[3][3],PI=3.1415926;
	CString  m_jiemian, m_heightZ;

	//最小二乘拟合圆心
    C3dPoint POINT[3600];
	double s11=0,s12=0,s13=0,s22=0,s23=0,x0,y0,z0;
    double sumx2=0,sumx=0,sumy2=0,sumy=0,sumxy=0,sumx2y2=0,sumxx2y2=0,sumyx2y2=0;
	for (j=0;j<m_IntPoint;j++)
	{
		POINT[j].x=(r[m_IntJM-1][j])*cos(j * Gdw);//横坐标
		POINT[j].y=(r[m_IntJM-1][j])*sin(j * Gdw);//纵坐标     左上
		POINT[j].z=z[m_IntJM-1];
		sumx2=sumx2+POINT[j].x*POINT[j].x;
		sumx=sumx+POINT[j].x;
		sumy2=sumy2+POINT[j].y*POINT[j].y;
        sumy=sumy+POINT[j].y;
        sumxy=sumxy+POINT[j].x*POINT[j].y;
		sumx2y2=sumx2y2+(POINT[j].x*POINT[j].x+POINT[j].y*POINT[j].y);
		sumxx2y2=sumxx2y2+POINT[j].x*(POINT[j].x*POINT[j].x+POINT[j].y*POINT[j].y);
		sumyx2y2=sumyx2y2+POINT[j].y*(POINT[j].x*POINT[j].x+POINT[j].y*POINT[j].y);
	}
    s11=2*(sumx2-(sumx*sumx/m_IntPoint));
	s12=2*(sumxy-(sumx*sumy/m_IntPoint));
	s13=sumxx2y2-(sumx*sumx2y2)/m_IntPoint;
	s22=2*(sumy2-(sumy*sumy/m_IntPoint));
	s23=sumyx2y2-(sumy*sumx2y2)/m_IntPoint;
    x0=(s12*s23-s13*s22)/(s12*s12-s11*s22);
	y0=(s12*s13-s11*s23)/(s12*s12-s11*s22);
    z0=z[m_IntJM-1];
   ////圆柱按小矩形图绘出//////////////////////////////////
    for (i=0;i<m_IntJM-1;i++)
	{
		for (j=0;j<m_IntPoint-m_IStep;j+=m_IStep)	
		{
				
		        TPoint[0].x=(r[i+1][j])*cos(j * Gdw)-x0;//横坐标
		        TPoint[0].y=(r[i+1][j])*sin(j * Gdw)-y0;//纵坐标     左上
		        TPoint[0].z=z[i+1]-z0;	

		        TPoint[1].x=(r[i][j])*cos(j * Gdw)-x0;//横坐标
		        TPoint[1].y=(r[i][j])*sin(j * Gdw)-y0;//纵坐标 左下     
	            TPoint[1].z=z[i]-z0;
	
				TPoint[2].x=(r[i][j+m_IStep])*cos((j+m_IStep)*Gdw)-x0;//横坐标
				TPoint[2].y=(r[i][j+m_IStep])*sin((j+m_IStep)*Gdw)-y0;//纵坐标   右下
				TPoint[2].z=z[i]-z0;	
		
				TPoint[3].x=(r[i+1][j+m_IStep])*cos((j+m_IStep)*Gdw)-x0;//横坐标
				TPoint[3].y=(r[i+1][j+m_IStep])*sin((j+m_IStep)*Gdw)-y0;//纵坐标   右上    
				TPoint[3].z=z[i+1]-z0;	
             
				p3.x=(r[i][(j+m_IStep)/2])*cos((j+m_IStep)*Gdw/2)-x0;//横坐标
				p3.y=(r[i][(j+m_IStep)/2])*sin((j+m_IStep)*Gdw/2)-y0;//纵坐标    
				p3.z=(z[i]+z[i+1])/2-z0;	

				Rotate(TPoint[0].x,TPoint[0].y,TPoint[0].z);
				Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z); //调用旋转函数直接将坐标转换为旋转之后的坐标
				Rotate(TPoint[2].x,TPoint[2].y,TPoint[2].z);
				Rotate(TPoint[3].x,TPoint[3].y,TPoint[3].z);
				Rotate(p3.x,p3.y,p3.z);	

				/////////////////以下几行代码实现圆柱背面的遮挡///////////////////////////
				double test1=(p3.x-VPOINT_X)*((TPoint[2].y-TPoint[0].y)*(TPoint[3].z-TPoint[1].z)-(TPoint[2].z-TPoint[0].z)*(TPoint[3].y-TPoint[1].y))-(p3.y-VPOINT_Y)*((TPoint[2].x-TPoint[0].x)*(TPoint[3].z-TPoint[1].z)-(TPoint[2].z-TPoint[0].z)*(TPoint[3].x-TPoint[1].x))+(p3.z-VPOINT_Z)*((TPoint[2].x-TPoint[0].x)*(TPoint[3].y-TPoint[1].y)-(TPoint[2].y-TPoint[0].y)*(TPoint[3].x-TPoint[1].x));
				if(test1<0.0)
				{
					if (m_datayzd[j+1+i*m_IntPoint].selected==1) //手动处理选中，变为黄色
					{
						a1.Line(TPoint[1],TPoint[2]);
						a2.Line(TPoint[2], TPoint[3]);
						b1.Line(TPoint[3],TPoint[0]);
						b2.Line(TPoint[0],TPoint[1]);
						
						a1.m_hide=2;
						a2.m_hide=1;
						b1.m_hide=1;
						b2.m_hide=2;
						
						a2.Draw(&memDC,centerPoint);
						b2.Draw(&memDC,centerPoint);
						a1.Draw(&memDC,centerPoint);
						b1.Draw(&memDC,centerPoint);	
					}

			        else  if (m_datayzd[j+1+(i+1)*m_IntPoint].selected==1)
					{
						a1.Line(TPoint[1],TPoint[2]);
						a2.Line(TPoint[2], TPoint[3]);
						b1.Line(TPoint[3],TPoint[0]);
						b2.Line(TPoint[0],TPoint[1]);
						
						a1.m_hide=1;
						a2.m_hide=1;
						b1.m_hide=2;
						b2.m_hide=2;
						
						a2.Draw(&memDC,centerPoint);
						b2.Draw(&memDC,centerPoint);
						a1.Draw(&memDC,centerPoint);
						b1.Draw(&memDC,centerPoint);	
					}
 
					else                            //否则显示蓝色
					{ 
						a1.Line(TPoint[1],TPoint[2]);
						a2.Line(TPoint[2], TPoint[3]); 
						b1.Line(TPoint[3],TPoint[0]);
						b2.Line(TPoint[0],TPoint[1]);
						
						a1.m_hide=1;
						a2.m_hide=1;
						b1.m_hide=1;
						b2.m_hide=1;
						
						a2.Draw(&memDC,centerPoint);
						b2.Draw(&memDC,centerPoint);
						a1.Draw(&memDC,centerPoint);
						b1.Draw(&memDC,centerPoint);	
					}

				}		
		}  
	}

   
   ////补上最后差下的矩形条//////////////////////////////////////
   for (i=0;i<m_IntJM-1;i++)
   {		   
		   TPoint[0].x=(r[i+1][j])*cos(j * Gdw)-x0;//横坐标
		   TPoint[0].y=(r[i+1][j])*sin(j * Gdw)-y0;//纵坐标     左上
		   TPoint[0].z=z[i+1]-z0;	
		   
		   TPoint[1].x=(r[i][j])*cos(j * Gdw)-x0;//横坐标
		   TPoint[1].y=(r[i][j])*sin(j * Gdw)-y0;//纵坐标 左下     
		   TPoint[1].z=z[i]-z0;
		   
		   TPoint[2].x=(r[i][0])*cos((0)*Gdw)-x0;//横坐标
		   TPoint[2].y=(r[i][0])*sin((0)*Gdw)-y0;//纵坐标   右下
		   TPoint[2].z=z[i]-z0;	
		   
		   TPoint[3].x=(r[i+1][0])*cos((0)*Gdw)-x0;//横坐标
		   TPoint[3].y=(r[i+1][0])*sin((0)*Gdw)-y0;//纵坐标   右上    
		   TPoint[3].z=z[i+1]-z0;	
		   
		   p3.x=(r[i][(m_IntPoint+j)/2])*cos((m_IntPoint+j)*Gdw/2)-x0;//横坐标
		   p3.y=(r[i][(m_IntPoint+j)/2])*sin((m_IntPoint+j)*Gdw/2)-y0;//纵坐标    
		   p3.z=(z[i]+z[i+1])/2-z0;	
		   
		   Rotate(TPoint[0].x,TPoint[0].y,TPoint[0].z);
		   Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z); //调用旋转函数直接将坐标转换为旋转之后的坐标
		   Rotate(TPoint[2].x,TPoint[2].y,TPoint[2].z);
		   Rotate(TPoint[3].x,TPoint[3].y,TPoint[3].z);
		   Rotate(p3.x,p3.y,p3.z);	
		   
		   /////////////////以下几行代码实现圆柱背面的遮挡///////////////////////////
		   double test1=(p3.x-VPOINT_X)*((TPoint[2].y-TPoint[0].y)*(TPoint[3].z-TPoint[1].z)-(TPoint[2].z-TPoint[0].z)*(TPoint[3].y-TPoint[1].y))-(p3.y-VPOINT_Y)*((TPoint[2].x-TPoint[0].x)*(TPoint[3].z-TPoint[1].z)-(TPoint[2].z-TPoint[0].z)*(TPoint[3].x-TPoint[1].x))+(p3.z-VPOINT_Z)*((TPoint[2].x-TPoint[0].x)*(TPoint[3].y-TPoint[1].y)-(TPoint[2].y-TPoint[0].y)*(TPoint[3].x-TPoint[1].x));
		   if(test1<0.0)
		   {
			   
			   if (m_datayzd[j+1+i*m_IntPoint].selected==1)
			   {
				   a1.Line(TPoint[1],TPoint[2]);
				   a2.Line(TPoint[2], TPoint[3]);
				   b1.Line(TPoint[3],TPoint[0]);
				   b2.Line(TPoint[0],TPoint[1]);
				   
				   a1.m_hide=2;
				   a2.m_hide=1;
				   b1.m_hide=1;
				   b2.m_hide=2;
				   
			  //  a2.Draw(&memDC,centerPoint);
				   b2.Draw(&memDC,centerPoint);
				   a1.Draw(&memDC,centerPoint);
				   b1.Draw(&memDC,centerPoint);	
			   }
			   
			   else  if (m_datayzd[j+1+(i+1)*m_IntPoint].selected==1)
			   {
				   a1.Line(TPoint[1],TPoint[2]);
				   a2.Line(TPoint[2], TPoint[3]);
				   b1.Line(TPoint[3],TPoint[0]);
				   b2.Line(TPoint[0],TPoint[1]);
				   
				   a1.m_hide=1;
				   a2.m_hide=1;
				   b1.m_hide=2;
				   b2.m_hide=2;
				   
			   //  a2.Draw(&memDC,centerPoint);
				   b2.Draw(&memDC,centerPoint);
				   a1.Draw(&memDC,centerPoint);
				   b1.Draw(&memDC,centerPoint);	
			   }
			   
			   else  
			   {
				   a1.Line(TPoint[1],TPoint[2]);
				   a2.Line(TPoint[2], TPoint[3]);
				   b1.Line(TPoint[3],TPoint[0]);
				   b2.Line(TPoint[0],TPoint[1]);
				   
				   a1.m_hide=1;
				   a2.m_hide=1;
				   b1.m_hide=1;
				   b2.m_hide=1;
				   
		    	// a2.Draw(&memDC,centerPoint);
				   b2.Draw(&memDC,centerPoint);
				   a1.Draw(&memDC,centerPoint);
				   b1.Draw(&memDC,centerPoint);	
			   }

		   }

   }
   ////画出最上面的半圆,最上面的半边圆并没有被遮挡
   for (j=0;j<m_IntPoint-m_IStep;j++)
   {		
	    TPoint[1].x=(r[m_IntJM-1][j])*cos(t[j])-x0;//横坐标
	    TPoint[1].y=(r[m_IntJM-1][j])*sin(t[j])-y0;//纵坐标      
    	TPoint[1].z=z[m_IntJM-1]-z0;
	    Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z);

		TPoint[2].x=(r[m_IntJM-1][j+m_IStep])*cos(t[j+m_IStep])-x0;//横坐标
		TPoint[2].y=(r[m_IntJM-1][j+m_IStep])*sin(t[j+m_IStep])-y0;//纵坐标      
		TPoint[2].z=z[m_IntJM-1]-z0;
				
		Rotate(TPoint[2].x,TPoint[2].y,TPoint[2].z);
				
		a1.Line( TPoint[1],TPoint[2]); 
		if (m_datayzd[j+1+i*m_IntPoint].selected==1)
		{
             a1.m_hide=2;
		}
		else
		{
             a1.m_hide=1;
		}
		
	    a1.Draw(&memDC,centerPoint);		
   }
  ////以下程序用来抽取各个截面信息  
  memDC.SetTextColor(RGB(0,0,0));//红色字体      
  for (i=0;i<m_IntJM;i++)
  {
	  j=3000;
	  m_jiemian.Format("%d",i+1);
	  m_heightZ.Format("%.1f",zz[i]);
	  {		
		  TPoint[1].x=(r[i][j])*cos(j*Gdw);//横坐标
		  TPoint[1].y=(r[i][j])*sin(j*Gdw);//纵坐标 左下     
		  TPoint[1].z=z[i];
		  
		  Z3DRondness[i][j].x=TPoint[1].x;
		  Z3DRondness[i][j].y=TPoint[1].y;
		  Z3DRondness[i][j].z=TPoint[1].z;
		  
		  Z2DRondness[i][j]=Z3DRondness[i][j].Change();
		  
		  XJM[i][j]=rect.left+10;
		  YJM[i][j]=Z2DRondness[i][j].y+centerPoint.y;
		  memDC.TextOut(XJM[i][j],YJM[i][j]-10,"M"+m_jiemian);//在圆柱的左边显示截面数
		  
		  XJM[i][j]=rect.Width()*3/5;
		  YJM[i][j]=Z2DRondness[i][j].y+centerPoint.y;
		  memDC.TextOut(XJM[i][j],YJM[i][j]-10,m_heightZ);  //在圆柱的右边显示截面高度
		  
	  }
  }
  //////////////以上实现圆柱的绘制及旋转实现//////////////////////////////////
}
void CDoCoaxiality::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd *pWndCy; 
	CRect rectCy; 
	CDC *pDCCy;          
	pWndCy = GetDlgItem(IDC_STATIC_Coaxiality);      
	pWndCy->GetClientRect(&rectCy); 
	pWndCy->ClientToScreen(rectCy);       //转换到屏幕坐标,左上角坐标为文本框在屏幕的坐标
	pDCCy = pWndCy->GetDC();
	this->ClientToScreen(&point);          //转换为屏幕坐标
	
	point.x=point.x-rectCy.left;         //把point坐标由相对于屏幕坐标转换为相对于静态框坐标，静态框左上角是(0,0)
	point.y=point.y-rectCy.top;
	double f1=(rectCy.right-rectCy.left)/2,f2= (rectCy.bottom-rectCy.top ) /2;
	
	CPoint centerPoint;
	centerPoint.x=(rectCy.right-rectCy.left)*3/5/2;
	centerPoint.y=(rectCy.bottom-rectCy.top)/8;//就是绘制圆柱的z[0]的中心点。
	
	int  i=0,j=0;
	CString str;

	for (i=0;i<m_IntJM;i++)   
	{
		j=3000;
		XJM[i][j]=rect.left+10;
		YJM[i][j]=Z2DRondness[i][j].y+centerPoint.y;
		if ( point.x>=XJM[i][j] && point.x<=YJM[i][j]+20 &&  point.y>= YJM[i][j]-10 && point.y<=YJM[i][j]+10)
		{
			((CMainFrame*)AfxGetMainWnd())->m_fullJMPath=((CMainFrame*)AfxGetMainWnd())->m_fullPath7;//获取圆柱度的路径
			((CMainFrame*)AfxGetMainWnd())->m_fullJMType=1;    //类型区分
			((CMainFrame*)AfxGetMainWnd())->m_fullJMNum=LenData; //鼠标单击的截面
            ((CMainFrame*)AfxGetMainWnd())->m_SelectJM=i;
			((CMainFrame*)AfxGetMainWnd())->DoJMAnalyse();
			OnPaint();
		}		
	}	
	
	CFormView::OnLButtonDblClk(nFlags, point);
}


void CDoCoaxiality:: WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata)
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


void CDoCoaxiality::SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr)
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
void  CDoCoaxiality::Rotate(double &x, double &y, double &z) 
{
	double xx=x,yy=y,zz=z;
	
	if((int)AngleZ!=0)
	{
		xx=x*cos(AngleZ/180.0*PI)-y*sin(AngleZ/180.0*PI);
		yy=x*sin(AngleZ/180.0*PI)+y*cos(AngleZ/180.0*PI);
		zz=z;
	}	
	x=xx;
	y=yy;
	z=zz;	
}

void CDoCoaxiality::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_editCylinder.GetSafeHwnd())
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
		m_editCylinder.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}
	
}

void CDoCoaxiality::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
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
	m_editCylinder.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
}

void CDoCoaxiality::OnToLeft() 
{
	// TODO: Add your control notification handler code here
	AngleZ+=10;
	OnPaint();
}

void CDoCoaxiality::OnToRight() 
{
	// TODO: Add your control notification handler code here
	AngleZ-=10;
	OnPaint();
}

void CDoCoaxiality::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pActivateView==this)
	{
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(-1,FALSE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(5,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(6,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(12,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(13,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(14,TRUE);
	}
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
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
void CDoCoaxiality::SubQKDataChuli(CString path,int Number, double *Resdata,BOOL GManCuliQkFlag,int JM,int Totaldot)
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
	for ( i=0;i<=Totaldot;i++)
	{	
		fin.read((char*)&m_datayzd[i], sizeof(shuju0)); //读取数据
	}
 
	for (i=0;i<Number;i++)
	{
    	ManDeal[i].data=m_datayzd[i+1+JM*3600].data;
        ManDeal[i].selected=m_datayzd[i+1+JM*3600].selected;
		Soudata[i]=ManDeal[i].data;
	}
	fin.close();  
	
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


void CDoCoaxiality::ReadDataFromFile()
{
	
	std::ifstream fin(((CMainFrame*)AfxGetMainWnd())->m_fullPath7, std::ios::binary);
	//fin.seekg(0);
	fin.read((char*)&m_datayzd[0], sizeof(shuju0)); //读取数据
	m_IntJM=m_datayzd[0].data;
	m_IntPoint=3600;
	LenData=m_IntJM*m_IntPoint;
	BTCHUL=((CMainFrame*)AfxGetMainWnd())->JMCL; //鼠标单击的截面
    int jmbtn=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;
	///////////////读取圆柱数据/////////////////////////////
	for ( int i=0;i<LenData;i++)
	{	
		fin.seekg((i+1)*sizeof(shuju0));
		fin.read((char*)&m_datayzd[i+1], sizeof(shuju0)); //读取数据
	}
	
	fin.seekg((LenData+1)*sizeof(shuju0)/*sizeof(CTime)*/);////////////////////////////////////////////////////sizeof(CTime)
	fin.read((char*)&G1, 8/*sizeof(double)*/);	
	fin.seekg(8+(LenData+1)*sizeof(shuju0));
	fin.read((char*)&G2, 8);
	//读取时间
	fin.read((char*)&m_time,sizeof(CTime));
    fin.close();
}

void CDoCoaxiality::OnPrint() 
{
	// TODO: Add your command handler code here
	CFormView::OnFilePrint();
}

void CDoCoaxiality::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFormView::OnPrepareDC(pDC, pInfo);
	pDC->SetMapMode(MM_ANISOTROPIC);
}

BOOL CDoCoaxiality::OnPreparePrinting(CPrintInfo* pInfo) 
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

void CDoCoaxiality::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
    int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);//X方向一英寸像素的个数,A4纸
    int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);//Y方向一英寸像素的个数
	int xLogPixPerMM=xLogPixPerInch/25.4;//X方向1mm像素的个数
	int yLogPixPerMM=yLogPixPerInch/25.4;//Y方向1mm像素的个数
	m_penScale=xLogPixPerInch/96;//x方向和y方向的m_penScale都一样
	
	//打印框的尺寸为150*250(mm)
	CPoint pt(0,0);//纸张的左上角为00点
	CSize  sz(270*xLogPixPerMM,200*yLogPixPerMM);//sz矩形框的大小，X方向和Y方向像素的总个数
	CRect  tRect(pt,sz);//定义的打印区的矩形框
	rect1.top=tRect.top+25*yLogPixPerMM;
	rect1.right=tRect.right;
	rect1.left=tRect.left+20*xLogPixPerMM;
	rect1.bottom=tRect.bottom-25*yLogPixPerMM;
	
	pOldBmp = NULL;                           // 将旧的位图指针置空	
	memDC.CreateCompatibleDC(pDC);             // 创建内存绘图设备，使内存位图的DC与控件的DC关联
	memBitmap.CreateCompatibleBitmap(pDC,tRect.right,tRect.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap);
    memDC.FillSolidRect(tRect.left,tRect.top,tRect.right,tRect.bottom,RGB(255,255,255));//给矩形框填充白色*/
	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDC.SelectObject(&RectPen);      //笔和字体用之前需要selectobject，用完后需要deleteobject      
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

	double gridleft=(rect1.right-rect1.left)*2/3+rect1.left;
	int gridxnums=1;int gridynums=22;//一列25行
	double dx= ((rect1.right-rect1.left)-gridleft)/gridxnums;//一列的宽度
	double dy=(rect1.bottom-rect1.top)/gridynums;//一行的高度
    CRect gridRect(gridleft,rect1.top,gridleft+dx*gridxnums,rect1.top+dy*gridynums);
	
	memDC.FillSolidRect(gridleft,gridRect.top,rect1.right,dy,RGB(232,232,232));
	memDC.FillSolidRect(gridleft,gridRect.top+dy*5,rect1.right,dy,RGB(232,232,232));//给指定行填充颜色
	memDC.FillSolidRect(gridleft,gridRect.top+dy*13,rect1.right,dy,RGB(232,232,232));
	
	for( int m0=0;m0<=0;m0++) //画出gridxnums条竖线                      
	{
		memDC.MoveTo(gridRect.left+m0*dx,gridRect.bottom);
		memDC.LineTo(gridRect.left+m0*dx,gridRect.top);
		memDC.MoveTo(rect1.right+m0*dx,rect1.bottom);
		memDC.LineTo(rect1.right+m0*dx,rect1.top);
	}
		
	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
	{
		memDC.MoveTo(gridRect.left,gridRect.top+n*dy);
		memDC.LineTo(rect1.right,gridRect.top+n*dy);
	}	


	//DrawCoaxiality();//调用画圆柱的函数,显示图形
    PrintCoaxiality();
	CalCoaxiality();//计算同轴度
    
	memDC.SetBkMode(TRANSPARENT);//去阴影，设置成透明色 
	int meter=4*m_penScale+rect1.top;
	int m1=gridleft+4*m_penScale;
// 	double m2=gridleft+dx/2;
// 	double m3=gridleft+dx-80*m_penScale;

	double m2=gridleft+dx/2;
	double m3=gridleft+dx-50;

	double mid=gridleft+dx/2-30*m_penScale;
	
	if (AngleZ%360>0)
	{
		SeeAngle=AngleZ%360;
	}
	else
	{
		SeeAngle=AngleZ%360;
	}

	m_Seeangle.Format("%d",SeeAngle);	
    memDC.TextOut(mid ,meter,"同轴度测量结果");	
	memDC.TextOut(mid+20*m_penScale,dy*5+meter,"规格要求");
	memDC.TextOut(mid+20*m_penScale,dy*13+meter,"测量参数");	
    memDC.TextOut(m1,dy+meter,"文件名");
	memDC.TextOut(m1,dy*2+meter,"测量时间");
	memDC.TextOut(m1,dy*6+meter,"参考类型");                                       
	memDC.TextOut(m1,dy*7+meter,"滤波器种类");                                              
	memDC.TextOut(m1,dy*8+meter,"滤波范围");    
	memDC.TextOut(m1,dy*9+meter,"截面个数");     
	memDC.TextOut(m1,dy*10+meter,"当前观测角度"); 	
	memDC.TextOut(m1,dy*14+meter,"工艺要求");
	memDC.TextOut(m1,dy*16+meter,"同轴度");
// 	memDC.TextOut(m1,dy*17+meter,"波峰");
// 	memDC.TextOut(m1,dy*18+meter,"波谷");

	CString str1;
	str1=((CMainFrame*)AfxGetMainWnd())->m_fullPath7;
	int num=str1.ReverseFind('\\');
	str1=str1.Right(str1.GetLength()-num-1);
	memDC.TextOut(m2,dy*1+meter,str1);
	str1=m_time.Format("%Y-%m-%d %H:%M");
	memDC.TextOut(m2,dy*2+meter,str1);
	str1.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[5]);
	memDC.TextOut(m2,dy*14+meter,str1);
	memDC.TextOut(m2,dy*15+meter,"  ");
	memDC.TextOut(m2,dy*6+meter,"最小二乘法");
	memDC.TextOut(m2,dy*7+meter,"Gaussian");
	memDC.TextOut(m2,dy*8+meter,"1-50");
	str1.Format("%d",m_IntJM);
	memDC.TextOut(m2,dy*9+meter,str1);
	memDC.TextOut(m3,dy*14+meter,"um");	
	memDC.TextOut(m3,dy*16+meter,"um");
// 	memDC.TextOut(m3,dy*17+meter,"um");
// 	memDC.TextOut(m3,dy*18+meter,"um");
	memDC.SetTextColor(RGB(0,0,0));//红色字体 
	memDC.TextOut(m2,dy*16+meter,m_tzd);
// 	memDC.TextOut(m2,dy*17+meter,m_CYLP);
// 	memDC.TextOut(m2,dy*18+meter,m_CYLV);	
	memDC.TextOut(m2,dy*10+meter,m_Seeangle+"°");	

	pDC->BitBlt(tRect.left,tRect.top,tRect.right,tRect.bottom,&memDC,0,0,SRCCOPY); 
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
    memBitmap.DeleteObject();//释放内存设备
	
	
}

void CDoCoaxiality::PrintCoaxiality()
{
	scale=rect1.Width()/rect.Width();
	CPoint centerPoint=0;
	centerPoint.x=rect1.Width()*3/5/2+rect1.left;
	centerPoint.y=rect1.Height()/8+rect1.top;//就是绘制圆柱的z[0]的中心点。
	memDC.SetBkMode(TRANSPARENT); 
	memDC.TextOut(rect1.Width()*3/5+rect1.left-20*m_penScale,centerPoint.y-30*m_penScale,"Z(mm)");
    memDC.TextOut(rect1.left+5*m_penScale,centerPoint.y-30*m_penScale,"截面");

	CPen CyPe1(PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDC.SelectObject(&CyPe1);  
	memDC.MoveTo(centerPoint.x,centerPoint.y+5*m_penScale);
    memDC.LineTo(centerPoint.x,rect1.top+20*m_penScale);
    CyPe1.DeleteObject();


	//以下代码实现圆柱各个截面上圆度信息的计算和最终圆柱度的计算
	int     i=0,j=0,jmbtn;
	double  dis=0,z[JMNum],zz[JMNum],t[3600],bcondata[3600],acondata[3600],SumTs = 0.0,m_dCirMax,m_dCirMin;
	double  a=0,b=0,l=0,g=0,DR=0,p=0,CYLt,m_dCymax,m_dCymin,aa11[JMNum],bb11[JMNum],A0[JMNum],SumTss=0.0 ,a3=0.0,bb3=0.0,fls[JMNum];
    double  Gdw=0.0,diss=0.0;
    BOOL    BTCHUL=0;
	ReadDataFromFile();

    ////////////////////////////////////////////////////
    diss=((rect1.bottom-rect1.top)-(centerPoint.y-rect1.top)*3/2)/(m_IntJM-1);      //画图的高度截面
    Gdw=2 * PI /m_IntPoint;

	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)	
		{  
			t[j]=3.1415926*j/1800;
			pem[i][j]=m_datayzd[j+1+i*m_IntPoint].data;
            DRAWpem[i][j]=m_datayzd[j+1+i*m_IntPoint].data;
			bcondata[j]=((pem[i][j]-2048)*10)/(G1*G2*4096);//每3600个数据进行2-50波滤波，便于用滤波之后的数据进行相应计算
            zz[i]=m_datayzd[j+1+i*m_IntPoint].height;        //读取截面高度数值
		}
		z[m_IntJM-1-i]=i*diss;
		WLS_Filter(5, m_IntPoint, bcondata, acondata);     //调用滤波函数
		for (j=0;j<m_IntPoint;j++)	
		{  
	    	Rr[i][j]=acondata[j];                          //滤波之后的数据
		}
	    a3=0 ,	bb3 = 0,SumTss = 0;
		for (j=0;j<m_IntPoint;j++)	
		{
		     a3 = a3+ Rr[i][j] * cos(j * Gdw);
		     bb3 =bb3 + Rr[i][j] * sin(j * Gdw);
			 SumTss= SumTss + Rr[i][j];
		}
		aa11[i]= 2 * a3/m_IntPoint;
		bb11[i] = 2 * bb3/m_IntPoint  ;                    //此式算出来的是各个截面的最小二乘圆心和半径
		A0[i] = SumTss/m_IntPoint;
	}
	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)	
		{  	
		m_dfls[i][j] = Rr[i][j]-(aa11[i] * cos(j * Gdw) + bb11[i] * sin(j * Gdw)) - A0[i] ; //2-50滤波之后的圆度
		cutE[i][j] = Rr[i][j]-(aa11[i] * cos(j * Gdw) + bb11[i] * sin(j * Gdw)) ;//- A0[i] ; 
		xp[i][j]=cutE[i][j]*cos(j * Gdw);
	    yp[i][j]=cutE[i][j]*sin(j * Gdw);
		}
	}		
	for (i=0;i<m_IntJM;i++)
	{    
		m_dCirMax=m_dfls[i][1];
    	m_dCirMin=m_dfls[i][1];
		for (j=0;j<m_IntPoint;j++)
		{
			if (m_dCirMax<m_dfls[i][j])
			{
				m_dCirMax=m_dfls[i][j];
			}

			if (m_dCirMin>=m_dfls[i][j])
			{
				m_dCirMin=m_dfls[i][j];
			}	 
		}
       fls[i]=m_dCirMax-m_dCirMin;    //各个截面的圆度值
	}
	
   
	/////////////////求取最大最小值便于绘图/////////////////////////////////
    double m_Middle=0.0,m_m_OutIn=0.0,rout=rect.Width()*0.25,rin=rect.Width()*0.15,m_OutIn=0.0,RSLC=200;
	double m_datamin=0.0, m_datamax=0.0;
	m_datamin=pem[0][0];
    m_datamax=pem[0][0];  
	for (i=0;i<m_IntJM;i++)
	{    
		for (j=0;j<m_IntPoint;j++)	
		{  
	       if (m_datamax<pem[i][j])
		   {
			   m_datamax=pem[i][j];
		   }
		   if (m_datamin>pem[i][j])
		   {
			   m_datamin=pem[i][j];
		   }
		}
	}
     m_Middle=(m_datamax+m_datamin)/2;
     m_OutIn=m_datamax-m_datamin;
	 for (i=0;i<m_IntJM;i++)   
	 {	
		 for (j=0;j<m_IntPoint;j++)
		 {
			 r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*(rout-rin)/m_OutIn+RSLC; //绘制圆度打点时按比例显示
			 
		 }
	}
    ////////////////////////////////////////////////////////////
    //////////以下实现高斯解线性方程组求解圆柱度/////////////////////////////////////////////
    //生成求解矩阵
	double suma11 = 0,suma12 = 0, suma13 = 0,suma14 = 0,suma15 = 0,suma16 = 0,a111 = 0,a122 = 0, a13 = 0,a14 = 0,a15 = 0,a16 = 0;
    double suma22 = 0, suma23 = 0,suma24 = 0,suma25 = 0,suma26 = 0,a211 = 0,a222 = 0, a23 = 0,a24 = 0,a25 = 0,a26 = 0;
    double suma33 = 0,suma34 = 0,suma35 = 0,suma36 = 0,a31 = 0,a32 = 0, a33 = 0,a34 = 0,a35 = 0,a36 = 0;
    double suma44 = 0,suma45 = 0,suma46 = 0,a41 = 0,a42 = 0, a43 = 0,a44 = 0,a45 = 0,a46 = 0;                          
	double suma55 = 0,suma56 = 0,a51 = 0,a52 = 0, a53 = 0,a54 = 0,a55 = 0,a56 = 0;                        
	double  suma66 = 0,a61 = 0,a62 = 0, a63 = 0,a64 = 0,a65 = 0,a66 = 0;                       
    double yyi = m_IntJM * m_IntPoint;
    double sumb1 = 0,sumb2 = 0,sumb3 = 0, sumb4 = 0,sumb5 = 0,sumb6 = 0;
	double BB11=0,BB22=0,BB33=0,BB44=0,BB55=0,BB66=0;
	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)
		{
		suma11 = suma11 + cos(j * Gdw) * cos(j* Gdw);
		suma12 = suma12 + sin(j * Gdw) * cos(j* Gdw);
		suma13 = suma13 + zz[i] * cos(j * Gdw) * cos(j * Gdw);
		suma14 = suma14 + zz[i]  * sin(j * Gdw) * cos(j * Gdw);
		suma15 = suma15 + cos(j * Gdw);
		suma16 = suma16 + zz[i]  * cos(j * Gdw);
        
		suma22 = suma22 + sin(j * Gdw) * sin(j * Gdw);
		suma23 = suma23 + zz[i] * sin(j * Gdw) * cos(j * Gdw);
		suma24 = suma24 + zz[i]  * sin(j * Gdw) * sin(j * Gdw);
		suma25 = suma25 + sin(j * Gdw);
		suma26 = suma26 + zz[i]  * sin(j * Gdw);
        
		suma33 = suma33 + zz[i]  * zz[i]  * cos(j* Gdw) * cos(j * Gdw);
		suma34 = suma34 + zz[i]  * zz[i]  * cos(j * Gdw) * sin(j * Gdw);
		suma35 = suma35 + zz[i]  * cos(j * Gdw);
		suma36 = suma36 + zz[i]  * zz[i]  * cos(j * Gdw);
        
		suma44 = suma44 + zz[i]  * zz[i]  * sin(j* Gdw) * sin(j * Gdw);
		suma45 = suma45 + zz[i] * sin(j * Gdw);
		suma46 = suma46 + zz[i]  * zz[i]  * sin(j* Gdw);
        
        
		suma56 = suma56 + zz[i] ;
        
		suma66 = suma66 + zz[i]  * zz[i] ;
        
		sumb1 = sumb1 +  cutE[i][j] * cos(j * Gdw);
		sumb2 = sumb2 +  cutE[i][j]  * sin(j * Gdw);
		sumb3 = sumb3 +  cutE[i][j]  * zz[i] * cos(j * Gdw);
		sumb4 = sumb4 +  cutE[i][j]  * zz[i] * sin(j * Gdw);
		sumb5 = sumb5 +  cutE[i][j] ;
		sumb6 = sumb6 +  cutE[i][j] * zz[i];
		}
	}
             
   	suma55 = yyi;
	a111 = suma11,a122 = suma12,a13 = suma13,a14 = suma14,a15 = suma15,a16 = suma16;
  	a211 = a122,a222 = suma22,a23 = suma23,a24 = suma24,a25 = suma25,a26 = suma26;
    a31 = a13,a32 = a23,a33 = suma33,a34 = suma34,a35 = suma35,a36 = suma36;
    a41 = a14,a42 = a24,a43 = a34,a44 = suma44,a45 = suma45,a46 = suma46;
   	a51 = a15,a52 = a25,a53 = a35,a54 = a45,a55 = suma55,a56 = suma56;
    a61 = a16,a62 = a26,a63 = a36,a64 = a46,a65 = a56,a66 = suma66;
        
    BB11 = sumb1,BB22 = sumb2,BB33 = sumb3,BB44 = sumb4,BB55= sumb5,BB66 = sumb6;
	//' 矩阵：		
    double AA[6][6]={ {a111, a122, a13, a14, a15, a16},{a211, a222, a23, a24, a25, a26},{a31, a32, a33, a34, a35, a36},{a41, a42, a43, a44, a45, a46},{a51, a52, a53, a54, a55, a56},{a61, a62, a63, a64, a65, a66}};
    double AAB[6]={BB11,BB22,BB33,BB44,BB55,BB66};
    double X0[6]={1,1,1,1,1,1};
    double XA[6]={0,0,0,0,0,0};
    double delx=100;
	int timecalcute=0;

	//以上代码实现线性方程组的构造，AA*XA=AAB
   while (delx >=0.0000000001)
	
   {
	      XA[0]  = (1 / AA[0][0]) * (AAB[0] - (AA[0][1] * X0[1] +  AA[0][2] * X0[2] +   AA[0][3] * X0[3] +   AA[0][4] * X0[4]  +  AA[0][5] * X0[5]));
          XA[1]  = (1 / AA[1][1]) * (AAB[1] -  AA[1][0] * XA[0] - (AA[1][2] * X0[2] +   AA[1][3] * X0[3] +   AA[1][4] * X0[4]  +  AA[1][5] * X0[5]));
          XA[2]  = (1 / AA[2][2]) * (AAB[2] - (AA[2][0] * XA[0] +  AA[2][1] * XA[1]) - (AA[2][3] * X0[3] +   AA[2][4] * X0[4]  +  AA[2][5] * X0[5]));
          XA[3]  = (1 / AA[3][3]) * (AAB[3] - (AA[3][0] * XA[0] +  AA[3][1] * XA[1] +   AA[3][2]*  XA[2]) - (AA[3][4] * X0[4]  +  AA[3][5] * X0[5]));
          XA[4]  = (1 / AA[4][4]) * (AAB[4] - (AA[4][0] * XA[0] +  AA[4][1] * XA[1] +   AA[4][2] * XA[2] +   AA[4][3] * XA[3]) -  AA[4][5] * X0[5]);
          XA[5]  = (1 / AA[5][5]) * (AAB[5] - (AA[5][0] * XA[0] +  AA[5][1] * XA[1] +   AA[5][2] * XA[2] +   AA[5][3] * XA[3]  +  AA[5][4] * XA[4]));
          timecalcute=timecalcute+1;

		  for (i=0;i<5;i++)
		  {  
			  if ( fabs(XA[i + 1] - X0[i + 1]) <= fabs(XA[i] - X0[i]) )
			  {
				  delx = fabs(XA[i] - X0[i]);
			  }
			  else
			  {
				  delx = fabs(XA[i + 1] - X0[i + 1]);
			  } 
		  }		 
		  for (i=0;i<6;i++)
		  {
           X0[i] = XA[i];
		  }
	}
	//' Gauss_Seidel solve X
    //    '  解出已知参数。
	double XX0=0.0,YY0=0.0,ZZ0=0.0,AA0=0.0,BB0=0.0,CC0=0.0,Rc=0.0,Kc=0.0;
   	XX0 = XA[0],YY0= XA[1],ZZ0 = 0,AA0= XA[2],BB0 = XA[3],CC0 = 1,Rc = XA[4],Kc = XA[5];//六个参数值

	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)
		{
			//测量点到理想轴线的距离
	        dis1[i][j] = sqrt( ( ((yp[i][j] - YY0) * CC0 - (zz[i] - ZZ0) * BB0)* ((yp[i][j] - YY0) * CC0 - (zz[i] - ZZ0) * BB0) +((zz[i] - ZZ0) * AA0 - (xp[i][j] - XX0) * CC0)* ((zz[i] - ZZ0) * AA0 - (xp[i][j] - XX0) * CC0)+ ((xp[i][j] - XX0) * BB0 - (yp[i][j]- YY0) * AA0)*((xp[i][j] - XX0) * BB0 - (yp[i][j]- YY0) * AA0)  ) / ( AA0*AA0 + BB0* BB0 + CC0*CC0 ));
	    	xi[i][j] = XX0 +  AA0* zz[i];
	    	yi[i][j] = YY0 + BB0* zz[i];
            //算出的Rij，需要从中减去e和kz的影响。
		    dis1[i][j] = dis1[i][j] - xi[i][j] * cos(j * Gdw) - yi[i][j] * sin(j * Gdw) - Rc - Kc * zz[i];
		}
	}	
    m_dCymin =dis1[1][1];
    m_dCymax =dis1[1][1];
	for (i=0;i<m_IntJM;i++)   
	{	
    	for (j=0;j<m_IntPoint;j++)
		{
		   if(  m_dCymin >= dis1[i][j] )   
		    	m_dCymin= dis1[i][j];
		   if(  m_dCymax<=dis1[i][j] )	
	        	m_dCymax= dis1[i][j];
		}
	}
    m_dCymin=-m_dCymin; 
   	CYLt=m_dCymax +m_dCymin; //圆柱度误差
    m_CYLT.Format("%.2f",CYLt);
    m_CYLP.Format("%.2f",m_dCymax);
    m_CYLV.Format("%.2f",m_dCymin);
    /////////////////以上代码实现圆柱度误差的计算///////////////////////
	double PV=tzd;	 
	if (flagAmpscale==1)
	{
		if (m_ModeChoose==1)
		{
			ratio=m_AmpScale/5;
			
		}
		else if (m_ModeChoose==0)
		{
			if( PV <= 0.15)
				ratio = 200;
			else if( PV <= 0.3)
				ratio = 100;
			else if( PV <= 0.75 )
				ratio = 40 ; 
			else if( PV <= 1.5)
				ratio = 20 ;
			else if( PV <= 3)
				ratio = 10 ;
			else if( PV <= 7.5)
				ratio = 4 ;
			else if( PV <= 15)
				ratio = 2 ;
			else if( PV <= 30)
				ratio = 1 ;
			else if( PV <= 60)
				ratio = 0.5 ;
			else if( PV <= 120)
				ratio = 0.25 ;
			else if( PV <= 240)
				ratio = 0.125 ;
			
			else
				ratio = 0.0635;
			ratio*=1000;
			ratio1=ratio;
			ratio=ratio/5; 			
		}
	}
	else if(flagAmpscale==0)
	{
		
		if( PV <= 0.15)
			ratio = 200;
		else if( PV <= 0.3)
			ratio = 100;
		else if( PV <= 0.75 )
			ratio= 40 ; 
		else if( PV <= 1.5)
			ratio = 20 ;
		else if( PV <= 3)
			ratio = 10 ;
		else if( PV <= 7.5)
			ratio = 4 ;
		else if( PV <= 15)
			ratio = 2 ;
		else if( PV <= 30)
			ratio = 1 ;
		else if( PV <= 60)
			ratio = 0.5 ;
		else if( PV <= 120)
			ratio = 0.25 ;
		else if( PV <= 240)
			ratio = 0.125 ;	
		else
			ratio = 0.0635;
		ratio*=1000;
		ratio1=ratio;
		ratio=ratio/5; 
	}
	
	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)
		{
			//		r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*ratio*(rout-rin)/m_OutIn+RSLC; //绘制圆度打点时按比例显示
			//r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*ratio*0.014/(rect.Height()*0.8/10)*(rout-rin)/m_OutIn+RSLC; 
		//	r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*ratio*0.01/(rect.Height()*6/10)*(rout-rin)/m_OutIn+RSLC; 

			r[i][j]=(((CMainFrame*)AfxGetMainWnd())->m_OutIn*((DRAWpem[i][j]-m_Middle))*ratio*0.01*(rout-rin)/(rect.Height()*m_OutIn))+RSLC;///ok
		}
	}
		
	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)
		{
			r[i][j]=1.5*r[i][j];
		}
	}
    /////////////////以下代码实现圆柱立体图形的显示//////////////////////
	C3dPoint TPoint[4],p3;
    CLine    a1,a2,b1,b2;
    int      m_IStep=10;
	double   Rz[3][3],PI=3.1415926;
	CString  m_jiemian, m_heightZ;
    //选转矩阵
//     Rz[0][0]=cos(AngleZ/180.0*PI);  
// 	Rz[0][1]=sin(AngleZ/180.0*PI),    
// 	Rz[0][2]=0;
// 
//     Rz[1][0]=-sin(AngleZ/180.0*PI);  
// 	Rz[1][1]=cos(AngleZ/180.0*PI) ,      
// 	Rz[1][2]=0;
// 
//     Rz[2][0]=0;                   
//     Rz[2][1]=0,                            
// 	Rz[2][2]=1;
	C3dPoint POINT[3600];
	double s11=0,s12=0,s13=0,s22=0,s23=0,x0,y0,z0;
    double sumx2=0,sumx=0,sumy2=0,sumy=0,sumxy=0,sumx2y2=0,sumxx2y2=0,sumyx2y2=0;
	for (j=0;j<m_IntPoint;j++)
	{
		POINT[j].x=(r[m_IntJM-1][j])*cos(j * Gdw);//横坐标
		POINT[j].y=(r[m_IntJM-1][j])*sin(j * Gdw);//纵坐标     左上
		POINT[j].z=z[m_IntJM-1];
		sumx2=sumx2+POINT[j].x*POINT[j].x;
		sumx=sumx+POINT[j].x;
		sumy2=sumy2+POINT[j].y*POINT[j].y;
        sumy=sumy+POINT[j].y;
        sumxy=sumxy+POINT[j].x*POINT[j].y;
		sumx2y2=sumx2y2+(POINT[j].x*POINT[j].x+POINT[j].y*POINT[j].y);
		sumxx2y2=sumxx2y2+POINT[j].x*(POINT[j].x*POINT[j].x+POINT[j].y*POINT[j].y);
		sumyx2y2=sumyx2y2+POINT[j].y*(POINT[j].x*POINT[j].x+POINT[j].y*POINT[j].y);
	}
    s11=2*(sumx2-(sumx*sumx/m_IntPoint));
	s12=2*(sumxy-(sumx*sumy/m_IntPoint));
	s13=sumxx2y2-(sumx*sumx2y2)/m_IntPoint;
	s22=2*(sumy2-(sumy*sumy/m_IntPoint));
	s23=sumyx2y2-(sumy*sumx2y2)/m_IntPoint;
    x0=(s12*s23-s13*s22)/(s12*s12-s11*s22);
	y0=(s12*s13-s11*s23)/(s12*s12-s11*s22);
    z0=z[m_IntJM-1];
   ////圆柱按小矩形图绘出//////////////////////////////////
    for (i=0;i<m_IntJM-1;i++)
	{
		for (j=0;j<m_IntPoint-m_IStep;j+=m_IStep)	
		{
				
		        TPoint[0].x=(r[i+1][j])*cos(j * Gdw)-x0;//横坐标
		        TPoint[0].y=(r[i+1][j])*sin(j * Gdw)-y0;//纵坐标     左上
		        TPoint[0].z=z[i+1]-z0;	

		        TPoint[1].x=(r[i][j])*cos(j * Gdw)-x0;//横坐标
		        TPoint[1].y=(r[i][j])*sin(j * Gdw)-y0;//纵坐标 左下     
	            TPoint[1].z=z[i]-z0;
	
				TPoint[2].x=(r[i][j+m_IStep])*cos((j+m_IStep)*Gdw)-x0;//横坐标
				TPoint[2].y=(r[i][j+m_IStep])*sin((j+m_IStep)*Gdw)-y0;//纵坐标   右下
				TPoint[2].z=z[i]-z0;	
		
				TPoint[3].x=(r[i+1][j+m_IStep])*cos((j+m_IStep)*Gdw)-x0;//横坐标
				TPoint[3].y=(r[i+1][j+m_IStep])*sin((j+m_IStep)*Gdw)-y0;//纵坐标   右上    
				TPoint[3].z=z[i+1]-z0;	
             
				p3.x=(r[i][(j+m_IStep)/2])*cos((j+m_IStep)*Gdw/2)-x0;//横坐标
				p3.y=(r[i][(j+m_IStep)/2])*sin((j+m_IStep)*Gdw/2)-y0;//纵坐标    
				p3.z=(z[i]+z[i+1])/2-z0;	

				Rotate(TPoint[0].x,TPoint[0].y,TPoint[0].z);
				Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z); //调用旋转函数直接将坐标转换为旋转之后的坐标
				Rotate(TPoint[2].x,TPoint[2].y,TPoint[2].z);
				Rotate(TPoint[3].x,TPoint[3].y,TPoint[3].z);
				Rotate(p3.x,p3.y,p3.z);	

				/////////////////以下几行代码实现圆柱背面的遮挡///////////////////////////
				double test1=(p3.x-VPOINT_X)*((TPoint[2].y-TPoint[0].y)*(TPoint[3].z-TPoint[1].z)-(TPoint[2].z-TPoint[0].z)*(TPoint[3].y-TPoint[1].y))-(p3.y-VPOINT_Y)*((TPoint[2].x-TPoint[0].x)*(TPoint[3].z-TPoint[1].z)-(TPoint[2].z-TPoint[0].z)*(TPoint[3].x-TPoint[1].x))+(p3.z-VPOINT_Z)*((TPoint[2].x-TPoint[0].x)*(TPoint[3].y-TPoint[1].y)-(TPoint[2].y-TPoint[0].y)*(TPoint[3].x-TPoint[1].x));
				if(test1<0.0)
				{
					TPoint[0].x=TPoint[0].x*scale;
					TPoint[0].y=TPoint[0].y*scale;				
					TPoint[1].x=TPoint[1].x*scale;
					TPoint[1].y=TPoint[1].y*scale;
					TPoint[2].x=TPoint[2].x*scale;
					TPoint[2].y=TPoint[2].y*scale;					
					TPoint[3].x=TPoint[3].x*scale;
					TPoint[3].y=TPoint[3].y*scale;
					a1.a=1*m_penScale;
					a1.b=2*m_penScale;
					a2.a=1*m_penScale;
					a2.b=2*m_penScale;
					b1.a=1*m_penScale;
					b1.b=2*m_penScale;
					b2.a=1*m_penScale;
					b2.b=2*m_penScale;
					
					if (m_datayzd[j+1+i*m_IntPoint].selected==1) //手动处理选中，变为黄色
					{
						a1.Line(TPoint[1],TPoint[2]);
						a2.Line(TPoint[2], TPoint[3]);
						b1.Line(TPoint[3],TPoint[0]);
						b2.Line(TPoint[0],TPoint[1]);
						
						a1.m_hide=2;
						a2.m_hide=1;
						b1.m_hide=1;
						b2.m_hide=2;
						
						
						a2.Draw(&memDC,centerPoint);
						b2.Draw(&memDC,centerPoint);
						a1.Draw(&memDC,centerPoint);
						b1.Draw(&memDC,centerPoint);	
					}

			        else  if (m_datayzd[j+1+(i+1)*m_IntPoint].selected==1)
					{
						a1.Line(TPoint[1],TPoint[2]);
						a2.Line(TPoint[2], TPoint[3]);
						b1.Line(TPoint[3],TPoint[0]);
						b2.Line(TPoint[0],TPoint[1]);
						
						a1.m_hide=1;
						a2.m_hide=1;
						b1.m_hide=2;
						b2.m_hide=2;
						
						a2.Draw(&memDC,centerPoint);
						b2.Draw(&memDC,centerPoint);
						a1.Draw(&memDC,centerPoint);
						b1.Draw(&memDC,centerPoint);	
					}
 
					else                            //否则显示蓝色
					{ 
						a1.Line(TPoint[1],TPoint[2]);
						a2.Line(TPoint[2], TPoint[3]); 
						b1.Line(TPoint[3],TPoint[0]);
						b2.Line(TPoint[0],TPoint[1]);
						
						a1.m_hide=1;
						a2.m_hide=1;
						b1.m_hide=1;
						b2.m_hide=1;
						
						a2.Draw(&memDC,centerPoint);
						b2.Draw(&memDC,centerPoint);
						a1.Draw(&memDC,centerPoint);
						b1.Draw(&memDC,centerPoint);	
					}

				}		
		}  
	}

   
   ////补上最后差下的矩形条//////////////////////////////////////
   for (i=0;i<m_IntJM-1;i++)
   {		   
		   TPoint[0].x=(r[i+1][j])*cos(j * Gdw)-x0;//横坐标
		   TPoint[0].y=(r[i+1][j])*sin(j * Gdw)-y0;//纵坐标     左上
		   TPoint[0].z=z[i+1]-z0;	
		   
		   TPoint[1].x=(r[i][j])*cos(j * Gdw)-x0;//横坐标
		   TPoint[1].y=(r[i][j])*sin(j * Gdw)-y0;//纵坐标 左下     
		   TPoint[1].z=z[i]-z0;
		   
		   TPoint[2].x=(r[i][0])*cos((0)*Gdw)-x0;//横坐标
		   TPoint[2].y=(r[i][0])*sin((0)*Gdw)-y0;//纵坐标   右下
		   TPoint[2].z=z[i]-z0;	
		   
		   TPoint[3].x=(r[i+1][0])*cos((0)*Gdw)-x0;//横坐标
		   TPoint[3].y=(r[i+1][0])*sin((0)*Gdw)-y0;//纵坐标   右上    
		   TPoint[3].z=z[i+1]-z0;	
		   
		   p3.x=(r[i][(m_IntPoint+j)/2])*cos((m_IntPoint+j)*Gdw/2)-x0;//横坐标
		   p3.y=(r[i][(m_IntPoint+j)/2])*sin((m_IntPoint+j)*Gdw/2)-y0;//纵坐标    
		   p3.z=(z[i]+z[i+1])/2-z0;	
		   
		   Rotate(TPoint[0].x,TPoint[0].y,TPoint[0].z);
		   Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z); //调用旋转函数直接将坐标转换为旋转之后的坐标
		   Rotate(TPoint[2].x,TPoint[2].y,TPoint[2].z);
		   Rotate(TPoint[3].x,TPoint[3].y,TPoint[3].z);
		   Rotate(p3.x,p3.y,p3.z);	
		   
		   /////////////////以下几行代码实现圆柱背面的遮挡///////////////////////////
		   double test1=(p3.x-VPOINT_X)*((TPoint[2].y-TPoint[0].y)*(TPoint[3].z-TPoint[1].z)-(TPoint[2].z-TPoint[0].z)*(TPoint[3].y-TPoint[1].y))-(p3.y-VPOINT_Y)*((TPoint[2].x-TPoint[0].x)*(TPoint[3].z-TPoint[1].z)-(TPoint[2].z-TPoint[0].z)*(TPoint[3].x-TPoint[1].x))+(p3.z-VPOINT_Z)*((TPoint[2].x-TPoint[0].x)*(TPoint[3].y-TPoint[1].y)-(TPoint[2].y-TPoint[0].y)*(TPoint[3].x-TPoint[1].x));
		   if(test1<0.0)
		   {
			   
			   TPoint[0].x=TPoint[0].x*scale;
			   TPoint[0].y=TPoint[0].y*scale;				
			   TPoint[1].x=TPoint[1].x*scale;
			   TPoint[1].y=TPoint[1].y*scale;
			   TPoint[2].x=TPoint[2].x*scale;
			   TPoint[2].y=TPoint[2].y*scale;					
			   TPoint[3].x=TPoint[3].x*scale;
			   TPoint[3].y=TPoint[3].y*scale;
			   a1.a=1*m_penScale;
			   a1.b=2*m_penScale;
			   a2.a=1*m_penScale;
			   a2.b=2*m_penScale;
			   b1.a=1*m_penScale;
			   b1.b=2*m_penScale;
			   b2.a=1*m_penScale;
			   b2.b=2*m_penScale;
			   if (m_datayzd[j+1+i*m_IntPoint].selected==1)
			   {
				   a1.Line(TPoint[1],TPoint[2]);
				   a2.Line(TPoint[2], TPoint[3]);
				   b1.Line(TPoint[3],TPoint[0]);
				   b2.Line(TPoint[0],TPoint[1]);
				   
				   a1.m_hide=2;
				   a2.m_hide=1;
				   b1.m_hide=1;
				   b2.m_hide=2;
				   
			  //  a2.Draw(&memDC,centerPoint);
				   b2.Draw(&memDC,centerPoint);
				   a1.Draw(&memDC,centerPoint);
				   b1.Draw(&memDC,centerPoint);	
			   }
			   
			   else  if (m_datayzd[j+1+(i+1)*m_IntPoint].selected==1)
			   {
				   a1.Line(TPoint[1],TPoint[2]);
				   a2.Line(TPoint[2], TPoint[3]);
				   b1.Line(TPoint[3],TPoint[0]);
				   b2.Line(TPoint[0],TPoint[1]);
				   
				   a1.m_hide=1;
				   a2.m_hide=1;
				   b1.m_hide=2;
				   b2.m_hide=2;
				   
			   //  a2.Draw(&memDC,centerPoint);
				   b2.Draw(&memDC,centerPoint);
				   a1.Draw(&memDC,centerPoint);
				   b1.Draw(&memDC,centerPoint);	
			   }
			   
			   else  
			   {
				   a1.Line(TPoint[1],TPoint[2]);
				   a2.Line(TPoint[2], TPoint[3]);
				   b1.Line(TPoint[3],TPoint[0]);
				   b2.Line(TPoint[0],TPoint[1]);
				   
				   a1.m_hide=1;
				   a2.m_hide=1;
				   b1.m_hide=1;
				   b2.m_hide=1;
				   
		    	// a2.Draw(&memDC,centerPoint);
				   b2.Draw(&memDC,centerPoint);
				   a1.Draw(&memDC,centerPoint);
				   b1.Draw(&memDC,centerPoint);	
			   }

		   }

   }
   ////画出最上面的半圆,最上面的半边圆并没有被遮挡
   for (j=0;j<m_IntPoint-m_IStep;j++)
   {		
	    TPoint[1].x=(r[m_IntJM-1][j])*cos(t[j])-x0;//横坐标
	    TPoint[1].y=(r[m_IntJM-1][j])*sin(t[j])-y0;//纵坐标      
    	TPoint[1].z=z[m_IntJM-1]-z0;
	    Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z);

		TPoint[2].x=(r[m_IntJM-1][j+m_IStep])*cos(t[j+m_IStep])-x0;//横坐标
		TPoint[2].y=(r[m_IntJM-1][j+m_IStep])*sin(t[j+m_IStep])-y0;//纵坐标      
		TPoint[2].z=z[m_IntJM-1]-z0;
				
		Rotate(TPoint[2].x,TPoint[2].y,TPoint[2].z);			
		TPoint[1].x=TPoint[1].x*scale;
		TPoint[1].y=TPoint[1].y*scale;
		TPoint[2].x=TPoint[2].x*scale;
		TPoint[2].y=TPoint[2].y*scale;
		a1.b=2*m_penScale;
		a1.a=1*m_penScale;
	
		a1.Line( TPoint[1],TPoint[2]); 
		if (m_datayzd[j+1+i*m_IntPoint].selected==1)
		{
             a1.m_hide=2;
		}
		else
		{
             a1.m_hide=1;
		}
		
	    a1.Draw(&memDC,centerPoint);		
   }
  ////以下程序用来抽取各个截面信息  
  memDC.SetTextColor(RGB(0,0,0));//红色字体      
  for (i=0;i<m_IntJM;i++)
  {
	  j=3000;
	  memDC.SetBkMode(TRANSPARENT); 
	  m_jiemian.Format("%d",i+1);
	  m_heightZ.Format("%.1f",zz[i]);
	  {		
		  TPoint[1].x=(r[i][j])*cos(j*Gdw);//横坐标
		  TPoint[1].y=(r[i][j])*sin(j*Gdw);//纵坐标 左下     
		  TPoint[1].z=z[i];
		  
		  Z3DRondness[i][j].x=TPoint[1].x;
		  Z3DRondness[i][j].y=TPoint[1].y;
		  Z3DRondness[i][j].z=TPoint[1].z;
		  
		  Z2DRondness[i][j]=Z3DRondness[i][j].Change();
		  
		  XJM[i][j]=rect1.left+10*m_penScale;
		  YJM[i][j]=Z2DRondness[i][j].y+centerPoint.y;
		  memDC.TextOut(XJM[i][j],YJM[i][j]-10,"M"+m_jiemian);//在圆柱的左边显示截面数
		  
		  XJM[i][j]=rect1.Width()*3/5+rect1.left;
		  YJM[i][j]=Z2DRondness[i][j].y+centerPoint.y;
		  memDC.TextOut(XJM[i][j],YJM[i][j]-10,m_heightZ);  //在圆柱的右边显示截面高度
		  
	  }
}
}

void CDoCoaxiality::OnBtntbegin() 
{
	// TODO: Add your command handler code here
	SetTimer(1,300,NULL);
}

void CDoCoaxiality::OnBtntstop() 
{
	// TODO: Add your command handler code here
	KillTimer(1);
}

void CDoCoaxiality::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	AngleZ+=5;
	OnPaint();
	CFormView::OnTimer(nIDEvent);
}

void CDoCoaxiality::OnAmplifyScale() 
{
	// TODO: Add your command handler code here
	CAmpScale dlg;
	dlg.m_ModeChoose=m_ModeChoose;
	dlg.m_DefaultAmpscale=ratio1;
	dlg.m_AmpScale=m_AmpScale;
	UpdateData(false);
	if (IDOK==dlg.DoModal())
	{
		m_ModeChoose=dlg.m_ModeChoose;
		m_AmpScale=dlg.m_AmpScale;
		flagAmpscale=1;
	}
	OnPaint();
	
}

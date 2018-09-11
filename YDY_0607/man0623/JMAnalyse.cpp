// JMAnalyse.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "JMAnalyse.h"
#include "MainFrm.h"
#include "const.h"
#include "math.h"
#include "PropertyDlg.h"
#include <fstream>
#include "DlgextendCircle.h"
#include "Dlgfrequency1.h"
#include "AmpScale.h"


using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#define PI  3.1415926
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJMAnalyse

IMPLEMENT_DYNCREATE(CJMAnalyse, CFormView)

CJMAnalyse::CJMAnalyse()
	: CFormView(CJMAnalyse::IDD)
{
	//{{AFX_DATA_INIT(CJMAnalyse)
	//}}AFX_DATA_INIT
    ratio1=0;
	flagAmpscale=0;
	m_AmpScale=1;
	m_ModeChoose=-1;
	ratio=0;
	GG1=1;
 	GG2=1;
	FlagMove=0;
	m_Flagcircle=0;
	FilterMode=5;
	m_strlvbo="2-50";
	m_strMethod="最小二乘法";
	m_bIsEnable=FALSE;
	m_BOOLSegmentprocess=0;
	CirEvalue=0;
	
	m_BOOLSegmentprocess=0;
	FlagFrequency=0;
	FlagBogao=0;
    BtnChuliDwon=0;
	m_Wa="";	//波纹度显示
	m_Wc="";	//波纹度显
	m_Wp="";	//波纹度显
	m_Wv="";	//波纹度显示
	m_Wt="";	//波纹度显
	m_Wq="";	//波纹度显
    m_Wwm="";	//波纹度显
	memset(m_BWD,0,sizeof(m_BWD)); 
	m_bIsAutoQK=((CMainFrame*)AfxGetMainWnd())->m_bAutoQK;
	
}

CJMAnalyse::~CJMAnalyse()
{
}

void CJMAnalyse::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJMAnalyse)
	DDX_Control(pDX, IDC_JManalyse, m_JManalyse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJMAnalyse, CFormView)
	//{{AFX_MSG_MAP(CJMAnalyse)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BTNCHULI, OnBtnchuli)
	ON_COMMAND(ID_BTNENABLE, OnBtnenable)
	ON_COMMAND(ID_BTNRESETDEAL, OnBtnresetdeal)
	ON_COMMAND(ID_BTNFENDUANCHULI, OnBtnfenduanchuli)
	ON_COMMAND(ID_BTNYUANDUCHULI, OnBtnyuanduchuli)
	ON_COMMAND(ID_BTNDELETE, OnBtndelete)
	ON_COMMAND(ID_BTNBGFX, OnBtnbgfx)
	ON_COMMAND(ID_BTNPPFX, OnBtnppfx)
	ON_WM_SIZE()
	ON_COMMAND(ID_Print, OnPrint)
	ON_COMMAND(ID_BTNDISABLE,OnBtnenable)
	ON_COMMAND(ID_AmplifyScale, OnAmplifyScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJMAnalyse diagnostics

#ifdef _DEBUG
void CJMAnalyse::AssertValid() const
{
	CFormView::AssertValid();
}

void CJMAnalyse::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJMAnalyse message handlers

void CJMAnalyse::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->DestroyVIEW(((CMainFrame*)AfxGetMainWnd())->m_DoJMAnalyse);
	((CMainFrame*)AfxGetMainWnd())->m_DoJMAnalyse=NULL;
	((CMainFrame*)AfxGetMainWnd())->Desktop();
}
void CJMAnalyse::canshu()
{
	FilterMode=((CMainFrame*)AfxGetMainWnd())->FilterMode;
	CirEvalue=((CMainFrame*)AfxGetMainWnd())->CirEvalue;
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
}
void CJMAnalyse::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	canshu();
	m_bIsEnable=TRUE;
	
	if (m_JManalyse.GetSafeHwnd())
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
		m_JManalyse.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}		
}

void CJMAnalyse::DrawJMofYZD()
{
	////读取文件并绘图///
	int    i;
	double datas[3600],drealx[3600],drealy[3600],theta=0,datacir[3600];
    double dRmax=0.0,dRmin=0.0,m_datamax=0.0,m_datamin=0.0;

    LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//对应圆柱所有的点数
    m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//鼠标单击选中的截面
	pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
 
	std::ifstream fin(pathJM, std::ios::binary);
   	for ( i=0;i<=LenDataJM;i++)
	{	
		fin.read((char*)&m_dataJM[i], sizeof(shuju0)); //读取数据
	}
	fin.read((char*)&GG1,sizeof(double));
	fin.read((char*)&GG2,sizeof(double));
	fin.read((char*)&m_time,sizeof(CTime));
    fin.close();

  
	//定义后面将要用到的变量
    double dY0= rectJM.Height()/2+rectJM.top,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5*1/2+rectJM.left;
	CString strcodinate;
	//rin为0圆，RSLC为2018圆，rout为4096圆
	int x1,y1,x2,y2;
	double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	dw=2*PI/3600;

	//绘制底色圆环带
    CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //绘制黄色圆环带 
    memDCJM.SelectObject(&penRing); 
	for(th=0;th<PI*2;th+=dw)
	{
		x1=dX0-(int)rin*cos(th);
		y1=dY0-(int)rin*sin(th);
		x2=dX0-(int)rout*cos(th);
		y2=dY0-(int)rout*sin(th);
		memDCJM.MoveTo(x1,y1);
		memDCJM.LineTo(x2,y2);	 
	}	 
	penRing.DeleteObject();	

	CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //绘制圆环变紫色带 
    memDCJM.SelectObject(&ping); 
    for (i=0;i<3600;i++)
	{
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{
			x1=dX0-(int)rin*cos(i*dw-PI);
			y1=dY0-(int)rin*sin(i*dw-PI);
			x2=dX0-(int)rout*cos(i*dw-PI);
			y2=dY0-(int)rout*sin(i*dw-PI);
			memDCJM.MoveTo(x1,y1);
			memDCJM.LineTo(x2,y2);
		}		
	}	
    ping.DeleteObject();
   	//----------构造动态圆环---------
	if (flagmanchuli==1)
	{	   
        m_IndexStart=alpha1/dw;
		m_IndexEnd=alpha2/dw;	
		if (FlagMove%2==0)
		{
			DynamicDrawCircleJM(m_IndexStart,m_IndexEnd);			
		}
		else  
		{      
			if ( 6.2814-alpha2>6.2814-alpha1)
			{		
				DynamicDrawCircleJM(m_IndexStart,3599);	
                DynamicDrawCircleJM(0,m_IndexEnd);
			}
			else if ( 6.2814-alpha1>6.2814-alpha2)
			{
				DynamicDrawCircleJM(m_IndexStart,0);	
                DynamicDrawCircleJM(3599,m_IndexEnd);				
			}			
		}
	}
	
	//----------------------以上代码实现灵活的选取-----------
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));     //创建空画刷，防止遮挡内
	CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//选择画刷 
	//double Rmincir=dX0/2-100;

    double Rmincir=rin*5/12;
	CPen pencir;
	pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
    memDCJM.SelectObject(&pencir); 
    memDCJM.Ellipse(dX0-RSLC,dY0-RSLC,dX0+RSLC,dY0+RSLC);//绘制基圆(2048)
	pencir.DeleteObject();
	
	CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	memDCJM.SelectObject(&RoutORin);               
    memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//绘制圆环内圆
    memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//绘制圆环外圆
    RoutORin.DeleteObject();
   
	///////////////////////////////////////////////////////////////////
	///////////////////////绘制坐标轴//////////////////////////////////
	double EverystrcodX=(rout)/10,EverystrcodY=EverystrcodX;
   
	CPen pen1 (PS_DOT,1*m_penScale,RGB(125,125,125));
	memDCJM.SelectObject(&pen1); 
	memDCJM.MoveTo(dX0-EverystrcodX*7,dY0-EverystrcodX*7);
    memDCJM.LineTo(dX0+EverystrcodX*7,dY0+EverystrcodX*7);
	memDCJM.MoveTo(dX0-EverystrcodX*7,dY0+EverystrcodX*7);
    memDCJM.LineTo(dX0+EverystrcodX*7,dY0-EverystrcodX*7);
	pen1.DeleteObject();

	CPen penCoordinate (PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&penCoordinate); 
    memDCJM.MoveTo(dX0-EverystrcodX*10,dY0);
    memDCJM.LineTo(dX0+EverystrcodX*10,dY0);//绘制x轴
    memDCJM.TextOut(dX0+(rout+dright-dX0)/2,dY0-EverystrcodY/2,"0°");
    memDCJM.TextOut(rectJM.left,dY0-EverystrcodY/2,"180°");
    memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
    memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //绘制y轴
    memDCJM.TextOut(dX0-EverystrcodX/2,dY0+EverystrcodY*11,"270°");
    memDCJM.TextOut(dX0-EverystrcodX/2,dY0-EverystrcodY*11.5,"90°");
	memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135°");
    memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315°");
	memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45°");
	memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225°");
		  	  
    for(i=0; i<10; i++)
	{
		strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //绘制X正轴刻度
  	    memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
	    memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	}	
    for( i=0; i<10; i++)
	{
	    strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //绘制X负轴刻度
	    memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
	    memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	}
    for( i=0; i<10; i++)      //写Y正轴刻度值
	{
	    strcodinate.Format("%.2f", dY0-i*EverystrcodY);
	    memDCJM.MoveTo(dX0-4*m_penScale, dY0-i*EverystrcodY);
	    memDCJM.LineTo(dX0+4*m_penScale, dY0-i*EverystrcodY);	
	}
	for( i=0; i<10; i++)  
	{
	    strcodinate.Format("%.2f", dY0-i*EverystrcodY);
	    memDCJM.MoveTo(dX0-4*m_penScale, dY0+i*EverystrcodY);
	    memDCJM.LineTo(dX0+4*m_penScale, dY0+i*EverystrcodY);
	}
    penCoordinate.DeleteObject();
	  ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    //第几个截面参数是传递过来的///////////////////截面参数是M;
	for (i=0;i<3600;i++)	
	{  
		fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		m_CirCal[i]=fpdata[i];    //计算圆度误差转换位移公式		
	}	
	////////////////////////////////////////////////////////////////////////////////
    //手动处理后的数据进行调用函数计算	
	for(i=0;i<3600;i++)		
	{ 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //计算圆度误差转换位移公式	
	}		
	DrawFilter (FilterMode,datacir,dataafterfilter);//调用滤波函数，滤波之后的数据反映在界面绘制上
	//////////////////////////////////////////////////
	//////////////求出绘图轮廓的最大值和最小值//////////////
	m_datamin=dataafterfilter[0];
	m_datamax=dataafterfilter[0];
	for (i=0;i<3600;i++)	
	{  
		if (m_datamax<dataafterfilter[i])
		{
			m_datamax=dataafterfilter[i];
		}
		if (m_datamin>dataafterfilter[i])
		{
			m_datamin=dataafterfilter[i];
		}
	}
    m_Middle=(m_datamax+m_datamin)/2;
    m_OutIn=m_datamax-m_datamin;
    //////////////////////////////////////////////////////////  
	//////////////////////算出轮廓的横、纵坐标///////////////////////////////
	m_endposition=360;
	   m_startposition=0;
	   double m_aveangle=3600/360;
	   double m_endpoint=m_aveangle*m_endposition;
	   double m_startpoint=m_aveangle*m_startposition;
	   double m_spiltavenum;
	   m_spiltavenum=(m_endpoint-m_startpoint)/1;  
	   for (int j=0;j<1;j++)
	   {	
		   m_maxsplit[j]=0;
		   m_minsplit[j]=0;
		   
		   for (i=m_startpoint+j* m_spiltavenum; i< m_startpoint+(j+1)* m_spiltavenum;  i++)
		   {
			   
			   
			   if (m_maxsplit[j]<=dataafterfilter[i])
			   {
				   m_maxsplit[j]=dataafterfilter[i];
			   }
			   
			   if (m_minsplit[j]>=dataafterfilter[i])
			   {
				   m_minsplit[j]=dataafterfilter[i];
				   
			   }
			   
			   m_PV[j]=fabs(m_maxsplit[j])+fabs(m_minsplit[j]);		
		   }
		   
	   }
	double PV=m_PV[0];	    
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
		
	for(i=0;i<3600;i++)		
	{ 
		datas[i]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(dataafterfilter[i]-m_Middle)*ratio*0.2/(rectJM.Height()*0.4/10)+RSLC;
		drealx[i]=datas[i]*cos(i*dw)+dX0;
		drealy[i]=datas[i]*sin(i*dw)+dY0;//实际轮廓的横、纵坐标(相对于二乘圆的)

	}	
	///////////////////////////////////////////////////////
    m_Intstep=5;//间隔点数连线
	CPen penreal;
	penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));    
	CPen pendeal;
	pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));    
	
	for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	{ 
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{  
		   memDCJM.SelectObject(&pendeal);
		   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//绿色曲线表示手动处理区域
		   memDCJM.MoveTo(drealx[i], drealy[i]);
		   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);	
		
		}
		else
		{
			memDCJM.SelectObject(&penreal);
			memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//蓝色曲线表示实际轮廓
			memDCJM.MoveTo(drealx[i], drealy[i]);
			memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
		}
	}
	if(i>=3600-m_Intstep)
	{ 
		for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		{
	       if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			{   
			    memDCJM.SelectObject(&pendeal);
			    memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//绿色曲线表示实际轮廓
		    	memDCJM.MoveTo(drealx[i], drealy[i]);
			    memDCJM.LineTo(drealx[0], drealy[0]);	
			}
			else
			{
				memDCJM.SelectObject(&penreal);
				memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//蓝色曲线表示实际轮廓
				memDCJM.MoveTo(drealx[i], drealy[i]);
				memDCJM.LineTo(drealx[0], drealy[0]);
			}
		}
	}
	penreal.DeleteObject();
    pendeal.DeleteObject();
	
	//-----------------绘制围绕一圈的小黑三角形---------------------------------
// 	double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
// 	CPen penblack(PS_SOLID, 1*m_penScale, RGB(0, 0,0));
// 	CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
// 	CBrush brushblack(RGB(0, 0, 0));
//     memDCJM.SelectObject(&brushblack);
// 	CPoint pts[3];
// 	double tr=2 * 3.1415926/36;// 每一次采样对应的角度间隔，弧度
// 	double wzd=asin(6/m_maxRTriangle); //每次三角形的底边两点相对于定点的旋转角度
// 	
// 	for (i=0;i<36;i++)
// 	{
// 		memDCJM.SelectObject(&penblack);
// 		pts[0].x = m_minrTriangle*cos(i*tr)+dX0;
// 		pts[0].y = m_minrTriangle*sin(i*tr)+dY0;
// 		
// 		pts[1].x = m_maxRTriangle*cos(i*tr-wzd)+dX0;
// 		pts[1].y = m_maxRTriangle*sin(i*tr-wzd)+dY0;
// 		
// 		pts[2].x = m_maxRTriangle*cos(i*tr+wzd)+dX0;
// 		pts[2].y = m_maxRTriangle*sin(i*tr+wzd)+dY0;
// 		
//    	    memDCJM.Polygon(pts, 3);
//         penblack.DeleteObject();
//         if (i%9!=0)
//         {
// 			memDCJM.SelectObject(&pengrey);
// 			memDCJM.MoveTo(rin*cos(i*tr)+dX0,rin*sin(i*tr)+dY0);
// 			memDCJM.LineTo(rout*cos(i*tr)+dX0,rout*sin(i*tr)+dY0);
//             pengrey.DeleteObject();
//         }
//         
// 	}
//     brushblack.DeleteObject();	
//     penblack.DeleteObject();
//     brushblack.DeleteObject();



	double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	CPen penblack(PS_SOLID, 1*m_penScale, RGB(0,0,0));
	CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	CBrush brushblack(RGB(0, 0, 0));
    memDCJM.SelectObject(&brushblack);
	CPoint pts[3];
	double tr=2 * 3.1415926/36;// 每一次采样对应的角度间隔，弧度
	double wzd=asin(6*m_penScale/m_maxRTriangle); //每次三角形的底边两点相对于定点的旋转角度
	
	for (i=0;i<36;i++)
	{
		memDCJM.SelectObject(&penblack);
		pts[0].x = m_minrTriangle*cos(i*tr)+dX0;
		pts[0].y = m_minrTriangle*sin(i*tr)+dY0;
		
		pts[1].x = m_maxRTriangle*cos(i*tr-wzd)+dX0;
		pts[1].y = m_maxRTriangle*sin(i*tr-wzd)+dY0;
		
		pts[2].x = m_maxRTriangle*cos(i*tr+wzd)+dX0;
		pts[2].y = m_maxRTriangle*sin(i*tr+wzd)+dY0;
		
   	    memDCJM.Polygon(pts, 3);
        penblack.DeleteObject();
		
		if (i%9!=0)
		{
			memDCJM.SelectObject(&pengrey);
			memDCJM.MoveTo(rin*cos(i*tr)+dX0,rin*sin(i*tr)+dY0);
			memDCJM.LineTo(rout*cos(i*tr)+dX0,rout*sin(i*tr)+dY0);
            pengrey.DeleteObject();
		}
        
	}
    brushblack.DeleteObject();
	penblack.DeleteObject();
    brushblack.DeleteObject();
	//图形显示标注说明
	CString m_SelectJM,m_TotalJM;
    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);
	
	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"截面总数:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"当前截面:");
	
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+30*m_penScale,m_TotalJM);
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+10*m_penScale,m_SelectJM);


}

void CJMAnalyse::OnPaint() 
{
	if(m_bIsAutoQK!=((CMainFrame*)AfxGetMainWnd())->m_bAutoQK)
	{
		m_bIsAutoQK=((CMainFrame*)AfxGetMainWnd())->m_bAutoQK;
		OnBtnresetdeal();	
	}
	else
	{
		if(((CMainFrame*)AfxGetMainWnd())->m_bAutoQK)
		{
			DrawingCleanAndResetJM(pathJM,0);
			flagmanchuli=0;
		}
		CPaintDC dc(this); 
		canshu();
		CRect rectFill;
		GetClientRect(rectFill);
		dc.FillSolidRect(rectFill,RGB(255,255,255));  //设置为白色背景 
		
		pWndJM = GetDlgItem(IDC_JManalyse);      // 获得对话框上的picture的窗口句柄
		pWndJM->GetClientRect(&rectJM);             // 获取绘制坐标的文本框
		pDCJM = pWndJM->GetDC();                     // 获得对话框上的picture的设备指针
		pOldBmpJM = NULL;                           // 将旧的位图指针置空
		int a=rectJM.Width();                                        
		memDCJM.CreateCompatibleDC(pDCJM);             // 创建内存绘图设备，使内存位图的DC与控件的DC关联
		memBitmapJM.CreateCompatibleBitmap(pDCJM,rectJM.right,rectJM.bottom);
		pOldBmpJM = memDCJM.SelectObject(&memBitmapJM);
		memDCJM.FillSolidRect(rectJM.left,rectJM.top,rectJM.right,rectJM.bottom,RGB(255,255,255));//给矩形框填充白色

		double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.right*3/5,dbottom=rectJM.bottom,dX0=dright/2;
		CPen RectPen(PS_SOLID,1,RGB(0,0,0));
		memDCJM.SelectObject(&RectPen);               
		memDCJM.Rectangle(rectJM.left,rectJM.top,rectJM.right,rectJM.bottom); //静态框加上 颜色 边框
		RectPen.DeleteObject();

		CFont   font; 
		font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
			DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
		CFont*   pOldFont=(CFont*)memDCJM.SelectObject(&font); 
		m_penScale=1;


	   ((CMainFrame*)AfxGetMainWnd())->JMCL=BtnChuliDwon; //鼠标单击的截面

	   LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//对应圆柱所有的点数
	   m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//鼠标单击选中的截面
	   pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;

    
		ReadDataFromFile();
		if(m_BOOLSegmentprocess==0  &&  FlagFrequency==0 )
		{	
				SubQKDataChuli(pathJM,m_LBtnJM,3600,!((CMainFrame*)AfxGetMainWnd())->m_bAutoQK,m_CirCal, Resdata,m_IndexStart,m_IndexEnd);
				if (CirEvalue==0)
				{
					DrawJMofYZD();
					SubAnaData (FilterMode, Resdata,GResult,GG1,GG2);	//圆度
					dRONT=GResult[1];
					SubAnaData(1,  Resdata,GResult,GG1,GG2);    //1
					dEcc=GResult[1]/2;  //偏心
					dEccPos=GResult[3];  //偏心角

					m_strFilterMode.Format("%d",FilterMode);
					m_strdRONT.Format("%.3f",dRONT); //将数据结果转换成字符串的形式，便于显示在表格中
					m_strdEcc.Format("%.2f",dEcc);
					m_strdEccPos.Format("%.2f",dEccPos);
					//显示波纹度
					m_Wa.Format("%.2f",m_BWD[0]); //将数据结果转换成字符串的形式，便于显示在表格中
					m_Wc.Format("%.2f",m_BWD[1]);
					m_Wp.Format("%.2f",m_BWD[2]);
					m_Wv.Format("%.2f",m_BWD[3]); //将数据结果转换成字符串的形式，便于显示在表格中
					m_Wt.Format("%.2f",m_BWD[4]);
					m_Wq.Format("%.2f",m_BWD[5]);
 					m_Wwm.Format("%.2f",m_BWD[6]);
						
				}
				else if (CirEvalue==1)
				{
					DrawCircleMZC();
					MZCyuandu(Resdata);
				}        
				
				else if (CirEvalue==2)
				{
					DrawCircleMCC();
					MCCyuandu(Resdata);
				}    
				
				else if (CirEvalue==3)
				{
					DrawCircleMIC();
					MICyuandu(Resdata);
				}
	  		
			if (FlagBogao==0)
			{
				DrawGride1();
					
			}	
			if (FlagBogao==1)
			{
				DrawBaogao();
				DrawGride1();			
			}
		}
		if(m_BOOLSegmentprocess==1 &&  FlagFrequency==0 )
		{
			DrawGrid2();
			Segmentationprocess();
		}	
		if(m_BOOLSegmentprocess==0  && FlagFrequency==1 )
		{
			DrawFrequency();
			DrawGrid3Frequency();  
		}  
		pDCJM->BitBlt(rectJM.left,rectJM.top,rectJM.right,rectJM.bottom,&memDCJM,0,0,SRCCOPY); //把已经绘好的图显示在制定位置上
		memDCJM.SelectObject(pOldBmpJM);
		memDCJM.DeleteDC();
		memBitmapJM.DeleteObject();//释放内存设备
	}
}

void CJMAnalyse::DynamicDrawCircleJM( int startPosition, int endPosition)
{	
	//定义后面将要用到的变量
	double dY0= rectJM.Height()/2,dright=rectJM.right*3/5,dX0=dright/2;//rin为0圆，RSLC为2018圆，rout为4096圆
	int x1,y1,x2,y2,i;
	double rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	dw= 2 * PI/3600;// 每一次采样对应的角度间隔，弧度nTriangle.DeleteObject();
	
	CPen ping1(PS_SOLID,2,RGB(250,200,238));   //绘制圆环变色带 
	memDCJM.SelectObject(&ping1); 	
	if ( endPosition>startPosition) 	
	{
		for (i=0;i<3600;i++)
		{		
			if ((i<=endPosition)&&(i>= startPosition))
			{
				x1=dX0-(int)rin*cos(i*dw-PI);
				y1=dY0-(int)rin*sin(i*dw-PI);
				x2=dX0-(int)rout*cos(i*dw-PI);
				y2=dY0-(int)rout*sin(i*dw-PI);
				memDCJM.MoveTo(x1,y1);
				memDCJM.LineTo(x2,y2);
			}
		}
	}
	else
	{
		for (i=0;i<3600;i++)
		{
			if ((i>=endPosition)&&(i<=startPosition))
			{
				x1=dX0-(int)rin*cos(i*dw-PI);
				y1=dY0-(int)rin*sin(i*dw-PI);
				x2=dX0-(int)rout*cos(i*dw-PI);
				y2=dY0-(int)rout*sin(i*dw-PI);
				memDCJM.MoveTo(x1,y1);
				memDCJM.LineTo(x2,y2);
			}
		}
	}		
	ping1.DeleteObject();
}

/*函数功能：当手动处理不合理数据时，相应点做变色处理
并且保存下来
*/
void CJMAnalyse::ChangeValueOfSelectJM(CString path,int startPosition, int endPosition, BOOL isSelected)
{
	
		shuju0 ChangeDate[36001];
		std::ifstream fin(path, std::ios::binary);
		int i;
		if (endPosition>startPosition)                       //顺势针旋转
		{	
			for (i=0;i<=LenDataJM;i++)
			{
				fin.read((char*)&ChangeDate[i],sizeof(shuju0));
			}
			fin.read((char*)&GG1,sizeof(double));
			fin.read((char*)&GG2,sizeof(double));
			fin.read((char*)&m_time,sizeof(CTime));
			fin.close();
			
			std::ofstream fout(path, std::ios::binary);
			for (i=0;i<3600;i++)
			{
				if ((i<=endPosition)&&(i>=startPosition))
				{
					ChangeDate[i+1+m_LBtnJM*3600].selected=isSelected;
				}	
			}
		   for (i=0;i<=LenDataJM;i++)
		   {
			   fout.write((char*)&ChangeDate[i], sizeof(shuju0));
		   }
		   fout.write((char*)&GG1,sizeof(double));
		   fout.write((char*)&GG2,sizeof(double));
		   fout.write((char*)&m_time,sizeof(CTime));
		   fout.close();
		}	
		else  //逆时针正常旋转
		{
			for (i=0;i<=LenDataJM;i++)
			{
				fin.read((char*)&ChangeDate[i],sizeof(shuju0));
			}
			fin.read((char*)&GG1,sizeof(double));
			fin.read((char*)&GG2,sizeof(double));
			fin.read((char*)&m_time,sizeof(CTime));
			fin.close();
			
			std::ofstream fout(path, std::ios::binary);
			for (i=0;i<3600;i++)
			{
				
				if ((i>=endPosition)&&(i<=startPosition))
				{
					ChangeDate[i+1+m_LBtnJM*3600].selected=isSelected;
				}
				
			}
			for (i=0;i<=LenDataJM;i++)
			{
				fout.write((char*)&ChangeDate[i], sizeof(shuju0));
			}
			fout.write((char*)&GG1,sizeof(double));
			fout.write((char*)&GG2,sizeof(double));
			fout.write((char*)&m_time,sizeof(CTime));
			fout.close();
		}	
}

/*  撤销手动删除数据
   调用函数的时候，.select=0;撤销之前的手动操作

*/
void CJMAnalyse::DrawingCleanAndResetJM(CString path, BOOL isSelected)
{
	//读出数据
	shuju0 ChangeDate[36001];
	std::ifstream fin(path, std::ios::binary);
	int i;
	for (i=0;i<=LenDataJM;i++)
	{
		fin.read((char*)&ChangeDate[i],sizeof(shuju0));
	}
	fin.read((char*)&GG1,sizeof(double));
	fin.read((char*)&GG2,sizeof(double));
	fin.read((char*)&m_time,sizeof(CTime));
	fin.close();
	//写入改变的数据
	std::ofstream fout(path, std::ios::binary);
	for (i=0;i<3600;i++)
	{
	    ChangeDate[i+1+m_LBtnJM*3600].selected=isSelected;	
	}
	for (i=0;i<=LenDataJM;i++)
	{			
		fout.write((char*)&ChangeDate[i], sizeof(shuju0));
	}
	fout.write((char*)&GG1,sizeof(double));
	fout.write((char*)&GG2,sizeof(double));
	fout.write((char*)&m_time,sizeof(CTime));
	fout.close();
}
/*
函数功能：删除测量数据块中的部分数据
函数参数：
		CString path			: 文件路径
		int NumOfCircle			: 删除的数据是第几个界面的数据， 1表示第一个界面
		BOOL isSaveTheFormer	: 是否保存原有数据：FALSE: 不保存 THRU :保存
返回参数：int error     
	0   : 表示无错
	1   : NumOfCircle<1
	2   : 界面位置大于最大的界面位置
	3   : 删除某个界面后文件的界面个数小于2
*/
int CJMAnalyse::DeletePartOfFile(CString path, int NumOfCircle,BOOL isSaveTheFormer)										   
{
	shuju0 measureData[3601];
	int intLength=0;
	int numofcircle=0;
	//如果删除的界面位置小于1，返回错误代码1
	if (NumOfCircle<1)
	{
		return 1;
	}
	std::ifstream fin(path,std::ios::binary);
	fin.read((char*)&measureData[intLength], sizeof(shuju0));
	intLength++;
	//如果删除的界面位置大于最大的界面位置，返回错误代码2
	if (NumOfCircle>measureData[0].data)
	{
		return 2;
	}
	//如果删除某个界面后文件的界面个数小于2，则返回错误代码3
	if ((measureData[0].data-1)<2)
	{
		return 3;
	}
	else
	{
		measureData[0].data--;
	}
	fin.close();

	int intPos=path.ReverseFind('.');
	CString szExt=path.Right(path.GetLength()-intPos);
 	CString newPath=path.Left(intPos)+"_Copy"+szExt;
	CopyFile((LPCSTR)path,(LPCSTR)newPath,FALSE);		
	DeleteFile((LPCSTR)path);
	//写入界面个数值
	std::ofstream fout(path, std::ios::binary);
	fout.write((char*)&measureData[0], sizeof(shuju0));
	std::ifstream fin2(newPath,std::ios::binary);
	numofcircle=1;
	fin2.read((char*)&measureData[intLength], sizeof(shuju0));
	while (measureData[0].data!=numofcircle)
	{
		fin2.read((char*)&measureData[intLength], sizeof(shuju0));
		if (numofcircle!=NumOfCircle)
		{					
			fout.seekp(0,ios::end);
			fout.write((char*)&measureData[intLength], sizeof(shuju0));	
		}	
		intLength++;
		if (intLength>3600)
		{
			intLength=1;
			numofcircle++;
		}
	}
	fin2.read((char*)&GG1,sizeof(double));
	fin2.read((char*)&GG2,sizeof(double));
	fin2.read((char*)&m_time,sizeof(CTime));
	fin2.close();

	fout.write((char*)&GG1,sizeof(double));
	fout.write((char*)&GG2,sizeof(double));
	fout.write((char*)&m_time,sizeof(CTime));
	fout.close();
	if (!isSaveTheFormer)
	{
		DeleteFile((LPCSTR)newPath);
	}
	return 0;	
}


/*函数功能：
 ---- 根据选择的率波段实现圆度信息的计算
 ---- 选择对应的波段的滤波函数
*/
void CJMAnalyse::SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr)
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
		   BWDANA(TsH);
			break;
   case 9:// '滤除17-100次谐波
			WLS_Filter(9, 3600, TsQ, TsH);
			//'6阶巴特沃斯滤波器 TsQ(i) to TsH(i)
			BWDANA(TsH);
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



void CJMAnalyse::DrawFilter (int  FilterMode ,double *pMem,double *drawdata)
{
	double TsQ[3600],TsH[3600],a1=0.0,b1=0.0;
    double SumTs=0.0 ,SumTcos=0.0, SumTsin=0.0, SumT2cos=0.0, SumT2sin=0.0 ;
    double dw=0.0  ,no=0.0   ,PVA=0.0, PVB=0.0, PVB0=0.0, A0=0.0 , A1=0.0, A2=0.0, B1=0.0 ,B2=0.0,D=0.0 ,D1=0.0 , D2=0.0,DispR=0.0;
    double U00=0.0 , U10=0.0 , U20=0.0 ,Zc1=0.0, Zc2=0.0 , Temp1=0.0;
    int ScanT=0 , TempK=0, M=0 , k=0, L=0, j=0, NV2=0, NM1=0,FTR=0 , FTI=0, FPI=0,FLE=0, FLE1=0 ,FUR=0 , FUR1=0,i=0; 
    double FUI=0.0 , FUI1=0.0 , FWR=0.0 ,FWI=0.0;

	for( i = 0;i< 3600 ;i++)
	{
       TsQ[i] = pMem[i];
	}
    dw = 2 * 3.1415926 / 3600.;// '每一次采样对应的角度间隔，弧度
	switch (FilterMode)
	 {
	case 0 ://'不滤波
	   for( i = 0;i<3600 ;i++)
	   {
           drawdata[i] = TsQ[i];
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
       drawdata[i] = A1 * cos(dw * i) + B1 * sin(dw * i);
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
		   drawdata[i] = TsH[i] - A0;
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
			  drawdata[i] = TsH[i] - A0 - A1 * cos(dw * i) - B1 * sin(dw * i);
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
			   drawdata[i] = TsH[i] - A0 - A1 * cos(dw * i) - B1 * sin(dw * i);
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
			   drawdata[i] = TsH[i] - A0 - a1 * cos(dw * i) - b1 * sin(dw * i);
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
			   drawdata[i] = TsH[i] - A0 - A1 * cos(dw * i) - B1 * sin(dw * i);
		   }
		   break;
   case 7:// '滤除15-500次谐波
		   WLS_Filter(7, 3600, TsQ, TsH);
		   for( i = 0;i<3600;i++)
		   {
			   drawdata[i] = TsH[i];
		   }
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
			   drawdata[i] = TsH[i] - A0 - A1 * cos(dw * i) - B1 * sin(dw * i)- A2 * cos(2 * dw * i) - B2 * sin(2 * dw * i);
		   }
		  break;
   case 9:// '滤除17-100次谐波
		   WLS_Filter(9, 3600, TsQ, TsH);
		   for( i = 0;i<3600;i++)
		   {
			   drawdata[i] = TsH[i];
		   }
		 //'6阶巴特沃斯滤波器 TsQ(i) to TsH(i)
			break;
	}
}

/*
函数功能：
滤波断的选择，进行滤波
*/
void CJMAnalyse:: WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata)
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


void CJMAnalyse::OnLButtonDown(UINT nFlags, CPoint point) 
{
			////////////////////////////////// 圆度鼠标响应显示
	if (m_BOOLSegmentprocess==0  && FlagFrequency==0 )
	{	
		CWnd *pWnd2;
		CDC  *pDC;                 // 控件的屏幕绘图设备指针
		pWnd2=GetDlgItem(IDC_JManalyse);     //获取静态框的指针
		pDC=pWnd2->GetDC();
		CRect rect_ctr;
		this->ClientToScreen(&point);          //转换为屏幕坐标
		pWnd2->GetClientRect(&rect_ctr);       //获得文本框矩形,左上角坐标(0,0)   
		pWnd2->ClientToScreen(rect_ctr);       //转换到屏幕坐标,左上角坐标为文本框在屏幕的坐标
		
		point.x=point.x-rect_ctr.left;         //把point
		point.y=point.y-rect_ctr.top;
		double f1=(rect_ctr.right-rect_ctr.left)*3/5,f2= (rect_ctr.bottom-rect_ctr.top )/2;
		double dY0= (rect_ctr.bottom-rect_ctr.top)/2,dleft=rect_ctr.left,dtop=rect_ctr.top,dright=(rect_ctr.right-rect_ctr.left)*3/5,
			dbottom=rect_ctr.bottom,dX0=dright/2;
		CString strcodinate;	
		//rin为0圆，RSLC为2018圆，rout为4096圆 
		double x1,y1,x2,y2;
		double th=0,rout=(rect_ctr.bottom-rect_ctr.top)*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5;

		if (th=atan2(point.y-dY0,point.x-dX0))
		{
			x1=rin*cos(th);
			y1=rin*sin(th);
			x2=rout*cos(th);
			y2=rout*sin(th);
			if( abs(point.x-dX0)<abs(x1) ||  abs(point.x-dX0)>abs(x2)	|| abs(point.y-dY0)>abs(y2) || abs(point.y-dY0)<abs(y1))
			{
				
			}
		else  
		{
       		m_bDraw=TRUE;             //准备好开始绘图
	    	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS ));
            flagmanchuli=1;	
		}
		}
  		m_zancunfinish=m_zancunOrigin=m_ptOrigin=m_ptEnd=point;	//保存当前点
 
	}

    //////////////////////////////////////// 频谱鼠标响应显示

    if(m_BOOLSegmentprocess==0  && FlagFrequency==1 )
	{
		BoolButtondown=1;
		CWnd *pWnd2;
		CDC  *pDC;                             // 控件的屏幕绘图设备指针
		pWnd2=GetDlgItem(IDC_JManalyse);     //获取静态框的指针
		pDC=pWnd2->GetDC();
		CRect rect_ctr;
		this->ClientToScreen(&point);          //转换为屏幕坐标
		pWnd2->GetClientRect(&rect_ctr);       //获得文本框矩形,左上角坐标(0,0)   
		pWnd2->ClientToScreen(rect_ctr);       //转换到屏幕坐标,左上角坐标为文本框在屏幕的坐标
		
		point.x=point.x-rect_ctr.left;         //把point
		point.y=point.y-rect_ctr.top;

		double fw1=3*rect_ctr.Width()/5,f1=rect_ctr.Width(),f2=rect_ctr.Height();                                                 	                             
	    double fw2=rect_ctr.Width()/30;
		double fh=rect_ctr.Height()/2;
	    double fh1=rect_ctr.Height()/4;
		double fh2=rect_ctr.Height()/30;

		CString str;
		CString str1;                                           	                             
        int m_Intendstart=m_Intend-m_Intstart;
        double pointStart=rect_ctr.left-fw1-fw2*2;                 //坐标起始点
        double pointEnd=fw2;
 		double m_smallavescale=(fw1-fw2*3)/m_Intendstart;
		if( (point.x)<fw2 ||  (point.x>fw1-fw2*2+m_smallavescale)	|| (point.y)>rect_ctr.Height() || (point.y)<0 )
			;
		else  
		{
			int i;
	        CPen newPen;         
	        newPen.CreatePen(PS_SOLID,1,RGB(255,0,255));
            pDC->SelectObject(&newPen); 
            
			//----------数据写入字体及大小
			CFont   font; 
			font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
			DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
			CFont*   pOldFont=(CFont*)pDC->SelectObject(&font); 
			for (i=0;i<=m_Intendstart;i++)
			{
				if ((point.x) > fw2+m_smallavescale*i &&  (point.x) <fw2+(i+1)*m_smallavescale )
				{
                  Frepointi=i;
				  Frepointx=point.x;
				  Frepointy=point.y;
				  str.Format("%.4f",XRf4[i+m_Intstart]);//幅值为
				  if (i<10-1)
				  {
					  str1.Format("%d",i+m_Intstart);
					  str1=str1+"  ";
				  }
				  if (i>=10-1&&i<100-1)
				  {
					  str1.Format("%d",i+m_Intstart);
					  str1=str1+" ";
				  }
				  if (i>100-1)
				  {
					  str1.Format("%d",i+m_Intstart);
				  }
				  
				  str1="当前谐波:"+str1;
                  str1=str1+"  幅值为：";
                  str1=str1+str+" um";
                  pDC->TextOut(10,10,str1);
				}	
			}
 	}
 
	}

	CFormView::OnLButtonDown(nFlags, point);
}


void CJMAnalyse::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_BOOLSegmentprocess==0  && FlagFrequency==0 && (MK_LBUTTON & nFlags))
	{	
		CWnd *pwnd=GetDlgItem(IDC_JManalyse);//获取静态框的指针
		CDC *pDC=pwnd->GetDC();
		CRect rect_ctr;
		this->ClientToScreen(&point);  //转换为屏幕坐标
		pwnd->GetClientRect(rect_ctr);       //获得文本框矩形,左上角坐标(0,0)   
		pwnd->ClientToScreen(rect_ctr);       //转换到屏幕坐标,左上角坐标为文本框在屏幕的坐标
		
		point.x=point.x-rect_ctr.left;
		point.y=point.y-rect_ctr.top;
		
		double f1=(rect_ctr.right-rect_ctr.left)/2,f2= (rect_ctr.bottom-rect_ctr.top ) /2; 
		double theta3, dw= 2 * 3.1415926/3600;
        double dY0= (rect_ctr.bottom-rect_ctr.top )/2, dleft=0,dtop=0,dright=(rect_ctr.right-rect_ctr.left)*3/5,dbottom=rect_ctr.bottom-rect_ctr.top,dX0=dright/2;
		CString strcodinate;	
		//rin为0圆，RSLC为2018圆，rout为4096圆 
		double x1,y1,x2,y2;
		double sita=0,rout=(rect_ctr.bottom-rect_ctr.top)*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5;
		
		if (sita=atan2(point.y-dY0,point.x-dX0))
		{
			x1=rin*cos(sita);
			y1=rin*sin(sita);
			x2=rout*cos(sita);
			y2=rout*sin(sita);
			if( abs(point.x-dX0)<abs(x1) ||  abs(point.x-dX0)>abs(x2)	|| abs(point.y-dY0)>abs(y2) || abs(point.y-dY0)<abs(y1))
			{
				
			}
		else  
		{	
			flagmanchuli=1;
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS ));
			int nDrawmode=pDC->SetROP2(R2_NOT); //设置异或绘图模式，并保存原来绘图模式 
			
			//----------------构造动态圆环--------------------
			{	       
				//擦除上次绘制的圆环线
				theta1=atan2(m_zancunOrigin.y-dY0,m_zancunOrigin.x-dX0);
				theta2=atan2(m_zancunfinish.y-dY0,m_zancunfinish.x-dX0);       
				
				//计算鼠标按下theta1和抬起时的角度theta2
				
				if (theta1<0)
				{
					theta1=2*3.141592+theta1;
				}
				if (theta2<0)
				{
					theta2=2*3.141592+theta2;
				}
				m_IndexStart=theta1/dw;
				m_IndexEnd=theta2/dw;
				
				theta3=atan2(point.y-dY0,point.x-dX0);       //计算鼠标按下theta1和抬起时的角度theta2
				if (theta3<0)
				{
					theta3=2*3.141592+theta3;
				}
				if (fabs(theta3-theta2)>=3*PI/2)            
				{
					Flagxzhou=1;
				}	
				else 
					Flagxzhou=0;
				if (Flagxzhou==1)
					FlagMove+=1;
				//----------------画出新的临时圆环线-----------------------//
				theta1=atan2(m_zancunOrigin.y-dY0,m_zancunOrigin.x-dX0);
				theta2=atan2(point.y-dY0,point.x-dX0);       //计算鼠标按下theta1和抬起时的角度theta2
				if (theta1<0)
				{
					theta1=2*3.141592+theta1;
				}
				if (theta2<0)
				{
					theta2=2*3.141592+theta2;
				}
				m_IndexStart=theta1/dw;
				m_IndexEnd=theta2/dw;
				alpha1=theta1;
				alpha2=theta2;
				m_zancunfinish=point;   //记录鼠标弹起时的点，以备再次绘图时用
				OnPaint(); //动态绘制
			}

			m_zancunfinish=point;   //记录鼠标弹起时的点，以备再次绘图时用
			pDC->SetROP2(nDrawmode); //恢复原绘图模式 	 
			ReleaseDC(pDC); //释放设备环境 
		}
			////////////////////////////////////////////////////////////
		}
	}
	CFormView::OnMouseMove(nFlags, point);
}


void CJMAnalyse::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_BOOLSegmentprocess==0  && FlagFrequency==0 )
	{
		CWnd *pWndJMUP;
		CDC  *pDC;
		CRect rect_ctr;
		pWndJMUP=GetDlgItem(IDC_JManalyse);                           //获取静态框的指针
		pDC=pWndJMUP->GetDC();
		pWndJMUP->GetClientRect(&rect_ctr);                             // 获取绘制坐标的文本框 
		
		CWnd *pnd=GetDlgItem(IDC_JManalyse);                       //获取静态框的指针
		CDC *DC=pnd->GetDC();
		CRect rect1;
		pnd->GetClientRect(&rect1);                                   // 获取绘制坐标的文本框 
		
		this->ClientToScreen(&point);                                 //转换为屏幕坐标
		pWndJMUP->GetClientRect(rect_ctr);                               //获得文本框矩形,左上角坐标(0,0)   
		pWndJMUP->ClientToScreen(rect_ctr);                              //转换到屏幕坐标,左上角坐标为文本框在屏幕的坐标
		
		point.x=point.x-rect_ctr.left;
		point.y=point.y-rect_ctr.top;                                 //实现point相对于静态框坐标的坐标
		double dY0= (rect_ctr.bottom-rect_ctr.top )/2, dleft=0,dtop=0,dright=(rect_ctr.right-rect_ctr.left)*3/5,dbottom=rect_ctr.bottom-rect_ctr.top,dX0=dright/2;
		double dw=2 * 3.1415926/3600;// 每一次采样对应的角度间隔，弧度;
		
		CString strcodinate;	
		//rin为0圆，RSLC为2018圆，rout为4096圆 
		double x1,y1,x2,y2;
		double sita=0,rout=(rect_ctr.bottom-rect_ctr.top)*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5;
		
		if (sita=atan2(point.y-dY0,point.x-dX0))
		{
			x1=rin*cos(sita);
			y1=rin*sin(sita);
			x2=rout*cos(sita);
			y2=rout*sin(sita);
			if( abs(point.x-dX0)<abs(x1) ||  abs(point.x-dX0)>abs(x2)	|| abs(point.y-dY0)>abs(y2) || abs(point.y-dY0)<abs(y1))
			{
				
			}
		else	
		{	 
			m_bDraw=FALSE;                                             //此时鼠标弹起不响应绘图
			m_zancunfinish=point;                                      //记录鼠标弹起时的点，以备再次绘图时用
			theta1=atan2(m_zancunOrigin.y-dY0,m_zancunOrigin.x-dX0);
			theta2=atan2(m_zancunfinish.y-dY0,m_zancunfinish.x-dX0);       //计算鼠标按下theta1和抬起时的角度theta2
			
			if (theta1<0)
			{
				theta1=2*3.141592+theta1;
			}
			if (theta2<0)
			{
				theta2=2*3.141592+theta2;
			}
			m_IndexStart=theta1/dw;
			m_IndexEnd=theta2/dw;
			
			if (FlagMove%2==0)
			{
				ChangeValueOfSelectJM(pathJM,m_IndexStart, m_IndexEnd,1);
			}
			else 
			{
				if ( 6.2814-theta2>6.2814-theta1)
				{
					ChangeValueOfSelectJM(pathJM,m_IndexStart, 3599,1);
					ChangeValueOfSelectJM(pathJM,0, m_IndexEnd,1);
				}
				else if ( 6.2814-theta1>6.2814-theta2)
				{
					ChangeValueOfSelectJM(pathJM,m_IndexStart, 0,1);
					ChangeValueOfSelectJM(pathJM,3599, m_IndexEnd,1);
				}	   
			}
			OnPaint();
		}
		}
		flagmanchuli=0;
		FlagMove=0;
	}
	CFormView::OnLButtonUp(nFlags, point);
	OnPaint();
	
}




void CJMAnalyse::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pActivateView==this)
	{
		if(FlagBogao|FlagFrequency|m_BOOLSegmentprocess)
		{
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(-1,TRUE);
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(7,FALSE);
		}
		else
		{
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(-1,TRUE);
			if (m_bIsEnable)
			{
				((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,FALSE);
			}
			else
			{
				((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,TRUE);
			}
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(1,TRUE);
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(7,TRUE);
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(8,TRUE);
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(9,TRUE);
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(10,TRUE);
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(12,TRUE);
		}
	}
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CJMAnalyse::OnBtnchuli() 
{
	// TODO: Add your command handler code here
	// TODO: Add your control notification handler code here
	m_Flagcircle=1;
	CPropertyDlg prop;
    if(IDOK==prop.DoModal())
	{
		((CMainFrame*)AfxGetMainWnd())->FilterMode=prop.m_IntFilter; //得到滤波选择的选择项标号
		((CMainFrame*)AfxGetMainWnd())->CirEvalue=prop.m_IntAlg;  //得到圆度评定方法选择方法的标号
		canshu();	
		//手动处理后的数据进行调用函数计算
		//////////////////////////////////////////////
        BtnChuliDwon=1;
		SubAnaData (FilterMode, Resdata,GResult,GG1,GG2);	//圆度
		//显示波纹度
		m_Wa.Format("%.2f",m_BWD[0]); //将数据结果转换成字符串的形式，便于显示在表格中
		m_Wc.Format("%.2f",m_BWD[1]);
		m_Wp.Format("%.2f",m_BWD[2]);
		m_Wv.Format("%.2f",m_BWD[3]); //将数据结果转换成字符串的形式，便于显示在表格中
		m_Wt.Format("%.2f",m_BWD[4]);
		m_Wq.Format("%.2f",m_BWD[5]);
	    m_Wwm.Format("%.2f",m_BWD[6]);
		OnPaint(); 
	}	
}

void CJMAnalyse::OnBtnenable() 
{
		// TODO: Add your command handler code here
		
		if (FlagFrequency==0)
		{	
			if (m_BOOLSegmentprocess==0  && FlagFrequency==0 && m_bIsEnable==1 )
			{
				
				GetDlgItem(IDC_JManalyse)->EnableWindow(false); //使窗口开始响应鼠标消息
				((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,TRUE);
				
			}
			else  
				if(m_BOOLSegmentprocess==0  && FlagFrequency==0 && m_bIsEnable==0 )
				{
					GetDlgItem(IDC_JManalyse)->EnableWindow(true); //使窗口开始响应鼠标消息
					((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,FALSE);
					
				}
				m_bIsEnable=!m_bIsEnable;
		}
	}
	


void CJMAnalyse::OnBtnresetdeal() 
{
	// TODO: Add your command handler code here
	DrawingCleanAndResetJM(pathJM,0);
	OnPaint();
}

void CJMAnalyse::OnBtnfenduanchuli() 
{
	// TODO: Add your command handler code here
	if(m_BOOLSegmentprocess==0)
	{
		CDlgextendCircle dlg;
		dlg.m_startposition=0;
		dlg.m_endposition=360;
		dlg.m_splitnumber=4;
		if (IDOK==dlg.DoModal())
		{
			m_startposition=dlg.m_startposition;
			m_endposition=dlg.m_endposition;
			m_splitnumber=dlg.m_splitnumber;
			if (m_startposition>m_endposition)
			{
				AfxMessageBox("输入的起始位置和终止位置错误",MB_OK|MB_ICONERROR);
				return;
			}
			if (m_splitnumber<=0)
			{
				AfxMessageBox("输入的分段数必须≤0",MB_OK|MB_ICONERROR);
				return;
			}	
			m_BOOLSegmentprocess=1;		
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(-1,TRUE);
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(7,FALSE);
			
			OnPaint();
		}
		else
		{
			m_BOOLSegmentprocess=0;
		}
		
	}
}

void CJMAnalyse::OnBtnyuanduchuli() 
{
	if (m_BOOLSegmentprocess==1|| FlagFrequency==1||FlagBogao==1)
	{
		m_BOOLSegmentprocess=0; 
		FlagFrequency=0;
		
		if (FlagFrequency==0)
		{			
			GetDlgItem(IDC_JManalyse)->EnableWindow(true); //使窗口开始响应鼠标消息
		}
		
		FlagBogao=0;
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(1,TRUE);		
		if (m_bIsEnable)
		{
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,FALSE);
		}
		else
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,TRUE);	
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(7,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(8,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(9,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(10,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(12,TRUE);
		BoolButtondown=0;
		OnPaint();
	}
	
}

void CJMAnalyse::DrawGride1()
{
	double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=dright/2;
	int gridxnums=1;int gridynums=22;
	double dx= (rectJM.Width()+rectJM.left-dright)/gridxnums;
	double dy=rectJM.Height()/gridynums;
    CRect gridRect(rectJM.left,rectJM.top,rectJM.left+dx*gridxnums,rectJM.top+dy*gridynums);

	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	CPen *oldpen=memDCJM.SelectObject(&RectPen);    

	//----------数据写入字体及大小


	memDCJM.SetBkMode(TRANSPARENT); 
	int m1=dright+dx/30;
	int meter=rectJM.Height()/70;
	double m2=dright+(rectJM.right-dright)/3+dx/30;
	double m3=dright+(rectJM.right-dright)*2/3+dx/30;
	double mid=dright+(rectJM.right-dright)/3+dx/30;

 
	if (FlagBogao==0)
	{
		    //------------------------------------------------------------
		memDCJM.FillSolidRect(dright,0+rectJM.top,dx,dy,RGB(232,232,232));//给头行填充颜色
	    memDCJM.FillSolidRect(dright,dy*5+rectJM.top,dx,dy,RGB(232,232,232));//给指定行填充颜色
		memDCJM.FillSolidRect(dright,dy*9+rectJM.top,dx,dy,RGB(232,232,232));//给指定行填充颜色	
		

		memDCJM.FillSolidRect(dright,dy*6+rectJM.top,gridRect.right-1*m_penScale,dy,RGB(255,255,255));			
		memDCJM.TextOut(m2,dy*6+rectJM.top+meter,m_strMethod); 		
		memDCJM.TextOut(m2,dy*7+rectJM.top+meter,"Gaussian");
 		memDCJM.TextOut(m2,dy*8+rectJM.top+meter,m_strlvbo);	
		memDCJM.TextOut(mid ,meter+rectJM.top,"圆度测量结果");

		memDCJM.TextOut(mid,dy*5+rectJM.top+meter," 评定参数 ");
		memDCJM.TextOut(mid,dy*9+rectJM.top+meter," 测量参数 ");

		memDCJM.TextOut(m1,dy+meter+rectJM.top,"文件名");
		memDCJM.TextOut(m1,dy*2+meter+rectJM.top,"测量时间");  
		memDCJM.TextOut(m1,dy*6+meter+rectJM.top,"评定方法");
		memDCJM.TextOut(m1,dy*7+meter+rectJM.top,"滤波器种类");                                              
		memDCJM.TextOut(m1,dy*8+meter+rectJM.top,"滤波范围");    
                                                 
		memDCJM.TextOut(m1,dy*10+meter+rectJM.top,"圆度");
		memDCJM.TextOut(m1,dy*11+meter+rectJM.top,"偏心");
		memDCJM.TextOut(m1,dy*12+meter+rectJM.top,"偏心角度");             
        memDCJM.TextOut(m1,dy*13+meter+rectJM.top,"放大倍数");
		memDCJM.TextOut(m1,dy*14+meter+rectJM.top,"每格");  
		CString str;	
		str.Format("%.2f",5000/(ratio*5));
		memDCJM.TextOut(m2,dtop+dy*14+meter,str);		
		str.Format("%d",(int)(ratio*5));
		memDCJM.TextOut(m2,dtop+dy*13+meter,str);	
		//显示文件名
		//CString str;
		str=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
		int num=str.ReverseFind('\\');
		str=str.Right(str.GetLength()-num-1);
		memDCJM.TextOut((m1+m2)/2,dy*1+meter+rectJM.top,str);
		//显示测量时间
		str=m_time.Format("%Y-%m-%d %H:%M");
		memDCJM.TextOut((m1+m2)/2,dy*2+meter+rectJM.top,str);
		memDCJM.TextOut(m3,dy*10+meter+rectJM.top,"   um");
		memDCJM.TextOut(m3,dy*11+meter+rectJM.top,"   um");
	//	memDCJM.TextOut(m3,dy*12+meter+rectJM.top,"   度");
        memDCJM.TextOut(m3,dy*13+meter+rectJM.top,"   倍");
		memDCJM.TextOut(m3,dy*14+meter+rectJM.top,"   um");
	
		if (CirEvalue==0) //最小二乘法
		{
		memDCJM.TextOut(m2,dy*10+meter+rectJM.top,m_strdRONT);
		memDCJM.TextOut(m2,dy*11+meter+rectJM.top,m_strdEcc);
		memDCJM.TextOut(m2,dy*12+meter+rectJM.top,m_strdEccPos);
		memDCJM.TextOut(m3,dy*12+meter+rectJM.top,"   度");
			
			if (FilterMode==8 || FilterMode==9)
		{
			//显示波纹度
            memDCJM.FillSolidRect(dright,dy*15+rectJM.top,gridRect.right-1,dy,RGB(232,232,232));
			memDCJM.TextOut(m2,dy*15+meter+rectJM.top,"波纹度");
			memDCJM.TextOut(m1,dy*16+meter+rectJM.top,"Wa");
			memDCJM.TextOut(m1,dy*17+meter+rectJM.top,"Wc");
			memDCJM.TextOut(m1,dy*18+meter+rectJM.top,"Wp");
			memDCJM.TextOut(m1,dy*19+meter+rectJM.top,"Wv");
			memDCJM.TextOut(m1,dy*20+meter+rectJM.top,"Wt");
			memDCJM.TextOut(m1,dy*21+meter+rectJM.top,"Wq");
			memDCJM.TextOut(m1,dy*22+meter+rectJM.top,"Wwm");
			
			
			memDCJM.TextOut(m2,dy*16+meter+rectJM.top,m_Wa);
			memDCJM.TextOut(m2,dy*17+meter+rectJM.top,m_Wc);
			memDCJM.TextOut(m2,dy*18+meter+rectJM.top,m_Wp);
			memDCJM.TextOut(m2,dy*19+meter+rectJM.top,m_Wv);
			memDCJM.TextOut(m2,dy*20+meter+rectJM.top,m_Wt);
			memDCJM.TextOut(m2,dy*21+meter+rectJM.top,m_Wq);
			memDCJM.TextOut(m2,dy*22+meter+rectJM.top,m_Wwm);

			memDCJM.TextOut(m3,dtop+dy*16+meter,"um");
			memDCJM.TextOut(m3,dtop+dy*17+meter,"um");
			memDCJM.TextOut(m3,dtop+dy*18+meter,"um");
			memDCJM.TextOut(m3,dtop+dy*19+meter,"um");
			memDCJM.TextOut(m3,dtop+dy*20+meter,"um");
			memDCJM.TextOut(m3,dtop+dy*21+meter,"um");
			memDCJM.TextOut(m3,dtop+dy*22+meter,"um");
			}
		}
		
		else if (CirEvalue==1)//最小区域法
		{	   
			memDCJM.TextOut(m2,dy*10+meter+rectJM.top,m_MZCRONT);
			memDCJM.TextOut(m2,dy*11+meter+rectJM.top,m_strdEcc);
//		    memDCJM.TextOut(m2,dy*12+meter+rectJM.top,m_strdEccPos);
		}
		
		else if (CirEvalue==2)//
		{
			memDCJM.TextOut(m2,dy*10+meter+rectJM.top,m_MCCRONT);
			memDCJM.TextOut(m2,dy*11+meter+rectJM.top,m_strdEcc);
		  //  memDCJM.TextOut(m2,dy*12+meter+rectJM.top,m_strdEccPos);
		}
		
		else if (CirEvalue==3)
		{
			//最大内切法评定圆度误差
			memDCJM.TextOut(m2,dy*10+meter+rectJM.top,m_MICRONT);
			memDCJM.TextOut(m2,dy*11+meter+rectJM.top,m_strdEcc);
//		    memDCJM.TextOut(m2,dy*12+meter+rectJM.top,m_strdEccPos);
		}

		//------------------------------------------------------------
		for(int m=0;m<=gridxnums;m++) //画出gridxnums条竖线                      
		{
			memDCJM.MoveTo(dright+m*dx,gridRect.bottom);
			memDCJM.LineTo(dright+m*dx,rectJM.top);
		}
			
		for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
		{
			memDCJM.MoveTo(dright,n*dy+rectJM.top);
			memDCJM.LineTo(rectJM.left+rectJM.Width(),n*dy+rectJM.top);
		}
    
		memDCJM.MoveTo(dright,rectJM.top);
		memDCJM.LineTo(dright,rectJM.bottom);

		memDCJM.MoveTo(rectJM.right,dtop);
		memDCJM.LineTo(rectJM.right,dbottom);
	}
	///////////////////////////////////////////////////////////波高数据显示
	if (FlagBogao==1)
	{
		memDCJM.FillSolidRect(dright,dtop,gridRect.Width(),dy,RGB(232,232,232));//给头行填充颜色

		memDCJM.MoveTo(dright,dtop+dy);
		memDCJM.LineTo(rectJM.left+rectJM.Width(),dtop+dy);

		memDCJM.MoveTo(rectJM.left+rectJM.right,rectJM.top);
		memDCJM.LineTo(rectJM.left+rectJM.right,rectJM.bottom);

		memDCJM.MoveTo(dright,dtop);
		memDCJM.LineTo(dright,dbottom);

		memDCJM.MoveTo(dright,rectJM.top);
		memDCJM.LineTo(rectJM.right,rectJM.top);
       
		CString bogaostr;
		CString weizhistr;
		CString bianhaostr;
		
		//显示内容
		memDCJM.TextOut(dright+rectJM.Width()/10,+rectJM.top+meter,"波高分析结果(左：um,右：°)");
		double dygridnum=rectJM.Height()*5/6/20;
		int meterbaogao=12*m_penScale;
		for (int i=1;i<=DispTempFnumber;i++)
		{
			
			if (i<=35)
			{
				if (i<10)
				{
					bianhaostr.Format("%d",i);
					bogaostr.Format("%.2f",bogao[i]);
					if (bogaostr=="0.000")
					{
						bogaostr="0";
					}
					bogaostr=bogaostr+"-";
					bogaostr=bianhaostr+" "+bogaostr;
					weizhistr.Format("%.1f",weizhi[i]);
					bogaostr=bogaostr+weizhistr;
				}
				if (i>=10)
				{
					bianhaostr.Format("%d",i);
					bogaostr.Format("%.2f",bogao[i]);
					if (bogaostr=="0.000")
					{
						bogaostr="0";
					}
					bogaostr=bogaostr+"-";
					bogaostr=bianhaostr+" "+bogaostr;
					weizhistr.Format("%.1f",weizhi[i]);
					bogaostr=bogaostr+weizhistr;
				}

				memDCJM.TextOut(m1,dtop+dygridnum*(i)+meterbaogao,bogaostr);
			}

			if (i>35  && i<=70)
			{
				bianhaostr.Format("%d",i);
				bogaostr.Format("%.2f",bogao[i]);
				if (bogaostr=="0.000")
				{
					bogaostr="0";
				}
				bogaostr=bogaostr+"-";
				bogaostr=bianhaostr+" "+bogaostr;
				weizhistr.Format("%.1f",weizhi[i]);
				bogaostr=bogaostr+weizhistr;
				memDCJM.TextOut(m2,dtop+dygridnum*(i-35)+meterbaogao,bogaostr);
			}
			if (i>70  && i<=100)
			{
				bianhaostr.Format("%d",i);
				bogaostr.Format("%.2f",bogao[i]);
				if (bogaostr=="0.000")
				{
					bogaostr="0";
				}
				bogaostr=bogaostr+"-";
				bogaostr=bianhaostr+" "+bogaostr; 
				weizhistr.Format("%.1f",weizhi[i]);
				bogaostr=bogaostr+weizhistr;
				memDCJM.TextOut(m3,dtop+dygridnum*(i-70)+meterbaogao,bogaostr);
			}
		}
	}
         RectPen.DeleteObject();
}
void CJMAnalyse::DrawGrid2()
{
	double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.right*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=dright/2;
	int gridxnums=1;int gridynums=22;
	double dx= (rectJM.Width()+rectJM.left-dright)/gridxnums;
	double dy=rectJM.Height()/gridynums;
    CRect gridRect(rectJM.left,rectJM.top,rectJM.left+dx*gridxnums,rectJM.top+dy*gridynums);
// 	CPen gridPen(0,0,RGB(0,0,20)); //网格线的颜色
// 	memDCJM.FillSolidRect(dright+dx,dy*12,dx,dy,RGB(139,216,224));//给指定格子填充颜色
//     CPen *oldpen=memDCJM.SelectObject(&gridPen);
	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	CPen *oldpen=memDCJM.SelectObject(&RectPen);    

	
    //------------------------------------------------------------
	memDCJM.FillSolidRect(dright,0+rectJM.top,dx,dy,RGB(232,232,232));//给头行填充颜色
	memDCJM.FillSolidRect(dright,dy*5+rectJM.top,dx,dy,RGB(232,232,232));//给指定行填充颜色
	memDCJM.FillSolidRect(dright,dy*9+rectJM.top,dx,dy,RGB(232,232,232));//给指定行填充颜色




	memDCJM.SetBkMode(TRANSPARENT); 
	int m1=dright+rectJM.Width()/100;
	int meter=rectJM.Height()/70;
	double m2=dright+dx/2-rectJM.Width()/20;
	double m3=dright+dx-rectJM.Width()/15;
	double mid=dright+dx/2-rectJM.Width()/20;
	int m_endstart=m_endposition-m_startposition;
	double m_splitmark=m_endstart/m_splitnumber;
 
	//将圆度计算的结果信息显示在表格对应的位置上，此处显示信息有：圆度、偏心、偏心角

	memDCJM.FillSolidRect(dright,dy*6+rectJM.top,dx,dy,RGB(255,255,255));
	memDCJM.TextOut(m2,dy*6+meter+rectJM.top,m_strMethod);
	memDCJM.TextOut(m2,dy*7+meter+rectJM.top,"Gaussian");
	memDCJM.TextOut(m2,dy*8+meter+rectJM.top,m_strlvbo);

	memDCJM.TextOut(mid ,meter+rectJM.top,"圆度测量结果");
	memDCJM.TextOut(mid,dy*5+meter+rectJM.top," 评定参数");
	memDCJM.TextOut(m1+rectJM.Width()/10,dy*9+meter+rectJM.top,"分段圆度评定(左:°右:um)");

    memDCJM.TextOut(m1,dy+meter+rectJM.top,"文件名");
	memDCJM.TextOut(m1,dy*2+meter+rectJM.top,"测量时间");
	memDCJM.TextOut(m1,dy*6+meter+rectJM.top,"评定方法");                                       
	memDCJM.TextOut(m1,dy*7+meter+rectJM.top,"滤波器种类");                                              
	memDCJM.TextOut(m1,dy*8+meter+rectJM.top,"滤波范围");   
                                                
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDCJM.TextOut((m1+m2)/2,dy*1+meter+rectJM.top,str);
	//显示测量时间
	str=m_time.Format("%Y-%m-%d %H:%M");
	memDCJM.TextOut((m1+m2)/2,dy*2+meter+rectJM.top,str);
	int i;
	CString strsplit;
	for (i=0;i<m_splitnumber;i++)
	{
		strsplit.Format("%d",i+1);
		strsplit="第"+strsplit+"段范围:";
		memDCJM.TextOut(m1,dy*(10+i)+meter+rectJM.top,strsplit);
		memDCJM.TextOut(m3-rectJM.Width()/15,dy*(10+i)+meter+rectJM.top,"P+V=");
	}
	
	CString strstart;
		CString strend;
		CString strstartend;
		for(i=0;i<m_splitnumber;i++)   //报表显示每段范围
		{
			strstart.Format("%.1f",m_splitmark*i+m_startposition);
			strend.Format("%.1f",m_splitmark*(i+1)+m_startposition);	
			//strstartend=strstart+"°- "+strend+"°";
			strstartend=strstart+"-"+strend;
            memDCJM.TextOut(m1+100*m_penScale,dy*(10+i)+meter+rectJM.top,strstartend);	
		}



	//------------------------------------------------------------

	for(int m=0;m<=gridxnums;m++) //画出gridxnums条竖线                      
	{
		memDCJM.MoveTo(dright+m*dx,gridRect.bottom);
		memDCJM.LineTo(dright+m*dx,rectJM.top);
	}
		
	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
	{
		memDCJM.MoveTo(dright,n*dy+rectJM.top);
		memDCJM.LineTo(rectJM.right,n*dy+rectJM.top);
	}
    
	memDCJM.MoveTo(dright,rectJM.top);
	memDCJM.LineTo(dright,rectJM.bottom);

	memDCJM.MoveTo(dright,dtop);
	memDCJM.LineTo(dright,dbottom);
	RectPen.DeleteObject();
}

void CJMAnalyse::Segmentationprocess()
{
    CFont   font; 
	font.CreateFont(13,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  	
	CFont*   pOldFont=(CFont*)memDCJM.SelectObject(&font); 
	ReadDataFromFile();
	
	//定义后面将要用到的变量
    double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left ,dbottom=rectJM.bottom,dX0=rectJM.Width()*(3/5)/2;
	double fw1=3*rectJM.Width()/5,f1=rectJM.Width(),f2=rectJM.Height();                                                 	                             
    double fw2=rectJM.Width()/30;
    double fh=rectJM.Height()/2+rectJM.top;
	double fh1=rectJM.Height()/4;
	double fh2=rectJM.Height()/30;
	
	CPen newPen;         
	newPen.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&newPen); 

	memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh); // 中线,横线
    memDCJM.LineTo(fw2*3/2+rectJM.left,fh); 

	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);//左边竖线
    memDCJM.LineTo(fw2*3/2+rectJM.left,fh+fh2*7); 

	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);  //左边箭头
    memDCJM.LineTo(fw2*3/2+rectJM.left-6*m_penScale,fh-fh2*7+fh2*0.4); 
	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);  
    memDCJM.LineTo(fw2*3/2+rectJM.left+6*m_penScale,fh-fh2*7+fh2*0.4); 

	memDCJM.TextOut(fw2+rectJM.left,fh-fh1-20*m_penScale,"单位：微米");	

	memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh+fh2*7);
	memDCJM.LineTo(fw2*3/2+rectJM.left,fh+fh2*7);

	

    int m_endstart=m_endposition-m_startposition;
	CString mark;
	double m_avescale=(fw1-2*fw2)/4;
	double m_smallavescale=(fw1-2*fw2)/(m_splitnumber*5);
	double m_splitave=(fw1-2*fw2)/m_splitnumber;
	double m_splitmark=m_endstart/m_splitnumber;
    
	int i;
	/////////////////////////////////// 标注横坐标 ////////
	for(i=0;i<m_splitnumber*5;i++)    //写X轴小刻度值
	{
		memDCJM.MoveTo(fw2*3/2+rectJM.left+m_smallavescale*i,fh+fh2*7);
		memDCJM.LineTo(fw2*3/2+rectJM.left+m_smallavescale*i,fh+fh2*7-fh/50);
	}

	CPen newPenfenduan;         
	newPenfenduan.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&newPenfenduan); 


	for(i=0;i<=m_splitnumber;i++)    //画分段线,X大刻度值
	{
		memDCJM.MoveTo(fw2*3/2+rectJM.left+m_splitave*i,fh+fh2*7);
		memDCJM.LineTo(fw2*3/2+rectJM.left+m_splitave*i,fh+fh2*7-fh/30);
		mark.Format("%.1f",m_splitmark*i+m_startposition);
		memDCJM.TextOut(fw2*7/8+m_splitave*i,fh+fh2*7+fh/60,mark);	
	}

    memDCJM.SetBkMode(TRANSPARENT); 
	////////////////////////////////////////////////////////////////////////////////
    double datacir[3600];
	double m_datamax=0.0,m_datamin=0.0,m_psum=0;

	//////////////////////////////////////////////
	for(i=0;i<3600;i++)		
	{ 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);   
	}	
	DrawFilter (FilterMode,datacir,dataafterfilter);
	//////////////////////////////////////////////////
	//////////////求出绘图轮廓的最大值和最小值//////////////
	m_datamin=dataafterfilter[0];
	m_datamax=dataafterfilter[0];
	for (i=100;i<3500;i++)	
	{  
		if (m_datamax<dataafterfilter[i])
		{
			m_datamax=dataafterfilter[i];
		}
		if (m_datamin>dataafterfilter[i])
		{
			m_datamin=dataafterfilter[i];
		}
		m_psum=m_psum+dataafterfilter[i];
	}
    m_Middle=m_psum/3400;
    m_OutIn=m_datamax-m_datamin;
    double m_jiange=fh2*10/m_OutIn;


	CPen newPeny;  // 中线平行线
	newPeny.CreatePen(PS_DOT,1*m_penScale,RGB(205,201,201));
    memDCJM.SelectObject(&newPeny);
	int j;
	for(i=fh2,j=1;j<6;j++)
	{
		memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh+i*j);
		memDCJM.LineTo(fw2*3/2+rectJM.left,fh+i*j);
	}
    
	for(i=fh2,j=1;j<6;j++)
	{
		memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh-i*j);
		memDCJM.LineTo(fw2*3/2+rectJM.left,fh-i*j);
	}


	mark.Format("%.2f",m_Middle);   //转化后的数值，Y中线坐标显示
	memDCJM.TextOut(fw2*1/3,fh-fh*1/60,mark);

	mark.Format("%.2f",m_datamax-m_Middle);   //上Y坐标值显示
	memDCJM.TextOut(fw2*1/3,fh-fh2*5-fh*1/60,mark);

	mark.Format("%.2f",m_datamin-m_Middle);   //下Y坐标值显示
	memDCJM.TextOut(fw2*1/3,fh+fh2*5-fh*1/60,mark);
	
	double m_aveangle=3600/360;
	double m_startpoint=m_aveangle*m_startposition;
	double m_endpoint=m_aveangle*m_endposition;
    double m_endstartpiont=m_endpoint-m_startpoint;
	double m_avesize=(fw1-2*fw2)/m_endstartpiont;
	double meter=10;//间隔点数

	for (i=m_startpoint+10;i<m_endpoint;i=i+5)//显示图形
	{
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{
			CPen newPenrelate; 
			newPenrelate.CreatePen(PS_SOLID,1*m_penScale,RGB(0,255,0));
			memDCJM.SelectObject(&newPenrelate); 
			memDCJM.SetPixel(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint+meter),fh-(dataafterfilter[i]-m_Middle)*m_jiange,RGB(0,255,0));
  			memDCJM.MoveTo(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint+meter),fh-(dataafterfilter[i]-m_Middle)*m_jiange);
   			memDCJM.LineTo(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint),fh-(dataafterfilter[i-10]-m_Middle)*m_jiange);
			
		}

		else
		{   
			CPen newPenrelate; 
			newPenrelate.CreatePen(PS_SOLID,1*m_penScale,RGB(255,0,255));
			memDCJM.SelectObject(&newPenrelate); 
			memDCJM.SetPixel(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint+meter),fh-(dataafterfilter[i]-m_Middle)*m_jiange,RGB(255,0,255));
 			memDCJM.MoveTo(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint+meter),fh-(dataafterfilter[i]-m_Middle)*m_jiange);
   			memDCJM.LineTo(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint),fh-(dataafterfilter[i-10]-m_Middle)*m_jiange);
		}
	}


	////////////////////////////////// 计算分段处理：最大，最小值 ///

	int gridxnums=1;int gridynums=22;
	double dx= (rectJM.Width()-dright)/gridxnums;
	double dy=rectJM.Height()/gridynums;
	int meter2=rectJM.Height()/70;
	double m3=rectJM.left+dright+dx-rectJM.Width()/15;

    double m_spiltavenum;
	m_spiltavenum=(m_endpoint-m_startpoint)/m_splitnumber;
  
	for (j=0;j<m_splitnumber;j++)
	{	
			m_maxsplit[j]=0;
			m_minsplit[j]=0;

		for (i=m_startpoint+j* m_spiltavenum; i< m_startpoint+(j+1)* m_spiltavenum;  i++)
		{
		
			if ( m_dataJM[i+1+m_LBtnJM*3600].selected==0 )
			{
				if (m_maxsplit[j]<dataafterfilter[i])
				{
					m_maxsplit[j]=dataafterfilter[i];
				}

				if (m_minsplit[j]>dataafterfilter[i])
				{
					m_minsplit[j]=dataafterfilter[i];
				}			
			}

			m_PV[j]=fabs(m_maxsplit[j])+fabs(m_minsplit[j]);		
		}

	}
	CString m_PVcstring;
	for (i=0; i<m_splitnumber; i++)
	{		
		m_PVcstring.Format("%.2f",m_PV[i]);
		memDCJM.TextOut(m3-rectJM.Width()/30,dy*(10+i)+meter2+rectJM.top,m_PVcstring);
	}
}

void CJMAnalyse::OnBtndelete() 
{
	UpdateData(TRUE);
	CString path1= pathJM;
	if (IDOK==MessageBox("确定要删除该界面吗？","删除提示",MB_OKCANCEL))
	{
		if (IDOK==MessageBox("是否保存删除原始数据？","删除提示",MB_OKCANCEL))
		{
			int ret=0;
			ret=DeletePartOfFile(path1,m_LBtnJM+1,TRUE);
			switch(ret) 
			{
			case 1: 
				AfxMessageBox("删除的界面小于1");
				break;
			case 2: 
				AfxMessageBox("试图删除大于最大界面的位置");
				break;
			case 3: 
				AfxMessageBox("删除后界面的个数小于2");
				break;
			default:
				break;
			}
			
		}
		else
		{
			//DeletePartOfFile("2.cyd",m_NumOfJieMian,FALSE);
			int ret=0;
			ret=DeletePartOfFile(path1,m_LBtnJM+1,FALSE);
			switch(ret) 
			{
			case 1: 
				AfxMessageBox("删除的界面小于1");
				break;
			case 2: 
				AfxMessageBox("试图删除大于最大界面的位置");
				break;
			case 3: 
				AfxMessageBox("删除后界面的个数小于2");
				break;
			default:
				break;
			}
		}
	}
}

void CJMAnalyse::DrawFrequency()
{
	////读取文件并绘图///
	ReadDataFromFile();
	int m_Intendstart=m_Intend-m_Intstart;
	int i=0,j=0;
	double fpdata[RecCount],datacir[RecCount],TsH[RecCount],DispAdata[RecCount];
	for (i=0;i<3600;i++)	
	{  
		fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
	}
	
	////////////////////////////////////////////////////////////////////////////////
    //手动处理后的数据进行调用函数计算	

	for(i=0;i<3600;i++)		
	{ 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //计算圆度误差转换位移公式	
	}		
	DrawFilter (FilterMode,datacir,TsH);

	double XR[RecCount+1],Xi[RecCount+1];
	int GDN=RecCount;
	for (i=1;i<=GDN;i++)
	{
		XR[i]=TsH[i-1];
		Xi[i]=0;
	}

      int  K, L, NV2, NM1, IP ,FLE;
	  int M;
	  
      double FTR, FTI, FPI,FLE1, FUR,FUR1, FUI,FUI1, FWR, FWI;

	  M=(log10(GDN*1.0)/log10(2.0)+0.1+0.5);
      Xi[0]=0;
	  XR[0]=0;
	  NV2=GDN/2;
	  NM1=GDN-1;
	  j=1;
	  for (i=1;i<RecCount;i++)
	  { 
		  if (i>=j) 
			  goto CONFFTA1;	  
		  else
		  {
			  FTR=XR[j];
			  FTI=Xi[j];
			  XR[j]=XR[i];
			  Xi[j]= Xi[i];
			  XR[i]=FTR;
			  Xi[i]=0;
	  	  }

CONFFTA1:
		  K=NV2;    //CONFFTA1

CONFFTA2: 
		  if (K >=j)  
			  goto CONFFTA3;
		  
		  else
		  {
 	 		   j = j - K;
      		   K = (K *1.0/ 2.0+0.5);
			   if (K==113)
			   {
				   K=112;
			   }
			   goto CONFFTA2;
		  }
CONFFTA3:
		  j = j + K;	 
	  }

int m=0;
int g=0;
FPI=4*atan(1.0);	
for (L=1;L<5;L++)
{
    FLE=exp(L*log(2.0))+0.5;
	FLE1=FLE/2;
	FUR=1.0;
	FUI=0;
	FWR=cos(FPI/FLE1);
	FWI=-sin(FPI/FLE1);
	for (m=1;m<=FLE1;m++)
	{
		for (g=m;g<=GDN; g=g+FLE)
		{
			IP=g+FLE1;
			FTR=XR[IP]*FUR-Xi[IP]*FUI;
			FTI=XR[IP]*FUI+Xi[IP]*FUR;
			XR[IP]=XR[g]-FTR;
			Xi[IP]=Xi[g]-FTI;
			XR[g]=XR[g]+FTR;
			Xi[g]=Xi[g]+FTI; 
		}
		 	FUR1=(FUR*FWR)-(FUI*FWI);
			FUI1=(FUR*FWI)+(FUI*FWR);
			FUR=FUR1;
			FUI=FUI1;			
	}
}

//////////////////////////////// L= 5_10
double XRf[RecCount+1], Xif[RecCount+1],XRfr[RecCount+1];
XRf[0]=0;
Xif[0]=0;
int ks;
int d;
for (i=1;i<RecCount+1;i++)
{
	XRf[i]=XR[i];
    Xif[i]=Xi[i];
}
int FG,FG1;
int IK;
for (L=5;L<11;L++)
{
	FG=exp(L*log(2.0))+0.5;
    FG1=FG/2;
	FUR=1.0;
	FUI=0;

 	FWR=cos(FPI/FG1);  
	FWI=-sin(FPI/FG1); 

	for (d=1;d<=FG1;d++)
	{    		
		for (ks=d ; ks<3000; ks=ks+FG)
		{
			IK=ks+FG1;
			FTR=XRf[IK]*FUR-Xif[IK]*FUI;
			FTI=XRf[IK]*FUI+Xif[IK]*FUR;
			XRf[IK]=XRf[ks]-FTR;
			Xif[IK]=Xif[ks]-FTI;
			XRf[ks]=XRf[ks]+FTR;
			Xif[ks]=Xif[ks]+FTI; 
		}
		 	FUR1=(FUR*FWR)-(FUI*FWI);
			FUI1=(FUR*FWI)+(FUI*FWR);
			FUR=FUR1;
			FUI=FUI1;
	
	}
}
	
//////////////////////////// L=11	    
	double XRf2[3601], Xif2[3601];
	XRf2[0]=0;
	Xif2[0]=0;
	int kg;
	for (i=1;i<3601;i++)
	{
		XRf2[i]=XRf[i];
		Xif2[i]=Xif[i];
	}  	
	for (L=11;L<12;L++)
	{
		FLE=exp(L*log(2.0))+0.5;
		FLE1=FLE/2;
		FUR=1.0;
		FUI=0;
		FWR=cos(FPI/FLE1);
		FWI=-sin(FPI/FLE1);

	for (m=1;m<=FLE1;m++)
	{
		for (kg=m ; kg<= 2000; kg=kg+FLE)
		{
			IP=kg+FLE1;
			FTR=XRf2[IP]*FUR-Xif2[IP]*FUI;
			FTI=XRf2[IP]*FUI+Xif2[IP]*FUR;
			XRf2[IP]=XRf2[kg]-FTR;
			Xif2[IP]=Xif2[kg]-FTI;
			XRf2[kg]=XRf2[kg]+FTR;
			Xif2[kg]=Xif2[kg]+FTI; 
		}

			FUR1=(FUR*FWR)-(FUI*FWI);
			FUI1=(FUR*FWI)+(FUI*FWR);
			FUR=FUR1;
			FUI=FUI1;			
		}
	}
///////////////////////////// L=12
	double XRf3[3601], Xif3[3601];
	XRf3[0]=0;
	Xif3[0]=0;
	for (i=1;i<3601;i++)
	{
		XRf3[i]=XRf2[i];
		Xif3[i]=Xif2[i];
	}  	
	for (L=12;L<13;L++)
	{
		FLE=exp(L*log(2.0))+0.5;
		FLE1=FLE/2;
		FUR=1.0;
		FUI=0;
		FWR=cos(FPI/FLE1);
		FWI=-sin(FPI/FLE1);

	for (m=1;m<=FLE1;m++)
	{
		for (kg=m ; kg< 800; kg=kg+FLE)
		{
			IP=kg+FLE1;
			FTR=XRf3[IP]*FUR-Xif3[IP]*FUI;
			FTI=XRf3[IP]*FUI+Xif3[IP]*FUR;
			XRf3[IP]=XRf3[kg]-FTR;
			Xif3[IP]=Xif3[kg]-FTI;
			XRf3[kg]=XRf3[kg]+FTR;
			Xif3[kg]=Xif3[kg]+FTI; 
		}

			FUR1=(FUR*FWR)-(FUI*FWI);
			FUI1=(FUR*FWI)+(FUI*FWR);
			FUR=FUR1;
			FUI=FUI1;			
		}
	}
/////////////////////////////////////////////////
	double  Xif4[3601];
	XRf4[0]=0;
	Xif4[0]=0;
	for (i=1;i<3601;i++)
	{
		XRf4[i]=XRf3[i];
		Xif4[i]=Xif3[i];
	}  	
     int n=0;
	 double XRsqr[3600],Xisqr[3600],XRi[3600];
     XRsqr[0]=0;Xisqr[0]=0;XRi[0]=0;
     for (i=1;i<3600;i++)
     {
		 XRsqr[i]=XRf4[i]*XRf4[i];
         Xisqr[i]=Xif4[i]*Xif4[i];
         XRi[i]=XRsqr[i]+Xisqr[i];
     }
	 for (i=1;i < GDN;i++)
	 {
		 XRf4[i]=2.0/ 3600.0 *sqrt(XRi[i]);
	 }
 	  XRf4[1]=0;//XR[1]/2;
	 
                
	 for( i = 1 ; i < GDN;i++)
	 {
		   dataafterfilter[i]=XRf4[i];
	 }

    double m_pmax=dataafterfilter[1], m_pmin=dataafterfilter[1];

	for (i=m_Intstart-1;i<m_Intend;i++)
	{	
		if (m_pmax<=dataafterfilter[i])
		{
			m_pmax=dataafterfilter[i];
		}

		if (m_pmin>=dataafterfilter[i])
		{
			m_pmin=dataafterfilter[i];	
		}
	}
	//定义后面将要用到的变量
	double fw1=3*rectJM.Width()/5,f1=rectJM.Width(),f2=rectJM.Height();                                                 	                             
    double fw2=rectJM.Width()/30;
    double fh=rectJM.Height()/2;
	double fh1=rectJM.Height()/4;
	double fh2=rectJM.Height()/30;
	CString mark;
	double m_avescale=((fw1-fw2*3)/m_Intendstart)*5;
	double m_smallavescale=(fw1-fw2*3)/m_Intendstart;
    double m_startmark=fw2+m_smallavescale/2;

	CPen newPen;         
	newPen.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&newPen); 

	memDCJM.MoveTo(fw1-fw2*2+m_smallavescale+rectJM.left,f2-fh2*4+rectJM.top); // X坐标线,横线
    memDCJM.LineTo(fw2+rectJM.left,f2-fh2*4+rectJM.top); 

	memDCJM.MoveTo(fw2+rectJM.left,fh2*4+rectJM.top);    //左边竖线
    memDCJM.LineTo(fw2+rectJM.left,f2-fh2*4+rectJM.top); 


	for(i=0;i<=m_Intendstart;i++)    //写X轴小刻度值
	{
		memDCJM.MoveTo(m_startmark+m_smallavescale*i+rectJM.left,f2-fh2*4+2*m_penScale+rectJM.top);
		memDCJM.LineTo(m_startmark+m_smallavescale*i+rectJM.left,f2-fh2*4-2*m_penScale+rectJM.top);
	}
	CPen newPen2;         
	newPen2.CreatePen(PS_SOLID,2*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&newPen2); 
	for(i=0;i<=m_Intendstart/5;i++)    //写X轴大刻度值
	{
		memDCJM.MoveTo(m_startmark+m_avescale*i+rectJM.left,f2-fh2*4+4*m_penScale+rectJM.top);
		memDCJM.LineTo(m_startmark+m_avescale*i+rectJM.left,f2-fh2*4-4*m_penScale+rectJM.top);
		
	}
	
 	double m_freave=(f2-fh2*4*2)/(m_pmax-m_pmin);
    CPen PenXX;
	PenXX.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,128));
    memDCJM.SelectObject(&PenXX); 


	for (i=0;i<=m_Intendstart;i++)               //每个点对应高度，横线
	{
		memDCJM.MoveTo(fw2+m_smallavescale*i+rectJM.left,f2-fh2*4-(m_freave*(dataafterfilter[i+m_Intstart]-m_pmin))+rectJM.top);
		memDCJM.LineTo(fw2+m_smallavescale*(i+1)+rectJM.left,f2-fh2*4-(m_freave*(dataafterfilter[i+m_Intstart]-m_pmin))+rectJM.top);
	}

	CPen PenXXX;
	PenXXX.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,128));
    memDCJM.SelectObject(&PenXXX); 

	for (i=0;i<=m_Intendstart;i++)
	{
			
			memDCJM.MoveTo(fw2+m_smallavescale*(i+1)+rectJM.left,f2-fh2*4-(m_freave*(dataafterfilter[i+m_Intstart]-m_pmin))+rectJM.top);
			memDCJM.LineTo(fw2+m_smallavescale*(i+1)+rectJM.left,f2-fh2*4-(m_freave*(dataafterfilter[i+1+m_Intstart]-m_pmin))+rectJM.top);
	}
	memDCJM.MoveTo(fw2+m_smallavescale*(m_Intendstart+1)+rectJM.left,f2-fh2*4-(m_freave*(dataafterfilter[m_Intendstart+1+m_Intstart]-m_pmin))+rectJM.top);
	memDCJM.LineTo(fw2+m_smallavescale*(m_Intendstart+1)+rectJM.left,f2-fh2*4+rectJM.top);


	if (BoolButtondown==0)
	{
		Frepointi=0;
		Frepointx=0;
		Frepointy=0;
	}

	//----------数据写入字体及大小
	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
	CFont*   pOldFont=(CFont*)memDCJM.SelectObject(&font); 
	if (BoolButtondown==1)
	{
		CString str;
		CString str1;
		str.Format("%.4f",XRf4[Frepointi+m_Intstart]);//幅值为
		if (Frepointi<10-1)
		{
			str1.Format("%d",Frepointi+m_Intstart);
			str1=str1+"  ";
		}
		if (Frepointi>=10-1&&Frepointi<100-1)
		{
			str1.Format("%d",Frepointi+m_Intstart);
			str1=str1+" ";
		}
		if (Frepointi>=100-1)
		{
			str1.Format("%d",Frepointi+m_Intstart);
		}
		
		str1="当前谐波:"+str1;
        str1=str1+"  幅值为：";
        str1=str1+str+" um";
        memDCJM.TextOut(10,10,str1);	
		CPen newPenp;         
		newPenp.CreatePen(PS_SOLID,1,RGB(255,0,255));
		memDCJM.SelectObject(&newPenp); 
	    memDCJM.MoveTo(rectJM.left+fw2+m_smallavescale*Frepointi+m_smallavescale/2,rectJM.top+fh2*3); // X坐标线,横线
		memDCJM.LineTo(rectJM.left+fw2+m_smallavescale*Frepointi+m_smallavescale/2,rectJM.top+f2-fh2*4);
	}

}


void CJMAnalyse::DrawBaogao()
{
	////读取文件并绘图///
	ReadDataFromFile();
	int i=0,j=0;
	double fpdata[RecCount],datacir[RecCount],TsH[RecCount],DispAdata[RecCount];
	for (i=0;i<3600;i++)	
	{  
		fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
	}
	
	////////////////////////////////////////////////////////////////////////////////
    //手动处理后的数据进行调用函数计算	

	for(i=0;i<3600;i++)		
	{ 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //计算圆度误差转换位移公式	
	}		
	DrawFilter (FilterMode,datacir,TsH);

	for (i=0;i<RecCount;i++)
	{
		DispAdata[i]=TsH[i];
	}
  

    int X1,TempStartWZ;int TempCount;double Swi[RecCount];//波纹度轮廓不平度间距
	int X,Y;
	int M;
	int WZIndex[RecCount];//与中线相交的点的位置
	BOOL FLAGIndex[RecCount];//与中线相交的点的趋势
	double MaxF,TempF;
	int TempFnumber;  //TempFindex[3600]
    BOOL TempFHave;
	double MaxG,TempG;
	double SumG;
    double BWDA;    //波纹度算术平均偏差
	double BWDC;    //波纹度轮廓不平度的平均高度
	BOOL EndFlag;
	
	//BOOL BGlist.Clear=True,Glist.Visible=True;
	//int ABIndex;
	int DaNumberA=RecCount;
	int ZeroNumber=0;
    //  1---查找与中线相交的点
	EndFlag = FALSE;

    for (i=0;i<RecCount;i++)
    {
		FLAGIndex[i]=FALSE;
		WZIndex[i]=0;
		Swi[i]=0;
    }

	for (i=0;i<RecCount;i++)
	{
		if (i==0)
		{
			X=DaNumberA-1;
		}
		else
			X=i-1;

		if (i==DaNumberA-1)
		{
			EndFlag=TRUE;
			Y=1;
		}
		else
			Y=i+1;

		if (i==443)
		{
			i=i;
		}

		if (DispAdata[X] <=0  && DispAdata[Y]>0 )  //由负变正
		{
			if (DispAdata[i] <= 0)
			{
				i = Y;
			}
			ZeroNumber = ZeroNumber + 1;
			WZIndex[ZeroNumber]= i;
			FLAGIndex[ZeroNumber] =TRUE;
		}
       	else
			if (DispAdata[X] >=0  &&  DispAdata[Y]<0 ) //由正变负
			{
				if (DispAdata[i] >= 0)
				{
					i = Y;
				}
				ZeroNumber = ZeroNumber + 1;
				WZIndex[ZeroNumber] = i;
				FLAGIndex[ZeroNumber] = FALSE;
			}

		if (EndFlag==TRUE)
		{
			goto CON1;
		}
	}
	 
CON1:
	if (ZeroNumber%2>0)
	{
		ZeroNumber = ZeroNumber + 1;
	}
	X1 = 0, TempStartWZ = 0,TempCount = 0;

    double Pi= 3.1415927;
	int TempRadiusA =0; //Pi * X * 1000;// '圆周长度即轮廓取样长度
	                                   // X 被测件直径,单位:毫米

	for (i=1;i<=ZeroNumber;i++)
	{
		if (FLAGIndex[i]==TRUE)
		{
			Swi[i] = (TempRadiusA * (WZIndex[i] - X1)) / 1024;//TempRadiusA圆周长度即轮廓取样长度-
			X1=WZIndex[i];
			if (TempStartWZ == 0)
			{
				TempStartWZ = WZIndex[i];
			}
			else
				TempCount = TempCount + 1;

			if (i == ZeroNumber - 1)
			{
				Swi[ZeroNumber + 1] = (TempRadiusA * (1024 - X1)) / 1024;
				Swi[ZeroNumber + 1] = Swi[ZeroNumber + 1] + (TempRadiusA * TempStartWZ) / 1024;
                TempCount = TempCount + 1;
			}
			else
				if (i == ZeroNumber)
				{
					Swi[ZeroNumber + 1] = (TempRadiusA * (1024 - X1)) / 1024;
					Swi[ZeroNumber + 1] = Swi[ZeroNumber + 1] + (TempRadiusA * TempStartWZ) / 1024;
					TempCount = TempCount + 1;
				}
		}
	}
 
//////////////////   2---查找轮廓峰
    TempFnumber = 0;
	int TempFindex[3600];
	for (i=0;i<3601;i++)
	{
		TempFindex[i]=0;
	}
	for (i=1; i<=ZeroNumber; i++)
	{
		TempFHave =FALSE;
		X=WZIndex[i];
		if (i==ZeroNumber)
		{
			Y = WZIndex[1];
		}
		else
			Y = WZIndex[i + 1];

		if (FLAGIndex[i] == TRUE) //由负变正,为轮廓峰
		{
			if (i == ZeroNumber)
			{
				TempF = 0;
				for (j = X;j<=DaNumberA-1;j++)
				{
					if (  DispAdata[j]>TempF )
					{
						TempF = DispAdata[j];
                        TempFHave = TRUE;
                        M = j;
					}
				}

				for (j=0;j<=Y;j++)
				{
					if (DispAdata[j] > TempF)
					{
						TempF = DispAdata[j];
                        TempFHave =TRUE;
                        M = j;
					}
				}

            }

			else
				{
					TempF = 0;
				
					for (j = X;j<=Y;j++)
					{
						if (DispAdata[j] > TempF)
						{
							TempF = DispAdata[j];
							TempFHave = TRUE;
							M = j;
						}
					}
				}
            
			if (TempFHave == TRUE)
			{
				 TempFnumber = TempFnumber + 1;
                 TempFindex[TempFnumber] = M;
			}
		}

	}
	
	///////////////////////  3--显示查找到的轮廓峰 
 
   ///////////////////////   4---排序显示查找到的轮廓峰
   for (i=1; i<=TempFnumber;i++)
   {
	   MaxF = DispAdata[TempFindex[i]];
	   
		 for (j=i; j<=TempFnumber; j++)
	   {
		   if (DispAdata[TempFindex[j]] > MaxF)
		   {
			   MaxF = DispAdata[TempFindex[j]];
               M = TempFindex[i];
               TempFindex[i] = TempFindex[j];
               TempFindex[j] = M;
		   }
	   }
   }

   
  ////////////////////////5---排序后显示查找到的轮廓峰,最大100个
   if (TempFnumber >= 100)
   {
	   DispTempFnumber = 100;
   }
   else
	   DispTempFnumber = TempFnumber;
   
   for (i=1; i<=DispTempFnumber; i++)
   {
	   bogao[i]=0;
	   weizhi[i]=0;
   }
   for (i=1;i<=DispTempFnumber;i++)
   {
	   bogao[i]=DispAdata[TempFindex[i]];
       weizhi[i]=TempFindex[i]*0.1;
   }

}


void CJMAnalyse::DrawGrid3Frequency()
{
	double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=dright/2;
	int gridxnums=1;int gridynums=22;
	double dx= (rectJM.Width()-dright)/gridxnums;
	double dy=rectJM.Height()/gridynums;
    CRect gridRect(rectJM.left,rectJM.top,rectJM.left+dx*gridxnums,rectJM.top+dy*gridynums);
	//CPen gridPen(0,0,RGB(0,0,20)); //网格线的颜色
	CPen gridPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDCJM.FillSolidRect(dright+dx,dy*12,dx,dy,RGB(139,216,224));//给指定格子填充颜色
    CPen *oldpen=memDCJM.SelectObject(&gridPen);
	
    //------------------------------------------------------------
	memDCJM.FillSolidRect(dright,0,dx,dy,RGB(232,232,232));//给头行填充颜色
	memDCJM.FillSolidRect(dright,dy*5,dx,dy,RGB(232,232,232));//给指定行填充颜色
	memDCJM.FillSolidRect(dright,dy*13,dx,dy,RGB(232,232,232));//给指定行填充颜色


	memDCJM.SetBkMode(TRANSPARENT); 
		int m1=rectJM.left+dright+rectJM.Width()/100;
	int meter=rectJM.Height()/70;
	double m2=rectJM.left+dright+dx/2-rectJM.Width()/20;
	double m3=rectJM.left+dright+dx-rectJM.Width()/15;
	double mid=rectJM.left+dright+dx/2-rectJM.Width()/20;
 

	memDCJM.FillSolidRect(dright,dy*6,gridRect.right-1,dy,RGB(255,255,255));
	memDCJM.TextOut(m2,dy*6+meter,m_strMethod);
	memDCJM.TextOut(m2,dy*7+meter,"Gaussian");
	memDCJM.TextOut(m2,dy*8+meter,m_strlvbo);

	memDCJM.TextOut(mid ,meter,"圆度测量结果");
	memDCJM.TextOut(mid,dy*5+meter," 评定参数");
	memDCJM.TextOut(mid,dy*13+meter," 测量参数");
	
    memDCJM.TextOut(m1,dy+meter,"文件名");
	memDCJM.TextOut(m1,dy*2+meter,"测量时间");
	memDCJM.TextOut(m1,dy*6+meter,"评定方法");                                       
	memDCJM.TextOut(m1,dy*7+meter,"滤波器种类");                                              
	memDCJM.TextOut(m1,dy*8+meter,"滤波范围");    
	
	memDCJM.TextOut(m1,dy*14+meter,"圆度");
	memDCJM.TextOut(m1,dy*15+meter,"偏心");
	memDCJM.TextOut(m1,dy*16+meter,"偏心角度");  
	memDCJM.TextOut(m2,dy*14+meter,m_strdRONT);
	memDCJM.TextOut(m2,dy*15+meter,m_strdEcc);
	memDCJM.TextOut(m2,dy*16+meter,m_strdEccPos);
	memDCJM.TextOut(m3,dy*14+meter,"   um");
	memDCJM.TextOut(m3,dy*15+meter,"   um");
	memDCJM.TextOut(m3,dy*16+meter,"   度");
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDCJM.TextOut((m1+m2)/2,dy*1+meter,str);
	//显示测量时间
	str=m_time.Format("%Y-%m-%d %H:%M");
	memDCJM.TextOut((m1+m2)/2,dy*2+meter,str);
		//------------------------------------------------------------
	for(int m=0;m<=gridxnums;m++) //画出gridxnums条竖线                      
	{
		memDCJM.MoveTo(dright+m*dx,gridRect.bottom);
		memDCJM.LineTo(dright+m*dx,0);
	}
		
	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
	{
		memDCJM.MoveTo(rectJM.left+dright,n*dy);
		memDCJM.LineTo(rectJM.left+rectJM.Width(),n*dy);
	}
    
	memDCJM.MoveTo(rectJM.left+dright,rectJM.top);
	memDCJM.LineTo(rectJM.left+dright,rectJM.bottom);

	memDCJM.MoveTo(dright,dtop);
	memDCJM.LineTo(dright,dbottom);


}


void CJMAnalyse::OnBtnbgfx() 
{
	// TODO: Add your command handler code here
	FlagBogao=1;
	((CMainFrame*)AfxGetMainWnd())->SetToolBarState(-1,TRUE);
	((CMainFrame*)AfxGetMainWnd())->SetToolBarState(7,FALSE);
	OnPaint();
}

void CJMAnalyse::OnBtnppfx() 
{
	// TODO: Add your command handler code here

	CDlgfrequency1  dlg;
	CString strTemp;
	if (IDOK==dlg.DoModal())
	{
		m_Intstart=dlg.m_Intstart;
		m_Intend=dlg.m_Intend;
		FlagFrequency=1;	
		GetDlgItem(IDC_JManalyse)->EnableWindow(FALSE);
  		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(-1,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(7,FALSE);
		OnPaint();
	}
}

/*
  函数功能:计算波纹度
  函数返回7个参数，并且显示在表格中
*/
void CJMAnalyse::BWDANA(double *Direc)
{
   //A组 =0
   //源数据数组BWDAdata( 0 To DaNumberA - 1)
   //出口参数  七个测量参数
   //BWDA-'波纹度算术平均偏差
   //BWDC-'波纹度轮廓不平度的平均高度
   //ZeroNumber-'与中线相交的点的个数
  
   int    i=0,j=0,X=0,Y=0,WZIndex[3600],ZeroNumber,ABIndex=0,DaNumberA=3600,DaNumberB=3600;
    bool   FLAGIndex[3600],EndFlag,GLiGangFlag=false ;//qy changed//bool   FLAGIndex[3600],EndFlag,GLiGangFlag ;
   double SumG=0,BWDA=0,BWDC=0,BWDAdata[3600],BWDBdata[3600];
   double SumPJ=0, SumPJ2=0,SumF=0,MaxF=0,TempF=0,MaxG=0,TempG=0;
   double TempRadiusA=0,TempRadiusB=0,TempRadiusAB=0,ResultBWDAB[7][3600],GLiGangK; 
   double BWDABdata3[3600],BWDABdata17[3600];
 


      for (i=1;i<=7;i++)
    {
        TempJgBWD[i]=0;
    }

	   for (i=0;i<DaNumberA;i++)
	   {
		   BWDAdata[i]=Direc[i];
	   }
     


switch(ABIndex) // Select Case ABIndex
{
 
 case 0 : //' A
       SumPJ=0, SumPJ2=0, MaxF=0, MaxG=0;
       for (i=0;i<DaNumberA;i++)
       {
		   if(BWDAdata[i]>MaxF) 
		   {
			  MaxF = BWDAdata[i];
		   }
		   if(BWDAdata[i]<MaxG)
		   {
              MaxG = BWDAdata[i];
		   }	
		   SumPJ = SumPJ + fabs(BWDAdata[i]);
           SumPJ2 = SumPJ2 + BWDAdata[i]* BWDAdata[i];
       }
       BWDA = SumPJ / DaNumberA;
       TempJgBWD[1] = BWDA;
       BWDA = sqrt(SumPJ2 / DaNumberA);
       TempJgBWD[6] = BWDA;
       TempJgBWD[3] = MaxF;
       TempJgBWD[4] = fabs(MaxG);
       TempJgBWD[5] = fabs(MaxG)+MaxF;
       //'--------------------
       //1---查找与中线相交的点
       EndFlag = 0;
       ZeroNumber = 0;
	   for (i=0;i<DaNumberA ;i++)
	   {
		   if(i==0)
		   {
			   X=DaNumberA-1;
		   }
		   else
		   {
			   X=i-1;
		   }

	       if (i==DaNumberA-1)
	       {
			   EndFlag = 1;
			   Y = 1;           // 'GoTo CON1
	       }
	       else
		   {
			   Y = i + 1;
		   }

           if ((BWDAdata[X]<=0) && (BWDAdata[Y]>0)) //由负变正
           {
			  if (BWDAdata[i]<= 0)
			  {
				  i = Y;
				  ZeroNumber = ZeroNumber + 1;
			      WZIndex[ZeroNumber] = i;
			      FLAGIndex[ZeroNumber]= 1;
			  }
		   }
		   else if ((BWDAdata[X]>=0) && (BWDAdata[Y]<0))//由正变负
		   {
			  if (BWDAdata[i]>=0) 
			  {
			 	 i = Y;
				 ZeroNumber = ZeroNumber + 1;
				 WZIndex[ZeroNumber] = i;
			     FLAGIndex[ZeroNumber] = 0;
			  }	 
		   }	
          if (EndFlag == 1) 
		  { 
		      goto CON1;
		  }
	   }
      //'-----------------------


    CON1:   //'BGlist.Visible = True  'add
        //' For i = 1 To ZeroNumber 'add
        //'BGlist.AddItem WZIndex(i) & " " & FLAGIndex(i)'add
        // 'Next i'add
        //'BGlist.Visible = False'add
       TempJgBWD[7]= (TempRadiusA*2)/ZeroNumber;//'--TempRadiusA圆周长度即轮廓取样长度-
       SumF=0, SumG=0;
	   for (i=1;i<=ZeroNumber;i++)
	   { 
		   X = WZIndex[i];
		   if(i==ZeroNumber)
		   {
			   Y = WZIndex[1];
		   }
		   else
		   {
			   Y=WZIndex[i+1];
		   }

		  if(FLAGIndex[i]==1)//'由负变正,为轮廓峰
		  {
			 TempF = 0;

			 if(i==ZeroNumber)
			 {
			   for(j=Y;j<= X;j++) 
			   {
				   if(BWDAdata[j]>TempF) 
				   {
					   TempF = BWDAdata[j];
				   }
			   }
			 }  
			 else
			 {
			   for(j=X;j<=Y;j++)
			   {
				 if(BWDAdata[j]>TempF)
				 {
                   TempF = BWDAdata[j];
				 }
			   }
			 }
			 SumF=SumF+TempF;
		  }
		 else    // '由正变负,为轮廓谷
		 {
			 TempG = 0;
			 if(i == ZeroNumber)
			 {
				  for(j=Y;j<=X;j++) 
				  {
                    if(BWDAdata[j]<TempG)
					{
					   TempG = BWDAdata[j];
					}
				  }
			  }
			  else
			  {
				  for(j=X;j<=Y;j++) 
				  {
					 if( BWDAdata[j]< TempG)
					 {
					   TempG = BWDAdata[j];
					 }
				  }
			  }

          SumG = SumG + TempG;
		 }
		
	   }
      // 'BWDA = SumF / DaNumberA + Abs(SumG) / DaNumberA
      // 'BWDANaLabel(2).Caption = "Wc= " & GETINT(BWDA, 3)
      // '------------------------------
      BWDA=(SumF+fabs(SumG))/ZeroNumber;
      TempJgBWD[2]= BWDA;
	  for(i=0;i<7;i++)
	  {
		  m_BWD[i]=TempJgBWD[i+1];
	  }

 case 1:  //' B
       SumPJ=0,SumPJ2=0, MaxF=0, MaxG =0;
       for(i=0;i<DaNumberB;i++)
	   {
         if(BWDBdata[i]> MaxF)
		 {
            MaxF=BWDBdata[i];
		 }
         if(BWDBdata[i]<MaxG)
		 {
            MaxG = BWDBdata[i];
		 }
         SumPJ=SumPJ+fabs(BWDBdata[i]);
         SumPJ2=SumPJ2+(BWDBdata[i])*BWDBdata[i];
       }
       BWDA = SumPJ / DaNumberB;
       TempJgBWD[1]= BWDA;
       BWDA = sqrt(SumPJ2/DaNumberB);
       TempJgBWD[6] = BWDA;
       TempJgBWD[3] = MaxF;
       TempJgBWD[4] = fabs(MaxG);
       TempJgBWD[5] = fabs(MaxG)+MaxF;

       // 1---查找与中线相交的点
       EndFlag = 0;
       ZeroNumber = 0;
       for (i=0; i<DaNumberB; i++)
	   {
		  if (i == 0)
		  {
             X = DaNumberB - 1;
		  }
		  else
		  {
			   X = i - 1;
		  }
		  if(i==DaNumberB-1)
		  {
			   Y = 1 ;//'0
			   EndFlag = 1;//'GoTo CON2
		  }
		  else
		  {
			   Y = i + 1;
		  }
		 if((BWDBdata[X]<= 0) && (BWDBdata[Y]> 0) )
		 {
		    // '由负变正
			if((BWDBdata[i]<= 0) )
			{
				i = Y;
			}
			 ZeroNumber = ZeroNumber + 1;
			 WZIndex[ZeroNumber] = i;
			 FLAGIndex[ZeroNumber]= 1;
		 }
		 else
		 {
		     if( (BWDBdata[X] >= 0) && (BWDBdata[Y] < 0))//'由正变负
			 {
				if(BWDBdata[i] >= 0) 
				{
				   i = Y;
				}
				ZeroNumber = ZeroNumber + 1;
				WZIndex[ZeroNumber]= i;
			    FLAGIndex[ZeroNumber]=0;
			  }
		 } 
         if(EndFlag == 1) 
		 {
		    goto CON2;
		 }

	   }
   //'--------------------------------------------
  CON2:  //'BGlist.Visible = True  'add
       //' For i = 1 To ZeroNumber 'add
       //'BGlist.AddItem WZIndex(i) & " " & FLAGIndex(i)'add
       //'Next i'add
       //'BGlist.Visible = False'add
       TempJgBWD[7]= (TempRadiusB*2)/ZeroNumber;
       //'--TempRadiusA圆周长度即轮廓取样长度-
       SumF=0, SumG = 0;
       for(i=1;i<=ZeroNumber;i++) 
	   {
           X = WZIndex[i];
           if(i==ZeroNumber)
		   {
             Y = WZIndex[1];
		   }
           else
		   {
             Y = WZIndex[i+1];
		   }
           if(FLAGIndex[i]==1)  
		   {
			  // '由负变正,为轮廓峰
               TempF = 0;
               if(i == ZeroNumber)  
			   {
                 for(j=Y;j<=X;j++) 
				 {
                   if(BWDBdata[j] > TempF) 
				   {
                      TempF = BWDBdata[j];
				   }
				 }
			   }
             else
			 {
               for( j=X ;j<=Y;j++)
			   {
                  if(BWDBdata[j]> TempF) 
				  {
                     TempF = BWDBdata[j];
				  }
			   }
			 }
             SumF = SumF + TempF;
		   }

           else//  '由正变负,为轮廓谷
		   {
             TempG = 0;
             if(i == ZeroNumber)
			 {
                for(j = Y;j<= X;j++) 
				{
                  if(BWDBdata[j] < TempG)
				  {
                     TempG = BWDBdata[j];
				  }
              
				}
			 }
             else
			 {
               for(j = X;j<=Y;j++)
			   {
                  if( BWDBdata[j] < TempG) 
				  {
                     TempG = BWDBdata[j];
				  }
			   }
			 }
             SumG = SumG + TempG;
		   }
	   }
       //'------------------------------
       BWDA = (SumF + fabs(SumG))/ZeroNumber;
       TempJgBWD[2] = BWDA;

 }
quit:
    for(i=1;i<=7;i++)
	{
      if( GLiGangFlag == 1 ) 
	  {
        TempJgBWD[i] = TempJgBWD[i]* GLiGangK;
	  }
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
  for (i=0;i<3600;i++)	
	{  
		fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
	}
*/
  void CJMAnalyse::SubQKDataChuli(CString path,int JM, int Number,BOOL AutoOrManChuli, double *Soudata, double *Resdata,int m_IndexStart, int m_IndexEnd)
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
	double Max, Min;
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
	for (i=0;i<100;i++)
	{
         QKnumberL[i]=0;
         QKnumberR[i]=0;
	}
	///////////////手工剔除//////////////////////////////
    // if( Number==0) 
    //	Exit Sub;

    //	将文件名传过来，进行缺口个数的统计
	shuju0 ManDeal[3600];
    double gh[3600];//定时结构体数据
//	std::ifstream fin(path,std::ios::binary);
	for (i=0;i<Number;i++)
	{	
		Soudata[i]=m_dataJM[i+1+m_LBtnJM*Number].data;
		gh[i]=Soudata[i];
		ManDeal[i].data=m_dataJM[i+1+m_LBtnJM*Number].data;
		ManDeal[i].selected=m_dataJM[i+1+m_LBtnJM*Number].selected;
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
	 
	if (AutoOrManChuli==FALSE )
	  {
		goto Automode;
	  }
	  
    else /*(AutoOrManChuli==true ) */
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
	   YDQKdata[i]=((Soudata[i]-2048)*10)/(GG1*GG2*4096); //将数据转换成位移
	   if(i== Number - 1) //如果数据为最后一个数
		   BHVdata[i]=((Soudata[0]-2048)*10)/(GG1*GG2*4096)-((Soudata[i]-2048)*10)/(GG1*GG2*4096);//用第一个数减去最后一个数
	   else
		   BHVdata[i]=((Soudata[i+1]-2048)*10)/(GG1*GG2*4096)-((Soudata[i]-2048)*10)/(GG1*GG2*4096);//否则的话用下一个数减去上一个数	
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
					if(abs(TempWZPL[TempNA]) > Number / 2) 
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
	
/*	int Starti,Endi;//本小段程序实现在自动去缺口以后反映在图形界面上的变化
    for( i=1;i<=QkNumber;i++)
	{
       Starti=MinIndex[i]-GBzDot;
       Endi=MaxIndex[i]+ GBzDot;
       ChangeValueOfSelectJM(path,1+m_LBtnJM*Number+Starti,1+m_LBtnJM*Number+Endi,1);
	}

*/
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
		   YDQKdata[i] = ((Soudata[i]-2048)*10)/(GG1*GG2*4096);
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

void CJMAnalyse::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_JManalyse.GetSafeHwnd())
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
		m_JManalyse.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}
}

void CJMAnalyse::ReadDataFromFile()
{
	////读取文件并绘图///
	std::ifstream fin(pathJM, std::ios::binary);
   	for (int i=0;i<=LenDataJM;i++)
	{	
		fin.read((char*)&m_dataJM[i], sizeof(shuju0)); //读取数据
	}
	fin.read((char*)&GG1,sizeof(double));
	fin.read((char*)&GG2,sizeof(double));
	fin.read((char*)&m_time,sizeof(CTime));
    fin.close();

}

void CJMAnalyse::OnPrint() 
{
	// TODO: Add your command handler code here
		CFormView::OnFilePrint();
}

void CJMAnalyse::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFormView::OnPrepareDC(pDC, pInfo);
	pDC->SetMapMode(MM_ANISOTROPIC);
}

BOOL CJMAnalyse::OnPreparePrinting(CPrintInfo* pInfo) 
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

void CJMAnalyse::OnDraw(CDC* pDC) 
{
	int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);//X方向一英寸像素的个数,A4纸
    int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);//Y方向一英寸像素的个数
	int xLogPixPerMM=xLogPixPerInch/25.4;//X方向1mm像素的个数
	int yLogPixPerMM=yLogPixPerInch/25.4;//Y方向1mm像素的个数
	m_penScale=xLogPixPerInch/96;//笔的比例，将线变粗，xLogPixPerInch是表示A4纸一英寸含有的像素个数，96是屏幕的，比例为从屏幕到纸pen所需放大的倍数
	
	//打印框的尺寸为150*250(mm)
	CPoint pt(0,0);//纸张的左上角为00点
	CSize  sz(270*xLogPixPerMM,200*yLogPixPerMM);//sz矩形框的大小，X方向和Y方向像素的总个数，打印都是按像素数打印的
	CRect  tRect(pt,sz);//定义的打印区的矩形框，蓝色框框的（除了页边距的）的为00点，rect1是表格的矩形框	
	rectJM.top=tRect.top+25*yLogPixPerMM;//rect的上下左右都是表示的像素的个数
	rectJM.right=tRect.right;
	rectJM.left=tRect.left+20*xLogPixPerMM;
	rectJM.bottom=tRect.bottom-25*yLogPixPerMM;
	
	
	pOldBmp = NULL;                           // 将旧的位图指针置空	
	memDCJM.CreateCompatibleDC(pDC);             // 创建内存绘图设备，使内存位图的DC与控件的DC关联
	memBitmap.CreateCompatibleBitmap(pDC,tRect.right,tRect.bottom);//参数为宽度和高度
	pOldBmp = memDCJM.SelectObject(&memBitmap);
    memDCJM.FillSolidRect(tRect.left,tRect.top,tRect.right,tRect.bottom,RGB(255,255,255));//给矩形框填充白色
	
	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));//原来的penscale=1，现在不是
	memDCJM.SelectObject(&RectPen);               
	memDCJM.Rectangle(rectJM.left,rectJM.top,rectJM.right,rectJM.bottom); //静态框加上 颜色 边框
	
	//修改打印字体大小
	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
		DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
	CFont*   pOldFont=(CFont*)memDCJM.SelectObject(&font); 
	
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
	//CFont newFont;
	CFont *oldFont;
	
	newFont.CreateFontIndirect(&newLogFont);
	//oldFont = memDCJM.SelectObject(&newFont );
	memDCJM.SelectObject(&newFont);
	
	//绘制上栏
	memDCJM.MoveTo(rectJM.left,rectJM.top);
	memDCJM.LineTo(rectJM.left,rectJM.top-10*xLogPixPerMM);
	memDCJM.MoveTo(rectJM.left,rectJM.top-10*xLogPixPerMM);
	memDCJM.LineTo(rectJM.right,rectJM.top-10*xLogPixPerMM);
	memDCJM.MoveTo(rectJM.right,rectJM.top-10*xLogPixPerMM);
	memDCJM.LineTo(rectJM.right,rectJM.top);
	//绘制下栏
	memDCJM.MoveTo(rectJM.left,rectJM.bottom);
	memDCJM.LineTo(rectJM.left,rectJM.bottom+10*xLogPixPerMM);
	memDCJM.MoveTo(rectJM.left,rectJM.bottom+10*xLogPixPerMM);
	memDCJM.LineTo(rectJM.right,rectJM.bottom+10*xLogPixPerMM);
	memDCJM.MoveTo(rectJM.right,rectJM.bottom+10*xLogPixPerMM);
	memDCJM.LineTo(rectJM.right,rectJM.bottom);
	RectPen.DeleteObject();

	//写入信息
    memDCJM.TextOut(0.8*rectJM.left+200*xLogPixPerMM,rectJM.bottom+11*yLogPixPerMM,
		"广州威而信精密仪器有限公司");
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_strOperatorName;
	str.Format("操作员:%s",str);
	memDCJM.TextOut(rectJM.left+75*xLogPixPerMM,rectJM.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineModel;
	str.Format("机床型号:%s",str);
	memDCJM.TextOut(rectJM.left+115*xLogPixPerMM,rectJM.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineName;
	str.Format("机床:%s",str);
	memDCJM.TextOut(rectJM.left+155*xLogPixPerMM,rectJM.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strProcess;
	str.Format("工序:%s",str);
	memDCJM.TextOut(rectJM.left+195*xLogPixPerMM,rectJM.top-7*yLogPixPerMM,str);
	
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceModel;
	str.Format("工件型号:%s",str);
	memDCJM.TextOut(rectJM.left+15*xLogPixPerMM,rectJM.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceNum;
	str.Format("工件编号:%s",str);
	memDCJM.TextOut(rectJM.left+75*xLogPixPerMM,rectJM.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strIndent;
	str.Format("订单:%s",str);
	memDCJM.TextOut(rectJM.left+135*xLogPixPerMM,rectJM.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strInspector;
	str.Format("检测员:%s",str);
	memDCJM.TextOut(rectJM.left+195*xLogPixPerMM,rectJM.bottom+3*yLogPixPerMM,str);

	((CMainFrame*)AfxGetMainWnd())->JMCL=BtnChuliDwon; //鼠标单击的截面	
	

	if(m_BOOLSegmentprocess==0  &&  FlagFrequency==0 )
	{	
		SubQKDataChuli(pathJM,m_LBtnJM,3600,!((CMainFrame*)AfxGetMainWnd())->m_bAutoQK,m_CirCal, Resdata,m_IndexStart,m_IndexEnd);
		if (CirEvalue==0)
		{
		    PrintJMofYZD();
			SubAnaData (FilterMode, Resdata,GResult,GG1,GG2);	//圆度
			dRONT=GResult[1];
			SubAnaData(1,  Resdata,GResult,GG1,GG2);    //1
			dEcc=GResult[1]/2;  //偏心
			dEccPos=GResult[3];  //偏心角
			
			m_strFilterMode.Format("%d",FilterMode);
			m_strdRONT.Format("%.3f",dRONT); //将数据结果转换成字符串的形式，便于显示在表格中
			m_strdEcc.Format("%.2f",dEcc);
			m_strdEccPos.Format("%.2f",dEccPos);
			//显示波纹度
			m_Wa.Format("%.2f",m_BWD[0]); //将数据结果转换成字符串的形式，便于显示在表格中
			m_Wc.Format("%.2f",m_BWD[1]);
			m_Wp.Format("%.2f",m_BWD[2]);
			m_Wv.Format("%.2f",m_BWD[3]); //将数据结果转换成字符串的形式，便于显示在表格中
			m_Wt.Format("%.2f",m_BWD[4]);
			m_Wq.Format("%.2f",m_BWD[5]);
		    m_Wwm.Format("%.2f",m_BWD[6]);
			
		}
		else if (CirEvalue==1)
		{
			PrintCircleMZC();
			MZCyuandu(Resdata);
		}        
		
		else if (CirEvalue==2)
		{
			PrintCircleMCC();
			MCCyuandu(Resdata);
		}    
		
		else if (CirEvalue==3)
		{
			PrintCircleMIC();
			MICyuandu(Resdata);
		}
		
		
		if (FlagBogao==0)
		{
			DrawGride1();
			
		}	
		if (FlagBogao==1)
		{
			DrawBaogao();
			DrawGride1();			
		}
	}
    if(m_BOOLSegmentprocess==1 &&  FlagFrequency==0 )
	{
		DrawGrid2();
        Segmentationprocess();
	}	
	if(m_BOOLSegmentprocess==0  && FlagFrequency==1 )
	{
		DrawFrequency();
		DrawGrid3Frequency();  
	}  
	newFont.DeleteObject();
	pDC->BitBlt(tRect.left,tRect.top,tRect.right,tRect.bottom,&memDCJM,0,0,SRCCOPY); //把已经绘好的图显示在制定位置上
	memDCJM.SelectObject(pOldBmp);
	memDCJM.DeleteDC();
    memBitmap.DeleteObject();//释放内存设备// TODO: Add your specialized code here and/or c


}

void CJMAnalyse::PrintSegmentationprocess()
{
// 	CFont   font; 
// 	font.CreateFont(13,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
// 	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  	
// 	CFont*   pOldFont=(CFont*)memDCJM.SelectObject(&font); 
	memDCJM.SelectObject(&newFont);
	ReadDataFromFile();
	
	//定义后面将要用到的变量
    double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left ,dbottom=rectJM.bottom,dX0=rectJM.Width()*(3/5)/2;
	double fw1=3*rectJM.Width()/5,f1=rectJM.Width(),f2=rectJM.Height();                                                 	                             
    double fw2=rectJM.Width()/30;
    double fh=rectJM.Height()/2+rectJM.top;
	double fh1=rectJM.Height()/4;
	double fh2=rectJM.Height()/30;
	
	CPen newPen;         
	newPen.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&newPen); 

	memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh); // 中线,横线
    memDCJM.LineTo(fw2*3/2+rectJM.left,fh); 

	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);//左边竖线
    memDCJM.LineTo(fw2*3/2+rectJM.left,fh+fh2*7); 

	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);  //左边箭头
    memDCJM.LineTo(fw2*3/2+rectJM.left-6*m_penScale,fh-fh2*7+fh2*0.4); 
	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);  
    memDCJM.LineTo(fw2*3/2+rectJM.left+6*m_penScale,fh-fh2*7+fh2*0.4); 

	memDCJM.TextOut(fw2+rectJM.left,fh-fh1-20*m_penScale,"单位：微米");	

	memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh+fh2*7);
	memDCJM.LineTo(fw2*3/2+rectJM.left,fh+fh2*7);

	

    int m_endstart=m_endposition-m_startposition;
	CString mark;
	double m_avescale=(fw1-2*fw2)/4;
	double m_smallavescale=(fw1-2*fw2)/(m_splitnumber*5);
	double m_splitave=(fw1-2*fw2)/m_splitnumber;
	double m_splitmark=m_endstart/m_splitnumber;
    int i;

	/////////////////////////////////// 标注横坐标 ////////
	for(i=0;i<m_splitnumber*5;i++)    //写X轴小刻度值
	{
		memDCJM.MoveTo(fw2*3/2+rectJM.left+m_smallavescale*i,fh+fh2*7);
		memDCJM.LineTo(fw2*3/2+rectJM.left+m_smallavescale*i,fh+fh2*7-fh/50);
	}

	CPen newPenfenduan;         
	newPenfenduan.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&newPenfenduan); 


	for(i=0;i<=m_splitnumber;i++)    //画分段线,X大刻度值
	{
		memDCJM.MoveTo(fw2*3/2+rectJM.left+m_splitave*i,fh+fh2*7);
		memDCJM.LineTo(fw2*3/2+rectJM.left+m_splitave*i,fh+fh2*7-fh/30);
		mark.Format("%.1f",m_splitmark*i+m_startposition);
		memDCJM.TextOut(rectJM.left+fw2*7/8+m_splitave*i,fh+fh2*7+fh/60,mark);	
	}

    memDCJM.SetBkMode(TRANSPARENT); 
	////////////////////////////////////////////////////////////////////////////////
    double datacir[3600];
	double m_datamax=0.0,m_datamin=0.0,m_psum=0;

	//////////////////////////////////////////////
	for(i=0;i<3600;i++)		
	{ 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);   
	}	
	DrawFilter (FilterMode,datacir,dataafterfilter);
	//////////////////////////////////////////////////
	//////////////求出绘图轮廓的最大值和最小值//////////////
	m_datamin=dataafterfilter[0];
	m_datamax=dataafterfilter[0];
	for (i=100;i<3500;i++)	
	{  
		if (m_datamax<dataafterfilter[i])
		{
			m_datamax=dataafterfilter[i];
		}
		if (m_datamin>dataafterfilter[i])
		{
			m_datamin=dataafterfilter[i];
		}
		m_psum=m_psum+dataafterfilter[i];
	}
    m_Middle=m_psum/3400;
    m_OutIn=m_datamax-m_datamin;
    double m_jiange=fh2*10/m_OutIn;


	CPen newPeny;  // 中线平行线
	newPeny.CreatePen(PS_DOT,1*m_penScale,RGB(205,201,201));
    memDCJM.SelectObject(&newPeny);
	int j;
	for(i=fh2,j=1;j<6;j++)
	{
		memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh+i*j);
		memDCJM.LineTo(fw2*3/2+rectJM.left,fh+i*j);
	}
    
	for(i=fh2,j=1;j<6;j++)
	{
		memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh-i*j);
		memDCJM.LineTo(fw2*3/2+rectJM.left,fh-i*j);
	}


	mark.Format("%.2f",m_Middle);   //转化后的数值，Y中线坐标显示
	memDCJM.TextOut(rectJM.left+fw2*1/3,fh-fh*1/60,mark);

	mark.Format("%.2f",m_datamax-m_Middle);   //上Y坐标值显示
	memDCJM.TextOut(rectJM.left+fw2*1/3,fh-fh2*5-fh*1/60,mark);

	mark.Format("%.2f",m_datamin-m_Middle);   //下Y坐标值显示
	memDCJM.TextOut(rectJM.left+fw2*1/3,fh+fh2*5-fh*1/60,mark);
	
	double m_aveangle=3600/360;
	double m_startpoint=m_aveangle*m_startposition;
	double m_endpoint=m_aveangle*m_endposition;
    double m_endstartpiont=m_endpoint-m_startpoint;
	double m_avesize=(fw1-2*fw2)/m_endstartpiont;
	double meter=10;//间隔点数

	for (i=m_startpoint+10;i<m_endpoint;i=i+5)//显示图形
	{
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{
			CPen newPenrelate; 
			newPenrelate.CreatePen(PS_SOLID,1*m_penScale,RGB(0,255,0));
			memDCJM.SelectObject(&newPenrelate); 
			memDCJM.SetPixel(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint+meter),fh-(dataafterfilter[i]-m_Middle)*m_jiange,RGB(0,255,0));
  			memDCJM.MoveTo(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint+meter),fh-(dataafterfilter[i]-m_Middle)*m_jiange);
   			memDCJM.LineTo(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint),fh-(dataafterfilter[i-10]-m_Middle)*m_jiange);
			
		}

		else
		{   
			CPen newPenrelate; 
			newPenrelate.CreatePen(PS_SOLID,1*m_penScale,RGB(255,0,255));
			memDCJM.SelectObject(&newPenrelate); 
			memDCJM.SetPixel(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint+meter),fh-(dataafterfilter[i]-m_Middle)*m_jiange,RGB(255,0,255));
 			memDCJM.MoveTo(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint+meter),fh-(dataafterfilter[i]-m_Middle)*m_jiange);
   			memDCJM.LineTo(fw2*3/2+rectJM.left+m_avesize*(i-m_startpoint),fh-(dataafterfilter[i-10]-m_Middle)*m_jiange);
		}
	}


	////////////////////////////////// 计算分段处理：最大，最小值 ///

	int gridxnums=1;int gridynums=22;
	double dx= (rectJM.Width()-dright)/gridxnums;
	double dy=rectJM.Height()/gridynums;
	int meter2=rectJM.Height()/70;
	double m3=rectJM.left+dright+dx-rectJM.Width()/15;

    double m_spiltavenum;
	m_spiltavenum=(m_endpoint-m_startpoint)/m_splitnumber;
  
	for (j=0;j<m_splitnumber;j++)
	{	
			m_maxsplit[j]=0;
			m_minsplit[j]=0;

		for (i=m_startpoint+j* m_spiltavenum; i< m_startpoint+(j+1)* m_spiltavenum;  i++)
		{
		
			if ( m_dataJM[i+1+m_LBtnJM*3600].selected==0 )
			{
				if (m_maxsplit[j]<dataafterfilter[i])
				{
					m_maxsplit[j]=dataafterfilter[i];
				}

				if (m_minsplit[j]>dataafterfilter[i])
				{
					m_minsplit[j]=dataafterfilter[i];
				}			
			}

			m_PV[j]=fabs(m_maxsplit[j])+fabs(m_minsplit[j]);		
		}

	}
	CString m_PVcstring;
	for (i=0; i<m_splitnumber; i++)
	{
		
		m_PVcstring.Format("%.2f",m_PV[i]);
		memDCJM.TextOut(m3-rectJM.Width()/30,dy*(10+i)+meter2+rectJM.top,m_PVcstring);
	}
}

void CJMAnalyse::PrintDrawGrid3Frequency()
{
	double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=dright/2;
	int gridxnums=1;int gridynums=22;
	double dx= (rectJM.Width()+rectJM.left-dright)/gridxnums;
	double dy=rectJM.Height()/gridynums;
    CRect gridRect(rectJM.left,rectJM.top,rectJM.left+dx*gridxnums,rectJM.top+dy*gridynums);
	//CPen gridPen(0,0,RGB(0,0,20)); //网格线的颜色
	CPen gridPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDCJM.FillSolidRect(dright+dx,dy*12+rectJM.top,dx,dy,RGB(139,216,224));//给指定格子填充颜色
    CPen *oldpen=memDCJM.SelectObject(&gridPen);
	
	memDCJM.SelectObject(&newFont);
	
    //------------------------------------------------------------
	memDCJM.FillSolidRect(dright,0+rectJM.top,dx,dy,RGB(232,232,232));//给头行填充颜色
	memDCJM.FillSolidRect(dright,dy*5+rectJM.top,dx,dy,RGB(232,232,232));//给指定行填充颜色
	memDCJM.FillSolidRect(dright,dy*13+rectJM.top,dx,dy,RGB(232,232,232));//给指定行填充颜色
	
	
	memDCJM.SetBkMode(TRANSPARENT); 
	int m1=dright+rectJM.Width()/100;
	int meter=rectJM.Height()/70;
	double m2=dright+dx/2-rectJM.Width()/20;
	double m3=dright+dx-rectJM.Width()/15;
	double mid=dright+dx/2-rectJM.Width()/20;
	
	
	memDCJM.FillSolidRect(dright,dy*6,gridRect.right-1*m_penScale,dy,RGB(255,255,255));
	memDCJM.TextOut(m2,dy*6+meter+rectJM.top,m_strMethod);
	memDCJM.TextOut(m2,dy*7+meter+rectJM.top,"Gaussian");
	memDCJM.TextOut(m2,dy*8+meter+rectJM.top,m_strlvbo);
	
	memDCJM.TextOut(mid ,meter+rectJM.top,"圆度测量结果");
	memDCJM.TextOut(mid,dy*5+meter+rectJM.top," 评定参数");
	memDCJM.TextOut(mid,dy*13+meter+rectJM.top," 测量参数");
	
    memDCJM.TextOut(m1,dy+meter+rectJM.top,"文件名");
	memDCJM.TextOut(m1,dy*2+meter+rectJM.top,"测量时间");
	memDCJM.TextOut(m1,dy*6+meter+rectJM.top,"评定方法");                                       
	memDCJM.TextOut(m1,dy*7+meter+rectJM.top,"滤波器种类");                                              
	memDCJM.TextOut(m1,dy*8+meter+rectJM.top,"滤波范围");    
	
	memDCJM.TextOut(m1,dy*14+meter+rectJM.top,"圆度");
	memDCJM.TextOut(m1,dy*15+meter+rectJM.top,"偏心");
	memDCJM.TextOut(m1,dy*16+meter+rectJM.top,"偏心角度");  
	memDCJM.TextOut(m2,dy*14+meter+rectJM.top,m_strdRONT);
	memDCJM.TextOut(m2,dy*15+meter+rectJM.top,m_strdEcc);
	memDCJM.TextOut(m2,dy*16+meter+rectJM.top,m_strdEccPos);
	memDCJM.TextOut(m3,dy*14+meter+rectJM.top,"   um");
	memDCJM.TextOut(m3,dy*15+meter+rectJM.top,"   um");
	memDCJM.TextOut(m3,dy*16+meter+rectJM.top,"   度");
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDCJM.TextOut((m1+m2)/2,dy*1+meter+rectJM.top,str);
	//显示测量时间
	str=m_time.Format("%Y-%m-%d %H:%M");
	memDCJM.TextOut((m1+m2)/2,dy*2+meter+rectJM.top,str);
	//------------------------------------------------------------
	memDCJM.SelectObject(&gridPen);
	for(int m=0;m<=gridxnums;m++) //画出gridxnums条竖线                      
	{
		memDCJM.MoveTo(dright+m*dx,gridRect.bottom);
		memDCJM.LineTo(dright+m*dx,rectJM.top);
	}
	
	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
	{
		memDCJM.MoveTo(dright,n*dy+rectJM.top);
		memDCJM.LineTo(rectJM.left+rectJM.Width(),n*dy+rectJM.top);
	}
    
	gridPen.DeleteObject();
	memDCJM.MoveTo(dright,rectJM.top);
	memDCJM.LineTo(dright,rectJM.bottom);
	gridPen.DeleteObject();
	
	//newFont.DeleteObject();
	
	//memDCJM.MoveTo(dright,dtop);
	//memDCJM.LineTo(dright,dbottom);

}

void CJMAnalyse::OnAmplifyScale() 
{
	// TODO: Add your command handler code here
	CAmpScale dlg;
	dlg.m_DefaultAmpscale=ratio1;
	dlg.m_AmpScale=ratio1;
	UpdateData(false);
	if (IDOK==dlg.DoModal())
	{
		m_ModeChoose=dlg.m_ModeChoose;
		m_AmpScale=dlg.m_AmpScale;
		flagAmpscale=1;
	}
	OnPaint();
}

void CJMAnalyse::PrintJMofYZD()
{
	int    i;
	double datas[3600],drealx[3600],drealy[3600],theta=0,datacir[3600];
    double dRmax=0.0,dRmin=0.0,m_datamax=0.0,m_datamin=0.0;

    LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//对应圆柱所有的点数
    m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//鼠标单击选中的截面
	pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
 
	std::ifstream fin(pathJM, std::ios::binary);
   	for ( i=0;i<=LenDataJM;i++)
	{	
		fin.read((char*)&m_dataJM[i], sizeof(shuju0)); //读取数据
	}
	fin.read((char*)&GG1,sizeof(double));
	fin.read((char*)&GG2,sizeof(double));
	fin.read((char*)&m_time,sizeof(CTime));
    fin.close();
  
	//定义后面将要用到的变量
    double dY0= rectJM.Height()/2+rectJM.top,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5*1/2+rectJM.left;
	CString strcodinate;
	//rin为0圆，RSLC为2018圆，rout为4096圆
	int x1,y1,x2,y2;
	double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	dw=2*PI/3600;

	//绘制底色圆环带
    CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //绘制黄色圆环带 
    memDCJM.SelectObject(&penRing); 
	for(th=0;th<PI*2;th+=dw)
	{
		x1=dX0-(int)rin*cos(th);
		y1=dY0-(int)rin*sin(th);
		x2=dX0-(int)rout*cos(th);
		y2=dY0-(int)rout*sin(th);
		memDCJM.MoveTo(x1,y1);
		memDCJM.LineTo(x2,y2);	 
	}	 
	penRing.DeleteObject();	

	CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //绘制圆环变紫色带 
    memDCJM.SelectObject(&ping); 
    for (i=0;i<3600;i++)
	{
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{
			x1=dX0-(int)rin*cos(i*dw-PI);
			y1=dY0-(int)rin*sin(i*dw-PI);
			x2=dX0-(int)rout*cos(i*dw-PI);
			y2=dY0-(int)rout*sin(i*dw-PI);
			memDCJM.MoveTo(x1,y1);
			memDCJM.LineTo(x2,y2);
		}		
	}	
    ping.DeleteObject();
   	//----------构造动态圆环---------
	if (flagmanchuli==1)
	{	   
        m_IndexStart=alpha1/dw;
		m_IndexEnd=alpha2/dw;	
		if (FlagMove%2==0)
		{
			DynamicDrawCircleJM(m_IndexStart,m_IndexEnd);			
		}
		else  
		{      
			if ( 6.2814-alpha2>6.2814-alpha1)
			{		
				DynamicDrawCircleJM(m_IndexStart,3599);	
                DynamicDrawCircleJM(0,m_IndexEnd);
			}
			else if ( 6.2814-alpha1>6.2814-alpha2)
			{
				DynamicDrawCircleJM(m_IndexStart,0);	
                DynamicDrawCircleJM(3599,m_IndexEnd);				
			}			
		}
	}
	
	//----------------------以上代码实现灵活的选取-----------
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));     //创建空画刷，防止遮挡内
	CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//选择画刷 
	//double Rmincir=dX0/2-100;
    double Rmincir=rin*5/12;
	CPen pencir;
	pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
    memDCJM.SelectObject(&pencir);   
    memDCJM.Ellipse(dX0-RSLC,dY0-RSLC,dX0+RSLC,dY0+RSLC);//绘制基圆(2048)
	pencir.DeleteObject();	
	
	CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	memDCJM.SelectObject(&RoutORin);               
    memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//绘制圆环内圆
    memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//绘制圆环外圆
    RoutORin.DeleteObject();
   
	///////////////////////////////////////////////////////////////////
	///////////////////////绘制坐标轴//////////////////////////////////
    double EverystrcodX=(rout)/10,EverystrcodY=EverystrcodX;
	CPen pen1 (PS_DOT,1*m_penScale,RGB(125,125,125));
	memDCJM.SelectObject(&pen1); 
	memDCJM.MoveTo(dX0-EverystrcodX*7,dY0-EverystrcodX*7);
    memDCJM.LineTo(dX0+EverystrcodX*7,dY0+EverystrcodX*7);
	memDCJM.MoveTo(dX0-EverystrcodX*7,dY0+EverystrcodX*7);
    memDCJM.LineTo(dX0+EverystrcodX*7,dY0-EverystrcodX*7);
	pen1.DeleteObject();

	CPen penCoordinate (PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDCJM.SelectObject(&penCoordinate); 
    memDCJM.MoveTo(dX0-EverystrcodX*10,dY0);
    memDCJM.LineTo(dX0+EverystrcodX*10,dY0);                    //绘制x轴
	memDCJM.MoveTo(dX0-EverystrcodX*10,dY0-10); 
	memDCJM.LineTo(dX0-EverystrcodX*10,dY0+10);
	memDCJM.MoveTo(dX0+EverystrcodX*10,dY0-10); 
	memDCJM.LineTo(dX0+EverystrcodX*10,dY0+10);
	//memDCJM.TextOut(dX0+EverystrcodX*10+10,dY0-10,"0°");
	//memDCJM.TextOut(dX0-rout-40,dY0-10,"180°");
	memDCJM.TextOut(dX0+rout*1.05,dY0-rout*0.025,"0°");
	memDCJM.TextOut(dX0-rout*1.15,dY0-rout*0.025,"180°");
	
	memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45°");
	memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225°");

    memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
    memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //绘制y轴
    memDCJM.MoveTo(dX0+10,dY0+EverystrcodY*10);
   	memDCJM.LineTo(dX0-10,dY0+EverystrcodY*10);
	memDCJM.MoveTo(dX0+10,dY0-EverystrcodY*10);
   	memDCJM.LineTo(dX0-10,dY0-EverystrcodY*10);
	//memDCJM.TextOut(dX0-10,dY0+EverystrcodY*10+10,"270°");
    //memDCJM.TextOut(dX0-10,dY0-EverystrcodY*10-30,"90°");
	memDCJM.TextOut(dX0-rout*0.026,dY0+rout*1.04,"270°");
    memDCJM.TextOut(dX0-rout*0.026,dY0-rout*1.1,"90°");
	memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135°");
    memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315°");

	
	for( i=0; i<10; i++)
	{
		strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //绘制X正轴刻度
		memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	}	
	for( i=0; i<10; i++)
	{
		strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //绘制X负轴刻度
		memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	}
	for( i=0; i<10; i++)      //写Y正轴刻度值
	{
		strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		memDCJM.MoveTo(dX0-4*m_penScale, dY0-i*EverystrcodY);
	    memDCJM.LineTo(dX0+4*m_penScale, dY0-i*EverystrcodY);	
	}
	for( i=0; i<10; i++)  
	{
		strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		memDCJM.MoveTo(dX0-4*m_penScale, dY0+i*EverystrcodY);
		memDCJM.LineTo(dX0+4*m_penScale, dY0+i*EverystrcodY);
	}
	penCoordinate.DeleteObject();
    ////////////////////////////////////////////////////////////////////////////////
    //第几个截面参数是传递过来的///////////////////截面参数是M;
	for (i=0;i<3600;i++)	
	{  
		fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		m_CirCal[i]=fpdata[i];    //计算圆度误差转换位移公式		
	}	
	////////////////////////////////////////////////////////////////////////////////
    //手动处理后的数据进行调用函数计算	
	for(i=0;i<3600;i++)		
	{ 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //计算圆度误差转换位移公式	
	}		
	DrawFilter (FilterMode,datacir,dataafterfilter);//调用滤波函数，滤波之后的数据反映在界面绘制上
	//////////////////////////////////////////////////
	//////////////求出绘图轮廓的最大值和最小值//////////////
	m_datamin=dataafterfilter[0];
	m_datamax=dataafterfilter[0];
	for (i=0;i<3600;i++)	
	{  
		if (m_datamax<dataafterfilter[i])
		{
			m_datamax=dataafterfilter[i];
		}
		if (m_datamin>dataafterfilter[i])
		{
			m_datamin=dataafterfilter[i];
		}
	}
    m_Middle=(m_datamax+m_datamin)/2;
    m_OutIn=m_datamax-m_datamin;
    //////////////////////////////////////////////////////////  
	//////////////////////算出轮廓的横、纵坐标///////////////////////////////
	m_endposition=360;
	   m_startposition=0;
	   double m_aveangle=3600/360;
	   double m_endpoint=m_aveangle*m_endposition;
	   double m_startpoint=m_aveangle*m_startposition;
	   double m_spiltavenum;
	   m_spiltavenum=(m_endpoint-m_startpoint)/1;  
	   for (int j=0;j<1;j++)
	   {	
		   m_maxsplit[j]=0;
		   m_minsplit[j]=0;
		   
		   for (i=m_startpoint+j* m_spiltavenum; i< m_startpoint+(j+1)* m_spiltavenum;  i++)
		   {
			   
			   
			   if (m_maxsplit[j]<=dataafterfilter[i])
			   {
				   m_maxsplit[j]=dataafterfilter[i];
			   }
			   
			   if (m_minsplit[j]>=dataafterfilter[i])
			   {
				   m_minsplit[j]=dataafterfilter[i];
				   
			   }
			   
			   m_PV[j]=fabs(m_maxsplit[j])+fabs(m_minsplit[j]);		
		   }
		   
	   }
	double PV=m_PV[0];	   
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
		
	for(i=0;i<3600;i++)		
	{ 
		datas[i]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(dataafterfilter[i]-m_Middle)*ratio*0.2*5/(rectJM.Height()*0.4/10)+RSLC; //绘制圆度打点时按比例显示
		//datas[i]=(dataafterfilter[i]-m_Middle)*(rout-rin-20)/m_OutIn+RSLC; //绘制圆度打点时按比例显示	
		//datas[i]=(dataafterfilter[i]-m_Middle)*ratio*5/(rectJM.Height()*0.4/10)+RSLC;
		drealx[i]=datas[i]*cos(i*dw)+dX0;
		drealy[i]=datas[i]*sin(i*dw)+dY0;//实际轮廓的横、纵坐标(相对于二乘圆的)
	}		
	///////////////////////////////////////////////////////
    m_Intstep=5;//间隔点数连线
	CPen penreal;
	penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));    
	CPen pendeal;
	pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));    
	
	for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	{ 
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{  
		   memDCJM.SelectObject(&pendeal);
		   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//绿色曲线表示手动处理区域
		   memDCJM.MoveTo(drealx[i], drealy[i]);
		   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);	
		
		}
		else
		{
			memDCJM.SelectObject(&penreal);
			memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//蓝色曲线表示实际轮廓
			memDCJM.MoveTo(drealx[i], drealy[i]);
			memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
		}
	}
	if(i>=3600-m_Intstep)
	{ 
		for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		{
	       if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			{   
			    memDCJM.SelectObject(&pendeal);
			    memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//绿色曲线表示实际轮廓
		    	memDCJM.MoveTo(drealx[i], drealy[i]);
			    memDCJM.LineTo(drealx[0], drealy[0]);	
			}
			else
			{
				memDCJM.SelectObject(&penreal);
				memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//蓝色曲线表示实际轮廓
				memDCJM.MoveTo(drealx[i], drealy[i]);
				memDCJM.LineTo(drealx[0], drealy[0]);
			}
		}
	}
	penreal.DeleteObject();
    pendeal.DeleteObject();
	



	double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	CPen penblack(PS_SOLID, 1*m_penScale, RGB(0,0,0));
	CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	CBrush brushblack(RGB(0, 0, 0));
    memDCJM.SelectObject(&brushblack);
	CPoint pts[3];
	double tr=2 * 3.1415926/36;// 每一次采样对应的角度间隔，弧度
	double wzd=asin(6*m_penScale/m_maxRTriangle); //每次三角形的底边两点相对于定点的旋转角度
	
	for (i=0;i<36;i++)
	{
		memDCJM.SelectObject(&penblack);
		pts[0].x = m_minrTriangle*cos(i*tr)+dX0;
		pts[0].y = m_minrTriangle*sin(i*tr)+dY0;
		
		pts[1].x = m_maxRTriangle*cos(i*tr-wzd)+dX0;
		pts[1].y = m_maxRTriangle*sin(i*tr-wzd)+dY0;
		
		pts[2].x = m_maxRTriangle*cos(i*tr+wzd)+dX0;
		pts[2].y = m_maxRTriangle*sin(i*tr+wzd)+dY0;
		
   	    memDCJM.Polygon(pts, 3);
        penblack.DeleteObject();
		
		if (i%9!=0)
		{
			memDCJM.SelectObject(&pengrey);
			memDCJM.MoveTo(rin*cos(i*tr)+dX0,rin*sin(i*tr)+dY0);
			memDCJM.LineTo(rout*cos(i*tr)+dX0,rout*sin(i*tr)+dY0);
            pengrey.DeleteObject();
		}
        
	}
    brushblack.DeleteObject();
	penblack.DeleteObject();
    brushblack.DeleteObject();
	//图形显示标注说明
	CString m_SelectJM,m_TotalJM;

    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);

	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"截面总数:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"当前截面:");
	
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+10*m_penScale,m_TotalJM);
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+30*m_penScale,m_SelectJM);
}

void CJMAnalyse::DrawCircleMCC()
{
  //读取文件并绘图
	  ReadDataFromFile();//调用最小区域法评定圆度误差
  	  //最小区域法圆心MZCDX, MZCDY, 
      //最小区域法的最大值和最小值 DispMaxdirec,DispMindirec
      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
      double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=dright/2;
	  //rin为0圆，RSLC为2018圆，rout为4096圆 
	  CString strcodinate;
	  //rin为0圆，RSLC为2018圆，rout为4096圆
	  int x1,y1,x2,y2;
	  double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	  dw=2*PI/3600;
	  
	  //绘制底色圆环带
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //绘制黄色圆环带 
	  memDCJM.SelectObject(&penRing); 
	  for(th=0;th<PI*2;th+=dw)
	  {
		  x1=dX0-(int)rin*cos(th);
		  y1=dY0-(int)rin*sin(th);
		  x2=dX0-(int)rout*cos(th);
		  y2=dY0-(int)rout*sin(th);
		  memDCJM.MoveTo(x1,y1);
		  memDCJM.LineTo(x2,y2);	 
	  }	 
	  penRing.DeleteObject();	
	  int i;
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //绘制圆环变紫色带 
	  memDCJM.SelectObject(&ping); 
	  for (i=0;i<3600;i++)
	  {
		  if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		  {
			  x1=dX0-(int)rin*cos(i*dw-PI);
			  y1=dY0-(int)rin*sin(i*dw-PI);
			  x2=dX0-(int)rout*cos(i*dw-PI);
			  y2=dY0-(int)rout*sin(i*dw-PI);
			  memDCJM.MoveTo(x1,y1);
			  memDCJM.LineTo(x2,y2);
		  }		
	  }	
	  ping.DeleteObject();
	  //----------构造动态圆环---------
	  if (flagmanchuli==1)
	  {	   
		  m_IndexStart=alpha1/dw;
		  m_IndexEnd=alpha2/dw;	
		  if (FlagMove%2==0)
		  {
			  DynamicDrawCircleJM(m_IndexStart,m_IndexEnd);		
			  
			  
		  }
		  else  
		  {      
			  if ( 6.2814-alpha2>6.2814-alpha1)
			  {		
				  DynamicDrawCircleJM(m_IndexStart,3599);	
				  DynamicDrawCircleJM(0,m_IndexEnd);
			  }
			  else if ( 6.2814-alpha1>6.2814-alpha2)
			  {
				  DynamicDrawCircleJM(m_IndexStart,0);	
				  DynamicDrawCircleJM(3599,m_IndexEnd);				
			  }			
		  }
	}	

	  //----------------------以上代码实现灵活的选取-----------
	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //创建空画刷，防止遮挡内
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//选择画刷 

	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//绘制圆环内圆
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//绘制圆环外圆
      RoutORin.DeleteObject();
	
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////绘制坐标轴//////////////////////////////////
	  double EverystrcodX=(rout)/10,EverystrcodY=EverystrcodX;
	  CPen pen1 (PS_DOT,1*m_penScale,RGB(125,125,125));
	  memDCJM.SelectObject(&pen1); 
	  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0-EverystrcodX*7);
	  memDCJM.LineTo(dX0+EverystrcodX*7,dY0+EverystrcodX*7);
	  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0+EverystrcodX*7);
	  memDCJM.LineTo(dX0+EverystrcodX*7,dY0-EverystrcodX*7);
	  pen1.DeleteObject();

	  CPen penCoordinate (PS_SOLID,1*m_penScale,RGB(0,0,0));
	  memDCJM.SelectObject(&penCoordinate); 
		  
	  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0);
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);//绘制x轴
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/2,dY0-EverystrcodY/2,"0°");
	  memDCJM.TextOut(rectJM.left,dY0-EverystrcodY/2,"180°");
	  
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45°");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225°");
	  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //绘制y轴
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0+EverystrcodY*11,"270°");
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0-EverystrcodY*11.5,"90°");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135°");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315°");

		  
		  
	  for(i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //绘制X正轴刻度
		  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	  }	
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //绘制X负轴刻度
		  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	  }
	  for( i=0; i<10; i++)      //写Y正轴刻度值
	  {
		  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		  memDCJM.MoveTo(dX0-4*m_penScale, dY0-i*EverystrcodY);
		  memDCJM.LineTo(dX0+4*m_penScale, dY0-i*EverystrcodY);	
	  }
	  for( i=0; i<10; i++)  
	  {
		  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		  memDCJM.MoveTo(dX0-4*m_penScale, dY0+i*EverystrcodY);
		  memDCJM.LineTo(dX0+4*m_penScale, dY0+i*EverystrcodY);
	  }
	  penCoordinate.DeleteObject();
	  ////////////////////////////////////////////////////////////////////////////////

     //====================================================//
		//第几个截面参数是传递过来的///////////////////截面参数是M;
		for (i=0;i<3600;i++)	
		{  
			fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
			m_CirCal[i]=fpdata[i];    //计算圆度误差转换位移公式		
		}	

			//手动处理后的数据进行调用函数计算	
			for(i=0;i<3600;i++)		
			{ 
				datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //计算圆度误差转换位移公式	
			}		
			DrawFilter (FilterMode,datacir,dataafterfilter);
			for(i=0;i<3600;i++)		
			{
				TsH[i]=dataafterfilter[i];
			}   
			SumTs = 0;
			SumTcos = 0; 
			SumTsin = 0;
			for( i = 0;i<3600;i++)
			{
				SumTs = SumTs + TsH[i];
				SumTcos = SumTcos + TsH[i] * cos(dw * i);
				SumTsin = SumTsin + TsH[i] * sin(dw * i);
			}
			A0 = SumTs/3600;       //1.4084237494346061最小二乘圆的半径和圆心坐标
			A1 = 2*SumTcos/3600;  //-0.29798988797225540
	        B1 = 2*SumTsin/3600; //-0.095864371049355274

	   //求轮廓的最大最小值-----
	   m_datamax=DispMaxdirecMCC;
	   m_datamin=DispMindirecMCC;
       m_Middle=(m_datamax+m_datamin)/2; 

	   double maxchange;
	   if (m_datamax<0)
		   m_datamax=-m_datamax;
	   if (m_datamin<0)
	   {
		   m_datamin=-m_datamin;
	   }
      
	   if (m_datamax<m_datamin)
	   {
		   maxchange=m_datamax;
		   m_datamax=m_datamin;
		   m_datamin=maxchange;

	   }

	   double  FDKP;
	   FDKP=43/m_datamax;
	   A1Draw=MCCDX*FDKP; //绘制圆度打点时圆心坐标显示
	   B1Draw=MCCDY*FDKP; 
       A0Draw=A0*FDKP;
	  //////////////////////算出轮廓的横、纵坐标///////////////////////////////
	   m_endposition=360;
	   m_startposition=0;
	   double m_aveangle=3600/360;
	   double m_endpoint=m_aveangle*m_endposition;
	   double m_startpoint=m_aveangle*m_startposition;
	   double m_spiltavenum;
	   m_spiltavenum=(m_endpoint-m_startpoint)/1;  
	   for (int j=0;j<1;j++)
	   {	
		   m_maxsplit[j]=0;
		   m_minsplit[j]=0;
		   
		   for (i=m_startpoint+j* m_spiltavenum; i< m_startpoint+(j+1)* m_spiltavenum;  i++)
		   {
			   
			   
			   if (m_maxsplit[j]<=dataafterfilter[i])
			   {
				   m_maxsplit[j]=dataafterfilter[i];
			   }
			   
			   if (m_minsplit[j]>=dataafterfilter[i])
			   {
				   m_minsplit[j]=dataafterfilter[i];
				   
			   }
			   
			   m_PV[j]=fabs(m_maxsplit[j])+fabs(m_minsplit[j]);		
		   }
		   
	   }
	double PV=m_PV[0];	   
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
	   for(i=0;i<3600;i++)		
	   { 
		   datas[i]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(dataafterfilter[i]-A0)*ratio*0.2/(rectJM.Height()*0.4/10)+RSLC;
		   drealx[i]=datas[i]*cos(i*dw)+dX0-A1;
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//实际轮廓的横、纵坐标(相对于二乘圆的)
	   }        
	double rout2;	 
	rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	m_Intstep=5;//间隔点数连线
	CPen penreal;
	penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));  
	CPen pendeal;
	pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));    
	

/*	for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
		   memDCJM.SelectObject(&pendeal);
		   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,0,255));
		   memDCJM.MoveTo(drealx[i], drealy[i]);
		   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);	
		  if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
			rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
	   }
	   penreal.DeleteObject();
	   CPen RoutORin(PS_SOLID ,1*m_penScale,RGB(20,230,20));
	   memDCJM.SelectObject(&RoutORin);               
	   memDCJM.Ellipse(dX0-rout2+rectJM.left,dY0-rout2+rectJM.top,dX0+rout2+rectJM.left,dY0+rout2+rectJM.top);//绘制圆环外圆
       RoutORin.DeleteObject();*/

	for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	{ 
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{  
		   memDCJM.SelectObject(&pendeal);
		   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//绿色曲线表示手动处理区域
		   memDCJM.MoveTo(drealx[i], drealy[i]);
		   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);	
		   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));	   
		}
		else
		{
			memDCJM.SelectObject(&penreal);
			memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//蓝色曲线表示实际轮廓
			memDCJM.MoveTo(drealx[i], drealy[i]);
			memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
			if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		}
	}


      CPen pencir;
	  pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
	  memDCJM.SelectObject(&pencir);
	  memDCJM.Ellipse(dX0-rout2+rectJM.left,dY0-rout2+rectJM.top,dX0+rout2+rectJM.left,dY0+rout2+rectJM.top);//绘制圆环外圆
	  double Rmincir=dX0/2-100*m_penScale;
	  pencir.DeleteObject();


	if(i>=3600-m_Intstep)
	{ 
		for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		{
	       if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			{   
			    memDCJM.SelectObject(&pendeal);
			    memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//绿色曲线表示实际轮廓
		    	memDCJM.MoveTo(drealx[i], drealy[i]);
			    memDCJM.LineTo(drealx[0], drealy[0]);	
				if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
			else
			{
				memDCJM.SelectObject(&penreal);
				memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//蓝色曲线表示实际轮廓
				memDCJM.MoveTo(drealx[i], drealy[i]);
				memDCJM.LineTo(drealx[0], drealy[0]);
				if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
			}
		}
	}
	penreal.DeleteObject();


	double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	CPen penblack(PS_SOLID, 1*m_penScale, RGB(0,0,0));
	CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	CBrush brushblack(RGB(0, 0, 0));
    memDCJM.SelectObject(&brushblack);
	CPoint pts[3];
	double tr=2 * 3.1415926/36;// 每一次采样对应的角度间隔，弧度
	double wzd=asin(6*m_penScale/m_maxRTriangle); //每次三角形的底边两点相对于定点的旋转角度
	
	for (i=0;i<36;i++)
	{
		memDCJM.SelectObject(&penblack);
		pts[0].x = m_minrTriangle*cos(i*tr)+dX0;
		pts[0].y = m_minrTriangle*sin(i*tr)+dY0;
		
		pts[1].x = m_maxRTriangle*cos(i*tr-wzd)+dX0;
		pts[1].y = m_maxRTriangle*sin(i*tr-wzd)+dY0;
		
		pts[2].x = m_maxRTriangle*cos(i*tr+wzd)+dX0;
		pts[2].y = m_maxRTriangle*sin(i*tr+wzd)+dY0;
		
   	    memDCJM.Polygon(pts, 3);
        penblack.DeleteObject();
		
		if (i%9!=0)
		{
			memDCJM.SelectObject(&pengrey);
			memDCJM.MoveTo(rin*cos(i*tr)+dX0,rin*sin(i*tr)+dY0);
			memDCJM.LineTo(rout*cos(i*tr)+dX0,rout*sin(i*tr)+dY0);
            pengrey.DeleteObject();
		}
        
	}
    brushblack.DeleteObject();
	penblack.DeleteObject();
    brushblack.DeleteObject();
	//图形显示标注说明
	CString m_SelectJM,m_TotalJM;

    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);
	
	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"截面总数:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"当前截面:");

    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+30*m_penScale,m_TotalJM);
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+10*m_penScale,m_SelectJM);	   
}

void CJMAnalyse::MCCyuandu(double *Soudata)
{
  //--------Case 2, 3-------------------
 	 //----'2- MCC 最小外接圆与显示轮廓相接触至少相接三点。
     //----'3- MIC 最大内切圆与显示轮廓相接触至少相切三点。
     double Direc[7200],Sirec[3600],TsQ[3600],TsH[3600],fpcircle[3600];
	 double SumTs,SumTcos,SumTsin,dw,A0,a1,b1,b2,A2,Zc1,Zc2,D,D1,D2,Maxdirec,Mindirec;
	 double Temp1,U1,U2,U10,U20, GLiGangK = 39.37008,PVA,PVB,PVB0;
     int    i=0,GDN=3600,AnaDataMode=2;//评定算法2为最小外接圆----------3为最大内切圆
	 int    ScanT,MaxIndex,MinIndex,MinI1,MinI2,MaxI1,MaxI2,MaxI3;
     BOOL   GLiGangFlag=false;//qy changed//BOOL   GLiGangFlag;

	// G1=16,G2= 0.121732414074473  ;
     dw= 2*3.1415926/GDN;
  	 SumTs=0,SumTcos=0,SumTsin=0;
	 //=============================================================================
	 ////读取文件并绘图///
	 LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//对应圆柱所有的点数
	 m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//鼠标单击选中的截面
	 pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;

	 
	 //-------------以上代码实现读文件----------------------
	 for(i=0;i<3600;i++)		
	 { 
		 TsQ[i]=(Soudata[i]-2048)*10/(GG1*GG2*4096); //计算圆度误差转换位移公式	
	 }
	 WLS_Filter(FilterMode,3600,TsQ,TsH);
	 
	 for (i=0;i<GDN;i++)
	 {
		 SumTs = SumTs + TsH[i];
	 }
	 A0=SumTs/GDN;
	 for (i=0;i<GDN;i++)
	 {
		 TsH[i]=TsH[i]-A0;
	 }
	 //====================================================================================
 	 SumTs=0;
     for(i=0;i<GDN;i++)
	 {
         SumTs=SumTs+TsH[i];
         SumTcos=SumTcos+TsH[i]*cos(dw*i);
         SumTsin=SumTsin+TsH[i]*sin(dw*i);
	 }
         A0=SumTs/GDN;
         a1=2*SumTcos/GDN;
         b1=2*SumTsin/GDN;
     if (AnaDataMode==2)
     {
	     for(i=0;i<GDN;i++)
		 {
			Direc[i]=TsH[i]-A0-a1*cos(dw*i)-b1*sin(dw*i);
			Direc[i+GDN]=Direc[i];
		 }
	 } 
     else
	 {
         for(i=0;i<GDN;i++)
		 {
             Direc[i]=-(TsH[i]-A0-a1*cos(dw*i)-b1*sin(dw*i));
             Direc[i+GDN]=Direc[i];
		 }
	 }

     //'--1 在Direc(i)中查找二个最大值及其位置 范围 0--Dn-1'2000
     ScanT=0,PVA=100;
     Maxdirec=Direc[0];
     MaxIndex=0;
     for(i=0;i<GDN;i++)
	 {
        if(Direc[i]>Maxdirec)
		{
           Maxdirec=Direc[i];
           MaxIndex=i;
		}
	 }//'2020
     MaxI1=MaxIndex;
     Maxdirec=Direc[MaxI1+int(GDN/4)];
     MaxIndex=MaxI1+int(GDN/4);

     for(i=(MaxI1+int(GDN/4));i<=(MaxI1+int(GDN/4)+int(GDN/2));i++)
	  {
         if(Direc[i]>Maxdirec)
		 {
	        Maxdirec = Direc[i];
		    MaxIndex = i;
		 }
	  }//'2030
      MaxI2 = MaxIndex;
      if(MaxI2>GDN)
	  {
        MaxI2 = MaxI2 - GDN;
	  }//'2040
       if(MaxI1>MaxI2)
	   {
         MaxIndex=MaxI2;
         MaxI2=MaxI1;
         MaxI1=MaxIndex;
	   }
       if(AnaDataMode==2)      //'--2A MCC 查到的二个最大值在半圆内 '2050
	   {
		  if(abs(MaxI2-MaxI1-GDN/2)<=1)    goto PDMiCTJ;//'2550
	   }
       else                    //'--2A MIC 查到的二个最大值在半圆内 '2050
	   {
          if (abs(MaxI2-MaxI1-GDN/2)<=3)   goto PDMiCTJ;// '2550
   
	   }

       // '--2B 查到的二个最大值在半圆外 '2060
       if ((MaxI2-MaxI1)>GDN/2)// '2090
	   {
          Maxdirec=Direc[MaxI2-GDN/2];
          MaxIndex=MaxI2-GDN/2;
          for(i=(MaxI2-GDN/2);i<=(MaxI1+GDN/2);i++)
		  {
              if(Direc[i]>Maxdirec)
			  {
                 Maxdirec = Direc[i];
                 MaxIndex = i;
			  }
		  }   //'2100
          MaxI3 = MaxI2;
          MaxI2 = MaxIndex;
		  goto CONC2130;
	   }
      else  //'2070
	  {
            Maxdirec=Direc[MaxI1+GDN/2];
            MaxIndex=MaxI1+GDN/2;
            for(i=(MaxI1+GDN/2);i<=(MaxI2+GDN/2);i++)
			{
               if(Direc[i]>Maxdirec)
			   {
                  Maxdirec=Direc[i];
                  MaxIndex=i;
			   }
            }//'2080
            MaxI3=MaxIndex;  // '2110
            if(MaxI3>GDN)
			{
               MaxIndex=MaxI3-GDN;
               MaxI3 = MaxI2;
               MaxI2 = MaxI1;
               MaxI1 = MaxIndex;
			}
          goto CONC2130;
	  }

//'---------------------------------
//'--3A 判断条件满足? 2550


PDMiCTJ:
        Temp1=(TsH[MaxI1]-TsH[MaxI2])/2;
        U1=Temp1*cos(dw*MaxI1);
        U2=Temp1*sin(dw*MaxI1);
        Maxdirec=TsH[0]-U1*cos(dw*0)-U2*sin(dw*0);
        Mindirec=Maxdirec;
        MaxIndex=0;
      
		if(AnaDataMode==2)
		{
           //'MCC 2570
           for(i=0 ;i<GDN;i++)
		   {
              Direc[i]=TsH[i]-U1*cos(dw*i)-U2*sin(dw*i);
              Direc[i+GDN]=Direc[i];
              if((i==MaxI1)||(i==MaxI2))
				  ;
              else
			  {
                if(Direc[i]> Maxdirec)
				{
                   Maxdirec = Direc[i];
                   MaxIndex = i;
                }
               if(Direc[i]< Mindirec)
			   {
                  Mindirec = Direc[i];
			   }
          
			  }
		   }
		}
      
		else //'MIC 2612
		{
           for(i=0 ;i<GDN;i++)
		   {
                Direc[i]=-(TsH[i]-U1*cos(dw*i)-U2*sin(dw*i));
                Direc[i+GDN]=Direc[i];
                if((i==MaxI1)||(i==MaxI2))
					;
                else
				{
					if(-Direc[i]< Mindirec)
					{
                       Mindirec=-Direc[i];
                       MaxIndex=i;
					}
                    if(-Direc[i]>Maxdirec)
					{
                       Maxdirec=-Direc[i];
					}
                
				}
		   }
		}//'2620

      if((MaxIndex==0)||(abs(MaxIndex-MaxI1)<=10)||(abs(MaxIndex-MaxI2)<=10)) //' 查找完毕,成功
	  {           
CONCRIGHT:
	      PVB = Maxdirec - Mindirec;
		  GResult[5]= PVB;
          goto QKquit;
	  }
      else     // '条件不满足,重新查找    
	  {
          if(MaxIndex<MaxI1)
		  {
             MaxI3 = MaxI2;
             MaxI2 = MaxI1;
             MaxI1 = MaxIndex;
		  }
         else
		 {
             if(MaxIndex>MaxI2)
			 {
                MaxI3 = MaxIndex;
			 }
             else
			 {
                MaxI3 = MaxI2;
                MaxI2 = MaxIndex;
			 }
		 }
          goto CONC2130;
	  }	  
      //'----------------------------------//'--3B  2130
CONC2130:
         a1=cos(dw*MaxI1)-cos(dw*MaxI2);
         b1=sin(dw*MaxI1)-sin(dw * MaxI2);
         Zc1=TsH[MaxI1]-TsH[MaxI2];
         A2=cos(dw*MaxI2)-cos(dw*MaxI3);
         b2=sin(dw*MaxI2)-sin(dw*MaxI3);
         Zc2=TsH[MaxI2]-TsH[MaxI3];
         D=a1*b2-A2*b1;
         D1=Zc1*b2-Zc2*b1;
         D2=a1*Zc2-A2*Zc1;
         if(D==0)
		 {
            goto  ErrQuit;
		 }
            U1=D1/D;
            U2=D2/D;
            MaxIndex=0;
      if(AnaDataMode==2)//'2180
	  {
            Maxdirec=TsH[MaxI1]-U1*cos(dw*MaxI1)-U2*sin(dw*MaxI1);
            Mindirec=Maxdirec;
            for(i=0;i<GDN;i++) 
			{
                Direc[i]=TsH[i]-U1*cos(dw*i)-U2*sin(dw*i);
                Direc[i+GDN]=Direc[i];
               if((i==MaxI1)||(i==MaxI2)||(i==MaxI3))
				   ;
               else
			   {
                   if(Direc[i]>Maxdirec)
				   {
                      Maxdirec=Direc[i];
                      MaxIndex=i;
                   }
                   if( Direc[i]<Mindirec)
				   {
                      Mindirec=Direc[i];
				   }
			   }
			}
	  }
      else  // '2250
	  {
           Mindirec=TsH[MaxI1]-U1*cos(dw*MaxI1)-U2*sin(dw*MaxI1);
           Maxdirec = Mindirec;
           for(i=0;i<GDN;i++)
		   {
               Direc[i]=-(TsH[i]-U1*cos(dw*i)-U2*sin(dw*i));
               Direc[i+GDN]=Direc[i];
               if((i==MaxI1) ||(i==MaxI2) || (i==MaxI3))
				   ;
          
               else
			   {
                   if(-Direc[i]<Mindirec)
				   {
                     Mindirec=-Direc[i];
                     MaxIndex=i;
                   }
                   if(-Direc[i]>Maxdirec)
				   {
                      Maxdirec=-Direc[i];
				   }
               }
           }
	  }
     //'2320
    if(MaxIndex!=0)//-----------------------------------------
	{
        // '2330
        ScanT=ScanT+1;
        PVB=Maxdirec-Mindirec;

        if(PVB<PVA)
		{
           PVA=PVB;
           U10=U1;
           U20=U2;
		}

        if(ScanT>20)
		{
           goto ErrQuit;// ' 错误退出
		}    

        if((MaxI1<MaxIndex) && (MaxIndex<MaxI2))
		{
            if((MaxIndex-MaxI1)<(MaxI2-MaxIndex))
			{
                MaxI1=MaxIndex;
			}
            else
			{
                MaxI2=MaxIndex;
			}
			goto CONC2130;
		}

        if ((MaxI2<MaxIndex) && (MaxIndex<MaxI3))  // '2430
		{
           if((MaxIndex-MaxI2)<(MaxI3-MaxIndex))
		   {
               MaxI2=MaxIndex;
		   }
           else
		   {
               MaxI3=MaxIndex;
		   }
           goto CONC2130;
		}

        if ((MaxIndex>MaxI1))   //'2390
		{
           if((MaxIndex-MaxI3)<(GDN+MaxI1-MaxIndex))
		   {
              MaxI3 = MaxIndex;
		   }
           else
		   {
              MaxI1 = MaxI2;
              MaxI2 = MaxI3;
              MaxI3 = MaxIndex;
		   }
           goto CONC2130;
		}
    
        if ((MaxI1-MaxIndex)<(GDN+MaxIndex-MaxI3))   //'2370
		{
             MaxI1 = MaxIndex;
		}
        else
		{
             MaxI3 = MaxI2;
             MaxI2 = MaxI1;
             MaxI1 = MaxIndex;
		}
        goto CONC2130;
	}
    else//---------------------------------------------------------------
	{
        ScanT=ScanT+1;
        goto  ConC2450;
	}
//'------------------------------------
ConC2450:
          if( (MaxI3-MaxI1)<(GDN/2) )  //'2490
		  {
               Maxdirec=Direc[MaxI1+GDN/2];
               MaxIndex=MaxI1+GDN/2;
               for(i=(MaxI1+GDN/2);i<=(MaxI3+GDN/2);i++)
			   {
                   if(Direc[i]>Maxdirec)
				   {
                       Maxdirec=Direc[i];
                       MaxIndex=i;
				   }
			  
               if(MaxIndex>GDN)
			   {
                  MaxI2=MaxI1;
                  MaxI1=MaxIndex-GDN;
			   }
               else
			   {
                  MaxI2=MaxI3;
                  MaxI3=MaxIndex;
			   }
			  }
               goto CONC2130;
		  }//'2460
          if((MaxI3-MaxI2)<=GDN/2)// '2520
		  {
              if(MaxI2-MaxI1<=GDN/2)
                 goto CONCRIGHT;
              else
			  {
                Maxdirec=Direc[MaxI2-GDN/2];
                MaxIndex=MaxI2-GDN/2;
                for(i=(MaxI2-GDN/2);i<=(MaxI1+GDN/2);i++)
				{
                    if(Direc[i]>Maxdirec)
					{
                       Maxdirec=Direc[i];
                       MaxIndex=i;
					}
				}
                MaxI3 = MaxI2;
                MaxI2 = MaxIndex;
                goto CONC2130;
			  }
		  }// '2470
          Maxdirec = Direc[MaxI3-GDN/2];
          MaxIndex = MaxI3-GDN/2;
          for(i=(MaxI3-GDN/2);i<=(MaxI2+GDN/2);i++)
		  {
              if(Direc[i]>Maxdirec)
			  {
                  Maxdirec=Direc[i];
			  }
		  }
          MaxI1=MaxI2;
          MaxI2=MaxIndex;
          goto CONC2130;

    //==========================
ErrQuit: //' 错误退出
     GResult[5]= PVB;

QKquit:
	    if(GLiGangFlag== 1)
		{
		 GResult[1]= GResult[1] * GLiGangK;
		 GResult[2] = GResult[2] * GLiGangK;
		 GResult[4] = GResult[4] * GLiGangK;
		 GResult[5] = GResult[5] * GLiGangK;
		}

  DispMaxdirecMCC=Maxdirec;
  DispMindirecMCC=Mindirec;
  MCCDX=U1;
  MCCDY=U2;
  MCCEcc=sqrt(MCCDX*MCCDX+MCCDY*MCCDY);
  MCCEccPos=atan2(MCCDY,MCCDX);
  m_strdEcc.Format("%.2f",MCCEcc); 
//  m_strdEccPos.Format("%.2f",MCCEccPos); 
  m_MCCRONT.Format("%.3f",GResult[5]);  //在报表中显示最小区域法评定圆度误差的结果

}

void CJMAnalyse::MICyuandu(double *Soudata)
{
	     //--------Case 2, 3-------------------
 	 //----'2- MCC 最小外接圆与显示轮廓相接触至少相接三点。
     //----'3- MIC 最大内切圆与显示轮廓相接触至少相切三点。
     double Direc[7200],Sirec[3600],TsQ[3600],TsH[3600],fpcircle[3600];
	 double SumTs,SumTcos,SumTsin,dw,A0,a1,b1,b2,A2,Zc1,Zc2,D,D1,D2,Maxdirec,Mindirec;
	 double Temp1,U1,U2,U10,U20, GLiGangK = 39.37008,PVA,PVB,PVB0;
     int    i=0,GDN=3600,AnaDataMode=3;//评定算法2为最小外接圆----------3为最大内切圆
	 int    ScanT,MaxIndex,MinIndex,MinI1,MinI2,MaxI1,MaxI2,MaxI3;
     BOOL   GLiGangFlag = false;//qy changed//BOOL   GLiGangFlag;

//	 G1=16,G2= 0.121732414074473  ;
     dw= 2*3.1415926/GDN;
  	 SumTs=0,SumTcos=0,SumTsin=0;
	 //=============================================================================
	 //=============================================================================
	 ////读取文件并绘图///
	 LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//对应圆柱所有的点数
	 m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//鼠标单击选中的截面
	 pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;

	 
	 //-------------以上代码实现读文件----------------------
	 for(i=0;i<3600;i++)		
	 { 
		 TsQ[i]=(Soudata[i]-2048)*10/(GG1*GG2*4096); //计算圆度误差转换位移公式	
	 }
	 WLS_Filter(FilterMode,3600,TsQ,TsH);
	 
	 for (i=0;i<GDN;i++)
	 {
		 SumTs = SumTs + TsH[i];
	 }
	 A0=SumTs/GDN;
	 for (i=0;i<GDN;i++)
	 {
		 TsH[i]=TsH[i]-A0;
	 }
	 //====================================================================================
 	 SumTs=0;
     for(i=0;i<GDN;i++)
	 {
         SumTs=SumTs+TsH[i];
         SumTcos=SumTcos+TsH[i]*cos(dw*i);
         SumTsin=SumTsin+TsH[i]*sin(dw*i);
	 }
         A0=SumTs/GDN;
         a1=2*SumTcos/GDN;
         b1=2*SumTsin/GDN;
     if (AnaDataMode==2)
     {
	     for(i=0;i<GDN;i++)
		 {
			Direc[i]=TsH[i]-A0-a1*cos(dw*i)-b1*sin(dw*i);
			Direc[i+GDN]=Direc[i];
		 }
	 } 
     else
	 {
         for(i=0;i<GDN;i++)
		 {
             Direc[i]=-(TsH[i]-A0-a1*cos(dw*i)-b1*sin(dw*i));
             Direc[i+GDN]=Direc[i];
		 }
	 }

     //'--1 在Direc(i)中查找二个最大值及其位置 范围 0--Dn-1'2000
     ScanT=0,PVA=100;
     Maxdirec=Direc[0];
     MaxIndex=0;
     for(i=0;i<GDN;i++)
	 {
        if(Direc[i]>Maxdirec)
		{
           Maxdirec=Direc[i];
           MaxIndex=i;
		}
	 }//'2020
     MaxI1=MaxIndex;
     Maxdirec=Direc[MaxI1+int(GDN/4)];
     MaxIndex=MaxI1+int(GDN/4);

     for(i=(MaxI1+int(GDN/4));i<=(MaxI1+int(GDN/4)+int(GDN/2));i++)
	  {
         if(Direc[i]>Maxdirec)
		 {
	        Maxdirec = Direc[i];
		    MaxIndex = i;
		 }
	  }//'2030
      MaxI2 = MaxIndex;
      if(MaxI2>GDN)
	  {
        MaxI2 = MaxI2 - GDN;
	  }//'2040
       if(MaxI1>MaxI2)
	   {
         MaxIndex=MaxI2;
         MaxI2=MaxI1;
         MaxI1=MaxIndex;
	   }
       if(AnaDataMode==2)      //'--2A MCC 查到的二个最大值在半圆内 '2050
	   {
		  if(abs(MaxI2-MaxI1-GDN/2)<=1)    goto PDMiCTJ;//'2550
	   }
       else                    //'--2A MIC 查到的二个最大值在半圆内 '2050
	   {
          if (abs(MaxI2-MaxI1-GDN/2)<=3)   goto PDMiCTJ;// '2550
   
	   }

       // '--2B 查到的二个最大值在半圆外 '2060
       if ((MaxI2-MaxI1)>GDN/2)// '2090
	   {
          Maxdirec=Direc[MaxI2-GDN/2];
          MaxIndex=MaxI2-GDN/2;
          for(i=(MaxI2-GDN/2);i<=(MaxI1+GDN/2);i++)
		  {
              if(Direc[i]>Maxdirec)
			  {
                 Maxdirec = Direc[i];
                 MaxIndex = i;
			  }
		  }   //'2100
          MaxI3 = MaxI2;
          MaxI2 = MaxIndex;
		  goto CONC2130;
	   }
      else  //'2070
	  {
            Maxdirec=Direc[MaxI1+GDN/2];
            MaxIndex=MaxI1+GDN/2;
            for(i=(MaxI1+GDN/2);i<=(MaxI2+GDN/2);i++)
			{
               if(Direc[i]>Maxdirec)
			   {
                  Maxdirec=Direc[i];
                  MaxIndex=i;
			   }
            }//'2080
            MaxI3=MaxIndex;  // '2110
            if(MaxI3>GDN)
			{
               MaxIndex=MaxI3-GDN;
               MaxI3 = MaxI2;
               MaxI2 = MaxI1;
               MaxI1 = MaxIndex;
			}
          goto CONC2130;
	  }

//'---------------------------------
//'--3A 判断条件满足? 2550


PDMiCTJ:
        Temp1=(TsH[MaxI1]-TsH[MaxI2])/2;
        U1=Temp1*cos(dw*MaxI1);
        U2=Temp1*sin(dw*MaxI1);
        Maxdirec=TsH[0]-U1*cos(dw*0)-U2*sin(dw*0);
        Mindirec=Maxdirec;
        MaxIndex=0;
      
		if(AnaDataMode==2)
		{
           //'MCC 2570
           for(i=0 ;i<GDN;i++)
		   {
              Direc[i]=TsH[i]-U1*cos(dw*i)-U2*sin(dw*i);
              Direc[i+GDN]=Direc[i];
              if((i==MaxI1)||(i==MaxI2))
				  ;
              else
			  {
                if(Direc[i]> Maxdirec)
				{
                   Maxdirec = Direc[i];
                   MaxIndex = i;
                }
               if(Direc[i]< Mindirec)
			   {
                  Mindirec = Direc[i];
			   }
          
			  }
		   }
		}
      
		else //'MIC 2612
		{
           for(i=0 ;i<GDN;i++)
		   {
                Direc[i]=-(TsH[i]-U1*cos(dw*i)-U2*sin(dw*i));
                Direc[i+GDN]=Direc[i];
                if((i==MaxI1)||(i==MaxI2))
					;
                else
				{
					if(-Direc[i]< Mindirec)
					{
                       Mindirec=-Direc[i];
                       MaxIndex=i;
					}
                    if(-Direc[i]>Maxdirec)
					{
                       Maxdirec=-Direc[i];
					}
                
				}
		   }
		}//'2620

      if((MaxIndex==0)||(abs(MaxIndex-MaxI1)<=10)||(abs(MaxIndex-MaxI2)<=10)) //' 查找完毕,成功
	  {           
CONCRIGHT:
	      PVB = Maxdirec - Mindirec;
		  GResult[5]= PVB;
          goto QKquit;
	  }
      else     // '条件不满足,重新查找    
	  {
          if(MaxIndex<MaxI1)
		  {
             MaxI3 = MaxI2;
             MaxI2 = MaxI1;
             MaxI1 = MaxIndex;
		  }
         else
		 {
             if(MaxIndex>MaxI2)
			 {
                MaxI3 = MaxIndex;
			 }
             else
			 {
                MaxI3 = MaxI2;
                MaxI2 = MaxIndex;
			 }
		 }
          goto CONC2130;
	  }	  
      //'----------------------------------//'--3B  2130
CONC2130:
         a1=cos(dw*MaxI1)-cos(dw*MaxI2);
         b1=sin(dw*MaxI1)-sin(dw * MaxI2);
         Zc1=TsH[MaxI1]-TsH[MaxI2];
         A2=cos(dw*MaxI2)-cos(dw*MaxI3);
         b2=sin(dw*MaxI2)-sin(dw*MaxI3);
         Zc2=TsH[MaxI2]-TsH[MaxI3];
         D=a1*b2-A2*b1;
         D1=Zc1*b2-Zc2*b1;
         D2=a1*Zc2-A2*Zc1;
         if(D==0)
		 {
            goto  ErrQuit;
		 }
            U1=D1/D;
            U2=D2/D;
            MaxIndex=0;
      if(AnaDataMode==2)//'2180
	  {
            Maxdirec=TsH[MaxI1]-U1*cos(dw*MaxI1)-U2*sin(dw*MaxI1);
            Mindirec=Maxdirec;
            for(i=0;i<GDN;i++) 
			{
                Direc[i]=TsH[i]-U1*cos(dw*i)-U2*sin(dw*i);
                Direc[i+GDN]=Direc[i];
               if((i==MaxI1)||(i==MaxI2)||(i==MaxI3))
				   ;
               else
			   {
                   if(Direc[i]>Maxdirec)
				   {
                      Maxdirec=Direc[i];
                      MaxIndex=i;
                   }
                   if( Direc[i]<Mindirec)
				   {
                      Mindirec=Direc[i];
				   }
			   }
			}
	  }
      else  // '2250
	  {
           Mindirec=TsH[MaxI1]-U1*cos(dw*MaxI1)-U2*sin(dw*MaxI1);
           Maxdirec = Mindirec;
           for(i=0;i<GDN;i++)
		   {
               Direc[i]=-(TsH[i]-U1*cos(dw*i)-U2*sin(dw*i));
               Direc[i+GDN]=Direc[i];
               if((i==MaxI1) ||(i==MaxI2) || (i==MaxI3))
				   ;
          
               else
			   {
                   if(-Direc[i]<Mindirec)
				   {
                     Mindirec=-Direc[i];
                     MaxIndex=i;
                   }
                   if(-Direc[i]>Maxdirec)
				   {
                      Maxdirec=-Direc[i];
				   }
               }
           }
	  }
     //'2320
    if(MaxIndex!=0)//-----------------------------------------
	{
        // '2330
        ScanT=ScanT+1;
        PVB=Maxdirec-Mindirec;

        if(PVB<PVA)
		{
           PVA=PVB;
           U10=U1;
           U20=U2;
		}

        if(ScanT>20)
		{
           goto ErrQuit;// ' 错误退出
		}    

        if((MaxI1<MaxIndex) && (MaxIndex<MaxI2))
		{
            if((MaxIndex-MaxI1)<(MaxI2-MaxIndex))
			{
                MaxI1=MaxIndex;
			}
            else
			{
                MaxI2=MaxIndex;
			}
			goto CONC2130;
		}

        if ((MaxI2<MaxIndex) && (MaxIndex<MaxI3))  // '2430
		{
           if((MaxIndex-MaxI2)<(MaxI3-MaxIndex))
		   {
               MaxI2=MaxIndex;
		   }
           else
		   {
               MaxI3=MaxIndex;
		   }
           goto CONC2130;
		}

        if ((MaxIndex>MaxI1))   //'2390
		{
           if((MaxIndex-MaxI3)<(GDN+MaxI1-MaxIndex))
		   {
              MaxI3 = MaxIndex;
		   }
           else
		   {
              MaxI1 = MaxI2;
              MaxI2 = MaxI3;
              MaxI3 = MaxIndex;
		   }
           goto CONC2130;
		}
    
        if ((MaxI1-MaxIndex)<(GDN+MaxIndex-MaxI3))   //'2370
		{
             MaxI1 = MaxIndex;
		}
        else
		{
             MaxI3 = MaxI2;
             MaxI2 = MaxI1;
             MaxI1 = MaxIndex;
		}
        goto CONC2130;
	}
    else//---------------------------------------------------------------
	{
        ScanT=ScanT+1;
        goto  ConC2450;
	}
//'------------------------------------
ConC2450:
          if( (MaxI3-MaxI1)<(GDN/2) )  //'2490
		  {
               Maxdirec=Direc[MaxI1+GDN/2];
               MaxIndex=MaxI1+GDN/2;
               for(i=(MaxI1+GDN/2);i<=(MaxI3+GDN/2);i++)
			   {
                   if(Direc[i]>Maxdirec)
				   {
                       Maxdirec=Direc[i];
                       MaxIndex=i;
				   }
			  
               if(MaxIndex>GDN)
			   {
                  MaxI2=MaxI1;
                  MaxI1=MaxIndex-GDN;
			   }
               else
			   {
                  MaxI2=MaxI3;
                  MaxI3=MaxIndex;
			   }
			  }
               goto CONC2130;
		  }//'2460
          if((MaxI3-MaxI2)<=GDN/2)// '2520
		  {
              if(MaxI2-MaxI1<=GDN/2)
                 goto CONCRIGHT;
              else
			  {
                Maxdirec=Direc[MaxI2-GDN/2];
                MaxIndex=MaxI2-GDN/2;
                for(i=(MaxI2-GDN/2);i<=(MaxI1+GDN/2);i++)
				{
                    if(Direc[i]>Maxdirec)
					{
                       Maxdirec=Direc[i];
                       MaxIndex=i;
					}
				}
                MaxI3 = MaxI2;
                MaxI2 = MaxIndex;
                goto CONC2130;
			  }
		  }// '2470
          Maxdirec = Direc[MaxI3-GDN/2];
          MaxIndex = MaxI3-GDN/2;
          for(i=(MaxI3-GDN/2);i<=(MaxI2+GDN/2);i++)
		  {
              if(Direc[i]>Maxdirec)
			  {
                  Maxdirec=Direc[i];
			  }
		  }
          MaxI1=MaxI2;
          MaxI2=MaxIndex;
          goto CONC2130;

    //==========================
ErrQuit: //' 错误退出
     GResult[5]= PVB;

QKquit:
	    if(GLiGangFlag== 1)
		{
		 GResult[1]= GResult[1] * GLiGangK;
		 GResult[2] = GResult[2] * GLiGangK;
		 GResult[4] = GResult[4] * GLiGangK;
		 GResult[5] = GResult[5] * GLiGangK;
		}

  DispMaxdirecMIC=Maxdirec;
  DispMindirecMIC=Mindirec;
  MICDX=U1;
  MICDY=U2;
  MICEcc=sqrt(MICDX*MICDX+MICDY*MICDY);
  MICEccPos=atan2(MICDY,MICDX);
  m_strdEcc.Format("%.2f",MICEcc); 
 // m_strdEccPos.Format("%.2f",MICEccPos); 
  m_MICRONT.Format("%.3f",GResult[5]);  //在报表中显示最小区域法评定圆度误差的结果


}

void CJMAnalyse::DrawCircleMIC()
{
		  //读取文件并绘图
	  ReadDataFromFile();//调用最小区域法评定圆度误差
  	  //最小区域法圆心MZCDX, MZCDY,最小区域法的最大值和最小值 DispMaxdirec,DispMindirec

      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
	  double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.right*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5/2;
      double dw= 2*3.1415926/3600;
	  //rin为0圆，RSLC为2018圆，rout为4096圆 
	  int i,x1,y1,x2,y2;
	  //double rout=dY0-dY0/5,Everystrcod=(rout)/10,rin=Everystrcod*5,RSLC=(rout+rin)/2;
	  double rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=rout*0.5,RSLC=(rout+rin)/2;
      double th,rout1=rout;
      CString strcodinate;

	  //绘制底色圆环带
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //绘制黄色圆环带 
	  memDCJM.SelectObject(&penRing); 
	  for(th=0;th<PI*2;th+=dw)
	  {
		  x1=dX0-(int)rin*cos(th);
		  y1=dY0-(int)rin*sin(th);
		  x2=dX0-(int)rout*cos(th);
		  y2=dY0-(int)rout*sin(th);
		  memDCJM.MoveTo(x1,y1);
		  memDCJM.LineTo(x2,y2);	 
	  }	 
	  penRing.DeleteObject();	
	  
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //绘制圆环变紫色带 
	  memDCJM.SelectObject(&ping); 
	  for (i=0;i<3600;i++)
	  {
		  if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		  {
			  x1=dX0-(int)rin*cos(i*dw-PI);
			  y1=dY0-(int)rin*sin(i*dw-PI);
			  x2=dX0-(int)rout*cos(i*dw-PI);
			  y2=dY0-(int)rout*sin(i*dw-PI);
			  memDCJM.MoveTo(x1,y1);
			  memDCJM.LineTo(x2,y2);
		  }		
	  }	
	  ping.DeleteObject();
	  //----------构造动态圆环---------
	  if (flagmanchuli==1)
	  {	   
		  m_IndexStart=alpha1/dw;
		  m_IndexEnd=alpha2/dw;	
		  if (FlagMove%2==0)
		  {
			  DynamicDrawCircleJM(m_IndexStart,m_IndexEnd);		
			  
			  
		  }
		  else  
		  {      
			  if ( 6.2814-alpha2>6.2814-alpha1)
			  {		
				  DynamicDrawCircleJM(m_IndexStart,3599);	
				  DynamicDrawCircleJM(0,m_IndexEnd);
			  }
			  else if ( 6.2814-alpha1>6.2814-alpha2)
			  {
				  DynamicDrawCircleJM(m_IndexStart,0);	
				  DynamicDrawCircleJM(3599,m_IndexEnd);				
			  }			
		  }
	  }	

	  //----------------------以上代码实现灵活的选取-----------
	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //创建空画刷，防止遮挡内
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//选择画刷 
	  
	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//绘制圆环内圆
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//绘制圆环外圆
      RoutORin.DeleteObject();
	  
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////绘制坐标轴//////////////////////////////////
  	  double EverystrcodX=(rout)/10,EverystrcodY=EverystrcodX;
	  CPen pen1 (PS_DOT,1*m_penScale,RGB(125,125,125));
	  memDCJM.SelectObject(&pen1); 
	  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0-EverystrcodX*7);
	  memDCJM.LineTo(dX0+EverystrcodX*7,dY0+EverystrcodX*7);
	  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0+EverystrcodX*7);
	  memDCJM.LineTo(dX0+EverystrcodX*7,dY0-EverystrcodX*7);
	  pen1.DeleteObject();
	  CPen penCoordinate (PS_SOLID,1*m_penScale,RGB(0,0,0));
	  memDCJM.SelectObject(&penCoordinate); 
		  
	  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0);
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);//绘制x轴
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/2,dY0-EverystrcodY/2,"0°");
	  memDCJM.TextOut(rectJM.left,dY0-EverystrcodY/2,"180°");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45°");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225°");
	  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //绘制y轴
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0+EverystrcodY*11,"270°");
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0-EverystrcodY*11.5,"90°");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135°");
      memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315°");
		  
		  
	  for(i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //绘制X正轴刻度
		  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	  }	
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //绘制X负轴刻度
		  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	  }
	  for( i=0; i<10; i++)      //写Y正轴刻度值
	  {
		  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		  memDCJM.MoveTo(dX0-4*m_penScale, dY0-i*EverystrcodY);
		  memDCJM.LineTo(dX0+4*m_penScale, dY0-i*EverystrcodY);	
	  }
	  for( i=0; i<10; i++)  
	  {
		  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		  memDCJM.MoveTo(dX0-4*m_penScale, dY0+i*EverystrcodY);
		  memDCJM.LineTo(dX0+4*m_penScale, dY0+i*EverystrcodY);
	  }
	  penCoordinate.DeleteObject();
	  ////////////////////////////////////////////////////////////////////////////////
	  //====================================================//
	  //第几个截面参数是传递过来的///////////////////截面参数是M;
	  for (i=0;i<3600;i++)	
	  {  
		  fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		  m_CirCal[i]=fpdata[i];    //计算圆度误差转换位移公式		
	  }	

	  for(i=0;i<3600;i++)		
	  { 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //计算圆度误差转换位移公式	
       // dataafterfilter[i]=fpdata[i];
	  }
       DrawFilter (FilterMode,datacir,dataafterfilter);

	  for(i=0;i<3600;i++)		
	  {
		TsH[i]=dataafterfilter[i];
	  }   
	   SumTs = 0;
	   SumTcos = 0; 
	   SumTsin = 0;
	  for( i = 0;i<3600;i++)
	  {
		   SumTs = SumTs + TsH[i];
		   SumTcos = SumTcos + TsH[i] * cos(dw * i);
	       SumTsin = SumTsin + TsH[i] * sin(dw * i);
	   }
	   A0 = SumTs/3600;       //1.4084237494346061最小二乘圆的半径和圆心坐标
	   A1 = 2*SumTcos/3600;  //-0.29798988797225540
	   B1 = 2*SumTsin/3600; //-0.095864371049355274
	   
	   //求轮廓的最大最小值-----
	   m_datamax=DispMaxdirecMIC;
	   m_datamin=DispMindirecMIC;
       m_Middle=(m_datamax-m_datamin)/2; 

	   double maxchange;
	   if (m_datamax<0)
		   m_datamax=-m_datamax;
	   if (m_datamin<0)
	   {
		   m_datamin=-m_datamin;
	   }
	   
	   if (m_datamax<m_datamin)
	   {
		   maxchange=m_datamax;
		   m_datamax=m_datamin;
		   m_datamin=maxchange;
		   
	   }
	  
	   double  FDKP;
	   FDKP=28.5000/m_datamax;
	   A1Draw=MICDX*FDKP; //绘制圆度打点时圆心坐标显示
	   B1Draw=MICDY*FDKP; 
       A0Draw=A0*FDKP;
	  
	   //////////////////////算出轮廓的横、纵坐标///////////////////////////////
	   m_endposition=360;
	   m_startposition=0;
	   double m_aveangle=3600/360;
	   double m_endpoint=m_aveangle*m_endposition;
	   double m_startpoint=m_aveangle*m_startposition;
	   double m_spiltavenum;
	   m_spiltavenum=(m_endpoint-m_startpoint)/1;  
	   for (int j=0;j<1;j++)
	   {	
		   m_maxsplit[j]=0;
		   m_minsplit[j]=0;
		   
		   for (i=m_startpoint+j* m_spiltavenum; i< m_startpoint+(j+1)* m_spiltavenum;  i++)
		   {
			   
			   
			   if (m_maxsplit[j]<=dataafterfilter[i])
			   {
				   m_maxsplit[j]=dataafterfilter[i];
			   }
			   
			   if (m_minsplit[j]>=dataafterfilter[i])
			   {
				   m_minsplit[j]=dataafterfilter[i];
				   
			   }
			   
			   m_PV[j]=fabs(m_maxsplit[j])+fabs(m_minsplit[j]);		
		   }
		   
	   }
	double PV=m_PV[0];	    
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
	   for(i=0;i<3600;i++)		
	   { 
		   datas[i]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(dataafterfilter[i]-A0)*ratio*0.2/(rectJM.Height()*0.4/10)+RSLC;	  
		   drealx[i]=datas[i]*cos(i*dw)+dX0-A1;
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//实际轮廓的横、纵坐标(相对于二乘圆的)
	   }	

	   double rout2;
       rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	   m_Intstep=5;//间隔几个点打点连线
	   CPen penreal;
	   penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));     
	   CPen pendeal;
	   pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));


/*	   for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
			   memDCJM.SelectObject(&penreal);
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//蓝色曲线表示实际轮廓
			   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
			   memDCJM.LineTo(drealx[i+m_Intstep]+rectJM.left, drealy[i+m_Intstep]+rectJM.top);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
	   }
	   penreal.DeleteObject();

	  CPen RoutORin(PS_SOLID ,1*m_penScale,RGB(20,230,20));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rout2+rectJM.left,dY0-rout2+rectJM.top,dX0+rout2+rectJM.left,dY0+rout2+rectJM.top);//绘制圆环外圆
      RoutORin.DeleteObject();*/

	   for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
		   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		   {  
			   memDCJM.SelectObject(&pendeal);
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//蓝色曲线表示实际轮廓
			   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
			   memDCJM.LineTo(drealx[i+m_Intstep]+rectJM.left, drealy[i+m_Intstep]+rectJM.top);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
                   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

		   }
		   else
		   {
			   memDCJM.SelectObject(&penreal);
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(255,0,0));//蓝色曲线表示实际轮廓
			   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
			   memDCJM.LineTo(drealx[i+m_Intstep]+rectJM.left, drealy[i+m_Intstep]+rectJM.top);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
                    rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
	   }
	   
	   
	   CPen pencir;
	   pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
	   memDCJM.SelectObject(&pencir);
	   memDCJM.Ellipse(dX0-rout2+rectJM.left,dY0-rout2+rectJM.top,dX0+rout2+rectJM.left,dY0+rout2+rectJM.top);//绘制圆环外圆
	   double Rmincir=dX0/2-100*m_penScale;
	   pencir.DeleteObject();

	   
	   if(i>=3600-m_Intstep)
	   { 
		   for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		   {
			   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			   {   

				   memDCJM.SelectObject(&pendeal);
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//蓝色曲线表示实际轮廓
				   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
				   memDCJM.LineTo(drealx[0]+rectJM.left, drealy[0]+rectJM.top);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
					   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

			   }
			   else
			   {
				   memDCJM.SelectObject(&penreal);
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(255,0,0));//蓝色曲线表示实际轮廓
				   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
				   memDCJM.LineTo(drealx[0]+rectJM.left, drealy[0]+rectJM.top);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
					   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

			   }
		   }
	   }
	penreal.DeleteObject();



	   //-----------------绘制围绕一圈的小黑三角形---------------------------------
	   double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	   CPen penblack(PS_SOLID, 1*m_penScale, RGB(0, 0,0));
	   CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	   CBrush brushblack(RGB(0, 0, 0));
	   memDCJM.SelectObject(&brushblack);
	   CPoint pts[3];
	   double tr=2 * 3.1415926/36;// 每一次采样对应的角度间隔，弧度
	   double wzd=asin(6*m_penScale/m_maxRTriangle); //每次三角形的底边两点相对于定点的旋转角度
	   
	   for (i=0;i<36;i++)
	   {
		   memDCJM.SelectObject(&penblack);
		   pts[0].x = m_minrTriangle*cos(i*tr)+dX0+rectJM.left;
		   pts[0].y = m_minrTriangle*sin(i*tr)+dY0+rectJM.top;
		   
		   pts[1].x = m_maxRTriangle*cos(i*tr-wzd)+dX0+rectJM.left;
		   pts[1].y = m_maxRTriangle*sin(i*tr-wzd)+dY0+rectJM.top;
		   
		   pts[2].x = m_maxRTriangle*cos(i*tr+wzd)+dX0+rectJM.left;
		   pts[2].y = m_maxRTriangle*sin(i*tr+wzd)+dY0+rectJM.top;
		   
		   memDCJM.Polygon(pts, 3);
		   penblack.DeleteObject();
		   
		   if (i%9!=0)
		   {
			   memDCJM.SelectObject(&pengrey);
			   memDCJM.MoveTo(rin*cos(i*tr)+dX0+rectJM.left,rin*sin(i*tr)+dY0+rectJM.top);
			   memDCJM.LineTo(rout*cos(i*tr)+dX0+rectJM.left,rout*sin(i*tr)+dY0+rectJM.top);
			   pengrey.DeleteObject();
		   }
		   
	   }
	   
	   
	   brushblack.DeleteObject();
	   /////////////////////////////////////////////////////////////


}

void CJMAnalyse::MZCyuandu(double *Soudata)
{
	    //'MZC--最小区域法—两个同心圆的内外包容圆与显示轮廓至少有相间四点接触
    double Direc[7200],Sirec[3600];
    double SumTs=0,SumTcos=0,SumTsin=0,TsQ[3600],TsH[3600];
    double dw,A0,a1,b1, Maxdirec,Mindirec,GLiGangK;
     int   i=0,GDN=3600;
     int   ScanT,PVB0,MaxIndex,MinIndex,MinI1,MaxI1,MinI2,MaxI2;
	 BOOL   GLiGangFlag= false;//qy changed //BOOL  GLiGangFlag;

	GLiGangK=39.37008;
    dw=2*3.1415926/GDN;

	 
	////读取文件并绘图///
	LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//对应圆柱所有的点数
	m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//鼠标单击选中的截面
	pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;


	for(i=0;i<GDN;i++)		
	{ 
		TsQ[i]=(Soudata[i]-2048)*10/(GG1*GG2*4096); //计算圆度误差转换位移公式	
	}

    WLS_Filter(FilterMode,GDN,TsQ,TsH);
    for (i=0;i<GDN;i++)
	{
		SumTs=SumTs+TsH[i];
    }
    A0=SumTs/GDN;
	for (i=0;i<GDN;i++)
	{
	    TsH[i]=TsH[i]-A0;
	}
	SumTs=0;
    for (i=0;i<GDN;i++)
	{
		SumTs=SumTs+TsH[i];
	    SumTcos=SumTcos+TsH[i]*cos(dw*i);  //TsH[i]是采集的圆度数据转换成的位移量
        SumTsin=SumTsin+TsH[i]*sin(dw*i);
	}
    A0=SumTs/GDN;
    a1=2*SumTcos/GDN;
    b1=2*SumTsin/GDN;                     //最小二乘圆的圆心坐标和半径

    for (i=0;i<GDN;i++)
	{
    	Direc[i]=TsH[i]-A0-a1*cos(dw*i)-b1*sin(dw*i);
	    Direc[i+GDN]=Direc[i];
	}
    ScanT=0,PVB0=100;

    //--查找最大值和最小值以及其位置(1)  范围 0--Dn-1
    Maxdirec=Direc[0],Mindirec=Maxdirec;
    for (i=0;i<GDN;i++)
	{
        if(Direc[i]>Maxdirec)
		{
           Maxdirec=Direc[i];
           MaxIndex=i;
		}
        if (Direc[i]<Mindirec)
		{
		  Mindirec=Direc[i];
		  MinIndex=i;
		}
	}
    MinI1 = MinIndex;
    MaxI1 = MaxIndex;

    if (abs(MaxI1-MinI1)<GDN/2)    //最大值和最小值出现在半周之内==外匹配if-else==
	{
         if(MaxI1>MinI1)            //--匹配if-else-
		 {
			  //'先大1后小1,'--反方向找小2
              Maxdirec = Direc[MaxI1];
              Mindirec = Direc[MaxI1];
              for (i=MaxI1;i<=(GDN+MinI1-int(GDN/5));i++)
              {
				  if(Direc[i]>Maxdirec)
				  {
					 Maxdirec=Direc[i];
					 MaxIndex=i;
				  }
				  if(Direc[i]<Mindirec)
				  {
					 Mindirec=Direc[i];
				 	 MinIndex=i;
				  }
              }       
              MinI2 = MinIndex;// '--在小1和小2之间查找大2
              Maxdirec = Direc[MinI2];

              for(i=MinI2;i<=(GDN + MinI1);i++)
			  {
                if(Direc[i]>Maxdirec)
				{
                   Maxdirec=Direc[i];
                   MaxIndex=i;
				}
			  }
              MaxI2=MaxIndex;
		 }
         else    //'先小1后大1--------反方向找大2
		 {
              Maxdirec = Direc[MinI1];
              for(i=MinI1;i<=(GDN+MaxI1-int(GDN/5));i++)
			  {
                if(Direc[i]>Maxdirec)
				{
                   Maxdirec=Direc[i];
                   MaxIndex=i;
				}
			  }
              MaxI2=MaxIndex;
              Mindirec = Direc[MaxI2];   //'--在大2和大1之间查找小2
              
			  for(i=MaxI2;i<=(GDN+MaxI1);i++)
			  {
                  if(Direc[i]< Mindirec)
				  {
                     Mindirec = Direc[i];
                     MinIndex = i;
				  }
			  }
              MinI2 = MinIndex;
		 }

         if(MaxI2>GDN)
		 {
            MaxI2=MaxI2-GDN;
		 }
         if(MinI2>GDN)
		 {
            MinI2 = MinI2 - GDN;
		 }
	}
 
  else    // '最大值和最小值出现在半周之外
   {
        if (MaxI1>MinI1)//'先小1后大1  '--反方向找大值
		{
            Maxdirec=Direc[MinI1];
            for(i=MinI1;i<=(MaxI1-int(GDN/5));i++)
			{
               if (Direc[i]>Maxdirec)
			   {
                   Maxdirec=Direc[i];
                   MaxIndex=i;
			   }
			}
            MaxI2 = MaxI1;
            MaxI1 = MaxIndex;
            //'-新大值作为大1,原大1作为大2,在大1和大2之间查找小2
            Mindirec = Direc[MaxI1];
            for(i=MaxI1;i<=MaxI2;i++)
			{
               if(Direc[i]<Mindirec)
			   {
                  Mindirec=Direc[i];
                  MinIndex=i;
			   }
			}
            MinI2 = MinIndex;
		}
        else  //'先大1后小1,'--反方向找小值
		{
             Mindirec=Direc[MaxI1];
             for(i=MaxI1;i<=(MinI1-int(GDN/5));i++)
			 {
               if(Direc[i]<Mindirec)
			   {
                  Mindirec=Direc[i];
                  MinIndex=i;
			   }
			 }
             MinI2 = MinI1;
             MinI1 = MinIndex;

             // '-新小值作为小1,原小1作为小2,在小1和小2之间查找大2
             Maxdirec = Direc[MinI1];
             for(i=MinI1;i<=MinI2;i++)
			 {
                  if(Direc[i]>Maxdirec)
				  {
                     Maxdirec=Direc[i];
                     MaxIndex=i;
				  }
			 }
             MaxI2=MaxIndex;
		}
	}
   
  PDMZCTJ:  // '判断条件满足?=========根据相间四点作交叉线
      double Zc1,A2,b2,Zc2,D,D1,D2,U1,U2,U0,TempK,PVB;
       a1 = cos(dw*MaxI1)-cos(dw*MaxI2);
       b1 = sin(dw*MaxI1)-sin(dw*MaxI2);
       Zc1= TsH[MaxI1]-TsH[MaxI2];
       A2 = cos(dw*MinI1)-cos(dw*MinI2);
       b2 = sin(dw*MinI1)-sin(dw*MinI2);
       Zc2= TsH[MinI1]-TsH[MinI2];
       D = a1*b2-A2*b1;
       D1=Zc1*b2-Zc2*b1;
       D2=a1*Zc2-A2*Zc1;
       if(D==0)   goto ErrQuit;
       U1=D1/D;
	   U2=D2/D;
       U0=(TsH[MaxI1]+TsH[MinI1]-U1*(cos(dw*MaxI1)+cos(dw * MinI1))-U2*(sin(dw*MaxI1)+sin(dw*MinI1)))/2;
       Maxdirec = TsH[MaxI1]-U0-U1*cos(dw*MaxI1)-U2*sin(dw*MaxI1);
       Mindirec = -Maxdirec;
       MaxIndex = 0;
       MinIndex = 0;
       TempK = 0;
       //'MsgBox "scant=" & ScanT & " " & MaxI1 & " " & MinI1 & " " & MaxI2 & " " & MinI2
       for(i=0 ;i<GDN;i++)
	   {
           Sirec[i]=TsH[i]-U0-U1*cos(dw*i)-U2*sin(dw*i);
           if((i==MaxI1)||(i==MaxI2)||(i==MinI1)||(i==MinI2))
			   ;
           else
		   {
              if(Sirec[i]>Maxdirec)
			  {
                  Maxdirec=Sirec[i];
                  MaxIndex=i;
			  }
              if(Sirec[i]<Mindirec)
			  {
                  Mindirec=Sirec[i];
                  MinIndex=i;
			  }
		   }
	   }
       if((MaxIndex==0) && (MinIndex==0))    //' 查找完毕,成功
	   {
          PVB=2*Maxdirec;
          GResult[1]=PVB;
	   }
       else goto CxScanLp;
       goto QKquit;//'---没有找到符合条件的相间四点,重新查找----
  
  CxScanLp: 
          double U00,U10,U20;
		  ScanT=ScanT+1;
          PVB = 2*Maxdirec;
          if(PVB<PVB0)
		  {
            PVB0=PVB;
            U00=U0;
            U10=U1;
            U20=U2;
		  }
          if(ScanT>20) 
		  {
               ERRAquit: GResult[1]=PVB;       // GResult[1]=PVB;// ' 错误退出
		  }
		  else
		  {
               if(MaxI1>MaxI2)
			   {
                  i=MaxI2;
                  MaxI2=MaxI1;
                  MaxI1=i;
			   }
              if(MinI1>MinI2)
			  {
                 i = MinI2;
                 MinI2 = MinI1;
                 MinI1 = i;
			  }
              if(MaxI1>MinI1)
			  {
                 TempK=1;
			  }
          if( MaxIndex!=0)
		  {	            // '1470
               if((MaxIndex>MinI1) && (MaxIndex<MinI2))
			   {
                  if(TempK==0)
                     MaxI2=MaxIndex;
                  else
                     MaxI1 = MaxIndex;
			   }
		       else
			   {
                  if(TempK==0)
                    MaxI1 = MaxIndex;
                  else
                    MaxI2 = MaxIndex;
			   }
		  }
          else
		  {              // '1420
              if((MinIndex>MaxI1) && (MinIndex<MaxI2)) //'1450
			  {
                 if(TempK==0)
                    MinI1 = MinIndex;
                 else
                    MinI2 = MinIndex;
			  }
              else //'1430
			  {
                 if(TempK == 0)
                    MinI2 = MinIndex;
                 else
                    MinI1 = MinIndex;
			  }
		  }
         goto PDMZCTJ ;//'判断条件满足?
   }            
		  
ErrQuit: //' 错误退出
   GResult[1]= PVB;     
	 
QKquit:
  if(GLiGangFlag==1) 
  {
	   GResult[1]= GResult[1] * GLiGangK;
	   GResult[2]= GResult[2] * GLiGangK;
	   GResult[4] = GResult[4]* GLiGangK;
	   GResult[5] = GResult[5]* GLiGangK;
  }
    DispMaxdirecMZC=Maxdirec;
    DispMindirecMZC=Mindirec;
    MZCDX=U1;
    MZCDY=U2;

	MZCEcc=sqrt(U1*U1+U2*U2);
	MZCEccPos=atan2(U2,U1);
	m_strdEcc.Format("%.2f",MZCEcc); 
//    m_strdEccPos.Format("%.2f",MZCEccPos); 
    m_MZCRONT.Format("%.3f",GResult[1]);  //在报表中显示最小区域法评定圆度误差的结果

}

void CJMAnalyse::DrawCircleMZC()
{
	  ReadDataFromFile();//调用最小区域法评定圆度误差,里面包含读取文件的函数

  	  //最小区域法圆心MZCDX, MZCDY, 最大值DispMaxdirec和最小值DispMindirec

      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
	  double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.right*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5/2;
      double dw= 2*3.1415926/3600;
	  int i,x1,y1,x2,y2;
	  //rin为0圆，RSLC为2018圆，rout为4096圆 
	  //double rout=260*m_penScale,Everystrcod=(rout)/10,rin=200*m_penScale,RSLC=(rout+rin)/2;
      double rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=0.5*rout,RSLC=(rout+rin)/2;
      double th,rout1=257*m_penScale;
      CString strcodinate;

	  	  //绘制底色圆环带
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //绘制黄色圆环带 
	  memDCJM.SelectObject(&penRing); 
	  for(th=0;th<PI*2;th+=dw)
	  {
		  x1=dX0-(int)rin*cos(th);
		  y1=dY0-(int)rin*sin(th);
		  x2=dX0-(int)rout*cos(th);
		  y2=dY0-(int)rout*sin(th);
		  memDCJM.MoveTo(x1,y1);
		  memDCJM.LineTo(x2,y2);	 
	  }	 
	  penRing.DeleteObject();	
	  
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //绘制圆环变紫色带 
	  memDCJM.SelectObject(&ping); 
	  for (i=0;i<3600;i++)
	  {
		  if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		  {
			  x1=dX0-(int)rin*cos(i*dw-PI);
			  y1=dY0-(int)rin*sin(i*dw-PI);
			  x2=dX0-(int)rout*cos(i*dw-PI);
			  y2=dY0-(int)rout*sin(i*dw-PI);
			  memDCJM.MoveTo(x1,y1);
			  memDCJM.LineTo(x2,y2);
		  }		
	  }	
	  ping.DeleteObject();
	  //----------构造动态圆环---------
	  if (flagmanchuli==1)
	  {	   
		  m_IndexStart=alpha1/dw;
		  m_IndexEnd=alpha2/dw;	
		  if (FlagMove%2==0)
		  {
			  DynamicDrawCircleJM(m_IndexStart,m_IndexEnd);		
			  
			  
		  }
		  else  
		  {      
			  if ( 6.2814-alpha2>6.2814-alpha1)
			  {		
				  DynamicDrawCircleJM(m_IndexStart,3599);	
				  DynamicDrawCircleJM(0,m_IndexEnd);
			  }
			  else if ( 6.2814-alpha1>6.2814-alpha2)
			  {
				  DynamicDrawCircleJM(m_IndexStart,0);	
				  DynamicDrawCircleJM(3599,m_IndexEnd);				
			  }			
		  }
	  }	

	  //----------------------以上代码实现灵活的选取-----------

	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //创建空画刷，防止遮挡内
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//选择画刷 
	  
	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//绘制圆环内圆
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//绘制圆环外圆
      RoutORin.DeleteObject();
	  
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////绘制坐标轴//////////////////////////////////
	  double EverystrcodX=(rout)/10,EverystrcodY=EverystrcodX;
	  CPen pen1 (PS_DOT,1*m_penScale,RGB(125,125,125));
	  memDCJM.SelectObject(&pen1); 
	  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0-EverystrcodX*7);
	  memDCJM.LineTo(dX0+EverystrcodX*7,dY0+EverystrcodX*7);
	  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0+EverystrcodX*7);
	  memDCJM.LineTo(dX0+EverystrcodX*7,dY0-EverystrcodX*7);
	  pen1.DeleteObject();
	  CPen penCoordinate (PS_SOLID,1*m_penScale,RGB(0,0,0));
	  memDCJM.SelectObject(&penCoordinate); 
	  
	  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0);
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);//绘制x轴
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/2,dY0-EverystrcodY/2,"0°");
	  memDCJM.TextOut(rectJM.left,dY0-EverystrcodY/2,"180°");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45°");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225°");
	  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //绘制y轴
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0+EverystrcodY*11,"270°");
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0-EverystrcodY*11.5,"90°");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135°");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315°");

	  
	  
	  for(i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //绘制X正轴刻度
		  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	  }	
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //绘制X负轴刻度
		  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	  }
	  for( i=0; i<10; i++)      //写Y正轴刻度值
	  {
		  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		  memDCJM.MoveTo(dX0-4*m_penScale, dY0-i*EverystrcodY);
		  memDCJM.LineTo(dX0+4*m_penScale, dY0-i*EverystrcodY);	
	  }
	  for( i=0; i<10; i++)  
	  {
		  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		  memDCJM.MoveTo(dX0-4*m_penScale, dY0+i*EverystrcodY);
		  memDCJM.LineTo(dX0+4*m_penScale, dY0+i*EverystrcodY);
	  }
	  penCoordinate.DeleteObject();
	  ////////////////////////////////////////////////////////////////////////////////
	  //====================================================//
	  //第几个截面参数是传递过来的///////////////////截面参数是M;
	  for (i=0;i<3600;i++)	
	  {  
		  fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		  m_CirCal[i]=fpdata[i];    //计算圆度误差转换位移公式		
	  }
	
	  for(i=0;i<3600;i++)		
	  { 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //计算圆度误差转换位移公式	
       // dataafterfilter[i]=fpdata[i];
	  }
       DrawFilter (FilterMode,datacir,dataafterfilter);

	  for(i=0;i<3600;i++)		
	  {
		TsH[i]=dataafterfilter[i];
	  }   
	   SumTs = 0;
	   SumTcos = 0; 
	   SumTsin = 0;
	  for( i = 0;i<3600;i++)
	  {
		   SumTs = SumTs + TsH[i];
		   SumTcos = SumTcos + TsH[i] * cos(dw * i);
	       SumTsin = SumTsin + TsH[i] * sin(dw * i);
	   }
	   A0 = SumTs/3600;       //1.4084237494346061最小二乘圆的半径和圆心坐标
	   A1 = 2*SumTcos/3600;  //-0.29798988797225540
	   B1 = 2*SumTsin/3600; //-0.095864371049355274
	   
	   //求轮廓的最大最小值-----
	   m_datamax=DispMaxdirecMZC;
	   m_datamin=DispMindirecMZC;
       m_Middle=(m_datamax-m_datamin)/2;//0 

	   double  FDKP;
	   FDKP=29.0000/m_datamax;
	   A1Draw=MZCDX*FDKP; //绘制圆度打点时圆心坐标显示
	   B1Draw=MZCDY*FDKP; 
       A0Draw=A0*FDKP;
	  
	   //////////////////////算出轮廓的横、纵坐标///////////////////////////////
	  
	   m_endposition=360;
	   m_startposition=0;
	   double m_aveangle=3600/360;
	   double m_endpoint=m_aveangle*m_endposition;
	   double m_startpoint=m_aveangle*m_startposition;
	   double m_spiltavenum;
	   m_spiltavenum=(m_endpoint-m_startpoint)/1;  
	   for (int j=0;j<1;j++)
	   {	
		   m_maxsplit[j]=0;
		   m_minsplit[j]=0;
		   
		   for (i=m_startpoint+j* m_spiltavenum; i< m_startpoint+(j+1)* m_spiltavenum;  i++)
		   {
			   
			   
			   if (m_maxsplit[j]<=dataafterfilter[i])
			   {
				   m_maxsplit[j]=dataafterfilter[i];
			   }
			   
			   if (m_minsplit[j]>=dataafterfilter[i])
			   {
				   m_minsplit[j]=dataafterfilter[i];
				   
			   }
			   
			   m_PV[j]=fabs(m_maxsplit[j])+fabs(m_minsplit[j]);		
		   }
		   
	   }
	double PV=m_PV[0];	    
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
	   for(i=0;i<3600;i++)		
	   { 
		   datas[i]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(dataafterfilter[i]-A0)*ratio*0.2/(rectJM.Height()*0.4/10)+RSLC;
		   drealx[i]=datas[i]*cos(i*dw)+dX0-A1;
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//实际轮廓的横、纵坐标(相对于二乘圆的)
	   }	

	   double rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0)),
		   rout3=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	   m_Intstep=5;//间隔几个点打点连线
	   CPen penreal;
	   penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));     
	   CPen pendeal;
	   pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0)); 
	   
/*	   for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
			   memDCJM.SelectObject(&penreal);
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//蓝色曲线表示实际轮廓
			   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
			   memDCJM.LineTo(drealx[i+m_Intstep]+rectJM.left, drealy[i+m_Intstep]+rectJM.top);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
               
	           if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout3)
               rout3=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
               
	   }
	   penreal.DeleteObject();*/

	   for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
		   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		   {  
			   memDCJM.SelectObject(&pendeal);
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//蓝色曲线表示实际轮廓
			   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
			   memDCJM.LineTo(drealx[i+m_Intstep]+rectJM.left, drealy[i+m_Intstep]+rectJM.top);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
				   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
               
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout3)
                   rout3=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
		   else
		   {
			   memDCJM.SelectObject(&penreal);
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(255,0,0));//蓝色曲线表示实际轮廓
			   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
			   memDCJM.LineTo(drealx[i+m_Intstep]+rectJM.left, drealy[i+m_Intstep]+rectJM.top);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
				   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
               
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout3)
                   rout3=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
	   }
	   

	   CPen pencir;
	   pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
	   memDCJM.SelectObject(&pencir);
	   memDCJM.Ellipse(dX0-rout2+rectJM.left,dY0-rout2+rectJM.top,dX0+rout2+rectJM.left,dY0+rout2+rectJM.top);//绘制圆环外圆
	   memDCJM.Ellipse(dX0-rout3+rectJM.left,dY0-rout3+rectJM.top,dX0+rout3+rectJM.left,dY0+rout3+rectJM.top);//绘制圆环内圆
	   double Rmincir=dX0/2-100*m_penScale;
	   pencir.DeleteObject();
	 
	    
	   if(i>=3600-m_Intstep)
	   { 
		   for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		   {
			   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			   {   
				   memDCJM.SelectObject(&pendeal);
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//蓝色曲线表示实际轮廓
				   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
				   memDCJM.LineTo(drealx[0]+rectJM.left, drealy[0]+rectJM.top);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
					   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
				   
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout3)
                       rout3=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
			   }
			   else
			   {
				   memDCJM.SelectObject(&penreal);
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(255,0,0));//蓝色曲线表示实际轮廓
				   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
				   memDCJM.LineTo(drealx[0]+rectJM.left, drealy[0]+rectJM.top);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
					   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
				   
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout3)
                       rout3=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
			   }
		   }
	   }
	penreal.DeleteObject();
      
	   //-----------------绘制围绕一圈的小黑三角形---------------------------------
	   double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	   CPen penblack(PS_SOLID, 1*m_penScale, RGB(0, 0,0));
	   CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	   CBrush brushblack(RGB(0, 0, 0));
	   memDCJM.SelectObject(&brushblack);
	   CPoint pts[3];
	   double tr=2 * 3.1415926/36;// 每一次采样对应的角度间隔，弧度
	   double wzd=asin(6*m_penScale/m_maxRTriangle); //每次三角形的底边两点相对于定点的旋转角度
	   
	   for (i=0;i<36;i++)
	   {
		   memDCJM.SelectObject(&penblack);
		   pts[0].x = m_minrTriangle*cos(i*tr)+dX0+rectJM.left;
		   pts[0].y = m_minrTriangle*sin(i*tr)+dY0+rectJM.top;
		   
		   pts[1].x = m_maxRTriangle*cos(i*tr-wzd)+dX0+rectJM.left;
		   pts[1].y = m_maxRTriangle*sin(i*tr-wzd)+dY0+rectJM.top;
		   
		   pts[2].x = m_maxRTriangle*cos(i*tr+wzd)+dX0+rectJM.left;
		   pts[2].y = m_maxRTriangle*sin(i*tr+wzd)+dY0+rectJM.top;
		   
		   memDCJM.Polygon(pts, 3);
		   penblack.DeleteObject();
		   
		   if (i%9!=0)
		   {
			   memDCJM.SelectObject(&pengrey);
			   memDCJM.MoveTo(rin*cos(i*tr)+dX0+rectJM.left,rin*sin(i*tr)+dY0+rectJM.top);
			   memDCJM.LineTo(rout*cos(i*tr)+dX0+rectJM.left,rout*sin(i*tr)+dY0+rectJM.top);
			   pengrey.DeleteObject();
		   }
		   
	   }
	   
	   
	   brushblack.DeleteObject();
	   /////////////////////////////////////////////////////////////
	

}

void CJMAnalyse::PrintCircleMCC()
{
	  //读取文件并绘图
	  ReadDataFromFile();//调用最小区域法评定圆度误差
  	  //最小区域法圆心MZCDX, MZCDY, 
      //最小区域法的最大值和最小值 DispMaxdirec,DispMindirec
      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
	  double dY0= rectJM.Height()/2+rectJM.top,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5*1/2+rectJM.left;
	  CString strcodinate;
	  //rin为0圆，RSLC为2018圆，rout为4096圆
	  int i,x1,y1,x2,y2;
	  double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	  dw=2*PI/3600;
	  
	  
	  //绘制底色圆环带
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //绘制黄色圆环带 
	  memDCJM.SelectObject(&penRing); 
	  for(th=0;th<PI*2;th+=dw)
	  {
		  x1=dX0-(int)rin*cos(th);
		  y1=dY0-(int)rin*sin(th);
		  x2=dX0-(int)rout*cos(th);
		  y2=dY0-(int)rout*sin(th);
		  memDCJM.MoveTo(x1,y1);
		  memDCJM.LineTo(x2,y2);	 
	  }	 
	  penRing.DeleteObject();	
	  
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //绘制圆环变紫色带 
	  memDCJM.SelectObject(&ping); 
	  for (i=0;i<3600;i++)
	  {
		  if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		  {
			  x1=dX0-(int)rin*cos(i*dw-PI);
			  y1=dY0-(int)rin*sin(i*dw-PI);
			  x2=dX0-(int)rout*cos(i*dw-PI);
			  y2=dY0-(int)rout*sin(i*dw-PI);
			  memDCJM.MoveTo(x1,y1);
			  memDCJM.LineTo(x2,y2);
		  }		
	  }	
    ping.DeleteObject();
	  //----------构造动态圆环---------
	  if (flagmanchuli==1)
	  {	   
		  m_IndexStart=alpha1/dw;
		  m_IndexEnd=alpha2/dw;	
		  if (FlagMove%2==0)
		  {
			  DynamicDrawCircleJM(m_IndexStart,m_IndexEnd);		
			  
			  
		  }
		  else  
		  {      
			  if ( 6.2814-alpha2>6.2814-alpha1)
			  {		
				  DynamicDrawCircleJM(m_IndexStart,3599);	
				  DynamicDrawCircleJM(0,m_IndexEnd);
			  }
			  else if ( 6.2814-alpha1>6.2814-alpha2)
			  {
				  DynamicDrawCircleJM(m_IndexStart,0);	
				  DynamicDrawCircleJM(3599,m_IndexEnd);				
			  }			
		  }
	}	

	  //----------------------以上代码实现灵活的选取-----------
	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //创建空画刷，防止遮挡内
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//选择画刷 

	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//绘制圆环内圆
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//绘制圆环外圆
      RoutORin.DeleteObject();
	
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////绘制坐标轴//////////////////////////////////

	  double EverystrcodX=(rout)/10,EverystrcodY=EverystrcodX;
	  CPen pen1 (PS_DOT,1*m_penScale,RGB(125,125,125));
	  memDCJM.SelectObject(&pen1); 
	  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0-EverystrcodX*7);
	  memDCJM.LineTo(dX0+EverystrcodX*7,dY0+EverystrcodX*7);
	  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0+EverystrcodX*7);
	  memDCJM.LineTo(dX0+EverystrcodX*7,dY0-EverystrcodX*7);
	  pen1.DeleteObject();
	  CPen penCoordinate (PS_SOLID,1*m_penScale,RGB(0,0,0));

	  memDCJM.SelectObject(&penCoordinate); 
	  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0);
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);                    //绘制x轴
	  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0-10); 
	  memDCJM.LineTo(dX0-EverystrcodX*10,dY0+10);
	  memDCJM.MoveTo(dX0+EverystrcodX*10,dY0-10); 
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0+10);
	  //memDCJM.TextOut(dX0+EverystrcodX*10+10,dY0-10,"0°");
	  //memDCJM.TextOut(dX0-rout-40,dY0-10,"180°");
	  memDCJM.TextOut(dX0+rout*1.05,dY0-rout*0.025,"0°");
	  memDCJM.TextOut(dX0-rout*1.15,dY0-rout*0.025,"180°");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45°");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225°");
	  

	  
	  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //绘制y轴
	  memDCJM.MoveTo(dX0+10,dY0+EverystrcodY*10);
	  memDCJM.LineTo(dX0-10,dY0+EverystrcodY*10);
	  memDCJM.MoveTo(dX0+10,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0-10,dY0-EverystrcodY*10);
	  //memDCJM.TextOut(dX0-10,dY0+EverystrcodY*10+10,"270°");
	  //memDCJM.TextOut(dX0-10,dY0-EverystrcodY*10-30,"90°");
	  memDCJM.TextOut(dX0-rout*0.026,dY0+rout*1.04,"270°");
	  memDCJM.TextOut(dX0-rout*0.026,dY0-rout*1.1,"90°");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135°");
      memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315°");
	  
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //绘制X正轴刻度
		  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	  }	
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //绘制X负轴刻度
		  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	  }
	  for( i=0; i<10; i++)      //写Y正轴刻度值
	  {
		  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		  memDCJM.MoveTo(dX0-4*m_penScale, dY0-i*EverystrcodY);
		  memDCJM.LineTo(dX0+4*m_penScale, dY0-i*EverystrcodY);	
	  }
	  for( i=0; i<10; i++)  
	  {
		  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		  memDCJM.MoveTo(dX0-4*m_penScale, dY0+i*EverystrcodY);
		  memDCJM.LineTo(dX0+4*m_penScale, dY0+i*EverystrcodY);
	  }
	  penCoordinate.DeleteObject();
	  ////////////////////////////////////////////////////////////////////////////////

     //====================================================//
		//第几个截面参数是传递过来的///////////////////截面参数是M;
		for (i=0;i<3600;i++)	
		{  
			fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
			m_CirCal[i]=fpdata[i];    //计算圆度误差转换位移公式		
		}	

			//手动处理后的数据进行调用函数计算	
			for(i=0;i<3600;i++)		
			{ 
				datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //计算圆度误差转换位移公式	
			}		
			WLS_Filter(FilterMode,3600,datacir,dataafterfilter);
			for(i=0;i<3600;i++)		
			{
				TsH[i]=dataafterfilter[i];
			}   
			SumTs = 0;
			SumTcos = 0; 
			SumTsin = 0;
			for( i = 0;i<3600;i++)
			{
				SumTs = SumTs + TsH[i];
				SumTcos = SumTcos + TsH[i] * cos(dw * i);
				SumTsin = SumTsin + TsH[i] * sin(dw * i);
			}
			A0 = SumTs/3600;       //1.4084237494346061最小二乘圆的半径和圆心坐标
			A1 = 2*SumTcos/3600;  //-0.29798988797225540
	        B1 = 2*SumTsin/3600; //-0.095864371049355274

	   //求轮廓的最大最小值-----
	   m_datamax=DispMaxdirecMCC;
	   m_datamin=DispMindirecMCC;
       m_Middle=(m_datamax+m_datamin)/2; 

	   double maxchange;
	   if (m_datamax<0)
		   m_datamax=-m_datamax;
	   if (m_datamin<0)
	   {
		   m_datamin=-m_datamin;
	   }
      
	   if (m_datamax<m_datamin)
	   {
		   maxchange=m_datamax;
		   m_datamax=m_datamin;
		   m_datamin=maxchange;

	   }

	   double  FDKP;
	   FDKP=43/m_datamax;
	   A1Draw=MCCDX*FDKP; //绘制圆度打点时圆心坐标显示
	   B1Draw=MCCDY*FDKP; 
       A0Draw=A0*FDKP;
	  //////////////////////算出轮廓的横、纵坐标///////////////////////////////
	   m_endposition=360;
	   m_startposition=0;
	   double m_aveangle=3600/360;
	   double m_endpoint=m_aveangle*m_endposition;
	   double m_startpoint=m_aveangle*m_startposition;
	   double m_spiltavenum;
	   m_spiltavenum=(m_endpoint-m_startpoint)/1;  
	   for (int j=0;j<1;j++)
	   {	
		   m_maxsplit[j]=0;
		   m_minsplit[j]=0;
		   
		   for (i=m_startpoint+j* m_spiltavenum; i< m_startpoint+(j+1)* m_spiltavenum;  i++)
		   {
			   
			   
			   if (m_maxsplit[j]<=dataafterfilter[i])
			   {
				   m_maxsplit[j]=dataafterfilter[i];
			   }
			   
			   if (m_minsplit[j]>=dataafterfilter[i])
			   {
				   m_minsplit[j]=dataafterfilter[i];
				   
			   }
			   
			   m_PV[j]=fabs(m_maxsplit[j])+fabs(m_minsplit[j]);		
		   }
		   
	   }
	double PV=m_PV[0];	   
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
	   for(i=0;i<3600;i++)		
	   { 
		   datas[i]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(dataafterfilter[i]-A0)*ratio*0.2*5/(rectJM.Height()*0.4/10)+RSLC;
		   drealx[i]=datas[i]*cos(i*dw)+dX0-A1;
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//实际轮廓的横、纵坐标(相对于二乘圆的)
	   }        
	double rout2;	 
	rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	m_Intstep=5;//间隔点数连线
	CPen penreal;
	penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));  
	CPen pendeal;
	pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));    
	
	for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	{ 
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{  
		   memDCJM.SelectObject(&pendeal);
		   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//绿色曲线表示手动处理区域
		   memDCJM.MoveTo(drealx[i], drealy[i]);
		   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);	
		   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));	   
		}
		else
		{
			memDCJM.SelectObject(&penreal);
			memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//蓝色曲线表示实际轮廓
			memDCJM.MoveTo(drealx[i], drealy[i]);
			memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
			if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		}
	}


      CPen pencir;
	  pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
	  memDCJM.SelectObject(&pencir);
	  memDCJM.Ellipse(dX0-rout2,dY0-rout2,dX0+rout2,dY0+rout2);	  //绘制圆环外圆
	  double Rmincir=dX0/2-100*m_penScale;
	  pencir.DeleteObject();


	if(i>=3600-m_Intstep)
	{ 
		for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		{
	       if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			{   
			    memDCJM.SelectObject(&pendeal);
			    memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//绿色曲线表示实际轮廓
		    	memDCJM.MoveTo(drealx[i], drealy[i]);
			    memDCJM.LineTo(drealx[0], drealy[0]);	
				if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
			else
			{
				memDCJM.SelectObject(&penreal);
				memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//蓝色曲线表示实际轮廓
				memDCJM.MoveTo(drealx[i], drealy[i]);
				memDCJM.LineTo(drealx[0], drealy[0]);
				if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
			}
		}
	}
	penreal.DeleteObject();


	double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	CPen penblack(PS_SOLID, 1*m_penScale, RGB(0,0,0));
	CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	CBrush brushblack(RGB(0, 0, 0));
    memDCJM.SelectObject(&brushblack);
	CPoint pts[3];
	double tr=2 * 3.1415926/36;// 每一次采样对应的角度间隔，弧度
	double wzd=asin(6*m_penScale/m_maxRTriangle); //每次三角形的底边两点相对于定点的旋转角度
	
	for (i=0;i<36;i++)
	{
		memDCJM.SelectObject(&penblack);
		pts[0].x = m_minrTriangle*cos(i*tr)+dX0;
		pts[0].y = m_minrTriangle*sin(i*tr)+dY0;
		
		pts[1].x = m_maxRTriangle*cos(i*tr-wzd)+dX0;
		pts[1].y = m_maxRTriangle*sin(i*tr-wzd)+dY0;
		
		pts[2].x = m_maxRTriangle*cos(i*tr+wzd)+dX0;
		pts[2].y = m_maxRTriangle*sin(i*tr+wzd)+dY0;
		
   	    memDCJM.Polygon(pts, 3);
        penblack.DeleteObject();
		
		if (i%9!=0)
		{
			memDCJM.SelectObject(&pengrey);
			memDCJM.MoveTo(rin*cos(i*tr)+dX0,rin*sin(i*tr)+dY0);
			memDCJM.LineTo(rout*cos(i*tr)+dX0,rout*sin(i*tr)+dY0);
            pengrey.DeleteObject();
		}
        
	}
    brushblack.DeleteObject();
	penblack.DeleteObject();
    brushblack.DeleteObject();
	//图形显示标注说明
	CString m_SelectJM,m_TotalJM;

    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);
	

	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"截面总数:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"当前截面:");
	
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+10*m_penScale,m_TotalJM);
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+30*m_penScale,m_SelectJM);
}

void CJMAnalyse::PrintCircleMIC()
{
			  //读取文件并绘图
	  ReadDataFromFile();//调用最小区域法评定圆度误差
  	  //最小区域法圆心MZCDX, MZCDY,最小区域法的最大值和最小值 DispMaxdirec,DispMindirec

      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
	  double dY0= rectJM.Height()/2+rectJM.top,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5*1/2+rectJM.left;
	  CString strcodinate;
	  //rin为0圆，RSLC为2018圆，rout为4096圆
	  int i,x1,y1,x2,y2;
	  double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
      dw=2*PI/3600;


	  //绘制底色圆环带
	  //绘制底色圆环带
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //绘制黄色圆环带 
	  memDCJM.SelectObject(&penRing); 
	  for(th=0;th<PI*2;th+=dw)
	  {
		  x1=dX0-(int)rin*cos(th);
		  y1=dY0-(int)rin*sin(th);
		  x2=dX0-(int)rout*cos(th);
		  y2=dY0-(int)rout*sin(th);
		  memDCJM.MoveTo(x1,y1);
		  memDCJM.LineTo(x2,y2);	 
	  }	 
	  penRing.DeleteObject();	
	  
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //绘制圆环变紫色带 
	  memDCJM.SelectObject(&ping); 
	  for (i=0;i<3600;i++)
	  {
		  if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		  {
			  x1=dX0-(int)rin*cos(i*dw-PI);
			  y1=dY0-(int)rin*sin(i*dw-PI);
			  x2=dX0-(int)rout*cos(i*dw-PI);
			  y2=dY0-(int)rout*sin(i*dw-PI);
			  memDCJM.MoveTo(x1,y1);
			  memDCJM.LineTo(x2,y2);
		  }		
	  }	
    ping.DeleteObject();

	  //----------构造动态圆环---------
	  if (flagmanchuli==1)
	  {	   
		  m_IndexStart=alpha1/dw;
		  m_IndexEnd=alpha2/dw;	
		  if (FlagMove%2==0)
		  {
			  DynamicDrawCircleJM(m_IndexStart,m_IndexEnd);		
			  
			  
		  }
		  else  
		  {      
			  if ( 6.2814-alpha2>6.2814-alpha1)
			  {		
				  DynamicDrawCircleJM(m_IndexStart,3599);	
				  DynamicDrawCircleJM(0,m_IndexEnd);
			  }
			  else if ( 6.2814-alpha1>6.2814-alpha2)
			  {
				  DynamicDrawCircleJM(m_IndexStart,0);	
				  DynamicDrawCircleJM(3599,m_IndexEnd);				
			  }			
		  }
	  }	

	  //----------------------以上代码实现灵活的选取-----------
	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //创建空画刷，防止遮挡内
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//选择画刷 

	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//绘制圆环内圆
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//绘制圆环外圆
      RoutORin.DeleteObject();

	  
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////绘制坐标轴//////////////////////////////////
	  	  double EverystrcodX=(rout)/10,EverystrcodY=EverystrcodX;
		  CPen pen1 (PS_DOT,1*m_penScale,RGB(125,125,125));
		  memDCJM.SelectObject(&pen1); 
		  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0-EverystrcodX*7);
		  memDCJM.LineTo(dX0+EverystrcodX*7,dY0+EverystrcodX*7);
		  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0+EverystrcodX*7);
		  memDCJM.LineTo(dX0+EverystrcodX*7,dY0-EverystrcodX*7);
	      pen1.DeleteObject();
		  CPen penCoordinate (PS_SOLID,1*m_penScale,RGB(0,0,0));
		  
		  memDCJM.SelectObject(&penCoordinate); 
		  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0);
		  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);                    //绘制x轴
		  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0-10); 
		  memDCJM.LineTo(dX0-EverystrcodX*10,dY0+10);
		  memDCJM.MoveTo(dX0+EverystrcodX*10,dY0-10); 
		  memDCJM.LineTo(dX0+EverystrcodX*10,dY0+10);
		  //memDCJM.TextOut(dX0+EverystrcodX*10+10,dY0-10,"0°");
		  //memDCJM.TextOut(dX0-rout-40,dY0-10,"180°");
		  memDCJM.TextOut(dX0+rout*1.05,dY0-rout*0.025,"0°");
		  memDCJM.TextOut(dX0-rout*1.15,dY0-rout*0.025,"180°");
		  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45°");
		  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225°");

		  
		  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
		  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //绘制y轴
		  memDCJM.MoveTo(dX0+10,dY0+EverystrcodY*10);
		  memDCJM.LineTo(dX0-10,dY0+EverystrcodY*10);
		  memDCJM.MoveTo(dX0+10,dY0-EverystrcodY*10);
		  memDCJM.LineTo(dX0-10,dY0-EverystrcodY*10);
		  //memDCJM.TextOut(dX0-10,dY0+EverystrcodY*10+10,"270°");
		  //memDCJM.TextOut(dX0-10,dY0-EverystrcodY*10-30,"90°");
		  memDCJM.TextOut(dX0-rout*0.026,dY0+rout*1.04,"270°");
		  memDCJM.TextOut(dX0-rout*0.026,dY0-rout*1.1,"90°");
		  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135°");
          memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315°");
		  
		  for( i=0; i<10; i++)
		  {
			  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //绘制X正轴刻度
			  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
			  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
		  }	
		  for( i=0; i<10; i++)
		  {
			  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //绘制X负轴刻度
			  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
			  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
		  }
		  for( i=0; i<10; i++)      //写Y正轴刻度值
		  {
			  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
			  memDCJM.MoveTo(dX0-4*m_penScale, dY0-i*EverystrcodY);
			  memDCJM.LineTo(dX0+4*m_penScale, dY0-i*EverystrcodY);	
		  }
		  for( i=0; i<10; i++)  
		  {
			  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
			  memDCJM.MoveTo(dX0-4*m_penScale, dY0+i*EverystrcodY);
			  memDCJM.LineTo(dX0+4*m_penScale, dY0+i*EverystrcodY);
		  }
	  penCoordinate.DeleteObject();
	  ////////////////////////////////////////////////////////////////////////////////
	  //====================================================//
	  //第几个截面参数是传递过来的///////////////////截面参数是M;
	  for (i=0;i<3600;i++)	
	  {  
		  fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		  m_CirCal[i]=fpdata[i];    //计算圆度误差转换位移公式		
	  }	

	  for(i=0;i<3600;i++)		
	  { 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //计算圆度误差转换位移公式	
       // dataafterfilter[i]=fpdata[i];
	  }
       WLS_Filter(FilterMode,3600,datacir,dataafterfilter);

	  for(i=0;i<3600;i++)		
	  {
		TsH[i]=dataafterfilter[i];
	  }   
	   SumTs = 0;
	   SumTcos = 0; 
	   SumTsin = 0;
	  for( i = 0;i<3600;i++)
	  {
		   SumTs = SumTs + TsH[i];
		   SumTcos = SumTcos + TsH[i] * cos(dw * i);
	       SumTsin = SumTsin + TsH[i] * sin(dw * i);
	   }
	   A0 = SumTs/3600;       //1.4084237494346061最小二乘圆的半径和圆心坐标
	   A1 = 2*SumTcos/3600;  //-0.29798988797225540
	   B1 = 2*SumTsin/3600; //-0.095864371049355274
	   
	   //求轮廓的最大最小值-----
	   m_datamax=DispMaxdirecMIC;
	   m_datamin=DispMindirecMIC;
       m_Middle=(m_datamax-m_datamin)/2; 

	   double maxchange;
	   if (m_datamax<0)
		   m_datamax=-m_datamax;
	   if (m_datamin<0)
	   {
		   m_datamin=-m_datamin;
	   }
	   
	   if (m_datamax<m_datamin)
	   {
		   maxchange=m_datamax;
		   m_datamax=m_datamin;
		   m_datamin=maxchange;
		   
	   }
	  
	   double  FDKP;
	   FDKP=28.5000/m_datamax;
	   A1Draw=MICDX*FDKP; //绘制圆度打点时圆心坐标显示
	   B1Draw=MICDY*FDKP; 
       A0Draw=A0*FDKP;
	  
	   //////////////////////算出轮廓的横、纵坐标///////////////////////////////
	   m_endposition=360;
	   m_startposition=0;
	   double m_aveangle=3600/360;
	   double m_endpoint=m_aveangle*m_endposition;
	   double m_startpoint=m_aveangle*m_startposition;
	   double m_spiltavenum;
	   m_spiltavenum=(m_endpoint-m_startpoint)/1;  
	   for (int j=0;j<1;j++)
	   {	
		   m_maxsplit[j]=0;
		   m_minsplit[j]=0;
		   
		   for (i=m_startpoint+j* m_spiltavenum; i< m_startpoint+(j+1)* m_spiltavenum;  i++)
		   {
			   
			   
			   if (m_maxsplit[j]<=dataafterfilter[i])
			   {
				   m_maxsplit[j]=dataafterfilter[i];
			   }
			   
			   if (m_minsplit[j]>=dataafterfilter[i])
			   {
				   m_minsplit[j]=dataafterfilter[i];
				   
			   }
			   
			   m_PV[j]=fabs(m_maxsplit[j])+fabs(m_minsplit[j]);		
		   }
		   
	   }
	double PV=m_PV[0];	   
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
	   for(i=0;i<3600;i++)		
	   { 
		   datas[i]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(dataafterfilter[i]-A0)*ratio*0.2*5/(rectJM.Height()*0.4/10)+RSLC;	  
		   drealx[i]=datas[i]*cos(i*dw)+dX0-A1;
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//实际轮廓的横、纵坐标(相对于二乘圆的)
	   }	

	   double rout2;
       rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	   m_Intstep=5;//间隔几个点打点连线
	   CPen penreal;
	   penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));     
	   CPen pendeal;
	   pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));

	   for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
		   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		   {  
			   memDCJM.SelectObject(&pendeal);
			   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//蓝色曲线表示实际轮廓
			   memDCJM.MoveTo(drealx[i], drealy[i]);
			   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
                   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

		   }
		   else
		   {
			   memDCJM.SelectObject(&penreal);
			   memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//蓝色曲线表示实际轮廓
			   memDCJM.MoveTo(drealx[i], drealy[i]);
			   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
                    rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
	   }
	   
	   
	   CPen pencir;
	   pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
	   memDCJM.SelectObject(&pencir);
	   memDCJM.Ellipse(dX0-rout2,dY0-rout2,dX0+rout2,dY0+rout2);//绘制圆环外圆
	   double Rmincir=dX0/2-100*m_penScale;
	   pencir.DeleteObject();

	   
	   if(i>=3600-m_Intstep)
	   { 
		   for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		   {
			   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			   {   

				   memDCJM.SelectObject(&pendeal);
				   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//蓝色曲线表示实际轮廓
				   memDCJM.MoveTo(drealx[i], drealy[i]);
				   memDCJM.LineTo(drealx[0], drealy[0]);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
					   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

			   }
			   else
			   {
				   memDCJM.SelectObject(&penreal);
				   memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//蓝色曲线表示实际轮廓
				   memDCJM.MoveTo(drealx[i], drealy[i]);
				   memDCJM.LineTo(drealx[0], drealy[0]);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
				   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

			   }
		   }
	   }
	penreal.DeleteObject();



	   //-----------------绘制围绕一圈的小黑三角形---------------------------------
	double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	CPen penblack(PS_SOLID, 1*m_penScale, RGB(0,0,0));
	CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	CBrush brushblack(RGB(0, 0, 0));
    memDCJM.SelectObject(&brushblack);
	CPoint pts[3];
	double tr=2 * 3.1415926/36;// 每一次采样对应的角度间隔，弧度
	double wzd=asin(6*m_penScale/m_maxRTriangle); //每次三角形的底边两点相对于定点的旋转角度
	
	for (i=0;i<36;i++)
	{
		memDCJM.SelectObject(&penblack);
		pts[0].x = m_minrTriangle*cos(i*tr)+dX0;
		pts[0].y = m_minrTriangle*sin(i*tr)+dY0;
		
		pts[1].x = m_maxRTriangle*cos(i*tr-wzd)+dX0;
		pts[1].y = m_maxRTriangle*sin(i*tr-wzd)+dY0;
		
		pts[2].x = m_maxRTriangle*cos(i*tr+wzd)+dX0;
		pts[2].y = m_maxRTriangle*sin(i*tr+wzd)+dY0;
		
   	    memDCJM.Polygon(pts, 3);
        penblack.DeleteObject();
		
		if (i%9!=0)
		{
			memDCJM.SelectObject(&pengrey);
			memDCJM.MoveTo(rin*cos(i*tr)+dX0,rin*sin(i*tr)+dY0);
			memDCJM.LineTo(rout*cos(i*tr)+dX0,rout*sin(i*tr)+dY0);
            pengrey.DeleteObject();
		}
        
	}
    brushblack.DeleteObject();
	penblack.DeleteObject();
    brushblack.DeleteObject();
	//图形显示标注说明
	CString m_SelectJM,m_TotalJM;
	
    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);

	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"截面总数:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"当前截面:");
	
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+30*m_penScale,m_TotalJM);
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+10*m_penScale,m_SelectJM);

}

void CJMAnalyse::PrintCircleMZC()
{
		  ReadDataFromFile();//调用最小区域法评定圆度误差,里面包含读取文件的函数

  	  //最小区域法圆心MZCDX, MZCDY, 最大值DispMaxdirec和最小值DispMindirec

      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
	  double dY0= rectJM.Height()/2+rectJM.top,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5*1/2+rectJM.left;
	  CString strcodinate;
	  //rin为0圆，RSLC为2018圆，rout为4096圆
	  int i,x1,y1,x2,y2;
	  double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	  dw=2*PI/3600;

	  	  //绘制底色圆环带
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //绘制黄色圆环带 
	  memDCJM.SelectObject(&penRing); 
	  for(th=0;th<PI*2;th+=dw)
	  {
		  x1=dX0-(int)rin*cos(th);
		  y1=dY0-(int)rin*sin(th);
		  x2=dX0-(int)rout*cos(th);
		  y2=dY0-(int)rout*sin(th);
		  memDCJM.MoveTo(x1,y1);
		  memDCJM.LineTo(x2,y2);	 
	  }	 
	  penRing.DeleteObject();	
	  
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //绘制圆环变紫色带 
	  memDCJM.SelectObject(&ping); 
	  for (i=0;i<3600;i++)
	  {
		  if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		  {
			  x1=dX0-(int)rin*cos(i*dw-PI);
			  y1=dY0-(int)rin*sin(i*dw-PI);
			  x2=dX0-(int)rout*cos(i*dw-PI);
			  y2=dY0-(int)rout*sin(i*dw-PI);
			  memDCJM.MoveTo(x1,y1);
			  memDCJM.LineTo(x2,y2);
		  }		
	  }	
	  ping.DeleteObject();
	  //----------构造动态圆环---------
	  if (flagmanchuli==1)
	  {	   
		  m_IndexStart=alpha1/dw;
		  m_IndexEnd=alpha2/dw;	
		  if (FlagMove%2==0)
		  {
			  DynamicDrawCircleJM(m_IndexStart,m_IndexEnd);		
			  
			  
		  }
		  else  
		  {      
			  if ( 6.2814-alpha2>6.2814-alpha1)
			  {		
				  DynamicDrawCircleJM(m_IndexStart,3599);	
				  DynamicDrawCircleJM(0,m_IndexEnd);
			  }
			  else if ( 6.2814-alpha1>6.2814-alpha2)
			  {
				  DynamicDrawCircleJM(m_IndexStart,0);	
				  DynamicDrawCircleJM(3599,m_IndexEnd);				
			  }			
		  }
	  }	

	  //----------------------以上代码实现灵活的选取-----------

	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //创建空画刷，防止遮挡内
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//选择画刷 
	  
	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//绘制圆环内圆
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//绘制圆环外圆
      RoutORin.DeleteObject();
	  
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////绘制坐标轴//////////////////////////////////
	  double EverystrcodX=(rout)/10,EverystrcodY=EverystrcodX;
	  CPen pen1 (PS_DOT,1*m_penScale,RGB(125,125,125));
	  memDCJM.SelectObject(&pen1); 
	  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0-EverystrcodX*7);
	  memDCJM.LineTo(dX0+EverystrcodX*7,dY0+EverystrcodX*7);
	  memDCJM.MoveTo(dX0-EverystrcodX*7,dY0+EverystrcodX*7);
	  memDCJM.LineTo(dX0+EverystrcodX*7,dY0-EverystrcodX*7);
	  pen1.DeleteObject();
	  CPen penCoordinate (PS_SOLID,1*m_penScale,RGB(0,0,0));
	  memDCJM.SelectObject(&penCoordinate); 
	  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0);
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);                    //绘制x轴
	  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0-10); 
	  memDCJM.LineTo(dX0-EverystrcodX*10,dY0+10);
	  memDCJM.MoveTo(dX0+EverystrcodX*10,dY0-10); 
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0+10);
	  //memDCJM.TextOut(dX0+EverystrcodX*10+10,dY0-10,"0°");
	  //memDCJM.TextOut(dX0-rout-40,dY0-10,"180°");
	  memDCJM.TextOut(dX0+rout*1.05,dY0-rout*0.025,"0°");
	  memDCJM.TextOut(dX0-rout*1.15,dY0-rout*0.025,"180°");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45°");
 	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225°");
	  
	  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //绘制y轴
	  memDCJM.MoveTo(dX0+10,dY0+EverystrcodY*10);
	  memDCJM.LineTo(dX0-10,dY0+EverystrcodY*10);
	  memDCJM.MoveTo(dX0+10,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0-10,dY0-EverystrcodY*10);
	  //memDCJM.TextOut(dX0-10,dY0+EverystrcodY*10+10,"270°");
	  //memDCJM.TextOut(dX0-10,dY0-EverystrcodY*10-30,"90°");
	  memDCJM.TextOut(dX0-rout*0.026,dY0+rout*1.04,"270°");
	  memDCJM.TextOut(dX0-rout*0.026,dY0-rout*1.1,"90°");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135°");
      memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315°");
	  
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //绘制X正轴刻度
		  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	  }	
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //绘制X负轴刻度
		  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	  }
	  for( i=0; i<10; i++)      //写Y正轴刻度值
	  {
		  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		  memDCJM.MoveTo(dX0-4*m_penScale, dY0-i*EverystrcodY);
		  memDCJM.LineTo(dX0+4*m_penScale, dY0-i*EverystrcodY);	
	  }
	  for( i=0; i<10; i++)  
	  {
		  strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		  memDCJM.MoveTo(dX0-4*m_penScale, dY0+i*EverystrcodY);
		  memDCJM.LineTo(dX0+4*m_penScale, dY0+i*EverystrcodY);
	  }
	  penCoordinate.DeleteObject();
	  ////////////////////////////////////////////////////////////////////////////////
	  //====================================================//
	  //第几个截面参数是传递过来的///////////////////截面参数是M;
	  for (i=0;i<3600;i++)	
	  {  
		  fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		  m_CirCal[i]=fpdata[i];    //计算圆度误差转换位移公式		
	  }
	
	  for(i=0;i<3600;i++)		
	  { 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //计算圆度误差转换位移公式	
       // dataafterfilter[i]=fpdata[i];
	  }
       WLS_Filter(FilterMode,3600,datacir,dataafterfilter);

	  for(i=0;i<3600;i++)		
	  {
		TsH[i]=dataafterfilter[i];
	  }   
	   SumTs = 0;
	   SumTcos = 0; 
	   SumTsin = 0;
	  for( i = 0;i<3600;i++)
	  {
		   SumTs = SumTs + TsH[i];
		   SumTcos = SumTcos + TsH[i] * cos(dw * i);
	       SumTsin = SumTsin + TsH[i] * sin(dw * i);
	   }
	   A0 = SumTs/3600;       //1.4084237494346061最小二乘圆的半径和圆心坐标
	   A1 = 2*SumTcos/3600;  //-0.29798988797225540
	   B1 = 2*SumTsin/3600; //-0.095864371049355274
	   
	   //求轮廓的最大最小值-----
	   m_datamax=DispMaxdirecMZC;
	   m_datamin=DispMindirecMZC;
       m_Middle=(m_datamax-m_datamin)/2;//0 

	   double  FDKP;
	   FDKP=29.0000/m_datamax;
	   A1Draw=MZCDX*FDKP; //绘制圆度打点时圆心坐标显示
	   B1Draw=MZCDY*FDKP; 
       A0Draw=A0*FDKP;
	  
	   //////////////////////算出轮廓的横、纵坐标///////////////////////////////
	  
	   m_endposition=360;
	   m_startposition=0;
	   double m_aveangle=3600/360;
	   double m_endpoint=m_aveangle*m_endposition;
	   double m_startpoint=m_aveangle*m_startposition;
	   double m_spiltavenum;
	   m_spiltavenum=(m_endpoint-m_startpoint)/1;  
	   for (int j=0;j<1;j++)
	   {	
		   m_maxsplit[j]=0;
		   m_minsplit[j]=0;
		   
		   for (i=m_startpoint+j* m_spiltavenum; i< m_startpoint+(j+1)* m_spiltavenum;  i++)
		   {
			   
			   
			   if (m_maxsplit[j]<=dataafterfilter[i])
			   {
				   m_maxsplit[j]=dataafterfilter[i];
			   }
			   
			   if (m_minsplit[j]>=dataafterfilter[i])
			   {
				   m_minsplit[j]=dataafterfilter[i];
				   
			   }
			   
			   m_PV[j]=fabs(m_maxsplit[j])+fabs(m_minsplit[j]);		
		   }
		   
	   }
	double PV=m_PV[0];	    
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
	   for(i=0;i<3600;i++)		
	   { 
		   datas[i]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(dataafterfilter[i]-A0)*ratio*0.2*5/(rectJM.Height()*0.4/10)+RSLC;
		   drealx[i]=datas[i]*cos(i*dw)+dX0-A1;
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//实际轮廓的横、纵坐标(相对于二乘圆的)
	   }	

	   double rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0)),
		   rout3=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	   m_Intstep=5;//间隔几个点打点连线
	   CPen penreal;
	   penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));     
	   CPen pendeal;
	   pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0)); 

	   for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
		   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		   {  
			   memDCJM.SelectObject(&pendeal);
			   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//蓝色曲线表示实际轮廓
			   memDCJM.MoveTo(drealx[i], drealy[i]);
			   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
				   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
               
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout3)
                   rout3=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
		   else
		   {
			   memDCJM.SelectObject(&penreal);
			   memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//蓝色曲线表示实际轮廓
			   memDCJM.MoveTo(drealx[i], drealy[i]);
			   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
				   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
               
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout3)
                   rout3=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
	   }
	   

	   CPen pencir;
	   pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
	   memDCJM.SelectObject(&pencir);
	   memDCJM.Ellipse(dX0-rout2,dY0-rout2,dX0+rout2,dY0+rout2);//绘制圆环外圆
	   memDCJM.Ellipse(dX0-rout3,dY0-rout3,dX0+rout3,dY0+rout3);//绘制圆环内圆
	   double Rmincir=dX0/2-100*m_penScale;
	   pencir.DeleteObject();
	 
	    
	   if(i>=3600-m_Intstep)
	   { 
		   for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		   {
			   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			   {   
				   memDCJM.SelectObject(&pendeal);
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//蓝色曲线表示实际轮廓
				   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
				   memDCJM.LineTo(drealx[0]+rectJM.left, drealy[0]+rectJM.top);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
					   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
				   
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout3)
                       rout3=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
			   }
			   else
			   {
				   memDCJM.SelectObject(&penreal);
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(255,0,0));//蓝色曲线表示实际轮廓
				   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
				   memDCJM.LineTo(drealx[0]+rectJM.left, drealy[0]+rectJM.top);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
					   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
				   
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout3)
                       rout3=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
			   }
		   }
	   }
	penreal.DeleteObject();
      
	   //-----------------绘制围绕一圈的小黑三角形---------------------------------
	double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	CPen penblack(PS_SOLID, 1*m_penScale, RGB(0,0,0));
	CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	CBrush brushblack(RGB(0, 0, 0));
    memDCJM.SelectObject(&brushblack);
	CPoint pts[3];
	double tr=2 * 3.1415926/36;// 每一次采样对应的角度间隔，弧度
	double wzd=asin(6*m_penScale/m_maxRTriangle); //每次三角形的底边两点相对于定点的旋转角度
	
	for (i=0;i<36;i++)
	{
		memDCJM.SelectObject(&penblack);
		pts[0].x = m_minrTriangle*cos(i*tr)+dX0;
		pts[0].y = m_minrTriangle*sin(i*tr)+dY0;
		
		pts[1].x = m_maxRTriangle*cos(i*tr-wzd)+dX0;
		pts[1].y = m_maxRTriangle*sin(i*tr-wzd)+dY0;
		
		pts[2].x = m_maxRTriangle*cos(i*tr+wzd)+dX0;
		pts[2].y = m_maxRTriangle*sin(i*tr+wzd)+dY0;
		
   	    memDCJM.Polygon(pts, 3);
        penblack.DeleteObject();
		
		if (i%9!=0)
		{
			memDCJM.SelectObject(&pengrey);
			memDCJM.MoveTo(rin*cos(i*tr)+dX0,rin*sin(i*tr)+dY0);
			memDCJM.LineTo(rout*cos(i*tr)+dX0,rout*sin(i*tr)+dY0);
            pengrey.DeleteObject();
		}
        
	}
    brushblack.DeleteObject();
	penblack.DeleteObject();
    brushblack.DeleteObject();
	//图形显示标注说明
	CString m_SelectJM,m_TotalJM;

    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);
	
	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"截面总数:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"当前截面:");

    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+30*m_penScale,m_TotalJM);
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+10*m_penScale,m_SelectJM);

}

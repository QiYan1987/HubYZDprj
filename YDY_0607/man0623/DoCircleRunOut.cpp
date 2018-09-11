// DoCircleRunOut.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DoCircleRunOut.h"
#include "MainFrm.h"
#include "math.h"
#include "PropertyDlg.h"
#include "DlgextendCircle.h"
#include "Dlgfrequency1.h"
#include <fstream>
#include <stdlib.h> 
#include <stdio.h>
#ifdef _DEBUG
#define WLS_PI 3.1415926
#define PI 3.1415926
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoCircleRunOut

IMPLEMENT_DYNCREATE(CDoCircleRunOut, CFormView)

CDoCircleRunOut::CDoCircleRunOut()
	: CFormView(CDoCircleRunOut::IDD)
{
	//{{AFX_DATA_INIT(CDoCircleRunOut)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Flagcircle=0;
	G1=1;
	G2=1;
    FilterMode=3;
	CirEvalue=0;
	FlagMove=0;
    m_BOOLSegmentprocess=0;
	FlagFrequency=0;
	m_bIsEnable=FALSE;
	m_IndexStart=0;
	m_IndexEnd=0;
	BoolButtondown=0;
	Frepointi=0;
	Frepointx=0;
	Frepointy=0;
	FlagBogao=0;
	m_strlvbo="1-500";
	m_strMethod="最小二乘法";
    m_Wa="";	//波纹度显示
	m_Wc="";	//波纹度显
	m_Wp="";	//波纹度显
	m_Wv="";	//波纹度显示
	m_Wt="";	//波纹度显
	m_Wq="";	//波纹度显
    m_Wwm="";	//波纹度显
    memset(m_BWD,0,sizeof(m_BWD));
	flag_bg=0;

}

CDoCircleRunOut::~CDoCircleRunOut()
{
}

void CDoCircleRunOut::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoCircleRunOut)
	DDX_Control(pDX, IDC_STATIC_CircleRunOut, m_Edit_CircleRunOut);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoCircleRunOut, CFormView)
	//{{AFX_MSG_MAP(CDoCircleRunOut)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_BTNDISABLE, OnBtndisable)
	ON_COMMAND(ID_BTNENABLE, OnBtnenable)
	ON_COMMAND(ID_BTNFENDUANCHULI, OnBtnfenduanchuli)
	ON_COMMAND(ID_BTNPPFX, OnBtnppfx)
	ON_COMMAND(ID_BTNRESETDEAL, OnBtnresetdeal)
	ON_COMMAND(ID_BTNYUANDUCHULI, OnBtnyuanduchuli)
	ON_COMMAND(ID_BTNCHULI, OnBtnchuli)
	ON_COMMAND(ID_BTNBGFX, OnBtnbgfx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoCircleRunOut diagnostics

#ifdef _DEBUG
void CDoCircleRunOut::AssertValid() const
{
	CFormView::AssertValid();
}

void CDoCircleRunOut::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoCircleRunOut message handlers

void CDoCircleRunOut::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
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
	m_bIsEnable=TRUE;
	
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
	m_Edit_CircleRunOut.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	// TODO: Add your specialized code here and/or call the base class
	
}

void CDoCircleRunOut::OnDestroy() 
{
	CFormView::OnDestroy();
	((CMainFrame*)AfxGetMainWnd())->DestroyVIEW(((CMainFrame*)AfxGetMainWnd())->m_DoCircleRunOut);
	((CMainFrame*)AfxGetMainWnd())->m_DoCircleRunOut=NULL;
	((CMainFrame*)AfxGetMainWnd())->Desktop();
	// TODO: Add your message handler code here
	
}

void CDoCircleRunOut::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	if (m_Edit_CircleRunOut.GetSafeHwnd())
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
		m_Edit_CircleRunOut.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}
	// TODO: Add your message handler code here
	
}
void CDoCircleRunOut::ReadDataFromFile()
{
	std::ifstream fin(((CMainFrame*)AfxGetMainWnd())->m_fullPath, std::ios::binary);
	//读取数据
	for (int i=0;i<3600;i++)
	{	
		fin.read((char*)&m_data[i], sizeof(shuju));
		fpdata[i]=m_data[i].data;
	}
	//读取信息
	fin.read((char*)&G1,sizeof(double));
	fin.read((char*)&G2,sizeof(double));
	fin.read((char*)&m_time,sizeof(CTime));
	fin.close();
}
/*
函数功能：1.实现坐标系的绘制和测量点的VC界面显示
2.当手动对数据处理时，在界面上实现变色处理
		  3.变色时包括点和点所在的区域一起变色
		  4.将最内圆、最外圆和基圆的代表数据显示在左上角
其中，轮廓打点的轮廓显示，需要根据率波段选择的不同而相应变化
*/
void CDoCircleRunOut::DrawCircle()
{
	////读取文件并绘图///
	ReadDataFromFile();

	//定义后面将要用到的变量
	double dY0= rect1.top+rect1.Height()/2,dleft=rect1.left,dtop=rect1.top,dright=rect1.left+rect1.Width()*3/5,
		dbottom=rect1.bottom,dX0=dleft+(dright-dleft)/2;
	CString strcodinate;

	//rin为0圆，RSLC为2018圆，rout为4096圆 
	int x1,y1,x2,y2;
	double th,rout=rect1.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	dw= 2 * 3.1415926/3600;// 每一次采样对应的角度间隔，弧度nTriangle.DeleteObject();

    CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //绘制圆环带 
    memDC.SelectObject(&penRing); 
    for(th=0;th<PI*2;th+=0.00157)
	 {
		 x1=dX0-(int)rin*cos(th);
		 y1=dY0-(int)rin*sin(th);
	     x2=dX0-(int)rout*cos(th);
	 	 y2=dY0-(int)rout*sin(th);
	 	 memDC.MoveTo(x1,y1);
	 	 memDC.LineTo(x2,y2);	 
 	 }	 
	penRing.DeleteObject();	
	int i;
	CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //绘制圆环变色带 
    memDC.SelectObject(&ping); 
    for (i=0;i<3600;i++)
	{
      	if (m_data[i].selected==1)
		{
			x1=dX0-(int)rin*cos(i*dw-PI);
			y1=dY0-(int)rin*sin(i*dw-PI);
			x2=dX0-(int)rout*cos(i*dw-PI);
			y2=dY0-(int)rout*sin(i*dw-PI);
			memDC.MoveTo(x1,y1);
	 	    memDC.LineTo(x2,y2);
		}
	}	
    ping.DeleteObject();
	
    //-构造动态圆环--
	if (flagmanchuli==1)
	{	   
        m_IndexStart=alpha1/dw;
	    m_IndexEnd=alpha2/dw;
		
		if (FlagMove%2==0)
		{
	    	 DynamicDrawCircle(m_IndexStart,m_IndexEnd);			
		}
		else  
		{      
			if ( 6.2814-alpha2>6.2814-alpha1)
			{
				
			    DynamicDrawCircle(m_IndexStart,3599);	
                DynamicDrawCircle(0,m_IndexEnd);
			}
			else if ( 6.2814-alpha1>6.2814-alpha2)
			{
				DynamicDrawCircle(m_IndexStart,0);	
                DynamicDrawCircle(3599,m_IndexEnd);				
			}			
		}
	}	
    //以上代码实现灵活的选取
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));     //创建空画刷，防止遮挡内
	CBrush *pOldBrush=memDC.SelectObject(pBrush);//选择画刷 

	CPen pencir;
	pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));    
	memDC.SelectObject(&pencir); 
    memDC.Ellipse(dX0-RSLC,dY0-RSLC,dX0+RSLC,dY0+RSLC);//绘制基圆(2048)
	pencir.DeleteObject();	
	CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	memDC.SelectObject(&RoutORin);               
    memDC.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//绘制圆环内圆
    memDC.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//绘制圆环外圆
    RoutORin.DeleteObject();
	
    ///////////////////////////////////////////////////////////////////
    ///////////////////////绘制坐标轴//////////////////////////////////
    double EverystrcodX=(rout)/10,EverystrcodY=EverystrcodX;
	CPen penCoordinate (PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDC.SelectObject(&penCoordinate); 

    memDC.MoveTo(dX0-EverystrcodX*10,dY0);
    memDC.LineTo(dX0+EverystrcodX*10,dY0);//绘制x轴
	memDC.TextOut(dX0+(rout+dright-dX0)/2,dY0-EverystrcodY/2,"0°");
	memDC.TextOut(rect1.left,dY0-EverystrcodY/2,"180°");
    memDC.MoveTo(dX0,dY0-EverystrcodY*10);
    memDC.LineTo(dX0,dY0+EverystrcodY*10);                      //绘制y轴
	memDC.TextOut(dX0-EverystrcodX/2,dY0+EverystrcodY*11,"270°");
    memDC.TextOut(dX0-EverystrcodX/2,dY0-EverystrcodY*11.5,"90°");
	
	
	for( i=0; i<10; i++)
	{
		strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //绘制X正轴刻度
		memDC.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		memDC.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	}	
	for( i=0; i<10; i++)
	{
		strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //绘制X负轴刻度
		memDC.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		memDC.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	}
	for( i=0; i<10; i++)      //写Y正轴刻度值
	{
		strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		memDC.MoveTo(dX0-4*m_penScale, dY0-i*EverystrcodY);
		memDC.LineTo(dX0+4*m_penScale, dY0-i*EverystrcodY);	
	}
	for( i=0; i<10; i++)  
	{
		strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		memDC.MoveTo(dX0-4*m_penScale, dY0+i*EverystrcodY);
		memDC.LineTo(dX0+4*m_penScale, dY0+i*EverystrcodY);
	}
	penCoordinate.DeleteObject();
    ////////////////////////////////////////////////////////////////////////////////
	
    double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	double m_datamax=0.0,m_datamin=0.0;

   //手动处理后的数据进行调用函数计算
   //////////////////////////////////////////////
   
   for(i=0;i<3600;i++)		
   { 
       datacir[i]=(fpdata[i]-2048)*10/(G1*G2*4096);    //计算圆度误差转换位移公式	
   }
   DrawFilter (FilterMode,datacir,dataafterfilter);//调用滤波函数，为后续的滤波后数据的显示与圆度的计算
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
	for(i=0;i<3600;i++)		
	{ 
		datas[i]=(dataafterfilter[i]-m_Middle)*(rout-rin)/m_OutIn+RSLC; //绘制圆度打点时按比例显示
		drealx[i]=datas[i]*cos(i*dw)+dX0;
    	drealy[i]=datas[i]*sin(i*dw)+dY0;//实际轮廓的横、纵坐标(相对于二乘圆的)
	}	
    m_Intstep=5;//间隔几个点打点连线
	CPen penreal;
	penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
  
	CPen pendeal;
	pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));   
  
	for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	{ 
		if (m_data[i].selected==1)
		{  memDC.SelectObject(&pendeal);
	       memDC.SetPixel(drealx[i],drealy[i],RGB(0,0,250));//绿色曲线表示手动处理后的轮廓
	       memDC.MoveTo(drealx[i], drealy[i]);
	       memDC.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);		
		}
		else
		{
		  memDC.SelectObject(&penreal);
          memDC.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//蓝色曲线表示实际轮廓
	      memDC.MoveTo(drealx[i], drealy[i]);
	      memDC.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
		}
	}

	if(i>=3600-m_Intstep)
	{ 
		for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		{
			if (m_data[i].selected==1)
			{  
				memDC.SelectObject(&pendeal);
			    memDC.SetPixel(drealx[i],drealy[i],RGB(0,0,250));//绿色曲线表示手动处理后的轮廓
			    memDC.MoveTo(drealx[i], drealy[i]);
		    	memDC.LineTo(drealx[0], drealy[0]);		
			}
			else
			{
				memDC.SelectObject(&penreal);
				memDC.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//蓝色曲线表示实际轮廓
				memDC.MoveTo(drealx[i], drealy[i]);
				memDC.LineTo(drealx[0], drealy[0]);
			}
		}
	}
	penreal.DeleteObject();
    pendeal.DeleteObject();
    pBrush->DeleteObject();

    //-----------------绘制围绕一圈的小黑三角形---------------------------------
	double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	CPen penblack(PS_SOLID, 1*m_penScale, RGB(0,0,0));
	CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	CBrush brushblack(RGB(0, 0, 0));
    memDC.SelectObject(&brushblack);
	CPoint pts[3];
	double tr=2 * 3.1415926/36;// 每一次采样对应的角度间隔，弧度
	double wzd=asin(6*m_penScale/m_maxRTriangle); //每次三角形的底边两点相对于定点的旋转角度

	for (i=0;i<36;i++)
	{
		memDC.SelectObject(&penblack);
		pts[0].x = m_minrTriangle*cos(i*tr)+dX0;
		pts[0].y = m_minrTriangle*sin(i*tr)+dY0;
		
		pts[1].x = m_maxRTriangle*cos(i*tr-wzd)+dX0;
		pts[1].y = m_maxRTriangle*sin(i*tr-wzd)+dY0;
		
		pts[2].x = m_maxRTriangle*cos(i*tr+wzd)+dX0;
		pts[2].y = m_maxRTriangle*sin(i*tr+wzd)+dY0;
		
   	    memDC.Polygon(pts, 3);
        penblack.DeleteObject();
       
		if (i%9!=0)
		{
			memDC.SelectObject(&pengrey);
			memDC.MoveTo(rin*cos(i*tr)+dX0,rin*sin(i*tr)+dY0);
			memDC.LineTo(rout*cos(i*tr)+dX0,rout*sin(i*tr)+dY0);
            pengrey.DeleteObject();
		}
        
	}
    brushblack.DeleteObject();
    /////////////////////////////////////////////////////////////

}
void CDoCircleRunOut::Segmentationprocess()
{
	////读取文件并绘图///
	ReadDataFromFile();
	//定义后面将要用到的变量
    double dY0= rect1.top+rect1.Height()/2,dleft=rect1.left,dtop=rect1.top,dright=rect1.left+rect1.Width()*3/5,
		dbottom=rect1.bottom,dX0=dleft+(dright-dleft)/2;
	double fw1=3*rect1.Width()/5,f1=rect1.Width(),f2=rect1.Height();                                                 	                             
    double fw2=rect1.Width()/30;
    double fh=rect1.Height()/2;
	double fh1=rect1.Height()/6;
	double fh2=rect1.Height()/30;
	
	CPen newPen;         
	newPen.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDC.SelectObject(&newPen); 

	memDC.MoveTo(rect1.left+fw2*3/2,dtop+fh); // 中线,横线
    memDC.LineTo(dright-fw1/40,dtop+fh); 

	memDC.MoveTo(rect1.left+fw2*3/2,dtop+fh-fh2*7);  //左边竖线
    memDC.LineTo(rect1.left+fw2*3/2,dtop+fh+fh2*6); 

	memDC.MoveTo(rect1.left+fw2*3/2,dtop+fh-fh2*7);  //左边箭头
    memDC.LineTo(rect1.left+fw2*3/2-6,dtop+fh-fh2*7+fh2*0.4); 
	memDC.MoveTo(rect1.left+fw2*3/2,dtop+fh-fh2*7);  
    memDC.LineTo(rect1.left+fw2*3/2+6,dtop+fh-fh2*7+fh2*0.4); 

	memDC.TextOut(rect1.left+fw2,rect1.top+fh1,"单位:um");	
    //绘制横坐标
	memDC.MoveTo(rect1.left+fw2*3/2,dtop+fh+fh2*6); // 中线,横线
    memDC.LineTo(dright-fw1/40,dtop+fh+fh2*6); 


	

    int m_endstart=m_endposition-m_startposition;
	CString mark;
	double m_avescale=(fw1-2*fw2)/4;
	double m_smallavescale=(dright-fw1/20-rect1.left-fw2*3/2)/(m_splitnumber*5);
	double m_splitave=(dright-fw1/20-rect1.left-fw2*3/2)/m_splitnumber;
	double m_splitmark=m_endstart/m_splitnumber;
    
	int i;
	/////////////////////////////////// 标注横坐标 ////////
	for(i=0;i<m_splitnumber*5;i++)    //写X轴小刻度值
	{
		memDC.MoveTo(rect1.left+fw2*3/2+m_smallavescale*i,dtop+fh+fh2*6);
		memDC.LineTo(rect1.left+fw2*3/2+m_smallavescale*i,dtop+fh+fh2*6-fh/50);
	}

	CPen newPenfenduan;         
	newPenfenduan.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDC.SelectObject(&newPenfenduan); 


	for(i=0;i<=m_splitnumber;i++)    //画分段线,X大刻度值
	{
		memDC.MoveTo(rect1.left+fw2*3/2+m_splitave*i,dtop+fh+fh2*6);
		memDC.LineTo(rect1.left+fw2*3/2+m_splitave*i,dtop+fh+fh2*6-fh/30);
		mark.Format("%.1f",m_splitmark*i+m_startposition);
		memDC.TextOut(rect1.left+fw2*7/8+m_splitave*i,dtop+fh+fh2*6+fh/60,mark);	
	}

    memDC.SetBkMode(TRANSPARENT); 
	////////////////////////////////////////////////////////////////////////////////
    double datacir[3600];
	double m_datamax=0.0,m_datamin=0.0,m_psum=0;

	//////////////////////////////////////////////
	for(i=0;i<3600;i++)		
	{ 
		datacir[i]=(fpdata[i]-2048)*10/(G1*G2*4096);   
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
    double m_jiange=fh2*12/m_OutIn;


	CPen newPeny;  // 中线平行线
	newPeny.CreatePen(PS_DOT,1*m_penScale,RGB(0,201,201));
    memDC.SelectObject(&newPeny);
	int j;
	for(j=1;j<6;j++)
	{
		memDC.MoveTo(rect1.left+fw2*3/2,dtop+fh+fh2*j);
		memDC.LineTo(dright-fw1/40,dtop+fh+fh2*j);
	}
    
	for(j=1;j<7;j++)
	{
		memDC.MoveTo(rect1.left+fw2*3/2,dtop+fh-fh2*j);
		memDC.LineTo(dright-fw1/40,dtop+fh-fh2*j);
	}


	mark.Format("%.2f",m_Middle);   //转化后的数值，Y中线坐标显示
	memDC.TextOut(rect1.left+fw2*1/3,dtop+fh,mark);

	mark.Format("%.2f",m_datamax-m_Middle);   //上Y坐标值显示
	memDC.TextOut(rect1.left+fw2*1/3,dtop+fh-fh2*7,mark);

	mark.Format("%.2f",m_datamin-m_Middle);   //下Y坐标值显示
	memDC.TextOut(rect1.left+fw2*1/3,dtop+fh+fh2*7,mark);
	
	double m_aveangle=3600/360;
	double m_startpoint=m_aveangle*m_startposition;
	double m_endpoint=m_aveangle*m_endposition;
    double m_endstartpiont=m_endpoint-m_startpoint;
	double m_avesize=(dright-fw1/40-rect1.left-fw2*3/2)/m_endstartpiont;
	double meter=10;//间隔点数

	for (i=m_startpoint+10;i<m_endpoint;i=i+5)
	{
		if (m_data[i].selected==1)
		{
			CPen newPenrelate; 
			newPenrelate.CreatePen(PS_SOLID,1*m_penScale,RGB(0,255,0));
			memDC.SelectObject(&newPenrelate); 
			memDC.SetPixel(rect1.left+fw2*3/2+m_avesize*(i-m_startpoint+meter),
				dtop+fh-(dataafterfilter[i]-m_Middle)*m_jiange,RGB(0,255,0));
  			memDC.MoveTo(rect1.left+fw2*3/2+m_avesize*(i-m_startpoint+meter),
				dtop+fh-(dataafterfilter[i]-m_Middle)*m_jiange);
   			memDC.LineTo(rect1.left+fw2*3/2+m_avesize*(i-m_startpoint),
				dtop+fh-(dataafterfilter[i-10]-m_Middle)*m_jiange);
			
		}
		else
		{   
			CPen newPenrelate; 
			newPenrelate.CreatePen(PS_SOLID,1*m_penScale,RGB(255,0,255));
			memDC.SelectObject(&newPenrelate); 
			memDC.SetPixel(rect1.left+fw2*3/2+m_avesize*(i-m_startpoint+meter),
				dtop+fh-(dataafterfilter[i]-m_Middle)*m_jiange,RGB(255,0,255));
 			memDC.MoveTo(rect1.left+fw2*3/2+m_avesize*(i-m_startpoint+meter),
				dtop+fh-(dataafterfilter[i]-m_Middle)*m_jiange);
   			memDC.LineTo(rect1.left+fw2*3/2+m_avesize*(i-m_startpoint),
				dtop+fh-(dataafterfilter[i-10]-m_Middle)*m_jiange);
		}
	}



	////////////////////////////////// 计算分段处理：最大，最小值 ///

	int gridxnums=1;int gridynums=22;
	double dx= (rect1.right-dright)/gridxnums;
	double dy=rect1.Height()/gridynums;
	int meter2=rect1.Height()/70;
	double m3=dright+dx/2;


    double m_spiltavenum;
	m_spiltavenum=(m_endpoint-m_startpoint)/m_splitnumber;
  
	for (j=0;j<m_splitnumber;j++)
	{	
			m_maxsplit[j]=0;
			m_minsplit[j]=0;

		for (i=m_startpoint+j* m_spiltavenum+10; i< m_startpoint+(j+1)* m_spiltavenum-10;  i++)
		{
		
			if ( m_data[i].selected==0 )
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
		m_PVcstring.Format("%f",m_PV[i]);
		memDC.TextOut(m3+(rect1.right-m3)/2,dtop+dy*(10+i)+meter2,m_PVcstring);
	}
}

void CDoCircleRunOut::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rectFill;
    GetClientRect(rectFill);
    dc.FillSolidRect(rectFill,RGB(255,255,255));  //设置为白色背景 
	m_penScale=1;
	

	
	pWnd1 = GetDlgItem(IDC_STATIC_CircleRunOut);      // 获得对话框上的picture的窗口句柄
	pWnd1->GetClientRect(&rect1);             // 获取绘制坐标的文本框
	pDC = pWnd1->GetDC();                     // 获得对话框上的picture的设备指针
	pOldBmp = NULL;                           // 将旧的位图指针置空
	                                        
	memDC.CreateCompatibleDC(pDC);             // 创建内存绘图设备，使内存位图的DC与控件的DC关联
	memBitmap.CreateCompatibleBitmap(pDC,rect1.right,rect1.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap);
    memDC.FillSolidRect(rect1.left,rect1.top,rect1.right,rect1.bottom,RGB(255,255,255));//给矩形框填充白色

    double dY0= rect1.Height()/2,dleft=rect1.left,dtop=rect1.top,dright=rect1.right*3/5,dbottom=rect1.bottom,dX0=dright/2;
	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDC.SelectObject(&RectPen);               
	memDC.Rectangle(rect1.left,rect1.top,rect1.right,rect1.bottom); //静态框加上 颜色 边框
    RectPen.DeleteObject();

	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
		DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
	CFont*   pOldFont=(CFont*)memDC.SelectObject(&font); 

	if(m_BOOLSegmentprocess==0  &&  FlagFrequency==0 )
	{
		//手动去缺口普调试好
		if (m_bIsEnable==TRUE)//没有选择手动去缺口按钮时默认采用自动去缺口
		{
	     SubQKDataChuli(((CMainFrame*)AfxGetMainWnd())->m_fullPath,3600,FALSE,fpdata, Resdata,m_IndexStart,m_IndexEnd); //自动去除缺口处理
		}
		else//否则采用手动去缺口
		{
          SubQKDataChuli(((CMainFrame*)AfxGetMainWnd())->m_fullPath,3600,TRUE,fpdata, Resdata,m_IndexStart,m_IndexEnd); //自动去除缺口处理
		}
	
		if (CirEvalue==0)
		{
			DrawCircle();
			SubAnaData (FilterMode, Resdata,GResult,G1,G2);	//圆度
			dRONT=GResult[1];
			SubAnaData(1,  Resdata,GResult,G1,G2);    //1
			dEcc=GResult[1]/2;  //偏心
			dEccPos=GResult[3];  //偏心角
			
			m_strdRONT.Format("%.3f",dRONT); //将数据结果转换成字符串的形式，便于显示在表格中
			m_strdEcc.Format("%.3f",dEcc);
			m_strdEccPos.Format("%.3f",dEccPos);
			//显示波纹度
			m_Wa.Format("%.3f",m_BWD[0]); //将数据结果转换成字符串的形式，便于显示在表格中
			m_Wc.Format("%.3f",m_BWD[1]);
			m_Wp.Format("%.3f",m_BWD[2]);
			m_Wv.Format("%.3f",m_BWD[3]); //将数据结果转换成字符串的形式，便于显示在表格中
			m_Wt.Format("%.3f",m_BWD[4]);
			m_Wq.Format("%.3f",m_BWD[5]);
 		    m_Wwm.Format("%.3f",m_BWD[6]);
		}
		else if (CirEvalue==1)
		{
		  // DrawCircleMZC();
            DrawCircle();
			MZCyuandu();
		}        
    
		else if (CirEvalue==2)
		{
	     // DrawCircleMZC();
            DrawCircle();
			MCCyuandu();
		}    

		else if (CirEvalue==3)
		{
	//	  DrawCircleMZC();
            DrawCircle();
		 	MICyuandu();
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


	pDC->BitBlt(rect1.left,rect1.top,rect1.right,rect1.bottom,&memDC,0,0,SRCCOPY); //把已经绘好的图显示在制定位置上
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
    memBitmap.DeleteObject();//释放内存设备

}

void CDoCircleRunOut::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		if (m_BOOLSegmentprocess==0  && FlagFrequency==0 )
	{	
		CWnd *pWnd2;
		CDC  *pDC;                 // 控件的屏幕绘图设备指针
		pWnd2=GetDlgItem(IDC_STATIC_CircleRunOut);     //获取静态框的指针
		pDC=pWnd2->GetDC();
		CRect rect_ctr;
		this->ClientToScreen(&point);          //转换为屏幕坐标
		pWnd2->GetClientRect(&rect_ctr);       //获得文本框矩形,左上角坐标(0,0)   
		pWnd2->ClientToScreen(rect_ctr);       //转换到屏幕坐标,左上角坐标为文本框在屏幕的坐标
		
		point.x=point.x-rect_ctr.left;         //把point
		point.y=point.y-rect_ctr.top;
		double f1=(rect_ctr.right-rect_ctr.left)*3/5,f2= (rect_ctr.bottom-rect_ctr.top )/2;
	
		if( (point.x)<0 ||  (point.x>f1)	|| (point.y)>(rect_ctr.bottom-rect_ctr.top) || (point.y)<0)
			;
		else  
		{
       		m_bDraw=TRUE;             //准备好开始绘图
	    	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS ));
            flagmanchuli=1;	
		}
  		m_zancunfinish=m_zancunOrigin=m_ptOrigin=m_ptEnd=point;	//保存当前点
 
	}

    //////////////////////////////////////// 频谱鼠标响应显示

    if(m_BOOLSegmentprocess==0  && FlagFrequency==1 )
	{
		BoolButtondown=1;
		CWnd *pWnd2;
		CDC  *pDC;                             // 控件的屏幕绘图设备指针
		pWnd2=GetDlgItem(IDC_Deal_Circle);     //获取静态框的指针
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
	
		if( (point.x)<fw2 ||  (point.x>fw1-fw2*2+m_smallavescale)	|| (point.y)>rect_ctr.Height() || (point.y)<0 );
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

				  pDC->MoveTo(fw2+m_smallavescale*i+m_smallavescale/2,fh2*3); // X坐标线,横线
		          pDC->LineTo(fw2+m_smallavescale*i+m_smallavescale/2,f2-fh2*4);

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

void CDoCircleRunOut::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_BOOLSegmentprocess==0 && (MK_LBUTTON & nFlags))
	{	
		
		CWnd *pwnd=GetDlgItem(IDC_STATIC_CircleRunOut);//获取静态框的指针
		CDC *pDC=pwnd->GetDC();
		CRect rect_ctr;
		this->ClientToScreen(&point);  //转换为屏幕坐标
		pwnd->GetClientRect(rect_ctr);       //获得文本框矩形,左上角坐标(0,0)   
		pwnd->ClientToScreen(rect_ctr);       //转换到屏幕坐标,左上角坐标为文本框在屏幕的坐标
		
		point.x=point.x-rect_ctr.left;
		point.y=point.y-rect_ctr.top;
		
		double f1=(rect_ctr.right-rect_ctr.left)*3/5,f2= (rect_ctr.bottom-rect_ctr.top)/2; 
		double dw= 2 * 3.1415926/3600,theta3=0;
        double dY0= (rect_ctr.bottom-rect_ctr.top )/2, dleft=0,dtop=0,dright=(rect_ctr.right-rect_ctr.left)*3/5,dbottom=rect_ctr.bottom-rect_ctr.top,dX0=dright/2;
		if( (point.x)<0 || (point.x>f1)|| (point.y+rect_ctr.top)>(rect_ctr.bottom) || (point.y)<0)
			;
		else  
		{    flagmanchuli=1;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS ));
		int nDrawmode=pDC->SetROP2(R2_NOT); //设置异或绘图模式，并保存原来绘图模式 
		//----------------构造动态圆环--------------------
		{	       
			//擦除上次绘制的圆环线
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
			
			theta3=atan2(point.y-dY0,point.x-dX0);       //计算鼠标按下theta1和抬起时的角度theta2
			if (theta3<0)
			{
				theta3=2*3.141592+theta3;
			}
			if (fabs(theta3-theta2)>=3*PI/2)             //注意放了10个点的间隔中间有20个点的区域
			{
				Flagxzhou=1;
			}	
			else 
				Flagxzhou=0;
			if (Flagxzhou==1)
				FlagMove+=1;
			//----------------画出新的临时圆环线---------------------------//
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
			OnPaint(); //动态绘制
		}
		m_zancunfinish=point;   //记录鼠标弹起时的点，以备再次绘图时用
		pDC->SetROP2(nDrawmode); //恢复原绘图模式 	 
		ReleaseDC(pDC); //释放设备环境 
		////////////////////////////////////////////////////////////
		}
  }
	CFormView::OnMouseMove(nFlags, point);
}

void CDoCircleRunOut::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	flagmanchuli=0;  
	if(m_BOOLSegmentprocess==0 && FlagFrequency==0)
	{
		CWnd *pWnd1=GetDlgItem(IDC_STATIC_CircleRunOut);  
		CDC  *pDC=pWnd1->GetDC();               // 控件的屏幕绘图设备指针                       //获取静态框的指针
		pWnd1->GetClientRect(&rect_ctr);                             // 获取绘制坐标的文本框 
		
		CWnd *pnd=GetDlgItem(IDC_STATIC_CircleRunOut);                       //获取静态框的指针
		CDC *DC=pnd->GetDC();
		pnd->GetClientRect(&rect1);                                   // 获取绘制坐标的文本框 
		
		this->ClientToScreen(&point);                                 //转换为屏幕坐标
		pWnd1->GetClientRect(rect_ctr);                               //获得文本框矩形,左上角坐标(0,0)   
		pWnd1->ClientToScreen(rect_ctr);                              //转换到屏幕坐标,左上角坐标为文本框在屏幕的坐标
		
		point.x=point.x-rect_ctr.left;
		point.y=point.y-rect_ctr.top;                                 //实现point相对于静态框坐标的坐标
		
		double dY0= (rect_ctr.bottom-rect_ctr.top )/2, dleft=0,dtop=0,dright=(rect_ctr.right-rect_ctr.left)*3/5,dbottom=rect_ctr.bottom-rect_ctr.top,dX0=dright/2;
		double theta1=0,theta2=0,dw=0;
		int m_IndexStart=0,m_IndexEnd=0,i=0;
		dw= 2 * 3.1415926/3600;// 每一次采样对应的角度间隔，弧度
		if( (point.x)<0 || (point.x>dright)|| (point.y)>(rect_ctr.bottom-rect_ctr.top) || (point.y)<0)
			;
		else	
		{                                        //此时鼠标弹起不响应绘图
			m_zancunfinish=point;   //记录鼠标弹起时的点，以备再次绘图时用
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
				ChangeValueOfSelect(((CMainFrame*)AfxGetMainWnd())->m_fullPath,m_IndexStart, m_IndexEnd,1);
			}
			else 
			{
				
				if ( 6.2814-theta2>6.2814-theta1)
				{
					ChangeValueOfSelect(((CMainFrame*)AfxGetMainWnd())->m_fullPath,m_IndexStart,3599,1);
					ChangeValueOfSelect(((CMainFrame*)AfxGetMainWnd())->m_fullPath,0,m_IndexEnd,1);
				}
				else if ( 6.2814-theta1>6.2814-theta2)
				{
					ChangeValueOfSelect(((CMainFrame*)AfxGetMainWnd())->m_fullPath,m_IndexStart,0,1);
					ChangeValueOfSelect(((CMainFrame*)AfxGetMainWnd())->m_fullPath,3599,m_IndexEnd,1);
				}
				
			}
			
			
		}   
		
		flagmanchuli=0;
		FlagMove=0;
		CFormView::OnLButtonUp(nFlags, point);
	}
   OnPaint();
}
void CDoCircleRunOut::ChangeValueOfSelect(CString path,int startPosition, int endPosition, BOOL isSelected)
{
	shuju ChangeDate[3600];
	std::ifstream fin(path, std::ios::binary);
	int i;
	
	if (endPosition>startPosition)                       //顺势针旋转
	{	
		for (i=0;i<3600;i++)
		{
			fin.read((char*)&ChangeDate[i],sizeof(shuju));
		}
		fin.read((char*)&G1,sizeof(double));
		fin.read((char*)&G2,sizeof(double));
		fin.read((char*)&m_time,sizeof(CTime));
		fin.close();
		
		std::ofstream fout(path, std::ios::binary);
		for (i=0;i<3600;i++)
		{
			if ((i<=endPosition)&&(i>=startPosition))
			{
				ChangeDate[i].selected=isSelected;
			}
			fout.write((char*)&ChangeDate[i], sizeof(shuju));
		}
		fout.write((char*)&G1,sizeof(double));
		fout.write((char*)&G2,sizeof(double));
		fout.write((char*)&m_time,sizeof(CTime));
		fout.close();
	}
	else  //逆时针正常旋转
	{
		for (i=0;i<3600;i++)
		{
			fin.read((char*)&ChangeDate[i],sizeof(shuju));
		}
		fin.read((char*)&G1,sizeof(double));
		fin.read((char*)&G2,sizeof(double));
		fin.read((char*)&m_time,sizeof(CTime));
		fin.close();
		
		std::ofstream fout(path, std::ios::binary);
		for (i=0;i<3600;i++)
		{
			
			if ((i>=endPosition)&&(i<=startPosition))
			{
				ChangeDate[i].selected=isSelected;
			}
			
			fout.write((char*)&ChangeDate[i], sizeof(shuju));
		}
		fout.write((char*)&G1,sizeof(double));
		fout.write((char*)&G2,sizeof(double));
		fout.write((char*)&m_time,sizeof(CTime));
		fout.close();
	}	
}

void CDoCircleRunOut::DynamicDrawCircle( int startPosition, int endPosition)
{
	
	//定义后面将要用到的变量
	double dY0= rect1.Height()/2,dright=rect1.right*3/5,dX0=dright/2;

	//rin为0圆，RSLC为2018圆，rout为4096圆
	int x1,y1,x2,y2,i;
	double rout=rect1.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	dw= 2 * 3.1415926/3600;// 每一次采样对应的角度间隔，弧度nTriangle.DeleteObject();

	CPen ping1(PS_SOLID,2,RGB(250,200,238));   //绘制圆环变色带 
	memDC.SelectObject(&ping1); 

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
					memDC.MoveTo(x1,y1);
					memDC.LineTo(x2,y2);
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
			memDC.MoveTo(x1,y1);
			memDC.LineTo(x2,y2);
		}
	}
 }	

   ping1.DeleteObject();
}

void CDoCircleRunOut::DrawingCleanAndReset(CString path, BOOL isSelected)
{
	shuju ChangeDate[3600];
	std::ifstream fin(path, std::ios::binary);
	int i;
	for (i=0;i<3600;i++)
	{
		fin.read((char*)&ChangeDate[i],sizeof(shuju));
	}
	fin.read((char*)&G1,sizeof(double));
	fin.read((char*)&G2,sizeof(double));
	fin.read((char*)&m_time,sizeof(CTime));
	fin.close();
	
	std::ofstream fout(path, std::ios::binary);
	for (i=0;i<3600;i++)
	{		
		ChangeDate[i].selected=isSelected;	
		fout.write((char*)&ChangeDate[i], sizeof(shuju));
	}
	fout.write((char*)&G1,sizeof(double));
	fout.write((char*)&G2,sizeof(double));
	fout.write((char*)&m_time,sizeof(CTime));
	fout.close();
}

HBRUSH CDoCircleRunOut::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{

	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);	
	// TODO: Change any attributes of the DC here
	return m_brush;  //返回白色刷子
}
/*函数功能：
 ---- 根据选择的率波段实现圆度信息的计算
 ---- 选择对应的波段的滤波函数
*/
void CDoCircleRunOut::SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr)
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
函数功能：
滤波断的选择，进行滤波
*/
void CDoCircleRunOut:: WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata)
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

void CDoCircleRunOut::DrawFilter (int  FilterMode ,double *pMem,double *drawdata)
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

void CDoCircleRunOut::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
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
		}
	}
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CDoCircleRunOut::DrawGride1()
{
	double dY0= rect1.top+rect1.Height()/2,dleft=rect1.left,dtop=rect1.top,dright=rect1.left+rect1.Width()*3/5,
		dbottom=rect1.bottom,dX0=dleft+(dright-dleft)/2;
	int gridxnums=1;int gridynums=22;
	double dx= (rect1.right-dright)/gridxnums;
	double dy=rect1.Height()/gridynums;
    CRect gridRect(rect1.left,rect1.top,rect1.left+dx*gridxnums,rect1.top+dy*gridynums);
	CPen gridPen(0,1*m_penScale,RGB(0,0,20)); //网格线的颜色
	memDC.FillSolidRect(dright+dx,dtop+dy*12,dx,dy,RGB(139,216,224));//给指定格子填充颜色
    CPen *oldpen=memDC.SelectObject(&gridPen);
	memDC.SetBkMode(TRANSPARENT); 

	int m1=dright+dx/30;	
	double m2=dright+(rect1.right-dright)/3;
	double m3=dright+(rect1.right-dright)*2/3;
	double mid=dright+(rect1.right-dright)/3;
	int meter=rect1.Height()/70;

	if (FlagBogao==0)
	{
		//------------------------------------------------------------
		memDC.FillSolidRect(dright,dtop+0,gridRect.right-1,dy,RGB(232,232,232));//给头行填充颜色
		memDC.FillSolidRect(dright,dtop+dy*5,gridRect.right-1,dy,RGB(232,232,232));//给指定行填充颜色
		memDC.FillSolidRect(dright,dtop+dy*12,gridRect.right-1,dy,RGB(232,232,232));//给指定行填充颜色
		
		//将圆度计算的结果信息显示在表格对应的位置上，此处显示信息有：圆度、偏心、偏心角
	 
		memDC.FillSolidRect(dright,dtop+dy*6,gridRect.right-1,dy,RGB(255,255,255));
		memDC.TextOut(m2,dtop+dy*6+meter,m_strMethod);
		memDC.TextOut(m2,dtop+dy*7+meter,"Gaussian");
		memDC.TextOut(m2,dtop+dy*8+meter,m_strlvbo);		
		memDC.TextOut(mid ,dtop+meter,"圆度测量结果");
		memDC.TextOut(mid,dtop+dy*5+meter," 评定参数 ");
		memDC.TextOut(mid,dtop+dy*12+meter," 测量参数 ");
		memDC.TextOut(m1,dtop+dy+meter,"文件名");
		memDC.TextOut(m1,dtop+dy*2+meter,"测量时间");  
		memDC.TextOut(m1,dtop+dy*6+meter,"评定方法");
		memDC.TextOut(m1,dtop+dy*7+meter,"滤波器种类");                                              
		memDC.TextOut(m1,dtop+dy*8+meter,"滤波范围");  		
		memDC.TextOut(m1,dtop+dy*13+meter,"工艺要求");
		memDC.TextOut(m1,dtop+dy*14+meter,"圆度");
		memDC.TextOut(m1,dtop+dy*15+meter,"偏心");
		memDC.TextOut(m1,dtop+dy*16+meter,"偏心角度");                                                                                   
		CString str;
		str=((CMainFrame*)AfxGetMainWnd())->m_fullPath;
		int num=str.ReverseFind('\\');
		str=str.Right(str.GetLength()-num-1);
		memDC.TextOut(m2,dtop+dy*1+meter,str);
		//显示测量时间
		str=m_time.Format("%Y-%m-%d %H:%M");
		memDC.TextOut(m2,dtop+dy*2+meter,str);
		str.Format("%.3f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[0]);
		memDC.TextOut(m2,dtop+dy*13+meter,str);
		memDC.TextOut(m3,dtop+dy*13+meter,"  um");
		memDC.TextOut(m3,dtop+dy*14+meter,"  um");
		memDC.TextOut(m3,dtop+dy*15+meter,"  um");
		memDC.TextOut(m3,dtop+dy*16+meter,"  °");

		if (CirEvalue==0) //最小二乘法
		{
	  	   memDC.TextOut(m2,dtop+dy*14+meter,m_strdRONT);//报表中显示最小二乘法计算结果
		   memDC.TextOut(m2,dtop+dy*15+meter,m_strdEcc);
		   memDC.TextOut(m2,dtop+dy*16+meter,m_strdEccPos);
		}

		else if (CirEvalue==1)//最小区域法
		{	   
			memDC.TextOut(m2,dtop+dy*14+meter,m_MZCRONT);
            memDC.TextOut(m2,dtop+dy*15+meter,m_strdEcc);//报表中显示最小区域法计算结果
            memDC.TextOut(m2,dtop+dy*16+meter,m_strdEccPos);
		}

		else if (CirEvalue==2)//
		{
			//最小外接法评定圆度误差
			memDC.TextOut(m2,dtop+dy*14+meter,m_MCCRONT);
            memDC.TextOut(m2,dtop+dy*15+meter,m_strdEcc);//报表中显示最小区域法计算结果
            memDC.TextOut(m2,dtop+dy*16+meter,m_strdEccPos);
		}

		else if (CirEvalue==3)
		{
			//最大内切法评定圆度误差
			memDC.TextOut(m2,dtop+dy*14+meter,m_MICRONT);
            memDC.TextOut(m2,dtop+dy*15+meter,m_strdEcc);//报表中显示最小区域法计算结果
            memDC.TextOut(m2,dtop+dy*16+meter,m_strdEccPos);
		}



		if (FilterMode==8 || FilterMode==9)
		{
			//显示波纹度
			memDC.TextOut(mid,dtop+dy*17+meter,"波纹度");
			memDC.TextOut(m1,dtop+dy*18+meter,"Wa");
			memDC.TextOut(m1,dtop+dy*19+meter,"Wc");
			memDC.TextOut(m1,dtop+dy*20+meter,"Wp");
			memDC.TextOut(m1,dtop+dy*21+meter,"Wv");
			memDC.TextOut(m1,dtop+dy*22+meter,"Wt");
			memDC.TextOut(m1,dtop+dy*23+meter,"Wq");
			memDC.TextOut(m1,dtop+dy*24+meter,"Wwm");
						
			memDC.TextOut(m2,dtop+dy*18+meter,m_Wa);
			memDC.TextOut(m2,dtop+dy*19+meter,m_Wc);
			memDC.TextOut(m2,dtop+dy*20+meter,m_Wp);
			memDC.TextOut(m2,dtop+dy*21+meter,m_Wv);
			memDC.TextOut(m2,dtop+dy*22+meter,m_Wt);
			memDC.TextOut(m2,dtop+dy*23+meter,m_Wq);
	        memDC.TextOut(m2,dtop+dy*24+meter,m_Wwm);

			memDC.TextOut(m3,dtop+dy*18+meter,"um");
			memDC.TextOut(m3,dtop+dy*19+meter,"um");
			memDC.TextOut(m3,dtop+dy*20+meter,"um");
			memDC.TextOut(m3,dtop+dy*21+meter,"um");
			memDC.TextOut(m3,dtop+dy*22+meter,"um");
			memDC.TextOut(m3,dtop+dy*23+meter,"um");
	        memDC.TextOut(m3,dtop+dy*24+meter,"um");
		}
		
		//------------------------------------------------------------
		for(int m=0;m<=gridxnums;m++) //画出gridxnums条竖线                      
		{
			memDC.MoveTo(dright+m*dx,gridRect.bottom);
			memDC.LineTo(dright+m*dx,gridRect.top);
		}
			
		for(int n=0;n<=gridynums-1;n++) //画出gridynums条横线                        
		{
			memDC.MoveTo(dright,dtop+n*dy);
			memDC.LineTo(rect1.right,dtop+n*dy);
		}  
 		memDC.MoveTo(dright,dtop);
 		memDC.LineTo(dright,dbottom);
	}
	///////////////////////////////////////////////////////////波高数据显示
	if (FlagBogao==1)
	{
		memDC.FillSolidRect(dright,dtop,gridRect.Width(),dy,RGB(232,232,232));//给头行填充颜色

		memDC.MoveTo(dright,dtop+dy);
		memDC.LineTo(rect1.left+rect1.Width(),dtop+dy);

		memDC.MoveTo(rect1.right,rect1.top);
		memDC.LineTo(rect1.right,rect1.bottom);
		memDC.MoveTo(dright,dtop);
		memDC.LineTo(dright,dbottom);
		memDC.MoveTo(dright,rect1.top);
		memDC.LineTo(rect1.right,rect1.top);
       
		CString bogaostr;
		CString weizhistr;
		CString bianhaostr;
		
		//显示内容
		memDC.TextOut(dright+rect1.Width()/10,dtop+meter,"波高分析结果(左：um,右：°)");
		double dygridnum=rect1.Height()*5/6/35;
		int meterbaogao=12;
		for (int i=1;i<=DispTempFnumber;i++)
		{
			
			if (i<=35)
			{
				if (i<10)
				{
					bianhaostr.Format("%d",i);
					bogaostr.Format("%.3f",bogao[i]);
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
					bogaostr.Format("%.3f",bogao[i]);
					if (bogaostr=="0.000")
					{
						bogaostr="0";
					}
					bogaostr=bogaostr+"-";
					bogaostr=bianhaostr+" "+bogaostr;
					weizhistr.Format("%.1f",weizhi[i]);
					bogaostr=bogaostr+weizhistr;
				}

				memDC.TextOut(m1,dtop+dygridnum*(i+1)+meterbaogao,bogaostr);
			}

			if (i>35  && i<=70)
			{
				bianhaostr.Format("%d",i);
				bogaostr.Format("%.3f",bogao[i]);
				if (bogaostr=="0.000")
				{
					bogaostr="0";
				}
				bogaostr=bogaostr+"-";
				bogaostr=bianhaostr+" "+bogaostr;
				weizhistr.Format("%.1f",weizhi[i]);
				bogaostr=bogaostr+weizhistr;
				memDC.TextOut(m2,dtop+dygridnum*(i-35+1)+meterbaogao,bogaostr);
			}
			if (i>70  && i<=100)
			{
				bianhaostr.Format("%d",i);
				bogaostr.Format("%.3f",bogao[i]);
				if (bogaostr=="0.000")
				{
					bogaostr="0";
				}
				bogaostr=bogaostr+"-";
				bogaostr=bianhaostr+" "+bogaostr; 
				weizhistr.Format("%.1f",weizhi[i]);
				bogaostr=bogaostr+weizhistr;
				memDC.TextOut(m3,dtop+dygridnum*(i-70+1)+meterbaogao,bogaostr);
			}
		}
	}
}

void CDoCircleRunOut::DrawGrid2()
{
	double dY0= rect1.top+rect1.Height()/2,dleft=rect1.left,dtop=rect1.top,dright=rect1.left+rect1.Width()*3/5,
		dbottom=rect1.bottom,dX0=dleft+(dright-dleft)/2;
	int gridxnums=1;int gridynums=22;
	double dx= (rect1.right-dright)/gridxnums;
	double dy=rect1.Height()/gridynums;
    CRect gridRect(rect1.left,rect1.top,rect1.left+dx*gridxnums,rect1.top+dy*gridynums);

	CPen gridPen(0,1*m_penScale,RGB(0,0,20)); //网格线的颜色
	memDC.FillSolidRect(dright+dx,dtop+dy*12,dx,dy,RGB(139,216,224));//给指定格子填充颜色
    CPen *oldpen=memDC.SelectObject(&gridPen);	
    //------------------------------------------------------------
	memDC.FillSolidRect(dright,dtop+0,gridRect.Width(),dy,RGB(232,232,232));//给头行填充颜色
	memDC.FillSolidRect(dright,dtop+dy*5,gridRect.Width(),dy,RGB(232,232,232));//给指定行填充颜色
	memDC.FillSolidRect(dright,dtop+dy*9,gridRect.Width(),dy,RGB(232,232,232));//给指定行填充颜色
	memDC.SetBkMode(TRANSPARENT); 

	int m1=dright+dx/30;	
	double m2=dright+(rect1.right-dright)/3;
	double m3=dright+(rect1.right-dright)*2/3;
	double mid=dright+(rect1.right-dright)/3;
	int meter=rect1.Height()/70;

	int m_endstart=m_endposition-m_startposition;
	double m_splitmark=m_endstart/m_splitnumber;
	
	memDC.FillSolidRect(dright,dtop+dy*6,gridRect.right-1,dy,RGB(255,255,255));
	memDC.TextOut(m2,dtop+dy*6+meter,m_strMethod);
 	memDC.TextOut(m2,dtop+dy*7+meter,"Gaussian");
	memDC.TextOut(m2,dtop+dy*8+meter,m_strlvbo);
	memDC.TextOut(mid,dtop+meter,"圆度测量结果");
	memDC.TextOut(mid,dtop+dy*5+meter," 评定参数");
	memDC.TextOut(m2,dtop+dy*9+meter,"分段圆度评定(左:°右:um)");
    memDC.TextOut(m1,dtop+dy+meter,"文件名");
	memDC.TextOut(m1,dtop+dy*2+meter,"测量时间");
	memDC.TextOut(m1,dtop+dy*6+meter,"评定方法");                                       
	memDC.TextOut(m1,dtop+dy*7+meter,"滤波器种类");                                              
	memDC.TextOut(m1,dtop+dy*8+meter,"滤波范围");   
                                                
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDC.TextOut(m2,dtop+dy*1+meter,str);
	//显示测量时间
	str=m_time.Format("%Y-%m-%d %H:%M");
	memDC.TextOut(m2,dtop+dy*2+meter,str);
	int i;
	CString strsplit;
	for (i=0;i<m_splitnumber;i++)
	{
		strsplit.Format("%d",i+1);
		strsplit="第"+strsplit+"段范围:";
		memDC.TextOut(m1,dtop+dy*(10+i)+meter,strsplit);
		memDC.TextOut(m3-10,dtop+dy*(10+i)+meter,"P+V=");
	}
	
	CString strstart;
	CString strend;
	CString strstartend;
	for(i=0;i<m_splitnumber;i++)   //报表显示每段范围
	{
		strstart.Format("%.1f",m_splitmark*i+m_startposition);
		strend.Format("%.1f",m_splitmark*(i+1)+m_startposition);	
		strstartend=strstart+"-"+strend;
		memDC.TextOut(m2,dtop+dy*(10+i)+meter,strstartend);	
	}
	
		
	for(int m=0;m<=gridxnums;m++) //画出gridxnums条竖线                      
	{
		memDC.MoveTo(dright+m*dx,gridRect.bottom);
		memDC.LineTo(dright+m*dx,gridRect.top);
	}
			
	for(int n=0;n<=gridynums-1;n++) //画出gridynums条横线                        
	{
		memDC.MoveTo(dright,dtop+n*dy);
		memDC.LineTo(rect1.right,dtop+n*dy);
	}  
 	memDC.MoveTo(dright,dtop);
	memDC.LineTo(dright,dbottom);
	
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
  void CDoCircleRunOut::SubQKDataChuli(CString path,int Number, BOOL AutoOrManChuli, double *Soudata, double *Resdata,int m_IndexStart, int m_IndexEnd)
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
	///////////////手工剔除//////////////////////////////
    // if( Number==0) 
    //	Exit Sub;

    //	将文件名传过来，进行缺口个数的统计
	shuju ManDeal[3600];//定时结构体数据
	std::ifstream fin(path,std::ios::binary);
	for (i=0;i<Number;i++)
	{	
		fin.read((char*)&ManDeal[i], sizeof(shuju));
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
       ChangeValueOfSelect(path,Starti,Endi,1);
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

void CDoCircleRunOut::DrawFrequency()
{
	////读取文件并绘图///
	int m_Intendstart=m_Intend-m_Intstart;
	ReadDataFromFile();
    
    //滤波函数
 	double TsQ[3600],TsH[3600];
	int  j=0; int i=0;

	for( i = 0;i< 3600 ;i++)
	{
       TsQ[i] = ((fpdata[i] - 2048) * 10) / (G1*G2 * 4096);
	}
	DrawFilter (FilterMode,TsQ,TsH);//调用滤波函数，为后续的滤波后数据的显示

	double XR[3601],Xi[3601];
	int GDN=3600;
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
	  for (i=1;i<3600;i++)
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
	double XRf[3601], Xif[3601],XRfr[3601];
	XRf[0]=0;
	Xif[0]=0;
	int ks;
	int d;
	for (i=1;i<3601;i++)
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

	double fw1=3*rect1.Width()/5,f1=rect1.Width(),f2=rect1.Height();                                                 	                             
    double fw2=rect1.Width()/30;
    double fh=rect1.Height()/2;
	double fh1=rect1.Height()/4;
	double fh2=rect1.Height()/30;
	CString mark;
	double m_avescale=((fw1-fw2*3)/m_Intendstart)*5;
	double m_smallavescale=(fw1-fw2*3)/m_Intendstart;
    double m_startmark=fw2+m_smallavescale/2;

	CPen newPen;         
	newPen.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDC.SelectObject(&newPen); 

	memDC.MoveTo(rect1.left+fw1-fw2*2+m_smallavescale,rect1.top+f2-fh2*4); // X坐标线,横线
    memDC.LineTo(rect1.left+fw2,rect1.top+f2-fh2*4); 

	memDC.MoveTo(rect1.left+fw2,rect1.top+fh2*4);    //左边竖线
    memDC.LineTo(rect1.left+fw2,rect1.top+f2-fh2*4); 


	for(i=0;i<=m_Intendstart;i++)    //写X轴小刻度值
	{
		memDC.MoveTo(rect1.left+m_startmark+m_smallavescale*i,rect1.top+f2-fh2*4+2);
		memDC.LineTo(rect1.left+m_startmark+m_smallavescale*i,rect1.top+f2-fh2*4-2);
	}
    CPen newPen2;         
	newPen2.CreatePen(PS_SOLID,2*m_penScale,RGB(0,0,0));
    memDC.SelectObject(&newPen2); 
	for(i=0;i<=m_Intendstart/5;i++)    //写X轴大刻度值
	{
		memDC.MoveTo(rect1.left+m_startmark+m_avescale*i,rect1.top+f2-fh2*4+4);
		memDC.LineTo(rect1.left+m_startmark+m_avescale*i,rect1.top+f2-fh2*4-4);
		
	}
	
 	double m_freave=(f2-fh2*4*2)/(m_pmax-m_pmin);
    CPen PenXX;
	PenXX.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDC.SelectObject(&PenXX); 

	for (i=0;i<=m_Intendstart;i++)               //每个点对应高度，横线
	{
		memDC.MoveTo(rect1.left+fw2+m_smallavescale*i,
			rect1.top+f2-fh2*4-(m_freave*(dataafterfilter[i+m_Intstart]-m_pmin)));
		memDC.LineTo(rect1.left+fw2+m_smallavescale*(i+1),
			rect1.top+f2-fh2*4-(m_freave*(dataafterfilter[i+m_Intstart]-m_pmin)));
	}

	CPen PenXXX;
	PenXXX.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDC.SelectObject(&PenXXX); 

	for (i=0;i<=m_Intendstart;i++)     //竖线
	{
	
		memDC.MoveTo(rect1.left+fw2+m_smallavescale*(i+1),
			rect1.top+f2-fh2*4-(m_freave*(dataafterfilter[i+m_Intstart]-m_pmin)));
		memDC.LineTo(rect1.left+fw2+m_smallavescale*(i+1),
			rect1.top+f2-fh2*4-(m_freave*(dataafterfilter[i+1+m_Intstart]-m_pmin)));
	}

    memDC.MoveTo(rect1.left+fw2+m_smallavescale*(m_Intendstart+1),
		rect1.top+f2-fh2*4-(m_freave*(dataafterfilter[m_Intendstart+1+m_Intstart]-m_pmin)));
	memDC.LineTo(rect1.left+fw2+m_smallavescale*(m_Intendstart+1),
		rect1.top+f2-fh2*4);

	if (BoolButtondown==0)
	{
		Frepointi=0;
		Frepointx=0;
		Frepointy=0;
	}

	//----------数据写入字体及大小
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
        memDC.TextOut(rect1.left+10*m_penScale,rect1.top+10*m_penScale,str1);
		

		CPen newPenp;         
		newPenp.CreatePen(PS_SOLID,1*m_penScale,RGB(255,0,255));
		memDC.SelectObject(&newPenp); 

		memDC.MoveTo(rect1.left+fw2+m_smallavescale*Frepointi+m_smallavescale/2,rect1.top+fh2*3); // X坐标线,横线
		memDC.LineTo(rect1.left+fw2+m_smallavescale*Frepointi+m_smallavescale/2,rect1.top+f2-fh2*4);
		
	}

}

void CDoCircleRunOut::DrawGrid3Frequency()
{
	double dY0= rect1.top+rect1.Height()/2,dleft=rect1.left,dtop=rect1.top,dright=rect1.left+rect1.Width()*3/5,
		dbottom=rect1.bottom,dX0=dleft+(dright-dleft)/2;
	int gridxnums=1;int gridynums=22;
	double dx= (rect1.right-dright)/gridxnums;
	double dy=rect1.Height()/gridynums;
    CRect gridRect(rect1.left,rect1.top,rect1.left+dx*gridxnums,rect1.top+dy*gridynums);
	CPen gridPen(0,1*m_penScale,RGB(0,0,20)); //网格线的颜色
	memDC.FillSolidRect(dright+dx,dtop+dy*12,dx,dy,RGB(139,216,224));//给指定格子填充颜色
    CPen *oldpen=memDC.SelectObject(&gridPen);

	
    //------------------------------------------------------------
	memDC.FillSolidRect(dright,dtop+0,gridRect.right-1,dy,RGB(232,232,232));//给头行填充颜色
	memDC.FillSolidRect(dright,dtop+dy*5,gridRect.right-1,dy,RGB(232,232,232));//给指定行填充颜色
	memDC.FillSolidRect(dright,dtop+dy*12,gridRect.right-1,dy,RGB(232,232,232));//给指定行填充颜色
	memDC.SetBkMode(TRANSPARENT); 

	int m1=dright+dx/30;	
	double m2=dright+(rect1.right-dright)/3;
	double m3=dright+(rect1.right-dright)*2/3;
	double mid=dright+(rect1.right-dright)/3;
	int meter=rect1.Height()/70;
	//将圆度计算的结果信息显示在表格对应的位置上，此处显示信息有：圆度、偏心、偏心角
	
	memDC.FillSolidRect(dright,dy*6,gridRect.right-1,dy,RGB(255,255,255)); 	
	memDC.TextOut(m2,dtop+dy*6+meter,m_strMethod); 	
	memDC.TextOut(m2,dtop+dy*7+meter,"Gaussian");
	memDC.TextOut(m2,dtop+dy*8+meter,m_strlvbo);
	memDC.TextOut(mid ,dtop+meter,"圆度测量结果");
	memDC.TextOut(mid,dtop+dy*5+meter," 评定参数");
	memDC.TextOut(mid,dtop+dy*12+meter," 测量参数");
	
    memDC.TextOut(m1,dtop+dy+meter,"文件名");
	memDC.TextOut(m1,dtop+dy*2+meter,"测量时间");
	memDC.TextOut(m1,dtop+dy*6+meter,"评定方法");                                       
	memDC.TextOut(m1,dtop+dy*7+meter,"滤波器种类");                                              
	memDC.TextOut(m1,dtop+dy*8+meter,"滤波范围");    
	memDC.TextOut(m1,dtop+dy*13+meter,"工艺要求");
	memDC.TextOut(m1,dtop+dy*14+meter,"圆度");
	memDC.TextOut(m1,dtop+dy*15+meter,"偏心");
	memDC.TextOut(m1,dtop+dy*16+meter,"偏心角度");  
	memDC.TextOut(m2,dtop+dy*14+meter,m_strdRONT);
	memDC.TextOut(m2,dtop+dy*15+meter,m_strdEcc);
	memDC.TextOut(m2,dtop+dy*16+meter,m_strdEccPos);
	memDC.TextOut(m3,dtop+dy*13+meter,"  um");
	memDC.TextOut(m3,dtop+dy*14+meter,"  um");
	memDC.TextOut(m3,dtop+dy*15+meter,"  um");
	memDC.TextOut(m3,dtop+dy*16+meter,"  °");
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDC.TextOut(m2,dtop+dy*1+meter,str);
	//显示测量时间
	str=m_time.Format("%Y-%m-%d %H:%M");
	memDC.TextOut(m2,dtop+dy*2+meter,str);
	str.Format("%.3f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[0]);
	memDC.TextOut(m2,dtop+dy*13+meter,str);

	for(int m=0;m<=gridxnums;m++) //画出gridxnums条竖线                      
	{
		memDC.MoveTo(dright+m*dx,gridRect.bottom);
		memDC.LineTo(dright+m*dx,gridRect.top);
	}
			
	for(int n=0;n<=gridynums-1;n++) //画出gridynums条横线                        
	{
		memDC.MoveTo(dright,dtop+n*dy);
		memDC.LineTo(rect1.right,dtop+n*dy);
	}  
 	memDC.MoveTo(dright,dtop);
	memDC.LineTo(dright,dbottom);
		
}

void CDoCircleRunOut::DrawBaogao()
{
	////读取文件并绘图///
	double DispAdata[3600];
    ReadDataFromFile();
    //滤波函数
 	double TsQ[3600],TsH[3600];
	int  j=0; 
	int i=0;

	for( i = 0;i< 3600 ;i++)
	{
       fpdata[i] = ((fpdata[i] - 2048) * 10) / (16*0.121732414074473 * 4096);
       TsQ[i] = fpdata[i];
	}
	DrawFilter (FilterMode,fpdata,TsH);//调用滤波函数，为后续的滤波后数据的显示
	for (i=0;i<3600;i++)
	{
		DispAdata[i]=TsH[i];
	}
  

    int X1,TempStartWZ;int TempCount;double Swi[3600];//波纹度轮廓不平度间距
	int X,Y;
	int M;
	int WZIndex[3600];//与中线相交的点的位置
	BOOL FLAGIndex[3600];//与中线相交的点的趋势
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
	int DaNumberA=3600;
	int ZeroNumber=0;
    //  1---查找与中线相交的点
	EndFlag = FALSE;

    for (i=0;i<3601;i++)
    {
		FLAGIndex[i]=FALSE;
		WZIndex[i]=0;
		Swi[i]=0;
    }

	for (i=0;i<3600;i++)
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
	for (i=1; i<ZeroNumber; i++)
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
				for (j = X;j<DaNumberA;j++)
				{
					if (  DispAdata[j]>TempF )
					{
						TempF = DispAdata[j];
                        TempFHave = TRUE;
                        M = j;
					}
				}

				for (j=0;j<Y;j++)
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
   
   for (i=0; i<3600; i++)
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

void CDoCircleRunOut::OnBtndisable() 
{
	// TODO: Add your command handler code here
	
}

void CDoCircleRunOut::OnBtnenable() 
{
	// TODO: Add your command handler code here
	// TODO: Add your control notification handler code here
	if (FlagFrequency==0)
	{	
		if (m_BOOLSegmentprocess==0  && FlagFrequency==0 && m_bIsEnable==1 )
		{
			
			GetDlgItem(IDC_Deal_Circle)->EnableWindow(false); //使窗口开始响应鼠标消息
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,TRUE);
			
		}
		else  
			if(m_BOOLSegmentprocess==0  && FlagFrequency==0 && m_bIsEnable==0 )
			{
				GetDlgItem(IDC_Deal_Circle)->EnableWindow(true); //使窗口开始响应鼠标消息
				((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,FALSE);
				
			}
			m_bIsEnable=!m_bIsEnable;
	}

}

void CDoCircleRunOut::OnBtnfenduanchuli() 
{
	// TODO: Add your command handler code here
	if(m_BOOLSegmentprocess==0 || FlagFrequency==1  ||FlagBogao==1)
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
            BoolButtondown=0;
			OnPaint();
		}
		else
		{
			m_BOOLSegmentprocess=0;
		}
		
	}	
}

void CDoCircleRunOut::OnBtnppfx() 
{
	// TODO: Add your command handler code here
    CDlgfrequency1  dlg;
	CString strTemp;
	if (IDOK==dlg.DoModal())
	{
		m_Intstart=dlg.m_Intstart;
		m_Intend=dlg.m_Intend;
		FlagFrequency=1;	
		GetDlgItem(IDC_Deal_Circle)->EnableWindow(FALSE);
  		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(-1,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(7,FALSE);
		OnPaint();
	}
}

void CDoCircleRunOut::OnBtnresetdeal() 
{
	// TODO: Add your command handler code here
	// TODO: Add your control notification handler code here
	DrawingCleanAndReset(((CMainFrame*)AfxGetMainWnd())->m_fullPath,0);
    flagmanchuli=0;
	OnPaint();
}

void CDoCircleRunOut::OnBtnyuanduchuli() 
{
	if (m_BOOLSegmentprocess==1|| FlagFrequency==1 ||FlagBogao==1)
	{
		m_BOOLSegmentprocess=0; 
		FlagFrequency=0;

		if (FlagFrequency==0)
		{			
			GetDlgItem(IDC_Deal_Circle)->EnableWindow(true); //使窗口开始响应鼠标消息
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
		BoolButtondown=0;
		OnPaint();
	}
}

void CDoCircleRunOut::OnBtnchuli() 
{
	// TODO: Add your command handler code here
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
		OnPaint();
	}		
}

void CDoCircleRunOut::OnBtnbgfx() 
{
	// TODO: Add your command handler code here
    FlagBogao=1;
	((CMainFrame*)AfxGetMainWnd())->SetToolBarState(-1,TRUE);
	((CMainFrame*)AfxGetMainWnd())->SetToolBarState(7,FALSE);
	OnPaint();
	flag_bg=1;
}
//最大内切圆法评定圆度误差
void CDoCircleRunOut::MICyuandu()
{

     //--------Case 2, 3-------------------
 	 //----'2- MCC 最小外接圆与显示轮廓相接触至少相接三点。
     //----'3- MIC 最大内切圆与显示轮廓相接触至少相切三点。
     double Direc[7200],Sirec[3600],TsQ[3600],TsH[3600],fpcircle[3600];
	 double SumTs,SumTcos,SumTsin,dw,A0,a1,b1,b2,A2,Zc1,Zc2,D,D1,D2,Maxdirec,Mindirec;
	 double Temp1,U1,U2,U10,U20, GLiGangK = 39.37008,PVA,PVB,PVB0;
     int    i=0,GDN=3600,AnaDataMode=3;//评定算法2为最小外接圆----------3为最大内切圆
	 int    ScanT,MaxIndex,MinIndex,MinI1,MinI2,MaxI1,MaxI2,MaxI3;
    BOOL   GLiGangFlag=false;//qy changed// BOOL   GLiGangFlag;

	 G1=16,G2= 0.121732414074473  ;
     dw= 2*3.1415926/GDN;
  	 SumTs=0,SumTcos=0,SumTsin=0;
	 //=============================================================================
	 ////读取文件并绘图///
	 ReadDataFromFile();
	 
	 //-------------以上代码实现读文件----------------------
	 for(i=0;i<3600;i++)		
	 { 
		 TsQ[i]=(fpdata[i]-2048)*10/(G1*G2*4096); //计算圆度误差转换位移公式	
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
  m_strdEcc.Format("%.3f",MICEcc); 
  m_strdEccPos.Format("%.3f",MICEccPos); 
  m_MICRONT.Format("%.3f",GResult[5]);  //在报表中显示最小区域法评定圆度误差的结果

}
/*

函数功能： 最小区域法评定圆度误差
  DispMaxdirecMZC    ：    最大值
  DispMindirecMZC    ：    最小值
  (MZCDX=U1,MZCDY=U2):     最小区域圆的圆心坐标
  m_MZCRONT          :     最小区域法评定圆度误差的结果
 
*/
void CDoCircleRunOut::MZCyuandu()
{
    //'MZC--最小区域法—两个同心圆的内外包容圆与显示轮廓至少有相间四点接触
    double Direc[7200],Sirec[3600];
    double SumTs=0,SumTcos=0,SumTsin=0,TsQ[3600],TsH[3600];
    double dw,A0,a1,b1, Maxdirec,Mindirec,GLiGangK;
     int   i=0,GDN=3600;
     int   ScanT,PVB0,MaxIndex,MinIndex,MinI1,MaxI1,MinI2,MaxI2;
	 BOOL  GLiGangFlag=false;

	GLiGangK=39.37008;
    dw=2*3.1415926/GDN;

	ReadDataFromFile();//读文件—读取数据、参数、和时间

	for(i=0;i<GDN;i++)		
	{ 
		TsQ[i]=(fpdata[i]-2048)*10/(G1*G2*4096); //计算圆度误差转换位移公式	
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
	m_strdEcc.Format("%.3f",MZCEcc); 
    m_strdEccPos.Format("%.3f",MZCEccPos); 
    m_MZCRONT.Format("%.3f",GResult[1]);  //在报表中显示最小区域法评定圆度误差的结果
}
 
void CDoCircleRunOut::MCCyuandu()
{

     //--------Case 2, 3-------------------
 	 //----'2- MCC 最小外接圆与显示轮廓相接触至少相接三点。
     //----'3- MIC 最大内切圆与显示轮廓相接触至少相切三点。
     double Direc[7200],Sirec[3600],TsQ[3600],TsH[3600],fpcircle[3600];
	 double SumTs,SumTcos,SumTsin,dw,A0,a1,b1,b2,A2,Zc1,Zc2,D,D1,D2,Maxdirec,Mindirec;
	 double Temp1,U1,U2,U10,U20, GLiGangK = 39.37008,PVA,PVB,PVB0;
     int    i=0,GDN=3600,AnaDataMode=2;//评定算法2为最小外接圆----------3为最大内切圆
	 int    ScanT,MaxIndex,MinIndex,MinI1,MinI2,MaxI1,MaxI2,MaxI3;
     BOOL   GLiGangFlag = false;  //qy changed //BOOL   GLiGangFlag;

	 G1=16,G2= 0.121732414074473  ;
     dw= 2*3.1415926/GDN;
  	 SumTs=0,SumTcos=0,SumTsin=0;
	 //=============================================================================
	 ////读取文件并绘图///
	 ReadDataFromFile();
	 
	 //-------------以上代码实现读文件----------------------
	 for(i=0;i<3600;i++)		
	 { 
		 TsQ[i]=(fpdata[i]-2048)*10/(G1*G2*4096); //计算圆度误差转换位移公式	
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
  m_strdEcc.Format("%.3f",MCCEcc); 
  m_strdEccPos.Format("%.3f",MCCEccPos); 
  m_MCCRONT.Format("%.3f",GResult[5]);  //在报表中显示最小区域法评定圆度误差的结果

}

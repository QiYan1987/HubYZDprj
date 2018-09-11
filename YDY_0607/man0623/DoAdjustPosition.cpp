// DoAdjustPosition.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DoAdjustPosition.h"
#include "MainFrm.h"
#include "math.h"
#include "PropertyDlg.h"
#include <fstream>

#ifdef _DEBUG
#define WLS_PI 3.1415926
#define PI 3.1415926
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoAdjustPosition

IMPLEMENT_DYNCREATE(CDoAdjustPosition, CFormView)

CDoAdjustPosition::CDoAdjustPosition()
	: CFormView(CDoAdjustPosition::IDD)
{
	//{{AFX_DATA_INIT(CDoAdjustPosition)
	//}}AFX_DATA_INIT

	G1=1;
	G2=1;
	dEcc=0;
	dEccPos=0;
}

CDoAdjustPosition::~CDoAdjustPosition()
{
}

void CDoAdjustPosition::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoAdjustPosition)
	DDX_Control(pDX, IDC_AdjustPosition, m_StaticAdjustPosition);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoAdjustPosition, CFormView)
	//{{AFX_MSG_MAP(CDoAdjustPosition)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoAdjustPosition diagnostics

#ifdef _DEBUG
void CDoAdjustPosition::AssertValid() const
{
	CFormView::AssertValid();
}

void CDoAdjustPosition::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoAdjustPosition message handlers

void CDoAdjustPosition::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->DestroyVIEW(((CMainFrame*)AfxGetMainWnd())->m_DoAdjustPosition);
	((CMainFrame*)AfxGetMainWnd())->m_DoAdjustPosition=NULL;
	((CMainFrame*)AfxGetMainWnd())->Desktop();
}

void CDoAdjustPosition::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here

	CRect rectFill;
    GetClientRect(rectFill);
    dc.FillSolidRect(rectFill,RGB(255,255,255));  //设置为白色背景 

	pWnd1 = GetDlgItem(IDC_AdjustPosition);      // 获得对话框上的picture的窗口句柄
	pWnd1->GetClientRect(&rect1);             // 获取绘制坐标的文本框
	pDC = pWnd1->GetDC();                     // 获得对话框上的picture的设备指针
	pOldBmp = NULL;                           // 将旧的位图指针置空
	
	memDC.CreateCompatibleDC(pDC);             // 创建内存绘图设备，使内存位图的DC与控件的DC关联
	memBitmap.CreateCompatibleBitmap(pDC,rect1.right,rect1.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap);
    memDC.FillSolidRect(rect1.left,rect1.top,rect1.right,rect1.bottom,RGB(255,255,255));//给矩形框填充白色
	
    double dY0= rect1.Height()/2,dleft=rect1.left,dtop=rect1.top,dright=rect1.right*3/5,dbottom=rect1.bottom,dX0=dright/2;
	CPen RectPen(PS_SOLID,1,RGB(0,0,0));
	memDC.SelectObject(&RectPen);               
	memDC.Rectangle(rect1.left,rect1.top,rect1.right,rect1.bottom); //静态框加上 颜色 边框
    RectPen.DeleteObject();
	DrawCircle();	
	m_strdEcc.Format("%.1f",dEcc*1000);
    m_strdEccPos.Format("%.1f",dEccPos);
	DrawGride1();
	pDC->BitBlt(rect1.left,rect1.top,rect1.right,rect1.bottom,&memDC,0,0,SRCCOPY); //把已经绘好的图显示在制定位置上
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
    memBitmap.DeleteObject();//释放内存设备
}

void CDoAdjustPosition::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	if (m_StaticAdjustPosition.GetSafeHwnd())
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
		m_StaticAdjustPosition.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}
}


/*
函数功能：1.实现坐标系的绘制和测量点的VC界面显示
          2.当手动对数据处理时，在界面上实现变色处理
		  3.变色时包括点和点所在的区域一起变色
		  4.将最内圆、最外圆和基圆的代表数据显示在左上角
其中，轮廓打点的轮廓显示，需要根据率波段选择的不同而相应变化
*/
void CDoAdjustPosition::DrawCircle()
{
	int i;
	dEcc=((CMainFrame*)AfxGetMainWnd())->m_down_pxin;//偏心
    dEccPos=((CMainFrame*)AfxGetMainWnd())->m_down_angle;//偏心角
	G1=((CMainFrame*)AfxGetMainWnd())->G11;//获取传感器参数G1
    G2=((CMainFrame*)AfxGetMainWnd())->G22;//获取传感器参数G2

	for(i=0;i<3600;i++)	
	{
        fpdata[i]=((CMainFrame*)AfxGetMainWnd())->m_down_circledata[i];//圆度数据
	}
/////////////////////////
	double dY0= rect1.Height()/2,dleft=rect1.left,dtop=rect1.top,dright=rect1.right*3/5,dbottom=rect1.bottom,dX0=dright/2;
	CString strcodinate;
	
	//rin为0圆，RSLC为2048圆，rout为4096圆 
	int x1,y1,x2,y2;
	double th,rout=dY0-32,Everystrcod=(rout)/10,rin=Everystrcod*2, RSLC=(rout+rin)/2;
	double     dw = 2 * 3.1415926 / 3600.;// '每一次采样对应的角度间隔，弧度
	//以上代码实现灵活的选取
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));     //创建空画刷，防止遮挡内
	CBrush *pOldBrush=memDC.SelectObject(pBrush);//选择画刷 	
	
	CPen RoutORin(PS_SOLID ,1,RGB(0,230,230));
	memDC.SelectObject(&RoutORin);               
    memDC.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//绘制圆环内圆
    memDC.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//绘制圆环外圆
    RoutORin.DeleteObject();
	CPen Jy(PS_SOLID ,1,RGB(0,0,255));
	memDC.SelectObject(&Jy);
	memDC.Ellipse(dX0-RSLC,dY0-RSLC,dX0+RSLC,dY0+RSLC);//绘制基圆(2048)
	Jy.DeleteObject();
	
    ///////////////////////////////////////////////////////////////////
    ///////////////////////绘制坐标轴//////////////////////////////////
    double EverystrcodX=(rout)/10,EverystrcodY=EverystrcodX;
	CPen penCoordinate (PS_SOLID,1,RGB(0,0,0));
	memDC.SelectObject(&penCoordinate); 
    memDC.MoveTo(dX0-EverystrcodX*10,dY0);
    memDC.LineTo(dX0+EverystrcodX*10,dY0);                    //绘制x轴
	memDC.MoveTo(dX0-EverystrcodX*10,dY0-10); 
	memDC.LineTo(dX0-EverystrcodX*10,dY0+10);
	memDC.MoveTo(dX0+EverystrcodX*10,dY0-10); 
	memDC.LineTo(dX0+EverystrcodX*10,dY0+10);
	memDC.TextOut(dX0+EverystrcodX*10+10,dY0-10,"0°");
	memDC.TextOut(dX0-rout-40,dY0-10,"180°");
	
    memDC.MoveTo(dX0,dY0-EverystrcodY*10);
    memDC.LineTo(dX0,dY0+EverystrcodY*10);                      //绘制y轴
    memDC.MoveTo(dX0+10,dY0+EverystrcodY*10);
   	memDC.LineTo(dX0-10,dY0+EverystrcodY*10);
	memDC.MoveTo(dX0+10,dY0-EverystrcodY*10);
   	memDC.LineTo(dX0-10,dY0-EverystrcodY*10);
	memDC.TextOut(dX0-10,dY0+EverystrcodY*10+10,"270°");
    memDC.TextOut(dX0-10,dY0-EverystrcodY*10-30,"90°");
	
	
	for( i=0; i<10; i++)
	{
		strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //绘制X正轴刻度
		memDC.MoveTo(dX0+i*EverystrcodX , dY0-4);
		memDC.LineTo(dX0+i*EverystrcodX  , dY0+4);
	}	
	for( i=0; i<10; i++)
	{
		strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //绘制X负轴刻度
		memDC.MoveTo(dX0-i*EverystrcodX , dY0-4);
		memDC.LineTo(dX0-i*EverystrcodX  , dY0+4);
	}
	for( i=0; i<10; i++)      //写Y正轴刻度值
	{
		strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		memDC.MoveTo(dX0-4, dY0-i*EverystrcodY);
		memDC.LineTo(dX0+4, dY0-i*EverystrcodY);	
	}
	for( i=0; i<10; i++)  
	{
		strcodinate.Format("%.2f", dY0-i*EverystrcodY);
		memDC.MoveTo(dX0-4, dY0+i*EverystrcodY);
		memDC.LineTo(dX0+4, dY0+i*EverystrcodY);
	}
	penCoordinate.DeleteObject();
	
	
    //-----------------绘制围绕一圈的小黑三角形---------------------------------
	double m_minrTriangle=rout,m_maxRTriangle=(rout+8);// Draw with a thick blue pen.
	CPen penblack(PS_SOLID, 1, RGB(0, 0,0));
	CPen pengrey(PS_DOT ,1,RGB(230,230,230));// And a solid red brush.
	CBrush brushblack(RGB(0, 0, 0));
    memDC.SelectObject(&brushblack);
	CPoint pts[3];
	double tr=2 * 3.1415926/36;// 每一次采样对应的角度间隔，弧度
	double wzd=asin(6/m_maxRTriangle); //每次三角形的底边两点相对于定点的旋转角度
	
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
	}  
	DeleteObject(pBrush);

	///////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
    double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	double m_datamax=0.0,m_datamin=0.0;
	double A0,A1,B1,SumTcos,SumTsin,SumTs,TsH[3600];
	  //手动处理后的数据进行调用函数计算
      for(i=0;i<3600;i++)		
	  { 
	  	   datacir[i]=(fpdata[i]-2048)*10/(G1*G2*4096);//计算圆度误差转换位移公式
		   TsH[i]=fpdata[i];
	  }
	  //WLS_Filter(FilterMode,3600,datacir,dataafterfilter);
	  SumTs = 0,SumTcos = 0,SumTsin = 0;
	  for( i = 0;i<3600;i++)
	  {
		   SumTs = SumTs + TsH[i];
		   SumTcos = SumTcos + TsH[i] * cos(dw * i);
		   SumTsin = SumTsin + TsH[i] * sin(dw * i);
	  }
	   A0 = SumTs/3600;       
	   A1 = 2*SumTcos/3600;  
	   B1 = 2*SumTsin/3600; 
	   
       m_datamin=0;
       m_datamax=4096;
       m_Middle=2048;
       m_OutIn=m_datamax-m_datamin;
       //算出轮廓的横、纵坐标
	   for(i=0;i<3600;i++)		
	   { 
		   datas[i]=(fpdata[i]-m_Middle)*(rout-rin)/m_OutIn+RSLC; //绘制圆度打点时按比例显示
		   drealx[i]=datas[i]*cos(i*dw)+dX0;
		   drealy[i]=datas[i]*sin(i*dw)+dY0;//实际轮廓的横、纵坐标(相对于二乘圆的)
	  }	
	 m_Intstep=5;//间隔几个点打点连线
	 CPen penreal;
	 penreal.CreatePen(PS_SOLID,1, RGB(250,0,0));  
	   
	 for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	 {  		
		 memDC.SelectObject(&penreal);
		 memDC.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//蓝色曲线表示实际轮廓
		 memDC.MoveTo(drealx[i], drealy[i]);
		 memDC.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
	 }
	penreal.DeleteObject();
	pBrush->DeleteObject();
}
void CDoAdjustPosition::DrawGride1()
{
	double dY0= rect1.Height()/2,dleft=rect1.left,dtop=rect1.top,dright=rect1.right*3/5,dbottom=rect1.bottom,dX0=dright/2;
	int gridxnums=1;int gridynums=22;
	double dx= (rect1.Width()-dright)/gridxnums;
	double dy=rect1.Height()/gridynums;
    CRect gridRect(rect1.left,rect1.top,rect1.left+dx*gridxnums,rect1.top+dy*gridynums);
	CPen gridPen(0,0,RGB(0,0,20)); //网格线的颜色
	memDC.FillSolidRect(dright+dx,dy*12,dx,dy,RGB(139,216,224));//给指定格子填充颜色
    CPen *oldpen=memDC.SelectObject(&gridPen);

	memDC.FillSolidRect(dright,0,gridRect.right-1,dy,RGB(232,232,232));//给头行填充颜色
	memDC.FillSolidRect(dright,dy*5,gridRect.right-1,dy,RGB(232,232,232));//给指定行填充颜色
	memDC.FillSolidRect(dright,dy*13,gridRect.right-1,dy,RGB(232,232,232));//给指定行填充颜色

	//----------数据写入字体及大小
	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
	CFont*   pOldFont=(CFont*)memDC.SelectObject(&font); 

	memDC.SetBkMode(TRANSPARENT); 
	int m1=rect1.left+dright+4;
	int meter=4;
	double m2=rect1.left+dright+dx/2;
	double m3=rect1.left+dright+dx-80;
	double mid=rect1.left+dright+dx/2-30;
 
	//将圆度计算的结果信息显示在表格对应的位置上，此处显示信息有：圆度、偏心、偏心角
 
	//报表显示圆度评定类型		

	memDC.TextOut(mid ,meter,"偏心调整测量结果");
	memDC.TextOut(m1,dy+meter,"调整次数");
	CString str;
	str.Format("%d/%d",((CMainFrame*)AfxGetMainWnd())->m_fintTimes,
		               ((CMainFrame*)AfxGetMainWnd())->m_intTimes);//
	memDC.TextOut(m2,dy,str);
	memDC.TextOut(m1,dy*2+meter,"偏心量");
	memDC.TextOut(m2,dy*2+meter,m_strdEcc);
	memDC.TextOut(m3,dy*2+meter,"um");
	memDC.TextOut(m1,dy*3+meter,"偏角度");
	memDC.TextOut(m2,dy*3+meter,m_strdEccPos);
	memDC.TextOut(m3,dy*3+meter,"°");
	//------------------------------------------------------------
	for(int m=0;m<=gridxnums;m++) //画出gridxnums条竖线                      
	{
		memDC.MoveTo(dright+m*dx,gridRect.bottom);
		memDC.LineTo(dright+m*dx,0);
	}
		
	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
	{
		memDC.MoveTo(rect1.left+dright,n*dy);
		memDC.LineTo(rect1.left+rect1.Width(),n*dy);
	}
    
	memDC.MoveTo(rect1.left+dright,rect1.top);
	memDC.LineTo(rect1.left+dright,rect1.bottom);

	memDC.MoveTo(dright,dtop);
	memDC.LineTo(dright,dbottom);
}


void CDoAdjustPosition::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_StaticAdjustPosition.GetSafeHwnd())
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
		m_StaticAdjustPosition.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}
}

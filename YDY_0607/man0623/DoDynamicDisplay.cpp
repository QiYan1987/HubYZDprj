// DoDynamicDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DoDynamicDisplay.h"
#include "math.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CDoDynamicDisplay

IMPLEMENT_DYNCREATE(CDoDynamicDisplay, CFormView)

CDoDynamicDisplay::CDoDynamicDisplay()
	: CFormView(CDoDynamicDisplay::IDD)
{
	//{{AFX_DATA_INIT(CDoDynamicDisplay)
	m_oldpos=0;
	m_bCalFlag=FALSE;
	m_dangwei = 0;
	//}}AFX_DATA_INIT
	dresult[0]=0;
	dresult[1]=0;
	m_flag==true;
	mes[0]=0;
	mes[1]=0;
}

CDoDynamicDisplay::~CDoDynamicDisplay()
{
}

void CDoDynamicDisplay::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoDynamicDisplay)
	DDX_Control(pDX, IDC_BUTTONOPENDYN, m_ctrlBtnOpen);
	DDX_Control(pDX, IDC_BUTTONSTOPDYN, m_ctrlBtnStop);
	DDX_Control(pDX, IDC_editDynamicDisplay, m_editDynamicDisplay);
	DDX_Radio(pDX, IDC_RADIO1, m_dangwei);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoDynamicDisplay, CFormView)
	//{{AFX_MSG_MAP(CDoDynamicDisplay)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTONOPENDYN, OnOpendyn)
	ON_BN_CLICKED(IDC_BUTTONSTOPDYN, OnStopdyn)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoDynamicDisplay diagnostics

#ifdef _DEBUG
void CDoDynamicDisplay::AssertValid() const
{
	CFormView::AssertValid();
}

void CDoDynamicDisplay::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoDynamicDisplay message handlers

void CDoDynamicDisplay::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CBitmap		memBitmap;        // 用于内存绘图的位图  
  //  dc.FillSolidRect(rectFill,RGB(255,255,0));  //设置为白色背景 
	pWnd1 = GetDlgItem(IDC_editDynamicDisplay);      // 获得对话框上的picture的窗口句柄
	pWnd1->GetClientRect(&rect);             // 获取绘制坐标的文本框
	pDC = pWnd1->GetDC();                     // 获得对话框上的picture的设备指针
	pOldBmp = NULL;      
	memDC.CreateCompatibleDC(pDC);             // 创建内存绘图设备，使内存位图的DC与控件的DC关联
	memBitmap.CreateCompatibleBitmap(pDC,rect.right,rect.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap);
//	((CMainFrame*)AfxGetMainWnd())->m_controlMotorPort.CM_GetiMSensorData(mesDate);
	m_G1=((CMainFrame*)AfxGetMainWnd())->G11;
	m_G2=((CMainFrame*)AfxGetMainWnd())->G22;
	//获得数据
	//绘图
    //double dleft=rect.left,dtop=rect.top,dright=rect.right,dbottom=rect.bottom,dY0= rect.Height()/2,dX0=dright/2;
	CPen RectPen(PS_SOLID,1,RGB(0,0,0));
	memDC.SelectObject(&RectPen);               
	memDC.Rectangle(rect.left,rect.top,rect.right,rect.bottom); //静态框加上颜色边框
    RectPen.DeleteObject();

	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
		DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
	CFont*   pOldFont=(CFont*)memDC.SelectObject(&font); 

	 double dtop=rect.top,dbottom=rect.bottom,dleft=rect.left,dright=rect.right,dY0= rect.Height()/2,dX0=dright/2;
	CString strcodinate;

	//rin为0圆，RSLC为2048圆，rout为4096圆 
	int i,x1,y1,x2,y2;
	double th,rout=dY0-32,Everystrcod=(rout)/10,rin=Everystrcod*2, RSLC=(rout+rin)/2;

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

	if (m_flag)
	{
		m_flag=!m_flag;
	}
	else
	{
		DynamicDrawCircle();//调用实时测量函数
	} 
	
	pDC->BitBlt(rect.left,rect.top,rect.right,rect.bottom,&memDC,0,0,SRCCOPY); //把已经绘好的图显示在制定位置上
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
	this->ReleaseDC(pDC);
}

void CDoDynamicDisplay::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	KillTimer(1);
	((CMainFrame*)AfxGetMainWnd())->DestroyVIEW(((CMainFrame*)AfxGetMainWnd())->m_DoDynamicDisplay);
	((CMainFrame*)AfxGetMainWnd())->m_DoDynamicDisplay=NULL;
	((CMainFrame*)AfxGetMainWnd())->Desktop();
}

void CDoDynamicDisplay::OnTimer(UINT nIDEvent) 
{
		//	mesData[i]=(mesData[i]-2048)*10/(m_G1*m_G2*4096);
	// TODO: Add your message handler code here and/or call default
	
	((CMainFrame*)AfxGetMainWnd())->GetMesData(mes);
	UINT pos=mes[0];//位置
	UINT Data=mes[1];
	int i;
	if(pos<m_oldpos)
	{
		for (i=m_oldpos+1;i<=3599;i++)
		{
			mesData[i]=Data;
		}
		for(i=0;i<pos;i++)
		{
			mesData[i]=Data;
		}
		m_bCalFlag=TRUE;
		double pem[3600];
		double dlimit;
		dlimit=((4096-2048)*10)/(m_G1*m_G2*4096)*0.001;

		for (int j=0;j<3600;j++)
		{
			if (mesData[j]>2048)
			{
              pem[j]=(((mesData[j]-2048)*10)/(m_G1*m_G2*4096))*0.001;
			}
			else
			pem[j]=-(((2048-mesData[j])*10)/(m_G1*m_G2*4096))*0.001;
		}
		((CMainFrame*)AfxGetMainWnd())->m_Adjustment.Celiang(pem,dlimit,dresult);
	}
	else
	{
		for (int i=m_oldpos+1;i<=pos;i++)
		{
			mesData[i]=Data;
		}
		m_bCalFlag=FALSE;
	}
	m_oldpos=pos;
	PostMessage(WM_PAINT);
	CFormView::OnTimer(nIDEvent);
}

void CDoDynamicDisplay::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CRect rect;
	int x,y;
	GetClientRect(rect);
// 	m_ctrlBtnOpen.MoveWindow(rect.right-150,rect.bottom-300,80,60);
// 	m_ctrlBtnStop.MoveWindow(rect.right-150,rect.bottom-180,80,60);
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
	m_editDynamicDisplay.MoveWindow(100,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);


	for (int i=0;i<3600;i++)
	{
		mesData[i]=0;
	}
	m_count=0;
	((CMainFrame*)AfxGetMainWnd())->SwitchG11(0);
	//SetTimer(1,10,NULL);
}

void CDoDynamicDisplay::DynamicDrawCircle()
{
	//定义后面将要用到的变量
    double dtop=rect.top,dbottom=rect.bottom,dleft=rect.left,dright=rect.right,dY0= rect.Height()/2,dX0=dright/2;
	CString strcodinate;
    //rin为0圆，RSLC为2048圆，rout为4096圆 
	int i,x1,y1,x2,y2;
	double th,rout=dY0-32,Everystrcod=(rout)/10,rin=Everystrcod*2, RSLC=(rout+rin)/2;
	
	//以上代码实现灵活的选取
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));     //创建空画刷，防止遮挡内
	CBrush *pOldBrush=memDC.SelectObject(pBrush);//选择画刷 
	
	CString strRes;
	strRes.Format("偏心量：%.1fum",1000*dresult[0]);
	memDC.TextOut(dX0+rout+10+20,dY0+rout-25,strRes);
	strRes.Format("偏心角度：%.1f°",dresult[1]);
	memDC.TextOut(dX0+rout+10+20,dY0+rout-5,strRes);
	////////////////////////绘制轮廓////////////////////////////////////////////////
    double datas[3600],drealx[3600],drealy[3600];
	int  starx,stary,endx,endy;
	double m_datamax=0.0,m_datamin=0.0;	
    m_datamin=0;
    m_datamax=4096;
    m_Middle=2048;
    m_OutIn=(m_datamax-m_datamin);
    //算出轮廓的横、纵坐标
	for(i=0;i<3600;i+=10)		
	{  
		datas[i]=(((CMainFrame*)AfxGetMainWnd())->m_OutIn)*(mesData[i]-m_Middle)*(rout-rin)/m_OutIn*1.5+RSLC; //绘制圆度打点时按比例显示
		if(datas[i]>rout)
			datas[i]=rout;
		if(datas[i]<rin)
			datas[i]=rin;
		drealx[i]=datas[i]*cos(i*2*3.1415926/3600)+dX0;
		drealy[i]=datas[i]*sin(i*2*3.1415926/3600)+dY0;//实际轮廓的横、纵坐标(相对于二乘圆的)
	}
	
	starx=cos(m_oldpos*2*3.1415926/3600)*((4096-m_Middle)*(rout-rin)/m_OutIn+RSLC)+dX0;
	stary=sin(m_oldpos*2*3.1415926/3600)*((4096-m_Middle)*(rout-rin)/m_OutIn+RSLC)+dY0;
	endx=cos(m_oldpos*2*3.1415926/3600)*((3500-m_Middle)*(rout-rin)/m_OutIn+RSLC)+dX0;
	endy=sin(m_oldpos*2*3.1415926/3600)*((3500-m_Middle)*(rout-rin)/m_OutIn+RSLC)+dY0;
	
	CPen penreal1;
	penreal1.CreatePen(PS_SOLID,1, RGB(255,0,0));  
	for(i=0;i<3600;i+=10)		
	{  		
		memDC.SelectObject(&penreal1);
		int rin1=1;
		memDC.Ellipse(drealx[i]-rin1,drealy[i]-rin1,drealx[i]+rin1,drealy[i]+rin1);//表示实际轮廓
	}
	memDC.MoveTo(starx,stary);
	memDC.LineTo(endx,endy);
	penreal1.DeleteObject();
	pBrush->DeleteObject();   
	DeleteObject(pBrush);
}

void CDoDynamicDisplay::OnOpendyn() 
{
	//// TODO: Add your control notification handler code here
    
	m_flag=true;
	OnPaint();
	GetDlgItem(IDC_BUTTONOPENDYN)->EnableWindow(false);
	GetDlgItem(IDC_BUTTONSTOPDYN)->EnableWindow(true);
	((CMainFrame*)AfxGetMainWnd())->OnOpendyn();
	GetDlgItem(IDC_RADIO1)->SetFocus();
	SetTimer(1,10,NULL);
}

void CDoDynamicDisplay::OnStopdyn() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	memset(mesData,0,sizeof(mesData));
	m_count=0;
	m_flag=true;
	m_oldpos=0;
	mes[0]=0;
	mes[1]=0;
	OnPaint();
	GetDlgItem(IDC_BUTTONOPENDYN)->EnableWindow(true);
	GetDlgItem(IDC_BUTTONSTOPDYN)->EnableWindow(false);
	((CMainFrame*)AfxGetMainWnd())->OnStopdyn();
}


void CDoDynamicDisplay::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)AfxGetMainWnd())->SwitchG11(0);
}

void CDoDynamicDisplay::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)AfxGetMainWnd())->SwitchG11(1);
}

void CDoDynamicDisplay::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)AfxGetMainWnd())->SwitchG11(2);
}

void CDoDynamicDisplay::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)AfxGetMainWnd())->SwitchG11(3);
}

void CDoDynamicDisplay::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)AfxGetMainWnd())->SwitchG11(4);
}

void CDoDynamicDisplay::OnRadio6() 
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)AfxGetMainWnd())->SwitchG11(5);
}

void CDoDynamicDisplay::OnRadio7() 
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)AfxGetMainWnd())->SwitchG11(6);
}

void CDoDynamicDisplay::OnRadio8() 
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)AfxGetMainWnd())->SwitchG11(7);
}

BOOL CDoDynamicDisplay::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
// 	if (WM_KEYDOWN != pMsg->message)
// 		return true;
	 if(pMsg->message == WM_KEYDOWN)
	 {  
		 int a=pMsg->wParam;
		 switch(pMsg->wParam)
		 {
		 case 49:  // 
			 m_dangwei=0;
			 OnRadio1();
			 break; 
		 case 97:  // 
			 m_dangwei=0;
			 OnRadio1();
			 break;
		 case 50:  //
			 m_dangwei=1;
			 OnRadio2();
			 break; 
		 case 98:  // 
			 m_dangwei=1;
			 OnRadio2();
			 break;
		 case 51:  // 
			 m_dangwei=2;
			 OnRadio3();
			 break; 
		 case 99:  // 
			 m_dangwei=2;
			 OnRadio3();
			 break;
		 case 52:  //  
			 m_dangwei=3;
			 OnRadio4();
			 break; 
		 case 100:  // 
			 m_dangwei=3;
			 OnRadio4();
			 break;
		 case 53:  //  
			 m_dangwei=4;
			 OnRadio5();
			 break; 
		 case 101:  // 
			 m_dangwei=4;
			 OnRadio5();
			 break;
		 case 54:  //  
			 m_dangwei=5;
			 OnRadio6();
			 break; 
		 case 102:  // 
			 m_dangwei=5;
			 OnRadio6();
			 break;
		 case 55:  // 
			 m_dangwei=6;
			 OnRadio7();
			 break; 
		 case 103:  // 
			 m_dangwei=6;
			 OnRadio7();
			 break;
		 case 56:  //   
			 m_dangwei=7;
			 OnRadio8();
			 break; 
		 case 104:  // 
			 m_dangwei=7;
			 OnRadio8();
			 break;
		 case 75:
			OnOpendyn();
			break;
		 case 84:
			 OnStopdyn();
			 break;
		 default:
			 break;
		 }
		 UpdateData(FALSE);
		 return TRUE;///禁止发声
	 }
	 return CFormView::PreTranslateMessage(pMsg);
	 //return TRUE;
}
void CDoDynamicDisplay::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
// 	CRect rect;
// 	int x,y;
// 	// TODO: Add your message handler code here
// 	if (m_editDynamicDisplay.GetSafeHwnd())
// 	{
// 		GetClientRect(rect);
// 		x=rect.left+rect.Width()/40;
// 		y=rect.top+rect.Height()/40;
// 		if (rect.Width()<5*rect.Height()/3)
// 		{
// 			y=rect.top+(rect.Height()-rect.Width()*3/5)/2;
// 			rect.bottom=rect.top+rect.Width()*3/5;	
// 		}
// 		else
// 		{
// 			x=rect.left+(rect.Width()-rect.Height()*5/3)/2;
// 			rect.right=rect.left+rect.Height()*5/3;
// 		}
// 		if(x>100)
// 		{
// 			m_editDynamicDisplay.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
// 			if (m_ctrlBtnOpen.GetSafeHwnd())
// 			{
// 				GetClientRect(rect);
// 				m_ctrlBtnOpen.MoveWindow(x+(rect.Height()-rect.Height()/20)*5/3+30,y+rect.Height()-rect.Height()/22-180,80,60);
// 			}
// 			if (m_ctrlBtnOpen.GetSafeHwnd())
// 			{
// 				GetClientRect(rect);
// 				m_ctrlBtnStop.MoveWindow(x+(rect.Height()-rect.Height()/20)*5/3+30,y+rect.Height()-rect.Height()/22-100,80,60);
// 			}
// 		}
// 	}
}


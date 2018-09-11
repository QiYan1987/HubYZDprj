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
	m_strMethod="��С���˷�";
	m_bIsEnable=FALSE;
	m_BOOLSegmentprocess=0;
	CirEvalue=0;
	
	m_BOOLSegmentprocess=0;
	FlagFrequency=0;
	FlagBogao=0;
    BtnChuliDwon=0;
	m_Wa="";	//���ƶ���ʾ
	m_Wc="";	//���ƶ���
	m_Wp="";	//���ƶ���
	m_Wv="";	//���ƶ���ʾ
	m_Wt="";	//���ƶ���
	m_Wq="";	//���ƶ���
    m_Wwm="";	//���ƶ���
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
	case 0: m_strlvbo="��"; break;
	case 1: m_strlvbo="һ�β�"; break;
	case 2: m_strlvbo="����"; break;
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
	case 0: m_strMethod="��С���˷�";break;
	case 1: m_strMethod="��С����";break;
	case 2: m_strMethod="��С���Բ";break;
	case 3: m_strMethod="�������Բ";break;
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
	////��ȡ�ļ�����ͼ///
	int    i;
	double datas[3600],drealx[3600],drealy[3600],theta=0,datacir[3600];
    double dRmax=0.0,dRmin=0.0,m_datamax=0.0,m_datamin=0.0;

    LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//��ӦԲ�����еĵ���
    m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//��굥��ѡ�еĽ���
	pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
 
	std::ifstream fin(pathJM, std::ios::binary);
   	for ( i=0;i<=LenDataJM;i++)
	{	
		fin.read((char*)&m_dataJM[i], sizeof(shuju0)); //��ȡ����
	}
	fin.read((char*)&GG1,sizeof(double));
	fin.read((char*)&GG2,sizeof(double));
	fin.read((char*)&m_time,sizeof(CTime));
    fin.close();

  
	//������潫Ҫ�õ��ı���
    double dY0= rectJM.Height()/2+rectJM.top,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5*1/2+rectJM.left;
	CString strcodinate;
	//rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ
	int x1,y1,x2,y2;
	double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	dw=2*PI/3600;

	//���Ƶ�ɫԲ����
    CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //���ƻ�ɫԲ���� 
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

	CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //����Բ������ɫ�� 
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
   	//----------���춯̬Բ��---------
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
	
	//----------------------���ϴ���ʵ������ѡȡ-----------
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));     //�����ջ�ˢ����ֹ�ڵ���
	CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//ѡ��ˢ 
	//double Rmincir=dX0/2-100;

    double Rmincir=rin*5/12;
	CPen pencir;
	pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
    memDCJM.SelectObject(&pencir); 
    memDCJM.Ellipse(dX0-RSLC,dY0-RSLC,dX0+RSLC,dY0+RSLC);//���ƻ�Բ(2048)
	pencir.DeleteObject();
	
	CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	memDCJM.SelectObject(&RoutORin);               
    memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//����Բ����Բ
    memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//����Բ����Բ
    RoutORin.DeleteObject();
   
	///////////////////////////////////////////////////////////////////
	///////////////////////����������//////////////////////////////////
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
    memDCJM.LineTo(dX0+EverystrcodX*10,dY0);//����x��
    memDCJM.TextOut(dX0+(rout+dright-dX0)/2,dY0-EverystrcodY/2,"0��");
    memDCJM.TextOut(rectJM.left,dY0-EverystrcodY/2,"180��");
    memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
    memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //����y��
    memDCJM.TextOut(dX0-EverystrcodX/2,dY0+EverystrcodY*11,"270��");
    memDCJM.TextOut(dX0-EverystrcodX/2,dY0-EverystrcodY*11.5,"90��");
	memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135��");
    memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315��");
	memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45��");
	memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225��");
		  	  
    for(i=0; i<10; i++)
	{
		strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //����X����̶�
  	    memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
	    memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	}	
    for( i=0; i<10; i++)
	{
	    strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //����X����̶�
	    memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
	    memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	}
    for( i=0; i<10; i++)      //дY����̶�ֵ
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
    //�ڼ�����������Ǵ��ݹ�����///////////////////���������M;
	for (i=0;i<3600;i++)	
	{  
		fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		m_CirCal[i]=fpdata[i];    //����Բ�����ת��λ�ƹ�ʽ		
	}	
	////////////////////////////////////////////////////////////////////////////////
    //�ֶ�����������ݽ��е��ú�������	
	for(i=0;i<3600;i++)		
	{ 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //����Բ�����ת��λ�ƹ�ʽ	
	}		
	DrawFilter (FilterMode,datacir,dataafterfilter);//�����˲��������˲�֮������ݷ�ӳ�ڽ��������
	//////////////////////////////////////////////////
	//////////////�����ͼ���������ֵ����Сֵ//////////////
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
	//////////////////////��������ĺᡢ������///////////////////////////////
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
		drealy[i]=datas[i]*sin(i*dw)+dY0;//ʵ�������ĺᡢ������(����ڶ���Բ��)

	}	
	///////////////////////////////////////////////////////
    m_Intstep=5;//�����������
	CPen penreal;
	penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));    
	CPen pendeal;
	pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));    
	
	for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	{ 
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{  
		   memDCJM.SelectObject(&pendeal);
		   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//��ɫ���߱�ʾ�ֶ���������
		   memDCJM.MoveTo(drealx[i], drealy[i]);
		   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);	
		
		}
		else
		{
			memDCJM.SelectObject(&penreal);
			memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//��ɫ���߱�ʾʵ������
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
			    memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//��ɫ���߱�ʾʵ������
		    	memDCJM.MoveTo(drealx[i], drealy[i]);
			    memDCJM.LineTo(drealx[0], drealy[0]);	
			}
			else
			{
				memDCJM.SelectObject(&penreal);
				memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//��ɫ���߱�ʾʵ������
				memDCJM.MoveTo(drealx[i], drealy[i]);
				memDCJM.LineTo(drealx[0], drealy[0]);
			}
		}
	}
	penreal.DeleteObject();
    pendeal.DeleteObject();
	
	//-----------------����Χ��һȦ��С��������---------------------------------
// 	double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
// 	CPen penblack(PS_SOLID, 1*m_penScale, RGB(0, 0,0));
// 	CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
// 	CBrush brushblack(RGB(0, 0, 0));
//     memDCJM.SelectObject(&brushblack);
// 	CPoint pts[3];
// 	double tr=2 * 3.1415926/36;// ÿһ�β�����Ӧ�ĽǶȼ��������
// 	double wzd=asin(6/m_maxRTriangle); //ÿ�������εĵױ���������ڶ������ת�Ƕ�
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
	double tr=2 * 3.1415926/36;// ÿһ�β�����Ӧ�ĽǶȼ��������
	double wzd=asin(6*m_penScale/m_maxRTriangle); //ÿ�������εĵױ���������ڶ������ת�Ƕ�
	
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
	//ͼ����ʾ��ע˵��
	CString m_SelectJM,m_TotalJM;
    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);
	
	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"��������:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"��ǰ����:");
	
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
		dc.FillSolidRect(rectFill,RGB(255,255,255));  //����Ϊ��ɫ���� 
		
		pWndJM = GetDlgItem(IDC_JManalyse);      // ��öԻ����ϵ�picture�Ĵ��ھ��
		pWndJM->GetClientRect(&rectJM);             // ��ȡ����������ı���
		pDCJM = pWndJM->GetDC();                     // ��öԻ����ϵ�picture���豸ָ��
		pOldBmpJM = NULL;                           // ���ɵ�λͼָ���ÿ�
		int a=rectJM.Width();                                        
		memDCJM.CreateCompatibleDC(pDCJM);             // �����ڴ��ͼ�豸��ʹ�ڴ�λͼ��DC��ؼ���DC����
		memBitmapJM.CreateCompatibleBitmap(pDCJM,rectJM.right,rectJM.bottom);
		pOldBmpJM = memDCJM.SelectObject(&memBitmapJM);
		memDCJM.FillSolidRect(rectJM.left,rectJM.top,rectJM.right,rectJM.bottom,RGB(255,255,255));//�����ο�����ɫ

		double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.right*3/5,dbottom=rectJM.bottom,dX0=dright/2;
		CPen RectPen(PS_SOLID,1,RGB(0,0,0));
		memDCJM.SelectObject(&RectPen);               
		memDCJM.Rectangle(rectJM.left,rectJM.top,rectJM.right,rectJM.bottom); //��̬����� ��ɫ �߿�
		RectPen.DeleteObject();

		CFont   font; 
		font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
			DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  
		CFont*   pOldFont=(CFont*)memDCJM.SelectObject(&font); 
		m_penScale=1;


	   ((CMainFrame*)AfxGetMainWnd())->JMCL=BtnChuliDwon; //��굥���Ľ���

	   LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//��ӦԲ�����еĵ���
	   m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//��굥��ѡ�еĽ���
	   pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;

    
		ReadDataFromFile();
		if(m_BOOLSegmentprocess==0  &&  FlagFrequency==0 )
		{	
				SubQKDataChuli(pathJM,m_LBtnJM,3600,!((CMainFrame*)AfxGetMainWnd())->m_bAutoQK,m_CirCal, Resdata,m_IndexStart,m_IndexEnd);
				if (CirEvalue==0)
				{
					DrawJMofYZD();
					SubAnaData (FilterMode, Resdata,GResult,GG1,GG2);	//Բ��
					dRONT=GResult[1];
					SubAnaData(1,  Resdata,GResult,GG1,GG2);    //1
					dEcc=GResult[1]/2;  //ƫ��
					dEccPos=GResult[3];  //ƫ�Ľ�

					m_strFilterMode.Format("%d",FilterMode);
					m_strdRONT.Format("%.3f",dRONT); //�����ݽ��ת�����ַ�������ʽ��������ʾ�ڱ�����
					m_strdEcc.Format("%.2f",dEcc);
					m_strdEccPos.Format("%.2f",dEccPos);
					//��ʾ���ƶ�
					m_Wa.Format("%.2f",m_BWD[0]); //�����ݽ��ת�����ַ�������ʽ��������ʾ�ڱ�����
					m_Wc.Format("%.2f",m_BWD[1]);
					m_Wp.Format("%.2f",m_BWD[2]);
					m_Wv.Format("%.2f",m_BWD[3]); //�����ݽ��ת�����ַ�������ʽ��������ʾ�ڱ�����
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
		pDCJM->BitBlt(rectJM.left,rectJM.top,rectJM.right,rectJM.bottom,&memDCJM,0,0,SRCCOPY); //���Ѿ���õ�ͼ��ʾ���ƶ�λ����
		memDCJM.SelectObject(pOldBmpJM);
		memDCJM.DeleteDC();
		memBitmapJM.DeleteObject();//�ͷ��ڴ��豸
	}
}

void CJMAnalyse::DynamicDrawCircleJM( int startPosition, int endPosition)
{	
	//������潫Ҫ�õ��ı���
	double dY0= rectJM.Height()/2,dright=rectJM.right*3/5,dX0=dright/2;//rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ
	int x1,y1,x2,y2,i;
	double rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	dw= 2 * PI/3600;// ÿһ�β�����Ӧ�ĽǶȼ��������nTriangle.DeleteObject();
	
	CPen ping1(PS_SOLID,2,RGB(250,200,238));   //����Բ����ɫ�� 
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

/*�������ܣ����ֶ���������������ʱ����Ӧ������ɫ����
���ұ�������
*/
void CJMAnalyse::ChangeValueOfSelectJM(CString path,int startPosition, int endPosition, BOOL isSelected)
{
	
		shuju0 ChangeDate[36001];
		std::ifstream fin(path, std::ios::binary);
		int i;
		if (endPosition>startPosition)                       //˳������ת
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
		else  //��ʱ��������ת
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

/*  �����ֶ�ɾ������
   ���ú�����ʱ��.select=0;����֮ǰ���ֶ�����

*/
void CJMAnalyse::DrawingCleanAndResetJM(CString path, BOOL isSelected)
{
	//��������
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
	//д��ı������
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
�������ܣ�ɾ���������ݿ��еĲ�������
����������
		CString path			: �ļ�·��
		int NumOfCircle			: ɾ���������ǵڼ�����������ݣ� 1��ʾ��һ������
		BOOL isSaveTheFormer	: �Ƿ񱣴�ԭ�����ݣ�FALSE: ������ THRU :����
���ز�����int error     
	0   : ��ʾ�޴�
	1   : NumOfCircle<1
	2   : ����λ�ô������Ľ���λ��
	3   : ɾ��ĳ��������ļ��Ľ������С��2
*/
int CJMAnalyse::DeletePartOfFile(CString path, int NumOfCircle,BOOL isSaveTheFormer)										   
{
	shuju0 measureData[3601];
	int intLength=0;
	int numofcircle=0;
	//���ɾ���Ľ���λ��С��1�����ش������1
	if (NumOfCircle<1)
	{
		return 1;
	}
	std::ifstream fin(path,std::ios::binary);
	fin.read((char*)&measureData[intLength], sizeof(shuju0));
	intLength++;
	//���ɾ���Ľ���λ�ô������Ľ���λ�ã����ش������2
	if (NumOfCircle>measureData[0].data)
	{
		return 2;
	}
	//���ɾ��ĳ��������ļ��Ľ������С��2���򷵻ش������3
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
	//д��������ֵ
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


/*�������ܣ�
 ---- ����ѡ����ʲ���ʵ��Բ����Ϣ�ļ���
 ---- ѡ���Ӧ�Ĳ��ε��˲�����
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
    dw = 2 * 3.1415926 / 3600.;// 'ÿһ�β�����Ӧ�ĽǶȼ��������
	switch (FilterMode)
	 {	
	case 0 ://'���˲�
		   for( i = 0;i<3600 ;i++)
		   {
			   TsH[i] = TsQ[i];
		   }
			break;
   case 1: //'����һ��г��
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
   case 2: //'����1-500��г��
		 WLS_Filter(2, 3600, TsQ, TsH);
		// '6�װ�����˹�˲��� pMem(i) to TsH(i)
		 //'----ȥ��ֱ������---
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
   case 3: //'����2-500��г��
		   WLS_Filter(3, 3600, TsQ, TsH);
		   //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
		   //'----ȥ��ֱ��������1��г�� ---
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
   case 4: //'����2-15��г��
		   WLS_Filter(4, 3600, TsQ, TsH);
		   //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
		   //'----ȥ��ֱ��������1��г�� ---
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
   case 5: //'�˳�2-50��г��
		   WLS_Filter(5, 3600, TsQ, TsH);
		   SumTs = 0;
		   SumTcos = 0;
		   SumTsin = 0; 
		   //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
		   //   '----ȥ��ֱ��������1��г�� ---
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
   case 6: //'�˳�2-150��г��
		   WLS_Filter(6, 3600, TsQ, TsH);
		   //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
		   //'----ȥ��ֱ��������1��г�� ---
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
   case 7:// '�˳�15-500��г��
		   WLS_Filter(7, 3600, TsQ, TsH);
		 //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
		   break;
   case 8:// '�˳�3-16��г��
		   WLS_Filter(8,3600, TsQ, TsH);
		   //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
		   //'----ȥ��ֱ��������1��г��,2��г�� ---
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
   case 9:// '�˳�17-100��г��
			WLS_Filter(9, 3600, TsQ, TsH);
			//'6�װ�����˹�˲��� TsQ(i) to TsH(i)
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
		  // '����һ��г�� ,����1-500��г��
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
	}//ƫ��  
    GResult[3] = (atan(fabs(B1 / A1)) * 180) / (3.1415926);
     // 'Atn (Number) ����һ�� Double��ָ��һ�����ķ�����ֵ��
     // 'A1Ϊ��С����ԲX����,B1Ϊ��С����ԲY����
    if( (A1 < 0) &(B1 >= 0))
	{  //'�ڶ�����	
		GResult[3] = 180 - GResult[3];
	}
	else if( (A1 < 0) & (B1 < 0)) 
	{//'��������
		GResult[3] = -(180 - GResult[3]);
	}
	 else if((A1 >= 0) & (B1 < 0))
	 {//'��������
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
    dw = 2 * 3.1415926 / 3600.;// 'ÿһ�β�����Ӧ�ĽǶȼ��������
	switch (FilterMode)
	 {
	case 0 ://'���˲�
	   for( i = 0;i<3600 ;i++)
	   {
           drawdata[i] = TsQ[i];
	   }
      break;
   case 1: //'����һ��г��
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
   case 2: //'����1-500��г��
		 WLS_Filter(2, 3600, TsQ, TsH);
		// '6�װ�����˹�˲��� pMem(i) to TsH(i)
		 //'----ȥ��ֱ������---
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
   case 3: //'����2-500��г��
		   WLS_Filter(3, 3600, TsQ, TsH);
		   //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
		   //'----ȥ��ֱ��������1��г�� ---
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
   case 4: //'����2-15��г��
		   WLS_Filter(4, 3600, TsQ, TsH);
		   //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
		   //'----ȥ��ֱ��������1��г�� ---
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
   case 5: //'�˳�2-50��г��
		   WLS_Filter(5, 3600, TsQ, TsH);
		   SumTs = 0;
		   SumTcos = 0;
		   SumTsin = 0; 
		   //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
		   //   '----ȥ��ֱ��������1��г�� ---
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
   case 6: //'�˳�2-150��г��
		   WLS_Filter(6, 3600, TsQ, TsH);
		   //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
		   //'----ȥ��ֱ��������1��г�� ---
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
   case 7:// '�˳�15-500��г��
		   WLS_Filter(7, 3600, TsQ, TsH);
		   for( i = 0;i<3600;i++)
		   {
			   drawdata[i] = TsH[i];
		   }
		 //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
	     break;
   case 8:// '�˳�3-16��г��
		   WLS_Filter(8,3600, TsQ, TsH);
		   //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
		   //'----ȥ��ֱ��������1��г��,2��г�� ---
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
   case 9:// '�˳�17-100��г��
		   WLS_Filter(9, 3600, TsQ, TsH);
		   for( i = 0;i<3600;i++)
		   {
			   drawdata[i] = TsH[i];
		   }
		 //'6�װ�����˹�˲��� TsQ(i) to TsH(i)
			break;
	}
}

/*
�������ܣ�
�˲��ϵ�ѡ�񣬽����˲�
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
	case 2: //'����1-500��г��,����2-500��г��
     FB0 = 0.9715407;
     FA11 = 0.3625683;
     FA12 = 0.1418361;
     FA21 = -0.1800023;
     FA22 = 0.04712104;
     FA31 = -0.3279947;
     FA32 = 0.03096972;
     goto JSA;
    break;
	case  3: //'����1-500��г��,����2-500��г��
	 FB0 = 0.9715407;
	 FA11 = 0.3625683;
	 FA12 = 0.1418361;
	 FA21 = -0.1800023;
	 FA22 = 0.04712104;
	 FA31 = -0.3279947;
     FA32 = 0.03096972;
     goto JSA;
   	break;
  case 4: //'����2-15��г��
	  FB0 = 0.00790757;
	  FA11 = -1.945375;
	  FA12 = 0.9534476;
	  FA21 = -1.870021;
	  FA22 = 0.877953;
	  FA31 = -1.829474;
	  FA32 = 0.8371969;
      goto JSA;  
	 break;
  case 5: //����2-50��г��
     FB0 = 0.07668238;
     FA11 = -1.766026;
     FA12 = 0.8522346;
     FA21 = -1.572835;
     FA22 = 0.6480164;
     FA31 = -1.485485;
     FA32 = 0.5550557;
     goto JSA;
	break;
 case 6: //'����2-150��г��
	 FB0 = 0.4420209;
     FA11 = -0.9900672;
     FA12 = 0.602457;
     FA21 = -0.8610914;
     FA22 = 0.2743281;
     FA31 = -0.8458274;
     FA32 = 0.1871002;
     goto JSA; 
	break;
 case 7: //'����15-500��г��
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
case 8: //'����3-16��г��
	FB0 = 0.00903713;
	FA11 = -1.940933;
	FA12 = 0.9504167;
	FA21 = -1.861476;
	FA22 = 0.8703692;
	FA31 = -1.8186;
	FA32 = 0.8273507;
     goto JSA;  
    break;
case 9: //'����17-100��г��
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
			////////////////////////////////// Բ�������Ӧ��ʾ
	if (m_BOOLSegmentprocess==0  && FlagFrequency==0 )
	{	
		CWnd *pWnd2;
		CDC  *pDC;                 // �ؼ�����Ļ��ͼ�豸ָ��
		pWnd2=GetDlgItem(IDC_JManalyse);     //��ȡ��̬���ָ��
		pDC=pWnd2->GetDC();
		CRect rect_ctr;
		this->ClientToScreen(&point);          //ת��Ϊ��Ļ����
		pWnd2->GetClientRect(&rect_ctr);       //����ı������,���Ͻ�����(0,0)   
		pWnd2->ClientToScreen(rect_ctr);       //ת������Ļ����,���Ͻ�����Ϊ�ı�������Ļ������
		
		point.x=point.x-rect_ctr.left;         //��point
		point.y=point.y-rect_ctr.top;
		double f1=(rect_ctr.right-rect_ctr.left)*3/5,f2= (rect_ctr.bottom-rect_ctr.top )/2;
		double dY0= (rect_ctr.bottom-rect_ctr.top)/2,dleft=rect_ctr.left,dtop=rect_ctr.top,dright=(rect_ctr.right-rect_ctr.left)*3/5,
			dbottom=rect_ctr.bottom,dX0=dright/2;
		CString strcodinate;	
		//rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ 
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
       		m_bDraw=TRUE;             //׼���ÿ�ʼ��ͼ
	    	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS ));
            flagmanchuli=1;	
		}
		}
  		m_zancunfinish=m_zancunOrigin=m_ptOrigin=m_ptEnd=point;	//���浱ǰ��
 
	}

    //////////////////////////////////////// Ƶ�������Ӧ��ʾ

    if(m_BOOLSegmentprocess==0  && FlagFrequency==1 )
	{
		BoolButtondown=1;
		CWnd *pWnd2;
		CDC  *pDC;                             // �ؼ�����Ļ��ͼ�豸ָ��
		pWnd2=GetDlgItem(IDC_JManalyse);     //��ȡ��̬���ָ��
		pDC=pWnd2->GetDC();
		CRect rect_ctr;
		this->ClientToScreen(&point);          //ת��Ϊ��Ļ����
		pWnd2->GetClientRect(&rect_ctr);       //����ı������,���Ͻ�����(0,0)   
		pWnd2->ClientToScreen(rect_ctr);       //ת������Ļ����,���Ͻ�����Ϊ�ı�������Ļ������
		
		point.x=point.x-rect_ctr.left;         //��point
		point.y=point.y-rect_ctr.top;

		double fw1=3*rect_ctr.Width()/5,f1=rect_ctr.Width(),f2=rect_ctr.Height();                                                 	                             
	    double fw2=rect_ctr.Width()/30;
		double fh=rect_ctr.Height()/2;
	    double fh1=rect_ctr.Height()/4;
		double fh2=rect_ctr.Height()/30;

		CString str;
		CString str1;                                           	                             
        int m_Intendstart=m_Intend-m_Intstart;
        double pointStart=rect_ctr.left-fw1-fw2*2;                 //������ʼ��
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
            
			//----------����д�����弰��С
			CFont   font; 
			font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
			DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  
			CFont*   pOldFont=(CFont*)pDC->SelectObject(&font); 
			for (i=0;i<=m_Intendstart;i++)
			{
				if ((point.x) > fw2+m_smallavescale*i &&  (point.x) <fw2+(i+1)*m_smallavescale )
				{
                  Frepointi=i;
				  Frepointx=point.x;
				  Frepointy=point.y;
				  str.Format("%.4f",XRf4[i+m_Intstart]);//��ֵΪ
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
				  
				  str1="��ǰг��:"+str1;
                  str1=str1+"  ��ֵΪ��";
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
		CWnd *pwnd=GetDlgItem(IDC_JManalyse);//��ȡ��̬���ָ��
		CDC *pDC=pwnd->GetDC();
		CRect rect_ctr;
		this->ClientToScreen(&point);  //ת��Ϊ��Ļ����
		pwnd->GetClientRect(rect_ctr);       //����ı������,���Ͻ�����(0,0)   
		pwnd->ClientToScreen(rect_ctr);       //ת������Ļ����,���Ͻ�����Ϊ�ı�������Ļ������
		
		point.x=point.x-rect_ctr.left;
		point.y=point.y-rect_ctr.top;
		
		double f1=(rect_ctr.right-rect_ctr.left)/2,f2= (rect_ctr.bottom-rect_ctr.top ) /2; 
		double theta3, dw= 2 * 3.1415926/3600;
        double dY0= (rect_ctr.bottom-rect_ctr.top )/2, dleft=0,dtop=0,dright=(rect_ctr.right-rect_ctr.left)*3/5,dbottom=rect_ctr.bottom-rect_ctr.top,dX0=dright/2;
		CString strcodinate;	
		//rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ 
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
			int nDrawmode=pDC->SetROP2(R2_NOT); //��������ͼģʽ��������ԭ����ͼģʽ 
			
			//----------------���춯̬Բ��--------------------
			{	       
				//�����ϴλ��Ƶ�Բ����
				theta1=atan2(m_zancunOrigin.y-dY0,m_zancunOrigin.x-dX0);
				theta2=atan2(m_zancunfinish.y-dY0,m_zancunfinish.x-dX0);       
				
				//������갴��theta1��̧��ʱ�ĽǶ�theta2
				
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
				
				theta3=atan2(point.y-dY0,point.x-dX0);       //������갴��theta1��̧��ʱ�ĽǶ�theta2
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
				//----------------�����µ���ʱԲ����-----------------------//
				theta1=atan2(m_zancunOrigin.y-dY0,m_zancunOrigin.x-dX0);
				theta2=atan2(point.y-dY0,point.x-dX0);       //������갴��theta1��̧��ʱ�ĽǶ�theta2
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
				m_zancunfinish=point;   //��¼��굯��ʱ�ĵ㣬�Ա��ٴλ�ͼʱ��
				OnPaint(); //��̬����
			}

			m_zancunfinish=point;   //��¼��굯��ʱ�ĵ㣬�Ա��ٴλ�ͼʱ��
			pDC->SetROP2(nDrawmode); //�ָ�ԭ��ͼģʽ 	 
			ReleaseDC(pDC); //�ͷ��豸���� 
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
		pWndJMUP=GetDlgItem(IDC_JManalyse);                           //��ȡ��̬���ָ��
		pDC=pWndJMUP->GetDC();
		pWndJMUP->GetClientRect(&rect_ctr);                             // ��ȡ����������ı��� 
		
		CWnd *pnd=GetDlgItem(IDC_JManalyse);                       //��ȡ��̬���ָ��
		CDC *DC=pnd->GetDC();
		CRect rect1;
		pnd->GetClientRect(&rect1);                                   // ��ȡ����������ı��� 
		
		this->ClientToScreen(&point);                                 //ת��Ϊ��Ļ����
		pWndJMUP->GetClientRect(rect_ctr);                               //����ı������,���Ͻ�����(0,0)   
		pWndJMUP->ClientToScreen(rect_ctr);                              //ת������Ļ����,���Ͻ�����Ϊ�ı�������Ļ������
		
		point.x=point.x-rect_ctr.left;
		point.y=point.y-rect_ctr.top;                                 //ʵ��point����ھ�̬�����������
		double dY0= (rect_ctr.bottom-rect_ctr.top )/2, dleft=0,dtop=0,dright=(rect_ctr.right-rect_ctr.left)*3/5,dbottom=rect_ctr.bottom-rect_ctr.top,dX0=dright/2;
		double dw=2 * 3.1415926/3600;// ÿһ�β�����Ӧ�ĽǶȼ��������;
		
		CString strcodinate;	
		//rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ 
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
			m_bDraw=FALSE;                                             //��ʱ��굯����Ӧ��ͼ
			m_zancunfinish=point;                                      //��¼��굯��ʱ�ĵ㣬�Ա��ٴλ�ͼʱ��
			theta1=atan2(m_zancunOrigin.y-dY0,m_zancunOrigin.x-dX0);
			theta2=atan2(m_zancunfinish.y-dY0,m_zancunfinish.x-dX0);       //������갴��theta1��̧��ʱ�ĽǶ�theta2
			
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
		((CMainFrame*)AfxGetMainWnd())->FilterMode=prop.m_IntFilter; //�õ��˲�ѡ���ѡ������
		((CMainFrame*)AfxGetMainWnd())->CirEvalue=prop.m_IntAlg;  //�õ�Բ����������ѡ�񷽷��ı��
		canshu();	
		//�ֶ�����������ݽ��е��ú�������
		//////////////////////////////////////////////
        BtnChuliDwon=1;
		SubAnaData (FilterMode, Resdata,GResult,GG1,GG2);	//Բ��
		//��ʾ���ƶ�
		m_Wa.Format("%.2f",m_BWD[0]); //�����ݽ��ת�����ַ�������ʽ��������ʾ�ڱ�����
		m_Wc.Format("%.2f",m_BWD[1]);
		m_Wp.Format("%.2f",m_BWD[2]);
		m_Wv.Format("%.2f",m_BWD[3]); //�����ݽ��ת�����ַ�������ʽ��������ʾ�ڱ�����
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
				
				GetDlgItem(IDC_JManalyse)->EnableWindow(false); //ʹ���ڿ�ʼ��Ӧ�����Ϣ
				((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,TRUE);
				
			}
			else  
				if(m_BOOLSegmentprocess==0  && FlagFrequency==0 && m_bIsEnable==0 )
				{
					GetDlgItem(IDC_JManalyse)->EnableWindow(true); //ʹ���ڿ�ʼ��Ӧ�����Ϣ
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
				AfxMessageBox("�������ʼλ�ú���ֹλ�ô���",MB_OK|MB_ICONERROR);
				return;
			}
			if (m_splitnumber<=0)
			{
				AfxMessageBox("����ķֶ��������0",MB_OK|MB_ICONERROR);
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
			GetDlgItem(IDC_JManalyse)->EnableWindow(true); //ʹ���ڿ�ʼ��Ӧ�����Ϣ
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

	//----------����д�����弰��С


	memDCJM.SetBkMode(TRANSPARENT); 
	int m1=dright+dx/30;
	int meter=rectJM.Height()/70;
	double m2=dright+(rectJM.right-dright)/3+dx/30;
	double m3=dright+(rectJM.right-dright)*2/3+dx/30;
	double mid=dright+(rectJM.right-dright)/3+dx/30;

 
	if (FlagBogao==0)
	{
		    //------------------------------------------------------------
		memDCJM.FillSolidRect(dright,0+rectJM.top,dx,dy,RGB(232,232,232));//��ͷ�������ɫ
	    memDCJM.FillSolidRect(dright,dy*5+rectJM.top,dx,dy,RGB(232,232,232));//��ָ���������ɫ
		memDCJM.FillSolidRect(dright,dy*9+rectJM.top,dx,dy,RGB(232,232,232));//��ָ���������ɫ	
		

		memDCJM.FillSolidRect(dright,dy*6+rectJM.top,gridRect.right-1*m_penScale,dy,RGB(255,255,255));			
		memDCJM.TextOut(m2,dy*6+rectJM.top+meter,m_strMethod); 		
		memDCJM.TextOut(m2,dy*7+rectJM.top+meter,"Gaussian");
 		memDCJM.TextOut(m2,dy*8+rectJM.top+meter,m_strlvbo);	
		memDCJM.TextOut(mid ,meter+rectJM.top,"Բ�Ȳ������");

		memDCJM.TextOut(mid,dy*5+rectJM.top+meter," �������� ");
		memDCJM.TextOut(mid,dy*9+rectJM.top+meter," �������� ");

		memDCJM.TextOut(m1,dy+meter+rectJM.top,"�ļ���");
		memDCJM.TextOut(m1,dy*2+meter+rectJM.top,"����ʱ��");  
		memDCJM.TextOut(m1,dy*6+meter+rectJM.top,"��������");
		memDCJM.TextOut(m1,dy*7+meter+rectJM.top,"�˲�������");                                              
		memDCJM.TextOut(m1,dy*8+meter+rectJM.top,"�˲���Χ");    
                                                 
		memDCJM.TextOut(m1,dy*10+meter+rectJM.top,"Բ��");
		memDCJM.TextOut(m1,dy*11+meter+rectJM.top,"ƫ��");
		memDCJM.TextOut(m1,dy*12+meter+rectJM.top,"ƫ�ĽǶ�");             
        memDCJM.TextOut(m1,dy*13+meter+rectJM.top,"�Ŵ���");
		memDCJM.TextOut(m1,dy*14+meter+rectJM.top,"ÿ��");  
		CString str;	
		str.Format("%.2f",5000/(ratio*5));
		memDCJM.TextOut(m2,dtop+dy*14+meter,str);		
		str.Format("%d",(int)(ratio*5));
		memDCJM.TextOut(m2,dtop+dy*13+meter,str);	
		//��ʾ�ļ���
		//CString str;
		str=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
		int num=str.ReverseFind('\\');
		str=str.Right(str.GetLength()-num-1);
		memDCJM.TextOut((m1+m2)/2,dy*1+meter+rectJM.top,str);
		//��ʾ����ʱ��
		str=m_time.Format("%Y-%m-%d %H:%M");
		memDCJM.TextOut((m1+m2)/2,dy*2+meter+rectJM.top,str);
		memDCJM.TextOut(m3,dy*10+meter+rectJM.top,"   um");
		memDCJM.TextOut(m3,dy*11+meter+rectJM.top,"   um");
	//	memDCJM.TextOut(m3,dy*12+meter+rectJM.top,"   ��");
        memDCJM.TextOut(m3,dy*13+meter+rectJM.top,"   ��");
		memDCJM.TextOut(m3,dy*14+meter+rectJM.top,"   um");
	
		if (CirEvalue==0) //��С���˷�
		{
		memDCJM.TextOut(m2,dy*10+meter+rectJM.top,m_strdRONT);
		memDCJM.TextOut(m2,dy*11+meter+rectJM.top,m_strdEcc);
		memDCJM.TextOut(m2,dy*12+meter+rectJM.top,m_strdEccPos);
		memDCJM.TextOut(m3,dy*12+meter+rectJM.top,"   ��");
			
			if (FilterMode==8 || FilterMode==9)
		{
			//��ʾ���ƶ�
            memDCJM.FillSolidRect(dright,dy*15+rectJM.top,gridRect.right-1,dy,RGB(232,232,232));
			memDCJM.TextOut(m2,dy*15+meter+rectJM.top,"���ƶ�");
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
		
		else if (CirEvalue==1)//��С����
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
			//������з�����Բ�����
			memDCJM.TextOut(m2,dy*10+meter+rectJM.top,m_MICRONT);
			memDCJM.TextOut(m2,dy*11+meter+rectJM.top,m_strdEcc);
//		    memDCJM.TextOut(m2,dy*12+meter+rectJM.top,m_strdEccPos);
		}

		//------------------------------------------------------------
		for(int m=0;m<=gridxnums;m++) //����gridxnums������                      
		{
			memDCJM.MoveTo(dright+m*dx,gridRect.bottom);
			memDCJM.LineTo(dright+m*dx,rectJM.top);
		}
			
		for(int n=0;n<=gridynums;n++) //����gridynums������                        
		{
			memDCJM.MoveTo(dright,n*dy+rectJM.top);
			memDCJM.LineTo(rectJM.left+rectJM.Width(),n*dy+rectJM.top);
		}
    
		memDCJM.MoveTo(dright,rectJM.top);
		memDCJM.LineTo(dright,rectJM.bottom);

		memDCJM.MoveTo(rectJM.right,dtop);
		memDCJM.LineTo(rectJM.right,dbottom);
	}
	///////////////////////////////////////////////////////////����������ʾ
	if (FlagBogao==1)
	{
		memDCJM.FillSolidRect(dright,dtop,gridRect.Width(),dy,RGB(232,232,232));//��ͷ�������ɫ

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
		
		//��ʾ����
		memDCJM.TextOut(dright+rectJM.Width()/10,+rectJM.top+meter,"���߷������(��um,�ң���)");
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
// 	CPen gridPen(0,0,RGB(0,0,20)); //�����ߵ���ɫ
// 	memDCJM.FillSolidRect(dright+dx,dy*12,dx,dy,RGB(139,216,224));//��ָ�����������ɫ
//     CPen *oldpen=memDCJM.SelectObject(&gridPen);
	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	CPen *oldpen=memDCJM.SelectObject(&RectPen);    

	
    //------------------------------------------------------------
	memDCJM.FillSolidRect(dright,0+rectJM.top,dx,dy,RGB(232,232,232));//��ͷ�������ɫ
	memDCJM.FillSolidRect(dright,dy*5+rectJM.top,dx,dy,RGB(232,232,232));//��ָ���������ɫ
	memDCJM.FillSolidRect(dright,dy*9+rectJM.top,dx,dy,RGB(232,232,232));//��ָ���������ɫ




	memDCJM.SetBkMode(TRANSPARENT); 
	int m1=dright+rectJM.Width()/100;
	int meter=rectJM.Height()/70;
	double m2=dright+dx/2-rectJM.Width()/20;
	double m3=dright+dx-rectJM.Width()/15;
	double mid=dright+dx/2-rectJM.Width()/20;
	int m_endstart=m_endposition-m_startposition;
	double m_splitmark=m_endstart/m_splitnumber;
 
	//��Բ�ȼ���Ľ����Ϣ��ʾ�ڱ����Ӧ��λ���ϣ��˴���ʾ��Ϣ�У�Բ�ȡ�ƫ�ġ�ƫ�Ľ�

	memDCJM.FillSolidRect(dright,dy*6+rectJM.top,dx,dy,RGB(255,255,255));
	memDCJM.TextOut(m2,dy*6+meter+rectJM.top,m_strMethod);
	memDCJM.TextOut(m2,dy*7+meter+rectJM.top,"Gaussian");
	memDCJM.TextOut(m2,dy*8+meter+rectJM.top,m_strlvbo);

	memDCJM.TextOut(mid ,meter+rectJM.top,"Բ�Ȳ������");
	memDCJM.TextOut(mid,dy*5+meter+rectJM.top," ��������");
	memDCJM.TextOut(m1+rectJM.Width()/10,dy*9+meter+rectJM.top,"�ֶ�Բ������(��:����:um)");

    memDCJM.TextOut(m1,dy+meter+rectJM.top,"�ļ���");
	memDCJM.TextOut(m1,dy*2+meter+rectJM.top,"����ʱ��");
	memDCJM.TextOut(m1,dy*6+meter+rectJM.top,"��������");                                       
	memDCJM.TextOut(m1,dy*7+meter+rectJM.top,"�˲�������");                                              
	memDCJM.TextOut(m1,dy*8+meter+rectJM.top,"�˲���Χ");   
                                                
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDCJM.TextOut((m1+m2)/2,dy*1+meter+rectJM.top,str);
	//��ʾ����ʱ��
	str=m_time.Format("%Y-%m-%d %H:%M");
	memDCJM.TextOut((m1+m2)/2,dy*2+meter+rectJM.top,str);
	int i;
	CString strsplit;
	for (i=0;i<m_splitnumber;i++)
	{
		strsplit.Format("%d",i+1);
		strsplit="��"+strsplit+"�η�Χ:";
		memDCJM.TextOut(m1,dy*(10+i)+meter+rectJM.top,strsplit);
		memDCJM.TextOut(m3-rectJM.Width()/15,dy*(10+i)+meter+rectJM.top,"P+V=");
	}
	
	CString strstart;
		CString strend;
		CString strstartend;
		for(i=0;i<m_splitnumber;i++)   //������ʾÿ�η�Χ
		{
			strstart.Format("%.1f",m_splitmark*i+m_startposition);
			strend.Format("%.1f",m_splitmark*(i+1)+m_startposition);	
			//strstartend=strstart+"��- "+strend+"��";
			strstartend=strstart+"-"+strend;
            memDCJM.TextOut(m1+100*m_penScale,dy*(10+i)+meter+rectJM.top,strstartend);	
		}



	//------------------------------------------------------------

	for(int m=0;m<=gridxnums;m++) //����gridxnums������                      
	{
		memDCJM.MoveTo(dright+m*dx,gridRect.bottom);
		memDCJM.LineTo(dright+m*dx,rectJM.top);
	}
		
	for(int n=0;n<=gridynums;n++) //����gridynums������                        
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
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  	
	CFont*   pOldFont=(CFont*)memDCJM.SelectObject(&font); 
	ReadDataFromFile();
	
	//������潫Ҫ�õ��ı���
    double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left ,dbottom=rectJM.bottom,dX0=rectJM.Width()*(3/5)/2;
	double fw1=3*rectJM.Width()/5,f1=rectJM.Width(),f2=rectJM.Height();                                                 	                             
    double fw2=rectJM.Width()/30;
    double fh=rectJM.Height()/2+rectJM.top;
	double fh1=rectJM.Height()/4;
	double fh2=rectJM.Height()/30;
	
	CPen newPen;         
	newPen.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&newPen); 

	memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh); // ����,����
    memDCJM.LineTo(fw2*3/2+rectJM.left,fh); 

	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);//�������
    memDCJM.LineTo(fw2*3/2+rectJM.left,fh+fh2*7); 

	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);  //��߼�ͷ
    memDCJM.LineTo(fw2*3/2+rectJM.left-6*m_penScale,fh-fh2*7+fh2*0.4); 
	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);  
    memDCJM.LineTo(fw2*3/2+rectJM.left+6*m_penScale,fh-fh2*7+fh2*0.4); 

	memDCJM.TextOut(fw2+rectJM.left,fh-fh1-20*m_penScale,"��λ��΢��");	

	memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh+fh2*7);
	memDCJM.LineTo(fw2*3/2+rectJM.left,fh+fh2*7);

	

    int m_endstart=m_endposition-m_startposition;
	CString mark;
	double m_avescale=(fw1-2*fw2)/4;
	double m_smallavescale=(fw1-2*fw2)/(m_splitnumber*5);
	double m_splitave=(fw1-2*fw2)/m_splitnumber;
	double m_splitmark=m_endstart/m_splitnumber;
    
	int i;
	/////////////////////////////////// ��ע������ ////////
	for(i=0;i<m_splitnumber*5;i++)    //дX��С�̶�ֵ
	{
		memDCJM.MoveTo(fw2*3/2+rectJM.left+m_smallavescale*i,fh+fh2*7);
		memDCJM.LineTo(fw2*3/2+rectJM.left+m_smallavescale*i,fh+fh2*7-fh/50);
	}

	CPen newPenfenduan;         
	newPenfenduan.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&newPenfenduan); 


	for(i=0;i<=m_splitnumber;i++)    //���ֶ���,X��̶�ֵ
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
	//////////////�����ͼ���������ֵ����Сֵ//////////////
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


	CPen newPeny;  // ����ƽ����
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


	mark.Format("%.2f",m_Middle);   //ת�������ֵ��Y����������ʾ
	memDCJM.TextOut(fw2*1/3,fh-fh*1/60,mark);

	mark.Format("%.2f",m_datamax-m_Middle);   //��Y����ֵ��ʾ
	memDCJM.TextOut(fw2*1/3,fh-fh2*5-fh*1/60,mark);

	mark.Format("%.2f",m_datamin-m_Middle);   //��Y����ֵ��ʾ
	memDCJM.TextOut(fw2*1/3,fh+fh2*5-fh*1/60,mark);
	
	double m_aveangle=3600/360;
	double m_startpoint=m_aveangle*m_startposition;
	double m_endpoint=m_aveangle*m_endposition;
    double m_endstartpiont=m_endpoint-m_startpoint;
	double m_avesize=(fw1-2*fw2)/m_endstartpiont;
	double meter=10;//�������

	for (i=m_startpoint+10;i<m_endpoint;i=i+5)//��ʾͼ��
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


	////////////////////////////////// ����ֶδ����������Сֵ ///

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
	if (IDOK==MessageBox("ȷ��Ҫɾ���ý�����","ɾ����ʾ",MB_OKCANCEL))
	{
		if (IDOK==MessageBox("�Ƿ񱣴�ɾ��ԭʼ���ݣ�","ɾ����ʾ",MB_OKCANCEL))
		{
			int ret=0;
			ret=DeletePartOfFile(path1,m_LBtnJM+1,TRUE);
			switch(ret) 
			{
			case 1: 
				AfxMessageBox("ɾ���Ľ���С��1");
				break;
			case 2: 
				AfxMessageBox("��ͼɾ�������������λ��");
				break;
			case 3: 
				AfxMessageBox("ɾ�������ĸ���С��2");
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
				AfxMessageBox("ɾ���Ľ���С��1");
				break;
			case 2: 
				AfxMessageBox("��ͼɾ�������������λ��");
				break;
			case 3: 
				AfxMessageBox("ɾ�������ĸ���С��2");
				break;
			default:
				break;
			}
		}
	}
}

void CJMAnalyse::DrawFrequency()
{
	////��ȡ�ļ�����ͼ///
	ReadDataFromFile();
	int m_Intendstart=m_Intend-m_Intstart;
	int i=0,j=0;
	double fpdata[RecCount],datacir[RecCount],TsH[RecCount],DispAdata[RecCount];
	for (i=0;i<3600;i++)	
	{  
		fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
	}
	
	////////////////////////////////////////////////////////////////////////////////
    //�ֶ�����������ݽ��е��ú�������	

	for(i=0;i<3600;i++)		
	{ 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //����Բ�����ת��λ�ƹ�ʽ	
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
	//������潫Ҫ�õ��ı���
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

	memDCJM.MoveTo(fw1-fw2*2+m_smallavescale+rectJM.left,f2-fh2*4+rectJM.top); // X������,����
    memDCJM.LineTo(fw2+rectJM.left,f2-fh2*4+rectJM.top); 

	memDCJM.MoveTo(fw2+rectJM.left,fh2*4+rectJM.top);    //�������
    memDCJM.LineTo(fw2+rectJM.left,f2-fh2*4+rectJM.top); 


	for(i=0;i<=m_Intendstart;i++)    //дX��С�̶�ֵ
	{
		memDCJM.MoveTo(m_startmark+m_smallavescale*i+rectJM.left,f2-fh2*4+2*m_penScale+rectJM.top);
		memDCJM.LineTo(m_startmark+m_smallavescale*i+rectJM.left,f2-fh2*4-2*m_penScale+rectJM.top);
	}
	CPen newPen2;         
	newPen2.CreatePen(PS_SOLID,2*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&newPen2); 
	for(i=0;i<=m_Intendstart/5;i++)    //дX���̶�ֵ
	{
		memDCJM.MoveTo(m_startmark+m_avescale*i+rectJM.left,f2-fh2*4+4*m_penScale+rectJM.top);
		memDCJM.LineTo(m_startmark+m_avescale*i+rectJM.left,f2-fh2*4-4*m_penScale+rectJM.top);
		
	}
	
 	double m_freave=(f2-fh2*4*2)/(m_pmax-m_pmin);
    CPen PenXX;
	PenXX.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,128));
    memDCJM.SelectObject(&PenXX); 


	for (i=0;i<=m_Intendstart;i++)               //ÿ�����Ӧ�߶ȣ�����
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

	//----------����д�����弰��С
	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  
	CFont*   pOldFont=(CFont*)memDCJM.SelectObject(&font); 
	if (BoolButtondown==1)
	{
		CString str;
		CString str1;
		str.Format("%.4f",XRf4[Frepointi+m_Intstart]);//��ֵΪ
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
		
		str1="��ǰг��:"+str1;
        str1=str1+"  ��ֵΪ��";
        str1=str1+str+" um";
        memDCJM.TextOut(10,10,str1);	
		CPen newPenp;         
		newPenp.CreatePen(PS_SOLID,1,RGB(255,0,255));
		memDCJM.SelectObject(&newPenp); 
	    memDCJM.MoveTo(rectJM.left+fw2+m_smallavescale*Frepointi+m_smallavescale/2,rectJM.top+fh2*3); // X������,����
		memDCJM.LineTo(rectJM.left+fw2+m_smallavescale*Frepointi+m_smallavescale/2,rectJM.top+f2-fh2*4);
	}

}


void CJMAnalyse::DrawBaogao()
{
	////��ȡ�ļ�����ͼ///
	ReadDataFromFile();
	int i=0,j=0;
	double fpdata[RecCount],datacir[RecCount],TsH[RecCount],DispAdata[RecCount];
	for (i=0;i<3600;i++)	
	{  
		fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
	}
	
	////////////////////////////////////////////////////////////////////////////////
    //�ֶ�����������ݽ��е��ú�������	

	for(i=0;i<3600;i++)		
	{ 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //����Բ�����ת��λ�ƹ�ʽ	
	}		
	DrawFilter (FilterMode,datacir,TsH);

	for (i=0;i<RecCount;i++)
	{
		DispAdata[i]=TsH[i];
	}
  

    int X1,TempStartWZ;int TempCount;double Swi[RecCount];//���ƶ�������ƽ�ȼ��
	int X,Y;
	int M;
	int WZIndex[RecCount];//�������ཻ�ĵ��λ��
	BOOL FLAGIndex[RecCount];//�������ཻ�ĵ������
	double MaxF,TempF;
	int TempFnumber;  //TempFindex[3600]
    BOOL TempFHave;
	double MaxG,TempG;
	double SumG;
    double BWDA;    //���ƶ�����ƽ��ƫ��
	double BWDC;    //���ƶ�������ƽ�ȵ�ƽ���߶�
	BOOL EndFlag;
	
	//BOOL BGlist.Clear=True,Glist.Visible=True;
	//int ABIndex;
	int DaNumberA=RecCount;
	int ZeroNumber=0;
    //  1---�����������ཻ�ĵ�
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

		if (DispAdata[X] <=0  && DispAdata[Y]>0 )  //�ɸ�����
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
			if (DispAdata[X] >=0  &&  DispAdata[Y]<0 ) //�����为
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
	int TempRadiusA =0; //Pi * X * 1000;// 'Բ�ܳ��ȼ�����ȡ������
	                                   // X �����ֱ��,��λ:����

	for (i=1;i<=ZeroNumber;i++)
	{
		if (FLAGIndex[i]==TRUE)
		{
			Swi[i] = (TempRadiusA * (WZIndex[i] - X1)) / 1024;//TempRadiusAԲ�ܳ��ȼ�����ȡ������-
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
 
//////////////////   2---����������
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

		if (FLAGIndex[i] == TRUE) //�ɸ�����,Ϊ������
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
	
	///////////////////////  3--��ʾ���ҵ��������� 
 
   ///////////////////////   4---������ʾ���ҵ���������
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

   
  ////////////////////////5---�������ʾ���ҵ���������,���100��
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
	//CPen gridPen(0,0,RGB(0,0,20)); //�����ߵ���ɫ
	CPen gridPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDCJM.FillSolidRect(dright+dx,dy*12,dx,dy,RGB(139,216,224));//��ָ�����������ɫ
    CPen *oldpen=memDCJM.SelectObject(&gridPen);
	
    //------------------------------------------------------------
	memDCJM.FillSolidRect(dright,0,dx,dy,RGB(232,232,232));//��ͷ�������ɫ
	memDCJM.FillSolidRect(dright,dy*5,dx,dy,RGB(232,232,232));//��ָ���������ɫ
	memDCJM.FillSolidRect(dright,dy*13,dx,dy,RGB(232,232,232));//��ָ���������ɫ


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

	memDCJM.TextOut(mid ,meter,"Բ�Ȳ������");
	memDCJM.TextOut(mid,dy*5+meter," ��������");
	memDCJM.TextOut(mid,dy*13+meter," ��������");
	
    memDCJM.TextOut(m1,dy+meter,"�ļ���");
	memDCJM.TextOut(m1,dy*2+meter,"����ʱ��");
	memDCJM.TextOut(m1,dy*6+meter,"��������");                                       
	memDCJM.TextOut(m1,dy*7+meter,"�˲�������");                                              
	memDCJM.TextOut(m1,dy*8+meter,"�˲���Χ");    
	
	memDCJM.TextOut(m1,dy*14+meter,"Բ��");
	memDCJM.TextOut(m1,dy*15+meter,"ƫ��");
	memDCJM.TextOut(m1,dy*16+meter,"ƫ�ĽǶ�");  
	memDCJM.TextOut(m2,dy*14+meter,m_strdRONT);
	memDCJM.TextOut(m2,dy*15+meter,m_strdEcc);
	memDCJM.TextOut(m2,dy*16+meter,m_strdEccPos);
	memDCJM.TextOut(m3,dy*14+meter,"   um");
	memDCJM.TextOut(m3,dy*15+meter,"   um");
	memDCJM.TextOut(m3,dy*16+meter,"   ��");
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDCJM.TextOut((m1+m2)/2,dy*1+meter,str);
	//��ʾ����ʱ��
	str=m_time.Format("%Y-%m-%d %H:%M");
	memDCJM.TextOut((m1+m2)/2,dy*2+meter,str);
		//------------------------------------------------------------
	for(int m=0;m<=gridxnums;m++) //����gridxnums������                      
	{
		memDCJM.MoveTo(dright+m*dx,gridRect.bottom);
		memDCJM.LineTo(dright+m*dx,0);
	}
		
	for(int n=0;n<=gridynums;n++) //����gridynums������                        
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
  ��������:���㲨�ƶ�
  ��������7��������������ʾ�ڱ�����
*/
void CJMAnalyse::BWDANA(double *Direc)
{
   //A�� =0
   //Դ��������BWDAdata( 0 To DaNumberA - 1)
   //���ڲ���  �߸���������
   //BWDA-'���ƶ�����ƽ��ƫ��
   //BWDC-'���ƶ�������ƽ�ȵ�ƽ���߶�
   //ZeroNumber-'�������ཻ�ĵ�ĸ���
  
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
       //1---�����������ཻ�ĵ�
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

           if ((BWDAdata[X]<=0) && (BWDAdata[Y]>0)) //�ɸ�����
           {
			  if (BWDAdata[i]<= 0)
			  {
				  i = Y;
				  ZeroNumber = ZeroNumber + 1;
			      WZIndex[ZeroNumber] = i;
			      FLAGIndex[ZeroNumber]= 1;
			  }
		   }
		   else if ((BWDAdata[X]>=0) && (BWDAdata[Y]<0))//�����为
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
       TempJgBWD[7]= (TempRadiusA*2)/ZeroNumber;//'--TempRadiusAԲ�ܳ��ȼ�����ȡ������-
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

		  if(FLAGIndex[i]==1)//'�ɸ�����,Ϊ������
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
		 else    // '�����为,Ϊ������
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

       // 1---�����������ཻ�ĵ�
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
		    // '�ɸ�����
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
		     if( (BWDBdata[X] >= 0) && (BWDBdata[Y] < 0))//'�����为
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
       //'--TempRadiusAԲ�ܳ��ȼ�����ȡ������-
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
			  // '�ɸ�����,Ϊ������
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

           else//  '�����为,Ϊ������
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
�������ܣ��Զ����ֶ�ȱ�ڴ���
�Զ�����ȱ�ڣ�
�ֶ�����ȱ�ڡ�
-----------------����˵��-------------------------
������ȱ�����ݴ���
Number     ���ݸ���
Soudata()  ����ǰ����
Resdata()  ����������
MaxIndex() ȱ�����յ��λ��
MinIndex() ȱ������ʼ���λ��

  ConstMaxQkNumber=100------�������ȱ�ڸ���
  QkZdnumber----------------ȱ���ص�����
  TempFLAGIndex-------------ȱ�ڵ������
  QkNumber------------------ȱ�ڸ���
  WZIndexP()----------------��ȱ��������ʼ���λ��
  WZIndexU()----------------��ȱ��������ʼ���λ��
  TempWZIndexPP()-----------���°������ı�ʾ���
  TempWZPL()----------------���°������뵱ǰ�ϰ������������
  TempWZPR()----------------���°������뵱ǰ�ϰ��������Ҿ���
  FLAGIndexU()--------------��ȱ�ڵ������
  FLAGIndexP()--------------��ȱ�ڵ������
  YDQKdata()----------------��ȱ�ڵ�Բ������
  KMaxValue-----------------ȱ������ʼ��λ���ж�ֵ
  KMinValue-----------------ȱ������ʼ��λ���ж�ֵ
  QKWzFlag------------------�ж�ȱ������
  for (i=0;i<3600;i++)	
	{  
		fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
	}
*/
  void CJMAnalyse::SubQKDataChuli(CString path,int JM, int Number,BOOL AutoOrManChuli, double *Soudata, double *Resdata,int m_IndexStart, int m_IndexEnd)
  { 
	  //�������
	  int     i,j,X,LX, LLX,TempStart,TempEnd;
	  int     Y, NY, NNY,iE,jE,QkNumber,GQkNumber ;
	  int      MinLI, MinRI;
	  int     TempN ,TempNA,TempNB;
	  int     MaxIndex[100],MinIndex[100],GQkorgWStart[100], GQkorgWEnd[100];
	  int     QkZdnumber,TempQKNumberU,TempQKNumberP,TempQknumber;
	  int     TempWZIndex[3600],WZIndexU[3600],WZIndexP[3600],TempWZIndexPP[3600];
	  int     TempWZPL[3600],TempWZPR[3600];
	int     TempWz1,TempWz2,TempWz3,TempWz4,GBzDot;//ȱ�ڵ��λ��1,2,3,4
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
	int     QKnumberL[100],QKnumberR[100],QKnumberr[100];//����ȱ�ڵ��±�

	//�����鸳��ֵ
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
	///////////////�ֹ��޳�//////////////////////////////
    // if( Number==0) 
    //	Exit Sub;

    //	���ļ���������������ȱ�ڸ�����ͳ��
	shuju0 ManDeal[3600];
    double gh[3600];//��ʱ�ṹ������
//	std::ifstream fin(path,std::ios::binary);
	for (i=0;i<Number;i++)
	{	
		Soudata[i]=m_dataJM[i+1+m_LBtnJM*Number].data;
		gh[i]=Soudata[i];
		ManDeal[i].data=m_dataJM[i+1+m_LBtnJM*Number].data;
		ManDeal[i].selected=m_dataJM[i+1+m_LBtnJM*Number].selected;
	} 
	
	//�ֱ�ͳ��ȱ�ڵĸ�����ȱ����ߺ�ȱ���ұߵ������±�
    int jLeft=0,jRight=0;
	for (i=0;i<Number-1;i++)
	{
		if (ManDeal[i].selected==0 && ManDeal[i+1].selected==1 )//�ֶ�ȥ���������ʼ��
		{
			QKnumberL[jLeft]=i; //����ȱ�ڵ���ʼ���±�
			jLeft=jLeft+1;
		}
		if (ManDeal[i].selected==1 && ManDeal[i+1].selected==0 )//�ֶ�ȥ���������ֹ��
		{
			QKnumberr[jRight]=i;//����ȱ�ڵ���ֹ����±�
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
    	goto  ManMode; //�ֹ��޳�
	 }

Automode:
	GLxLkFlag = true;//'����������־	
	QkNumber = 0;
    Number=3600;	  ////////////����
	TempAngle = 360.0/Number;
    TempN = 0; 
	//zpg2012-06-07
   for (i=0;i<Number;i++)
   {
	   TransData[i] = Soudata[i];//��������
   }
  //---�������ݱ仯��-------
   for (i=0;i<Number;i++)
   {
	   YDQKdata[i]=((Soudata[i]-2048)*10)/(GG1*GG2*4096); //������ת����λ��
	   if(i== Number - 1) //�������Ϊ���һ����
		   BHVdata[i]=((Soudata[0]-2048)*10)/(GG1*GG2*4096)-((Soudata[i]-2048)*10)/(GG1*GG2*4096);//�õ�һ������ȥ���һ����
	   else
		   BHVdata[i]=((Soudata[i+1]-2048)*10)/(GG1*GG2*4096)-((Soudata[i]-2048)*10)/(GG1*GG2*4096);//����Ļ�����һ������ȥ��һ����	
   }
   //---����ƽ�����ݱ仯�ʺ����ֵ��Сֵ---
   TempValueA=0,TempValueB=0, TempValueC=0,TempNA=0,TempNB=0;
   for (i=0;i<Number;i++)
   {
	    TempValueC = TempValueC + YDQKdata[i];
	   if (BHVdata[i] >=0) //���仯����0���ͼ�¼��TempValueA�У����ݸ�����¼��TempNA��
	   { 
		   TempNA=TempNA+1;
		   TempValueA=TempValueA+BHVdata[i];
	   }	
	   else if (BHVdata[i]<0) //���仯С��0���ͼ�¼��TempValueB�У����ݸ�����¼��TempNB��
	   {
		   TempNB=TempNB+1;
		   TempValueB=TempValueB+BHVdata[i];
	   }
   }
   //-----------------------------------------/////////////////////���ϴ�����VBʵ�ֵ��ԣ���ȷ
   Max = BHVdata[0]; //����仯���е�������С����
   Min = BHVdata[0];
   for (i=0;i<Number;i++)
   {
	   if (Max<BHVdata[i])
	   {
          Max = BHVdata[i];
          TempWz1 = i;  //���仯������Ӧ�����±�
	   }
	   if (Min > BHVdata[i])
       {
		   Min = BHVdata[i];
           TempWz2 = i;//��С�仯������Ӧ�����±�
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
	//���ϴ�����2012.6.28.8:25��VBУ����ȷ

  if((fabs(Max) >= ConstMinQkPHValue) && (fabs(Min) >= ConstMinQkPHValue) && (fabs(TempValueA) + (fabs(TempValueB)) >= ConstMinQkBZ) )
  {
	//'ȱ�ڱ�������������������
	//	'1. �������仯��  ����  ConstMinQkPHValue(Ϊ0.4)
	//	'2. �������仯����ƽ���仯ֵ�ı�ֵ  ����  ConstMinQkBZ(Ϊ8)
   }
   else
   { 
	   GLxLkFlag =true;
      // QkNumber = 0;
	  goto QuitA;
   }
    
  //--------------------------------------------
    //'����Ϊ�������� ����Ϊ���������������ݴ���
   // '�ж�ȱ������
   // '���������仯����Ϊ�ο�(����)���ж�ȱ��������ʼ��λ��
   // '1A---����ȱ��������ʼ���λ��(�ٶ����ߵ�͹�𲿷�)

   if ((fabs(TempValueC) > fabs(YDQKdata[TempWz1])) && (fabs(TempValueC) > fabs(YDQKdata[TempWz2])))
   {
          KMaxValue = ConstKXS1 * YDQKdata[TempWz1];
          KMinValue = ConstKXS1 * YDQKdata[TempWz2];// 'ȱ��������ʼ��λ���ж�ֵ
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
          KMinValue = ConstKXS2 * YDQKdata[TempWz2]; //'ȱ��������ʼ��λ���ж�ֵ
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
           //  '�ɸ�����
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
                 //'�����为
				 if (YDQKdata[i] >= KMaxValue)
				 {
					 i = Y;
				 }
                TempQKNumberU = TempQKNumberU + 1;
                WZIndexU[TempQKNumberU] = i;
                if(QKWzFlag == true)
				{
                  FLAGIndexU[TempQKNumberU] = false;//ԭ��Ϊfalse
				 }
				else
				{
                  FLAGIndexU[TempQKNumberU] = true;//ԭ��Ϊture
				 }			
	}
	if (EndFlag == true)
	{
		goto  CONA1A;
	}   
 }
 /////////////////////////////////////////////////////////////////////// 
  CONA1A: //'�������ڵ�
 if ((TempQKNumberU % 2) == 0 )
 {
 }
 else
 {      // '����������������
	 if(FLAGIndexU[1] == FLAGIndexU[TempQKNumberU])
	 {
             TempQKNumberU = TempQKNumberU - 1;
	 }
 }
    TempQknumber =0;		
	//��������ȱ�ڸ���Ϊ  " & TempQKNumberU
	//'1B---����ȱ��������ʼ���λ��(�ٶ����ߵİ��²���)
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
            // '�ɸ�����
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
              //   '�����为
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
 //----------------------------------6.29.15:54����˶�  
CONA2:// '�������ڵ�
    if( (TempQKNumberP % 2) == 0) 
	{
	}
	else
	{ 
	  if( FLAGIndexP[1] = FLAGIndexP[TempQKNumberP]) //'����������������
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
      //  '���ȳ���͹��Ϊ�ȵ�������Ѱ����͹����������İ�������
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
                        // '�°�����
                     TempNA = TempNA + 1;
                     TempWZIndexPP[TempNA]=j;
                     TempWz1 = WZIndexP[j];
                     TempWz2 = WZIndexP[jE];
                        //  '----A1�õ����°������뵱ǰ�ϰ������������
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
               // '----B1�õ����°������뵱ǰ�ϰ��������Ҿ���
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
      // '---A2�õ��뵱ǰ�ϰ��������������С���°�����
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
         //'---B2�õ��뵱ǰ�ϰ��������Ҿ�����С���°�����///////////2012.6.28.22:30У�Գ�����ȷ
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
          // '--�õ�����----------  
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
 	if((QkNumber==TempQKNumberU/2) && (QkNumber==TempQKNumberP/2)) //ԭ���ǵȺ�
	{
      
	}
	else
	{
         GLxLkFlag = true;
         goto QuitA;
     }
    //  '---Step-2   ����ȱ�ڸ�����������--
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
		GBzDot =(int)(GPHWidthK*((360-GQkAngle)/QkNumber)*(Number/360)+0.5);//�������뱣������
		// '������������ֵ�㷶Χ
		// 'GPHWidthK ---ȱ��֮��ƽ��������ȱ���
		if(GBzDot > Number/16)
		 GBzDot = Number/16;
		//'������䱣֤��ȥ���仯������򣬻����仯���򲻴���
		 // '-----------
		 for(i=1;i<=QkNumber;i++)
		  {
		   GQkAngle = (MaxIndex[i] - MinIndex[i]) * TempAngle;
			
	    	//	 'SJChuli.List1.AddItem "ȱ�ڽǶ�= " & (MaxIndex(i) - MinIndex(i)) * TempAngle
			//	 '----����ȱ��λ�ò�ֵ---
			//	 '-��ȱ�ڼ���--�Զ��޳�
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
			//	 '-��ȱ�ڼ���--�Զ��޳�
				 TempValueB = 0;
				 TempN = 0;
				 TempStart = MaxIndex[i]+(GBzDot-5);
				 TempEnd = MaxIndex[i]+(GBzDot+5);
			//	 'GBzDot = 20 '������������ֵ�㷶Χ
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
				  //'SJChuli.List1.AddItem "��ֵA= " & TempValueA
                  //'SJChuli.List1.AddItem "��ֵB= " & TempValueB
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

			   	    //'--�������Բ�ֵ-�Զ��޳�
					if(TempEnd > TempStart) 
					{
						for(j=TempStart;j<=TempEnd;j++)
						{
							Soudata[j] = Soudata[TempStart]+TempK*(j - TempStart);
                            ManDeal[j].selected=1;//����
						}
					}
					else 
					{
					  for(j=TempStart;j<Number;j++)
					  {	
						Soudata[j]=Soudata[TempStart]+TempK*(j-TempStart);
                        ManDeal[j].selected=1;//����
					  }
					for (j=0;j<=TempEnd;j++)
					{
	                    Soudata[j]=Soudata[TempStart]+TempK*(j + Number - TempStart);
                        ManDeal[j].selected=1;//����
					}
				}
			}
					//'-�Զ��޳�--�õ���i��Ƭ(ȱ�ڼ�)����ʼλ��,��ֹλ��----
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

        GQkWStart[i] = TempStart; //'��Ӧ�ڼ���Ƭ��ȱ�����⣩����ʼλ��
        GQkWEnd[i] = TempEnd; //'��Ӧ�ڼ���Ƭ��ȱ�����⣩����ֹλ�� 
     }		
    }
	else
	{
			GLxLkFlag =true;
		    QkNumber = 0;
	}
	
/*	int Starti,Endi;//��С�γ���ʵ�����Զ�ȥȱ���Ժ�ӳ��ͼ�ν����ϵı仯
    for( i=1;i<=QkNumber;i++)
	{
       Starti=MinIndex[i]-GBzDot;
       Endi=MaxIndex[i]+ GBzDot;
       ChangeValueOfSelectJM(path,1+m_LBtnJM*Number+Starti,1+m_LBtnJM*Number+Endi,1);
	}

*/
  		//'---Step-3   �õ��������--
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
 //  --------------------����Ϊ�Զ��޳�ȱ��----------------
 //  ------------------- ����ʵ���ֶ��޳�------------------
 /*
   Soudata()----------------------------------------- ����ǰ����
   Resdata()----------------------------------------- ����������
   QkNumber------------------------------------------'ȱ�ڸ���
   TempValueA-----------------------------------------��ֵA �仯�ʴ���0��ƽ����
   TempValueB-----------------------------------------��ֵB �仯��С��0��ƽ����
   TempN ---------------------------------------------��ֵ����
   GLxLkFlag = True-----------------------------------����������־
   ConstMaxQkNumber=100-------------------------------�������ȱ�ڸ���
   BHVdata(Number)------------------------------------�������ݱ仯��
   YDQKdata( Number)----------------------------------��ȱ�ڵ�Բ������
   TempStart & " ** " & TempEnd ----------------------��ֵ��Χ
   (MaxIndex(i) - MinIndex(i)) * TempAngle------------ȱ�ڽǶ�
   MaxIndex(ConstMaxQkNumber) ------------------------ȱ�����յ��λ��
   MinIndex(ConstMaxQkNumber)-------------------------ȱ������ʼ���λ��
   TempValueA = TempValueA + Soudata(j)---------------ȱ���ڵ����ݺ�
   TempValueA = TempValueA / TempN--------------------��ֵָȥ������������ƽ��ֵ

*/

ManMode:
	  
		TempAngle=360.0/Number;       //0.1���һ����
		TempN=0;                  //��ֵ����
		for(i=0;i<Number;i++)
		{
		   TransData[i] = Soudata[i];//	'��������
		   YDQKdata[i] = ((Soudata[i]-2048)*10)/(GG1*GG2*4096);
		}			
       //���������������ݴ���
       //Step-2   ����ȱ�ڸ�����������--
       //1D---�Ż�ȱ��λ�� '�ֶ��޳�
       QkNumber = GQkNumber=jLeft; //ȱ�ڸ���
       if(QkNumber>=1)
           GLxLkFlag =false;    //����������     
       for(i=1;i<=QkNumber;i++)
	   {
           MinIndex[i] =QKnumberL[i-1];// GQkorgWStart[i];//ȱ������ʼ���λ��,�ֶ�ȥ��ȱ��ʱ�İ��µ�
           MaxIndex[i] =QKnumberR[i-1];//GQkorgWEnd[i];//ȱ�����յ��λ�ã��ֶ�ȥ��ȱ��ʱ��̧���
	   }
       for(i=1;i<=QkNumber;i++)
	   {
           TempStart=MinIndex[i]; //��Ӧһ��ȱ�ڵ�����ʼ��
           TempEnd=MaxIndex[i];   //��Ӧһ��ȱ�ڵ�����ֹ��
           if (TempEnd>=TempStart) 
		   {
		  	   TempNA=TempEnd-TempStart;// '���������
               TempNB=Number+TempStart-TempEnd;// '���������
		   }
           else
		   {
              TempNA=Number+TempEnd-TempStart;// '���������
              TempNB=TempStart-TempEnd;// '���������
		   }
          /* if(TempNA >= TempNB) //��������ж�ÿ�δ���ֻ������ԽǶ���ת�Ƚ�С���Ǳ�
		   {
              // 'λ�ñ귴
              MinIndex[i]=TempEnd;
              MaxIndex[i]=TempStart;
		   }
        */
	   }
       GQkAngle = 0;
       for(i=1;i<=QkNumber;i++)
	   {
          if((MaxIndex[i]- MinIndex[i]) < 0)
              GQkAngle = GQkAngle + (Number + MaxIndex[i] - MinIndex[i]) * TempAngle; //�õ�ȱ�ڰ����ĽǶ�
          else
              GQkAngle = GQkAngle + (MaxIndex[i] - MinIndex[i]) * TempAngle;
	   }

       //GBzDot=GPHWidthK*((360-GQkAngle)/QkNumber)*(Number/360);//��Ӳ���ж�ȡ
       GBzDot=0;
       // '������������ֵ�㷶Χ
       // 'GPHWidthK ---ȱ��֮��ƽ��������ȱ���
       if(GBzDot>Number/16) 
		  GBzDot = Number/16;
       //'������䱣֤��ȥ���仯������򣬻����仯���򲻴���
       // if(QkNumber == 0 )
	   //  goto  Automode;
      for (i=1;i<=QkNumber;i++)//'�ֹ��޳�
	  {
		   TempValueA=0;
           TempN=0;
           TempStart=MinIndex[i]-(GBzDot+5);
           TempEnd=MinIndex[i]-(GBzDot-5);
           GQkAngle=(MaxIndex[i]- MinIndex[i]) * TempAngle;
           // ''�ֹ��޳�--��ȱ�ڼ���
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
          //TempK = (TempValueB - TempValueA) / TempN;  //��ȡƽ��ֵ
          //'-��ȱ�ڼ���--'�ֹ��޳�
			   TempValueB = 0;
			   TempN = 0;
			   TempStart = MaxIndex[i] + (GBzDot - 5);
			   TempEnd = MaxIndex[i] + (GBzDot + 5);
			   // 'GBzDot = 20 '������������ֵ�㷶Χ
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
				// ''�ֹ��޳�--
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

	      //'SJChuli.List1.AddItem "��ֵ����= " & TempN
          //'SJChuli.List1.AddItem "��ֵ��Χ: " & TempStart & " ** " & TempEnd
          TempK = (TempValueB - TempValueA) / TempN;
         if (TempEnd > TempStart) 
		  {
            for (j = TempStart;j<=TempEnd;j++)
			{
                Soudata[j]= Soudata[TempStart] + TempK * (j - TempStart); //��ȱ�ڴ����ƽ��ֵ
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
		 //  '-'�ֹ��޳�--�õ���i��Ƭ(ȱ�ڼ�)����ʼλ��,��ֹλ��----
		 GQkWStart[i] = TempStart;// '��Ӧ�ڼ���Ƭ��ȱ�����⣩����ʼλ��
		 GQkWEnd[i] = TempEnd;// '��Ӧ�ڼ���Ƭ��ȱ�����⣩����ֹλ
}	 

      double DH[3600];
       for (i = 0 ;i< Number;i++)
	   {
			 Resdata[i]= Soudata[i];
			 DH[i]=Soudata[i];
	   } 
       GQkNumber = QkNumber;

	  //  '---Step-3   �õ��������--
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
	////��ȡ�ļ�����ͼ///
	std::ifstream fin(pathJM, std::ios::binary);
   	for (int i=0;i<=LenDataJM;i++)
	{	
		fin.read((char*)&m_dataJM[i], sizeof(shuju0)); //��ȡ����
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
	int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);//X����һӢ�����صĸ���,A4ֽ
    int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);//Y����һӢ�����صĸ���
	int xLogPixPerMM=xLogPixPerInch/25.4;//X����1mm���صĸ���
	int yLogPixPerMM=yLogPixPerInch/25.4;//Y����1mm���صĸ���
	m_penScale=xLogPixPerInch/96;//�ʵı��������߱�֣�xLogPixPerInch�Ǳ�ʾA4ֽһӢ�纬�е����ظ�����96����Ļ�ģ�����Ϊ����Ļ��ֽpen����Ŵ�ı���
	
	//��ӡ��ĳߴ�Ϊ150*250(mm)
	CPoint pt(0,0);//ֽ�ŵ����Ͻ�Ϊ00��
	CSize  sz(270*xLogPixPerMM,200*yLogPixPerMM);//sz���ο�Ĵ�С��X�����Y�������ص��ܸ�������ӡ���ǰ���������ӡ��
	CRect  tRect(pt,sz);//����Ĵ�ӡ���ľ��ο���ɫ���ģ�����ҳ�߾�ģ���Ϊ00�㣬rect1�Ǳ���ľ��ο�	
	rectJM.top=tRect.top+25*yLogPixPerMM;//rect���������Ҷ��Ǳ�ʾ�����صĸ���
	rectJM.right=tRect.right;
	rectJM.left=tRect.left+20*xLogPixPerMM;
	rectJM.bottom=tRect.bottom-25*yLogPixPerMM;
	
	
	pOldBmp = NULL;                           // ���ɵ�λͼָ���ÿ�	
	memDCJM.CreateCompatibleDC(pDC);             // �����ڴ��ͼ�豸��ʹ�ڴ�λͼ��DC��ؼ���DC����
	memBitmap.CreateCompatibleBitmap(pDC,tRect.right,tRect.bottom);//����Ϊ���Ⱥ͸߶�
	pOldBmp = memDCJM.SelectObject(&memBitmap);
    memDCJM.FillSolidRect(tRect.left,tRect.top,tRect.right,tRect.bottom,RGB(255,255,255));//�����ο�����ɫ
	
	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));//ԭ����penscale=1�����ڲ���
	memDCJM.SelectObject(&RectPen);               
	memDCJM.Rectangle(rectJM.left,rectJM.top,rectJM.right,rectJM.bottom); //��̬����� ��ɫ �߿�
	
	//�޸Ĵ�ӡ�����С
	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
		DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  
	CFont*   pOldFont=(CFont*)memDCJM.SelectObject(&font); 
	
	// ȡ��ǰ�����С
	CFont *curFont = pDC->GetCurrentFont();
	LOGFONT curLogFont;
	LOGFONT newLogFont;
	
	curFont->GetLogFont( &curLogFont );
	long NewFontWidth = curLogFont.lfWidth;
	long NewFontHeight = curLogFont.lfHeight;
	newLogFont = curLogFont;
	
	//�����µ������С--��Сһ��
	newLogFont.lfWidth =(long)((float)NewFontWidth
		* ((float)xLogPixPerInch / 96.0));
	newLogFont.lfHeight =(long)((float)NewFontHeight
		* ((float)yLogPixPerInch / 96.0)); 
	
	//�����������µ����壬������ǰ������
	//CFont newFont;
	CFont *oldFont;
	
	newFont.CreateFontIndirect(&newLogFont);
	//oldFont = memDCJM.SelectObject(&newFont );
	memDCJM.SelectObject(&newFont);
	
	//��������
	memDCJM.MoveTo(rectJM.left,rectJM.top);
	memDCJM.LineTo(rectJM.left,rectJM.top-10*xLogPixPerMM);
	memDCJM.MoveTo(rectJM.left,rectJM.top-10*xLogPixPerMM);
	memDCJM.LineTo(rectJM.right,rectJM.top-10*xLogPixPerMM);
	memDCJM.MoveTo(rectJM.right,rectJM.top-10*xLogPixPerMM);
	memDCJM.LineTo(rectJM.right,rectJM.top);
	//��������
	memDCJM.MoveTo(rectJM.left,rectJM.bottom);
	memDCJM.LineTo(rectJM.left,rectJM.bottom+10*xLogPixPerMM);
	memDCJM.MoveTo(rectJM.left,rectJM.bottom+10*xLogPixPerMM);
	memDCJM.LineTo(rectJM.right,rectJM.bottom+10*xLogPixPerMM);
	memDCJM.MoveTo(rectJM.right,rectJM.bottom+10*xLogPixPerMM);
	memDCJM.LineTo(rectJM.right,rectJM.bottom);
	RectPen.DeleteObject();

	//д����Ϣ
    memDCJM.TextOut(0.8*rectJM.left+200*xLogPixPerMM,rectJM.bottom+11*yLogPixPerMM,
		"���������ž����������޹�˾");
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_strOperatorName;
	str.Format("����Ա:%s",str);
	memDCJM.TextOut(rectJM.left+75*xLogPixPerMM,rectJM.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineModel;
	str.Format("�����ͺ�:%s",str);
	memDCJM.TextOut(rectJM.left+115*xLogPixPerMM,rectJM.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineName;
	str.Format("����:%s",str);
	memDCJM.TextOut(rectJM.left+155*xLogPixPerMM,rectJM.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strProcess;
	str.Format("����:%s",str);
	memDCJM.TextOut(rectJM.left+195*xLogPixPerMM,rectJM.top-7*yLogPixPerMM,str);
	
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceModel;
	str.Format("�����ͺ�:%s",str);
	memDCJM.TextOut(rectJM.left+15*xLogPixPerMM,rectJM.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceNum;
	str.Format("�������:%s",str);
	memDCJM.TextOut(rectJM.left+75*xLogPixPerMM,rectJM.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strIndent;
	str.Format("����:%s",str);
	memDCJM.TextOut(rectJM.left+135*xLogPixPerMM,rectJM.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strInspector;
	str.Format("���Ա:%s",str);
	memDCJM.TextOut(rectJM.left+195*xLogPixPerMM,rectJM.bottom+3*yLogPixPerMM,str);

	((CMainFrame*)AfxGetMainWnd())->JMCL=BtnChuliDwon; //��굥���Ľ���	
	

	if(m_BOOLSegmentprocess==0  &&  FlagFrequency==0 )
	{	
		SubQKDataChuli(pathJM,m_LBtnJM,3600,!((CMainFrame*)AfxGetMainWnd())->m_bAutoQK,m_CirCal, Resdata,m_IndexStart,m_IndexEnd);
		if (CirEvalue==0)
		{
		    PrintJMofYZD();
			SubAnaData (FilterMode, Resdata,GResult,GG1,GG2);	//Բ��
			dRONT=GResult[1];
			SubAnaData(1,  Resdata,GResult,GG1,GG2);    //1
			dEcc=GResult[1]/2;  //ƫ��
			dEccPos=GResult[3];  //ƫ�Ľ�
			
			m_strFilterMode.Format("%d",FilterMode);
			m_strdRONT.Format("%.3f",dRONT); //�����ݽ��ת�����ַ�������ʽ��������ʾ�ڱ�����
			m_strdEcc.Format("%.2f",dEcc);
			m_strdEccPos.Format("%.2f",dEccPos);
			//��ʾ���ƶ�
			m_Wa.Format("%.2f",m_BWD[0]); //�����ݽ��ת�����ַ�������ʽ��������ʾ�ڱ�����
			m_Wc.Format("%.2f",m_BWD[1]);
			m_Wp.Format("%.2f",m_BWD[2]);
			m_Wv.Format("%.2f",m_BWD[3]); //�����ݽ��ת�����ַ�������ʽ��������ʾ�ڱ�����
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
	pDC->BitBlt(tRect.left,tRect.top,tRect.right,tRect.bottom,&memDCJM,0,0,SRCCOPY); //���Ѿ���õ�ͼ��ʾ���ƶ�λ����
	memDCJM.SelectObject(pOldBmp);
	memDCJM.DeleteDC();
    memBitmap.DeleteObject();//�ͷ��ڴ��豸// TODO: Add your specialized code here and/or c


}

void CJMAnalyse::PrintSegmentationprocess()
{
// 	CFont   font; 
// 	font.CreateFont(13,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
// 	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  	
// 	CFont*   pOldFont=(CFont*)memDCJM.SelectObject(&font); 
	memDCJM.SelectObject(&newFont);
	ReadDataFromFile();
	
	//������潫Ҫ�õ��ı���
    double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left ,dbottom=rectJM.bottom,dX0=rectJM.Width()*(3/5)/2;
	double fw1=3*rectJM.Width()/5,f1=rectJM.Width(),f2=rectJM.Height();                                                 	                             
    double fw2=rectJM.Width()/30;
    double fh=rectJM.Height()/2+rectJM.top;
	double fh1=rectJM.Height()/4;
	double fh2=rectJM.Height()/30;
	
	CPen newPen;         
	newPen.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&newPen); 

	memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh); // ����,����
    memDCJM.LineTo(fw2*3/2+rectJM.left,fh); 

	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);//�������
    memDCJM.LineTo(fw2*3/2+rectJM.left,fh+fh2*7); 

	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);  //��߼�ͷ
    memDCJM.LineTo(fw2*3/2+rectJM.left-6*m_penScale,fh-fh2*7+fh2*0.4); 
	memDCJM.MoveTo(fw2*3/2+rectJM.left,fh-fh2*7);  
    memDCJM.LineTo(fw2*3/2+rectJM.left+6*m_penScale,fh-fh2*7+fh2*0.4); 

	memDCJM.TextOut(fw2+rectJM.left,fh-fh1-20*m_penScale,"��λ��΢��");	

	memDCJM.MoveTo(fw1-fw2*1/2+rectJM.left,fh+fh2*7);
	memDCJM.LineTo(fw2*3/2+rectJM.left,fh+fh2*7);

	

    int m_endstart=m_endposition-m_startposition;
	CString mark;
	double m_avescale=(fw1-2*fw2)/4;
	double m_smallavescale=(fw1-2*fw2)/(m_splitnumber*5);
	double m_splitave=(fw1-2*fw2)/m_splitnumber;
	double m_splitmark=m_endstart/m_splitnumber;
    int i;

	/////////////////////////////////// ��ע������ ////////
	for(i=0;i<m_splitnumber*5;i++)    //дX��С�̶�ֵ
	{
		memDCJM.MoveTo(fw2*3/2+rectJM.left+m_smallavescale*i,fh+fh2*7);
		memDCJM.LineTo(fw2*3/2+rectJM.left+m_smallavescale*i,fh+fh2*7-fh/50);
	}

	CPen newPenfenduan;         
	newPenfenduan.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    memDCJM.SelectObject(&newPenfenduan); 


	for(i=0;i<=m_splitnumber;i++)    //���ֶ���,X��̶�ֵ
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
	//////////////�����ͼ���������ֵ����Сֵ//////////////
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


	CPen newPeny;  // ����ƽ����
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


	mark.Format("%.2f",m_Middle);   //ת�������ֵ��Y����������ʾ
	memDCJM.TextOut(rectJM.left+fw2*1/3,fh-fh*1/60,mark);

	mark.Format("%.2f",m_datamax-m_Middle);   //��Y����ֵ��ʾ
	memDCJM.TextOut(rectJM.left+fw2*1/3,fh-fh2*5-fh*1/60,mark);

	mark.Format("%.2f",m_datamin-m_Middle);   //��Y����ֵ��ʾ
	memDCJM.TextOut(rectJM.left+fw2*1/3,fh+fh2*5-fh*1/60,mark);
	
	double m_aveangle=3600/360;
	double m_startpoint=m_aveangle*m_startposition;
	double m_endpoint=m_aveangle*m_endposition;
    double m_endstartpiont=m_endpoint-m_startpoint;
	double m_avesize=(fw1-2*fw2)/m_endstartpiont;
	double meter=10;//�������

	for (i=m_startpoint+10;i<m_endpoint;i=i+5)//��ʾͼ��
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


	////////////////////////////////// ����ֶδ����������Сֵ ///

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
	//CPen gridPen(0,0,RGB(0,0,20)); //�����ߵ���ɫ
	CPen gridPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDCJM.FillSolidRect(dright+dx,dy*12+rectJM.top,dx,dy,RGB(139,216,224));//��ָ�����������ɫ
    CPen *oldpen=memDCJM.SelectObject(&gridPen);
	
	memDCJM.SelectObject(&newFont);
	
    //------------------------------------------------------------
	memDCJM.FillSolidRect(dright,0+rectJM.top,dx,dy,RGB(232,232,232));//��ͷ�������ɫ
	memDCJM.FillSolidRect(dright,dy*5+rectJM.top,dx,dy,RGB(232,232,232));//��ָ���������ɫ
	memDCJM.FillSolidRect(dright,dy*13+rectJM.top,dx,dy,RGB(232,232,232));//��ָ���������ɫ
	
	
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
	
	memDCJM.TextOut(mid ,meter+rectJM.top,"Բ�Ȳ������");
	memDCJM.TextOut(mid,dy*5+meter+rectJM.top," ��������");
	memDCJM.TextOut(mid,dy*13+meter+rectJM.top," ��������");
	
    memDCJM.TextOut(m1,dy+meter+rectJM.top,"�ļ���");
	memDCJM.TextOut(m1,dy*2+meter+rectJM.top,"����ʱ��");
	memDCJM.TextOut(m1,dy*6+meter+rectJM.top,"��������");                                       
	memDCJM.TextOut(m1,dy*7+meter+rectJM.top,"�˲�������");                                              
	memDCJM.TextOut(m1,dy*8+meter+rectJM.top,"�˲���Χ");    
	
	memDCJM.TextOut(m1,dy*14+meter+rectJM.top,"Բ��");
	memDCJM.TextOut(m1,dy*15+meter+rectJM.top,"ƫ��");
	memDCJM.TextOut(m1,dy*16+meter+rectJM.top,"ƫ�ĽǶ�");  
	memDCJM.TextOut(m2,dy*14+meter+rectJM.top,m_strdRONT);
	memDCJM.TextOut(m2,dy*15+meter+rectJM.top,m_strdEcc);
	memDCJM.TextOut(m2,dy*16+meter+rectJM.top,m_strdEccPos);
	memDCJM.TextOut(m3,dy*14+meter+rectJM.top,"   um");
	memDCJM.TextOut(m3,dy*15+meter+rectJM.top,"   um");
	memDCJM.TextOut(m3,dy*16+meter+rectJM.top,"   ��");
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDCJM.TextOut((m1+m2)/2,dy*1+meter+rectJM.top,str);
	//��ʾ����ʱ��
	str=m_time.Format("%Y-%m-%d %H:%M");
	memDCJM.TextOut((m1+m2)/2,dy*2+meter+rectJM.top,str);
	//------------------------------------------------------------
	memDCJM.SelectObject(&gridPen);
	for(int m=0;m<=gridxnums;m++) //����gridxnums������                      
	{
		memDCJM.MoveTo(dright+m*dx,gridRect.bottom);
		memDCJM.LineTo(dright+m*dx,rectJM.top);
	}
	
	for(int n=0;n<=gridynums;n++) //����gridynums������                        
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

    LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//��ӦԲ�����еĵ���
    m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//��굥��ѡ�еĽ���
	pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;
 
	std::ifstream fin(pathJM, std::ios::binary);
   	for ( i=0;i<=LenDataJM;i++)
	{	
		fin.read((char*)&m_dataJM[i], sizeof(shuju0)); //��ȡ����
	}
	fin.read((char*)&GG1,sizeof(double));
	fin.read((char*)&GG2,sizeof(double));
	fin.read((char*)&m_time,sizeof(CTime));
    fin.close();
  
	//������潫Ҫ�õ��ı���
    double dY0= rectJM.Height()/2+rectJM.top,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5*1/2+rectJM.left;
	CString strcodinate;
	//rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ
	int x1,y1,x2,y2;
	double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	dw=2*PI/3600;

	//���Ƶ�ɫԲ����
    CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //���ƻ�ɫԲ���� 
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

	CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //����Բ������ɫ�� 
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
   	//----------���춯̬Բ��---------
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
	
	//----------------------���ϴ���ʵ������ѡȡ-----------
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));     //�����ջ�ˢ����ֹ�ڵ���
	CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//ѡ��ˢ 
	//double Rmincir=dX0/2-100;
    double Rmincir=rin*5/12;
	CPen pencir;
	pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
    memDCJM.SelectObject(&pencir);   
    memDCJM.Ellipse(dX0-RSLC,dY0-RSLC,dX0+RSLC,dY0+RSLC);//���ƻ�Բ(2048)
	pencir.DeleteObject();	
	
	CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	memDCJM.SelectObject(&RoutORin);               
    memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//����Բ����Բ
    memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//����Բ����Բ
    RoutORin.DeleteObject();
   
	///////////////////////////////////////////////////////////////////
	///////////////////////����������//////////////////////////////////
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
    memDCJM.LineTo(dX0+EverystrcodX*10,dY0);                    //����x��
	memDCJM.MoveTo(dX0-EverystrcodX*10,dY0-10); 
	memDCJM.LineTo(dX0-EverystrcodX*10,dY0+10);
	memDCJM.MoveTo(dX0+EverystrcodX*10,dY0-10); 
	memDCJM.LineTo(dX0+EverystrcodX*10,dY0+10);
	//memDCJM.TextOut(dX0+EverystrcodX*10+10,dY0-10,"0��");
	//memDCJM.TextOut(dX0-rout-40,dY0-10,"180��");
	memDCJM.TextOut(dX0+rout*1.05,dY0-rout*0.025,"0��");
	memDCJM.TextOut(dX0-rout*1.15,dY0-rout*0.025,"180��");
	
	memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45��");
	memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225��");

    memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
    memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //����y��
    memDCJM.MoveTo(dX0+10,dY0+EverystrcodY*10);
   	memDCJM.LineTo(dX0-10,dY0+EverystrcodY*10);
	memDCJM.MoveTo(dX0+10,dY0-EverystrcodY*10);
   	memDCJM.LineTo(dX0-10,dY0-EverystrcodY*10);
	//memDCJM.TextOut(dX0-10,dY0+EverystrcodY*10+10,"270��");
    //memDCJM.TextOut(dX0-10,dY0-EverystrcodY*10-30,"90��");
	memDCJM.TextOut(dX0-rout*0.026,dY0+rout*1.04,"270��");
    memDCJM.TextOut(dX0-rout*0.026,dY0-rout*1.1,"90��");
	memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135��");
    memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315��");

	
	for( i=0; i<10; i++)
	{
		strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //����X����̶�
		memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	}	
	for( i=0; i<10; i++)
	{
		strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //����X����̶�
		memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	}
	for( i=0; i<10; i++)      //дY����̶�ֵ
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
    //�ڼ�����������Ǵ��ݹ�����///////////////////���������M;
	for (i=0;i<3600;i++)	
	{  
		fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		m_CirCal[i]=fpdata[i];    //����Բ�����ת��λ�ƹ�ʽ		
	}	
	////////////////////////////////////////////////////////////////////////////////
    //�ֶ�����������ݽ��е��ú�������	
	for(i=0;i<3600;i++)		
	{ 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //����Բ�����ת��λ�ƹ�ʽ	
	}		
	DrawFilter (FilterMode,datacir,dataafterfilter);//�����˲��������˲�֮������ݷ�ӳ�ڽ��������
	//////////////////////////////////////////////////
	//////////////�����ͼ���������ֵ����Сֵ//////////////
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
	//////////////////////��������ĺᡢ������///////////////////////////////
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
		datas[i]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(dataafterfilter[i]-m_Middle)*ratio*0.2*5/(rectJM.Height()*0.4/10)+RSLC; //����Բ�ȴ��ʱ��������ʾ
		//datas[i]=(dataafterfilter[i]-m_Middle)*(rout-rin-20)/m_OutIn+RSLC; //����Բ�ȴ��ʱ��������ʾ	
		//datas[i]=(dataafterfilter[i]-m_Middle)*ratio*5/(rectJM.Height()*0.4/10)+RSLC;
		drealx[i]=datas[i]*cos(i*dw)+dX0;
		drealy[i]=datas[i]*sin(i*dw)+dY0;//ʵ�������ĺᡢ������(����ڶ���Բ��)
	}		
	///////////////////////////////////////////////////////
    m_Intstep=5;//�����������
	CPen penreal;
	penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));    
	CPen pendeal;
	pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));    
	
	for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	{ 
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{  
		   memDCJM.SelectObject(&pendeal);
		   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//��ɫ���߱�ʾ�ֶ���������
		   memDCJM.MoveTo(drealx[i], drealy[i]);
		   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);	
		
		}
		else
		{
			memDCJM.SelectObject(&penreal);
			memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//��ɫ���߱�ʾʵ������
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
			    memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//��ɫ���߱�ʾʵ������
		    	memDCJM.MoveTo(drealx[i], drealy[i]);
			    memDCJM.LineTo(drealx[0], drealy[0]);	
			}
			else
			{
				memDCJM.SelectObject(&penreal);
				memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//��ɫ���߱�ʾʵ������
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
	double tr=2 * 3.1415926/36;// ÿһ�β�����Ӧ�ĽǶȼ��������
	double wzd=asin(6*m_penScale/m_maxRTriangle); //ÿ�������εĵױ���������ڶ������ת�Ƕ�
	
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
	//ͼ����ʾ��ע˵��
	CString m_SelectJM,m_TotalJM;

    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);

	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"��������:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"��ǰ����:");
	
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+10*m_penScale,m_TotalJM);
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+30*m_penScale,m_SelectJM);
}

void CJMAnalyse::DrawCircleMCC()
{
  //��ȡ�ļ�����ͼ
	  ReadDataFromFile();//������С��������Բ�����
  	  //��С����Բ��MZCDX, MZCDY, 
      //��С���򷨵����ֵ����Сֵ DispMaxdirec,DispMindirec
      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
      double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=dright/2;
	  //rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ 
	  CString strcodinate;
	  //rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ
	  int x1,y1,x2,y2;
	  double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	  dw=2*PI/3600;
	  
	  //���Ƶ�ɫԲ����
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //���ƻ�ɫԲ���� 
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
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //����Բ������ɫ�� 
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
	  //----------���춯̬Բ��---------
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

	  //----------------------���ϴ���ʵ������ѡȡ-----------
	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //�����ջ�ˢ����ֹ�ڵ���
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//ѡ��ˢ 

	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//����Բ����Բ
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//����Բ����Բ
      RoutORin.DeleteObject();
	
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////����������//////////////////////////////////
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
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);//����x��
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/2,dY0-EverystrcodY/2,"0��");
	  memDCJM.TextOut(rectJM.left,dY0-EverystrcodY/2,"180��");
	  
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45��");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225��");
	  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //����y��
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0+EverystrcodY*11,"270��");
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0-EverystrcodY*11.5,"90��");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135��");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315��");

		  
		  
	  for(i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //����X����̶�
		  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	  }	
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //����X����̶�
		  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	  }
	  for( i=0; i<10; i++)      //дY����̶�ֵ
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
		//�ڼ�����������Ǵ��ݹ�����///////////////////���������M;
		for (i=0;i<3600;i++)	
		{  
			fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
			m_CirCal[i]=fpdata[i];    //����Բ�����ת��λ�ƹ�ʽ		
		}	

			//�ֶ�����������ݽ��е��ú�������	
			for(i=0;i<3600;i++)		
			{ 
				datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //����Բ�����ת��λ�ƹ�ʽ	
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
			A0 = SumTs/3600;       //1.4084237494346061��С����Բ�İ뾶��Բ������
			A1 = 2*SumTcos/3600;  //-0.29798988797225540
	        B1 = 2*SumTsin/3600; //-0.095864371049355274

	   //�������������Сֵ-----
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
	   A1Draw=MCCDX*FDKP; //����Բ�ȴ��ʱԲ��������ʾ
	   B1Draw=MCCDY*FDKP; 
       A0Draw=A0*FDKP;
	  //////////////////////��������ĺᡢ������///////////////////////////////
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
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//ʵ�������ĺᡢ������(����ڶ���Բ��)
	   }        
	double rout2;	 
	rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	m_Intstep=5;//�����������
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
	   memDCJM.Ellipse(dX0-rout2+rectJM.left,dY0-rout2+rectJM.top,dX0+rout2+rectJM.left,dY0+rout2+rectJM.top);//����Բ����Բ
       RoutORin.DeleteObject();*/

	for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	{ 
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{  
		   memDCJM.SelectObject(&pendeal);
		   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//��ɫ���߱�ʾ�ֶ���������
		   memDCJM.MoveTo(drealx[i], drealy[i]);
		   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);	
		   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));	   
		}
		else
		{
			memDCJM.SelectObject(&penreal);
			memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//��ɫ���߱�ʾʵ������
			memDCJM.MoveTo(drealx[i], drealy[i]);
			memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
			if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		}
	}


      CPen pencir;
	  pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
	  memDCJM.SelectObject(&pencir);
	  memDCJM.Ellipse(dX0-rout2+rectJM.left,dY0-rout2+rectJM.top,dX0+rout2+rectJM.left,dY0+rout2+rectJM.top);//����Բ����Բ
	  double Rmincir=dX0/2-100*m_penScale;
	  pencir.DeleteObject();


	if(i>=3600-m_Intstep)
	{ 
		for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		{
	       if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			{   
			    memDCJM.SelectObject(&pendeal);
			    memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//��ɫ���߱�ʾʵ������
		    	memDCJM.MoveTo(drealx[i], drealy[i]);
			    memDCJM.LineTo(drealx[0], drealy[0]);	
				if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
			else
			{
				memDCJM.SelectObject(&penreal);
				memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//��ɫ���߱�ʾʵ������
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
	double tr=2 * 3.1415926/36;// ÿһ�β�����Ӧ�ĽǶȼ��������
	double wzd=asin(6*m_penScale/m_maxRTriangle); //ÿ�������εĵױ���������ڶ������ת�Ƕ�
	
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
	//ͼ����ʾ��ע˵��
	CString m_SelectJM,m_TotalJM;

    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);
	
	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"��������:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"��ǰ����:");

    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+30*m_penScale,m_TotalJM);
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+10*m_penScale,m_SelectJM);	   
}

void CJMAnalyse::MCCyuandu(double *Soudata)
{
  //--------Case 2, 3-------------------
 	 //----'2- MCC ��С���Բ����ʾ������Ӵ�����������㡣
     //----'3- MIC �������Բ����ʾ������Ӵ������������㡣
     double Direc[7200],Sirec[3600],TsQ[3600],TsH[3600],fpcircle[3600];
	 double SumTs,SumTcos,SumTsin,dw,A0,a1,b1,b2,A2,Zc1,Zc2,D,D1,D2,Maxdirec,Mindirec;
	 double Temp1,U1,U2,U10,U20, GLiGangK = 39.37008,PVA,PVB,PVB0;
     int    i=0,GDN=3600,AnaDataMode=2;//�����㷨2Ϊ��С���Բ----------3Ϊ�������Բ
	 int    ScanT,MaxIndex,MinIndex,MinI1,MinI2,MaxI1,MaxI2,MaxI3;
     BOOL   GLiGangFlag=false;//qy changed//BOOL   GLiGangFlag;

	// G1=16,G2= 0.121732414074473  ;
     dw= 2*3.1415926/GDN;
  	 SumTs=0,SumTcos=0,SumTsin=0;
	 //=============================================================================
	 ////��ȡ�ļ�����ͼ///
	 LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//��ӦԲ�����еĵ���
	 m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//��굥��ѡ�еĽ���
	 pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;

	 
	 //-------------���ϴ���ʵ�ֶ��ļ�----------------------
	 for(i=0;i<3600;i++)		
	 { 
		 TsQ[i]=(Soudata[i]-2048)*10/(GG1*GG2*4096); //����Բ�����ת��λ�ƹ�ʽ	
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

     //'--1 ��Direc(i)�в��Ҷ������ֵ����λ�� ��Χ 0--Dn-1'2000
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
       if(AnaDataMode==2)      //'--2A MCC �鵽�Ķ������ֵ�ڰ�Բ�� '2050
	   {
		  if(abs(MaxI2-MaxI1-GDN/2)<=1)    goto PDMiCTJ;//'2550
	   }
       else                    //'--2A MIC �鵽�Ķ������ֵ�ڰ�Բ�� '2050
	   {
          if (abs(MaxI2-MaxI1-GDN/2)<=3)   goto PDMiCTJ;// '2550
   
	   }

       // '--2B �鵽�Ķ������ֵ�ڰ�Բ�� '2060
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
//'--3A �ж���������? 2550


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

      if((MaxIndex==0)||(abs(MaxIndex-MaxI1)<=10)||(abs(MaxIndex-MaxI2)<=10)) //' �������,�ɹ�
	  {           
CONCRIGHT:
	      PVB = Maxdirec - Mindirec;
		  GResult[5]= PVB;
          goto QKquit;
	  }
      else     // '����������,���²���    
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
           goto ErrQuit;// ' �����˳�
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
ErrQuit: //' �����˳�
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
  m_MCCRONT.Format("%.3f",GResult[5]);  //�ڱ�������ʾ��С��������Բ�����Ľ��

}

void CJMAnalyse::MICyuandu(double *Soudata)
{
	     //--------Case 2, 3-------------------
 	 //----'2- MCC ��С���Բ����ʾ������Ӵ�����������㡣
     //----'3- MIC �������Բ����ʾ������Ӵ������������㡣
     double Direc[7200],Sirec[3600],TsQ[3600],TsH[3600],fpcircle[3600];
	 double SumTs,SumTcos,SumTsin,dw,A0,a1,b1,b2,A2,Zc1,Zc2,D,D1,D2,Maxdirec,Mindirec;
	 double Temp1,U1,U2,U10,U20, GLiGangK = 39.37008,PVA,PVB,PVB0;
     int    i=0,GDN=3600,AnaDataMode=3;//�����㷨2Ϊ��С���Բ----------3Ϊ�������Բ
	 int    ScanT,MaxIndex,MinIndex,MinI1,MinI2,MaxI1,MaxI2,MaxI3;
     BOOL   GLiGangFlag = false;//qy changed//BOOL   GLiGangFlag;

//	 G1=16,G2= 0.121732414074473  ;
     dw= 2*3.1415926/GDN;
  	 SumTs=0,SumTcos=0,SumTsin=0;
	 //=============================================================================
	 //=============================================================================
	 ////��ȡ�ļ�����ͼ///
	 LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//��ӦԲ�����еĵ���
	 m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//��굥��ѡ�еĽ���
	 pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;

	 
	 //-------------���ϴ���ʵ�ֶ��ļ�----------------------
	 for(i=0;i<3600;i++)		
	 { 
		 TsQ[i]=(Soudata[i]-2048)*10/(GG1*GG2*4096); //����Բ�����ת��λ�ƹ�ʽ	
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

     //'--1 ��Direc(i)�в��Ҷ������ֵ����λ�� ��Χ 0--Dn-1'2000
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
       if(AnaDataMode==2)      //'--2A MCC �鵽�Ķ������ֵ�ڰ�Բ�� '2050
	   {
		  if(abs(MaxI2-MaxI1-GDN/2)<=1)    goto PDMiCTJ;//'2550
	   }
       else                    //'--2A MIC �鵽�Ķ������ֵ�ڰ�Բ�� '2050
	   {
          if (abs(MaxI2-MaxI1-GDN/2)<=3)   goto PDMiCTJ;// '2550
   
	   }

       // '--2B �鵽�Ķ������ֵ�ڰ�Բ�� '2060
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
//'--3A �ж���������? 2550


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

      if((MaxIndex==0)||(abs(MaxIndex-MaxI1)<=10)||(abs(MaxIndex-MaxI2)<=10)) //' �������,�ɹ�
	  {           
CONCRIGHT:
	      PVB = Maxdirec - Mindirec;
		  GResult[5]= PVB;
          goto QKquit;
	  }
      else     // '����������,���²���    
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
           goto ErrQuit;// ' �����˳�
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
ErrQuit: //' �����˳�
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
  m_MICRONT.Format("%.3f",GResult[5]);  //�ڱ�������ʾ��С��������Բ�����Ľ��


}

void CJMAnalyse::DrawCircleMIC()
{
		  //��ȡ�ļ�����ͼ
	  ReadDataFromFile();//������С��������Բ�����
  	  //��С����Բ��MZCDX, MZCDY,��С���򷨵����ֵ����Сֵ DispMaxdirec,DispMindirec

      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
	  double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.right*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5/2;
      double dw= 2*3.1415926/3600;
	  //rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ 
	  int i,x1,y1,x2,y2;
	  //double rout=dY0-dY0/5,Everystrcod=(rout)/10,rin=Everystrcod*5,RSLC=(rout+rin)/2;
	  double rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=rout*0.5,RSLC=(rout+rin)/2;
      double th,rout1=rout;
      CString strcodinate;

	  //���Ƶ�ɫԲ����
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //���ƻ�ɫԲ���� 
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
	  
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //����Բ������ɫ�� 
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
	  //----------���춯̬Բ��---------
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

	  //----------------------���ϴ���ʵ������ѡȡ-----------
	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //�����ջ�ˢ����ֹ�ڵ���
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//ѡ��ˢ 
	  
	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//����Բ����Բ
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//����Բ����Բ
      RoutORin.DeleteObject();
	  
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////����������//////////////////////////////////
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
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);//����x��
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/2,dY0-EverystrcodY/2,"0��");
	  memDCJM.TextOut(rectJM.left,dY0-EverystrcodY/2,"180��");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45��");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225��");
	  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //����y��
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0+EverystrcodY*11,"270��");
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0-EverystrcodY*11.5,"90��");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135��");
      memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315��");
		  
		  
	  for(i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //����X����̶�
		  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	  }	
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //����X����̶�
		  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	  }
	  for( i=0; i<10; i++)      //дY����̶�ֵ
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
	  //�ڼ�����������Ǵ��ݹ�����///////////////////���������M;
	  for (i=0;i<3600;i++)	
	  {  
		  fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		  m_CirCal[i]=fpdata[i];    //����Բ�����ת��λ�ƹ�ʽ		
	  }	

	  for(i=0;i<3600;i++)		
	  { 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //����Բ�����ת��λ�ƹ�ʽ	
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
	   A0 = SumTs/3600;       //1.4084237494346061��С����Բ�İ뾶��Բ������
	   A1 = 2*SumTcos/3600;  //-0.29798988797225540
	   B1 = 2*SumTsin/3600; //-0.095864371049355274
	   
	   //�������������Сֵ-----
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
	   A1Draw=MICDX*FDKP; //����Բ�ȴ��ʱԲ��������ʾ
	   B1Draw=MICDY*FDKP; 
       A0Draw=A0*FDKP;
	  
	   //////////////////////��������ĺᡢ������///////////////////////////////
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
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//ʵ�������ĺᡢ������(����ڶ���Բ��)
	   }	

	   double rout2;
       rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	   m_Intstep=5;//���������������
	   CPen penreal;
	   penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));     
	   CPen pendeal;
	   pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));


/*	   for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
			   memDCJM.SelectObject(&penreal);
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//��ɫ���߱�ʾʵ������
			   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
			   memDCJM.LineTo(drealx[i+m_Intstep]+rectJM.left, drealy[i+m_Intstep]+rectJM.top);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
	   }
	   penreal.DeleteObject();

	  CPen RoutORin(PS_SOLID ,1*m_penScale,RGB(20,230,20));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rout2+rectJM.left,dY0-rout2+rectJM.top,dX0+rout2+rectJM.left,dY0+rout2+rectJM.top);//����Բ����Բ
      RoutORin.DeleteObject();*/

	   for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
		   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		   {  
			   memDCJM.SelectObject(&pendeal);
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//��ɫ���߱�ʾʵ������
			   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
			   memDCJM.LineTo(drealx[i+m_Intstep]+rectJM.left, drealy[i+m_Intstep]+rectJM.top);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
                   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

		   }
		   else
		   {
			   memDCJM.SelectObject(&penreal);
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(255,0,0));//��ɫ���߱�ʾʵ������
			   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
			   memDCJM.LineTo(drealx[i+m_Intstep]+rectJM.left, drealy[i+m_Intstep]+rectJM.top);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
                    rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
	   }
	   
	   
	   CPen pencir;
	   pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
	   memDCJM.SelectObject(&pencir);
	   memDCJM.Ellipse(dX0-rout2+rectJM.left,dY0-rout2+rectJM.top,dX0+rout2+rectJM.left,dY0+rout2+rectJM.top);//����Բ����Բ
	   double Rmincir=dX0/2-100*m_penScale;
	   pencir.DeleteObject();

	   
	   if(i>=3600-m_Intstep)
	   { 
		   for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		   {
			   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			   {   

				   memDCJM.SelectObject(&pendeal);
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//��ɫ���߱�ʾʵ������
				   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
				   memDCJM.LineTo(drealx[0]+rectJM.left, drealy[0]+rectJM.top);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
					   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

			   }
			   else
			   {
				   memDCJM.SelectObject(&penreal);
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(255,0,0));//��ɫ���߱�ʾʵ������
				   memDCJM.MoveTo(drealx[i]+rectJM.left, drealy[i]+rectJM.top);
				   memDCJM.LineTo(drealx[0]+rectJM.left, drealy[0]+rectJM.top);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
					   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

			   }
		   }
	   }
	penreal.DeleteObject();



	   //-----------------����Χ��һȦ��С��������---------------------------------
	   double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	   CPen penblack(PS_SOLID, 1*m_penScale, RGB(0, 0,0));
	   CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	   CBrush brushblack(RGB(0, 0, 0));
	   memDCJM.SelectObject(&brushblack);
	   CPoint pts[3];
	   double tr=2 * 3.1415926/36;// ÿһ�β�����Ӧ�ĽǶȼ��������
	   double wzd=asin(6*m_penScale/m_maxRTriangle); //ÿ�������εĵױ���������ڶ������ת�Ƕ�
	   
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
	    //'MZC--��С���򷨡�����ͬ��Բ���������Բ����ʾ��������������ĵ�Ӵ�
    double Direc[7200],Sirec[3600];
    double SumTs=0,SumTcos=0,SumTsin=0,TsQ[3600],TsH[3600];
    double dw,A0,a1,b1, Maxdirec,Mindirec,GLiGangK;
     int   i=0,GDN=3600;
     int   ScanT,PVB0,MaxIndex,MinIndex,MinI1,MaxI1,MinI2,MaxI2;
	 BOOL   GLiGangFlag= false;//qy changed //BOOL  GLiGangFlag;

	GLiGangK=39.37008;
    dw=2*3.1415926/GDN;

	 
	////��ȡ�ļ�����ͼ///
	LenDataJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMNum;//��ӦԲ�����еĵ���
	m_LBtnJM=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;//��굥��ѡ�еĽ���
	pathJM=((CMainFrame*)AfxGetMainWnd())->m_fullJMPath;


	for(i=0;i<GDN;i++)		
	{ 
		TsQ[i]=(Soudata[i]-2048)*10/(GG1*GG2*4096); //����Բ�����ת��λ�ƹ�ʽ	
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
	    SumTcos=SumTcos+TsH[i]*cos(dw*i);  //TsH[i]�ǲɼ���Բ������ת���ɵ�λ����
        SumTsin=SumTsin+TsH[i]*sin(dw*i);
	}
    A0=SumTs/GDN;
    a1=2*SumTcos/GDN;
    b1=2*SumTsin/GDN;                     //��С����Բ��Բ������Ͱ뾶

    for (i=0;i<GDN;i++)
	{
    	Direc[i]=TsH[i]-A0-a1*cos(dw*i)-b1*sin(dw*i);
	    Direc[i+GDN]=Direc[i];
	}
    ScanT=0,PVB0=100;

    //--�������ֵ����Сֵ�Լ���λ��(1)  ��Χ 0--Dn-1
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

    if (abs(MaxI1-MinI1)<GDN/2)    //���ֵ����Сֵ�����ڰ���֮��==��ƥ��if-else==
	{
         if(MaxI1>MinI1)            //--ƥ��if-else-
		 {
			  //'�ȴ�1��С1,'--��������С2
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
              MinI2 = MinIndex;// '--��С1��С2֮����Ҵ�2
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
         else    //'��С1���1--------�������Ҵ�2
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
              Mindirec = Direc[MaxI2];   //'--�ڴ�2�ʹ�1֮�����С2
              
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
 
  else    // '���ֵ����Сֵ�����ڰ���֮��
   {
        if (MaxI1>MinI1)//'��С1���1  '--�������Ҵ�ֵ
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
            //'-�´�ֵ��Ϊ��1,ԭ��1��Ϊ��2,�ڴ�1�ʹ�2֮�����С2
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
        else  //'�ȴ�1��С1,'--��������Сֵ
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

             // '-��Сֵ��ΪС1,ԭС1��ΪС2,��С1��С2֮����Ҵ�2
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
   
  PDMZCTJ:  // '�ж���������?=========��������ĵ���������
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
       if((MaxIndex==0) && (MinIndex==0))    //' �������,�ɹ�
	   {
          PVB=2*Maxdirec;
          GResult[1]=PVB;
	   }
       else goto CxScanLp;
       goto QKquit;//'---û���ҵ���������������ĵ�,���²���----
  
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
               ERRAquit: GResult[1]=PVB;       // GResult[1]=PVB;// ' �����˳�
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
         goto PDMZCTJ ;//'�ж���������?
   }            
		  
ErrQuit: //' �����˳�
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
    m_MZCRONT.Format("%.3f",GResult[1]);  //�ڱ�������ʾ��С��������Բ�����Ľ��

}

void CJMAnalyse::DrawCircleMZC()
{
	  ReadDataFromFile();//������С��������Բ�����,���������ȡ�ļ��ĺ���

  	  //��С����Բ��MZCDX, MZCDY, ���ֵDispMaxdirec����СֵDispMindirec

      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
	  double dY0= rectJM.Height()/2,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.right*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5/2;
      double dw= 2*3.1415926/3600;
	  int i,x1,y1,x2,y2;
	  //rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ 
	  //double rout=260*m_penScale,Everystrcod=(rout)/10,rin=200*m_penScale,RSLC=(rout+rin)/2;
      double rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=0.5*rout,RSLC=(rout+rin)/2;
      double th,rout1=257*m_penScale;
      CString strcodinate;

	  	  //���Ƶ�ɫԲ����
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //���ƻ�ɫԲ���� 
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
	  
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //����Բ������ɫ�� 
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
	  //----------���춯̬Բ��---------
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

	  //----------------------���ϴ���ʵ������ѡȡ-----------

	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //�����ջ�ˢ����ֹ�ڵ���
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//ѡ��ˢ 
	  
	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//����Բ����Բ
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//����Բ����Բ
      RoutORin.DeleteObject();
	  
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////����������//////////////////////////////////
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
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);//����x��
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/2,dY0-EverystrcodY/2,"0��");
	  memDCJM.TextOut(rectJM.left,dY0-EverystrcodY/2,"180��");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45��");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225��");
	  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //����y��
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0+EverystrcodY*11,"270��");
	  memDCJM.TextOut(dX0-EverystrcodX/2,dY0-EverystrcodY*11.5,"90��");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135��");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315��");

	  
	  
	  for(i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //����X����̶�
		  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	  }	
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //����X����̶�
		  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	  }
	  for( i=0; i<10; i++)      //дY����̶�ֵ
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
	  //�ڼ�����������Ǵ��ݹ�����///////////////////���������M;
	  for (i=0;i<3600;i++)	
	  {  
		  fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		  m_CirCal[i]=fpdata[i];    //����Բ�����ת��λ�ƹ�ʽ		
	  }
	
	  for(i=0;i<3600;i++)		
	  { 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //����Բ�����ת��λ�ƹ�ʽ	
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
	   A0 = SumTs/3600;       //1.4084237494346061��С����Բ�İ뾶��Բ������
	   A1 = 2*SumTcos/3600;  //-0.29798988797225540
	   B1 = 2*SumTsin/3600; //-0.095864371049355274
	   
	   //�������������Сֵ-----
	   m_datamax=DispMaxdirecMZC;
	   m_datamin=DispMindirecMZC;
       m_Middle=(m_datamax-m_datamin)/2;//0 

	   double  FDKP;
	   FDKP=29.0000/m_datamax;
	   A1Draw=MZCDX*FDKP; //����Բ�ȴ��ʱԲ��������ʾ
	   B1Draw=MZCDY*FDKP; 
       A0Draw=A0*FDKP;
	  
	   //////////////////////��������ĺᡢ������///////////////////////////////
	  
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
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//ʵ�������ĺᡢ������(����ڶ���Բ��)
	   }	

	   double rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0)),
		   rout3=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	   m_Intstep=5;//���������������
	   CPen penreal;
	   penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));     
	   CPen pendeal;
	   pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0)); 
	   
/*	   for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
			   memDCJM.SelectObject(&penreal);
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//��ɫ���߱�ʾʵ������
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
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//��ɫ���߱�ʾʵ������
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
			   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(255,0,0));//��ɫ���߱�ʾʵ������
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
	   memDCJM.Ellipse(dX0-rout2+rectJM.left,dY0-rout2+rectJM.top,dX0+rout2+rectJM.left,dY0+rout2+rectJM.top);//����Բ����Բ
	   memDCJM.Ellipse(dX0-rout3+rectJM.left,dY0-rout3+rectJM.top,dX0+rout3+rectJM.left,dY0+rout3+rectJM.top);//����Բ����Բ
	   double Rmincir=dX0/2-100*m_penScale;
	   pencir.DeleteObject();
	 
	    
	   if(i>=3600-m_Intstep)
	   { 
		   for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		   {
			   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			   {   
				   memDCJM.SelectObject(&pendeal);
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//��ɫ���߱�ʾʵ������
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
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(255,0,0));//��ɫ���߱�ʾʵ������
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
      
	   //-----------------����Χ��һȦ��С��������---------------------------------
	   double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	   CPen penblack(PS_SOLID, 1*m_penScale, RGB(0, 0,0));
	   CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	   CBrush brushblack(RGB(0, 0, 0));
	   memDCJM.SelectObject(&brushblack);
	   CPoint pts[3];
	   double tr=2 * 3.1415926/36;// ÿһ�β�����Ӧ�ĽǶȼ��������
	   double wzd=asin(6*m_penScale/m_maxRTriangle); //ÿ�������εĵױ���������ڶ������ת�Ƕ�
	   
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
	  //��ȡ�ļ�����ͼ
	  ReadDataFromFile();//������С��������Բ�����
  	  //��С����Բ��MZCDX, MZCDY, 
      //��С���򷨵����ֵ����Сֵ DispMaxdirec,DispMindirec
      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
	  double dY0= rectJM.Height()/2+rectJM.top,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5*1/2+rectJM.left;
	  CString strcodinate;
	  //rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ
	  int i,x1,y1,x2,y2;
	  double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	  dw=2*PI/3600;
	  
	  
	  //���Ƶ�ɫԲ����
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //���ƻ�ɫԲ���� 
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
	  
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //����Բ������ɫ�� 
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
	  //----------���춯̬Բ��---------
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

	  //----------------------���ϴ���ʵ������ѡȡ-----------
	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //�����ջ�ˢ����ֹ�ڵ���
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//ѡ��ˢ 

	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//����Բ����Բ
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//����Բ����Բ
      RoutORin.DeleteObject();
	
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////����������//////////////////////////////////

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
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);                    //����x��
	  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0-10); 
	  memDCJM.LineTo(dX0-EverystrcodX*10,dY0+10);
	  memDCJM.MoveTo(dX0+EverystrcodX*10,dY0-10); 
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0+10);
	  //memDCJM.TextOut(dX0+EverystrcodX*10+10,dY0-10,"0��");
	  //memDCJM.TextOut(dX0-rout-40,dY0-10,"180��");
	  memDCJM.TextOut(dX0+rout*1.05,dY0-rout*0.025,"0��");
	  memDCJM.TextOut(dX0-rout*1.15,dY0-rout*0.025,"180��");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45��");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225��");
	  

	  
	  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //����y��
	  memDCJM.MoveTo(dX0+10,dY0+EverystrcodY*10);
	  memDCJM.LineTo(dX0-10,dY0+EverystrcodY*10);
	  memDCJM.MoveTo(dX0+10,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0-10,dY0-EverystrcodY*10);
	  //memDCJM.TextOut(dX0-10,dY0+EverystrcodY*10+10,"270��");
	  //memDCJM.TextOut(dX0-10,dY0-EverystrcodY*10-30,"90��");
	  memDCJM.TextOut(dX0-rout*0.026,dY0+rout*1.04,"270��");
	  memDCJM.TextOut(dX0-rout*0.026,dY0-rout*1.1,"90��");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135��");
      memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315��");
	  
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //����X����̶�
		  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	  }	
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //����X����̶�
		  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	  }
	  for( i=0; i<10; i++)      //дY����̶�ֵ
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
		//�ڼ�����������Ǵ��ݹ�����///////////////////���������M;
		for (i=0;i<3600;i++)	
		{  
			fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
			m_CirCal[i]=fpdata[i];    //����Բ�����ת��λ�ƹ�ʽ		
		}	

			//�ֶ�����������ݽ��е��ú�������	
			for(i=0;i<3600;i++)		
			{ 
				datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //����Բ�����ת��λ�ƹ�ʽ	
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
			A0 = SumTs/3600;       //1.4084237494346061��С����Բ�İ뾶��Բ������
			A1 = 2*SumTcos/3600;  //-0.29798988797225540
	        B1 = 2*SumTsin/3600; //-0.095864371049355274

	   //�������������Сֵ-----
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
	   A1Draw=MCCDX*FDKP; //����Բ�ȴ��ʱԲ��������ʾ
	   B1Draw=MCCDY*FDKP; 
       A0Draw=A0*FDKP;
	  //////////////////////��������ĺᡢ������///////////////////////////////
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
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//ʵ�������ĺᡢ������(����ڶ���Բ��)
	   }        
	double rout2;	 
	rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	m_Intstep=5;//�����������
	CPen penreal;
	penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));  
	CPen pendeal;
	pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));    
	
	for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	{ 
		if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		{  
		   memDCJM.SelectObject(&pendeal);
		   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//��ɫ���߱�ʾ�ֶ���������
		   memDCJM.MoveTo(drealx[i], drealy[i]);
		   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);	
		   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));	   
		}
		else
		{
			memDCJM.SelectObject(&penreal);
			memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//��ɫ���߱�ʾʵ������
			memDCJM.MoveTo(drealx[i], drealy[i]);
			memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
			if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		}
	}


      CPen pencir;
	  pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
	  memDCJM.SelectObject(&pencir);
	  memDCJM.Ellipse(dX0-rout2,dY0-rout2,dX0+rout2,dY0+rout2);	  //����Բ����Բ
	  double Rmincir=dX0/2-100*m_penScale;
	  pencir.DeleteObject();


	if(i>=3600-m_Intstep)
	{ 
		for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		{
	       if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			{   
			    memDCJM.SelectObject(&pendeal);
			    memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//��ɫ���߱�ʾʵ������
		    	memDCJM.MoveTo(drealx[i], drealy[i]);
			    memDCJM.LineTo(drealx[0], drealy[0]);	
				if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))>rout2)
               rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
			else
			{
				memDCJM.SelectObject(&penreal);
				memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//��ɫ���߱�ʾʵ������
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
	double tr=2 * 3.1415926/36;// ÿһ�β�����Ӧ�ĽǶȼ��������
	double wzd=asin(6*m_penScale/m_maxRTriangle); //ÿ�������εĵױ���������ڶ������ת�Ƕ�
	
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
	//ͼ����ʾ��ע˵��
	CString m_SelectJM,m_TotalJM;

    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);
	

	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"��������:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"��ǰ����:");
	
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+10*m_penScale,m_TotalJM);
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+30*m_penScale,m_SelectJM);
}

void CJMAnalyse::PrintCircleMIC()
{
			  //��ȡ�ļ�����ͼ
	  ReadDataFromFile();//������С��������Բ�����
  	  //��С����Բ��MZCDX, MZCDY,��С���򷨵����ֵ����Сֵ DispMaxdirec,DispMindirec

      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
	  double dY0= rectJM.Height()/2+rectJM.top,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5*1/2+rectJM.left;
	  CString strcodinate;
	  //rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ
	  int i,x1,y1,x2,y2;
	  double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
      dw=2*PI/3600;


	  //���Ƶ�ɫԲ����
	  //���Ƶ�ɫԲ����
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //���ƻ�ɫԲ���� 
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
	  
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //����Բ������ɫ�� 
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

	  //----------���춯̬Բ��---------
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

	  //----------------------���ϴ���ʵ������ѡȡ-----------
	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //�����ջ�ˢ����ֹ�ڵ���
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//ѡ��ˢ 

	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//����Բ����Բ
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//����Բ����Բ
      RoutORin.DeleteObject();

	  
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////����������//////////////////////////////////
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
		  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);                    //����x��
		  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0-10); 
		  memDCJM.LineTo(dX0-EverystrcodX*10,dY0+10);
		  memDCJM.MoveTo(dX0+EverystrcodX*10,dY0-10); 
		  memDCJM.LineTo(dX0+EverystrcodX*10,dY0+10);
		  //memDCJM.TextOut(dX0+EverystrcodX*10+10,dY0-10,"0��");
		  //memDCJM.TextOut(dX0-rout-40,dY0-10,"180��");
		  memDCJM.TextOut(dX0+rout*1.05,dY0-rout*0.025,"0��");
		  memDCJM.TextOut(dX0-rout*1.15,dY0-rout*0.025,"180��");
		  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45��");
		  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225��");

		  
		  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
		  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //����y��
		  memDCJM.MoveTo(dX0+10,dY0+EverystrcodY*10);
		  memDCJM.LineTo(dX0-10,dY0+EverystrcodY*10);
		  memDCJM.MoveTo(dX0+10,dY0-EverystrcodY*10);
		  memDCJM.LineTo(dX0-10,dY0-EverystrcodY*10);
		  //memDCJM.TextOut(dX0-10,dY0+EverystrcodY*10+10,"270��");
		  //memDCJM.TextOut(dX0-10,dY0-EverystrcodY*10-30,"90��");
		  memDCJM.TextOut(dX0-rout*0.026,dY0+rout*1.04,"270��");
		  memDCJM.TextOut(dX0-rout*0.026,dY0-rout*1.1,"90��");
		  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135��");
          memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315��");
		  
		  for( i=0; i<10; i++)
		  {
			  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //����X����̶�
			  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
			  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
		  }	
		  for( i=0; i<10; i++)
		  {
			  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //����X����̶�
			  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
			  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
		  }
		  for( i=0; i<10; i++)      //дY����̶�ֵ
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
	  //�ڼ�����������Ǵ��ݹ�����///////////////////���������M;
	  for (i=0;i<3600;i++)	
	  {  
		  fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		  m_CirCal[i]=fpdata[i];    //����Բ�����ת��λ�ƹ�ʽ		
	  }	

	  for(i=0;i<3600;i++)		
	  { 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //����Բ�����ת��λ�ƹ�ʽ	
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
	   A0 = SumTs/3600;       //1.4084237494346061��С����Բ�İ뾶��Բ������
	   A1 = 2*SumTcos/3600;  //-0.29798988797225540
	   B1 = 2*SumTsin/3600; //-0.095864371049355274
	   
	   //�������������Сֵ-----
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
	   A1Draw=MICDX*FDKP; //����Բ�ȴ��ʱԲ��������ʾ
	   B1Draw=MICDY*FDKP; 
       A0Draw=A0*FDKP;
	  
	   //////////////////////��������ĺᡢ������///////////////////////////////
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
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//ʵ�������ĺᡢ������(����ڶ���Բ��)
	   }	

	   double rout2;
       rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	   m_Intstep=5;//���������������
	   CPen penreal;
	   penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));     
	   CPen pendeal;
	   pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0));

	   for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
		   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		   {  
			   memDCJM.SelectObject(&pendeal);
			   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//��ɫ���߱�ʾʵ������
			   memDCJM.MoveTo(drealx[i], drealy[i]);
			   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
                   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

		   }
		   else
		   {
			   memDCJM.SelectObject(&penreal);
			   memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//��ɫ���߱�ʾʵ������
			   memDCJM.MoveTo(drealx[i], drealy[i]);
			   memDCJM.LineTo(drealx[i+m_Intstep], drealy[i+m_Intstep]);
			   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
                    rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));
		   }
	   }
	   
	   
	   CPen pencir;
	   pencir.CreatePen(PS_SOLID,1*m_penScale, RGB(0,0,255));    
	   memDCJM.SelectObject(&pencir);
	   memDCJM.Ellipse(dX0-rout2,dY0-rout2,dX0+rout2,dY0+rout2);//����Բ����Բ
	   double Rmincir=dX0/2-100*m_penScale;
	   pencir.DeleteObject();

	   
	   if(i>=3600-m_Intstep)
	   { 
		   for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		   {
			   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			   {   

				   memDCJM.SelectObject(&pendeal);
				   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//��ɫ���߱�ʾʵ������
				   memDCJM.MoveTo(drealx[i], drealy[i]);
				   memDCJM.LineTo(drealx[0], drealy[0]);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
					   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

			   }
			   else
			   {
				   memDCJM.SelectObject(&penreal);
				   memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//��ɫ���߱�ʾʵ������
				   memDCJM.MoveTo(drealx[i], drealy[i]);
				   memDCJM.LineTo(drealx[0], drealy[0]);
				   if(sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0))<rout2)
				   rout2=sqrt((drealx[i]-dX0)*(drealx[i]-dX0)+(drealy[i]-dY0)*(drealy[i]-dY0));

			   }
		   }
	   }
	penreal.DeleteObject();



	   //-----------------����Χ��һȦ��С��������---------------------------------
	double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	CPen penblack(PS_SOLID, 1*m_penScale, RGB(0,0,0));
	CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	CBrush brushblack(RGB(0, 0, 0));
    memDCJM.SelectObject(&brushblack);
	CPoint pts[3];
	double tr=2 * 3.1415926/36;// ÿһ�β�����Ӧ�ĽǶȼ��������
	double wzd=asin(6*m_penScale/m_maxRTriangle); //ÿ�������εĵױ���������ڶ������ת�Ƕ�
	
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
	//ͼ����ʾ��ע˵��
	CString m_SelectJM,m_TotalJM;
	
    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);

	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"��������:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"��ǰ����:");
	
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+30*m_penScale,m_TotalJM);
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+10*m_penScale,m_SelectJM);

}

void CJMAnalyse::PrintCircleMZC()
{
		  ReadDataFromFile();//������С��������Բ�����,���������ȡ�ļ��ĺ���

  	  //��С����Բ��MZCDX, MZCDY, ���ֵDispMaxdirec����СֵDispMindirec

      double datas[3600],drealx[3600],drealy[3600],datacir[3600];
	  double m_datamax=0.0,m_datamin=0.0,m_Middle;
	  double A0,A1,B1,A0Draw,A1Draw,B1Draw,SumTcos,SumTsin,SumTs,TsH[3600];
	  double dY0= rectJM.Height()/2+rectJM.top,dleft=rectJM.left,dtop=rectJM.top,dright=rectJM.Width()*3/5+rectJM.left,dbottom=rectJM.bottom,dX0=rectJM.Width()*3/5*1/2+rectJM.left;
	  CString strcodinate;
	  //rinΪ0Բ��RSLCΪ2018Բ��routΪ4096Բ
	  int i,x1,y1,x2,y2;
	  double th,rout=rectJM.Height()*0.4,Everystrcod=(rout)/10,rin=Everystrcod*5, RSLC=(rout+rin)/2,dw;
	  dw=2*PI/3600;

	  	  //���Ƶ�ɫԲ����
	  CPen penRing(PS_SOLID,2*m_penScale,RGB(250,250,250));   //���ƻ�ɫԲ���� 
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
	  
	  CPen ping(PS_SOLID,2*m_penScale,RGB(250,200,238));   //����Բ������ɫ�� 
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
	  //----------���춯̬Բ��---------
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

	  //----------------------���ϴ���ʵ������ѡȡ-----------

	  CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	  //�����ջ�ˢ����ֹ�ڵ���
	  CBrush *pOldBrush=memDCJM.SelectObject(pBrush);//ѡ��ˢ 
	  
	  CPen RoutORin(PS_DOT ,1*m_penScale,RGB(0,230,230));
	  memDCJM.SelectObject(&RoutORin);               
	  memDCJM.Ellipse(dX0-rin,dY0-rin,dX0+rin,dY0+rin);//����Բ����Բ
	  memDCJM.Ellipse(dX0-rout,dY0-rout,dX0+rout,dY0+rout);//����Բ����Բ
      RoutORin.DeleteObject();
	  
	  ///////////////////////////////////////////////////////////////////
	  ///////////////////////����������//////////////////////////////////
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
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0);                    //����x��
	  memDCJM.MoveTo(dX0-EverystrcodX*10,dY0-10); 
	  memDCJM.LineTo(dX0-EverystrcodX*10,dY0+10);
	  memDCJM.MoveTo(dX0+EverystrcodX*10,dY0-10); 
	  memDCJM.LineTo(dX0+EverystrcodX*10,dY0+10);
	  //memDCJM.TextOut(dX0+EverystrcodX*10+10,dY0-10,"0��");
	  //memDCJM.TextOut(dX0-rout-40,dY0-10,"180��");
	  memDCJM.TextOut(dX0+rout*1.05,dY0-rout*0.025,"0��");
	  memDCJM.TextOut(dX0-rout*1.15,dY0-rout*0.025,"180��");
	  memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0-EverystrcodY*8,"45��");
 	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0+EverystrcodY*7,"225��");
	  
	  memDCJM.MoveTo(dX0,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0,dY0+EverystrcodY*10);                      //����y��
	  memDCJM.MoveTo(dX0+10,dY0+EverystrcodY*10);
	  memDCJM.LineTo(dX0-10,dY0+EverystrcodY*10);
	  memDCJM.MoveTo(dX0+10,dY0-EverystrcodY*10);
	  memDCJM.LineTo(dX0-10,dY0-EverystrcodY*10);
	  //memDCJM.TextOut(dX0-10,dY0+EverystrcodY*10+10,"270��");
	  //memDCJM.TextOut(dX0-10,dY0-EverystrcodY*10-30,"90��");
	  memDCJM.TextOut(dX0-rout*0.026,dY0+rout*1.04,"270��");
	  memDCJM.TextOut(dX0-rout*0.026,dY0-rout*1.1,"90��");
	  memDCJM.TextOut(dX0-(rout+dright-dX0)/2.5,dY0-EverystrcodY*8,"135��");
      memDCJM.TextOut(dX0+(rout+dright-dX0)/3,dY0+EverystrcodY*7,"315��");
	  
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0+i*EverystrcodX);              //����X����̶�
		  memDCJM.MoveTo(dX0+i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0+i*EverystrcodX  , dY0+4*m_penScale);
	  }	
	  for( i=0; i<10; i++)
	  {
		  strcodinate.Format("%.2f", dX0-i*EverystrcodX);	            //����X����̶�
		  memDCJM.MoveTo(dX0-i*EverystrcodX , dY0-4*m_penScale);
		  memDCJM.LineTo(dX0-i*EverystrcodX  , dY0+4*m_penScale);
	  }
	  for( i=0; i<10; i++)      //дY����̶�ֵ
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
	  //�ڼ�����������Ǵ��ݹ�����///////////////////���������M;
	  for (i=0;i<3600;i++)	
	  {  
		  fpdata[i]=m_dataJM[i+1+m_LBtnJM*3600].data;
		  m_CirCal[i]=fpdata[i];    //����Բ�����ת��λ�ƹ�ʽ		
	  }
	
	  for(i=0;i<3600;i++)		
	  { 
		datacir[i]=(fpdata[i]-2048)*10/(GG1*GG2*4096);    //����Բ�����ת��λ�ƹ�ʽ	
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
	   A0 = SumTs/3600;       //1.4084237494346061��С����Բ�İ뾶��Բ������
	   A1 = 2*SumTcos/3600;  //-0.29798988797225540
	   B1 = 2*SumTsin/3600; //-0.095864371049355274
	   
	   //�������������Сֵ-----
	   m_datamax=DispMaxdirecMZC;
	   m_datamin=DispMindirecMZC;
       m_Middle=(m_datamax-m_datamin)/2;//0 

	   double  FDKP;
	   FDKP=29.0000/m_datamax;
	   A1Draw=MZCDX*FDKP; //����Բ�ȴ��ʱԲ��������ʾ
	   B1Draw=MZCDY*FDKP; 
       A0Draw=A0*FDKP;
	  
	   //////////////////////��������ĺᡢ������///////////////////////////////
	  
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
		   drealy[i]=datas[i]*sin(i*dw)+dY0-B1;//ʵ�������ĺᡢ������(����ڶ���Բ��)
	   }	

	   double rout2=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0)),
		   rout3=sqrt((drealx[0]-dX0)*(drealx[0]-dX0)+(drealy[0]-dY0)*(drealy[0]-dY0));
	   m_Intstep=5;//���������������
	   CPen penreal;
	   penreal.CreatePen(PS_SOLID,1*m_penScale, RGB(255,0,0));     
	   CPen pendeal;
	   pendeal.CreatePen(PS_SOLID,1*m_penScale, RGB(0,255,0)); 

	   for(i=0;i<3600-m_Intstep;i=i+m_Intstep)		
	   { 
		   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
		   {  
			   memDCJM.SelectObject(&pendeal);
			   memDCJM.SetPixel(drealx[i],drealy[i],RGB(0,255,0));//��ɫ���߱�ʾʵ������
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
			   memDCJM.SetPixel(drealx[i],drealy[i],RGB(255,0,0));//��ɫ���߱�ʾʵ������
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
	   memDCJM.Ellipse(dX0-rout2,dY0-rout2,dX0+rout2,dY0+rout2);//����Բ����Բ
	   memDCJM.Ellipse(dX0-rout3,dY0-rout3,dX0+rout3,dY0+rout3);//����Բ����Բ
	   double Rmincir=dX0/2-100*m_penScale;
	   pencir.DeleteObject();
	 
	    
	   if(i>=3600-m_Intstep)
	   { 
		   for (i=3600-m_Intstep;i<3600; i+=m_Intstep)
		   {
			   if (m_dataJM[i+1+m_LBtnJM*3600].selected==1)
			   {   
				   memDCJM.SelectObject(&pendeal);
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(0,255,0));//��ɫ���߱�ʾʵ������
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
				   memDCJM.SetPixel(drealx[i]+rectJM.left,drealy[i]+rectJM.top,RGB(255,0,0));//��ɫ���߱�ʾʵ������
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
      
	   //-----------------����Χ��һȦ��С��������---------------------------------
	double m_minrTriangle=rout,m_maxRTriangle=(rout+8*m_penScale);// Draw with a thick blue pen.
	CPen penblack(PS_SOLID, 1*m_penScale, RGB(0,0,0));
	CPen pengrey(PS_DOT ,1*m_penScale,RGB(230,230,230));// And a solid red brush.
	CBrush brushblack(RGB(0, 0, 0));
    memDCJM.SelectObject(&brushblack);
	CPoint pts[3];
	double tr=2 * 3.1415926/36;// ÿһ�β�����Ӧ�ĽǶȼ��������
	double wzd=asin(6*m_penScale/m_maxRTriangle); //ÿ�������εĵױ���������ڶ������ת�Ƕ�
	
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
	//ͼ����ʾ��ע˵��
	CString m_SelectJM,m_TotalJM;

    m_SelectJM.Format("%d",m_LBtnJM+1);
    m_TotalJM.Format("%d",(LenDataJM)/3600);
	
	memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+30*m_penScale,"��������:");
    memDCJM.TextOut(rectJM.left+5*m_penScale,rectJM.top+10*m_penScale,"��ǰ����:");

    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+30*m_penScale,m_TotalJM);
    memDCJM.TextOut(rectJM.left+80*m_penScale,rectJM.top+10*m_penScale,m_SelectJM);

}
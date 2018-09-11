// DoCylinder.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DoCylinder.h"
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
// CDoCylinder

IMPLEMENT_DYNCREATE(CDoCylinder, CFormView)

CDoCylinder::CDoCylinder()
	: CFormView(CDoCylinder::IDD)
{
	//{{AFX_DATA_INIT(CDoCylinder)
	//}}AFX_DATA_INIT
	m_ModeChoose=0;
	flagAmpscale=0;
	m_AmpScale=1;
	ratio1=0;
	AngleZ=0;
	FilterMode=5;
    SeeAngle=0;
	m_Wa="";	//���ƶ���ʾ
	m_Wc="";	//���ƶ���
	m_Wp="";	//���ƶ���
	m_Wv="";	//���ƶ���ʾ
	m_Wt="";	//���ƶ���
	m_Wq="";	//���ƶ���
    m_Wwm="";	//���ƶ���

}

CDoCylinder::~CDoCylinder()
{
}

void CDoCylinder::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoCylinder)
	DDX_Control(pDX, IDC_Cylinder, m_editCylinder);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoCylinder, CFormView)
	//{{AFX_MSG_MAP(CDoCylinder)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_BTNTRIGHT,OnTRight)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(ID_BTNTLEFT,OnTLeft)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_COMMAND(ID_Print, OnPrint)
	ON_COMMAND(ID_BTNTBEGIN, OnBtntbegin)
	ON_WM_TIMER()
	ON_COMMAND(ID_BTNTSTOP, OnBtntstop)
	ON_COMMAND(ID_AmplifyScale, OnAmplifyScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoCylinder diagnostics

#ifdef _DEBUG
void CDoCylinder::AssertValid() const
{
	CFormView::AssertValid();
}

void CDoCylinder::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoCylinder message handlers

void CDoCylinder::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->DestroyVIEW(((CMainFrame*)AfxGetMainWnd())->m_DoCylinder);
	((CMainFrame*)AfxGetMainWnd())->m_DoCylinder=NULL;
	((CMainFrame*)AfxGetMainWnd())->Desktop();
}


void CDoCylinder::OnPaint() 
{
	
    CPaintDC dc(this);  
	CRect rectFill;
    GetClientRect(rectFill);
    dc.FillSolidRect(rectFill,RGB(255,255,255));  //����Ϊ��ɫ���� 

   	pWndPicture = GetDlgItem(IDC_Cylinder);      // ��öԻ����ϵ�picture�Ĵ��ھ��
	pWndPicture->GetClientRect(&rect);             // ��ȡ����������ı���
	pDCPicture = pWndPicture->GetDC();                     // ��öԻ����ϵ�picture���豸ָ��
	
	pOldBmp= NULL;  // ��öԻ����ϵ�picture���豸ָ��
	memDC.CreateCompatibleDC(pDCPicture);             // �����ڴ��ͼ�豸��ʹ�ڴ�λͼ��DC��ؼ���DC����
	memBitmap.CreateCompatibleBitmap(pDCPicture ,rect.right,rect.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap); 

 
	CPen CyPen(PS_SOLID,1,RGB(0,0,0));
	memDC.SelectObject(&CyPen);               
	memDC.Rectangle(rect.left,rect.top,rect.right,rect.bottom); //��̬�������ɫ�߿�
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
	//mDC.FillSolidRect(dx*3,dy*12,dx,dy,RGB(139,216,224));//��ָ�����������ɫ

   //------------------------------------------------------------
	memDC.FillSolidRect(gridleft,0,gridRect.right-1,dy,RGB(232,232,232));//��ͷ�������ɫ
	memDC.FillSolidRect(gridleft,dy*5,gridRect.right-1,dy,RGB(232,232,232));//��ָ���������ɫ
	memDC.FillSolidRect(gridleft,dy*12,gridRect.right-1,dy,RGB(232,232,232));//��ָ���������ɫ

	CPen *oldpen=memDC.SelectObject(&gridPen);

	for( int m0=0;m0<=gridxnums;m0++) //����gridxnums������                      
	{
		memDC.MoveTo(gridleft+m0*dx,gridRect.bottom);
		memDC.LineTo(gridleft+m0*dx,0);
	}
	for(int n=0;n<=gridynums;n++) //����gridynums������                        
	{
		memDC.MoveTo(rect.left+gridleft,n*dy);
		memDC.LineTo(rect.left+rect.Width(),n*dy);
	}
	//------------------------------------------------------------
    
	//----------����д�����弰��С
	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  
	CFont*   pOldFont=(CFont*)memDC.SelectObject(&font); 

	memDC.SetBkMode(TRANSPARENT); 
	int meter=4;
	int m1=gridleft+4;
	double m2=gridleft+dx/2;
	double m3=gridleft+dx-50;
	double mid=gridleft+dx/2-30;

	DrawCylinder();//���û�Բ���ĺ���  

	if (AngleZ%360>0)
	{
		SeeAngle=AngleZ%360;
	}
	else
	{
		SeeAngle=AngleZ%360;
	}


    m_Seeangle.Format("%d",SeeAngle);

    memDC.TextOut(mid-10,meter,"Բ���Ȳ������");

	memDC.TextOut(mid+20,dy*5+meter,"��������");
	memDC.TextOut(mid+20,dy*12+meter,"��������");

    memDC.TextOut(m1,dy+meter,"�ļ���");
	memDC.TextOut(m1,dy*2+meter,"����ʱ��");
	memDC.TextOut(m1,dy*6+meter,"�ο�����");                                       
	memDC.TextOut(m1,dy*7+meter,"�˲�������");                                              
	memDC.TextOut(m1,dy*8+meter,"�˲���Χ");    
	memDC.TextOut(m1,dy*9+meter,"�������");      
	memDC.TextOut(m1,dy*10+meter,"��ǰ�۲�Ƕ�");   
	

	memDC.TextOut(m1,dy*13+meter,"����Ҫ��");
	memDC.TextOut(m1,dy*14+meter,"Բ����");
// 	memDC.TextOut(m1,dy*15+meter,"����");
// 	memDC.TextOut(m1,dy*16+meter,"����");

	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath2;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDC.TextOut((m1+m2)/2,dy*1+meter,str);
	str=m_time.Format("%Y-%m-%d %H:%M");
	memDC.TextOut((m2+m1)/2,dy*2+meter,str);

	memDC.TextOut(m2,dy*6+meter,"��С���˷�");
	memDC.TextOut(m2,dy*7+meter,"Gaussian");
	memDC.TextOut(m2,dy*8+meter,"1-50");
	

	memDC.TextOut(m3,dy*13+meter,"um");
	memDC.TextOut(m3,dy*14+meter,"um");
//	memDC.TextOut(m3,dy*14+meter,"um");
// 	memDC.TextOut(m3,dy*15+meter,"um");
// 	memDC.TextOut(m3,dy*16+meter,"um"); 

	str.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[1]);
	memDC.TextOut(m2,dy*13+meter,str);
	memDC.TextOut(m2,dy*14+meter,m_CYLT);
// 	memDC.TextOut(m2,dy*15+meter,m_CYLP);
// 	memDC.TextOut(m2,dy*16+meter,m_CYLV);
	str.Format("%d",m_IntJM);
	memDC.TextOut(m2,dy*9+meter,str);
	memDC.TextOut(m2,dy*10+meter,m_Seeangle+"��");

	pDCPicture->BitBlt(rect.left,rect.top,rect.right,rect.bottom,&memDC,0,0,SRCCOPY); 
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
	memBitmap.DeleteObject();

}


void CDoCylinder:: WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata)
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



void CDoCylinder::SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr)
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
			break;
   case 9:// '�˳�17-100��г��
			WLS_Filter(9, 3600, TsQ, TsH);
			//'6�װ�����˹�˲��� TsQ(i) to TsH(i)
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

void  CDoCylinder::Rotate(double &x, double &y, double &z) 
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


void CDoCylinder::DrawCylinder()//��Բ��
{
	// ��öԻ����ϵ�picture���豸ָ��	
	//�����ͼ�����ĵ�
	CPoint centerPoint=0;
	centerPoint.x=rect.right*3/5/2;
	centerPoint.y=rect.bottom/8;//���ǻ���Բ����z[0]�����ĵ㡣

	CPen CyPe1(PS_SOLID,1,RGB(0,0,0));
	memDC.SelectObject(&CyPe1); 
	memDC.MoveTo(centerPoint.x,centerPoint.y+5);
    memDC.LineTo(centerPoint.x,rect.top+20);
    CyPe1.DeleteObject();


	memDC.TextOut(rect.Width()*3/5-20,centerPoint.y-30,"Z(mm)");
    memDC.TextOut(rect.left+5,centerPoint.y-30,"����");

	/////////////////////////////////////////////////////////////////////////////////////////////
	//���´���ʵ��Բ������������Բ����Ϣ�ļ��������Բ���ȵļ���/////////////////////////////////
	int     i=0,j=0,jmbtn;
	double  dis=0,z[JMNum],t[3600],bcondata[3600],acondata[3600],SumTs = 0.0,m_dCirMax,m_dCirMin;
	double  a=0,b=0,l=0,g=0,DR=0,p=0,CYLt,m_dCymax,m_dCymin,aa11[JMNum],bb11[JMNum],A0[JMNum],SumTss=0.0 ,a3=0.0,bb3=0.0,fls[JMNum];
    double  Gdw=0.0,diss=0.0;
    BOOL BTCHUL=0;
    //���ļ���ͼ
    ReadDataFromFile();
	
    BTCHUL=((CMainFrame*)AfxGetMainWnd())->JMCL; //��굥���Ľ���
    jmbtn=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;
	
    //////////////////////////////////////////////
    diss=(rect.bottom-centerPoint.y*3/2)/(m_IntJM-1);      //��ͼ�ĸ߶Ƚ���
    Gdw=2 * PI/m_IntPoint;
	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)	
		{ 
			t[j]=3.1415926*j/1800;
 			pem[i][j]=m_datayzd[j+1+i*m_IntPoint].data;
			jmdata[j]=pem[i][j];
            DRAWpem[i][j]=m_datayzd[j+1+i*m_IntPoint].data;
		}
        SubQKDataChuli(((CMainFrame*)AfxGetMainWnd())->m_fullPath2,m_IntPoint,i, !((CMainFrame*)AfxGetMainWnd())->m_bAutoQK, jmdata, Resdata);
		for (j=0;j<m_IntPoint;j++)	
		{  
		    pem[i][j]= Resdata[j];    
		}
	}

	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)	
		{  
			bcondata[j]=((pem[i][j]-2048)*10)/(G1*G2*4096)+1000;//ÿ3600�����ݽ���2-50���˲����������˲�֮������ݽ�����Ӧ����
            zz[i]=m_datayzd[j+1+i*m_IntPoint].height;        //��ȡ����߶���ֵ
		}
		z[m_IntJM-1-i]=i*diss;
		WLS_Filter(FilterMode, m_IntPoint, bcondata, acondata);     //�����˲�����
		for (j=0;j<m_IntPoint;j++)	
		{  
	    	Rr[i][j]=acondata[j];                          //�˲�֮�������
		}
	    a3=0 ,	bb3 = 0,SumTss = 0;
		for (j=0;j<m_IntPoint;j++)	
		{
		     a3 = a3+ Rr[i][j] * cos(j * Gdw);
		     bb3 =bb3 + Rr[i][j] * sin(j * Gdw);
			 SumTss= SumTss + Rr[i][j];
		}
		aa11[i]= 2 * a3/m_IntPoint;
		bb11[i] = 2 * bb3/m_IntPoint ;                   //��ʽ��������Ǹ����������С����Բ�ĺͰ뾶
		A0[i] = SumTss/m_IntPoint;
	}

	 for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)	
		{  	
		m_dfls[i][j] = Rr[i][j]-(aa11[i] * cos(j * Gdw) + bb11[i] * sin(j * Gdw)) - A0[i] ; //2-50�˲�֮���Բ��
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
       fls[i]=m_dCirMax-m_dCirMin;    //���������Բ��ֵ
	}
	/////////////////��ȡ�����Сֵ���ڻ�ͼ/////////////////////////////////
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
// 			 r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*(rout-rin)/m_OutIn+RSLC; //����Բ�ȴ��ʱ��������ʾ
// 			 
// 		 }
// 	}
    ////////////////////////////////////////////////////////////
    //////////����ʵ�ָ�˹�����Է��������Բ����/////////////////////////////////////////////
    //����������
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
	//' ����		
    double AA[6][6]={ {a111, a122, a13, a14, a15, a16},{a211, a222, a23, a24, a25, a26},{a31, a32, a33, a34, a35, a36},{a41, a42, a43, a44, a45, a46},{a51, a52, a53, a54, a55, a56},{a61, a62, a63, a64, a65, a66}};
    double AAB[6]={BB11,BB22,BB33,BB44,BB55,BB66};
    double X0[6]={1,1,1,1,1,1};
    double XA[6]={0,0,0,0,0,0};
    double delx=100;
	int timecalcute=0;

	//���ϴ���ʵ�����Է�����Ĺ��죬AA*XA=AAB
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
			  if ( (XA[i + 1] - X0[i + 1]) <= fabs(XA[i] - X0[i]) )
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
    //    '  �����֪������
	double XX0=0.0,YY0=0.0,ZZ0=0.0,AA0=0.0,BB0=0.0,CC0=0.0,Rc=0.0,Kc=0.0;
   	XX0 = XA[0],YY0= XA[1],ZZ0 = 0,AA0= XA[2],BB0 = XA[3],CC0 = 1,Rc = XA[4],Kc = XA[5];//��������ֵ

	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)
		{
			//�����㵽�������ߵľ���
	        dis1[i][j] = sqrt( ( ((yp[i][j] - YY0) * CC0 - (zz[i] - ZZ0) * BB0)* ((yp[i][j] - YY0) * CC0 - (zz[i] - ZZ0) * BB0) +((zz[i] - ZZ0) * AA0 - (xp[i][j] - XX0) * CC0)* ((zz[i] - ZZ0) * AA0 - (xp[i][j] - XX0) * CC0)+ ((xp[i][j] - XX0) * BB0 - (yp[i][j]- YY0) * AA0)*((xp[i][j] - XX0) * BB0 - (yp[i][j]- YY0) * AA0)  ) / ( AA0*AA0 + BB0* BB0 + CC0*CC0 ));
	    	xi[i][j] = XX0 +  AA0* zz[i];
	    	yi[i][j] = YY0 + BB0* zz[i];
            //�����Rij����Ҫ���м�ȥe��kz��Ӱ�졣
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
   	CYLt=m_dCymax +m_dCymin; //Բ�������
    m_CYLT.Format("%.3f",CYLt);
    m_CYLP.Format("%.2f",m_dCymax);
    m_CYLV.Format("%.2f",m_dCymin);

////////////////////////Բ���ȷŴ���////////////////////////
	double PV=CYLt;	 
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
		//	r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*(rout-rin)/m_OutIn*ratio*0.001+RSLC; //����Բ�ȴ��ʱ��������ʾ
//			r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*ratio*0.014/(rect.Height()*0.8/10)*(rout-rin)/m_OutIn+RSLC; 
			r[i][j]=(((CMainFrame*)AfxGetMainWnd())->m_OutIn*((DRAWpem[i][j]-m_Middle))*ratio*0.1*(rout-rin)/(rect.Height()*m_OutIn))+RSLC;///ok
//			r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*((DRAWpem[i][j]-m_Middle))*0.2*ratio*(rout-rin)/(1.5*(rect.Height()*m_OutIn))+RSLC;
//			r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(pem[i][j]-m_Middle)*ratio*0.01/(2*(rect.Height()/10))+RSLC;
//			r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*((pem[i][j]-m_Middle))*0.035*ratio*m_OutIn/(1.2*(rect.Height()*(rout-rin)))+RSLC;
			
		}
	}

	for (i=0;i<m_IntJM;i++) 
	{
		for (j=0;j<m_IntPoint;j++)
		{
			r[i][j]=0.9*r[i][j];
		}

	}

	
	//datas[i]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*((dataafterfilter[i]-m_Middle))*ratio*0.2/(rect1.Height()*0.4/10)+RSLC; //����Բ�ȴ��ʱ��������ʾ
/////////////////////////////////////////////////////////////////

    /////////////////���ϴ���ʵ��Բ�������ļ���///////////////////////
    /////////////////���´���ʵ��Բ������ͼ�ε���ʾ//////////////////////
	C3dPoint TPoint[4],p3;
    CLine    a1,a2,b1,b2;
    int      m_IStep=10;
	double   Rz[3][3],PI=3.1415926;
	CString  m_jiemian, m_heightZ;
	j=3000;
	for (i=0;i<m_IntJM;i++)
	{
		m_jiemian.Format("%d",i+1);
		m_heightZ.Format("%.1f",zz[i]);
		{		
			Z3DRondness[i][j].x=(r[i][j])*cos(j*Gdw);//������
			Z3DRondness[i][j].y=(r[i][j])*sin(j*Gdw);//������ ����    
			Z3DRondness[i][j].z=z[i];
			
			Z2DRondness[i][j]=Z3DRondness[i][j].Change();
			
			XJM[i][j]=rect.left+10;
			YJM[i][j]=Z2DRondness[i][j].y+centerPoint.y;
			memDC.TextOut(XJM[i][j],YJM[i][j]-10,"M"+m_jiemian);//��Բ���������ʾ������
			
			XJM[i][j]=rect.Width()*3/5;
			YJM[i][j]=Z2DRondness[i][j].y+centerPoint.y;
			memDC.TextOut(XJM[i][j],YJM[i][j]-10,m_heightZ);  //��Բ�����ұ���ʾ����߶�
			
		}
	}
	
	//��С�������Բ��
    C3dPoint POINT[3600];
	double s11=0,s12=0,s13=0,s22=0,s23=0,x0,y0,z0;
    double sumx2=0,sumx=0,sumy2=0,sumy=0,sumxy=0,sumx2y2=0,sumxx2y2=0,sumyx2y2=0;
	for (j=0;j<m_IntPoint;j++)
	{
		POINT[j].x=(r[m_IntJM-1][j])*cos(j * Gdw);//������
		POINT[j].y=(r[m_IntJM-1][j])*sin(j * Gdw);//������     ����
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

   ////Բ����С����ͼ���//////////////////////////////////
    for (i=0;i<m_IntJM-1;i++)
	{
		for (j=0;j<m_IntPoint-m_IStep;j+=m_IStep)	
		{
				
		        TPoint[0].x=(r[i+1][j])*cos(j * Gdw)-x0;//������
		        TPoint[0].y=(r[i+1][j])*sin(j * Gdw)-y0;//������     ����
		        TPoint[0].z=z[i+1]-z0;	

		        TPoint[1].x=(r[i][j])*cos(j * Gdw)-x0;//������
		        TPoint[1].y=(r[i][j])*sin(j * Gdw)-y0;//������ ����     
	            TPoint[1].z=z[i]-z0;
	
				TPoint[2].x=(r[i][j+m_IStep])*cos((j+m_IStep)*Gdw)-x0;//������
				TPoint[2].y=(r[i][j+m_IStep])*sin((j+m_IStep)*Gdw)-y0;//������   ����
				TPoint[2].z=z[i]-z0;	
		
				TPoint[3].x=(r[i+1][j+m_IStep])*cos((j+m_IStep)*Gdw)-x0;//������
				TPoint[3].y=(r[i+1][j+m_IStep])*sin((j+m_IStep)*Gdw)-y0;//������   ����    
				TPoint[3].z=z[i+1]-z0;	
             
				p3.x=(r[i][(j+m_IStep)/2])*cos((j+m_IStep)*Gdw/2)-x0;//������
				p3.y=(r[i][(j+m_IStep)/2])*sin((j+m_IStep)*Gdw/2)-y0;//������    
				p3.z=(z[i]+z[i+1])/2-z0;	


			    Rotate(TPoint[0].x,TPoint[0].y,TPoint[0].z);
				Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z); //������ת����ֱ�ӽ�����ת��Ϊ��ת֮�������  
			    Rotate(TPoint[2].x,TPoint[2].y,TPoint[2].z);
				Rotate(TPoint[3].x,TPoint[3].y,TPoint[3].z);   
				Rotate(p3.x,p3.y,p3.z);		
				/////////////////���¼��д���ʵ��Բ��������ڵ�///////////////////////////
				double test1=(p3.x-VPOINT_X)*((TPoint[2].y-TPoint[0].y)*(TPoint[3].z-TPoint[1].z)-(TPoint[2].z-TPoint[0].z)*(TPoint[3].y-TPoint[1].y))-(p3.y-VPOINT_Y)*((TPoint[2].x-TPoint[0].x)*(TPoint[3].z-TPoint[1].z)-(TPoint[2].z-TPoint[0].z)*(TPoint[3].x-TPoint[1].x))+(p3.z-VPOINT_Z)*((TPoint[2].x-TPoint[0].x)*(TPoint[3].y-TPoint[1].y)-(TPoint[2].y-TPoint[0].y)*(TPoint[3].x-TPoint[1].x));
				if(test1<0.0)
				{
					if (m_datayzd[j+1+i*m_IntPoint].selected==1) //�ֶ�����ѡ�У���Ϊ��ɫ
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
 
					else                            //������ʾ��ɫ
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

   //���������µľ�����//////////////////////////////////////
   for (i=0;i<m_IntJM-1;i++)
   {		   
		   TPoint[0].x=(r[i+1][j])*cos(j * Gdw)-x0;//������
		   TPoint[0].y=(r[i+1][j])*sin(j * Gdw)-y0;//������     ����
		   TPoint[0].z=z[i+1]-z0;	
		   
		   TPoint[1].x=(r[i][j])*cos(j * Gdw)-x0;//������
		   TPoint[1].y=(r[i][j])*sin(j * Gdw)-y0;//������ ����     
		   TPoint[1].z=z[i]-z0;
		   
		   TPoint[2].x=(r[i][0])*cos((0)*Gdw)-x0;//������
		   TPoint[2].y=(r[i][0])*sin((0)*Gdw)-y0;//������   ����
		   TPoint[2].z=z[i]-z0;	
		   
		   TPoint[3].x=(r[i+1][0])*cos((0)*Gdw)-x0;//������
		   TPoint[3].y=(r[i+1][0])*sin((0)*Gdw)-y0;//������   ����    
		   TPoint[3].z=z[i+1]-z0;	
		   
		   p3.x=(r[i][(m_IntPoint+j)/2])*cos((m_IntPoint+j)*Gdw/2)-x0;//������
		   p3.y=(r[i][(m_IntPoint+j)/2])*sin((m_IntPoint+j)*Gdw/2)-y0;//������    
		   p3.z=(z[i]+z[i+1])/2-z0;	
		   
		 
		   Rotate(TPoint[0].x,TPoint[0].y,TPoint[0].z);
		   Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z); //������ת����ֱ�ӽ�����ת��Ϊ��ת֮�������
		   Rotate(TPoint[2].x,TPoint[2].y,TPoint[2].z);
		   Rotate(TPoint[3].x,TPoint[3].y,TPoint[3].z);
		   Rotate(p3.x,p3.y,p3.z);	
		   /////////////////���¼��д���ʵ��Բ��������ڵ�///////////////////////////
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
   ////����������İ�Բ,������İ��Բ��û�б��ڵ�
  for (j=0;j<m_IntPoint-m_IStep;j++)
   {		
	    TPoint[1].x=(r[m_IntJM-1][j])*cos(t[j])-x0;//������
	    TPoint[1].y=(r[m_IntJM-1][j])*sin(t[j])-y0;//������      
    	TPoint[1].z=z[m_IntJM-1]-z0;
	    Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z);

		TPoint[2].x=(r[m_IntJM-1][j+m_IStep])*cos(t[j+m_IStep])-x0;//������
		TPoint[2].y=(r[m_IntJM-1][j+m_IStep])*sin(t[j+m_IStep])-y0;//������      
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

}

void CDoCylinder::OnInitialUpdate() 
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
void CDoCylinder::OnTRight() 
{
	// TODO: Add your control notification handler code here
	AngleZ-=10;
	OnPaint();
}
void CDoCylinder::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd *pWndCy; 
	CRect rectCy; 
	CDC *pDCCy;          
	pWndCy = GetDlgItem(IDC_Cylinder);      
	pWndCy->GetClientRect(&rectCy); 
	pWndCy->ClientToScreen(rectCy);       //ת������Ļ����,���Ͻ�����Ϊ�ı�������Ļ������
	pDCCy = pWndCy->GetDC();
	this->ClientToScreen(&point);          //ת��Ϊ��Ļ����
	
	point.x=point.x-rectCy.left;         //��point�������������Ļ����ת��Ϊ����ھ�̬�����꣬��̬�����Ͻ���(0,0)
	point.y=point.y-rectCy.top;
	double f1=(rectCy.right-rectCy.left)/2,f2= (rectCy.bottom-rectCy.top ) /2;
	
	CPoint centerPoint;
	centerPoint.x=(rectCy.right-rectCy.left)*3/5/2;
	centerPoint.y=(rectCy.bottom-rectCy.top)/8;//���ǻ���Բ����z[0]�����ĵ㡣
	int  i=0,j=0;
	CString str;
	
	for (i=0;i<m_IntJM;i++)   
	{
		j=3000;
		XJM[i][j]=rect.left+10;
		YJM[i][j]=Z2DRondness[i][j].y+centerPoint.y;
		if ( point.x>=XJM[i][j] && point.x<=YJM[i][j]+20 &&  point.y>= YJM[i][j]-10 && point.y<=YJM[i][j]+10)
		{
			((CMainFrame*)AfxGetMainWnd())->m_fullJMPath=((CMainFrame*)AfxGetMainWnd())->m_fullPath2;//��ȡԲ���ȵ�·��
			((CMainFrame*)AfxGetMainWnd())->m_fullJMType=1;    //��������
			((CMainFrame*)AfxGetMainWnd())->m_fullJMNum=LenData; 
            ((CMainFrame*)AfxGetMainWnd())->m_SelectJM=i;//��굥���Ľ���
			((CMainFrame*)AfxGetMainWnd())->DoJMAnalyse();
			OnPaint();
		}		
	}				
  CFormView::OnLButtonDblClk(nFlags, point);
}

void CDoCylinder::OnTLeft() 
{
	// TODO: Add your control notification handler code here
	AngleZ+=10;
	OnPaint();
}

HBRUSH CDoCylinder::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CDoCylinder::OnSize(UINT nType, int cx, int cy) 
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

void CDoCylinder::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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
  */
  void CDoCylinder::SubQKDataChuli(CString path,int Number, int JM, BOOL AutoOrManChuli, double *Soudata, double *Resdata)
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
	///////////////�ֹ��޳�//////////////////////////////
    // if( Number==0) 
    //	Exit Sub;

    //	���ļ���������������ȱ�ڸ�����ͳ��
	///////////��ȡ��������//////////////////////
	std::ifstream fin(path, std::ios::binary);
	fin.read((char*)&m_datayzd[0], sizeof(shuju0)); //��ȡ����
	m_IntJM=m_datayzd[0].data;
	m_IntPoint=3600;
    LenData=m_IntJM*m_IntPoint;
    ///////////////��ȡԲ������/////////////////////////////
	for ( i=0;i<LenData;i++)
	{	
		fin.read((char*)&m_datayzd[i+1], sizeof(shuju0)); //��ȡ����
	}
	fin.read((char*)&G1,sizeof(double));
	fin.read((char*)&G2,sizeof(double));
	fin.read((char*)&m_time,sizeof(double));
    fin.close();


	//�ֱ�ͳ��ȱ�ڵĸ�����ȱ����ߺ�ȱ���ұߵ������±�
    int jLeft=0,jRight=0;
	for (i=0;i<Number-1;i++)
	{
		if (m_datayzd[i+1+JM*m_IntPoint].selected==0 && m_datayzd[i+1+1+JM*m_IntPoint].selected==1 )//�ֶ�ȥ���������ʼ��
		{
			QKnumberL[jLeft]=i; //����ȱ�ڵ���ʼ���±�
			jLeft=jLeft+1;
		}
		if (m_datayzd[i+1+JM*m_IntPoint].selected==1 && m_datayzd[i+1+1+JM*m_IntPoint].selected==0 )//�ֶ�ȥ���������ֹ��
		{
			QKnumberr[jRight]=i;//����ȱ�ڵ���ֹ����±�
            jRight=jRight+1;
		}
	}

    if (m_datayzd[3599+1+JM*m_IntPoint].selected==1 && m_datayzd[1+JM*m_IntPoint].selected==1 && jLeft>1)
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
	   YDQKdata[i]=((Soudata[i]-2048)*10)/(G1*G2*4096); //������ת����λ��
	   if(i== Number - 1) //�������Ϊ���һ����
		   BHVdata[i]=((Soudata[0]-2048)*10)/(G1*G2*4096)-((Soudata[i]-2048)*10)/(G1*G2*4096);//�õ�һ������ȥ���һ����
	   else
		   BHVdata[i]=((Soudata[i+1]-2048)*10)/(G1*G2*4096)-((Soudata[i]-2048)*10)/(G1*G2*4096);//����Ļ�����һ������ȥ��һ����	
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
					if( abs(TempWZPL[TempNA]) > Number / 2) 
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
                         //   m_datayzd[j+1+JM*m_IntPoint].selected=1;//����
						}
					}
					else 
					{
					  for(j=TempStart;j<Number;j++)
					  {	
						Soudata[j]=Soudata[TempStart]+TempK*(j-TempStart);
                      //  m_datayzd[j+1+JM*m_IntPoint].selected=1;//����
					  }
					for (j=0;j<=TempEnd;j++)
					{
	                    Soudata[j]=Soudata[TempStart]+TempK*(j + Number - TempStart);
                     //   m_datayzd[j+1+JM*m_IntPoint].selected=1;//����
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
	
//	int Starti,Endi;//��С�γ���ʵ�����Զ�ȥȱ���Ժ�ӳ��ͼ�ν����ϵı仯
//     for( i=1;i<=QkNumber;i++)
// 	{
//        Starti=MinIndex[i]-GBzDot;
//        Endi=MaxIndex[i]+ GBzDot;
//        ChangeValueOfSelect(path,Starti,Endi,1);
// 	}


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
		   YDQKdata[i] = ((Soudata[i]-2048)*10)/(G1*G2*4096);
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



void CDoCylinder::ReadDataFromFile()
{
	///////////��ȡ��������//////////////////////
	std::ifstream fin(((CMainFrame*)AfxGetMainWnd())->m_fullPath2, std::ios::binary);
	fin.read((char*)&m_datayzd[0], sizeof(shuju0)); //��ȡ����
	m_IntJM=m_datayzd[0].data;
	m_IntPoint=3600;
    LenData=m_IntJM*m_IntPoint;
    ///////////////��ȡԲ������/////////////////////////////
	for (int i=0;i<LenData;i++)
	{	
		fin.read((char*)&m_datayzd[i+1], sizeof(shuju0)); //��ȡ����
	}
	fin.read((char*)&G1,sizeof(double));
	fin.read((char*)&G2,sizeof(double));
	fin.read((char*)&m_time,sizeof(double));
    fin.close();
}


double CDoCylinder::vect_norm(double vect[], int n)
{
	double rst = 0;
	double result;                                                
	int i;
	
	for (i = 0; i < n; i++)	
	rst = rst + vect[i] * vect[i];
    result = sqrt(rst);
	return (result);
}

void CDoCylinder::OnPrint() 
{
	// TODO: Add your command handler code here
	CFormView::OnFilePrint();
}

void CDoCylinder::OnDraw(CDC* pDC) 
{
    int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);//X����һӢ�����صĸ���,A4ֽ
    int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);//Y����һӢ�����صĸ���
	int xLogPixPerMM=xLogPixPerInch/25.4;//X����1mm���صĸ���
	int yLogPixPerMM=yLogPixPerInch/25.4;//Y����1mm���صĸ���
	m_penScale=xLogPixPerInch/96;//
	
	//��ӡ��ĳߴ�Ϊ150*250(mm)
	CPoint pt(0,0);//ֽ�ŵ����Ͻ�Ϊ00��
	CSize  sz(270*xLogPixPerMM,200*yLogPixPerMM);//sz���ο�Ĵ�С��X�����Y�������ص��ܸ���
	CRect  tRect(pt,sz);//����Ĵ�ӡ���ľ��ο�
	rect1.top=tRect.top+25*yLogPixPerMM;
	rect1.right=tRect.right;
	rect1.left=tRect.left+20*xLogPixPerMM;
	rect1.bottom=tRect.bottom-25*yLogPixPerMM;
	
	pOldBmp = NULL;                           // ���ɵ�λͼָ���ÿ�	
	memDC.CreateCompatibleDC(pDC);             // �����ڴ��ͼ�豸��ʹ�ڴ�λͼ��DC��ؼ���DC����
	memBitmap.CreateCompatibleBitmap(pDC,tRect.right,tRect.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap);
    memDC.FillSolidRect(tRect.left,tRect.top,tRect.right,tRect.bottom,RGB(255,255,255));//�����ο�����ɫ*/
	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDC.SelectObject(&RectPen);      //�ʺ�������֮ǰ��Ҫselectobject���������Ҫdeleteobject      
	memDC.Rectangle(rect1.left,rect1.top,rect1.right,rect1.bottom); //��̬����� ��ɫ �߿�
	
	//�޸Ĵ�ӡ�����С
	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
		DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  
	CFont*   pOldFont=(CFont*)memDC.SelectObject(&font); 
	
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
	CFont newFont;
	CFont *oldFont;
	
	newFont.CreateFontIndirect(&newLogFont);
	oldFont = memDC.SelectObject(&newFont );
	
	//��������
	memDC.MoveTo(rect1.left,rect1.top);
	memDC.LineTo(rect1.left,rect1.top-10*xLogPixPerMM);
	memDC.MoveTo(rect1.left,rect1.top-10*xLogPixPerMM);
	memDC.LineTo(rect1.right,rect1.top-10*xLogPixPerMM);
	memDC.MoveTo(rect1.right,rect1.top-10*xLogPixPerMM);
	memDC.LineTo(rect1.right,rect1.top);
	//��������
	memDC.MoveTo(rect1.left,rect1.bottom);
	memDC.LineTo(rect1.left,rect1.bottom+10*xLogPixPerMM);
	memDC.MoveTo(rect1.left,rect1.bottom+10*xLogPixPerMM);
	memDC.LineTo(rect1.right,rect1.bottom+10*xLogPixPerMM);
	memDC.MoveTo(rect1.right,rect1.bottom+10*xLogPixPerMM);
	memDC.LineTo(rect1.right,rect1.bottom);
	RectPen.DeleteObject();
	
	//д����Ϣ
    memDC.TextOut(0.8*rect1.left+200*xLogPixPerMM,rect1.bottom+11*yLogPixPerMM,
		"���������ž����������޹�˾");
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_strOperatorName;
	str.Format("����Ա:%s",str);
	memDC.TextOut(rect1.left+75*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineModel;
	str.Format("�����ͺ�:%s",str);
	memDC.TextOut(rect1.left+115*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineName;
	str.Format("����:%s",str);
	memDC.TextOut(rect1.left+155*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strProcess;
	str.Format("����:%s",str);
	memDC.TextOut(rect1.left+195*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceModel;
	str.Format("�����ͺ�:%s",str);
	memDC.TextOut(rect1.left+15*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceNum;
	str.Format("�������:%s",str);
	memDC.TextOut(rect1.left+75*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strIndent;
	str.Format("����:%s",str);
	memDC.TextOut(rect1.left+135*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strInspector;
	str.Format("���Ա:%s",str);
	memDC.TextOut(rect1.left+195*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);

	double gridleft=(rect1.right-rect1.left)*2/3+rect1.left;
	int gridxnums=1;int gridynums=22;//һ��25��
	double dx= ((rect1.right-rect1.left)-gridleft)/gridxnums;//һ�еĿ���
	double dy=(rect1.bottom-rect1.top)/gridynums;//һ�еĸ߶�
    CRect gridRect(gridleft,rect1.top,gridleft+dx*gridxnums,rect1.top+dy*gridynums);
	
	memDC.FillSolidRect(gridleft,gridRect.top,rect1.right,dy,RGB(232,232,232));
	memDC.FillSolidRect(gridleft,gridRect.top+dy*5,rect1.right,dy,RGB(232,232,232));//��ָ���������ɫ
	memDC.FillSolidRect(gridleft,gridRect.top+dy*12,rect1.right,dy,RGB(232,232,232));
	
	for( int m0=0;m0<=0;m0++) //����gridxnums������                      
	{
		memDC.MoveTo(gridRect.left+m0*dx,gridRect.bottom);
		memDC.LineTo(gridRect.left+m0*dx,gridRect.top);
		memDC.MoveTo(rect1.right+m0*dx,rect1.bottom);
		memDC.LineTo(rect1.right+m0*dx,rect1.top);
	}
		
	for(int n=0;n<=gridynums;n++) //����gridynums������                        
	{
		memDC.MoveTo(gridRect.left,gridRect.top+n*dy);
		memDC.LineTo(rect1.right,gridRect.top+n*dy);
	}

    PrintCylinder();

	memDC.SetBkMode(TRANSPARENT); 
	int meter=4*m_penScale+rect1.top;
	int m1=gridleft+4*m_penScale;
	double m2=gridleft+dx/2;
	double m3=gridleft+dx-50;
	double mid=gridleft+dx/2-30;

	if (AngleZ%360>0)
	{
		SeeAngle=AngleZ%360;
	}
	else
	{
		SeeAngle=AngleZ%360;
	}

	
    m_Seeangle.Format("%d",SeeAngle);
	
    memDC.TextOut(mid-10*m_penScale,meter,"Բ���Ȳ������");
	
	memDC.TextOut(mid+20*m_penScale,dy*5+meter,"��������");
	memDC.TextOut(mid+20*m_penScale,dy*12+meter,"��������");
	
    memDC.TextOut(m1,dy+meter,"�ļ���");
	memDC.TextOut(m1,dy*2+meter,"����ʱ��");
	memDC.TextOut(m1,dy*6+meter,"�ο�����");                                       
	memDC.TextOut(m1,dy*7+meter,"�˲�������");                                              
	memDC.TextOut(m1,dy*8+meter,"�˲���Χ");    
	memDC.TextOut(m1,dy*9+meter,"�������");      
	memDC.TextOut(m1,dy*10+meter,"��ǰ�۲�Ƕ�");   
	
	
	memDC.TextOut(m1,dy*13+meter,"����Ҫ��");
	memDC.TextOut(m1,dy*14+meter,"Բ����");
// 	memDC.TextOut(m1,dy*15+meter,"����");
// 	memDC.TextOut(m1,dy*16+meter,"����");	

	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath2;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDC.TextOut((m1+m2)/2,dy*1+meter,str);
	str=m_time.Format("%Y-%m-%d %H:%M");
	memDC.TextOut((m2+m1)/2,dy*2+meter,str);
	
	memDC.TextOut(m2,dy*6+meter,"��С���˷�");
	memDC.TextOut(m2,dy*7+meter,"Gaussian");
	memDC.TextOut(m2,dy*8+meter,"2-50");
	
	
	memDC.TextOut(m3,dy*13+meter,"um");
	memDC.TextOut(m3,dy*14+meter,"um");
	memDC.TextOut(m3,dy*14+meter,"um");
// 	memDC.TextOut(m3,dy*15+meter,"um");
// 	memDC.TextOut(m3,dy*16+meter,"um"); 
	memDC.SetBkMode(TRANSPARENT); 
	str.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[1]);
	memDC.TextOut(m2,dy*13+meter,str);
	memDC.TextOut(m2,dy*14+meter,m_CYLT);
// 	memDC.TextOut(m2,dy*15+meter,m_CYLP);
// 	memDC.TextOut(m2,dy*16+meter,m_CYLV);
	str.Format("%d",m_IntJM);
	memDC.TextOut(m2,dy*9+meter,str);
	memDC.TextOut(m2,dy*10+meter,m_Seeangle+"��");
	
	pDC->BitBlt(tRect.left,tRect.top,tRect.right,tRect.bottom,&memDC,0,0,SRCCOPY); 
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
    memBitmap.DeleteObject();//�ͷ��ڴ��豸// TODO: Add your specialized code here and/or call the base class
	
	
}

void CDoCylinder::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFormView::OnPrepareDC(pDC, pInfo);
	pDC->SetMapMode(MM_ANISOTROPIC);
}

BOOL CDoCylinder::OnPreparePrinting(CPrintInfo* pInfo) 
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




void CDoCylinder::PrintCylinder()
{
	int scale=rect1.Width()/rect.Width();
	CPoint centerPoint=0;
	centerPoint.x=rect1.Width()*3/5/2+rect1.left;
	centerPoint.y=rect1.bottom/8+rect1.top;//���ǻ���Բ����z[0]�����ĵ㡣

	CPen CyPe1(PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDC.SelectObject(&CyPe1); 
	memDC.MoveTo(centerPoint.x,centerPoint.y+5*m_penScale);
    memDC.LineTo(centerPoint.x,rect1.top+20*m_penScale);
    CyPe1.DeleteObject();

	memDC.SetBkMode(TRANSPARENT); 
	memDC.TextOut(rect1.Width()*3/5+rect1.left-20*m_penScale,centerPoint.y-30*m_penScale,"Z(mm)");
    memDC.TextOut(rect1.left+5*m_penScale,centerPoint.y-30*m_penScale,"����");

	/////////////////////////////////////////////////////////////////////////////////////////////
	//���´���ʵ��Բ������������Բ����Ϣ�ļ��������Բ���ȵļ���/////////////////////////////////
	int     i=0,j=0,jmbtn;
	double  dis=0,z[JMNum],t[3600],bcondata[3600],acondata[3600],SumTs = 0.0,m_dCirMax,m_dCirMin;
	double  a=0,b=0,l=0,g=0,DR=0,p=0,CYLt,m_dCymax,m_dCymin,aa11[JMNum],bb11[JMNum],A0[JMNum],SumTss=0.0 ,a3=0.0,bb3=0.0,fls[JMNum];
    double  Gdw=0.0,diss=0.0;
    BOOL BTCHUL=0;
    //���ļ���ͼ
    ReadDataFromFile();
	
    BTCHUL=((CMainFrame*)AfxGetMainWnd())->JMCL; //��굥���Ľ���
    jmbtn=((CMainFrame*)AfxGetMainWnd())->m_SelectJM;
	
    //////////////////////////////////////////////
    diss=(rect1.Height()-(centerPoint.y-rect1.top)*3/2)/(m_IntJM-1);      //��ͼ�ĸ߶Ƚ���
    Gdw=2 * PI/m_IntPoint;
	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)	
		{ 
			t[j]=3.1415926*j/1800;
 			pem[i][j]=m_datayzd[j+1+i*m_IntPoint].data;
			jmdata[j]=pem[i][j];
            DRAWpem[i][j]=m_datayzd[j+1+i*m_IntPoint].data;
		}
        SubQKDataChuli(((CMainFrame*)AfxGetMainWnd())->m_fullPath2,m_IntPoint,i, !((CMainFrame*)AfxGetMainWnd())->m_bAutoQK, jmdata, Resdata);
		for (j=0;j<m_IntPoint;j++)	
		{  
		    pem[i][j]= Resdata[j];    
		}
	}

	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)	
		{  
			bcondata[j]=((pem[i][j]-2048)*10)/(G1*G2*4096)+1000;//ÿ3600�����ݽ���2-50���˲����������˲�֮������ݽ�����Ӧ����
            zz[i]=m_datayzd[j+1+i*m_IntPoint].height;        //��ȡ����߶���ֵ
		}
		z[m_IntJM-1-i]=i*diss;
		WLS_Filter(FilterMode, m_IntPoint, bcondata, acondata);     //�����˲�����
		for (j=0;j<m_IntPoint;j++)	
		{  
	    	Rr[i][j]=acondata[j];                          //�˲�֮�������
		}
	    a3=0 ,	bb3 = 0,SumTss = 0;
		for (j=0;j<m_IntPoint;j++)	
		{
		     a3 = a3+ Rr[i][j] * cos(j * Gdw);
		     bb3 =bb3 + Rr[i][j] * sin(j * Gdw);
			 SumTss= SumTss + Rr[i][j];
		}
		aa11[i]= 2 * a3/m_IntPoint;
		bb11[i] = 2 * bb3/m_IntPoint ;                   //��ʽ��������Ǹ����������С����Բ�ĺͰ뾶
		A0[i] = SumTss/m_IntPoint;
	}

	double xx,yy;
	double jiaodianx,jiaodiany;
     yy=bb11[m_IntJM-1]-bb11[0];
     xx=aa11[m_IntJM-1]-aa11[0];
	 jiaodianx=centerPoint.x;
	 jiaodiany=(yy/xx)*jiaodianx;

	 for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)	
		{  	
		m_dfls[i][j] = Rr[i][j]-(aa11[i] * cos(j * Gdw) + bb11[i] * sin(j * Gdw)) - A0[i] ; //2-50�˲�֮���Բ��
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
       fls[i]=m_dCirMax-m_dCirMin;    //���������Բ��ֵ
	}
	/////////////////��ȡ�����Сֵ���ڻ�ͼ/////////////////////////////////
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
			 r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*(rout-rin)/m_OutIn+RSLC; //����Բ�ȴ��ʱ��������ʾ
			 
		 }
	}
    ////////////////////////////////////////////////////////////
    //////////����ʵ�ָ�˹�����Է��������Բ����/////////////////////////////////////////////
    //����������
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
	//' ����		
    double AA[6][6]={ {a111, a122, a13, a14, a15, a16},{a211, a222, a23, a24, a25, a26},{a31, a32, a33, a34, a35, a36},{a41, a42, a43, a44, a45, a46},{a51, a52, a53, a54, a55, a56},{a61, a62, a63, a64, a65, a66}};
    double AAB[6]={BB11,BB22,BB33,BB44,BB55,BB66};
    double X0[6]={1,1,1,1,1,1};
    double XA[6]={0,0,0,0,0,0};
    double delx=100;
	int timecalcute=0;

	//���ϴ���ʵ�����Է�����Ĺ��죬AA*XA=AAB
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
			  if ( (XA[i + 1] - X0[i + 1]) <= fabs(XA[i] - X0[i]) )
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
    //    '  �����֪������
	double XX0=0.0,YY0=0.0,ZZ0=0.0,AA0=0.0,BB0=0.0,CC0=0.0,Rc=0.0,Kc=0.0;
   	XX0 = XA[0],YY0= XA[1],ZZ0 = 0,AA0= XA[2],BB0 = XA[3],CC0 = 1,Rc = XA[4],Kc = XA[5];//��������ֵ

	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)
		{
			//�����㵽�������ߵľ���
	        dis1[i][j] = sqrt( ( ((yp[i][j] - YY0) * CC0 - (zz[i] - ZZ0) * BB0)* ((yp[i][j] - YY0) * CC0 - (zz[i] - ZZ0) * BB0) +((zz[i] - ZZ0) * AA0 - (xp[i][j] - XX0) * CC0)* ((zz[i] - ZZ0) * AA0 - (xp[i][j] - XX0) * CC0)+ ((xp[i][j] - XX0) * BB0 - (yp[i][j]- YY0) * AA0)*((xp[i][j] - XX0) * BB0 - (yp[i][j]- YY0) * AA0)  ) / ( AA0*AA0 + BB0* BB0 + CC0*CC0 ));
	    	xi[i][j] = XX0 +  AA0* zz[i];
	    	yi[i][j] = YY0 + BB0* zz[i];
            //�����Rij����Ҫ���м�ȥe��kz��Ӱ�졣
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
   	CYLt=m_dCymax +m_dCymin; //Բ�������
    m_CYLT.Format("%.3f",CYLt);
    m_CYLP.Format("%.2f",m_dCymax);
    m_CYLV.Format("%.2f",m_dCymin);
    /////////////////���ϴ���ʵ��Բ�������ļ���///////////////////////

	double PV=CYLt;	 
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
			//		r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*ratio*(rout-rin)/m_OutIn+RSLC; //����Բ�ȴ��ʱ��������ʾ
		
			//	r[i][j]=((CMainFrame*)AfxGetMainWnd())->m_OutIn*(DRAWpem[i][j]-m_Middle)*ratio*0.014/(rect.Height()*0.8/10)*(rout-rin)/m_OutIn+RSLC; 
			r[i][j]=(((CMainFrame*)AfxGetMainWnd())->m_OutIn*((DRAWpem[i][j]-m_Middle))*ratio*0.1*(rout-rin)/(rect.Height()*m_OutIn))+RSLC;///ok
		}
	}
	for (i=0;i<m_IntJM;i++) 
	{
		for (j=0;j<m_IntPoint;j++)
		{
			r[i][j]=1.5*r[i][j];
		}
		
	}
    /////////////////���´���ʵ��Բ������ͼ�ε���ʾ//////////////////////
	C3dPoint TPoint[4],p3,meanup,meandown;
    CLine    a1,a2,b1,b2;
    int      m_IStep=10;
	double   Rz[3][3],PI=3.1415926;
	CString  m_jiemian, m_heightZ;
	int jy;

	for (i=0;i<m_IntJM;i++)
	{
		m_jiemian.Format("%d",i+1);
		m_heightZ.Format("%.1f",zz[i]);
		{		
			Z3DRondness[i][j].x=(r[i][j])*cos(j*Gdw);//������
			Z3DRondness[i][j].y=(r[i][j])*sin(j*Gdw);//������ ����    
			Z3DRondness[i][j].z=z[i];
			
			Z2DRondness[i][j]=Z3DRondness[i][j].Change();
			memDC.SetBkMode(TRANSPARENT); 
			XJM[i][j]=rect1.left+10*m_penScale;
			YJM[i][j]=Z2DRondness[i][j].y+centerPoint.y;
			memDC.TextOut(XJM[i][j],YJM[i][j]-10,"M"+m_jiemian);//��Բ���������ʾ������
			
			XJM[i][j]=rect1.Width()*3/5+rect1.left;
			YJM[i][j]=Z2DRondness[i][j].y+centerPoint.y;
			memDC.TextOut(XJM[i][j],YJM[i][j]-10,m_heightZ);  //��Բ�����ұ���ʾ����߶�
			
		}
	}
	//��С�������Բ��
    C3dPoint POINT[3600];
	double s11=0,s12=0,s13=0,s22=0,s23=0,x0,y0,z0;
    double sumx2=0,sumx=0,sumy2=0,sumy=0,sumxy=0,sumx2y2=0,sumxx2y2=0,sumyx2y2=0;
	for (j=0;j<m_IntPoint;j++)
	{
		POINT[j].x=(r[m_IntJM-1][j])*cos(j * Gdw);//������
		POINT[j].y=(r[m_IntJM-1][j])*sin(j * Gdw);//������     ����
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

   ////Բ����С����ͼ���//////////////////////////////////
    for (i=0;i<m_IntJM-1;i++)
	{
		for (j=0;j<m_IntPoint-m_IStep;j+=m_IStep)	
		{
				
		        TPoint[0].x=(r[i+1][j])*cos(j * Gdw)-x0;//������
		        TPoint[0].y=(r[i+1][j])*sin(j * Gdw)-y0;//������     ����
		        TPoint[0].z=z[i+1]-z0;	

		        TPoint[1].x=(r[i][j])*cos(j * Gdw)-x0;//������
		        TPoint[1].y=(r[i][j])*sin(j * Gdw)-y0;//������ ����     
	            TPoint[1].z=z[i]-z0;
	
				TPoint[2].x=(r[i][j+m_IStep])*cos((j+m_IStep)*Gdw)-x0;//������
				TPoint[2].y=(r[i][j+m_IStep])*sin((j+m_IStep)*Gdw)-y0;//������   ����
				TPoint[2].z=z[i]-z0;	
		
				TPoint[3].x=(r[i+1][j+m_IStep])*cos((j+m_IStep)*Gdw)-x0;//������
				TPoint[3].y=(r[i+1][j+m_IStep])*sin((j+m_IStep)*Gdw)-y0;//������   ����    
				TPoint[3].z=z[i+1]-z0;	
             
				p3.x=(r[i][(j+m_IStep)/2])*cos((j+m_IStep)*Gdw/2)-x0;//������
				p3.y=(r[i][(j+m_IStep)/2])*sin((j+m_IStep)*Gdw/2)-y0;//������    
				p3.z=(z[i]+z[i+1])/2-z0;	

			    Rotate(TPoint[0].x,TPoint[0].y,TPoint[0].z);
				Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z); //������ת����ֱ�ӽ�����ת��Ϊ��ת֮�������  
			    Rotate(TPoint[2].x,TPoint[2].y,TPoint[2].z);
				Rotate(TPoint[3].x,TPoint[3].y,TPoint[3].z);   
				Rotate(p3.x,p3.y,p3.z);		
				/////////////////���¼��д���ʵ��Բ��������ڵ�///////////////////////////
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
					if (m_datayzd[j+1+i*m_IntPoint].selected==1) //�ֶ�����ѡ�У���Ϊ��ɫ
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
 
					else                            //������ʾ��ɫ
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
for (i=0;i<m_IntJM-1;i++)
   {		   
		   TPoint[0].x=(r[i+1][j])*cos(j * Gdw)-x0;//������
		   TPoint[0].y=(r[i+1][j])*sin(j * Gdw)-y0;//������     ����
		   TPoint[0].z=z[i+1]-z0;	
		   
		   TPoint[1].x=(r[i][j])*cos(j * Gdw)-x0;//������
		   TPoint[1].y=(r[i][j])*sin(j * Gdw)-y0;//������ ����     
		   TPoint[1].z=z[i]-z0;
		   
		   TPoint[2].x=(r[i][0])*cos((0)*Gdw)-x0;//������
		   TPoint[2].y=(r[i][0])*sin((0)*Gdw)-y0;//������   ����
		   TPoint[2].z=z[i]-z0;	
		   
		   TPoint[3].x=(r[i+1][0])*cos((0)*Gdw)-x0;//������
		   TPoint[3].y=(r[i+1][0])*sin((0)*Gdw)-y0;//������   ����    
		   TPoint[3].z=z[i+1]-z0;	
		   
		   p3.x=(r[i][(m_IntPoint+j)/2])*cos((m_IntPoint+j)*Gdw/2)-x0;//������
		   p3.y=(r[i][(m_IntPoint+j)/2])*sin((m_IntPoint+j)*Gdw/2)-y0;//������    
		   p3.z=(z[i]+z[i+1])/2-z0;	
		 
		   Rotate(TPoint[0].x,TPoint[0].y,TPoint[0].z);
		   Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z); //������ת����ֱ�ӽ�����ת��Ϊ��ת֮�������
		   Rotate(TPoint[2].x,TPoint[2].y,TPoint[2].z);
		   Rotate(TPoint[3].x,TPoint[3].y,TPoint[3].z);
		   Rotate(p3.x,p3.y,p3.z);	
		   /////////////////���¼��д���ʵ��Բ��������ڵ�///////////////////////////
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
				   
				   b2.Draw(&memDC,centerPoint);
				   a1.Draw(&memDC,centerPoint);
				   b1.Draw(&memDC,centerPoint);	
			   }

		   }

   }
   ////����������İ�Բ,������İ��Բ��û�б��ڵ�
   for (j=0;j<m_IntPoint-m_IStep;j++)
   {		
	    TPoint[1].x=(r[m_IntJM-1][j])*cos(t[j])-x0;//������
	    TPoint[1].y=(r[m_IntJM-1][j])*sin(t[j])-y0;//������      
    	TPoint[1].z=z[m_IntJM-1]-z0;
	    Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z);

		TPoint[2].x=(r[m_IntJM-1][j+m_IStep])*cos(t[j+m_IStep])-x0;//������
		TPoint[2].y=(r[m_IntJM-1][j+m_IStep])*sin(t[j+m_IStep])-y0;//������      
		TPoint[2].z=z[m_IntJM-1]-z0;
		Rotate(TPoint[2].x,TPoint[2].y,TPoint[2].z);	
	
		TPoint[1].x=TPoint[1].x*scale;
		TPoint[1].y=TPoint[1].y*scale;
		TPoint[2].x=TPoint[2].x*scale;
		TPoint[2].y=TPoint[2].y*scale;	
		a1.a=1*m_penScale;
		a1.b=2*m_penScale;
		a2.a=1*m_penScale;
		a2.b=2*m_penScale;
		b1.a=1*m_penScale;
		b1.b=2*m_penScale;
		b2.a=1*m_penScale;
	    b2.b=2*m_penScale;
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
}

void CDoCylinder::OnBtntbegin() 
{
	// TODO: Add your command handler code here
	SetTimer(1,300,NULL);
}

void CDoCylinder::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	AngleZ+=5;
	OnPaint();
	CFormView::OnTimer(nIDEvent);
}

void CDoCylinder::OnBtntstop() 
{
	// TODO: Add your command handler code here
	KillTimer(1);
}

void CDoCylinder::OnAmplifyScale() 
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
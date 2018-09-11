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
	m_strMethod="��С���˷�";
	FilterMode=3;
	m_intNumOfPlaneness=1;
	//}}AFX_DATA_INIT
	CirEvalue=0;//�����㷨
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
    dc.FillSolidRect(rectback,RGB(255,255,255));  //����Ϊ��ɫ����

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
    //////////////////////���///////////////////////////////
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
	mDC.FillSolidRect(l1+fw1,l2,fw2,dy,RGB(232,232,232));//��ͷ�������ɫ
 	mDC.FillSolidRect(l1+fw1,l2+dy*5,fw2,dy,RGB(232,232,232));//��ָ���������ɫ
 	mDC.FillSolidRect(l1+fw1,l2+dy*9,fw2,dy,RGB(232,232,232));//��ָ���������ɫ

	for(int m=0;m<=gridxnums;m++) //����gridxnums������                      
	{
		mDC.MoveTo(l1+fw1+m*dx,gridRect.bottom);
		mDC.LineTo(l1+fw1+m*dx,0);
	}

	for(int n=0;n<=gridynums;n++) //����gridynums������                        
	{
		mDC.MoveTo(l1+fw1,n*dy);
		mDC.LineTo(l1+fw1+fw2,n*dy);
	}
	int i;
	//��ȡ����
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
	//���Ʊ���
   	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  
	CFont*   pOldFont=(CFont*)mDC.SelectObject(&font); 
   
    mDC.SetBkMode(TRANSPARENT); 
	int meter=dy/10;
	int m1=l1+fw1+fw2/30;
	double m2=l1+fw1+dx*0.45;
	double m3=l1+fw1+dx*0.66;
	double mid=l1+fw1+dx*0.4;

    mDC.TextOut(mid ,l2+meter,"ƽ��Ȳ������");

	mDC.TextOut(mid,l2+dy*5+meter,"���Ҫ��");
	mDC.TextOut(mid,l2+dy*9+meter,"��������");

    mDC.TextOut(m1,l2+dy+meter,"�ļ���");
	mDC.TextOut(m1,l2+dy*2+meter,"����ʱ��");
	mDC.TextOut(m1,l2+dy*6+meter,"�ο�����");                                       
	mDC.TextOut(m1,l2+dy*7+meter,"�˲�������");                                              
	mDC.TextOut(m1,l2+dy*8+meter,"�˲���Χ");    
                                                 
                     	
	mDC.TextOut(m1,l2+dy*10+meter,"����Ҫ��");
	mDC.TextOut(m1,l2+dy*11+meter,"ƽ���");
 
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath5;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	mDC.TextOut(m2,dy*1+meter,str);
	//��ʾ����ʱ��
	CString strText=m_t.Format("%Y-%m-%d %H:%M");
	mDC.TextOut(m2,dy*2+meter,strText);

	mDC.TextOut(m2,dy*6+meter,m_strMethod);
	mDC.TextOut(m2,dy*7+meter,"Gaussian");
	mDC.TextOut(m2,dy*8+meter,m_strlvbo);
	strText.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[4]);
	mDC.TextOut(m2,dy*10+meter,strText);
	mDC.TextOut(m3,dy*10+meter,"um");
	mDC.TextOut(m3,dy*11+meter,"um");
 	//����ͼ��
	C3dPoint pt3[4]; 
	CPoint pts[4];
	CPoint centerPoint(rect.Width()*0.667/2,rect.Height()*3/5);
	BYTE r3; 
	BYTE g3; 
	BYTE b3;
	int endNum=0;
 	//����߶Ⱥͻ�ͼ�ļ��
	int intHeight=rect.Height()*0.2;
	int dwidth=4;
	int intMinRadius=rect.Width()*0.6/5;
	int intMaxRadius=rect.Width()*0.6/2;

	//�����ӵ�
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
	//������ֱ����ϵ
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
	str+="um/ÿ��";
//	mDC.TextOut(centerPoint.x,centerPoint.y-rect.Height()*0.55,str);
	mDC.TextOut(centerPoint.x+rect.Height()/3,rect.bottom-rect.Height()/30,str);
	mDC.TextOut(centerPoint.x-R,centerPoint.y-rect.Height()*0.55,"�������");

	//���Ʊ�ʶͼ
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
	SubAnaData (3, Resdata,GResult,G1,G2);	//Բ��
	m_strpmd.Format("%.3f",GResult[1]); //�����ݽ��ת�����ַ�������ʽ��������ʾ�ڱ����

	mDC.SetTextColor(RGB(0,0,0));//��ɫ����      
    mDC.TextOut(m2,dy*11+meter,m_strpmd);//������ʾƽ���

 	pDC->BitBlt(rect.left,rect.top,rect.right,rect.bottom,&mDC,0,0,SRCCOPY); //���Ѿ���õ�ͼ��ʾ���ƶ�λ����
    mDC.SelectObject(pOldBmp);
    mDC.DeleteDC();
    memBitmap.DeleteObject();//�ͷ��ڴ��豸
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
	GetPrivateProfileString ("�˲�","����1",NULL,inBuf,10,strPath);
	FilterMode=atoi(inBuf);
	GetPrivateProfileString ("�����㷨","����2",NULL,inBuf,10,strPath);
	CirEvalue=atoi(inBuf);
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
	//��ȡ�����ļ�
	m_Flagcircle=1;
	CPropertyDlg prop;
    if(IDOK==prop.DoModal())
	{
		FilterMode=prop.m_IntFilter; //�õ��˲�ѡ���ѡ������
		CirEvalue=prop.m_IntAlg;  //�õ�Բ����������ѡ�񷽷��ı��
		switch(FilterMode)
		{
	//	case 0: m_strlvbo="���˲�"; break;
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


/*
  �������ܣ��Զ����ֶ�ȱ�ڴ���
  �Զ�����ȱ�ڣ�
  �ֶ�����ȱ�ڡ�
  -----------------����˵��-------------------------
  ������ȱ�����ݴ���
  Number     ���ݸ���
  Soudata()  ����ǰ����
  Resdata()  ���������
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
void CDoPlaneness::SubQKDataChuli(CString path,int Number, double *Resdata,BOOL GManCuliQkFlag,int JM,int Totaldot)
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
	double Max, Min,Soudata[3600];
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

	shuju0 ManDeal[3600];//��ʱ�ṹ������
	std::ifstream fin(path,std::ios::binary);
	fin.read((char*)&m_data[0], sizeof(shuju0));
	for ( i=1;i<3601;i++)
	{	
		fin.read((char*)&m_data[i], sizeof(shuju0)); //��ȡ����
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
	 
	if (jLeft==0 && jRight==0  )
	  {
		goto Automode;
	  }
	  
    else /*(GManCuliQkFlag==true ) */
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
		// 'GPHWidthK ---ȱ��֮��ƽ�������ȱ���
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
                            ManDeal[j].selected=1;//���
						}
					}
					else 
					{
					  for(j=TempStart;j<Number;j++)
					  {	
						Soudata[j]=Soudata[TempStart]+TempK*(j-TempStart);
                        ManDeal[j].selected=1;//���
					  }
					for (j=0;j<=TempEnd;j++)
					{
	                    Soudata[j]=Soudata[TempStart]+TempK*(j + Number - TempStart);
                        ManDeal[j].selected=1;//���
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
	
	int Starti,Endi;//��С�γ���ʵ�����Զ�ȥȱ���Ժ�ӳ��ͼ�ν����ϵı仯
    for( i=1;i<=QkNumber;i++)
	{
       Starti=MinIndex[i]-GBzDot;
       Endi=MaxIndex[i]+ GBzDot;
   //    ChangeValueOfSelect(path,Starti,Endi,1);
	}


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
   Resdata()----------------------------------------- ���������
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
       // 'GPHWidthK ---ȱ��֮��ƽ�������ȱ���
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

// TODO: Add your message handler code here and/or call default
void CDoPlaneness::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
		// TODO: Add your message handler code here and/or call default
	CWnd *pWndCy; 
	CRect rectP; 
	CDC *pDCP;          
	pWndCy = GetDlgItem(IDC_Planeness);      
	pWndCy->GetClientRect(&rectP); 
	pWndCy->ClientToScreen(rectP);       //ת������Ļ����,���Ͻ�����Ϊ�ı�������Ļ������
	pDCP = pWndCy->GetDC();
	this->ClientToScreen(&point);          //ת��Ϊ��Ļ����
		
	point.x=point.x-rectP.left;         //��point�������������Ļ����ת��Ϊ����ھ�̬�����꣬��̬�����Ͻ���(0,0)
	point.y=point.y-rectP.top;
	
	CPoint centerPoint;
	centerPoint.x=(rectP.right-rectP.left)*0.667/2;
	centerPoint.y=(rectP.bottom-rectP.top)*3/5;//���ǻ���Բ����z[0]�����ĵ㡣
	int R=rectP.Width()*0.6/2.2;

	//����ͼ��
	if ( point.x>=(centerPoint.x-R) && point.x<=(centerPoint.x-0.2*R)
		&&point.y>= (centerPoint.y-rectP.Height()*0.55) && point.y<=(centerPoint.y-rectP.Height()*0.45))
	{	
		((CMainFrame*)AfxGetMainWnd())->m_fullJMPath=((CMainFrame*)AfxGetMainWnd())->m_fullPath5;//��ȡԲ���ȵ�·��
		((CMainFrame*)AfxGetMainWnd())->m_fullJMType=1;    //��������
		((CMainFrame*)AfxGetMainWnd())->m_fullJMNum=3600; 
		((CMainFrame*)AfxGetMainWnd())->m_SelectJM=0;//��굥���Ľ���
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
	//��ӡ��ĳߴ�Ϊ150*250(mm)
	CPoint pt(0,0);
	CSize  sz(270*xLogPixPerMM,200*yLogPixPerMM);
	CRect  tRect(pt,sz);
	rect1.top=tRect.top+25*yLogPixPerMM;
	rect1.right=tRect.right;
	rect1.left=tRect.left+20*xLogPixPerMM;
	rect1.bottom=tRect.bottom-25*yLogPixPerMM;
	
	pOldBmp = NULL;                           // ���ɵ�λͼָ���ÿ�	
	memDC.CreateCompatibleDC(pDC);             // �����ڴ��ͼ�豸��ʹ�ڴ�λͼ��DC��ؼ���DC����
	memBitmap.CreateCompatibleBitmap(pDC,tRect.right,tRect.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap);
    memDC.FillSolidRect(tRect.left,tRect.top,tRect.right,tRect.bottom,RGB(255,255,255));//�����ο�����ɫ
	
	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	memDC.SelectObject(&RectPen);               
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

	
	double fw1=2*rect1.Width()/3;
	double f1=rect1.Width();
	double f2=rect1.Height();                                            	                             
    double fw2=1*rect1.Width()/3;	
    //////////////////////���///////////////////////////////
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
	memDC.FillSolidRect(l1+fw1,l2,fw2,dy,RGB(232,232,232));//��ͷ�������ɫ
 	memDC.FillSolidRect(l1+fw1,l2+dy*5,fw2,dy,RGB(232,232,232));//��ָ���������ɫ
 	memDC.FillSolidRect(l1+fw1,l2+dy*9,fw2,dy,RGB(232,232,232));//��ָ���������ɫ

	for(int m=0;m<=gridxnums;m++) //����gridxnums������                      
	{
		memDC.MoveTo(l1+fw1+m*dx,gridRect.bottom);
		memDC.LineTo(l1+fw1+m*dx,gridRect.top);
	}

	for(int n=0;n<=gridynums;n++) //����gridynums������                        
	{
		memDC.MoveTo(l1+fw1,l2+n*dy);
		memDC.LineTo(l1+fw1+fw2,l2+n*dy);
	}
	int i;
	//��ȡ����
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
	//���Ʊ���
  
    memDC.SetBkMode(TRANSPARENT); 
	int meter=dy/10;
	int m1=l1+fw1+fw2/30;
	double m2=l1+fw1+dx*0.45;
	double m3=l1+fw1+dx*0.66;
	double mid=l1+fw1+dx*0.4;

    memDC.TextOut(mid ,l2+meter,"ƽ��Ȳ������");

	memDC.TextOut(mid,l2+dy*5+meter,"���Ҫ��");
	memDC.TextOut(mid,l2+dy*9+meter,"��������");

    memDC.TextOut(m1,l2+dy+meter,"�ļ���");
	memDC.TextOut(m1,l2+dy*2+meter,"����ʱ��");
	memDC.TextOut(m1,l2+dy*6+meter,"�ο�����");                                       
	memDC.TextOut(m1,l2+dy*7+meter,"�˲�������");                                              
	memDC.TextOut(m1,l2+dy*8+meter,"�˲���Χ");    
                                                 
                     	
	memDC.TextOut(m1,l2+dy*10+meter,"����Ҫ��");
	memDC.TextOut(m1,l2+dy*11+meter,"ƽ���");
 
	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath5;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	memDC.TextOut(m2,l2+dy*1+meter,str);
	//��ʾ����ʱ��
	CString strText=m_t.Format("%Y-%m-%d %H:%M");
	memDC.TextOut(m2,l2+dy*2+meter,strText);

	memDC.TextOut(m2,l2+dy*6+meter,m_strMethod);
	memDC.TextOut(m2,l2+dy*7+meter,"Gaussian");
	memDC.TextOut(m2,l2+dy*8+meter,m_strlvbo);
	strText.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[4]);
	memDC.TextOut(m2,l2+dy*10+meter,strText);
	memDC.TextOut(m3,l2+dy*10+meter,"um");
	memDC.TextOut(m3,l2+dy*11+meter,"um");
	//����ͼ��
	C3dPoint pt3[4]; 
	CPoint pts[4];
	CPoint centerPoint(rect1.left+rect1.Width()*0.667/2,rect1.top+rect1.Height()*3/5);
	BYTE r3; 
	BYTE g3; 
	BYTE b3;
	int endNum=0;
	//����߶Ⱥͻ�ͼ�ļ��
	int intHeight=rect1.Height()*0.2;
	int dwidth=4;
	int intMinRadius=rect1.Width()*0.6/5;
	int intMaxRadius=rect1.Width()*0.6/2;

	//�����ӵ�
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
	//������ֱ����ϵ
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
	str+="um/ÿ��";
//	memDC.TextOut(centerPoint.x,centerPoint.y-rect1.Height()*0.55,str);
	memDC.TextOut(centerPoint.x+rect1.Height()/3,rect1.bottom-rect1.Height()/30,str);
	memDC.TextOut(centerPoint.x-R,centerPoint.y-rect1.Height()*0.55,"�������");

	//���Ʊ�ʶͼ
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
	SubAnaData (3, Resdata,GResult,G1,G2);	//Բ��
	m_strpmd.Format("%.3f",GResult[1]); //�����ݽ��ת�����ַ�������ʽ��������ʾ�ڱ����

	memDC.SetTextColor(RGB(0,0,0));//��ɫ����      
    memDC.TextOut(m2,l2+dy*11+meter,m_strpmd);//������ʾƽ���

	pDC->BitBlt(tRect.left,tRect.top,tRect.right,tRect.bottom,&memDC,0,0,SRCCOPY);  //���Ѿ���õ�ͼ��ʾ���ƶ�λ����
    memDC.SelectObject(pOldBmp);
    memDC.DeleteDC();
    memBitmap.DeleteObject();//�ͷ��ڴ��豸


	
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



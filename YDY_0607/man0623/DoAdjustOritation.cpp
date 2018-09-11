// DoAdjustOritation.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DoAdjustOritation.h"
#include "MainFrm.h"
#include "const.h"
#include "math.h"
#include "3dPoint.h"
#include "Line.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoAdjustOritation

IMPLEMENT_DYNCREATE(CDoAdjustOritation, CFormView)

CDoAdjustOritation::CDoAdjustOritation()
	: CFormView(CDoAdjustOritation::IDD)
{
	//{{AFX_DATA_INIT(CDoAdjustOritation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	AngleZ=0;
	FilterMode=3;
}

CDoAdjustOritation::~CDoAdjustOritation()
{
}

void CDoAdjustOritation::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoAdjustOritation)
	DDX_Control(pDX, IDC_STATIC_AdjustOritation, m_AdjustOritation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoAdjustOritation, CFormView)
	//{{AFX_MSG_MAP(CDoAdjustOritation)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_COMMAND(ID_BTNTLEFT, OnBtntleft)
	ON_COMMAND(ID_BTNTRIGHT, OnBtntright)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_COMMAND(ID_BTNTBEGIN, OnBtntbegin)
	ON_COMMAND(ID_BTNTSTOP, OnBtntstop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoAdjustOritation diagnostics

#ifdef _DEBUG
void CDoAdjustOritation::AssertValid() const
{
	CFormView::AssertValid();
}

void CDoAdjustOritation::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoAdjustOritation message handlers

void CDoAdjustOritation::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rectFill;
    GetClientRect(rectFill);
    dc.FillSolidRect(rectFill,RGB(255,255,255));  //����Ϊ��ɫ���� 

   	pWndPicture = GetDlgItem(IDC_STATIC_AdjustOritation);      // ��öԻ����ϵ�picture�Ĵ��ھ��
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

    //======================================
	double gridleft=rect.Width()*2/3;
	int gridxnums=1;int gridynums=22;
	double dx= (rect.Width()-gridleft)/gridxnums;
	double dy=rect.Height()/gridynums;
    CRect gridRect(gridleft,rect.top,rect.left+dx*gridxnums,rect.top+dy*gridynums);
	CPen gridPen(0,0,RGB(0,0,20));
	//mDC.FillSolidRect(dx*3,dy*12,dx,dy,RGB(139,216,224));//��ָ�����������ɫ

	memDC.FillSolidRect(gridleft,0,gridRect.right-1,dy,RGB(232,232,232));//��ͷ�������ɫ
	memDC.FillSolidRect(gridleft,dy*5,gridRect.right-1,dy,RGB(232,232,232));//��ָ���������ɫ
	memDC.FillSolidRect(gridleft,dy*13,gridRect.right-1,dy,RGB(232,232,232));//��ָ���������ɫ

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
	memDC.SetTextColor(RGB(0,0,0));//��ɫ���� 
    memDC.TextOut(mid-10,meter,"�Զ����ĵ�ƽ���");
	memDC.TextOut(m1,dy+meter,"��������");
	memDC.TextOut(m1,dy*2+meter,"��ƫ��");
	memDC.TextOut(m1,dy*3+meter,"��ƫ�ĽǶ�");
	memDC.TextOut(m1,dy*4+meter,"��ƫ��");
	memDC.TextOut(m1,dy*5+meter,"��ƫ�ĽǶ�");

	CString str;
	str.Format("%d/%d",((CMainFrame*)AfxGetMainWnd())->m_fintTimes,
		               ((CMainFrame*)AfxGetMainWnd())->m_intTimes);//
	memDC.TextOut(m2,dy+meter,str);
	str.Format("%.1f",m_up_YZdEcc);
	memDC.TextOut(m2,dy*2+meter,str);
	memDC.TextOut(m3,dy*2+meter,"um");
	str.Format("%.1f",m_up_YZdEccPos);
	memDC.TextOut(m2,dy*3+meter,str);
	memDC.TextOut(m3,dy*3+meter,"��");
	str.Format("%.1f",m_down_YZdEcc);
	memDC.TextOut(m2,dy*4+meter,str);
	memDC.TextOut(m3,dy*4+meter,"um");
	str.Format("%.1f",m_down_YZdEccPos);
	memDC.TextOut(m2,dy*5+meter,str);
	memDC.TextOut(m3,dy*5+meter,"��");

	pDCPicture->BitBlt(rect.left,rect.top,rect.right,rect.bottom,&memDC,0,0,SRCCOPY); 
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
	memBitmap.DeleteObject();
}

void CDoAdjustOritation::OnDestroy() 
{
	CFormView::OnDestroy();
	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->DestroyVIEW(((CMainFrame*)AfxGetMainWnd())->m_DoAdjustOritation);
	((CMainFrame*)AfxGetMainWnd())->m_DoAdjustOritation=NULL;
	((CMainFrame*)AfxGetMainWnd())->Desktop();
}

void CDoAdjustOritation::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	if (m_AdjustOritation.GetSafeHwnd())
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
		m_AdjustOritation.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}
}

void  CDoAdjustOritation::Rotate(double &x, double &y, double &z) 
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

void CDoAdjustOritation::DrawCylinder()//��Բ��
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

	//���´���ʵ��Բ������������Բ����Ϣ�ļ��������Բ���ȵļ���/////////////////////////////////
	int     i=0,j=0;
	double  dis=0,z[JMNum],zz[JMNum],t[3600],bcondata[3600],acondata[3600],SumTs = 0.0,m_dCirMax,m_dCirMin;
	double  a=0,b=0,l=0,g=0,DR=0,p=0,CYLt,m_dCymax,m_dCymin,aa11[JMNum],bb11[JMNum],A0[JMNum],SumTss=0.0 ,a3=0.0,bb3=0.0,fls[JMNum];
    double  Gdw=0.0,diss=0.0,m_sumryzd,m_RYZD[5];

	//------------------��ȡԲ���������������-------------------
	m_IntJM=2,m_IntPoint=3600,m_FullData=m_IntJM*m_IntPoint;

	G1=((CMainFrame*)AfxGetMainWnd())->G11;//��ȡ����������G1
    G2=((CMainFrame*)AfxGetMainWnd())->G22;//��ȡ����������G2
	m_down_YZdEcc=((CMainFrame*)AfxGetMainWnd())->m_down_pxin*1000;//�½���ƫ����
    m_down_YZdEccPos=((CMainFrame*)AfxGetMainWnd())->m_down_angle;//�½���ƫ�Ľ�
	zz[0]=((CMainFrame*)AfxGetMainWnd())->m_old_lzhupulse*0.004;
	zz[1]=((CMainFrame*)AfxGetMainWnd())->m_old_lzhupulse*0.004+
		((CMainFrame*)AfxGetMainWnd())->m_dHeight;

	m_up_YZdEcc=((CMainFrame*)AfxGetMainWnd())->m_up_pxin*1000;//�Ͻ���ƫ����
    m_up_YZdEccPos=((CMainFrame*)AfxGetMainWnd())->m_up_angle;//�Ͻ���ƫ�Ľ�

	
	for(i=0;i<m_IntPoint;i++)	
	{
        m_datayzd[i].data=((CMainFrame*)AfxGetMainWnd())->m_down_circledata[i];//��Բ��Բ����������
	}
	
	for(i=m_IntPoint;i<m_FullData;i++)	
	{
		m_datayzd[i].data=((CMainFrame*)AfxGetMainWnd())->m_up_circledata[i-3600];//��Բ��Բ����������
	}
    diss=(rect.bottom-centerPoint.y*3/2)/(m_IntJM-1);                //��ͼ�ĸ߶Ƚ���
    Gdw=2 * PI/m_IntPoint;


	for (i=0;i<m_IntJM;i++)   
	{	
		for (j=0;j<m_IntPoint;j++)	
		{  
			t[j]=3.1415926*j/1800;
			pem[i][j]=m_datayzd[j+i*m_IntPoint].data;
			bcondata[j]=((pem[i][j]-2048)*10)/(G1*G2*4096)+1000;//ÿ3600�����ݽ���2-50���˲����������˲�֮������ݽ�����Ӧ����
            //zz[i]=m_datayzd[j+i*m_IntPoint].height*1000;        //��ȡ����߶���ֵ
		}
		z[m_IntJM-1-i]=i*diss;
		WLS_Filter(5, m_IntPoint, bcondata, acondata);     //�����˲�����
		for (j=0;j<m_IntPoint;j++)	
		{  
	    	Rr[i][j]=acondata[j];                          //�˲�֮�������
		}
	    a3=0 ,	bb3 = 0,SumTss = 0,m_sumryzd=0;
		for (j=0;j<m_IntPoint;j++)	
		{
		     a3 = a3+ Rr[i][j] * cos(j * Gdw);
		     bb3 =bb3 + Rr[i][j] * sin(j * Gdw);
			 SumTss= SumTss + Rr[i][j];
			 m_sumryzd=m_sumryzd+pem[i][j];
		}
		aa11[i]= 2 * a3/m_IntPoint;
		bb11[i] = 2 * bb3/m_IntPoint  ;                    //��ʽ��������Ǹ����������С����Բ�ĺͰ뾶
		A0[i] = SumTss/m_IntPoint;
		m_RYZD[i]=m_sumryzd/m_IntPoint;
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
    double m_m_OutIn=0.0,rout=280,rin=120,m_OutIn=0.0,RSLC=200;
	double m_datamin=0.0, m_datamax=0.0;

	m_datamin=0;
	m_datamax=4096;
	m_OutIn=m_datamax-m_datamin;
	//��������ĺᡢ������
	for (i=0;i<m_IntJM;i++)   
	{	
		 for (j=0;j<m_IntPoint;j++)	
		 { 
	      	 r[i][j]=(pem[i][j]-m_RYZD[i])*(rout-rin)/m_OutIn+RSLC; //����Բ�ȴ��ʱ��������ʾ

		 }
	}
   
    /////////////////���ϴ���ʵ��Բ�������ļ���///////////////////////
    /////////////////���´���ʵ��Բ������ͼ�ε���ʾ//////////////////////
	C3dPoint TPoint[4],p3;
    CLine    a1,a2,b1,b2;
    int      m_IStep=10;
	double   Rz[3][3],PI=3.1415926;
	CString  m_jiemian, m_heightZ;
    //ѡת����
    Rz[0][0]=cos(AngleZ/180.0*PI);  
	Rz[0][1]=sin(AngleZ/180.0*PI),    
	Rz[0][2]=0;

    Rz[1][0]=-sin(AngleZ/180.0*PI);  
	Rz[1][1]=cos(AngleZ/180.0*PI) ,      
	Rz[1][2]=0;

    Rz[2][0]=0;                   
    Rz[2][1]=0,                            
	Rz[2][2]=1;
   ////Բ����С����ͼ���//////////////////////////////////
    for (i=0;i<m_IntJM-1;i++)
	{
		for (j=0;j<m_IntPoint-m_IStep;j+=m_IStep)	
		{
				
		        TPoint[0].x=(r[i+1][j])*cos(j * Gdw);//������
		        TPoint[0].y=(r[i+1][j])*sin(j * Gdw);//������     ����
		        TPoint[0].z=z[i+1];	

		        TPoint[1].x=(r[i][j])*cos(j * Gdw);//������
		        TPoint[1].y=(r[i][j])*sin(j * Gdw);//������ ����     
	            TPoint[1].z=z[i];
	
				TPoint[2].x=(r[i][j+m_IStep])*cos((j+m_IStep)*Gdw);//������
				TPoint[2].y=(r[i][j+m_IStep])*sin((j+m_IStep)*Gdw);//������   ����
				TPoint[2].z=z[i];	
		
				TPoint[3].x=(r[i+1][j+m_IStep])*cos((j+m_IStep)*Gdw);//������
				TPoint[3].y=(r[i+1][j+m_IStep])*sin((j+m_IStep)*Gdw);//������   ����    
				TPoint[3].z=z[i+1];	
             
				p3.x=(r[i][(j+m_IStep)/2])*cos((j+m_IStep)*Gdw/2);//������
				p3.y=(r[i][(j+m_IStep)/2])*sin((j+m_IStep)*Gdw/2);//������    
				p3.z=(z[i]+z[i+1])/2;	

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

   
   ////���������µľ�����//////////////////////////////////////
   for (i=0;i<m_IntJM-1;i++)
   {		   
		   TPoint[0].x=(r[i+1][j])*cos(j * Gdw);//������
		   TPoint[0].y=(r[i+1][j])*sin(j * Gdw);//������     ����
		   TPoint[0].z=z[i+1];	
		   
		   TPoint[1].x=(r[i][j])*cos(j * Gdw);//������
		   TPoint[1].y=(r[i][j])*sin(j * Gdw);//������ ����     
		   TPoint[1].z=z[i];
		   
		   TPoint[2].x=(r[i][0])*cos((0)*Gdw);//������
		   TPoint[2].y=(r[i][0])*sin((0)*Gdw);//������   ����
		   TPoint[2].z=z[i];	
		   
		   TPoint[3].x=(r[i+1][0])*cos((0)*Gdw);//������
		   TPoint[3].y=(r[i+1][0])*sin((0)*Gdw);//������   ����    
		   TPoint[3].z=z[i+1];	
		   
		   p3.x=(r[i][(m_IntPoint+j)/2])*cos((m_IntPoint+j)*Gdw/2);//������
		   p3.y=(r[i][(m_IntPoint+j)/2])*sin((m_IntPoint+j)*Gdw/2);//������    
		   p3.z=(z[i]+z[i+1])/2;	
		   
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
	    TPoint[1].x=(r[m_IntJM-1][j])*cos(t[j]);//������
	    TPoint[1].y=(r[m_IntJM-1][j])*sin(t[j]);//������      
    	TPoint[1].z=z[m_IntJM-1];
	    Rotate(TPoint[1].x,TPoint[1].y,TPoint[1].z);

		TPoint[2].x=(r[m_IntJM-1][j+m_IStep])*cos(t[j+m_IStep]);//������
		TPoint[2].y=(r[m_IntJM-1][j+m_IStep])*sin(t[j+m_IStep]);//������      
		TPoint[2].z=z[m_IntJM-1];
				
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
  ////���³���������ȡ����������Ϣ  
  //memDC.SetTextColor(RGB(255,105,180));//��ɫ����   
  int jy;
  CPoint axisy,axis;
  C3dPoint AxiX;
  j=3000;
  jy=1500;
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
  //���Ƴ��������ߣ����Ҹ���Բ����ת
 ///////////////���´���ʵ��Բ��������������Ϣ����ȡ//////////////////////////
}


void CDoAdjustOritation::SubAnaData (int  FilterMode ,double *pMem,double *GResult,float m_Yd,float m_Tr)
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
// 	case 0 ://'���˲�
// 		   for( i = 0;i<3600 ;i++)
// 		   {
// 			   TsH[i] = TsQ[i];
// 		   }
// 			break;
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


void CDoAdjustOritation:: WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata)
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

void CDoAdjustOritation::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pActivateView==this)
	{
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(-1,FALSE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(5,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(6,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(13,TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(14,TRUE);
		
	}
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CDoAdjustOritation::OnBtntleft() 
{
	// TODO: Add your command handler code here
	AngleZ+=10;
	OnPaint();
}

void CDoAdjustOritation::OnBtntright() 
{
	// TODO: Add your command handler code here
	AngleZ-=10;
	OnPaint();
}

void CDoAdjustOritation::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd *pWndCy; 
	CRect rectCy; 
	CDC *pDCCy;          
	pWndCy = GetDlgItem(IDC_STATIC_AdjustOritation);      
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
			//			CCylAnalysis  CYAnalysis; 
			//          CYAnalysis.m_IntNumOfJIEMIAN=i;
			//			CYAnalysis.m_intyzJM=m_IntJM;
			//			CYAnalysis.G1=G1 ; 
			//			CYAnalysis.G2=G2;//���ĸ��������Դ��ⲿ��ȡ
			//          CYAnalysis.m1=m_IntPoint;
			//          CYAnalysis.LenDataJM=LenData;
			//			CYAnalysis.path=((CMainFrame*)AfxGetMainWnd())->m_fullPath2;
			//          CYAnalysis.DoModal();
			// 			OnPaint();
			((CMainFrame*)AfxGetMainWnd())->m_fullJMPath="654.cyd";//��ȡԲ���ȵ�·��
			((CMainFrame*)AfxGetMainWnd())->m_fullJMType=1;    //��������
			((CMainFrame*)AfxGetMainWnd())->m_fullJMNum=m_FullData; //��굥���Ľ���
            ((CMainFrame*)AfxGetMainWnd())->m_SelectJM=i;
			// ((CMainFrame*)AfxGetMainWnd())->G11=G1;
			// ((CMainFrame*)AfxGetMainWnd())->G22=G2;
			G1=((CMainFrame*)AfxGetMainWnd())->G11;
            G2=((CMainFrame*)AfxGetMainWnd())->G22;
			((CMainFrame*)AfxGetMainWnd())->DoJMAnalyse();
			OnPaint();
		}		
	}			
	CFormView::OnLButtonDblClk(nFlags, point);
}

void CDoAdjustOritation::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_AdjustOritation.GetSafeHwnd())
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
		m_AdjustOritation.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}
}

void CDoAdjustOritation::OnBtntbegin() 
{
	// TODO: Add your command handler code here
	
}

void CDoAdjustOritation::OnBtntstop() 
{
	// TODO: Add your command handler code here
	
}
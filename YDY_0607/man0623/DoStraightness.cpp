// DoStraightness.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DoStraightness.h"
#include "MainFrm.h"
#include <fstream>
#include "math.h"
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoStraightness

IMPLEMENT_DYNCREATE(CDoStraightness, CFormView)

CDoStraightness::CDoStraightness()
	: CFormView(CDoStraightness::IDD)
{
	//{{AFX_DATA_INIT(CDoStraightness)
	//}}AFX_DATA_INIT
	m_bDraw=false;
	m_LButtonUp=false;
	m_Height=50;

}

CDoStraightness::~CDoStraightness()
{
}

void CDoStraightness::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoStraightness)
	DDX_Control(pDX, IDC_LINE_STATIC, m_editStraightness);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoStraightness, CFormView)
	//{{AFX_MSG_MAP(CDoStraightness)
	ON_WM_DESTROY()
	ON_BN_CLICKED(ID_BTNDISABLE,OnSelectbutton)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(ID_BTNRESETDEAL,Onresetzxd)
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_BTNENABLE,OnSelectbutton)
	ON_BN_CLICKED(IDC_resetzxd, Onresetzxd)
	ON_COMMAND(ID_Print, OnPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoStraightness diagnostics

#ifdef _DEBUG
void CDoStraightness::AssertValid() const
{
	CFormView::AssertValid();
}

void CDoStraightness::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoStraightness message handlers

void CDoStraightness::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->DestroyVIEW(((CMainFrame*)AfxGetMainWnd())->m_DoStraightness);
	((CMainFrame*)AfxGetMainWnd())->m_DoStraightness=NULL;
	((CMainFrame*)AfxGetMainWnd())->Desktop();
}

void CDoStraightness::OnSelectbutton() 
{
	// TODO: Add your control notification handler code here

	if (m_lineselect==TRUE)
	{
		GetDlgItem(IDC_LINE_STATIC)->EnableWindow(FALSE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,TRUE);

	}
	else if (m_lineselect==FALSE)	
	{
		GetDlgItem(IDC_LINE_STATIC)->EnableWindow(TRUE);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,FALSE);

	}
	m_lineselect=!m_lineselect;
	
}

void CDoStraightness::OnAnalysisbutton() 
{
	// TODO: Add your control notification handler code here
	
}      

void CDoStraightness::OnPaint() 
{

	CPaintDC dc1(this); 
 	CRect rectback;
    GetClientRect(rectback);
    dc1.FillSolidRect(rectback,RGB(255,255,255));  //����Ϊ��ɫ����

    CWnd *pWnd; 
    CRect rect; 
    CDC *pDC;
    CDC mDC;                      //ȡ��ǰ���ڵ�CDC 
	pWnd = GetDlgItem(IDC_LINE_STATIC);      // ��öԻ����ϵ�picture�Ĵ��ھ��
	pWnd->GetClientRect(&rect); // ��ȡ����������ı���
	pDC = pWnd->GetDC();
	CBitmap* pOldBmp= NULL;     // ��öԻ����ϵ�picture���豸ָ��
	CBitmap memBitmap;
                                    
	mDC.CreateCompatibleDC(pDC);             // �����ڴ��ͼ�豸��ʹ�ڴ�λͼ��DC��ؼ���DC����
	memBitmap.CreateCompatibleBitmap(pDC,rect.right,rect.bottom);
	pOldBmp = mDC.SelectObject(&memBitmap);
    mDC.FillSolidRect(rect.left,rect.top,rect.right,rect.bottom,RGB(255,255,255));//�����ο�����ɫ   

	CPen RectPen(PS_SOLID,1,RGB(0,0,0));
	mDC.SelectObject(&RectPen);               
	mDC.Rectangle(rect.left,rect.top,rect.right+1,rect.bottom); //��̬����� �߿�
    RectPen.DeleteObject();


	//////////////////////////////////////////////////////////////////////

	CFont   font; 
	font.CreateFont(13,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  
	CFont*   pOldFont=(CFont*)mDC.SelectObject(&font); 

	double fw1=3*rect.Width()/5,f1=rect.Width(),f2=rect.Height();                                                 	                             
    double fw2=2*rect.Width()/5;
    double fh=rect.Height()/30;
    int i,j;
	double m_Y;
	double m_avescale;
    m_Y=f2-fh*2;
    m_avescale=m_Y/4;
    int m_mark[5]={360,270,180,90,0};
	CString mark;
	double m_smallavescale;
	m_smallavescale=m_Y/36;
	double f2h=f2-fh;
	double m_avesize;    //y��ƽ���ֳ�3600��	
	m_avesize=m_Y/3600;

	mDC.FillSolidRect(fw1/10,fh,fw1-fw1/5,f2-fh,RGB(255,255,255)); //ֱ�߶��������������ɫ
	if (m_StartPoint==m_mouseFinish)
	{
        m_MovePoint=m_mouseFinish;
		mDC.FillSolidRect(fw1/10,m_StartPoint.y,fw1-fw1/5,m_MovePoint.y-m_StartPoint.y,RGB(255,192,203)); //ѡ��Χ�����ɫ
	}
	else
 	mDC.FillSolidRect(fw1/10,m_StartPoint.y,fw1-fw1/5,m_MovePoint.y-m_StartPoint.y,RGB(255,192,203)); //ѡ��Χ�����ɫ
		
	/////////////////////////////�����ݲ���ʾ//////////////////////////////


	////��ȡ�ļ�����ͼ///
	ReadDataFromFile();

	//////////////////////////////////////////////////////
	for (i=100;i<3600-100;i=i+1)
	{
		if (m_data[i].selected==1)
		{
			CPen Penpink; 
			Penpink.CreatePen(PS_SOLID,1,RGB(255,192,203));
			mDC.SelectObject(&Penpink); 
			mDC.MoveTo(fw1/10,f2h-m_avesize*i);
   			mDC.LineTo(fw1-fw1/10,f2h-m_avesize*i);
		}
	}

	 ////////////////////////////////////pointer[]�����ֵҪ�������ݴ�С���ʵ���ʾ����
	double m_psum=0;
	m_pmax=pointer[0];
	m_pmin=pointer[0];
	for (i=100;i<3500;i++)
	{
		m_psum=m_psum+pointer[i];
	}
   m_paverage=m_psum/3400; 	   //��׼ֵ*/
	
	for (i=100;i<3500;i++)
	{
				
		if (m_pmax<pointer[i])
		{
			m_pmax=pointer[i];
		}

		if (m_pmin>pointer[i])
		{
			m_pmin=pointer[i];
		}
			
	}
	
	 	
	double m_pmaxaverage=m_pmax-m_paverage;
	double m_pminaverage=m_pmin-m_paverage;
	double m_pmaxminaverage;
	double m_jiange;

	if (m_pmaxaverage>m_pminaverage)
	{
		m_pmaxminaverage=m_pmaxaverage;
	}
	else
		m_pmaxminaverage=m_pminaverage;
 
	m_jiange=(fw1/10)/m_pmaxminaverage;  //��������ȥ�����Ժ�ķŴ�����
		 
    ////////////////////дX������/////////////////////////////

	CPen PenX;
	PenX.CreatePen(PS_SOLID,2,RGB(0,0,0));
    mDC.SelectObject(&PenX); 

	///////////////////////////////////////////////////////
      		
 	m_max=((m_pmax-m_paverage)*m_jiange)*2+fw1/2;
    m_min=((m_pmin-m_paverage)*m_jiange)*2+fw1/2;
   
	double AAA[3600];
	for (i=0;i<3600;i=i+1)
	{
		AAA[i]=pointer[i] - m_paverage;          //ƫ��
	}
	
    ///////////////////////////////////////////////////////////////        

	for (i=100;i<3600-100;i=i+10)
	{
	   	if (m_data[i].selected==1)
		{ 	
			if (0.8*AAA[i]*m_jiange+fw1/2>fw1/10+10&&0.8*AAA[i]*m_jiange+fw1/2<fw1-fw1/10-10)
			{
				CPen newPenrelate; 
				newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
				mDC.SelectObject(&newPenrelate); 
				mDC.SetPixel(0.8*AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i,RGB(0,255,0));
  				mDC.MoveTo(0.8*AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i);
   				mDC.LineTo(0.8*AAA[i+10]*m_jiange+fw1/2,f2h-m_avesize*(i+10));	
			}				
	}
		else
		{   
			CPen newPenrelate; 
			newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
			mDC.SelectObject(&newPenrelate); 
			mDC.SetPixel(0.8*AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i,RGB(0,0,255));
 			mDC.MoveTo(0.8*AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i);
   			mDC.LineTo(0.8*AAA[i+10]*m_jiange+fw1/2,f2h-m_avesize*(i+10));
		}
	}
	


	///////////////////////////////////////////////////////////////////////////
	CPen Penn(PS_SOLID,1,RGB(0,0,0));
  	mDC.SelectObject(&Penn);

    mDC.SetBkMode(TRANSPARENT); 
    
    mDC.MoveTo(fw1/10,fh);
    mDC.LineTo(fw1-fw1/10,fh); //��:x��
 
	mDC.MoveTo(fw1/10,f2-fh);
    mDC.LineTo(fw1-fw1/10,f2-fh); //��:x��

	mDC.MoveTo(fw1/2,fh); 
    mDC.LineTo(fw1/2,f2-fh); //�м�:y��

	////////////////////////////��ע�߶�///////////////////	
    CPen newPen;
	newPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
    mDC.SelectObject(&newPen); 
	mDC.MoveTo(fw1/10,fh);    //������
    mDC.LineTo(fw1/10,f2-fh); 

	mDC.MoveTo(fw1-fw1/10,fh);    //������
    mDC.LineTo(fw1-fw1/10,f2-fh);

	for(i=fh,j=0;i<=f2-fh,j<5;i+=m_avescale,j++)//дY���̶�ֵ
	{
		mDC.MoveTo(fw1/10,fh+m_avescale*j);
		mDC.LineTo(fw1/10-10,fh+m_avescale*j);
		mark.Format("%.1f",m_Height/4*(4-j));
		mDC.TextOut(fw1/10-40,fh+m_avescale*j-6,mark);	

		mDC.MoveTo(fw1-fw1/10,fh+m_avescale*j);
		mDC.LineTo(fw1-fw1/10+10,fh+m_avescale*j);
		mDC.TextOut(fw1-fw1/10+10,fh+m_avescale*j-6,mark);
	}

	for(i=fh,j=0;i<=f2-fh,j<36;i+=m_smallavescale,j++)//дY��С�̶�ֵ
	{
		mDC.MoveTo(fw1/10,fh+m_smallavescale*j);
		mDC.LineTo(fw1/10-6,fh+m_smallavescale*j);

		mDC.MoveTo(fw1-fw1/10,fh+m_smallavescale*j);
		mDC.LineTo(fw1-fw1/10+6,fh+m_smallavescale*j);
	}

	CPen newPeny; //��Y��ƽ����
	newPeny.CreatePen(PS_DOT,1,RGB(205,201,201));
    mDC.SelectObject(&newPeny); 
/////////////////////////////////////////////////////////////
	double m_paverageerror;
    m_paverageerror=(m_paverage-2048)*10/(G1*G2*4096);
	CString strm_paverageerror;
    strm_paverageerror.Format("%.1f",0);

	Straightalgorithm();	
    mDC.TextOut(fw1/2-4,f2-fh,strm_paverageerror);
	for(i=fw1/10,j=-3;j<0;j++)
	{
		mDC.MoveTo(fw1/2-i*abs(j),fh);
		mDC.LineTo(fw1/2-i*abs(j),f2-fh);
		double m_markX1;
//	    m_markX1=((m_paverage-m_pmaxminaverage*j)-2048)*10/(G1*G2*4096)-m_paverageerror;//j
		m_markX1=j;
// 		int m_markX11;
// 		m_markX11=int(m_markX1);
 		CString markx1;
  		markx1.Format("%.1f",m_markX1);
 		mDC.TextOut(fw1/2-i*abs(j)-16,f2-fh,markx1);
	} 
// 
	for(i=fw1/10,j=1;j<4;j++)
	{
		mDC.MoveTo(fw1/2+i*j,fh);
		mDC.LineTo(fw1/2+i*j,f2-fh);

		double m_markX2;
// 	    m_markX2=((m_paverage+m_pmaxminaverage*j)-2048)*10/(G1*G2*4096)-m_paverageerror;//j
		m_markX2=j;
 		CString markx2;
  		markx2.Format("%.1f",m_markX2);
 		mDC.TextOut(fw1/2+i*j-10,f2-fh,markx2);        //������̶�
	}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

	for(i=fh,j=1;i<=f2-fh,j<18;i+=m_smallavescale*2,j++) // X��ƽ����
	{
		mDC.MoveTo(fw1/10,fh+m_smallavescale*2*j);
		mDC.LineTo(fw1-fw1/10,fh+m_smallavescale*2*j);
	}

	for(i=fw1/10,j=1;j<4;j++)      //x���̶�
	{
		CPen newPenx;
	    newPenx.CreatePen(PS_SOLID,1,RGB(0,0,0));
        mDC.SelectObject(&newPenx); 
		mDC.MoveTo(fw1/2+i*j,f2-fh-10);
		mDC.LineTo(fw1/2+i*j,f2-fh);

		mDC.MoveTo(fw1/2-i*j,f2-fh-10);
		mDC.LineTo(fw1/2-i*j,f2-fh);

	}


	for(i=fw1/10,j=1;j<8;j++)      //x��С�̶�
	{
		CPen newPenx;
	    newPenx.CreatePen(PS_SOLID,1,RGB(0,0,0));
        mDC.SelectObject(&newPenx); 
		mDC.MoveTo(fw1/2+i*j/2,f2-fh-5);
		mDC.LineTo(fw1/2+i*j/2,f2-fh);

		mDC.MoveTo(fw1/2-i*j/2,f2-fh-5);
		mDC.LineTo(fw1/2-i*j/2,f2-fh);
	}
    //////////////////////����/////////////////////////////////////////////////////////
	CFont   fontgrid; 
	fontgrid.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  
	CFont*   pOldFontgrid=(CFont*)mDC.SelectObject(&fontgrid); 

    double l1=rect.left,l2=rect.top,l3=rect.right,l4=rect.bottom;
	int gridxnums=1;int gridynums=22;
    double fwgx=fw2,fwgy=f2;
	double dx=fw2/gridxnums;
	double dy=f2/gridynums;
	CRect gridRect(l1+fw1,l2,fw2,l4);
	mDC.FillSolidRect(l1+fw1,l2,fw2,l4,RGB(255,255,255));
    
	CPen gridPen(0,0,RGB(0,0,0));
    CPen *oldpen2=mDC.SelectObject(&gridPen);
	mDC.FillSolidRect(l1+fw1,l2,fw2,dy-1,RGB(232,232,232));//��ͷ�������ɫ
 	mDC.FillSolidRect(l1+fw1,dy*5,fw2,dy-1,RGB(232,232,232));//��ָ���������ɫ
 	mDC.FillSolidRect(l1+fw1,dy*13,fw2,dy-1,RGB(232,232,232));//��ָ���������ɫ
 

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
   
    mDC.SetBkMode(TRANSPARENT); 
	int meter=rect.Height()/70;
	int m1=l1+fw1+rect.Width()/100;
	double m2=l1+fw1+dx/2-rect.Width()/20;
	double m3=l1+fw1+dx-rect.Width()/15;
	double mid=l1+fw1+dx/2-rect.Width()/20;

    mDC.TextOut(mid ,meter,"ֱ�߶Ȳ������");
	mDC.TextOut(mid+20,dy*5+meter," ���Ҫ��");
	mDC.TextOut(mid+20,dy*13+meter," ��������");
    mDC.TextOut(m1,dy+meter,"�ļ���");
	mDC.TextOut(m1,dy*2+meter,"����ʱ��");
	mDC.TextOut(m1,dy*6+meter,"��������");                                                                                                         	
	mDC.TextOut(m1,dy*14+meter,"����Ҫ��");
	mDC.TextOut(m1,dy*15+meter,"ֱ�߶�");        
   
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath3;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	mDC.TextOut((m1+m2)/2,dy*1+meter,str);
		//��ʾ����ʱ��
	str=m_time.Format("%Y-%m-%d %H:%M");
	mDC.TextOut((m1+m2)/2,dy*2+meter,str);
	str.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[2]);
	mDC.TextOut(m2,dy*14+meter,str);
	mDC.TextOut(m2,dy*6+meter," ��С���˷�");
	mDC.TextOut(m3,dy*14+meter,"  um");
	mDC.TextOut(m3,dy*15+meter,"  um");

	///////////////////////////////////////////////////////////////////////////////////////
	Straightalgorithm();
	CString x1;		
	x1.Format("%.2f",GResult);		
 	mDC.TextOut(m2,dy*15+meter,x1);



	////////////////////////////��С����ֱ��/////////////////////////////
	
	double X0=0,Y0=0,XX=0,XY=0,K=0,Bb;
	double N0=3400;

	double Xroughness[3400],Yroughness[3400];
	j=0;
	m_jiange=(fw1/10)/m_pmaxminaverage;  //��������ȥ�����Ժ�ķŴ�����
	for (i=100;i<3500;i++)
	{	
		if (m_data[i].selected==0)
		{		
			Xroughness[j] =0.8*AAA[i]*m_jiange+fw1/2;  //������ĺ�����
			Yroughness[j] =-(f2h-m_avesize*i);  //�������������
			j++;
		}
	}

	for (i=0;i<j;i++)
	{			
			X0 = X0+ Xroughness[i];
			Y0 = Y0 + Yroughness[i];
			XX = XX + Xroughness[i]*Xroughness[i];
			XY= XY + Xroughness[i]*Yroughness[i]; 
	}	
		N0=j;
		K=(N0 * XY - X0 * Y0) / (N0 * XX - X0*X0);
 		Bb=(XY * X0- Y0* XX ) / (X0 * X0- N0 * XX);	
    double yL1[3400];
	for (i=0;i<N0;i++)
	{
		xL1[i] = Xroughness[i];
		yL1[i] = K * xL1[i]+ (-Bb) ;// the first equation of the LSC line��
	}
		
     CPen Pennihe(PS_SOLID,1,RGB(255,0,0));	  
	 mDC.SelectObject(&Pennihe);

     int meterthata=f2h/100;

	 if (K<0)
	 {	 
		double m_AB=-Bb/K;
	    double m_ab=m_AB-(f2h-m_avesize*0 ) /K;

 		if (m_AB>fw1/10  &&  m_AB<fw1-fw1/10  &&  m_ab>fw1/10  && m_ab<fw1-fw1/10 ) 
  		{		
			mDC.MoveTo( m_AB+meterthata, f2h-m_avesize*3600 - meterthata*K);    //��X�ᣬ����ֱ�߽���
 			mDC.LineTo(  m_ab -meterthata, f2h-m_avesize*0+ meterthata*K);      //��X�ᣬ����ֱ�߽���	
 		}

		 if ( m_AB<fw1/10   &&  m_ab>fw1/10  &&  m_ab<fw1-fw1/10  ) 
 		{		
  			mDC.MoveTo( fw1/10+meterthata, f2h+K*(m_ab-fw1/10)-meterthata*K);                  //��y�ᣬ����ֱ�߽���
  			mDC.LineTo( m_ab -meterthata, f2h-m_avesize*0+ meterthata*K);      //��X�ᣬ����ֱ�߽���	
 		}
		
		
		 if ( m_AB<fw1/10  &&   m_ab >fw1-fw1/10 ) 
 		{		
  			mDC.MoveTo(fw1/10 + meterthata, f2h+K*(m_ab-fw1/10) - meterthata*K);                      //��y�ᣬ����ֱ�߽���
  			mDC.LineTo( fw1-fw1/10 -meterthata,f2h+K*(m_ab-(fw1-fw1/10))+meterthata*K);    //��y�ᣬ����ֱ�߽���	
		 } 

		 if ( m_AB>fw1/10 && m_AB<fw1-fw1/10  &&   m_ab>fw1-fw1/10 ) 
 		{		
  			mDC.MoveTo( m_AB+meterthata , f2h-m_avesize*3600-meterthata*K);      //��X�ᣬ����ֱ�߽���
  			mDC.LineTo( fw1-fw1/10 -meterthata,f2h+K*(m_ab-(fw1-fw1/10))+meterthata*K);   //��y�ᣬ����ֱ�߽���	
 		}

}


	 if (K>0)
	 {	 
		double m_AB=-Bb/K;
	    double m_ab=m_AB-(f2h-m_avesize*0 ) /K;
 		if (m_AB>fw1/10  &&  m_AB<fw1-fw1/10  &&  m_ab>fw1/10  && m_ab<fw1-fw1/10 ) 
  		{		
			mDC.MoveTo( m_AB-meterthata, f2h-m_avesize*3600 +meterthata*K);    //��X�ᣬ����ֱ�߽���
 			mDC.LineTo(  m_ab +meterthata, f2h-m_avesize*0-meterthata*K);      //��X�ᣬ����ֱ�߽���	
 		}

		 if ( m_AB>fw1-fw1/10  &&  m_ab>fw1/10  &&  m_ab<fw1-fw1/10 ) 
 		{		
  			mDC.MoveTo( fw1-fw1/10 -meterthata, f2h-K*((fw1-fw1/10)-m_ab)+meterthata*K);      //��y�ᣬ����ֱ�߽���
  			mDC.LineTo( m_ab +meterthata, f2h-m_avesize*0-meterthata*K);      //��X�ᣬ����ֱ�߽���
 		}
		
		
		if ( m_AB>fw1-fw1/10  &&    m_ab<fw1/10 ) 
 		{	  		
			mDC.MoveTo( fw1-fw1/10-meterthata , f2h-K*((fw1-fw1/10)-m_ab)+meterthata*K); 	  //��y�ᣬ����ֱ�߽���
  			mDC.LineTo(fw1/10+meterthata, f2h-K*(fw1/10-m_ab)-meterthata*K);                     //��y�ᣬ����ֱ�߽���
 	
 		}

		 if ( m_AB>fw1/10 && m_AB<fw1-fw1/10 &&   m_ab<fw1/10 ) 
 		{		
  			mDC.MoveTo( m_AB-meterthata , f2h-m_avesize*3600+meterthata*K);      //��X�ᣬ����ֱ�߽���
  			mDC.LineTo( fw1/10+meterthata, f2h-K*(fw1/10-m_ab)-meterthata*K);   //��y�ᣬ����ֱ�߽���
  			Pennihe.DeleteObject();	
 		}


}

 		//����ͼ��
			CPen newPenlast; 
			newPenlast.CreatePen(PS_SOLID,3,RGB(0,0,0));
			mDC.SelectObject(&newPenlast); 
  			mDC.MoveTo(rect.left,rect.bottom);
   			mDC.LineTo(rect.right,rect.bottom);

			mDC.MoveTo(rect.right,rect.top);
   			mDC.LineTo(rect.right,rect.bottom);
	
	//////////////////////////////////////////////////////////////////////////////////////

	pDC->BitBlt(rect.left,rect.top,rect.right,rect.bottom,&mDC,0,0,SRCCOPY); //���Ѿ���õ�ͼ��ʾ���ƶ�λ����
    mDC.SelectObject(pOldBmp);
    mDC.DeleteDC();
   memBitmap.DeleteObject();//�ͷ��ڴ��豸	
}

void CDoStraightness::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	////////////////////��ȡ����////////////////////////
	
	CWnd *pWnd=GetDlgItem(IDC_LINE_STATIC);    
    CDC  *pDC=pWnd->GetDC();
	CRect rect;
	this->ClientToScreen(&point);          
	pWnd->GetClientRect(&rect);  
    pWnd->ClientToScreen(rect);        
	point.x=point.x-rect.left;
	point.y=point.y-rect.top;
	pDC->SetBkMode(TRANSPARENT);
	double fh=(rect.bottom-rect.top)/30;
		
	if( (point.x)<m_min ||  (point.x>m_max)	|| (point.y)>(rect.bottom-rect.top-fh) || (point.y)<fh);	

	else
		{
			m_StartPoint=m_LastEndPoint=point;//���浱ǰ��
			m_bDraw=TRUE;	
 		}
	
		m_mouseOrigin=m_StartPoint;

	ReleaseDC(pDC);
	CFormView::OnLButtonDown(nFlags, point);
}

void CDoStraightness::OnLButtonUp(UINT nFlags, CPoint point) 
{
		// TODO: Add your message handler code here and/or call default
	m_LButtonUp=TRUE;
	m_bDraw=false; 
	CWnd * pWnd=GetDlgItem(IDC_LINE_STATIC);                           
    CDC *pDC=pWnd->GetDC();
	CRect rect;
    pWnd->GetClientRect(&rect);  
	
	this->ClientToScreen(&point);                                
    pWnd->GetClientRect(rect);                               
    pWnd->ClientToScreen(rect);                              

	point.x=point.x-rect.left;
	point.y=point.y-rect.top;
	
    double fh=(rect.bottom-rect.top)/30;
	if((point.x)<m_min||(point.x)>m_max||(point.y)>(rect.bottom-rect.top-fh)||(point.y)<fh);	

	else	
	{	 
	 //��ʱ��굯����Ӧ��ͼ
		m_mouseFinish=point;
			///////////////ѡ��������ɫ///////////////////
	double f2= rect.Height();                                                 	                             
    double fh=rect.Height()/30;
	double m_Y;
    m_Y=f2-fh*2;
	double m_avesize; //y��ƽ���ֳ�3600��	
    m_avesize=m_Y/3600;
    double fw1=3*rect.Width()/5;
    int i;
	double f2h=f2-fh;
 	double m_pmaxaverage=m_pmax-m_paverage;
	double m_jiange=(fw1/5)/m_pmaxaverage;;

	double AAA[3600];
	for (i=10;i<3600;i++)
	{	
        m_startPosition=3600-(m_mouseOrigin.y-fh)/m_avesize;
		m_endPosition=3600-(m_mouseFinish.y-fh)/m_avesize;
	}

    ChangeValueOfSelect(((CMainFrame*)AfxGetMainWnd())->m_fullPath3,m_startPosition,m_endPosition,1);
	
	}
	CFormView::OnLButtonUp(nFlags, point);
}

 void CDoStraightness::OnMouseMove(UINT nFlags, CPoint point) 
{
// TODO: Add your message handler code here and/or call default
 	if (MK_LBUTTON & nFlags)
 	{	
 		CWnd *pwnd=GetDlgItem(IDC_LINE_STATIC);//��ȡ��̬���ָ��
 		CDC *pDC=pwnd->GetDC();
 		CRect rect;
 		this->ClientToScreen(&point);  
 		pwnd->GetClientRect(rect);          
 		pwnd->ClientToScreen(rect);  	
 		point.x=point.x-rect.left;
 		point.y=point.y-rect.top;	
 		double fh=(rect.bottom-rect.top)/30;
 		if((point.x)<m_min||(point.x)>m_max||(point.y)>(rect.bottom-rect.top-fh)||(point.y)<fh);				
 		else  
 		{	
 			if(m_bDraw==TRUE)             //���������¿��Կ�ʼ��ͼ
 			{	
				 m_MovePoint=point;
 			}	
		}
 	
		
 	}
	OnPaint();
	CFormView::OnMouseMove(nFlags, point);
}

void CDoStraightness::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_lineselect=TRUE;
	if (m_editStraightness.GetSafeHwnd())
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
		m_editStraightness.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}

	
}

void CDoStraightness::ChangeValueOfSelect(CString path, int startPosition, int endPosition, BOOL isSelected)
{
	shuju ChangeDate[3600];
	std::ifstream fin(path, std::ios::binary);
	int i;

	if (endPosition>startPosition)
	{	
		for (i=0;i<3600;i++)
		{
			fin.read((char*)&ChangeDate[i],sizeof(shuju));
		}
		fin.read((char*)&G1,sizeof(double));
		fin.read((char*)&G2,sizeof(double));
		fin.read((char*)&m_Height,sizeof(float));
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
		fout.write((char*)&m_Height,sizeof(float));
		fout.write((char*)&m_time,sizeof(CTime));
		fout.close();
	}
	else
	{
		for (i=0;i<3600;i++)
		{
			fin.read((char*)&ChangeDate[i],sizeof(shuju));
		}
		fin.read((char*)&G1,sizeof(double));
		fin.read((char*)&G2,sizeof(double));
		fin.read((char*)&m_Height,sizeof(float));
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
		fout.write((char*)&m_Height,sizeof(float));
		fout.write((char*)&m_time,sizeof(CTime));
		fout.close();
	}

}

void CDoStraightness::Onresetzxd() 
{
	// TODO: Add your control notification handler code here
	DrawingCleanAndReset(((CMainFrame*)AfxGetMainWnd())->m_fullPath3,0);
	m_MovePoint.y=0;
	m_StartPoint.y=0;
	m_extendzxd=0;
	OnPaint();
	
}

void CDoStraightness::DrawingCleanAndReset(CString path, BOOL isSelected)
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
	fin.read((char*)&m_Height,sizeof(float));
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
	fout.write((char*)&m_Height,sizeof(float));
	fout.write((char*)&m_time,sizeof(CTime));
	fout.close();

}

void CDoStraightness::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here	
	if (m_editStraightness.GetSafeHwnd())
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
		m_editStraightness.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}
}



void CDoStraightness::Straightalgorithm()
{

	 /////////////////////////////////////ֱ�߶��㷨//////////////////////////////
/*	double G1=4,G2=0.151605489873827;*/
    double Yroughness[3500],xroughness[3500], AAA[3600],aa1[3600],yL1[3600],xL1[3600],pointer1[3600]; 
    double miny ,maxy,an=0,M=0,b=0;
	int i;
	double t0=0,s1=0,t1=0,s2=0;
    double z=98;
	int  j=0;
    int s0=3400;
	for (i=0;i<3600;i++)
	{
		AAA[i]=((pointer[i]-2048)* 10) / (G1 * G2 * 4096);
		aa1[i]=z * i / 3600;  
	}
	for (i=0;i<3400;i++)
	{
		if (m_data[i].selected==0)
		{
		 Yroughness[j] = AAA[i+99];  //�������������
		 xroughness[j] = aa1[i+99];  //������ĺ�����
         j++;
		}

	}
	 s0 =j; //ȥ�����ʣ�µĵ���
	 
	 for (i=0;i<j;i++)
	{
		t0 = t0 + Yroughness[i];
		s1 = s1 + xroughness[i];                  
		t1 = t1 + xroughness[i] * Yroughness[i];
		s2 = s2 + xroughness[i] * xroughness[i];  
	}
	 an = s0 * s2 - s1*s1;                  //ֱ�߶ȵķ�ĸ
	if (an == 0) 
	{
		an = 0.00001;        //��ĸ����Ϊ0
	}
    M = (s0 * t1 - s1 * t0) / (s0 * s2 - s1*s1) ;// �����С�������ֱ��ϵ����
    b = (s2 * t0 - s1 * t1) /(s0 * s2 - s1*s1);
  
	for (i=0;i<j;i++)
	{
		xL1[i] = xroughness[i];
		yL1[i] = M * xL1[i]+ b ;// the first equation of the LSC line��
	}

	for (i=0;i<j;i++)
	{
		yL1[i] = Yroughness[i] - (M * xroughness[i] + b); //��С����ֱ�ߵĲв�
		if(i==0)
		{
			miny = yL1[0];
			maxy = yL1[0];
		}
		else
		{
			if(miny >= yL1[i])
				miny = yL1[i];
			
			if(maxy <= yL1[i])
				maxy = yL1[i];
		}
	}
	GResult =fabs(miny) + fabs(maxy);
   
}



void CDoStraightness::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pActivateView==this)
	{
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(-1,FALSE);
		if (m_lineselect)
		{
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,FALSE);
		}
		else
		{
			((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,TRUE);
		}
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(8,TRUE);
	}
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CDoStraightness::ReadDataFromFile()
{
	std::ifstream fin(((CMainFrame*)AfxGetMainWnd())->m_fullPath3, std::ios::binary);
	
	for (int i=0;i<3600;i++)
	{
		
		fin.seekg(i*sizeof(shuju));
		fin.read((char*)&m_data[i], sizeof(shuju));
		pointer[i]=m_data[i].data;
	}
	
    fin.seekg(3600*sizeof(shuju));            //sizeof(CTime)
	fin.read((char*)&G1, 8);	
	fin.seekg(8+3600*sizeof(shuju));
	fin.read((char*)&G2, 8);
	fin.read((char*)&m_Height,sizeof(float));
	fin.read((char*)&m_time,sizeof(shuju));
	fin.close();
}

void CDoStraightness::SubAnaData(int FilterMode, double *pMem, double *GResult, float m_Yd, float m_Tr)
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

void CDoStraightness::WLS_Filter(int ModeIndex, int Number, double *Soudata, double *Resdata)
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



void CDoStraightness::OnPrint() 
{
	// TODO: Add your command handler code here
	CFormView::OnFilePrint();
}

void CDoStraightness::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);//X����һӢ�����صĸ���,A4ֽ
    int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);//Y����һӢ�����صĸ���
	int xLogPixPerMM=xLogPixPerInch/25.4;//X����1mm���صĸ���
	int yLogPixPerMM=yLogPixPerInch/25.4;//Y����1mm���صĸ���
	m_penScale=xLogPixPerInch/96;//
	
	//��ӡ��ĳߴ�Ϊ150*250(mm)
	CPoint pt(0,0);//ֽ�ŵ����Ͻ�Ϊ00��
	CSize  sz(270*xLogPixPerMM,200*yLogPixPerMM);//sz���ο�Ĵ�С��X�����Y�������ص��ܸ���
	CRect  tRect(pt,sz);//����Ĵ�ӡ���ľ��ο�
	rect.top=tRect.top+25*yLogPixPerMM;
	rect.right=tRect.right;
	rect.left=tRect.left+20*xLogPixPerMM;
	rect.bottom=tRect.bottom-25*yLogPixPerMM;
	
	pOldBmp = NULL;                           // ���ɵ�λͼָ���ÿ�	
	mDC.CreateCompatibleDC(pDC);             // �����ڴ��ͼ�豸��ʹ�ڴ�λͼ��DC��ؼ���DC����
	memBitmap.CreateCompatibleBitmap(pDC,tRect.right,tRect.bottom);
	pOldBmp = mDC.SelectObject(&memBitmap);
    mDC.FillSolidRect(tRect.left,tRect.top,tRect.right,tRect.bottom,RGB(255,255,255));//�����ο�����ɫ*/
	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	mDC.SelectObject(&RectPen);      //�ʺ�������֮ǰ��Ҫselectobject���������Ҫdeleteobject      
	mDC.Rectangle(rect.left,rect.top,rect.right,rect.bottom); //��̬����� ��ɫ �߿�
	
	//�޸Ĵ�ӡ�����С
	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
		DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  
	CFont*   pOldFont=(CFont*)mDC.SelectObject(&font); 
	
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
	lstrcpy((LPSTR)newLogFont.lfFaceName,(LPSTR)"����"); 
	newLogFont.lfEscapement=0; 
	newLogFont.lfUnderline=FALSE; 
	newLogFont.lfItalic=FALSE; 
	newLogFont.lfStrikeOut=FALSE; 
    newLogFont.lfCharSet=GB2312_CHARSET;
	//�����������µ����壬������ǰ������
	CFont newFont;
	CFont *oldFont;
	
	newFont.CreateFontIndirect(&newLogFont);
	oldFont = mDC.SelectObject(&newFont );
	
	//��������
	mDC.MoveTo(rect.left,rect.top);
	mDC.LineTo(rect.left,rect.top-10*xLogPixPerMM);
	mDC.MoveTo(rect.left,rect.top-10*xLogPixPerMM);
	mDC.LineTo(rect.right,rect.top-10*xLogPixPerMM);
	mDC.MoveTo(rect.right,rect.top-10*xLogPixPerMM);
	mDC.LineTo(rect.right,rect.top);
	//��������
	mDC.MoveTo(rect.left,rect.bottom);
	mDC.LineTo(rect.left,rect.bottom+10*xLogPixPerMM);
	mDC.MoveTo(rect.left,rect.bottom+10*xLogPixPerMM);
	mDC.LineTo(rect.right,rect.bottom+10*xLogPixPerMM);
	mDC.MoveTo(rect.right,rect.bottom+10*xLogPixPerMM);
	mDC.LineTo(rect.right,rect.bottom);
	RectPen.DeleteObject();
	
	//д����Ϣ
    mDC.TextOut(0.8*rect.left+200*xLogPixPerMM,rect.bottom+11*yLogPixPerMM,
		"���������ž����������޹�˾");
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_strOperatorName;
	str.Format("����Ա:%s",str);
	mDC.TextOut(rect.left+75*xLogPixPerMM,rect.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineModel;
	str.Format("�����ͺ�:%s",str);
	mDC.TextOut(rect.left+115*xLogPixPerMM,rect.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineName;
	str.Format("����:%s",str);
	mDC.TextOut(rect.left+155*xLogPixPerMM,rect.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strProcess;
	str.Format("����:%s",str);
	mDC.TextOut(rect.left+195*xLogPixPerMM,rect.top-7*yLogPixPerMM,str);
	
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceModel;
	str.Format("�����ͺ�:%s",str);
	mDC.TextOut(rect.left+15*xLogPixPerMM,rect.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceNum;
	str.Format("�������:%s",str);
	mDC.TextOut(rect.left+75*xLogPixPerMM,rect.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strIndent;
	str.Format("����:%s",str);
	mDC.TextOut(rect.left+135*xLogPixPerMM,rect.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strInspector;
	str.Format("���Ա:%s",str);
	mDC.TextOut(rect.left+195*xLogPixPerMM,rect.bottom+3*yLogPixPerMM,str);

	double gridleft=(rect.right-rect.left)*3/5+rect.left;
	int gridxnums=1;int gridynums=22;//һ��25��
	double dx= ((rect.right-rect.left)-gridleft)/gridxnums;//һ�еĿ���
	double dy=(rect.bottom-rect.top)/gridynums;//һ�еĸ߶�
    CRect gridRect(gridleft,rect.top,gridleft+dx*gridxnums,rect.top+dy*gridynums);
	
	mDC.FillSolidRect(gridleft,gridRect.top,rect.right,dy,RGB(232,232,232));
	mDC.FillSolidRect(gridleft,gridRect.top+dy*5,rect.right,dy,RGB(232,232,232));//��ָ���������ɫ
	mDC.FillSolidRect(gridleft,gridRect.top+dy*13,rect.right,dy,RGB(232,232,232));
	
	for( int m0=0;m0<=0;m0++) //����gridxnums������                      
	{
		mDC.MoveTo(gridRect.left+m0*dx,gridRect.bottom);
		mDC.LineTo(gridRect.left+m0*dx,gridRect.top);
		mDC.MoveTo(rect.right+m0*dx,rect.bottom);
		mDC.LineTo(rect.right+m0*dx,rect.top);
	}
		
	for(int n=0;n<=gridynums;n++) //����gridynums������                        
	{
		mDC.MoveTo(gridRect.left,gridRect.top+n*dy);
		mDC.LineTo(rect.right,gridRect.top+n*dy);
	}  

	double fw1=3*rect.Width()/5,f1=rect.Width(),f2=rect.Height();                                                 	                             
    double fw2=2*rect.Width()/5;
    double fh=rect.Height()/30;
    int i,j;
	double m_Y;
	double m_avescale;
    m_Y=f2-fh*2;
    m_avescale=m_Y/4;
    int m_mark[5]={360,270,180,90,0};
	CString mark;
	double m_smallavescale;
	m_smallavescale=m_Y/36;
	double f2h=f2-fh;
	double m_avesize;    //y��ƽ���ֳ�3600��	
	m_avesize=m_Y/3600;

	mDC.FillSolidRect(fw1/10+rect.left,fh+rect.top,fw1-fw1/5,f2-fh,RGB(255,255,255)); //ֱ�߶��������������ɫ
	/*if (m_StartPoint==m_mouseFinish)
	{
        m_MovePoint=m_mouseFinish;
		mDC.FillSolidRect(fw1/10+rect.left,m_StartPoint.y,fw1-fw1/5,m_MovePoint.y-m_StartPoint.y,RGB(255,192,250)); //ѡ��Χ�����ɫ
	}
	else
 	mDC.FillSolidRect(fw1/10+rect.left,m_StartPoint.y,fw1-fw1/5,m_MovePoint.y-m_StartPoint.y,RGB(255,192,250)); //ѡ��Χ�����ɫ*/


	/////////////////////////////�����ݲ���ʾ//////////////////////////////


	////��ȡ�ļ�����ͼ///
	ReadDataFromFile();

	//////////////////////////////////////////////////////
	for (i=100;i<3600-100;i=i+1)
	{
		if (m_data[i].selected==1)
		{
			CPen Penpink; 
			Penpink.CreatePen(PS_SOLID,1*m_penScale,RGB(255,192,203));
			mDC.SelectObject(&Penpink); 
			mDC.MoveTo(fw1/10+rect.left,f2h-m_avesize*i+rect.top);//Ϊѡ������ɫ
   			mDC.LineTo(fw1-fw1/10+rect.left,f2h-m_avesize*i+rect.top);
		}
	}

	 ////////////////////////////////////pointer[]�����ֵҪ�������ݴ�С���ʵ���ʾ����
	double m_psum=0;
	m_pmax=pointer[0];
	m_pmin=pointer[0];
	for (i=100;i<3500;i++)
	{
		m_psum=m_psum+pointer[i];
	}
   m_paverage=m_psum/3400; 	   //��׼ֵ*/
	
	for (i=100;i<3500;i++)
	{
				
		if (m_pmax<pointer[i])
		{
			m_pmax=pointer[i];
		}

		if (m_pmin>pointer[i])
		{
			m_pmin=pointer[i];
		}
			
	}
	
	 	
	double m_pmaxaverage=m_pmax-m_paverage;
	double m_pminaverage=m_pmin-m_paverage;
	double m_pmaxminaverage;
	double m_jiange;

	if (m_pmaxaverage>m_pminaverage)
	{
		m_pmaxminaverage=m_pmaxaverage;
	}
	else
		m_pmaxminaverage=m_pminaverage;
 
	m_jiange=(fw1/10)/m_pmaxminaverage;  //��������ȥ�����Ժ�ķŴ�����
		 
    ////////////////////дX������/////////////////////////////

	CPen PenX;
	PenX.CreatePen(PS_SOLID,2*m_penScale,RGB(0,0,0));
    mDC.SelectObject(&PenX); 

	///////////////////////////////////////////////////////
      		
 	m_max=((m_pmax-m_paverage)*m_jiange)*2+fw1/2;
    m_min=((m_pmin-m_paverage)*m_jiange)*2+fw1/2;
   
	double AAA[3600];
	for (i=0;i<3600;i=i+1)
	{
		AAA[i]=pointer[i] - m_paverage;          //ƫ��
	}
	
    ///////////////////////////////////////////////////////////////        

	for (i=100;i<3600-100;i=i+10)
	{
	   	if (m_data[i].selected==1)
		{ 	
			if (0.8*AAA[i]*m_jiange+fw1/2>fw1/10+10&&0.8*AAA[i]*m_jiange+fw1/2<fw1-fw1/10-10)
			{
				CPen newPenrelate; 
				newPenrelate.CreatePen(PS_SOLID,1*m_penScale,RGB(0,255,0));
				mDC.SelectObject(&newPenrelate); 
				mDC.SetPixel(AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i,RGB(0,255,0));
  				mDC.MoveTo(0.8*AAA[i]*m_jiange+fw1/2+rect.left,f2h-m_avesize*i+rect.top);
   				mDC.LineTo(0.8*AAA[i+10]*m_jiange+fw1/2+rect.left,f2h-m_avesize*(i+10)+rect.top);	
			}				
	}
		else
		{   
			CPen newPenrelate; 
			newPenrelate.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,255));
			mDC.SelectObject(&newPenrelate); 
			mDC.SetPixel(AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i,RGB(0,0,255));
 			mDC.MoveTo(0.8*AAA[i]*m_jiange+fw1/2+rect.left,f2h-m_avesize*i+rect.top);
   			mDC.LineTo(0.8*AAA[i+10]*m_jiange+fw1/2+rect.left,f2h-m_avesize*(i+10)+rect.top);
		}
	}
	


	///////////////////////////////////////////////////////////////////////////
	CPen Penn(PS_SOLID,1*m_penScale,RGB(0,0,0));
  	mDC.SelectObject(&Penn);

    mDC.SetBkMode(TRANSPARENT); 
    
    mDC.MoveTo(fw1/10+rect.left,fh+rect.top);
    mDC.LineTo(fw1-fw1/10+rect.left,fh+rect.top); //��:x��
 
    mDC.MoveTo(fw1/10+rect.left,f2-fh+rect.top);
    mDC.LineTo(fw1-fw1/10+rect.left,f2-fh+rect.top); //��:x��

	mDC.MoveTo(fw1/2+rect.left,fh+rect.top); 
    mDC.LineTo(fw1/2+rect.left,f2-fh+rect.top); //�м�:y��

	////////////////////////////��ע�߶�///////////////////	
    CPen newPen;
	newPen.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
    mDC.SelectObject(&newPen); 
	mDC.MoveTo(fw1/10+rect.left,fh+rect.top);    //������
    mDC.LineTo(fw1/10+rect.left,f2-fh+rect.top); 

	mDC.MoveTo(fw1-fw1/10+rect.left,fh+rect.top);    //������
    mDC.LineTo(fw1-fw1/10+rect.left,f2-fh+rect.top);

	for(i=fh,j=0;i<=f2-fh,j<5;i+=m_avescale,j++)//дY���̶�ֵ
	{
		mDC.MoveTo(fw1/10+rect.left,fh+m_avescale*j+rect.top);
		mDC.LineTo(fw1/10-10*m_penScale+rect.left,fh+m_avescale*j+rect.top);
		mark.Format("%.1f",m_Height/4*(4-j));
		mDC.TextOut(fw1/10-40*m_penScale+rect.left,fh+m_avescale*j-6*m_penScale+rect.top,mark);	

		mDC.MoveTo(fw1-fw1/10+rect.left,fh+m_avescale*j+rect.top);
	    mDC.LineTo(fw1-fw1/10+10*m_penScale+rect.left,fh+m_avescale*j+rect.top);
		mDC.TextOut(fw1-fw1/10+10*m_penScale+rect.left,fh+m_avescale*j-6*m_penScale+rect.top,mark);

	}

	for(i=fh,j=0;i<=f2-fh,j<36;i+=m_smallavescale,j++)//дY��С�̶�ֵ
	{
		mDC.MoveTo(fw1/10+rect.left,fh+m_smallavescale*j+rect.top);
		mDC.LineTo(fw1/10-6*m_penScale+rect.left,fh+m_smallavescale*j+rect.top);

		mDC.MoveTo(fw1-fw1/10+rect.left,fh+m_smallavescale*j+rect.top);
		mDC.LineTo(fw1-fw1/10+6*m_penScale+rect.left,fh+m_smallavescale*j+rect.top);
	}

	CPen newPeny; //��Y��ƽ����
	newPeny.CreatePen(PS_DOT,1*m_penScale,RGB(205,201,201));
    mDC.SelectObject(&newPeny); 

	double m_paverageerror;
    m_paverageerror=(m_paverage-2048)*10/(G1*G2*4096);
	CString strm_paverageerror;
    strm_paverageerror.Format("%.1f",0);

    mDC.TextOut(fw1/2-4*m_penScale+rect.left,f2-fh+rect.top,strm_paverageerror);
	for(i=fw1/10,j=-3;j<0;j++)
	{
		mDC.MoveTo(fw1/2-i*abs(j)+rect.left,fh+rect.top);
		mDC.LineTo(fw1/2-i*abs(j)+rect.left,f2-fh+rect.top);
		double m_markX1;
 	    m_markX1=j;
 		CString markx1;
  		markx1.Format("%.1f",m_markX1);
 		mDC.TextOut(fw1/2-i*abs(j)-20*m_penScale+rect.left,f2-fh+rect.top,markx1);
	} 

	for(i=fw1/10,j=1;j<4;j++)
	{
		mDC.MoveTo(fw1/2+i*j+rect.left,fh+rect.top);
		mDC.LineTo(fw1/2+i*j+rect.left,f2-fh+rect.top);

		double m_markX2;
 	    m_markX2=j;
 		CString markx2;
  		markx2.Format("%.1f",m_markX2);
 		mDC.TextOut(fw1/2+i*j-20*m_penScale+rect.left,f2-fh+rect.top,markx2);        //������̶�
	}

	  

	for(i=fh,j=1;i<=f2-fh,j<18;i+=m_smallavescale*2,j++) // X��ƽ����
	{
		mDC.MoveTo(fw1/10+rect.left,fh+m_smallavescale*2*j+rect.top);
		mDC.LineTo(fw1-fw1/10+rect.left,fh+m_smallavescale*2*j+rect.top);
	}

	for(i=fw1/10,j=1;j<4;j++)      //x���̶�
	{
		CPen newPenx;
	    newPenx.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
        mDC.SelectObject(&newPenx); 
		mDC.MoveTo(fw1/2+i*j+rect.left,f2-fh-10*m_penScale+rect.top);
		mDC.LineTo(fw1/2+i*j+rect.left,f2-fh+rect.top);

		mDC.MoveTo(fw1/2-i*j+rect.left,f2-fh-10*m_penScale+rect.top);
		mDC.LineTo(fw1/2-i*j+rect.left,f2-fh+rect.top);

	}


	for(i=fw1/10,j=1;j<8;j++)      //x��С�̶�
	{
		CPen newPenx;
	    newPenx.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
        mDC.SelectObject(&newPenx); 
		mDC.MoveTo(fw1/2+i*j/2+rect.left,f2-fh-5*m_penScale+rect.top);
		mDC.LineTo(fw1/2+i*j/2+rect.left,f2-fh+rect.top);

		mDC.MoveTo(fw1/2-i*j/2+rect.left,f2-fh-5*m_penScale+rect.top);
		mDC.LineTo(fw1/2-i*j/2+rect.left,f2-fh+rect.top);
	}
    //////////////////////����/////////////////////////////////////////////////////////

	double l1=rect.left,l2=rect.top,l3=rect.right,l4=rect.bottom;

    mDC.SetBkMode(TRANSPARENT); // 	CFont   fontgrid; 
// 	fontgrid.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
// 	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "����");  
// 	CFont*   pOldFontgrid=(CFont*)mDC.SelectObject(&fontgrid); 

	int meter=rect.Height()/70;
	int m1=l1+fw1+rect.Width()/100;
	double m2=l1+fw1+dx/2-rect.Width()/20;
	double m3=l1+fw1+dx-rect.Width()/15;
	double mid=l1+fw1+dx/2-rect.Width()/20;

    mDC.TextOut(mid,meter+rect.top,"ֱ�߶Ȳ������");
	mDC.TextOut(mid+20*m_penScale,dy*5+meter+rect.top," ���Ҫ��");
	mDC.TextOut(mid+20*m_penScale,dy*13+meter+rect.top," ��������");
    mDC.TextOut(m1,dy+meter+rect.top,"�ļ���");
	mDC.TextOut(m1,dy*2+meter+rect.top,"����ʱ��");
	mDC.TextOut(m1,dy*6+meter+rect.top,"��������");                                                                                                         	
	mDC.TextOut(m1,dy*14+meter+rect.top,"����Ҫ��");
	mDC.TextOut(m1,dy*15+meter+rect.top,"ֱ�߶�");        
   
	

	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath3;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	mDC.TextOut((m1+m2)/2+10*xLogPixPerMM,dy*1+meter+rect.top,str);
		//��ʾ����ʱ��
	str=m_time.Format("%Y-%m-%d %H:%M");
	mDC.TextOut((m1+m2)/2+10*xLogPixPerMM,dy*2+meter+rect.top,str);
	str.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[2]);
	mDC.TextOut(m2+10*xLogPixPerMM,dy*14+meter+rect.top,str);
	mDC.TextOut(m2,dy*6+meter+rect.top," ��С���˷�");
	mDC.TextOut(m3,dy*14+meter+rect.top,"  um");
	mDC.TextOut(m3,dy*15+meter+rect.top,"  um");

	///////////////////////////////////////////////////////////////////////////////////////
	Straightalgorithm();
	CString x1;		
	x1.Format("%.2f",GResult);		
 	mDC.TextOut(m2+10*xLogPixPerMM,dy*15+meter+rect.top,x1);



	////////////////////////////��С����ֱ��/////////////////////////////
	
	double X0=0,Y0=0,XX=0,XY=0,K=0,Bb;
	double N0=3400;

	double Xroughness[3400],Yroughness[3400];
	j=0;
	m_jiange=(fw1/10)/m_pmaxminaverage;  //��������ȥ�����Ժ�ķŴ�����
	for (i=100;i<3500;i++)
	{	
		if (m_data[i].selected==0)
		{		
			Xroughness[j] =0.8*AAA[i]*m_jiange+fw1/2;  //������ĺ�����
			Yroughness[j] =-(f2h-m_avesize*i);  //�������������
			j++;
		}
	}

	for (i=0;i<j;i++)
	{			
			X0 = X0+ Xroughness[i];
			Y0 = Y0 + Yroughness[i];
			XX = XX + Xroughness[i]*Xroughness[i];
			XY= XY + Xroughness[i]*Yroughness[i]; 
	}	
		N0=j;
		K=(N0 * XY - X0 * Y0) / (N0 * XX - X0*X0);
 		Bb=(XY * X0- Y0* XX ) / (X0 * X0- N0 * XX);	
    double yL1[3400];
	for (i=0;i<N0;i++)
	{
		xL1[i] = Xroughness[i];
		yL1[i] = K * xL1[i]+ (-Bb) ;// the first equation of the LSC line��
	}
		
     CPen Pennihe(PS_SOLID,1*m_penScale,RGB(255,0,0));	  
	 mDC.SelectObject(&Pennihe);

     int meterthata=f2h/100;

	 if (K<0)
	 {	 
		double m_AB=-Bb/K;
	    double m_ab=m_AB-(f2h-m_avesize*0 ) /K;

 		if (m_AB>fw1/10  &&  m_AB<fw1-fw1/10  &&  m_ab>fw1/10  && m_ab<fw1-fw1/10 ) 
  		{		
			mDC.MoveTo( m_AB+meterthata+rect.left, f2h-m_avesize*3600 - meterthata*K+rect.top);    //��X�ᣬ����ֱ�߽���
 			mDC.LineTo(  m_ab -meterthata+rect.left, f2h-m_avesize*0+ meterthata*K+rect.top);      //��X�ᣬ����ֱ�߽���	
 		}

		 if ( m_AB<fw1/10   &&  m_ab>fw1/10  &&  m_ab<fw1-fw1/10  ) 
 		{		
  			mDC.MoveTo( fw1/10+meterthata+rect.left, f2h+K*(m_ab-fw1/10)-meterthata*K+rect.top);                  //��y�ᣬ����ֱ�߽���
  			mDC.LineTo( m_ab -meterthata+rect.left, f2h-m_avesize*0+ meterthata*K+rect.top);      //��X�ᣬ����ֱ�߽���	
 		}
		
		
		 if ( m_AB<fw1/10  &&   m_ab >fw1-fw1/10 ) 
 		{		
  			mDC.MoveTo(fw1/10 + meterthata+rect.left, f2h+K*(m_ab-fw1/10) - meterthata*K+rect.top);                      //��y�ᣬ����ֱ�߽���
  			mDC.LineTo( fw1-fw1/10 -meterthata+rect.left,f2h+K*(m_ab-(fw1-fw1/10))+meterthata*K+rect.top);    //��y�ᣬ����ֱ�߽���	
		 } 

		 if ( m_AB>fw1/10 && m_AB<fw1-fw1/10  &&   m_ab>fw1-fw1/10 ) 
 		{		
  			mDC.MoveTo( m_AB+meterthata+rect.left , f2h-m_avesize*3600-meterthata*K+rect.top);      //��X�ᣬ����ֱ�߽���
  			mDC.LineTo( fw1-fw1/10 -meterthata+rect.left,f2h+K*(m_ab-(fw1-fw1/10))+meterthata*K+rect.top);   //��y�ᣬ����ֱ�߽���	
 		}

}


	 if (K>0)
	 {	 
		double m_AB=-Bb/K;
	    double m_ab=m_AB-(f2h-m_avesize*0 ) /K;
 		if (m_AB>fw1/10  &&  m_AB<fw1-fw1/10  &&  m_ab>fw1/10  && m_ab<fw1-fw1/10 ) 
  		{		
			mDC.MoveTo( m_AB-meterthata+rect.left, f2h-m_avesize*3600 +meterthata*K+rect.top);    //��X�ᣬ����ֱ�߽���
 			mDC.LineTo(  m_ab +meterthata+rect.left, f2h-m_avesize*0-meterthata*K+rect.top);      //��X�ᣬ����ֱ�߽���	
 		}

		 if ( m_AB>fw1-fw1/10  &&  m_ab>fw1/10  &&  m_ab<fw1-fw1/10 ) 
 		{		
  			mDC.MoveTo( fw1-fw1/10 -meterthata+rect.left, f2h-K*((fw1-fw1/10)-m_ab)+meterthata*K+rect.top);      //��y�ᣬ����ֱ�߽���
  			mDC.LineTo( m_ab +meterthata+rect.left, f2h-m_avesize*0-meterthata*K+rect.top);      //��X�ᣬ����ֱ�߽���
 		}
		
		
		if ( m_AB>fw1-fw1/10  &&    m_ab<fw1/10 ) 
 		{	  		
			mDC.MoveTo( fw1-fw1/10-meterthata+rect.left , f2h-K*((fw1-fw1/10)-m_ab)+meterthata*K+rect.top); 	  //��y�ᣬ����ֱ�߽���
  			mDC.LineTo(fw1/10+meterthata+rect.left, f2h-K*(fw1/10-m_ab)-meterthata*K+rect.top);                     //��y�ᣬ����ֱ�߽���
 	
 		}

		 if ( m_AB>fw1/10 && m_AB<fw1-fw1/10 &&   m_ab<fw1/10 ) 
 		{		
  			mDC.MoveTo( m_AB-meterthata +rect.left, f2h-m_avesize*3600+meterthata*K+rect.top);      //��X�ᣬ����ֱ�߽���
  			mDC.LineTo( fw1/10+meterthata+rect.left, f2h-K*(fw1/10-m_ab)-meterthata*K+rect.top);   //��y�ᣬ����ֱ�߽���
  			Pennihe.DeleteObject();	
 		}


}

 		//����ͼ��
			CPen newPenlast; 
			newPenlast.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
			mDC.SelectObject(&newPenlast); 
			mDC.MoveTo(rect.right,rect.top);			
			mDC.LineTo(rect.right,rect.top-10*xLogPixPerMM);
			mDC.MoveTo(rect.right,rect.bottom);			
			mDC.LineTo(rect.right,rect.top+10*xLogPixPerMM);
  			mDC.MoveTo(rect.left,rect.bottom);
   			mDC.LineTo(rect.right,rect.bottom);
			mDC.MoveTo(rect.right,rect.top);
   			mDC.LineTo(rect.right,rect.bottom);			
			mDC.MoveTo(rect.right,rect.top-10*xLogPixPerMM);			
			mDC.LineTo(rect.right,rect.bottom+10*xLogPixPerMM);
			

	pDC->BitBlt(tRect.left,tRect.top,tRect.right,tRect.bottom,&mDC,0,0,SRCCOPY); 
	mDC.SelectObject(pOldBmp);
	mDC.DeleteDC();
    memBitmap.DeleteObject();//��
	
}

void CDoStraightness::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFormView::OnPrepareDC(pDC, pInfo);
	pDC->SetMapMode(MM_ANISOTROPIC);
}

BOOL CDoStraightness::OnPreparePrinting(CPrintInfo* pInfo) 
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
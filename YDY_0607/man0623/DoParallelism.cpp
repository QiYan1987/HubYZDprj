// DoParallelism.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DoParallelism.h"
#include "MainFrm.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoParallelism

IMPLEMENT_DYNCREATE(CDoParallelism, CFormView)

CDoParallelism::CDoParallelism()
	: CFormView(CDoParallelism::IDD)
{
	//{{AFX_DATA_INIT(CDoParallelism)
	//}}AFX_DATA_INIT
	m_bDrawStartFigeure1=true;
	m_bDrawMoveFigeure1=true;
	m_bDrawEndFigeure1=true;

 	m_bDrawStartFigeure2=true;
	m_bDrawMoveFigeure2=true;
	m_bDrawEndFigeure2=true;
	m_bDraw1=FALSE;
	m_bDraw2=FALSE;
}

CDoParallelism::~CDoParallelism()
{
}

void CDoParallelism::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoParallelism)
	DDX_Control(pDX, IDC_PARALLEL_STATIC, m_editParallelism);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoParallelism, CFormView)
	//{{AFX_MSG_MAP(CDoParallelism)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SELECTBUTTON, OnSelectbutton)
	ON_BN_CLICKED(IDC_ANALYSISBUTTON, OnAnalysisbutton)
	ON_BN_CLICKED(IDC_resetpxd, Onresetpxd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_COMMAND(ID_BTNRESETDEAL, OnBtnresetdeal)
	ON_BN_CLICKED(ID_BTNENABLE,OnSelectbutton)
	ON_BN_CLICKED(ID_BTNDISABLE,OnSelectbutton)
	ON_COMMAND(ID_Print, OnPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoParallelism diagnostics

#ifdef _DEBUG
void CDoParallelism::AssertValid() const
{
	CFormView::AssertValid();
}

void CDoParallelism::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoParallelism message handlers

void CDoParallelism::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->DestroyVIEW(((CMainFrame*)AfxGetMainWnd())->m_DoParallelism);
	((CMainFrame*)AfxGetMainWnd())->m_DoParallelism=NULL;
	((CMainFrame*)AfxGetMainWnd())->Desktop();
}

void CDoParallelism::OnSelectbutton() 
{
	// TODO: Add your control notification handler code here
	if (m_lineselect==TRUE)
	{
		GetDlgItem(IDC_PARALLEL_STATIC)->EnableWindow(false);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,TRUE);
	
	}
	else if (m_lineselect==FALSE)	
	{
		GetDlgItem(IDC_PARALLEL_STATIC)->EnableWindow(true);
		((CMainFrame*)AfxGetMainWnd())->SetToolBarState(2,FALSE);
	}
	m_lineselect=!m_lineselect;
}

void CDoParallelism::OnAnalysisbutton() 
{
	// TODO: Add your control notification handler code here
	
}

void CDoParallelism::Onresetpxd() 
{
	// TODO: Add your control notification handler code here

}

void CDoParallelism::DrawingCleanAndReset(CString path, BOOL isSelected)
{
	shuju ChangeDate[7200];
	std::ifstream fin(path, std::ios::binary);
	int i;
	for (i=0;i<7200;i++)
	{
		fin.read((char*)&ChangeDate[i],sizeof(shuju));
	}
	fin.read((char*)&G1,sizeof(double));
	fin.read((char*)&G2,sizeof(double));
	fin.read((char*)&m_Height,sizeof(float));
	fin.read((char*)&m_time,sizeof(CTime));
	fin.close();
	
	std::ofstream fout(path, std::ios::binary);
	for (i=0;i<7200;i++)
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

void CDoParallelism::ChangeValueOfSelect(CString path, int startPosition, int endPosition, BOOL isSelected)
{
	shuju ChangeDate[7200];
	std::ifstream fin(path, std::ios::binary);
	int i;

	if (endPosition>startPosition)
	{	
		for (i=0;i<7200;i++)
		{
			fin.read((char*)&ChangeDate[i],sizeof(shuju));
		}
		fin.read((char*)&G1,sizeof(double));
		fin.read((char*)&G2,sizeof(double));
		fin.read((char*)&m_Height,sizeof(float));
		fin.read((char*)&m_time,sizeof(CTime));
		fin.close();
		
		std::ofstream fout(path, std::ios::binary);
		for (i=0;i<7200;i++)
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
		for (i=0;i<7200;i++)
		{
			fin.read((char*)&ChangeDate[i],sizeof(shuju));
		}
		fin.read((char*)&G1,sizeof(double));
		fin.read((char*)&G2,sizeof(double));
		fin.read((char*)&m_Height,sizeof(float));
		fin.read((char*)&m_time,sizeof(CTime));
		fin.close();
		
		std::ofstream fout(path, std::ios::binary);
		for (i=0;i<7200;i++)
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

void CDoParallelism::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	m_lineselect=TRUE;
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
	m_editParallelism.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);	
}

void CDoParallelism::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd *pWnd=GetDlgItem(IDC_PARALLEL_STATIC);    
    CDC  *pDC=pWnd->GetDC();
	CRect rect;
	this->ClientToScreen(&point);          
	pWnd->GetClientRect(&rect);  
    pWnd->ClientToScreen(rect);        
	point.x=point.x-rect.left;
	point.y=point.y-rect.top;
	pDC->SetBkMode(TRANSPARENT);
    double fh=(rect.bottom-rect.top)/30;
	if((point.x)<m_min||(point.x)>m_max||(point.y)>(rect.bottom-rect.top-fh)||(point.y)<fh);	
	else
	{
		m_bDraw1=TRUE;
		m_bDrawStartFigeure1=TRUE;
		m_bDrawStartFigeure2=FALSE;
		m_StartPoint=m_LastEndPoint=point;//保存当前点
 	}

	if((point.x)<m_min2||(point.x)>m_max2||(point.y)>(rect.bottom-rect.top-fh)||(point.y)<fh);	
	else
	{
		m_bDrawStartFigeure1=FALSE;
		m_bDrawStartFigeure2=TRUE;
		m_StartPoint=m_LastEndPoint=point;//保存当前点
		m_bDraw2=TRUE;	
 	}

	m_mouseOrigin=m_StartPoint;

	ReleaseDC(pDC);	
	CFormView::OnLButtonDown(nFlags, point);
}

void CDoParallelism::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd * pWnd=GetDlgItem(IDC_PARALLEL_STATIC);                           
    CDC *pDC=pWnd->GetDC();
	CRect rect;
    pWnd->GetClientRect(&rect);  
	
	this->ClientToScreen(&point);                                
    pWnd->GetClientRect(rect);                               
    pWnd->ClientToScreen(rect);                              

	point.x=point.x-rect.left;
	point.y=point.y-rect.top;
	  
	double f2= rect.Height();                                                 	                             
    double fh=rect.Height()/30;
	double m_Y;
    m_Y=f2-fh*2;
	double m_avesize; //y轴平均分成3600份	
    m_avesize=m_Y/3600;
    double fw1=(3*rect.Width()/5)/2;
	double f_pmid=fw1+3*rect.Width()/20;//f_pmid:图2中线
    int i;
	double f2h=f2-fh;
 	double m_pmaxaverage=m_pmax-m_paverage;
	double m_pmaxaverage2=m_pmax2-m_paverage2;
	if((point.x)<m_min||(point.x)>m_max||(point.y)>(rect.bottom-rect.top-fh)||(point.y)<fh);	
	else	
	{	 
		m_bDraw1=FALSE;  
		m_bDrawEndFigeure1=FALSE;
		m_bDrawEndFigeure2=FALSE;
		m_mouseFinish=point;

	//////计算鼠标按下的y值和抬起时的y值////////////
	CPen selectPen(PS_SOLID,1,RGB(148,0,211));
	pDC->SelectObject(&selectPen); 
			
	///////////////选择线条变色///////////////////	
    m_startPosition=3600-(m_mouseOrigin.y-fh)/m_avesize;
	m_endPosition=3600-(m_mouseFinish.y-fh)/m_avesize;
	

    ChangeValueOfSelect(((CMainFrame*)AfxGetMainWnd())->m_fullPath4,m_startPosition,m_endPosition,1);
	
}
	///////////////////////////图2：显示//////////////////////////////////////////////////////////
	if((point.x)<m_min2||(point.x)>m_max2||(point.y)>(rect.bottom-rect.top-fh)||(point.y)<fh);	
	else	
	{	 
		m_bDraw2=FALSE;      
		m_bDrawEndFigeure1==FALSE;
		m_bDrawEndFigeure2=FALSE;
		m_mouseFinish=point;	        
			
        m_startPosition=7200-(m_mouseOrigin.y-fh)/m_avesize;
		m_endPosition=7200-(m_mouseFinish.y-fh)/m_avesize;			
	
    ChangeValueOfSelect(((CMainFrame*)AfxGetMainWnd())->m_fullPath4,m_startPosition,m_endPosition,1);
}
	CFormView::OnLButtonUp(nFlags, point);
}

void CDoParallelism::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		if (MK_LBUTTON & nFlags)
	{	
		CWnd *pwnd=GetDlgItem(IDC_PARALLEL_STATIC);//获取静态框的指针
		CDC *pDC=pwnd->GetDC();
		CRect rect;
		this->ClientToScreen(&point);  
		pwnd->GetClientRect(rect);          
		pwnd->ClientToScreen(rect);  	
		point.x=point.x-rect.left;
		point.y=point.y-rect.top;	
		CPen pen(PS_SOLID,2,RGB(192,14,35));
		pDC->SelectObject(&pen);	
		double fh=(rect.bottom-rect.top)/30;
		if((point.x)<m_min||(point.x)>m_max||(point.y)>(rect.bottom-rect.top-fh)||(point.y)<fh);				
		
		else  
		{	
			if(m_bDraw1==TRUE)             //鼠标左键按下可以开始绘图
				{	
					m_bDrawMoveFigeure1=TRUE;
					m_bDrawMoveFigeure2=false;
					m_MovePoint=point;
				}	
		}

		if((point.x)<m_min2||(point.x)>m_max2||(point.y)>(rect.bottom-rect.top-fh)||(point.y)<fh);				
		else  
		{	
			if(m_bDraw2==TRUE)             //鼠标左键按下可以开始绘图
				{	
				     m_bDrawMoveFigeure1=false;
					 m_bDrawMoveFigeure2=TRUE;
					 m_MovePoint=point;
				}	
		}
		pen.DeleteObject();
	}	

		OnPaint();
	CFormView::OnMouseMove(nFlags, point);
}


void CDoParallelism::OnPaint() 
{
	CPaintDC dc1(this); 
 	CRect rectback;
    GetClientRect(rectback);
    dc1.FillSolidRect(rectback,RGB(255,255,255));  //设置为白色背景
    CWnd *pWnd; 
    CRect rect; 
    CDC *pDC;
    CDC mDC;                      
	pWnd = GetDlgItem(IDC_PARALLEL_STATIC);      
	pWnd->GetClientRect(&rect); 
	pDC = pWnd->GetDC();
	CBitmap* pOldBmp= NULL;     
	CBitmap memBitmap;                               
	mDC.CreateCompatibleDC(pDC);             
	memBitmap.CreateCompatibleBitmap(pDC,rect.right,rect.bottom);
	pOldBmp = mDC.SelectObject(&memBitmap);
    mDC.FillSolidRect(rect.left,rect.top,rect.right,rect.bottom,RGB(255,255,255));
	CPen RectPen(PS_SOLID,1,RGB(0,0,0));
	mDC.SelectObject(&RectPen);               
	mDC.Rectangle(rect.left,rect.top,rect.right,rect.bottom); //静态框加上绿色边框
    RectPen.DeleteObject();
	//////////////////////////////////////////////////////////////////////
	CFont   font; 
	font.CreateFont(12,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
	CFont*   pOldFont=(CFont*)mDC.SelectObject(&font); 
  	CPen Penn(PS_SOLID,1,RGB(0,150,150));
  	mDC.SelectObject(&Penn);

	double fw1=(3*rect.Width()/5)/2,f1=rect.Width(),f2=rect.Height();  //fw1图1和图2分割线，fw1/2图1中线                                             	                             
    double fw2=2*rect.Width()/5;
    double fh=rect.Height()/30;
	double f_pmid=fw1+3*rect.Width()/20;//f_pmid:图2中线
	double f_pleft=fw1,f_pright=2*fw1,f_pwidth=f_pright-f_pleft;
    mDC.SetBkMode(TRANSPARENT); 
	int i,j;
	double m_Y; 
	double m_avescale;
    m_Y=f2-fh*2;
    m_avescale=m_Y/4;
	double m_smallavescale;
	m_smallavescale=m_Y/36;
	double f2h=f2-fh;
	double m_avesize; //y轴平均分成3600份	
    m_avesize=m_Y/3600;

	if (m_bDrawStartFigeure1==TRUE && m_bDrawMoveFigeure1==TRUE)
	{			
		if (m_StartPoint==m_mouseFinish)
		{
			m_MovePoint=m_mouseFinish;
			mDC.FillSolidRect(fw1/10,m_StartPoint.y,fw1-fw1/5,m_MovePoint.y-m_StartPoint.y,RGB(255,192,203)); //选择范围填充颜色
		}
		else
 		   mDC.FillSolidRect(fw1/10,m_StartPoint.y,fw1-fw1/5,m_MovePoint.y-m_StartPoint.y,RGB(255,192,203)); //选择范围填充颜色
	    	m_mouseFinish=m_MovePoint;
	}


	if (m_bDrawStartFigeure2==TRUE && m_bDrawMoveFigeure2==TRUE)
	{			
		if (m_StartPoint==m_mouseFinish)
		{
			m_MovePoint=m_mouseFinish;
			mDC.FillSolidRect(fw1+fw1/10,m_StartPoint.y,fw1-fw1/5,m_MovePoint.y-m_StartPoint.y,RGB(255,192,203)); //选择范围填充颜色
		}
		else
 			mDC.FillSolidRect(fw1+fw1/10,m_StartPoint.y,fw1-fw1/5,m_MovePoint.y-m_StartPoint.y,RGB(255,192,203)); //选择范围填充颜色
			m_mouseFinish=m_MovePoint;
	}   
	/////////////////////////////读数据并显示///////////////////////////////  
    ReadDataFromFile();

    for(i=0;i<3600;i++)
	{
		pointer[i]=pointer0[i];
		pointer2[i]=pointer0[3600+i];
	}
	double m_psum=0,m_psum2=0;
	for (i=100;i<3500;i++)
	{
		m_psum=m_psum+pointer[i];
	}
	m_paverage=m_psum/3400;

   for (i=100;i<3500;i++)
	{
		m_psum2=m_psum2+pointer2[i];
	}
    m_paverage2=m_psum2/3400;
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
	for (i=3600+100;i<7200-100;i=i+1)
	{
		if (m_data[i].selected==1)
		{
			CPen Penpink; 
			Penpink.CreatePen(PS_SOLID,1,RGB(255,192,203));
			mDC.SelectObject(&Penpink); 
			mDC.MoveTo(fw1+fw1/10,f2h-m_avesize*(i-3600));
   			mDC.LineTo(2*fw1-fw1/10,f2h-m_avesize*(i-3600));
		}
	}
	 ////////////////////////////////////pointer[]数组的值要根据数据大小合适的显示出来
	 //---------pointer[]---------//
	m_pmax=pointer[0];
	m_pmin=pointer[0];

		for (i=100;i<3600-100;i++)
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

	//--------pointer2[]数组---------//
	m_pmax2=pointer2[0];
	m_pmin2=pointer2[0];
	
		for (i=100;i<3600-100;i++)
		{
			if (m_pmax2<pointer2[i])
			{
				m_pmax2=pointer2[i];
			}
			if (m_pmin2>pointer2[i])
			{
				m_pmin2=pointer2[i];
			}	
		}


	//////////////////////////////////////////
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
	m_jiange=(fw1/5)/m_pmaxminaverage;  //用来控制去除点以后的放大作用
	double m_pmaxaverage2=m_pmax2-m_paverage2;
	double m_pminaverage2=m_pmin2-m_paverage2;
	double m_pmaxminaverage2;
	double m_jiange2;
	if (m_pmaxaverage2>m_pminaverage2)
	{
		m_pmaxminaverage2=m_pmaxaverage2;
	}
	else
		m_pmaxminaverage2=m_pminaverage2;
	m_jiange2=(fw1/5)/m_pmaxminaverage2;  //用来控制去除点以后的放大作用
	//----------------------放大倍数的确定--------//
	if (m_jiange>m_jiange2)
	{
		m_jiange=m_jiange2;

	}
	else
		m_jiange2=m_jiange;
	
	//------图1：鼠标作用范围标定
	m_max=2*((m_pmax-m_paverage)*(fw1/5))/m_pmaxaverage+fw1/2;
    m_min=2*((m_pmin-m_paverage)*(fw1/5))/m_pmaxaverage+fw1/2;	
	//------图2：鼠标作用范围标定
	m_max2=2*((m_pmax2-m_paverage2)*(fw1/5))/m_pmaxaverage2+f_pmid;
    m_min2=2*((m_pmin2-m_paverage2)*(fw1/5))/m_pmaxaverage2+f_pmid;
     ////////////////////////////图1：显示///////////////////////////////////
	double AAA[3600];
	for (i=0;i<3600;i=i+1)
	{
		AAA[i]=pointer0[i] -m_paverage;
	}
// 	for (i=100;i<3600-100;i=i+10)
// 	{
// 		if (m_data[i].selected==1)
// 		{
// 			if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
// 			{
// 				CPen newPenrelate; 
// 				newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
// 				mDC.SelectObject(&newPenrelate); 		
// 				mDC.SetPixel(AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i,RGB(0,255,0));//图1：打点
//  				mDC.MoveTo(AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i);
//         		mDC.LineTo(AAA[i+10]*m_jiange+fw1/2,f2h-m_avesize*(i+10));
// 			}
// 		}
// 		else
// 		{   
// 			CPen newPenrelate; 
// 			newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
// 			mDC.SelectObject(&newPenrelate); 
// 			mDC.SetPixel(AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i,RGB(0,0,255));//图1：打点
// 			mDC.MoveTo(AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i);
//        	    mDC.LineTo(AAA[i+10]*m_jiange+fw1/2,f2h-m_avesize*(i+10));
// 		}
// 	}

	/////////////////////////////图2：显示///////////////////////////////////////
	double AAA2[3600];
	for (i=0;i<3600;i=i+1)
	{
		AAA2[i]=pointer2[i] -m_paverage2;
	}
// 	for (i=3600+100;i<7200-100;i=i+10)
// 	{
// 		if (m_data[i].selected==1)
// 		{
// 			if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
// 			{
// 				CPen newPenrelate; 
// 				newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
// 				mDC.SelectObject(&newPenrelate); 
// 				mDC.SetPixel(AAA2[i-3600]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
// 				mDC.MoveTo(AAA2[i-3600]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600));
//         		mDC.LineTo(AAA2[i-3600+10]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600+10));
// 			}
// 		}
// 		else
// 		{   
// 			CPen newPenrelate; 
// 			newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
// 			mDC.SelectObject(&newPenrelate); 
// 			mDC.SetPixel(AAA2[i-3600]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
// 			mDC.MoveTo(AAA2[i-3600]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600));
// 			mDC.LineTo(AAA2[i-3600+10]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600+10));
// 		}
// 	}	

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	CPen newPeny; //图1：画Y轴平行线
	newPeny.CreatePen(PS_DOT,1,RGB(205,205,193));
    mDC.SelectObject(&newPeny);
	CString mark;
	double m_markX2;
	for(i=fw1/10,j=0;j<4;j++)
	{
		mDC.MoveTo(fw1/2-i*j,fh);
		mDC.LineTo(fw1/2-i*j,f2-fh);	
	}
	for(i=fw1/10,j=0;j<5;j++)
	{
		mDC.MoveTo(fw1/2+i*j,fh);
		mDC.LineTo(fw1/2+i*j,f2-fh);
	}
	for(i=fw1/10,j=0;j<4;j++)
	{
		mDC.MoveTo(f_pleft+fw1/2+i*j,fh);
		mDC.LineTo(f_pleft+fw1/2+i*j,f2-fh);
	}
	for(i=fw1/10,j=0;j<5;j++)
	{
		mDC.MoveTo(f_pleft+fw1/2-i*j,fh);
		mDC.LineTo(f_pleft+fw1/2-i*j,f2-fh);
	}
    for(i=fh,j=0;i<=f2-fh,j<36;i+=m_smallavescale,j++)//x轴平行线
	{
		mDC.MoveTo(fw1/10,fh+m_smallavescale*2*j);
		mDC.LineTo(fw1*2-fw1/10,fh+m_smallavescale*2*j);
	}	
	mDC.MoveTo(fw1,fh); 
    mDC.LineTo(fw1,f2-fh);   //图一和图二中线
   	CPen newPenxy; 
	newPenxy.CreatePen(PS_SOLID,1,RGB(0,0,0));
    mDC.SelectObject(&newPenxy); 
	////////////////图一 x轴刻度/////////////////////
	double m_paverageerror;
    m_paverageerror=(m_paverage-2048)*10/(G1*G2*4096);
	CString strm_paverageerror;
    strm_paverageerror.Format("%.2f",m_paverageerror);
	mDC.TextOut(fw1/2-5,f2-fh+2,strm_paverageerror);
	for(i=fw1/10,j=1;j<4;j++)
	{
		mDC.MoveTo(fw1/2-i*j,f2-fh-3);
		mDC.LineTo(fw1/2-i*j,f2-fh);
		if (j%2==0)
		{
			mDC.MoveTo(fw1/2-i*j,f2-fh-8);
			mDC.LineTo(fw1/2-i*j,f2-fh);
		}
	}
	for(i=fw1/10,j=1;j<5;j++)
	{
		mDC.MoveTo(fw1/2+i*j,f2-fh-3);
		mDC.LineTo(fw1/2+i*j,f2-fh);
		if (j%2==0)
		{
			mDC.MoveTo(fw1/2+i*j,f2-fh-8);
			mDC.LineTo(fw1/2+i*j,f2-fh);
		}
	}
	for(i=fw1/5,j=1;j<2;j++)
	{
		m_markX2=((m_paverage-m_pmaxminaverage*j)-2048)*10/(G1*G2*4096);
		mark.Format("%.2f",m_markX2);
		mDC.TextOut(fw1/2-i*j-13,f2-fh+2,mark);
	}

	for(i=fw1/5,j=1;j<3;j++)
	{
		m_markX2=((m_paverage+m_pmaxminaverage*j)-2048)*10/(G1*G2*4096);
		mark.Format("%.2f",m_markX2);
		mDC.TextOut(fw1/2+i*j-10,f2-fh+2,mark);
	}	
    ///////////////图二 x 刻度 //////////////////////
	double m_paverageerror2;
    m_paverageerror2=(m_paverage2-2048)*10/(G1*G2*4096);
	CString strm_paverageerror2;
    strm_paverageerror2.Format("%.2f",m_paverageerror2);
	mDC.TextOut(f_pleft+fw1/2-5,f2-fh+2,strm_paverageerror2);
	for(i=fw1/10,j=1;j<4;j++)
	{
		mDC.MoveTo(f_pleft+fw1/2+i*j,f2-fh-3);
		mDC.LineTo(f_pleft+fw1/2+i*j,f2-fh);
		if (j%2==0)
		{
			mDC.MoveTo(f_pleft+fw1/2+i*j,f2-fh-8);
		    mDC.LineTo(f_pleft+fw1/2+i*j,f2-fh);
		}
	}
	for(i=fw1/10,j=1;j<5;j++)
	{
		mDC.MoveTo(f_pleft+fw1/2-i*j,f2-fh-3);
		mDC.LineTo(f_pleft+fw1/2-i*j,f2-fh);
		if (j%2==0)
		{
			mDC.MoveTo(f_pleft+fw1/2-i*j,f2-fh-8);
		    mDC.LineTo(f_pleft+fw1/2-i*j,f2-fh);
		}
	}
	for(i=fw1/5,j=1;j<2;j++)
	{
		m_markX2=((m_paverage+m_pmaxminaverage*j)-2048)*10/(G1*G2*4096);
		mark.Format("%.2f",m_markX2);
		mDC.TextOut(f_pleft+fw1/2+i*j-10,f2-fh+2,mark);
	}
	for(i=fw1/5,j=1;j<3;j++)
	{
		m_markX2=((m_paverage-m_pmaxminaverage*j)-2048)*10/(G1*G2*4096);
		mark.Format("%.2f",m_markX2);
		mDC.TextOut(f_pleft+fw1/2-i*j-13,f2-fh+2,mark);
	}
	mDC.MoveTo(fw1/10,fh);  //图1和图2连接起来，上x轴
    mDC.LineTo(f_pleft+fw1-fw1/10,fh); 

	mDC.MoveTo(fw1/10,f2-fh);  //图1和图2连接起来，下x轴
    mDC.LineTo(f_pleft+fw1-fw1/10,f2-fh); 

	mDC.MoveTo(fw1/2,fh); 
    mDC.LineTo(fw1/2,f2-fh); //图1中间:y轴
 
	mDC.MoveTo(f_pleft+fw1/2,fh); 
    mDC.LineTo(f_pleft+fw1/2,f2-fh); //图2中间:y轴

	////////////////////////////标注高度///////////////////	
    CPen newPen;
	newPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
    mDC.SelectObject(&newPen); 
	mDC.MoveTo(fw1/10,fh);
    mDC.LineTo(fw1/10,f2-fh);  
	mDC.MoveTo(fw1*2-fw1/10,fh);
    mDC.LineTo(fw1*2-fw1/10,f2-fh);  
	
	for(i=fh,j=0;i<=f2-fh,j<5;i+=m_avescale,j++)//写Y轴大刻度值
	{
		mDC.MoveTo(fw1/10,fh+m_avescale*j);
		mDC.LineTo(fw1/10-4,fh+m_avescale*j);
		mDC.MoveTo(2*fw1-fw1/10,fh+m_avescale*j);
		mDC.LineTo(2*fw1-fw1/10+4,fh+m_avescale*j);
		mark.Format("%.1f",m_Height/4*(4-j));
		mDC.TextOut(fw1/10-26,fh+m_avescale*j-4,mark);	
		mDC.TextOut(2*fw1-fw1/10+5,fh+m_avescale*j-5,mark);	
	}

    CPen newsasPen;
    newsasPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
    mDC.SelectObject(&newsasPen); 
    for(i=fh,j=0;i<=f2-fh,j<36;i+=m_smallavescale,j++)//写Y轴小刻度值
	{
		mDC.MoveTo(fw1/10,fh+m_smallavescale*j);
		mDC.LineTo(fw1/10-2,fh+m_smallavescale*j);

		mDC.MoveTo(2*fw1-fw1/10,fh+m_smallavescale*j);
		mDC.LineTo(2*fw1-fw1/10+2,fh+m_smallavescale*j);
	}

	 	/////////////////////////////////最小二乘直线/////////////////////////////

		double Xroughness[3400],Yroughness[3400];
		double K=0;
		double X0=0,Y0=0,XX=0,XY=0,Bb,Ysum,Xsum,Yave,Xave;
	    double N0=3400;
		Ysum=0;
		Xsum=0;
		Yave=0;
		Xave=0;

		int j1=0;
		for (i=100;i<3500;i++)
		{
			if (m_data[i].selected==0)
			{
				Xroughness[j1] =AAA[i]*m_jiange+fw1/2;  //测量点的横坐标
				Yroughness[j1] =-(f2h-m_avesize*i);  //测量点的纵坐标
				j1++;
			}		
		}
		for (i=0;i<j1;i++)
		{
		
			X0 = X0+ Xroughness[i];
			Y0 = Y0 + Yroughness[i];
			XX = XX + Xroughness[i]*Xroughness[i];
			XY= XY + Xroughness[i]*Yroughness[i];   
		}	
			N0=j1;
			K=(N0 * XY - X0 * Y0) / (N0 * XX - X0*X0) ;  //斜率
 		    Bb=(XY * X0- Y0* XX ) / (X0 * X0- N0 * XX);  //截距

		double yL1[3400];
		for (i=0;i<N0;i++)
		{
			xL1[i] = Xroughness[i];
			yL1[i] = K * xL1[i]+ Bb ;// the first equation of the LSC line；
		}
   
		CPen Pennihe2(PS_SOLID,1,RGB(255,0,255));	  
		mDC.SelectObject(&Pennihe2);

		int meterthata=f2h/100;

			if (K<0)
	{	
		double m_AB=-Bb/K;
	    double m_ab=m_AB-(f2h-m_avesize*0 ) /K;
		mDC.MoveTo( fw1/2, f2h-m_avesize*3600 +meterthata*K);    //上X轴，二乘直线交点
		mDC.LineTo( fw1/2 , f2h-m_avesize*0-meterthata*K); //下X轴，二乘直线交点
		Pennihe2.DeleteObject();

		if (m_AB>fw1/10  &&  m_AB<fw1-fw1/10  &&  m_ab>fw1/10  && m_ab<fw1-fw1/10 ) 
		{
		for (i=100;i<3600-100;i=i+10)
		{
		
			if (m_data[i].selected==1)
			{
				if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
				{  
					double sita=pi/2+atan(K);
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),(f2h-m_avesize*i),RGB(0,255,0));//图1：打点	
					mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),(f2h-m_avesize*i));
					mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*(i+10));
				}
			}
			else
			{   
				if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
				{  
					double sita=pi/2+atan(K);
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*i,RGB(0,0,255));//图1：打点	
					mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),(f2h-m_avesize*i));
					mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*(i+10));
				}
			}
				//Pennihe2.DeleteObject();
		}
		}
		if ( m_AB<fw1/10   &&  m_ab>fw1/10  &&  m_ab<fw1-fw1/10 ) 
 		{		
  		//	mDC.MoveTo( fw1/10+meterthata, f2h+K*(m_ab-fw1/10)-meterthata*K);                  //左y轴，二乘直线交点
  		//	mDC.LineTo( m_ab -meterthata, f2h-m_avesize*0 +meterthata*K);      //下X轴，二乘直线交点
  		//	Pennihe2.DeleteObject();
			for (i=100;i<3600-100;i=i+10)
			{
				
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),(f2h-m_avesize*i),RGB(0,255,0));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),(f2h-m_avesize*i));
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*i,RGB(0,0,255));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*i);
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
				//Pennihe2.DeleteObject();
		}
 		}
		if ( m_AB<fw1/10  &&   m_ab >fw1-fw1/10 ) 
 		{		
  		//	mDC.MoveTo(fw1/10+meterthata, f2h+K*(m_ab-fw1/10)-meterthata*K );                      //左y轴，二乘直线交点
  		//	mDC.LineTo( fw1-fw1/10 -meterthata,f2h+K*(m_ab-(fw1-fw1/10))+meterthata*K);    //右y轴，二乘直线交点
  		//	Pennihe2.DeleteObject();
			for (i=100;i<3600-100;i=i+10)
			{
				
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),(f2h-m_avesize*i),RGB(0,255,0));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),(f2h-m_avesize*i));
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*i,RGB(0,0,255));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*i);
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
			//	Pennihe2.DeleteObject();
		}
 		}
		if ( m_AB>fw1/10 && m_AB<fw1-fw1/10  &&   m_ab>fw1-fw1/10 ) 
 		{		
  		//	mDC.MoveTo( m_AB +meterthata, f2h-m_avesize*3600 - meterthata*K);      //上X轴，二乘直线交点
  		//	mDC.LineTo( fw1-fw1/10 -meterthata,f2h+K*(m_ab-(fw1-fw1/10)) + meterthata*K);   //右y轴，二乘直线交点
  		//	Pennihe2.DeleteObject();	
			for (i=100;i<3600-100;i=i+10)
			{
			
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),(f2h-m_avesize*i),RGB(0,255,0));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),(f2h-m_avesize*i));
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*i,RGB(0,0,255));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*i);
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
			//	Pennihe2.DeleteObject();
		}
 		}
	}
		 if (K>0)
	 {	 
		double m_AB=-Bb/K;//上交点
	    double m_ab=m_AB-(f2h-m_avesize*0 ) /K;//下交点
		mDC.MoveTo( fw1/2, f2h-m_avesize*3600 +meterthata*K);    //上X轴，二乘直线交点
		mDC.LineTo( fw1/2 , f2h-m_avesize*0-meterthata*K); //下X轴，二乘直线交点
 		if (m_AB>fw1/10  &&  m_AB<fw1-fw1/10  &&  m_ab>fw1/10  && m_ab<fw1-fw1/10 ) 
  		{		
//  			mDC.MoveTo( f2h-m_avesize*0-meterthata*K, f2h-m_avesize*3600 +meterthata*K);    //上X轴，二乘直线交点
//   		    mDC.LineTo(  m_ab+meterthata , f2h-m_avesize*0-meterthata*K);      //下X轴，二乘直线交点

			Pennihe2.DeleteObject();

			for (i=100;i<3600-100;i=i+10)
			{
				
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=atan(K)-pi/2;
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),(f2h-m_avesize*i),RGB(0,255,0));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),(f2h-m_avesize*i));
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=atan(K)-pi/2;
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*i,RGB(0,0,255));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*i);
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
			//	Pennihe2.DeleteObject();		
 		}
		}

			if ( m_AB>fw1-fw1/10  &&   m_ab>fw1/10 &&  m_ab<fw1-fw1/10 ) 
 		{		
  			//mDC.MoveTo( fw1-fw1/10-meterthata, f2h-K*((fw1-fw1/10)-m_ab)+meterthata*K);                  //右y轴，二乘直线交点
			//mDC.LineTo( m_ab +meterthata, f2h-m_avesize*0-meterthata*K);      //下X轴，二乘直线交点
			//Pennihe2.DeleteObject();
			//	mDC.MoveTo( fw1/2, f2h-m_avesize*3500 +meterthata*K);    //上X轴，二乘直线交点
			//	mDC.LineTo( fw1/2 , f2h-m_avesize*100-meterthata*K); //下X轴，二乘直线交点
				
				
				for (i=100;i<3600-100;i=i+10)
				{
					if (m_data[i].selected==1)
					{
						if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
						{  
							double sita=atan(K)-pi/2;
							CPen newPenrelate; 
							newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
							mDC.SelectObject(&newPenrelate); 
							mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),(f2h-m_avesize*i),RGB(0,255,0));//图1：打点	
							mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),(f2h-m_avesize*i));
							mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*(i+10));
						}
					}
					else
					{   
						if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
						{  
							double sita=atan(K)-pi/2;
							CPen newPenrelate; 
							newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
							mDC.SelectObject(&newPenrelate); 
							mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*i,RGB(0,0,255));//图1：打点	
							mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*i);
							mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*(i+10));
						}
					}
				//	Pennihe2.DeleteObject();		
 		}
		}	
		if ( m_AB>fw1-fw1/10  &&    m_ab<fw1/10 ) 
		{		
			//mDC.MoveTo( fw1-fw1/10 -meterthata,f2h-K*((fw1-fw1/10)-m_ab)+meterthata*K);    //右y轴，二乘直线交点	
			//mDC.LineTo(fw1/10+meterthata, f2h-K*(fw1/10-m_ab) -meterthata*K);                      //左y轴，二乘直线交点
			//Pennihe2.DeleteObject();	
			//mDC.MoveTo( fw1/2, f2h-m_avesize*3500 +meterthata*K);    //上X轴，二乘直线交点
			//mDC.LineTo( fw1/2 , f2h-m_avesize*100-meterthata*K); //下X轴，二乘直线交点
			
			
			for (i=100;i<3600-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=atan(K)-pi/2;
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),(f2h-m_avesize*i),RGB(0,255,0));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),(f2h-m_avesize*i));
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=atan(K)-pi/2;
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*i,RGB(0,0,255));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*i);
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
			//	Pennihe2.DeleteObject();		
 		}
		}
		if ( m_AB>fw1/10 && m_AB<fw1-fw1/10 &&   m_ab<fw1/10 ) 
		{		
			//mDC.MoveTo( m_AB-meterthata , f2h-m_avesize*3600+meterthata*K);      //上X轴，二乘直线交点
			//mDC.LineTo( fw1/10+meterthata,f2h-K*(fw1/10-m_ab)-meterthata*K);   //左y轴，二乘直线交点
			//Pennihe2.DeleteObject();
			//mDC.MoveTo( fw1/2, f2h-m_avesize*3500 +meterthata*K);    //上X轴，二乘直线交点
			//mDC.LineTo( fw1/2 , f2h-m_avesize*100-meterthata*K); //下X轴，二乘直线交点
			
			
			for (i=100;i<3600-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=atan(K)-pi/2;
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),(f2h-m_avesize*i),RGB(0,255,0));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),(f2h-m_avesize*i));
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=atan(K)-pi/2;
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*i,RGB(0,0,255));//图1：打点	
						mDC.MoveTo(((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*i);
						mDC.LineTo(((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-fw1/2+0.5*meterthata),f2h-m_avesize*(i+10));
					}
				}
		//		Pennihe2.DeleteObject();		
 		}
		}
	}

 		////////////////////////////最小二乘直线2/////////////////////////////  
		double Xroughness2[3400],Yroughness2[3400];
		double K2=0;
		double X02=0,Y02=0,XX2=0,XY2=0,Bb2;
	    double N02=3400;
		int j2=0;
		for (i=100;i<3500;i++)
		{
			if (m_data[i+3600].selected==0)
			{
				Xroughness2[j2] =AAA2[i]*m_jiange2+f_pmid;  //测量点的横坐标
				Yroughness2[j2] =-(f2h-m_avesize*i);  //测量点的纵坐标
				j2++;
			}
		}
		for (i=0;i<j2;i++)
		{	
			X02 = X02+ Xroughness2[i];
			Y02 = Y02 + Yroughness2[i];
			XX2 = XX2 + Xroughness2[i]*Xroughness2[i];
			XY2= XY2 + Xroughness2[i]*Yroughness2[i];   
		}	
		    N02=j2;
			K2=(N02 * XY2 - X02 * Y02) / (N02 * XX2 - X02*X02) ;
 		    Bb2=(XY2 * X02- Y02* XX2 ) / (X02 * X02- N02 * XX2);
   
		CPen Pennihe22(PS_SOLID,1,RGB(255,0,255));	  
		mDC.SelectObject(&Pennihe22);

		if (K2<0)
	{	 
		double m_AB2=-Bb2/K2;
	    double m_ab2=m_AB2-(f2h-m_avesize*0 ) /K2;
		double sita=pi/2+atan(K);
		mDC.MoveTo( (m_AB2+meterthata)*cos(sita)-(f2h-m_avesize*3600 -meterthata*K2)*sin(sita)-(m_AB2-2*meterthata-fw1*3/2), f2h-m_avesize*3600 +meterthata*K2);    //上X轴，二乘直线交点
	   	mDC.LineTo( ( m_ab2 -meterthata)*cos(sita)-(f2h-m_avesize*0+meterthata*K2)*sin(sita)-(m_AB2-2*meterthata-fw1*3/2), f2h-m_avesize*0-meterthata*K2);      //下X轴，二乘直线交点
		
		if (m_AB2>fw1/10  &&  m_AB2<fw1-fw1/10  &&  m_ab2>fw1/10  && m_ab2<fw1-fw1/10 ) 
		{
			

			for (i=3600+100;i<7200-100;i=i+10)
			{
			if (m_data[i].selected==1)
			{
				if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
				{
					
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
					mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600));
					mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10));
				}
			}
			else
			{   
				CPen newPenrelate; 
				newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
				mDC.SelectObject(&newPenrelate); 
				mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
				mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600));
				mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10));
			}
			Pennihe2.DeleteObject();
			}
		}
	
		
		
		if (m_AB2>fw1+fw1/10  &&  m_AB2< 2*fw1-fw1/10  &&  m_ab2>fw1+fw1/10  && m_ab2< 2*fw1-fw1/10 ) 
  		{		
			for (i=3600+100;i<7200-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
					{
						
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
						mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600));
						mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10));
					}
				}
				else
				{   
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
					mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600));
					mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10));
				}
				Pennihe2.DeleteObject();
			}
 		}
		if ( m_AB2<fw1+fw1/10   &&  m_ab2>fw1+fw1/10  &&  m_ab2< 2*fw1-fw1/10 ) 
 		{		
			for (i=3600+100;i<7200-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
					{
						
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
						mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600));
						mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10));
					}
				}
				else
				{   
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
					mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600));
					mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10));
				}
				Pennihe2.DeleteObject();
			}
 		}	
		if ( m_AB2<fw1+fw1/10  &&   m_ab2 > 2*fw1-fw1/10) 
 		{		
			for (i=3600+100;i<7200-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
					{
						
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
						mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600));
						mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10));
					}
				}
				else
				{   
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
					mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600));
					mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10));
				}
				Pennihe2.DeleteObject();
			}	
 		}
		if ( m_AB2>fw1+fw1/10 && m_AB2< 2*fw1-fw1/10  &&   m_ab2> 2*fw1-fw1/10 ) 
 		{		
			for (i=3600+100;i<7200-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
					{
						
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
						mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600));
						mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10));
					}
				}
				else
				{   
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
					mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600));
					mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-2*meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10));
				}
				Pennihe2.DeleteObject();
			}	
		}
		}	
		if (K2>0)
	{	 
		double m_AB2=-Bb2/K2;
	    double m_ab2=m_AB2-(f2h-m_avesize*0 ) /K2;
	    double sita=atan(K)-pi/2;
		mDC.MoveTo( (m_AB2+meterthata)*cos(sita)-(f2h-m_avesize*3600 -meterthata*K2)*sin(sita)+(fw1*3/2-m_AB2+meterthata), f2h-m_avesize*3600 +meterthata*K2);    //上X轴，二乘直线交点
	   	mDC.LineTo( ( m_ab2 -meterthata)*cos(sita)-(f2h-m_avesize*0+meterthata*K2)*sin(sita)+(fw1*3/2-m_AB2+meterthata), f2h-m_avesize*0-meterthata*K2);      //下X轴，二乘直线交点
		
		if (m_AB2>fw1/10  &&  m_AB2<fw1-fw1/10  &&  m_ab2>fw1/10  && m_ab2<fw1-fw1/10 ) 
		{
			

			for (i=3600+100;i<7200-100;i=i+10)
			{
			if (m_data[i].selected==1)
			{
				if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
				{
					
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
					mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600));
					mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600+10));
				}
			}
			else
			{   
				CPen newPenrelate; 
				newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
				mDC.SelectObject(&newPenrelate); 
				mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
				mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600));
				mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600+10));
			}
			Pennihe2.DeleteObject();
			}
		}
	
		
		
		if (m_AB2>fw1+fw1/10  &&  m_AB2< 2*fw1-fw1/10  &&  m_ab2>fw1+fw1/10  && m_ab2< 2*fw1-fw1/10 ) 
  		{		
			for (i=3600+100;i<7200-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
					{
						
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
						mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600));
						mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600+10));
					}
				}
				else
				{   
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
					mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600));
					mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600+10));
				}
				Pennihe2.DeleteObject();
			}
 		}
		if ( m_AB2<fw1+fw1/10   &&  m_ab2>fw1+fw1/10  &&  m_ab2< 2*fw1-fw1/10 ) 
 		{		
			for (i=3600+100;i<7200-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
					{
						
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
						mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600));
						mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600+10));
					}
				}
				else
				{   
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
					mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600));
					mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600+10));
				}
				Pennihe2.DeleteObject();
			}
 		}	
		if ( m_AB2<fw1+fw1/10  &&   m_ab2 > 2*fw1-fw1/10) 
 		{		
			for (i=3600+100;i<7200-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
					{
						
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
						mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600));
						mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600+10));
					}
				}
				else
				{   
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
					mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600));
					mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600+10));
				}
				Pennihe2.DeleteObject();
			}	
 		}
		if ( m_AB2>fw1+fw1/10 && m_AB2< 2*fw1-fw1/10  &&   m_ab2> 2*fw1-fw1/10 ) 
 		{		
			for (i=3600+100;i<7200-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
					{
						
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
						mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600));
						mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600+10));
					}
				}
				else
				{   
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
					mDC.MoveTo((AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600));
					mDC.LineTo((AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)+(fw1*3/2-m_AB2+meterthata),f2h-m_avesize*(i-3600+10));
				}
				Pennihe2.DeleteObject();
			}	
		}
		}
	fw1=2*fw1;
    //////////////////////表格///////////////////////////////
	CFont   fontgrid; 
	fontgrid.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体"); 
	CFont*   pOldFontgrid=(CFont*)mDC.SelectObject(&fontgrid); 

    double l1=rect.left,l2=rect.top,l3=rect.right,l4=rect.bottom;
	int gridxnums=1;int gridynums=22;
    double fwgx=fw2,fwgy=f2;
	double dx=fw2/gridxnums;
	double dy=f2/gridynums;
	CRect gridRect(l1+fw1,l2,fw2,l4);
	mDC.FillSolidRect(l1+fw1,l2,fw2,l4,RGB(255,255,255));
	CPen gridPen(0,0,RGB(0,0,20));
    CPen *oldpen2=mDC.SelectObject(&gridPen);
	mDC.FillSolidRect(l1+fw1,l2,fw2,dy-1,RGB(232,232,232));//给头行填充颜色
 	mDC.FillSolidRect(l1+fw1,dy*5,fw2,dy-1,RGB(232,232,232));//给指定行填充颜色
 	mDC.FillSolidRect(l1+fw1,dy*13,fw2,dy-1,RGB(232,232,232));//给指定行填充颜色
	for(int m=0;m<gridxnums;m++) //画出gridxnums条竖线                      
	{
		mDC.MoveTo(l1+fw1+m*dx,gridRect.bottom);
		mDC.LineTo(l1+fw1+m*dx,0);
	}
	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
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
    mDC.TextOut(mid ,meter,"平行度测量结果");
	mDC.TextOut(mid,dy*5+meter," 规格要求");
	mDC.TextOut(mid,dy*13+meter," 测量参数");
    mDC.TextOut(m1,dy+meter,"文件名");
	mDC.TextOut(m1,dy*2+meter,"测量时间");
	mDC.TextOut(m1,dy*6+meter,"参考类型");                                       
	mDC.TextOut(m1,dy*7+meter,"滤波器种类");                                              
	mDC.TextOut(m1,dy*8+meter,"滤波范围");    
	mDC.TextOut(m1,dy*9+meter,"测量高度");                                                                   	
	mDC.TextOut(m1,dy*14+meter,"工艺要求");  
	mDC.TextOut(m1,dy*15+meter,"平行度");                                                                             
   //显示文件名
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath4;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	mDC.TextOut((m1+m2)/2,dy*1+meter,str);
	//显示测量时间
	str=m_time.Format("%Y-%m-%d %H:%M");
	mDC.TextOut((m1+m2)/2,dy*2+meter,str);
	//显示测量高度
	CString markheight;
	markheight.Format("%.1f",m_Height);
	mDC.TextOut(m2,dy*9+meter,markheight);
	str.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[3]);
	mDC.TextOut(m2,dy*14+meter,str);
	mDC.TextOut(m2,dy*6+meter," 最小二乘法");
	mDC.TextOut(m2,dy*7+meter,"Gaussian");
	mDC.TextOut(m2,dy*8+meter,"1-50");
	mDC.TextOut(m3,dy*9+meter,"  mm");
	mDC.TextOut(m3,dy*14+meter,"  um");
	mDC.TextOut(m3,dy*15+meter,"  um");
	Parallelalgorithm();
	CString x1;	
	x1.Format("%.3f",GResult);		
 	mDC.TextOut(m2,dy*15+meter,x1);
	//修正图形
	CPen newPenlast; 
	newPenlast.CreatePen(PS_SOLID,3,RGB(0,0,0));
	mDC.SelectObject(&newPenlast); 
  	mDC.MoveTo(rect.left,rect.bottom);
   	mDC.LineTo(rect.right,rect.bottom);

	pDC->BitBlt(rect.left,rect.top,rect.right,rect.bottom,&mDC,0,0,SRCCOPY); //把已经绘好的图显示在制定位置上
    mDC.SelectObject(pOldBmp);
    mDC.DeleteDC();
    memBitmap.DeleteObject();//释放内存设备
   // Do not call CFormView::OnPaint() for painting messages
}

void CDoParallelism::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_editParallelism.GetSafeHwnd())
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
		m_editParallelism.MoveWindow(x,y,(rect.Height()-rect.Height()/20)*5/3,rect.Height()-rect.Height()/22);
	}
}

void CDoParallelism::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

void CDoParallelism::OnBtnresetdeal() 
{
	// TODO: Add your command handler code here
	DrawingCleanAndReset(((CMainFrame*)AfxGetMainWnd())->m_fullPath4,0);
	m_bDrawStartFigeure1=FALSE;
	m_bDrawMoveFigeure1=FALSE;
	m_bDrawEndFigeure1=FALSE;
	m_MovePoint.y=0;
	m_StartPoint.y=0;
	OnPaint();
}



void CDoParallelism::Parallelalgorithm()
{
		/////////////////////////////////////直线度1算法//////////////////////////////
	double mindd,maxdd;
    double Yroughness[3600],xroughness[3600], AAA[3600],aa1[3600],yL1[3600],xL1[3600]; 
    double miny,maxy,z=360,an=0,M=0,b=0;
	/*double G1=4,G2=0.1516;*/
	double t0=0,s1=0,t1=0,s2=0;

    int s0=3400;
	int i;
	for (i=0;i<3600;i++)
	{
		AAA[i]=((pointer[i]-2048)* 10) / (G1 * G2 * 4096);
		aa1[i]= z * i / 3600;
		
	}

	for (i=0;i<s0;i++)
	{
		xroughness[i] = aa1[i+99];   //测量点的横坐标
		if (m_data[i].selected==0)
		{
		 Yroughness[i] = AAA[i+99];   //测量点的纵坐标
		}

        else Yroughness[i] =((m_paverage-2048)* 10) / (G1 * G2 * 4096);
	}
	
	 for (i=0;i<s0;i++)
	{
		t0 = t0 + Yroughness[i];
		s1 = s1 + xroughness[i];                  
		t1 = t1 + xroughness[i] * Yroughness[i];
		s2 = s2 + xroughness[i] * xroughness[i];  
	}
	 an = s0 * s2 - s1*s1;                  //直线度的分母
	if (an == 0) 
	{
		an = 0.00001;        //分母不能为0
	}
    M = (s0 * t1 - s1 * t0) / an ;// 求解最小二乘拟合直线系数。
    b = (s2 * t0 - s1 * t1) / an;

	for (i=0;i<s0;i++)
	{
		xL1[i] = xroughness[i];
		yL1[i] = M * xL1[i]+ b ;// the first equation of the LSC line；
	}


    /////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////直线度2算法//////////////////////////////
    double Yroughness2[3600],xroughness2[3600], AAA2[3600],aa2[3600],yL2[3600],xL2[3600],DD[3600]; 
    double an2=0,M2=0,b2=0;
	double t02=0,s12=0,t12=0,s22=0;
    int s02=3400;
	for (i=0;i<3600;i++)
	{
		AAA2[i]=((pointer2[i]-2048)* 10) / (G1 * G2 * 4096);
		aa2[i]= z * i / 3600;  
		
	}

	for (i=0;i<s02;i++)
	{
		xroughness2[i] = aa2[i+99];  //测量点的横坐标
		if (m_data[i+3600].selected==0)
		{
		 Yroughness2[i] = AAA2[i+99];  //测量点的纵坐标
		}
		else Yroughness2[i] =((m_paverage-2048)* 10) / (G1 * G2 * 4096);

	}  
	 for (i=0;i<s02;i++)
	{
		t02 = t02 + Yroughness2[i];
		s12 = s12 + xroughness2[i];                  
		t12 = t12 + xroughness2[i] * Yroughness2[i];
		s22 = s22 + xroughness2[i] * xroughness2[i];  
	}
	 an2 = s02 * s22 - s12*s12;                  //直线度的分母
	if (an2 == 0) 
	{
		an2 = 0.00001;        //分母不能为0
	}
    M2= (s02 * t12 - s12 * t02) / an2 ;// 求解最小二乘拟合直线系数。
    b2 = (s22 * t02 - s12 * t12) / an2;

	for (i=0;i<s02;i++)
	{
		xL2[i] = xroughness2[i];
		yL2[i] = M2 * xL2[i]+ b2 ;// the first equation of the LSC line；
	}

	for (i=0;i<3400;i++)
	{
	 DD[i]=sqrt((xL1[i]-xL2[i])*(xL1[i]-xL2[i])+(yL2[i]-yL1[i])*(yL2[i]-yL1[i]));
	 if(i==0)
		{
			mindd = DD[0];
			maxdd = DD[0];
		}
		else
		{
			if(mindd >= DD[i])
				mindd = DD[i];
			
			if(maxdd <= DD[i])
				maxdd = DD[i];
		}
	}

	GResult =maxdd - mindd;


}

void CDoParallelism::ReadDataFromFile()
{
	std::ifstream fin(((CMainFrame*)AfxGetMainWnd())->m_fullPath4, std::ios::binary);
	for(int i=0;i<7200;i++)
	{
		fin.read((char*)&m_data[i], sizeof(shuju));
		pointer0[i]=m_data[i].data;
	}
	fin.read((char*)&G1,sizeof(double));
	fin.read((char*)&G2,sizeof(double));
	fin.read((char*)&m_Height,sizeof(float));
	fin.read((char*)&m_time,sizeof(CTime));
 	fin.close();
}

void CDoParallelism::OnDraw(CDC* pDC) 
{
			// TODO: Add your specialized code here and/or call the base class
	CRect rect1;
	int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);//X方向一英寸像素的个数,A4纸
    int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);//Y方向一英寸像素的个数
	int xLogPixPerMM=xLogPixPerInch/25.4;//X方向1mm像素的个数
	int yLogPixPerMM=yLogPixPerInch/25.4;//Y方向1mm像素的个数
	m_penScale=xLogPixPerInch/96;//
	
	//打印框的尺寸为150*250(mm)
	CPoint pt(0,0);//纸张的左上角为00点
	CSize  sz(270*xLogPixPerMM,200*yLogPixPerMM);//sz矩形框的大小，X方向和Y方向像素的总个数
	CRect  tRect(pt,sz);//定义的打印区的矩形框
	rect1.top=tRect.top+25*yLogPixPerMM;
	rect1.right=tRect.right;
	rect1.left=tRect.left+20*xLogPixPerMM;
	rect1.bottom=tRect.bottom-25*yLogPixPerMM;
	
	pOldBmp = NULL;                           // 将旧的位图指针置空	
	mDC.CreateCompatibleDC(pDC);             // 创建内存绘图设备，使内存位图的DC与控件的DC关联
	memBitmap.CreateCompatibleBitmap(pDC,tRect.right,tRect.bottom);
	pOldBmp = mDC.SelectObject(&memBitmap);
    mDC.FillSolidRect(tRect.left,tRect.top,tRect.right,tRect.bottom,RGB(255,255,255));//给矩形框填充白色*/
	CPen RectPen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	mDC.SelectObject(&RectPen);      //笔和字体用之前需要selectobject，用完后需要deleteobject      
	mDC.Rectangle(rect1.left,rect1.top,rect1.right,rect1.bottom); //静态框加上 颜色 边框
	
	//修改打印字体大小
	CFont   font; 
	font.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
		DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体");  
	CFont*   pOldFont=(CFont*)mDC.SelectObject(&font); 
	
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
	lstrcpy((LPSTR)newLogFont.lfFaceName,(LPSTR)"宋体"); 
	newLogFont.lfEscapement=0; 
	newLogFont.lfUnderline=FALSE; 
	newLogFont.lfItalic=FALSE; 
	newLogFont.lfStrikeOut=FALSE; 
    newLogFont.lfCharSet=GB2312_CHARSET;
	//创建并设置新的字体，保留以前的字体
	CFont newFont;
	CFont *oldFont;
	
	newFont.CreateFontIndirect(&newLogFont);
	oldFont = mDC.SelectObject(&newFont );
	
	//绘制上栏
	mDC.MoveTo(rect1.left,rect1.top);
	mDC.LineTo(rect1.left,rect1.top-10*xLogPixPerMM);
	mDC.MoveTo(rect1.left,rect1.top-10*xLogPixPerMM);
	mDC.LineTo(rect1.right,rect1.top-10*xLogPixPerMM);
	mDC.MoveTo(rect1.right,rect1.top-10*xLogPixPerMM);
	mDC.LineTo(rect1.right,rect1.top);
	//绘制下栏
	mDC.MoveTo(rect1.left,rect1.bottom);
	mDC.LineTo(rect1.left,rect1.bottom+10*xLogPixPerMM);
	mDC.MoveTo(rect1.left,rect1.bottom+10*xLogPixPerMM);
	mDC.LineTo(rect1.right,rect1.bottom+10*xLogPixPerMM);
	mDC.MoveTo(rect1.right,rect1.bottom+10*xLogPixPerMM);
	mDC.LineTo(rect1.right,rect1.bottom);
	RectPen.DeleteObject();
	
	//写入信息
    mDC.TextOut(0.8*rect1.left+200*xLogPixPerMM,rect1.bottom+11*yLogPixPerMM,
		"广州威而信精密仪器有限公司");
	
	CString str;
	str=((CMainFrame*)AfxGetMainWnd())->m_strOperatorName;
	str.Format("操作员:%s",str);
	mDC.TextOut(rect1.left+75*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineModel;
	str.Format("机床型号:%s",str);
	mDC.TextOut(rect1.left+115*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strMachineName;
	str.Format("机床:%s",str);
	mDC.TextOut(rect1.left+155*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strProcess;
	str.Format("工序:%s",str);
	mDC.TextOut(rect1.left+195*xLogPixPerMM,rect1.top-7*yLogPixPerMM,str);
	
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceModel;
	str.Format("工件型号:%s",str);
	mDC.TextOut(rect1.left+15*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strWorkpieceNum;
	str.Format("工件编号:%s",str);
	mDC.TextOut(rect1.left+75*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strIndent;
	str.Format("订单:%s",str);
	mDC.TextOut(rect1.left+135*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);
	str=((CMainFrame*)AfxGetMainWnd())->m_strInspector;
	str.Format("检测员:%s",str);
	mDC.TextOut(rect1.left+195*xLogPixPerMM,rect1.bottom+3*yLogPixPerMM,str);

	double gridleft=(rect1.right-rect1.left)*3/5+rect1.left;
	int gridxnums=1;int gridynums=22;//一列25行
	double dx= ((rect1.right-rect1.left)-gridleft)/gridxnums;//一列的宽度
	double dy=(rect1.bottom-rect1.top)/gridynums;//一行的高度
    CRect gridRect(gridleft,rect1.top,gridleft+dx*gridxnums,rect1.top+dy*gridynums);
	
	mDC.FillSolidRect(gridleft,gridRect.top,rect1.right,dy,RGB(232,232,232));
	mDC.FillSolidRect(gridleft,gridRect.top+dy*5,rect1.right,dy,RGB(232,232,232));//给指定行填充颜色
	mDC.FillSolidRect(gridleft,gridRect.top+dy*13,rect1.right,dy,RGB(232,232,232));
	
	for( int m0=0;m0<=0;m0++) //画出gridxnums条竖线                      
	{
		mDC.MoveTo(gridRect.left+m0*dx,gridRect.bottom);
		mDC.LineTo(gridRect.left+m0*dx,gridRect.top);
		mDC.MoveTo(rect1.right+m0*dx,rect1.bottom);
		mDC.LineTo(rect1.right+m0*dx,rect1.top);
	}
		
	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
	{
		mDC.MoveTo(gridRect.left,gridRect.top+n*dy);
		mDC.LineTo(rect1.right,gridRect.top+n*dy);
	}  
////////////////////////////////////////////////////////////////////////////
	double fw1=(3*rect1.Width()/5)/2,f1=rect1.Width(),f2=rect1.Height();  //fw1图1和图2分割线，fw1/2图1中线                                             	                             
    double fw2=2*rect1.Width()/5;
    double fh=rect1.Height()/30;
	double f_pmid=fw1+3*rect1.Width()/20;//f_pmid:图2中线
	double f_pleft=fw1,f_pright=2*fw1,f_pwidth=f_pright-f_pleft;
    mDC.SetBkMode(TRANSPARENT); 
	int i,j;
	double m_Y; 
	double m_avescale;
    m_Y=f2-fh*2;
    m_avescale=m_Y/4;
	double m_smallavescale;
	m_smallavescale=m_Y/36;
	double f2h=f2-fh;
	double m_avesize; //y轴平均分成3600份	
    m_avesize=m_Y/3600;

	/////////////////////////////读数据并显示///////////////////////////////  
    ReadDataFromFile();

    for(i=0;i<3600;i++)
	{
		pointer[i]=pointer0[i];
		pointer2[i]=pointer0[3600+i];
	}
	double m_psum=0,m_psum2=0;
	for (i=100;i<3500;i++)
	{
		m_psum=m_psum+pointer[i];
	}
	m_paverage=m_psum/3400;

   for (i=100;i<3500;i++)
	{
		m_psum2=m_psum2+pointer2[i];
	}
    m_paverage2=m_psum2/3400;
	//////////////////////////////////////////////////////
	for (i=100;i<3600-100;i=i+1)
	{
		if (m_data[i].selected==1)
		{
			CPen Penpink; 
			Penpink.CreatePen(PS_SOLID,1,RGB(255,192,203));
			mDC.SelectObject(&Penpink); 
			mDC.MoveTo(rect1.left+fw1/10,rect1.top+f2h-m_avesize*i);
   			mDC.LineTo(rect1.left+fw1-fw1/10,rect1.top+f2h-m_avesize*i);
		}
	}
	for (i=3600+100;i<7200-100;i=i+1)
	{
		if (m_data[i].selected==1)
		{
			CPen Penpink; 
			Penpink.CreatePen(PS_SOLID,1,RGB(255,192,203));
			mDC.SelectObject(&Penpink); 
			mDC.MoveTo(rect1.left+fw1+fw1/10,rect1.top+f2h-m_avesize*(i-3600));
   			mDC.LineTo(rect1.left+fw1*2-fw1/10,rect1.top+f2h-m_avesize*(i-3600));
		}
	}
	 ////////////////////////////////////pointer[]数组的值要根据数据大小合适的显示出来
	 //---------pointer[]---------//
	m_pmax=pointer[0];
	m_pmin=pointer[0];

		for (i=100;i<3600-100;i++)
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

	//--------pointer2[]数组---------//
	m_pmax2=pointer2[0];
	m_pmin2=pointer2[0];
	
		for (i=100;i<3600-100;i++)
		{
			if (m_pmax2<pointer2[i])
			{
				m_pmax2=pointer2[i];
			}
			if (m_pmin2>pointer2[i])
			{
				m_pmin2=pointer2[i];
			}	
		}


	//////////////////////////////////////////
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
	m_jiange=(fw1/5)/m_pmaxminaverage;  //用来控制去除点以后的放大作用
	double m_pmaxaverage2=m_pmax2-m_paverage2;
	double m_pminaverage2=m_pmin2-m_paverage2;
	double m_pmaxminaverage2;
	double m_jiange2;
	if (m_pmaxaverage2>m_pminaverage2)
	{
		m_pmaxminaverage2=m_pmaxaverage2;
	}
	else
		m_pmaxminaverage2=m_pminaverage2;
	m_jiange2=(fw1/5)/m_pmaxminaverage2;  //用来控制去除点以后的放大作用
	//----------------------放大倍数的确定--------//
	if (m_jiange>m_jiange2)
	{
		m_jiange=m_jiange2;

	}
	else
		m_jiange2=m_jiange;
	
	//------图1：鼠标作用范围标定
	m_max=2*((m_pmax-m_paverage)*(fw1/5))/m_pmaxaverage+fw1/2;
    m_min=2*((m_pmin-m_paverage)*(fw1/5))/m_pmaxaverage+fw1/2;	
	//------图2：鼠标作用范围标定
	m_max2=2*((m_pmax2-m_paverage2)*(fw1/5))/m_pmaxaverage2+f_pmid;
    m_min2=2*((m_pmin2-m_paverage2)*(fw1/5))/m_pmaxaverage2+f_pmid;
     ////////////////////////////图1：显示///////////////////////////////////
	double AAA[3600];
	for (i=0;i<3600;i=i+1)
	{
		AAA[i]=pointer0[i] -m_paverage;
	}
// 	for (i=100;i<3600-100;i=i+10)
// 	{
// 		if (m_data[i].selected==1)
// 		{
// 			if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
// 			{
// 				CPen newPenrelate; 
// 				newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
// 				mDC.SelectObject(&newPenrelate); 		
// 				mDC.SetPixel(AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i,RGB(0,255,0));//图1：打点
//  				mDC.MoveTo(AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i);
//         		mDC.LineTo(AAA[i+10]*m_jiange+fw1/2,f2h-m_avesize*(i+10));
// 			}
// 		}
// 		else
// 		{   
// 			CPen newPenrelate; 
// 			newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
// 			mDC.SelectObject(&newPenrelate); 
// 			mDC.SetPixel(AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i,RGB(0,0,255));//图1：打点
// 			mDC.MoveTo(AAA[i]*m_jiange+fw1/2,f2h-m_avesize*i);
//        	    mDC.LineTo(AAA[i+10]*m_jiange+fw1/2,f2h-m_avesize*(i+10));
// 		}
// 	}

	/////////////////////////////图2：显示///////////////////////////////////////
	double AAA2[3600];
	for (i=0;i<3600;i=i+1)
	{
		AAA2[i]=pointer2[i] -m_paverage2;
	}
// 	for (i=3600+100;i<7200-100;i=i+10)
// 	{
// 		if (m_data[i].selected==1)
// 		{
// 			if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
// 			{
// 				CPen newPenrelate; 
// 				newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
// 				mDC.SelectObject(&newPenrelate); 
// 				mDC.SetPixel(AAA2[i-3600]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600),RGB(0,255,0));//图2：打点
// 				mDC.MoveTo(AAA2[i-3600]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600));
//         		mDC.LineTo(AAA2[i-3600+10]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600+10));
// 			}
// 		}
// 		else
// 		{   
// 			CPen newPenrelate; 
// 			newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
// 			mDC.SelectObject(&newPenrelate); 
// 			mDC.SetPixel(AAA2[i-3600]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600),RGB(0,0,255));//图2：打点
// 			mDC.MoveTo(AAA2[i-3600]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600));
// 			mDC.LineTo(AAA2[i-3600+10]*m_jiange2+f_pmid,f2h-m_avesize*(i-3600+10));
// 		}
// 	}	

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	CPen newPeny; //图1：画Y轴平行线
	newPeny.CreatePen(PS_DOT,1,RGB(205,205,193));
    mDC.SelectObject(&newPeny);
	CString mark;
	double m_markX2;
	for(i=fw1/10,j=0;j<4;j++)
	{
		mDC.MoveTo(rect1.left+fw1/2-i*j,fh+rect1.top);
		mDC.LineTo(rect1.left+fw1/2-i*j,f2-fh+rect1.top);	
	}
	for(i=fw1/10,j=0;j<5;j++)
	{
		mDC.MoveTo(rect1.left+fw1/2+i*j,fh+rect1.top);
		mDC.LineTo(rect1.left+fw1/2+i*j,f2-fh+rect1.top);
	}
	for(i=fw1/10,j=0;j<4;j++)
	{
		mDC.MoveTo(rect1.left+f_pleft+fw1/2+i*j,fh+rect1.top);
		mDC.LineTo(rect1.left+f_pleft+fw1/2+i*j,f2-fh+rect1.top);
	}
	for(i=fw1/10,j=0;j<5;j++)
	{
		mDC.MoveTo(rect1.left+f_pleft+fw1/2-i*j,fh+rect1.top);
		mDC.LineTo(rect1.left+f_pleft+fw1/2-i*j,f2-fh+rect1.top);
	}
    for(i=fh,j=0;i<=f2-fh,j<36;i+=m_smallavescale,j++)//x轴平行线
	{
		mDC.MoveTo(rect1.left+fw1/10,fh+m_smallavescale*2*j+rect1.top);
		mDC.LineTo(rect1.left+fw1*2-fw1/10,fh+m_smallavescale*2*j+rect1.top);
	}	
	mDC.MoveTo(rect1.left+fw1,fh+rect1.top); 
    mDC.LineTo(rect1.left+fw1,f2-fh+rect1.top);   //图一和图二中线
   	CPen newPenxy; 
	newPenxy.CreatePen(PS_SOLID,1,RGB(0,0,0));
    mDC.SelectObject(&newPenxy); 
	////////////////图一 x轴刻度/////////////////////
	double m_paverageerror;
    m_paverageerror=(m_paverage-2048)*10/(G1*G2*4096);
	CString strm_paverageerror;
    strm_paverageerror.Format("%.2f",m_paverageerror);
	mDC.TextOut(rect1.left+fw1/2-5,f2-fh+2+rect1.top,strm_paverageerror);
	for(i=fw1/10,j=1;j<4;j++)
	{
		mDC.MoveTo(rect1.left+fw1/2-i*j,f2-fh-3+rect1.top);
		mDC.LineTo(rect1.left+fw1/2-i*j,f2-fh+rect1.top);
		if (j%2==0)
		{
			mDC.MoveTo(rect1.left+fw1/2-i*j,f2-fh-8+rect1.top);
			mDC.LineTo(rect1.left+fw1/2-i*j,f2-fh+rect1.top);
		}
	}
	for(i=fw1/10,j=1;j<5;j++)
	{
		mDC.MoveTo(rect1.left+fw1/2+i*j,f2-fh-3+rect1.top);
		mDC.LineTo(rect1.left+fw1/2+i*j,f2-fh+rect1.top);
		if (j%2==0)
		{
			mDC.MoveTo(rect1.left+fw1/2+i*j,f2-fh-8+rect1.top);
			mDC.LineTo(rect1.left+fw1/2+i*j,f2-fh+rect1.top);
		}
	}
	for(i=fw1/5,j=1;j<2;j++)
	{
		m_markX2=((m_paverage-m_pmaxminaverage*j)-2048)*10/(G1*G2*4096);
		mark.Format("%.2f",m_markX2);
		mDC.TextOut(rect1.left+fw1/2-i*j-13,f2-fh+2+rect1.top,mark);
	}

	for(i=fw1/5,j=1;j<3;j++)
	{
		m_markX2=((m_paverage+m_pmaxminaverage*j)-2048)*10/(G1*G2*4096);
		mark.Format("%.2f",m_markX2);
		mDC.TextOut(rect1.left+fw1/2+i*j-10,f2-fh+2+rect1.top,mark);
	}	
    ///////////////图二 x 刻度 //////////////////////
	double m_paverageerror2;
    m_paverageerror2=(m_paverage2-2048)*10/(G1*G2*4096);
	CString strm_paverageerror2;
    strm_paverageerror2.Format("%.2f",m_paverageerror2);
	mDC.TextOut(rect1.left+f_pleft+fw1/2-5,f2-fh+2+rect1.top,strm_paverageerror2);
	for(i=fw1/10,j=1;j<4;j++)
	{
		mDC.MoveTo(rect1.left+f_pleft+fw1/2+i*j,f2-fh-3+rect1.top);
		mDC.LineTo(rect1.left+f_pleft+fw1/2+i*j,f2-fh+rect1.top);
		if (j%2==0)
		{
			mDC.MoveTo(rect1.left+f_pleft+fw1/2+i*j,f2-fh-8+rect1.top);
		    mDC.LineTo(rect1.left+f_pleft+fw1/2+i*j,f2-fh+rect1.top);
		}
	}
	for(i=fw1/10,j=1;j<5;j++)
	{
		mDC.MoveTo(rect1.left+f_pleft+fw1/2-i*j,f2-fh-3+rect1.top);
		mDC.LineTo(rect1.left+f_pleft+fw1/2-i*j,f2-fh+rect1.top);
		if (j%2==0)
		{
			mDC.MoveTo(rect1.left+f_pleft+fw1/2-i*j,f2-fh-8+rect1.top);
		    mDC.LineTo(rect1.left+f_pleft+fw1/2-i*j,f2-fh+rect1.top);
		}
	}
	for(i=fw1/5,j=1;j<2;j++)
	{
		m_markX2=((m_paverage+m_pmaxminaverage*j)-2048)*10/(G1*G2*4096);
		mark.Format("%.2f",m_markX2);
		mDC.TextOut(rect1.left+f_pleft+fw1/2+i*j-10,f2-fh+2+rect1.top,mark);
	}
	for(i=fw1/5,j=1;j<3;j++)
	{
		m_markX2=((m_paverage-m_pmaxminaverage*j)-2048)*10/(G1*G2*4096);
		mark.Format("%.2f",m_markX2);
		mDC.TextOut(rect1.left+f_pleft+fw1/2-i*j-13,f2-fh+2+rect1.top,mark);
	}
	mDC.MoveTo(rect1.left+fw1/10,fh+rect1.top);  //图1和图2连接起来，上x轴
    mDC.LineTo(rect1.left+f_pleft+fw1-fw1/10,fh+rect1.top); 

	mDC.MoveTo(rect1.left+fw1/10,f2-fh+rect1.top);  //图1和图2连接起来，下x轴
    mDC.LineTo(rect1.left+f_pleft+fw1-fw1/10,f2-fh+rect1.top); 

	mDC.MoveTo(rect1.left+fw1/2,fh+rect1.top); 
    mDC.LineTo(rect1.left+fw1/2,f2-fh+rect1.top); //图1中间:y轴
 
	mDC.MoveTo(rect1.left+f_pleft+fw1/2,fh+rect1.top); 
    mDC.LineTo(rect1.left+f_pleft+fw1/2,f2-fh+rect1.top); //图2中间:y轴

	////////////////////////////标注高度///////////////////	
    CPen newPen;
	newPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
    mDC.SelectObject(&newPen); 
	mDC.MoveTo(rect1.left+fw1/10,fh+rect1.top);
    mDC.LineTo(rect1.left+fw1/10,f2-fh+rect1.top);  
	mDC.MoveTo(rect1.left+fw1*2-fw1/10,fh+rect1.top);
    mDC.LineTo(rect1.left+fw1*2-fw1/10,f2-fh+rect1.top);  
	
	for(i=fh,j=0;i<=f2-fh,j<5;i+=m_avescale,j++)//写Y轴大刻度值
	{
		mDC.MoveTo(rect1.left+fw1/10,fh+m_avescale*j+rect1.top);
		mDC.LineTo(rect1.left+fw1/10-4,fh+m_avescale*j+rect1.top);
		mDC.MoveTo(rect1.left+2*fw1-fw1/10,fh+m_avescale*j+rect1.top);
		mDC.LineTo(rect1.left+2*fw1-fw1/10+4,fh+m_avescale*j+rect1.top);
		mark.Format("%.1f",m_Height/4*(4-j));
		mDC.TextOut(rect1.left+fw1/10-26,fh+m_avescale*j-4+rect1.top,mark);	
		mDC.TextOut(rect1.left+2*fw1-fw1/10+5,fh+m_avescale*j-5+rect1.top,mark);	
	}

    CPen newsasPen;
    newsasPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
    mDC.SelectObject(&newsasPen); 
    for(i=fh,j=0;i<=f2-fh,j<36;i+=m_smallavescale,j++)//写Y轴小刻度值
	{
		mDC.MoveTo(rect1.left+fw1/10,fh+m_smallavescale*j+rect1.top);
		mDC.LineTo(rect1.left+fw1/10-2,fh+m_smallavescale*j+rect1.top);

		mDC.MoveTo(rect1.left+2*fw1-fw1/10,fh+m_smallavescale*j+rect1.top);
		mDC.LineTo(rect1.left+2*fw1-fw1/10+2,fh+m_smallavescale*j+rect1.top);
	}

 	/////////////////////////////////最小二乘直线/////////////////////////////
		double Xroughness[3400],Yroughness[3400];
		double K=0;
		double X0=0,Y0=0,XX=0,XY=0,Bb,Ysum,Xsum,Yave,Xave;
	    double N0=3400;
		Ysum=0;
		Xsum=0;
		Yave=0;
		Xave=0;

		int j1=0;
		for (i=100;i<3500;i++)
		{
			if (m_data[i].selected==0)
			{
				Xroughness[j1] =AAA[i]*m_jiange+fw1/2;  //测量点的横坐标
				Yroughness[j1] =-(f2h-m_avesize*i);  //测量点的纵坐标
				j1++;
			}		
		}
		for (i=0;i<j1;i++)
		{
		
			X0 = X0+ Xroughness[i];
			Y0 = Y0 + Yroughness[i];
			XX = XX + Xroughness[i]*Xroughness[i];
			XY= XY + Xroughness[i]*Yroughness[i];   
		}	
			N0=j1;
			K=(N0 * XY - X0 * Y0) / (N0 * XX - X0*X0) ;  //斜率
 		    Bb=(XY * X0- Y0* XX ) / (X0 * X0- N0 * XX);  //截距

		double yL1[3400];
		for (i=0;i<N0;i++)
		{
			xL1[i] = Xroughness[i];
			yL1[i] = K * xL1[i]+ Bb ;// the first equation of the LSC line；
		}
   
		CPen Pennihe2(PS_SOLID,1,RGB(255,0,255));	  
		mDC.SelectObject(&Pennihe2);

		int meterthata=f2h/100;


		double sita;
	if (K<0)
	{	
		double m_AB=-Bb/K;
	    double m_ab=m_AB-(f2h-m_avesize*0 ) /K;
		mDC.MoveTo( rect1.left+fw1/2, f2h-m_avesize*3600 +meterthata*K+rect1.top);    //上X轴，二乘直线交点
		mDC.LineTo( rect1.left+fw1/2 , f2h-m_avesize*0-meterthata*K+rect1.top); //下X轴，二乘直线交点
		
	//	double sita=(-pi/2+atan(K));
		if (m_AB>fw1/10  &&  m_AB<fw1-fw1/10  &&  m_ab>fw1/10  && m_ab<fw1-fw1/10 ) 
		{
		for (i=100;i<3600-100;i=i+10)
		{
		
			if (m_data[i].selected==1)
			{
				if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
				{  
						sita=pi/2+atan(K);
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB-meterthata),(f2h-m_avesize*i)+rect1.top,RGB(0,255,0));//图1：打点	
					mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB-meterthata),(f2h-m_avesize*i)+rect1.top);
					mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB-meterthata),f2h-m_avesize*(i+10)+rect1.top);
				}
			}
			else
			{   
				if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
				{  
						sita=pi/2+atan(K);
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB-meterthata),f2h-m_avesize*i+rect1.top,RGB(0,0,255));//图1：打点	
					mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB-meterthata),(f2h-m_avesize*i)+rect1.top);
					mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB-meterthata),f2h-m_avesize*(i+10)+rect1.top);
				}
			}
				Pennihe2.DeleteObject();
		}
		}
		if ( m_AB<fw1/10   &&  m_ab>fw1/10  &&  m_ab<fw1-fw1/10 ) 
 		{		
  		//	mDC.MoveTo( fw1/10+meterthata, f2h+K*(m_ab-fw1/10)-meterthata*K);                  //左y轴，二乘直线交点
  		//	mDC.LineTo( m_ab -meterthata, f2h-m_avesize*0 +meterthata*K);      //下X轴，二乘直线交点
  		//	Pennihe2.DeleteObject();
			for (i=100;i<3600-100;i=i+10)
			{
				
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-fw1/10-meterthata),(f2h-m_avesize*i)+rect1.top,RGB(0,255,0));//图1：打点	
						mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-fw1/10-meterthata),(f2h-m_avesize*i)+rect1.top);
						mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-fw1/10-meterthata),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-fw1/10-meterthata),f2h-m_avesize*i+rect1.top,RGB(0,0,255));//图1：打点	
						mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-fw1/10-meterthata),f2h-m_avesize*i+rect1.top);
						mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-fw1/10-meterthata),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				Pennihe2.DeleteObject();
		}
 		}
		if ( m_AB<fw1/10  &&   m_ab >fw1-fw1/10 ) 
 		{		
  		//	mDC.MoveTo(fw1/10+meterthata, f2h+K*(m_ab-fw1/10)-meterthata*K );                      //左y轴，二乘直线交点
  		//	mDC.LineTo( fw1-fw1/10 -meterthata,f2h+K*(m_ab-(fw1-fw1/10))+meterthata*K);    //右y轴，二乘直线交点
  		//	Pennihe2.DeleteObject();
			for (i=100;i<3600-100;i=i+10)
			{
				
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-fw1/10-meterthata),(f2h-m_avesize*i)+rect1.top,RGB(0,255,0));//图1：打点	
						mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-fw1/10-meterthata),(f2h-m_avesize*i)+rect1.top);
						mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-fw1/10-meterthata),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-fw1/10-meterthata),f2h-m_avesize*i+rect1.top,RGB(0,0,255));//图1：打点	
						mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-fw1/10-meterthata),f2h-m_avesize*i+rect1.top);
						mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-fw1/10-meterthata),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				Pennihe2.DeleteObject();
		}
 		}
		if ( m_AB>fw1/10 && m_AB<fw1-fw1/10  &&   m_ab>fw1-fw1/10 ) 
 		{		
  		//	mDC.MoveTo( m_AB +meterthata, f2h-m_avesize*3600 - meterthata*K);      //上X轴，二乘直线交点
  		//	mDC.LineTo( fw1-fw1/10 -meterthata,f2h+K*(m_ab-(fw1-fw1/10)) + meterthata*K);   //右y轴，二乘直线交点
  		//	Pennihe2.DeleteObject();	
			for (i=100;i<3600-100;i=i+10)
			{
			
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
							sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB -meterthata),(f2h-m_avesize*i)+rect1.top,RGB(0,255,0));//图1：打点	
						mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB -meterthata),(f2h-m_avesize*i)+rect1.top);
						mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB -meterthata),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
							sita=pi/2+atan(K);
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB -meterthata),f2h-m_avesize*i+rect1.top,RGB(0,0,255));//图1：打点	
						mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))+(fw1/2-m_AB -meterthata),f2h-m_avesize*i+rect1.top);
						mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))+(fw1/2-m_AB -meterthata),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				Pennihe2.DeleteObject();
		}
 		}
	}
	 if (K>0)
	 {	 
		double m_AB=-Bb/K;//上交点
	    double m_ab=m_AB-(f2h-m_avesize*0 ) /K;//下交点
 		if (m_AB>fw1/10  &&  m_AB<fw1-fw1/10  &&  m_ab>fw1/10  && m_ab<fw1-fw1/10 ) 
  		{		
//  			mDC.MoveTo( f2h-m_avesize*0-meterthata*K, f2h-m_avesize*3600 +meterthata*K);    //上X轴，二乘直线交点
//   		    mDC.LineTo(  m_ab+meterthata , f2h-m_avesize*0-meterthata*K);      //下X轴，二乘直线交点
			mDC.MoveTo( rect1.left+fw1/2, f2h-m_avesize*3600 +meterthata*K+rect1.top);    //上X轴，二乘直线交点
			mDC.LineTo( rect1.left+fw1/2 , f2h-m_avesize*0-meterthata*K+rect1.top); //下X轴，二乘直线交点
			
			for (i=100;i<3600-100;i=i+10)
			{
				
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=-(pi/2-atan(K));
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-meterthata-fw1/2),(f2h-m_avesize*i)+rect1.top,RGB(0,255,0));//图1：打点	
						mDC.MoveTo( rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-meterthata-fw1/2),(f2h-m_avesize*i)+rect1.top);
						mDC.LineTo( rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-meterthata-fw1/2),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=-(pi/2-atan(K));
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-meterthata-fw1/2),f2h-m_avesize*i+rect1.top,RGB(0,0,255));//图1：打点	
						mDC.MoveTo( rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-meterthata-fw1/2),f2h-m_avesize*i+rect1.top);
						mDC.LineTo( rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-meterthata-fw1/2),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				Pennihe2.DeleteObject();		
 		}
		}

			if ( m_AB>fw1-fw1/10  &&   m_ab>fw1/10 &&  m_ab<fw1-fw1/10 ) 
 		{		
  			//mDC.MoveTo( fw1-fw1/10-meterthata, f2h-K*((fw1-fw1/10)-m_ab)+meterthata*K);                  //右y轴，二乘直线交点
			//mDC.LineTo( m_ab +meterthata, f2h-m_avesize*0-meterthata*K);      //下X轴，二乘直线交点
			//Pennihe2.DeleteObject();
				mDC.MoveTo( rect1.left+ fw1/2, f2h-m_avesize*3600 +meterthata*K+rect1.top);    //上X轴，二乘直线交点
				mDC.LineTo(  rect1.left+fw1/2 , f2h-m_avesize*0-meterthata*K+rect1.top); //下X轴，二乘直线交点
				
				
				for (i=100;i<3600-100;i=i+10)
				{
					if (m_data[i].selected==1)
					{
						if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
						{  
							double sita=-(pi/2-atan(K));
							CPen newPenrelate; 
							newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
							mDC.SelectObject(&newPenrelate); 
							mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(fw1-fw1/10-meterthata-fw1/2),(f2h-m_avesize*i)+rect1.top,RGB(0,255,0));//图1：打点	
							mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(fw1-fw1/10-meterthata-fw1/2),(f2h-m_avesize*i)+rect1.top);
							mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(fw1-fw1/10-meterthata-fw1/2),f2h-m_avesize*(i+10)+rect1.top);
						}
					}
					else
					{   
						if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
						{  
							double sita=-(pi/2-atan(K));
							CPen newPenrelate; 
							newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
							mDC.SelectObject(&newPenrelate); 
							mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(fw1-fw1/10-meterthata-fw1/2),f2h-m_avesize*i+rect1.top,RGB(0,0,255));//图1：打点	
							mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(fw1-fw1/10-meterthata-fw1/2),f2h-m_avesize*i+rect1.top);
							mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(fw1-fw1/10-meterthata-fw1/2),f2h-m_avesize*(i+10)+rect1.top);
						}
					}
					Pennihe2.DeleteObject();		
 		}
		}	
		if ( m_AB>fw1-fw1/10  &&    m_ab<fw1/10 ) 
		{		
			//mDC.MoveTo( fw1-fw1/10 -meterthata,f2h-K*((fw1-fw1/10)-m_ab)+meterthata*K);    //右y轴，二乘直线交点	
			//mDC.LineTo(fw1/10+meterthata, f2h-K*(fw1/10-m_ab) -meterthata*K);                      //左y轴，二乘直线交点
			//Pennihe2.DeleteObject();	
			mDC.MoveTo( rect1.left+fw1/2, f2h-m_avesize*3600 +meterthata*K+rect1.top);    //上X轴，二乘直线交点
			mDC.LineTo( rect1.left+fw1/2 , f2h-m_avesize*0-meterthata*K+rect1.top); //下X轴，二乘直线交点
			
			
			for (i=100;i<3600-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=-(pi/2-atan(K));
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(fw1-fw1/10 -meterthata-fw1/2),(f2h-m_avesize*i)+rect1.top,RGB(0,255,0));//图1：打点	
						mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(fw1-fw1/10 -meterthata-fw1/2),(f2h-m_avesize*i)+rect1.top);
						mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(fw1-fw1/10 -meterthata-fw1/2),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=-(pi/2-atan(K));
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(fw1-fw1/10 -meterthata-fw1/2),f2h-m_avesize*i+rect1.top,RGB(0,0,255));//图1：打点	
						mDC.MoveTo(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(fw1-fw1/10 -meterthata-fw1/2),f2h-m_avesize*i+rect1.top);
						mDC.LineTo(rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(fw1-fw1/10 -meterthata-fw1/2),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				Pennihe2.DeleteObject();		
 		}
		}
		if ( m_AB>fw1/10 && m_AB<fw1-fw1/10 &&   m_ab<fw1/10 ) 
		{		
			//mDC.MoveTo( m_AB-meterthata , f2h-m_avesize*3600+meterthata*K);      //上X轴，二乘直线交点
			//mDC.LineTo( fw1/10+meterthata,f2h-K*(fw1/10-m_ab)-meterthata*K);   //左y轴，二乘直线交点
			//Pennihe2.DeleteObject();
			mDC.MoveTo( rect1.left+fw1/2, f2h-m_avesize*3600 +meterthata*K+rect1.top);    //上X轴，二乘直线交点
			mDC.LineTo( rect1.left+fw1/2 , f2h-m_avesize*0-meterthata*K+rect1.top); //下X轴，二乘直线交点
			
			
			for (i=100;i<3600-100;i=i+10)
			{
				if (m_data[i].selected==1)
				{
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=-(pi/2-atan(K));
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-meterthata-fw1/2),(f2h-m_avesize*i)+rect1.top,RGB(0,255,0));//图1：打点	
						mDC.MoveTo( rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-meterthata-fw1/2),(f2h-m_avesize*i)+rect1.top);
						mDC.LineTo( rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-meterthata-fw1/2),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				else
				{   
					if ( AAA[i]*m_jiange+fw1/2>fw1/10+15  &&  AAA[i]*m_jiange+fw1/2<fw1-fw1/10-15 )
					{  
						double sita=-(pi/2-atan(K));
						CPen newPenrelate; 
						newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
						mDC.SelectObject(&newPenrelate); 
						mDC.SetPixel(rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-meterthata-fw1/2),f2h-m_avesize*i+rect1.top,RGB(0,0,255));//图1：打点	
						mDC.MoveTo( rect1.left+((AAA[i]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*i)*sin(sita))-(m_AB-meterthata-fw1/2),f2h-m_avesize*i+rect1.top);
						mDC.LineTo( rect1.left+((AAA[i+10]*m_jiange+fw1/2)*cos(sita)-(f2h-m_avesize*(i+10))*sin(sita))-(m_AB-meterthata-fw1/2),f2h-m_avesize*(i+10)+rect1.top);
					}
				}
				Pennihe2.DeleteObject();		
 		}
		}
	}
 		////////////////////////////最小二乘直线2/////////////////////////////  
		double Xroughness2[3400],Yroughness2[3400];
		double K2=0;
		double X02=0,Y02=0,XX2=0,XY2=0,Bb2;
	    double N02=3400;
		int j2=0;
		for (i=100;i<3500;i++)
		{
			if (m_data[i+3600].selected==0)
			{
				Xroughness2[j2] =AAA2[i]*m_jiange2+f_pmid;  //测量点的横坐标
				Yroughness2[j2] =-(f2h-m_avesize*i);  //测量点的纵坐标
				j2++;
			}
		}
		for (i=0;i<j2;i++)
		{	
			X02 = X02+ Xroughness2[i];
			Y02 = Y02 + Yroughness2[i];
			XX2 = XX2 + Xroughness2[i]*Xroughness2[i];
			XY2= XY2 + Xroughness2[i]*Yroughness2[i];   
		}	
		    N02=j2;
			K2=(N02 * XY2 - X02 * Y02) / (N02 * XX2 - X02*X02) ;
 		    Bb2=(XY2 * X02- Y02* XX2 ) / (X02 * X02- N02 * XX2);
   
		CPen Pennihe22(PS_SOLID,1,RGB(255,0,255));	  
		mDC.SelectObject(&Pennihe22);
	
		
	if (K2<0)
	{	 
		double m_AB2=-Bb2/K2;
	    double m_ab2=m_AB2-(f2h-m_avesize*0 ) /K2;
	//	mDC.MoveTo( 3*fw1/2, f2h-m_avesize*3600 +meterthata*K);    //上X轴，二乘直线交点
	//	mDC.LineTo( 3*fw1/2 , f2h-m_avesize*0-meterthata*K); //下X轴，二乘直线交点

		double sita=(-pi/2+atan(K));
	//	mDC.MoveTo( (m_AB2-meterthata)*cos(sita)-(f2h-m_avesize*3600 +meterthata*K2)*sin(sita)-(m_AB2-meterthata-fw1*3/2), f2h-m_avesize*3600 +meterthata*K2);    //上X轴，二乘直线交点
	//	mDC.LineTo( ( m_ab2 +meterthata)*cos(sita)-(f2h-m_avesize*0-meterthata*K2)*sin(sita)-(m_AB2-meterthata-fw1*3/2), f2h-m_avesize*0-meterthata*K2);      //下X轴，二乘直线交点

		for (i=3600+100;i<7200-100;i=i+10)
		{
			if (m_data[i].selected==1)
			{
				if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
				{
					CPen newPenrelate; 
					newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
					mDC.SelectObject(&newPenrelate); 
					mDC.SetPixel(rect1.left+(AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600)+rect1.top,RGB(0,255,0));//图2：打点
					mDC.MoveTo(rect1.left+(AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600)+rect1.top);
					mDC.LineTo(rect1.left+(AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10)+rect1.top);
				}
			}
			else
			{   
				CPen newPenrelate; 
				newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
				mDC.SelectObject(&newPenrelate); 
				mDC.SetPixel(rect1.left+(AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600)+rect1.top,RGB(0,0,255));//图2：打点
				mDC.MoveTo(rect1.left+(AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)+(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600)+rect1.top);
				mDC.LineTo(rect1.left+(AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)+(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10)+rect1.top);
			}
			Pennihe2.DeleteObject();
		}		
		
/* 		if (m_AB2>fw1+fw1/10  &&  m_AB2< 2*fw1-fw1/10  &&  m_ab2>fw1+fw1/10  && m_ab2< 2*fw1-fw1/10 ) 
  		{		
			mDC.MoveTo( m_AB2+meterthata, f2h-m_avesize*3600 -meterthata*K2);    //上X轴，二乘直线交点
 			mDC.LineTo(  m_ab2 -meterthata, f2h-m_avesize*0+meterthata*K2);      //下X轴，二乘直线交点
 			Pennihe22.DeleteObject();		
 		}
		if ( m_AB2<fw1+fw1/10   &&  m_ab2>fw1+fw1/10  &&  m_ab2< 2*fw1-fw1/10 ) 
 		{		
  			mDC.MoveTo( fw1+fw1/10+ meterthata, f2h+K2*(m_ab2-(fw1+fw1/10))-meterthata*K2);                  //左y轴，二乘直线交点
  			mDC.LineTo( m_ab2 -meterthata, f2h-m_avesize*0+meterthata*K2);      //下X轴，二乘直线交点
  			Pennihe22.DeleteObject();	
 		}	
		if ( m_AB2<fw1+fw1/10  &&   m_ab2 > 2*fw1-fw1/10) 
 		{		
  			mDC.MoveTo(fw1+fw1/10+meterthata, f2h+K2*(m_ab2-(fw1+fw1/10)) -meterthata*K2);                      //左y轴，二乘直线交点
  			mDC.LineTo( 2*fw1-fw1/10-meterthata ,f2h+K2*(m_ab2-(2*fw1-fw1/10))+meterthata*K2);    //右y轴，二乘直线交点
  			Pennihe22.DeleteObject();	
 		}
		if ( m_AB2>fw1+fw1/10 && m_AB2< 2*fw1-fw1/10  &&   m_ab2> 2*fw1-fw1/10 ) 
 		{		
  			mDC.MoveTo( m_AB2 +meterthata, f2h-m_avesize*3600-meterthata*K2);      //上X轴，二乘直线交点
  			mDC.LineTo( 2*fw1-fw1/10 -meterthata,f2h+K2*(m_ab2-(2*fw1-fw1/10))+meterthata*K2);   //右y轴，二乘直线交点
  			Pennihe2.DeleteObject();	
		}*/
	}
	 if(K2>0)
	 {	 
		double m_AB2=-Bb2/K2;
	    double m_ab2=m_AB2-(f2h-m_avesize*0 ) /K2;
 //	if (m_AB2>fw1+fw1/10  &&  m_AB2<2*fw1-fw1/10  &&  m_ab2>fw1+fw1/10  && m_ab2<2*fw1-fw1/10 ) 
 // 		{	
			double sita=-(pi/2-atan(K));
			mDC.MoveTo(rect1.left+ (m_AB2-meterthata)*cos(sita)-(f2h-m_avesize*3600 +meterthata*K2)*sin(sita)-(m_AB2-meterthata-fw1*3/2), f2h-m_avesize*3600 +meterthata*K2+rect1.top);    //上X轴，二乘直线交点
   		    mDC.LineTo( rect1.left+( m_ab2 +meterthata)*cos(sita)-(f2h-m_avesize*0-meterthata*K2)*sin(sita)-(m_AB2-meterthata-fw1*3/2), f2h-m_avesize*0-meterthata*K2+rect1.top);      //下X轴，二乘直线交点
 		//	mDC.MoveTo( 3*fw1/2, f2h-m_avesize*3600 +meterthata*K2);    //上X轴，二乘直线交点
 		//	mDC.LineTo( 3*fw1/2 , f2h-m_avesize*0-meterthata*K2); //下X轴，二乘直线交点
 			
			
			for (i=3600+100;i<7200-100;i=i+10)
			{
		if (m_data[i].selected==1)
		{
			if ( AAA2[i-3600]*m_jiange2+f_pmid>fw1+fw1/10+15 && AAA2[i-3600]*m_jiange2+f_pmid< 2*fw1-fw1/10-15)
			{
				CPen newPenrelate; 
				newPenrelate.CreatePen(PS_SOLID,1,RGB(0,255,0));
				mDC.SelectObject(&newPenrelate); 
				mDC.SetPixel(rect1.left+(AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600)+rect1.top,RGB(0,255,0));//图2：打点
				mDC.MoveTo(rect1.left+(AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600)+rect1.top);
        		mDC.LineTo(rect1.left+(AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10)+rect1.top);
			}
		}
		else
		{   
			CPen newPenrelate; 
			newPenrelate.CreatePen(PS_SOLID,1,RGB(0,0,255));
			mDC.SelectObject(&newPenrelate); 
			mDC.SetPixel(rect1.left+(AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600)+rect1.top,RGB(0,0,255));//图2：打点
			mDC.MoveTo(rect1.left+(AAA2[i-3600]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600))*sin(sita)-(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600)+rect1.top);
        	mDC.LineTo(rect1.left+(AAA2[i-3600+10]*m_jiange2+f_pmid)*cos(sita)-(f2h-m_avesize*(i-3600+10))*sin(sita)-(m_AB2-meterthata-fw1*3/2),f2h-m_avesize*(i-3600+10)+rect1.top);
			}
		     Pennihe2.DeleteObject();
			}		
	//	}
/*		if ( m_AB2>2*fw1-fw1/10  && m_ab2>fw1+fw1/10 &&  m_ab2< 2*fw1-fw1/10 ) 
 		{		
  			mDC.MoveTo( 2*fw1-fw1/10-meterthata, f2h-K2*((2*fw1-fw1/10)-m_ab2)+meterthata*K2);                  //右y轴，二乘直线交点
  			mDC.LineTo( m_ab2 +meterthata, f2h-m_avesize*0-meterthata*K2);      //下X轴，二乘直线交点
  			Pennihe2.DeleteObject();	
 		}		
		if ( m_AB2>2*fw1-fw1/10 &&    m_ab2<fw1+fw1/10 ) 
 		{		
			mDC.MoveTo( 2*fw1-fw1/10 -meterthata,f2h-K2*((2*fw1-fw1/10)-m_ab2)+meterthata*K2);    //右y轴，二乘直线交点
  			mDC.LineTo(fw1+fw1/10+meterthata, f2h-K2*((fw1+fw1/10)-m_ab2) -meterthata*K2);                      //左y轴，二乘直线交点
  			
  			Pennihe2.DeleteObject();	
 		}
		if ( m_AB2>fw1+fw1/10 && m_AB2<2*fw1-fw1/10  &&   m_ab2<fw1+fw1/10 ) 
 		{		
  			mDC.MoveTo( m_AB2 -meterthata, f2h-m_avesize*3600+meterthata*K2);      //上X轴，二乘直线交点
  			mDC.LineTo( fw1+fw1/10 +meterthata,f2h-K2*((fw1+fw1/10)-m_ab2)-meterthata*K2);   //右y轴，二乘直线交点
  			Pennihe2.DeleteObject();	
 		}*/
	}
		fw1=2*fw1;

    //////////////////////表格///////////////////////////////
/*	CFont   fontgrid; 
	fontgrid.CreateFont(15,0,0,0,200,FALSE,FALSE,FALSE, GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,   
	DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "宋体"); 
	CFont*   pOldFontgrid=(CFont*)mDC.SelectObject(&fontgrid); */

    double l1=rect1.left,l2=rect1.top,l3=rect1.right,l4=rect1.bottom;
/*	int gridxnums=1;int gridynums=25;
    double fwgx=fw2,fwgy=f2;
	double dx=fw2/gridxnums;
	double dy=f2/gridynums;
	CRect gridRect(l1+fw1,l2,fw2,l4);
	mDC.FillSolidRect(rect.left+l1+fw1,l2,rect.top+fw2,l4,RGB(255,255,255));
	CPen gridPen(0,0,RGB(0,0,20));
    CPen *oldpen2=mDC.SelectObject(&gridPen);
	mDC.FillSolidRect(rect.left+l1+fw1,l2,rect.top+fw2,dy-1,RGB(232,232,232));//给头行填充颜色
 	mDC.FillSolidRect(rect.left+l1+fw1,dy*5,rect.top+fw2,dy-1,RGB(232,232,232));//给指定行填充颜色
 	mDC.FillSolidRect(rect.left+l1+fw1,dy*13,rect.top+fw2,dy-1,RGB(232,232,232));//给指定行填充颜色
	for(int m=0;m<gridxnums;m++) //画出gridxnums条竖线                      
	{
		mDC.MoveTo(rect.left+l1+fw1+m*dx,rect.top+gridRect.bottom);
		mDC.LineTo(rect.left+l1+fw1+m*dx,rect.top+0);
	}
	for(int n=0;n<=gridynums;n++) //画出gridynums条横线                        
	{
		mDC.MoveTo(rect.left+l1+fw1,rect.top+n*dy);
		mDC.LineTo(rect.left+l1+fw1+fw2,rect.top+n*dy);
	}
    mDC.SetBkMode(TRANSPARENT); */

	int meter=rect1.Height()/70;
	int m1=l1+fw1+rect1.Width()/100;
	double m2=l1+fw1+dx/2-rect1.Width()/20;
	double m3=l1+fw1+dx-rect1.Width()/15;
	double mid=l1+fw1+dx/2-rect1.Width()/20;
    mDC.TextOut(mid ,rect1.top+meter,"平行度测量结果");
	mDC.TextOut(mid,rect1.top+dy*5+meter," 规格要求");
	mDC.TextOut(mid,rect1.top+dy*13+meter," 测量参数");
    mDC.TextOut(m1,rect1.top+dy+meter,"文件名");
	mDC.TextOut(m1,rect1.top+dy*2+meter,"测量时间");
	mDC.TextOut(m1,rect1.top+dy*6+meter,"参考类型");                                       
	mDC.TextOut(m1,rect1.top+dy*7+meter,"滤波器种类");                                              
	mDC.TextOut(m1,rect1.top+dy*8+meter,"滤波范围");    
	mDC.TextOut(m1,rect1.top+dy*9+meter,"测量高度");                                                                   	
	mDC.TextOut(m1,rect1.top+dy*14+meter,"工艺要求");  
	mDC.TextOut(m1,rect1.top+dy*15+meter,"平行度");                                                                             
   //显示文件名
	str=((CMainFrame*)AfxGetMainWnd())->m_fullPath4;
	int num=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-num-1);
	mDC.TextOut((m1+m2)/1.9,rect1.top+dy*1+meter,str);
	//显示测量时间
	str=m_time.Format("%Y-%m-%d %H:%M");
	mDC.TextOut((m1+m2)/1.9,rect1.top+dy*2+meter,str);
	//显示测量高度
	CString markheight;
	markheight.Format("%.1f",m_Height);
	mDC.TextOut(m2,rect1.top+dy*9+meter,markheight);
	str.Format("%.2f",((CMainFrame*)AfxGetMainWnd())->m_dGongyiPara[3]);
	mDC.TextOut(m2,rect1.top+dy*14+meter,str);
	mDC.TextOut(m2,rect1.top+dy*6+meter," 最小二乘法");
	mDC.TextOut(m2,rect1.top+dy*7+meter,"Gaussian");
	mDC.TextOut(m2,rect1.top+dy*8+meter,"1-50");
	mDC.TextOut(m3,rect1.top+dy*9+meter,"  mm");
	mDC.TextOut(m3,rect1.top+dy*14+meter,"  um");
	mDC.TextOut(m3,rect1.top+dy*15+meter,"  um");
	Parallelalgorithm();
	CString x1;	
	x1.Format("%.2f",GResult);		
 	mDC.TextOut(m2,rect1.top+dy*15+meter,x1);

//////////////////////////////////////////////////////////////////////////

	 		//修正图形
	CPen newPenlast; 
	newPenlast.CreatePen(PS_SOLID,1*m_penScale,RGB(0,0,0));
	mDC.SelectObject(&newPenlast); 
	mDC.MoveTo(rect1.right,rect1.top);			
	mDC.LineTo(rect1.right,rect1.top-10*xLogPixPerMM);
	mDC.MoveTo(rect1.right,rect1.bottom);			
	mDC.LineTo(rect1.right,rect1.top+10*xLogPixPerMM);
	mDC.MoveTo(rect1.left,rect1.bottom);
	mDC.LineTo(rect1.right,rect1.bottom);
	mDC.MoveTo(rect1.right,rect1.top);
	mDC.LineTo(rect1.right,rect1.bottom);			
	mDC.MoveTo(rect1.right,rect1.top-10*xLogPixPerMM);			
	mDC.LineTo(rect1.right,rect1.bottom+10*xLogPixPerMM);
	
	
	pDC->BitBlt(tRect.left,tRect.top,tRect.right,tRect.bottom,&mDC,0,0,SRCCOPY); 
	mDC.SelectObject(pOldBmp);
	mDC.DeleteDC();
    memBitmap.DeleteObject();//释

}

void CDoParallelism::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFormView::OnPrepareDC(pDC, pInfo);
	pDC->SetMapMode(MM_ANISOTROPIC);
}

BOOL CDoParallelism::OnPreparePrinting(CPrintInfo* pInfo) 
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

void CDoParallelism::OnPrint() 
{
	// TODO: Add your command handler code here
	CFormView::OnFilePrint();
}

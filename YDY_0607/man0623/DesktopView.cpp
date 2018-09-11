// DesktopView.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DesktopView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDesktopView

IMPLEMENT_DYNCREATE(CDesktopView, CFormView)

CDesktopView::CDesktopView()
	: CFormView(CDesktopView::IDD)
{
	//{{AFX_DATA_INIT(CDesktopView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDesktopView::~CDesktopView()
{
}

void CDesktopView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDesktopView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDesktopView, CFormView)
	//{{AFX_MSG_MAP(CDesktopView)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesktopView diagnostics

#ifdef _DEBUG
void CDesktopView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDesktopView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDesktopView message handlers

void CDesktopView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->DestroyVIEW(((CMainFrame*)AfxGetMainWnd())->m_desktopview);
	((CMainFrame*)AfxGetMainWnd())->m_desktopview=NULL;
	((CMainFrame*)AfxGetMainWnd())->Desktop();
}

void CDesktopView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect  rect;  
	GetClientRect(&rect);  
	CDC  dcMem;  
	dcMem.CreateCompatibleDC(&dc);  
	CBitmap  bmpBackground;  
	bmpBackground.LoadBitmap(IDB_BITMAP_desktop); 
	BITMAP  bitmap;  
	bmpBackground.GetBitmap(&bitmap);  
	CBitmap  *pbmpOld=dcMem.SelectObject(&bmpBackground); 
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0, bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
	
}

BOOL CDesktopView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CFormView::OnEraseBkgnd(pDC);
}

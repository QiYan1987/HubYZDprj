// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wilson6.h"
#include "Line.h"
#include "const.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{
	a=1;
	b=2;
	m_color=RGB(30,144,255);
	mm_color=RGB(255,255,0);
}

CLine::~CLine()
{

}
void CLine::Line(C3dPoint sp, C3dPoint ep)  //�����ӿڣ������ߵ�����ֵ
{
	m_sp=sp;
	m_ep=ep;
	
}

void CLine::Line(C3dPoint *sp,C3dPoint *ep) //�����ӿڣ�ȡ���ߵ�����ֵ
{
	*sp=m_sp;
	*ep=m_ep;
}

void CLine::Draw(CDC *pDC,CPoint centerPoint)//�ߵĻ��ƺ���
{
	CPoint sp2d;
	CPoint ep2d;
// 	m_sp.x=m_sp.x*10;	m_sp.y=m_sp.y*10;	m_sp.z=m_sp.z*10; //��άͼ����άͼ֮��ת�������еı���
// 	m_ep.x=m_ep.x*10;	m_ep.y=m_ep.y*10;	m_ep.z=m_ep.z*10;
	m_sp.x=m_sp.x;	m_sp.y=m_sp.y;	m_sp.z=m_sp.z;
	m_ep.x=m_ep.x;	m_ep.y=m_ep.y;	m_ep.z=m_ep.z;

	sp2d=m_sp.Change();
	sp2d.x=sp2d.x+centerPoint.x;
	sp2d.y=sp2d.y+centerPoint.y;
	ep2d=m_ep.Change();
	ep2d.x=ep2d.x+centerPoint.x;
	ep2d.y=ep2d.y+centerPoint.y;
	if (m_hide==1)
	{
		CPen myPen(PS_SOLID,a,m_color); //ʵ��
		CPen *pOldPen=pDC->SelectObject(&myPen);
		pDC->MoveTo(sp2d.x,sp2d.y);
		pDC->LineTo(ep2d.x,ep2d.y);
		pDC->SelectObject(pOldPen);
	}
	
	else if (m_hide==2)
	{
		CPen myPen(PS_SOLID,b,mm_color); //ʵ��
		CPen *pOldPen=pDC->SelectObject(&myPen);
		pDC->MoveTo(sp2d.x,sp2d.y);
		pDC->LineTo(ep2d.x,ep2d.y);
		pDC->SelectObject(pOldPen);
	}
}


void CLine::Color(COLORREF col)
{
	m_color=col;
}

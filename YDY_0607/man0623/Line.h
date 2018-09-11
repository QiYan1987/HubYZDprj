// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__3822D52B_AF97_4BA1_9ADA_E54404089A68__INCLUDED_)
#define AFX_LINE_H__3822D52B_AF97_4BA1_9ADA_E54404089A68__INCLUDED_

#include "3dPoint.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLine : public CObject  
{
protected:
	COLORREF m_color;
    COLORREF mm_color;
	C3dPoint m_sp;
	C3dPoint m_ep;  //隐藏数据，设为保护类型
public:
	int b;
	int a;
	
	void Color(COLORREF col);
	int m_hide;
	void Draw(CDC *pDC,CPoint centerPoint);
	void Line(C3dPoint *sp,C3dPoint *ep);
	void Line(C3dPoint sp,C3dPoint ep);
	CLine();
	virtual ~CLine();



};

#endif // !defined(AFX_LINE_H__3822D52B_AF97_4BA1_9ADA_E54404089A68__INCLUDED_)

// 3dPoint.h: interface for the C3dPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DPOINT_H__0FB8101F_E166_4195_9EC9_5A716B42AAEC__INCLUDED_)
#define AFX_3DPOINT_H__0FB8101F_E166_4195_9EC9_5A716B42AAEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class C3dPoint : public CObject    
{
public:
	CPoint Change();
	CPoint Change(int VPOINT_x,int VPOINT_y,int VPOINT_z);
	double x;       //x,y,z是空间三位点的世界坐标
	double y;
	double z;
	C3dPoint();
	C3dPoint(C3dPoint &point);
	C3dPoint operator =(C3dPoint &point);
	~C3dPoint();

};

#endif // !defined(AFX_3DPOINT_H__0FB8101F_E166_4195_9EC9_5A716B42AAEC__INCLUDED_)

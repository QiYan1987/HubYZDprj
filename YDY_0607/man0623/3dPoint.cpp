// 3dPoint.cpp: implementation of the C3dPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wilson6.h"
#include "3dPoint.h"
#include "math.h"
#include "const.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3dPoint::C3dPoint()   //初始化坐标值
{
	x=0;
	y=0;
	z=0;
}

C3dPoint::C3dPoint(C3dPoint &point)  //拷贝构造函数，赋值函数

{
	x=point.x;
	y=point.y;
	z=point.z;
}


C3dPoint::~C3dPoint()
{

}

CPoint C3dPoint::Change()  //三维坐标转化为二维坐标
{
	CPoint point;
	double u=sqrt(VPOINT_X*VPOINT_X+VPOINT_Y*VPOINT_Y+VPOINT_Z*VPOINT_Z);
	double v=sqrt(VPOINT_X*VPOINT_X+VPOINT_Y*VPOINT_Y);
	
	//添加以下五行代码实现了一点透视
	/**/			
	if(OnePoint==true)
	{
		double tempx=(int)((-VPOINT_Y/v)*x+VPOINT_X/v*y);
		double tempy=(int)(-((VPOINT_X*VPOINT_Z)/(u*v))*x-((VPOINT_Y*VPOINT_Z)/(u*v))*y+v/u*z);
		double tempz=-VPOINT_X/u*x-VPOINT_Y/u*y-VPOINT_Z/u*z+u;
		point.x=(int)(tempx*VPOINT_Z/tempz);
		point.y=(int)(tempy*VPOINT_Z/tempz);
		
	}
	
	//以下两行代码实现了透视
	else
	{
		point.x=(int)((-VPOINT_Y/v)*x+VPOINT_X/v*y);
		point.y=(int)(-((VPOINT_X*VPOINT_Z)/(u*v))*x-((VPOINT_Y*VPOINT_Z)/(u*v))*y+v/u*z);
		
	}
	
	return point;
	
}
CPoint C3dPoint :: Change (int VPOINT_x,int VPOINT_y,int VPOINT_z)
{
	CPoint point;
	double u=sqrt(VPOINT_x*VPOINT_x+VPOINT_y*VPOINT_y+VPOINT_z*VPOINT_z*1.0);
	double v=sqrt(VPOINT_x*VPOINT_x+VPOINT_y*VPOINT_y*1.0);
	
	//添加以下五行代码实现了一点透视
	/**/			
	if(OnePoint==true)
	{
		double tempx=(int)((-VPOINT_y/v)*x+VPOINT_x/v*y);
		double tempy=(int)(-((VPOINT_x*VPOINT_z)/(u*v))*x-((VPOINT_y*VPOINT_z)/(u*v))*y+v/u*z);
		double tempz=-VPOINT_x/u*x-VPOINT_y/u*y-VPOINT_z/u*z+u;
		point.x=(int)(tempx*VPOINT_z/tempz);
		point.y=(int)(tempy*VPOINT_z/tempz);
		
	}
	
	//以下两行代码实现了透视
	else
	{
		point.x=(int)((-VPOINT_y/v)*x+VPOINT_x/v*y);
		point.y=(int)(-((VPOINT_x*VPOINT_z)/(u*v))*x-((VPOINT_y*VPOINT_z)/(u*v))*y+v/u*z);
		
	}
	
	return point;
}  



C3dPoint C3dPoint::operator =(C3dPoint &point)  //重载赋值运算符
{
	this->x=point.x;
	this->y=point.y;
	this->z=point.z;
	return *this;
	
}

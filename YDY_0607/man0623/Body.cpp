// Body.cpp: implementation of the CBody class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wilson6.h"
#include "Body.h"
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
IMPLEMENT_DYNAMIC(CBody, CObject)
CBody::CBody()
{
	AngleX=10;
	AngleY=10;
	AngleZ=0;
	ShiftX=0;
	ShiftY=0;
	ShiftZ=0;
}

void CBody::Draw(CDC *pDC)  //纯虚函数，实现多态
{
	
}

void CBody::Color(CDC *pDC)
{
	
}

CBody::~CBody()
{

}
//公共接口，设置体的角度，平移的距离等参数
void CBody::SetPara(double ax,double ay,double az, double mx, double my, double mz)
{
	AngleX+=ax;
	AngleY+=ay;
	AngleZ+=az;
	ShiftX+=mx;
	ShiftY+=my;
	ShiftZ+=mz;
}

void CBody::Move(double &x, double &y, double &z)  //将点进行平移变换，并传出去
{
	x+=ShiftX;
	y+=ShiftY;
	z+=ShiftZ;
	
}

//将点进行旋转变换，并把结果传出,注意不要引用的值时刻在变，所以
//又设了xx,yy,zz
void CBody::Rotate(double &x, double &y, double &z)  
{
	double xx=x,yy=y,zz=z;
	if((int)AngleX!=0)
	{	xx=x;
	yy=y*cos(AngleX/180.0*PI)-z*sin(AngleX/180.0*PI);
	zz=y*sin(AngleX/180.0*PI)+z*cos(AngleX/180.0*PI);
	}
	
	x=xx;
	y=yy;
	z=zz;
	
	if((int)AngleY!=0)
	{
		xx=x*cos(AngleY/180.0*PI)+z*sin(AngleY/180.0*PI);
		yy=y;
		zz=-x*sin(AngleY/180.0*PI)+z*cos(AngleY/180.0*PI);
	}
	
	x=xx;
	y=yy;
	z=zz;
	
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


void CBody::GetPara(double &ax, double &ay, double &az, double &mx, double &my, double &mz)
{
	ax=AngleX;
	ay=AngleY;
	az=AngleZ;
	mx=ShiftX;
	my=ShiftY;
	mz=ShiftZ;
	
}

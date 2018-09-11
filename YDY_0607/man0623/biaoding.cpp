// biaoding.cpp: implementation of the Cbiaoding class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "biaoding.h"
#include "stdlib.h"
#define PI 3.1415926

        
                                                 // 当前腿长和


#ifdef _DEBUG                              
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cbiaoding::Cbiaoding()
{
	flag0 = -1;                                           
	flag1 = -1;
	TempAngle =0;
	deltaL=20;


}

Cbiaoding::~Cbiaoding()
{

}

/*

  函数功能：工件位置调整计算
  入口参数：工件的位置gCenterLow（x,y,z），电机的相对运动量LegMov[4]
  返回值：0 表示函数完成正常
          1 表示工件的位置不合法
  应用实例：
           rtn=UAdjustPositin(gCenterLow[], LegMov[]);

*/
int Cbiaoding::UAdjustPositin(double gCenterLow[], double LegMov[])
{


		// 棒子位置合法性判断
	    int rtn;
		while ((fabs(gCenterLow[0]) > 2.50)||(fabs(gCenterLow[1]) > 2.50))
		{
			::AfxMessageBox("棒子位置不合法！");
			return 1;
	
		}

		rtn = AdjustPosition(gCenterLow, LegMov);     // 求取电机的[相对]控制量Leglong
		return 0;


}

int Cbiaoding::AdjustPosition(double gCenterLow[], double LegMov[])
{

	int rtn;
	double lRodPos0[3];                        // local 坐标系下的位置 + 姿态
	double lPlatPos[3], lPlatRot[3];           // 平台的期望终点位姿
	double InitialLeglong[4], Leglong[4];      // 四个驱动关节的初始值
	
	lRodPos0[2] = gCenterLow[2];
	
	PosZero[0] = x0;
	PosZero[1] = y0;
	PosZero[2] = H0;             // 平台归零后的理论位姿   // 2010-5-14
	OriZero[0] = 0.0;
	OriZero[1] = 0.0;
	OriZero[2] = 0.0;
	
    // 计算出低圆圆心的局部坐标
	rtn = TransForm(gCenterLow, lRodPos0);
	
    // 计算运动平台目标点的局部坐标
	lPlatPos[0] = -1.0 * lRodPos0[0] + PosZero[0];
	lPlatPos[1] = -1.0 * lRodPos0[1] + PosZero[1];
	lPlatPos[2] = H0;                                // 胡克铰的Z高度不能变！★
	lPlatRot[0] = 0;
	lPlatRot[1] = 0;
	
	// 运动学逆解
	rtn = InvKin(PosZero,OriZero, InitialLeglong);
	
	rtn = InvKin(lPlatPos, lPlatRot, Leglong);
	
	for (int i = 0; i < 4; i++)
	{
		LegMov[i] = Leglong[i] - InitialLeglong[i];
	}
	
	flag1 = 1;                         //  已离开零位
	
	return 0;
}

int Cbiaoding::InvKin(double WeiZhi[], double ZiTai[], double Leglong[])
{

	double rotx[3][3], roty[3][3], ABR[3][3];
	double A,B,C,cossita;                                 // Normal vector
	
	if (fabs(WeiZhi[2] - H0) > 0.0001)
	{
		return 0;
	} 
	else
	{
		/////////////////////////////////////////////////////: Z - Y - X 
		rotx[0][0] = 1.0;                            ///  rotx
		rotx[0][1] = 0.0;
		rotx[0][2] = 0.0;
		rotx[1][0] = 0.0;
		rotx[1][1] = cos(ZiTai[0] * pi/180.0);
		rotx[1][2] = - sin(ZiTai[0] * pi/180.0);
		rotx[2][0] = 0.0;
		rotx[2][1] = sin(ZiTai[0] * pi/180.0);
		rotx[2][2] = cos(ZiTai[0] * pi/180.0);
		roty[0][0] = cos(ZiTai[1] * pi/180.0);    /// roty
		roty[0][1] = 0.0;
		roty[0][2] = sin(ZiTai[1] * pi/180.0);
		roty[1][0] = 0.0;
		roty[1][1] = 1.0;
		roty[1][2] = 0.0;
		roty[2][0] = - sin(ZiTai[1] * pi/180.0);
		roty[2][1] = 0.0;
		roty[2][2] = cos(ZiTai[1] * pi/180.0);
		// rotx * roty
		ABR[0][0] = rotx[0][0] * roty[0][0] + rotx[0][1] * roty[1][0] + rotx[0][2] * roty[2][0];
		ABR[0][1] = rotx[0][0] * roty[0][1] + rotx[0][1] * roty[1][1] + rotx[0][2] * roty[2][1];
		ABR[0][2] = rotx[0][0] * roty[0][2] + rotx[0][1] * roty[1][2] + rotx[0][2] * roty[2][2];
		ABR[1][0] = rotx[1][0] * roty[0][0] + rotx[1][1] * roty[1][0] + rotx[1][2] * roty[2][0];
		ABR[1][1] = rotx[1][0] * roty[0][1] + rotx[1][1] * roty[1][1] + rotx[1][2] * roty[2][1];
		ABR[1][2] = rotx[1][0] * roty[0][2] + rotx[1][1] * roty[1][2] + rotx[1][2] * roty[2][2];
		ABR[2][0] = rotx[2][0] * roty[0][0] + rotx[2][1] * roty[1][0] + rotx[2][2] * roty[2][0];
		ABR[2][1] = rotx[2][0] * roty[0][1] + rotx[2][1] * roty[1][1] + rotx[2][2] * roty[2][1];
		ABR[2][2] = rotx[2][0] * roty[0][2] + rotx[2][1] * roty[1][2] + rotx[2][2] * roty[2][2];
		
		// Plane eq.: M0(x0, y0, z0), n = {A, B, C}; A(x-x0) + B(y-y0) + C(z-z0)=0
		A = ABR[0][2];
		B = ABR[1][2];
		C = ABR[2][2];
		
		Leglong[2] = WeiZhi[2] - ( A * (B2x - WeiZhi[0]) + B * (B2y - WeiZhi[1]))/C;
		Leglong[3] = WeiZhi[2] - ( A * (B3x - WeiZhi[0]) + B * (B3y - WeiZhi[1]))/C;
		cossita = ABR[2][2];
		
		Leglong[0] = WeiZhi[0] ;
		Leglong[1] = WeiZhi[1] ;
		
		return 0;
	}
}

int Cbiaoding::TransForm(double gXYZ[], double lXYZ[])
{

	double ABR[3][3];

	ABR[0][0] = cos(Angle * pi/180.0);    // rotz
	ABR[0][1] = -sin(Angle * pi/180.0);
	ABR[0][2] = 0.0;
	ABR[1][0] = sin(Angle * pi/180.0);
	ABR[1][1] = cos(Angle * pi/180.0);
	ABR[1][2] = 0.0;
	ABR[2][0] = 0.0;
	ABR[2][1] = 0.0;
	ABR[2][2] = 1.0;

	lXYZ[0] = ABR[0][0] * gXYZ[0] + ABR[0][1] * gXYZ[1] + ABR[0][2] * gXYZ[2];
	lXYZ[1] = ABR[1][0] * gXYZ[0] + ABR[1][1] * gXYZ[1] + ABR[1][2] * gXYZ[2];
	lXYZ[2] = ABR[2][0] * gXYZ[0] + ABR[2][1] * gXYZ[1] + ABR[2][2] * gXYZ[2];
	
	return 0;
	
}

int Cbiaoding::FindZitai(double CenterLow[], double CenterHigh[], double Zitai[])
{

	double zdir[3], zdir_u[3];
	double phi,sita,psi,t;                                // 姿态角
	int i;
	for (i = 0; i < 3; i ++)                          // 求取平台法向量
	{
		zdir[i] = CenterHigh[i] - CenterLow[i];
	}
	
	t = vect_norm(zdir, 3);                               // 求取平台法向量的模值
	
	for ( i = 0; i < 3; i ++)                             // 求取平台[单位]法向量
	{
		zdir_u[i] = zdir[i] / t;
	}
	
	if (fabs(zdir_u[1] ) < 0.0001)
	{ 
		phi = 0;
		sita = acos(zdir_u[2]);
		psi = 0;
	} 
	else
	{
		phi = asin(-1 * zdir_u[1]);
		sita = atan2(zdir_u[0]/cos(phi), zdir_u[2]/cos(phi));
		psi = 0;
	}
	
	Zitai[0] = phi * 180.0 / 3.141593;
	Zitai[1] = sita * 180.0 / 3.141593;
	Zitai[2] = psi;
	
	return 0;
}

int Cbiaoding::MotionComput(double gCenterLow[], double gCenterHigh[], double LegMov[])
{

	int rtn;
	double gRodRot0[3], gOriVect[3];          // global 坐标系下姿态
	double lRodPos0[3], lRodRot0[3];          // local  坐标系下的位置 + 姿态
	double lPlatPos[3], lPlatRot[3];          // 平台的期望终点位姿
	double InitialLeglong[4], Leglong[4];     // 四个驱动关节的初始值
	
	lRodPos0[2] = gCenterLow[2];

		
	PosZero[0] = x0;
	PosZero[1] = y0;
	PosZero[2] = H0;             // 平台归零后的理论位姿   // 2010-5-14
	OriZero[0] = 0;
	OriZero[1] = 0;
	OriZero[2] = 0;
	
    // 计算出低圆圆心的局部坐标
	rtn = TransForm(gCenterLow, lRodPos0);
	
	rtn = FindOriVect(gCenterLow, gCenterHigh, gOriVect);       //  求取棒子的姿态
	rtn = FindOriAngle(gOriVect,gRodRot0);
	
    // 计算出棒子姿态的局部坐标
	rtn = TransForm(gRodRot0, lRodRot0);
	
    // 计算运动平台目标点的局部坐标
	lPlatPos[0] = -1.0 * lRodPos0[0] + PosZero[0];
	lPlatPos[1] = -1.0 * lRodPos0[1] + PosZero[1];
	lPlatPos[2] = H0;                                      // 胡克铰的Z高度不能变！★
	lPlatRot[0] = -1.0 * lRodRot0[0];
	lPlatRot[1] = -1.0 * lRodRot0[1];

	// 运动学逆解
	rtn = InvKin(PosZero,OriZero, InitialLeglong);
	
	rtn = InvKin(lPlatPos, lPlatRot, Leglong);

	for (int i = 0; i < 4; i++)
	{
		LegMov[i] = Leglong[i] - InitialLeglong[i];
	}
	
	flag1 = 1;                         //  已离开零位
	
	return 0;
}

int Cbiaoding::AdjustOritation(double gCenterLow[], double gCenterHigh[], double LegMov[])
{

	int rtn;
	double gOriVect[3];                       // global 坐标系下姿态
	double lOriVect[3], lOriAngle[3];
	double lRodPos0[3];                       // local 坐标系下的位置 + 姿态
	double lPlatPos[3], lPlatRot[3];          // 平台的期望终点位姿
	double InitialLeglong[4], Leglong[4];     // 四个驱动关节的初始值
	
	lRodPos0[2] = gCenterLow[2];
		
	PosZero[0] = x0;
	PosZero[1] = y0;
	PosZero[2] = H0;             // 平台归零后的理论位姿   // 2010-5-14
	OriZero[0] = 0;
	OriZero[1] = 0;
	OriZero[2] = 0;
	
    // 计算出低圆圆心的局部坐标
	rtn = TransForm(gCenterLow, lRodPos0);

	rtn = FindOriVect(gCenterLow, gCenterHigh, gOriVect);    //  求取棒子的方位向量
	// 计算出棒子姿态的局部坐标
	rtn = TransForm(gOriVect, lOriVect);
	rtn = FindOriAngle(lOriVect,lOriAngle);
	
    // 计算运动平台目标点的局部坐标
	lPlatPos[0] = PosZero[0];
	lPlatPos[1] = PosZero[1];
	lPlatPos[2] = H0;                                       // 胡克铰的Z高度不能变！★
	lPlatRot[0] = -1.0 * lOriAngle[0];
	lPlatRot[1] = -1.0 * lOriAngle[1];
	
	// 运动学逆解
	rtn = InvKin(PosZero, OriZero, InitialLeglong);
	
	rtn = InvKin(lPlatPos, lPlatRot, Leglong);
	
	for (int i = 0; i < 4; i++)
	{
		LegMov[i] = Leglong[i] - InitialLeglong[i];
	}
	
	flag1 = 1;                         //  已离开零位
	
	return 0;
	
}
/*
    函数功能：工件姿态调节计算
	入口参数：
				gCenterLow:工件下部的位置（x,y，z）
				gCenterHigh:工件上部的位置（x,y,z）
				LegMov     :电机的相对运动量
	返回值  ：0   函数运行正常
			  1   工件的位置不合法
			  2   工件的姿态不合法
			  
 */
int Cbiaoding::UAdjustOritation(double gCenterLow[], double gCenterHigh[], double LegMov[])
{
		
		int rtn;
	// 棒子位置合法性判断
		if((fabs(gCenterLow[0]) > 2.50)||(fabs(gCenterLow[1]) > 2.50))
		{
			::AfxMessageBox("工件位置不合法");
			return 1;
		}
		
		rtn = FindZitai(gCenterLow, gCenterHigh, gRodRot0);       //  求取棒子的姿态
		
		// 棒子姿态合法性判断
		if ((fabs(gRodRot0[0]) > 2.50)||(fabs(gRodRot0[1]) > 2.50) )
		{
			::AfxMessageBox("工件的姿态不合法");
			return 2;
		}
		
		rtn = AdjustOritation(gCenterLow, gCenterHigh, LegMov);      // 这个函数求取电机的[相对]控制量Leglong
		// 屏幕输出调整量
		return 0;
}

/*
    函数功能：工件姿态和位置调节计算
	入口参数：
				gCenterLow:工件下部的位置（x,y，z）
				gCenterHigh:工件上部的位置（x,y,z）
				LegMov     :电机的相对运动量
	返回值  ：0   函数运行正常
			  1   工件的位置不合法
			  2   工件的姿态不合法
  */
int Cbiaoding::UMotionComput(double gCenterLow[], double gCenterHigh[], double LegMov[])
{
	    
	    int rtn;
	
	    if ((fabs(gCenterLow[0]) > 2.50)||(fabs(gCenterLow[1]) > 2.50))
		{
			::AfxMessageBox("工件位置不合法");
			return 1;
		}
		
		rtn = FindZitai(gCenterLow, gCenterHigh, gRodRot0);       //  求取棒子的姿态
		
		// 棒子姿态合法性判断
		if ((fabs(gRodRot0[0]) > 2.50)||(fabs(gRodRot0[1]) > 2.50) )/////////////封学真
		{
			::AfxMessageBox("工件姿态不合法");
			return 2;
		}
		
//		rtn = MotionComput(gCenterLow, gCenterHigh, LegMov);      // 这个函数求取电机的[相对]控制量Leglong
		rtn = AdjustBoth(gCenterLow, gCenterHigh, deltaL, LegMov);    // 这个函数求取电机的[相对]控制量Leglong
		
		return 0;
}

double Cbiaoding::vect_norm(double vect[], int n)
{

	double rst = 0;
	double result;                                                //  result
	int i;

	for (i = 0; i < n; i++)
	
	    rst = rst + vect[i] * vect[i];
	
    result = sqrt(rst);

	return (result);
}

int Cbiaoding::FindOriAngle(double zdir_u[], double OriAngle[])
{
	double phi,sita,psi;

	if (fabs(zdir_u[1] ) < 0.00000001)
	{ 
		phi = 0;
		sita = acos(zdir_u[2]);
		psi = 0;
	} 
	else
	{
		phi = asin(-1 * zdir_u[1]);
		sita = atan2(zdir_u[0]/cos(phi), zdir_u[2]/cos(phi));
		psi = 0;
	}
	
	OriAngle[0] = phi * 180.0 / 3.1415926;
	OriAngle[1] = sita * 180.0 / 3.1415926;
	OriAngle[2] = psi;
	
	return 0;
}

int Cbiaoding::FindOriVect(double CenterLow[], double CenterHigh[], double OriVect[])
{
	double zdir[3];                            // 姿态向量
	double t;                                
	int i;
	for (i = 0; i < 3; i ++)                          // 求取平台法向量
	{
		zdir[i] = CenterHigh[i] - CenterLow[i];
	}
	
	t = vect_norm(zdir, 3);                               // 求取平台法向量的模值
	
	for ( i = 0; i < 3; i ++)                             // 求取平台[单位]法向量
	{
		OriVect[i] = zdir[i] / t;
	}

	if (OriVect[2] < 0) 
	{
		OriVect[0] = -1 * OriVect[0];
		OriVect[1] = -1 * OriVect[1];
		OriVect[2] = -1 * OriVect[2];
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////
// 调整工作台姿态的运动量计算函数
// 产生各关节驱动量的数据
// Input: data[3600] 宝石测量点， radius：水平光栅给出的测量圆半径
// Output Unit: 四个驱动关节的运动量.
// 2010-5-27
//////////////////////////////////////////////////////////////////////////
int Cbiaoding::AdjustPlatOritation(double data[], double radius,double LegMov[])
{
	int rtn;
	double lOriAngle[3], zdir_u[3];           // 局部坐标系下姿态角
	double lRodRot0[3];                       // local 坐标系下的位置 + 姿态
	double lPlatPos[3], lPlatRot[3];          // 平台的期望终点位姿
	double InitialLeglong[4], Leglong[4];     // 四个驱动关节的初始值
		
	PosZero[0] = x0;
	PosZero[1] = y0;
	PosZero[2] = H0;             // 平台归零后的理论位姿   // 2010-5-14
	OriZero[0] = 0;
	OriZero[1] = 0;
	OriZero[2] = 0;
	
	// 计算出平晶的方位向量
	rtn = PingjingOriVectII(data, radius, zdir_u);

	// 计算出平晶在工作台局部坐标下的向量
	rtn = TransForm(zdir_u, lRodRot0);
	
	// ★ 求出平晶的姿态角
	rtn = FindOriAngle(lRodRot0, lOriAngle);  
	
   	// 计算运动平台目标点的局部坐标
	lPlatPos[0] = PosZero[0];
	lPlatPos[1] = PosZero[1];
	lPlatPos[2] = H0;                          // 胡克铰的Z高度不能变！★
	lPlatRot[0] = -1.0 * lOriAngle[0];
	lPlatRot[1] = -1.0 * lOriAngle[1];
	
	// 运动学逆解
	rtn = InvKin(PosZero, OriZero, InitialLeglong);
	
	rtn = InvKin(lPlatPos, lPlatRot, Leglong);
	
	for (int i = 0; i < 4; i++)
	{
		LegMov[i] = Leglong[i] - InitialLeglong[i];
	}
	
	flag1 = 1;                                  //  已离开零位
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// 利用三点求平晶姿态.【推荐】
// Input: 宝石测量值：data[3600], 宝石和平晶接触圆的半径radius  Unit: mm
// Output: zdir_u[3] Unit: degree.
// Return: Number of good data.
// 2010-6-2, 2010-6-6, 2010-7-16
//////////////////////////////////////////////////////////////////////////
int Cbiaoding::PingjingOriVect(double data[], double radius, double zdir_u[])
{
	int rtn, Num, index1, index2, index3, max_index, i, j = 0;
	double zdir1[3], zdir2[3],zdir3[3],zdir4[3], zdir[3], vect1[3], vect2[3];
	double p1[3], p2[3], p3[3], max_value[2];             // 两个向量
	double norm_v;                                        // 姿态角
	double good_data[3600], angle[3600];
	
	for ( i = 0; i < 3600; i ++)              //  初始化向量
	{
		good_data[i] = 0;
		angle[i] = 0;
	}
	
	for ( i = 0; i < 3600; i ++)
	{
		if ((data[i] < LIMIT * 0.001) && (data[i] > -LIMIT * 0.001))
		{
			good_data[j] = data[i];
			angle[j] =  (3599 - i) * pi /1800.0;  // i or (3599 - i) 注意顺时针和逆时针
			j ++;
		}
	}
	Num = j - 1;            // 好点的个数；

	//  第一个法向矢量
	index1 = 2;
	index2 = Num/2;
	index3 = Num - 2;
	
	p1[0] = radius * cos(angle[index1]);
	p1[1] = radius * sin(angle[index1]);
	p1[2] = good_data[index1];
	
	p2[0] = radius * cos(angle[index2]);
	p2[1] = radius * sin(angle[index2]);
	p2[2] = good_data[index2];
	
	p3[0] = radius * cos(angle[index3]);
	p3[1] = radius * sin(angle[index3]);
	p3[2] = good_data[index3];
	
	rtn = vect_minus(p1, p2, 3, vect1);
	rtn = vect_minus(p3, p2, 3, vect2);
	rtn = vect_cross(vect1, vect2, zdir1);
	
	//  第二个法向矢量
	index1 = 9;
	index2 = Num/2 + 9;
	index3 = Num - 7;
	
	p1[0] = radius * cos(angle[index1]);
	p1[1] = radius * sin(angle[index1]);
	p1[2] = good_data[index1];
	
	p2[0] = radius * cos(angle[index2]);
	p2[1] = radius * sin(angle[index2]);
	p2[2] = good_data[index2];
	
	p3[0] = radius * cos(angle[index3]);
	p3[1] = radius * sin(angle[index3]);
	p3[2] = good_data[index3];
	
	rtn = vect_minus(p1, p2, 3, vect1);
	rtn = vect_minus(p3, p2, 3, vect2);
	rtn = vect_cross(vect1, vect2, zdir2);

	//  第三个法向矢量
	index1 = 15;
	index2 = Num/2 + 14;
	index3 = Num - 16;
	
	p1[0] = radius * cos(angle[index1]);
	p1[1] = radius * sin(angle[index1]);
	p1[2] = good_data[index1];
	
	p2[0] = radius * cos(angle[index2]);
	p2[1] = radius * sin(angle[index2]);
	p2[2] = good_data[index2];
	
	p3[0] = radius * cos(angle[index3]);
	p3[1] = radius * sin(angle[index3]);
	p3[2] = good_data[index3];
	
	rtn = vect_minus(p1, p2, 3, vect1);
	rtn = vect_minus(p3, p2, 3, vect2);
	rtn = vect_cross(vect1, vect2, zdir3);

	//  第四个法向矢量
	index1 = Num/6;
	index2 = Num/4;
	index3 = Num/2;
	
	p1[0] = radius * cos(angle[index1]);
	p1[1] = radius * sin(angle[index1]);
	p1[2] = good_data[index1];
	
	p2[0] = radius * cos(angle[index2]);
	p2[1] = radius * sin(angle[index2]);
	p2[2] = good_data[index2];
	
	p3[0] = radius * cos(angle[index3]);
	p3[1] = radius * sin(angle[index3]);
	p3[2] = good_data[index3];
	
	rtn = vect_minus(p1, p2, 3, vect1);
	rtn = vect_minus(p3, p2, 3, vect2);
	rtn = vect_cross(vect1, vect2, zdir4);

    // 最终法向量
	norm_v=vect_norm(zdir1,3);
	zdir1[0] = zdir1[0]/norm_v;
	zdir1[1] = zdir1[1]/norm_v;
	zdir1[2] = zdir1[2]/norm_v;
	
	norm_v=vect_norm(zdir2,3);
	zdir2[0] = zdir2[0]/norm_v;
	zdir2[1] = zdir2[1]/norm_v;
	zdir2[2] = zdir2[2]/norm_v;

	norm_v=vect_norm(zdir3,3);
	zdir3[0] = zdir3[0]/norm_v;
	zdir3[1] = zdir3[1]/norm_v;
	zdir3[2] = zdir3[2]/norm_v;

	norm_v=vect_norm(zdir4,3);
	zdir4[0] = zdir4[0]/norm_v;
	zdir4[1] = zdir4[1]/norm_v;
	zdir4[2] = zdir4[2]/norm_v;

	zdir[0] = (zdir1[0] +  zdir2[0] + zdir3[0] + zdir4[0])/4.0;
	zdir[1] = (zdir1[1] +  zdir2[1] + zdir3[1] + zdir4[1])/4.0;
	zdir[2] = (zdir1[2] +  zdir2[2] + zdir3[2] + zdir4[2])/4.0;

	norm_v = vect_norm(zdir, 3);
	zdir_u[0] = zdir[0]/norm_v;
	zdir_u[1] = zdir[1]/norm_v;
	zdir_u[2] = zdir[2]/norm_v;
	
	if (zdir_u[2] < 0) 
	{
		zdir_u[0] = -1 * zdir_u[0];
		zdir_u[1] = -1 * zdir_u[1];
		zdir_u[2] = -1 * zdir_u[2];
	}

	return Num;

}

//////////////////////////////////////////////////////////////////////////
// 求平晶姿态.
// Input: 宝石测量值：data[3600], 宝石和平晶接触圆的半径radius  Unit: mm
// Output: Zitai[3](phi-sita-psi) Unit: degree.
// 2010-5-27
//////////////////////////////////////////////////////////////////////////
/*
int Cbiaoding::PingjingOriVect(double data[], double radius, double zdir_u[])
{
	int rtn, index1, index2, index3, max_index, i, j = 0;
	double zdir[3], vect1[3], vect2[3];
	double p1[3], p2[3], p3[3], max_value[2];             // 两个向量
	double norm_v;                                        // 姿态角
	double good_data[3600];
	int angle_index[3600];
	
	for ( i = 0; i < 3600; i ++)              //  初始化向量
	{
		good_data[i] = 0;
		angle_index[i] = 0;
	}
	
	max_index = Max(data, max_value);         // 判断数据合理性

	if (fabs(max_value[0]) > 149 * 0.001)
	{
		zdir_u[0] = 0.0;
		zdir_u[1] = 0.0;
		zdir_u[2] = 1.0;
	}
	else
	{       
		for ( i = 0; i < 3600; i ++)
		{
			if ((data[i] < 149 * 0.001) && (data[i] > -149 * 0.001))
			{
				good_data[j] = data[i];
				angle_index[j] = 3599 - i; 
				j ++;
			}
		}
		j --;
		
		index1 = angle_index[2];
		index2 = angle_index[j/2];
		index3 = angle_index[j - 2];
		
		// 	vect1[0] = radius * cos(index1 * pi /1800 ) * radius / sqrt(radius * radius + good_data[index1] * good_data[index1]);
		// 	vect1[1] = radius * sin(index1 * pi /1800 ) * radius / sqrt(radius * radius + good_data[index1] * good_data[index1]);
		// 	vect1[2] = data[index1];
		
		p1[0] = radius * cos(index1 * pi /1800 ) ;
		p1[1] = radius * sin(index1 * pi /1800 ) ;
		p1[2] = good_data[2];
		
		p2[0] = radius * cos(index2 * pi /1800 ) ;
		p2[1] = radius * sin(index2 * pi /1800 ) ;
		p2[2] = good_data[j/2];
		
		p3[0] = radius * cos(index3 * pi /1800 ) ;
		p3[1] = radius * sin(index3 * pi /1800 ) ;
		p3[2] = good_data[j-2];
		
		rtn = vect_minus(p1, p2, 3, vect1);
		rtn = vect_minus(p3, p2, 3, vect2);
		
		rtn = vect_cross(vect1, vect2, zdir);
		
		norm_v = vect_norm(zdir, 3);
		
		zdir_u[0] = zdir[0]/norm_v;
		zdir_u[1] = zdir[1]/norm_v;
		zdir_u[2] = zdir[2]/norm_v;
		
		if (zdir_u[2] < 0) 
		{
			zdir_u[0] = -1 * zdir_u[0];
			zdir_u[1] = -1 * zdir_u[1];
			zdir_u[2] = -1 * zdir_u[2];
		}
//	}

	return 0;
}

*/


int Cbiaoding::vect_minus(double a[], double b[], int n, double result[])
{
  	int i;
  	
  	for (i = 0; i < n; i++)
  	  		result[i] = a[i] - b[i];
  	
  	return 0;
  	
}

int Cbiaoding::vect_cross(double a[], double b[], double rst[])
{
	rst[0] = a[1] * b[2] - a[2] * b[1];
	rst[1] = a[2] * b[0] - a[0] * b[2];
	rst[2] = a[0] * b[1] - a[1] * b[0];
 
   return 0;
}

int Cbiaoding::Max(double x[], double max_value[])
{
	double tmp_max, tmp_min;
	int max_index;

	tmp_max = x[0];
	tmp_min = x[0];
	max_index = 0;

	for (int i = 0; i < 3600; i ++)
	{
		if (x[i] > tmp_max)
		{
			tmp_max = x[i];
			max_index = i;
		}
		if (x[i] < tmp_min)
		{
			tmp_min = x[i];
		}
		else
			;
	}

	max_value[0] = tmp_max;
	max_value[1] = tmp_min;

	return max_index;
}

void Cbiaoding::BuChang(double old_pxin, double new_pxin, double old_jdu, double new_jdu, double longmov[],double old_longmov[])
{
	double dx,dy;
    double dx2,dy2;
    double dx3,dy3;
    double k3=3,k4=3;
    double st3=0.5,st4=0.5;
    double r3=1.2,r4=1.2;
    dx=new_pxin*cos(3.1415926*new_jdu/180)-old_pxin*cos(3.145926*old_jdu/180);
    dy=new_pxin*sin(3.1415926*new_jdu/180)-old_pxin*sin(3.145926*old_jdu/180);
    dx2=cos(131*3.1415926/180)*dx-sin(131*3.1415926/180)*dy;
    dy2=sin(131*3.1415926/180)*dx+cos(131*3.1415926/180)*dy;
//    dx3=-cos(131*3.1415926/180)*new_pxin*cos(3.145926*new_jdu/180)
 //       +sin(131*3.1415926/180)*new_pxin*sin(3.145926*new_jdu/180);
 //   dy3=-sin(131*3.1415926/180)*new_pxin*cos(3.145926*new_jdu/180)
 //       -cos(131*3.1415926/180)*new_pxin*sin(3.145926*new_jdu/180);
    longmov[0]=(longmov[0])*k3*st3/(r3+st3*st3);
    longmov[1]=(longmov[1])*k4*st4/(r4+st4*st4);
}

int Cbiaoding::Celiang(double data[3600], double dataLIMIT, double RouTheta[2])
{//1
	int rtn;
	int L1;
	int sm;
	int numGoodData=0;
	int failureFlag1 = 0;
	int failureFlag2 = 0;
	int flag;
	const double precision = 0.0001;         // in mm;
	int i, j = 0;
	double x1 = 0, a = 0, b = 0;             // 初始化一些后面要用到的参数
	double b1 = 0, b2 = 0, b3 = 0;
	double y1 = 0, y2 = 0;
	double a1 = 0, a2 = 0;
	double a3 = 0, a4 = 0;
	double b4 = 0;
	double a11 = 0, a12 = 0, a13 = 0;  
	double a21 = 0, a22 = 0, a23 = 0;
	double a31 = 0, a32 = 0, a33 = 0; 
	double b11, b12, b13, b22;
	double A[3][3], Ainv[3][3];
	double B[3], C[3]; 
	double A1[2][2], Ainv1[2][2];
	double B1[2];
	double A2[2];
	double aa[3600];
	double angle[3600];
	double beta;
	double e1;
	double c1;
	double e2;
	double c2;
	double e3;
	double c3;
	double sn[3600];
	double cs[3600];
	double bb[3600];
	double r3[3600];
		
	L1 = 3600;

	for ( i = 0; i < L1; i ++)                          //  初始化数组
	{
		aa[i] = 0;
		angle[i] = 0;
		sn[i] = 0;
		cs[i] = 0;
		bb[i] = 0;
		r3[i] = 0;
	}

	/// 开始处理测量数据
	for ( i = 0; i < L1; i ++)                          //  给出对应角度值
	{
		aa[i] = data[i];
		angle[i] = i * 2 * PI/3599.0;
	}
	
	// 给出迭代初值
	for ( i = 0; i < L1; i ++)   
	{
		a = a + aa[i] * cos(angle[i]);
		b = b + aa[i] * sin(angle[i]);
	}

	a = 2 * a/double(L1);
	b = 2 * b/double(L1);
	e1 = sqrt(a * a + b * b);          // Rou
	c1 = atan2(b, a) * 180/PI;         // Theta

	// 筛选有效的测量值
	dataLIMIT = dataLIMIT - 0.001; 

	for ( i = 0; i < 3600; i ++)
	{
		if ((data[i] < dataLIMIT) && (data[i] > -1.0 * dataLIMIT))
		{
			aa[j] = data[i];
			angle[j] = i * 2 * PI/3599.0;   
			j ++;                                     
		}
	}
	                 
	numGoodData = j ;          //  表示有效数据的个数

	if (numGoodData < 200)
	{
	// 	AfxMessageBox("有效数据个数小于200,工件安装不合法,请重新安装!");  /// 换成弹出式对话框

		RouTheta[0] = 0;
		RouTheta[1] = 0;

		return -1;

	}
	else if (numGoodData > 3500)
	{
		RouTheta[0] = e1;
		RouTheta[1] = c1;
		
		return 0;
	}
    else
	{
		for (i = 0; i < numGoodData; i ++)
		{
			x1 = x1 + aa[i];
			a1 = a1 + aa[i] * cos(angle[i]);
			a2 = a2 + aa[i] * sin(angle[i]);
			a11 = a11 + 1;
			a12 = a12 - cos(angle[i]);
			a13 = a13 - sin(angle[i]);
			a22 = a22 + cos(angle[i]) * cos(angle[i]);
			a23 = a23 + cos(angle[i]) * sin(angle[i]);
			a33 = a33 + sin(angle[i]) * sin(angle[i]);
		}

		A[0][0] = a11;
		A[0][1] = a12;
		A[0][2] = a13;
		A[1][0] = a12;
		A[1][1] = a22;
		A[1][2] = a23;
		A[2][0] = a13;
		A[2][1] = a23;
		A[2][2] = a33;
		B[0] = x1;
		B[1] = a1;
		B[2] = a2;

		rtn = invmat3(A, Ainv);
		rtn = mat_vect_dot3(Ainv, B, C);
		beta = atan2(C[2], C[1]);
		e2 = sqrt(C[1] * C[1] + C[2] * C[2]);   // Rou
		c2 = beta * 180.0/PI;                   // Theta

		if ( (fabs(C[1]) > 3.0) || (fabs(C[2]) > 3.0) )
		{
			failureFlag1 = 1;
		}

		flag = 1;

		sm = 0;
		b1 = a;
		b2 = b;
		y1 = 0;
		y2 = 0;
		a3 = 0;
		b3 = 0;
		a4 = 0;
		b4 = 0;

		for (i = 1; i < numGoodData; i ++)
		{
			bb[i-1] = aa[i] - aa[0];
			cs[i-1] = cos(angle[i]) - cos(angle[0]);
			sn[i-1] = sin(angle[i]) - sin(angle[0]);
			r3[i-1] = 0;
		}

		b11 = 0; 
		b12 = 0; 
		b22 = 0;

		for(i = 0 ; i < numGoodData - 1; i ++)
		{
			b11 = b11 + cs[i] * cs[i];
			b12 = b12 + cs[i] * sn[i];
			b22 = b22 + sn[i] * sn[i];
		}

		A1[0][0] = b11;
		A1[0][1] = b12;
		A1[1][0] = b12;
		A1[1][1] = b22;

		while (1 == flag)
		{
			y1=0;//2011
			y2=0;  //2011
			for (i = 0; i < numGoodData - 1; i ++)
			{
				r3[i] = bb[i] - b1 * cs[i] - b2 * sn[i];
				y1 = y1 + r3[i] * cs[i];
				y2 = y2 + r3[i] * sn[i];
			}
			
			B1[0] = y1;
			B1[1] = y2;
			rtn = invmat2(A1, Ainv1);
			a3 = Ainv1[0][0] * B1[0] +  Ainv1[0][1] * B1[1];
			b3 = Ainv1[1][0] * B1[0] +  Ainv1[1][1] * B1[1];

			if ( (fabs(a3) < precision) && (fabs(b3) < precision) )
			{
				flag = 0;
			}
			else if ( (fabs(b1) > 3.0) || (fabs(b2) > 3.0) || (sm > 1000) )
			{
				flag = 0;
				failureFlag2 = 1; 
			}
			else
			{
				b1 = b1 + a3;
				b2 = b2 + b3;
				y1 = 0;
				y2 = 0;
			}

			sm ++;
		} // while cycle

		e3 = sqrt(b1 * b1 + b2 * b2);          // Rou
    	c3 = atan2(b2, b1) * 180/PI;

		if (failureFlag2 == 1)
		{
			if ( failureFlag1 == 1)
			{
				RouTheta[0] = e1;
				RouTheta[1] = c1;
			}
			else
			{
				RouTheta[0] = e2;
				RouTheta[1] = c2;
			}
		}
		else
		{
			RouTheta[0] = e3;
			RouTheta[1] = c3;
		}

		return 0;
	}
	
}//1

int Cbiaoding::CeliangII(double data[], double RouTheta[])
{
	int rtn, i, j = 0,num=0;
	double x1 = 0, a=0,b=0,a0=0, b1=0, b2 = 0;
	double a11 =0,a12=0,a13=0,a21 = 0, a22=0, a23=0, a31 = 0, a32=0,a33=0;  // 初始化一些后面要用到的参数
	double A[9], Apinv[9],u[9],v[9];
	double ApinvM[3][3];
	// 	double A[3][3], Apinv[3][3],u[3][3],v[3][3];
	double eps=0.000001, beta;
	int ka = 4;   // max(m,n) + 1
	double B[3],C[3]; 
	double aa[3600], angle[3600];
	
	for ( i = 0; i < 3600; i ++)                          //  初始化数组
	{
		aa[i] = 0;
		angle[i] = 0;
	}
	
	// 筛选有效的测量值
	for ( i = 0; i < 3600; i ++)
	{
		if ((data[i] < 0.001 * LIMIT) && (data[i] > -0.001 * LIMIT))
		{
			aa[j] = data[i];
			//			angle[j] = (3599 - i) * pi/1800;          //【注】如果主轴旋转方向定义不同，要修改3599 - i 为 i
			angle[j] =  i * pi/1800; 
			j ++;
		}
	}
	num=j;
	
	// 累加，计算各参数值
	for ( i = 0; i < j; i ++)
	{
		x1 = x1 + aa[i];
		a = a + aa[i]*cos(angle[i]);
		b = b + aa[i]*sin(angle[i]);
		a0 = a0 + 1;
		a11 = a11 + cos(angle[i]);
		a12 = a12 + sin(angle[i]); 
		a22 = a22 + cos(angle[i]) * cos(angle[i]);
		a23 = a23 + cos(angle[i]) * sin(angle[i]);
		a33 = a33 + sin(angle[i]) * sin(angle[i]);
		b1 = a;
        b2 = b;
	}
	///  方法一
	// 	a = 2 * a/j;
	// 	b = 2 * b/j;
	// 	RouTheta[0] = sqrt(a * a + b * b);          // Rou
	//  RouTheta[1] = atan(b, a) * 180/pi;           // Theta
	
	/// 方法二
	// 	A[0][0] = a11;
	// 	A[0][1] = a12;
	// 	A[0][2] = a13;
	// 	A[1][0] = a21;
	// 	A[1][1] = a22;
	// 	A[1][2] = a23;
	// 	A[2][0] = a31;
	// 	A[2][1] = a32;
	// 	A[2][2] = a33;
	A[0] = a11;
	A[1] = a12;
	A[2] = a13;
	A[3] = a21;
	A[4] = a22;
	A[5] = a23;
	A[6] = a31;
	A[7] = a32;
	A[8] = a33;
	
	B[0] = x1;
	B[1] = b1;
	B[2] = b2;
	rtn = bginv(A, 3, 3, Apinv, eps, u, v, ka);
	
    for (i=0; i<3; i ++)
		for (j=0; j<3; j ++)
		{
			ApinvM[i][j] = Apinv[ 3 * i + j];
		}
		
		rtn = mat_vect_dot3(ApinvM, B, C);
		beta = atan2(C[2], C[1]);
		RouTheta[0] = sqrt(C[1] * C[1] + C[2] * C[2]);          // Rou
		RouTheta[1] = beta * 180/pi;           // Theta
		
		return num;
		
}

void Cbiaoding::sss(double fg[], double cs[])
{
	double r,d;

    if ((fabs(fg[0]) + fabs(fg[1]))==0.0)
	{ 
		cs[0]=1.0; cs[1]=0.0; d=0.0;
	}
    else 
    { 
		d=sqrt(fg[0]*fg[0]+fg[1]*fg[1]);

        if (fabs(fg[0])>fabs(fg[1]))
        { 
			d=fabs(d);
            if (fg[0]<0.0) d=-d;
        }

        if (fabs(fg[1]) >= fabs(fg[0]))

          { d=fabs(d);
            if (fg[1]<0.0) d=-d;
          }
        cs[0]=fg[0]/d; cs[1]=fg[1]/d;
      }
    r=1.0;

    if (fabs(fg[0]) > fabs(fg[1])) r = cs[1];
    else
      if (cs[0]!=0.0) r=1.0/cs[0];

    fg[0] = d; fg[1] = r;

    return;
}

void Cbiaoding::ppp(double a[], double e[], double s[], double v[], int m, int n)
{
    int i,j,p,q;
    double d;
    if (m>=n) i=n;
    else i=m;
    for (j=1; j<=i-1; j++)
      { a[(j-1)*n+j-1]=s[j-1];
        a[(j-1)*n+j]=e[j-1];
      }
    a[(i-1)*n+i-1]=s[i-1];
    if (m<n) a[(i-1)*n+i]=e[i-1];
    for (i=1; i<=n-1; i++)
    for (j=i+1; j<=n; j++)
      { p=(i-1)*n+j-1; q=(j-1)*n+i-1;
        d=v[p]; v[p]=v[q]; v[q]=d;
      }
    return ;
}

int Cbiaoding::bmuav(double a[], int m, int n, double u[], double v[], double eps, int ka)
{
    int i,j,k,l,it,ll,kk,ix,iy,mm,nn,iz,m1,ks;
    double d,dd,t,sm,sm1,em1,sk,ek,b,c,shh,fg[2],cs[2];
    double *s,*e,*w;
   
    s = (double *) malloc(ka*sizeof(double));
    e = (double *) malloc(ka*sizeof(double));
    w = (double *) malloc(ka*sizeof(double));
    it=60; 
	k=n;
    if (m-1<n) k=m-1;
    l=m;
    if (n-2<m) l=n-2;
    if (l<0) l=0;
    ll=k;
    if (l>k) ll=l;
    if (ll>=1)
      { for (kk=1; kk<=ll; kk++)
          { if (kk<=k)
              { d=0.0;
                for (i=kk; i<=m; i++)
                  { ix=(i-1)*n+kk-1; d=d+a[ix]*a[ix];}
                s[kk-1]=sqrt(d);
                if (s[kk-1]!=0.0)
                  { ix=(kk-1)*n+kk-1;
                    if (a[ix]!=0.0)
                      { s[kk-1]=fabs(s[kk-1]);
                        if (a[ix]<0.0) s[kk-1]=-s[kk-1];
                      }
                    for (i=kk; i<=m; i++)
                      { iy=(i-1)*n+kk-1;
                        a[iy]=a[iy]/s[kk-1];
                      }
                    a[ix]=1.0+a[ix];
                  }
                s[kk-1]=-s[kk-1];
              }
            if (n>=kk+1)
              { for (j=kk+1; j<=n; j++)
                  { if ((kk<=k)&&(s[kk-1]!=0.0))
                      { d=0.0;
                        for (i=kk; i<=m; i++)
                          { ix=(i-1)*n+kk-1;
                            iy=(i-1)*n+j-1;
                            d=d+a[ix]*a[iy];
                          }
                        d=-d/a[(kk-1)*n+kk-1];
                        for (i=kk; i<=m; i++)
                          { ix=(i-1)*n+j-1;
                            iy=(i-1)*n+kk-1;
                            a[ix]=a[ix]+d*a[iy];
                          }
                      }
                    e[j-1]=a[(kk-1)*n+j-1];
                  }
              }
            if (kk<=k)
              { for (i=kk; i<=m; i++)
                  { ix=(i-1)*m+kk-1; iy=(i-1)*n+kk-1;
                    u[ix]=a[iy];
                  }
              }
            if (kk<=l)
              { d=0.0;
                for (i=kk+1; i<=n; i++)
                  d=d+e[i-1]*e[i-1];
                e[kk-1]=sqrt(d);
                if (e[kk-1]!=0.0)
                  { if (e[kk]!=0.0)
                      { e[kk-1]=fabs(e[kk-1]);
                        if (e[kk]<0.0) e[kk-1]=-e[kk-1];
                      }
                    for (i=kk+1; i<=n; i++)
                      e[i-1]=e[i-1]/e[kk-1];
                    e[kk]=1.0+e[kk];
                  }
                e[kk-1]=-e[kk-1];
                if ((kk+1<=m)&&(e[kk-1]!=0.0))
                  { for (i=kk+1; i<=m; i++) w[i-1]=0.0;
                    for (j=kk+1; j<=n; j++)
                      for (i=kk+1; i<=m; i++)
                        w[i-1]=w[i-1]+e[j-1]*a[(i-1)*n+j-1];
                    for (j=kk+1; j<=n; j++)
                      for (i=kk+1; i<=m; i++)
                        { ix=(i-1)*n+j-1;
                          a[ix]=a[ix]-w[i-1]*e[j-1]/e[kk];
                        }
                  }
                for (i=kk+1; i<=n; i++)
                  v[(i-1)*n+kk-1]=e[i-1];
              }
          }
      }
    mm=n;
    if (m+1<n) mm=m+1;
    if (k<n) s[k]=a[k*n+k];
    if (m<mm) s[mm-1]=0.0;
    if (l+1<mm) e[l]=a[l*n+mm-1];
    e[mm-1]=0.0;
    nn=m;
    if (m>n) nn=n;
    if (nn>=k+1)
      { for (j=k+1; j<=nn; j++)
          { for (i=1; i<=m; i++)
              u[(i-1)*m+j-1]=0.0;
            u[(j-1)*m+j-1]=1.0;
          }
      }
    if (k>=1)
      { for (ll=1; ll<=k; ll++)
          { kk=k-ll+1; iz=(kk-1)*m+kk-1;
            if (s[kk-1]!=0.0)
              { if (nn>=kk+1)
                  for (j=kk+1; j<=nn; j++)
                    { d=0.0;
                      for (i=kk; i<=m; i++)
                        { ix=(i-1)*m+kk-1;
                          iy=(i-1)*m+j-1;
                          d=d+u[ix]*u[iy]/u[iz];
                        }
                      d=-d;
                      for (i=kk; i<=m; i++)
                        { ix=(i-1)*m+j-1;
                          iy=(i-1)*m+kk-1;
                          u[ix]=u[ix]+d*u[iy];
                        }
                    }
                  for (i=kk; i<=m; i++)
                    { ix=(i-1)*m+kk-1; u[ix]=-u[ix];}
                  u[iz]=1.0+u[iz];
                  if (kk-1>=1)
                    for (i=1; i<=kk-1; i++)
                      u[(i-1)*m+kk-1]=0.0;
              }
            else
              { for (i=1; i<=m; i++)
                  u[(i-1)*m+kk-1]=0.0;
                u[(kk-1)*m+kk-1]=1.0;
              }
          }
      }
    for (ll=1; ll<=n; ll++)
      { kk=n-ll+1; iz=kk*n+kk-1;
        if ((kk<=l)&&(e[kk-1]!=0.0))
          { for (j=kk+1; j<=n; j++)
              { d=0.0;
                for (i=kk+1; i<=n; i++)
                  { ix=(i-1)*n+kk-1; iy=(i-1)*n+j-1;
                    d=d+v[ix]*v[iy]/v[iz];
                  }
                d=-d;
                for (i=kk+1; i<=n; i++)
                  { ix=(i-1)*n+j-1; iy=(i-1)*n+kk-1;
                    v[ix]=v[ix]+d*v[iy];
                  }
              }
          }
        for (i=1; i<=n; i++)
          v[(i-1)*n+kk-1]=0.0;
        v[iz-n]=1.0;
      }
    for (i=1; i<=m; i++)
    for (j=1; j<=n; j++)
      a[(i-1)*n+j-1]=0.0;
    m1=mm; it=60;
    while (1==1)
      { if (mm==0)
          { ppp(a,e,s,v,m,n);    // ppp(a,e,s,v,m,n);
            free(s); free(e); free(w); return(1);
          }
        if (it==0)
          { ppp(a,e,s,v,m,n);
            free(s); free(e); free(w); return(-1);
          }
        kk=mm-1;
	while ((kk!=0)&&(fabs(e[kk-1])!=0.0))
          { d=fabs(s[kk-1])+fabs(s[kk]);
            dd=fabs(e[kk-1]);
            if (dd>eps*d) kk=kk-1;
            else e[kk-1]=0.0;
          }
        if (kk==mm-1)
          { kk=kk+1;
            if (s[kk-1]<0.0)
              { s[kk-1]=-s[kk-1];
                for (i=1; i<=n; i++)
                  { ix=(i-1)*n+kk-1; v[ix]=-v[ix];}
              }
            while ((kk!=m1)&&(s[kk-1]<s[kk]))
              { d=s[kk-1]; s[kk-1]=s[kk]; s[kk]=d;
                if (kk<n)
                  for (i=1; i<=n; i++)
                    { ix=(i-1)*n+kk-1; iy=(i-1)*n+kk;
                      d=v[ix]; v[ix]=v[iy]; v[iy]=d;
                    }
                if (kk<m)
                  for (i=1; i<=m; i++)
                    { ix=(i-1)*m+kk-1; iy=(i-1)*m+kk;
                      d=u[ix]; u[ix]=u[iy]; u[iy]=d;
                    }
                kk=kk+1;
              }
            it=60;
            mm=mm-1;
          }
        else
          { ks=mm;
            while ((ks>kk)&&(fabs(s[ks-1])!=0.0))
              { d=0.0;
                if (ks!=mm) d=d+fabs(e[ks-1]);
                if (ks!=kk+1) d=d+fabs(e[ks-2]);
                dd=fabs(s[ks-1]);
                if (dd>eps*d) ks=ks-1;
                else s[ks-1]=0.0;
              }
            if (ks==kk)
              { kk=kk+1;
                d=fabs(s[mm-1]);
                t=fabs(s[mm-2]);
                if (t>d) d=t;
                t=fabs(e[mm-2]);
                if (t>d) d=t;
                t=fabs(s[kk-1]);
                if (t>d) d=t;
                t=fabs(e[kk-1]);
                if (t>d) d=t;
                sm=s[mm-1]/d; sm1=s[mm-2]/d;
                em1=e[mm-2]/d;
                sk=s[kk-1]/d; ek=e[kk-1]/d;
                b=((sm1+sm)*(sm1-sm)+em1*em1)/2.0;
                c=sm*em1; c=c*c; shh=0.0;
                if ((b!=0.0)||(c!=0.0))
                  { shh=sqrt(b*b+c);
                    if (b<0.0) shh=-shh;
                    shh=c/(b+shh);
                  }
                fg[0]=(sk+sm)*(sk-sm)-shh;
                fg[1]=sk*ek;
                for (i=kk; i<=mm-1; i++)
                  { sss(fg, cs);
                    if (i!=kk) e[i-2]=fg[0];
                    fg[0]=cs[0]*s[i-1]+cs[1]*e[i-1];
                    e[i-1]=cs[0]*e[i-1]-cs[1]*s[i-1];
                    fg[1]=cs[1]*s[i];
                    s[i]=cs[0]*s[i];
                    if ((cs[0]!=1.0)||(cs[1]!=0.0))
                      for (j=1; j<=n; j++)
                        { ix=(j-1)*n+i-1;
                          iy=(j-1)*n+i;
                          d=cs[0]*v[ix]+cs[1]*v[iy];
                          v[iy]=-cs[1]*v[ix]+cs[0]*v[iy];
                          v[ix]=d;
                        }
                    sss(fg,cs); 
                    s[i-1]=fg[0];
                    fg[0]=cs[0]*e[i-1]+cs[1]*s[i];
                    s[i]=-cs[1]*e[i-1]+cs[0]*s[i];
                    fg[1]=cs[1]*e[i];
                    e[i]=cs[0]*e[i];
                    if (i<m)
                      if ((cs[0]!=1.0)||(cs[1]!=0.0))
                        for (j=1; j<=m; j++)
                          { ix=(j-1)*m+i-1;
                            iy=(j-1)*m+i;
                            d=cs[0]*u[ix]+cs[1]*u[iy];
                            u[iy]=-cs[1]*u[ix]+cs[0]*u[iy];
                            u[ix]=d;
                          }
                  }
                e[mm-2]=fg[0];
                it=it-1;
              }
            else
              { if (ks==mm)
                  { kk=kk+1;
                    fg[1]=e[mm-2]; e[mm-2]=0.0;
                    for (ll=kk; ll<=mm-1; ll++)
                      { i=mm+kk-ll-1;
                        fg[0]=s[i-1];
                        sss(fg,cs);
                        s[i-1]=fg[0];
                        if (i!=kk)
                          { fg[1]=-cs[1]*e[i-2];
                            e[i-2]=cs[0]*e[i-2];
                          }
                        if ((cs[0]!=1.0)||(cs[1]!=0.0))
                          for (j=1; j<=n; j++)
                            { ix=(j-1)*n+i-1;
                              iy=(j-1)*n+mm-1;
                              d=cs[0]*v[ix]+cs[1]*v[iy];
                              v[iy]=-cs[1]*v[ix]+cs[0]*v[iy];
                              v[ix]=d;
                            }
                      }
                  }
                else
                  { kk=ks+1;
                    fg[1]=e[kk-2];
                    e[kk-2]=0.0;
                    for (i=kk; i<=mm; i++)
                      { fg[0]=s[i-1];
                        sss(fg,cs);
                        s[i-1]=fg[0];
                        fg[1]=-cs[1]*e[i-1];
                        e[i-1]=cs[0]*e[i-1];
                        if ((cs[0]!=1.0)||(cs[1]!=0.0))
                          for (j=1; j<=m; j++)
                            { ix=(j-1)*m+i-1;
                              iy=(j-1)*m+kk-2;
                              d=cs[0]*u[ix]+cs[1]*u[iy];
                              u[iy]=-cs[1]*u[ix]+cs[0]*u[iy];
                              u[ix]=d;
                            }
                      }
                  }
              }
          }
      }
    return(1);
}

int Cbiaoding::bginv(double a[], int m, int n, double aa[], double eps, double u[], double v[], int ka)
{
    int i,j,k,l,t,p,q,f;

	i = bmuav(a,m,n,u,v,eps,ka);

	if (i < 0)  return(-1);
	j = n;
	if (m < n) j=m;

	j = j-1;
	k = 0;

	while ((k <= j)&&(a[k * n + k] != 0.0)) k = k + 1;
	k = k-1;
	
	for (i = 0 ; i <= n - 1; i ++)
		for (j=0; j<=m-1; j++)
			{ t=i*m+j; aa[t]=0.0;
				for (l=0; l<=k; l++)
				{ f=l*n+i; p=j*m+l; q=l*n+l;
				  aa[t]=aa[t]+v[f]*u[p]/a[q];
				}
			}

	return(1);
}

int Cbiaoding::invmat3(double a[][3], double b[][3])
{
	int i,j,k,l,m,n;
	double zgm[3][6];
	double t;
	double ta,tb,tc,td;
	
	for (i=0; i <= 2; i ++)                                    //  general matrix left
		for (j=0; j <= 2; j ++)
			zgm[i][j] = a[i][j];
		
		for (i=0; i <= 2; i ++)                                    //  general matrix right half part
		{  for (j = 3; j <= 5; j++)
		if (i + 3 == j)
			zgm[i][j] = 1.0;
		else
			zgm[i][j] = 0.0;
		}
		
		// choose the main component in column
		i = 0;
		while (i < 2)
		{
			t = fabs(zgm[i][i]);
			n = i;                                                    // max value in row n
			if (t == 0)
				break;
			else
			{
				
				for (j=i+1; j <= 2; j ++)
				{
					if (fabs(zgm[j][i]) > t)                             // find the max column: n
					{
						t = fabs(zgm[j][i]);
						n = j;
					}
					
				}
				
				//  replace the rows
				for (k = 0; k <= 5; k ++)                                 // replace the rows
				{
					ta = zgm[n][k];
					zgm[n][k] = zgm[i][k];
					zgm[i][k] = ta;
				}
				
			}
			i ++;
		}
		
		// get the triangle matrix                                           1st step
		for (i = 0; i <= 1; i ++)
		{
			tb = zgm[i][i];
			for (l = i + 1; l <= 2; l++)
			{
				tc = zgm[l][i];
				for (m = i; m <= 5; m ++)
					zgm[l][m] = - (tc/tb)* zgm[i][m] + zgm[l][m];
				
			}
		}
		
		// solve the inverse matrix, get trial array
		for (i = 0; i <= 1; i ++)
		{
			for (j = i+1; j <= 2; j ++)
			{
				tb = zgm[i][j];
				tc = zgm[j][j];
				td = tb/tc;
				for (k = j; k <= 5; k ++)
					zgm[i][k] = - td * zgm[j][k] + zgm[i][k];                 //  2 step
				
			}
		}
		for (i = 0; i <= 2; i ++)
		{
			tb = zgm[i][i];
			for (j = i; j <= 5; j ++)
				zgm[i][j] = zgm[i][j]/tb;
		}
		
		// get the rusult
		for (i=0; i <= 2; i ++)                                                      //  result matrix
			for (j=0; j <= 2; j ++)                                                  //  b - result: the inverse matrix
			{
				a[i][j] = zgm[i][j];
				b[i][j] = zgm[i][j + 3];
			}
			
		return 0;
}

int Cbiaoding::mat_vect_dot3(double mat[][3], double vect[], double result[])
{	
	int i;
	
	for (i = 0; i < 3; i ++)
	   result[i] = mat[i][0] * vect[0] +  mat[i][1] * vect[1] +  mat[i][2] * vect[2];
	
	return 0;

}

//////////////////////////////////////////////////////////////////////////
// 运动计算函数，既调平又调心
// 产生各关节驱动量的数据
// Input: CenterLow[3](低圆圆心xyz), CenterHigh[3]（高圆圆心XYZ）Unit: mm
//  DeltaL                   // 下圆周离运动平台的高度
// Output: Unit: mm.
// 2010-7-13, 2010-7-16
//////////////////////////////////////////////////////////////////////////
int Cbiaoding::AdjustBoth(double gCenterLow[], double gCenterHigh[], double DeltaL, double LegMov[])
{
	int rtn;
	double gRodRot0[3], gOriVect[3];          // global 坐标系下姿态
	double gCenterBottom[3], lRodPos0[3], lRodRot0[3];  // local  坐标系下的位置 + 姿态
	double lPlatPos[3], lPlatRot[3];          // 平台的期望终点位姿
	double InitialLeglong[4], Leglong[4];     // 四个驱动关节的初始值
	
//	double DeltaL = 10;                        // 下圆周离运动平台的高度
		
	PosZero[0] = x0;
	PosZero[1] = y0;
	PosZero[2] = H0;             // 平台归零后的理论位姿   // 2010-5-14
	OriZero[0] = 0;
	OriZero[1] = 0;
	OriZero[2] = 0;

	rtn = FindOriVect(gCenterLow, gCenterHigh, gOriVect);       //  求取棒子的法向量 gOriVect
	rtn = FindOriAngle(gOriVect, gRodRot0);

	// 计算运动平台中心的全局位置坐标
    gCenterBottom[0] = gCenterLow[0] - DeltaL * gOriVect[0];
	gCenterBottom[1] = gCenterLow[1] - DeltaL * gOriVect[1];
	gCenterBottom[2] = gCenterLow[2] - DeltaL * gOriVect[2];

	// 计算出低圆圆心的局部坐标
	rtn = TransForm(gCenterBottom, lRodPos0);
	
    // 计算出棒子姿态的局部坐标
	rtn = TransForm(gRodRot0, lRodRot0);
	
    // 计算运动平台目标点的局部坐标
	lPlatPos[0] = -1.0 * (lRodPos0[0] - sign(lRodPos0[0]) * fabs(B1x) * (1 - cos(lRodPos0[1] * pi/180))) + PosZero[0];
	lPlatPos[1] = -1.0 * (lRodPos0[1] - sign(lRodPos0[1]) * fabs(B1y) * (1 - cos(lRodPos0[0] * pi/180))) + PosZero[1];
	lPlatPos[2] = H0;                                          // 胡克铰的Z高度不能变！★
	lPlatRot[0] = -1.0 * lRodRot0[0];
	lPlatRot[1] = -1.0 * lRodRot0[1];
	
	// 运动学逆解
	rtn = InvKin(PosZero,OriZero, InitialLeglong);
	
	rtn = InvKin(lPlatPos, lPlatRot, Leglong);
	
	for (int i = 0; i < 4; i++)
	{
		LegMov[i] = Leglong[i] - InitialLeglong[i];
	}
	
	flag1 = 1;                         //  已离开零位
	
	return 0;
}

double Cbiaoding::sign(double data)
{
	if (data > 0)
		return 1.0;
	else if (data < 0)
		return -1.0;
	else
	    return 0.0;
}
int Cbiaoding::invmat2(double a[2][2],double b[2][2])           // find the inverse matrix of a 2 by 2 matrix
{
	double det;
	double k;

	det = a[0][0] * a[1][1] - a[0][1] * a[1][0];

	if (fabs(det) > 0.0000001)
	{
		k = 1.0/det;
		
		b[0][0] = k * a[1][1];
		b[0][1] = -k * a[0][1];
		b[1][0] = -k * a[1][0];
		b[1][1] = k * a[0][0]; 

		return 0;
	}
	else
	{
		b[0][0] = 1;
		b[0][1] = 0;
		b[1][0] = 0;
		b[1][1] = 1; 

		return -1;
	}

}
//////////////////////////////////////////////////////////////////////////
// 利用最小二乘法LSM 求平晶姿态.【推荐】
// Input: 宝石测量值：data[3600], 宝石和平晶接触圆的半径radius  Unit: mm
// Output: zdir_u[3] Unit: degree.
// Return: Number of good data.
// 2012-5-15
//////////////////////////////////////////////////////////////////////////
int Cbiaoding::PingjingOriVectII(double data[], double radius, double zdir_u[])
{
		
	int rtn, Num, i, j = 0;
	double zdir[3];
	double norm_v;                                        // 姿态角
	double good_data[3600], sitarad[3600];
	double x[3600], y[3600], z[3600];
	
	for ( i = 0; i < 3600; i ++)                          //  初始化向量
	{
		good_data[i] = 0;
		sitarad[i] = 0;
	}
	
	for ( i = 0; i < 3600; i ++)
	{
		if ((data[i] < LIMIT * 0.001) && (data[i] > - 0.001 * LIMIT))
		{
			good_data[j] = data[i];
			sitarad[j] =  (3599 - i) * pi /1800.0;  // i or (3599 - i) 注意顺时针和逆时针
			j ++;
		}
	}

	Num = j - 1;

	double x1 = 0, a=0,b=0,a0=0, b1=0, b2 =0;
	double a11 =0,a12=0,a13=0, a21 = 0, a22=0, a23=0, a31 = 0, a32=0, a33=0;  // 初始化一些后面要用到的参数
	double ATA[9], Apinv[9],u[9],v[9];
	double ApinvM[3][3];
	double eps = 0.000001;
	int ka = 4;   // max(m,n) + 1
	double Rst[3], ATb[3]; 
	
	for (i = 0; i < 3; i ++)
	{
		ATb[i] = 0;
	}
	//  x,y,z
	for ( i = 0; i < Num; i ++)
	{
		x[i] = radius * cos(sitarad[i]); // x
		y[i] = radius * sin(sitarad[i]); // y
		z[i] = good_data[i]; // z
	}

	for ( i = 0; i < Num; i ++)
	{
		ATb[0] = ATb[0] - x[i] * z[i]; // x
		ATb[1] = ATb[1] - y[i] * z[i]; // y
		ATb[2] = ATb[2] - z[i];    // z
		
		a11 = a11 + x[i] * x[i];
		a12 = a12 + x[i] * y[i]; 
		a13 = a13 + x[i]; 
		a22 = a22 + y[i] * y[i];
		a23 = a23 + y[i];
		a33 = a33 + 1;
	}
	
	a21 = a12;
	a31 = a13;
	a32 = a23;
	
	ATA[0] = a11;
	ATA[1] = a12;
	ATA[2] = a13;
	ATA[3] = a21;
	ATA[4] = a22;
	ATA[5] = a23;
	ATA[6] = a31;
	ATA[7] = a32;
	ATA[8] = a33;
	
	rtn = bginv(ATA, 3, 3, Apinv, eps, u, v, ka);
	
    for (i = 0; i < 3; i ++)
	{
		for (j = 0; j < 3; j ++)
			ApinvM[i][j] = Apinv[ 3 * i + j];
	}
	
	rtn = mat_vect_dot3(ApinvM, ATb, Rst);
	
    // 最终法向量
	zdir[0] = Rst[0];
	zdir[1] = Rst[1];
	zdir[2] = 1;
	
	norm_v = vect_norm(zdir, 3);
	zdir_u[0] = zdir[0]/norm_v;
	zdir_u[1] = zdir[1]/norm_v;
	zdir_u[2] = zdir[2]/norm_v;
	
	if (zdir_u[2] < 0) 
	{
		zdir_u[0] = -1 * zdir_u[0];
		zdir_u[1] = -1 * zdir_u[1];
		zdir_u[2] = -1 * zdir_u[2];
	}

	return Num;
}

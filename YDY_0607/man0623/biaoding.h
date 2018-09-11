// biaoding.h: interface for the Cbiaoding class.
//
//////////////////////////////////////////////////////////////////////

#include"math.h"

const double pi = 3.1415926;
//const double PI = 3.1415926;

// The coordinates in local frame of the joints

// 2010-5-14
// #define B1x    56.5685//
// #define B1y   -56.5685                       
// #define B1z     0.0
// #define B2x    20.7055
// #define B2y    77.2741
// #define B2z     0.0
// #define B3x   -77.2741
// #define B3y   -20.7055
// #define B3z     0.0
// #define P1x     0.0 
// #define P1y     0.0 
// #define P1z     0.0 
// 
// #define x0     56.5685  
// #define y0    -56.5685   
// #define H0     80            // 平台初始高度

// const double Angle=84;    // 零光栅X轴与OXYZ坐标系X轴夹角，单位：度  测量角度+75 
// const double LIMIT=90;     // 测量极限值 单位：微米


#if !defined(AFX_BIAODING_H__7F5DC274_D613_45F3_A8DB_64AC4D883335__INCLUDED_)
#define AFX_BIAODING_H__7F5DC274_D613_45F3_A8DB_64AC4D883335__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Cbiaoding  
{
public:
	double LIMIT;
	double H0;
	double y0;
	double x0;
    double P1z;
	double P1y;
	double P1x;
	double B3z;
	double B3y;
	double B3x;
	double B2z;
	double B2y;
	double B2x;
	double B1z;
	double B1y;
	double B1x;
	double gRodRot0[3];                      // 工件棒子的姿态角                   
	double NowLeg[4];  
	double PosZero[3];
	double OriZero[3];
	int flag0 ;                                           
	int flag1 ;
	int TempAngle ;
	double deltaL;
	int PingjingOriVectII(double data[3600], double radius, double zdir_u[3]);
	double Angle;
	int invmat2(double a[2][2],double b[2][2]);           // find the inverse matrix of a 2 by 2 matrix
	double sign(double data);
	int AdjustBoth(double gCenterLow[3], double gCenterHigh[3], double DeltaL, double LegMov[4]);
	int mat_vect_dot3(double mat[3][3], double vect[3], double result[3]);
	int invmat3(double a[3][3],double b[3][3]);
	int bginv(double a[], int m, int n,double aa[],double eps, double u[],double v[],int ka);
	int bmuav(double a[], int m, int n, double u[], double v[], double eps, int ka);
	void ppp(double a[], double e[], double s[],double v[], int m, int n);
	void sss(double fg[2], double cs[2]);
	int CeliangII(double data[3600], double RouTheta[2]);
	int Celiang(double data[3600], double dataLIMIT, double RouTheta[2]);
	void BuChang(double old_pxin,double new_pxin,double old_jdu,double new_jdu,double longmov[],double old_longmov[]);
	int Max(double x[3600], double max_value[2]);
	int vect_cross(double a[3], double b[3], double rst[3]);
	int vect_minus(double a[], double b[], int n, double result[]);
	int PingjingOriVect(double data[3600], double radius, double zdir_u[3]);
	int AdjustPlatOritation(double data[3600], double radius,double LegMov[]);
	int FindOriVect(double CenterLow[3], double CenterHigh[3], double OriVect[3]);
	int FindOriAngle(double zdir_u[3], double OriAngle[3]);
	double vect_norm(double vect[],int n);
	int UMotionComput(double gCenterLow[3], double gCenterHigh[3], double LegMov[4]);
	int UAdjustOritation(double gCenterLow[3], double gCenterHigh[3], double LegMov[4]);
	int AdjustOritation(double gCenterLow[3], double gCenterHigh[3], double LegMov[4]);
	int MotionComput(double gCenterLow[3], double gCenterHigh[3], double LegMov[4]);
	int FindZitai(double CenterLow[3], double CenterHigh[3], double Zitai[3]);
	int TransForm(double gXYZ[3], double lXYZ[3]);
	int InvKin(double WeiZhi[3], double ZiTai[3], double Leglong[4]);
	int AdjustPosition(double gCenterLow[3], double LegMov[4]);
	int UAdjustPositin(double gCenterLow[3], double LegMov[4]);
	Cbiaoding();
	virtual ~Cbiaoding();

};

#endif // !defined(AFX_BIAODING_H__7F5DC274_D613_45F3_A8DB_64AC4D883335__INCLUDED_)

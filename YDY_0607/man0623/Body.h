// Body.h: interface for the CBody class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BODY_H__F7E6A94F_1137_402A_A378_239D6EF4EAB8__INCLUDED_)
#define AFX_BODY_H__F7E6A94F_1137_402A_A378_239D6EF4EAB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBody : public CObject  
{
	DECLARE_DYNAMIC(CBody)		
public:
	void GetPara(double &ax,double &ay,double &az,double &mx,double &my,double &mz);
	void SetPara(double ax,double ay,double az,double mx,double my,double mz);
	virtual void Draw(CDC *pDC)=0;
	virtual void Color(CDC *pDC)=0;
	CBody();
	virtual ~CBody();
	
protected:
	double AngleX;
	double AngleY;
	double AngleZ;
	double ShiftX;
	double ShiftY;
	double ShiftZ;
	void Rotate(double &x,double &y,double &z);
 	void Move(double &x,double &y,double &z);
};

#endif // !defined(AFX_BODY_H__F7E6A94F_1137_402A_A378_239D6EF4EAB8__INCLUDED_)

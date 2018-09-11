// ColorMap.cpp: implementation of the CColorMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ColorMap.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColorMap::CColorMap()
{
	m_colormapLength=64;

}
CColorMap::CColorMap(int colorLength)
{
	m_colormapLength=colorLength;
	for (int i=0;i<m_colormapLength;i++)
	{
		camp[i][0]=0;
		camp[i][1]=0;
		camp[i][2]=0;
	}
}

CColorMap::~CColorMap()
{

}

void CColorMap::Jet()
{
	float cMatrix[4096][3];
	int n=(int)ceil(m_colormapLength/4.0);
	int fArray_length=3*n-1;
	int nMod=0;
	float fArray[4096];
	int red[4096];
	int green[4096];
	int blue[4096];
	int i=0,j=0;
	for (i=0;i<4096;i++)
	{
		cMatrix[i][0]=0;
		cMatrix[i][1]=0;
		cMatrix[i][2]=0;
		red[i]=0;
		green[i]=0;
		blue[i]=0;
		fArray[i]=0.0;

	}

	if ((m_colormapLength%4)==1)
	{
		nMod=1;
	}
	for ( i=0;i<fArray_length;i++)
	{
		if (i<n)
		{
			fArray[i]=(float)(1.0*(i+1)/n);
		}
		else if ((i>=n)&&(i<2*n-1))
		{
			fArray[i]=1.0;
		}
		else if (i>=2*n-1)
		{
			fArray[i]=(float)(1.0*(3*n-1-i)/n);
		}
		green[i]=(int)(ceil(n/2.0)-nMod+i);
		red[i]=green[i]+n;
		blue[i]=green[i]-n;
	}
	int nb=0;
	for ( i=0;i<m_colormapLength;i++)
	{
		if (blue[i]>0)
		{
			nb++;
		}
	}
	for ( i=0;i<m_colormapLength;i++)
	{
		for (j=0;j<m_colormapLength;j++ )
		{
			if ((i==red[j])&&(red[j]<m_colormapLength))
			{
				cMatrix[i][0]=fArray[i-red[0]];
			}
			if ((i==green[j])&&(green[j]<m_colormapLength))
			{
				cMatrix[i][1]=fArray[i-(int)green[0]];
			}
			if ((i==blue[j])&&(blue[j]>=0))
			{
				cMatrix[i][2]=fArray[fArray_length-1-nb+i];
			}
		}

	}
	for (i=0;i<m_colormapLength;i++)
	{
		for (j=0;j<3;j++)
		{
			camp[i][j]=(int)(cMatrix[i][j]*255);
		}
	}

}

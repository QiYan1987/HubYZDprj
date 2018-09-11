// ColorMap.h: interface for the CColorMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLORMAP_H__59F24E46_2D98_494F_84E9_42F14EB1E84D__INCLUDED_)
#define AFX_COLORMAP_H__59F24E46_2D98_494F_84E9_42F14EB1E84D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CColorMap  
{
public:
	void Jet();
	int m_colormapLength;
	int camp[4096][3];
	CColorMap();
	CColorMap(int colorLength);
	virtual ~CColorMap();

};

#endif // !defined(AFX_COLORMAP_H__59F24E46_2D98_494F_84E9_42F14EB1E84D__INCLUDED_)

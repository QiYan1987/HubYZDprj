// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__58DC0960_FDAF_4C3B_AE32_987B3196BD5E__INCLUDED_)
#define AFX_STDAFX_H__58DC0960_FDAF_4C3B_AE32_987B3196BD5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "sizecbar.h" 
#include "scbarg.h"
#define RecCount 3600
#define JMNum  20
struct shuju//圆度，直线度，平行度
{
	int data;
	BOOL selected;
};

struct shuju0//圆柱度，平面度，垂直度，同轴度
{
	int data;
	float height;
	BOOL selected;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__58DC0960_FDAF_4C3B_AE32_987B3196BD5E__INCLUDED_)

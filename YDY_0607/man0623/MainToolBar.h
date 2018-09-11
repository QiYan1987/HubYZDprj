// MainToolBar.h: interface for the CMainToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINTOOLBAR_H__F4B8EE4F_4635_4217_BD1A_6E432B473A05__INCLUDED_)
#define AFX_MAINTOOLBAR_H__F4B8EE4F_4635_4217_BD1A_6E432B473A05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainToolBar : public CToolBar  
{
public:
	CMainToolBar();
	virtual ~CMainToolBar();
     CComboBox m_wndZoom; 
};

#endif // !defined(AFX_MAINTOOLBAR_H__F4B8EE4F_4635_4217_BD1A_6E432B473A05__INCLUDED_)

// ComboToolBar.h: interface for the CComboToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMBOTOOLBAR_H__4D7F65E6_E431_4137_8514_8312A97D4805__INCLUDED_)
#define AFX_COMBOTOOLBAR_H__4D7F65E6_E431_4137_8514_8312A97D4805__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CComboToolBar : public CToolBar  
{
public:
	CComboToolBar();
	virtual ~CComboToolBar();
     CComboBox m_combobox;
};

#endif // !defined(AFX_COMBOTOOLBAR_H__4D7F65E6_E431_4137_8514_8312A97D4805__INCLUDED_)

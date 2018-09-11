// ComboToolBar1.h: interface for the CComboToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMBOTOOLBAR1_H__EF60924C_CEC2_448A_B413_267632BDF338__INCLUDED_)
#define AFX_COMBOTOOLBAR1_H__EF60924C_CEC2_448A_B413_267632BDF338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CComboToolBar : public CToolBar  
{
public:
	CComboToolBar();
	virtual ~CComboToolBar();
     CComboBox   m_combobox;
};

#endif // !defined(AFX_COMBOTOOLBAR1_H__EF60924C_CEC2_448A_B413_267632BDF338__INCLUDED_)

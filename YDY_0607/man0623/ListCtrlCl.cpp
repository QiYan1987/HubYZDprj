// ListCtrlCl.cpp : implementation file
//

#include "stdafx.h"
#include "Wilson6.h"
#include "ListCtrlCl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlCl
struct stColor
{
	int nRow;
	int nCol;
	COLORREF rgb;
};
CListCtrlCl::CListCtrlCl()
: m_nRowHeight(0)
, m_fontHeight(12)
, m_fontWith(0)
{
	m_color = RGB(0,0,0);
}

CListCtrlCl::~CListCtrlCl()
{
}


BEGIN_MESSAGE_MAP(CListCtrlCl, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlCl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlCl message handlers

void CListCtrlCl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	TCHAR lpBuffer[256];

	LV_ITEM lvi;

	lvi.mask = LVIF_TEXT | LVIF_PARAM ;//结构成员屏蔽位

	lvi.iItem = lpDrawItemStruct->itemID ; //表项索引号

	lvi.iSubItem = 0;//子表项索引号

	lvi.pszText = lpBuffer ;//表项名文本

	lvi.cchTextMax = sizeof(lpBuffer);//表项名最大长度


	VERIFY(GetItem(&lvi));//是一个判断的宏,ASSERT与VERIFY宏在Debug模式下作用基本一致，
	                      //二者都对表达式的值进行计算，如果值为非0，则什么事也不做；如果值为0，则输出诊断信息。   
	LV_COLUMN lvc, lvcprev ;
	::ZeroMemory(&lvc, sizeof(lvc));//宏用0来填充一块内存区域,&lvc:指向一块准备用0来填充的内存区域的开始地址
                            	//sizeof(lvc):准备用0来填充的内存区域的大小，按字节来计算
	::ZeroMemory(&lvcprev, sizeof(lvcprev));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;
	lvcprev.mask = LVCF_WIDTH | LVCF_FMT;

	CDC* pDC;//这里 pDC 表示指向 CDC 类对象的指针
   	// DC 即，device context 设备上下文，简单说是系统维护的一堆数据，里面放着各种设置

	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);//FromHandle先查找由用户定义的内核对象对象的封装类,
	                                             // 如果找到直接返回,没有找到构造一个临时对象返回. 
	CRect rtClient;
	GetClientRect(&rtClient); //该函数获取窗口客户区的坐标
	for ( int nCol=0; GetColumn(nCol, &lvc); nCol++)// 先用setcolumn（）在listctrl中插入几行信息；然后用getcolumn()获取里面的信息。
	{
		if ( nCol > 0 ) 
		{
			// Get Previous Column Width in order to move the next display item
			GetColumn(nCol-1, &lvcprev) ;
			lpDrawItemStruct->rcItem.left += lvcprev.cx ;//长度、宽度的CX、CY
			lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left; 
		}

		CRect rcItem;   
		if (!GetSubItemRect(lpDrawItemStruct->itemID,nCol,LVIR_LABEL,rcItem)) //1子项的父项的索引值。
		                                                                 	//2以1为基数的子项的索引 
		                                                                    //3决定要获取的列表视图子项的绑定矩形的部分
																			//4包含子项绑定矩形坐标的CRect对象的参考
																	//LVIR_LABEL 返回整个项的绑定矩形，包括图标和标签。它与LVIR_BOUNDS相同 
			continue;   

		::ZeroMemory(&lvi, sizeof(lvi));
		lvi.iItem = lpDrawItemStruct->itemID; //表项索引号
		lvi.mask = LVIF_TEXT | LVIF_PARAM; //结构成员屏蔽位
		lvi.iSubItem = nCol; //子表项索引号
		lvi.pszText = lpBuffer;     //表项名文本
		lvi.cchTextMax = sizeof(lpBuffer);//表项名最大长度
		VERIFY(GetItem(&lvi));//指向LVITEM结构体的一个指针，获取属性


		CRect rcTemp;
		rcTemp = rcItem;

		if (nCol==0)
		{
			rcTemp.left -=2;
		}

		if ( lpDrawItemStruct->itemState & ODS_SELECTED )
		{
			pDC->FillSolidRect(&rcTemp, GetSysColor(COLOR_HIGHLIGHT));//调用该成员函数用指定的固体色填充矩形。
			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT)) ;//设置指定设备环境(HDC)的字体颜色 
		}
		else
		{
			COLORREF color;
			color = GetBkColor();//得到当前背景颜色
			pDC->FillSolidRect(rcTemp,color);

			if (FindColColor(nCol,color)) //自定义函数
			{
				pDC->FillSolidRect(rcTemp,color);
			}
			if (FindItemColor(nCol,lpDrawItemStruct->itemID,color))//自定义函数
			{
				pDC->FillSolidRect(rcTemp,color);
			}
			
			//pDC->SetTextColor(m_color);
		}

		pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));//该函数选择一对象到指定的设备上下文环境中，
		                                                    //该新对象替换先前的相同类型的对象。 

		UINT   uFormat = DT_CENTER ;
		if (m_Header.m_Format[nCol]=='0')
		{
			uFormat = DT_LEFT;
		}
		else if (m_Header.m_Format[nCol]=='1')
		{
			uFormat = DT_CENTER;
		}
		else if (m_Header.m_Format[nCol]=='2')
		{
			uFormat = DT_RIGHT;
		}
		TEXTMETRIC metric;
		pDC->GetTextMetrics(&metric);//该函数把程序当前的字体信息，存放到TEXTMETRIC（即MSDN原文中的specified buffer）中 
		int ofst;
		ofst = rcItem.Height() - metric.tmHeight;
		rcItem.OffsetRect(0,ofst/2);
		pDC->SetTextColor(m_color);
		COLORREF color;
		if (FindColTextColor(nCol,color))
		{
			pDC->SetTextColor(color);
		}
		if (FindItemTextColor(nCol,lpDrawItemStruct->itemID,color))
		{
			pDC->SetTextColor(color);
		}
		CFont nFont ,* nOldFont; 
		nFont.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("宋体"));//创建字体 
		nOldFont = pDC->SelectObject(&nFont);
		DrawText(lpDrawItemStruct->hDC, lpBuffer, strlen(lpBuffer), 
			&rcItem, uFormat) ;

		pDC->SelectStockObject(SYSTEM_FONT) ;
	}


}

bool CListCtrlCl::FindColColor(int col, COLORREF &color)
{
		int flag = 0;
	for (POSITION pos = m_ptrListCol.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_ptrListCol.GetNext(pos);
		if (pColor->nCol==col)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;


}

bool CListCtrlCl::FindColTextColor(int col, COLORREF &color)
{
	int flag = 0;
	for (POSITION pos = m_colTextColor.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_colTextColor.GetNext(pos);
		if (pColor->nCol==col)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;


}

bool CListCtrlCl::FindItemColor(int col, int row, COLORREF &color)
{
	int flag = 0;
	for (POSITION pos = m_ptrListItem.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_ptrListItem.GetNext(pos);
		if (pColor->nCol==col&&pColor->nRow==row)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;


}

bool CListCtrlCl::FindItemTextColor(int col, int row, COLORREF &color)
{
		int flag = 0;
	for (POSITION pos = m_ItemTextColor.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_ItemTextColor.GetNext(pos);
		if (pColor->nCol==col&&pColor->nRow==row)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;

}

int CListCtrlCl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat, int nWidth, int nSubItem)
{
		m_Header.m_HChar.Add(lpszColumnHeading);
	if (nFormat==LVCFMT_LEFT)
	{
		m_Header.m_Format = m_Header.m_Format + "0";
	}
	else if (nFormat==LVCFMT_CENTER)
	{
		m_Header.m_Format = m_Header.m_Format + "1";
	}
	else if (nFormat==LVCFMT_RIGHT)
	{
		m_Header.m_Format = m_Header.m_Format + "2";
	}
	else
	{
		m_Header.m_Format = m_Header.m_Format + "1";
	}
	return CListCtrl::InsertColumn(nCol,lpszColumnHeading,nFormat,nWidth,nSubItem);

}

void CListCtrlCl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
		if (m_nRowHeight>0)
	{
		lpMeasureItemStruct->itemHeight = m_nRowHeight;
	}

}

void CListCtrlCl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
		// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);

}



void CListCtrlCl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0,LVS_OWNERDRAWFIXED);
	CListCtrl::PreSubclassWindow();
	CHeaderCtrl *pHeader = GetHeaderCtrl();
	m_Header.SubclassWindow(pHeader->GetSafeHwnd());

}

void CListCtrlCl::SetColColor(int col, COLORREF color)
{
	stColor *pColor  = new stColor;
	pColor->nCol = col;
	pColor->rgb = color;
	m_ptrListCol.AddTail(pColor);

}

void CListCtrlCl::SetColTextColor(int col, COLORREF color)
{
	stColor *pColor = new stColor;
	pColor->nCol = col;
	pColor->rgb = color;
	m_colTextColor.AddTail(pColor);

}

void CListCtrlCl::SetFontHW(int nHeight, int nWith)
{
		m_fontHeight = nHeight;
	m_fontWith = nWith;

}

void CListCtrlCl::SetHeaderBKColor(int R, int G, int B, int Gradient)
{
		m_Header.m_R = R;
	m_Header.m_G = G;
	m_Header.m_B = B;
	m_Header.m_Gradient = Gradient;

}

void CListCtrlCl::SetHeaderFontHW(int nHeight, int nWith)
{
		m_Header.m_fontHeight = nHeight;
	m_Header.m_fontWith = nWith;

}

void CListCtrlCl::SetHeaderHeight(float Height)
{
	m_Header.m_Height = Height;

}

void CListCtrlCl::SetHeaderTextColor(COLORREF color)
{
	m_Header.m_color = color;

}

void CListCtrlCl::SetItemColor(int col, int row, COLORREF color)
{
		stColor *pColor  = new stColor;
	pColor->nCol = col;
	pColor->nRow = row;
	pColor->rgb = color;
	m_ptrListItem.AddTail(pColor);

}

void CListCtrlCl::SetItemTextColor(int col, int row, COLORREF color)
{
		stColor *pColor = new stColor;
	pColor->nCol = col;
	pColor->nRow = row;
	pColor->rgb = color;
	m_ItemTextColor.AddTail(pColor);

}

void CListCtrlCl::SetRowHeigt(int nHeight)
{
	m_nRowHeight = nHeight;

	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

BOOL CListCtrlCl::SetTextColor(COLORREF cr)
{
	m_color = cr;
	return TRUE;

}

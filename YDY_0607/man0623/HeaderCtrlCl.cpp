// HeaderCtrlCl.cpp : implementation file
//

#include "stdafx.h"
#include "Wilson6.h"
#include "HeaderCtrlCl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlCl

CHeaderCtrlCl::CHeaderCtrlCl()
{
}

CHeaderCtrlCl::~CHeaderCtrlCl()
{
}


BEGIN_MESSAGE_MAP(CHeaderCtrlCl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CHeaderCtrlCl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlCl message handlers

void CHeaderCtrlCl::OnPaint()
{
	CPaintDC dc(this); //device context for painting为了传递一个句柄给dc。
	                      //既然有dc，所以你必然是定义的窗口类，因此this也可以说是你所定义的窗口类的指针
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CHeaderCtrl::OnPaint()
	int nItem; 
	nItem = GetItemCount();//得到有几个单元，返回值：列表视图控件中项的数目。
 
	for(int i = 0; i<nItem;i ++) 
	{ 
		CRect tRect;
		GetItemRect(i,&tRect);//得到Item的尺寸
		int R = m_R,G = m_G,B = m_B;
		CRect nRect(tRect);//拷贝尺寸到新的容器中 
		nRect.left++;//留出分割线的地方 
		//绘制立体背景 
		for(int j = tRect.top;j<=tRect.bottom;j++) 
		{ 
			nRect.bottom = nRect.top+1; 
			CBrush _brush; 
			_brush.CreateSolidBrush(RGB(R,G,B));//创建画刷 ，reateSolidBrush用指定的实线初始化画刷 
			dc.FillRect(&nRect,&_brush); //填充背景,该函数用指定的画刷填充矩形，此函数包括矩形的左上边界，但不包括矩形的右下边界
			_brush.DeleteObject(); //释放画刷 该函数删除一个逻辑笔、画笔、字体、位图、区域或者调色板，
	                            	//释放所有与该对象有关的系统资源，在对象被删除之后，指定的句柄也就失效了。 

			R-=m_Gradient;G-=m_Gradient;B-=m_Gradient;//m_Gradient 画立体背景，渐变系数
			if (R<0)R = 0;
			if (G<0)G = 0;
			if (B<0)B= 0;
			nRect.top = nRect.bottom; 
		} 
		dc.SetBkMode(TRANSPARENT); //使用透明的输出，也就是文字的背景是不改变的。 
		CFont nFont ,* nOldFont; 
		//dc.SetTextColor(RGB(250,50,50)); 
		dc.SetTextColor(m_color);  //设置指定设备环境(HDC)的字体颜色 
		nFont.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("宋体"));//创建字体 
		nOldFont = dc.SelectObject(&nFont);//该函数选择一对象到指定的设备上下文环境中，该新对象替换先前的相同类型的对象。 

		UINT nFormat = 1;
		if (m_Format[i]=='0')
		{
			nFormat = DT_LEFT;  //左对齐
			tRect.left+=3;
		}
		else if (m_Format[i]=='1')
		{
			nFormat = DT_CENTER;  //居中
		}
		else if (m_Format[i]=='2')
		{
			nFormat = DT_RIGHT;  //右对齐
			tRect.right-=3;
		}
		TEXTMETRIC metric;
		dc.GetTextMetrics(&metric); //获得TEXTMETRIC类型变量的值
		int ofst = 0;
		ofst = tRect.Height() - metric.tmHeight;//Height 计算CRect的高度,LONG tmHeight字符高度
		tRect.OffsetRect(0,ofst/2);//OffsetRect 将CRect移动到指定的偏移
		dc.DrawText(m_HChar[i],&tRect,nFormat);//&tRect指向矩形结构RECT的指针.nFormat指定格式化文本的方法
		dc.SelectObject(nOldFont); 
		nFont.DeleteObject(); //释放字体 
	} 
	//画头部剩余部分
	CRect rtRect;
	CRect clientRect;
	GetItemRect(nItem - 1,rtRect);//确定列表框的尺寸

	GetClientRect(clientRect);
	rtRect.left = rtRect.right+1;
	rtRect.right = clientRect.right;//（left，top，right，和bottom）也是CRect的可访问数据成员
	int R = m_R,G = m_G,B = m_B;
	CRect nRect(rtRect);
	//绘制立体背景 
	for(int j = rtRect.top;j<=rtRect.bottom;j++) 
	{ 
		nRect.bottom = nRect.top+1; 
		CBrush _brush; 
		_brush.CreateSolidBrush(RGB(R,G,B));//创建画刷 
		dc.FillRect(&nRect,&_brush); //填充背景 
		_brush.DeleteObject(); //释放画刷 
		R-=m_Gradient;G-=m_Gradient;B-=m_Gradient;
		if (R<0)R = 0;
		if (G<0)G = 0;
		if (B<0)B= 0;
		nRect.top = nRect.bottom; 
	} 

}

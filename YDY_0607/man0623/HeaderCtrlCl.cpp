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
	CPaintDC dc(this); //device context for paintingΪ�˴���һ�������dc��
	                      //��Ȼ��dc���������Ȼ�Ƕ���Ĵ����࣬���thisҲ����˵����������Ĵ������ָ��
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CHeaderCtrl::OnPaint()
	int nItem; 
	nItem = GetItemCount();//�õ��м�����Ԫ������ֵ���б���ͼ�ؼ��������Ŀ��
 
	for(int i = 0; i<nItem;i ++) 
	{ 
		CRect tRect;
		GetItemRect(i,&tRect);//�õ�Item�ĳߴ�
		int R = m_R,G = m_G,B = m_B;
		CRect nRect(tRect);//�����ߴ絽�µ������� 
		nRect.left++;//�����ָ��ߵĵط� 
		//�������屳�� 
		for(int j = tRect.top;j<=tRect.bottom;j++) 
		{ 
			nRect.bottom = nRect.top+1; 
			CBrush _brush; 
			_brush.CreateSolidBrush(RGB(R,G,B));//������ˢ ��reateSolidBrush��ָ����ʵ�߳�ʼ����ˢ 
			dc.FillRect(&nRect,&_brush); //��䱳��,�ú�����ָ���Ļ�ˢ�����Σ��˺����������ε����ϱ߽磬�����������ε����±߽�
			_brush.DeleteObject(); //�ͷŻ�ˢ �ú���ɾ��һ���߼��ʡ����ʡ����塢λͼ��������ߵ�ɫ�壬
	                            	//�ͷ�������ö����йص�ϵͳ��Դ���ڶ���ɾ��֮��ָ���ľ��Ҳ��ʧЧ�ˡ� 

			R-=m_Gradient;G-=m_Gradient;B-=m_Gradient;//m_Gradient �����屳��������ϵ��
			if (R<0)R = 0;
			if (G<0)G = 0;
			if (B<0)B= 0;
			nRect.top = nRect.bottom; 
		} 
		dc.SetBkMode(TRANSPARENT); //ʹ��͸���������Ҳ�������ֵı����ǲ��ı�ġ� 
		CFont nFont ,* nOldFont; 
		//dc.SetTextColor(RGB(250,50,50)); 
		dc.SetTextColor(m_color);  //����ָ���豸����(HDC)��������ɫ 
		nFont.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("����"));//�������� 
		nOldFont = dc.SelectObject(&nFont);//�ú���ѡ��һ����ָ�����豸�����Ļ����У����¶����滻��ǰ����ͬ���͵Ķ��� 

		UINT nFormat = 1;
		if (m_Format[i]=='0')
		{
			nFormat = DT_LEFT;  //�����
			tRect.left+=3;
		}
		else if (m_Format[i]=='1')
		{
			nFormat = DT_CENTER;  //����
		}
		else if (m_Format[i]=='2')
		{
			nFormat = DT_RIGHT;  //�Ҷ���
			tRect.right-=3;
		}
		TEXTMETRIC metric;
		dc.GetTextMetrics(&metric); //���TEXTMETRIC���ͱ�����ֵ
		int ofst = 0;
		ofst = tRect.Height() - metric.tmHeight;//Height ����CRect�ĸ߶�,LONG tmHeight�ַ��߶�
		tRect.OffsetRect(0,ofst/2);//OffsetRect ��CRect�ƶ���ָ����ƫ��
		dc.DrawText(m_HChar[i],&tRect,nFormat);//&tRectָ����νṹRECT��ָ��.nFormatָ����ʽ���ı��ķ���
		dc.SelectObject(nOldFont); 
		nFont.DeleteObject(); //�ͷ����� 
	} 
	//��ͷ��ʣ�ಿ��
	CRect rtRect;
	CRect clientRect;
	GetItemRect(nItem - 1,rtRect);//ȷ���б��ĳߴ�

	GetClientRect(clientRect);
	rtRect.left = rtRect.right+1;
	rtRect.right = clientRect.right;//��left��top��right����bottom��Ҳ��CRect�Ŀɷ������ݳ�Ա
	int R = m_R,G = m_G,B = m_B;
	CRect nRect(rtRect);
	//�������屳�� 
	for(int j = rtRect.top;j<=rtRect.bottom;j++) 
	{ 
		nRect.bottom = nRect.top+1; 
		CBrush _brush; 
		_brush.CreateSolidBrush(RGB(R,G,B));//������ˢ 
		dc.FillRect(&nRect,&_brush); //��䱳�� 
		_brush.DeleteObject(); //�ͷŻ�ˢ 
		R-=m_Gradient;G-=m_Gradient;B-=m_Gradient;
		if (R<0)R = 0;
		if (G<0)G = 0;
		if (B<0)B= 0;
		nRect.top = nRect.bottom; 
	} 

}

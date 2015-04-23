// DrawAppearance  .cpp: interface for the CDrawAppearance   class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "DrawAppearance.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDrawAppearance ::CDrawAppearance ()
{
	m_clrTitle=RGB(255,255,255);
	m_wdFontW = 0;
	m_wdFontH = 0;
	m_wdSpace = 1;
	
	m_rtMaxBtn=NULL;
	m_rtMinBtn=NULL;
	m_rtCloseBtn=NULL;

	m_unIDMInNor=0;
	m_unIDClsNor=0;
	m_unIDMaxNor=0;
	m_unIDResNor=0;

	m_unIDMInDown=0;
	m_unIDClsDown=0;
	m_unIDMaxDown=0;
	m_unIDResDown=0;
	
	m_bDownMin=FALSE;
	m_bDownMax=FALSE;
	m_bDownCls=FALSE;
	
	m_bRedrawWnd=FALSE;
}

CDrawAppearance ::~CDrawAppearance ()
{

}

/************************************************************************/
/* ���ܣ����ƴ��ڷǿͻ���
/*-------------------------------------------------------------------
/* ������CDC	  *pWinDC		---- ���� DC    	
/*		 int	  LeftBmp	---- �� ��0 (�����߿��bmpͼƬ)
/*		 int	  RightBmp	---- �� ��0
/*		 int	  ButtomBmp	---- ��	��0
/*		 int	  TitleBmp	---- ��	��0
/*-------------------------------------------------------------------
/* ���أ�	
/*-------------------------------------------------------------------
/* ע  ����DC������GetWindowDC()��� ����GetDC()
/*		 
/* GetWindowDC()�� ����������ڵ�DC     GetDC()�� ��ÿͻ�����DC
/*
/************************************************************************/

void CDrawAppearance::DrawDlg(CDC *pWinDC,COLORREF colorValue)//����ɫ���
{
	ASSERT(pWinDC!=NULL);

	CDC memDC;
	CRect wndRC;
	CBitmap bmp;

	::GetWindowRect(pWinDC->GetWindow()->m_hWnd,&wndRC);	
	wndRC.OffsetRect(wndRC.Width(),wndRC.Height());
	int nTitleHeight = GetSystemMetrics(SM_CYCAPTION);
	int nborder = ::GetSystemMetrics(SM_CXFIXEDFRAME);

	if(pWinDC->GetWindow()->GetStyle()&WS_THICKFRAME)
	{
		int nborder = ::GetSystemMetrics(SM_CXBORDER);
	}

	memDC.CreateCompatibleDC(NULL);

	//������߽�
	bmp.CreateCompatibleBitmap(pWinDC,nborder,wndRC.Height()-nTitleHeight);
	memDC.SelectObject(&bmp);
	memDC.FillSolidRect(0,0,nborder,wndRC.Height()-nTitleHeight, colorValue);
	pWinDC->BitBlt(0,nTitleHeight,nborder,wndRC.Height()-nTitleHeight,&memDC,0,0,SRCCOPY);
	bmp.DeleteObject();

	//�����ұ߽�
	bmp.CreateCompatibleBitmap(pWinDC,nborder,wndRC.Height()-nTitleHeight);
	memDC.SelectObject(&bmp);
	memDC.FillSolidRect(0,0,nborder,wndRC.Height()-nTitleHeight,colorValue);
	pWinDC->BitBlt(wndRC.Width()-nborder,nTitleHeight,nborder,wndRC.Height()-nTitleHeight,&memDC,0,0,SRCCOPY);
	bmp.DeleteObject();

	//���صױ�
	bmp.CreateCompatibleBitmap(pWinDC,wndRC.Width()-2*nborder,nborder);
	memDC.SelectObject(&bmp);
	memDC.FillSolidRect(0,0,wndRC.Width()-2*nborder,nborder,colorValue);
	pWinDC->BitBlt(nborder,wndRC.Height()-nborder,wndRC.Width()-2*nborder,wndRC.Height(),&memDC,0,0,SRCCOPY);
	bmp.DeleteObject();


	////���ر�����
	bmp.CreateCompatibleBitmap(pWinDC,wndRC.Width()-2*nborder,nborder);
	memDC.SelectObject(&bmp);
	memDC.FillSolidRect(0,0,wndRC.Width(),nTitleHeight+nborder,colorValue);
	pWinDC->BitBlt(0,0,wndRC.Width(),nTitleHeight+nborder,&memDC,0,0,SRCCOPY);

	bmp.DeleteObject();
	memDC.DeleteDC();
} 

/************************************************************************/
/* ���ܣ����ƴ��ڷǿͻ���
/*-------------------------------------------------------------------
/* ������CDC	  *pWinDC		---- ���� DC    
/*		 COLORREF color			---- �߿���ɫ	
/*-------------------------------------------------------------------
/* ���أ�	
/*-------------------------------------------------------------------
/* ע  ����DC������GetWindowDC()��� ����GetDC()
/*		 
/* GetWindowDC()�� ����������ڵ�DC     GetDC()�� ��ÿͻ�����DC
/*
/************************************************************************/
void CDrawAppearance::DrawDlg(CDC *pWinDC,UINT LeftBmp,UINT RightBmp,UINT ButtomBmp,UINT TitleBmp)
{
	ASSERT(pWinDC!=NULL);

	CDC memDC;
	CRect wndRC;
	CBitmap bmp;

	::GetWindowRect(pWinDC->GetWindow()->m_hWnd,&wndRC);
	wndRC.OffsetRect(wndRC.Width(),wndRC.Height());
	int nTitleHeight = GetSystemMetrics(SM_CYCAPTION);
	int nborder = ::GetSystemMetrics(SM_CXFIXEDFRAME);
	if(pWinDC->GetWindow()->GetStyle()&WS_THICKFRAME)
	{
		int nborder = ::GetSystemMetrics(SM_CXBORDER);
	}

	//������߽�λͼ
	bmp.LoadBitmap(LeftBmp);
	BITMAP so_bmp;
	bmp.GetBitmap(&so_bmp);
	int nBmpWidth, nbmpHeight;
	nBmpWidth = so_bmp.bmWidth;
	nbmpHeight = so_bmp.bmHeight;

	memDC.CreateCompatibleDC(pWinDC);
	memDC.SelectObject(&bmp);
	pWinDC->StretchBlt(0,nTitleHeight,nborder,wndRC.Height()-nTitleHeight,&memDC,0,0,nBmpWidth,nbmpHeight,SRCCOPY);
	bmp.DeleteObject();

	//�����ұ߽�λͼ
	bmp.LoadBitmap(RightBmp);
	bmp.GetBitmap(&so_bmp);
	nBmpWidth = so_bmp.bmWidth;
	nbmpHeight = so_bmp.bmHeight;

	memDC.SelectObject(&bmp);
	pWinDC->StretchBlt(wndRC.Width()-nborder,nTitleHeight,nborder,wndRC.Height()-nTitleHeight,&memDC,0,0,nBmpWidth,nbmpHeight,SRCCOPY);
	bmp.DeleteObject();

	//���صױ�λͼ
	bmp.LoadBitmap(ButtomBmp);
	bmp.GetBitmap(&so_bmp);
	nBmpWidth = so_bmp.bmWidth;
	nbmpHeight = so_bmp.bmHeight;

	memDC.SelectObject(&bmp);
	pWinDC->StretchBlt(nborder,wndRC.Height()-nborder,wndRC.Width()-2*nborder,nborder,&memDC,0,0,nBmpWidth,nbmpHeight,SRCCOPY);
	bmp.DeleteObject();


	//���ر�����λͼ
	bmp.LoadBitmap(TitleBmp);
	bmp.GetBitmap(&so_bmp);
	nBmpWidth = so_bmp.bmWidth;
	nbmpHeight = so_bmp.bmHeight;

	memDC.SelectObject(&bmp);
	pWinDC->StretchBlt(0,0,wndRC.Width(),nTitleHeight+nborder,&memDC,0,0,nBmpWidth,nbmpHeight,SRCCOPY);
	bmp.DeleteObject();

	memDC.DeleteDC();
} 


/************************************************************************/
/* ���ܣ����Ʊ�����
/*------------------------------------------------
/* ������CDC	  *pWinDC		---- ����DC
		 COLORREF clrTop		---- ������������ɫ	
		 COLORREF clrBottom		---- �������ײ���ɫ
/*------------------------------------------------		
/* ���أ��ɹ����� TRUE   DC��Ч����FALSE
/*------------------------------------------------
/* ע  ����DC������GetWindowDC()��� ����GetDC()
/************************************************************************/
void CDrawAppearance::DrawTitleBar(CDC *pWinDC, COLORREF color)
{
	CDC memDC;
	CBitmap bmp;
	CRect rtWnd, rtTitle;
	CPoint point;
	::GetWindowRect(pWinDC->GetWindow()->m_hWnd,&rtWnd);

	//��ȡ��������С
	rtTitle.left = GetSystemMetrics(SM_CXFRAME);
	rtTitle.top = GetSystemMetrics(SM_CYFRAME);
	rtTitle.right = rtWnd.right - rtWnd.left - GetSystemMetrics(SM_CXFRAME);
	rtTitle.bottom = rtTitle.top + GetSystemMetrics(SM_CYSIZE);

	point.x = rtWnd.right  + GetSystemMetrics(SM_CXFRAME);
	point.y = 30;

	memDC.CreateCompatibleDC(pWinDC);
	bmp.CreateCompatibleBitmap(pWinDC,point.x,point.y);
	memDC.SelectObject(&bmp);

	memDC.FillSolidRect(0,0,point.x,point.y, color);	//������ɫ

	////��ͼ
	/*CBitmap pic;
	pic.LoadBitmap(IDB_BITMAP_BG);
	ShowBitmap(&memDC,0,0, rtTitle.right, 30, pic);*/

	pWinDC->BitBlt(0,0,point.x,point.y,&memDC,0,0,SRCCOPY);
	
	memDC.DeleteDC();
	bmp.DeleteObject();
}

void CDrawAppearance::DrawSystemBtn1(CDC *pWinDC,UINT nIDSysBtn)
{
	CBrush Brush(RGB(0,100,255));//RGB(165,201,235)
	CBrush* pOldBrush = pWinDC->SelectObject(&Brush);

	CRect rtWnd, rtTitle, rtButtons;
	::GetWindowRect(pWinDC->GetWindow()->m_hWnd,&rtWnd);

	//ȡ�ñ�������λ��
	rtTitle.left = GetSystemMetrics(SM_CXFRAME);
	rtTitle.top = GetSystemMetrics(SM_CYFRAME);
	rtTitle.right = rtWnd.right - rtWnd.left - GetSystemMetrics(SM_CXFRAME);
	rtTitle.bottom = rtTitle.top + GetSystemMetrics(SM_CYSIZE);

	//������С����ť��λ�ã�λͼ��СΪ15X15
	rtButtons.left = rtTitle.right-55;
	rtButtons.top= rtTitle.top;
	rtButtons.right = rtTitle.right-37;
	rtButtons.bottom = rtTitle.top+20;
	m_rtMinBtn = rtButtons;
	//������󻯰�ť��λ�ã�λͼ��СΪ15X15
	m_rtMaxBtn.left = m_rtMinBtn.left + 18;
	m_rtMaxBtn.top = m_rtMinBtn.top;
	m_rtMaxBtn.right = m_rtMinBtn.right + 16;
	m_rtMaxBtn.bottom = m_rtMinBtn.bottom;

	m_rtCloseBtn.left = m_rtMaxBtn.left + 18;
	m_rtCloseBtn.top =  m_rtMaxBtn.top;
	m_rtCloseBtn.right = m_rtMaxBtn.right + 16;
	m_rtCloseBtn.bottom = m_rtMaxBtn.bottom;

	CBitmap* pBitmap = new CBitmap;
	BITMAP BmpInfo;
	CBitmap* pOldBitmap;
	CDC* pDisplayMemDC=new CDC;
	pDisplayMemDC->CreateCompatibleDC(pWinDC);

	//rtButtons = m_rtMinBtn;
	pBitmap->LoadBitmap(nIDSysBtn);
	pBitmap->GetBitmap(&BmpInfo);
	pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
	pWinDC->BitBlt(rtButtons.left, rtButtons.top-6, BmpInfo.bmWidth, BmpInfo.bmHeight, pDisplayMemDC, 0, 0, SRCCOPY);
	pDisplayMemDC->SelectObject(pOldBitmap);

	pBitmap->DeleteObject();
	pDisplayMemDC->DeleteDC();

}

/************************************************************************/
/* ���ܣ����ƴ��ڱ߿�
/*-------------------------------------------------------------------
/* ������CDC	  *pWinDC		---- ���� DC    
/*		 COLORREF color			---- �߿���ɫ	
/*		 int	  nLefOffset	---- �� ��0 (�����߿�Ĵ�ϸ +n �� -n)
/*		 int	  nTopOffset	---- �� ��0
/*		 int	  nRitOffset	---- ��	��0
/*		 int	  nBtmOffset	---- ��	��0
/*-------------------------------------------------------------------
/* ���أ��ɹ����� TRUE   DC��Ч����FALSE	
/*-------------------------------------------------------------------
/* ע  ����DC������GetWindowDC()��� ����GetDC()
/*		 
/* GetWindowDC()�� ����������ڵ�DC     GetDC()�� ��ÿͻ�����DC
/*
/************************************************************************/
BOOL CDrawAppearance ::DrawBorder(CDC *pWinDC,COLORREF color,int nLefOffset,int nTopOffset,int nRitOffset,int nBtmOffset)
{
	if(!pWinDC)
	{	//AfxMessageBox("���ڲ����ڣ�",MB_ICONASTERISK);
		return FALSE; 
	}

	CBrush Brush(color);								// ����һ����ˢ����
    CBrush* pOldBrush = pWinDC->SelectObject(&Brush);	// ����ָ����ɫ�Ļ�ˢ
	
    CRect rtWnd;
    pWinDC->GetWindow()->GetWindowRect(&rtWnd);			//��ô��ھ���

    CPoint point;
    //��䶥�����
    point.x = rtWnd.Width();
	
	//GetSystemMetrics��������÷ǿͻ����Ĳ�ͬ���ֵĴ�С������������˵��͹�����
	//offset������˼Ϊƫ��������ʼΪ0
	
	//SM_CXFRAME ���ڱ߿�ı�Ե��ȣ����أ�
	//SM_CYFRAME ���ڱ߿�ı�Ե�߶�
	//SM_CXSIZE ���ڱ��������
	//SM_CYSIZE ���ڱ������߶�	
	//SM_CXSIZEFRAME��SM_CYFRAME��ͬ��SM_CXSIZE��SM_CYSIZE

    point.y = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYSIZE) + nTopOffset;
	
	//PatBlt���豸�ϴ���ģʽ,���豸���е�ģʽ��ѡ��Ļ�ˢ���
	//�������������Ͻ����꣬������դ��������
    pWinDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
    
	//��������
    point.x = GetSystemMetrics(SM_CXFRAME) + nLefOffset;			
    point.y = rtWnd.Height();
    pWinDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
    
	//���ײ����
    point.x = rtWnd.Width(); 
    point.y = GetSystemMetrics(SM_CYFRAME) + nBtmOffset;
    pWinDC->PatBlt(0, rtWnd.Height()-point.y, point.x, point.y, PATCOPY);
    
	//����Ҳ���
    point.x = GetSystemMetrics(SM_CXFRAME) + nRitOffset;
    point.y = rtWnd.Height();
    pWinDC->PatBlt(rtWnd.Width()-point.x, 0, point.x, point.y, PATCOPY);

	return TRUE;
}

/************************************************************************/
/* ���ܣ����Ʊ�����
/*------------------------------------------------
/* ������CDC	  *pWinDC		---- ����DC
		 COLORREF clrTop		---- ������������ɫ	
		 COLORREF clrBottom		---- �������ײ���ɫ
/*------------------------------------------------		
/* ���أ��ɹ����� TRUE   DC��Ч����FALSE
/*------------------------------------------------
/* ע  ����DC������GetWindowDC()��� ����GetDC()
/************************************************************************/
BOOL CDrawAppearance ::DrawTitleBar(CDC *pWinDC, COLORREF clrTop, COLORREF clrBottom)
{
	if (!pWinDC)
		return FALSE;

	CPen Pen; 
	CRect  rtWnd,rtTitle; 

	::GetWindowRect(pWinDC->GetWindow()->m_hWnd,&rtWnd);		//����Window���������Ļ�ľ��� 
	rtTitle=GetTitleBarRect(pWinDC);

	rtTitle.left -=10;											//�޸ĳߴ�
	rtTitle.top	 -=10;
	rtTitle.right+=10;

	CPen* pOldPen=pWinDC-> SelectObject(&Pen);					//ѡ�뻭��

	int R,G,B; 
	R=(GetRValue(clrTop)-GetRValue(clrBottom))/rtTitle.Height();//��ɫ��ֵ
	G=(GetGValue(clrTop)-GetGValue(clrBottom))/rtTitle.Height(); 
	B=(GetBValue(clrTop)-GetBValue(clrBottom))/rtTitle.Height(); 
	
	int ColR = GetRValue(clrTop),ColG= GetGValue(clrTop),ColB=GetBValue(clrTop); 
	
	for (int i=0;i<rtTitle.Height();i++)					//���Ʊ���Ĺ���,�Ӿ��ε����濪ʼ�����ߣ�һֱ�� 
	{ 
		ColR -= R;											//�����εĵײ���������ɫ�𽥱��� 
		ColG -= G; 
		ColB -= B; 

		Pen.DeleteObject(); 
		Pen.CreatePen(PS_SOLID,2,RGB(ColR,ColG,ColB));		//��������
		pWinDC-> SelectObject(&Pen); 

		pWinDC-> MoveTo(rtTitle.left,rtTitle.top+i);		//����
		pWinDC-> LineTo(rtTitle.right,rtTitle.top+i); 
	} 
	
	pWinDC-> SelectObject(pOldPen);

	return TRUE;
}

/************************************************************************/
/* ���ܣ����ƴ���ͼ��
/*---------------------------------------------------------
/* ������CDC  *pWinDC		---- ����DC
		 UINT idIcon		---- ͼ��ID
		 int  nLeftSpace	---- ͼ��Ŀ��λ�����������߾���
/*----------------------------------------------------------		
/* ���أ��ɹ����� TRUE   DC��Ч����NULL
/*----------------------------------------------------------
/* ע  ����DC������GetWindowDC()��� ����GetDC()
/************************************************************************/
BOOL CDrawAppearance ::DrawIcon(CDC *pWinDC, UINT idIcon, int nLeftSpace)
{
	if (!pWinDC)
		return NULL;

	CRect rtIcon;										
	CRect rtTitle=GetTitleBarRect(pWinDC);						
	
	rtIcon.left =/*rtTitle.left*/ + nLeftSpace;					//����ͼ�����
	rtIcon.top	=rtTitle.top-5; 
	rtIcon.right=rtIcon.left+rtTitle.bottom-8;
	rtIcon.bottom=rtTitle.bottom+rtIcon.top-10;
								
	::DrawIconEx(pWinDC->m_hDC,rtIcon.left,rtIcon.top, AfxGetApp()->LoadIcon(idIcon), //����ͼ��
		rtIcon.Width(), rtIcon.Height(), 0, NULL,DI_NORMAL);
	return TRUE;
}

/************************************************************************/
/* ���ܣ���ñ�������������
/************************************************************************/
CRect CDrawAppearance ::GetTitleBarRect(CDC *pWinDC)
{
	if (!pWinDC)
	{	AfxMessageBox("���ڲ����ڣ�",MB_ICONASTERISK);
		return NULL; 
	}
	
	CRect rtTitle;
	CRect rtWnd;

	GetWindowRect(pWinDC->GetWindow()->m_hWnd,&rtWnd);		//����Window���������Ļ�ľ��� 

	rtTitle.left = GetSystemMetrics(SM_CXFRAME); 			//ȡ������Title bar�ľ��� 
	rtTitle.top  = GetSystemMetrics(SM_CYFRAME); 
	rtTitle.right= rtWnd.Width() - GetSystemMetrics(SM_CXFRAME);
	rtTitle.bottom=rtTitle.top + GetSystemMetrics(SM_CYSIZE);
	return rtTitle;
}

/************************************************************************/
/* ���ܣ����ƴ��ڱ���
/*--------------------------------------------------------
/* ������CDC	 *pWinDC	---- ����DC
/*		 CString strTitle	---- �����ı�
/*		 int	 nLeftSpace	---- ����������������ߵľ���
/*--------------------------------------------------------
/* ���أ��ɹ����� TRUE   DC��Ч����NULL
/*--------------------------------------------------------
/* ע  ����DC������GetWindowDC()��� ����GetDC()
/************************************************************************/
BOOL CDrawAppearance ::DrawTitle(CDC *pWinDC, CString strTitle, int nLeftSpace)
{	
	if (!pWinDC)
		return FALSE;

	CFont font;										
	CFont *pOldFont;
	
	int nOldMode = pWinDC->SetBkMode(TRANSPARENT);			//����͸����ʾ
	COLORREF clOldText=pWinDC->SetTextColor(m_clrTitle);	//�����ı���ɫ
	
	font.CreateFont(m_wdFontH,m_wdFontW,0,0,0,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("����_GB2312"));//��������
	pOldFont=pWinDC->SelectObject(&font);					//ѡ������
	
	//pWinDC->SelectStockObject(OEM_FIXED_FONT);			//ѡ������

	CRect rtTitle=GetTitleBarRect(pWinDC);					//��ñ���������

	rtTitle.left += nLeftSpace;								//�������λ��

	if (m_wdFontH<=0)	
		rtTitle.top -=rtTitle.top/2;
	else
		rtTitle.top +=(rtTitle.Height()-m_wdFontH)/2-1;		//-1����Ϊ��Щƫ��

	pWinDC->DrawText(strTitle, &rtTitle, DT_LEFT);			//���Ʊ���
	pWinDC->SetBkMode(nOldMode);							//�ָ�
	pWinDC->SetTextColor(clOldText);					
	pWinDC->SelectObject(pOldFont);
	
	return TRUE;			
}

/************************************************************************/
/* ���ܣ����ƴ��ڱ���
/*-----------------------------------------------------------------------
/* ������CDC		*pWinDC,	    ---- ����DC		
/*		 CRect		*pDesRect,		---- Ŀ���������
/*		 COLORREF	clrBrush,		---- ������ˢ��ΪNULL������
/*		 UINT		unIDBitmap,		---- ����λͼ��ΪNULL������  
/*		 BOOL		bCenter,		---- �Ƿ������ʾ��Ĭ��TRUE �� FALSE
/*		 BOOL		bTransparent,	---- λͼ�Ƿ�͸����ʾ ��FALSE
/*		 COLORREF	clrTransparent	---- ��Ҫ͸������ɫ	  ��0
/*-----------------------------------------------------------------------
/* ���أ�bSet	----���غ����Ƿ�ִ�гɹ�	
/*-----------------------------------------------------------------------
/* ע  ��****��DCʹ�� GetDC()���*****
/*-----------------------------------------------------------------------				
/* ��������Ҫ����������ĵ��౳��������ǶԻ����޸ı���������OnCtrlColor��
/*
/* ���´�����ˢ (������λͼ��ˢ)��������������ʵ��λͼ������ʾ��͸����ʾ��
/* 
/* ���Ը����Ļ���λͼ�뻭ˢ�������͸����ʾʱ�ı���λͼ��С��λͼ��ʧ�档
/* 
/************************************************************************/
BOOL CDrawAppearance ::DrawBackground(CDC *pWinDC, CRect *pDesRect, COLORREF clrBrush, UINT unIDBitmap,
									  BOOL bCenter,BOOL bTransparent,COLORREF clrTransparent)	
{
	BOOL bSet=FALSE;									//����ֵ		
	if (pWinDC==NULL && !IsWindow(pWinDC->GetWindow()->m_hWnd))
	{	AfxMessageBox("��Ч��DC,�򴰿ڲ����ڣ�",MB_ICONASTERISK);
		return NULL;
	}

	if (clrBrush!=NULL)									//���ñ�����ˢ
	{	
		CBrush brush(clrBrush);							
		CBrush *pOldBrush=pWinDC->SelectObject(&brush);	
		bSet=pWinDC->PatBlt(pDesRect->left,pDesRect->top,pDesRect->Width(),pDesRect->Height(),PATCOPY);
		pWinDC->SelectObject(pOldBrush);					
		pOldBrush->DeleteObject();
	}	
	if (unIDBitmap!=NULL)								//���ñ���λͼ
	{
		BOOL	bZoom=FALSE;
		CDC		dcMem;												
		BITMAP	bmOriginal;
		BITMAP	bmNew;
		CBitmap bitmap;
		int x,y,nWidth,nHeight;
		
		dcMem.CreateCompatibleDC(pWinDC);
		
		if (!bitmap.LoadBitmap(unIDBitmap))				//����λͼ
		{
			AfxMessageBox("Load bitmap failure!\r\rThe bitmap exist?",MB_ICONERROR|MB_OK);
			return bSet;
		}
		
		bitmap.GetBitmap(&bmOriginal);					//���λͼ�ߴ�
		CBitmap *pOldBitmap=dcMem.SelectObject(&bitmap);
		
		double dBitmapWidth  = bmOriginal.bmWidth;
		double dBitmapHeight = bmOriginal.bmHeight;
		double dBitmapRatio=dBitmapWidth/dBitmapHeight;	//ͼ���߱�
		
		if (pDesRect->Width()<bmOriginal.bmWidth)		//���Ŀ����ο�С��λͼ��
		{	
			bmNew.bmWidth  = (int)(pDesRect->Width()/dBitmapWidth*dBitmapHeight);	
			bmNew.bmHeight = (int)(bmNew.bmWidth/dBitmapRatio);
			bZoom = TRUE;
		}
		else if(pDesRect->Height()<bmOriginal.bmHeight) //���Ŀ����θ�С��λͼ��
		{	
			bmNew.bmHeight = (int)(pDesRect->Height()/dBitmapWidth*dBitmapHeight);
			bmNew.bmWidth  = (int)(bmNew.bmHeight*dBitmapRatio);
			bZoom = TRUE;
		}
		else
			bmNew=bmOriginal;							//����λͼ��С����
		
		if (bCenter)
		{	
			x=(pDesRect->Width()-bmNew.bmWidth)/2;		//ͼ�������ʾ
			y=(pDesRect->Height()-bmNew.bmHeight)/2;	
			nWidth =bmNew.bmWidth;
			nHeight=bmNew.bmHeight;
		}
		else
		{
			x=pDesRect->left;							//ͼ�����������Ŀ�����
			y=pDesRect->top;
			nWidth =pDesRect->Width();					
			nHeight=pDesRect->Height();
		}
		
		pWinDC->SetStretchBltMode(HALFTONE);			//����ͼ��ƽ����ʾ 
		if(bTransparent&& !bZoom && bCenter)
			bSet=TransparentBlt(pWinDC->m_hDC,x,y,nWidth,nHeight,dcMem.m_hDC,0,0,bmOriginal.bmWidth,bmOriginal.bmHeight,
							clrTransparent);			//����λͼ
		else
			bSet=pWinDC->StretchBlt(x,y,nWidth,nHeight,&dcMem,0,0,bmOriginal.bmWidth,bmOriginal.bmHeight,SRCCOPY);//����λͼ
		
		dcMem.SelectObject(pOldBitmap);					//�ָ�Ĭλͼ
		dcMem.DeleteDC();								//�ͷ�DC
	}					
	return bSet;
}

/************************************************************************/
/*���ܣ�λͼ͸����ʾ
/*--------------------------------------------------
/*������HDC		hdcDest,		---- Ŀ��DC
/*		int		nXOriginDest,   ---- Ŀ��Xƫ��
/*		int		nYOriginDest,   ---- Ŀ��Yƫ��
/*		int		nWidthDest,     ---- Ŀ����
/*		int		nHeightDest,    ---- Ŀ��߶�
/*		HDC		hdcSrc,         ---- ԴDC
/*		int		nXOriginSrc,    ---- ԴX���
/*		int		nYOriginSrc,    ---- ԴY���
/*		int		nWidthSrc,      ---- Դ���
/*		int		nHeightSrc,     ---- Դ�߶�
/*		UINT	crTransparent   ---- ͸��ɫ,COLORREF����
/*---------------------------------------------------
/*���أ��ɹ������� 		
/************************************************************************/
BOOL CDrawAppearance ::TransparentBlt( HDC hdcDest,int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
					   HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent)
{
	HBITMAP hOldImageBMP, hImageBMP;
	hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// ��������λͼ
	
	HBITMAP hOldMaskBMP, hMaskBMP;
	hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// ������ɫ����λͼ

	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);

	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP =  (HBITMAP)SelectObject(hMaskDC, hMaskBMP);

	// ��ԴDC�е�λͼ��������ʱDC��
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
					hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);

	// ����͸��ɫ
	SetBkColor(hImageDC, crTransparent);

	// ����͸������Ϊ��ɫ����������Ϊ��ɫ������λͼ
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);

	// ����͸������Ϊ��ɫ���������򱣳ֲ����λͼ
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// ͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
	SetBkColor(hdcDest,RGB(255,255,255));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// "��"����,��������Ч��
	BOOL bResult=BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);

	// �����ָ�	
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
	return bResult;
}

/************************************************************************/
/*���ܣ����ñ������ɫ
/*--------------------
/*ע  ���ڻ���֮ǰ����
/************************************************************************/
void CDrawAppearance ::SetTitleColor(COLORREF clrTitle)
{
	m_clrTitle=clrTitle;
}

/************************************************************************/
/*���ܣ����ñ��������С
/*-----------------------
/*��������ȡ��߶�
/*-----------------------
/*ע  ���ڻ���֮ǰ����
/************************************************************************/
void CDrawAppearance ::SetTitleFontSize(WORD wdFontW, WORD wdFontH)
{
	m_wdFontW=wdFontW;
	m_wdFontH=wdFontH;
}

/************************************************************************/
/* ���ܣ���ð�ťλͼID�����û�ͼ�������л��ƣ����水ťλ��
/*---------------------------------------------------------
/* ������CDC  *pWinDC		---- ����DC
/*		 UINT unIDClose 	---- ������ť��λͼID Ĭ��ֵ��0
/*		 UINT unIDMax			 
/*		 UINT unIDRestore		 
/*       UINT unIDMin		
/*---------------------------------------------------------
/* ���أ��ɹ�����-TRUE   DC��Ч����-NULL
/*---------------------------------------------------------
/* ע  ����DC������GetWindowDC()��� ����GetDC()
/************************************************************************/
BOOL CDrawAppearance ::DrawSystemBtn(CDC *pWinDC, UINT unIDClose, UINT unIDMax, UINT unIDRestore, UINT unIDMin)
{
	if (!pWinDC)
		return FALSE;
	
	m_bRedrawWnd=TRUE;		

	m_rtCloseBtn = DrawBtnBmp(pWinDC,unIDClose);		//����λͼ������λ��

	if (pWinDC->GetWindow()->IsZoomed())			
		m_rtMaxBtn = DrawBtnBmp(pWinDC,unIDRestore);
	else
		m_rtMaxBtn = DrawBtnBmp(pWinDC,unIDMax);

	m_rtMinBtn = DrawBtnBmp(pWinDC,unIDMin);

	m_wdSpace = 0;									//ȫ��������Ϻ�Ҫ��0

	m_unIDMaxNor = unIDMax;							//����λͼID
	m_unIDMInNor = unIDMin;
	m_unIDClsNor = unIDClose;
	m_unIDResNor = unIDRestore;

	return TRUE;
}	

/************************************************************************/
/* ���ܣ����ư�ťλͼ
/*-----------------------------------------------------------
/* ������CDC   *pWinDC		---- ����DC
/*		 UINT  unIDBmp 		---- λͼID
/*		 CRect rect			---- ��MouseMoveʱ,���ݱ����λ��			
/*-----------------------------------------------------------
/* ���أ��ɹ����ذ�ťλ��   λͼID��Ч����-NULL
/*-----------------------------------------------------------
/* ע  ����DC������GetWindowDC()��� ����GetDC()
/************************************************************************/
CRect CDrawAppearance ::DrawBtnBmp(CDC *pWinDC, UINT unIDBmp, CRect rect)
{
	if (unIDBmp==0)
		return NULL;
	
	CDC		MemDC;
	BITMAP  bmSrc;
	CBitmap	Bitmap,*pOldBitmap;;
	CRect rtButton;
	CRect rtWnd;
	CRect rtTitle=GetTitleBarRect(pWinDC);						//��ñ���������

	MemDC.CreateCompatibleDC(pWinDC);							//��������DC

	Bitmap.LoadBitmap(unIDBmp);									//����λͼ
	Bitmap.GetBitmap(&bmSrc);									//���λͼ�ߴ�
	pOldBitmap=MemDC.SelectObject(&Bitmap);						//ѡ��DC

	GetWindowRect(pWinDC->GetWindow()->m_hWnd,&rtWnd);			//����Window���������Ļ�ľ��� 
	
	if (m_bRedrawWnd)											//��������ػ棬��Ҫ���¼��㰴ťλ��
	{
		if (bmSrc.bmHeight<rtTitle.Height())
		{	
			rtButton.left = rtTitle.right-bmSrc.bmWidth-m_wdSpace;	
			rtButton.right= rtTitle.right-m_wdSpace;
			rtButton.top  = rtTitle.top+(rtTitle.Height()-bmSrc.bmHeight)/2-2;
			rtButton.bottom = rtButton.top+bmSrc.bmHeight;		//���ð�ťλ��
		}
		else
		{	
			rtButton.bottom = rtTitle.bottom-3;					//����Ŀ��λͼ��С��λ��	
			rtButton.top  = rtTitle.top+1;						//��ʱ�Ϳ��Եõ�Ŀ��λͼ��
			
			int nW=bmSrc.bmWidth-(bmSrc.bmHeight-rtButton.Height()); //ԭλͼ��-��ԭλͼ��-Ŀ��λͼ�ߣ� = Ŀ��λͼ�� 
		 	
			rtButton.right = rtTitle.right-m_wdSpace;				
			rtButton.left  = rtTitle.right-nW-m_wdSpace;			 	
		}
	}
	else														//δ�����ػ棬ʹ�ñ��水ť��λ��
	{
		rect.OffsetRect(-rtWnd.left,-rtWnd.top);
		rtButton=rect;
	}
	
	if (bmSrc.bmHeight<rtTitle.Height())
		pWinDC->BitBlt(rtButton.left,rtButton.top,bmSrc.bmWidth,bmSrc.bmHeight,&MemDC,0,0,SRCCOPY);
	else
	{	
		pWinDC->SetStretchBltMode(HALFTONE);					//����ͼ��ƽ����ʾ
		pWinDC->StretchBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), &MemDC, 
			0, 0,bmSrc.bmWidth,bmSrc.bmHeight,SRCCOPY);	
	}
	
	m_wdSpace=rtTitle.right-rtButton.left+1;					//ÿ�μ���֮ǰλͼ�Ŀ�Ȳ�+1�ָ���ť

	MemDC.SelectObject(pOldBitmap);								//ѡ��ԭʼλͼ
	MemDC.DeleteDC();											//�ͷ�DC����Դ
	DeleteObject(&Bitmap);

	rtButton.OffsetRect(rtWnd.TopLeft());						//����rtButton�洢�ľ��ζ��ڴ��������
																//������Ҫ��������������Ļ��
	return rtButton;											
}

/************************************************************************/
/* ���ܣ��ػ���Ϣ�����ж���Ϣ���ͣ�������Ӧ�������д���
/*---------------------------------------------------------------------
/* ������UINT   msg			---- ָ����ǰ�ػ����Ϣ����
/*		 HWND   hWnd 		---- ���ھ����this->m_hWnd
/*		 CPoint point		---- ��Ϣ����ʱMouse����λ��
/*		 UINT   unIDClose	---- ��ͬ��ϢҪ���ݲ�ͬ��λͼ
/*		 UINT   unIDMax			 ����ƶ�ʱ�����ȵ��λͼ
/*		 UINT   unIDRestore	     ��갴��ʱ���ݰ��µ�λͼ
/*		 UINT   unIDMin			 4������Ĭ��ֵ �� 0
/*----------------------------------------------------------------------
/* ���أ�������ݵ���Ϣ��ȷ���� TRUE    ���� FALSE
/*----------------------------------------------------------------------
/* ע  ��msg �ɴ���MFC�ṩ�ı�׼��Ϣ�������Զ���			
/*		 
/*		 �������г��ĶԻ������Ϣ��Ӧ����Ӵ˺���
/************************************************************************/
BOOL CDrawAppearance ::InterceptMessage(UINT msg, HWND hWnd, CPoint point, UINT unIDClose, 
										UINT unIDMax, UINT unIDRestore, UINT unIDMin)
{	
	BOOL bResult=FALSE;
	m_bRedrawWnd=FALSE;
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		//
		LButtonUP(hWnd,point);
		break;
	case WM_NCMOUSEMOVE:
		//������Ƶ���ťʱ�����û������ť����
		//NcMouseMove(hWnd, point, unIDClose, unIDMax, unIDRestore, unIDMin);
		NcMouseMove1(hWnd, point, unIDClose, unIDMax, unIDRestore, unIDMin);
		break;
	case WM_NCLBUTTONDOWN:
		//bResult = NcLButtonDown(hWnd, point, unIDClose, unIDMax, unIDRestore, unIDMin);
		bResult = NcLButtonDown1(hWnd, point, unIDClose, unIDMax, unIDRestore, unIDMin);
		break;
	case WM_NCLBUTTONUP:
		bResult = NcLButtonUp(hWnd, point);
		break;
	case WM_NCLBUTTONDBLCLK:
		NcLButtonDblClk(hWnd, point);
		break;
	default:
		bResult = FALSE;
		break;
	}	

	m_wdSpace=0; //��0 ����Ӱ����һ�λ�ͼ

	return bResult;
}

/************************************************************************/
/*���ܣ�����LButtonDownʱ�İ�ťλͼ
/*------------------------------------------------
/*������ͬ��
/*------------------------------------------------		
/*���أ��������ڰ�ť���򷵻� TRUE  ���򷵻� FALSE (�ɵ���Ĭ�Ϻ�������)
/************************************************************************/
BOOL CDrawAppearance ::NcLButtonDown(HWND hWnd, CPoint point, UINT unIDClose, UINT unIDMax, UINT unIDRestore, UINT unIDMin)
{
	m_unIDMInDown = unIDMin;		//���水��ʱ��λͼ
	m_unIDClsDown = unIDClose;
	m_unIDMaxDown = unIDMax;
	m_unIDResDown = unIDRestore;

	CDC *pWinDC=CDC::FromHandle(GetWindowDC(hWnd));

	if (m_rtMaxBtn.PtInRect(point))	
	{	
		m_bDownMax = TRUE;
		if (IsZoomed(hWnd))
		{
			DrawBtnBmp (pWinDC, unIDRestore, m_rtMaxBtn);
		}
			
		else
			DrawBtnBmp (pWinDC, unIDMax, m_rtMaxBtn);					
	}
	else if (m_rtCloseBtn.PtInRect(point))	
	{
		m_bDownCls = TRUE;
		DrawBtnBmp (pWinDC, unIDClose, m_rtCloseBtn);
	}
	else if (m_rtMinBtn.PtInRect(point))
	{
		m_bDownMin = TRUE;
		DrawBtnBmp (pWinDC, unIDMin, m_rtMinBtn);
	}
	else	
		return FALSE;

	return TRUE;
}

BOOL CDrawAppearance ::NcLButtonDown1(HWND hWnd, CPoint point, UINT unIDClose, UINT unIDMax, UINT unIDRestore, UINT unIDMin)
{
	m_unIDMInDown = unIDMin;		//���水��ʱ��λͼ
	m_unIDClsDown = unIDClose;
	m_unIDMaxDown = unIDMax;
	m_unIDResDown = unIDRestore;
    
	CRect rtWnd;
	GetWindowRect(hWnd,&rtWnd);	

	//mouse����ת��Ϊ���������� ��Ҫ
	point.x = point.x - rtWnd.left;
	point.y = point.y - rtWnd.top;

	CDC *pWinDC=CDC::FromHandle(GetWindowDC(hWnd));

	if (m_rtMaxBtn.PtInRect(point))	
	{	
		m_bDownMax = TRUE;
		if (IsZoomed(hWnd))
		{
			DrawBtnBmp (pWinDC, unIDRestore, m_rtMaxBtn);
		}

		else
			DrawBtnBmp (pWinDC, unIDMax, m_rtMaxBtn);					
	}
	else if (m_rtCloseBtn.PtInRect(point))	
	{
		m_bDownCls = TRUE;
		DrawBtnBmp (pWinDC, unIDClose, m_rtCloseBtn);
	}
	else if (m_rtMinBtn.PtInRect(point))
	{
		m_bDownMin = TRUE;
		DrawBtnBmp (pWinDC, unIDMin, m_rtMinBtn);
	}
	else	
		return FALSE;

	return TRUE;
}


/************************************************************************/
/*���ܣ�˫������������ָ�����
/*------------------------------------------------
/*������ͬ��
/************************************************************************/
void CDrawAppearance ::NcLButtonDblClk(HWND hWnd, CPoint point)
{
	if  (IsZoomed(hWnd))
		SendMessage(hWnd,WM_SYSCOMMAND,SC_RESTORE,MAKELPARAM(point.x,point.y));
	else 
	{	
		SendMessage(hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,MAKELPARAM(point.x,point.y));									
	
		CRect rect;
		
		HWND hwTaskbar=FindWindow("Shell_TrayWnd","");		// ������������ھ��			
	
		GetWindowRect(hwTaskbar,&rect);			// ����������
		
		int nHeight=rect.Height();  			// �������ĸ߶�	
		
		GetWindowRect(hWnd,&rect);

		MoveWindow(hWnd,rect.left,rect.top,rect.Width(),rect.Height()-nHeight,TRUE);//�ı䴰�ڸ߶ȣ������ס������	
	};
}

/************************************************************************/
/*���ܣ�����ƶ�����ťλ�û����ȵ�λͼ,�����������״̬ʱλͼ
/*-----------------------------------------------------------
/*������ͬ��
/************************************************************************/
void CDrawAppearance ::NcMouseMove(HWND hWnd, CPoint point,UINT unIDClose, UINT unIDMax, UINT unIDRestore, UINT unIDMin)
{

	CDC *pWinDC= CDC::FromHandle(GetWindowDC(hWnd));			
	BOOL bDown = m_bDownMax || m_bDownMin || m_bDownCls;		// �ó��Ƿ��а�ť���ڰ���״̬
	 
	if ( m_rtMaxBtn.PtInRect(point) )
	{	
		if( bDown && !m_bDownMax )								// ������ڰ���״̬�������Ǵ˰�ť���أ����bDownΪFALSE˵
				return;											// ��û�а�ť�����£���ʱm_bDownMaxҲһ��������TRUE����ô
		 														// ���Ի����ȵ�״̬ʱ��λͼ������ͬ��
		if ( IsZoomed(hWnd) )	
		{	
			if (m_bDownMax)								
				DrawBtnBmp(pWinDC, m_unIDResDown, m_rtMaxBtn);    
			else
				DrawBtnBmp(pWinDC, unIDRestore, m_rtMaxBtn);
		}
		else
		{
			if (m_bDownMax)
				DrawBtnBmp(pWinDC, m_unIDMaxDown, m_rtMaxBtn); 
			else
				DrawBtnBmp(pWinDC, unIDMax, m_rtMaxBtn); 
		}
	}
	else
	{
		if (IsZoomed(hWnd))
			DrawBtnBmp(pWinDC, m_unIDResNor, m_rtMaxBtn);
		else
			DrawBtnBmp(pWinDC, m_unIDMaxNor, m_rtMaxBtn); 
	}
	

	if (m_rtCloseBtn.PtInRect(point))	
	{
		if( bDown && !m_bDownCls )
				return;
		if (m_bDownCls)
			DrawBtnBmp(pWinDC, m_unIDClsDown, m_rtCloseBtn);
		else
			DrawBtnBmp(pWinDC, unIDClose, m_rtCloseBtn);
	}
	else
		DrawBtnBmp(pWinDC, m_unIDClsNor, m_rtCloseBtn);


	if (m_rtMinBtn.PtInRect(point))
	{
		if( bDown && !m_bDownMin )
				return;
		if (m_bDownMin)
			DrawBtnBmp(pWinDC, m_unIDMInDown, m_rtMinBtn);
		else
			DrawBtnBmp(pWinDC, unIDMin, m_rtMinBtn);
	}
	else
		DrawBtnBmp(pWinDC,m_unIDMInNor, m_rtMinBtn);	
}

void CDrawAppearance::NcMouseMove1(HWND hWnd, CPoint point,UINT unIDClose, UINT unIDMax, UINT unIDRestore, UINT unIDMin) 
{
	CDC* pWinDC= CDC::FromHandle(GetWindowDC(hWnd));	
	
	CDC* pDisplayMemDC=new CDC;
	pDisplayMemDC->CreateCompatibleDC(pWinDC);
	CBitmap* pBitmap = new CBitmap;
	CBitmap* pOldBitmap;
	CRect rtWnd, rtButton;

	if (pWinDC)
	{
		CString StrTemp = "";
		GetWindowRect(hWnd,&rtWnd);	
		
		//mouse����ת��Ϊ���������� ��Ҫ
		point.x = point.x - rtWnd.left;
		point.y = point.y - rtWnd.top;
		//�ж�mouse�Ƿ��Ƶ�ϵͳ��ť��
		if (m_rtCloseBtn.PtInRect(point))
		{
			pBitmap->LoadBitmap(unIDClose);
			StrTemp = _T("�ر�");
		}
		else
		{
			if(m_rtMinBtn.PtInRect(point))
			{
				pBitmap->LoadBitmap(unIDMin);
				StrTemp = _T("��С������");
			}
			else
			{
				if(m_rtMaxBtn.PtInRect(point))
				{
					pBitmap->LoadBitmap(unIDMax);
					if(IsZoomed(hWnd))
					{
						StrTemp = _T("��ԭ����");
					}
					else
					{
						StrTemp = _T("��󴰿�");
					}
				}
				else
				{
					pBitmap->LoadBitmap(unIDRestore);
				}
			}
		}

		rtButton = m_rtMinBtn;
		BITMAP BmpInfo;
		pBitmap->GetBitmap(&BmpInfo);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pWinDC->BitBlt(rtButton.left, rtButton.top-6, BmpInfo.bmWidth, BmpInfo.bmHeight, pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();
		CRect ShowTipRec;
		ShowTipRec = m_rtMinBtn;
		//if(!StrTemp.IsEmpty())
		//{
		//	ScreenToClient(hWnd,&ShowTipRec);
		//	/*m_ToolTip.AddToolTip(IDD_TITLEBAR_DIALOG,&ShowTipRec,StrTemp);
		//	m_ToolTip.SetDelayTime(200);*/
		//}
	}

	pDisplayMemDC->DeleteDC();
	pWinDC->DeleteDC();
	delete pDisplayMemDC;
	delete pBitmap;
}


/************************************************************************/
/*���ܣ������ڷ�����Ӧ��Ϣ
/*------------------------------------------------
/*������ͬ��
/*------------------------------------------------		
/*���أ��������ڰ�ť���򷵻� TRUE  ���򷵻� FALSE (�ɵ���Ĭ�Ϻ�������)
/************************************************************************/
BOOL CDrawAppearance ::NcLButtonUp(HWND hWnd, CPoint point)
{
	BOOL bDown = m_bDownMax || m_bDownMin || m_bDownCls, bResult=TRUE;	//�ó��Ƿ��а�ť���ڰ���״̬
	
	if ( !bDown )	//û�з���
	{	return FALSE; }

	CRect rtWnd;
	GetWindowRect(hWnd,&rtWnd);	
	//mouse����ת��Ϊ���������� ��Ҫ
	point.x = point.x - rtWnd.left;
	point.y = point.y - rtWnd.top;
 
	CDC *pWinDC=CDC::FromHandle(GetWindowDC(hWnd));						
	
	if ( m_rtMaxBtn.PtInRect(point) && m_bDownMax)						//����ڰ�ť��Χ����֮ǰ�б�����
	{	
		if (IsZoomed(hWnd))
			SendMessage(hWnd,WM_SYSCOMMAND,SC_RESTORE,MAKELPARAM(point.x,point.y));
		else
		{	
			SendMessage(hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,MAKELPARAM(point.x,point.y));

			//CRect rtWnd;	
			//CRect rtTask;		
			//
			//HWND hwTaskbar=FindWindow(L"Shell_TrayWnd",L"");				//������������ھ��
			//
			//GetWindowRect(hwTaskbar,&rtTask);							//����������				
			//GetWindowRect(hWnd,&rtWnd);									//���ھ���				
			//TRACE("%d",rtTask.Height());
			////�ı䴰�ڸ߶ȣ������ס������
			//SetWindowPos(hWnd,NULL,0,0,rtWnd.Width(),rtWnd.Height()-rtTask.Height(),SWP_NOMOVE);	
		}
	}
	else if (m_rtCloseBtn.PtInRect(point) && m_bDownCls)
	{	
		SendMessage(hWnd,WM_CLOSE,0,0);
	}
	else if (m_rtMinBtn.PtInRect(point) && m_bDownMin)
	{	
		SendMessage(hWnd,WM_SYSCOMMAND,SC_MINIMIZE,MAKELPARAM(point.x,point.y));
	}
	else
		bResult=FALSE;

	m_bDownCls = FALSE;		//ȫ����Ϊ̧��״̬
	m_bDownMax = FALSE;
	m_bDownMin = FALSE;	
	return bResult;		
}

/************************************************************************/
/*���ܣ����̧��ʱ��ʾϵͳ��ťΪ̧��״̬
/*------------------------------------------------
/*������ͬ�ϡ����Դ���NULL ��Ҳ���Զ�����;��
/************************************************************************/
void CDrawAppearance::LButtonUP(HWND hWnd, CPoint point)
{
	m_bDownCls = FALSE;		//ȫ����Ϊ̧��״̬
	m_bDownMax = FALSE;
	m_bDownMin = FALSE;
}

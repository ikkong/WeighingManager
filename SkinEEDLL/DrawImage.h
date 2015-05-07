#ifndef _SKINEE_IMAGE_H
#define _SKINEE_IMAGE_H 

#include "SkinEEManager.h"

class DrawImage
{
public:
	 DrawImage()
	 {

	 }
	
	~DrawImage()
	{

	}
	
    //ImageList_V
	void Draw(HDC hDC,int nResImage,CRect rect,int nSub,int subWidth)
	{   
		Graphics graphics(hDC);
		Image *pImage = CSkinManager::GetInstance()->GetResItem(nResImage);
        if (pImage==NULL)
            return;

		int srcwidth=subWidth;
		int srcheight=pImage->GetHeight();
		int srcx=srcwidth*nSub;
		int srcy=0;

		RectF grect;
		grect.X=(Gdiplus::REAL)rect.left;
		grect.Y=(Gdiplus::REAL)rect.top;
		grect.Width = (Gdiplus::REAL)rect.Width();
		grect.Height = (Gdiplus::REAL)rect.Height();
		graphics.DrawImage(pImage, grect, srcx,srcy,srcwidth,srcheight, UnitPixel);
	}

	void Draw(HDC hDC,int nResImage,CRect rect)
	{
		RectF grect;
		grect.X=(Gdiplus::REAL)rect.left;
		grect.Y=(Gdiplus::REAL)rect.top;
		grect.Width = (Gdiplus::REAL)rect.Width();
		grect.Height = (Gdiplus::REAL)rect.Height();

		Graphics graphics( hDC );
		Image *pImage = CSkinManager::GetInstance()->GetResItem(nResImage);
		graphics.DrawImage(pImage,grect ,0,0,pImage->GetWidth(),pImage->GetHeight(),UnitPixel);
	}

    void Draw(CDC *pWinDC,int nResImage,CRect rect,int srcx,int srcy,int srcwidth,int srcheight)
    {    
        Graphics graphics( pWinDC->m_hDC );
        Image *pImage = CSkinManager::GetInstance()->GetResItem(nResImage);
      
        int a=pImage->GetWidth();
        RectF grect;
        grect.X=(Gdiplus::REAL)rect.left;
        grect.Y=(Gdiplus::REAL)rect.top;
        grect.Width = (Gdiplus::REAL)rect.Width();
        grect.Height = (Gdiplus::REAL)rect.Height();
        graphics.DrawImage(pImage, grect, srcx,srcy,srcwidth,srcheight, UnitPixel);
    }

	BOOL DrawBackground(HDC hDC, CRect rect, COLORREF clrBrush, UINT nResImage
		/*BOOL bCenter,BOOL bTransparent,COLORREF clrTransparent*/)	
	{
		BOOL bSet=FALSE;									//����ֵ		

		Graphics graphics(hDC);
		Image *pImage = CSkinManager::GetInstance()->GetResItem(nResImage);

		if (clrBrush!=NULL)									//���ñ�����ˢ
		{	
			SolidBrush brush(clrBrush);	
			graphics.FillRectangle(&brush,rect.left,rect.top,rect.Width(),rect.Height());
		}	
		if (pImage!=NULL)								    //���ñ���λͼ
		{
			RectF grect;
			grect.X=(Gdiplus::REAL)rect.left;
			grect.Y=(Gdiplus::REAL)rect.top;
			grect.Width = (Gdiplus::REAL)rect.Width();
			grect.Height = (Gdiplus::REAL)rect.Height();

			graphics.DrawImage(pImage, grect);
		}					
		return bSet;
	}

	void  DrawString(HDC hDC,TCHAR* text,PointF pointf ,Color color,int size,int style=FontStyleRegular)
	{
		Graphics graphics(hDC);

		SolidBrush brush(color);//����һ����ˢ ��һ����͸���� ��������RGBֵColor(100,0,0,255)
		FontFamily fontFamily(L"Arial");//ѡ��һ������
		Font font(&fontFamily,size,style,UnitPixel);
		StringFormat stringformat;  
		stringformat.SetAlignment(StringAlignmentCenter);  

		graphics.DrawString(text,-1,&font,pointf, &stringformat,&brush);
	}

    void  DrawString(CDC *pWinDC,TCHAR* string,Font* font1,PointF pointF,Color color)
    {
        Graphics graphics( pWinDC->m_hDC );

        //---------------------------------------   
        // fontFamily��һ����������������   
        // ���塢���塢���Ρ����塢�����Լ���Բ�ȶ�������   
        // �ر�˵��:Gdi+��֧��OpenType���壬����һ�ο���   
        //---------------------------------------   
        FontFamily fontFamily(L"��Բ");   

        //---------------------------------------   
        // font�ĸ��������ڶ���������߶ȣ���λ�ɵ��ĸ�����   
        // ��������������:   
        //  FontStyleRegular(����)��   
        //  FontStyleBold(�Ӵ�)��   
        //  FontStyleItalic(б��)��   
        //  FontStyleBoldItalic (��б��)��   
        //  FontStyleUnderline(�»���)   
        //  FontStyleStrikeout(ɾ����)   
        // ���ĸ�:UnitDisplay(1/75Ӣ��)��   
        //  UnitPixel(����)��   
        //  UnitPoint(��)��һ��Լ�ۺ�Ϊ1/72Ӣ��   
        //  UnitInch(Ӣ��)��   
        //  UnitDocument(1/300Ӣ��)��   
        //  UnitMillimeter(����)   
        //---------------------------------------   
        Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel); 

        //---------------------------------------   
        // ����Ϊ�˺���ǰ��GDI����   
        // font��������:   
        //  HDC�� LOGFONT   
        //---------------------------------------   
        LOGFONT lf;  
        ::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT), sizeof(lf), &lf);  
        memcpy(lf.lfFaceName, "Arial", 5) ;  
        lf.lfHeight = 13 ;  

        Gdiplus::Font Gdi_font(pWinDC->GetSafeHdc(), &lf);  

        //-----------------------------------------   
        //stringformat��Ҫ�����µĺ����������ı�����ʾ��ʽ   
        // SetAlignment   
        //-----------------------------------------   
        StringFormat stringformat;  

        //-----------------------------------------   
        //  StringAlignmentNear(�������Ҷ��룬ȡ������д�����Ǵ����һ��Ǵ��ҵ���)��   
        //  StringAlignmentCenter(ˮƽ����)   
        //  StringAlignmentFar(���˶���)��   
        //  Ĭ�϶���Ӱ�촹ֱ   
        //-----------------------------------------   
        stringformat.SetAlignment(StringAlignmentCenter);  

        //-----------------------------------------   
        // ��SetAlignment��Ӧ��Ϊ��ֱ������   
        //-----------------------------------------   
        stringformat.SetLineAlignment(StringAlignmentCenter);  

        //------------------------------------------   
        // SolidBrush   
        // HatchBrush(��Ӱ��ˢ)   
        // TextureBrush(����ˢ):ʹ��ͼ���������״���ڲ����޷��̳д���   
        // LinearGradientBrush(���仭ˢ)   
        // ע�⣬�õ���Color��ʼ������Ҫ��RGB��ʼ�������ᱨ�����治������   
        //------------------------------------------   
        SolidBrush brush(Color(255, 255, 0, 0));  

        //------------------------------------------   
        // SetTextRenderingHint�����ı����������   
        //------------------------------------------   
        graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);  


        //------------------------------------------   
        // һ����point ,һ����rect�������   
        //------------------------------------------   
        CRect rcClient ;  
        //GetClientRect(rcClient);  

        graphics.DrawString(TEXT("1234"), -1, &font,  
            RectF(0, 0, rcClient.Width(), rcClient.Height()), &stringformat, &brush); 
    }

	void GetImageRect(int nResImage,CRect& rect)
	{
		Image *pImage = CSkinManager::GetInstance()->GetResItem(nResImage);
	    rect.SetRect(0,0,pImage->GetWidth(),pImage->GetHeight());
	}

    void GetImageColor(int nResImage,Color* color)
    {
        Bitmap *pImage = (Bitmap*)CSkinManager::GetInstance()->GetResItem(nResImage);
        //ColorPalette Palette;
        pImage->GetPixel(5,5,color);
    }


	//---------------------------------------------GDI------------------------------------------
	 void Draw(CDC *pWinDC,CString strImage,CRect rect)
	 {
		 CBitmap bmpObj,*OldObj;
		 BITMAPINFO bitinfo;
		 CDC memDC;
		 memDC.CreateCompatibleDC(NULL);

		 HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL,
			 strImage,
			 IMAGE_BITMAP,
				0,
				0,
				LR_LOADFROMFILE);

		 bmpObj.Attach(hBitmap);
		 bmpObj.GetObject(sizeof(bitinfo),&bitinfo);//��ȡλͼ��С
		 OldObj = memDC.SelectObject(&bmpObj);
		 int x = bitinfo.bmiHeader.biWidth;
		 int y = bitinfo.bmiHeader.biHeight;
		 pWinDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC,0,0,x,y,SRCCOPY);
         int a=rect.Width();
		 memDC.SelectObject(OldObj);
		 bmpObj.DeleteObject();
		 memDC.DeleteDC();	
	 }

     void GetImageRect(CString strImage,CRect& rect)
     {
         CBitmap bmpObj;
         BITMAPINFO bitinfo;

         rect.SetRect(0,0,0,0);
         HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL,
             strImage,
             IMAGE_BITMAP,
             0,
             0,
             LR_LOADFROMFILE);

         bmpObj.Attach(hBitmap);
         bmpObj.GetObject(sizeof(bitinfo),&bitinfo);//��ȡλͼ��С
         rect.right = bitinfo.bmiHeader.biWidth;
         rect.bottom = bitinfo.bmiHeader.biHeight;
         bmpObj.DeleteObject();
     }

	 void  DrawString(CDC *pWinDC,TCHAR* text,CRect rect ,Color color=(200,255,255,0),Font* font1=NULL)
	 {
		 pWinDC->SetBkMode(TRANSPARENT);
		 pWinDC->SetTextColor(RGB(255,255,0));
		 pWinDC->SetTextAlign(TA_CENTER);

		 //pWinDC->SelectObject(&m_CaptionFont);
		 pWinDC->TextOut(rect.Width(), rect.Height() ,text);
	
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
     BOOL DrawBackground(CDC *pWinDC, CRect *pDesRect, COLORREF clrBrush, UINT unIDBitmap,
         BOOL bCenter,BOOL bTransparent,COLORREF clrTransparent)	
     {
         BOOL bSet=FALSE;									//����ֵ		
         if (pWinDC==NULL && !IsWindow(pWinDC->GetWindow()->m_hWnd))
         {	AfxMessageBox(L"��Ч��DC,�򴰿ڲ����ڣ�",MB_ICONASTERISK);
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
                 AfxMessageBox(L"Load bitmap failure!\r\rThe bitmap exist?",MB_ICONERROR|MB_OK);
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
};

#endif//
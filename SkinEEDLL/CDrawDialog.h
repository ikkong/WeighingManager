#ifndef _CDRAWDIALOG_H
#define _CDRAWDIALOG_H

#include "ResDefine.h"
#include "DrawImage.h"
#include "until.h"
//����Ի�����
enum CButtonState{bsNone,bsIni,bsMin,bsMax,bsRes,bsClose};

#define fLeftBand     1
#define fLeftTitle    2
#define fRightTitle   4
#define fMidTitle     8
#define fRightBand    16
#define fBottomBand   32
#define fLeftBottom   64
#define fRightBottom  128
#define fMinButton    256
#define fMaxButton    512
#define fCloseButton  1024
#define fAll          2047

class CDrawDialog
{
public:
    WNDPROC     m_OldProc;         //��¼���ں���
    int         m_Flag; 
    CButtonState m_ButtonState;		//��ť״̬
    BOOL      m_IsMax;				//�Ƿ������״̬
	CRect     m_IniRect, m_MinRect, m_MaxRect, m_CloseRect, m_rtIcon; //��������ť����ʾ����
    CRect     m_LTitleRc, m_MTitleRc,m_RTitleRc;         //�����,�м����,�ұ�����ʾ����
    CRect     m_LBandRc, m_BBandRc,m_RBandRc;         //��߿�,�ױ߿�,�ұ߿�����
    BOOL      m_IsDrawForm;		//�Ƿ���Ҫ���ƴ���
    int       m_TitleDrawHeight;	//������ʵ�ʵĻ��Ƹ߶�
    int       m_BorderWidth;		//�߿���
    int       m_BorderHeight;		//�߿�߶�
    int       m_FrameWidth ;		//����3D���
    int       m_FrameHeight;		//����3D�߶�
    int       m_CaptionHeight;		//�������ĸ߶�
    CString   m_Caption;			//���ڱ���
    COLORREF  m_CapitonColor;		//����������ɫ
    CFont     m_CaptionFont;		//��������
    int       m_ButtonWidth;		//��ťλͼ���
    int       m_ButtonHeight;		//��ťλͼ�߶�
    CRgn      WndRgn,ClipRgn;		//������ʾ�ͼ�������
    TCHAR     m_Text[MAX_PATH];		//��¼�ؼ��ı�
    BOOL	  m_bGetText;			//�Ƿ��Ѿ���ȡ���ı�
    int       m_linewidth;         //����߿��3D���
    CRect     m_FactRC;
    BOOL	  m_bHaveMaxBox;
    BOOL	  m_bHaveMinBox;
    Color     m_bgColor;
    CBrush    m_brush;
    DrawImage m_DrawObj;
    int       m_type;

public:
    CDrawDialog()
    {
        m_IsMax = TRUE;
        m_OldProc = NULL;
        m_Flag    = 0;
        m_bGetText = FALSE;
        m_CapitonColor = RGB(255,255,0);
        m_ButtonWidth = 16;
        m_ButtonHeight = 16;
        m_bHaveMaxBox =FALSE;
        m_bHaveMinBox = FALSE;

        m_FrameHeight= GetSystemMetrics(SM_CYFIXEDFRAME);
        m_BorderHeight = GetSystemMetrics(SM_CYBORDER);
        m_FrameWidth= GetSystemMetrics(SM_CXFIXEDFRAME);
        m_BorderWidth = GetSystemMetrics(SM_CXBORDER);
        m_CaptionHeight = GetSystemMetrics(SM_CYCAPTION);
        m_linewidth =  m_FrameWidth+m_BorderWidth;
    }
    CDrawDialog(HWND hWnd)
    {
        m_IsMax = TRUE;
        m_OldProc = NULL;
        m_Flag    = 0;
        m_bGetText = FALSE;
        m_CapitonColor = RGB(255,255,0);
        m_ButtonWidth = 16;
        m_ButtonHeight = 16;
        m_bHaveMaxBox =FALSE;
        m_bHaveMinBox = FALSE;

        m_FrameHeight= GetSystemMetrics(SM_CYFIXEDFRAME);
        m_BorderHeight = GetSystemMetrics(SM_CYBORDER);
        m_FrameWidth= GetSystemMetrics(SM_CXFIXEDFRAME);
        m_BorderWidth = GetSystemMetrics(SM_CXBORDER);
        m_CaptionHeight = GetSystemMetrics(SM_CYCAPTION);
        m_linewidth =  m_FrameWidth+m_BorderWidth;

        GetWindowText(hWnd,m_Text,MAX_PATH);
        SetWindowText(hWnd,_T(""));

        DWORD dwStyle = (DWORD)GetWindowLong(hWnd, GWL_STYLE);
        if (dwStyle&WS_MAXIMIZEBOX)
            m_bHaveMaxBox = TRUE;
        if (dwStyle&WS_MINIMIZEBOX)
            m_bHaveMinBox = TRUE;

        CWnd *pWnd = CWnd::FromHandle( hWnd );
        pWnd->ModifyStyle(WS_SYSMENU,0,0);

        //dwStyle = pWnd->GetStyle();//��ȡ����ʽ
        //DWORD dwNewStyle = WS_CAPTION|WS_OVERLAPPED | WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
        //dwNewStyle&=dwStyle;//��λ�뽫����ʽȥ��
        //SetWindowLong(hWnd,GWL_STYLE,dwNewStyle);//���ó��µ���ʽ
        //DWORD dwExStyle = pWnd->GetExStyle();//��ȡ����չ��ʽ
        //DWORD dwNewExStyle = WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR;
        //dwNewExStyle&=dwExStyle;//��λ�뽫����չ��ʽȥ��
        //SetWindowLong(hWnd,GWL_EXSTYLE,dwNewExStyle);//�����µ���չ��ʽ
        //pWnd->SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED);//����windows���ҵ���ʽ�ı��ˣ�����λ�úʹ�С����ԭ�����䣡
        
        //SetWindowStyle(hWnd);
    }

    void SetWindowStyle(HWND hWnd)
    {
        typedef HRESULT (WINAPI *PFUN_SetWindowTheme)(HWND, LPCWSTR, LPCWSTR);
        typedef HRESULT (WINAPI * TmpFun)(HWND,DWORD,LPCVOID,DWORD);

        HINSTANCE hInst = LoadLibrary(_T("UxTheme.dll"));
        if (hInst)
        {
            PFUN_SetWindowTheme pFun = (PFUN_SetWindowTheme)GetProcAddress(hInst, "SetWindowTheme");
            if (pFun)
                pFun(hWnd, L"", L"");        //ȥ��xp����
            FreeLibrary(hInst);
        }

        hInst = LoadLibrary(_T("dwmapi.dll"));
        if (hInst)
        {
            TmpFun DwmSetWindowAttributeEX = (TmpFun)::GetProcAddress(hInst, "DwmSetWindowAttribute");
            if (DwmSetWindowAttributeEX)
            {
                DWORD dwAttr = 1;
                DwmSetWindowAttributeEX(hWnd, 2, &dwAttr, 4);    //ȥ��vista��Ч
            }
            FreeLibrary(hInst);
        }
    }

    void OnNcPaint(HWND hWnd, WPARAM wParam, LPARAM lParam) 
    {
        HDC hDC = GetWindowDC(hWnd);

        Calculate(hWnd);
        DrawTitle(hDC);
        DrawBorder(hDC);
        DrawDialogText(hWnd,hDC);
        DrawNcButton(hDC);
		DrawIcon(hDC);
        ReleaseDC(hWnd,hDC);
    }

    BOOL OnEraseBkgnd(HWND hWnd,WPARAM wParam,  LPARAM lParam)
    {
        CRect rect;
        GetClientRect(hWnd,rect);
        //m_DrawObj.DrawBackground(cDC,&rect,COLORREF(RGB(229,246,234)),0,TRUE,TRUE,COLORREF(RGB(0,0,0)));
        //����GDI+���ܱȽϲ�
        m_DrawObj.DrawBackground((HDC)wParam, rect, COLORREF(RGB(229,246,234)), ID_WINDOW_BACKGROUND/*,TRUE,TRUE,COLORREF(RGB(0,0,0))*/);
        return TRUE;
    }

    void OnSize(HWND hWnd,UINT nType, LPARAM lParam) 
    {
        SetDlgZone(hWnd);
    }

    void OnNCCalSize(HWND hWnd,WPARAM wParam, LPARAM lParam) 
    { 
            NCCALCSIZE_PARAMS * hh=(NCCALCSIZE_PARAMS* )lParam;
           
            if (m_type>=m_linewidth)
            {
                hh->rgrc[0].left-=m_linewidth;
                hh->rgrc[0].right+=m_linewidth;
                hh->rgrc[0].bottom+=m_linewidth;
            }
            else
            {
               hh->rgrc[0].top+=m_linewidth;
            }
    }

    void SetDlgZone(HWND hWnd)
    {
        CRect winrect,factRC;
        GetWindowRect(hWnd,winrect);
        factRC.CopyRect(CRect(0,0,winrect.Width(),winrect.Height()));
        WndRgn.DeleteObject();
        //���������������ĸ��Ǽ�������
        WndRgn.CreateRectRgnIndirect(factRC);
        SetWindowRgn(hWnd,WndRgn,TRUE);
        DeleteObject(WndRgn);
    }

    BOOL OnNcActivate(HWND hWnd,BOOL bActive) 
    {	
        return TRUE;
    }

    LRESULT OnCtlColor(HWND hWnd, WPARAM wParam,  LPARAM lParam) 
    { 
        //CDC dc;  
        //dc.Attach((HDC)wParam);  // ֻ������Ч������   
        //dc.Detach();
        //TextureBrush b(CSkinManager::GetInstance()->GetResItem(ID_WINDOW_BACKGROUND), WrapModeTile);
        return (long)(HBRUSH)m_brush;
    }

    void OnNcLButtonDown( HWND hWnd, UINT nHitTest, LPARAM lParam) 
    {
        CPoint pt;
        pt.x = (int)(short)LOWORD(lParam);
        pt.y = (int)(short)HIWORD(lParam)+m_CaptionHeight;
		ScreenToClient(hWnd, &pt);
		if (m_rtIcon.PtInRect(pt))
		{
			SendMessage(hWnd, WM_APP + 1, 0, lParam);
		}

        switch (m_ButtonState)
        {
        case bsClose: 
            SendMessage(hWnd,WM_CLOSE,0,0);				
            break;
        case bsMin: 
            ShowWindow(hWnd,SW_SHOWMINIMIZED);
            break;
        case bsMax:
            m_ButtonState = bsMax;
            ShowWindow(hWnd,SW_SHOWMAXIMIZED);
            m_IsMax = FALSE;
            break;
        case bsRes:		
            ShowWindow(hWnd,SW_RESTORE);
            m_IsMax = TRUE;
            break;
        }
    }

    void OnNcMouseMove(HWND hWnd,UINT nHitTest,LPARAM lParam) 
    {
        CRect WinRect;
        HDC hWndDC = GetWindowDC(hWnd);
        GetWindowRect(hWnd,WinRect);
        CPoint point=CPoint(LOWORD(lParam),HIWORD(lParam));
        point.Offset(-WinRect.left,-WinRect.top);//ƽ���豸����

        if((m_MinRect.PtInRect(point))&&m_bHaveMinBox) //�������С����ť���ƶ�ʱ,���İ�ť��ʾ��λͼ
        {
            if (m_ButtonState!= bsMin)
            {
                m_DrawObj.Draw(hWndDC,ID_WINDOW_SYSBTN,m_MinRect,1,16);
                m_ButtonState = bsMin;
            }
        }
        else if ((m_MaxRect.PtInRect(point))&&m_bHaveMaxBox)
        {
            if (m_ButtonState !=bsMax && m_ButtonState!=bsRes)
            {
                m_DrawObj.Draw(hWndDC,ID_WINDOW_SYSBTN,m_MaxRect,3,16);
                if (m_IsMax)
                    m_ButtonState = bsMax;
                else
                    m_ButtonState = bsRes;	
            }
        }
        else if (m_CloseRect.PtInRect(point))
        {
            if (m_ButtonState != bsClose)
            {
                m_DrawObj.Draw(hWndDC,ID_WINDOW_SYSBTN,m_CloseRect,5,16);
                m_ButtonState = bsClose;
            }
        }
        else
        {		
            if (m_ButtonState==bsMin)
                DrawNcButton(hWndDC, fMinButton);
            else if (m_ButtonState==bsClose)
                DrawNcButton(hWndDC, fCloseButton);
            else if (m_ButtonState==bsMax||m_ButtonState==bsRes)
                DrawNcButton(hWndDC, fMaxButton);
            m_ButtonState = bsNone;
        }
        ::ReleaseDC(hWnd,hWndDC);		
    }

    LRESULT OnNcHittest(HWND hWnd, WPARAM wParam,  LPARAM lParam)
    {
        CPoint pt(LOWORD(lParam),HIWORD(lParam));
        CRect rect;
        GetClientRect(hWnd,&rect);
        ScreenToClient(hWnd,&pt);
        static int nFrame = 4; // ���ڱ߿�Ŀ��
        rect.DeflateRect(nFrame,nFrame);
        CRect RectResize(rect.right - 20, rect.bottom - 20, rect.right, rect.bottom);
        CRect rectTitle(nFrame,nFrame, rect.right - nFrame,m_TitleDrawHeight);
        if (!rect.PtInRect(pt))
        {
            if (pt.x <= nFrame && pt.y >= rect.bottom - nFrame)
            {
                return HTBOTTOMLEFT;
            }
            else if (pt.x <= nFrame && pt.y <= nFrame-rectTitle.Height())
            {
                return HTTOPLEFT;
            }
            else if (pt.x >= rect.right - nFrame && pt.y <= nFrame-rectTitle.Height())
            {
                return HTTOPRIGHT;
            }
            else if (pt.x >= rect.right - nFrame && pt.y >= rect.bottom-nFrame)
            {
                return HTBOTTOMRIGHT;
            }
            else if (pt.x <= nFrame)
            {
                return HTLEFT;
            }
            else if (pt.y <= nFrame-rectTitle.Height())
            {
                return HTTOP;
            }
            else if (pt.y >= rect.bottom - nFrame)
            {
                return HTBOTTOM;
            }
            else if (pt.x >= rect.right+nFrame)
            {
                return HTRIGHT;
            }
        }
        else if (RectResize.PtInRect(pt))
        {
            return HTBOTTOMRIGHT;
        }
        else if (rectTitle.PtInRect(pt))
        {
            return HTCAPTION;
        }
        else
        {
            return HTCLIENT;
        }
    }

    void OnCreate(HWND hWnd,WPARAM wParam, LPARAM lParam)
    {
        CRect rc1,rc2;
        GetWindowRect(hWnd,&rc1);
        GetClientRect(hWnd,&rc2);
        m_type = (rc1.Width()-rc2.Width())/2;

        OnChangeSkin(); 
    }

    void Calculate(HWND hWnd)
    {
        CRect rect;
        CPoint pos;

        CRect WinRC;
        GetWindowRect(hWnd,WinRC);
        m_FactRC.CopyRect(CRect(0,0,WinRC.Width(),WinRC.Height()));

        m_DrawObj.GetImageRect(ID_WINDOW_LEFTTITLE,rect);
        m_TitleDrawHeight = (m_CaptionHeight+4>rect.bottom)?m_CaptionHeight+4:rect.bottom;
        m_LTitleRc.CopyRect(CRect(0,0,rect.right,m_TitleDrawHeight));

        m_DrawObj.GetImageRect(ID_WINDOW_RIGHTTITLE,rect);
        m_RTitleRc.CopyRect(CRect((m_FactRC.right- rect.right),0,m_FactRC.right,m_TitleDrawHeight));
        m_MTitleRc.CopyRect(CRect(m_LTitleRc.right,0,m_RTitleRc.left+2*m_BorderWidth,m_TitleDrawHeight));

        m_LBandRc.SetRect(0,m_TitleDrawHeight,m_linewidth,m_FactRC.Height()-m_linewidth);
        m_RBandRc.SetRect(m_FactRC.right-m_linewidth,m_TitleDrawHeight,m_FactRC.right,m_FactRC.Height()-m_linewidth);
        m_BBandRc.SetRect(0,m_FactRC.Height()-m_linewidth,m_FactRC.right, m_FactRC.Height());

        pos.SetPoint(30,1);
        m_MinRect.CopyRect(CRect(m_RTitleRc.left+pos.x,(m_TitleDrawHeight+2*m_BorderHeight -m_ButtonHeight)/2+pos.y,m_RTitleRc.left+pos.x+m_ButtonWidth,(m_TitleDrawHeight+2*m_BorderHeight +m_ButtonHeight)/2+pos.y));
        pos.x = 55;	
        m_MaxRect.CopyRect(CRect(m_RTitleRc.left+pos.x,(m_TitleDrawHeight+2*m_BorderHeight -m_ButtonHeight)/2+pos.y,m_RTitleRc.left+pos.x+m_ButtonWidth,(m_TitleDrawHeight+2*m_BorderHeight +m_ButtonHeight)/2+pos.y));
        pos.x = 80;
        m_CloseRect.CopyRect(CRect(m_RTitleRc.left+pos.x,(m_TitleDrawHeight+2*m_BorderHeight -m_ButtonHeight)/2+pos.y,m_RTitleRc.left+pos.x+m_ButtonWidth,(m_TitleDrawHeight+2*m_BorderHeight +m_ButtonHeight)/2+pos.y));
    
		m_rtIcon.SetRect(2, 2, m_LTitleRc.bottom - 3, m_LTitleRc.bottom-3);
	}

    void OnChangeSkin()
    {
        m_DrawObj.GetImageColor(ID_WINDOW_BACKGROUND,&m_bgColor);
        m_brush.DeleteObject();  
        m_brush.CreateSolidBrush(RGB(m_bgColor.GetR(),m_bgColor.GetG(),m_bgColor.GetB()));
    }

    void DrawTitle(HDC hDC,UINT Flags =fAll)
    {
        if ( Flags & fLeftTitle)
            m_DrawObj.Draw(hDC,ID_WINDOW_LEFTTITLE,m_LTitleRc);

        if ( Flags & fRightTitle)
            m_DrawObj.Draw(hDC,ID_WINDOW_RIGHTTITLE,m_RTitleRc);	

        if ( Flags & fMidTitle)
            m_DrawObj.Draw(hDC,ID_WINDOW_MINDTITLE,m_MTitleRc);
    }

    void DrawBorder(HDC hDC,UINT Flags =fAll)
    {
        if ( Flags & fLeftBand )
            m_DrawObj.Draw(hDC,ID_WINDOW_LEFTBAND,m_LBandRc);
        if ( Flags & fRightBand)
            m_DrawObj.Draw(hDC,ID_WINDOW_RIGHTBAND,m_RBandRc);

        if ( Flags & fBottomBand)
            m_DrawObj.Draw(hDC,ID_WINDOW_BOTTOMBAND,m_BBandRc);
    }

    void DrawDialogText(HWND hWnd,HDC hDC)
    {
        //m_DrawObj.DrawString(pDC,m_Text,CRect(0,0,m_FactRC.Width()/2, m_CaptionHeight/3));//GDI
        m_DrawObj.DrawString(hDC,m_Text,PointF(m_FactRC.Width()/2, m_CaptionHeight/3),Color(255,255,255,0),14,FontStyleBold);//GDI+
    }

    void DrawNcButton(HDC hDC,UINT Flags =fAll)
    {
        if ( (Flags & fMinButton)&&m_bHaveMinBox)
            m_DrawObj.Draw(hDC,ID_WINDOW_SYSBTN,m_MinRect,0,16);

        if ( (Flags & fMaxButton)&&m_bHaveMaxBox) 
            m_DrawObj.Draw(hDC,ID_WINDOW_SYSBTN,m_MaxRect,2,16);

        if ( Flags & fCloseButton)
            m_DrawObj.Draw(hDC,ID_WINDOW_SYSBTN,m_CloseRect,4,16); 
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
	BOOL DrawIcon(HDC hDC)
	{
		m_DrawObj.Draw(hDC, ID_WINDOW_APP, m_rtIcon);
		return TRUE;
	}

    //���ں���
    static LRESULT CALLBACK DialogWndProc(HWND hWnd, UINT uMsg, WPARAM wParam,  LPARAM lParam)
    {
        CDrawDialog *pDlg=(CDrawDialog*)GetWindowLong(hWnd,GWL_USERDATA);
        PAINTSTRUCT ps;
        switch (uMsg)
        {
        case WM_NCPAINT: 
            {
                TRACE("%S ���ڷ���WM_NCPAINT\n",pDlg->m_Text);
                pDlg->OnNcPaint(hWnd, wParam, lParam);
                return 0;
            }

        case WM_CTLCOLORDLG:
            {
                TRACE("%S ���ڷ���WM_CTLCOLORDLG\n",pDlg->m_Text);
                return pDlg->OnCtlColor(hWnd, wParam, lParam);
                break;
            }

        case WM_NCACTIVATE : 
            {
                TRACE("%S ���ڷ���WM_NCACTIVATE\n",pDlg->m_Text);
               //::InvalidateRgn(hWnd,(HRGN)lParam,TRUE);
                return 1;
            }

        case WM_NCMOUSEMOVE: 
            {
                TRACE("%S ���ڷ���WM_NCMOUSEMOVE\n",pDlg->m_Text);
                pDlg->OnNcMouseMove(hWnd,wParam,lParam);
                break;
            }

        case WM_NCLBUTTONDOWN: 
            {
                TRACE("%S ���ڷ���WM_NCLBUTTONDOWN\n",pDlg->m_Text);
                pDlg->OnNcLButtonDown(hWnd,wParam,lParam);
                break;
            }
        case WM_NCLBUTTONUP: 
            {
                TRACE("%S ���ڷ���WM_NCLBUTTONDOWN\n",pDlg->m_Text);
                break;
            }

        case WM_NCHITTEST: 
            {
                TRACE("%S ���ڷ���WM_NCMOUSEMOVE\n",pDlg->m_Text);
                //return pDlg->OnNcHittest(hWnd,wParam,lParam);
                break;
            }

        case WM_SIZE: 
            {
                TRACE("%S ���ڷ���WM_SIZE\n",pDlg->m_Text);
                pDlg->OnSize(hWnd,wParam,lParam);
                break;
            }
        case WM_NCCALCSIZE://����ͻ����ķ����ѷ���
            {
                TRACE("%S ���ڷ���WM_NCCALCSIZE\n",pDlg->m_Text);
                pDlg->OnNCCalSize(hWnd,wParam,lParam);
                break;
            }

        case WM_CHANGESKIN:
            {
                TRACE("%S ���ڷ���WM_CREATE\n",pDlg->m_Text);
                pDlg->OnChangeSkin();
                pDlg->OnNcPaint(hWnd, wParam, lParam);
                ::InvalidateRect(hWnd,NULL,TRUE);
                break;
            }

        case WM_CREATE:
            {
                TRACE("%S ���ڷ���WM_CREATE\n",pDlg->m_Text);
                pDlg->OnCreate(hWnd, wParam, lParam);
                break;
            }

        case WM_DESTROY:
            {
                TRACE("%S ���ڷ���WM_DESTROY\n",pDlg->m_Text);
                SetWindowLong(hWnd,GWL_WNDPROC,(long)pDlg->m_OldProc);
                delete pDlg;
				return 0;
               // break;
            }

        default :
            break;	
        }
        return CallWindowProc(pDlg->m_OldProc,hWnd,uMsg,wParam,lParam);
    }
};

#endif//
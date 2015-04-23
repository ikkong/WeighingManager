
// WeighingManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WeighingManager.h"
#include "WeighingManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWeighingManagerDlg �Ի���



CWeighingManagerDlg::CWeighingManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWeighingManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_BKColor = RGB(165, 201, 235);
	m_BKBrush.CreateSolidBrush(RGB(160, 200, 235));
}

void CWeighingManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWeighingManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCPAINT()
	ON_WM_CTLCOLOR()
	//ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CWeighingManagerDlg ��Ϣ�������

BOOL CWeighingManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	theApp.serialPort1.InitPort(this);

	InitImageList();
	InitToolBar();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWeighingManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWeighingManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWeighingManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWeighingManagerDlg::InitImageList()
{
	m_ImageListToolbar.Create(48, 48, ILC_COLOR24 | ILC_MASK, 1, 1);
	m_ImageListToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_ImageListToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_ImageListToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	m_ImageListToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON7));

	m_ImageListHotToolbar.Create(48, 48, ILC_COLOR24 | ILC_MASK, 1, 1);
	m_ImageListHotToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_ImageListHotToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_ImageListHotToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	m_ImageListHotToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON7));

}

BOOL CWeighingManagerDlg::InitToolBar()
{
	UINT array[8];
	array[0] = IDC_TOOLBAR_BUTTON1;//¼����ѯ
	array[1] = IDC_TOOLBAR_BUTTON2;//ϵͳ���ò���
	array[2] = IDC_TOOLBAR_BUTTON3;//ͨ������
	array[3] = IDC_TOOLBAR_BUTTON4;//�û�����

	m_ToolBar.Create(this);
	m_ToolBar.SetButtons(array, 4);

	m_ToolBar.SetButtonText(0, _T("�Զ�ʶ��"));
	m_ToolBar.SetButtonText(1, _T("�ֶ�ʶ��"));
	m_ToolBar.SetButtonText(2, _T("���ɱ���"));
	m_ToolBar.SetButtonText(3, _T("ϵͳ����"));

	m_ToolBar.GetToolBarCtrl().SetImageList(&m_ImageListToolbar);//����ͼƬ����ť��
	m_ToolBar.GetToolBarCtrl().SetHotImageList(&m_ImageListToolbar);
	m_ToolBar.GetToolBarCtrl().SetDisabledImageList(&m_ImageListToolbar);
	m_ToolBar.GetToolBarCtrl().SetButtonWidth(60, 200);//���ð�ť�Ŀ��
	m_ToolBar.SetSizes(CSize(68, 68), CSize(48, 48));//���ð�ť��С
	m_ToolBar.EnableToolTips(TRUE);//������ʾ��Ϣ

	//m_ToolBar.GetToolBarCtrl().SetState(IDC_TOOLBAR_BUTTON2, TBSTATE_INDETERMINATE);
	//m_ToolBar.GetToolBarCtrl().SetState(IDC_TOOLBAR_BUTTON2, TBSTATE_ENABLED);
	//m_ToolBar.GetToolBarCtrl().SetState(IDC_TOOLBAR_BUTTON2, TBSTATE_HIDDEN);
	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, CWnd::reposDefault, NULL, NULL, true);

	m_ToolBar.GetToolBarCtrl().SetWindowPos(&CWnd::wndBottom, 10, 10, 100, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);


	//�ڶ��ַ�������λͼ
	{
		////ʹ������ͼ����ʾ256ɫ
		//HBITMAP hbm = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),  
		//	MAKEINTRESOURCE(IDR_TOOLBAR1), //����IDB_TOOLBAR 
		//	IMAGE_BITMAP, //��λͼ��ʽ
		//	0,0, // cx,cy  
		//	LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS ); 
		//CBitmap bm;  
		//bm.Attach(hbm); 
		//m_ilToolBar.Create(48,48,ILC_COLOR8, 4, 4); 
		//m_ilToolBar.Add(&bm,(CBitmap*)NULL); 
	}

	return true;
}
LRESULT CWeighingManagerDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	//return CDialog::DefWindowProc(message, wParam, lParam);
	LRESULT lrst = CDialog::DefWindowProc(message, wParam, lParam);
	if (message == WM_NCPAINT || message == WM_MOVE || message == WM_NCACTIVATE || message == WM_PAINT/*||message == WM_NOTIFY*/)
	{
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
		{
			m_drawApe.DrawDlg(pWinDC, m_BKColor);
			m_drawApe.DrawTitleBar(pWinDC, m_BKColor);
			m_drawApe.DrawIcon(pWinDC, IDI_ICON1, 2);
			//m_drawApe.DrawDlg(pWinDC,IDB_BITMAP_BG,IDB_BITMAP_BG,IDB_BITMAP_BG,IDB_BITMAP_BG);

			//DrawTitleBar(pWinDC);
			//DrawDlg(m_BKColor);
			//DrawDlg(IDB_BITMAP_BG,IDB_BITMAP_BG,IDB_BITMAP_BG,IDB_BITMAP_BG);

			TCHAR szWndTitle[MAX_PATH];
			ZeroMemory(szWndTitle, sizeof(szWndTitle));
			GetWindowText(szWndTitle, sizeof(TCHAR)*MAX_PATH);
			//SendMessage(hWnd, WM_GETTEXT, (WPARAM)MAX_PATH, (LPARAM)szWndTitle); 
			m_drawApe.SetTitleColor(RGB(0, 0, 0));
			m_drawApe.DrawTitle(pWinDC, szWndTitle, 20);
			//m_drawApe.DrawSystemBtn1(pWinDC, IDB_NORMAL);
		}
		ReleaseDC(pWinDC);
	}
	return lrst;
}

void CWeighingManagerDlg::OnNcPaint()
{
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnNcPaint()
}

//void CWeighingManagerDlg::DrawTitleBar(CDC *pDC)
//{
//	CDC memDC;
//	CBitmap bmp;
//	CRect rect, rtTitle;
//	CPoint point;
//	GetClientRect(&rect);
//
//	//��ȡ��������С
//	rtTitle.left = GetSystemMetrics(SM_CXFRAME);
//	rtTitle.top = GetSystemMetrics(SM_CYFRAME);
//	rtTitle.right = rect.right - rect.left - GetSystemMetrics(SM_CXFRAME);
//	rtTitle.bottom = rtTitle.top + GetSystemMetrics(SM_CYSIZE);
//
//	point.x = rect.right + GetSystemMetrics(SM_CXFRAME);
//	point.y = 30;
//
//	memDC.CreateCompatibleDC(NULL);
//	bmp.CreateCompatibleBitmap(pDC, point.x, point.y);
//	CBitmap *pOldBit = memDC.SelectObject(&bmp);
//
//
//	//������ɫ
//	memDC.FillSolidRect(0, 0, point.x, point.y, m_BKColor);
//
//	////��ͼ
//	/*CBitmap pic;
//	pic.LoadBitmap(IDB_BITMAP_BG);
//	ShowBitmap(&memDC,0,0, rtTitle.right, 30, pic);*/
//
//	pDC->BitBlt(0, 0, point.x, point.y, &memDC, 0, 0, SRCCOPY);
//
//	pOldBit->DeleteObject();
//	memDC.DeleteDC();
//	bmp.DeleteObject();
//
//}
//
//void CWeighingManagerDlg::DrawDlg(COLORREF colorValue)//����ɫ���
//{
//	CDC memDC;
//	CRect wndRC;
//	CBitmap bmp;
//	CDC* pDC = GetWindowDC();
//
//	GetWindowRect(wndRC);
//	wndRC.OffsetRect(wndRC.Width(), wndRC.Height());
//	int nTitleHeight = GetSystemMetrics(SM_CYCAPTION);
//	int nborder = ::GetSystemMetrics(SM_CXFIXEDFRAME);
//
//	if (GetStyle()&WS_THICKFRAME)
//	{
//		int nborder = ::GetSystemMetrics(SM_CXBORDER);
//	}
//
//	memDC.CreateCompatibleDC(NULL);
//
//
//	//������߽�
//	bmp.CreateCompatibleBitmap(pDC, nborder, wndRC.Height() - nTitleHeight);
//	memDC.SelectObject(&bmp);
//	memDC.FillSolidRect(0, 0, nborder, wndRC.Height() - nTitleHeight, colorValue);
//	pDC->BitBlt(0, nTitleHeight, nborder, wndRC.Height() - nTitleHeight, &memDC, 0, 0, SRCCOPY);
//	bmp.DeleteObject();
//
//	//�����ұ߽�
//	bmp.CreateCompatibleBitmap(pDC, nborder, wndRC.Height() - nTitleHeight);
//	memDC.SelectObject(&bmp);
//	memDC.FillSolidRect(0, 0, nborder, wndRC.Height() - nTitleHeight, colorValue);
//	pDC->BitBlt(wndRC.Width() - nborder, nTitleHeight, nborder, wndRC.Height() - nTitleHeight, &memDC, 0, 0, SRCCOPY);
//	bmp.DeleteObject();
//
//
//
//	//���صױ�
//	bmp.CreateCompatibleBitmap(pDC, wndRC.Width() - 2 * nborder, nborder);
//	memDC.SelectObject(&bmp);
//	memDC.FillSolidRect(0, 0, wndRC.Width() - 2 * nborder, nborder, colorValue);
//	pDC->BitBlt(nborder, wndRC.Height() - nborder, wndRC.Width() - 2 * nborder, wndRC.Height(), &memDC, 0, 0, SRCCOPY);
//	bmp.DeleteObject();
//
//
//	////���ر�����
//	bmp.CreateCompatibleBitmap(pDC, wndRC.Width() - 2 * nborder, nborder);
//	memDC.SelectObject(&bmp);
//	memDC.FillSolidRect(0, 0, wndRC.Width(), nTitleHeight + nborder, colorValue);
//	pDC->BitBlt(0, 0, wndRC.Width(), nTitleHeight + nborder, &memDC, 0, 0, SRCCOPY);
//
//	bmp.DeleteObject();
//	memDC.DeleteDC();
//}
//
//void CWeighingManagerDlg::DrawDlg(UINT LeftBmp, UINT RightBmp, UINT ButtomBmp, UINT TitleBmp)
//{
//	CDC memDC;
//	CRect wndRC;
//	CBitmap bmp;
//
//	CDC* pDC = GetWindowDC();
//	GetWindowRect(wndRC);
//	wndRC.OffsetRect(wndRC.Width(), wndRC.Height());
//	int nTitleHeight = GetSystemMetrics(SM_CYCAPTION);
//	int nborder = ::GetSystemMetrics(SM_CXFIXEDFRAME);
//	if (GetStyle()&WS_THICKFRAME)
//	{
//		int nborder = ::GetSystemMetrics(SM_CXBORDER);
//	}
//
//	//������߽�λͼ
//	bmp.LoadBitmap(LeftBmp);
//	BITMAP so_bmp;
//	bmp.GetBitmap(&so_bmp);
//	int nBmpWidth, nbmpHeight;
//	nBmpWidth = so_bmp.bmWidth;
//	nbmpHeight = so_bmp.bmHeight;
//
//	memDC.CreateCompatibleDC(pDC);
//	memDC.SelectObject(&bmp);
//	pDC->StretchBlt(0, nTitleHeight, nborder, wndRC.Height() - nTitleHeight, &memDC, 0, 0, nBmpWidth, nbmpHeight, SRCCOPY);
//	bmp.DeleteObject();
//
//	//�����ұ߽�λͼ
//	bmp.LoadBitmap(RightBmp);
//	bmp.GetBitmap(&so_bmp);
//	nBmpWidth = so_bmp.bmWidth;
//	nbmpHeight = so_bmp.bmHeight;
//
//	memDC.SelectObject(&bmp);
//	pDC->StretchBlt(wndRC.Width() - nborder, nTitleHeight, nborder, wndRC.Height() - nTitleHeight, &memDC, 0, 0, nBmpWidth, nbmpHeight, SRCCOPY);
//	bmp.DeleteObject();
//
//	//���صױ�λͼ
//	bmp.LoadBitmap(ButtomBmp);
//	bmp.GetBitmap(&so_bmp);
//	nBmpWidth = so_bmp.bmWidth;
//	nbmpHeight = so_bmp.bmHeight;
//
//	memDC.SelectObject(&bmp);
//	pDC->StretchBlt(nborder, wndRC.Height() - nborder, wndRC.Width() - 2 * nborder, nborder, &memDC, 0, 0, nBmpWidth, nbmpHeight, SRCCOPY);
//	bmp.DeleteObject();
//
//
//	//���ر�����λͼ
//	bmp.LoadBitmap(TitleBmp);
//	bmp.GetBitmap(&so_bmp);
//	nBmpWidth = so_bmp.bmWidth;
//	nbmpHeight = so_bmp.bmHeight;
//
//	memDC.SelectObject(&bmp);
//	pDC->StretchBlt(0, 0, wndRC.Width(), nTitleHeight + nborder, &memDC, 0, 0, nBmpWidth, nbmpHeight, SRCCOPY);
//	bmp.DeleteObject();
//
//	memDC.DeleteDC();
//}

HBRUSH CWeighingManagerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return (HBRUSH)m_BKBrush.GetSafeHandle();
	}
	
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

BOOL CWeighingManagerDlg::OnEraseBkgnd(CDC* pDC)
{
	return CDialog::OnEraseBkgnd(pDC);
}

// WeighingManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WeighingManager.h"
#include "WeighingManagerDlg.h"
#include "WeighingManagerImp.h"
#include "afxdialogex.h"
#include "ProcessBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define SAVE_LP2FILE	//����ú꣬�����������ĳ���ʶ����
#endif

const int TIMER_RECORD_ID = 1001;
const int TIMER_RECORD_VALUE = 10 * 60 * 1000; // ��ʱ��10����

enum
{
	DEV_STATUS_ONLINE,
	DEV_STATUS_OFFLINE,
};

enum
{
	IDM_REPORT = 10001,
    IDM_SET,
    IDM_LOGOUT
};

static void iImageListLoadIDB(int IDB_, CImageList *pImgList)
{
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_);
	pImgList->Add(&bitmap, RGB(0, 0, 0));
}

static const char *iGetResultTypeName(VZ_LPRC_RESULT_TYPE eResultType)
{
	static const char *pStrTypeName[VZ_LPRC_RESULT_TYPE_NUM]
		= { "ʵʱ", "�Զ�����", "�������", "�ⲿ����", "������Ȧ", "���ش���" };

	return(pStrTypeName[eResultType]);
}

static const char *iGetResultTypeNameByBits(unsigned uBits)
{
	const int LenStr = 256;
	static char strTypes[LenStr];
	strTypes[0] = 0;
	if (uBits == 0)
	{
		strcat_s(strTypes, LenStr, iGetResultTypeName(VZ_LPRC_RESULT_REALTIME));
	}
	if (uBits & TRIGGER_TYPE_AUTO_BIT)
	{
		strcat_s(strTypes, LenStr, iGetResultTypeName(VZ_LPRC_RESULT_STABLE));
	}
	if (uBits & TRIGGER_TYPE_EXTERNAL_BIT)
	{
		strcat_s(strTypes, LenStr, iGetResultTypeName(VZ_LPRC_RESULT_IO_TRIGGER));
		strcat_s(strTypes, LenStr, "|");
	}
	if (uBits & TRIGGER_TYPE_SOFTWARE_BIT)
	{
		strcat_s(strTypes, LenStr, iGetResultTypeName(VZ_LPRC_RESULT_FORCE_TRIGGER));
		strcat_s(strTypes, LenStr, "|");
	}
	if (uBits & TRIGGER_TYPE_VLOOP_BIT)
	{
		strcat_s(strTypes, LenStr, iGetResultTypeName(VZ_LPRC_RESULT_VLOOP_TRIGGER));
		strcat_s(strTypes, LenStr, "|");
	}

	return(strTypes);
};

static const char *iGetDirString(int nDir)
{
	if (nDir == 3)
		return("����");
	if (nDir == 4)
		return("����");
	return(" ");
}

void __stdcall OnCommonNotify(VzLPRClientHandle handle, void *pUserData,
	VZ_LPRC_COMMON_NOTIFY eNotify, const char *pStrDetail)
{
	CWeighingManagerDlg *pInstance = (CWeighingManagerDlg *)pUserData;
	pInstance->OnCommonNotify0(handle, eNotify, pStrDetail);
}

int __stdcall OnPlateInfo(VzLPRClientHandle handle, void *pUserData,
	const TH_PlateResult *pResult, unsigned uNumPlates,
	VZ_LPRC_RESULT_TYPE eResultType,
	const VZ_LPRC_IMAGE_INFO *pImgFull,
	const VZ_LPRC_IMAGE_INFO *pImgPlateClip)
{
	CWeighingManagerDlg *pInstance = (CWeighingManagerDlg *)pUserData;
	pInstance->OnPlateInfo0(handle, pResult, uNumPlates, eResultType, pImgFull, pImgPlateClip);

	return(0);
}

int __stdcall OnQueryPlateInfo(VzLPRClientHandle handle, void *pUserData,
	const TH_PlateResult *pResult, unsigned uNumPlates,
	VZ_LPRC_RESULT_TYPE eResultType,
	const VZ_LPRC_IMAGE_INFO *pImgFull,
	const VZ_LPRC_IMAGE_INFO *pImgPlateClip)
{
	int mm = 0;

	return 0;
}

int __stdcall OnVideoFrame(VzLPRClientHandle handle, void *pUserData,
	WORD wVideoID, const VzYUV420P *pFrame)
{
	CWeighingManagerDlg *pInstance = (CWeighingManagerDlg *)pUserData;
	pInstance->OnVideoFrame0(handle, wVideoID, pFrame);

	return(0);
}

//void __stdcall OnSerialRecvData(int nSerialHandle, const unsigned char *pRecvData, unsigned uRecvSize, void *pUserData)
//{
//	CWeighingManagerDlg *pInstance = (CWeighingManagerDlg *)pUserData;
//	pInstance->OnSerialRecvData1(nSerialHandle, pRecvData, uRecvSize);
//}

void CALLBACK iOnViewerMouse(IV_EVENT eEvent, int x, int y, void *pUserData, int nId)
{
	CWeighingManagerDlg *pInstance = (CWeighingManagerDlg *)pUserData;
	pInstance->OnViewerMouse0(eEvent, x, y, nId);
}


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
	//m_BKColor = RGB(165, 201, 235);
	//m_BKBrush.CreateSolidBrush(RGB(165, 201, 235));
}

void CWeighingManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SHOW_1_1, m_winOut[0].m_struInterV);
	DDX_Control(pDX, IDC_STATIC_SHOW_1_2, m_winOut[1].m_struInterV);
	DDX_Control(pDX, IDC_STATIC_SHOW_2_1, m_winOut[2].m_struInterV);
	DDX_Control(pDX, IDC_STATIC_SHOW_2_2, m_winOut[3].m_struInterV);
	DDX_Control(pDX, IDC_TREE1, m_treeDeviceList);
}

BEGIN_MESSAGE_MAP(CWeighingManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_MESSAGE(WM_APP + 1, OnMyMsgHandler)
	ON_COMMAND(IDC_TOOLBAR_BUTTON1, OnAutoStart)
	ON_COMMAND(IDM_SET, OnToolbarSet)
	ON_COMMAND(IDM_LOGOUT, OnOK)
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
	Init();
	InitStatusBar();

	InitImageList();
	InitToolBar();

	SetTimer(1, 1000, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWeighingManagerDlg::Init()
{
	//��ʼ�����ڣ���������߼�
	serialPort1.InitPort(CWnd::FromHandle(m_hWnd));

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//	_CrtSetBreakAlloc(100);
#endif

	//��ʼ������������
	GetModuleFileName(NULL, m_strModuleDir, MAX_PATH);
	*strrchr(m_strModuleDir, '\\') = 0;
	strcpy_s(m_strModuleName, MAX_PATH, "VzLPRSDKDemoDlg");

	VZLPRClient_SetCommonNotifyCallBack(OnCommonNotify, this);

	int nIDCEditResult[MAX_OUTPUT_NUM] =
	{
		IDC_EDIT_RESULT_1_1, IDC_EDIT_RESULT_1_2,
		IDC_EDIT_RESULT_2_1, IDC_EDIT_RESULT_2_2
	};
	for (int i = 0; i<MAX_OUTPUT_NUM; i++)
	{
		m_winOut[i].pEditResult = (CEdit *)GetDlgItem(nIDCEditResult[i]);
		m_winOut[i].m_struInterV.SetID(i);
		m_winOut[i].m_struInterV.SetInteractCallback(iOnViewerMouse, this);
		m_winOut[i].m_struInterV.SetCallBackOnPaint(iOnIVPaint, this);
	}

	//Ϊm_treeDeviceList����ͼ���б�
	m_pImageList = new CImageList();
	m_pImageList->Create(16, 16, ILC_COLOR32, 0, 2);
	iImageListLoadIDB(IDB_BMP_ONLINE, m_pImageList);
	iImageListLoadIDB(IDB_BMP_OFFLINE, m_pImageList);

	char strIP[32] = { 0 };
	{
		//ʹ����һ�ε�IP��ַ
		char strINI[MAX_PATH];
		sprintf_s(strINI, MAX_PATH, "%s/user.ini", m_strModuleDir);
		GetPrivateProfileString(m_strModuleName, "LastIP", "", strIP, 32, strINI);
	}
	//SetDlgItemText(IDC_EDIT_IP, strIP);
	//SetDlgItemText(IDC_EDIT_PORT, "80");
	//SetDlgItemText(IDC_EDIT_USERNAME, "admin");
	//SetDlgItemText(IDC_EDIT_PASSWORD, "admin");

	//((CButton *)GetDlgItem(IDC_CHK_SAVE_STABLE))->SetCheck(BST_CHECKED);
	m_bSaveJPG = true;

	char strFilePath[MAX_PATH];

	sprintf_s(strFilePath, MAX_PATH, "%s/%s",
		m_strModuleDir, "Cap");

	if (!PathIsDirectory(strFilePath))
	{
		CreateDirectory(strFilePath, NULL);
	}

	m_strCommNotify[0] = 0;

	//m_dlgTriggerShow.Create(m_dlgTriggerShow.IDD, this);

	//�������˿�����
	/*CComboBox *pCmbOP = (CComboBox *)GetDlgItem(IDC_CMB_OUT_PORT_ID);
	pCmbOP->AddString("������ 1");
	pCmbOP->AddString("������ 2");
	pCmbOP->AddString("5V TLL 1");
	pCmbOP->AddString("5V TLL 2");*/

	/*CComboBox *pCmbBaudRate = (CComboBox *)GetDlgItem(IDC_CMB_SERIAL_PORT);
	pCmbBaudRate->AddString("Port1");
	pCmbBaudRate->AddString("Port2");
	pCmbBaudRate->SetCurSel(0);*/

	SetTimer(1000, 300, NULL);

	SetTimer(TIMER_RECORD_ID, TIMER_RECORD_VALUE, NULL);

#ifdef SAVE_LP2FILE
	time_t ttCurr;
	time(&ttCurr);
	tm tmCurr;
	localtime_s(&tmCurr, &ttCurr);
	sprintf_s(strFilePath, MAX_PATH, "%s/LP_%d%02d%02d_%2d%02d%02d.log",
		m_strModuleDir, tmCurr.tm_year + 1900, tmCurr.tm_mon + 1, tmCurr.tm_mday,
		tmCurr.tm_hour, tmCurr.tm_min, tmCurr.tm_sec);

	fopen_s(&m_pFSaveLP, strFilePath, "w");
#endif
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

void CWeighingManagerDlg::InitStatusBar()
{
	m_imglistStatusBar.Create(16, 16, ILC_COLOR24 | ILC_MASK, 5, 0);
	m_imglistStatusBar.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_imglistStatusBar.Add(AfxGetApp()->LoadIcon(IDI_ICON4));


	promptInfo[0] = "";
	promptInfo[1] = "���ư�1����";
	promptInfo[2] = "���ư�2����";
	promptInfo[3] = "����ͷ1�˿�";
	promptInfo[4] = "����ͷ2�˿�";
	promptInfo[5] = "LED��Ļ����";
	promptInfo[6] = "�ذ�����";
	promptInfo[7] = "���ݿ�״̬";
	promptInfo[8] = theApp.m_pGlobalObject->GetUsername();

	m_StatusBar.Create(WS_CHILD | WS_VISIBLE | SBT_OWNERDRAW, CRect(0, 0, 0, 0), this, 0);
	int strPartDim[11] = { 0, 100, 200, 300, 400, 500, 600, 700, 800, 1020, -1 };
	m_StatusBar.SetParts(11, strPartDim);

	m_StatusBar.SetText(promptInfo[0], 0, 0);
	m_StatusBar.SetText(promptInfo[1], 1, 0);
	m_StatusBar.SetText(promptInfo[2], 2, 0);
	m_StatusBar.SetText(promptInfo[3], 3, 0);
	m_StatusBar.SetText(promptInfo[4], 4, 0);
	m_StatusBar.SetText(promptInfo[5], 5, 0);
	m_StatusBar.SetText(promptInfo[6], 6, 0);
	m_StatusBar.SetText(promptInfo[7], 7, 0);
	m_StatusBar.SetText(promptInfo[8], 8, 0);

	m_StatusBar.SetIcon(1, m_imglistStatusBar.ExtractIcon(1));
	m_StatusBar.SetIcon(2, m_imglistStatusBar.ExtractIcon(1));
	m_StatusBar.SetIcon(3, m_imglistStatusBar.ExtractIcon(1));
	m_StatusBar.SetIcon(4, m_imglistStatusBar.ExtractIcon(1));
	m_StatusBar.SetIcon(5, m_imglistStatusBar.ExtractIcon(1));
	m_StatusBar.SetIcon(6, m_imglistStatusBar.ExtractIcon(1));
	m_StatusBar.SetIcon(7, m_imglistStatusBar.ExtractIcon(1));
	//m_StatusBar.SetIcon(8, m_imglistStatusBar.ExtractIcon(1));
	//m_StatusBar.SetIcon(9, m_imglistStatusBar.ExtractIcon(1));
	//m_StatusBar.SetIcon(10, m_imglistStatusBar.ExtractIcon(0));
	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	m_StatusBar.SetBkColor(RGB(180,180,180));   //״̬������ɫ

	//Ҫʵ�ֿ��϶����ڵ�״̬���ĸ����϶���Ҫ��onsize�и�����Ϣ���磺	
	RECT   winrect;
	if (m_StatusBar.GetSafeHwnd() == NULL)
		return;
	this->GetClientRect(&winrect); //ȡ�ÿͻ�����С
	m_StatusBar.MoveWindow((winrect.left + 50), (winrect.bottom - 30),
		(winrect.right - winrect.left - 100), 30, TRUE); //���ʵ��ĵط���ʾ״̬�� 
}

void CWeighingManagerDlg::InitImageList()
{
	m_ImageListToolbar.Create(48, 48, ILC_COLOR24|ILC_MASK, 1, 1);
	m_ImageListToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_ImageListToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_ImageListToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	m_ImageListToolbar.Add(AfxGetApp()->LoadIcon(IDI_ICON7));

	m_ImageListHotToolbar.Create(48, 48, ILC_COLOR24|ILC_MASK, 1, 1);
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
	//RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);  //��ʾ������

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, CWnd::reposDefault, NULL, NULL, true);
	m_ToolBar.GetToolBarCtrl().SetWindowPos(&CWnd::wndBottom, 10, 10, 100, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	m_ToolBar.ModifyStyle(0, TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | TBSTYLE_WRAPABLE );//���ù���������ɫ͸��    ---  (����Ҫ�󣬿�������ѡ��)

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

LRESULT CWeighingManagerDlg::OnMyMsgHandler(WPARAM wparam, LPARAM lParam)
{
	CPoint pt;
	CMenu menu;

	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, IDM_REPORT, "����");
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, IDM_SET, "����");
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, IDM_LOGOUT, "�˳�");

	pt.x = (int)(short)LOWORD(lParam);
	pt.y = (int)(short)HIWORD(lParam);

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_HORPOSANIMATION
		, pt.x, pt.y, CWnd::FromHandle(m_hWnd));

	menu.DestroyMenu();
	return 0;
}

void CWeighingManagerDlg::OnAutoStart()
{
	CWeighingManagerImp cWMI;
	cWMI.process_start();
}

void CWeighingManagerDlg::OnToolbarSet()
{
	ProcessBar dlg1;
	dlg1.DoModal();
	CSysParametrSet dlg;
	dlg.DoModal();
}

void CWeighingManagerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == TIMER_RECORD_ID)
	{
		// ��ʱȫ������¼��
		iReRecordAllVideo();
	}
	else
	{
		//��ѯ�����豸��״̬
		for (unsigned i = 0; i<m_vDev.size(); i++)
		{
			BYTE cStatus = 0;
			VzLPRClient_IsConnected(m_vDev[i]->hLPRClient, &cStatus);
			if (cStatus == 1)
			{
				iChangeDlgImageItem(m_vDev[i]->hLPRClient, DEV_STATUS_ONLINE);
			}
			else
			{
				iChangeDlgImageItem(m_vDev[i]->hLPRClient, DEV_STATUS_OFFLINE);
			}
		}

		//���½�������
		for (unsigned i = 0; i<MAX_OUTPUT_NUM >> 1; i++)
		{
			m_winOut[i].ShowString();
		}

		if (m_nCDCleanCommNotify > 0)
		{
			m_nCDCleanCommNotify--;
			if (m_nCDCleanCommNotify == 0)
			{
				m_strCommNotify[0] = 0;
			}
			SetDlgItemText(IDC_EDIT_NOTIFY, m_strCommNotify);
		}

		//iUpdateSerialRecvInfo();
	}

	if (nIDEvent == 1)
	{
		CTime time;
		time = CTime::GetCurrentTime();
		m_StatusBar.SetText(time.Format("%Y") + ("��") + time.Format("%m") + ("��") + time.Format("%d") + ("�� ") + (" ") + time.Format("%H:%M:%S"), 9, 0);
	}

	CDialog::OnTimer(nIDEvent);

	CDialog::OnTimer(nIDEvent);
}

void CWeighingManagerDlg::iReRecordAllVideo()
{
	char szPath[MAX_PATH] = { 0 };

	int nSize = m_vecRecordHandle.size();
	for (int i = 0; i < nSize; i++)
	{
		VzLPRClientHandle hLPRClient = (VzLPRClientHandle)m_vecRecordHandle[i];
		if (hLPRClient != NULL)
		{
			CString strDevice = iGetDeviceItemText(hLPRClient);
			if (strDevice != "")
			{
				// ֹͣ¼��
				VzLPRClient_StopSaveRealData(hLPRClient);

				// ����¼��
				iRecordVideo(hLPRClient, strDevice);
			}
		}
	}
}

CString CWeighingManagerDlg::iGetDeviceItemText(VzLPRClientHandle hLPRClient)
{
	CString strDevice;

	HTREEITEM hItem = m_treeDeviceList.GetRootItem();
	VzLPRClientHandle hCurClient;

	while (hItem != NULL)
	{
		hCurClient = m_treeDeviceList.GetItemData(hItem);
		if (hCurClient == hLPRClient)
		{
			strDevice = m_treeDeviceList.GetItemText(hItem);
			break;
		}

		hItem = m_treeDeviceList.GetNextItem(hItem, TVGN_NEXT);
	}

	return strDevice;
}

void CWeighingManagerDlg::iRecordVideo(VzLPRClientHandle hLPRClient, CString strDevice)
{
	COleDateTime dtNow = COleDateTime::GetCurrentTime();

	char strFilePath[MAX_PATH] = { 0 };
	sprintf_s(strFilePath, MAX_PATH, "%s\\Video", m_strModuleDir);

	if (!PathIsDirectory(strFilePath))
	{
		CreateDirectory(strFilePath, NULL);
	}

	char szPath[MAX_PATH] = { 0 };
	sprintf_s(szPath, sizeof(szPath), "%s\\%s_%d%02d%02d%02d%02d%02d.avi", strFilePath, strDevice.GetBuffer(0), dtNow.GetYear(), dtNow.GetMonth(), dtNow.GetDay(),
		dtNow.GetHour(), dtNow.GetMinute(), dtNow.GetSecond());

	VzLPRClient_SaveRealData(hLPRClient, szPath);
}

void CWeighingManagerDlg::iChangeDlgImageItem(VzLPRClientHandle handle, int imageID)
{
	HTREEITEM hRoot = m_treeDeviceList.GetRootItem();
	while (hRoot)
	{
		if (handle == m_treeDeviceList.GetItemData(hRoot))
		{
			m_treeDeviceList.SetItemImage(hRoot, imageID, imageID);
			return;
		}
		hRoot = m_treeDeviceList.GetNextItem(hRoot, TVGN_NEXT);
	}
}

void CALLBACK CWeighingManagerDlg::iOnIVPaint(int nID, bool bActive, bool bInUse, void *pUserData)
{
	CWeighingManagerDlg *pInstance = (CWeighingManagerDlg *)pUserData;
	pInstance->iOnIVPaint1(nID, bActive, bInUse);
}

void CWeighingManagerDlg::iOnIVPaint1(int nID, bool bActive, bool bInUse)
{
	m_winOut[nID].ShowString();

	if (bInUse)
	{
		if (nID >= (MAX_OUTPUT_NUM >> 1))
			m_winOut[nID].ShowFrame();
	}
}

void CWeighingManagerDlg::OnPlateInfo0(VzLPRClientHandle handle,
	const TH_PlateResult *pResult, unsigned uNumPlates,
	VZ_LPRC_RESULT_TYPE eResultType,
	const VZ_LPRC_IMAGE_INFO *pImgFull,
	const VZ_LPRC_IMAGE_INFO *pImgPlateClip)
{
	if (handle == NULL || pResult == NULL || uNumPlates == 0)
		return;

	DeviceLPR *pDev = iGetLocalDev(handle);

	char strMsg[MAX_LEN_STR] = { 0 };
	for (unsigned i = 0; i<uNumPlates; i++)
	{
		char strTmp[MAX_LEN_STR];

		sprintf_s(strTmp, MAX_LEN_STR, " [%s:%s �����=%d)] %s %d/%02d/%02d %02d:%02d:%02d",
			iGetResultTypeNameByBits(pResult[i].uBitsTrigType), pResult[i].license,
			pResult[i].rcLocation.right - pResult[i].rcLocation.left, iGetDirString(pResult[i].nDirection),
			pResult[i].struBDTime.bdt_year, pResult[i].struBDTime.bdt_mon, pResult[i].struBDTime.bdt_mday,
			pResult[i].struBDTime.bdt_hour, pResult[i].struBDTime.bdt_min, pResult[i].struBDTime.bdt_sec);
		strcat_s(strMsg, MAX_LEN_STR, strTmp);
	}

	OutputWin *pOutWin = eResultType == VZ_LPRC_RESULT_REALTIME
		? iGetOutputWinByIdx(pDev->GetWinIdx()) : iGetStableOutputWinByIdx(pDev->GetWinIdx());

	if (pOutWin)
	{
		pOutWin->UpdateString(strMsg);
		if (pImgFull)
		{
			pOutWin->SetFrame(pImgFull->pBuffer, pImgFull->uWidth, pImgFull->uHeight, pImgFull->uPitch);
			unsigned uYOffset = 4;
			for (unsigned i = 0; i<uNumPlates; i++)
			{
				pOutWin->AddPatch(pImgPlateClip[i].pBuffer, pImgPlateClip[i].uWidth,
					pImgPlateClip[i].uHeight, pImgPlateClip[i].uPitch, 4, uYOffset);
				uYOffset += pImgPlateClip[i].uHeight;
			}
		}
	}

	if (m_bSaveJPG)
	{
		iSaveJPEG(pImgFull, eResultType, pResult[0].license);
	}

	//���津�����͵Ľ�����ı�����ʵʱ��
	if (m_pFSaveLP && eResultType != VZ_LPRC_RESULT_REALTIME)
	{
		if (uNumPlates > 0)
		{
			for (unsigned i = 0; i<uNumPlates; i++)
			{
				fprintf(m_pFSaveLP, "%s ", pResult[0].license);
			}
			fprintf(m_pFSaveLP, "\n");
		}
		fflush(m_pFSaveLP);
	}
}

void CWeighingManagerDlg::OnVideoFrame0(VzLPRClientHandle handle, WORD wVideoID, const VzYUV420P *pFrame)
{
	OutputWin *pWinOut = iGetOutputWinByIdx(wVideoID);
	if (pWinOut == NULL)
		return;
}

void CWeighingManagerDlg::OnViewerMouse0(IV_EVENT eEvent, int x, int y, int nId)
{
	if (nId == 2 || nId == 3)
		nId -= 2;

	OutputWin &winOut = m_winOut[nId];
	OutputWin &winOut2 = m_winOut[nId + 2];

	if (eEvent == IV_EVENT_L_BTN_DOWN)
	{
		m_nIdxWinCurrSelected = nId;
		winOut.m_struInterV.SetActive(true);
		winOut2.m_struInterV.SetActive(true);
		for (int i = 0; i<MAX_OUTPUT_NUM; i++)
		{
			if (i == nId || i == nId + 2)
				continue;
			m_winOut[i].m_struInterV.SetActive(false);
		}
	}
}

void CWeighingManagerDlg::OnCommonNotify0(VzLPRClientHandle handle,
	VZ_LPRC_COMMON_NOTIFY eNotify, const char *pStrDetail)
{
	char strDetail[MAX_LEN_STR];

	if (pStrDetail)
		sprintf_s(strDetail, MAX_LEN_STR, "[0x%08x]Noitfy=%d: %s", handle, eNotify, pStrDetail);
	else
		sprintf_s(strDetail, MAX_LEN_STR, "[0x%08x]Noitfy=%d", handle, eNotify);

	iSetCommonInfo(strDetail);
}

DeviceLPR *CWeighingManagerDlg::iGetLocalDev(VzLPRClientHandle hLPRClient)
{
	for (unsigned i = 0; i<m_vDev.size(); i++)
	{
		if (m_vDev[i]->hLPRClient == hLPRClient)
			return(m_vDev[i]);
	}

	return(NULL);
}

OutputWin *CWeighingManagerDlg::iGetOutputWinByIdx(int nIdxWin)
{
	if (nIdxWin >= 0 && nIdxWin < (MAX_OUTPUT_NUM >> 1))
		return(m_winOut + nIdxWin);

	return(NULL);
}

OutputWin *CWeighingManagerDlg::iGetStableOutputWinByIdx(int nIdx)
{
	OutputWin *pWin = iGetOutputWinByIdx(nIdx);
	if (pWin == NULL)
		return(NULL);

	return(pWin + (MAX_OUTPUT_NUM >> 1));
}

//�ҵ�һ�����ʵ�������ڣ�
int CWeighingManagerDlg::iGetOutputWinIndex(VzLPRClientHandle hLPRClient)
{
	//���δָ���ͻ��˾��
	if (hLPRClient == NULL)
	{
		//�����ѡ��ĳ�����ڣ���ֱ��ʹ�øô���
		if (m_nIdxWinCurrSelected >= 0)
			return(m_nIdxWinCurrSelected);

		//���δѡ����һ���ڣ���ʹ��δ��ռ�õ�һ�����д���
		for (int i = 0; i<MAX_OUTPUT_NUM >> 1; i++)
		{
			if (m_winOut[i].GetClientHandle() == NULL)
				return(i);
		}
	}
	else	//�����ָ��һ���ͻ��˾������ʹ���Ѻ͸ÿͻ��˾�������Ĵ���
	{
		for (int i = 0; i<MAX_OUTPUT_NUM >> 1; i++)
		{
			if (m_winOut[i].GetClientHandle() == hLPRClient)
				return(i);
		}
	}

	return(-1);
}

void CWeighingManagerDlg::iSetCommonInfo(const char *pStrInfo)
{
	if (pStrInfo == NULL)
		return;

	m_nCDCleanCommNotify = 10;
	strcpy_s(m_strCommNotify, MAX_LEN_STR, pStrInfo);
}

void CWeighingManagerDlg::iSaveJPEG(const VZ_LPRC_IMAGE_INFO *pImgInfo, VZ_LPRC_RESULT_TYPE eType, const char *pStrLicense)
{
	char strFilePath[MAX_PATH];

	sprintf_s(strFilePath, MAX_PATH, "%s/%s/%s",
		m_strModuleDir, "Cap", iGetResultTypeName(eType));

	if (!PathIsDirectory(strFilePath))
	{
		CreateDirectory(strFilePath, NULL);
	}

	char strFileName[MAX_PATH];

	CTime time = CTime::GetCurrentTime();
	sprintf_s(strFileName, MAX_PATH, "%s/%02d%02d%02d_%d%02d%02d_%s.jpg",
		strFilePath,
		time.GetYear() % 100, time.GetMonth(), time.GetDay(),
		time.GetHour(), time.GetMinute(), time.GetSecond(),
		pStrLicense);

	if (pImgInfo)
	{
		VzLPRClient_ImageSaveToJpeg(pImgInfo, strFileName, 80);
	}
}
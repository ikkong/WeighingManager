// ControlPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WeighingManager.h"
#include "ControlPanel.h"
#include "afxdialogex.h"


// CControlPanel �Ի���

IMPLEMENT_DYNAMIC(CControlPanel, CDialogEx)

CControlPanel::CControlPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CControlPanel::IDD, pParent)
{

}

CControlPanel::~CControlPanel()
{
}

void CControlPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CControlPanel, CDialogEx)
END_MESSAGE_MAP()


// CControlPanel ��Ϣ�������


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
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CControlPanel::OnBnClickedMfcbutton1)
END_MESSAGE_MAP()


// CControlPanel ��Ϣ�������


void CControlPanel::OnBnClickedMfcbutton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

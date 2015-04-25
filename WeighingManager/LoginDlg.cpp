// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WeighingManager.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_userName(_T(""))
	, m_userPwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_userName);
	DDV_MaxChars(pDX, m_userName, 20);
	DDX_Text(pDX, IDC_EDIT2, m_userPwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������

LRESULT login(CString m_userName, CString m_userPwd, WPARAM wparam, LPARAM lpram)
{
	return 0;
}
void CLoginDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	WPARAM wparam=NULL;
	LPARAM lpram=NULL;

	LRESULT ret = login(m_userName, m_userPwd, wparam, lpram);
	if (ret != 0)
	{
		MessageBox("��¼ʧ��");
		return;
	}

	CDialogEx::OnOK();
}

// CSysParametrSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WeighingManager.h"
#include "SysParametrSet.h"
#include "afxdialogex.h"


// CSysParametrSet �Ի���

IMPLEMENT_DYNAMIC(CSysParametrSet, CDialogEx)

CSysParametrSet::CSysParametrSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSysParametrSet::IDD, pParent)
{

}

CSysParametrSet::~CSysParametrSet()
{
}

void CSysParametrSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabParamter);
}


BEGIN_MESSAGE_MAP(CSysParametrSet, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CSysParametrSet::OnTcnSelchangeTab1)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CSysParametrSet ��Ϣ�������
void CSysParametrSet::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	CRect rect;
	m_TabParamter.InsertItem(0, "���ư���Ϣ");
	m_TabParamter.InsertItem(1, "����ͷ��Ϣ");
	m_TabParamter.InsertItem(2, "�ذ���Ϣ");
	m_TabParamter.InsertItem(3, "LED��Ļ��Ϣ");
	m_TabParamter.InsertItem(3, "���ݿ���Ϣ");

	m_pControlPanel.Create(IDD_DIALOG_CONTROLPANEL, &m_TabParamter);
	m_pLprControl.Create(IDD_DIALOG_LPR, &m_TabParamter);

	m_TabParamter.GetClientRect(rect);
	rect.InflateRect(-1, -21, -2, -2);
	m_pControlPanel.MoveWindow(rect);
	m_pLprControl.MoveWindow(rect);
	m_pControlPanel.ShowWindow(SW_SHOW);
	m_pLprControl.ShowWindow(SW_HIDE);
}


void CSysParametrSet::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int cursel = m_TabParamter.GetCurSel(); //��ȡ��ǰ��ǩ���� 
	switch (cursel)
	{
	case 0: {
				m_pLprControl.ShowWindow(SW_HIDE);
				m_pControlPanel.ShowWindow(SW_SHOW);
				break;
	}
	case 1: {
				m_pLprControl.ShowWindow(SW_SHOW);
				m_pControlPanel.ShowWindow(SW_HIDE);
				break;
	}
	case 2: {
				
				break;
	}
	case 3: {
				
				break;
	}
	case 4: {
			
				break;
	}
	}
	*pResult = 0;
}

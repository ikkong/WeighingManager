#include "stdafx.h"
#include "WeighingManagerImp.h"

CWeighingManagerImp::CWeighingManagerImp(CDialogEx *pView) :m_iSts(STS_INACTIVE)
{
	m_pView = pView;
	//��ʼ�����ڣ���������߼�
	m_mapSerialPort[PORT_CONTROLPANEL1].InitPort(CWnd::FromHandle(m_pView->m_hWnd));

}
int CWeighingManagerImp::process_start()
{
	m_iSts = !m_iSts;
	if (m_iSts == E_STS::STS_ACTIVE) MessageBox(NULL, _T("��ʼ�Զ�����"), _T("��ʾ"), 0);
	else MessageBox(NULL, _T("ֹͣ�Զ�����"), _T("��ʾ"), 0);
	while (m_iSts == STS_ACTIVE)
	{
		MessageBox(NULL, _T("�����Ȧ1����Ȧ4"), _T("��ʾ"), 0);
		//m_mapSerialPort[PORT_CONTROLPANEL1].StartMonitoring();
	}
	return 0;
}

void CWeighingManagerImp::SetView(CDialogEx * pView)
{
	m_pView = pView;
}
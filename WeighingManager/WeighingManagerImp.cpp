#include "stdafx.h"
#include "WeighingManagerImp.h"

CWeighingManagerImp::CWeighingManagerImp(CDialogEx *pView)
{
	m_pView = pView;
	//��ʼ�����ڣ���������߼�
}

int CWeighingManagerImp::Init(map<int, int>& mapSerialPort)
{
	map<int, int>::iterator it;
	for ( it= mapSerialPort.begin(); it != mapSerialPort.end(); it++)
	{
		m_mapSerialPort[it->first].InitPort(CWnd::FromHandle(m_pView->m_hWnd), mapSerialPort[it->second]);
	}

	return 0;
}

int CWeighingManagerImp::process_start()
{
	//MessageBox(NULL, _T("�����Ȧ1����Ȧ4"), _T("��ʾ"), 0);
	m_mapSerialPort[PORT_CONTROLPANEL1].StartMonitoring();
	return 0;
}

int CWeighingManagerImp::process_stop()
{
	m_mapSerialPort[PORT_CONTROLPANEL1].StopMonitoring();
	m_mapSerialPort[PORT_CONTROLPANEL1].ClosePort();
	return 0;
}

void CWeighingManagerImp::SetView(CDialogEx * pView)
{
	m_pView = pView;
}
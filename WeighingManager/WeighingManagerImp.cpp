#include "stdafx.h"
#include "WeighingManagerImp.h"

CWeighingManagerImp::CWeighingManagerImp(CDialogEx *pView)
{
	m_pView = pView;
	//��ʼ�����ڣ���������߼�
	m_mapSerialPort[PORT_CONTROLPANEL1].InitPort(CWnd::FromHandle(m_pView->m_hWnd));

}
int CWeighingManagerImp::process_start()
{
	//MessageBox(NULL, _T("�����Ȧ1����Ȧ4"), _T("��ʾ"), 0);
	return 0;
}

void CWeighingManagerImp::SetView(CDialogEx * pView)
{
	m_pView = pView;
}
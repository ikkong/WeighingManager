#ifndef __WEIGHINGMANAGERIMP_H__
#define __WEIGHINGMANAGERIMP_H__

#include <map>
//#include "double_map.h"

enum E_PORT_TYPE
{
	PORT_CONTROLPANEL1 = 1,	// ���ư�1
	PORT_CONTROLPANEL2 = 2,	// ���ư�2
	PORT_POUNDSCONTROL = 3,	// �ذ�
	PORT_LEDCONTROL = 4		// LED��ʾ��
};

// ����Ϊҵ��ʵ���࣬ʵ�ֳ��ع���ϵͳ���Զ�������
class CWeighingManagerImp
{
public:
	CWeighingManagerImp(){};
	CWeighingManagerImp(CDialogEx *pView);
	~CWeighingManagerImp(){}

public:
	int Init(map<int, int>& mapPortType);
	int process_start();
	int process_stop();
	void SetView(CDialogEx * pView);
	int  AddPort(int iPortID, int iType);
	int OnHandleXXX();
	int ring_detected(WPARAM wParam, LPARAM lParam);

protected:
	CDialogEx * m_pView;
	//double_map<int, int, CSerialPort*> m_mapSerialPort;	// key: �˿ں�, value1: Ӳ������, value2: ���������
	map<int,CSerialPort> m_mapSerialPort;
	map<int, int> m_mapPortType;
};

#endif

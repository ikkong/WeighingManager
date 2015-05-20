#ifndef __WEIGHINGMANAGERIMP_H__
#define __WEIGHINGMANAGERIMP_H__

#include <map>

// ����Ϊҵ��ʵ���࣬ʵ�ֳ��ع���ϵͳ���Զ�������
class CWeighingManagerImp
{
public:
	CWeighingManagerImp(){};
	CWeighingManagerImp(CDialogEx *pView);
	~CWeighingManagerImp(){}

public:
	int Init(int iPort);
	int process_start();
	int process_stop();
	void SetView(CDialogEx * pView);
	int OnHandleXXX();

protected:
	CDialogEx * m_pView;
	enum E_PORT
	{
		PORT_CONTROLPANEL1 = 1,	// ���ư�1
		PORT_CONTROLPANEL2 = 2,	// ���ư�2
		PORT_POUNDSCONTROL = 3,	// �ذ�
		PORT_LEDCONTROL = 4		// LED��ʾ��
	};
	map<int, CSerialPort> m_mapSerialPort;
	//CSerialPort serialPort1;
	//CSerialPort serialPort2;
	//CSerialPort serialPort3;
	//CSerialPort serialPort4;
	//CSerialPort serialPort5;
};

#endif

#ifndef __WEIGHINGMANAGERIMP_H__
#define __WEIGHINGMANAGERIMP_H__

// ����Ϊҵ��ʵ���࣬ʵ�ֳ��ع���ϵͳ���Զ�������
class CWeighingManagerImp
{
public:
	CWeighingManagerImp(){};
	CWeighingManagerImp(CDialogEx *pView);
	~CWeighingManagerImp(){}

public:
	int process_start();
	void SetView(CDialogEx * pView);
	int OnHandleXXX();

protected:
	CDialogEx * m_pView;
};

#endif

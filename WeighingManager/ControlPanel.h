#pragma once


// CControlPanel �Ի���

class CControlPanel : public CDialogEx
{
	DECLARE_DYNAMIC(CControlPanel)

public:
	CControlPanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CControlPanel();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONTROLPANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

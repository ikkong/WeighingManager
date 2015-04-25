#pragma once


// CLprControl �Ի���

class CLprControl : public CDialogEx
{
	DECLARE_DYNAMIC(CLprControl)

public:
	CLprControl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLprControl();

// �Ի�������
	enum { IDD = IDD_DIALOG_LPR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFind();
	void OnDevFound(const char *pStrDevName, const char *pStrIPAddr, WORD usPort1, WORD usPort2);
	afx_msg void OnBnClickedStopFind();
	afx_msg void OnBnClickedOpen();

	CString m_port;
	CString m_loginname;
	CString m_loginpwd;
	CString m_ip;
};

#pragma once
#include "afxcmn.h"


// ProcessBar �Ի���

class ProcessBar : public CDialogEx
{
	DECLARE_DYNAMIC(ProcessBar)

public:
	ProcessBar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProcessBar();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_processbar;
};

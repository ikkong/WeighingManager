#pragma once

//#include "MyTab.h"
#include "afxcmn.h"
#include "ControlPanel.h"
#include "LprControl.h"
// CSysParametrSet �Ի���

class CSysParametrSet : public CDialogEx
{
	DECLARE_DYNAMIC(CSysParametrSet)

public:
	CSysParametrSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysParametrSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//CMyTab	m_TabParamter;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_TabParamter;
	CControlPanel m_pControlPanel;
	CLprControl   m_pLprControl;
};

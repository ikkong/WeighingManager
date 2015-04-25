
// WeighingManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "CToolBarEx.h"
#include "DrawAppearance.h"
#include "SysParametrSet.h"

// CWeighingManagerDlg �Ի���
class CWeighingManagerDlg : public CDialogEx
{
// ����
public:
	CWeighingManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WEIGHINGMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	afx_msg LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNcPaint();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void InitImageList();
	BOOL InitToolBar();
private:
	CImageList      m_ImageListHotToolbar;//ʹ������ͼ����ʾ256ɫ
	CImageList      m_ImageListToolbar;
	CToolBarEx      m_ToolBar;
	CDrawAppearance m_drawApe;
	COLORREF        m_BKColor;
	CBrush          m_BKBrush;
public:
	void OnToolbarSet();
};

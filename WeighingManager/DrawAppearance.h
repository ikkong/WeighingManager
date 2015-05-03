//////// DrawAppearance  .h: interface for the CDrawAppearance   class.
//
//////////////////////////////////////////////////////////////////////
/*
			|**************************************************|
			| ��ӥ�ĳ��ֻ������հ����ʱ��������� -- Tercel |
			|--------------------------------------------------|   
			|      email��ChinaTianXiang@foxmail.com		   |                                                         
			|**************************************************|
*/
#if !defined(AFX_DRAWAPPEARANCE_H__D181D9FE_00B4_42F3_9432_37A4027770DD__INCLUDED_)
#define AFX_DRAWAPPEARANCE_H__D181D9FE_00B4_42F3_9432_37A4027770DD__INCLUDED_

#include "AFXWIN.H"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawAppearance 
{
public:
	CDrawAppearance  ();
	virtual ~CDrawAppearance  (); 
private :
	WORD  m_wdFontH;			//��������߶�	��0
	WORD  m_wdFontW;			//����������	��0	
	WORD  m_wdSpace;			//����ϵͳ��ť�ľ��룺1
	
	UINT  m_unIDMInNor;			//ϵͳ��ť����״̬ʱ��λͼID  ��DrawStytemBtn�����б��� ��0
	UINT  m_unIDMaxNor;
	UINT  m_unIDResNor;
	UINT  m_unIDClsNor;	
	UINT  m_unIDMInDown;		//ϵͳ��ť����״̬ʱ��λͼID  ��NcLButtonDown�����б��� ��0
	UINT  m_unIDMaxDown;
	UINT  m_unIDResDown;
	UINT  m_unIDClsDown;
	
	
	BOOL  m_bRedrawWnd;			//��ʾ���������Ƿ����ػ棬��DrawBtnBmp�������ж� ��FALSE
	BOOL  m_bDownMin;			//��ʾ��ť�Ƿ��ڰ���״̬ 
	BOOL  m_bDownMax;
	BOOL  m_bDownCls;
	
	CRect m_rtMinBtn;			//����ϵͳ��ť��λ�� ��NULL
	CRect m_rtMaxBtn;
	CRect m_rtCloseBtn;	
	CRect m_rtHelpBtn;	//������ťλ��
	CRect m_rtIcon;		//ͼ��λ��

	COLORREF m_BKColor;
	CBrush   m_BKBrush;	
	COLORREF m_clrTitle;		//������ɫ ��RGB(255,255,255)
protected:
	void LButtonUP(HWND hWnd, CPoint point);
	
	void NcMouseMove(HWND hWnd, CPoint point, UINT nIDClose, UINT nIDMax, UINT nIDRestore, UINT nIDMin);  

	void NcMouseMove1(HWND hWnd, CPoint point,UINT unIDClose, UINT unIDMax, UINT unIDRestore, UINT unIDMin);
	
	void NcLButtonDblClk(HWND hWnd, CPoint point);
	
	BOOL NcLButtonDown(HWND hWnd, CPoint point, UINT nIDClose, UINT nIDMax, UINT nIDRestore, UINT nIDMin);

	BOOL NcLButtonDown1(HWND hWnd, CPoint point, UINT unIDClose, UINT unIDMax, UINT unIDRestore, UINT unIDMin);
	
	BOOL NcLButtonUp(HWND hWnd, CPoint point);
	
	BOOL TransparentBlt(HDC hdcDest,int nXOriginDest,int nYOriginDest,int nWidthDest,int nHeightDest,HDC hdcSrc,
			int nXOriginSrc,int nYOriginSrc,int nWidthSrc,int nHeightSrc,UINT crTransparent);	
	
	CRect GetTitleBarRect(CDC *pWinDC);											//��ñ���������
	
	CRect DrawBtnBmp(CDC *pWinDC, UINT nIDBmp, CRect rect=NULL);					
public:
	void SetTitleFontSize(WORD nFontW,WORD nFontH);								//���ñ�������
	
	void SetTitleColor(COLORREF clrTitle);										//���ñ�����ɫ

	BOOL DrawIcon(CDC *pWinDC,UINT idIcon,int nLeftSpace);					
	
	BOOL DrawTitle(CDC *pWinDC,CString strTitle,int nLeftSpace);				//���ƴ��ڱ���
	
	BOOL DrawTitleBar(CDC *pWinDC,COLORREF clrTop,COLORREF clrBottom);			//���Ʊ�����
	
	BOOL DrawBorder(CDC *pWinDC,COLORREF color,int nLefOffset=0,int nTopOffset=0,int nRitOffset=0,int nBtmOffset=0);
	
	BOOL InterceptMessage(UINT msg,HWND hWnd,CPoint point,UINT nIDClose=0,UINT nIDMax=0,UINT nIDRestore=0,UINT nIDMin=0);

	BOOL InterceptMessage(UINT msg, HWND hWnd,WPARAM wParam, LPARAM lParam);
	
	BOOL DrawSystemBtn(CDC *pWinDC,UINT nIDClose=0,UINT nIDMax=0,UINT nIDRestore=0,UINT nIDMin=0);
	
	BOOL DrawBackground(CDC *pWinDC,CRect *pDesRect,COLORREF clrBrush,UINT nIDBitmap,BOOL bCenter=FALSE,
			BOOL bTransparent=FALSE,COLORREF clrTransparent=0);	
	void DrawDlg(CDC *pWinDC, COLORREF colorValue);//����ɫ���
	void DrawDlg(CDC *pWinDC,UINT LeftBmp,UINT RightBmp,UINT ButtomBmp,UINT TitleBmp);
	void DrawTitleBar(CDC *pWinDC,COLORREF color);
	void DrawSystemBtn1(CDC *pWinDC,UINT nIDSysBtn);
};

#endif // !defined(AFX_DRAWAPPEARANCE_H__D181D9FE_00B4_42F3_9432_37A4027770DD__INCLUDED_)

#ifndef _CDRAWEDIT_H
#define _CDRAWEDIT_H
//����༭����
class CDrawEdit
{
public:
	WNDPROC     m_OldProc;         //��¼�༭��Ĵ��ں���
	int         m_Flag;
	CBrush      m_brush;
	CRect       m_rect;
	static int  m_Style; 
public:
	CDrawEdit()
	{
		m_OldProc = NULL;
		m_Flag = 0;
	}

	void OnErasebkgnd(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		CDC* dc = CDC::FromHandle(HDC(wParam));	//��ȡ��������
		/*CPaintDC dc(CWnd::FromHandle(hWnd)); */
		dc->FrameRect(m_rect, &m_brush);		    //���Ʊ߿�
	}

	void OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		GetClientRect(hWnd, m_rect);			    //��ȡ�ͻ�����
		m_rect.InflateRect(1, 1, 1, 1);		    //���ͻ���������һ������
		m_brush.DeleteObject();
		m_brush.CreateSolidBrush(RGB(0, 64, 255));	//������ˢ
	}

	//�༭�򴰿ں���
	static LRESULT CALLBACK EditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		CPoint pt;
		CDrawEdit *pEdit = (CDrawEdit*)GetWindowLong(hWnd, GWL_USERDATA);
		switch (uMsg)
		{
		case WM_CREATE:
		{
						  TRACE("Edit����WM_CREATE\n");
						  pEdit->OnCreate(hWnd, wParam, lParam);
						  break;
		}
		case WM_ERASEBKGND:
		{
			TRACE("Edit����WM_ERASEBKGND\n");
			pEdit->OnErasebkgnd(hWnd, wParam, lParam);
							  break;
		}
		case WM_PAINT:
		{
							  TRACE("Edit����WM_ERASEBKGND\n");
							  pEdit->OnErasebkgnd(hWnd, wParam, lParam);
							  break;
		}

		case WM_DESTROY:
		{
						   SetWindowLong(hWnd, GWL_WNDPROC, (long)pEdit->m_OldProc); //�ָ�ԭ���Ĵ��ں���
						   CWnd* pWnd = ::CWnd::FromHandle(hWnd);			//����ť������������
						   if (pWnd)
						   {
							   pWnd->Detach();
						   }
						   pEdit->m_Flag = 1;
						   delete pEdit;
						   return 0;
		}

		default:
		{
				   break;
		}
		}
		return CallWindowProc(pEdit->m_OldProc, hWnd, uMsg, wParam, lParam);
	}
};
int CDrawEdit::m_Style = 1;

#endif//
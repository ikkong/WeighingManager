#ifndef __TOOLBAREX_H__
#define __TOOLBAREX_H__

class CToolBarEx :public CToolBar
{
public:


protected:
	//{{AFX_MSG(CSXBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);     //������Ϣ��Ӧ����
	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
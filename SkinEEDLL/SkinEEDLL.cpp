// SkinEEDLL.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "include\SkinEEApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Ψһ��Ӧ�ó������
CWinApp theApp;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
    int nRetCode = 0;

    // ��ʼ�� MFC ����ʧ��ʱ��ʾ����
    if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
    {
        // TODO: ���Ĵ�������Է���������Ҫ
        _tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
        nRetCode = 1;
    }
    else
    {
        // TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
    }

    return nRetCode;
}
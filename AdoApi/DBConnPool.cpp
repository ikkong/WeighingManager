
#include "stdafx.h"
#include "DBConnPool.h"
#include <tchar.h>


//////////////////////////////////////DBConnect/////////////////////////
DBConnect::DBConnect(LPCSTR strConnect,BOOL &state)
{
	m_bDBOpen = false;
	if (0 == Open(strConnect))
	{
		state =true;
	}
	else
	{
		state = false;
	}
}
DBConnect::~DBConnect()
{
	Close();
}
int DBConnect::Open(LPCSTR strConnect)
{
	HRESULT hr = ::CoInitialize(NULL);
	if (FAILED(hr))
	{
		return -1;
	}

	hr = m_pAdoConn.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
	{
		return -1;
	}
	/*m_pAdoConn->ConnectionTimeout = COMMAND_TIMEOUT;
	m_pAdoConn->CommandTimeout = CONNECT_TIMEOUT;*/

	try
	{
		// ���ӵ������������ݿ�
		hr =m_pAdoConn->Open((bstr_t)strConnect, "", "",adModeUnknown) ;
		if (FAILED(hr))
			return -1;
	}
	catch (_com_error e)
	{
		MessageBox(NULL,e.Description(),_T("��ʾ") ,1);
		//throw e;
		//OutputDebugString(_T("���ݿ����ʧ��"));
		/*char *szlog=NULL;
		sprintf(szlog, "���ݿ����ʧ��! ������Ϣ:%s, �ļ�:%s, ��:%d./n", e.Description(), __FILE__, __LINE__);*/
		//TRACE(_T("���ݿ����ʧ��! ������Ϣ:%s, �ļ�:%s, ��:%d./n"), err.ErrorMessage(), __FILE__, __LINE__);
		return -1;
	}
	m_bDBOpen = TRUE;
	return 0;
}
int DBConnect::Close()
{
	if (m_bDBOpen)
	{
		HRESULT hr =m_pAdoConn->Close();

		if (FAILED(hr))
		{
			return -1;
		}
		::CoUninitialize();
		m_bDBOpen = FALSE;
	}

	return 0;
}

LRESULT  DBConnect::QuerySQL(LPCSTR bstrSQL, _RecordsetPtr& pRecordset, CursorTypeEnum cursorType, LockTypeEnum lockType)
{
	if (!m_bDBOpen||m_pAdoConn->GetState()!=ADODB::adStateOpen)
	{
		return -1;
	}

	try
	{
		pRecordset.CreateInstance(__uuidof(Recordset));
		pRecordset->Open((_bstr_t)bstrSQL, m_pAdoConn.GetInterfacePtr(), cursorType /*adOpenStatic*/ /*adOpenDynamic*/, lockType/*adLockOptimistic*/, adCmdText);
	}
	catch(_com_error e)
	{
		MessageBox(NULL,e.Description(),_T("��ʾ") ,1);
		throw e;
	}
	return 0;
}

LRESULT  DBConnect::ExecuteProcSQL(LPCSTR storeProcStr)
{
	if (!m_bDBOpen||m_pAdoConn->GetState()!=ADODB::adStateOpen)
	{
		return -1;
	}

	HRESULT hr = m_pCommand.CreateInstance(__uuidof(Command));

	try
	{
		m_pCommand.CreateInstance("ADODB.Command");
		m_pCommand->ActiveConnection = m_pAdoConn;

		m_pCommand->CommandText = (_bstr_t)storeProcStr;//�洢����ΪTest
		m_pCommand->CommandType = adCmdStoredProc;
	}
	catch(_com_error e)
	{
		MessageBox(NULL,e.Description(),_T("��ʾ") ,1);
		throw e;
	}
	return 0;//�ɹ�
}

LRESULT  DBConnect::ExecuteSQL(LPCSTR lpszSQL)
{
	if (!m_bDBOpen||m_pAdoConn->GetState()!=ADODB::adStateOpen)
	{
		return -1;
	}

	_bstr_t bstrSQL = (_bstr_t)lpszSQL;
	_variant_t RecordsAffected;//����Ӱ��ļ�¼���� ������Ӧ���Ƿ���1��

	try
	{
		m_pAdoConn->Execute(bstrSQL,&RecordsAffected,(LONG)-1);
	}
	catch(_com_error e)
	{
		MessageBox(NULL,e.Description(),_T("��ʾ") ,1);
		throw e;
	}
	return (long)RecordsAffected;
}

//////////////////////////////////////End//////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DBConnPool* DBConnPool::m_pInstanse = NULL;
DBConnPool::DBConnPool()
{
	m_bNeedStop = FALSE;
	m_bNeedConnection = FALSE;
	m_hMaintanceThread = INVALID_HANDLE_VALUE;

	// �߳̿���
	m_hHaveData = CreateEvent (NULL, TRUE, FALSE, _T("DataConnPool"));


	InitializeCriticalSection(&m_csIdleConnList);
	InitializeCriticalSection(&m_csBusyConnList);
}

void DBConnPool::SetDBInfo(LPCSTR strConnect ,int minConn, int maxConn)
{
	_strConnect=strConnect;
	m_nMaxCount = maxConn;
	m_nMinCount = minConn;
}

DBConnPool::~DBConnPool()
{
	m_hMaintanceThread = INVALID_HANDLE_VALUE;
	m_bNeedStop = TRUE;
	CloseHandle(m_hHaveData);
	CloseHandle(m_hMaintanceThread);

	DeleteCriticalSection(&m_csIdleConnList);
	DeleteCriticalSection(&m_csBusyConnList);
}

DBConnPool *DBConnPool::Instanse()
{
	if (NULL == m_pInstanse)
	{
		m_pInstanse = new DBConnPool();
	}
	return m_pInstanse;
}

int DBConnPool::InitializeAllDBConnections()
{
	// ���߹������е�����
	DestroyAllDBConnections();
	// ��ʼ������С������ʼ����
	DBConnect* pDBConnect = NULL;
	int nCount = 0;
	for (unsigned int i = 0; i < m_nMinCount; i++)
	{
		nCount = InitializeAConnection();
	}
	// ����һ�������̣߳���������һЩ��̨ά������
	if (INVALID_HANDLE_VALUE == m_hMaintanceThread)
	{
		m_hMaintanceThread = CreateThread(NULL, NULL, thread_run, (LPVOID)this, 0, NULL);
	}
	return nCount;
}

void DBConnPool::DestroyAllDBConnections()
{
	// �������ݿ����ӿ���ʹ�ô���
	EnterCriticalSection(&m_csIdleConnList);
	DBConnectList::iterator itIdle = m_listIdleConnection.begin();
	DBConnectList::iterator itIdleEnd = m_listIdleConnection.end();
	while (itIdle != itIdleEnd)
	{
		if (NULL != (*itIdle))
		{
			(*itIdle)->Close();
			delete (*itIdle);
		}
		// erase����ͻ�ѵ�����ָ����һ��
		itIdle = m_listIdleConnection.erase(itIdle);
	}
	LeaveCriticalSection(&m_csIdleConnList);
	// ����ʹ���е�����
	EnterCriticalSection(&m_csBusyConnList);
	DBConnectList::iterator itBusy = m_listBusyConnection.begin();
	DBConnectList::iterator itBusyEnd = m_listBusyConnection.end();
	while (itBusy != itBusyEnd)
	{
		if (NULL != (*itBusy))
		{
			(*itBusy)->Close();
			delete (*itBusy);
		}
		// erase����ͻ�ѵ�����ָ����һ��
		itBusy = m_listBusyConnection.erase(itBusy);
	}
	LeaveCriticalSection(&m_csBusyConnList);
}

int DBConnPool::InitializeAConnection()
{
	BOOL bSuccess = FALSE;
	DBConnect* pDBEngine = new DBConnect(_strConnect, bSuccess);
	if (bSuccess)
	{
		m_bNeedConnection = FALSE;
		return RestoreAConnection(pDBEngine);
	}
	else
	{
		delete pDBEngine;
		return m_listIdleConnection.size();
	}
}

void DBConnPool::CloseAConnection(DBConnect* pDBEngine)
{
	pDBEngine->Close();
	// �ӿ��ж��н���ɾ��
	EnterCriticalSection(&m_csIdleConnList);
	m_listIdleConnection.remove(pDBEngine);
	LeaveCriticalSection(&m_csIdleConnList);
}

DBConnect* DBConnPool::GetAConnection()
{
	DBConnect * pDBEngine = NULL;
	// ��һ��ѭ���������������ȡ���ӣ�ÿ�μ��1����
	int nTimes = 0;
	while ((m_listIdleConnection.size() <= 0) && (nTimes < 5))
	{
		Sleep(1000);
		nTimes++;
	}
	if (5 == nTimes)
	{
		// �����Ǳ��Ľ����϶���û�п��������ˣ���¼��־�˳�
		// g_pSvrLog->AddRunLog(LL_ERROR, _T("Waiting for a connection for a long time, but failed."));
		return pDBEngine;
	}
	// �ӿ��ж�����ȡ�������Ҽ��뵽ʹ�ö�����
	EnterCriticalSection(&m_csIdleConnList);
	if (m_listIdleConnection.size() > 0)
	{
		pDBEngine = m_listIdleConnection.front();
		m_listIdleConnection.pop_front();
		// ����ʹ�õ����Ӷ���
		EnterCriticalSection(&m_csBusyConnList);
		m_listBusyConnection.push_back(pDBEngine);
		LeaveCriticalSection(&m_csBusyConnList);
	}
	LeaveCriticalSection(&m_csIdleConnList);
	if (m_listIdleConnection.size() <= 1)
	{
		// ʣ��������ӵ���ĿС�ڵ���1��ʱ����Ҫ��鿪ʼ����
		if ((m_listIdleConnection.size() + m_listBusyConnection.size()) < m_nMaxCount)
		{
			// ��С��������ƣ����Դ���
			SetEvent(m_hHaveData);
			m_bNeedConnection = TRUE;
		}
		else
		{
			// ���������ˣ�������¼��
			//g_pSvrLog->AddRunLog(LL_ERROR, _T("Database connection reached max count."));
		}
	}
	return pDBEngine;
}

int DBConnPool::RestoreAConnection(DBConnect* pDBEngine)
{
	if (NULL != pDBEngine)
	{
		// ��ʹ���еĶ���ȡ��
		EnterCriticalSection(&m_csBusyConnList);
		m_listBusyConnection.remove(pDBEngine);
		LeaveCriticalSection(&m_csBusyConnList);
		// ���뵽���ж�����
		EnterCriticalSection(&m_csIdleConnList);
		m_listIdleConnection.push_back(pDBEngine);
		LeaveCriticalSection(&m_csIdleConnList);
	}
	EnterCriticalSection(&m_csIdleConnList);
	int nCount = m_listIdleConnection.size();
	LeaveCriticalSection(&m_csIdleConnList);
	return nCount;
}

void DBConnPool::StopThread()
{
	m_bNeedStop = TRUE;
	// ��Ϊ�߳��������Ƶȴ��źŵģ����������Ȱѱ�־λ��Ϊֹͣ��Ȼ���ź����̼߳��
	SetEvent(m_hHaveData);
	// �ȴ��˳�
	WaitForSingleObject(m_hMaintanceThread, INFINITE);
	CloseHandle(m_hMaintanceThread);
}

BOOL DBConnPool::IsNeedStop()
{
	return m_bNeedStop;
}

BOOL DBConnPool::IsNeedConnection()
{
	return m_bNeedConnection;
}
/************************************************************************/
/* ά���߳�                                                             */
/************************************************************************/
DWORD WINAPI DBConnPool::thread_run( LPVOID pdata)
{
	DBConnPool * pConPool = (DBConnPool *) pdata;
	while (!pConPool->IsNeedStop())
	{
		// �����¼�Ϊ���ź�, ���������Ƶȴ�
		ResetEvent(pConPool->m_hHaveData);  
		WaitForSingleObject(pConPool->m_hHaveData, INFINITE);
		if (pConPool->IsNeedConnection())
		{
			// g_pSvrLog->AddRunLog(LL_DEBUG, _T("Create a new DB connection."));
			pConPool->InitializeAConnection();
		}
	}
	return 0;
}

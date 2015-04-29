#ifndef DBCONNPOOL_H
#define DBCONNPOOL_H

#include "stdafx.h"
#include <list>
#include <string>

#define  SQL_BUFFER_LEN 1024
#define  COMMAND_TIMEOUT 2000
#define  CONNECT_TIMEOUT 2000

class  DBConnect
{
public:
	 DBConnect(LPCSTR strConnect,BOOL &state);
	~DBConnect();
public:
	// ���ӵ����ݿ�
	int Open(LPCSTR strConnect);
	// �ر����ݿ�
	int Close();
	// ���ݿ��Ƿ�������
	BOOL IsOpen() const;

private:
	ADODB::_ConnectionPtr     m_pAdoConn;   //ADO�����ݿ���������ָ��
	ADODB::_CommandPtr        m_pCommand;
	bool                      _isAdoValid;       //ADO�����Ƿ��Ѿ������ɹ���־��
	bool                      m_bDBOpen;

	LPCSTR       _strDstAddress;    //����Դ��ַ�������
	LPCSTR       _strUsername;      //���ݿ��û���
	LPCSTR       _strPassword;      //���ݿ�����
	LPCSTR       _strDBName;        //���ݿ�����
	//void         VarientToString(_variant_t var, string& str);
	//���⹫���ӿ�
public:
	LRESULT	   ExecuteSQL(LPCSTR lpszSQL);//ִ��sql��� ������Ӽ�¼��
	LRESULT    ExecuteProcSQL(LPCSTR storeProcStr);
	LRESULT    QuerySQL(LPCSTR lpszSQL, _RecordsetPtr& pRecordset, CursorTypeEnum cursorType = adOpenForwardOnly, LockTypeEnum lockType = adLockReadOnly);
	LRESULT    UserLogin(LPCSTR name,LPCSTR password);
}; 
typedef std::list<DBConnect*> DBConnectList;

class  DBConnPool  
{
public:
	DBConnPool();
	virtual ~DBConnPool();
	// ��ȡʵ��ָ��
	static DBConnPool* Instanse();
	// ��ʼ����������
	int InitializeAllDBConnections();

	// �ر���������
	void DestroyAllDBConnections();
	// ��ȡһ����������
	DBConnect* GetAConnection();
	// �������Ӹ����ж���
	int RestoreAConnection(DBConnect* pDBEngine);
	void SetDBInfo(LPCSTR strConnect,int minConn,int maxConn);
private:
 
	// ����һ������
	int InitializeAConnection();
	// �ر�һ������
	void CloseAConnection(DBConnect* pDBEngine);
	// ֹͣ�����߳�
	void StopThread();

	// �ж��Ƿ���Ҫֹͣ
	BOOL IsNeedStop();
	BOOL IsNeedConnection();
	// ����������Ϊ���ӳ������Ԫ��
	friend class ConnGuard;
	// Ψһʵ��
	static DBConnPool *m_pInstanse;

	// �������ݿ����Ӷ���
	DBConnectList m_listIdleConnection;
	// ��ʹ�õ����ݿ�����
	DBConnectList m_listBusyConnection;

	// ���б������ٽ���
	CRITICAL_SECTION m_csIdleConnList;
	CRITICAL_SECTION m_csBusyConnList;

	// ������������������ָ�꣺�����С
	unsigned int m_nMaxCount;
	unsigned int m_nMinCount;

	// ���ݿ���Ϣ
	LPCSTR       _strDstAddress;    //����Դ��ַ�������
	LPCSTR       _strUsername;      //���ݿ��û���
	LPCSTR       _strPassword;      //���ݿ�����
	LPCSTR       _strDBName;        //���ݿ�����
	LPCSTR       _strConnect;       //�����ַ���

	// ά���߳�
	HANDLE m_hMaintanceThread; // �߳̾��
	HANDLE m_hHaveData; // �ź�

	BOOL m_bNeedStop; // �����߳���ͣ�ı�־λ
	BOOL m_bNeedConnection; // ��Ҫ�������ӵı�־
	static DWORD WINAPI thread_run( LPVOID pdata);
};
// �����࣬���ù��������������֤����ȡ���͹黹����ɶԣ���ֹ��Դй¶
class  DBConnGuard
{
public:
	DBConnGuard(DBConnect*& DBConn)
	{
		DBConn = DBConnPool::Instanse()->GetAConnection();
		m_pDBConn = DBConn;
	}
	virtual ~DBConnGuard()
	{
		DBConnPool::Instanse()->RestoreAConnection(m_pDBConn);
	}
private:
	DBConnect *m_pDBConn;
};
#endif // !defined(AFX_DBCONNPOOL_H__42089E9A_FD85_4DD4_A973_64A4980332A5__INCLUDED_)

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// ��ѯ�̺߳���
UINT ThreadFuncSer(LPVOID lpParam);

// ��ѯ�̺߳����Ľṹ��
struct threadSearch
{
	// list control
	CListCtrl *ts_pList;
	// ���ݿ�ָ��
	MYSQL *ts_pConn;
	// sql���
	CString ts_sql;
	// �ɼ�����־������ϵͳ��Ӧ�ó���
	CString ts_logName;
};
// SEARCH �Ի���

class SEARCH : public CDialogEx
{
	DECLARE_DYNAMIC(SEARCH)

public:
	SEARCH(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SEARCH();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	MYSQL *conn;
	CString m_sbox;
	HANDLE hThread;                                      //�߳̾��
	DWORD ThreadID;                                      //�߳�ID
public:
	// ��ѯҳ��� Combo Box
	CComboBox m_comboxSer;
	// ��ѯҳ���list control
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButtonSearch();
	// ��ѯ������
	CDateTimeCtrl m_dateSer;
	afx_msg void OnBnClickedBtOutexcel();
	// ��ѯʱ�Ľ�����
	CProgressCtrl m_progressSave;
	CButton m_Chart;
	afx_msg void OnBnClickedButton1();
};

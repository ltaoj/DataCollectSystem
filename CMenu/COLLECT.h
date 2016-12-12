#pragma once
#include "afxcmn.h"
#include "afxwin.h"
/**************************************************/
//2016-07-11 20:24 add by li//
//�����̺߳���
UINT ThreadFunc(LPVOID lpParam);
//���屣���̺߳���
UINT ThreadFuncSave(LPVOID lpParam);
//����ṹ��
struct threadInfo
{
	//�ṹ��
	CListCtrl *ti_list;
	//CDataCollecctSysDlg ti_dlg;
	MYSQL *ti_conn;

	CString ti_strbox;
};
// COLLECT �Ի���
/***************************************************/
class COLLECT : public CDialogEx
{
	DECLARE_DYNAMIC(COLLECT)

public:
	COLLECT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COLLECT();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COLLECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	/***************************************************************/
	//2016-07-11 20:24 add by li
	MYSQL *conn;                                         //���ݿ�ָ��
	HANDLE hThread;                                      //�߳̾��
	DWORD ThreadID;                                      //�߳�ID
	HANDLE hSaveThread;                                      //�߳̾��
	DWORD SaveThreadID;                                      //�߳�ID
	/***************************************************************/

public:
	// �ɼ����б�
	CListCtrl m_Grid;
	// �ռ�ҳ�濪ʼ��ť
	CButton m_COL_Start;
	// ��ѯ������ͣ��ť
	CButton m_COL_Pause;
	// �ɼ�����ֹͣ��ť
	CButton m_COL_Resume;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtStart();
	afx_msg void OnBnClickedBtPause();
	afx_msg void OnBnClickedBtResume();
	// �����б���Ͽ�
	CComboBox m_combox;
	//���������û������б��ѡ�е��ַ���
	CString m_strBox;
	afx_msg void OnCbnSelchangeComboCollect();
	// ��ʾ��ǰ�ɼ�����Ϣ״̬
	CEdit m_colstate;
	afx_msg void OnBnClickedBtSave();
};

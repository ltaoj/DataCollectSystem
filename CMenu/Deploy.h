#pragma once
#include "afxcmn.h"


// Deploy �Ի���

class Deploy : public CDialogEx
{
	DECLARE_DYNAMIC(Deploy)

public:
	Deploy(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Deploy();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEPLOY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ϵͳ�ɼ�Ƶ��
	CString m_frequency;
	// ���ݿ���
	CString m_dbName;
	// �û���
	CString m_userName;
	// ����
	CString m_password;
	afx_msg void OnBnClickedBtIniok();
	// ip���Ʊ���
	CIPAddressCtrl m_ip;
};

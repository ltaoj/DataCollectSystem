#pragma once
#include "afxwin.h"


// LOGIN �Ի���

class LOGIN : public CDialogEx
{
	DECLARE_DYNAMIC(LOGIN)

public:
	LOGIN(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LOGIN();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��¼������˻�
	CEdit m_Login_Name;
	// ��¼���������
	CEdit m_Login_No;
	// ��¼��ť
	CButton m_LoginBt_Login;
	// ע�ᰴť
	CButton m_LoginBt_Regist;
	afx_msg void OnBnClickedButton1();
};

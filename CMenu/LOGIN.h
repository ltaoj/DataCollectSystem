#pragma once
#include "afxwin.h"


// LOGIN 对话框

class LOGIN : public CDialogEx
{
	DECLARE_DYNAMIC(LOGIN)

public:
	LOGIN(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LOGIN();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 登录界面的账户
	CEdit m_Login_Name;
	// 登录界面的密码
	CEdit m_Login_No;
	// 登录按钮
	CButton m_LoginBt_Login;
	// 注册按钮
	CButton m_LoginBt_Regist;
	afx_msg void OnBnClickedButton1();
};

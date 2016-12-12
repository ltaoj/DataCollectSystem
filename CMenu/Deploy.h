#pragma once
#include "afxcmn.h"


// Deploy 对话框

class Deploy : public CDialogEx
{
	DECLARE_DYNAMIC(Deploy)

public:
	Deploy(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Deploy();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEPLOY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 系统采集频率
	CString m_frequency;
	// 数据库名
	CString m_dbName;
	// 用户名
	CString m_userName;
	// 密码
	CString m_password;
	afx_msg void OnBnClickedBtIniok();
	// ip控制变量
	CIPAddressCtrl m_ip;
};

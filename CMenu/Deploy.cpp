// Deploy.cpp : 实现文件
//

#include "stdafx.h"
#include "CMenu.h"
#include "Deploy.h"
#include "afxdialogex.h"


// Deploy 对话框

IMPLEMENT_DYNAMIC(Deploy, CDialogEx)

Deploy::Deploy(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DEPLOY, pParent)
	, m_dbName(_T(""))
	, m_userName(_T(""))
	, m_password(_T(""))
	, m_frequency(_T(""))
{

}

Deploy::~Deploy()
{
}

void Deploy::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX, IDC_EDIT_DBNAME, m_dbName);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_userName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_CBString(pDX, IDC_COMBO_FRE, m_frequency);
	DDX_Control(pDX, IDC_IPADDRESS_HOST, m_ip);
}


BEGIN_MESSAGE_MAP(Deploy, CDialogEx)
	ON_BN_CLICKED(IDC_BT_INIOK, &Deploy::OnBnClickedBtIniok)
END_MESSAGE_MAP()


// Deploy 消息处理程序

// 添加系统配置确定响应事件
void Deploy::OnBnClickedBtIniok()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);  //获取控件上的变量值

	int m_iAppCheck = IsDlgButtonChecked(IDC_CHECK_APP);  //获取应用程序复选框的选中状态
	int m_iSysCheck = IsDlgButtonChecked(IDC_CHECK_SYS);  //获取系统复选框的选中状态
	int m_iSecCheck = IsDlgButtonChecked(IDC_CHECK_SEC);  //获取安全复选框的选中状态

	CString m_ipAddress;
	unsigned char* pIP;
	DWORD dwIP;
	m_ip.GetAddress(dwIP);
	pIP = (unsigned char*)&dwIP;
	m_ipAddress.Format("%u.%u.%u.%u", *(pIP + 3), *(pIP + 2), *(pIP + 1), *(pIP));


	if (::WritePrivateProfileString("系统采集频率", "frequency", m_frequency, "..\\myDefault.ini") &&
		::WritePrivateProfileString("采集应用日志", "appevent_log", m_iAppCheck ? "1" : "0", "..\\myDefault.ini") &&
		::WritePrivateProfileString("采集系统日志", "system_log", m_iSysCheck ? "1" : "0", "..\\myDefault.ini") &&
		::WritePrivateProfileString("采集安全日志", "security_log", m_iSecCheck ? "1" : "0", "..\\myDefault.ini") &&
		::WritePrivateProfileString("服务器", "servername", m_ipAddress, "..\\myDefault.ini") &&
		::WritePrivateProfileString("数据库名称", "databasename", m_dbName, "..\\myDefault.ini") &&
		::WritePrivateProfileString("用户名", "username", m_userName, "..\\myDefault.ini") &&
		::WritePrivateProfileString("密码", "password", m_password, "..\\myDefault.ini"))
	{
		AfxMessageBox("系统配置完成");
	}
	else
	{
		AfxMessageBox("系统配置失败");
	}

}

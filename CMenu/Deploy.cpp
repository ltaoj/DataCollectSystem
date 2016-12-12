// Deploy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMenu.h"
#include "Deploy.h"
#include "afxdialogex.h"


// Deploy �Ի���

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


// Deploy ��Ϣ�������

// ���ϵͳ����ȷ����Ӧ�¼�
void Deploy::OnBnClickedBtIniok()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);  //��ȡ�ؼ��ϵı���ֵ

	int m_iAppCheck = IsDlgButtonChecked(IDC_CHECK_APP);  //��ȡӦ�ó���ѡ���ѡ��״̬
	int m_iSysCheck = IsDlgButtonChecked(IDC_CHECK_SYS);  //��ȡϵͳ��ѡ���ѡ��״̬
	int m_iSecCheck = IsDlgButtonChecked(IDC_CHECK_SEC);  //��ȡ��ȫ��ѡ���ѡ��״̬

	CString m_ipAddress;
	unsigned char* pIP;
	DWORD dwIP;
	m_ip.GetAddress(dwIP);
	pIP = (unsigned char*)&dwIP;
	m_ipAddress.Format("%u.%u.%u.%u", *(pIP + 3), *(pIP + 2), *(pIP + 1), *(pIP));


	if (::WritePrivateProfileString("ϵͳ�ɼ�Ƶ��", "frequency", m_frequency, "..\\myDefault.ini") &&
		::WritePrivateProfileString("�ɼ�Ӧ����־", "appevent_log", m_iAppCheck ? "1" : "0", "..\\myDefault.ini") &&
		::WritePrivateProfileString("�ɼ�ϵͳ��־", "system_log", m_iSysCheck ? "1" : "0", "..\\myDefault.ini") &&
		::WritePrivateProfileString("�ɼ���ȫ��־", "security_log", m_iSecCheck ? "1" : "0", "..\\myDefault.ini") &&
		::WritePrivateProfileString("������", "servername", m_ipAddress, "..\\myDefault.ini") &&
		::WritePrivateProfileString("���ݿ�����", "databasename", m_dbName, "..\\myDefault.ini") &&
		::WritePrivateProfileString("�û���", "username", m_userName, "..\\myDefault.ini") &&
		::WritePrivateProfileString("����", "password", m_password, "..\\myDefault.ini"))
	{
		AfxMessageBox("ϵͳ�������");
	}
	else
	{
		AfxMessageBox("ϵͳ����ʧ��");
	}

}

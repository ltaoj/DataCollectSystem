/ LOGIN.cpp : 实现文件
//

#include "stdafx.h"
#include "CMenu.h"
#include "LOGIN.h"
#include "afxdialogex.h"


// LOGIN 对话框

IMPLEMENT_DYNAMIC(LOGIN, CDialogEx)

LOGIN::LOGIN(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
{

}

LOGIN::~LOGIN()
{
}

void LOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Login_Name);
	DDX_Control(pDX, IDC_EDIT2, m_Login_No);
	DDX_Control(pDX, IDC_BUTTON1, m_LoginBt_Login);
	DDX_Control(pDX, IDC_BUTTON2, m_LoginBt_Regist);
}


BEGIN_MESSAGE_MAP(LOGIN, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &LOGIN::OnBnClickedButton1)
END_MESSAGE_MAP()


// LOGIN 消息处理程序


void LOGIN::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

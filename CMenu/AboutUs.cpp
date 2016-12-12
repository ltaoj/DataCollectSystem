// AboutUs.cpp : 实现文件
//

#include "stdafx.h"
#include "CMenu.h"
#include "AboutUs.h"
#include "afxdialogex.h"


// AboutUs 对话框

IMPLEMENT_DYNAMIC(AboutUs, CDialogEx)

AboutUs::AboutUs(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ABOUT, pParent)
{

}

AboutUs::~AboutUs()
{
}

void AboutUs::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutUs, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &AboutUs::OnBnClickedButton1)
	ON_COMMAND(ID_ABOUT, &AboutUs::OnAbout)
END_MESSAGE_MAP()


// AboutUs 消息处理程序


void AboutUs::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void AboutUs::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	AboutUs dlg;
	dlg.DoModal();

}

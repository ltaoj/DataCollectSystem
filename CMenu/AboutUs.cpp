// AboutUs.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMenu.h"
#include "AboutUs.h"
#include "afxdialogex.h"


// AboutUs �Ի���

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


// AboutUs ��Ϣ�������


void AboutUs::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void AboutUs::OnAbout()
{
	// TODO: �ڴ���������������
	AboutUs dlg;
	dlg.DoModal();

}

// About.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMenu.h"
#include "About.h"
#include "afxdialogex.h"


// About �Ի���

IMPLEMENT_DYNAMIC(About, CDialogEx)

About::About(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ABOUTUS, pParent)
{

}

About::~About()
{
}

void About::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(About, CDialogEx)
END_MESSAGE_MAP()


// About ��Ϣ�������

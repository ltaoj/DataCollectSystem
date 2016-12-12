// Computer.cpp : 实现文件
//

#include "stdafx.h"
#include "CMenu.h"
#include "Computer.h"
#include "afxdialogex.h"
#include "CPUInfo.h"

// Computer 对话框

IMPLEMENT_DYNAMIC(Computer, CDialogEx)

Computer::Computer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_COM, pParent)
	, m_cpuProductor(_T(""))
	, m_cpuType(_T(""))
	, m_cpuBasicFre(0)
{

}

Computer::~Computer()
{
}

void Computer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BASICFRE, m_cpuBasicFre);
	DDX_Text(pDX, IDC_EDIT_PRODUCT, m_cpuProductor);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_cpuType);
	DDX_Text(pDX, IDC_EDIT_BASICFRE, m_cpuBasicFre);
}


BEGIN_MESSAGE_MAP(Computer, CDialogEx)
END_MESSAGE_MAP()


// Computer 消息处理程序


BOOL Computer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CCPUInfo cpuInfo;
	m_cpuBasicFre = cpuInfo.GetCPUFreq();
	m_cpuProductor = cpuInfo.GetManID();
	m_cpuType = cpuInfo.GetCPUType();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


// CMenuDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "COLLECT.h"

#include "mysql.h"
#include "About.h"
#include "Deploy.h"
#include "Computer.h"



// 2016-07-12  14:34 add by li 
// 查询页面添加新的对话框
#include "SEARCH.h"

#define WM_MYMSG (WM_USER + 0x7F)

// CCMenuDlg 对话框
class CCMenuDlg : public CDialogEx
{
// 构造
public:
	CCMenuDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMENU_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	COLLECT *colDlg;
	SEARCH *serDlg;
	About* aboutDlg;
	Computer* comDlg;
	Deploy* depDlg;

	// 添加查询对话框
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//2016-07-11 10:14 add by li
	MYSQL *conn;                                         //数据库指针
public:
	afx_msg LRESULT MyMsg(WPARAM wParam, LPARAM IParam);

	afx_msg void OnBnClickedBtExit();
	CStatic m_Pic_back;
	afx_msg void OnIdrMenu1();
	CButton m_BTbmp_Collect;
	// 查询的位图按钮
	CButton m_BTbmp_Search;
	// 系统的位图按钮
	CButton m_BTbmp_System;
	// 退出的位图按钮
	CButton m_BTbmp_Exit;
	// 背景
	CStatic m_PICbmp_Back;
	afx_msg void OnAbout();
	afx_msg void OnBnClickedBtCollect();
	afx_msg void OnBnClickedBtSearchcha();
	afx_msg void OnBnClickedBtSystem();
	afx_msg void OnMenuReg();

	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedBtComputer();
	afx_msg void OnBnClickedBtDeploy();
	afx_msg void OnBnClickedBtAbout2();
	// 配置按钮
	CButton m_deploy;
	// 关于我们
	CButton m_about;
	// 主机信息
	CButton m_computer;

	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);

	void OnSize(UINT nType, int cx, int cy);
	BOOL DestroyWindow();


	CToolTipCtrl m_Mytip;// 为按钮添加提示
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
/**************************************************/
//2016-07-11 20:24 add by li//
//声明线程函数
UINT ThreadFunc(LPVOID lpParam);
//定义保存线程函数
UINT ThreadFuncSave(LPVOID lpParam);
//定义结构体
struct threadInfo
{
	//结构体
	CListCtrl *ti_list;
	//CDataCollecctSysDlg ti_dlg;
	MYSQL *ti_conn;

	CString ti_strbox;
};
// COLLECT 对话框
/***************************************************/
class COLLECT : public CDialogEx
{
	DECLARE_DYNAMIC(COLLECT)

public:
	COLLECT(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COLLECT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COLLECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	/***************************************************************/
	//2016-07-11 20:24 add by li
	MYSQL *conn;                                         //数据库指针
	HANDLE hThread;                                      //线程句柄
	DWORD ThreadID;                                      //线程ID
	HANDLE hSaveThread;                                      //线程句柄
	DWORD SaveThreadID;                                      //线程ID
	/***************************************************************/

public:
	// 采集的列表
	CListCtrl m_Grid;
	// 收集页面开始按钮
	CButton m_COL_Start;
	// 查询界面暂停按钮
	CButton m_COL_Pause;
	// 采集界面停止按钮
	CButton m_COL_Resume;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtStart();
	afx_msg void OnBnClickedBtPause();
	afx_msg void OnBnClickedBtResume();
	// 下拉列表组合框
	CComboBox m_combox;
	//用来保存用户下拉列表框选中的字符串
	CString m_strBox;
	afx_msg void OnCbnSelchangeComboCollect();
	// 显示当前采集的信息状态
	CEdit m_colstate;
	afx_msg void OnBnClickedBtSave();
};

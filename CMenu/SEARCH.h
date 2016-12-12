#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// 查询线程函数
UINT ThreadFuncSer(LPVOID lpParam);

// 查询线程函数的结构体
struct threadSearch
{
	// list control
	CListCtrl *ts_pList;
	// 数据库指针
	MYSQL *ts_pConn;
	// sql语句
	CString ts_sql;
	// 采集的日志名，如系统，应用程序
	CString ts_logName;
};
// SEARCH 对话框

class SEARCH : public CDialogEx
{
	DECLARE_DYNAMIC(SEARCH)

public:
	SEARCH(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SEARCH();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	MYSQL *conn;
	CString m_sbox;
	HANDLE hThread;                                      //线程句柄
	DWORD ThreadID;                                      //线程ID
public:
	// 查询页面的 Combo Box
	CComboBox m_comboxSer;
	// 查询页面的list control
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButtonSearch();
	// 查询的日期
	CDateTimeCtrl m_dateSer;
	afx_msg void OnBnClickedBtOutexcel();
	// 查询时的进度条
	CProgressCtrl m_progressSave;
	CButton m_Chart;
	afx_msg void OnBnClickedButton1();
};

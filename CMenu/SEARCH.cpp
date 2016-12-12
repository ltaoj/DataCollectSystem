// SEARCH.cpp : 实现文件
//

#include "stdafx.h"
#include "CMenu.h"
#include "SEARCH.h"
#include "afxdialogex.h"
#include "OptExcel.h"
#include "Chart.h"


// 声明全局结构体
threadSearch tsInfo;
// 定义全局变量用来表示线程的状态
BOOL bThreadRun = FALSE;
//定义全局字符串,用于判断
CString strChange;
// SEARCH 对话框
IMPLEMENT_DYNAMIC(SEARCH, CDialogEx)

SEARCH::SEARCH(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SEARCH, pParent)
{
	hThread = NULL;
	conn = NULL;
}

SEARCH::~SEARCH()
{
}

void SEARCH::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboxSer);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_DT_SEA, m_dateSer);
	DDX_Control(pDX, IDC_BUTTON1, m_Chart);
}


BEGIN_MESSAGE_MAP(SEARCH, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &SEARCH::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &SEARCH::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BT_OUTEXCEL, &SEARCH::OnBnClickedBtOutexcel)
	ON_BN_CLICKED(IDC_BUTTON1, &SEARCH::OnBnClickedButton1)
END_MESSAGE_MAP()
// SEARCH 消息处理程序


BOOL SEARCH::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/*初始化数据库指针*/
	if ((conn = mysql_init(NULL)) == NULL)
	{
		AfxMessageBox("数据库指针初始化失败~");
		exit(1);
	}
	//设置数据库编码为GBK
	int ret = mysql_set_character_set(conn, "GBK");
	/*链接数据库:t_log , 根据用户查询需求，使用t_log中不同的表进行查询*/
	if (mysql_real_connect(conn, NULL, "root", "", "t_log", 0, NULL, 0) == NULL)
	{
		AfxMessageBox("数据库链接失败~");
		exit(1);
	}
	/*初始化 Combo Box 下拉项*/
	m_comboxSer.AddString("全部");
	m_comboxSer.AddString("信息");
	m_comboxSer.AddString("警告");
	m_comboxSer.AddString("错误");
	m_comboxSer.AddString("审核成功");
	m_comboxSer.AddString("审核失败");
	//初始化全局字符串
	strChange = "";
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//选择 ComBo Box 下拉项的响应事件 , m_sbox保存下拉项的字符串
void SEARCH::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strChange;
	int nSel = m_comboxSer.GetCurSel();
	m_comboxSer.GetLBText(nSel, strChange);
	if (m_sbox == "")
	{
		m_sbox = strChange;
	}

	if (!bThreadRun && strChange != m_sbox)
	{
		m_sbox = strChange;
	}
}


void SEARCH::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (bThreadRun)
	{
		AfxMessageBox("正在查询" + m_sbox + "日志信息");
		return;
	}
	else
	{
		// 退出当前线程，并且清空 list 列表

		if (hThread) {
			int listCount = tsInfo.ts_pList->GetItemCount();
			for (int i = 0;i < listCount;i++)
			{
				tsInfo.ts_pList->DeleteItem(0);
			}
		}
		hThread = NULL;
	}
	// AfxMessageBox(m_sbox);
	// 初始化sql语句,通过界面用户选择的信息,进行sql 语句的拼接        2016-07-13 18:32
	// 将Date Time Picker中时间用CTime保存日期
	// 将日期转换为 16-01-12 日期格式的字符串,字符串日期用m_sDate保存
	CTime m_date;
	CString m_sDate;
	m_dateSer.GetTime(m_date);
	m_sDate = m_date.Format("%y-%m-%d");
	//AfxMessageBox(m_sDate);
	CString sql;
	if (m_sbox == "全部" || m_sbox == "")
	{
		sql.Format("select *from t_log where DEL=%d and LogDate='%s'", 0, m_sDate);
	}
	else if (m_sbox == "信息")
	{
		sql.Format("select *from t_log where DEL=%d and LogType='%s' and LogDate='%s'", 0, "信息", m_sDate);
	}
	else if (m_sbox == "警告")
	{
		sql.Format("select *from t_log where DEL=%d and LogType='%s' and LogDate='%s'", 0, "警告", m_sDate);
	}
	else if (m_sbox == "错误")
	{
		sql.Format("select *from t_log where DEL=%d and LogType='%s' and LogDate='%s'", 0, "错误", m_sDate);
	}
	else if (m_sbox == "审核成功")
	{
		sql.Format("select *from t_log where DEL=%d and LogType='%s' and LogDate='%s'", 0, "审核成功", m_sDate);
	}
	else if (m_sbox == "审核失败")
	{
		sql.Format("select *from t_log where DEL=%d and LogType='%s' and LogDate='%s'", 0, "审核失败", m_sDate);
	}
	else
	{
		AfxMessageBox("程序错误");
		return;
	}
	// AfxMessageBox(sql);
	// 初始化 全局结构体
	tsInfo.ts_pConn = this->conn;
	tsInfo.ts_pList = &m_list;
	tsInfo.ts_sql = sql;
	tsInfo.ts_logName = m_sbox;
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFuncSer, &tsInfo, 0, &ThreadID);
}
// 实现***查询***线程函数
UINT ThreadFuncSer(LPVOID lpParam)
{
	bThreadRun = TRUE;

	threadSearch *pThreadInfo = (threadSearch *)lpParam;
	if (mysql_query(pThreadInfo->ts_pConn, pThreadInfo->ts_sql))
	{
		AfxMessageBox("查询错误");
	}
	else
	{
		MYSQL_RES *res_set;
		res_set = mysql_store_result(pThreadInfo->ts_pConn);
		if (res_set == NULL)
		{
			AfxMessageBox("没有找到符合条件的记录");
		}
		else
		{
			MYSQL_ROW row;
			int count = 0;

			while ((row = mysql_fetch_row(res_set)) != NULL)
			{
				// 将搜索到的***结果***逐条显示在  list control 
				pThreadInfo->ts_pList->InsertItem(count, row[5]);
				pThreadInfo->ts_pList->SetItemText(count, 1, row[2]);
				pThreadInfo->ts_pList->SetItemText(count, 2, row[3]);
				pThreadInfo->ts_pList->SetItemText(count, 3, row[6]);
				pThreadInfo->ts_pList->SetItemText(count, 4, row[7]);
				pThreadInfo->ts_pList->SetItemText(count, 5, row[4]);
				pThreadInfo->ts_pList->SetItemText(count, 6, row[8]);
				//pThreadInfo->ts_pList->SetItemText(count, 7, row[9]);
				//pThreadInfo->ts_pList->SetItemText(count, 8, row[10]);
				//pThreadInfo->ts_pList->SetItemText(count, 9, row[11]);
				pThreadInfo->ts_pList->SetItemText(count, 7, row[0]);
				count++;
			}
			CString sCount;
			sCount.Format("%d", count);
			AfxMessageBox("共有" + pThreadInfo->ts_logName + "日志信息" + sCount + "条");
		}
	}
	bThreadRun = FALSE;
	return 0;
}
// 导出Excel 响应事件
void SEARCH::OnBnClickedBtOutexcel()
{
	// TODO: 在此添加控件通知处理程序代码
	COptExcel excel;

	if (excel.ExportExcel(&m_list))
	{
		AfxMessageBox("导出完成！");
	}
	else
	{
		AfxMessageBox("导出失败！");
	}
}

CString GetType(int i)
{
	CString type = "";
	switch (i)
	{
	case 0:
		type = "信息";
		break;
	case 1:
		type = "警告";
		break;
	case 2:
		type = "错误";
		break;
	case 3:
		type = "审核成功";
		break;
	case 4:
		type = "审核失败";
		break;
	default:
		break;
	}
	return type;
}
// 2016-07-17 17:03 
// 通过该函数得到画统计图所需的数组
// 参数：sql语句，数据库指针
// 返回：记录的数目
int GetCount(CString sql, MYSQL *conn)
{
	int count = 0;
	if (mysql_query(conn, sql))
	{
		AfxMessageBox("统计出错了");
	}
	else
	{
		MYSQL_RES *res_set;
		res_set = mysql_store_result(conn);
		if (res_set != NULL)
		{
			MYSQL_ROW row;

			while ((row = mysql_fetch_row(res_set)) != NULL)
			{
				count++;
			}
		}
	}
	return count;
}
// 统计按钮的响应事件
void SEARCH::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	Chart dlg;
	CTime m_date;
	CString m_sDate;
	m_dateSer.GetTime(m_date);
	m_sDate = m_date.Format("%y-%m-%d");
	CString sql;
	CString type;
	for (int i = 0;i < 5;i++)
	{
		type = GetType(i);
		sql.Format("select *from t_log where DEL=%d and LogType='%s' and LogDate='%s'", 0, type, m_sDate);
		dlg.a[i] = GetCount(sql, conn);
	}
	dlg.title = m_sDate;
	dlg.DoModal();
}

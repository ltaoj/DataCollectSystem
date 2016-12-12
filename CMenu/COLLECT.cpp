// OLLECT.cpp : 实现文件
//

#include "stdafx.h"
#include "CMenu.h"
#include "COLLECT.h"
#include "afxdialogex.h"
//// 2016-07-12 1:27 add by li 
//DWORD dwExitCode;//声明全局变量，用于指定线程的状态
// 2016-07-11 20:26 add by li
threadInfo Info;//声明一个全局结构体
threadInfo SaveInfo;
#define BUFFER_SIZE 1024*64
// 2016-07-11 22:44 add by li ** 在实现开始采集后，继续实现采集的暂停和继续功能          
// 通过CreateThread创建线程，采集系统日志信息，获得线程的句柄
// 通过DWORD SuspendThread(HANDLE hThread);实现线程运行中的挂起
// 通过DWORD ResumeThread(HANDLE  hThread);实现唤醒线程恢复线程的执行

//定义BOOL变量,用于标志线程是否需要结束
BOOL m_runThread;
BOOL m_runSaveThread;
int i_Id;
int i_SaveId = 0;
// COLLECT 对话框

IMPLEMENT_DYNAMIC(COLLECT, CDialogEx)

COLLECT::COLLECT(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_COLLECT, pParent)
{
	conn = NULL;//初始化数据库指针;
	hThread = NULL;
}

COLLECT::~COLLECT()
{
}

void COLLECT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COLLECT, m_Grid);
	DDX_Control(pDX, IDC_BT_START, m_COL_Start);
	DDX_Control(pDX, IDC_BT_PAUSE, m_COL_Pause);
	DDX_Control(pDX, IDC_BT_RESUME, m_COL_Resume);
	DDX_Control(pDX, IDC_COMBO_COLLECT, m_combox);
	DDX_Control(pDX, IDC_EDIT2, m_colstate);
}


BEGIN_MESSAGE_MAP(COLLECT, CDialogEx)
	ON_BN_CLICKED(IDC_BT_START, &COLLECT::OnBnClickedBtStart)
	ON_BN_CLICKED(IDC_BT_PAUSE, &COLLECT::OnBnClickedBtPause)
	ON_BN_CLICKED(IDC_BT_RESUME, &COLLECT::OnBnClickedBtResume)
	ON_CBN_SELCHANGE(IDC_COMBO_COLLECT, &COLLECT::OnCbnSelchangeComboCollect)
	ON_BN_CLICKED(IDC_BT_SAVE, &COLLECT::OnBnClickedBtSave)
END_MESSAGE_MAP()

CString GetType(CString s_LogType)
{
	CString LogType = NULL;
	if (s_LogType == "0" || s_LogType == "3" || s_LogType == "4")
		LogType = "信息";
	if (s_LogType == "1")
		LogType = "错误";
	if (s_LogType == "2")
		LogType = "警告";
	if (s_LogType == "7")
		LogType = "审核失败";
	if (s_LogType == "8")
		LogType = "审核成功";
	return LogType;
}

CString GetLogName(CString m_strbox)
{
	CString LogName = NULL;
	if (m_strbox == "应用程序日志")
		LogName = "AppEvent";
	if (m_strbox == "系统日志")
		LogName = "SYSTEM";
	if (m_strbox == "安全日志")
		LogName = "Security";
	return LogName;
}

// COLLECT 消息处理程序
// 实现线程函数
// 该函数打开事件日志，获得每条记录的事件类型(级别),事件日期，事件来源，事件ID
// 该函数将信息逐条写入数据库t_log,表名t_log_application
// 该函数将每条记录显示在CCtrlList控件上边，CCtrlList 变量为m_Grid
UINT ThreadFunc(LPVOID lpParam)
{
	m_runThread = TRUE;
	//创建结构体对象，用于获取线程中的信息
	threadInfo *pInfo = (threadInfo*)lpParam;
	//OpenEventLog函数返回的日志文件的句柄
	HANDLE h;
	//事件日志记录结构体，保存每条日志记录的重要信息
	EVENTLOGRECORD *pevlr;
	//为读取的记录保存开辟内存
	TCHAR bBuffer[BUFFER_SIZE] = { 0 };
	//实际读取的字节数，需要的实际内存大小
	DWORD dwRead, dwNeeded;
	//获取事件日志的名称
	CString log_name = pInfo->ti_strbox;
	//返回日志文件的句柄
	h = OpenEventLog(NULL, log_name);
	pevlr = (EVENTLOGRECORD*)&bBuffer;

	//
	int/* i_Id = 0,*/ i_LogCategory, i_LogEventID/*, DEL = 0*/;
	//
	CString s_LogName, s_LogDate, s_LogTime, s_LogType, s_LogSource,
		/*s_LogUserName, s_LogComputerName,*/s_CollectTime;

	CTime time1, time2;CString s_Id, s_LogCateGory, s_LogEventID/*,s_DEL*/;
	//向后读取,顺序读取
	while (ReadEventLog(h, EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ,
		0, pevlr, BUFFER_SIZE, &dwRead, &dwNeeded))
	{

		while (dwRead > 0)
		{
			i_Id++;
			//s_LogName = log_name;
			CTime time1(pevlr->TimeGenerated);
			s_LogDate = time1.Format("%y-%m-%d");
			s_LogTime = time1.Format("%H:%M:%S");
			i_LogCategory = pevlr->EventCategory;
			s_LogType.Format("%d", pevlr->EventType);
			s_LogSource = (LPCTSTR)((LPBYTE)pevlr + sizeof(EVENTLOGRECORD));
			i_LogEventID = pevlr->EventID;
			//s_LogUserName = "李涛江";
			//s_LogComputerName = "Lenovo";
			time2 = CTime::GetCurrentTime(); //获取系统日期
			s_CollectTime.Format("%d:%d:%d", time2.GetHour(), time2.GetMinute(), time2.GetSecond());
			//DEL = 0;
			s_Id.Format("%d", i_Id);
			s_LogCateGory.Format("%d", i_LogCategory);
			//s_DEL.Format("%d", DEL);
			s_LogEventID.Format("%d", i_LogEventID);

			pInfo->ti_list->InsertItem(0, GetType(s_LogType));
			pInfo->ti_list->SetItemText(0, 1, s_LogDate);
			pInfo->ti_list->SetItemText(0, 2, s_LogTime);
			pInfo->ti_list->SetItemText(0, 3, s_LogSource);
			pInfo->ti_list->SetItemText(0, 4, s_LogEventID);
			pInfo->ti_list->SetItemText(0, 5, s_LogCateGory);
			pInfo->ti_list->SetItemText(0, 6, s_CollectTime);
			pInfo->ti_list->SetItemText(0, 7, s_Id);

			dwRead -= pevlr->Length;
			pevlr = (EVENTLOGRECORD *)((LPBYTE)pevlr + pevlr->Length);
		}
		pevlr = (EVENTLOGRECORD *)&bBuffer;
	}

	CloseEventLog(h);
	m_runThread = FALSE;
	return 0;
}
// 2016-07-11 20:50 add by li 
// 开始采集的响应函数，调用线程函数ThreadFunc（Info）
// hThread在构造函数中初始化为NULL,在初次开启线程时，开始采集为开启一个线程
// 之后开始按钮和继续按钮有了相同的功能。


UINT ThreadFuncSave(LPVOID lpParam)
{
	m_runSaveThread = TRUE;
	//创建结构体对象，用于获取线程中的信息
	threadInfo *pInfo = (threadInfo*)lpParam;
	//OpenEventLog函数返回的日志文件的句柄
	HANDLE h;
	//事件日志记录结构体，保存每条日志记录的重要信息
	EVENTLOGRECORD *pevlr;
	//为读取的记录保存开辟内存
	TCHAR bBuffer[BUFFER_SIZE] = { 0 };
	//实际读取的字节数，需要的实际内存大小
	DWORD dwRead, dwNeeded;
	//获取事件日志的名称
	CString log_name = pInfo->ti_strbox;
	//返回日志文件的句柄
	h = OpenEventLog(NULL, log_name);
	pevlr = (EVENTLOGRECORD*)&bBuffer;

	//
	int /*i_Id = 0, */i_LogCategory, i_LogEventID, DEL = 0;
	//
	CString s_LogName, s_LogDate, s_LogTime, s_LogType, s_LogSource,
		/*s_LogUserName, s_LogComputerName,*/ s_CollectTime;

	CTime time1, time2;CString s_Id, s_LogCateGory, s_LogEventID, s_DEL, sql;
	//向后读取,顺序读取
	while (ReadEventLog(h, EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ,
		0, pevlr, BUFFER_SIZE, &dwRead, &dwNeeded))
	{

		while (dwRead > 0)
		{
			i_SaveId++;
			s_LogName = log_name;
			CTime time1(pevlr->TimeGenerated);
			s_LogDate = time1.Format("%y-%m-%d");
			s_LogTime = time1.Format("%H:%M:%S");
			i_LogCategory = pevlr->EventCategory;
			s_LogType.Format("%d", pevlr->EventType);
			s_LogSource = (LPCTSTR)((LPBYTE)pevlr + sizeof(EVENTLOGRECORD));
			i_LogEventID = pevlr->EventID;
			time2 = CTime::GetCurrentTime(); //获取系统日期
			s_CollectTime.Format("%d:%d:%d", time2.GetHour(), time2.GetMinute(), time2.GetSecond());
			//DEL = 0;
			s_Id.Format("%d", i_SaveId);
			s_LogCateGory.Format("%d", i_LogCategory);
			s_DEL.Format("%d", DEL);
			s_LogEventID.Format("%d", i_LogEventID);

			sql.Format("insert into t_log(id,LogName,LogDate,LogTime,LogCategory,LogType,LogSource,LogEventID,CollectTime,DEL) values (%d,'%s','%s','%s',%d,'%s','%s',%d ,'%s',%d)", i_SaveId, s_LogName, s_LogDate, s_LogTime, i_LogCategory, GetType(s_LogType), s_LogSource, i_LogEventID, s_CollectTime, DEL);
			if (mysql_query(pInfo->ti_conn, sql))
			{
				AfxMessageBox("已保存过,请查看数据库");
				m_runSaveThread = FALSE;
				break;
			}

			if (i_SaveId == 10)
			{
				AfxMessageBox("正在保存" + GetLogName(pInfo->ti_strbox) + "日志信息");
			}
			dwRead -= pevlr->Length;
			pevlr = (EVENTLOGRECORD *)((LPBYTE)pevlr + pevlr->Length);
		}
		pevlr = (EVENTLOGRECORD *)&bBuffer;
		if (!m_runSaveThread)
			break;
	}
	if (m_runSaveThread)
	{
		AfxMessageBox("保存完毕");
	}
	CloseEventLog(h);
	m_runSaveThread = FALSE;
	return 0;
}

void COLLECT::OnBnClickedBtStart()
{
	// TODO: 在此添加控件通知处理程序代码

	if (m_strBox != "") {
		if (m_runThread)
		{
			AfxMessageBox("等待" + m_strBox + "日志信息采集完毕,才可以采集其他日志");
			return;
		}
		else
		{
			hThread = NULL;
		}
		//如果线程句柄还未创建，或者线程执行完毕后，被设为NULL,则初始化结构体，并且开启线程
		if (!hThread&&m_strBox != "主机信息")
		{
			Info.ti_conn = this->conn;
			Info.ti_list = &m_Grid;
			Info.ti_strbox = GetLogName(m_strBox);
			//如果有线程在运行，则等待该线程执行完毕
			GetDlgItem(IDC_BT_PAUSE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BT_RESUME)->EnableWindow(TRUE);
			hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc, &Info, 0, &ThreadID);
		}
		else
		{
			//执行采集主机信息的函数
		}

		//显示系统正在采集的日志类型
		m_colstate.SetWindowText("正在采集" + m_strBox);
	}
	else
	{
		AfxMessageBox("请选择采集数据类型");
		return;
	}
}

//挂起当前线程
void COLLECT::OnBnClickedBtPause()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BT_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_RESUME)->EnableWindow(TRUE);
	SuspendThread(hThread);
}

//唤醒当前线程
void COLLECT::OnBnClickedBtResume()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BT_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BT_RESUME)->EnableWindow(FALSE);
	ResumeThread(hThread);
}

// 2016-07-11 20:44 add by li 
// 此处Dialog初始化函数用于COLLECT对象链接数据库t_log,表名t_log_application
// COLLECT另外的初始化代码在主界面点击BUTTON时已经初始化
// COLLECT构造函数初始化时已将conn = NULL，此处的conn修饰符为protected和主界面conn链接的数据库不同
BOOL COLLECT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	/**//*初始化数据库指针*/
	if ((conn = mysql_init(NULL)) == NULL)
	{
		AfxMessageBox(TEXT("数据库出错"));
		exit(1);
	}
	int ret = mysql_set_character_set(conn, "GBK");
	/**//*数据库链接*/
	if (mysql_real_connect(conn, NULL, "root", "", "t_log", 0, NULL, 0) == NULL)
	{
		AfxMessageBox(TEXT("数据库链接错误"));
		mysql_close(conn);
		exit(1);
	}

	// 2016-07-12 0:23 add by li
	// 初始化ComBo Box空间的下拉项
	m_combox.AddString("应用程序日志");//AppEvent
	m_combox.AddString("系统日志");//SYSTEM
	m_combox.AddString("安全日志");//Security
	////设置查询的默认日志类型为Application类型
	//m_strBox = "Application";
	GetDlgItem(IDC_BT_RESUME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_PAUSE)->EnableWindow(FALSE);
	m_colstate.SetWindowText("请选择需要采集的消息");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void COLLECT::OnCbnSelchangeComboCollect()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel;
	//获取组合框控件的列表框中选中项的索引
	nSel = m_combox.GetCurSel();
	//根据选中项的索引值获取该项字符串
	m_combox.GetLBText(nSel, m_strBox);
}

/*保存原始数据*/
void COLLECT::OnBnClickedBtSave()
{
	CString LogName = Info.ti_strbox;
	SaveInfo.ti_conn = conn;
	SaveInfo.ti_list = NULL;
	SaveInfo.ti_strbox = GetLogName(m_strBox);
	hSaveThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ThreadFuncSave, &SaveInfo, 0, &SaveThreadID);
}


// CMenuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CMenu.h"
#include "CMenuDlg.h"
#include "afxdialogex.h"
#include "AboutUs.h"
#include "LOGIN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

NOTIFYICONDATA m_nid;
// CCMenuDlg 对话框
#define WM_SHOWTASK WM_USER+8 // 自定义消息，


CCMenuDlg::CCMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CMENU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	colDlg = NULL;
	serDlg = NULL;
	aboutDlg = NULL;
	comDlg = NULL;
	depDlg = NULL;
}

void CCMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BT_COLLECT, m_BTbmp_Collect);
	DDX_Control(pDX, IDC_BT_SEARCHCHA, m_BTbmp_Search);
	DDX_Control(pDX, IDC_BT_SYSTEM, m_BTbmp_System);
	DDX_Control(pDX, IDC_BT_EXIT, m_BTbmp_Exit);
	DDX_Control(pDX, IDC_BACKGR_STATIC, m_PICbmp_Back);
	DDX_Control(pDX, IDC_BT_DEPLOY, m_deploy);
	DDX_Control(pDX, IDC_BT_ABOUT2, m_about);
	DDX_Control(pDX, IDC_BT_COMPUTER, m_computer);
}

BEGIN_MESSAGE_MAP(CCMenuDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MYMSG, MyMsg)
	ON_BN_CLICKED(IDC_BT_EXIT, &CCMenuDlg::OnBnClickedBtExit)
	ON_COMMAND(IDR_MENU1, &CCMenuDlg::OnIdrMenu1)
	ON_COMMAND(ID_ABOUT, &CCMenuDlg::OnAbout)
	ON_BN_CLICKED(IDC_BT_COLLECT, &CCMenuDlg::OnBnClickedBtCollect)
	ON_BN_CLICKED(IDC_BT_SEARCHCHA, &CCMenuDlg::OnBnClickedBtSearchcha)
	ON_BN_CLICKED(IDC_BT_SYSTEM, &CCMenuDlg::OnBnClickedBtSystem)
	ON_COMMAND(ID_Menu_Reg, &CCMenuDlg::OnMenuReg)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BT_COMPUTER, &CCMenuDlg::OnBnClickedBtComputer)
	ON_BN_CLICKED(IDC_BT_DEPLOY, &CCMenuDlg::OnBnClickedBtDeploy)
	ON_BN_CLICKED(IDC_BT_ABOUT2, &CCMenuDlg::OnBnClickedBtAbout2)
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
END_MESSAGE_MAP()


// CCMenuDlg 消息处理程序

BOOL CCMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	//HMENU m_hMenu1;
	//m_hMenu1 = LoadMenu(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MENU1));//导入资源创建菜单
	//::SetMenu(this->GetSafeHwnd(), m_hMenu1);//添加到对话框


	//初始化位图按钮
	HBITMAP hBitmap;
	//采集页面按钮
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_COLE));
	m_BTbmp_Collect.SetBitmap(hBitmap);

	//查找界面按钮
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_SEAR));
	m_BTbmp_Search.SetBitmap(hBitmap);

	//系统界面按钮
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_GEAR));
	m_BTbmp_System.SetBitmap(hBitmap);

	//退出按钮
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3));
	m_BTbmp_Exit.SetBitmap(hBitmap);

	//主机信息按钮
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_COM));
	m_computer.SetBitmap(hBitmap);

	//关于我们按钮
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_ABOU));
	m_about.SetBitmap(hBitmap);

	//配置按钮
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_SET));
	m_deploy.SetBitmap(hBitmap);






	//// 加载菜单资源
	//m_Menu.LoadMenu(IDR_MENU1);
	//// 为对话框设置菜单
	//this->SetMenu(&m_Menu);

	/**//*初始化数据库指针*/
	if ((conn = mysql_init(NULL)) == NULL)
	{
		AfxMessageBox(TEXT("数据库出错"));
		//iMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
		exit(1);
	}
	int ret = mysql_set_character_set(conn, "GBK");
	/**//*数据库链接*/
	if (mysql_real_connect(conn, NULL, "root", "", "t_user_info", 0, NULL, 0) == NULL)
	{
		AfxMessageBox(TEXT("数据库链接错误"));
		mysql_close(conn);
		exit(1);
	}
	//为按钮添加提示的初始化
	m_Mytip.Create(this);
	m_Mytip.AddTool(GetDlgItem(IDC_BT_COLLECT), "采集日志");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_SEARCHCHA), "查询日志");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_SYSTEM), "系统信息");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_EXIT), "退出系统");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_COMPUTER), "主机性能");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_DEPLOY), "系统配置");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_ABOUT2), "关于我们");
	m_Mytip.SetDelayTime(200);
	m_Mytip.SetTipTextColor(RGB(0, 0, 0));
	m_Mytip.SetTipBkColor(RGB(255, 255, 255));
	m_Mytip.Activate(TRUE);
	// 2016-07-18 0:07 add by li  读取配置文件并进行界面传值传递给其他页面
	/*********************************************************************/
	int m_frequency; // 系统采集频率
	int m_appeventlog; //采集应用日志
	int m_systemlog; //采集系统日志
	int m_securitylog; //采集安全日志
	CString m_servername; // 服务器地址
	CString m_databasename; // 数据库名称
	CString m_username; //用户名
	CString m_password; //密码

	m_frequency = ::GetPrivateProfileInt("系统采集频率", "frequency", 2, "..\\myDefault.ini");
	m_appeventlog = ::GetPrivateProfileInt("采集应用日志", "appevent_log", 1, "..\\myDefault.ini");
	m_systemlog = ::GetPrivateProfileInt("采集系统日志", "system_log", 1, "..\\myDefault.ini");
	m_securitylog = ::GetPrivateProfileInt("采集安全日志", "security_log", 1, "..\\myDefault.ini");

	::GetPrivateProfileString("服务器", "servername", "127.0.0.1", m_servername.GetBuffer(100), 100, "C:\\Users\\lenovo\\Desktop\\项目5\\CMenu\\myDefault.ini");
	::GetPrivateProfileString("数据库名称", "databasename", "t_log", m_databasename.GetBuffer(100), 100, "C:\\Users\\lenovo\\Desktop\\项目5\\CMenu\\myDefault.ini");
	::GetPrivateProfileString("用户名", "username", "root", m_username.GetBuffer(100), 100, "C:\\Users\\lenovo\\Desktop\\项目5\\CMenu\\myDefault.ini");
	::GetPrivateProfileString("密码", "password", "", m_password.GetBuffer(100), 100, "C:\\Users\\lenovo\\Desktop\\项目5\\CMenu\\myDefault.ini");
	
	/********************************************************************/
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // 自定义的消息名称
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy_s(m_nid.szTip, "数据采集系统");                // 信息提示条为"服务器程序"，VS2008 UNICODE编码用wcscpy_s()函数
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // 在托盘区添加图标
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCMenuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCMenuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LRESULT CCMenuDlg::MyMsg(WPARAM wParam, LPARAM IParam)
{
	MessageBox((LPTSTR)wParam);

	return 0;
}



void CCMenuDlg::OnBnClickedBtExit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CCMenuDlg::OnIdrMenu1()
{
	// TODO: 在此添加命令处理程序代码

}


void CCMenuDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	AboutUs dlg;
	dlg.DoModal();

}

//采集页面响应函数
void CCMenuDlg::OnBnClickedBtCollect()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (depDlg != NULL)
	{
		depDlg->ShowWindow(SW_HIDE);
	}

	if (comDlg != NULL)
	{
		comDlg->ShowWindow(SW_HIDE);
	}
	if (aboutDlg != NULL)
	{
		aboutDlg->ShowWindow(SW_HIDE);
	}
	if (serDlg != NULL)
	{
		serDlg->ShowWindow(SW_HIDE);
	}


	if (NULL == colDlg)
	{
		colDlg = new COLLECT();
		colDlg->Create(IDD_DIALOG_COLLECT);
		CRect rc;
		GetWindowRect(&rc);
		rc.top += 78;
		//rc.bottom -= 8;
		rc.MoveToX(1);
		//rc.left -=200;
		//rc.right -= 7;
		colDlg->MoveWindow(&rc);
		colDlg->ShowWindow(SW_SHOW);
		//设置表格样式
		colDlg->m_Grid.SetExtendedStyle(LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		//设置表头
		colDlg->m_Grid.InsertColumn(0, _T("日志类型"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(1, _T("事件日期"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(2, _T("事件时间"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(3, _T("事件来源"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(4, _T("日志编号"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(5, _T("类别"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(6, _T("采集时间"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(7, _T("ID编号"), LVCFMT_LEFT, 100);
		//初始化位图按钮
		HBITMAP hBitmap;


		//
		hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_START));
		colDlg->m_COL_Start.SetBitmap(hBitmap);

		//
		hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_START));
		colDlg->m_COL_Pause.SetBitmap(hBitmap);

		//
		hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_STOP));
		colDlg->m_COL_Resume.SetBitmap(hBitmap);

	}
	colDlg->ShowWindow(SW_SHOW);
}

//查询页面响应函数
void CCMenuDlg::OnBnClickedBtSearchcha()
{
	// TODO: 在此添加控件通知处理程序代码

	if (colDlg != NULL)
	{
		colDlg->ShowWindow(SW_HIDE);
	}
	if (depDlg != NULL)
	{
		depDlg->ShowWindow(SW_HIDE);
	}
	if (comDlg != NULL)
	{
		comDlg->ShowWindow(SW_HIDE);
	}
	if (aboutDlg != NULL)
	{
		aboutDlg->ShowWindow(SW_HIDE);
	}

	if (NULL == serDlg)
	{
		serDlg = new SEARCH();
		serDlg->Create(IDD_DIALOG_SEARCH);
		CRect rc;
		GetWindowRect(&rc);
		rc.top += 78;
		rc.MoveToX(1);
		serDlg->MoveWindow(&rc);
		//设置表格样式
		serDlg->m_list.SetExtendedStyle(LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		//设置表头
		serDlg->m_list.InsertColumn(0, _T("日志类型"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(1, _T("事件日期"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(2, _T("事件时间"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(3, _T("事件来源"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(4, _T("日志编号"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(5, _T("类别"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(6, _T("采集时间"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(7, _T("ID编号"), LVCFMT_LEFT, 100);
	}
	serDlg->ShowWindow(SW_SHOW);
}

//系统页面响应函数
void CCMenuDlg::OnBnClickedBtSystem()
{
	// TODO: 在此添加控件通知处理程序代码
	if (colDlg != NULL)
	{
        colDlg->ShowWindow(SW_HIDE);
	}
	if (serDlg != NULL)
	{
		serDlg->ShowWindow(SW_HIDE);
	}
	/*if (NULL == sysDlg)
	{*/
		//sysDlg = new SYSTEM();
		//sysDlg->Create(IDD_DIALOG_SYSTEM);
		//CRect rc;
		//GetWindowRect(&rc);
		//rc.top += 33;
		////rc.bottom -= 8;
		//rc.MoveToX(1);
		////rc.left -=200;
		////rc.right -= 7;
		//sysDlg->MoveWindow(&rc);
		////设置表格样式
		////sysDlg->m_Grid.SetExtendedStyle(LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		//////设置表头
		////sysDlg->m_Grid.InsertColumn(0, _T("访问地址"), LVCFMT_LEFT, 180);
		////sysDlg->m_Grid.InsertColumn(1, _T("次数"), LVCFMT_LEFT, 100);
		////sysDlg->m_Grid.InsertColumn(1, _T("访问方式"), LVCFMT_LEFT, 200);

		////初始化位图按钮
		//HBITMAP hBitmap;

		////主机性能按钮
		//hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_SAVE));
		//sysDlg->m_Sys_Computer.SetBitmap(hBitmap);

		////配置系统按钮
		//hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_EXPORT));
		//sysDlg->m_Sys_Deploy.SetBitmap(hBitmap);

		////关于我们按钮
		//hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_EXPORT));
		//sysDlg->m_Sys_About.SetBitmap(hBitmap);


		//////保存按钮
		////hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_SAVE));
		////sysDlg->m_save.SetBitmap(hBitmap);

		//////导出按钮
		////hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_EXPORT));
		////sysDlg->m_Export.SetBitmap(hBitmap);
		/*sysDlg->ShowWindow(SW_SHOW);
	}	
	sysDlg->ShowWindow(SW_SHOW);*/

}
void CCMenuDlg::OnMenuReg()
{
	// TODO: 在此添加命令处理程序代码
	LOGIN dlg;
	dlg.DoModal();
	
}

// 无标题窗口的拖拽
LRESULT CCMenuDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
}


void CCMenuDlg::OnBnClickedBtComputer()
{

	if (aboutDlg != NULL)
	{
		aboutDlg->ShowWindow(SW_HIDE);
	}
	if (depDlg != NULL)
	{
		depDlg->ShowWindow(SW_HIDE);
	}
	if (colDlg != NULL)
	{
		colDlg->ShowWindow(SW_HIDE);
	}
	if (serDlg != NULL)
	{
		serDlg->ShowWindow(SW_HIDE);
	}

	if (NULL == comDlg)
	{
		comDlg = new Computer();
		comDlg->Create(IDD_DIALOG_COM);
	}

	CRect rc;
	GetWindowRect(&rc);
	rc.top += 78;

	rc.MoveToX(50);

	comDlg->MoveWindow(&rc);
	comDlg->ShowWindow(SW_SHOW);

}


void CCMenuDlg::OnBnClickedBtDeploy()
{
	if (aboutDlg != NULL)
	{
		aboutDlg->ShowWindow(SW_HIDE);
	}

	if (comDlg != NULL)
	{
		comDlg->ShowWindow(SW_HIDE);
	}
	if (colDlg != NULL)
	{
		colDlg->ShowWindow(SW_HIDE);
	}
	if (serDlg != NULL)
	{
		serDlg->ShowWindow(SW_HIDE);
	}

	if (NULL == depDlg)
	{
		depDlg = new Deploy();
		depDlg->Create(IDD_DIALOG_DEPLOY);
	}

	CRect rc;
	GetWindowRect(&rc);
	rc.top += 78;

	rc.MoveToX(50);

	depDlg->MoveWindow(&rc);
	depDlg->ShowWindow(SW_SHOW);
}



void CCMenuDlg::OnBnClickedBtAbout2()
{
	if (depDlg != NULL)
	{
		depDlg->ShowWindow(SW_HIDE);
	}

	if (comDlg != NULL)
	{
		comDlg->ShowWindow(SW_HIDE);
	}

	if (colDlg != NULL)
	{
		colDlg->ShowWindow(SW_HIDE);
	}
	if (serDlg != NULL)
	{
		serDlg->ShowWindow(SW_HIDE);
	}
	if (NULL == aboutDlg)
	{
		aboutDlg = new About();
		aboutDlg->Create(IDD_DIALOG_ABOUTUS);
	}

	CRect rc;
	GetWindowRect(&rc);
	rc.top += 78;

	rc.MoveToX(50);

	aboutDlg->MoveWindow(&rc);
	aboutDlg->ShowWindow(SW_SHOW);
}

LRESULT CCMenuDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP:                                        // 右键起来时弹出菜单
	{

		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);                    // 得到鼠标位置
		CMenu menu;
		menu.CreatePopupMenu();                    // 声明一个弹出式菜单
		menu.AppendMenu(MF_STRING, WM_DESTROY, "退出");
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	}
	break;
	case WM_LBUTTONDBLCLK:                                 // 双击左键的处理
	{
		this->ShowWindow(SW_SHOWNORMAL);         // 显示主窗口
	}
	break;
	case WM_LBUTTONDOWN:
	{
		if (this->IsWindowVisible())
		{
			this->ShowWindow(SW_HIDE);
		}
		else
		{
			this->ShowWindow(SW_SHOWNORMAL);
		}
	}
	}
	return 0;
}

void CCMenuDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	if (nType == SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE); // 当最小化市，隐藏主窗口              
	}
}

BOOL CCMenuDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	// 在托盘区删除图标
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
	return CDialog::DestroyWindow();
}

// 按钮出现提示文字
BOOL CCMenuDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
		if (pMsg->message == WM_MOUSEMOVE)
		m_Mytip.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}
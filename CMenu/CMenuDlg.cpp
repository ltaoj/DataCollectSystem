
// CMenuDlg.cpp : ʵ���ļ�
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
// CCMenuDlg �Ի���
#define WM_SHOWTASK WM_USER+8 // �Զ�����Ϣ��


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


// CCMenuDlg ��Ϣ�������

BOOL CCMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	//HMENU m_hMenu1;
	//m_hMenu1 = LoadMenu(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MENU1));//������Դ�����˵�
	//::SetMenu(this->GetSafeHwnd(), m_hMenu1);//��ӵ��Ի���


	//��ʼ��λͼ��ť
	HBITMAP hBitmap;
	//�ɼ�ҳ�水ť
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_COLE));
	m_BTbmp_Collect.SetBitmap(hBitmap);

	//���ҽ��水ť
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_SEAR));
	m_BTbmp_Search.SetBitmap(hBitmap);

	//ϵͳ���水ť
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_GEAR));
	m_BTbmp_System.SetBitmap(hBitmap);

	//�˳���ť
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3));
	m_BTbmp_Exit.SetBitmap(hBitmap);

	//������Ϣ��ť
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_COM));
	m_computer.SetBitmap(hBitmap);

	//�������ǰ�ť
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_ABOU));
	m_about.SetBitmap(hBitmap);

	//���ð�ť
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_SET));
	m_deploy.SetBitmap(hBitmap);






	//// ���ز˵���Դ
	//m_Menu.LoadMenu(IDR_MENU1);
	//// Ϊ�Ի������ò˵�
	//this->SetMenu(&m_Menu);

	/**//*��ʼ�����ݿ�ָ��*/
	if ((conn = mysql_init(NULL)) == NULL)
	{
		AfxMessageBox(TEXT("���ݿ����"));
		//iMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
		exit(1);
	}
	int ret = mysql_set_character_set(conn, "GBK");
	/**//*���ݿ�����*/
	if (mysql_real_connect(conn, NULL, "root", "", "t_user_info", 0, NULL, 0) == NULL)
	{
		AfxMessageBox(TEXT("���ݿ����Ӵ���"));
		mysql_close(conn);
		exit(1);
	}
	//Ϊ��ť�����ʾ�ĳ�ʼ��
	m_Mytip.Create(this);
	m_Mytip.AddTool(GetDlgItem(IDC_BT_COLLECT), "�ɼ���־");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_SEARCHCHA), "��ѯ��־");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_SYSTEM), "ϵͳ��Ϣ");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_EXIT), "�˳�ϵͳ");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_COMPUTER), "��������");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_DEPLOY), "ϵͳ����");
	m_Mytip.AddTool(GetDlgItem(IDC_BT_ABOUT2), "��������");
	m_Mytip.SetDelayTime(200);
	m_Mytip.SetTipTextColor(RGB(0, 0, 0));
	m_Mytip.SetTipBkColor(RGB(255, 255, 255));
	m_Mytip.Activate(TRUE);
	// 2016-07-18 0:07 add by li  ��ȡ�����ļ������н��洫ֵ���ݸ�����ҳ��
	/*********************************************************************/
	int m_frequency; // ϵͳ�ɼ�Ƶ��
	int m_appeventlog; //�ɼ�Ӧ����־
	int m_systemlog; //�ɼ�ϵͳ��־
	int m_securitylog; //�ɼ���ȫ��־
	CString m_servername; // ��������ַ
	CString m_databasename; // ���ݿ�����
	CString m_username; //�û���
	CString m_password; //����

	m_frequency = ::GetPrivateProfileInt("ϵͳ�ɼ�Ƶ��", "frequency", 2, "..\\myDefault.ini");
	m_appeventlog = ::GetPrivateProfileInt("�ɼ�Ӧ����־", "appevent_log", 1, "..\\myDefault.ini");
	m_systemlog = ::GetPrivateProfileInt("�ɼ�ϵͳ��־", "system_log", 1, "..\\myDefault.ini");
	m_securitylog = ::GetPrivateProfileInt("�ɼ���ȫ��־", "security_log", 1, "..\\myDefault.ini");

	::GetPrivateProfileString("������", "servername", "127.0.0.1", m_servername.GetBuffer(100), 100, "C:\\Users\\lenovo\\Desktop\\��Ŀ5\\CMenu\\myDefault.ini");
	::GetPrivateProfileString("���ݿ�����", "databasename", "t_log", m_databasename.GetBuffer(100), 100, "C:\\Users\\lenovo\\Desktop\\��Ŀ5\\CMenu\\myDefault.ini");
	::GetPrivateProfileString("�û���", "username", "root", m_username.GetBuffer(100), 100, "C:\\Users\\lenovo\\Desktop\\��Ŀ5\\CMenu\\myDefault.ini");
	::GetPrivateProfileString("����", "password", "", m_password.GetBuffer(100), 100, "C:\\Users\\lenovo\\Desktop\\��Ŀ5\\CMenu\\myDefault.ini");
	
	/********************************************************************/
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // �Զ������Ϣ����
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy_s(m_nid.szTip, "���ݲɼ�ϵͳ");                // ��Ϣ��ʾ��Ϊ"����������"��VS2008 UNICODE������wcscpy_s()����
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // �����������ͼ��
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCMenuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


void CCMenuDlg::OnIdrMenu1()
{
	// TODO: �ڴ���������������

}


void CCMenuDlg::OnAbout()
{
	// TODO: �ڴ���������������
	AboutUs dlg;
	dlg.DoModal();

}

//�ɼ�ҳ����Ӧ����
void CCMenuDlg::OnBnClickedBtCollect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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
		//���ñ����ʽ
		colDlg->m_Grid.SetExtendedStyle(LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		//���ñ�ͷ
		colDlg->m_Grid.InsertColumn(0, _T("��־����"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(1, _T("�¼�����"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(2, _T("�¼�ʱ��"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(3, _T("�¼���Դ"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(4, _T("��־���"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(5, _T("���"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(6, _T("�ɼ�ʱ��"), LVCFMT_LEFT, 100);
		colDlg->m_Grid.InsertColumn(7, _T("ID���"), LVCFMT_LEFT, 100);
		//��ʼ��λͼ��ť
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

//��ѯҳ����Ӧ����
void CCMenuDlg::OnBnClickedBtSearchcha()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
		//���ñ����ʽ
		serDlg->m_list.SetExtendedStyle(LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		//���ñ�ͷ
		serDlg->m_list.InsertColumn(0, _T("��־����"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(1, _T("�¼�����"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(2, _T("�¼�ʱ��"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(3, _T("�¼���Դ"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(4, _T("��־���"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(5, _T("���"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(6, _T("�ɼ�ʱ��"), LVCFMT_LEFT, 100);
		serDlg->m_list.InsertColumn(7, _T("ID���"), LVCFMT_LEFT, 100);
	}
	serDlg->ShowWindow(SW_SHOW);
}

//ϵͳҳ����Ӧ����
void CCMenuDlg::OnBnClickedBtSystem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		////���ñ����ʽ
		////sysDlg->m_Grid.SetExtendedStyle(LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		//////���ñ�ͷ
		////sysDlg->m_Grid.InsertColumn(0, _T("���ʵ�ַ"), LVCFMT_LEFT, 180);
		////sysDlg->m_Grid.InsertColumn(1, _T("����"), LVCFMT_LEFT, 100);
		////sysDlg->m_Grid.InsertColumn(1, _T("���ʷ�ʽ"), LVCFMT_LEFT, 200);

		////��ʼ��λͼ��ť
		//HBITMAP hBitmap;

		////�������ܰ�ť
		//hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_SAVE));
		//sysDlg->m_Sys_Computer.SetBitmap(hBitmap);

		////����ϵͳ��ť
		//hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_EXPORT));
		//sysDlg->m_Sys_Deploy.SetBitmap(hBitmap);

		////�������ǰ�ť
		//hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_EXPORT));
		//sysDlg->m_Sys_About.SetBitmap(hBitmap);


		//////���水ť
		////hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_SAVE));
		////sysDlg->m_save.SetBitmap(hBitmap);

		//////������ť
		////hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BIT_EXPORT));
		////sysDlg->m_Export.SetBitmap(hBitmap);
		/*sysDlg->ShowWindow(SW_SHOW);
	}	
	sysDlg->ShowWindow(SW_SHOW);*/

}
void CCMenuDlg::OnMenuReg()
{
	// TODO: �ڴ���������������
	LOGIN dlg;
	dlg.DoModal();
	
}

// �ޱ��ⴰ�ڵ���ק
LRESULT CCMenuDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	case WM_RBUTTONUP:                                        // �Ҽ�����ʱ�����˵�
	{

		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);                    // �õ����λ��
		CMenu menu;
		menu.CreatePopupMenu();                    // ����һ������ʽ�˵�
		menu.AppendMenu(MF_STRING, WM_DESTROY, "�˳�");
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	}
	break;
	case WM_LBUTTONDBLCLK:                                 // ˫������Ĵ���
	{
		this->ShowWindow(SW_SHOWNORMAL);         // ��ʾ������
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
		ShowWindow(SW_HIDE); // ����С���У�����������              
	}
}

BOOL CCMenuDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	// ��������ɾ��ͼ��
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
	return CDialog::DestroyWindow();
}

// ��ť������ʾ����
BOOL CCMenuDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
		if (pMsg->message == WM_MOUSEMOVE)
		m_Mytip.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}
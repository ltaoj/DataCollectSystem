// OLLECT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMenu.h"
#include "COLLECT.h"
#include "afxdialogex.h"
//// 2016-07-12 1:27 add by li 
//DWORD dwExitCode;//����ȫ�ֱ���������ָ���̵߳�״̬
// 2016-07-11 20:26 add by li
threadInfo Info;//����һ��ȫ�ֽṹ��
threadInfo SaveInfo;
#define BUFFER_SIZE 1024*64
// 2016-07-11 22:44 add by li ** ��ʵ�ֿ�ʼ�ɼ��󣬼���ʵ�ֲɼ�����ͣ�ͼ�������          
// ͨ��CreateThread�����̣߳��ɼ�ϵͳ��־��Ϣ������̵߳ľ��
// ͨ��DWORD SuspendThread(HANDLE hThread);ʵ���߳������еĹ���
// ͨ��DWORD ResumeThread(HANDLE  hThread);ʵ�ֻ����ָ̻߳��̵߳�ִ��

//����BOOL����,���ڱ�־�߳��Ƿ���Ҫ����
BOOL m_runThread;
BOOL m_runSaveThread;
int i_Id;
int i_SaveId = 0;
// COLLECT �Ի���

IMPLEMENT_DYNAMIC(COLLECT, CDialogEx)

COLLECT::COLLECT(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_COLLECT, pParent)
{
	conn = NULL;//��ʼ�����ݿ�ָ��;
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
		LogType = "��Ϣ";
	if (s_LogType == "1")
		LogType = "����";
	if (s_LogType == "2")
		LogType = "����";
	if (s_LogType == "7")
		LogType = "���ʧ��";
	if (s_LogType == "8")
		LogType = "��˳ɹ�";
	return LogType;
}

CString GetLogName(CString m_strbox)
{
	CString LogName = NULL;
	if (m_strbox == "Ӧ�ó�����־")
		LogName = "AppEvent";
	if (m_strbox == "ϵͳ��־")
		LogName = "SYSTEM";
	if (m_strbox == "��ȫ��־")
		LogName = "Security";
	return LogName;
}

// COLLECT ��Ϣ�������
// ʵ���̺߳���
// �ú������¼���־�����ÿ����¼���¼�����(����),�¼����ڣ��¼���Դ���¼�ID
// �ú�������Ϣ����д�����ݿ�t_log,����t_log_application
// �ú�����ÿ����¼��ʾ��CCtrlList�ؼ��ϱߣ�CCtrlList ����Ϊm_Grid
UINT ThreadFunc(LPVOID lpParam)
{
	m_runThread = TRUE;
	//�����ṹ��������ڻ�ȡ�߳��е���Ϣ
	threadInfo *pInfo = (threadInfo*)lpParam;
	//OpenEventLog�������ص���־�ļ��ľ��
	HANDLE h;
	//�¼���־��¼�ṹ�壬����ÿ����־��¼����Ҫ��Ϣ
	EVENTLOGRECORD *pevlr;
	//Ϊ��ȡ�ļ�¼���濪���ڴ�
	TCHAR bBuffer[BUFFER_SIZE] = { 0 };
	//ʵ�ʶ�ȡ���ֽ�������Ҫ��ʵ���ڴ��С
	DWORD dwRead, dwNeeded;
	//��ȡ�¼���־������
	CString log_name = pInfo->ti_strbox;
	//������־�ļ��ľ��
	h = OpenEventLog(NULL, log_name);
	pevlr = (EVENTLOGRECORD*)&bBuffer;

	//
	int/* i_Id = 0,*/ i_LogCategory, i_LogEventID/*, DEL = 0*/;
	//
	CString s_LogName, s_LogDate, s_LogTime, s_LogType, s_LogSource,
		/*s_LogUserName, s_LogComputerName,*/s_CollectTime;

	CTime time1, time2;CString s_Id, s_LogCateGory, s_LogEventID/*,s_DEL*/;
	//����ȡ,˳���ȡ
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
			//s_LogUserName = "���ν�";
			//s_LogComputerName = "Lenovo";
			time2 = CTime::GetCurrentTime(); //��ȡϵͳ����
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
// ��ʼ�ɼ�����Ӧ�����������̺߳���ThreadFunc��Info��
// hThread�ڹ��캯���г�ʼ��ΪNULL,�ڳ��ο����߳�ʱ����ʼ�ɼ�Ϊ����һ���߳�
// ֮��ʼ��ť�ͼ�����ť������ͬ�Ĺ��ܡ�


UINT ThreadFuncSave(LPVOID lpParam)
{
	m_runSaveThread = TRUE;
	//�����ṹ��������ڻ�ȡ�߳��е���Ϣ
	threadInfo *pInfo = (threadInfo*)lpParam;
	//OpenEventLog�������ص���־�ļ��ľ��
	HANDLE h;
	//�¼���־��¼�ṹ�壬����ÿ����־��¼����Ҫ��Ϣ
	EVENTLOGRECORD *pevlr;
	//Ϊ��ȡ�ļ�¼���濪���ڴ�
	TCHAR bBuffer[BUFFER_SIZE] = { 0 };
	//ʵ�ʶ�ȡ���ֽ�������Ҫ��ʵ���ڴ��С
	DWORD dwRead, dwNeeded;
	//��ȡ�¼���־������
	CString log_name = pInfo->ti_strbox;
	//������־�ļ��ľ��
	h = OpenEventLog(NULL, log_name);
	pevlr = (EVENTLOGRECORD*)&bBuffer;

	//
	int /*i_Id = 0, */i_LogCategory, i_LogEventID, DEL = 0;
	//
	CString s_LogName, s_LogDate, s_LogTime, s_LogType, s_LogSource,
		/*s_LogUserName, s_LogComputerName,*/ s_CollectTime;

	CTime time1, time2;CString s_Id, s_LogCateGory, s_LogEventID, s_DEL, sql;
	//����ȡ,˳���ȡ
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
			time2 = CTime::GetCurrentTime(); //��ȡϵͳ����
			s_CollectTime.Format("%d:%d:%d", time2.GetHour(), time2.GetMinute(), time2.GetSecond());
			//DEL = 0;
			s_Id.Format("%d", i_SaveId);
			s_LogCateGory.Format("%d", i_LogCategory);
			s_DEL.Format("%d", DEL);
			s_LogEventID.Format("%d", i_LogEventID);

			sql.Format("insert into t_log(id,LogName,LogDate,LogTime,LogCategory,LogType,LogSource,LogEventID,CollectTime,DEL) values (%d,'%s','%s','%s',%d,'%s','%s',%d ,'%s',%d)", i_SaveId, s_LogName, s_LogDate, s_LogTime, i_LogCategory, GetType(s_LogType), s_LogSource, i_LogEventID, s_CollectTime, DEL);
			if (mysql_query(pInfo->ti_conn, sql))
			{
				AfxMessageBox("�ѱ����,��鿴���ݿ�");
				m_runSaveThread = FALSE;
				break;
			}

			if (i_SaveId == 10)
			{
				AfxMessageBox("���ڱ���" + GetLogName(pInfo->ti_strbox) + "��־��Ϣ");
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
		AfxMessageBox("�������");
	}
	CloseEventLog(h);
	m_runSaveThread = FALSE;
	return 0;
}

void COLLECT::OnBnClickedBtStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (m_strBox != "") {
		if (m_runThread)
		{
			AfxMessageBox("�ȴ�" + m_strBox + "��־��Ϣ�ɼ����,�ſ��Բɼ�������־");
			return;
		}
		else
		{
			hThread = NULL;
		}
		//����߳̾����δ�����������߳�ִ����Ϻ󣬱���ΪNULL,���ʼ���ṹ�壬���ҿ����߳�
		if (!hThread&&m_strBox != "������Ϣ")
		{
			Info.ti_conn = this->conn;
			Info.ti_list = &m_Grid;
			Info.ti_strbox = GetLogName(m_strBox);
			//������߳������У���ȴ����߳�ִ�����
			GetDlgItem(IDC_BT_PAUSE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BT_RESUME)->EnableWindow(TRUE);
			hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc, &Info, 0, &ThreadID);
		}
		else
		{
			//ִ�вɼ�������Ϣ�ĺ���
		}

		//��ʾϵͳ���ڲɼ�����־����
		m_colstate.SetWindowText("���ڲɼ�" + m_strBox);
	}
	else
	{
		AfxMessageBox("��ѡ��ɼ���������");
		return;
	}
}

//����ǰ�߳�
void COLLECT::OnBnClickedBtPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BT_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_RESUME)->EnableWindow(TRUE);
	SuspendThread(hThread);
}

//���ѵ�ǰ�߳�
void COLLECT::OnBnClickedBtResume()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BT_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BT_RESUME)->EnableWindow(FALSE);
	ResumeThread(hThread);
}

// 2016-07-11 20:44 add by li 
// �˴�Dialog��ʼ����������COLLECT�����������ݿ�t_log,����t_log_application
// COLLECT����ĳ�ʼ����������������BUTTONʱ�Ѿ���ʼ��
// COLLECT���캯����ʼ��ʱ�ѽ�conn = NULL���˴���conn���η�Ϊprotected��������conn���ӵ����ݿⲻͬ
BOOL COLLECT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	/**//*��ʼ�����ݿ�ָ��*/
	if ((conn = mysql_init(NULL)) == NULL)
	{
		AfxMessageBox(TEXT("���ݿ����"));
		exit(1);
	}
	int ret = mysql_set_character_set(conn, "GBK");
	/**//*���ݿ�����*/
	if (mysql_real_connect(conn, NULL, "root", "", "t_log", 0, NULL, 0) == NULL)
	{
		AfxMessageBox(TEXT("���ݿ����Ӵ���"));
		mysql_close(conn);
		exit(1);
	}

	// 2016-07-12 0:23 add by li
	// ��ʼ��ComBo Box�ռ��������
	m_combox.AddString("Ӧ�ó�����־");//AppEvent
	m_combox.AddString("ϵͳ��־");//SYSTEM
	m_combox.AddString("��ȫ��־");//Security
	////���ò�ѯ��Ĭ����־����ΪApplication����
	//m_strBox = "Application";
	GetDlgItem(IDC_BT_RESUME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_PAUSE)->EnableWindow(FALSE);
	m_colstate.SetWindowText("��ѡ����Ҫ�ɼ�����Ϣ");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void COLLECT::OnCbnSelchangeComboCollect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel;
	//��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = m_combox.GetCurSel();
	//����ѡ���������ֵ��ȡ�����ַ���
	m_combox.GetLBText(nSel, m_strBox);
}

/*����ԭʼ����*/
void COLLECT::OnBnClickedBtSave()
{
	CString LogName = Info.ti_strbox;
	SaveInfo.ti_conn = conn;
	SaveInfo.ti_list = NULL;
	SaveInfo.ti_strbox = GetLogName(m_strBox);
	hSaveThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ThreadFuncSave, &SaveInfo, 0, &SaveThreadID);
}

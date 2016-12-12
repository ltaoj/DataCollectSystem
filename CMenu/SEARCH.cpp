// SEARCH.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMenu.h"
#include "SEARCH.h"
#include "afxdialogex.h"
#include "OptExcel.h"
#include "Chart.h"


// ����ȫ�ֽṹ��
threadSearch tsInfo;
// ����ȫ�ֱ���������ʾ�̵߳�״̬
BOOL bThreadRun = FALSE;
//����ȫ���ַ���,�����ж�
CString strChange;
// SEARCH �Ի���
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
// SEARCH ��Ϣ�������


BOOL SEARCH::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/*��ʼ�����ݿ�ָ��*/
	if ((conn = mysql_init(NULL)) == NULL)
	{
		AfxMessageBox("���ݿ�ָ���ʼ��ʧ��~");
		exit(1);
	}
	//�������ݿ����ΪGBK
	int ret = mysql_set_character_set(conn, "GBK");
	/*�������ݿ�:t_log , �����û���ѯ����ʹ��t_log�в�ͬ�ı���в�ѯ*/
	if (mysql_real_connect(conn, NULL, "root", "", "t_log", 0, NULL, 0) == NULL)
	{
		AfxMessageBox("���ݿ�����ʧ��~");
		exit(1);
	}
	/*��ʼ�� Combo Box ������*/
	m_comboxSer.AddString("ȫ��");
	m_comboxSer.AddString("��Ϣ");
	m_comboxSer.AddString("����");
	m_comboxSer.AddString("����");
	m_comboxSer.AddString("��˳ɹ�");
	m_comboxSer.AddString("���ʧ��");
	//��ʼ��ȫ���ַ���
	strChange = "";
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


//ѡ�� ComBo Box ���������Ӧ�¼� , m_sbox������������ַ���
void SEARCH::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	if (bThreadRun)
	{
		AfxMessageBox("���ڲ�ѯ" + m_sbox + "��־��Ϣ");
		return;
	}
	else
	{
		// �˳���ǰ�̣߳�������� list �б�

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
	// ��ʼ��sql���,ͨ�������û�ѡ�����Ϣ,����sql ����ƴ��        2016-07-13 18:32
	// ��Date Time Picker��ʱ����CTime��������
	// ������ת��Ϊ 16-01-12 ���ڸ�ʽ���ַ���,�ַ���������m_sDate����
	CTime m_date;
	CString m_sDate;
	m_dateSer.GetTime(m_date);
	m_sDate = m_date.Format("%y-%m-%d");
	//AfxMessageBox(m_sDate);
	CString sql;
	if (m_sbox == "ȫ��" || m_sbox == "")
	{
		sql.Format("select *from t_log where DEL=%d and LogDate='%s'", 0, m_sDate);
	}
	else if (m_sbox == "��Ϣ")
	{
		sql.Format("select *from t_log where DEL=%d and LogType='%s' and LogDate='%s'", 0, "��Ϣ", m_sDate);
	}
	else if (m_sbox == "����")
	{
		sql.Format("select *from t_log where DEL=%d and LogType='%s' and LogDate='%s'", 0, "����", m_sDate);
	}
	else if (m_sbox == "����")
	{
		sql.Format("select *from t_log where DEL=%d and LogType='%s' and LogDate='%s'", 0, "����", m_sDate);
	}
	else if (m_sbox == "��˳ɹ�")
	{
		sql.Format("select *from t_log where DEL=%d and LogType='%s' and LogDate='%s'", 0, "��˳ɹ�", m_sDate);
	}
	else if (m_sbox == "���ʧ��")
	{
		sql.Format("select *from t_log where DEL=%d and LogType='%s' and LogDate='%s'", 0, "���ʧ��", m_sDate);
	}
	else
	{
		AfxMessageBox("�������");
		return;
	}
	// AfxMessageBox(sql);
	// ��ʼ�� ȫ�ֽṹ��
	tsInfo.ts_pConn = this->conn;
	tsInfo.ts_pList = &m_list;
	tsInfo.ts_sql = sql;
	tsInfo.ts_logName = m_sbox;
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFuncSer, &tsInfo, 0, &ThreadID);
}
// ʵ��***��ѯ***�̺߳���
UINT ThreadFuncSer(LPVOID lpParam)
{
	bThreadRun = TRUE;

	threadSearch *pThreadInfo = (threadSearch *)lpParam;
	if (mysql_query(pThreadInfo->ts_pConn, pThreadInfo->ts_sql))
	{
		AfxMessageBox("��ѯ����");
	}
	else
	{
		MYSQL_RES *res_set;
		res_set = mysql_store_result(pThreadInfo->ts_pConn);
		if (res_set == NULL)
		{
			AfxMessageBox("û���ҵ����������ļ�¼");
		}
		else
		{
			MYSQL_ROW row;
			int count = 0;

			while ((row = mysql_fetch_row(res_set)) != NULL)
			{
				// ����������***���***������ʾ��  list control 
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
			AfxMessageBox("����" + pThreadInfo->ts_logName + "��־��Ϣ" + sCount + "��");
		}
	}
	bThreadRun = FALSE;
	return 0;
}
// ����Excel ��Ӧ�¼�
void SEARCH::OnBnClickedBtOutexcel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	COptExcel excel;

	if (excel.ExportExcel(&m_list))
	{
		AfxMessageBox("������ɣ�");
	}
	else
	{
		AfxMessageBox("����ʧ�ܣ�");
	}
}

CString GetType(int i)
{
	CString type = "";
	switch (i)
	{
	case 0:
		type = "��Ϣ";
		break;
	case 1:
		type = "����";
		break;
	case 2:
		type = "����";
		break;
	case 3:
		type = "��˳ɹ�";
		break;
	case 4:
		type = "���ʧ��";
		break;
	default:
		break;
	}
	return type;
}
// 2016-07-17 17:03 
// ͨ���ú����õ���ͳ��ͼ���������
// ������sql��䣬���ݿ�ָ��
// ���أ���¼����Ŀ
int GetCount(CString sql, MYSQL *conn)
{
	int count = 0;
	if (mysql_query(conn, sql))
	{
		AfxMessageBox("ͳ�Ƴ�����");
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
// ͳ�ư�ť����Ӧ�¼�
void SEARCH::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

#pragma once


// Computer �Ի���

class Computer : public CDialogEx
{
	DECLARE_DYNAMIC(Computer)

public:
	Computer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Computer();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// ����cpu��������
	CString m_cpuProductor;
	// ����cpu���ͺ�
	CString m_cpuType;
	// ����cpu����Ƶlong
	long m_cpuBasicFre;
};

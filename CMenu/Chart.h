#pragma once


// Chart �Ի���

class Chart : public CDialogEx
{
	DECLARE_DYNAMIC(Chart)

protected:
	afx_msg void OnPaint();
	afx_msg void DrawHistogram(int count[]);

public:
	Chart(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Chart();
	HICON m_hIcon;
	int num;
	int a[5];
	CString title;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

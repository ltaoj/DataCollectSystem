#pragma once


// AboutUs �Ի���

class AboutUs : public CDialogEx
{
	DECLARE_DYNAMIC(AboutUs)

public:
	AboutUs(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AboutUs();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ABOUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnAbout();
};

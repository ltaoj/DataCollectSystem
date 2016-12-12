#pragma once


// AboutUs 对话框

class AboutUs : public CDialogEx
{
	DECLARE_DYNAMIC(AboutUs)

public:
	AboutUs(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AboutUs();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ABOUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnAbout();
};

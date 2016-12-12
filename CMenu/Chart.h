#pragma once


// Chart 对话框

class Chart : public CDialogEx
{
	DECLARE_DYNAMIC(Chart)

protected:
	afx_msg void OnPaint();
	afx_msg void DrawHistogram(int count[]);

public:
	Chart(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Chart();
	HICON m_hIcon;
	int num;
	int a[5];
	CString title;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

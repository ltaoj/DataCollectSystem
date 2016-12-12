#pragma once


// Computer 对话框

class Computer : public CDialogEx
{
	DECLARE_DYNAMIC(Computer)

public:
	Computer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Computer();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// 保存cpu的制造商
	CString m_cpuProductor;
	// 保存cpu的型号
	CString m_cpuType;
	// 保存cpu的主频long
	long m_cpuBasicFre;
};

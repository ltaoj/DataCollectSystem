
// CMenuDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "COLLECT.h"

#include "mysql.h"
#include "About.h"
#include "Deploy.h"
#include "Computer.h"



// 2016-07-12  14:34 add by li 
// ��ѯҳ������µĶԻ���
#include "SEARCH.h"

#define WM_MYMSG (WM_USER + 0x7F)

// CCMenuDlg �Ի���
class CCMenuDlg : public CDialogEx
{
// ����
public:
	CCMenuDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMENU_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	COLLECT *colDlg;
	SEARCH *serDlg;
	About* aboutDlg;
	Computer* comDlg;
	Deploy* depDlg;

	// ��Ӳ�ѯ�Ի���
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//2016-07-11 10:14 add by li
	MYSQL *conn;                                         //���ݿ�ָ��
public:
	afx_msg LRESULT MyMsg(WPARAM wParam, LPARAM IParam);

	afx_msg void OnBnClickedBtExit();
	CStatic m_Pic_back;
	afx_msg void OnIdrMenu1();
	CButton m_BTbmp_Collect;
	// ��ѯ��λͼ��ť
	CButton m_BTbmp_Search;
	// ϵͳ��λͼ��ť
	CButton m_BTbmp_System;
	// �˳���λͼ��ť
	CButton m_BTbmp_Exit;
	// ����
	CStatic m_PICbmp_Back;
	afx_msg void OnAbout();
	afx_msg void OnBnClickedBtCollect();
	afx_msg void OnBnClickedBtSearchcha();
	afx_msg void OnBnClickedBtSystem();
	afx_msg void OnMenuReg();

	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedBtComputer();
	afx_msg void OnBnClickedBtDeploy();
	afx_msg void OnBnClickedBtAbout2();
	// ���ð�ť
	CButton m_deploy;
	// ��������
	CButton m_about;
	// ������Ϣ
	CButton m_computer;

	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);

	void OnSize(UINT nType, int cx, int cy);
	BOOL DestroyWindow();


	CToolTipCtrl m_Mytip;// Ϊ��ť�����ʾ
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

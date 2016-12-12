// Chart.cpp : 实现文件
//

#include "stdafx.h"
#include "CMenu.h"
#include "Chart.h"
#include "afxdialogex.h"


// Chart 对话框

IMPLEMENT_DYNAMIC(Chart, CDialogEx)

Chart::Chart(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Chart::~Chart()
{
}
BEGIN_MESSAGE_MAP(Chart, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void Chart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
void Chart::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawHistogram(a);
		CDialogEx::OnPaint();
	}
	
	

	
}


	void Chart::DrawHistogram(int count[])
	{
		CPaintDC dc(this);
		//得到控件的大小  
		CRect rect;
		GetClientRect(&rect);
		CBrush brush(RGB(106, 106, 95));//创建一个画刷，颜色由RGB宏制定
		CBrush* OldBrush = NULL;//保存原有画刷
		CPen* pPenBlue = new CPen;                                  //创建画笔对象  
		pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 0));     //黑色画笔  
		CPen* pPenBlack = new CPen;                                 //创建画笔对象  
		pPenBlack->CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); //黑色画笔  
														 //选中黑色画笔，并保存当前画笔  
		CGdiObject* pOldPen = dc.SelectObject(pPenBlack);
		OldBrush = dc.SelectObject(&brush);//用自定义画刷替换原有画刷
		int i = 0;
		CString str;
		int num = 200;
		//绘制坐标系  
		int OriX = rect.left + 40, OriY = rect.bottom - 20;//坐标系原点OriX，OriY  
		CPoint OPos(OriX, OriY), NowPos;  //OPos是原点坐标  
										  //绘制x坐标轴  
		dc.MoveTo(OPos);
		int flag = 0;//flag=0,原比例坐标，flag=1，扩大比例坐标  
		int temp = 40 + (num - 1) * 2 + 5;
		//str.Format("%d",temp);  
		//AfxMessageBox(str);  
		if (rect.right - rect.left>temp)
		{
			flag = 1;
			NowPos.x = OriX + temp;
		}
		else
		{
			flag = 0;
			NowPos.x = OriX + (num - 1) + 5;
		}
		NowPos.y = OriY;
		dc.LineTo(NowPos);
		//绘制箭头  
		dc.LineTo(NowPos.x - 5, NowPos.y - 5);
		dc.MoveTo(NowPos);
		dc.LineTo(NowPos.x - 5, NowPos.y + 5);
		//绘制x轴坐标系数  

		CString name[] = { "信息","警告","错误","审核成功","审核失败" };
		int arry = 0;

		for (i = 0; i < num; i = i + 5)
		{
			if (i % 10 == 0)
			{
				if (flag == 1)
				{
					dc.MoveTo(OPos.x + 2 * i, OPos.y);
					dc.LineTo(CPoint(OPos.x + 2 * i, OPos.y - 5));
				}
				else
				{
					dc.MoveTo(OPos.x + i, OPos.y);
					dc.LineTo(CPoint(OPos.x + i, OPos.y - 5));
				}
			}
			if (i % 40 == 0)
			{

				if (flag == 1)
				{
					dc.TextOut(OPos.x + 2 * i, OPos.y + 1, name[arry]);
				}
				else
				{
					dc.TextOut(OPos.x + i, OPos.y + 1, name[arry]);
				}
				arry++;
			}
		}

		//绘制最大的255  
		str.Format("%d", (num - 1));
		if (flag == 1)
		{
			dc.MoveTo(OPos.x + 2 * (num - 1), OPos.y);
			dc.LineTo(CPoint(OPos.x + 2 * (num - 1), OPos.y - 5));
			//dc.TextOut(OPos.x + 2 * (num - 1), OPos.y + 1, str);
		}
		else
		{
			dc.MoveTo(OPos.x + (num - 1), OPos.y);
			dc.LineTo(CPoint(OPos.x + (num - 1), OPos.y - 5));
			//dc.TextOut(OPos.x + (num - 1), OPos.y + 1, str);
		}
		//AfxMessageBox("a");  
		//绘制y轴坐标系数  
		dc.MoveTo(OPos);
		NowPos.x = OPos.x;
		NowPos.y = rect.top;
		dc.LineTo(NowPos);
		//绘制箭头  
		dc.LineTo(NowPos.x - 5, NowPos.y + 5);
		dc.MoveTo(NowPos);
		dc.LineTo(NowPos.x + 5, NowPos.y + 5);

		//寻找数据数组最大的数据  
		int max = 0;
		for (i = 0; i < 5; i++)
		{
			if (max < count[i])
			{
				max = count[i];
			}
		}
		//y轴坐标系数的数据步长  
		int Tstep = max / 10;   //10个数据  
								//y轴坐标系数的刻度步长  
		int Ystep = (OriY - rect.top) / 21;//除以21的原因是，有20是因为上面的数据步长是10，现在20就是2格显示一个步长，还有一个1是多出来的好看  
										   //显示y坐标的刻度和数据  
		for (i = 1; i != 22; i++)//显示21个刻度  
		{
			dc.MoveTo(OPos.x, OPos.y - Ystep * i);
			dc.LineTo(CPoint(OPos.x + 5, OPos.y - Ystep * i));
			if (i % 2 == 0)
			{
				str.Format("%d", Tstep * i * 3);
				dc.TextOut(rect.left, OPos.y - Ystep * i - 10, str);
			}
		}

		//绘制灰度图像的直方图  
		arry = 0;

		for (i = 0; i < num; i++)
		{
			if (flag == 1)
			{
				NowPos.x = OPos.x + (2 * i);
			}
			else
			{
				NowPos.x = OPos.x + i;
			}
			if (i % 40 == 0)
			{
				NowPos.y = OPos.y;
				dc.Rectangle(NowPos.x + 20, NowPos.y, NowPos.x + 40, NowPos.y - count[arry]);
				arry++;
			}
		}
		//恢复以前的画笔  
		dc.SelectObject(pOldPen);
		dc.SelectObject(OldBrush);//还原原有画刷
		delete pPenBlue;
		delete pPenBlack;

	}

// Chart 消息处理程序

BOOL Chart::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	SetWindowText(title + "统计结果柱状图");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
// Chart.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMenu.h"
#include "Chart.h"
#include "afxdialogex.h"


// Chart �Ի���

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
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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
		//�õ��ؼ��Ĵ�С  
		CRect rect;
		GetClientRect(&rect);
		CBrush brush(RGB(106, 106, 95));//����һ����ˢ����ɫ��RGB���ƶ�
		CBrush* OldBrush = NULL;//����ԭ�л�ˢ
		CPen* pPenBlue = new CPen;                                  //�������ʶ���  
		pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 0));     //��ɫ����  
		CPen* pPenBlack = new CPen;                                 //�������ʶ���  
		pPenBlack->CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); //��ɫ����  
														 //ѡ�к�ɫ���ʣ������浱ǰ����  
		CGdiObject* pOldPen = dc.SelectObject(pPenBlack);
		OldBrush = dc.SelectObject(&brush);//���Զ��廭ˢ�滻ԭ�л�ˢ
		int i = 0;
		CString str;
		int num = 200;
		//��������ϵ  
		int OriX = rect.left + 40, OriY = rect.bottom - 20;//����ϵԭ��OriX��OriY  
		CPoint OPos(OriX, OriY), NowPos;  //OPos��ԭ������  
										  //����x������  
		dc.MoveTo(OPos);
		int flag = 0;//flag=0,ԭ�������꣬flag=1�������������  
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
		//���Ƽ�ͷ  
		dc.LineTo(NowPos.x - 5, NowPos.y - 5);
		dc.MoveTo(NowPos);
		dc.LineTo(NowPos.x - 5, NowPos.y + 5);
		//����x������ϵ��  

		CString name[] = { "��Ϣ","����","����","��˳ɹ�","���ʧ��" };
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

		//��������255  
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
		//����y������ϵ��  
		dc.MoveTo(OPos);
		NowPos.x = OPos.x;
		NowPos.y = rect.top;
		dc.LineTo(NowPos);
		//���Ƽ�ͷ  
		dc.LineTo(NowPos.x - 5, NowPos.y + 5);
		dc.MoveTo(NowPos);
		dc.LineTo(NowPos.x + 5, NowPos.y + 5);

		//Ѱ������������������  
		int max = 0;
		for (i = 0; i < 5; i++)
		{
			if (max < count[i])
			{
				max = count[i];
			}
		}
		//y������ϵ�������ݲ���  
		int Tstep = max / 10;   //10������  
								//y������ϵ���Ŀ̶Ȳ���  
		int Ystep = (OriY - rect.top) / 21;//����21��ԭ���ǣ���20����Ϊ��������ݲ�����10������20����2����ʾһ������������һ��1�Ƕ�����ĺÿ�  
										   //��ʾy����Ŀ̶Ⱥ�����  
		for (i = 1; i != 22; i++)//��ʾ21���̶�  
		{
			dc.MoveTo(OPos.x, OPos.y - Ystep * i);
			dc.LineTo(CPoint(OPos.x + 5, OPos.y - Ystep * i));
			if (i % 2 == 0)
			{
				str.Format("%d", Tstep * i * 3);
				dc.TextOut(rect.left, OPos.y - Ystep * i - 10, str);
			}
		}

		//���ƻҶ�ͼ���ֱ��ͼ  
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
		//�ָ���ǰ�Ļ���  
		dc.SelectObject(pOldPen);
		dc.SelectObject(OldBrush);//��ԭԭ�л�ˢ
		delete pPenBlue;
		delete pPenBlack;

	}

// Chart ��Ϣ�������

BOOL Chart::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(title + "ͳ�ƽ����״ͼ");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
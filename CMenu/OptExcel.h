#pragma once
#include "CApplication.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CRange.h"

class COptExcel
{
public:
	COptExcel(void);
	~COptExcel(void);

	bool OpenExcelBook(CString filename);
	CString GetValue(int row, int col);//��ȡĳ��ĳ�е�ֵ
	CString IndexToString( int row, int col );//�õ��ĵ�Ԫ����EXCEL�еĶ�λ�����ַ���
	long GetUsedColnums();//�õ�����������ʹ�õ�����  
	long GetUsedRows();//�õ�����������ʹ�õ�����


	bool ExportExcel(CListCtrl * list);
	bool ReadExcel(CListCtrl * list);
	void SetCellString(long irow, long icolumn,CString new_string);  
	void SaveasXSLFile(const CString &xls_file);

	CApplication app;
	CWorkbooks books;  ///EXCEL BOOK���ϣ�������ļ�ʱ��
	CWorkbook book;///��ǰʹ�õ�BOOK����ǰ������ļ�  
	CWorksheets sheets; ///EXCEL��sheets����  
	CWorksheet sheet;///��ǰʹ��sheet  
	CRange range;///��ǰ�Ĳ�������  
	CRange cell;

};
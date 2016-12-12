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
	CString GetValue(int row, int col);//获取某行某列的值
	CString IndexToString( int row, int col );//得到的单元格在EXCEL中的定位名称字符串
	long GetUsedColnums();//得到工作簿中已使用的列数  
	long GetUsedRows();//得到工作簿中已使用的行数


	bool ExportExcel(CListCtrl * list);
	bool ReadExcel(CListCtrl * list);
	void SetCellString(long irow, long icolumn,CString new_string);  
	void SaveasXSLFile(const CString &xls_file);

	CApplication app;
	CWorkbooks books;  ///EXCEL BOOK集合，（多个文件时）
	CWorkbook book;///当前使用的BOOK，当前处理的文件  
	CWorksheets sheets; ///EXCEL的sheets集合  
	CWorksheet sheet;///当前使用sheet  
	CRange range;///当前的操作区域  
	CRange cell;

};
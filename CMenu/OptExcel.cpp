#include "StdAfx.h"
#include "OptExcel.h"


COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
////////////////////////////////////////////////////////////////////////  
///Function:    COptExcel  
///Description: 初始化函数，初始化中附加excel应用程序  
///Call:        app.CreateDispatch(_T("Excel.Application")  
//////////////////////////////////////////////////////////////////////// 
COptExcel::COptExcel(void)
{
	if (::CoInitialize( NULL ) == E_INVALIDARG)
	{   
		AfxMessageBox(_T("初始化Com失败!"));   
		return;  
	}  

	//验证office文件是否可以正确运行  

	if( !app.CreateDispatch(_T("Excel.Application")) )  
	{  
		AfxMessageBox(_T("无法创建Excel应用！"));  
		return;  
	}  
	 app.put_Visible(false); 
	//在程序执行文件路径名中，剪掉执行文件名，得到程序路径，追加模板文件名，得到模板完整路径  
}

////////////////////////////////////////////////////////////////////////  
///Function:    ~COptExcel  
///Description: 析构函数，释放对象，非常重要，不全部释放，占用内存，下  
///             一次使用此类时会中断  
///Call:        ReleaseDispatch()  
//////////////////////////////////////////////////////////////////////// 
COptExcel::~COptExcel(void)
{
	books.Close();

	books.ReleaseDispatch();  
	book.ReleaseDispatch();  
	sheets.ReleaseDispatch();  
	sheet.ReleaseDispatch();  
	range.ReleaseDispatch();  
	cell.ReleaseDispatch();  

	app.Quit();  

	app.ReleaseDispatch();  
	::CoUninitialize();  
}



////////////////////////////////////////////////////////////////////////  
///Function:    OpenExcelBook  
///Description: 打开表名为filename的文件，注意，文件路径非自动生成，以后  
///             考虑从下处理方法  
///Call:        GetAppPath()  
///Input:       CString filename 文件名  
////////////////////////////////////////////////////////////////////////  
bool COptExcel::OpenExcelBook(CString filename)  
{  
	CFileFind filefind; 
	if( !filefind.FindFile(filename) )   
	{   
		AfxMessageBox(_T("文件不存在"));  
		return false;  
	}  
	LPDISPATCH lpDisp; //接口指针  
	books=app.get_Workbooks();  
	lpDisp = books.Open(filename,  
		covOptional, covOptional, covOptional, covOptional,  
		covOptional, covOptional, covOptional, covOptional,  
		covOptional, covOptional, covOptional, covOptional,  
		covOptional, covOptional  
		);                                      //与office 2000的不同，是个参数的，直接在后面加了两个covOptional成功了  
	//得到Workbook  
	book.AttachDispatch(lpDisp);  
	//得到当前活跃sheet  
	//如果有单元格正处于编辑状态中，此操作不能返回，会一直等待  
	lpDisp=book.get_ActiveSheet();  
	sheet.AttachDispatch(lpDisp);   
	return true;  
}

////////////////////////////////////////////////////////////////////////  
///Function:    GetCellValue  
///Description: 得到的单元格中的值  
///Call:        IndexToString() 从(x,y)坐标形式转化为“A1”格式字符串  
///Input:       int row 单元格所在行  
///             int col 单元格所在列  
///Return:      CString 单元格中的值  
////////////////////////////////////////////////////////////////////////  
CString COptExcel::GetValue(int row, int col)  
{  
	COleVariant rValue;
	CString str;

	//读取第一个单元格的值  
	range.AttachDispatch(sheet.get_Cells());  
	range.AttachDispatch(range.get_Item (COleVariant((long)row),COleVariant((long)col)).pdispVal );   
	
	rValue=COleVariant(range.get_Value2());  
	rValue.ChangeType(VT_BSTR);
	if(rValue.vt == VT_BSTR) //字符串  
	{  
		str=rValue.bstrVal;  
	}  
	else if (rValue.vt==VT_R8) //8字节的数字  
	{  
		str.Format(_T("%f"),rValue.dblVal);  
	} 
	//else if(rValue.vt==VT_DATE) //时间格式  
 //   {  
	//	rValue.ChangeType(VT_DATE);
	//	COleDateTime time1(rValue);
	//	SYSTEMTIME st; 
	//	VariantTimeToSystemTime(time1, &st);  
 //   }  
 //   else if(rValue.vt==VT_EMPTY) //单元格空的  
 //   {  
	//	str="";  
 //   }    



	return str; 
}

////////////////////////////////////////////////////////////////////////  
///Function:    IndexToString  
///Description: 得到的单元格在EXCEL中的定位名称字符串  
///Input:       int row 单元格所在行  
///             int col 单元格所在列  
///Return:      CString 单元格在EXCEL中的定位名称字符串  
////////////////////////////////////////////////////////////////////////  
CString COptExcel::IndexToString( int row, int col )   
{   
	CString strResult;  
	if( col > 26 )   
	{   
		strResult.Format(_T("%c%c%d"),'A' + (col-1)/26-1,'A' + (col-1)%26,row);  
	}   
	else   
	{   
		strResult.Format(_T("%c%d"), 'A' + (col-1)%26,row);  
	}   
	return strResult;  
}

////////////////////////////////////////////////////////////////////////  
///Function:    GetUsedRows  
///Description: 得到工作簿中已使用的行数  
///Return:      long工作簿中已使用的行数  
//////////////////////////////////////////////////////////////////////// 
long COptExcel::GetUsedRows()
{
	CRange usedRange;
	usedRange.AttachDispatch(sheet.get_UsedRange());
	range.AttachDispatch(usedRange.get_Rows());
	long iRowNum=range.get_Count();                   //已经使用的行数
	return iRowNum;
}


////////////////////////////////////////////////////////////////////////  
///Function:    GetUsedColnums  
///Description: 得到工作簿中已使用的列数  
///Return:      long工作簿中已使用的列数  
//////////////////////////////////////////////////////////////////////// 
long COptExcel::GetUsedColnums()
{
	CRange usedRange;
	usedRange.AttachDispatch(sheet.get_UsedRange());
	range.AttachDispatch(usedRange.get_Columns());
	long iColNum=range.get_Count();                   //已经使用的列数
	return iColNum;
}


////////////////////////////////////////////////////////////////////////  
///Function:    ReadExcel  
///Description: 读取Excel文件到指定的CListCtrl中
///Input:       CListCtrl 控件的内存地址  
///               
///Return:      bool  true ：成功  flase：失败 
////////////////////////////////////////////////////////////////////////  
bool COptExcel::ReadExcel(CListCtrl * list)
{
	CString filename;
	CFileDialog dlg(TRUE,"xls",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Worksheet Files (*.xls;*.xlsx)|*.xls;*.xlsx||");
	if(dlg.DoModal() == IDOK)
	{
		filename= dlg.GetPathName();
	}else{
		return false;
	}


	COptExcel m_optExc;

	//打开excel文件
	if (!m_optExc.OpenExcelBook(filename))
	{
		return false;
	}

	//读取已经使用区域的信息，包括已经使用的行数、列数、起始行、起始列
	CRange usedRange;
	usedRange.AttachDispatch(m_optExc.sheet.get_UsedRange());

	long m_iRowNum=m_optExc.GetUsedRows();                   //已经使用的行数

	long m_iColNum=m_optExc.GetUsedColnums();                   //已经使用的列数

	long m_iStartRow=usedRange.get_Row();               //已使用区域的起始行，从1开始
	long m_iStartCol=usedRange.get_Column();            //已使用区域的起始列，从1开始

	long i,j;
	//初始化表头
	for(j=m_iStartCol;j<=m_iColNum;j++)
	{
		CString str;
		str = m_optExc.GetValue(1,j); 
		list->InsertColumn(j-1,str,LVCFMT_LEFT,80);
	}



	for(i=m_iStartRow+1;i<=m_iRowNum;i++)
	{
		CString tmp;
		tmp = m_optExc.GetValue(i,1);
		list->InsertItem(i-2,tmp);//插入表头数据
		for(j=m_iStartCol;j<=m_iColNum;j++)
		{
			CString str;
			str = m_optExc.GetValue(i,j); //插入表述
			list->SetItemText(i-2,j-1,str);//行 + 表示略过表头，因为前面表头信息我们已经添加了
		}

	}
	return true;
}

////////////////////////////////////////////////////////////////////////  
///Function:    SetCellString  
///Description: 写入一个CELL一个string  
///Input:       irow :行     icolumn : 列   new_string :字符串
///               
///Return:       
////////////////////////////////////////////////////////////////////////  

void COptExcel::SetCellString(long irow, long icolumn,CString new_string)  
{  
	COleVariant new_value(new_string);  
	CRange start_range = sheet.get_Range(COleVariant("A1"),covOptional);  
	CRange write_range = start_range.get_Offset(COleVariant((long)irow -1),COleVariant((long)icolumn -1) );  
	write_range.put_Value2(new_value);  
	start_range.ReleaseDispatch();  
	write_range.ReleaseDispatch();  

}  



////////////////////////////////////////////////////////////////////////  
///Function:    ExportExcel  
///Description: 将CListCtrl中的数据导出到Excel文件中
///Input:       CListCtrl 控件的内存地址  
///               
///Return:      bool  true ：成功  flase：失败 
////////////////////////////////////////////////////////////////////////  

bool COptExcel::ExportExcel(CListCtrl * list)
{
	CFileDialog dlg(FALSE,_T("(*.xls)"),NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT, 
		_T("(*.xls)|*.xls||"),NULL);

	if (dlg.DoModal())
	{
		//获取路径
		CString strFileName=dlg.GetPathName();

		//获取一个新的Workbook
		books = app.get_Workbooks();

		book = books.Add(covOptional);

		//获取第一个工作簿 
		sheets = book.get_Worksheets();

		//选择第一个工作簿
		sheet = sheets.get_Item(COleVariant((short)1));

		CHeaderCtrl   *pmyHeaderCtrl;//声明Ctrl表格头对象
		HDITEM   hdi; //声明表格头项
		TCHAR     lpBuffer[256];//表格头项的缓存

		hdi.mask   =   HDI_TEXT;//设置类型为文本
		hdi.pszText   =   lpBuffer;//指定缓存
		hdi.cchTextMax   =   256;//指定长度

		pmyHeaderCtrl = list->GetHeaderCtrl();//此句取得CListCtrl控件的列表頭

		int   iRow,iCol;

		int   m_cols   =   pmyHeaderCtrl-> GetItemCount();

		int   m_rows = list->GetItemCount();


		for(iCol=0;   iCol <m_cols;   iCol++)//将列表的标题头写入EXCEL
		{

			pmyHeaderCtrl-> GetItem(iCol,   &hdi);

			int   nWidth   =   list->GetColumnWidth(iCol)/6;//获取宽度

			range.put_ColumnWidth(_variant_t((long)nWidth));//设置宽度

			SetCellString(1,iCol+1,hdi.pszText);


		}


		int list_rows = 0,list_cols =0;
		list_rows = list->GetItemCount();//得到最大行数
		list_cols = m_cols;


		for (int i = 0 ; i < list_rows; i++)
		{
			for (int j = 0 ; j < m_cols; j++)
			{
				CString tmp;
				tmp = list->GetItemText(i,j);
				SetCellString(i+2,j+1,tmp);
			}
		}



		//保存文件
		SaveasXSLFile(strFileName);
	}

	return true;
}



////////////////////////////////////////////////////////////////////////  
///Function:    SaveasXSLFile  
///Description: 保存为excel文件
///Input:       xls_file ： 文件保存路径
///               
///Return:      
////////////////////////////////////////////////////////////////////////  

void COptExcel::SaveasXSLFile(const CString &xls_file)  
{  
	book.SaveAs(COleVariant(xls_file),  
		covOptional,  
		covOptional,  
		covOptional,  
		covOptional,  
		covOptional,  
		0,  
		covOptional,  
		covOptional,  
		covOptional,  
		covOptional,  
		covOptional);  
	return;  
}  

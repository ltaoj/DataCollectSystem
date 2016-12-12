#include "StdAfx.h"
#include "OptExcel.h"


COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
////////////////////////////////////////////////////////////////////////  
///Function:    COptExcel  
///Description: ��ʼ����������ʼ���и���excelӦ�ó���  
///Call:        app.CreateDispatch(_T("Excel.Application")  
//////////////////////////////////////////////////////////////////////// 
COptExcel::COptExcel(void)
{
	if (::CoInitialize( NULL ) == E_INVALIDARG)
	{   
		AfxMessageBox(_T("��ʼ��Comʧ��!"));   
		return;  
	}  

	//��֤office�ļ��Ƿ������ȷ����  

	if( !app.CreateDispatch(_T("Excel.Application")) )  
	{  
		AfxMessageBox(_T("�޷�����ExcelӦ�ã�"));  
		return;  
	}  
	 app.put_Visible(false); 
	//�ڳ���ִ���ļ�·�����У�����ִ���ļ������õ�����·����׷��ģ���ļ������õ�ģ������·��  
}

////////////////////////////////////////////////////////////////////////  
///Function:    ~COptExcel  
///Description: �����������ͷŶ��󣬷ǳ���Ҫ����ȫ���ͷţ�ռ���ڴ棬��  
///             һ��ʹ�ô���ʱ���ж�  
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
///Description: �򿪱���Ϊfilename���ļ���ע�⣬�ļ�·�����Զ����ɣ��Ժ�  
///             ���Ǵ��´�����  
///Call:        GetAppPath()  
///Input:       CString filename �ļ���  
////////////////////////////////////////////////////////////////////////  
bool COptExcel::OpenExcelBook(CString filename)  
{  
	CFileFind filefind; 
	if( !filefind.FindFile(filename) )   
	{   
		AfxMessageBox(_T("�ļ�������"));  
		return false;  
	}  
	LPDISPATCH lpDisp; //�ӿ�ָ��  
	books=app.get_Workbooks();  
	lpDisp = books.Open(filename,  
		covOptional, covOptional, covOptional, covOptional,  
		covOptional, covOptional, covOptional, covOptional,  
		covOptional, covOptional, covOptional, covOptional,  
		covOptional, covOptional  
		);                                      //��office 2000�Ĳ�ͬ���Ǹ������ģ�ֱ���ں����������covOptional�ɹ���  
	//�õ�Workbook  
	book.AttachDispatch(lpDisp);  
	//�õ���ǰ��Ծsheet  
	//����е�Ԫ�������ڱ༭״̬�У��˲������ܷ��أ���һֱ�ȴ�  
	lpDisp=book.get_ActiveSheet();  
	sheet.AttachDispatch(lpDisp);   
	return true;  
}

////////////////////////////////////////////////////////////////////////  
///Function:    GetCellValue  
///Description: �õ��ĵ�Ԫ���е�ֵ  
///Call:        IndexToString() ��(x,y)������ʽת��Ϊ��A1����ʽ�ַ���  
///Input:       int row ��Ԫ��������  
///             int col ��Ԫ��������  
///Return:      CString ��Ԫ���е�ֵ  
////////////////////////////////////////////////////////////////////////  
CString COptExcel::GetValue(int row, int col)  
{  
	COleVariant rValue;
	CString str;

	//��ȡ��һ����Ԫ���ֵ  
	range.AttachDispatch(sheet.get_Cells());  
	range.AttachDispatch(range.get_Item (COleVariant((long)row),COleVariant((long)col)).pdispVal );   
	
	rValue=COleVariant(range.get_Value2());  
	rValue.ChangeType(VT_BSTR);
	if(rValue.vt == VT_BSTR) //�ַ���  
	{  
		str=rValue.bstrVal;  
	}  
	else if (rValue.vt==VT_R8) //8�ֽڵ�����  
	{  
		str.Format(_T("%f"),rValue.dblVal);  
	} 
	//else if(rValue.vt==VT_DATE) //ʱ���ʽ  
 //   {  
	//	rValue.ChangeType(VT_DATE);
	//	COleDateTime time1(rValue);
	//	SYSTEMTIME st; 
	//	VariantTimeToSystemTime(time1, &st);  
 //   }  
 //   else if(rValue.vt==VT_EMPTY) //��Ԫ��յ�  
 //   {  
	//	str="";  
 //   }    



	return str; 
}

////////////////////////////////////////////////////////////////////////  
///Function:    IndexToString  
///Description: �õ��ĵ�Ԫ����EXCEL�еĶ�λ�����ַ���  
///Input:       int row ��Ԫ��������  
///             int col ��Ԫ��������  
///Return:      CString ��Ԫ����EXCEL�еĶ�λ�����ַ���  
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
///Description: �õ�����������ʹ�õ�����  
///Return:      long����������ʹ�õ�����  
//////////////////////////////////////////////////////////////////////// 
long COptExcel::GetUsedRows()
{
	CRange usedRange;
	usedRange.AttachDispatch(sheet.get_UsedRange());
	range.AttachDispatch(usedRange.get_Rows());
	long iRowNum=range.get_Count();                   //�Ѿ�ʹ�õ�����
	return iRowNum;
}


////////////////////////////////////////////////////////////////////////  
///Function:    GetUsedColnums  
///Description: �õ�����������ʹ�õ�����  
///Return:      long����������ʹ�õ�����  
//////////////////////////////////////////////////////////////////////// 
long COptExcel::GetUsedColnums()
{
	CRange usedRange;
	usedRange.AttachDispatch(sheet.get_UsedRange());
	range.AttachDispatch(usedRange.get_Columns());
	long iColNum=range.get_Count();                   //�Ѿ�ʹ�õ�����
	return iColNum;
}


////////////////////////////////////////////////////////////////////////  
///Function:    ReadExcel  
///Description: ��ȡExcel�ļ���ָ����CListCtrl��
///Input:       CListCtrl �ؼ����ڴ��ַ  
///               
///Return:      bool  true ���ɹ�  flase��ʧ�� 
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

	//��excel�ļ�
	if (!m_optExc.OpenExcelBook(filename))
	{
		return false;
	}

	//��ȡ�Ѿ�ʹ���������Ϣ�������Ѿ�ʹ�õ���������������ʼ�С���ʼ��
	CRange usedRange;
	usedRange.AttachDispatch(m_optExc.sheet.get_UsedRange());

	long m_iRowNum=m_optExc.GetUsedRows();                   //�Ѿ�ʹ�õ�����

	long m_iColNum=m_optExc.GetUsedColnums();                   //�Ѿ�ʹ�õ�����

	long m_iStartRow=usedRange.get_Row();               //��ʹ���������ʼ�У���1��ʼ
	long m_iStartCol=usedRange.get_Column();            //��ʹ���������ʼ�У���1��ʼ

	long i,j;
	//��ʼ����ͷ
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
		list->InsertItem(i-2,tmp);//�����ͷ����
		for(j=m_iStartCol;j<=m_iColNum;j++)
		{
			CString str;
			str = m_optExc.GetValue(i,j); //�������
			list->SetItemText(i-2,j-1,str);//�� + ��ʾ�Թ���ͷ����Ϊǰ���ͷ��Ϣ�����Ѿ������
		}

	}
	return true;
}

////////////////////////////////////////////////////////////////////////  
///Function:    SetCellString  
///Description: д��һ��CELLһ��string  
///Input:       irow :��     icolumn : ��   new_string :�ַ���
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
///Description: ��CListCtrl�е����ݵ�����Excel�ļ���
///Input:       CListCtrl �ؼ����ڴ��ַ  
///               
///Return:      bool  true ���ɹ�  flase��ʧ�� 
////////////////////////////////////////////////////////////////////////  

bool COptExcel::ExportExcel(CListCtrl * list)
{
	CFileDialog dlg(FALSE,_T("(*.xls)"),NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT, 
		_T("(*.xls)|*.xls||"),NULL);

	if (dlg.DoModal())
	{
		//��ȡ·��
		CString strFileName=dlg.GetPathName();

		//��ȡһ���µ�Workbook
		books = app.get_Workbooks();

		book = books.Add(covOptional);

		//��ȡ��һ�������� 
		sheets = book.get_Worksheets();

		//ѡ���һ��������
		sheet = sheets.get_Item(COleVariant((short)1));

		CHeaderCtrl   *pmyHeaderCtrl;//����Ctrl���ͷ����
		HDITEM   hdi; //�������ͷ��
		TCHAR     lpBuffer[256];//���ͷ��Ļ���

		hdi.mask   =   HDI_TEXT;//��������Ϊ�ı�
		hdi.pszText   =   lpBuffer;//ָ������
		hdi.cchTextMax   =   256;//ָ������

		pmyHeaderCtrl = list->GetHeaderCtrl();//�˾�ȡ��CListCtrl�ؼ����б��^

		int   iRow,iCol;

		int   m_cols   =   pmyHeaderCtrl-> GetItemCount();

		int   m_rows = list->GetItemCount();


		for(iCol=0;   iCol <m_cols;   iCol++)//���б�ı���ͷд��EXCEL
		{

			pmyHeaderCtrl-> GetItem(iCol,   &hdi);

			int   nWidth   =   list->GetColumnWidth(iCol)/6;//��ȡ���

			range.put_ColumnWidth(_variant_t((long)nWidth));//���ÿ��

			SetCellString(1,iCol+1,hdi.pszText);


		}


		int list_rows = 0,list_cols =0;
		list_rows = list->GetItemCount();//�õ��������
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



		//�����ļ�
		SaveasXSLFile(strFileName);
	}

	return true;
}



////////////////////////////////////////////////////////////////////////  
///Function:    SaveasXSLFile  
///Description: ����Ϊexcel�ļ�
///Input:       xls_file �� �ļ�����·��
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

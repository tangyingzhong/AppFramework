#include "PreCompile.h"
#include "Excel.h"

GENERATE_PLUGIN(EXCEL_PLUGIN, Excel);

// Construct the Excel
Excel::Excel() :
	m_pBook(NULL),
	m_pSheet(NULL),
	m_pFont(NULL),
	m_pFormat(NULL),
	m_strErrorMessage(""),
	m_bIsClosed(false),
	m_bDisposed(false)
{
	Initialize();
}

// Detructe the Excel
Excel::~Excel()
{
	Destory();
}

// Initialize the Excel
None Excel::Initialize()
{
	// Create a book
	CreateBook();
}

// Destory the Excel
None Excel::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Destory the book
		DestoryBook();
	}
}

// Create a book
None Excel::CreateBook()
{
	SetBook(xlCreateXMLBook());

	GetBook()->setKey(L"Michael Hillier", L"windows-222329040ec5ec046fb46767a7h1gej6");
}

// Destory the book
None Excel::DestoryBook()
{
	if (GetBook())
	{
		Release();

		SetBook(NULL);
	}
}

// Load the excel
Boolean Excel::Load(String strExcelFilePath)
{
	if (strExcelFilePath.IsEmpty())
	{
		SetErrorMessage("Please input valid excel file path");

		return false;
	}

	if (GetBook()==NULL)
	{
		SetErrorMessage("Excel module hasn't been loaded");

		return false;
	}

	if (!GetBook()->load(strExcelFilePath.CStr()))
	{
		std::string strError = GetBook()->errorMessage();

		SetErrorMessage(strError);

		return false;
	}

	// Set default sheet
	SetWorkSheet(0);

	return true;
}

// Set the current active sheet
Boolean Excel::SetWorkSheet(Int32 iIndex)
{
	if (iIndex<0)
	{
		SetErrorMessage("Invalid sheet index,maybe there is no such sheet index");

		return false;
	}

	Sheet* pSheet = GetBook()->getSheet(iIndex);
	if (pSheet == NULL)
	{
		std::string strError = GetBook()->errorMessage();

		SetErrorMessage(strError);

		SetSheet(pSheet);

		return false;
	}

	SetSheet(pSheet);

	return true;
}

// Get the cell value
Boolean Excel::GetCell(Int32 iRowIndex, Int32 iColumnIndex, AlterType& AlterValue)
{
	if (iRowIndex<0)
	{
		SetErrorMessage("Invalid row index,It must >=0");

		return false;
	}

	if (iColumnIndex<0)
	{
		SetErrorMessage("Invalid column index,It must >=0");

		return false;
	}

	// Get the current sheet
	if (GetSheet() == NULL)
	{
		SetErrorMessage("Please set the sheet by SetWorkSheet at first!");

		return false;
	}

	CellType celltype = GetSheet()->cellType(iRowIndex, iColumnIndex);

	switch (celltype)
	{
	case libxl::CELLTYPE_EMPTY:
	{
		AlterValue = "None Cell";
	}
	break;
	case libxl::CELLTYPE_NUMBER:
	{
		Real dValue = GetSheet()->readNum(iRowIndex, iColumnIndex);

		AlterValue = dValue;
	}
	break;
	case libxl::CELLTYPE_STRING:
	{
		String strContect =GetSheet()->readStr(iRowIndex, iColumnIndex);

		AlterValue = strContect.CStr();
	}
	break;
	case libxl::CELLTYPE_BOOLEAN:
	{
		Boolean bValue = GetSheet()->readBool(iRowIndex, iColumnIndex);

		AlterValue = bValue;
	}
	break;
	case libxl::CELLTYPE_BLANK:
	{
		AlterValue = "Blank Cell";
	}
	break;
	case libxl::CELLTYPE_ERROR:
	{
		std::string strError = GetBook()->errorMessage();

		SetErrorMessage(strError);

		return false;
	}
	}

	return true;
}

// Get a column data
Boolean Excel::GetColumn(Int32 iColIndex, ColumnTable& CTable)
{
	if (iColIndex<0)
	{
		SetErrorMessage("Invalid column index,it should >=0");

		return false;
	}

	if (GetBook()==NULL)
	{
		SetErrorMessage("Excel module hasn't been loaded");

		return false;
	}

	// Get the current sheet
	if (GetSheet()==NULL)
	{
		SetErrorMessage("Please set the sheet by SetWorkSheet at first!");

		return false;
	}

	// Get the sheet's width and height
	Int32 iFirstRow = GetSheet()->firstRow();

	Int32 iLastRow = GetSheet()->lastRow();

	for (Int32 iIndex = iFirstRow; iIndex < iLastRow;++iIndex)
	{
		AlterType AlterValue;

		if (!GetCell(iIndex, iColIndex, AlterValue))
		{
			return false;
		}

		CTable.push_back(AlterValue);
	}

	return true;
}

// Get a row data
Boolean Excel::GetRow(Int32 iRowIndex, RowTable& RTable)
{
	if (iRowIndex < 0)
	{
		SetErrorMessage("Invalid row index,it should >=0");

		return false;
	}

	if (GetBook() == NULL)
	{
		SetErrorMessage("Excel module hasn't been loaded");

		return false;
	}

	// Get the current sheet
	if (GetSheet() == NULL)
	{
		SetErrorMessage("Please set the sheet by SetWorkSheet at first!");

		return false;
	}

	// Get the sheet's width and height
	Int32 iFirstCol = GetSheet()->firstCol();

	Int32 iLastCol = GetSheet()->lastCol();

	for (Int32 iIndex = iFirstCol; iIndex < iLastCol; ++iIndex)
	{
		AlterType AlterValue;

		if (!GetCell(iRowIndex, iIndex, AlterValue))
		{
			return false;
		}

		RTable.push_back(AlterValue);
	}

	return true;
}

// Set cell's format
None Excel::SetCellAlign(AlignHEnum eAlignH, AlignVEnum eAlignV)
{
	if (GetBook())
	{
		SetFormat(GetBook()->addFormat());

		GetFormat()->setAlignH((AlignH)eAlignH);

		GetFormat()->setAlignV((AlignV)eAlignV);
	}
}

// Set cell's font
None Excel::SetCellFont(FontColorEnum eColor, Boolean bIsFontBold)
{
	if (GetBook())
	{
		SetFont(GetBook()->addFont());

		GetFont()->setColor((Color)eColor);

		GetFont()->setBold(bIsFontBold);

		GetFormat()->setFont(GetFont());
	}
}

// Get the column with
Boolean Excel::GetColumnWidth(Int32 iColumnIndex, Real& dWidth)
{
	if (iColumnIndex<0)
	{
		SetErrorMessage("Invalid column index,It must >=0");

		return false;
	}

	// Get the current sheet
	if (GetSheet() == NULL)
	{
		SetErrorMessage("Please set the sheet by SetWorkSheet at first!");

		return false;
	}

	dWidth= GetSheet()->colWidth(iColumnIndex);

	return true;
}

// Set column's width
Boolean Excel::SetColumnWidth(Int32 iColumnIndex, Int32 iWidth)
{
	if (iColumnIndex < 0)
	{
		SetErrorMessage("Invalid column index,It must >=0");

		return false;
	}

	if (iWidth <= 0)
	{
		SetErrorMessage("Invalid column width,It must >0");

		return false;
	}

	// Get the current sheet
	if (GetSheet() == NULL)
	{
		SetErrorMessage("Please set the sheet by SetWorkSheet at first!");

		return false;
	}

	return GetSheet()->setCol(iColumnIndex, iColumnIndex, iWidth);
}

// Get the row height
Boolean Excel::GetRowHeight(Int32 iRowIndex, Real& dHeight)
{
	if (iRowIndex < 0)
	{
		SetErrorMessage("Invalid row index,It must >=0");

		return false;
	}

	// Get the current sheet
	if (GetSheet() == NULL)
	{
		SetErrorMessage("Please set the sheet by SetWorkSheet at first!");

		return false;
	}

	dHeight = GetSheet()->rowHeight(iRowIndex);

	return true;
}

// Set row's height
Boolean Excel::SetRowHeight(Int32 iRowIndex, Int32 iHeight)
{
	if (iRowIndex < 0)
	{
		SetErrorMessage("Invalid row index,It must >=0");

		return false;
	}

	if (iHeight <= 0)
	{
		SetErrorMessage("Invalid row height,It must >0");

		return false;
	}

	// Get the current sheet
	if (GetSheet() == NULL)
	{
		SetErrorMessage("Please set the sheet by SetWorkSheet at first!");

		return false;
	}

	return GetSheet()->setRow(iRowIndex, iHeight);
}

// Write a cell
Boolean Excel::WriteCell(Int32 iRowIndex,
	Int32 iColumnIndex,
	String strValue,
	Boolean bIsUseCellFormat)
{
	if (iRowIndex < 0)
	{
		SetErrorMessage("Invalid row index,It must >=0");

		return false;
	}

	if (iColumnIndex < 0)
	{
		SetErrorMessage("Invalid column index,It must >=0");

		return false;
	}

	if (strValue.IsEmpty())
	{
		strValue = "NULL";
	}

	// Get the current sheet
	if (GetSheet() == NULL)
	{
		SetErrorMessage("Please set the sheet by SetWorkSheet at first!");

		return false;
	}

	if (bIsUseCellFormat)
	{
		if (!GetSheet()->writeStr(iRowIndex, iColumnIndex, strValue.CStr(), GetFormat()))
		{
			SetErrorMessage("Failed to write string value with format!");

			return false;
		}

		return true;
	}

	if (!GetSheet()->writeStr(iRowIndex, iColumnIndex, strValue.CStr()))
	{
		SetErrorMessage("Failed to write string value!");

		return false;
	}

	return true;
}

// Write a cell
Boolean Excel::WriteCell(Int32 iRowIndex,
	Int32 iColumnIndex,
	Int32 iValue,
	Boolean bIsUseCellFormat)
{
	return WriteCell(iRowIndex, iColumnIndex, (Real)iValue, bIsUseCellFormat);
}

// Write a cell
Boolean Excel::WriteCell(Int32 iRowIndex,
	Int32 iColumnIndex,
	Real dValue,
	Boolean bIsUseCellFormat)
{
	if (iRowIndex < 0)
	{
		SetErrorMessage("Invalid row index,It must >=0");

		return false;
	}

	if (iColumnIndex < 0)
	{
		SetErrorMessage("Invalid column index,It must >=0");

		return false;
	}

	// Get the current sheet
	if (GetSheet() == NULL)
	{
		SetErrorMessage("Please set the sheet by SetWorkSheet at first!");

		return false;
	}

	if (bIsUseCellFormat)
	{
		if (!GetSheet()->writeNum(iRowIndex, iColumnIndex, dValue, GetFormat()))
		{
			SetErrorMessage("Failed to write double value with format !");

			return false;
		}

		return true;
	}

	if (!GetSheet()->writeNum(iRowIndex, iColumnIndex, dValue))
	{
		SetErrorMessage("Failed to write double value !");

		return false;
	}

	return true;
}

// Write a cell
Boolean Excel::WriteCell(Int32 iRowIndex,
	Int32 iColumnIndex,
	Boolean bValue,
	Boolean bIsUseCellFormat)
{
	if (iRowIndex < 0)
	{
		SetErrorMessage("Invalid row index,It must >=0");

		return false;
	}

	if (iColumnIndex < 0)
	{
		SetErrorMessage("Invalid column index,It must >=0");

		return false;
	}

	// Get the current sheet
	if (GetSheet() == NULL)
	{
		SetErrorMessage("Please set the sheet by SetWorkSheet at first!");

		return false;
	}

	if (bIsUseCellFormat)
	{
		if (!GetSheet()->writeBool(iRowIndex, iColumnIndex, bValue, GetFormat()))
		{
			SetErrorMessage("Failed to write bool value with format !");

			return false;
		}

		return true;
	}

	if (!GetSheet()->writeBool(iRowIndex, iColumnIndex, bValue))
	{
		SetErrorMessage("Failed to write bool value!");

		return false;
	}

	return true;
}

// Write a cell
Boolean Excel::WriteCellByFormula(Int32 iRowIndex,
	Int32 iColumnIndex,
	String strFormula,
	Boolean bIsUseCellFormat)
{
	if (iRowIndex < 0)
	{
		SetErrorMessage("Invalid row index,It must >=0");

		return false;
	}

	if (iColumnIndex < 0)
	{
		SetErrorMessage("Invalid column index,It must >=0");

		return false;
	}

	if (strFormula.IsEmpty())
	{
		return WriteCell(iRowIndex, iColumnIndex, strFormula, bIsUseCellFormat);
	}

	// Get the current sheet
	if (GetSheet() == NULL)
	{
		SetErrorMessage("Please set the sheet by SetWorkSheet at first!");

		return false;
	}

	if (bIsUseCellFormat)
	{
		if (!GetSheet()->writeFormula(iRowIndex, iColumnIndex, strFormula.CStr(), GetFormat()))
		{
			SetErrorMessage("Failed to write formula with format !");

			return false;
		}

		return true;
	}

	if (!GetSheet()->writeFormula(iRowIndex, iColumnIndex, strFormula.CStr()))
	{
		SetErrorMessage("Failed to write formula!");

		return false;
	}

	return true;
}

// Save the excel
Boolean Excel::Save(String strExcelFileName)
{
	if (strExcelFileName.IsEmpty())
	{
		SetErrorMessage("Save file path cannot be None!");

		return false;
	}

	if (!strExcelFileName.IsContain(":") && !strExcelFileName.IsContain("\\"))
	{
		SetErrorMessage("Please input valid path,such as \"D:\\A.xls\"!");

		return false;
	}

	if (GetBook() == NULL)
	{
		SetErrorMessage("Excel module hasn't been loaded");

		return false;
	}

	if (!GetBook()->save(strExcelFileName.CStr()))
	{
		std::string strErrorMsg = GetBook()->errorMessage();

		SetErrorMessage(strErrorMsg);

		return false;
	}

	return true;
}

// Release the excel
None Excel::Release()
{
	if (!GetIsClosed())
	{
		SetIsClosed(true);

		if (GetBook() == NULL)
		{
			SetErrorMessage("Excel module hasn't been loaded");

			return;
		}

		GetBook()->release();
	}
}

// Get the error message
String Excel::GetErrorMsg()
{
	return GetErrorMessage();
}
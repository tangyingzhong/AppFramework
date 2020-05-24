///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Offering excel's functions 
///</describe>
/// <date>2019/11/21</date>
///***********************************************************************
#ifndef IEXCEL_H
#define IEXCEL_H

#include <comdef.h>
#include "Common/PluginGenerator.h"

#define EXCEL _T("Excel.dll")
#define EXCEL_NAME _T("Excel")
#define EXCEL_VERSION 1,0,0
#define EXCEL_PLUGIN EXCEL_NAME,EXCEL_VERSION
#define EXCEL_BASE_EVENT_ID  BASE_EVENT_ID +3800

enum HorizontalAlignEnum
{
	H_GENERAL = 0,

	H_LEFT,

	H_CENTER,

	H_RIGHT,

	H_FILL,

	H_JUSTIFY,

	H_MERGE,

	H_DISTRIBUTED
};

enum VerticalAlignEnum
{
	V_TOP = 0,

	V_CENTER,

	V_BOTTOM,

	V_JUSTIFY,

	V_DISTRIBUTED
};

enum Font_ColorEnum
{
	COLOR_BLACK = 8, COLOR_WHITE, COLOR_RED, COLOR_BRIGHTGREEN, COLOR_BLUE, COLOR_YELLOW, COLOR_PINK, COLOR_TURQUOISE, COLOR_DARKRED,
	COLOR_GREEN, COLOR_DARKBLUE, COLOR_DARKYELLOW, COLOR_VIOLET, COLOR_TEAL, COLOR_GRAY25, COLOR_GRAY50, COLOR_PERIWINKLE_CF,
	COLOR_PLUM_CF, COLOR_IVORY_CF, COLOR_LIGHTTURQUOISE_CF, COLOR_DARKPURPLE_CF, COLOR_CORAL_CF, COLOR_OCEANBLUE_CF, COLOR_ICEBLUE_CF,
	COLOR_DARKBLUE_CL, COLOR_PINK_CL, COLOR_YELLOW_CL, COLOR_TURQUOISE_CL, COLOR_VIOLET_CL, COLOR_DARKRED_CL, COLOR_TEAL_CL,
	COLOR_BLUE_CL, COLOR_SKYBLUE, COLOR_LIGHTTURQUOISE, COLOR_LIGHTGREEN, COLOR_LIGHTYELLOW, COLOR_PALEBLUE, COLOR_ROSE, COLOR_LAVENDER,
	COLOR_TAN, COLOR_LIGHTBLUE, COLOR_AQUA, COLOR_LIME, COLOR_GOLD, COLOR_LIGHTORANGE, COLOR_ORANGE, COLOR_BLUEGRAY, COLOR_GRAY40,
	COLOR_DARKTEAL, COLOR_SEAGREEN, COLOR_DARKGREEN, COLOR_OLIVEGREEN, COLOR_BROWN, COLOR_PLUM, COLOR_INDIGO, COLOR_GRAY80,
	COLOR_DEFAULT_FOREGROUND = 0x0040, COLOR_DEFAULT_BACKGROUND = 0x0041, COLOR_TOOLTIP = 0x0051, COLOR_NONE = 0x7F, COLOR_AUTO = 0x7FFF
};

class IExcel:public IPlugin
{
public:
	typedef vector<String> HeadTable;
	typedef _variant_t AlterType;
	typedef vector<AlterType> ColumnTable;
	typedef ColumnTable RowTable;
	typedef HorizontalAlignEnum AlignHEnum;
	typedef VerticalAlignEnum AlignVEnum;
	typedef Font_ColorEnum FontColorEnum;

public:
	// Detructe the IExcel
	virtual ~IExcel() {	}

public:
	// Load the excel
	virtual Boolean Load(String strExcelFilePath) = 0;

	// Set the current active sheet
	virtual Boolean SetWorkSheet(Int32 iIndex) = 0;

	// Get the cell value
	virtual Boolean GetCell(Int32 iRowIndex, Int32 iColumnIndex, AlterType& AlterValue) = 0;

	// Get a column data
	virtual Boolean GetColumn(Int32 iColIndex, ColumnTable& CTable) = 0;

	// Get a row data
	virtual Boolean GetRow(Int32 iRowIndex, RowTable& RTable) = 0;

	// Set cell's format
	virtual None SetCellAlign(AlignHEnum eAlignH, AlignVEnum eAlignV) = 0;

	// Set cell's font
	virtual None SetCellFont(FontColorEnum eColor, Boolean bIsFontBold) = 0;

	// Get the column with
	virtual Boolean GetColumnWidth(Int32 iColumnIndex, Real& dWidth) = 0;

	// Set column's width
	virtual Boolean SetColumnWidth(Int32 iColumnIndex, Int32 iWidth) = 0;

	// Get the row height
	virtual Boolean GetRowHeight(Int32 iRowIndex, Real& dHeight) = 0;

	// Set row's height
	virtual Boolean SetRowHeight(Int32 iRowIndex, Int32 iHeight) = 0;

	// Write a cell
	virtual Boolean WriteCell(Int32 iRowIndex,
		Int32 iColumnIndex,
		String strValue,
		Boolean bIsUseCellFormat) = 0;

	// Write a cell
	virtual Boolean WriteCell(Int32 iRowIndex,
		Int32 iColumnIndex,
		Int32 iValue,
		Boolean bIsUseCellFormat) = 0;

	// Write a cell
	virtual Boolean WriteCell(Int32 iRowIndex,
		Int32 iColumnIndex,
		Real dValue,
		Boolean bIsUseCellFormat) = 0;

	// Write a cell
	virtual Boolean WriteCell(Int32 iRowIndex,
		Int32 iColumnIndex,
		Boolean bValue,
		Boolean bIsUseCellFormat) = 0;

	// Write a cell. Such as "SUM(B5:B6)"
	virtual Boolean WriteCellByFormula(Int32 iRowIndex,
		Int32 iColumnIndex,
		String strFormula,
		Boolean bIsUseCellFormat) = 0;

	// Save the excel
	virtual Boolean Save(String strExcelFileName) = 0;

	// Get the error message
	virtual String GetErrorMsg() = 0;
};

#endif // IEXCEL_H

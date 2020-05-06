#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tool_UnitTest
{
	TEST_CLASS(Excel_UnitTest)
	{
	public:
		TEST_METHOD(TestMethod_Load)
		{
			Excel ExcelHelper;

			Assert::IsFalse(ExcelHelper.Load(_T("D:\\34.xlsx")));

			Assert::IsFalse(ExcelHelper.Load(_T("D:软件参数对照表.xlsx")));

			Assert::IsFalse(ExcelHelper.Load(_T("D\\软件参数对照表.xlsx")));

			Assert::IsTrue(ExcelHelper.Load(_T("D:\\软件参数对照表.xlsx")));
		}

		TEST_METHOD(TestMethod_SetWorkSheet)
		{
			Excel ExcelHelper;

			Assert::IsTrue(ExcelHelper.Load(_T("D:\\软件参数对照表.xlsx")));

			Assert::IsTrue(ExcelHelper.SetWorkSheet(0));

			Assert::IsTrue(ExcelHelper.SetWorkSheet(1));

			Assert::IsFalse(ExcelHelper.SetWorkSheet(-1));

			Assert::IsFalse(ExcelHelper.SetWorkSheet(19000));
		}

		TEST_METHOD(TestMethod_GetCell)
		{
			Excel ExcelHelper;

			Assert::IsTrue(ExcelHelper.Load(_T("D:\\软件参数对照表.xlsx")));

			Excel::AlterType Value;

			Assert::IsTrue(ExcelHelper.GetCell(3, 1, Value));

			_bstr_t strValue = Value.bstrVal;

			String strFinalValue = strValue;

			Assert::IsTrue(strFinalValue == _T("目前没有传"));

			Assert::IsTrue(ExcelHelper.GetCell(40, 0, Value));

			_bstr_t strValue2 = Value.bstrVal;

			String strFinalValue2 = strValue2;

			Assert::IsTrue(strFinalValue2 == _T("sampleAccuracy name"));

			Assert::IsTrue(ExcelHelper.GetCell(17, 1, Value));

			Int32 iValue = (Int32)Value.dblVal;

			Assert::IsTrue(iValue == 620700);

			Assert::IsFalse(ExcelHelper.GetCell(-1, 1, Value));

			Assert::IsTrue(ExcelHelper.GetCell(0, 1999999, Value));

			_bstr_t strValue3 = Value.bstrVal;

			String strFinalValue3 = strValue3;

			Assert::IsTrue(strFinalValue3 == _T("None Cell"));
		}

		TEST_METHOD(TestMethod_GetColumn)
		{
			Excel ExcelHelper;

			Assert::IsTrue(ExcelHelper.Load(_T("D:\\软件参数对照表.xlsx")));

			Excel::ColumnTable Table;

			Assert::IsTrue(ExcelHelper.GetColumn(1, Table));

			Assert::IsTrue(!Table.None());

			Table.clear();

			Assert::IsTrue(ExcelHelper.GetColumn(19999, Table));

			for (Int32 iIndex = 0; iIndex < (Int32)Table.size();++iIndex)
			{
				String strValue = Table[iIndex].bstrVal;

				Assert::IsTrue(strValue ==_T("None Cell"));
			}

			Table.clear();

			Assert::IsFalse(ExcelHelper.GetColumn(-1, Table));
		}

		TEST_METHOD(TestMethod_GetRow)
		{
			Excel ExcelHelper;

			Assert::IsTrue(ExcelHelper.Load(_T("D:\\软件参数对照表.xlsx")));

			Excel::RowTable Table;

			Assert::IsTrue(ExcelHelper.GetRow(1, Table));

			Assert::IsTrue(!Table.None());

			Table.clear();

			Assert::IsTrue(ExcelHelper.GetRow(19999, Table));

			for (Int32 iIndex = 0; iIndex < (Int32)Table.size(); ++iIndex)
			{
				String strValue = Table[iIndex].bstrVal;

				Assert::IsTrue(strValue == _T("None Cell"));
			}

			Table.clear();

			Assert::IsFalse(ExcelHelper.GetRow(-1, Table));
		}

		TEST_METHOD(TestMethod_SetCellAlign)
		{
			Excel ExcelHelper;

			Assert::IsTrue(ExcelHelper.Load(_T("D:\\软件参数对照表.xlsx")));

			Excel::AlterType Value;

			Assert::IsTrue(ExcelHelper.GetCell(0, 0, Value));

			ExcelHelper.SetCellAlign(AlignH::ALIGNH_RIGHT, AlignV::ALIGNV_BOTTOM);

			String strValue = Value.bstrVal;

			Assert::IsTrue(ExcelHelper.WriteCell(0, 0, strValue, true));

			Assert::IsTrue(ExcelHelper.Save(_T("D:\\软件参数对照表.xlsx")));
		}

		TEST_METHOD(TestMethod_SetCellFont)
		{
			Excel ExcelHelper;

			Assert::IsTrue(ExcelHelper.Load(_T("D:\\软件参数对照表.xlsx")));

			Excel::AlterType Value;

			Assert::IsTrue(ExcelHelper.GetCell(3, 1, Value));

			ExcelHelper.SetCellAlign(AlignH::ALIGNH_RIGHT, AlignV::ALIGNV_BOTTOM);

			ExcelHelper.SetCellFont(Excel::FontColorEnum::COLOR_BLUE, true);

			String strValue = Value.bstrVal;

			Assert::IsTrue(ExcelHelper.WriteCell(3, 1, strValue, true));

			Assert::IsTrue(ExcelHelper.Save(_T("D:\\软件参数对照表.xlsx")));
		}

		TEST_METHOD(TestMethod_SetCellWidth)
		{
			Excel ExcelHelper;

			Assert::IsTrue(ExcelHelper.Load(_T("D:\\软件参数对照表.xlsx")));

			Excel::AlterType Value;

			Assert::IsTrue(ExcelHelper.GetCell(3, 1, Value));

			ExcelHelper.SetCellAlign(AlignH::ALIGNH_RIGHT, AlignV::ALIGNV_BOTTOM);

			ExcelHelper.SetCellFont(Excel::FontColorEnum::COLOR_RED, true);

			String strValue = Value.bstrVal;

			Assert::IsFalse(ExcelHelper.WriteCell(-1, 1, strValue, true));

			Assert::IsTrue(ExcelHelper.WriteCell(3, 1, strValue, true));

			Assert::IsFalse(ExcelHelper.SetColumnWidth(-1, 120));

			Assert::IsTrue(ExcelHelper.SetColumnWidth(1,50));

			Real dColWidth = 0;
			Assert::IsTrue(ExcelHelper.GetColumnWidth(1, dColWidth));

			Assert::IsTrue((Int32)dColWidth == 50);

			Assert::IsFalse(ExcelHelper.SetRowHeight(-1, 120));

			Assert::IsTrue(ExcelHelper.SetRowHeight(1, 50));

			Real dRowHeight = 0;
			Assert::IsTrue(ExcelHelper.GetRowHeight(1,dRowHeight));

			Assert::IsTrue((Int32)dRowHeight == 50);

			Assert::IsTrue(ExcelHelper.Save(_T("D:\\软件参数对照表.xlsx")));
		}

		TEST_METHOD(TestMethod_WriteCellByFormula)
		{
			Excel ExcelHelper;

			Assert::IsTrue(ExcelHelper.Load(_T("D:\\软件参数对照表.xlsx")));

			Assert::IsTrue(ExcelHelper.WriteCell(4, 1, 1000, false));

			Assert::IsTrue(ExcelHelper.WriteCell(5, 1, 2000, false));

			Assert::IsTrue(ExcelHelper.WriteCellByFormula(6, 1, _T("SUM(B5:B6)"), false));

			Assert::IsTrue(ExcelHelper.Save(_T("D:\\软件参数对照表.xlsx")));
		}
	};
}
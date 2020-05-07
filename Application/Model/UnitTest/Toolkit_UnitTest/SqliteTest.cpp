#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tool_UnitTest
{
	TEST_CLASS(SqliteTest)
	{
	public:
		TEST_METHOD(SqliteTest_Open)
		{
			SqliteDB db;

			if (!db.Open(_T("D:\\histroy.db")))
			{
				Assert::Fail(db.GetErrorMessage().CStr());
			}

			db.Close();
		}
	};
}

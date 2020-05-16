#include "pch.h"
#include "CppUnitTest.h"
#include "Model/Fundation/ILocalDB.h"
#include "PluginPtr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LocalDB_UnitTest
{
	TEST_CLASS(LocalDBTest)
	{
	public:
		TEST_METHOD(TestCreateTableFunc)
		{
			LoadLocalDb();

			if (!MyLocalDb->CreateTable(_T("CREATE TABLE SMT( \
			id INTEGER PRIMARY KEY NOT NULL, \
			name VARCHAR(50) NOT NULL, \
			age INTEGER NOT NULL \
			)")))
			{
				Assert::Fail(MyLocalDb->GetErrorMsg().CStr());
			}
		}

		TEST_METHOD(TestIsExistTableFunc)
		{
			LoadLocalDb();

			Assert::IsTrue(MyLocalDb->IsExisted("SMT"));
		}

		TEST_METHOD(TestAddRecordFunc)
		{
			LoadLocalDb();

			String strSql = String(_T("insert into SMT (id,name,age) values (%d,'%s',%d)"));

			String strTemp = strSql;

			String strSql1 = strSql.Arg(1).Arg("ÌÆÓ¦ÖÒ").Arg(28);

			Assert::IsTrue(MyLocalDb->AddRecord(strSql1));

			String strBase2 = strTemp;

			String strSql2 = strBase2.Arg(2).Arg("Ö£ÎÄÑà").Arg(27);

			Assert::IsTrue(MyLocalDb->AddRecord(strSql2));

			String strBase3 = strTemp;

			String strSql3 = strBase3.Arg(3).Arg("ÌÆÐÂºì").Arg(26);

			Assert::IsTrue(MyLocalDb->AddRecord(strSql3));

			String strBase4 = strTemp;

			String strSql4 = strBase4.Arg(4).Arg("Ö£ÎÄ¾ê").Arg(29);

			Assert::IsTrue(MyLocalDb->AddRecord(strSql4));
		}

		TEST_METHOD(TestModifyRecordFunc)
		{
			LoadLocalDb();

			String strSql = String(_T("update SMT set name = '%s' where id = %d"));

			String strSql1 = strSql.Arg("ÌÆÓ¦ÖÒ2").Arg(4);

			Assert::IsTrue(MyLocalDb->UpdateRecord(strSql1));
		}

		TEST_METHOD(TestDeleteRecordFunc)
		{
			LoadLocalDb();

			String strSql = String(_T("delete from SMT where id = %d"));

			String strSql1 = strSql.Arg(4);

			Assert::IsTrue(MyLocalDb->DeleteRecord(strSql1));
		}

		TEST_METHOD(TestSearchRecordFunc)
		{
			LoadLocalDb();

			String strSql = String(_T("select * from SMT where id = %d"));

			String strSql1 = strSql.Arg(2);

			ILocalDB::RecordTable Table;

			Assert::IsTrue(MyLocalDb->SearchRecord(strSql1, Table));
		}

		TEST_METHOD(TestGetTotalCountFunc)
		{
			LoadLocalDb();

			String strSql = String(_T("select count(*) from SMT"));

			String strSql1 = strSql;

			Int32 iCount = 0;

			Assert::IsTrue(MyLocalDb->GetTotalCount(strSql1,iCount));
		}

	private:
		// Load local db
		None LoadLocalDb()
		{
			Assert::IsTrue(MyLocalDb.SetPluginVersion(LOCALDB_PLUGIN));

			Assert::IsTrue(MyLocalDb.IsValid());

			Assert::IsTrue(MyLocalDb->Configure("D:\\history.db"));
		}

	private:
		// Local db plugin
		PluginPtr<ILocalDB> MyLocalDb;
	};
}

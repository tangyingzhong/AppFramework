#include "PreCompile.h"
#include "Database.h"
#include "LocalDB.h"

GENERATE_PLUGIN(LOCALDB_PLUGIN, LocalDB);

// Construct the LocalDB
LocalDB::LocalDB() :
	m_strDbFilePath(String("")),
	m_strErrorMsg(String("")),
	m_bDisposed(false)
{
	Initialize();
}

// Detructe the LocalDB
LocalDB::~LocalDB()
{
	Destory();
}

// Initialize the LocalDB
None LocalDB::Initialize()
{
	// Create the db
	CreateDbHelper();
}

// Destory the LocalDB
None LocalDB::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Destory db helper
		DestoryDbHelper();
	}
}

// Create db helper
None LocalDB::CreateDbHelper()
{
	if (!m_DbHelper.IsValid())
	{
		if (!m_DbHelper.Load(DATABASE_NAME))
		{
			SetDBHelper(NULL);

			return;
		}
	}

	SetDBHelper(m_DbHelper.Data());
}

// Destory db helper
None LocalDB::DestoryDbHelper()
{
	
}

// Configure the db
bool LocalDB::Configure(String strFilePath)
{
	if (strFilePath.IsEmpty())
	{
		SetErrorMessage(String("DB file path is None!"));

		return false;
	}

	SetDbFilePath(strFilePath);

	return true;
}

// Is table existed
bool LocalDB::IsExisted(String strTableName)
{
	if (strTableName.IsEmpty())
	{
		SetErrorMessage("Table name is empty!");

		return false;
	}

	if (GetDBHelper()==NULL)
	{
		SetErrorMessage("Database object is null !");

		return false;
	}

	if (!GetDBHelper()->IsOpen())
	{
		GetDBHelper()->Open(GetDbFilePath());
	}

	if (!GetDBHelper()->IsExistedTable(strTableName))
	{
		SetErrorMessage(GetDBHelper()->GetErrorMsg());

		return false;
	}

	return true;
}

// Excute the sql
Boolean LocalDB::ExcuteSql(String strSql)
{
	if (strSql.IsEmpty())
	{
		SetErrorMessage("Database object is null !");

		return false;
	}

	if (GetDBHelper() == NULL)
	{
		SetErrorMessage("Database object is null !");

		return false;
	}

	if (!GetDBHelper()->IsOpen())
	{
		GetDBHelper()->Open(GetDbFilePath());
	}

	Int32 iRetCode = 0;

	if (!GetDBHelper()->ExecuteNonQuery(strSql, iRetCode))
	{
		SetErrorMessage(GetDBHelper()->GetErrorMsg());

		return false;
	}

	return true;
}

// Create table in db
bool LocalDB::CreateTable(String strSql)
{
	return ExcuteSql(strSql);
}

// Add record to db
bool LocalDB::AddRecord(String strSql)
{
	return ExcuteSql(strSql);
}

// Delete record from the db
bool LocalDB::DeleteRecord(String strSql)
{
	return ExcuteSql(strSql);
}

// Update the record in db
bool LocalDB::UpdateRecord(String strSql)
{
	return ExcuteSql(strSql);
}

// Excute the sql
Boolean LocalDB::ExcuteSql(String strSql, RecordTable& Table)
{
	if (strSql.IsEmpty())
	{
		SetErrorMessage(String("Sql is empty!"));

		return false;
	}

	if (GetDBHelper() == NULL)
	{
		SetErrorMessage("Database object is null !");

		return false;
	}

	if (!GetDBHelper()->IsOpen())
	{
		GetDBHelper()->Open(GetDbFilePath());
	}

	if (!GetDBHelper()->ExecuteNonQuery(strSql, Table))
	{
		SetErrorMessage(GetDBHelper()->GetErrorMsg());

		return false;
	}

	return true;
}

// Search records from the db
bool LocalDB::SearchRecord(String strSql, RecordTable& Table)
{
	return ExcuteSql(strSql, Table);
}

// Get table's total count
bool LocalDB::GetTotalCount(String strSql, int& iTotalCount)
{
	RecordTable Table;

	if (!ExcuteSql(strSql, Table))
	{
		return false;
	}

	String strTotalCount = Table[0][0];

	iTotalCount = Int::Parse(strTotalCount);

	return true;
}

// Get error message
String LocalDB::GetErrorMsg()
{
	return GetErrorMessage();
}

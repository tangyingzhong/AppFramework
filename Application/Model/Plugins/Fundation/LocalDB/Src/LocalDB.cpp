#include "PreCompile.h"
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
	// Open db
	OpenDb();
}

// Destory the LocalDB
None LocalDB::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Close Db
		CloseDb();
	}
}

// Open the db
Boolean LocalDB::OpenDb()
{
	// Open the db
	if (!m_DB.IsOpen())
	{
		if (GetDbFilePath().IsEmpty())
		{
			SetErrorMessage("Db file path is empty, you have to configure local db at first !");

			return false;
		}

		if (!m_DB.Open(GetDbFilePath()))
		{
			SetErrorMessage(m_DB.GetErrorMessage());

			return false;
		}
	}

	return true;
}

// Close db
None LocalDB::CloseDb()
{
	if (m_DB.IsOpen())
	{
		m_DB.Close();
	}
}

// Excute the sql
Boolean LocalDB::ExcuteSql(String strSql, Int32 iRetCode)
{
	if (strSql.IsEmpty())
	{
		SetErrorMessage("Sql is empty!");

		return false;
	}

	// Open the db
	if (!OpenDb())
	{
		return false;
	}

	// Excute the sql
	if (!m_DB.ExecuteNonQuery(strSql, iRetCode))
	{
		SetErrorMessage(m_DB.GetErrorMessage());

		return false;
	}

	return true;
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

	// Open the db
	if (!OpenDb())
	{
		return false;
	}

	// Excute the sql
	if (!m_DB.IsExistedTable(strTableName))
	{
		SetErrorMessage(m_DB.GetErrorMessage());

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

// Search records from the db
bool LocalDB::SearchRecord(String strSql, RecordTable& Table)
{
	if (strSql.IsEmpty())
	{
		SetErrorMessage(String("Sql is None!"));

		return false;
	}

	// Open the db
	if (!OpenDb())
	{
		return false;
	}

	if (!m_DB.ExecuteNonQuery(strSql, Table))
	{
		SetErrorMessage(m_DB.GetErrorMessage());

		return false;
	}

	return true;
}

// Get table's total count
bool LocalDB::GetTotalCount(String strSql, int& iTotalCount)
{
	if (strSql.IsEmpty())
	{
		SetErrorMessage(String("Sql is None!"));

		return false;
	}

	// Open the db
	if (!OpenDb())
	{
		return false;
	}

	// Excute the sql
	RecordTable Table;

	if (!m_DB.ExecuteNonQuery(strSql, Table))
	{
		SetErrorMessage(m_DB.GetErrorMessage());

		return false;
	}

	String strTotalCount = Table[0][0];

	iTotalCount = Int::Parse(strTotalCount);

	return true;
}

// Get error message
String LocalDB::GetErrorMsg()
{
	return GetErrorMessage().ToANSIData();
}

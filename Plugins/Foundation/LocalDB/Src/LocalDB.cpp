#include "PreCompile.h"
#include "LocalDB.h"

GENERATE_PLUGIN(LOCALDB_PLUGIN, LocalDB);

// Construct the LocalDB
LocalDB::LocalDB() :
	m_strDbFilePath("")),
	m_strErrorMsg("")),
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
			SetErrorMessage(String("Db file path is None!"));

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
		SetErrorMessage(String("Sql is None!"));

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
bool LocalDB::Configure(std::string strFilePath)
{
	if (strFilePath.empty())
	{
		SetErrorMessage(String("DB file path is None!"));

		return false;
	}

	SetDbFilePath(strFilePath);

	return true;
}

// Is table existed
bool LocalDB::IsExisted(std::string strTableName)
{
	if (strTableName.empty())
	{
		SetErrorMessage(String("Table name is None!"));

		return false;
	}

	String strSql = String("SELECT * FROM sqlite_master WHERE type='table' and name = %s").Arg(strTableName);

	Int32 iRetCode = 0;

	if (!ExcuteSql(strSql, iRetCode))
	{
		return false;
	}

	if (iRetCode==SQLITE_DONE)
	{
		return false;
	}
	else if (iRetCode == SQLITE_ROW)
	{
		return true;
	}

	return false;
}

// Create table in db
bool LocalDB::CreateTable(std::string strSql)
{
	return ExcuteSql(strSql);
}

// Add record to db
bool LocalDB::AddRecord(std::string strSql)
{
	return ExcuteSql(strSql);
}

// Delete record from the db
bool LocalDB::DeleteRecord(std::string strSql)
{
	return ExcuteSql(strSql);
}

// Update the record in db
bool LocalDB::UpdateRecord(std::string strSql)
{
	return ExcuteSql(strSql);
}

// Search records from the db
bool LocalDB::SearchRecord(std::string strSql, RecordTable& Table)
{
	if (strSql.empty())
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
bool LocalDB::GetTotalCount(std::string strSql, int& iTotalCount)
{
	if (strSql.empty())
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
std::string LocalDB::GetErrorMsg()
{
	return GetErrorMessage().ToANSIData();
}

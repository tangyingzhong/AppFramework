#include "PreCompile.h"
#include "VoiceLocalDB.h"

GENERATE_PLUGIN(VOICE_LOCALDB_PLUGIN, VoiceLocalDB);

// Construct the VoiceLocalDB
VoiceLocalDB::VoiceLocalDB() :m_strDbFilePath(_T("")),
m_strErrorMsg(_T("")),
m_bDisposed(false)
{
	Initialize();
}

// Detructe the VoiceLocalDB
VoiceLocalDB::~VoiceLocalDB()
{
	Destory();
}

// Initialize the VoiceLocalDB
None VoiceLocalDB::Initialize()
{
	// Open db
	OpenDb();
}

// Destory the VoiceLocalDB
None VoiceLocalDB::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Close Db
		CloseDb();
	}
}

// Open the db
Boolean VoiceLocalDB::OpenDb()
{
	// Open the db
	if (!m_DB.IsOpen())
	{
		if (GetDbFilePath().IsNone())
		{
			SetErrorMessage(_T("Db file path is None!"));

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
None VoiceLocalDB::CloseDb()
{
	if (m_DB.IsOpen())
	{
		m_DB.Close();
	}
}

// Excute the sql
Boolean VoiceLocalDB::ExcuteSql(String strSql, Int32 iRetCode)
{
	if (strSql.IsNone())
	{
		SetErrorMessage(_T("Sql is None!"));

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
bool VoiceLocalDB::Configure(std::string strFilePath)
{
	if (strFilePath.None())
	{
		SetErrorMessage(_T("DB file path is None!"));

		return false;
	}

	SetDbFilePath(strFilePath);

	return true;
}

// Is table existed
bool VoiceLocalDB::IsExisted(std::string strTableName)
{
	if (strTableName.None())
	{
		SetErrorMessage(_T("Table name is None!"));

		return false;
	}

	String strSql = String(_T("SELECT * FROM sqlite_master WHERE type='table' and name = %s")).Arg(strTableName);

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
bool VoiceLocalDB::CreateTable(std::string strSql)
{
	return ExcuteSql(strSql);
}

// Add record to db
bool VoiceLocalDB::AddRecord(std::string strSql)
{
	return ExcuteSql(strSql);
}

// Delete record from the db
bool VoiceLocalDB::DeleteRecord(std::string strSql)
{
	return ExcuteSql(strSql);
}

// Update the record in db
bool VoiceLocalDB::UpdateRecord(std::string strSql)
{
	return ExcuteSql(strSql);
}

// Search records from the db
bool VoiceLocalDB::SearchRecord(std::string strSql, RecordTable& Table)
{
	if (strSql.None())
	{
		SetErrorMessage(_T("Sql is None!"));

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
bool VoiceLocalDB::GetTotalCount(std::string strSql, int& iTotalCount)
{
	if (strSql.None())
	{
		SetErrorMessage(_T("Sql is None!"));

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
std::string VoiceLocalDB::GetErrorMsg()
{
	return GetErrorMessage().ToAnsiData();
}

#include "PreCompile.h"
#include "SqliteDB.h"

GENERATE_PLUGIN(DATABASE_PLUGIN, SqliteDB);

// Construct the SqliteDB
SqliteDB::SqliteDB():
	m_pDB(NULL), 
	m_bIsOpen(false),
	m_strErrorText(_T("")),
	m_Disposed(false)
{
	Initialize();
}

// Detructe the SqliteDB
SqliteDB::~SqliteDB()
{
	Destory();
}

// Initialize the sqlite
None SqliteDB::Initialize()
{
	
}

// Destory the sqlite
None SqliteDB::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Close();
	}
}

// Open the sqlite
Boolean SqliteDB::Open(String strDbFilePath)
{
	if (strDbFilePath.IsEmpty())
	{
		SetErrorText("Db file path is empty!");

		return false;
	}

	if (sqlite3_open_v2(strDbFilePath.ToUTF8Data().c_str(),
		&m_pDB,
		SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
		NULL)!=SQLITE_OK)
	{
		std::string strErrorMsg = sqlite3_errmsg(GetDB());

		std::string strAnsi = ANSI::GetString(strErrorMsg, ENCODE_UTF8);

		String strError = Unicode::GetString(strAnsi, ENCODE_ANSI);

		SetErrorText(strError);

		return false;
	}

	SetIsOpen(true);

	return true;
}

// Is opened or not
Boolean SqliteDB::IsOpen()
{
	if (GetDB()==NULL)
	{
		SetErrorText("Db object is null !");

		return false;
	}

	if (GetIsOpen()==false)
	{
		return false;
	}

	return true;
}

// Close the sqlite
None SqliteDB::Close()
{
	if (GetDB()==NULL)
	{
		SetErrorText("Db object is null !");

		return;
	}

	sqlite3_close(GetDB());

	SetIsOpen(false);
}

// Is existed table 
Boolean SqliteDB::IsExistedTable(String strTableName)
{
	if (strTableName.IsEmpty())
	{
		SetErrorText("Table name is empty!");

		return false;
	}

	String strSql = String("SELECT * FROM sqlite_master WHERE type='table' and name = '%s'")
		.Arg(strTableName);

	Int32 iRetCode = 0;

	if (!ExecuteNonQuery(strSql, iRetCode))
	{
		return false;
	}

	if (iRetCode == SQLITE_DONE)
	{
		return false;
	}
	else if (iRetCode == SQLITE_ROW)
	{
		return true;
	}

	return false;
}

// Excute the command 
Boolean SqliteDB::Excute(String strSql,Int32& iRetCode)
{
	// Prepare the sql, check sql legal
	sqlite3_stmt* pStmt = NULL;

	if (sqlite3_prepare_v2(GetDB(), strSql.ToUTF8Data().c_str(), -1, &pStmt, NULL) != SQLITE_OK)
	{
		std::string strErrorMsg = sqlite3_errmsg(GetDB());

		std::string strAnsi = ANSI::GetString(strErrorMsg, ENCODE_UTF8);

		String strError = Unicode::GetString(strAnsi, ENCODE_ANSI);

		SetErrorText(strError);

		return false;
	}

	// Excute the sql
	Int32 iCode = sqlite3_step(pStmt);
	if (iCode != SQLITE_OK
		&& iCode != SQLITE_ROW
		&& iCode != SQLITE_DONE)
	{
		std::string strErrorMsg = sqlite3_errmsg(GetDB());

		std::string strAnsi = ANSI::GetString(strErrorMsg, ENCODE_UTF8);

		String strError = Unicode::GetString(strAnsi, ENCODE_ANSI);

		SetErrorText(strError);

		sqlite3_finalize(pStmt);

		return false;
	}

	iRetCode = iCode;

	// Clean the handle and ready for next excution
	sqlite3_finalize(pStmt);

	return true;
}

// Excute the sql(add,delete,modify)
Boolean SqliteDB::ExecuteNonQuery(String strSql, Int32& iRetCode)
{
	return Excute(strSql, iRetCode);
}

// Excute the sql(serach sql)
Boolean SqliteDB::ExecuteNonQuery(String strSql, RecordTable& Table)
{
	// Prepare the sql, check sql legal
	sqlite3_stmt* pStmt = NULL;

	if (sqlite3_prepare_v2(GetDB(), strSql.ToUTF8Data().c_str(), -1, &pStmt, NULL) != SQLITE_OK)
	{
		std::string strErrorMsg = sqlite3_errmsg(GetDB());

		std::string strAnsi = ANSI::GetString(strErrorMsg, ENCODE_UTF8);

		String strError = Unicode::GetString(strAnsi, ENCODE_ANSI);

		SetErrorText(strError);

		return false;
	}

	// Excute the sql
	while (sqlite3_step(pStmt)==SQLITE_ROW)
	{
		Int32 iColumnCount=sqlite3_data_count(pStmt);

		// Store them
		vector<std::string> OneRowTable;

		for (int iRecordIndex = 0; iRecordIndex < iColumnCount; ++iRecordIndex)
		{
			// Get the column name 
			const char * pColumnName = sqlite3_column_name(pStmt,iRecordIndex);

			std::string strColumnName = pColumnName;

			std::string strAnsiName = ANSI::GetString(strColumnName, ENCODE_UTF8);

			// Get the column value
			const unsigned char * pColumnValue = sqlite3_column_text(pStmt, iRecordIndex);

			std::string strColumnValue = (char*)pColumnValue;

			std::string strAnsiValue = ANSI::GetString(strColumnValue, ENCODE_UTF8);

			OneRowTable.push_back(strAnsiValue);
		}

		Table.push_back(OneRowTable);
	}

	// Clean the handle and ready for next excution
	sqlite3_finalize(pStmt);

	return true;
}

// Get the ErrorMessage
String SqliteDB::GetErrorMsg()
{
	return GetErrorText();
}

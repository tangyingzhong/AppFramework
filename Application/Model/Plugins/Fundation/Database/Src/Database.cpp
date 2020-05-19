#include "PreCompile.h"
#include "Database.h"
#include "SqliteDB.h"

GENERATE_PLUGIN(DATABASE_PLUGIN, Database);

// Construct the Database
Database::Database() :
	m_pDB(NULL),
	m_bDisposed(false)
{
	Initialize();
}

// Detructe the Database
Database::~Database()
{
	Destory();
}

// Initialize the Database
None Database::Initialize()
{
	// Create the db
	CreateDb();
}

// Destory the Database
None Database::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Destory the db
		DestoryDb();
	}
}

// Create db
None Database::CreateDb()
{
	SetDB(new SqliteDB());
}

// Destory db
None Database::DestoryDb()
{
	if (GetDB())
	{
		delete GetDB();

		SetDB(NULL);
	}
}

// Open the Database
Boolean Database::Open(String strDbFilePath)
{
	if (strDbFilePath.IsEmpty())
	{
		SetErrorText("Db file path is empty!");

		return false;
	}

	if (GetDB()==NULL)
	{
		SetErrorText("Db object is null !");

		return false;
	}

	if (!GetDB()->Open(strDbFilePath))
	{
		SetErrorText(GetDB()->GetErrorMsg());

		return false;
	}

	return true;
}

// Close the Database
None Database::Close()
{
	if (GetDB() == NULL)
	{
		SetErrorText("Db object is null !");

		return;
	}

	GetDB()->Close();
}

// Is opened or not
Boolean Database::IsOpen()
{
	if (GetDB() == NULL)
	{
		SetErrorText("Db object is null !");

		return false;
	}

	return GetDB()->IsOpen();
}

// Is existed table 
Boolean Database::IsExistedTable(String strTableName)
{
	if (strTableName.IsEmpty())
	{
		SetErrorText("Table name is empty !");

		return false;
	}

	if (GetDB() == NULL)
	{
		SetErrorText("Db object is null !");

		return false;
	}

	if (!GetDB()->IsExistedTable(strTableName))
	{
		SetErrorText(GetDB()->GetErrorMsg());

		return false;
	}

	return true;
}

// Excute the sql(serach sql)
Boolean Database::ExecuteNonQuery(String strSql, Int32& iRetCode)
{
	if (strSql.IsEmpty())
	{
		SetErrorText("Sql is empty !");

		return false;
	}

	if (GetDB() == NULL)
	{
		SetErrorText("Db object is null !");

		return false;
	}

	if (!GetDB()->ExecuteNonQuery(strSql,iRetCode))
	{
		SetErrorText(GetDB()->GetErrorMsg());

		return false;
	}

	return true;
}

// Excute the sql(serach sql)
Boolean Database::ExecuteNonQuery(String strSql, RecordTable& Table)
{
	if (strSql.IsEmpty())
	{
		SetErrorText("Sql is empty !");

		return false;
	}

	if (GetDB() == NULL)
	{
		SetErrorText("Db object is null !");

		return false;
	}

	if (!GetDB()->ExecuteNonQuery(strSql, Table))
	{
		SetErrorText(GetDB()->GetErrorMsg());

		return false;
	}

	return true;
}

// Get the ErrorMessage
String Database::GetErrorMsg()
{
	return GetErrorText();
}

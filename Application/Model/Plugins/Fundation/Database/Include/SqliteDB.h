///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
///  You can operate the sqlite by this class
///</describe>
/// <date>2019/8/6</date>
///***********************************************************************
#ifndef SQLITEDB_H
#define SQLITEDB_H

#include "Model/Fundation/IDatabase.h"
#include "sqlite3.h"

using namespace std;

class SqliteDB:public PluginBase<IDatabase>
{
public:
	typedef sqlite3* SqliteDataBase;
	typedef vector<vector<std::string> > RecordTable;

public:
	// Construct the SqliteDB
	SqliteDB();

	// Detructe the SqliteDB
	~SqliteDB();

private:
	// Forbid the Copy 
	SqliteDB(const SqliteDB& other) {	}

	// Forbid the assigment of 
	SqliteDB& operator=(const SqliteDB& other) { return *this; }

public:
	// Open the database
	virtual Boolean Open(String strDbFilePath);

	// Close the database
	virtual None Close();

	// Is opened or not
	virtual Boolean IsOpen();

	// Is existed table 
	virtual Boolean IsExistedTable(String strTableName);

	// Excute the sql(serach sql)
	virtual Boolean ExecuteNonQuery(String strSql, Int32& iRetCode);

	// Excute the sql(serach sql)
	virtual Boolean ExecuteNonQuery(String strSql, RecordTable& Table);

	// Get the ErrorMessage
	virtual String GetErrorMsg();

private:
	// Initialize the sqlite
	None Initialize();

	// Destory the sqlite
	None Destory();

	// Excute the command 
	Boolean Excute(String strSql, Int32& iRetCode);

private:
	// Get the DB
	inline SqliteDataBase& GetDB()
	{
		return m_pDB;
	}

	// Set the DB
	inline void SetDB(SqliteDataBase pDB)
	{
		m_pDB = pDB;
	}

	// Get the ErrorText
	inline String GetErrorText() const
	{
		return m_strErrorText;
	}

	// Set the ErrorText
	inline void SetErrorText(String strErrorText)
	{
		m_strErrorText = strErrorText;
	}

	// Get disposed status
	inline Boolean GetDisposed() const
	{
		return this->m_Disposed;
	}

	// Set the disposed status
	inline void SetDisposed(Boolean bDisposed)
	{
		this->m_Disposed = bDisposed;
	}

	// Get the IsOpen
	inline Boolean GetIsOpen() const
	{
		return m_bIsOpen;
	}

	// Set the IsOpen
	inline None SetIsOpen(Boolean bIsOpen)
	{
		m_bIsOpen = bIsOpen;
	}

private:
	// Sqlite db
	SqliteDataBase m_pDB;

	// Db is opened or not
	Boolean m_bIsOpen;

	// Error Message
	String m_strErrorText;

	// Disposed status
	Boolean m_Disposed;
};

#endif //SQLITEDB_H
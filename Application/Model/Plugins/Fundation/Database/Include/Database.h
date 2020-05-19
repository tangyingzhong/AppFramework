///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
///  It is a abstract class of db
///</describe>
/// <date>2019/8/6</date>
///***********************************************************************
#ifndef DATABASE_H
#define DATABASE_H

#include "Tool/BaseType/String.h"
#include "Tool/Common/SystemType.h"
#include "Model/Fundation/IDatabase.h"
#include "IDb.h"

using namespace std;
using namespace System::BasicType;

class Database:public PluginBase<IDatabase>
{
public:
	typedef IDb* DbHelper;
	typedef vector<vector<std::string> > RecordTable;

public:
	// Construct the Database
	Database();

	// Detructe the Database
	~Database();

private:
	// Forbid the Copy 
	Database(const Database& other) {	}

	// Forbid the assigment of 
	Database& operator=(const Database& other) { return *this; }

public:
	// Open the Database
	virtual Boolean Open(String strDbFilePath);

	// Close the Database
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
	// Initialize the Database
	None Initialize();

	// Destory the Database
	None Destory();

	// Create db
	None CreateDb();

	// Destory db
	None DestoryDb();

private:
	// Get the DB
	inline DbHelper GetDB()
	{
		return m_pDB;
	}

	// Set the DB
	inline void SetDB(DbHelper pDB)
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
		return m_bDisposed;
	}

	// Set the disposed status
	inline void SetDisposed(Boolean bDisposed)
	{
		m_bDisposed = bDisposed;
	}

private:
	// Database db
	DbHelper m_pDB;

	// Error Message
	String m_strErrorText;
	
	// Disposed status
	Boolean m_bDisposed;
};

#endif // DATABASE_H

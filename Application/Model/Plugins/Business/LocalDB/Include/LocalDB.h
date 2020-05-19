///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Local db which is abstract of db
///</describe>
/// <date>2019/12/18</date>
///***********************************************************************
#ifndef LOCALDB_H
#define LOCALDB_H

#include "Model/Business/ILocalDB.h"
#include "Model/Fundation/IDatabase.h"
#include "PluginLoader.h"

class LocalDB:public PluginBase<ILocalDB>
{
public:
	typedef IDatabase* DbHelper;

public:
	// Construct the LocalDB
	LocalDB();
	
	// Detructe the LocalDB
	virtual ~LocalDB();

private:
	// Forbid the copy LocalDB
	LocalDB(const LocalDB& other){	}
	
	// Forbid the assigment of LocalDB
	LocalDB& operator=(const LocalDB& other) { return *this; }
	
public:
	// Configure the db
	virtual bool Configure(String strFilePath);

	// Is table existed
	virtual bool IsExisted(String strTableName);

	// Create table in db
	virtual bool CreateTable(String strSql);

	// Add record to db
	virtual bool AddRecord(String strSql);

	// Delete record from the db
	virtual bool DeleteRecord(String strSql);

	// Update the record in db
	virtual bool UpdateRecord(String strSql);

	// Search records from the db
	virtual bool SearchRecord(String strSql, RecordTable& Table);

	// Get table's total count
	virtual bool GetTotalCount(String strSql, int& iTotalCount);

	// Get error message
	virtual String GetErrorMsg();

private:
	// Initialize the LocalDB
	None Initialize();

	// Destory the LocalDB
	None Destory();

	// Create db helper
	None CreateDbHelper();

	// Destory db helper
	None DestoryDbHelper();

	// Excute the sql
	Boolean ExcuteSql(String strSql);

	// Excute the sql
	Boolean ExcuteSql(String strSql, RecordTable& Table);

private:
	// Get the DbFilePath
	inline String GetDbFilePath() const
	{
		return m_strDbFilePath;
	}

	// Set the DbFilePath
	inline None SetDbFilePath(String strDbFilePath)
	{
		m_strDbFilePath = strDbFilePath;
	}

	// Get the disposed status
	inline Boolean GetDisposed() const
	{
		return m_bDisposed;
	}
	
	// Set the disposed status
	inline None SetDisposed(Boolean bDisposed)
	{
		m_bDisposed = bDisposed;
	}

	// Get the ErrorMsg
	inline String GetErrorMessage() const
	{
		return m_strErrorMsg;
	}

	// Set the ErrorMsg
	inline None SetErrorMessage(String strErrorMsg)
	{
		m_strErrorMsg = strErrorMsg;
	}

	// Get the DBHelper
	inline DbHelper GetDBHelper() const
	{
		return m_pDBHelper;
	}

	// Set the DBHelper
	inline void SetDBHelper(DbHelper pDBHelper)
	{
		m_pDBHelper = pDBHelper;
	}

private:
	// Database db
	DbHelper m_pDBHelper;

	// Plugin loader
	PluginLoader<IDatabase> m_DbHelper;

	// Db file path
	String m_strDbFilePath;

	// Error message
	String m_strErrorMsg;

	// Disposed status
	Boolean m_bDisposed;	
};

#endif // LocalDB_H

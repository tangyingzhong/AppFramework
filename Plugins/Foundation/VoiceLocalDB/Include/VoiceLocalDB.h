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
#ifndef VOICELOCALDB_H
#define VOICELOCALDB_H

#include "IVoiceLocalDB.h"

class VoiceLocalDB:public PluginBase<IVoiceLocalDB>
{
public:
	// Construct the VoiceLocalDB
	VoiceLocalDB();
	
	// Detructe the VoiceLocalDB
	virtual ~VoiceLocalDB();

private:
	// Forbid the copy VoiceLocalDB
	VoiceLocalDB(const VoiceLocalDB& other){	}
	
	// Forbid the assigment of VoiceLocalDB
	VoiceLocalDB& operator=(const VoiceLocalDB& other){	}
	
public:
	// Configure the db
	virtual bool Configure(std::string strFilePath);

	// Is table existed
	virtual bool IsExisted(std::string strTableName);

	// Create table in db
	virtual bool CreateTable(std::string strSql);

	// Add record to db
	virtual bool AddRecord(std::string strSql);

	// Delete record from the db
	virtual bool DeleteRecord(std::string strSql);

	// Update the record in db
	virtual bool UpdateRecord(std::string strSql);

	// Search records from the db
	virtual bool SearchRecord(std::string strSql, RecordTable& Table);

	// Get table's total count
	virtual bool GetTotalCount(std::string strSql, int& iTotalCount);

	// Get error message
	virtual std::string GetErrorMsg();

private:
	// Initialize the VoiceLocalDB
	None Initialize();

	// Destory the VoiceLocalDB
	None Destory();

	// Open the db
	Boolean OpenDb();

	// Close db
	None CloseDb();

	// Excute the sql
	Boolean ExcuteSql(String strSql,Int32 iRetCode=0);

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

private:
	// Sqlite db
	SqliteDB m_DB;

	// Db file path
	String m_strDbFilePath;

	// Error message
	String m_strErrorMsg;

	// Disposed status
	Boolean m_bDisposed;	
};

#endif // VOICELOCALDB_H

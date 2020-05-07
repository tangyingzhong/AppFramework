///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It offers the interfaces for local db
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef ILOCALDB_H
#define ILOCALDB_H

#include <string>
#include <tchar.h>
#include "Common/PluginGenerator.h"

#define LOACALDB _T("LocalDB.dll")
#define LOCALDB_NAME _T("LocalDB")
#define LOCALDB_VERSION 1,0,0
#define LOCALDB_PLUGIN LOCALDB_NAME,LOCALDB_VERSION
#define LOCALDB_BASE_EVENT_ID  BASE_EVENT_ID +3500

#include <string>
#include <vector>
#include <comutil.h>

class ILocalDB :public IPlugin
{
public:
	typedef std::vector<std::string> ColumnTable;
	typedef std::vector<ColumnTable > RecordTable;

public:
	// Virtual detructe the local db
	virtual ~ILocalDB() {		}

public:
	// Configure the db
	virtual bool Configure(std::string strFilePath) = 0;

	// Is table existed
	virtual bool IsExisted(std::string strTableName)=0;

	// Create table in db
	virtual bool CreateTable(std::string strSql) = 0;

	// Add record to db
	virtual bool AddRecord(std::string strSql) = 0;

	// Delete record from the db
	virtual bool DeleteRecord(std::string strSql) = 0;

	// Update the record in db
	virtual bool UpdateRecord(std::string strSql) = 0;

	// Search records from the db
	virtual bool SearchRecord(std::string strSql, RecordTable& Table) = 0;

	// Get table's total count
	virtual bool GetTotalCount(std::string strSql,int& iTotalCount) = 0;

	// Get error message
	virtual std::string GetErrorMsg() = 0;
};

#endif // IVOICELOCALDB_H

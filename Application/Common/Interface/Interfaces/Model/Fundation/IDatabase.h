#pragma once
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
#ifndef IDATABASE_H
#define IDATABASE_H

#include <string>
#include <tchar.h>
#include <vector>
#include "Common/PluginGenerator.h"

#define DATABASE _T("Database.dll")
#define DATABASE_NAME _T("Database")
#define DATABASE_VERSION 1,0,0
#define DATABASE_PLUGIN DATABASE_NAME,DATABASE_VERSION

class IDatabase :public IPlugin
{
public:
	typedef std::vector<std::string> ColumnTable;
	typedef std::vector<ColumnTable > RecordTable;

public:
	// Virtual detructe the database
	virtual ~IDatabase() {		}

public:
	// Open the database
	virtual Boolean Open(String strDbFilePath) = 0;

	// Close the database
	virtual None Close() = 0;

	// Is opened or not
	virtual Boolean IsOpen() = 0;

	// Is existed table 
	virtual Boolean IsExistedTable(String strTableName) = 0;

	// Excute the sql(serach sql)
	virtual Boolean ExecuteNonQuery(String strSql, Int32& iRetCode) = 0;

	// Excute the sql(serach sql)
	virtual Boolean ExecuteNonQuery(String strSql, RecordTable& Table) = 0;

	// Get the ErrorMessage
	virtual String GetErrorMsg() = 0;
};

#endif // IDATABASE_H

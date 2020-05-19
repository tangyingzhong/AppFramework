#pragma once
///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It offers the interfaces for real db
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef IDB_H
#define IDB_H

#include <string>
#include <tchar.h>
#include <vector>

class IDb
{
public:
	typedef std::vector<std::string> ColumnTable;
	typedef std::vector<ColumnTable > RecordTable;

public:
	// Virtual detructe the database
	virtual ~IDb() {		}

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

#endif // IDB_H

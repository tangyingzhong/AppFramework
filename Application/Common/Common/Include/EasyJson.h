///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// You can get some easily json operation service here
///</describe>
/// <date>2019/11/8</date>
///***********************************************************************
#ifndef EASYJSON_H
#define EASYJSON_H

class EasyJson
{
public:
	// Construct the EasyJson
	EasyJson();

	// Detructe the EasyJson
	~EasyJson();
	
private:
	// Forbid the copy EasyJson
	EasyJson(const EasyJson& other){	}
	
	// Forbid the assigment of EasyJson
	EasyJson& operator=(const EasyJson& other) { return *this; }

public:
	// Get Json document
	Boolean GetJsonDoc(String strJsonFilePath,JsonDocument& JsonDoc);

	// Set Json document
	Boolean SetJsonDoc(String strJsonFilePath, JsonDocument& JsonDoc);

private:
	// Initialize the EasyJson
	None Initialize();

	// Destory the EasyJson
	None Destory();
	
	// Set the object  string to file
	Boolean Save(String& strObject, String strJsonFilePath);

private:
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

private:
	// Disposed status
	Boolean m_bDisposed;	
};

#endif // EASYJSON_H
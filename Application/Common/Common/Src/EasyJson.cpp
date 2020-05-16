#include "PreCompile.h"
#include  "EasyJson.h"

// Construct the EasyJson
EasyJson::EasyJson() :
	m_pstrErrorText(new String()),
	m_bDisposed(false)
{
	Initialize();
}

// Detructe the EasyJson
EasyJson::~EasyJson()
{
	Destory();
}

// Initialize the EasyJson
None EasyJson::Initialize()
{

}

// Destory the EasyJson
None EasyJson::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Get Json document
Boolean EasyJson::GetJsonDoc(String strJsonFilePath, JsonDocument& JsonDoc)
{
	if (strJsonFilePath.IsEmpty())
	{
		SetErrorText("Json file path is empty!");

		return false;
	}

	String strErrorText;

	JsonDoc = JsonDocument::FromJsonFile(strJsonFilePath, strErrorText);

	if (JsonDoc.IsNull())
	{
		SetErrorText(JsonDoc.GetErrorMsg());

		return false;
	}

	return true;
}

// Set Json document
Boolean EasyJson::SetJsonDoc(String strJsonFilePath, JsonDocument& JsonDoc)
{
	if (strJsonFilePath.IsEmpty())
	{
		SetErrorText("Json file path is empty!");

		return false;
	}

	if (JsonDoc.IsNull())
	{
		SetErrorText(JsonDoc.GetErrorMsg());

		return false;
	}

	String strJson = JsonDoc.ToJson();

	return Save(strJson, strJsonFilePath);
}

// Set the device reg to file
Boolean EasyJson::Save(String strData, String strJsonFilePath)
{
	if (strJsonFilePath.IsEmpty() || strData.IsEmpty())
	{
		SetErrorText("Json file path is empty!");

		return false;
	}

	File FileHelper;

	if (!FileHelper.Open(strJsonFilePath, File::FileMode::CREATE, File::FileAccess::READWRITE))
	{
		return false;
	}

	FileHelper.Write(strData.ToUTF8Data().c_str(),0,strData.ToUTF8Data().length());

	FileHelper.Close();

	return true;
}

// Get error message
String EasyJson::GetErrorMsg()
{
	return GetErrorText();
}

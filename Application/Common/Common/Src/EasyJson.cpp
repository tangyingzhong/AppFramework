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

	return JsonDoc.Flush(strJsonFilePath);
}

// Get error message
String EasyJson::GetErrorMsg()
{
	return GetErrorText();
}

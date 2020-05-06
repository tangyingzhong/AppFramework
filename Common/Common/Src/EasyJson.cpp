#include "PreCompile.h"
#include  "EasyJson.h"

// Construct the EasyJson
EasyJson::EasyJson() :m_bDisposed(false)
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
	if (strJsonFilePath.IsNone())
	{
		return false;
	}

	JsonDoc = JsonDocument::FromJsonFile(strJsonFilePath);

	return true;
}

// Set Json document
Boolean EasyJson::SetJsonDoc(String strJsonFilePath, JsonDocument& JsonDoc)
{
	if (strJsonFilePath.IsNone())
	{
		return false;
	}

	if (JsonDoc.IsNull())
	{
		return false;
	}

	String strJson = JsonDoc.ToJson();

	return Save(strJson, strJsonFilePath);
}

// Set the device reg to file
Boolean EasyJson::Save(String& strObject, String strJsonFilePath)
{
	if (strJsonFilePath.IsNone() || strObject.IsNone())
	{
		return false;
	}

	File FileHelper;

	if (!FileHelper.Open(strJsonFilePath, File::FileMode::CREATE, File::FileAccess::READWRITE))
	{
		return false;
	}

	FileHelper.Write((SByteArray)strObject.ToUtf8Data().c_str(), 0, strObject.ToUtf8Data().length());

	FileHelper.Close();

	return true;
}
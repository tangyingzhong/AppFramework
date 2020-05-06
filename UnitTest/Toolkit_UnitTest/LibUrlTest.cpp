#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tool_UnitTest
{		
	TEST_CLASS(LibCurl_UnitTest)
	{
	public:
		TEST_METHOD(TestMethod_Post)
		{
			LibCurl CurlHelper;

			TransPara Paramenter;

			Paramenter.strRequestUrl = "http://192.168.0.101:8769/swk/equipment/info";

			JsonDocument JasonArray;

			JsonDocument JsonObj;

			JsonObj.SetKeyValue(_T("equipmentId"), _T("SHENGYANG-13-VCS2000-006C4004JV002B6F1"));

			JsonObj.SetKeyValue(_T("orgNo"), _T("132154625321"));

			JsonObj.SetKeyValue(_T("orgName"), _T("广东省--深圳市香港中文大学研究院602"));

			JsonObj.SetKeyValue(_T("ip"), _T("192.168.0.196"));

			JsonObj.SetKeyValue(_T("mac"), _T("iopMAC"));

			JsonObj.SetKeyValue(_T("systemName"), _T("SHENGYANG"));

			JasonArray.Append(JsonObj);

			String strUtf8Json = JasonArray.ToJson();

			Paramenter.strPostPara = strUtf8Json.ToAnsiData();

			Paramenter.iSecondTimeout = 1;

			Int32 iErrorCode = 0;

			String strErrorMsg = _T("");

			Boolean bRet = CurlHelper.Post(Paramenter, iErrorCode,strErrorMsg);

			Assert::IsTrue(bRet);

			File FileHelper;

			FileHelper.Open(_T("D:\\aaa.txt"), File::FileMode::CREATE);

			FileHelper.Write(Paramenter.strResponse.c_str(),
				0,
				Paramenter.strResponse.size());

			FileHelper.Close();
		}

		TEST_METHOD(TestMethod_Get)
		{
			LibCurl CurlHelper;

			TransPara Paramenter;

			Paramenter.strRequestUrl = "http://192.168.0.101:48769/swk/equipment/notice/SHENGYANG-13-VCS2000-006C4004JV002B6F1";

			Paramenter.iSecondTimeout = 1;

			Int32 iErrorCode = 0;
			
			String strErrorMsg = _T("");

			bool bRet = CurlHelper.Get(Paramenter, iErrorCode, strErrorMsg);

			Assert::IsTrue(bRet);

			File FileHelper;

			FileHelper.Open(_T("D:\\aaa.txt"), File::FileMode::CREATE);

			FileHelper.Write(Paramenter.strResponse.c_str(),
				0,
				Paramenter.strResponse.size());

			FileHelper.Close();
		}
	};
}
#include "pch.h"
#include "CppUnitTest.h"
#include "Model/Fundation/ILibCurl.h"
#include "LibCurl.h"
#include "PluginPtr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LibCurl_UnitTest
{		
	TEST_CLASS(LibCurlTest)
	{
	public:
		TEST_METHOD(TestMethod_Post)
		{
			LoadLibCurl();

			std::string strRespondData;

			Boolean bRet = LibCurlHelper->Post("https://www.baidu.com","yuer",strRespondData);

			Assert::IsTrue(bRet);

			File FileHelper;

			FileHelper.Open(_T("D:\\aaa.txt"), File::FileMode::CREATE);

			FileHelper.Write(strRespondData.c_str(),0,strRespondData.size());

			FileHelper.Close();
		}

		TEST_METHOD(TestMethod_Get)
		{
			LoadLibCurl();

			std::string strRespondData;

			Boolean bRet = LibCurlHelper->Get("https://www.baidu.com", "", strRespondData);

			if (!bRet)
			{
				Int32 iErrorCode = 0;

				std::string strErrorMsg = "";
				
				LibCurlHelper->GetErrorInfo(iErrorCode, strErrorMsg);
			}

			Assert::IsTrue(bRet);

			File FileHelper;

			FileHelper.Open(_T("D:\\aaa.txt"), File::FileMode::CREATE);

			FileHelper.Write(strRespondData.c_str(), 0, strRespondData.size());

			FileHelper.Close();
		}

		TEST_METHOD(Test_FtpUpload)
		{
			LoadLibCurl();

			bool bUploadOk = LibCurlHelper->FtpUpload("ftp://127.0.0.1/test/aaa2.txt", "D:\\Pool3.txt", "abc", "tang1028");

			Assert::IsTrue(bUploadOk);
		}

		TEST_METHOD(Test_FtpDownload)
		{
			LoadLibCurl();

			bool bUploadOk = LibCurlHelper->FtpDownload("ftp://127.0.0.1/test/aaa2.txt", "D:\\aaatest.txt", "abc", "tang1028");

			Assert::IsTrue(bUploadOk);
		}

	private:
		// Load curl
		None LoadLibCurl()
		{
			Assert::IsTrue(LibCurlHelper.SetPluginVersion(LIBCURL_PLUGIN));

			Assert::IsTrue(LibCurlHelper.IsValid());
		}

	private:
		// Local db plugin
		PluginPtr<ILibCurl> LibCurlHelper;
	};
}
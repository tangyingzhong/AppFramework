#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tool_UnitTest
{
	TEST_CLASS(Word_UnitTest)
	{
	public:
		TEST_METHOD(TestMethod_Load)
		{
			Word WordHelper;

			if (!WordHelper.Load(_T("D:\\1.docx")))
			{
				Assert::Fail(WordHelper.GetErrorMsg().CStr());
			}
		}

		TEST_METHOD(TestMethod_GetDoc)
		{
			Word WordHelper;

			if (!WordHelper.Load(_T("D:\\1.docx")))
			{
				Assert::Fail(WordHelper.GetErrorMsg().CStr());
			}

			String strContent;

			if (!WordHelper.GetDoc(strContent))
			{
				Assert::Fail(WordHelper.GetErrorMsg().CStr());
			}

			File FileHelper;

			Assert::IsTrue(FileHelper.Open(_T("D:\\aaa.txt"), File::FileMode::CREATE));

			FileHelper.Write(strContent.ToAnsiData().c_str(), 0, strContent.ToAnsiData().length());

			FileHelper.Close();
		}
	};
}
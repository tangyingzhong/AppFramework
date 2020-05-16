#include "pch.h"
#include "CppUnitTest.h"
#include "EasyJson.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EasyJson_UnitTest
{
	TEST_CLASS(EasyJsonTest)
	{
	public:
		TEST_METHOD(TestGetJsonDoc)
		{
			String strJsonFilePath = _T("D:\\System.json");

			JsonDocument JsonDoc;

			Assert::IsTrue(EasyJson().GetJsonDoc(strJsonFilePath, JsonDoc));

			Assert::IsFalse(JsonDoc.IsNull());
		}

		TEST_METHOD(TestSetJsonDoc1)
		{
			String strJsonFilePath = _T("D:\\System.json");

			JsonDocument JsonDoc;

			Assert::IsTrue(EasyJson().GetJsonDoc(strJsonFilePath, JsonDoc));

			Assert::IsFalse(JsonDoc.IsNull());

			String strNewJsonFilePath = _T("D:\\System231.json");

			Assert::IsTrue(EasyJson().SetJsonDoc(strNewJsonFilePath, JsonDoc));
		}
	};
}

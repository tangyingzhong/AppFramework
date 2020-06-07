#include "pch.h"
#include "CppUnitTest.h"
#include "Model/Fundation/IMiniZip.h"
#include "PluginPtr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MiniZip_UnitTest
{
	TEST_CLASS(MiniZipTest)
	{
	public:
		TEST_METHOD(TestCompressFile)
		{
			if (!MyZip.IsValid())
			{
				MyZip.SetPluginVersion(MINIZIP_PLUGIN);
			}

			Assert::IsTrue(MyZip.IsValid());

			if (!MyZip->CompressFile("D:\\aa.zip",
				"D:\\test.zip"))
			{
				Assert::Fail(MyZip->GetErrorMsg().ToUnicodeData().c_str());
			}
		}

		TEST_METHOD(TestUnCompressFolder)
		{
			if (!MyZip.IsValid())
			{
				MyZip.SetPluginVersion(MINIZIP_PLUGIN);
			}

			Assert::IsTrue(MyZip.IsValid());

			if (!MyZip->CompressFolder("D:\\Good\\",
				"D:\\test.zip"))
			{
				Assert::Fail(MyZip->GetErrorMsg().ToUnicodeData().c_str());
			}
		}

		TEST_METHOD(TestUnCompress)
		{
			if (!MyZip.IsValid())
			{
				MyZip.SetPluginVersion(MINIZIP_PLUGIN);
			}

			Assert::IsTrue(MyZip.IsValid());

			if (!MyZip->UnCompress("D:\\test.zip", 
				"D:\\test\\"))
			{
				Assert::Fail(MyZip->GetErrorMsg().ToUnicodeData().c_str());
			}
		}

		TEST_METHOD(TestGetFilePathInZip)
		{
			if (!MyZip.IsValid())
			{
				MyZip.SetPluginVersion(MINIZIP_PLUGIN);
			}

			Assert::IsTrue(MyZip.IsValid());

			String strFilePathInZip;

			Assert::IsTrue(MyZip->GetFilePathInZip("D:\\test.zip",
				"YB_王丽永_452702199210282075_6101-out.wav",
				strFilePathInZip));

			Assert::IsFalse(strFilePathInZip.IsEmpty());
		}

		TEST_METHOD(TestGetFileListInZip)
		{
			if (!MyZip.IsValid())
			{
				MyZip.SetPluginVersion(MINIZIP_PLUGIN);
			}

			Assert::IsTrue(MyZip.IsValid());

			std::vector<String> FileTableInZip;

			Assert::IsTrue(MyZip->GetFileListInZip("D:\\test.zip",
				FileTableInZip));

			Assert::IsFalse(FileTableInZip.empty());
		}

		TEST_METHOD(TestIsFileInZip)
		{
			if (!MyZip.IsValid())
			{
				MyZip.SetPluginVersion(MINIZIP_PLUGIN);
			}

			Assert::IsTrue(MyZip.IsValid());

			Assert::IsTrue(MyZip->IsFileInZip("D:\\test.zip",
				"Pool2.txt",
				true));
		}

		TEST_METHOD(TestIsFileInChildZip)
		{
			if (!MyZip.IsValid())
			{
				MyZip.SetPluginVersion(MINIZIP_PLUGIN);
			}

			Assert::IsTrue(MyZip.IsValid());

			Assert::IsTrue(MyZip->IsFileInChildZip("D:\\test.zip",
				"Win10激活工具.zip",
				"Q&A.txt",
				true));
		}

	private:
		PluginPtr<IMiniZip> MyZip;
	};
}

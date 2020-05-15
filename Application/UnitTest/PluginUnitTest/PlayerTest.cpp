#include "pch.h"
#include "CppUnitTest.h"
#include "Model/Fundation/IPlayer.h"
#include "PluginPtr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Player_UnitTest
{
	TEST_CLASS(PlayerTest)
	{
	public:
		TEST_METHOD(TestPlayerFunc)
		{
			PluginPtr<IPlayer> MyPlayer(PLAYER_PLUGIN);

			Assert::IsTrue(MyPlayer.IsValid());

			std::thread t = std::thread([=, &MyPlayer] {
				Assert::IsTrue(MyPlayer->Run(_T("D:\\林俊杰.-.[因你而在](2013)[WAV].wav")));
				});

			Sleep(60000);

			Assert::IsTrue(MyPlayer->Pause());

			Sleep(10000);

			Assert::IsTrue(MyPlayer->Continue());

			Sleep(60000);

			Assert::IsTrue(MyPlayer->Stop());

			if (t.joinable())
			{
				t.join();
			}
		}
	};
}

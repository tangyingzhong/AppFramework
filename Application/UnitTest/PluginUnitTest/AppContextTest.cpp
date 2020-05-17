#include "pch.h"
#include "CppUnitTest.h"
#include "Model/Core/IApplicationContext.h"
#include "AppFramework.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AppContext_UnitTest
{
	TEST_CLASS(AppContextTest)
	{
	public:
		TEST_METHOD(TestStartFunc)
		{
			StartAppContext();

			TaskEntry Task;

			Task.SetTaskId(1);

			Task.SetTaskName("��ط���");

			Task.SetUserFunc(TaskCallbackFunc);

			Task.SetUserData(this);

			Assert::IsTrue(m_pContext->Excute(&Task));

			TaskEntry Task2;

			Task2.SetTaskId(2);

			Task2.SetTaskName("��ط���2");

			Task2.SetUserFunc(TaskCallbackFunc2);

			Task2.SetUserData(this);

			Assert::IsTrue(m_pContext->Excute(&Task2));

			while (true)
			{
				Sleep(3000);

				SetExitTask(true);

				Sleep(3000);

				SetExitTask1(true);

				break;
			}
		}

	private:
		// Get the exit task 
		inline Boolean GetExitTask()
		{
			std::lock_guard<std::mutex> Locker(m_Lock);

			return m_bExitTask;
		}

		// Set the exit task
		inline void SetExitTask(Boolean bExited)
		{
			std::lock_guard<std::mutex> Locker(m_Lock);

			m_bExitTask = bExited;
		}

		// Get the exit task 
		inline Boolean GetExitTask1()
		{
			std::lock_guard<std::mutex> Locker(m_Lock1);

			return m_bExitTask1;
		}

		// Set the exit task
		inline void SetExitTask1(Boolean bExited)
		{
			std::lock_guard<std::mutex> Locker(m_Lock1);

			m_bExitTask1 = bExited;
		}

	private:
		// App context
		IApplicationContext* m_pContext;

		// Start the app context
		Boolean StartAppContext()
		{
			m_pContext = AppFramework::GetInstance()->GetGlobalContext();
			if (m_pContext == NULL)
			{
				return false;
			}

			return true;
		}

	private:
		// Callback count
		Int m_iExcuteCount;

		// Lock for the exit flag
		std::mutex m_Lock;

		// Exit thread
		Boolean m_bExitTask;

		// Lock for the exit flag
		std::mutex m_Lock1;

		// Exit thread
		Boolean m_bExitTask1;

		// Save the count
		Boolean Save(String strFilePath, String strData)
		{
			File FileHelper;

			if (!FileHelper.Open(strFilePath, File::FileMode::OPENORCREATE, File::FileAccess::WRITE))
			{
				return false;
			}

			FileHelper.Write(strData.ToANSIData().c_str(), 0, strData.ToANSIData().length());

			FileHelper.Close();

			return true;
		}

		// Task callback function
		static void TaskCallbackFunc(TaskEntry * pTask)
		{
			AppContextTest* pThis = (AppContextTest*)(pTask->GetUserData());

			Int32 iTotalDelayTime = 600;

			Int iDelayTime = 60;

			Int32 iDelayCount = iTotalDelayTime / iDelayTime;

			while (1)
			{
				if (pTask->GetIsExitPool())
				{
					break;
				}

				if (pThis->GetExitTask())
				{
					break;
				}

				// Do your business
				std::string strData = std::string("�ҵ��߳�ִ�д���:")
					+ std::to_string(pThis->m_iExcuteCount++)
					+ "\r\n";

				std::cout << strData;

				pThis->Save("D:\\Pool3.txt", strData);

				for (int index = 0; index < iDelayCount; ++index)
				{
					if (pTask->GetIsExitPool())
					{
						return;
					}

					if (pThis->GetExitTask())
					{
						return;
					}

					std::this_thread::sleep_for(std::chrono::milliseconds(iDelayTime));
				}
			}
		}

		// Task callback function
		static void TaskCallbackFunc2(TaskEntry * pTask)
		{
			AppContextTest* pThis = (AppContextTest*)(pTask->GetUserData());

			Int32 iTotalDelayTime = 600;

			Int iDelayTime = 60;

			Int32 iDelayCount = iTotalDelayTime / iDelayTime;

			while (1)
			{
				if (pTask->GetIsExitPool())
				{
					break;
				}

				if (pThis->GetExitTask1())
				{
					break;
				}

				// Do your business
				std::string strData = std::string("�ҵ��߳�ִ�д���:")
					+ std::to_string(pThis->m_iExcuteCount++)
					+ "\r\n";

				std::cout << strData;

				pThis->Save("D:\\Pool4.txt", strData);

				for (int index = 0; index < iDelayCount; ++index)
				{
					if (pTask->GetIsExitPool())
					{
						return;
					}

					if (pThis->GetExitTask1())
					{
						return;
					}

					std::this_thread::sleep_for(std::chrono::milliseconds(iDelayTime));
				}
			}
		}
	};
}

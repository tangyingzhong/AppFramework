#include "PreCompile.h"
#include "StateMachine.h"
#include "VoicePlayer.h"

GENERATE_PLUGIN(VOICE_PLAYER_PLUGIN, VoicePlayer);

// Construct the Player
VoicePlayer::VoicePlayer() :m_pAudioCallbackFunc(NULL),
m_bExitTask(false),
m_bDisposed(false)
{
	Initialize();
}

// Destory the Player
VoicePlayer::~VoicePlayer()
{
	Destory();
}

// Init the Player
None VoicePlayer::Initialize()
{

}

// Destory the Player
None VoicePlayer::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		if (m_WaitForCompleteThread.joinable())
		{
			m_WaitForCompleteThread.join();
		}
	}
}

// Playing call back
None VoicePlayer::PlayCallbackFunc()
{
	FixedInt32 iEventCode = 0;

	while (1)
	{
		if (GetExitTask())
		{
			break;
		}

		if (m_AudioPlayer.WaitForCompletion(0, &iEventCode))
		{
			if (GetAudioCallbackFunc())
			{
				Int64 iDuration = m_AudioPlayer.GetAudioTotalDuration();

				m_pAudioCallbackFunc(0, iDuration, true, m_pUserData);
			}

			break;
		}
		else
		{
			if (GetAudioCallbackFunc())
			{
				Int64 iPos = m_AudioPlayer.GetCurPlayPos();

				Int64 iDuration = m_AudioPlayer.GetAudioTotalDuration();

				m_pAudioCallbackFunc(iPos, iDuration, false, m_pUserData);
			}
		}

		Sleep(100);
	}
}

// Run the audio
Boolean VoicePlayer::Run(String strAudioFilePath,
	AudioCallbackFunc pFunc,
	void* pUserData)
{
	if (strAudioFilePath.IsNone())
	{
		return false;
	}

	m_pUserData = pUserData;

	if (!m_AudioPlayer.Load(strAudioFilePath))
	{
		Int32 iCode = ::GetLastError();

		LOG_ERROR(String(_T("Failed to laod audio file: %d")).Arg(iCode), _T(""));

		return false;
	}

	SetAudioCallbackFunc(pFunc);

	if (!m_AudioPlayer.Play())
	{
		Int32 iCode = ::GetLastError();

		LOG_ERROR(String(_T("Failed to play audio: %d")).Arg(iCode), _T(""));

		return false;
	}

	// Create  a thread to wait for the playing's completion
	m_WaitForCompleteThread = std::thread(&VoicePlayer::PlayCallbackFunc, this);

	return true;
}

// Close the player
Boolean VoicePlayer::Close()
{
	if (!m_AudioPlayer.Stop())
	{
		return false;
	}

	SetExitTask(true);

	return true;
}

// Comtinue the playing
Boolean VoicePlayer::Continue()
{
	return m_AudioPlayer.Resume();
}

// Pause the player
Boolean VoicePlayer::Pause()
{
	return m_AudioPlayer.Pause();
}
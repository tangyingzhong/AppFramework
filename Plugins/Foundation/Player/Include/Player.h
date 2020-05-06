///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
///  Offering the service for player
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef PLAYER_H
#define PLAYER_H

#include <thread>

class Player :public PluginBase<IPlayer>
{
public:
	// Construct the player
	Player();

	// Destory the player
	~Player();

private:
	// Forbid the player's copy
	Player(const Player& other){	}

	// Forbid the player's assignment
	Player& operator=(const Player& other){ return *this; }

public:
	// Run the audio
	virtual Boolean Run(String strAudioFilePath,
		AudioCallbackFunc pFunc = NULL,
		void* pUserData = NULL);

	// Close the player
	virtual Boolean Close();

	// Comtinue the playing
	virtual Boolean Continue();

	// Pause the player
	virtual Boolean Pause();

private:
	// Init the player
	None Initialize();

	// Destory the player
	None Destory();

	// Playing call back
	None PlayCallbackFunc();

private:
	// Get the AudioCallbackFunc
	inline AudioCallbackFunc GetAudioCallbackFunc() const
	{
		return m_pAudioCallbackFunc;
	}

	// Set the AudioCallbackFunc
	inline None SetAudioCallbackFunc(AudioCallbackFunc pAudioCallbackFunc)
	{
		m_pAudioCallbackFunc = pAudioCallbackFunc;
	}

	// Get the Disposed
	inline Boolean GetDisposed() const
	{
		return m_bDisposed;
	}

	// Set the Disposed
	inline None SetDisposed(Boolean bDisposed)
	{
		m_bDisposed = bDisposed;
	}

	// Get the ExitTask
	inline Boolean GetExitTask()
	{
		MutexLocker Locker(&m_ExitTaskLock);

		return m_bExitTask;
	}

	// Set the ExitTask
	inline None SetExitTask(Boolean bExitTask)
	{
		MutexLocker Locker(&m_ExitTaskLock);

		m_bExitTask = bExitTask;
	}

private:
	// Audio Player
	GeneralPlayer m_AudioPlayer;

	// Audio call back function
	AudioCallbackFunc m_pAudioCallbackFunc;

	// User data
	void* m_pUserData;

	// Wait for playing finished thread
	std::thread m_WaitForCompleteThread;

	// Lock for the task
	Mutex m_ExitTaskLock;

	// Exit the play task
	Boolean m_bExitTask;

	// Disposed status
	Boolean m_bDisposed;
};

#endif // Player_H
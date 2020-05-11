///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It offers the interfaces for player
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef IPLAYER_H
#define IPLAYER_H

#include "Common/PluginGenerator.h"

#define PLAYER _T("Player.dll")
#define PLAYER_NAME _T("Player")
#define PLAYER_VERSION 1,0,0
#define PLAYER_PLUGIN PLAYER_NAME,PLAYER_VERSION

class IPlayer :public IPlugin
{
public:
	typedef None(*AudioCallbackFunc)(Int64 iCurPlayingPos,
		Int64 iTotalDuration,
		Boolean bIsFinished,
		void* pUserData);

public:
	// Virtual detructe the player
	virtual ~IPlayer() {	}

public:
	// Run the audio
	virtual Boolean Run(String strAudioFilePath, 
		AudioCallbackFunc pFunc = NULL, 
		void* pUserData=NULL) = 0;

	// Close the player
	virtual Boolean Close() = 0;

	// Comtinue the playing
	virtual Boolean Continue() = 0;

	// Pause the player
	virtual Boolean Pause() = 0;
};

#endif // IVOICEPLAYER_H
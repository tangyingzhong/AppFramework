///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Defines the exported functions for the DLL application
///</describe>
/// <date>2019/7/15</date>
///***********************************************************************
#ifndef VOICEPLAYER_PRECOMPILE_H
#define  VOICEPLAYER_PRECOMPILE_H

#include "targetver.h"

// Disable the warnning of the non-security
#define _CRT_SECURE_NO_WARNINGS

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN           

// Windows Header Files:
#include <windows.h>

#include "Tool/Toolkit.h"

#include "Common/PluginBase.h"

#endif // VOICEPLAYER_PRECOMPILE_H
///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Generate the plugin here so that others can see it
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef PLUGINGENERATOR_H
#define PLUGINGENERATOR_H

#include "PluginBase.h"

template<class T>
struct PluginCreator
{
	// Create a plugin 
	static IPlugin* Create()
	{
		return new T();
	}

	// Destory the plugin
	static None Destory(IPlugin* pPlugin)
	{
		if (pPlugin)
		{
			T* pInstance = (T*)pPlugin;

			delete pInstance;

			pPlugin = NULL;
		}
	}
};

#define GENERATE_PLUGIN(NAME_AND_VERSION,PLUGIN_CLASS) \
static PluginInfo g_PluginInfo={NAME_AND_VERSION,NULL,\
PluginCreator<##PLUGIN_CLASS>::Create,\
PluginCreator<##PLUGIN_CLASS>::Destory}; \
class C##PLUGIN_CLASS :public PLUGIN_CLASS\
{\
public:\
	C##PLUGIN_CLASS() :PLUGIN_CLASS()\
	{\
		SetPluginInfo(g_PluginInfo);\
	}\
\
};\
REGISTER_MODULE(IPlugin,C##PLUGIN_CLASS)\


#endif //PLUGINGENERATOR_H

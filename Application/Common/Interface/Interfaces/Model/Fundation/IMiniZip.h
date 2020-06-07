///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Offer compress and uncompress file or folder interfaces
///</describe>
/// <date>2019/11/21</date>
///***********************************************************************
#ifndef IMINIZIP_H
#define IMINIZIP_H

#include "Common/PluginGenerator.h"

#define MINIZIP _T("MiniZip.dll")
#define MINIZIP_NAME _T("MiniZip")
#define MINIZIP_VERSION 1,0,0
#define MINIZIP_PLUGIN MINIZIP_NAME,MINIZIP_VERSION

class IMiniZip :public IPlugin
{
public:
	// Detructe the IMiniZip
	virtual ~IMiniZip() {	}

public:
	// Compress the file
	virtual Boolean CompressFile(String strSrcFilePath,
		String strZipFilePath,
		String strPassword = String("")) = 0;

	// Compress the file
	virtual Boolean CompressFile(std::vector<String>& SrcFilePathTable,
		String strZipFilePath,
		String strPassword = String("")) = 0;

	// Compress the folder (If you have another zip file to the current zip file ,you should not use password)
	virtual Boolean CompressFolder(String strSrcFolderPath,
		String strZipFilePath,
		String strPassword = String("")) = 0;

	// Uncompress zip file
	virtual Boolean UnCompress(String strZipFilePath,
		String strDestDirPath,
		String strPassword = String("")) = 0;

	// Get file path in zip
	virtual Boolean GetFilePathInZip(String strZipFilePath,
		String strFileName,
		String& strFilePathInZip,
		String strPassword = String("")) = 0;

	// Get file list in zip
	virtual Boolean GetFileListInZip(String strZipFilePath,
		std::vector<String>& FileList,
		String strPassword = String("")) = 0;

	// Is the file in this zip file
	virtual Boolean IsFileInZip(String strZipFilePath,
		String strFileName,
		bool bInsensitiveCase,
		String strPassword = String("")) = 0;

	// Is file in the zip by recursively(Child zip file must be in parent zip file)
	virtual Boolean IsFileInChildZip(String strParentZipFilePath,
		String strChildZipFileName,
		String strFileName,
		bool bInsensitiveCase,
		String strPassword = String("")) = 0;

	// Get the error message
	virtual String GetErrorMsg() = 0;
};

#endif // IMINIZIP_H

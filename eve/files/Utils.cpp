
/*
 Copyright (c) 2014, The eve Project
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of the {organization} nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Main header
#include "eve/files/Utils.h"



//=================================================================================================
std::string eve::files::normalizePath(const std::string & p_path)
{
	std::string str(p_path);

#if defined(EVE_OS_WIN)
	size_t inc = 0;
	for (size_t i = 0; i < p_path.length(); i++)
	{
		if (p_path.at(i) == '\\')
		{
			str.insert(i + inc, "\\");
			inc++;
		}
		else if (p_path.at(i) == '/')
		{
			str.replace(i + inc, 1, "\\");
		}
	}
#endif

	return str;
}



//=================================================================================================
bool eve::files::exists(const std::string & p_path)
{
	bool bret = false;

	// Try to open file
	FILE * file = fopen(p_path.c_str(), "r");
	// File exists
	if (file)
	{
		// Update return value
		bret = true;
		// Free memory
		fclose(file);
	}

	return bret;
}



//=================================================================================================
bool eve::files::copy(const std::string & p_pathSource, const std::string & p_pathDestination)
{
	bool bret = false;

	if (eve::files::exists(p_pathSource))
	{
		std::ifstream  src(p_pathSource, std::ios::binary);
		std::ofstream  dst(p_pathDestination, std::ios::binary);

		dst << src.rdbuf();

		bret = true;
	}

	return bret;
}



//=================================================================================================
std::string eve::files::remove_file_name(const std::string & p_path)
{
	std::string str = std::string(p_path);

	const size_t last_slash_idx = str.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		const size_t length = str.length();
		str.erase(last_slash_idx + 1, length);
	}

	return str;
}

//=================================================================================================
std::string eve::files::remove_extension(const std::string & p_name)
{
	std::string str = std::string(p_name);

	const size_t last_dot_idx = str.find_last_of(".");
	if (std::string::npos != last_dot_idx)
	{
		const size_t length = str.length();
		str.erase(last_dot_idx, length);
	}

	return str;
}

//=================================================================================================
std::string eve::files::get_file_name(const std::string & p_path)
{
	std::string str = std::string(p_path);

	const size_t last_slash_idx = str.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		str.erase(0, last_slash_idx + 1);
	}

	return str;
}



////-------------------------------------------------------------------------------------------
//COMDLG_FILTERSPEC extensionsToFileterSpec(std::pair<std::vector<std::string>, std::string> p_extensions)
//{
//	wchar_t extensionName[10000];
//	wchar_t extensionSpec[10000];
//
//	if (p_extensions.first.empty())
//	{
//		wcscpy(extensionName, NATIVE_TEXT_UNICODE("All\0"));
//		wcscpy(extensionSpec, NATIVE_TEXT_UNICODE("*.*\0"));
//	}
//	else
//	{
//		size_t offsetName = 0;
//		size_t offsetSpec = 0;
//
//		wchar_t * temp = toUnicode(p_extensions.second.c_str());
//
//		wcscpy(extensionName, temp);
//		offsetName += wcslen(extensionName) + 1;
//
//		delete temp;
//
//		for (std::vector<std::string>::const_iterator strIt = p_extensions.first.begin(); strIt != p_extensions.first.end(); ++strIt)
//		{
//			// Extension
//			wchar_t * ext = toUnicode(strIt->c_str());
//
//			// Name
//			wcscpy(extensionName + offsetName, L"(*.");
//			offsetName += 3;
//
//			wcscpy(extensionName + offsetName, ext);
//			offsetName += strIt->length();
//
//			wcscpy(extensionName + offsetName, L")");
//			offsetName += 1;
//
//			// Spec
//			wcscpy(extensionSpec + offsetSpec, L"*.");
//			offsetSpec += 2;
//
//			wcscpy(extensionSpec + offsetSpec, ext);
//			offsetSpec += strIt->length();
//
//
//			delete ext;
//
//			// append a semicolon to all but the last extensions
//			if (strIt + 1 != p_extensions.first.end())
//			{
//				extensionName[offsetName] = ';';
//				offsetName += 1;
//
//				extensionSpec[offsetSpec] = ';';
//				offsetSpec += 1;
//			}
//			else
//			{
//				extensionName[offsetName] = 0;
//				offsetName += 1;
//
//				extensionSpec[offsetSpec] = 0;
//				offsetSpec += 1;
//			}
//		}
//
//		extensionName[offsetName] = 0;
//		extensionSpec[offsetSpec] = 0;
//	}
//
//	COMDLG_FILTERSPEC extensionsArray;
//	extensionsArray.pszName = extensionName;
//	extensionsArray.pszSpec = extensionSpec;
//
//	return extensionsArray;
//}
//
//
////-------------------------------------------------------------------------------------------
//std::pair<std::string, std::string> getOpenFilePath(std::pair<std::vector<std::string>, std::string> p_extensions, const std::string & p_targetPath)
//{
//	LPWSTR szFilePath;
//	// Grab target path
//	IShellItem * pItemFolder = NULL;
//	if (p_targetPath.size() > 1)
//	{
//		szFilePath = toUnicode(p_targetPath.c_str());
//
//		HRESULT hr = ::SHCreateItemFromParsingName(szFilePath, NULL, IID_PPV_ARGS(&pItemFolder));
//
//		if (!SUCCEEDED(hr)) {
//			native_error_msg("NATIVESYSTEM::getOpenFolderPath", "unable to create IShellItem from path \n");
//		}
//	}
//
//	// Return value
//	std::pair<std::string, std::string> fileInfo = std::pair<std::string, std::string>(std::string(), std::string());
//
//	// Create the File Open Dialog object.
//	IFileDialog *pfd = NULL;
//	HRESULT hr = ::CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
//
//	// Dialog box created
//	if (SUCCEEDED(hr))
//	{
//		// Set the options on the dialog.
//		DWORD dwFlags;
//		// Before setting, always get the options first in order not to override existing options.
//		hr = pfd->GetOptions(&dwFlags);
//		if (SUCCEEDED(hr))
//		{
//			// In this case, get only files which extensions are specified below.
//			hr = pfd->SetOptions(dwFlags | FOS_STRICTFILETYPES);
//			if (SUCCEEDED(hr))
//			{
//				// Convert extensions vector to filter spec
//				COMDLG_FILTERSPEC extensionsArray = extensionsToFileterSpec(p_extensions);
//
//				// Set the file types to display only. Notice that, this is a 1-based array.
//				hr = pfd->SetFileTypes(1, &extensionsArray);
//				if (SUCCEEDED(hr))
//				{
//
//					pfd->SetFileTypeIndex(1);
//					if (!SUCCEEDED(hr)) {
//						native_error_msg("NATIVESYSTEM::getOpenFolderPath", "unable to set file type \n");
//					}
//					// Set target folder
//					if (pItemFolder)
//					{
//						hr = pfd->SetFolder(pItemFolder);
//
//						if (!SUCCEEDED(hr)) {
//							native_error_msg("NATIVESYSTEM::getOpenFolderPath", "unable to set default folder \n");
//						}
//					}
//
//					// Show the dialog
//					hr = pfd->Show(NULL);
//
//					if (SUCCEEDED(hr))
//					{
//						// Obtain the result, once the user clicks the 'Open' button.
//						// The result is an IShellItem object.
//						IShellItem *psiResult;
//						hr = pfd->GetResult(&psiResult);
//						if (SUCCEEDED(hr))
//						{
//							// Grab file path from dialog box
//							PWSTR pszFilePath = NULL;
//							hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
//							if (SUCCEEDED(hr))
//							{
//								// Grab file path
//								NATIVE_char8_t * path = toWideChar(pszFilePath);
//								std::string filePath = std::string(path);
//								// Free file path
//								CoTaskMemFree(pszFilePath);
//								delete path;
//
//								// Grab file name
//								std::string filename = getFileNameFromPath(filePath);
//
//								// Return value
//								fileInfo.first = std::string(filePath);
//								fileInfo.second = std::string(filename);
//							}
//							psiResult->Release();
//						}
//					}
//				}
//			}
//		}
//		if (pItemFolder) {
//			pItemFolder->Release();
//		}
//		pfd->Release();
//	}
//
//	//delete[](szFilePath); -> crash au load de video
//
//	// Return value
//	return fileInfo;
//}
//
//
//
////=============================================================================================
//void openDropBrowser(std::pair<std::vector<std::string>, std::string> p_extensions, const std::string & p_targetPath)
//{
//	wchar_t * dir = toUnicode(p_targetPath.c_str());
//
//	::ShellExecuteW(NULL, L"explore", dir, NULL, NULL, SW_NORMAL);
//
//	delete dir;
//}
//
//
//
////-------------------------------------------------------------------------------------------
//std::pair<std::string, std::string> getSaveFilePath(std::pair<std::vector<std::string>, std::string> p_extensions, const std::string & p_targetPath)
//{
//	// Grab target path
//	IShellItem * pItemFolder = NULL;
//	if (p_targetPath.size() > 1)
//	{
//		LPWSTR szFilePath = toUnicode(p_targetPath.c_str());
//
//		HRESULT hr = ::SHCreateItemFromParsingName(szFilePath, NULL, IID_PPV_ARGS(&pItemFolder));
//
//		if (!SUCCEEDED(hr)) {
//			native_error_msg("NATIVESYSTEM::getOpenFolderPath", "unable to create IShellItem from path \n");
//		}
//	}
//
//	// Return value
//	std::pair<std::string, std::string> fileInfo = std::pair<std::string, std::string>(std::string(), std::string());
//
//	// Create the File Open Dialog object.
//	IFileDialog *pfd = NULL;
//	HRESULT hr = ::CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
//
//	// Dialog box created
//	if (SUCCEEDED(hr))
//	{
//		// Set the options on the dialog.
//		DWORD dwFlags;
//		// Before setting, always get the options first in order not to override existing options.
//		hr = pfd->GetOptions(&dwFlags);
//		if (SUCCEEDED(hr))
//		{
//			// In this case, get only files which extensions are specified below.
//			hr = pfd->SetOptions(dwFlags | FOS_STRICTFILETYPES);
//			if (SUCCEEDED(hr))
//			{
//				// Convert extensions vector to filter spec
//				COMDLG_FILTERSPEC extensionsArray = extensionsToFileterSpec(p_extensions);
//
//				// Set the file types to display only. Notice that, this is a 1-based array.
//				hr = pfd->SetFileTypes(1, &extensionsArray);
//				if (SUCCEEDED(hr))
//				{
//					pfd->SetFileTypeIndex(1);
//					if (!SUCCEEDED(hr)) {
//						native_error_msg("NATIVESYSTEM::getOpenFolderPath", "unable to set file type \n");
//					}
//					// Set target folder
//					if (pItemFolder)
//					{
//						hr = pfd->SetFolder(pItemFolder);
//
//						if (!SUCCEEDED(hr)) {
//							native_error_msg("NATIVESYSTEM::getOpenFolderPath", "unable to set default folder \n");
//						}
//					}
//
//					// Show the dialog
//					hr = pfd->Show(NULL);
//
//					if (SUCCEEDED(hr))
//					{
//						// Obtain the result, once the user clicks the 'Save' button.
//						// The result is an IShellItem object.
//						IShellItem *psiResult;
//						hr = pfd->GetResult(&psiResult);
//						if (SUCCEEDED(hr))
//						{
//							// Grab file path from dialog box
//							PWSTR pszFilePath = NULL;
//							hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
//							if (SUCCEEDED(hr))
//							{
//								// Grab file path
//								NATIVE_char8_t * path = toWideChar(pszFilePath);
//								std::string pathStr = std::string(path);
//								std::string filePath;
//								std::string extension = "." + p_extensions.first.at(0);
//								if (pathStr.find(extension) == std::string::npos)
//									filePath = pathStr + extension; // have to get extension here cause dialog box display name doesn't return it :/
//								else
//									filePath = pathStr;
//								// Free file path
//								::CoTaskMemFree(pszFilePath);
//								delete path;
//
//								// Grab file name
//								std::string filename = getFileNameFromPath(filePath);
//
//								// Return value
//								fileInfo.first = std::string(filePath);
//								fileInfo.second = std::string(filename);
//							}
//							psiResult->Release();
//						}
//					}
//				}
//			}
//		}
//		if (pItemFolder) {
//			pItemFolder->Release();
//		}
//		pfd->Release();
//	}
//
//	// Return value
//	return fileInfo;
//}
//
//
//
////-------------------------------------------------------------------------------------------
//std::string getOpenFolderPath(const std::string & p_targetPath)
//{
//	// Grab target path
//	IShellItem * pItemFolder = NULL;
//	if (p_targetPath.size() > 1)
//	{
//		LPWSTR szFilePath = toUnicode(p_targetPath.c_str());
//
//		HRESULT hr = ::SHCreateItemFromParsingName(szFilePath, NULL, IID_PPV_ARGS(&pItemFolder));
//
//		if (!SUCCEEDED(hr)) {
//			native_error_msg("NATIVESYSTEM::getOpenFolderPath", "unable to create IShellItem from path \n");
//		}
//	}
//
//	// Return value
//	std::string String_Return = "";
//
//	// Create the File Open Dialog object.
//	IFileOpenDialog *pfd = NULL;
//	HRESULT hr = ::CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
//
//	// Dialog box created
//	if (SUCCEEDED(hr))
//	{
//		// Set the options on the dialog.
//		DWORD dwFlags;
//		// Before setting, always get the options first in order not to override existing options.
//		hr = pfd->GetOptions(&dwFlags);
//		if (SUCCEEDED(hr))
//		{
//			// In this case, get only files which extensions are specified below.
//			hr = pfd->SetOptions(dwFlags | FOS_PICKFOLDERS);
//			if (SUCCEEDED(hr))
//			{
//
//				// Set target folder
//				if (pItemFolder)
//				{
//					hr = pfd->SetFolder(pItemFolder);
//
//					if (!SUCCEEDED(hr)) {
//						native_error_msg("NATIVESYSTEM::getOpenFolderPath", "unable to set default folder \n");
//					}
//				}
//
//				// Show the dialog
//				hr = pfd->Show(NULL);
//
//				if (SUCCEEDED(hr))
//				{
//					// Obtain the result, once the user clicks the 'Open' button.
//					// The result is an IShellItem object.
//					IShellItem *psiResult = NULL;
//					hr = pfd->GetResult(&psiResult);
//					if (SUCCEEDED(hr))
//					{
//						// Grab file path from dialog box
//						PWSTR pszFilePath = NULL;
//						hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
//						if (SUCCEEDED(hr))
//						{
//							// Grab folder path
//							NATIVE_char8_t * path = toWideChar(pszFilePath);
//							String_Return = std::string(path);
//							// Free file path
//							::CoTaskMemFree(pszFilePath);
//							delete path;
//						}
//						psiResult->Release();
//					}
//				}
//			}
//		}
//		if (pItemFolder) {
//			pItemFolder->Release();
//		}
//		pfd->Release();
//	}
//
//	// Return value
//	return String_Return;
//}
//
//
//
////---------------------------------------------------------------------------------------------
//std::vector<std::string> listDirectoryFiles(const std::string & p_pathDirectory)
//{
//	// Return vector
//	std::vector<std::string> Vec_Return;
//
//
//	WIN32_FIND_DATA ffd;
//	TCHAR szDir[MAX_PATH];
//	size_t length_of_arg;
//	HANDLE hFind = INVALID_HANDLE_VALUE;
//	DWORD dwError = 0;
//
//
//	// Check that the input path plus 3 is not longer than MAX_PATH
//	// Three characters are for the "\*" plus NULL appended below
//	length_of_arg = p_pathDirectory.length();
//	if (length_of_arg > (MAX_PATH - 3))
//	{
//		native_error_msg("native_system::listDirectoryFiles", "Directory path is too long. \n");
//		return Vec_Return;
//	}
//
//
//	// Prepare string for use with FindFile functions.  First, copy the
//	// string to a buffer, then append '\*' to the directory name
//	wchar_t * wpathDirectory = toUnicode(p_pathDirectory.c_str());
//	wcscpy(szDir, wpathDirectory);
//	wcscat(szDir, NATIVE_TEXT_UNICODE("\\*"));
//
//	// Find the first file in the directory
//	hFind = ::FindFirstFileW(szDir, &ffd);
//	// If no file found
//	if (INVALID_HANDLE_VALUE == hFind)
//	{
//		native_info_msg("native_system::listDirectoryFiles", "Directory is empty. \n");
//		return Vec_Return;
//	}
//
//	// List all the files in the directory
//	do
//	{
//		NATIVE_char8_t * wcFileName = toWideChar(ffd.cFileName);
//		Vec_Return.push_back(std::string(wcFileName));
//		delete wcFileName;
//	} while (::FindNextFileW(hFind, &ffd) != 0);
//
//	// Check if files were missed
//	dwError = GetLastError();
//	if (dwError != ERROR_NO_MORE_FILES)
//	{
//		native_error_msg("native_system::listDirectoryFiles", "Files listing failed. \n");
//	}
//
//	// Release finding engine
//	::FindClose(hFind);
//
//	delete wpathDirectory;
//
//	return Vec_Return;
//}
//
//
//
////---------------------------------------------------------------------------------------------
//std::string getPathLocalDedicated(void)
//{
//	std::string path = getPathLocal();
//
//	// Local dir found
//	if (path.length() > 1)
//	{
//		// Add Dedicated directory to path
//		path += NATIVE_LOCAL_PATH_DEDICATED;
//
//		// Test directory
//		std::string testPath = std::string(path);
//		testPath += NATIVE_LOCAL_DIR_DEDICATED;
//		FILE * file = fopen(testPath.c_str(), "w+");
//
//		// Directory doesn't exist
//		if (!file)
//		{
//			wchar_t * wpath = toUnicode(path.c_str());
//			// Create directory
//			if (::CreateDirectoryW(wpath, NULL) != 0)
//			{
//				// create dummy file for test
//				file = fopen(testPath.c_str(), "w+");
//			}
//			else
//				native_error_msg("native_system::getPathLocalCPGP", "unable to create directory. \n");
//
//			delete wpath;
//		}
//		// Free memory
//		fclose(file);
//	}
//
//	return path;
//}
//
//
//
////=============================================================================================
//std::string getPathDesktop(void)
//{
//	static std::string path = "";
//
//	if (path.length() < 1)
//	{
//		wchar_t * my_path = 0;
//
//		if (::SHGetKnownFolderPath(FOLDERID_Desktop, 0/*KF_FLAG_NO_ALIAS | KF_FLAG_DONT_UNEXPAND*/, NULL, &my_path) == S_OK)
//		{
//			std::wstring ws(my_path);
//			path = std::string(ws.begin(), ws.end());
//		}
//		else
//			native_error_msg("native_system::getPathDesktop", "unable to retrieve desktop path. \n");
//
//		// free memory
//		::CoTaskMemFree(static_cast<void*>(my_path));
//	}
//
//	return path;
//}
//
//
//
////---------------------------------------------------------------------------------------------
//std::string getPathLogDedicated(void)
//{
//	std::string path = getPathLocalDedicated();
//
//	// Local dir found
//	if (path.length() > 1)
//	{
//		// Add dedicated directory to path
//		path += "\\log\\";
//
//		// Test directory
//		std::string testPath = std::string(path);
//		testPath += NATIVE_LOCAL_DIR_DEDICATED;
//		FILE * file = fopen(testPath.c_str(), "w+");
//
//		// Directory doesn't exist
//		if (!file)
//		{
//			wchar_t * wpath = toUnicode(path.c_str());
//			// Create directory
//			if (::CreateDirectoryW(wpath, NULL) != 0)
//			{
//				// create dummy file for test
//				file = fopen(testPath.c_str(), "w+");
//			}
//			else
//				native_error_msg("NATIVESYSTEM::getPathLogDedicated", "unable to create dedicated directory. \n");
//
//			delete wpath;
//		}
//		// Free memory
//		fclose(file);
//	}
//
//	return path;
//}
//
//std::string getPathPresetDedicated(void)
//{
//	std::string path = getPathLocalDedicated();
//
//	// Local dir found
//	if (path.length() > 1)
//	{
//		// Add preset directory to path
//		path += "\\preset\\";
//
//		// Test directory
//		std::string testPath = std::string(path);
//		testPath += NATIVE_LOCAL_DIR_DEDICATED;
//		FILE * file = fopen(testPath.c_str(), "w+");
//
//		// Directory doesn't exist
//		if (!file)
//		{
//			wchar_t * wpath = toUnicode(path.c_str());
//			// Create directory
//			if (::CreateDirectoryW(wpath, NULL) != 0)
//			{
//				// create dummy file for test
//				file = fopen(testPath.c_str(), "w+");
//			}
//			else
//				native_error_msg("native_system::getPathLocalCPGP", "unable to create directory. \n");
//
//			delete wpath;
//		}
//		// Free memory
//		fclose(file);
//	}
//
//	return path;
//}
//
////---------------------------------------------------------------------------------------------
//std::string getPathDocuments(void)
//{
//	static std::string path = "";
//
//	if (path.length() < 1)
//	{
//		wchar_t * my_path = 0;
//
//		if (::SHGetKnownFolderPath(FOLDERID_Documents, 0/*KF_FLAG_NO_ALIAS | KF_FLAG_DONT_UNEXPAND*/, NULL, &my_path) == S_OK)
//		{
//			std::wstring ws(my_path);
//			path = std::string(ws.begin(), ws.end());
//		}
//		else
//			native_error_msg("native_system::getPathDocuments", "unable to retrieve documents path. \n");
//
//		// free memory
//		::CoTaskMemFree(static_cast<void*>(my_path));
//	}
//
//	return path;
//}
//
//
//
////---------------------------------------------------------------------------------------------
//std::string getPathRoaming(void)
//{
//	// This has benn normalized cause of OSX, we added "\\MWM\\" to local path retrieve, 
//	// this need to be normalized in this file !!! otherwise we'll have to run threw every file of code 
//	// calling this method !!!
//	NATIVE_ASSERT(0);
//
//	static std::string path = "";
//
//	if (path.length() < 1)
//	{
//		wchar_t * my_path = 0;
//
//		if (::SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0/*KF_FLAG_NO_ALIAS | KF_FLAG_DONT_UNEXPAND*/, NULL, &my_path) == S_OK)
//		{
//			std::wstring ws(my_path);
//			path = std::string(ws.begin(), ws.end());
//		}
//		else
//			native_error_msg("native_system::getPathRoaming", "unable to retrieve roaming path. \n");
//
//		// free memory
//		::CoTaskMemFree(static_cast<void*>(my_path));
//	}
//
//	return path;
//}
//
//
//
////---------------------------------------------------------------------------------------------
//std::string getPathLocal(void)
//{
//	static std::string path = "";
//
//	if (path.length() < 1)
//	{
//		wchar_t * my_path = 0;
//
//		if (::SHGetKnownFolderPath(FOLDERID_LocalAppData, 0/*KF_FLAG_NO_ALIAS | KF_FLAG_DONT_UNEXPAND*/, NULL, &my_path) == S_OK)
//		{
//			std::wstring ws(my_path);
//			path = std::string(ws.begin(), ws.end());
//		}
//		else
//			native_error_msg("native_system::getPathLocal", "unable to retrieve local path. \n");
//
//		// free memory
//		::CoTaskMemFree(static_cast<void*>(my_path));
//	}
//
//	return path;
//}
//
//
//
////------------------------------------------------------------------------------------------------
//bool createDirectory(const std::string & p_path)
//{
//	wchar_t * wpath = toUnicode(p_path.c_str());
//	BOOL bReturn = ::CreateDirectoryW(wpath, NULL);
//	delete wpath;
//	return (bReturn != 0);
//}

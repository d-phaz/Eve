
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

#pragma once
#ifndef __EVE_FILES_UTILS_H__
#define __EVE_FILES_UTILS_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

namespace eve
{
	namespace files
	{
		/** \brief normalize path to fit system requirements. */
		std::wstring normalize_path(const std::wstring & p_path);


		/**
		* \brief test file existence.
		* \return true if file exists, false otherwise.
		*/
		bool exists(const std::wstring & p_path);


		/**
		* \brief copy file from path \p_pathSource to path \p_pathDestination.
		* \return true if file exists and copy was successful, false otherwise.
		*/
		bool copy(const std::wstring & p_pathSource, const std::wstring & p_pathDestination);


		/**
		* \brief remove file name from path.
		* \param p_path target path as std::wstring.
		* \return new path as std::wstring.
		*/
		std::wstring remove_file_name(const std::wstring & p_path);
		/**
		* \brief remove file name from path.
		* \param p_path target path as std::string.
		* \return new path as std::string.
		*/
		std::string remove_file_name(const std::string & p_path);


		/**
		* \brief remove extension from file name.
		* \param p_name target file name as std::wstring.
		* \return new name as std::wstring.
		*/
		std::wstring remove_extension(const std::wstring & p_name);
		/**
		* \brief remove extension from file name.
		* \param p_name target file name as std::string.
		* \return new name as std::string.
		*/
		std::string remove_extension(const std::string & p_name);


		/**
		* \brief get file name from path.
		* \param p_path target path as std::wstring.
		* \return file name as std::wstring.
		*/
		std::wstring get_file_name(const std::wstring & p_path);
		/**
		* \brief get file name from path.
		* \param p_path target path as std::string.
		* \return file name as std::string.
		*/
		std::string get_file_name(const std::string & p_path);


//#if defined(EVE_OS_WIN)
//		/**
//		* @brief convert extensions to filter spec
//		* @param p_extensions taget extensions list as std::vector<std::wstring>
//		* @return filter spec as COMDLG_FILTERSPEC
//		*/
//		COMDLG_FILTERSPEC extensionsToFileterSpec(std::pair<std::vector<std::wstring>, std::wstring> p_extensions);
//#endif //defined (NATIVE_OS_WIN32)
//
//
//		/**
//		* @brief open file
//		* @param p_extensions taget extensions list as std::vector<std::wstring>
//		* @param p_targetPath target path to start browsing as std::wstring (default to empty)
//		* @return file path and file name as std::pair<std::wstring,std::wstring>
//		* @note call folder browsing window
//		*/
//		std::wstring getOpenFilePath(const std::vector<std::wstring> & p_extensions, const std::wstring & p_targetPath = "");
//		/**
//		* @brief open folder
//		* @return folder path as std::wstring
//		* @param p_targetPath target path to start browsing as std::wstring (default to empty)
//		* @note call folder browsing window
//		*/
//		std::wstring getOpenFolderPath(const std::wstring & p_targetPath = "");
//		/**
//		* @brief open file browser to easily drop files on GUI
//		* @param p_extensions taget extensions list as std::vector<std::wstring>
//		* @param p_targetPath target path to start browsing as std::wstring (default to empty)
//		* @note call folder browsing window
//		*/
//		void openDropBrowser(const std::vector<std::wstring> & p_extensions, const std::wstring & p_targetPath = "");
//		/**
//		* @brief get save file path
//		* @param p_extensions taget extensions list as std::vector<std::wstring>
//		* @param p_targetPath target path to start browsing as std::wstring (default to empty)
//		* @return file path and file name as std::pair<std::wstring,std::wstring>
//		*/
//		std::wstring getSaveFilePath(const std::vector<std::wstring> & p_extensions, const std::wstring & p_targetPath = "");
//
//
//		/**
//		* @brief get the exe Path
//		* @return executable path as std::wstring
//		*/
//		std::wstring ExePath(void);
//
//
//		/**
//		* @brief list target directory files
//		* @param p_pathDirectory target directory path as std::wstring
//		* @return files list as std::vector<std::wstring>
//		*/
//		std::vector<std::wstring> listDirectoryFiles(const std::wstring & p_pathDirectory);
//
//
//		/**
//		* @brief get dedicated local directory, AppData/Local/mwm on windows
//		* @note if directory doesn't exist it'll be created
//		* @return directory path as std::wstring
//		*/
//		std::wstring getPathLocal(void);
//		/**
//		* @brief get documents path (user/Documents)
//		* @return documents path as std::wstring
//		*/
//		std::wstring getPathDocuments(void);
//		/**
//		* @brief get roaming path (AppData/Roaming)
//		* @return roaming path as std::wstring
//		*/
//		std::wstring getPathRoamingDedicated(void);
//		/**
//		* @brief get local path (AppData/Local)
//		* @return local path as std::wstring
//		*/
//		std::wstring getPathLocalDedicated(void);
//		/**
//		* @brief get desktop path
//		* @return path as std::wstring
//		*/
//		std::wstring getPathDesktop(void);
//
//
//		/**
//		* @brief create directory
//		* @param p_path new directory path
//		* @return true on success, false otherwise
//		*/
//		bool createDirectory(const std::wstring & p_path);

	} // namespace files

} // namespace eve

#endif // __EVE_FILES_UTILS_H__

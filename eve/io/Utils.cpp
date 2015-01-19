
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
#include "eve/io/Utils.h"

#ifndef __EVE_STRING_UTILS_H__
#include "eve/str/Utils.h"
#endif


//=================================================================================================
std::string eve::io::resource_path_material(const std::string & p_name)
{
	std::string ret = EVE_RESOURCES_PATH;
	ret += "/material/";
	ret += p_name;

	return ret;
}

//=================================================================================================
std::string eve::io::resource_path_glsl(const std::string & p_name)
{
	std::string ret = EVE_RESOURCES_PATH;
	ret += "/glsl/";
	ret += p_name;

	return ret;
}



//=================================================================================================
std::string eve::io::load_program(const std::string & p_filePath, const char * p_preamble, size_t * p_finalLength)
{
	// locals
	FILE * pFileStream = nullptr;
	size_t szSourceLength;

	// Open source code file.
#if defined(EVE_OS_WIN)   
	if (fopen_s(&pFileStream, p_filePath.c_str(), "rb") != 0)
	{
		// File open failed, path issue?
		EVE_ASSERT_FAILURE;
		EVE_LOG_ERROR("File opening failed, path is %s", eve::str::to_wstring(p_filePath).c_str());
		return NULL;
	}
#else
	pFileStream = fopen(p_filePath.c_str(), "rb");
	if (pFileStream == 0)
	{
		// File open failed, path issue?
		EVE_LOG_ERROR("File opening failed, path is %s", eve::str::to_wstring(p_filePath).c_str());
		EVE_ASSERT_FAILURE;
		return NULL;
	}
#endif


	// Get source code length.
	fseek(pFileStream, 0, SEEK_END);
	szSourceLength = ftell(pFileStream);
	fseek(pFileStream, 0, SEEK_SET);

	// Allocate string buffer.
	size_t szPreambleLength = 0;
	if (p_preamble)
	{
		szPreambleLength = strlen(p_preamble);
	}

	char * cSourceString = (char*)malloc(szSourceLength + szPreambleLength + 1);

	if (p_preamble)
	{
		memcpy(cSourceString, p_preamble, szPreambleLength);
	}

	if (fread((cSourceString)+szPreambleLength, szSourceLength, 1, pFileStream) != 1)
	{
		fclose(pFileStream);
		free(cSourceString);

		// File read failed.
		EVE_ASSERT_FAILURE;
		return NULL;
	}

	// Close the file and retrieve the total length of combined (preamble + source) string.
	fclose(pFileStream);
	if (p_finalLength)
	{
		*p_finalLength = szSourceLength + szPreambleLength;
	}
	cSourceString[szSourceLength + szPreambleLength] = '\0';

	std::string ret(cSourceString);
	free(cSourceString);
	return ret;
}

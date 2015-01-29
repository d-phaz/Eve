
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

// Main header.
#include "eve/ocl/core/Program.h"

#ifndef __EVE_STRING_UTILS_H__
#include "eve/str/Utils.h"
#endif



//=================================================================================================
eve::ocl::Program * eve::ocl::Program::create_ptr(cl_context p_context, cl_device_id p_device, const std::wstring & p_path)
{
	EVE_ASSERT(p_context);
	EVE_ASSERT(!p_path.empty());

	eve::ocl::Program * ptr = new eve::ocl::Program(p_context, p_device, p_path);
	ptr->init();
	return ptr;
}



//=================================================================================================
eve::ocl::Program::Program(cl_context p_context, cl_device_id p_device, const std::wstring & p_path)
	// Inheritance
	: eve::mem::Pointer()
	// Members init
	, m_context(p_context)
	, m_device(p_device)
	, m_path(p_path)
	, m_pPrgmContent(nullptr)
	, m_pKernels(nullptr)

	, m_err(CL_SUCCESS)
{}



//=================================================================================================
void eve::ocl::Program::init(void)
{
	std::string path	= eve::str::to_string(m_path);
	size_t prgmLength	= 0;

	m_pPrgmContent = this->load(path.c_str(), "", &prgmLength);
	EVE_ASSERT(m_pPrgmContent);

	m_program = clCreateProgramWithSource(m_context, 1, (const char **)&m_pPrgmContent, &prgmLength, &m_err);
	EVE_OCL_CHECK_PROGRAM(m_err);

	m_err = clBuildProgram(m_program, 1, &m_device, NULL, NULL, NULL);
	if (m_err != CL_SUCCESS)
	{
		char * build_log;
		size_t ret_val_size;
		m_err = clGetProgramBuildInfo(m_program, m_device, CL_PROGRAM_BUILD_LOG, 0, NULL, &ret_val_size);
		EVE_OCL_CHECK_PROGRAM(m_err);

		build_log = (char *)eve::mem::malloc(ret_val_size + 1);
		m_err = clGetProgramBuildInfo(m_program, m_device, CL_PROGRAM_BUILD_LOG, ret_val_size, build_log, NULL);
		EVE_OCL_CHECK_PROGRAM(m_err);

		// to be careful, terminate with \0, there's no information in the reference whether the string is 0 terminated or not.
		build_log[ret_val_size] = '\0';

		std::wstring wLog = eve::str::to_wstring(std::string(build_log));
		EVE_LOG_ERROR("OpenCL program build log: %s", wLog.c_str());
		eve::mem::free(build_log);
	}

	m_pKernels = new std::vector<eve::ocl::Kernel*>();
}

//=================================================================================================
void eve::ocl::Program::release(void)
{
	while (!m_pKernels->empty())
	{
		eve::ocl::Kernel * tmp = m_pKernels->back();
		m_pKernels->pop_back();
		EVE_RELEASE_PTR(tmp);
	}
	EVE_RELEASE_PTR_CPP(m_pKernels);


	if (m_program) {
		m_err = clReleaseProgram(m_program);
		EVE_OCL_CHECK_PROGRAM(m_err);
		m_program = nullptr;
	}
	EVE_RELEASE_PTR_C_SAFE(m_pPrgmContent);
}



//=================================================================================================
char * eve::ocl::Program::load(const char * p_path, const char * p_preamble, size_t * p_length)
{
	FILE* pFileStream = NULL;
	size_t szSourceLength;

	// Open OpenCL source code file.
#if defined(EVE_OS_WIN)
	if (fopen_s(&pFileStream, p_path, "rb") != 0)
	{
		return NULL;
	}
#else 
	pFileStream = fopen(p_path, "rb");
	if (pFileStream == 0)
	{
		return NULL;
	}
#endif

	size_t szPreambleLength = strlen(p_preamble);

	// Get source code length.
	fseek(pFileStream, 0, SEEK_END);
	szSourceLength = ftell(pFileStream);
	fseek(pFileStream, 0, SEEK_SET);

	// Allocate a buffer for the source code string and read it in.
	char* cSourceString = (char *)eve::mem::malloc(szSourceLength + szPreambleLength + 1);
	memcpy(cSourceString, p_preamble, szPreambleLength);
	if (fread((cSourceString)+szPreambleLength, szSourceLength, 1, pFileStream) != 1)
	{
		fclose(pFileStream);
		eve::mem::free(cSourceString);
		return 0;
	}

	// Close the file and return the total length of the combined (preamble + source) string.
	fclose(pFileStream);
	if (p_length != 0)
	{
		*p_length = szSourceLength + szPreambleLength;
	}
	cSourceString[szSourceLength + szPreambleLength] = '\0';

	return cSourceString;
}



//=================================================================================================
eve::ocl::Kernel * eve::ocl::Program::createKernel(const std::string & p_name)
{
	eve::ocl::Kernel * ret = eve::ocl::Kernel::create_ptr(m_program, p_name);
	m_pKernels->push_back(ret);
	return ret;
}


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
#ifndef __EVE_OPENCL_DEBUG_H__
#define __EVE_OPENCL_DEBUG_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_OPENCL_EXTERNAL_H__
#include "eve/ocl/core/External.h"
#endif

namespace eve
{
	namespace ocl
	{
		/** \brief check OpenCL platform error, log it and create error assertion. */
		void check_error_platform(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError);

		/** \brief check OpenCL device error, log it and create error assertion. */
		void check_error_device(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError);

		/** \brief check OpenCL context error, log it and create error assertion. */
		void check_error_context(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError);

		/** \brief check OpenCL command queue error, log it and create error assertion. */
		void check_error_command_qeue(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError);

		/** \brief check OpenCL program error, log it and create error assertion. */
		void check_error_program(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError);

		/** \brief check OpenCL kernel error, log it and create error assertion. */
		void check_error_kernel(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError);

	} // namespace ocl

} // namespace eve

/**
* \def EVE_OCL_CHECK_PLATFORM
* \brief Convenience macro to check OpenCL platform call for possible error.
*/
#ifndef NDEBUG
#define EVE_OCL_CHECK_PLATFORM(ERR_CODE)		eve::ocl::check_error_platform(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT_ENFORCE(__FILE__), __LINE__, ERR_CODE)
#else
#define EVE_OCL_CHECK_PLATFORM(ERR_CODE)
#endif

/**
* \def EVE_OCL_CHECK_DEVICE
* \brief Convenience macro to check OpenCL device call for possible error.
*/
#ifndef NDEBUG
#define EVE_OCL_CHECK_DEVICE(ERR_CODE)			eve::ocl::check_error_device(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT_ENFORCE(__FILE__), __LINE__, ERR_CODE)
#else
#define EVE_OCL_CHECK_DEVICE(ERR_CODE)
#endif

/**
* \def EVE_OCL_CHECK_CONTEXT
* \brief Convenience macro to check OpenCL context call for possible error.
*/
#ifndef NDEBUG
#define EVE_OCL_CHECK_CONTEXT(ERR_CODE)			eve::ocl::check_error_context(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT_ENFORCE(__FILE__), __LINE__, ERR_CODE)
#else
#define EVE_OCL_CHECK_CONTEXT(ERR_CODE)
#endif

/**
* \def EVE_OCL_CHECK_COMMAND_QUEUE
* \brief Convenience macro to check OpenCL command queue call for possible error.
*/
#ifndef NDEBUG
#define EVE_OCL_CHECK_COMMAND_QUEUE(ERR_CODE)	eve::ocl::check_error_command_qeue(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT_ENFORCE(__FILE__), __LINE__, ERR_CODE)
#else
#define EVE_OCL_CHECK_COMMAND_QUEUE(ERR_CODE)
#endif

/**
* \def EVE_OCL_CHECK_PROGRAM
* \brief Convenience macro to check OpenCL program call for possible error.
*/
#ifndef NDEBUG
#define EVE_OCL_CHECK_PROGRAM(ERR_CODE)			eve::ocl::check_error_program(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT_ENFORCE(__FILE__), __LINE__, ERR_CODE)
#else
#define EVE_OCL_CHECK_PROGRAM(ERR_CODE)
#endif

/**
* \def EVE_OCL_CHECK_KERNEL
* \brief Convenience macro to check OpenCL kernel call for possible error.
*/
#ifndef NDEBUG
#define EVE_OCL_CHECK_KERNEL(ERR_CODE)			eve::ocl::check_error_kernel(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT_ENFORCE(__FILE__), __LINE__, ERR_CODE)
#else
#define EVE_OCL_CHECK_KERNEL(ERR_CODE)
#endif

#endif // __EVE_OPENCL_DEBUG_H__

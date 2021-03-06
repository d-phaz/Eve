
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
#include "eve/ocl/core/Kernel.h"

#ifndef __EVE_STRING_UTILS_H__
#include "eve/str/Utils.h"
#endif



//=================================================================================================
eve::ocl::Kernel * eve::ocl::Kernel::create_ptr(cl_program p_program, const std::string & p_name)
{
	EVE_ASSERT(p_program);
	EVE_ASSERT(!p_name.empty());

	eve::ocl::Kernel * ptr = new eve::ocl::Kernel(p_program, p_name);
	ptr->init();
	return ptr;
}



//=================================================================================================
eve::ocl::Kernel::Kernel(cl_program p_program, const std::string & p_name)
	// Inheritance
	: eve::mem::Pointer()
	// Members init
	, m_program(p_program)
	, m_name(p_name)
	, m_kernel(nullptr)

	, m_err(CL_SUCCESS)
{}



//=================================================================================================
void eve::ocl::Kernel::init(void)
{
	m_kernel = clCreateKernel(m_program, m_name.c_str(), &m_err);
	EVE_OCL_CHECK_KERNEL(m_err);
}

//=================================================================================================
void eve::ocl::Kernel::release(void)
{
	if (m_kernel) {
		m_err = clReleaseKernel(m_kernel);
		EVE_OCL_CHECK_KERNEL(m_err);
		m_kernel = nullptr;
	}
}



//=================================================================================================
void eve::ocl::Kernel::setArgument(cl_uint p_index, size_t p_size, void * p_arg)
{
	m_err = clSetKernelArg(m_kernel, p_index, p_size, p_arg);
	EVE_OCL_CHECK_KERNEL(m_err);
}

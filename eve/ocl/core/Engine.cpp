
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
#include "eve/ocl/core/Engine.h"


//=================================================================================================
eve::ocl::Engine * eve::ocl::Engine::m_p_instance = nullptr;

//=================================================================================================
eve::ocl::Engine * eve::ocl::Engine::create_instance(void)
{
	EVE_ASSERT(!m_p_instance);

	m_p_instance = new eve::ocl::Engine();
	m_p_instance->init();
	return m_p_instance;
}

//=================================================================================================
void eve::ocl::Engine::release_instance(void)
{
	EVE_ASSERT(m_p_instance);
	EVE_RELEASE_PTR(m_p_instance);
}



//=================================================================================================
eve::ocl::Engine::Engine(void)
	// Inheritance
	: eve::mem::Pointer()
	// Members init
	, m_numPlatforms(0)
	, m_pPlatforms(nullptr)

	, m_numDevices(0)
	, m_pDevices(nullptr)

	, m_err(CL_SUCCESS)
{}



//=================================================================================================
void eve::ocl::Engine::init(void)
{
	// Get available platforms number.
	m_err = clGetPlatformIDs(0, NULL, &m_numPlatforms);
	EVE_OCL_CHECK_PLATFORM(m_err);

	if (m_numPlatforms > 0)
	{
		// Get available platforms.
		m_pPlatforms = (cl_platform_id*)malloc(m_numPlatforms * sizeof(cl_platform_id));
		m_err = clGetPlatformIDs(m_numPlatforms, m_pPlatforms, NULL);
		EVE_OCL_CHECK_PLATFORM(m_err);

		// Run threw platforms.
		for (cl_uint i = 0; i < m_numPlatforms; i++)
		{

		}
	}
}

//=================================================================================================
void eve::ocl::Engine::release(void)
{
	EVE_RELEASE_PTR_C_SAFE(m_pDevices);
	EVE_RELEASE_PTR_C_SAFE(m_pPlatforms);
}

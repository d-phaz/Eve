
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

#ifndef __EVE_OPENCL_CONTEXT_H__
#include "eve/ocl/core/Context.h"
#endif

#ifndef __EVE_STRING_UTILS_H__
#include "eve/str/Utils.h"
#endif


//=================================================================================================
eve::ocl::Engine * eve::ocl::Engine::m_p_instance = nullptr;

//=================================================================================================
eve::ocl::Engine * eve::ocl::Engine::create_instance(void)
{
	EVE_ASSERT(!m_p_instance);

	m_p_instance = EVE_CREATE_PTR(eve::ocl::Engine);
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

	, m_deviceMaxFlops(nullptr)
	, m_maxClockFrequency(0)
	, m_maxComputeUnits(0)
	, m_flops(0)

	, m_pContext(nullptr)
	, m_pContextGL(nullptr)
	, m_pContextDX(nullptr)

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

		// Useful vars.
		cl_platform_id	platform		= nullptr;
		cl_device_id	device			= nullptr;
		cl_int			computeUnits	= 0;
		cl_int			clockFrequency	= 0;
		cl_int			flops			= 0;

		// Run threw platforms.
		for (cl_uint i = 0; i < m_numPlatforms; i++)
		{
			platform = m_pPlatforms[i];

			// Get per platform available device(s) number.
			m_err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &m_numDevices);
			EVE_OCL_CHECK_DEVICE(m_err);

			// Get per platform available device(s).
			m_pDevices = (cl_device_id*)malloc(m_numDevices * sizeof(cl_device_id));
			m_err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, m_numDevices, m_pDevices, NULL);
			EVE_OCL_CHECK_DEVICE(m_err);


			// Run threw devices.
			for (cl_uint j = 0; j < m_numDevices; j++)
			{
				device = m_pDevices[j];

				m_err = clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_int), &clockFrequency, NULL);
				EVE_OCL_CHECK_DEVICE(m_err);

				m_err = clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_int), &computeUnits, NULL);
				EVE_OCL_CHECK_DEVICE(m_err);

				flops = computeUnits * clockFrequency;

				if (flops > m_flops)
				{
					m_platformMaxFlops  = platform;

					m_maxClockFrequency = clockFrequency;
					m_maxComputeUnits	= computeUnits;
					m_flops				= flops;
					m_deviceMaxFlops	= device;
				}
			}
		}
	}

	// Print selected device infos.
#ifndef NDEBUG
	if (m_deviceMaxFlops)
	{
		// Useful vars.
		size_t paramValueSize;
		char * txt = nullptr;
		std::wstring mess;


		// Device vendor.
		m_err = clGetDeviceInfo(m_deviceMaxFlops, CL_DEVICE_VENDOR, 0, NULL, &paramValueSize);
		EVE_OCL_CHECK_DEVICE(m_err);

		txt = (char*)malloc(sizeof(char)* paramValueSize);
		m_err = clGetDeviceInfo(m_deviceMaxFlops, CL_DEVICE_VENDOR, paramValueSize, txt, NULL);
		EVE_OCL_CHECK_DEVICE(m_err);

		mess = eve::str::to_wstring(txt);
		free(txt);
		EVE_LOG_INFO("OpenCL Device Vendor:          %s", mess.c_str());


		// Device name.
		m_err = clGetDeviceInfo(m_deviceMaxFlops, CL_DEVICE_NAME, 0, NULL, &paramValueSize);
		EVE_OCL_CHECK_DEVICE(m_err);

		txt = (char*)malloc(sizeof(char)* paramValueSize);
		m_err = clGetDeviceInfo(m_deviceMaxFlops, CL_DEVICE_NAME, paramValueSize, txt, NULL);
		EVE_OCL_CHECK_DEVICE(m_err);

		mess = eve::str::to_wstring(txt);
		free(txt);
		EVE_LOG_INFO("OpenCL Device Name:            %s", mess.c_str());


		// Device version.
		m_err = clGetDeviceInfo(m_deviceMaxFlops, CL_DEVICE_VERSION, 0, NULL, &paramValueSize);
		EVE_OCL_CHECK_DEVICE(m_err);

		txt = (char*)malloc(sizeof(char)* paramValueSize);
		m_err = clGetDeviceInfo(m_deviceMaxFlops, CL_DEVICE_VERSION, paramValueSize, txt, NULL);
		EVE_OCL_CHECK_DEVICE(m_err);

		mess = eve::str::to_wstring(txt);
		free(txt);
		EVE_LOG_INFO("OpenCL Device Version:         %s", mess.c_str());


		// Flops.
		EVE_LOG_INFO("OpenCL Device Clock Frequency: %d", m_maxClockFrequency);
		EVE_LOG_INFO("OpenCL Device Compute Units:   %d", m_maxComputeUnits);
	}
#endif


	// Initialize default context
	cl_context_properties props[] =
	{
		CL_CONTEXT_PLATFORM, cl_context_properties(m_platformMaxFlops),
		0
	};
	cl_context context = clCreateContext(props, 1, &m_deviceMaxFlops, NULL, NULL, &m_err);
	EVE_OCL_CHECK_CONTEXT(m_err);

	m_pContext = eve::ocl::Context::create_ptr(context);
}

//=================================================================================================
void eve::ocl::Engine::release(void)
{
	EVE_RELEASE_PTR_SAFE(m_pContext);
	EVE_RELEASE_PTR_SAFE(m_pContextGL);
	EVE_RELEASE_PTR_SAFE(m_pContextDX);

	EVE_RELEASE_PTR_C_SAFE(m_pDevices);
	EVE_RELEASE_PTR_C_SAFE(m_pPlatforms);
}



//=================================================================================================
eve::ocl::Context * eve::ocl::Engine::create_context_OpenGL(HGLRC p_GLRC, HDC p_DC)
{
	EVE_ASSERT(!m_p_instance->m_pContextGL);

	cl_context_properties props[] = 
	{ 
		CL_GL_CONTEXT_KHR,		(cl_context_properties)p_GLRC, 
		CL_WGL_HDC_KHR,			(cl_context_properties)p_DC, 
		CL_CONTEXT_PLATFORM,	(cl_context_properties)m_p_instance->m_platformMaxFlops,
		0 
	}; 
	cl_int err;
	cl_context context = clCreateContext(props, 1, &m_p_instance->m_deviceMaxFlops, NULL, NULL, &err);
	EVE_OCL_CHECK_CONTEXT(err);

	m_p_instance->m_pContextGL = eve::ocl::Context::create_ptr(context);

	return m_p_instance->m_pContextGL;
}

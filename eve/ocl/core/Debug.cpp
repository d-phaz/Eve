
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
#include "eve/ocl/core/Debug.h"

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif


//=================================================================================================
void eve::ocl::check_error_platform(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError)
{
	if (p_clError != CL_SUCCESS)
	{
		std::wstring mess;
		std::wstring errorString;
		std::wstring errorTitle;

		switch (p_clError)
		{
		case  CL_INVALID_VALUE:
			errorTitle   = EVE_TXT("CL_INVALID_VALUE");
			errorString  = EVE_TXT("clGetPlatformIDs : num_entries is equal to zero and platforms is not NULL, or both num_platforms and platforms are NULL. \n");
			errorString += EVE_TXT("clGetPlatformInfo : param_name is not one of the supported values or size in bytes specified by param_value_size is less than size of return type and param_value is not a NULL value.");
			break;

		case CL_INVALID_PLATFORM:
			errorTitle  = EVE_TXT("CL_INVALID_PLATFORM");
			errorString = EVE_TXT("clGetPlatformInfo : platform is not a valid platform.");
			break;
		}

		mess  = errorTitle;
		mess += EVE_TXT(" spec. info: ");
		mess += errorString;

		EVE_LOG_ERROR("OpenCL Error: %s in function %s in file %s at line %d.", mess.c_str(), p_pFunction, p_pFile, p_line);
		EVE_ASSERT_FAILURE;
	}
}



//=================================================================================================
void eve::ocl::check_error_device(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError)
{
	if (p_clError != CL_SUCCESS)
	{
		std::wstring mess;
		std::wstring errorString;
		std::wstring errorTitle;

		switch (p_clError)
		{
		case  CL_INVALID_PLATFORM:
			errorTitle  = EVE_TXT("CL_INVALID_PLATFORM");
			errorString = EVE_TXT("clGetDeviceIDs : platform is not a valid platform.");
			break;

		case  CL_INVALID_DEVICE_TYPE:
			errorTitle  = EVE_TXT("CL_INVALID_DEVICE_TYPE");
			errorString = EVE_TXT("clGetDeviceIDs : device_type is not a valid value.");
			break;

		case  CL_INVALID_VALUE:
			errorTitle   = EVE_TXT("CL_INVALID_VALUE");
			errorString  = EVE_TXT("clGetDeviceIDs : num_entries is equal to zero and device_type is not NULL or both num_devices and device_type are NULL. \n");
			errorString += EVE_TXT("clGetDeviceInfo : param_name is not one of the supported values or size in bytes specified by param_value_size is less than size of return type and param_value is not a NULL value.");
			break;

		case  CL_DEVICE_NOT_FOUND:
			errorTitle  = EVE_TXT("CL_DEVICE_NOT_FOUND");
			errorString = EVE_TXT("clGetDeviceIDs : no OpenCL devices that matched device_type were found.");
			break;

		case  CL_INVALID_DEVICE:
			errorTitle  = EVE_TXT("CL_INVALID_DEVICE");
			errorString = EVE_TXT("clGetDeviceInfo : device is not valid.");
			break;
		}

		mess  = errorTitle;
		mess += EVE_TXT(" spec. info: ");
		mess += errorString;

		EVE_LOG_ERROR("OpenCL Error: %s in function %s in file %s at line %d.", mess.c_str(), p_pFunction, p_pFile, p_line);
		EVE_ASSERT_FAILURE;
	}
}



//=================================================================================================
void eve::ocl::check_error_context(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError)
{
	if (p_clError != CL_SUCCESS)
	{
		std::wstring mess;
		std::wstring errorString;
		std::wstring errorTitle;

		switch (p_clError)
		{
		case  CL_INVALID_PLATFORM:
			errorTitle   = EVE_TXT("CL_INVALID_PLATFORM");
			errorString  = EVE_TXT("clCreateContext: properties is NULL and no platform could be selected or platform value specified in properties is not a valid platform. \n");
			errorString += EVE_TXT("clCreateContextFromType: properties is NULL and no platform could be selected or platform value specified in properties is not a valid platform.");
			break;

		case  CL_INVALID_VALUE:
			errorTitle   = EVE_TXT("CL_INVALID_VALUE");
			errorString  = EVE_TXT("clCreateContext: context property name in properties is not a supported property name or devices is NULL or num_devices is equal to zero or pfn_notify is NULL but user_data is not NULL. \n");
			errorString += EVE_TXT("clCreateContextFromType: context property name in properties is not a supported property name, or pfn_notify is NULL but user_data is not NULL. \n");
			errorString += EVE_TXT("clGetContextInfo: param_name is not one of the supported values or size in bytes specified by param_value_size is less than size of return type and param_value is not a NULL value.");
			break;

		case  CL_INVALID_DEVICE:
			errorTitle  = EVE_TXT("CL_INVALID_DEVICE");
			errorString = EVE_TXT("clCreateContext: devices contains an invalid device or are not associated with the specified platform.");
			break;

		case  CL_DEVICE_NOT_AVAILABLE:
			errorTitle  = EVE_TXT("CL_DEVICE_NOT_AVAILABLE");
			errorString = EVE_TXT("clCreateContext: a device in devices is currently not available even though the device was returned by clGetDeviceIDs. \n");
			errorString = EVE_TXT("clCreateContextFromType: no devices that match device_type are currently available.");
			break;

		case CL_DEVICE_NOT_FOUND:
			errorTitle  = EVE_TXT("CL_DEVICE_NOT_FOUND");
			errorString = EVE_TXT("clCreateContextFromType: no devices that match device_type were found.");
			break;

		case CL_INVALID_DEVICE_TYPE:
			errorTitle  = EVE_TXT("CL_INVALID_DEVICE_TYPE");
			errorString = EVE_TXT("clCreateContextFromType: device_type is not a valid value.");
			break;

		case  CL_OUT_OF_HOST_MEMORY:
			errorTitle   = EVE_TXT("CL_OUT_OF_HOST_MEMORY");
			errorString  = EVE_TXT("clCreateContext: there is a failure to allocate resources required by the OpenCL implementation on the host. \n");
			errorString += EVE_TXT("clCreateContextFromType: there is a failure to allocate resources required by the OpenCL implementation on the host.");
			break;

		case CL_INVALID_CONTEXT:
			errorTitle   = EVE_TXT("CL_INVALID_CONTEXT");
			errorString  = EVE_TXT("clRetainContext: context is not a valid OpenCL context. \n");
			errorString += EVE_TXT("clReleaseContext: context is not a valid OpenCL context. \n");
			errorString += EVE_TXT("clGetContextInfo: context is not a valid OpenCL context.");
			break;
		}

		mess  = errorTitle;
		mess += EVE_TXT(" spec. info: ");
		mess += errorString;

		EVE_LOG_ERROR("OpenCL Error: %s in function %s in file %s at line %d.", mess.c_str(), p_pFunction, p_pFile, p_line);
		EVE_ASSERT_FAILURE;
	}
}



//=================================================================================================
void eve::ocl::check_error_command_qeue(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError)
{
	if (p_clError != CL_SUCCESS)
	{
		std::wstring mess;
		std::wstring errorString;
		std::wstring errorTitle;

		switch (p_clError)
		{
		case  CL_INVALID_CONTEXT:
			errorTitle  = EVE_TXT("CL_INVALID_CONTEXT");
			errorString = EVE_TXT("clCreateCommandQueue : context is not a valid context.");
			break;

		case CL_INVALID_DEVICE:
			errorTitle  = EVE_TXT("CL_INVALID_DEVICE");
			errorString = EVE_TXT("clCreateCommandQueue: device is not a valid device or is not associated with context.");
			break;

		case CL_INVALID_VALUE:
			errorTitle   = EVE_TXT("CL_INVALID_VALUE");
			errorString  = EVE_TXT("clCreateCommandQueue: values specified in properties are not valid. \n");
			errorString += EVE_TXT("clGetCommandQueueInfo: param_name is not one of the supported values or size in bytes specified by param_value_size is less than size of return type and param_value is not a NULL value. \n");
			errorString += EVE_TXT("clSetCommandQueueProperty: values specified in properties are not valid.");
			break;

		case CL_INVALID_COMMAND_QUEUE:
			errorTitle   = EVE_TXT("CL_INVALID_COMMAND_QUEUE");
			errorString  = EVE_TXT("clGetCommandQueueInfo: command_queue is not a valid command-queue. \n");
			errorString += EVE_TXT("clReleaseCommandQueue: command_queue is not a valid command-queue. \n");
			errorString += EVE_TXT("clRetainCommandQueue: command_queue is not a valid command-queue. \n");
			errorString += EVE_TXT("clSetCommandQueueProperty: command_queue is not a valid command-queue.");
			break;

		case CL_INVALID_QUEUE_PROPERTIES:
			errorTitle   = EVE_TXT("CL_INVALID_QUEUE_PROPERTIES");
			errorString  = EVE_TXT("clCreateCommandQueue: values specified in properties are valid but are not supported by the device. \n");
			errorString += EVE_TXT("clSetCommandQueueProperty: values specified in properties are valid but are not supported by the device.");
			break;

		case CL_OUT_OF_HOST_MEMORY:
			errorTitle  = EVE_TXT("CL_OUT_OF_HOST_MEMORY");
			errorString = EVE_TXT("clCreateCommandQueue: there is a failure to allocate resources required by the OpenCL implementation on the host.");
			break;
		}

		mess  = errorTitle;
		mess += EVE_TXT(" spec. info: ");
		mess += errorString;

		EVE_LOG_ERROR("OpenCL Error: %s in function %s in file %s at line %d.", mess.c_str(), p_pFunction, p_pFile, p_line);
		EVE_ASSERT_FAILURE;
	}
}



//=================================================================================================
void eve::ocl::check_error_program(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError)
{
	if (p_clError != CL_SUCCESS)
	{
		std::wstring mess;
		std::wstring errorString;
		std::wstring errorTitle;

		switch (p_clError)
		{
		case  CL_INVALID_CONTEXT:
			errorTitle   = EVE_TXT("CL_INVALID_CONTEXT");
			errorString  = EVE_TXT("clCreateProgramWithSource: context is not a valid context. \n");
			errorString += EVE_TXT("clCreateProgramWithBinary: context is not a valid context.");
			break;

		case  CL_INVALID_VALUE:
			errorTitle   = EVE_TXT("CL_INVALID_VALUE");
			errorString  = EVE_TXT("clCreateProgramWithSource: count is zero or strings or any entry in strings is NULL. \n");
			errorString += EVE_TXT("clCreateProgramWithBinary: device_list is NULL or num_devices is zero or lengths or binaries are NULL or any entry in lengths[i] or binaries[i] is NULL.");
			break;

		case CL_INVALID_DEVICE:
			errorTitle  = EVE_TXT("CL_INVALID_DEVICE");
			errorString = EVE_TXT("clCreateProgramWithBinary: OpenCL devices listed in device_list are not in the list of devices associated with context.");
			break;

		case CL_INVALID_BINARY:
			errorTitle  = EVE_TXT("CL_INVALID_BINARY");
			errorString = EVE_TXT("clCreateProgramWithBinary: an invalid program binary was encountered for any device. binary_status will return specific status for each device.");
			break;

		case CL_INVALID_PROGRAM:
			errorTitle   = EVE_TXT("CL_INVALID_PROGRAM");
			errorString  = EVE_TXT("clReleaseProgram: program is not a valid program. \n");
			errorString += EVE_TXT("clRetainProgram: program is not a valid program.");
			break;

		case  CL_OUT_OF_HOST_MEMORY:
			errorTitle   = EVE_TXT("CL_OUT_OF_HOST_MEMORY");
			errorString  = EVE_TXT("clCreateProgramWithSource: there is a failure to allocate resources required by the OpenCL implementation on the host. \n");
			errorString += EVE_TXT("clCreateProgramWithBinary: there is a failure to allocate resources required by the OpenCL implementation on the host.");
			break;
		}

		mess  = errorTitle;
		mess += EVE_TXT(" spec. info: ");
		mess += errorString;

		EVE_LOG_ERROR("OpenCL Error: %s in function %s in file %s at line %d.", mess.c_str(), p_pFunction, p_pFile, p_line);
		EVE_ASSERT_FAILURE;
	}
}



//=================================================================================================
void eve::ocl::check_error_kernel(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, cl_int p_clError)
{
	if (p_clError != CL_SUCCESS)
	{
		std::wstring mess;
		std::wstring errorString;
		std::wstring errorTitle;

		switch (p_clError)
		{
		case  CL_INVALID_PROGRAM:
			errorTitle   = EVE_TXT("CL_INVALID_PROGRAM");
			errorString  = EVE_TXT("clCreateKernel: program is not a valid program object. \n");
			errorString += EVE_TXT("clCreateKernelsInProgram: program is not a valid program object.");
			break;

		case  CL_INVALID_PROGRAM_EXECUTABLE:
			errorTitle   = EVE_TXT("CL_INVALID_PROGRAM_EXECUTABLE");
			errorString  = EVE_TXT("clCreateKernel: there is no successfully built executable for program. \n");
			errorString += EVE_TXT("clCreateKernelsInProgram: there is no successfully built executable for program.");
			break;

		case  CL_INVALID_KERNEL_NAME:
			errorTitle  = EVE_TXT("CL_INVALID_KERNEL_NAME");
			errorString = EVE_TXT("clCreateKernel: kernel_name is not found in program.");
			break;

		case  CL_INVALID_KERNEL_DEFINITION:
			errorTitle  = EVE_TXT("CL_INVALID_KERNEL_DEFINITION");
			errorString = EVE_TXT("clCreateKernel: the function definition for __kernel function given by kernel_name such as the number of arguments, the argument types are not the same for all devices for which the program executable has been built.");
			break;

		case  CL_INVALID_VALUE:
			errorTitle   = EVE_TXT("CL_INVALID_VALUE");
			errorString  = EVE_TXT("clCreateKernel: kernel_name is NULL. \n");
			errorString += EVE_TXT("clCreateKernelsInProgram: kernels is not NULL and num_kernels is less than the number of kernels in program. \n");
			errorString += EVE_TXT("clGetKernelInfo: param_name is not valid, or size in bytes specified by param_value_size is less than the size of return type and param_value is not NULL. \n");
			errorString += EVE_TXT("clGetKernelWorkGroupInfo: param_name is not valid, or size in bytes specified by param_value_size is less than the size of return type and param_value is not NULL.");
			break;

		case CL_INVALID_KERNEL:
			errorTitle   = EVE_TXT("CL_INVALID_KERNEL");
			errorString  = EVE_TXT("clRetainKernel: kernel is not a valid kernel object. \n");
			errorString += EVE_TXT("clReleaseKernel: kernel is not a valid kernel object. \n");
			errorString += EVE_TXT("clSetKernelArg: kernel is not a valid kernel object. \n");
			errorString += EVE_TXT("clGetKernelInfo: kernel is not a valid kernel object. \n");
			errorString += EVE_TXT("clGetKernelWorkGroupInfo: kernel is not a valid kernel object.");
			break;

		case CL_INVALID_DEVICE:
			errorTitle  = EVE_TXT("CL_INVALID_DEVICE");
			errorString = EVE_TXT("clGetKernelWorkGroupInfo: device is not in the list of devices associated with kernel or device is NULL but there is more than one device associated with kernel.");
			break;

		case CL_INVALID_ARG_INDEX:
			errorTitle  = EVE_TXT("CL_INVALID_ARG_INDEX");
			errorString = EVE_TXT("clSetKernelArg: arg_index is not a valid argument index.");
			break;

		case CL_INVALID_ARG_VALUE:
			errorTitle  = EVE_TXT("CL_INVALID_ARG_VALUE");
			errorString = EVE_TXT("clSetKernelArg: arg_value specified is NULL for an argument that is not declared with the __local qualifier or vice-versa.");
			break;

		case CL_INVALID_MEM_OBJECT:
			errorTitle  = EVE_TXT("CL_INVALID_MEM_OBJECT");
			errorString = EVE_TXT("clSetKernelArg: for an argument declared to be a memory object when the specified arg_value is not a valid memory object.");
			break;

		case CL_INVALID_SAMPLER:
			errorTitle  = EVE_TXT("CL_INVALID_SAMPLER");
			errorString = EVE_TXT("clSetKernelArg: for an argument declared to be of type sampler_t when the specified arg_value is not a valid sampler object.");
			break;

		case CL_INVALID_ARG_SIZE:
			errorTitle  = EVE_TXT("CL_INVALID_ARG_SIZE");
			errorString = EVE_TXT("clSetKernelArg: arg_size does not match the size of the data type for an argument that is not a memory object or the argument is a memory object and arg_size != sizeof(cl_mem) or arg_size is zero and the argument is declared with the __local qualifier or the argument is a sampler and arg_size != sizeof(cl_sampler).");
			break;

		case  CL_OUT_OF_HOST_MEMORY:
			errorTitle   = EVE_TXT("CL_OUT_OF_HOST_MEMORY");
			errorString  = EVE_TXT("clCreateKernel: there is a failure to allocate resources required by the OpenCL implementation on the host. \n");
			errorString += EVE_TXT("clCreateKernelsInProgram: there is a failure to allocate resources required by the OpenCL implementation on the host.");
			break;
		}

		mess  = errorTitle;
		mess += EVE_TXT(" spec. info: ");
		mess += errorString;

		EVE_LOG_ERROR("OpenCL Error: %s in function %s in file %s at line %d.", mess.c_str(), p_pFunction, p_pFile, p_line);
		EVE_ASSERT_FAILURE;
	}
}

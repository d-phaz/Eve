
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
#include "eve/sys/win32/Info.h"


#ifndef __EVE_MESSAGING_ERROR_H__
#include "eve/mess/Error.h"
#endif

#ifndef __EVE_MESSAGING_SERVER_H__
#include "eve/mess/Server.h"
#endif


//=================================================================================================
bool eve::sys::app_is_x86(void)
{
	static bool ret = false;

	static bool checked = false;
	if (!checked)
	{
		BOOL bIsWow64 = FALSE;
		if (!::IsWow64Process(::GetCurrentProcess(), &bIsWow64))
		{
			EVE_LOG_ERROR("Unable to retrieve application x86 state, error: %s.", eve::mess::get_error_msg() );
		}

		ret = (bIsWow64 == TRUE);
	}

	return ret;
}

//=================================================================================================
bool eve::sys::app_is_x64(void)
{
	return (!eve::sys::app_is_x86());
}



//=================================================================================================
eve::sys::ProcArch eve::sys::get_processor_arch(void)
{
	static eve::sys::ProcArch arch = proc_ArchUnknown;
	if (arch = proc_ArchUnknown)
	{
		SYSTEM_INFO sysinfo;
		if (eve::sys::app_is_x86()) {
			::GetNativeSystemInfo(&sysinfo);
		}
		else {
			::GetSystemInfo(&sysinfo);
		}

		switch (sysinfo.wProcessorArchitecture)
		{
		case PROCESSOR_ARCHITECTURE_AMD64:	arch = proc_ArchX64;			break;
		case PROCESSOR_ARCHITECTURE_INTEL:	arch = proc_ArchX86;			break;
		case PROCESSOR_ARCHITECTURE_ARM:	arch = proc_ArchARM;			break;
		case PROCESSOR_ARCHITECTURE_IA64:	arch = proc_ArchIntelItanium;	break;

		case PROCESSOR_ARCHITECTURE_UNKNOWN: 
		default:	
			EVE_LOG_ERROR("Unable to retrieve the processor architecture of the installed operating system.");
			arch = proc_ArchUnknown;		
			break;
		}
	}
	return arch;
}

//=================================================================================================
uint32_t eve::sys::get_logical_processor_num(void)
{
	static uint32_t num = 0;
	if (num == 0)
	{
		SYSTEM_INFO sysinfo;
		if (eve::sys::app_is_x86()) {
			::GetNativeSystemInfo(&sysinfo);
		}
		else {
			::GetSystemInfo(&sysinfo);
		}

		num = sysinfo.dwNumberOfProcessors;
		if (num == 0)
		{
			EVE_LOG_ERROR("Unable to retrieve the number of logical processors in the current group");
		}
	}
	return num;
}



//=================================================================================================
uint32_t eve::sys::get_page_size(void)
{
	static uint32_t pageSize = 0;
	if (pageSize == 0)
	{
		SYSTEM_INFO sysinfo;
		if (eve::sys::app_is_x86()) {
			::GetNativeSystemInfo(&sysinfo);
		}
		else {
			::GetSystemInfo(&sysinfo);
		}

		pageSize = sysinfo.dwPageSize;
		if (pageSize == 0)
		{
			EVE_LOG_ERROR("Unable to retrieve page size (used by aligned allocations).");
		}
	}
	return pageSize;
}
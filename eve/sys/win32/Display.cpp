
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
#include "eve/sys/win32/Display.h"

//=================================================================================================
int32_t eve::sys::get_main_monitor_width(void)		{ return ::GetSystemMetrics(SM_CXFULLSCREEN); }
int32_t eve::sys::get_main_monitor_height(void)		{ return ::GetSystemMetrics(SM_CYFULLSCREEN); }

//=================================================================================================
int32_t eve::sys::get_main_display_width(void)		{ return ::GetSystemMetrics(SM_CXSCREEN); }
int32_t eve::sys::get_main_display_height(void)		{ return ::GetSystemMetrics(SM_CYSCREEN); }



//=================================================================================================
uint32_t eve::sys::get_work_area_width(void)
{
	RECT rect;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

	return static_cast<uint32_t>(rect.right - rect.left);
}

//=================================================================================================
uint32_t eve::sys::get_work_area_height(void)
{
	RECT rect;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

	return static_cast<uint32_t>(rect.bottom - rect.top);
}

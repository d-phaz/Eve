
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
#include "eve/sys/win32/Notification.h"


//=================================================================================================
bool eve::sys::notify_prompt_user(const std::wstring & p_title, const std::wstring & p_text)
{
	int32_t ret = ::MessageBoxW(::GetForegroundWindow(), p_text.c_str(), p_title.c_str(), MB_OKCANCEL | MB_ICONQUESTION);

#ifndef NDEBUG
	if (ret == 0) {
		EVE_LOG_ERROR("Unable to create user prompt Message Box, error: %s", eve::mess::get_error_msg());
	}
#endif

	return (ret == IDOK);
}

//=================================================================================================
bool eve::sys::notify_warning(const std::wstring & p_title, const std::wstring & p_text)
{
	int32_t ret = ::MessageBoxW(::GetForegroundWindow(), p_text.c_str(), p_title.c_str(), MB_OK | MB_ICONWARNING);

#ifndef NDEBUG
	if (ret == 0) {
		EVE_LOG_ERROR("Unable to create user prompt Message Box, error: %s", eve::mess::get_error_msg());
	}
#endif

	return (ret == IDOK);
}

//=================================================================================================
bool eve::sys::notify_error(const std::wstring & p_title, const std::wstring & p_text)
{
	int32_t ret = ::MessageBoxW(::GetForegroundWindow(), p_text.c_str(), p_title.c_str(), MB_OK | MB_ICONERROR);

#ifndef NDEBUG
	if (ret == 0) {
		EVE_LOG_ERROR("Unable to create user prompt Message Box, error: %s", eve::mess::get_error_msg());
	}
#endif

	return (ret == IDOK);
}

//=================================================================================================
void eve::sys::notify_fatal_error(const std::wstring & p_text)
{
	::FatalAppExitW(-1, p_text.c_str());
}

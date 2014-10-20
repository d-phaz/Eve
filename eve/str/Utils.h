
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
#ifndef __EVE_STRING_UTILS_H__
#define __EVE_STRING_UTILS_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif


namespace eve
{
	namespace str
	{
		/** \brief Convert Unicode wchar_t to non-Unicode standard string. */
		std::string to_string(const wchar_t * p_txt);
		/** \brief Convert Unicode std::wstring to non-Unicode standard string. */
		std::string to_string(const std::wstring & p_txt);


		/** \brief Convert non-Unicode char to Unicode standard wstring. */
		std::wstring to_wstring(const char * p_txt);
		/** \brief Convert non-Unicode std::string to Unicode standard wstring. */
		std::wstring to_wstring(const std::string & p_txt);


		/** \brief Convert numerical value to std::string. */
		template<typename T>
		std::string num_to_string(T p_value)
		{
			std::ostringstream ost;
			ost << p_value;

			return ost.str();
		}
		/** \brief Convert numerical value to std::wstring. */
		template<typename T>
		std::wstring num_to_wstring(T p_value)
		{
			std::wostringstream ost;
			ost << p_value;

			return ost.str();
		}

	} // namespace str

} // namespace eve

#endif // __EVE_TIME_UTILS_H__

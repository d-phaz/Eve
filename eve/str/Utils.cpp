
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
#include "eve/str/Utils.h"


//=================================================================================================
std::string eve::str::to_string(const wchar_t * p_txt)
{
	const size_t size = wcslen(p_txt) + 1;
	char * ch = new char[size];
	wcstombs(ch, p_txt, size);

	std::string ret(ch);
	delete[] ch;

	return ret;
}

//=================================================================================================
std::string eve::str::to_string(const std::wstring & p_txt)
{
	return eve::str::to_string(p_txt.c_str());
}



//=================================================================================================
std::wstring eve::str::to_wstring(const char * p_txt)
{
	const size_t size = strlen(p_txt) + 1;
	wchar_t * ch = new wchar_t[size];
	mbstowcs(ch, p_txt, size);

	std::wstring ret(ch);
	delete[] ch;

	return ret;
}

//=================================================================================================
std::wstring eve::str::to_wstring(const std::string & p_txt)
{
	return eve::str::to_wstring(p_txt.c_str());
}

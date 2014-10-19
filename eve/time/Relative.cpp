
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
#include "eve/time/Relative.h"


//=================================================================================================
const double eve::time::Relative::m_mult_minute = 1.0 / 60.0;
const double eve::time::Relative::m_mult_hours	= 1.0 / (60.0 * 60.0);
const double eve::time::Relative::m_mult_days	= 1.0 / (60.0 * 60.0 * 24.0);
const double eve::time::Relative::m_mult_weeks	= 1.0 / (60.0 * 60.0 * 24.0 * 7.0);



//=================================================================================================
eve::time::Relative::Relative(double p_seconds) throw()
	: m_seconds(p_seconds) 
{}

//=================================================================================================
eve::time::Relative::Relative(const eve::time::Relative & p_other) throw()
	: m_seconds(p_other.m_seconds) 
{}

//=================================================================================================
eve::time::Relative::~Relative(void) throw()
{}



//=================================================================================================
eve::time::Relative & eve::time::Relative::operator = (const eve::time::Relative & p_other) throw()
{ 
	m_seconds = p_other.m_seconds;
	return *this; 
}



//=================================================================================================
eve::time::Relative eve::time::Relative::create_from_milliseconds	(const int32_t p_milliseconds)	throw() { return eve::time::Relative(p_milliseconds * 0.001);				}
eve::time::Relative eve::time::Relative::create_from_milliseconds	(const int64_t p_milliseconds)	throw() { return eve::time::Relative(p_milliseconds * 0.001);				}
eve::time::Relative eve::time::Relative::create_from_seconds		(double p_seconds)				throw() { return eve::time::Relative(p_seconds);							}
eve::time::Relative eve::time::Relative::create_from_minutes		(const double p_minutes)		throw() { return eve::time::Relative(p_minutes * 60.0);						}
eve::time::Relative eve::time::Relative::create_from_hours			(const double p_hours)			throw() { return eve::time::Relative(p_hours * (60.0 * 60.0));				}
eve::time::Relative eve::time::Relative::create_from_days			(const double p_days)			throw() { return eve::time::Relative(p_days  * (60.0 * 60.0 * 24.0));		}
eve::time::Relative eve::time::Relative::create_from_weeks			(const double p_weeks)			throw() { return eve::time::Relative(p_weeks * (60.0 * 60.0 * 24.0 * 7.0)); }



//=================================================================================================
eve::time::Relative eve::time::Relative::operator += (const eve::time::Relative & p_time) throw() { m_seconds += p_time.m_seconds; return *this; }
eve::time::Relative eve::time::Relative::operator -= (const eve::time::Relative & p_time) throw() { m_seconds -= p_time.m_seconds; return *this; }
eve::time::Relative eve::time::Relative::operator *= (const eve::time::Relative & p_time) throw() { m_seconds *= p_time.m_seconds; return *this; }
eve::time::Relative eve::time::Relative::operator /= (const eve::time::Relative & p_time) throw() { m_seconds /= p_time.m_seconds; return *this; }

//=================================================================================================
eve::time::Relative eve::time::Relative::operator += (const double p_seconds) throw() {	m_seconds += p_seconds; return *this; }
eve::time::Relative eve::time::Relative::operator -= (const double p_seconds) throw() { m_seconds -= p_seconds; return *this; }
eve::time::Relative eve::time::Relative::operator *= (const double p_seconds) throw() { m_seconds *= p_seconds; return *this; }
eve::time::Relative eve::time::Relative::operator /= (const double p_seconds) throw() { m_seconds /= p_seconds; return *this; }



//=================================================================================================
static inline void translate_time_field(std::wstring & p_result, int32_t p_n, const wchar_t * p_singular, const wchar_t * p_plural)
{
	p_result += std::to_wstring(p_n);
	p_result += (p_n == 1 ? p_singular : p_plural);
}

//=================================================================================================
std::wstring eve::time::Relative::formatted(const std::wstring & p_retZero) const
{
	if (m_seconds < 0.001 && m_seconds > -0.001)
		return p_retZero;

	std::wstring result;

	if (m_seconds < 0) {
		result += EVE_TXT("-");
	}

	int32_t fieldsShown = 0;
	int32_t n = std::abs(static_cast<int32_t>(getWeeks()));
	if (n > 0)
	{
		translate_time_field(result, n, EVE_TXT("week"), EVE_TXT("weeks"));
		++fieldsShown;
	}

	n = std::abs(static_cast<int32_t>(getDays())) % 7;
	if (n > 0)
	{
		translate_time_field(result, n, EVE_TXT("day"), EVE_TXT("days"));
		++fieldsShown;
	}

	if (fieldsShown < 2)
	{
		n = std::abs(static_cast<int32_t>(getHours())) % 24;
		if (n > 0)
		{
			translate_time_field(result, n, EVE_TXT("hr"), EVE_TXT("hrs"));
			++fieldsShown;
		}

		if (fieldsShown < 2)
		{
			n = std::abs(static_cast<int32_t>(getMinutes())) % 60;
			if (n > 0)
			{
				translate_time_field(result, n, EVE_TXT("min"), EVE_TXT("mins"));
				++fieldsShown;
			}

			if (fieldsShown < 2)
			{
				n = std::abs(static_cast<int32_t>(getSeconds())) % 60;
				if (n > 0)
				{
					translate_time_field(result, n, EVE_TXT("sec"), EVE_TXT("secs"));
					++fieldsShown;
				}

				if (fieldsShown == 0)
				{
					n = std::abs(static_cast<int32_t>(getMilliseconds())) % 1000;
					if (n > 0)
						translate_time_field(result, n, EVE_TXT("ms"), EVE_TXT("ms"));
				}
			}
		}
	}

	return result;
}


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

// main header
#include "eve/time/Absolute.h"

#ifndef __EVE_TIME_UTILS_H__
#include "eve/time/Utils.h"
#endif

#ifndef __EVE_STRING_UTILS_H__
#include "eve/str/Utils.h"
#endif


//=================================================================================================
eve::time::Absolute::Absolute(void) throw()
	: m_milliSinceEpoch(0)
{}

//=================================================================================================
eve::time::Absolute::Absolute(const int64_t p_milliseconds) throw()
	: m_milliSinceEpoch(p_milliseconds)
{}

//=================================================================================================
eve::time::Absolute::Absolute(const int32_t year,
							  const int32_t month,
							  const int32_t day,
							  const int32_t hours,
							  const int32_t minutes,
							  const int32_t seconds,
							  const int32_t milliseconds,
							  const bool useLocalTime) throw()
{
	EVE_ASSERT(year > 100); // year must be a 4-digit version

	if (year < 1971 || year >= 2038 || !useLocalTime)
	{
		// use extended maths for dates beyond 1970 to 2037..
		const int32_t timeZoneAdjustment = useLocalTime ? (31536000 - (int32_t)(eve::time::Absolute(1971, 0, 1, 0, 0).getMilliseconds() / 1000)) : 0;
		const int32_t a		= (13 - month) / 12;
		const int32_t y		= year + 4800 - a;
		const int32_t jd	= day + (153 * (month + 12 * a - 2) + 2) / 5 + (y * 365) + (y / 4) - (y / 100) + (y / 400) - 32045;
		const int64_t s		= ((int64_t)jd) * 86400LL - 210866803200LL;

		m_milliSinceEpoch = 1000 * (s + (hours * 3600 + minutes * 60 + seconds - timeZoneAdjustment)) + milliseconds;
	}
	else
	{
		struct tm t;
		t.tm_year	= year - 1900;
		t.tm_mon	= month;
		t.tm_mday	= day;
		t.tm_hour	= hours;
		t.tm_min	= minutes;
		t.tm_sec	= seconds;
		t.tm_isdst	= -1;

		m_milliSinceEpoch = 1000 * (int64_t)mktime(&t);

		if (m_milliSinceEpoch < 0)
			m_milliSinceEpoch = 0;
		else
			m_milliSinceEpoch += milliseconds;
	}
}

//=================================================================================================
eve::time::Absolute::Absolute(const eve::time::Absolute& p_other) throw()
	: m_milliSinceEpoch(p_other.m_milliSinceEpoch)
{}

//=================================================================================================
eve::time::Absolute::~Absolute(void) throw()
{}



//=================================================================================================
eve::time::Absolute & eve::time::Absolute::operator = (const eve::time::Absolute & p_other) throw()
{
	m_milliSinceEpoch = p_other.m_milliSinceEpoch;
	return *this;
}



//=================================================================================================
eve::time::Absolute eve::time::Absolute::create_from_current_time	(void)				throw() { return eve::time::Absolute(eve::time::current_time_milli());				}
eve::time::Absolute eve::time::Absolute::create_from_seconds		(float p_seconds)	throw() { return eve::time::Absolute(static_cast<int64_t>(p_seconds * 1000));		}
eve::time::Absolute eve::time::Absolute::create_from_milliseconds	(int32_t p_milli)	throw()	{ return eve::time::Absolute(static_cast<int64_t>(p_milli));				}
eve::time::Absolute eve::time::Absolute::create_from_milliseconds	(int64_t p_milli)	throw()	{ return eve::time::Absolute(p_milli);										}
eve::time::Absolute eve::time::Absolute::create_from_microseconds	(int64_t p_micro)	throw() { return eve::time::Absolute(p_micro / 1000);								}



//=================================================================================================
eve::time::Absolute & eve::time::Absolute::operator += (const eve::time::Absolute & p_delta) throw() { m_milliSinceEpoch += p_delta.m_milliSinceEpoch; return *this; }
eve::time::Absolute & eve::time::Absolute::operator -= (const eve::time::Absolute & p_delta) throw() { m_milliSinceEpoch -= p_delta.m_milliSinceEpoch; return *this; }
eve::time::Absolute & eve::time::Absolute::operator *= (const eve::time::Absolute & p_delta) throw() { m_milliSinceEpoch *= p_delta.m_milliSinceEpoch; return *this; }
eve::time::Absolute & eve::time::Absolute::operator /= (const eve::time::Absolute & p_delta) throw() { m_milliSinceEpoch /= p_delta.m_milliSinceEpoch; return *this; }

//=================================================================================================
eve::time::Absolute & eve::time::Absolute::operator += (const eve::time::Relative & p_delta) throw() { m_milliSinceEpoch += p_delta.getMilliseconds(); return *this; }
eve::time::Absolute & eve::time::Absolute::operator -= (const eve::time::Relative & p_delta) throw() { m_milliSinceEpoch -= p_delta.getMilliseconds(); return *this; }
eve::time::Absolute & eve::time::Absolute::operator *= (const eve::time::Relative & p_delta) throw() { m_milliSinceEpoch *= p_delta.getMilliseconds(); return *this; }
eve::time::Absolute & eve::time::Absolute::operator /= (const eve::time::Relative & p_delta) throw() { m_milliSinceEpoch /= p_delta.getMilliseconds(); return *this; }

//=================================================================================================
eve::time::Absolute & eve::time::Absolute::operator += (int64_t p_milliseconds) throw() { m_milliSinceEpoch += p_milliseconds; return *this; }
eve::time::Absolute & eve::time::Absolute::operator -= (int64_t p_milliseconds) throw() { m_milliSinceEpoch -= p_milliseconds; return *this; }
eve::time::Absolute & eve::time::Absolute::operator *= (int64_t p_milliseconds) throw() { m_milliSinceEpoch *= p_milliseconds; return *this; }
eve::time::Absolute & eve::time::Absolute::operator /= (int64_t p_milliseconds) throw() { m_milliSinceEpoch /= p_milliseconds; return *this; }



//=================================================================================================
int32_t eve::time::Absolute::extended_modulo(const int64_t p_value, const int32_t p_modulo) throw()
{
	return static_cast<int32_t>(p_value >= 0 ? (p_value % p_modulo) : (p_value - ((p_value / p_modulo) + 1) * p_modulo));
}




//==============================================================================
std::wstring eve::time::Absolute::formatted(const std::wstring& format) const
{
	struct tm t(eve::time::millis_to_local(m_milliSinceEpoch));
	return eve::time::formatted(format, &t);
}

//==============================================================================
std::wstring eve::time::Absolute::toString(bool includeDate, bool includeTime, bool includeSeconds, bool use24HourClock) const throw()
{
	std::wstring result;

	if (includeDate)
	{
		result += eve::str::num_to_wstring(getDayOfMonth()); 
		result += ' ';
		result += getMonthName(true);
		result += ' ';
		result += eve::str::num_to_wstring(getYear());
	}

	if (includeTime)
	{
		result += ' ';

		const int32_t mins = getMinutes();

		result += eve::str::num_to_wstring((use24HourClock ? getHours() : getHoursInAmPmFormat()));
		result += (mins < 10 ? EVE_TXT(":0") : EVE_TXT(":"));
		result += eve::str::num_to_wstring(mins);

		if (includeSeconds)
		{
			const int32_t secs = getSeconds();
			result += (secs < 10 ? EVE_TXT(":0") : EVE_TXT(":"));
			result += eve::str::num_to_wstring(secs);
		}

		if (!use24HourClock)
		{
			result += (isAfternoon() ? EVE_TXT("pm") : EVE_TXT("am"));
		}
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
//////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
int32_t eve::time::Absolute::getYear(void) const throw()          { return eve::time::millis_to_local(m_milliSinceEpoch).tm_year + 1900;	}
int32_t eve::time::Absolute::getMonth(void) const throw()         { return eve::time::millis_to_local(m_milliSinceEpoch).tm_mon;			}
int32_t eve::time::Absolute::getDayOfYear(void) const throw()     { return eve::time::millis_to_local(m_milliSinceEpoch).tm_yday;			}
int32_t eve::time::Absolute::getDayOfMonth(void) const throw()    { return eve::time::millis_to_local(m_milliSinceEpoch).tm_mday;			}
int32_t eve::time::Absolute::getDayOfWeek(void) const throw()     { return eve::time::millis_to_local(m_milliSinceEpoch).tm_wday;			}
int32_t eve::time::Absolute::getHours(void) const throw()         { return eve::time::millis_to_local(m_milliSinceEpoch).tm_hour;			}
int32_t eve::time::Absolute::getMinutes(void) const throw()       { return eve::time::millis_to_local(m_milliSinceEpoch).tm_min;			}
int32_t eve::time::Absolute::getSeconds(void) const throw()       { return extended_modulo(m_milliSinceEpoch / 1000, 60);					}
int32_t eve::time::Absolute::getMilliseconds(void) const throw()  { return extended_modulo(m_milliSinceEpoch, 1000);						}



//=================================================================================================
std::wstring eve::time::Absolute::getMonthName	(const bool p_threeLetterVersion) const { return eve::time::month_name(getMonth(), p_threeLetterVersion);			}
std::wstring eve::time::Absolute::getWeekdayName(const bool p_threeLetterVersion) const { return eve::time::week_day_name(getDayOfWeek(), p_threeLetterVersion);	}



//=================================================================================================
bool eve::time::Absolute::isAfternoon(void) const throw()
{
	return getHours() >= 12;
}

//=================================================================================================
int32_t eve::time::Absolute::getHoursInAmPmFormat(void) const throw()
{
	const int32_t hours = getHours();

	if (hours == 0)  return 12;
	if (hours <= 12) return hours;

	return hours - 12;
}



//=================================================================================================
bool eve::time::Absolute::isDaylightSavingTime(void) const throw()
{
	return eve::time::millis_to_local(m_milliSinceEpoch).tm_isdst != 0;
}

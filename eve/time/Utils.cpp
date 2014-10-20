
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
#include "eve/time/Utils.h"

#ifndef __EVE_TIME_ABSOLUTE_H__
#include "eve/time/Absolute.h"
#endif


//=================================================================================================
int64_t eve::time::current_time_milli(void)
{
#if defined(EVE_OS_WIN)
	struct _timeb t;
#ifdef _INC_TIME_INL
	_ftime_s(&t);
#else
	_ftime(&t);
#endif

	return static_cast<int64_t>(t.time * 1000 + t.millitm);

#else
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return static_cast<int64_t>(tv.tv_sec * 1000 + tv.tv_usec / 1000);

#endif
}



//=================================================================================================
struct tm eve::time::millis_to_local(const int64_t p_millis)
{
	struct tm res;
	const int64_t seconds = p_millis / 1000;

	if (seconds < 86400LL || seconds >= 2145916800LL)
	{
		// use extended maths for dates beyond 1970 to 2037..
		const int32_t timeZoneAdjustment = 31536000 - static_cast<int32_t>(eve::time::Absolute(1971, 0, 1, 0, 0).getValue() / 1000);
		const int64_t jdm = seconds + timeZoneAdjustment + 210866803200LL;

		const int32_t days = static_cast<int32_t>(jdm / 86400LL);
		const int32_t a = 32044 + days;
		const int32_t b = (4 * a + 3) / 146097;
		const int32_t c = a - (b * 146097) / 4;
		const int32_t d = (4 * c + 3) / 1461;
		const int32_t e = c - (d * 1461) / 4;
		const int32_t m = (5 * e + 2) / 153;

		res.tm_mday = e - (153 * m + 2) / 5 + 1;
		res.tm_mon = m + 2 - 12 * (m / 10);
		res.tm_year = b * 100 + d - 6700 + (m / 10);
		res.tm_wday = (days + 1) % 7;
		res.tm_yday = -1;

		int32_t t = static_cast<int32_t>(jdm % 86400LL);
		res.tm_hour = t / 3600;
		t %= 3600;
		res.tm_min = t / 60;
		res.tm_sec = t % 60;
		res.tm_isdst = -1;
	}
	else
	{
		time_t now = static_cast <time_t> (seconds);

#if defined(EVE_OS_WIN)
#if defined(_INC_TIME_INL)
		if (now >= 0 && now <= 0x793406fff)
			localtime_s(&res, &now);
		else
			memset(&res, 0, sizeof(tm));
#else
		result = *localtime(&now);
#endif
#else
		localtime_r(&now, &res); // thread-safe
#endif
	}

	return res;
}



//=================================================================================================
std::wstring eve::time::week_day_name(int32_t p_dayNumber, bool p_threeLetterVersion)
{
	static const std::wstring shortDayNames[] = { EVE_TXT("Sun"),		EVE_TXT("Mon"),		EVE_TXT("Tue"),		EVE_TXT("Wed"),		  EVE_TXT("Thu"),	   EVE_TXT("Fri"),    EVE_TXT("Sat")		};
	static const std::wstring longDayNames[]  = { EVE_TXT("Sunday"),	EVE_TXT("Monday"),	EVE_TXT("Tuesday"), EVE_TXT("Wednesday"), EVE_TXT("Thursday"), EVE_TXT("Friday"), EVE_TXT("Saturday")	};

	p_dayNumber %= 7;

	return (p_threeLetterVersion ? shortDayNames[p_dayNumber] : longDayNames[p_dayNumber]);
}

//=================================================================================================
std::wstring eve::time::month_name(int32_t p_monthNumber, bool p_threeLetterVersion)
{
	static const std::wstring shortMonthNames[] = { EVE_TXT("Jan"),		EVE_TXT("Feb"),		 EVE_TXT("Mar"),   EVE_TXT("Apr"),   EVE_TXT("May"), EVE_TXT("Jun"),  EVE_TXT("Jul"),  EVE_TXT("Aug"),    EVE_TXT("Sep"),		EVE_TXT("Oct"),	    EVE_TXT("Nov"),	     EVE_TXT("Dec") };
	static const std::wstring longMonthNames[]  = { EVE_TXT("January"), EVE_TXT("February"), EVE_TXT("March"), EVE_TXT("April"), EVE_TXT("May"), EVE_TXT("June"), EVE_TXT("July"), EVE_TXT("August"), EVE_TXT("September"), EVE_TXT("October"), EVE_TXT("November"), EVE_TXT("December") };

	p_monthNumber %= 12;

	return (p_threeLetterVersion ? shortMonthNames[p_monthNumber] : longMonthNames[p_monthNumber]);
}



//=================================================================================================
std::wstring eve::time::formatted(const std::wstring & p_format, const struct tm * const tm)
{
	wchar_t * buffer	= nullptr;
	size_t numChars		= 0;

	for (size_t bufferSize = 256;; bufferSize += 256)
	{
		buffer		= (wchar_t*)malloc(bufferSize * sizeof(wchar_t));
		numChars	= wcsftime(buffer, bufferSize - 1, p_format.c_str(), tm);

		if (numChars > 0)
		{
			std::wstring ret(buffer);
			free(buffer);
			return ret;
		}
	}

	return std::wstring();
}

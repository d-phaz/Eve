
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
#ifndef __EVE_TIME_UTILS_H__
#define __EVE_TIME_UTILS_H__

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
	namespace time
	{		

		/**
		* \brief Returns the number of milliseconds since midnight January 1st 1970.
		* Should be accurate to within a few milliseconds, depending on platform, hardware, etc.
		*/
		int64_t current_time_milli(void);


		/** \brief Convert milliseconds to local time. */
		struct tm millis_to_local(const int64_t p_millis);


		/** 
		* \brief Returns the name of a day of the week. This function is C strftime() compliant and use Sunday as the first day of the week.
		* \param p_dayNumber            the day, 0 to 6 (0 = Sunday, 1 = Monday, etc)
		* \param p_threeLetterVersion   if true, it'll return a 3-letter abbreviation, e.g. "Tue"; if false, it'll return the full version, e.g. "Tuesday".
		*/
		std::wstring week_day_name(int32_t p_dayNumber, bool p_threeLetterVersion);
		/** 
		* \brief Returns the name of one of the months.
		* \param p_monthNumber			the month, 0 to 11
		* \param p_threeLetterVersion	if true, it'll be a 3-letter abbreviation, e.g. "Jan"; if false it'll return the long form, e.g. "January"
		*/
		std::wstring month_name(int32_t p_monthNumber, bool p_threeLetterVersion);


		/**
		* \brief Converts tm structure (local time) to a user-defined formatted string.
		*
		* This uses the C strftime() function to format this time as a string.
		* These are the escape codes that strftime uses (other codes might work on some platforms and not others, but these are the common ones):
		*
		*	%a  is replaced by the locale's abbreviated weekday name.
		*	%A  is replaced by the locale's full weekday name.
		*	%b  is replaced by the locale's abbreviated month name.
		*	%B  is replaced by the locale's full month name.
		*	%c  is replaced by the locale's appropriate date and time representation.
		*	%d  is replaced by the day of the month as a decimal number [01,31].
		*	%H  is replaced by the hour (24-hour clock) as a decimal number [00,23].
		*	%I  is replaced by the hour (12-hour clock) as a decimal number [01,12].
		*	%j  is replaced by the day of the year as a decimal number [001,366].
		*	%m  is replaced by the month as a decimal number [01,12].
		*	%M  is replaced by the minute as a decimal number [00,59].
		*	%p  is replaced by the locale's equivalent of either a.m. or p.m.
		*	%S  is replaced by the second as a decimal number [00,61].
		*	%U  is replaced by the week number of the year (Sunday as the first day of the week) as a decimal number [00,53].
		*	%w  is replaced by the weekday as a decimal number [0,6], with 0 representing Sunday.
		*	%W  is replaced by the week number of the year (Monday as the first day of the week) as a decimal number [00,53]. All days in a new year preceding the first Monday are considered to be in week 0.
		*	%x  is replaced by the locale's appropriate date representation.
		*	%X  is replaced by the locale's appropriate time representation.
		*	%y  is replaced by the year without century as a decimal number [00,99].
		*	%Y  is replaced by the year with century as a decimal number.
		*	%Z  is replaced by the timezone name or abbreviation, or by no bytes if no timezone information exists.
		*	%%  is replaced by %.
		*/
		std::wstring formatted(const std::wstring & p_format, const struct tm * const tm);



// 		//==============================================================================
// 		// High-resolution timers..
// 
// 		/**
// 		* \brief Returns the current high-resolution counter's tick-count.
// 		* This is a similar to getMillisecondCounter(), but with a higher resolution.
// 		*/
// 		static int64_t getHighResolutionTicks(void) throw();
// 
// 		/** Returns the resolution of the high-resolution counter in ticks per second.
// 
// 		@see getHighResolutionTicks, highResolutionTicksToSeconds,
// 		secondsToHighResolutionTicks
// 		*/
// 		static int64_t getHighResolutionTicksPerSecond() throw();
// 
// 		/** Converts a number of high-resolution ticks into seconds.
// 
// 		@see getHighResolutionTicks, getHighResolutionTicksPerSecond,
// 		secondsToHighResolutionTicks
// 		*/
// 		static double highResolutionTicksToSeconds(int64_t ticks) throw();
// 
// 		/** Converts a number seconds into high-resolution ticks.
// 
// 		@see getHighResolutionTicks, getHighResolutionTicksPerSecond,
// 		highResolutionTicksToSeconds
// 		*/
// 		static	int64_t secondsToHighResolutionTicks(double seconds) throw();
// 
// 
// 		/** Returns the number of millisecs since a fixed event (usually system startup).
// 
// 		This returns a monotonically increasing value which it unaffected by changes to the
// 		system clock. It should be accurate to within a few millisecs, depending on platform,
// 		hardware, etc.
// 
// 		Being a 32-bit return value, it will of course wrap back to 0 after 2^32 seconds of
// 		uptime, so be careful to take that into account. If you need a 64-bit time, you can
// 		use currentTimeMillis() instead.
// 
// 		@see getApproximateMillisecondCounter
// 		*/
// 		static uint32_t getMillisecondCounter() throw();
// 
// 		/** Returns the number of millisecs since a fixed event (usually system startup).
// 
// 		This has the same function as getMillisecondCounter(), but returns a more accurate
// 		value, using a higher-resolution timer if one is available.
// 
// 		@see getMillisecondCounter
// 		*/
// 		static double getMillisecondCounterHiRes() throw();
// 
// 		/** Waits until the getMillisecondCounter() reaches a given value.
// 
// 		This will make the thread sleep as efficiently as it can while it's waiting.
// 		*/
// 		static void waitForMillisecondCounter(uint32_t targetTime) throw();
// 
// 		/** Less-accurate but faster version of getMillisecondCounter().
// 
// 		This will return the last value that getMillisecondCounter() returned, so doesn't
// 		need to make a system call, but is less accurate - it shouldn't be more than
// 		100ms away from the correct time, though, so is still accurate enough for a
// 		lot of purposes.
// 
// 		@see getMillisecondCounter
// 		*/
// 		static uint32_t getApproximateMillisecondCounter() throw();


	} // namespace time

} // namespace eve

#endif // __EVE_TIME_UTILS_H__

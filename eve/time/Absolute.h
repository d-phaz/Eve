
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
#ifndef __EVE_TIME_ABSOLUTE_H__
#define __EVE_TIME_ABSOLUTE_H__

#ifndef __EVE_TIME_RELATIVE_H__
#include "eve/time/Relative.h"
#endif


namespace eve
{
	namespace time
	{
		/** 
		* \class eve::time::Absolute
		*
		* \brief An absolute date and time stored at millisecond precision.
		*/
		class Absolute
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			int64_t			m_milliSinceEpoch;		//!< Milliseconds since 1st January 1970.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			/** 
			* \brief Class default constructor.
			* Creates a time of 1st January 1970, (which is represented internally as 0ms).
			* To create a time object representing the current time, use getCurrentTime().
			*/
			Absolute(void) throw();

			/**
			* \brief Class constructor.
			* Creates a time based on a number of milliseconds.
			* The internal millisecond count is set to 0 (1st January 1970). 
			* To create a time object set to the current time, use getCurrentTime().
			*
			* \param p_milliseconds the number of milliseconds since the unix 'epoch' (midnight Jan 1st 1970).
			*/
			explicit Absolute(int64_t p_milliseconds) throw();

			/**
			* \brief Class constructor.
			* Creates a time from a set of date components.
			* 
			* The timezone is assumed to be whatever the system is using as its locale.
			* 
			* \param p_year             the year, in 4-digit format, e.g. 2004
			* \param p_month            the month, in the range 0 to 11
			* \param p_day              the day of the month, in the range 1 to 31
			* \param p_hours            hours in 24-hour clock format, 0 to 23
			* \param p_minutes          minutes 0 to 59
			* \param p_seconds          seconds 0 to 59
			* \param p_milliseconds     milliseconds 0 to 999
			* \param p_useLocalTime     if true, encode using the current machine's local time; if false, it will always work in GMT.
			*/
			Absolute(int32_t p_year,
					 int32_t p_month,
					 int32_t p_day,
					 int32_t p_hours,
					 int32_t p_minutes,
					 int32_t p_seconds = 0,
					 int32_t p_milliseconds = 0,
					 bool	 p_useLocalTime = true) throw();

			/** \brief Copy constructor. */
			Absolute(const Absolute & p_other) throw();

			/** \brief Class destructor. */
			virtual ~Absolute(void) throw();

			/** \brief Assignation operator. */
			Absolute & operator = (const Absolute & p_other) throw();


		public:
			/** \brief Returns a eve::time::Absolute object that is set to the current system time. */
			static eve::time::Absolute create_from_current_time(void) throw();
			/** \brief Construct a time value from a number of seconds. */
			static eve::time::Absolute create_from_seconds(float p_seconds) throw();
			/** \brief Construct a time value from a number of milliseconds. */
			static eve::time::Absolute create_from_milliseconds(int32_t p_milli) throw();
			/** \brief Construct a time value from a number of milliseconds. */
			static eve::time::Absolute create_from_milliseconds(int64_t p_milli) throw();
			/* \brief Construct a time value from a number of microseconds. */
			static eve::time::Absolute create_from_microseconds(int64_t p_micro) throw();


		public:
			/** \brief Adds a eve::time::Absolute to this time. */
			Absolute & operator += (const eve::time::Absolute & p_delta) throw();
			/** \brief Subtracts a eve::time::Absolute from this time. */
			Absolute & operator -= (const eve::time::Absolute & p_delta) throw();
			/** \brief Multiply time. */
			Absolute & operator *= (const eve::time::Absolute & p_time) throw();
			/** \brief Divide time. */
			Absolute & operator /= (const eve::time::Absolute & p_time) throw();

			/** \brief Adds a eve::time::Relative to this time. */
			Absolute & operator += (const eve::time::Relative & p_delta) throw();
			/** \brief Subtracts a eve::time::Relative from this time. */
			Absolute & operator -= (const eve::time::Relative & p_delta) throw();
			/** \brief Multiply time. */
			Absolute & operator *= (const eve::time::Relative & p_time) throw();
			/** \brief Divide time. */
			Absolute & operator /= (const eve::time::Relative & p_time) throw();


			/** \brief Adds milliseconds to this time. */
			Absolute & operator += (int64_t p_milliseconds) throw();
			/** \brief Subtracts milliseconds from this time. */
			Absolute & operator -= (int64_t p_milliseconds) throw();
			/** \brief Multiply time. */
			Absolute & operator *= (int64_t p_milliseconds) throw();
			/** \brief Divide time. */
			Absolute & operator /= (int64_t p_milliseconds) throw();


		private:
			/** \brief Convenience modulo to handle negative values. */
			static int32_t extended_modulo(const int64_t p_value, const int32_t p_modulo) throw();


		public:
			/**
			* \brief Quick way of getting a string version of a date and time.
			*
			* For a more powerful way of formatting the date and time, see the formatted() method.
			*
			* \param includeDate      whether to include the date in the string
			* \param includeTime      whether to include the time in the string
			* \param includeSeconds   if the time is being included, this provides an option not to include the seconds in it
			* \param use24HourClock   if the time is being included, sets whether to use am/pm or 24 hour notation.
			*/
			std::wstring toString(bool p_includeDate, bool p_includeTime, bool p_includeSeconds = true, bool p_use24HourClock = true) const throw();

			/** 
			* \brief Converts this date/time to a string with a user-defined format.
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
			std::wstring formatted(const std::wstring & p_format) const;


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Returns the year. A 4-digit format is used, e.g. 2004. */
			int32_t getYear(void) const throw();
			/** \brief Returns the number of the month. The value returned is in the range 0 to 11. */
			int32_t getMonth(void) const throw();
			/** \brief Returns the number of the day of the year. The value returned is in the range 0 to 365. */
			int32_t getDayOfYear(void) const throw();
			/** \brief Returns the day of the month. The value returned is in the range 1 to 31. */
			int32_t getDayOfMonth(void) const throw();
			/** \brief Returns the number of the day of the week. The value returned is in the range 0 to 6 (0 = Sunday, 1 = Monday, etc). */
			int32_t getDayOfWeek(void) const throw();
			/** \brief Returns the number of hours since midnight. The value returned is in 24-hour clock format, in the range 0 to 23. */
			int32_t getHours(void) const throw();
			/** \brief Returns the number of minutes, 0 to 59. */
			int32_t getMinutes(void) const throw();
			/** \brief Returns the number of seconds, 0 to 59. */
			int32_t getSeconds(void) const throw();
			/** 
			* \brief Returns the number of milliseconds, 0 to 999.
			* This just returns the position within the current second rather than the total number since the epoch.
			* Use getValue() to get the total number since the epoch.
			*/
			int32_t getMilliseconds(void) const throw();


		public:
			/** \brief Returns the number of milliseconds this Time object represents, since midnight January 1st 1970. */
			int64_t getValue(void) const throw();


		public:
			/** 
			* \brief Returns the name of the month.
			* \param p_threeLetterVersion   if true, it'll be a 3-letter abbreviation, e.g. "Jan"; if false it'll return the long form, e.g. "January"
			*/
			std::wstring getMonthName(bool p_threeLetterVersion) const;
			/** 
			* \brief Returns the name of the weekday.
			* \param p_threeLetterVersion   if true, it'll return a 3-letter abbreviation, e.g. "Tue"; if false, it'll return the full version, e.g. "Tuesday".
			*/
			std::wstring getWeekdayName(bool p_threeLetterVersion) const;


			/** 
			* \brief Returns true if the time is in the afternoon.
			* Returns true for "PM", false for "AM".
			*/
			bool isAfternoon(void) const throw();
			/** 
			* \brief Returns the hours in 12-hour clock format.
			* This will return a value 1 to 12 - use isAfternoon() to find out whether this is in the afternoon or morning.
			*/
			int32_t getHoursInAmPmFormat(void) const throw();


			/** Returns true if the local timezone uses a daylight saving correction (summer time). */
			bool isDaylightSavingTime() const throw();

		}; // class Absolute

	} // namespace time

} // namespace eve

//=================================================================================================
inline int64_t eve::time::Absolute::getValue(void) const throw() { return m_milliSinceEpoch; }



//=================================================================================================
/** Compares two Time objects. */
inline bool operator == (const eve::time::Absolute & t1, const eve::time::Absolute & t2) throw() { return t1.getValue() == t2.getValue(); }
/** Compares two Time objects. */
inline bool operator != (const eve::time::Absolute & t1, const eve::time::Absolute & t2) throw() { return t1.getValue() != t2.getValue(); }
/** Compares two Time objects. */
inline bool operator <  (const eve::time::Absolute & t1, const eve::time::Absolute & t2) throw() { return t1.getValue() <  t2.getValue(); }
/** Compares two Time objects. */
inline bool operator <= (const eve::time::Absolute & t1, const eve::time::Absolute & t2) throw() { return t1.getValue() <= t2.getValue(); }
/** Compares two Time objects. */
inline bool operator >  (const eve::time::Absolute & t1, const eve::time::Absolute & t2) throw() { return t1.getValue() >  t2.getValue(); }
/** Compares two Time objects. */
inline bool operator >= (const eve::time::Absolute & t1, const eve::time::Absolute & t2) throw() { return t1.getValue() >= t2.getValue(); }

//=================================================================================================
/** Compares two Time objects. */
inline bool operator == (const eve::time::Absolute & t1, const eve::time::Relative & t2) throw() { return t1.getValue() == t2.getMilliseconds(); }
/** Compares two Time objects. */
inline bool operator != (const eve::time::Absolute & t1, const eve::time::Relative & t2) throw() { return t1.getValue() != t2.getMilliseconds(); }
/** Compares two Time objects. */
inline bool operator <  (const eve::time::Absolute & t1, const eve::time::Relative & t2) throw() { return t1.getValue() <  t2.getMilliseconds(); }
/** Compares two Time objects. */
inline bool operator <= (const eve::time::Absolute & t1, const eve::time::Relative & t2) throw() { return t1.getValue() <= t2.getMilliseconds(); }
/** Compares two Time objects. */
inline bool operator >  (const eve::time::Absolute & t1, const eve::time::Relative & t2) throw() { return t1.getValue() >  t2.getMilliseconds(); }
/** Compares two Time objects. */
inline bool operator >= (const eve::time::Absolute & t1, const eve::time::Relative & t2) throw() { return t1.getValue() >= t2.getMilliseconds(); }

//=================================================================================================
/** Compares two Time objects. */
inline bool operator == (const eve::time::Relative & t1, const eve::time::Absolute & t2) throw() { return t1.getMilliseconds() == t2.getValue(); }
/** Compares two Time objects. */
inline bool operator != (const eve::time::Relative & t1, const eve::time::Absolute & t2) throw() { return t1.getMilliseconds() != t2.getValue(); }
/** Compares two Time objects. */
inline bool operator <  (const eve::time::Relative & t1, const eve::time::Absolute & t2) throw() { return t1.getMilliseconds() <  t2.getValue(); }
/** Compares two Time objects. */
inline bool operator <= (const eve::time::Relative & t1, const eve::time::Absolute & t2) throw() { return t1.getMilliseconds() <= t2.getValue(); }
/** Compares two Time objects. */
inline bool operator >  (const eve::time::Relative & t1, const eve::time::Absolute & t2) throw() { return t1.getMilliseconds() > t2.getValue(); }
/** Compares two Time objects. */
inline bool operator >= (const eve::time::Relative & t1, const eve::time::Absolute & t2) throw() { return t1.getMilliseconds() >= t2.getValue(); }

//=================================================================================================
/** Compares Time object to int64_t (milliseconds). */
inline bool operator == (const eve::time::Absolute & t1, int64_t p_milliseconds) throw() { return t1.getValue() == p_milliseconds; }
/** Compares Time object to int64_t (milliseconds). */
inline bool operator != (const eve::time::Absolute & t1, int64_t p_milliseconds) throw() { return t1.getValue() != p_milliseconds; }
/** Compares Time object to int64_t (milliseconds). */
inline bool operator <  (const eve::time::Absolute & t1, int64_t p_milliseconds) throw() { return t1.getValue() <  p_milliseconds; }
/** Compares Time object to int64_t (milliseconds). */
inline bool operator <= (const eve::time::Absolute & t1, int64_t p_milliseconds) throw() { return t1.getValue() <= p_milliseconds; }
/** Compares Time object to int64_t (milliseconds). */
inline bool operator >  (const eve::time::Absolute & t1, int64_t p_milliseconds) throw() { return t1.getValue() >  p_milliseconds; }
/** Compares Time object to int64_t (milliseconds). */
inline bool operator >= (const eve::time::Absolute & t1, int64_t p_milliseconds) throw() { return t1.getValue() >= p_milliseconds; }



//=================================================================================================
/** \brief Addition of two times. */
inline eve::time::Absolute operator + (eve::time::Absolute & t1, eve::time::Absolute & t2) throw() { return t1 += t2; }
/** \brief Subtraction of two times. */
inline eve::time::Absolute operator - (eve::time::Absolute & t1, eve::time::Absolute & t2) throw() { return t1 -= t2; }
/** \brief Multiplication of two times. */
inline eve::time::Absolute operator * (eve::time::Absolute & t1, eve::time::Absolute & t2) throw() { return t1 *= t2; }
/** \brief Division of two times. */
inline eve::time::Absolute operator / (eve::time::Absolute & t1, eve::time::Absolute & t2) throw() { return t1 /= t2; }

//=================================================================================================
/** \brief Addition of two times. */
inline eve::time::Absolute operator + (eve::time::Absolute & t1, eve::time::Relative & t2) throw() { return t1 += t2; }
/** \brief Subtraction of two times. */
inline eve::time::Absolute operator - (eve::time::Absolute & t1, eve::time::Relative & t2) throw() { return t1 -= t2; }
/** \brief Multiplication of two times. */
inline eve::time::Absolute operator * (eve::time::Absolute & t1, eve::time::Relative & t2) throw() { return t1 *= t2; }
/** \brief Division of two times. */
inline eve::time::Absolute operator / (eve::time::Absolute & t1, eve::time::Relative & t2) throw() { return t1 /= t2; }

//=================================================================================================
/** \brief Addition of two times. */
inline eve::time::Absolute operator + (eve::time::Relative & t1, eve::time::Absolute & t2) throw() { return t2 += t1; }
/** \brief Subtraction of two times. */
inline eve::time::Absolute operator - (eve::time::Relative & t1, eve::time::Absolute & t2) throw() { return t2 -= t1; }
/** \brief Multiplication of two times. */
inline eve::time::Absolute operator * (eve::time::Relative & t1, eve::time::Absolute & t2) throw() { return t2 *= t1; }
/** \brief Division of two times. */
inline eve::time::Absolute operator / (eve::time::Relative & t1, eve::time::Absolute & t2) throw() { return t2 /= t1; }

//=================================================================================================
/** \brief Addition of time and int64_t (milliseconds). */
inline eve::time::Absolute operator + (eve::time::Absolute & t1, int64_t p_milliseconds) throw() { return t1 += p_milliseconds; }
/** \brief Subtraction of time by int64_t (milliseconds). */
inline eve::time::Absolute operator - (eve::time::Absolute & t1, int64_t p_milliseconds) throw() { return t1 -= p_milliseconds; }
/** \brief Multiplication of time by int64_t (milliseconds). */
inline eve::time::Absolute operator * (eve::time::Absolute & t1, int64_t p_milliseconds) throw() { return t1 *= p_milliseconds; }
/** \brief Division of time by int64_t (milliseconds). */
inline eve::time::Absolute operator / (eve::time::Absolute & t1, int64_t p_milliseconds) throw() { return t1 /= p_milliseconds; }


/** 
* \def EVE_LOG_TIME
* \brief Convenience macro to log detailed time (e.g. "Sunday October 19 2014 23:02:49 Paris, Madrid (summer time)").
*/
#define EVE_LOG_TIME	EVE_LOG_INFO("%s", eve::time::Absolute::create_from_current_time().formatted(EVE_TXT("%A %B %d %Y %H:%M:%S %Z")).c_str())

#endif // __EVE_TIME_ABSOLUTE_H__

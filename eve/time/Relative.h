
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
#ifndef __EVE_TIME_RELATIVE_H__
#define __EVE_TIME_RELATIVE_H__

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
		* \class eve::time::Relative
		*
		* \brief A relative date and time stored as a number of seconds, at double-precision floating point accuracy.
		* May be positive or negative.
		*/
		class Relative
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			static const double m_mult_minute;		//!< Convenience double factor to retrieve minutes.
			static const double m_mult_hours;		//!< Convenience double factor to retrieve hours.
			static const double m_mult_days;		//!< Convenience double factor to retrieve days.
			static const double m_mult_weeks;		//!< Convenience double factor to retrieve weeks.


		private:
			double				m_seconds;			//!< Seconds representing time as double precision floating point.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////


		public:
			/** \brief Class constructor. */
			explicit Relative(double p_seconds = 0.0) throw();

			/** \brief Copy constructor. */
			Relative(const Relative & p_other) throw();

			/** \brief Class destructor. */
			virtual ~Relative(void) throw();

			/** \brief Assignment operator. */
			Relative & operator= (const Relative & p_other) throw();


		public:
			/** \brief Creates a new Relative object representing a number of milliseconds. */
			static Relative create_from_milliseconds(int32_t p_milliseconds) throw();
			/** \brief Creates a new Relative object representing a number of milliseconds. */
			static Relative create_from_milliseconds(int64_t p_milliseconds) throw();
			/** \brief Creates a new Relative object representing a number of seconds. */
			static Relative create_from_seconds(double p_seconds) throw();
			/** \brief Creates a new Relative object representing a number of minutes. */
			static Relative create_from_minutes(double p_minutes) throw();
			/** \brief Creates a new Relative object representing a number of hours. */
			static Relative create_from_hours(double p_hours) throw();
			/** \brief Creates a new Relative object representing a number of days. */
			static Relative create_from_days(double p_days) throw();
			/** \brief Creates a new Relative object representing a number of weeks. */
			static Relative create_from_weeks(double p_weeks) throw();


		public:
			/** \brief Adds another Relative to this one. */
			Relative operator += (const Relative & p_time) throw();
			/** \brief Subtracts another Relative from this one. */
			Relative operator -= (const Relative & p_time) throw();
			/** \brief Multiply time. */
			Relative operator *= (const Relative & p_time) throw();
			/** \brief Divide time. */
			Relative operator /= (const Relative & p_time) throw();

			/** \brief Adds a number of seconds to this time. */
			Relative operator += (double p_seconds) throw();
			/** \brief Subtracts a number of seconds from this time. */
			Relative operator -= (double p_seconds) throw();
			/** \brief Multiply time. */
			Relative operator *= (double p_seconds) throw();
			/** \brief Divide time. */
			Relative operator /= (double p_seconds) throw();


		public:
			/**
			* \brief Returns a readable textual description of the time.
			*
			* The exact format of the string returned will depend on
			* the magnitude of the time - e.g.
			*
			* "1 min 4 secs", "1 hr 45 mins", "2 weeks 5 days", "140 ms"
			*
			* so that only the two most significant units are printed.
			*
			* The p_retZero value is the result that is returned if the
			* length is zero. Depending on your application you might want to use this
			* to return something more relevant like "empty" or "0 secs", etc.
			*/
			std::wstring formatted(const std::wstring & p_retZero = EVE_TXT("0")) const;


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Returns the number of milliseconds this time represents. */
			int64_t getMilliseconds(void) const throw();
			/** \brief Returns the number of milliseconds this time represents. */
			int32_t getMillisecondsShort(void) const throw();
			/** \brief Returns the number of seconds this time represents. */
			double getSeconds(void) const throw();
			/** \brief Returns the number of minutes this time represents. */
			double getMinutes(void) const throw();
			/** \brief Returns the number of hours this time represents. */
			double getHours(void) const throw();
			/** \brief Returns the number of days this time represents. */
			double getDays(void) const throw();
			/** \brief Returns the number of weeks this time represents. */
			double getWeeks(void) const throw();

		}; // class Relative

	} // namespace time

} // namespace eve


//=================================================================================================
inline int64_t eve::time::Relative::getMilliseconds(void) const throw()			{ return static_cast<int64_t>(m_seconds * 1000.0);	}
inline int32_t eve::time::Relative::getMillisecondsShort(void) const throw()	{ return static_cast<int32_t>(m_seconds * 1000.0);	}
inline double  eve::time::Relative::getSeconds(void) const throw()				{ return m_seconds;									}
inline double  eve::time::Relative::getMinutes(void) const throw()				{ return m_seconds * m_mult_minute;					}
inline double  eve::time::Relative::getHours(void) const throw()				{ return m_seconds * m_mult_hours;					}
inline double  eve::time::Relative::getDays(void) const throw()					{ return m_seconds * m_mult_days;					}
inline double  eve::time::Relative::getWeeks(void) const throw()				{ return m_seconds * m_mult_weeks;					}



//=================================================================================================
/** \brief Compares two eve::time::Relative. */
inline bool operator == (const eve::time::Relative & t1, const eve::time::Relative & t2) throw()	{ return t1.getSeconds() == t2.getSeconds(); }
/** \brief Compares two eve::time::Relative. */
inline bool operator != (const eve::time::Relative & t1, const eve::time::Relative & t2) throw()	{ return t1.getSeconds() != t2.getSeconds(); }
/** \brief Compares two eve::time::Relative. */
inline bool operator >  (const eve::time::Relative & t1, const eve::time::Relative & t2) throw()	{ return t1.getSeconds() >  t2.getSeconds(); }
/** \brief Compares two eve::time::Relative. */
inline bool operator <  (const eve::time::Relative & t1, const eve::time::Relative & t2) throw()	{ return t1.getSeconds() <  t2.getSeconds(); }
/** \brief Compares two eve::time::Relative. */
inline bool operator >= (const eve::time::Relative & t1, const eve::time::Relative & t2) throw()	{ return t1.getSeconds() >= t2.getSeconds(); }
/** \brief Compares two eve::time::Relative. */
inline bool operator <= (const eve::time::Relative & t1, const eve::time::Relative & t2) throw()	{ return t1.getSeconds() <= t2.getSeconds(); }

//=================================================================================================
/** \brief Compares eve::time::Relative to double (seconds). */
inline bool operator == (const eve::time::Relative & t1, double p_seconds) throw()	{ return t1.getSeconds() == p_seconds; }
/** \brief Compares eve::time::Relative to double (seconds). */
inline bool operator != (const eve::time::Relative & t1, double p_seconds) throw()	{ return t1.getSeconds() != p_seconds; }
/** \brief Compares eve::time::Relative to double (seconds). */
inline bool operator >  (const eve::time::Relative & t1, double p_seconds) throw()	{ return t1.getSeconds() >  p_seconds; }
/** \brief Compares eve::time::Relative to double (seconds). */
inline bool operator <  (const eve::time::Relative & t1, double p_seconds) throw()	{ return t1.getSeconds() <  p_seconds; }
/** \brief Compares eve::time::Relative to double (seconds). */
inline bool operator >= (const eve::time::Relative & t1, double p_seconds) throw()	{ return t1.getSeconds() >= p_seconds; }
/** \brief Compares eve::time::Relative to double (seconds). */
inline bool operator <= (const eve::time::Relative & t1, double p_seconds) throw()	{ return t1.getSeconds() <= p_seconds; }



//=================================================================================================
/** \brief Adds two eve::time::Relative together. */
inline eve::time::Relative  operator + (eve::time::Relative & t1, eve::time::Relative & t2) throw()		{ return t1 += t2; }
/** \brief Subtracts two eve::time::Relative. */
inline eve::time::Relative  operator - (eve::time::Relative & t1, eve::time::Relative & t2) throw()		{ return t1 -= t2; }
/** \brief Multiply two eve::time::Relative. */
inline eve::time::Relative  operator * (eve::time::Relative & t1, eve::time::Relative & t2) throw()		{ return t1 *= t2; }
/** \brief Divide two eve::time::Relative. */
inline eve::time::Relative  operator / (eve::time::Relative & t1, eve::time::Relative & t2) throw()		{ return t1 /= t2; }

//=================================================================================================
/** \brief Adds double (seconds) to eve::time::Relative. */
inline eve::time::Relative  operator + (eve::time::Relative & t1, double p_seconds) throw()		{ return t1 += p_seconds; }
/** \brief Subtracts double (seconds) from eve::time::Relative. */
inline eve::time::Relative  operator - (eve::time::Relative & t1, double p_seconds) throw()		{ return t1 -= p_seconds; }
/** \brief Multiply eve::time::Relative by double (seconds). */
inline eve::time::Relative  operator * (eve::time::Relative & t1, double p_seconds) throw()		{ return t1 *= p_seconds; }
/** \brief Divide eve::time::Relative by double (seconds). */
inline eve::time::Relative  operator / (eve::time::Relative & t1, double p_seconds) throw()		{ return t1 /= p_seconds; }

#endif // __EVE_TIME_RELATIVE_H__

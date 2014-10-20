
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
#ifndef __EVE_TIME_TIMER_H__
#define __EVE_TIME_TIMER_H__

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
		* \class eve::time::Timer
		* 
		* \brief High-resolution timer.
		*
		* \note extends eve::mem::Pointer.
		*/
		class Timer
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			int64_t		m_startTime;			//!< Timer start time in milliseconds.
			int64_t		m_endTime;				//!< Timer end time in milliseconds.
			int64_t		m_milliElapsed;			//!< Timer elapsed time.

			double		m_invFrequency;			//!< Convenience inverse native frequency factor.

			bool		m_bRunning;				//!< Timer running state.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_PROTECT_DESTRUCTOR(Timer);

		public:
			/**
			* \brief Create and return new pointer.
			* \param p_start decide if the timer shall start at creation time.
			*/
			static Timer * create_ptr(bool p_start = false);


		protected:
			/** \brief Class constructor. */
			explicit Timer(void);


		public:
			/** \brief Copy constructor. */
			Timer(const Timer & p_other);
			/** \brief Assignation operator. */
			Timer & operator = (const Timer & p_other);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		protected:
#if defined(EVE_OS_WIN)
			/** \brief Query performance counter (Windows only). */
			static int64_t query_performance_counter(void);
#endif


		public:
			/** \brief Start timer. */
			void start(void);
			/** \brief Stop timer. */
			void stop(void);


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get timer running state. */
			const bool isRunning(void) const;
			/** \brief Get timer stopped state. */
			const bool isStopped(void) const;


		public:
			/** \brief Get timer start time in milliseconds. */
			const int64_t getStartTime(void) const;
			/** \brief Get timer end time in milliseconds. */
			const int64_t getEndTime(void) const;
			/** \brief Get timer elapsed time in milliseconds. */
			int64_t getElapsedTime(void);

		}; // class Timer

	} // namespace time

} // namespace eve

//=================================================================================================
inline const bool eve::time::Timer::isRunning(void) const			{ return  m_bRunning;		}
inline const bool eve::time::Timer::isStopped(void) const			{ return !m_bRunning;		}

//=================================================================================================
inline const int64_t eve::time::Timer::getStartTime(void) const		{ return m_startTime;		}
inline const int64_t eve::time::Timer::getEndTime(void) const		{ return m_endTime;			}

#endif //__EVE_TIME_TIMER_H__

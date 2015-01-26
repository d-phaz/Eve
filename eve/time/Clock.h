
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
#ifndef __EVE_TIME_CLOCK_H__
#define __EVE_TIME_CLOCK_H__

#ifndef __EVE_THREADING_THREAD_H__
#include "eve/thr/Thread.h"
#endif 

#ifndef __EVE_EVT_TEVENT_H__
#include "eve/evt/TEvent.h"
#endif

#ifndef __EVE_TIME_TIMER_H__
#include "eve/time/Timer.h"
#endif

namespace eve
{
	namespace time
	{
		/** 
		* \class eve::time::Clock
		* 
		* \brief Thread-based high-resolution clock.
		* 
		* A clock starts a thread that first waits for a given start interval.
		* Once that interval expires, the clock triggers an event repeatedly in the given periodic interval.
		* If the interval is below 10 milliseconds, please set run wait time to fit your needs (initial run wait time is 10 milliseconds).
		* 
		* The exact interval at which the event is triggered depends on many factors like operating system, CPU performance and system load and may differ from the specified interval.
		* 
		* The time needed to execute the timer event is included in the interval between invocations.
		* 
		* For example, if the interval is 500 milliseconds, and the event needs 400 milliseconds to execute, the event is triggered every 100 milliseconds.
		* 
		* If the event takes longer to execute than the interval, the event will not be triggered until the next proper interval.
		* 
		* The clock is thread-based, so there is a limit to the number of available concurrent clocks.
		*
		* \note extends eve::thr::Thread
		*/
		class Clock
			: public eve::thr::Thread
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			eve::time::Timer *			m_pTimer;				//!< High resolution timer.

			int64_t						m_intervalPeriod;		//!< Periodic interval between each event trigger in milliseconds.
			int64_t						m_intervalSleep;		//!< Interval used to compensate event dispatch time.

		protected:
			eve::evt::TEvent<void>		m_event;				//!< Event triggered.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Clock);
			EVE_PUBLIC_DESTRUCTOR(Clock);

		public:
			/** \brief Class constructor. */
			explicit Clock(void);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/**
			* \brief Release and delete class members. (pure virtual)
			* Stop this object's thread execution (if any) immediately.
			*/
			virtual void release(void) override;


		protected:
			/** \brief Alloc and init threaded data. (pure virtual) */
			virtual void initThreadedData(void) override;
			/** \brief Release and delete threaded data. (pure virtual) */
			virtual void releaseThreadedData(void) override;


		protected:
			/**
			* \brief Run is the main loop for this thread. (pure virtual)
			* Usually this is called by Start(), but may be called directly for single-threaded applications.
			*/
			virtual void run(void) override;


		public:
			/** \brief Restarts the periodic interval. If it is already running, nothing will happen. */
			void restart(void);
			/** \brief Sets a new periodic interval and restarts the clock. */
			void restart(int64_t p_milliseconds);


		public:
			/**
			* \brief Register listener class to clock event.
			* Listener class must provide event handler methods using the following signatures:
			*		void cb_evtClock(void)
			*/
			template<class ListenerClass>
			void registerListener(ListenerClass * p_pListener);
			/**
			* \brief Unregister listener class to clock events.
			* Listener class must provide event handler methods using the following signatures:
			*		void cb_evtClock(void)
			*/
			template<class ListenerClass>
			void unregisterListener(ListenerClass * p_pListener);


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get periodic interval in milliseconds. */
			int64_t getPeriodicInterval(void) const;
			/** 
			* \brief Sets the periodic interval.
			* If the timer is already running the new interval will be effective when the current interval expires.
			*/
			void setPeriodicInterval(int64_t p_milliseconds);
			
		}; // class Timer

	} // namespace time

} // namespace eve

//=================================================================================================
template<class ListenerClass>
inline void eve::time::Clock::registerListener(ListenerClass * p_pListener)
{
	m_pFence->lock();
	eve::evt::add_listener(m_event, p_pListener, &ListenerClass::cb_evtClock);
	m_pFence->unlock();
}

//=================================================================================================
template<class ListenerClass>
inline void eve::time::Clock::unregisterListener(ListenerClass * p_pListener)
{
	m_pFence->lock();
	eve::evt::remove_listener(m_event, p_pListener, &ListenerClass::cb_evtClock);
	m_pFence->unlock();
}



//=================================================================================================
inline int64_t eve::time::Clock::getPeriodicInterval(void) const
{
	return m_intervalPeriod;
}

#endif //__EVE_TIME_TIMER_H__

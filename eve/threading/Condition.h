
/*
 Copyright (c) 2014, The Eve Project
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
#ifndef __EVE_THREADING_CONDITION_H__
#define __EVE_THREADING_CONDITION_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "Eve/core/Includes.h"
#endif

#ifndef __EVE_THREADING_MUTEX_H__
#include "Eve/threading/Mutex.h"
#endif


namespace eve
{
	namespace threading
	{

		/**
		* @class threading::Condition
		*
		* @brief locking condition class
		* @note extends threading::Mutex, memory::Pointer
		*/
		class Condition
			: public eve::threading::Mutex
		{

			friend class eve::memory::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			void *			m_condition;

		private:
			int32_t			m_conditionnedVar;
			bool			m_isValid;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Condition)
			EVE_PROTECT_DESTRUCTOR(Condition)

		protected:
			/** Class constructor. */
			Condition(void);


		protected:
			/** Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** Sleep this thread, waiting for condition signal,
			* atomically release mutex and wait on condition,
			* then re-acquire the mutex.
			*/
			void wait(void);

			/** Sleep this thread, waiting for condition signal,
			* but bound sleep time by the relative time p_inSeconds.
			* Atomically release mutex and wait on condition,
			* then re-acquire the mutex.
			*/
			void timedWait(time_t p_inSeconds);

			/** Sleep this thread, waiting for condition signal,
			* but bound sleep time by the relative time p_inMiliSeconds.
			* Atomically release mutex and wait on condition,
			* then re-acquire the mutex.
			*/
			void timedWaitMili(time_t p_inMiliSeconds);


			/** Wait for condition and retain thread. */
			bool waitAndRetain(int32_t p_value);

			/** Waits until the Condition's value == p_awaitedValue and protects the Condition.
			* You're responsible for unlocking the Condition with Unlock() after
			* WaitAndLock() returned and after you're done working on protected data,
			* or enabling the auto unlocking mechanism.
			*
			* The Condition locking guarantees that the condition remains true until
			* you unlock it and that you are the only one that acquired the Condition.
			*
			* @p_awaitedValue: the value that should unlock the Condition
			*
			* @autoUnlock: Condition::AutoUnlock (true) to automatically unlock the Condition
			* protection after it has been validated, or ManualUnlock (false) to
			* manually choose when the Condition should be unlocked. While a Condition
			* is locked, both WaitAndLock() and operator=() will block
			* until the Condition is unlocked or invalidated. When a Condition is
			* *automatically* unlocked, its value is not updated.
			*
			* @return: true if the @p_awaitedValue has been reached, false otherwise.
			* WaitAndLock() may return even if @p_awaitedValue has not been
			* reached if the Condition has been disabled through Invalidate(). An
			* invalidated Condition always returns in an unlocked state.
			*/
			bool waitAndLock(int32_t p_awaitedValue, bool p_autorelease = false);


			/** Send a condition signal to wake one thread waiting on condition
			* in Win32, this actually wakes up all threads, same as Broadcast
			* use PulseEvent to auto-reset the signal after waking all threads.
			*/
			void signal(void);

			/** Send a condition signal to wake all threads waiting on condition. */
			void broadcast(void);


			/** Release thread and condition. */
			void release(int32_t value);


			/** Performs an assignement followed by a signal() call.
			* The internal Condition value is updated to @value and the Condition is
			* signaled. Note that the Condition must be unlocked in order
			* to be updated, otherwise it'll block until the Condition
			* is unlocked.
			*
			* @value: the value to be assigned to the Condition.
			*
			* @return: @value.
			*/
			int32_t operator=(int32_t value);


			/** Signals the Condition and disables blocking calls,
			* thus WaitAndLock() does no more wait whatever
			* the p_awaitedValue is and waiting calls are unlocked, returning false.
			*/
			void invalidate(void);


			/** Restores the blocking capabilities of the Condition,
			* possibly previously disabled using invalidate()
			*/
			void restore(void);


			/* Get the current internal Condition value.
			* This is a non-blocking call.
			*
			* @return the current internal state.
			*/
			const int32_t getValue(void) const;

			/** Set the new internal condition value.
			* Make sure the Condition's value is not modified while retained.
			*/
			void setValue(int32_t value);

		}; // class Condition

	} // namespace threading

} // namespace eve



//=================================================================================================
inline const int32_t eve::threading::Condition::getValue(void) const
{
	return m_conditionnedVar;
}



#endif // __EVE_THREADING_CONDITION_H__

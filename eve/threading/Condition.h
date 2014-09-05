
#pragma once
#ifndef __EVE_THREADING_CONDITION_H__
#define __EVE_THREADING_CONDITION_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "core/Includes.h"
#endif

#ifndef __THREADING_MUTEX_H__
#include "threading/Mutex.h"
#endif


namespace eve
{
	namespace threading
	{

		/**
		* @class threading::Condition
		*
		* @brief locking condition class
		* @note extends threading::Mutex
		*/
		class Condition
			: public threading::Mutex
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			HANDLE			m_condition;

		private:
			int32_t			m_conditionnedVar;
			bool			m_isValid;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			/**
			* @brief Condition class constructor : initialize base condition
			*/
			Condition(int32_t p_var);
			/**
			* @brief Condition class destructor : TODO -> make sure condition is unlocked
			*/
			virtual ~Condition(void);


			/**
			* @brief sleep this thread, waiting for condition signal,
			* atomically release mutex and wait on condition,
			* then re-acquire the mutex
			*/
			void wait(void);
			/**
			* @brief sleep this thread, waiting for condition signal,
			* but bound sleep time by the relative time p_inSeconds.
			* Atomically release mutex and wait on condition,
			* then re-acquire the mutex
			*/
			void timedWait(time_t p_inSeconds);
			/**
			* @brief sleep this thread, waiting for condition signal,
			* but bound sleep time by the relative time p_inMiliSeconds.
			* Atomically release mutex and wait on condition,
			* then re-acquire the mutex
			*/
			void timedWaitMili(time_t p_inMiliSeconds);


			/**
			* @brief wait for condition and retain thread
			*/
			bool waitAndRetain(int32_t p_value);
			/** 
			* @brief Waits until the Condition's value == p_awaitedValue and protects the Condition.
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


			/**
			* @brief send a condition signal to wake one thread waiting on condition
			* in Win32, this actually wakes up all threads, same as Broadcast
			* use PulseEvent to auto-reset the signal after waking all threads
			*/
			void signal(void);
			/**
			* @brief send a condition signal to wake all threads waiting on condition
			*/
			void broadcast(void);


			/**
			* @brief release thread and condition
			*/
			void release(int32_t value);


			/**
			* @brief Performs an assignement followed by a signal() call.
			* The internal Condition value is updated to @value and the Condition is
			* signaled. Note that the Condition must be unlocked in order
			* to be updated, otherwise it'll block until the Condition
			* is unlocked.
			*
			* @value: the value to be assigned to the Condition
			*
			* @return: @value
			*/
			int32_t operator=(int32_t value);


			/**
			* @brief Signals the Condition and disables blocking calls,
			* thus WaitAndLock() does no more wait whatever
			* the p_awaitedValue is and waiting calls are unlocked, returning false.
			*/
			void invalidate(void);


			/**
			* @brief Restores the blocking capabilities of the Condition,
			* possibly previously disabled with Invalidate()
			*/
			void restore(void);


			/*
			* @brief Get the current internal Condition value.
			* This is a non-blocking call.
			*
			* @return the current internal state
			*/
			const int32_t getValue(void) const;
			/**
			* @brief set the new internal condition value.
			* Make sure the Condition's value is not modified while retained
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

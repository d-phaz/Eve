
#pragma once
#ifndef __THREADING_CONDITION_H__
#define __THREADING_CONDITION_H__

#ifndef __THREADING_MUTEX_H__
#include "threading/Mutex.h"
#endif


namespace NativeT {

	/**
	* @class NativeT::Condition
	*
	* @brief base locking condition class
	*
	* @note extends NativeT::Mutex
	*/
	class Condition 
		: public NativeT::Mutex
	{

		//////////////////////////////////////
		//				DATAS				//
		//////////////////////////////////////

	protected:
		HANDLE			m_condition;

	private:
		int				m_conditionnedVar;
		bool			m_isValid;


		//////////////////////////////////////
		//				METHOD				//
		//////////////////////////////////////

	public:
		/**
		* @brief Condition class constructor : initialise base condition
		*/
		Condition( int p_var=0 )
			// Inheritance
			: NativeT::Mutex()
			// Members init
			, m_isValid				( true )
			, m_conditionnedVar		( p_var )
		{
			// set all conditions to be broadcast
			// unfortunately in Win32 you have to know at creation
			// whether the signal is broadcast or not.
			m_condition = CreateEventA( NULL, true, false, NULL );
		}
		/**
		* @brief Condition class destructor : TODO -> make sure condition is unlocked
		*/
		virtual ~Condition( void )
		{
			CloseHandle( m_condition );
		}


		/**
		* @brief sleep this thread, waiting for condition signal,
		* atomically release mutex and wait on condition,
		* then re-acquire the mutex
		*/
		void Wait( void )
		{
			SignalObjectAndWait( m_mutex, m_condition, INFINITE, false );
			WaitForSingleObject( m_mutex, INFINITE );
		}
		/**
		* @brief sleep this thread, waiting for condition signal,
		* but bound sleep time by the relative time p_inSeconds.
		* Atomically release mutex and wait on condition,
		* then re-acquire the mutex
		*/
		void TimedWait( time_t p_inSeconds )
		{
			SignalObjectAndWait( m_mutex, m_condition, (DWORD)(p_inSeconds*1000), false );
			WaitForSingleObject( m_mutex, INFINITE );
		}
		/**
		* @brief sleep this thread, waiting for condition signal,
		* but bound sleep time by the relative time p_inMiliSeconds.
		* Atomically release mutex and wait on condition,
		* then re-acquire the mutex
		*/
		void TimedWaitMili( time_t p_inMiliSeconds )
		{
			SignalObjectAndWait( m_mutex, m_condition, (DWORD)(p_inMiliSeconds), false );
			WaitForSingleObject( m_mutex, INFINITE );
		}


		/**
		* @brief wait for condition and retain thread
		*/
		bool waitAndRetain( int p_value )
		{
			Lock();

			while( m_conditionnedVar != p_value && m_isValid )
			{
				Unlock();
				WaitForSingleObject(m_condition, INFINITE);
				Lock();
			}

			bool B_Return = false;
			if( m_isValid ) {
				B_Return = true;
			}
			else {
				Unlock();
			}

			return B_Return;
		}


		/** @brief Waits until the Condition's value == p_awaitedValue and protects the Condition.
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
		bool waitAndLock( int p_awaitedValue, bool p_autorelease=false )
		{
			bool B_Return = this->waitAndRetain( p_awaitedValue );

			if( p_autorelease ) {
				this->release(p_awaitedValue);
			}

			return B_Return;
		}


		/**
		* @brief send a condition signal to wake one thread waiting on condition
		* in Win32, this actually wakes up all threads, same as Broadcast
		* use PulseEvent to auto-reset the signal after waking all threads
		*/
		void Signal( void )
		{
			PulseEvent( m_condition );
		}
		/**
		* @brief send a condition signal to wake all threads waiting on condition
		*/
		void Broadcast( void )
		{
			PulseEvent( m_condition );
		}


		/**
		* @brief release thread and condition
		*/
		void release( int value )
		{
			m_conditionnedVar = value;
			Unlock();
			this->Signal();
		}


		/* 
		* @brief Get the current internal Condition value.
		* This is a non-blocking call.
		*
		* @return the current internal state
		*/
		int value(void) const
		{
			return m_conditionnedVar;
		}
		/**
		* @brief set the new internal condition value.
		* Make sure the Condition's value is not modified while retained
		*/
		void setValue(int value)
		{
			Lock();
			m_conditionnedVar = value;
			Unlock();

			this->Signal();
		}


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
		int operator=( int value )
		{
			this->setValue( value );
			return value;
		}


		/**
		* @brief Signals the Condition and disables blocking calls,
		* thus WaitAndLock() does no more wait whatever
		* the p_awaitedValue is and waiting calls are unlocked, returning false.
		*/
		void invalidate( void )
		{
			if (m_isValid)
			{
				m_isValid = false;
				this->Signal();
			}
		}

		/**
		* @brief Restores the blocking capabilities of the Condition,
		* possibly previously disabled with Invalidate() 
		*/
		void restore( void )
		{
			if( !m_isValid ) {
				m_isValid = true;
			}
		}

	};

} // namespace NativeT

#endif // __THREADING_CONDITION_H__

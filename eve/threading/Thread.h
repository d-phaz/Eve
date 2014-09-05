
#pragma once
#ifndef __EVE_THREADING_THREAD_H__
#define __EVE_THREADING_THREAD_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "core/Includes.h"
#endif

#ifndef __EVE_THREADING_MUTEX_H__
#include "threading/Mutex.h"
#endif

#ifndef __EVE_THREADING_LOCK_H__
#include "threading/Lock.h"
#endif 

#ifndef __EVE_THREADING_CONDITION_H__
#include "threading/Condition.h"
#endif


namespace eve
{
	namespace threading
		{
		/**
		* @class NativeT::Thread
		*
		* Abstract base thread class containing init and release abstract methods,
		* each thread must inherit from this class to properly alloc/init and release/free its members.
		*/
		class Thread 
		{

		public:
			enum priorities 
			{
				IdlePriority,

				LowestPriority,
				LowPriority,
				NormalPriority,
				HighPriority,
				HighestPriority,

				TimeCriticalPriority,

				InheritPriority
			};

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////
	
		public:
			mutable Mutex		m_mutex;
			HANDLE				m_hThread;
			HANDLE				m_hShutdownEvent;
			HANDLE				m_StartEvent;
			int32_t				m_waiters;
			int32_t				m_runWait;

		protected:
			DWORD				m_threadID;
			bool				m_bRunning;
			bool				m_bDeleteSelf;

			int32_t				m_returnCode;
			priorities			m_priority;

		
			static int32_t		m_thread_number;	//<! count of threads, used in joinall
			static Condition	m_num_cond;			//<! count of conditions, used in joinall


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		private:
			// Suppress copying
			Thread(const Thread &);
			const Thread & operator=(const Thread &);


			/**
			* @brief Low level function which starts a new thread, called by
			* Start(). The argument should be a pointer to a Thread object.
			* Calls the virtual Run() function for that object.
			* Upon completing, decrements thread count and resets thread m_threadID.
			* If the object is deallocated immediately after calling Start(),
			* such as an object created on the stack that has since gone
			* out-of-scope, this will obviously fail.
			* This must be static in order to work with _beginthread / _beginthreadex / ...
			*
			* @note static function
			*/
			static uint32_t WINAPI run_wrapper(void * p_pThread);


		public:
			/**
			* @brief Thread class constructor
			*
			* @param p_runWait run wait time in milliseconds (default to 5)
			*/
			Thread( int32_t p_runWait=5 );
			/**
			* @brief Thread class destructor.
			* Stop this object's thread execution (if any) immediately.
			*/
			virtual ~Thread( void );


			/**
			* @brief run is the main loop for this thread
			* usually this is called by Start(), but may be called
			* directly for single-threaded applications.
			*
			* @note pure virtual function
			*/
			virtual void Run( void ) = 0;

		
			/**
			* @brief Start the object's thread execution. Increments thread
			* count, spawns new thread, and stores thread m_threadID.
			*
			* @note pure virtual function
			*/
			virtual void Start( void );
			/**
			* @brief Stop the thread immediately. Decrements thread count and
			* resets the thread m_threadID.
			* @note virtual function
			*/
			virtual void Stop( void );
			/**
			* @brief pause thread execution
			* @note OSX compatibility compliance (calls Stop)
			*/
			void Pause(void);


		protected:
			/**
			* @brief initialization function
			* @note pure virtual function
			*/
			virtual void init(void) = 0;
			/**
			* @brief release function
			* @note pure virtual function
			*/
			virtual void release(void) = 0;


			/**
			* @brief Wait for this object's thread execution (if any) to complete.
			*/
			virtual bool Join( void );
			/**
			* @brief wait for all threads to complete
			*/
			/**
			* @brief Wait for all thread object's execution to complete. Depends on the
			* thread count being accurate and the threads sending a condition
			* signal when they terminate.
			*
			* @note static function
			*/
			static void join_all( void );
			/**
			* @brief guarantees resources consumed by thread are released when thread terminates,
			* after this join can no-longer be used
			*/
			virtual void detach( void );
		

			/**
			* @brief sleep thread for given amount of milliseconds
			* @param p_milliseconds milliseconds amount to sleep
			*
			* @note static function
			*/
			static void m_sleep( const int32_t p_milliseconds );
			/**
			* @brief (micro)sleep thread for given amount of iterations, switch hand to other threads
			* @param p_iters iterations amount
			*
			* @note static function
			*/
			static void u_sleep( uint32_t p_iters );
			/**
			* @brief (micro)sleep thread for given amount of micro seconds, switch hand to other threads
			* @param p_ticks target ticks amount
			*
			* @note static function
			*/
			static void u_sleep( uint64_t p_ticks );

		
			/**
			* @brief get current thread ID
			* @return id as DWORD
			*/
			static DWORD current_thread_ID( void );
			/**
			* @brief Compare the thread m_threadID's (inLeft == inRight); return true if they
			* are equal. On some OS's DWORD is a struct so == will not work.
			*
			* @note static function
			*/
			static bool equal_ID( DWORD inLeft, DWORD inRight );
			/**
			* @brief Return a zero'd out thread m_threadID. On some OS's DWORD is a struct
			* so == 0 will not work.
			*
			* @note static function
			*/
			static DWORD zero_ID( void );


			///////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** Get the number of user (i.e. not daemon) threads as int32_t. */
			static int32_t get_number_user_threads( void );


			/** Set a thread to be daemon, so joinall won't wait on it
			* this simply decrements the thread count that joinall uses,
			* which is not a thorough solution, but works for the moment
			*/
			virtual void setDaemon( void );


			/** Set thread deletion after run property. */
			virtual void setDeleteSelfAfterRun( void );


			/**
			* @brief get thread priority
			*
			* @param p_priority target reference to stock thread priority value
			* @return true if successful, false otherwise
			*/
			virtual bool getPriority( priorities & p_priority );
			/**
			* @brief Set the m_priority for the native thread if supported by the system.
			*
			* @param p_priority target priority as priorities enum
			* @return true if successful, false otherwise
			*/
			virtual bool setPriority( priorities p_priority );


			/**
			* @brief get thread running state
			* @return true if thread is running, false otherwise
			*/
			virtual bool running( void );


			/**
			* @brief get thread started state
			* @return true if thread started, false otherwise
			*/
			virtual bool started( void );

		protected:
			/**
			* @brief set thread started state
			*/
			virtual void setStarted ( void );
			/**
			* @brief reset thread started state
			*/
			virtual void resetStarted ( void );

		}; // Class Thread

	} // namespace threading

} // namespace eve

#endif // __EVE_THREADING_THREAD_H__

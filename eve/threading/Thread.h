
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
#ifndef __EVE_THREADING_THREAD_H__
#define __EVE_THREADING_THREAD_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "Eve/core/Includes.h"
#endif


namespace eve
{
	namespace threading
	{
		class Condition;
		class Lock;
		class Mutex;

		/**
		* @class NativeT::Thread
		*
		* Abstract base thread class containing init and release abstract methods,
		* each thread must inherit from this class to properly alloc/init and release/free its members.
		*
		* @note extends memory::Pointer
		*/
		class Thread
			: public eve::memory::Pointer
		{

			friend class eve::memory::Pointer;

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
			mutable Mutex *		m_mutex;
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
			static Condition *	m_num_cond;			//<! count of conditions, used in joinall


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Thread)
			EVE_PROTECT_DESTRUCTOR(Thread)


		public:
			/** Create new pointer. */
			static Thread * create_ptr(void);
			/** Release pointer. */
			static void release_ptr(Thread * p_pPtr);


		private:
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


		protected:
			/** Class constructor. */
			Thread( void );


		protected:
			/** Alloc and init class members. (pure virtual) */
			virtual void init(void);
			/** 
			* Release and delete class members. (pure virtual) 
			* Stop this object's thread execution (if any) immediately
			*/
			virtual void release(void);


		public:
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
			virtual void inThreadInit(void) = 0;
			/**
			* @brief release function
			* @note pure virtual function
			*/
			virtual void inThreadRelease(void) = 0;


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

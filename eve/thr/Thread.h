
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
#ifndef __EVE_THREADING_THREAD_H__
#define __EVE_THREADING_THREAD_H__

#include <thread>

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif


namespace eve { namespace thr { class SpinLock; } }


namespace eve
{
	namespace thr
	{

		/**
		* \class eve::thr::Thread
		*
		* \brief Abstract base thread class containing init and release abstract methods,
		* each thread must inherit from this class to properly alloc/init and release/free its members.
		*
		* \note extends eve::mem::Pointer
		*/
		class Thread
			: public eve::mem::Pointer
		{

			//////////////////////////////////////
			//				TYPE				//
			//////////////////////////////////////

		public:
			/** 
			* \brief Thread function pointer type. 
			* Used in _beginthreadex call.
			*/
			typedef unsigned(__stdcall *ThreadRoutine)(void *);


			/** \brief Human readable thread priority enum. */
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
			//				DATA				//
			//////////////////////////////////////
	
		protected:
			//std::thread *				m_hThread;					//!< Thread handle (void*).
			//std::thread::id			m_threadID;					//!< Thread ID (DWORD)
			HANDLE						m_hThread;					//!< Thread handle (void*).
			DWORD						m_threadID;					//!< Thread ID (DWORD)

			HANDLE						m_hShutdownEvent;			//!< Thread shut down event.
			HANDLE						m_StartEvent;				//!< Thread start event.
			
			uint32_t					m_runWait;					//!< Sleep time when testing running() in milliseconds. \sa running()


		protected:
			eve::thr::SpinLock *		m_pFence;					//!< Spin lock protecting workers and run loop.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Thread);
			EVE_PUBLIC_DESTRUCTOR(Thread);

		public:
			/** \brief Class constructor. */
			explicit Thread(void);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** 
			* \brief Release and delete class members. (pure virtual) 
			* Stop this object's thread execution (if any) immediately.
			*/
			virtual void release(void) override;


		public:
			/**
			* \brief Start the object's thread execution. 
			* Increments thread count, spawns new thread, and stores thread m_threadID.
			*/
			void start(void);


		private:
			/**
			* \brief Low level function which starts a new thread, called by start().
			*
			* The argument should be a pointer to a Thread object.
			* Calls the virtual run() function for that object.
			* Upon completing, decrements thread count and resets thread m_threadID.
			*
			* If the object is deallocated immediately after calling start(),
			* such as an object created on the stack that has since gone
			* out-of-scope, this will obviously fail.
			*
			* This must be static in order to work with _beginthread / _beginthreadex / ...
			*/
			static uint32_t __stdcall routine(void * p_pThread);


		protected:
			/** \brief Alloc and init threaded data. (pure virtual) */
			virtual void initThreadedData(void) = 0;
			/** \brief Release and delete threaded data. (pure virtual) */
			virtual void releaseThreadedData(void) = 0;

			/** \brief Run is the main loop for this thread (\sa start()). (pure virtual) */
			virtual void run(void) = 0;


		public:
			/** \brief Wait for thread execution (if any) to complete. */
			bool join(void);
			/** \brief Signal the thread to stop and wait for execution to complete. */
			void stop(void);
		private:
			/** \brief Detach thread, close its handle and resets the thread ID. */
			void detach(void);


			///////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////

		private:
			/** \brief Set thread started state. */
			virtual void setStarted(void);
			/** \brief Reset thread started state. */
			virtual void resetStarted(void);


		public:
			/**
			* \brief Get thread priority.
			*
			* \param p_priority target reference to stock thread priority value.
			* \return true if successful, false otherwise.
			*/
			bool getPriority( priorities & p_priority );
			/**
			* \brief Set the m_priority for the native thread if supported by the system.
			*
			* \param p_priority target priority as priorities enum.
			* \return false if thread is already running.
			*/
			bool setPriority( priorities p_priority );


		protected:
			/**
			* \brief get thread running state.
			* \return true if thread is running, false otherwise.
			*/
			bool running( void );
			/**
			* \brief get thread started state.
			* \return true if thread started, false otherwise.
			*/
			bool started( void );


		public:
			/** \brief Get wait time in milliseconds between each run iteration. */
			const uint32_t getRunWait(void) const;
			/** 
			* \brief Set wait time in milliseconds between each run iteration.
			* \return false if thread is already running.
			*/
			bool setRunWait(uint32_t p_wait);


		}; // class Thread

	} // namespace thr

} // namespace eve


//=================================================================================================
inline const uint32_t eve::thr::Thread::getRunWait(void) const { return m_runWait; }

#endif // __EVE_THREADING_THREAD_H__

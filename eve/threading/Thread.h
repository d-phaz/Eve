
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

#include <thread>

#ifndef __EVE_CORE_INCLUDES_H__
#include "Eve/core/Includes.h"
#endif

namespace eve
{
	namespace threading
	{
		/**
		* \class threading::Thread
		*
		* \brief Abstract base thread class containing init and release abstract methods,
		* each thread must inherit from this class to properly alloc/init and release/free its members.
		*
		* \note extends memory::Pointer
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
	
		protected:
			//std::thread *		m_hThread;
			//std::thread::id		m_threadID;
			HANDLE				m_hThread;
			DWORD				m_threadID;

			HANDLE				m_hShutdownEvent;
			HANDLE				m_StartEvent;
			
			uint32_t			m_runWait;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Thread)
			EVE_PROTECT_DESTRUCTOR(Thread)


		protected:
			/** \brief Class constructor. */
			Thread(void);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** 
			* \brief Release and delete class members. (pure virtual) 
			* Stop this object's thread execution (if any) immediately
			*/
			virtual void release(void) override;


		protected:
			/** \brief In thread initialization function. (pure virtual) */
			virtual void inThreadInit(void) = 0;
			/** \brief In thread release function. (pure virtual) */
			virtual void inThreadRelease(void) = 0;


		public:
			/**
			* \brief Run is the main loop for this thread. (pure virtual)
			* Usually this is called by Start(), but may be called directly for single-threaded applications.
			*/
			virtual void run(void) = 0;


			/**
			* \brief Start the object's thread execution. Increments thread
			* count, spawns new thread, and stores thread m_threadID.
			*
			* \param p_priority thread desired priority.
			*/
			void start(priorities p_priority=InheritPriority);
			/**
			* \brief Stop the thread. 
			* Decrements thread count and resets the thread m_threadID.
			*/
			void stop( void );


		protected:
			/** \brief Terminate thread. */
			void terminate(void);
			/** \brief Wait for thread execution (if any) to complete. */
			bool complete(void);
			/** \brief Close thread. */
			void close(void);


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
			static uint32_t __stdcall run_wrapper(void * p_pThread);


			///////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////

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
			* \return true if successful, false otherwise.
			*/
			bool setPriority( priorities p_priority );


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


		protected:
			/** \brief Set thread started state. */
			virtual void setStarted ( void );
			/** \brief Reset thread started state. */
			virtual void resetStarted ( void );

		}; // class Thread

	} // namespace threading

} // namespace eve

#endif // __EVE_THREADING_THREAD_H__

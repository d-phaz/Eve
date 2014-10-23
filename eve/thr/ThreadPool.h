
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
#ifndef __EVE_THREADING_THREAD_POOL_H__
#define __EVE_THREADING_THREAD_POOL_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif


namespace eve { namespace thr	{ class SpinLock;		} }
namespace eve { namespace thr	{ class ThreadedWorkIO; } }
namespace eve { namespace thr	{ class Worker;			} }

namespace eve { namespace thr	{ template<class T> class TPCQueue; } }


namespace eve
{
	namespace thr
	{

		/**
		* \class eve::thr::ThreadPool
		*
		* \brief Thread pool using threaded works (tasks).
		* Create thread and schedule task.
		*
		* \note extends mem::Pointer
		*/
		class ThreadPool final
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;
			friend class eve::thr::ThreadedWorkIO;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:

		private:
			size_t											m_numThread;			//!< Contained threads amount.

			std::vector<eve::thr::ThreadedWorkIO *> *		m_pThreadsActive;		//!< Active contained threads.
			std::vector<eve::thr::ThreadedWorkIO *> *		m_pThreadsSleeping;		//!< Sleeping contained threads.

			eve::thr::SpinLock *							m_pFence;				//!< Spin lock protecting thread queues.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(ThreadPool);
			EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(ThreadPool);

		public:
			/**
			* \brief Create and return new pointer.
			* \param p_numThread amount of created thread(s).
			*/
			static ThreadPool * create_ptr(size_t p_numThread);


		private:
			/** \brief Class constructor.	*/
			explicit ThreadPool(size_t p_numThread);


		private:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		private:
			/** \brief Add target thread to active thread queue. Called by thread itself. */
			void threadSetActive(eve::thr::ThreadedWorkIO * p_pThread);
			/** \brief Add target thread to sleeping thread queue. Called by thread itself. */
			void threadSetSleeping(eve::thr::ThreadedWorkIO * p_pThread);


		public:
			/** \brief Add worker and return immediately. */
			void addWorker(eve::thr::Worker * p_pWorker);
			/** \brief Add worker so that it will be the next one used and return immediately. */
			void addPriorityWorker(eve::thr::Worker * p_pWorker);

		}; // class ThreadPool

	} // namespace thr

} // namespace eve

#endif // __EVE_THREADING_THREAD_POOL_H__


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
#ifndef __EVE_THREADING_PRODUCER_CONSUMER_QUEUE_H__
#define __EVE_THREADING_PRODUCER_CONSUMER_QUEUE_H__

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


namespace eve
{
	namespace thr
	{

		/**
		* \class eve::thr::TPCQueue
		*
		* \brief Base producer/consumer queue template.
		* Stored elements are template type pointers.
		* This class does not take ownership of elements, they are not deleted when class is.
		* Use Windows threading API event to manage queue access.
		*
		* \note extends mem::Pointer
		*/
		template<class T>
		class TPCQueue
			: public eve::mem::Pointer
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			std::deque<T*> *					m_pQueue;		//!< Standard library deque.
			void *								m_pEvent;		//!< Queue access management event.
			eve::thr::SpinLock *				m_pFence;		//!< Spin lock protecting queue.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(TPCQueue);
			EVE_PUBLIC_DESTRUCTOR(TPCQueue);

		public:
			/** \brief Class constructor. */
			explicit TPCQueue(void);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Insert p_data in queue, if p_addToFront is true p_data will be inserted in front (first position). */
			void enqueue(T * p_data, bool p_addToFront = false);
			/** \brief Retrieve first element in queue, element is then released from queue. */
			T * dequeue(void);

		}; // class TPCQueue

	} // namespace thr

} // namespace eve

//=================================================================================================
template<class T>
eve::thr::TPCQueue<T>::TPCQueue(void)
	// Inheritance
	: eve::mem::Pointer()
	// Members init
	, m_pQueue(nullptr)
	, m_pEvent(nullptr)
	, m_pFence(nullptr)
{}



//=================================================================================================
template<class T>
void eve::thr::TPCQueue<T>::init(void)
{
	m_pQueue = new std::deque<T*>();
	m_pEvent = ::CreateEventW(NULL, TRUE, FALSE, NULL);
	m_pFence = EVE_CREATE_PTR(eve::thr::SpinLock);
}

//=================================================================================================
template<class T>
void eve::thr::TPCQueue<T>::release(void)
{
	EVE_RELEASE_PTR(m_pFence);
	::CloseHandle(m_pEvent);
	EVE_RELEASE_PTR_CPP(m_pQueue);
}



//=================================================================================================
template<class T>
void eve::thr::TPCQueue<T>::enqueue(T * p_data, bool p_addToFront)
{
	m_pFence->lock();

	if (p_addToFront) {
		m_pQueue->push_front(p_data);
	}
	else {
		m_pQueue->push_back(p_data);
	}

	if (::SetEvent(m_pEvent) == 0) {
		EVE_LOG_ERROR("Unable to dispatch thread event, SetEvent() failed %s", eve::mess::get_error_msg().c_str());
	}

	m_pFence->unlock();
}

//=================================================================================================
template<class T>
T * eve::thr::TPCQueue<T>::dequeue(void)
{
	T * ptr = nullptr;

	if (::WaitForSingleObjectEx(m_pEvent, 1000, TRUE) == WAIT_OBJECT_0)
	{
		m_pFence->lock();

		if (!m_pQueue->empty())
		{
			::ResetEvent(m_pEvent);
			ptr = m_pQueue->front();
			m_pQueue->pop_front();
		}

		m_pFence->unlock();
	}

	return ptr;
}

#endif // __EVE_THREADING_PRODUCER_CONSUMER_QUEUE_H__


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
#ifndef __EVE_EVT_TQUEUE_H__
#define __EVE_EVT_TQUEUE_H__


#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 

namespace eve
{
	namespace evt
	{
		/**
		* \class eve::evt::TQueue
		*
		* \brief FIFO event queue using back and front buffering.
		* TEvt template type is the event type of this queue.
		* Events are objects and should NOT be pointers.
		*
		* \note extends mem::Pointer
		*/
		template <class TEvt>
		class TQueue
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;


		protected:
			std::deque<TEvt> *	            m_pQueueBack;			//!< Back event queue.
			std::deque<TEvt> *	            m_pQueueFront;			//!< Front event queue.
			std::deque<TEvt> *	            m_pQueueRef;			//!< Reference event queue used for swapping.

			eve::thr::SpinLock *			m_pFence;				//!< Memory fence as spin lock.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(TQueue);
			EVE_PROTECT_DESTRUCTOR(TQueue);

		public:
			/** \brief Class constructor. */
			TQueue(void);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Add event to back queue. */
			void addEvent(TEvt & p_evt);
			/** Get front queue front event. */
			TEvt & getEvent(void);
			/** \brief Get front queue empty state. */
			bool empty(void);


			/** \brief Swap queues. */
			void swap(void);


		public:
			/** \brief Copy content from a target \p_queue. */
			void copy(const TQueue<TEvt> & p_ref);

		}; // class TEvent

	} // namespace evt

} // namespace eve


//=================================================================================================
template <class TEvt>
eve::evt::TQueue<TEvt>::TQueue(void)
	// Inheritance
	: eve::mem::Pointer()
	// Members init
	, m_pQueueBack(nullptr)
	, m_pQueueFront(nullptr)
	, m_pQueueRef(nullptr)
	, m_pFence(nullptr)
{}



//=================================================================================================
template <class TEvt>
inline void eve::evt::TQueue<TEvt>::init(void)
{
	m_pQueueBack	= new std::deque<TEvt>(200);
	m_pQueueFront	= new std::deque<TEvt>(200);
	m_pFence		= EVE_CREATE_PTR(eve::thr::SpinLock);
}

//=================================================================================================
template <class TEvt>
inline void eve::evt::TQueue<TEvt>::release(void)
{
	EVE_RELEASE_PTR(m_pFence);

	m_pQueueFront->clear();
	EVE_RELEASE_PTR_CPP(m_pQueueFront);

	m_pQueueBack->clear();
	EVE_RELEASE_PTR_CPP(m_pQueueBack);
}



//=================================================================================================
template <class TEvt>
inline void eve::evt::TQueue<TEvt>::addEvent(TEvt & p_evt)
{
	m_pQueueBack->push_back(p_evt);
}

//=================================================================================================
template <class TEvt>
inline TEvt & eve::evt::TQueue<TEvt>::getEvent(void)
{
	TEvt ret = m_pQueueFront->front();
	m_pQueueFront->pop_front();

	return ret;
}

//=================================================================================================
template <class TEvt>
inline bool eve::evt::TQueue<TEvt>::empty(void)
{
	return m_pQueueFront->empty();
}



//=================================================================================================
template <class TEvt>
inline void eve::evt::TQueue<TEvt>::swap(void)
{
	m_pFence->lock();

	m_pQueueRef		= m_pQueueBack;
	m_pQueueBack	= m_pQueueFront;
	m_pQueueFront	= m_pQueueRef;

	m_pFence->unlock();
}



//=================================================================================================
template <class TEvt>
inline void eve::evt::TQueue<TEvt>::copy(const TQueue<TEvt> & p_ref)
{
	m_pFence->lock();

	for (auto & it : (*p_ref.m_pQueueBack))
	{
		m_pQueueBack->push_back(*it);
	}

	for (auto & it : (*p_ref.m_pQueueFront))
	{
		m_pQueueFront->push_back(*it);
	}

	m_pFence->unlock();
}

#endif // __EVE_EVT_TQUEUE_H__

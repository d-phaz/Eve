
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
#ifndef __EVE_THREADING_TWORKER_H__
#define __EVE_THREADING_TWORKER_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_EVT_INCLUDES_H__
#include "eve/evt/Includes.h"
#endif


namespace eve
{
	namespace threading
	{

		/**
		* \class eve::threading::TWorker
		*
		* \brief Abstract base thread worker class.
		* Workers are the ONLY thread level stored data and should be the basis for any engine.
		* TEvt template type is the event type consumed by the worker.
		*
		* \note extends memory::Pointer
		*/
		template<class TEvt>
		class TWorker
			: public eve::memory::Pointer
		{

			friend class eve::memory::Pointer;


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			eve::evt::TQueue<TEvt> *		m_pEventQUeue;		//!< FIFO event queue.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(TWorker);
			EVE_PROTECT_DESTRUCTOR(TWorker);

		protected:
			/** Class constructor. */
			TWorker(void);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/**
			* \brief Event received handler.
			* Event is queued in the back queue while front queue consumes events.
			*/
			void cb_evtReceived(TEvt & p_evt);


		public:
			/** \brief Consume front queue events. (pure virtual) */
			virtual void consumeEvents(void) = 0;


		public:
			/** Main schedule work method. (pure virtual) */
			virtual void work(void) = 0;

		}; // Class TWorker

	} // namespace threading

} // namespace eve


//=================================================================================================
template<class TEvt>
eve::threading::TWorker<TEvt>::TWorker(void)
	// Inheritance
	: eve::memory::Pointer()
	// Members init
	, m_pEventQUeue(nullptr)
{}



//=================================================================================================
template<class TEvt>
void eve::threading::TWorker<TEvt>::init(void)
{
	m_pEventQUeue = EVE_CREATE_PTR(eve::evt::TQueue<TEvt>);
}

//=================================================================================================
template<class TEvt>
void eve::threading::TWorker<TEvt>::release(void)
{
	EVE_RELEASE_PTR(m_pEventQUeue);
}



//=================================================================================================
template<class TEvt>
void eve::threading::TWorker<TEvt>::cb_evtReceived(TEvt & p_evt)
{
	m_pEventQUeue->addEvent(p_evt);
}

#endif // __EVE_THREADING_TWORKER_H__

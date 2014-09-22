
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
#ifndef __EVE_EVT_TABSTRACT_EVENT_H__
#define __EVE_EVT_TABSTRACT_EVENT_H__


#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_THREADING_SCOPED_FENCE_H__
#include "eve/thr/ScopedFence.h"
#endif

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 

#ifndef __EVE_EVT_TDELEGATE_H__
#include "eve/evt/TDelegate.h"
#endif

namespace eve
{
	namespace evt
	{
		/**
		* \class eve::evt::TEventAbstract
		*
		* \brief TEventAbstract is the base class of all events. 
		*
		* Events can be used to send information to a set of delegates
		* which are registered with the event. The type of the data is specified with
		* the template parameter TArgs. The TStrategy parameter must be a subclass 
		* of NotificationStrategy. The parameter TDelegate can either be a subclass of AbstractDelegate
		* or of AbstractPriorityDelegate. 
		*
		* Event works with a delegate. A delegate comes with an attached priority value
		* and allows one object to register for one priority value one or more delegates.
		*
		* Firing the event is done by calling the event's notify().
		*/
		template <class TArgs, class TStrategy, class TDelegate>
		class TEventAbstract
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			TStrategy							m_strategy;  /// The strategy used to notify observers.
			bool								m_bEnabled;   /// Stores if an event is enabled. Notifies on disabled events have no effect
															/// but it is possible to change the observers.
			mutable eve::thr::SpinLock *		m_pFence;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////
			
			EVE_DISABLE_COPY(TEventAbstract);

		public:
			/** \brief Class constructor. */
			TEventAbstract(void);
			/** \brief Copy constructor. */
			TEventAbstract(const TStrategy& strat);
			/** \brief Class destructor. */
			virtual ~TEventAbstract(void);

			/** \brief Adds a delegate to the event. */
			void operator += (const TDelegate& aDelegate);

			/** \brief Removes a delegate from the event. If the delegate is not found, this function does nothing. */
			void operator -= (const TDelegate& aDelegate);

			/**
			* \brief Sends a notification to all registered delegates.
			* The order is determined by the TStrategy.
			* This method is blocking.
			* While executing, the list of delegates may be modified.
			* These changes don't influence the current active notifications but are activated with the next notify.
			* If a delegate is removed during a notify(),
			* the delegate will no longer be invoked (unless it has already been invoked prior to removal).
			* If one of the delegates throws an exception, the notify method is immediately aborted and the exception is propagated to the caller.
			*/
			void notify(const void* pSender, TArgs& args);

			/** \brief  Enables the event. */
			void enable(void);

			/** \brief Disables the event. notify() will be ignored but adding/removing delegates is still allowed. */
			void disable(void);

			/** \brief Get event enable state. */
			bool isEnabled(void) const;

			/** \brief Removes all delegates. */
			void clear(void);

			/** \brief Checks if any delegates are registered. */
			bool empty(void) const;
		};



		/**
		* \class eve::evt::TEventAbstract (specialized)
		*
		* \brief TEventAbstract is the base class of all events.
		*
		* Events can be used to send information to a set of delegates
		* which are registered with the event. The type of the data is specified with
		* the template parameter TArgs. The TStrategy parameter must be a subclass
		* of NotificationStrategy. The parameter TDelegate can either be a subclass of AbstractDelegate
		* or of AbstractPriorityDelegate.
		*
		* Event works with a delegate. A delegate comes with an attached priority value
		* and allows one object to register for one priority value one or more delegates.
		*
		* Firing the event is done by calling the event's notify().
		*/
		template <class TStrategy, class TDelegate>
		class TEventAbstract<void, TStrategy, TDelegate>
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			TStrategy							m_strategy;		//!< The strategy used to notify observers.
			bool								m_bEnabled;		//!< Stores if an event is enabled. Notifies on disabled events have no effect but it is possible to change the observers.
			mutable eve::thr::SpinLock *		m_pFence;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(TEventAbstract);

		public:
			/** \brief Class constructor. */
			TEventAbstract(void);
			/** \brief Copy constructor. */
			TEventAbstract(const TStrategy& strat);
			/** \brief Class destructor. */
			virtual ~TEventAbstract(void);

			/** \brief Adds a delegate to the event. */
			void operator += (const TDelegate & aDelegate);

			/** \brief Removes a delegate from the event. If the delegate is not found, this function does nothing. */
			void operator -= (const TDelegate & aDelegate);

			/** 
			* \brief Sends a notification to all registered delegates. 
			* The order is determined by the TStrategy. 
			* This method is blocking. 
			* While executing, the list of delegates may be modified. 
			* These changes don't influence the current active notifications but are activated with the next notify. 
			* If a delegate is removed during a notify(), 
			* the delegate will no longer be invoked (unless it has already been invoked prior to removal). 
			* If one of the delegates throws an exception, the notify method is immediately aborted and the exception is propagated to the caller.
			*/
			void notify(const void * pSender);

			/** \brief  Enables the event. */
			void enable(void);

			/** \brief Disables the event. notify() will be ignored but adding/removing delegates is still allowed. */
			void disable(void);

			/** \brief Get event enable state. */
			bool isEnabled(void) const;

			/** \brief Removes all delegates. */
			void clear(void);

			/** \brief Checks if any delegates are registered. */
			bool empty(void) const;

		}; // class TEventAbstract

	} // namespace evt

} // namespace eve


//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::TEventAbstract(void) 
	: m_strategy()
	, m_bEnabled(true)
{
	m_pFence = EVE_CREATE_PTR(eve::thr::SpinLock);
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::TEventAbstract(const TStrategy& strat) 
	: m_strategy(strat)
	, m_bEnabled(true)
{
	m_pFence = EVE_CREATE_PTR(eve::thr::SpinLock);
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::~TEventAbstract(void)
{
	EVE_RELEASE_PTR(m_pFence);
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::operator += (const TDelegate& aDelegate)
{
	m_pFence->lock();
	m_strategy.add(aDelegate);
	m_pFence->unlock();
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::operator -= (const TDelegate& aDelegate)
{
	m_pFence->lock();
	m_strategy.remove(aDelegate);
	m_pFence->unlock();
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::notify(const void* pSender, TArgs& args)
{
	eve::thr::ScopedFence<eve::thr::SpinLock> lock(m_pFence);

	if (!m_bEnabled) return;

	// copy should be faster and safer than blocking until execution ends
	TStrategy strategy(m_strategy);
	lock.unlock();
	strategy.notify(pSender, args);
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::enable(void)
{
	m_pFence->lock();
	m_bEnabled = true;
	m_pFence->unlock();
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::disable(void)
{
	m_pFence->lock();
	m_bEnabled = false;
	m_pFence->unlock();
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
bool eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::isEnabled(void) const
{
	eve::thr::ScopedFence<eve::thr::SpinLock> lock(m_pFence);
	return m_bEnabled;
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::clear(void)
{
	m_pFence->lock();
	m_strategy.clear();
	m_pFence->unlock();
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
bool eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::empty(void) const
{
	eve::thr::ScopedFence<eve::thr::SpinLock> lock(m_pFence);
	return m_strategy.empty();
}


//-----------------------------------------------


//=================================================================================================
template <class TStrategy, class TDelegate>
eve::evt::TEventAbstract<void, TStrategy, TDelegate>::TEventAbstract(void) 
	: m_strategy()
	, m_bEnabled(true)
{
	m_pFence = EVE_CREATE_PTR(eve::thr::SpinLock);
}

//=================================================================================================
template <class TStrategy, class TDelegate>
eve::evt::TEventAbstract<void, TStrategy, TDelegate>::TEventAbstract(const TStrategy& strat)
	: m_strategy(strat)
	, m_bEnabled(true)
{
	m_pFence = EVE_CREATE_PTR(eve::thr::SpinLock);
}

//=================================================================================================
template <class TStrategy, class TDelegate>
eve::evt::TEventAbstract<void, TStrategy, TDelegate>::~TEventAbstract(void)
{
	EVE_RELEASE_PTR(m_pFence);
}

//=================================================================================================
template <class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<void, TStrategy, TDelegate>::operator += (const TDelegate& aDelegate)
{
	m_pFence->lock();
	m_strategy.add(aDelegate);
	m_pFence->unlock();
}

//=================================================================================================
template <class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<void, TStrategy, TDelegate>::operator -= (const TDelegate& aDelegate)
{
	m_pFence->lock();
	m_strategy.remove(aDelegate);
	m_pFence->unlock();
}

//=================================================================================================
template <class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<void, TStrategy, TDelegate>::notify(const void* pSender)
{
	eve::thr::ScopedFence<eve::thr::SpinLock> lock(m_pFence);

	if (!m_bEnabled) return;

	// copy should be faster and safer than blocking until execution ends
	TStrategy strategy(m_strategy);
	lock.unlock();
	strategy.notify(pSender);
}

//=================================================================================================
template <class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<void, TStrategy, TDelegate>::enable(void)
{
	m_pFence->lock();
	m_bEnabled = true;
	m_pFence->unlock();
}

//=================================================================================================
template <class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<void, TStrategy, TDelegate>::disable(void)
{
	m_pFence->lock();
	m_bEnabled = false;
	m_pFence->unlock();
}

//=================================================================================================
template <class TStrategy, class TDelegate>
bool eve::evt::TEventAbstract<void, TStrategy, TDelegate>::isEnabled(void) const
{
	eve::thr::ScopedFence<eve::thr::SpinLock> lock(m_pFence);
	return m_bEnabled;
}

//=================================================================================================
template <class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<void, TStrategy, TDelegate>::clear(void)
{
	m_pFence->lock();
	m_strategy.clear();
	m_pFence->unlock();
}

//=================================================================================================
template <class TStrategy, class TDelegate>
bool eve::evt::TEventAbstract<void, TStrategy, TDelegate>::empty(void) const
{
	eve::thr::ScopedFence<eve::thr::SpinLock> lock(m_pFence);
	return m_strategy.empty();
}

#endif // __EVE_EVT_TABSTRACT_EVENT_H__

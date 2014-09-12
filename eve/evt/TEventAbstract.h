
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
#include "eve/threading/ScopedFence.h"
#endif

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/threading/SpinLock.h"
#endif 

#ifndef __EVE_EVT_TDELEGATE_H__
#include "eve/evt/TDelegate.h"
#endif

namespace eve
{
	namespace evt
	{
		/// An TEventAbstract is the base class of all events. 
		/// It works similar to the way C# handles notifications (aka events in C#).
		///
		/// Events can be used to send information to a set of delegates
		/// which are registered with the event. The type of the data is specified with
		/// the template parameter TArgs. The TStrategy parameter must be a subclass 
		/// of NotificationStrategy. The parameter TDelegate can either be a subclass of AbstractDelegate
		/// or of AbstractPriorityDelegate. 
		///
		/// Note that TEventAbstract should never be used directly. One ought to use
		/// one of its subclasses which set the TStrategy and TDelegate template parameters
		/// to fixed values. For most use-cases the BasicEvent template will be sufficient:
		///
		///     #include "Poco/BasicEvent.h"
		///     #include "Poco/Delegate.h"
		///
		/// Note that as of release 1.4.2, the behavior of BasicEvent equals that of FIFOEvent,
		/// so the FIFOEvent class is no longer necessary and provided for backwards compatibility
		/// only.
		///
		/// BasicEvent works with a standard delegate. They allow one object to register
		/// onr or more delegates with an event. In contrast, a PriorityDelegate comes with an attached priority value
		/// and allows one object to register for one priority value one or more delegates. Note that PriorityDelegates
		/// only work with PriorityEvents:
		///
		///     #include "Poco/PriorityEvent.h"
		///     #include "Poco/PriorityDelegate.h"
		///
		/// Use events by adding them as public members to the object which is throwing notifications:
		///
		///     class MyData
		///     {
		///     public:
		///         Poco::BasicEvent<int> dataChanged;
		///         
		///         MyData();
		///         ...
		///         void setData(int i);
		///         ...
		///     private:
		///         int _data;
		///     };
		///
		/// Firing the event is done by calling the event's notify() method:
		///
		///     void MyData::setData(int i)
		///     {
		///         this->_data = i;
		///         dataChanged.notify(this, this->_data);
		///     }
		///
		/// Alternatively, instead of notify(), operator () can be used.
		///
		///     void MyData::setData(int i)
		///     {
		///         this->_data = i;
		///         dataChanged(this, this->_data);
		///     }
		///
		/// Note that operator (), notify() and notifyAsync() do not catch exceptions, i.e. in case a  
		/// delegate throws an exception, notifying is immediately aborted and the exception is propagated
		/// back to the caller.
		///
		/// Delegates can register methods at the event. In the case of a BasicEvent
		/// the Delegate template is used, in case of an PriorityEvent a PriorityDelegate is used.
		/// Mixing of delegates, e.g. using a PriorityDelegate with a BasicEvent is not allowed and
		/// can lead to compile-time and/or run-time errors. The standalone delegate() functions
		/// can be used to construct Delegate objects.
		///
		/// Events require the observers to have one of the following method signatures:
		///
		///     void onEvent(const void* pSender, TArgs& args);
		///     void onEvent(TArgs& args);
		///     static void onEvent(const void* pSender, TArgs& args);
		///     static void onEvent(void* pSender, TArgs& args);
		///     static void onEvent(TArgs& args);
		///
		/// For performance reasons arguments are always sent by reference. This also allows observers
		/// to modify the event argument. To prevent that, use <[const TArg]> as template
		/// parameter. A non-conformant method signature leads to compile errors.
		///
		/// Assuming that the observer meets the method signature requirement, it can register
		/// this method with the += operator:
		///
		///     class MyController
		///     {
		///     protected:
		///         MyData _data;
		///         
		///         void onDataChanged(void* pSender, int& data);
		///         ...
		///     };
		///         
		///     MyController::MyController()
		///     {
		///         _data.dataChanged += delegate(this, &MyController::onDataChanged);
		///     }
		///
		/// In some cases it might be desirable to work with automatically expiring registrations. Simply add
		/// to delegate as 3rd parameter a expireValue (in milliseconds):
		///
		///     _data.dataChanged += delegate(this, &MyController::onDataChanged, 1000);
		///
		/// This will add a delegate to the event which will automatically be removed in 1000 millisecs.
		///
		/// Unregistering happens via the -= operator. Forgetting to unregister a method will lead to
		/// segmentation faults later, when one tries to send a notify to a no longer existing object.
		///
		///     MyController::~MyController()
		///     {
		///         _data.dataChanged -= delegate(this, &MyController::onDataChanged);
		///     }
		///
		/// Working with PriorityDelegate's as similar to working with BasicEvent.
		/// Instead of delegate(), the priorityDelegate() function must be used
		/// to create the PriorityDelegate.
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
			mutable eve::threading::SpinLock *	m_pFence;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////
			
			EVE_DISABLE_COPY(TEventAbstract);

		public:
			TEventAbstract(void);

			TEventAbstract(const TStrategy& strat);

			virtual ~TEventAbstract(void);

			/// Adds a delegate to the event. 
			///
			/// Exact behavior is determined by the TStrategy.
			void operator += (const TDelegate& aDelegate);

			/// Removes a delegate from the event.
			///
			/// If the delegate is not found, this function does nothing.
			void operator -= (const TDelegate& aDelegate);

			/// Shortcut for notify(pSender, args);
			void operator () (const void* pSender, TArgs& args);

			/// Shortcut for notify(args).
			void operator () (TArgs& args);

			/// Sends a notification to all registered delegates. The order is 
			/// determined by the TStrategy. This method is blocking. While executing,
			/// the list of delegates may be modified. These changes don't
			/// influence the current active notifications but are activated with
			/// the next notify. If a delegate is removed during a notify(), the
			/// delegate will no longer be invoked (unless it has already been
			/// invoked prior to removal). If one of the delegates throws an exception, 
			/// the notify method is immediately aborted and the exception is propagated
			/// to the caller.
			void notify(const void* pSender, TArgs& args);

			/// Enables the event.
			void enable(void);

			/// Disables the event. notify and notifyAsnyc will be ignored,
			/// but adding/removing delegates is still allowed.
			void disable(void);

			bool isEnabled(void) const;

			/// Removes all delegates.
			void clear(void);

			/// Checks if any delegates are registered at the delegate.
			bool empty(void) const;
		};



		/// An TEventAbstract is the base class of all events. 
		/// It works similar to the way C# handles notifications (aka events in C#).
		///
		/// Events can be used to send information to a set of delegates
		/// which are registered with the event. The type of the data is specified with
		/// the template parameter TArgs. The TStrategy parameter must be a subclass 
		/// of NotificationStrategy. The parameter TDelegate can either be a subclass of AbstractDelegate
		/// or of AbstractPriorityDelegate. 
		///
		/// Note that TEventAbstract should never be used directly. One ought to use
		/// one of its subclasses which set the TStrategy and TDelegate template parameters
		/// to fixed values. For most use-cases the BasicEvent template will be sufficient:
		///
		///     #include "Poco/BasicEvent.h"
		///     #include "Poco/Delegate.h"
		///
		/// Note that as of release 1.4.2, the behavior of BasicEvent equals that of FIFOEvent,
		/// so the FIFOEvent class is no longer necessary and provided for backwards compatibility
		/// only.
		///
		/// BasicEvent works with a standard delegate. They allow one object to register
		/// onr or more delegates with an event. In contrast, a PriorityDelegate comes with an attached priority value
		/// and allows one object to register for one priority value one or more delegates. Note that PriorityDelegates
		/// only work with PriorityEvents:
		///
		///     #include "Poco/PriorityEvent.h"
		///     #include "Poco/PriorityDelegate.h"
		///
		/// Use events by adding them as public members to the object which is throwing notifications:
		///
		///     class MyData
		///     {
		///     public:
		///         Poco::BasicEvent<int> dataChanged;
		///         
		///         MyData();
		///         ...
		///         void setData(int i);
		///         ...
		///     private:
		///         int _data;
		///     };
		///
		/// Firing the event is done either by calling the event's notify() or notifyAsync() method:
		///
		///     void MyData::setData(int i)
		///     {
		///         this->_data = i;
		///         dataChanged.notify(this, this->_data);
		///     }
		///
		/// Alternatively, instead of notify(), operator () can be used.
		///
		///     void MyData::setData(int i)
		///     {
		///         this->_data = i;
		///         dataChanged(this, this->_data);
		///     }
		///
		/// Note that operator (), notify() and notifyAsync() do not catch exceptions, i.e. in case a  
		/// delegate throws an exception, notifying is immediately aborted and the exception is propagated
		/// back to the caller.
		///
		/// Delegates can register methods at the event. In the case of a BasicEvent
		/// the Delegate template is used, in case of an PriorityEvent a PriorityDelegate is used.
		/// Mixing of delegates, e.g. using a PriorityDelegate with a BasicEvent is not allowed and
		/// can lead to compile-time and/or run-time errors. The standalone delegate() functions
		/// can be used to construct Delegate objects.
		///
		/// Events require the observers to have one of the following method signatures:
		///
		///     void onEvent(const void* pSender, TArgs& args);
		///     void onEvent(TArgs& args);
		///     static void onEvent(const void* pSender, TArgs& args);
		///     static void onEvent(void* pSender, TArgs& args);
		///     static void onEvent(TArgs& args);
		///
		/// For performance reasons arguments are always sent by reference. This also allows observers
		/// to modify the event argument. To prevent that, use <[const TArg]> as template
		/// parameter. A non-conformant method signature leads to compile errors.
		///
		/// Assuming that the observer meets the method signature requirement, it can register
		/// this method with the += operator:
		///
		///     class MyController
		///     {
		///     protected:
		///         MyData _data;
		///         
		///         void onDataChanged(void* pSender, int& data);
		///         ...
		///     };
		///         
		///     MyController::MyController()
		///     {
		///         _data.dataChanged += delegate(this, &MyController::onDataChanged);
		///     }
		///
		/// In some cases it might be desirable to work with automatically expiring registrations. Simply add
		/// to delegate as 3rd parameter a expireValue (in milliseconds):
		///
		///     _data.dataChanged += delegate(this, &MyController::onDataChanged, 1000);
		///
		/// This will add a delegate to the event which will automatically be removed in 1000 millisecs.
		///
		/// Unregistering happens via the -= operator. Forgetting to unregister a method will lead to
		/// segmentation faults later, when one tries to send a notify to a no longer existing object.
		///
		///     MyController::~MyController()
		///     {
		///         _data.dataChanged -= delegate(this, &MyController::onDataChanged);
		///     }
		///
		/// Working with PriorityDelegate's as similar to working with BasicEvent.
		/// Instead of delegate(), the priorityDelegate() function must be used
		/// to create the PriorityDelegate.
		template <class TStrategy, class TDelegate>
		class TEventAbstract<void, TStrategy, TDelegate>
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			TStrategy							m_strategy;		//!< The strategy used to notify observers.
			bool								m_bEnabled;		//!< Stores if an event is enabled. Notifies on disabled events have no effect but it is possible to change the observers.
			mutable eve::threading::SpinLock *	m_pFence;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(TEventAbstract);

		public:
			TEventAbstract(void);

			TEventAbstract(const TStrategy& strat);

			virtual ~TEventAbstract(void);

			/// Adds a delegate to the event. 
			///
			/// Exact behavior is determined by the TStrategy.
			void operator += (const TDelegate& aDelegate);

			/// Removes a delegate from the event.
			///
			/// If the delegate is not found, this function does nothing.
			void operator -= (const TDelegate& aDelegate);

			/// Shortcut for notify(pSender, args);
			void operator () (const void* pSender);

			/// Shortcut for notify(args).
			void operator () ();

			/// Sends a notification to all registered delegates. The order is 
			/// determined by the TStrategy. This method is blocking. While executing,
			/// the list of delegates may be modified. These changes don't
			/// influence the current active notifications but are activated with
			/// the next notify. If a delegate is removed during a notify(), the
			/// delegate will no longer be invoked (unless it has already been
			/// invoked prior to removal). If one of the delegates throws an exception, 
			/// the notify method is immediately aborted and the exception is propagated
			/// to the caller.
			void notify(const void* pSender);

			/// Enables the event.
			void enable(void);

			/// Disables the event. notify and notifyAsnyc will be ignored,
			/// but adding/removing delegates is still allowed.
			void disable(void);

			bool isEnabled(void) const;

			/// Removes all delegates.
			void clear(void);

			/// Checks if any delegates are registered at the delegate.
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
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::TEventAbstract(const TStrategy& strat) 
	: m_strategy(strat)
	, m_bEnabled(true)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
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
void eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::operator () (const void* pSender, TArgs& args)
{
	notify(pSender, args);
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::operator () (TArgs& args)
{
	notify(0, args);
}

//=================================================================================================
template <class TArgs, class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<TArgs, TStrategy, TDelegate>::notify(const void* pSender, TArgs& args)
{
	eve::threading::ScopedFence<eve::threading::SpinLock> lock(m_pFence);

	if (!m_bEnabled) return;

	// thread-safeness: 
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
	eve::threading::ScopedFence<eve::threading::SpinLock> lock(m_pFence);
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
	eve::threading::ScopedFence<eve::threading::SpinLock> lock(m_pFence);
	return m_strategy.empty();
}


//-----------------------------------------------


//=================================================================================================
template <class TStrategy, class TDelegate>
eve::evt::TEventAbstract<void, TStrategy, TDelegate>::TEventAbstract(void) 
	: m_strategy()
	, m_bEnabled(true)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TStrategy, class TDelegate>
eve::evt::TEventAbstract<void, TStrategy, TDelegate>::TEventAbstract(const TStrategy& strat)
	: m_strategy(strat)
	, m_bEnabled(true)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
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
void eve::evt::TEventAbstract<void, TStrategy, TDelegate>::operator () (const void* pSender)
{
	notify(pSender);
}

//=================================================================================================
template <class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<void, TStrategy, TDelegate>::operator () ()
{
	notify(0);
}

//=================================================================================================
template <class TStrategy, class TDelegate>
void eve::evt::TEventAbstract<void, TStrategy, TDelegate>::notify(const void* pSender)
{
	eve::threading::ScopedFence<eve::threading::SpinLock> lock(m_pFence);

	if (!m_bEnabled) return;

	// thread-safeness: 
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
	eve::threading::ScopedFence<eve::threading::SpinLock> lock(m_pFence);
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
	eve::threading::ScopedFence<eve::threading::SpinLock> lock(m_pFence);
	return m_strategy.empty();
}

#endif // __EVE_EVT_TABSTRACT_EVENT_H__

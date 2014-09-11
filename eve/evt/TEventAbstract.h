
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


#include <Poco/Foundation.h>
#include <Poco/SharedPtr.h>
#include <Poco/ActiveResult.h>
#include <Poco/ActiveMethod.h>
#include <Poco/Mutex.h>

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
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
		template <class TArgs, class TStrategy, class TDelegate>
		class TEventAbstract
		{
			
			EVE_DISABLE_COPY(TEventAbstract);

		public:
			typedef TArgs Args;

			TEventAbstract() :
				_executeAsync(this, &TEventAbstract::executeAsyncImpl),
				_enabled(true)
			{
			}

			TEventAbstract(const TStrategy& strat) :
				_executeAsync(this, &TEventAbstract::executeAsyncImpl),
				_strategy(strat),
				_enabled(true)
			{
			}

			virtual ~TEventAbstract()
			{
			}

			void operator += (const TDelegate& aDelegate)
				/// Adds a delegate to the event. 
				///
				/// Exact behavior is determined by the TStrategy.
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				_strategy.add(aDelegate);
			}

			void operator -= (const TDelegate& aDelegate)
				/// Removes a delegate from the event.
				///
				/// If the delegate is not found, this function does nothing.
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				_strategy.remove(aDelegate);
			}

			void operator () (const void* pSender, TArgs& args)
				/// Shortcut for notify(pSender, args);
			{
				notify(pSender, args);
			}

			void operator () (TArgs& args)
				/// Shortcut for notify(args).
			{
				notify(0, args);
			}

			void notify(const void* pSender, TArgs& args)
				/// Sends a notification to all registered delegates. The order is 
				/// determined by the TStrategy. This method is blocking. While executing,
				/// the list of delegates may be modified. These changes don't
				/// influence the current active notifications but are activated with
				/// the next notify. If a delegate is removed during a notify(), the
				/// delegate will no longer be invoked (unless it has already been
				/// invoked prior to removal). If one of the delegates throws an exception, 
				/// the notify method is immediately aborted and the exception is propagated
				/// to the caller.
			{
				Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

				if (!_enabled) return;

				// thread-safeness: 
				// copy should be faster and safer than blocking until
				// execution ends
				TStrategy strategy(_strategy);
				lock.unlock();
				strategy.notify(pSender, args);
			}

			/// Sends a notification to all registered delegates. The order is 
			/// determined by the TStrategy. This method is not blocking and will
			/// immediately return. The delegates are invoked in a seperate thread.
			/// Call activeResult.wait() to wait until the notification has ended.
			/// While executing, other objects can change the delegate list. These changes don't
			/// influence the current active notifications but are activated with
			/// the next notify. If a delegate is removed during a notify(), the
			/// delegate will no longer be invoked (unless it has already been
			/// invoked prior to removal). If one of the delegates throws an exception, 
			/// the execution is aborted and the exception is propagated to the caller.
			Poco::ActiveResult<TArgs> notifyAsync(const void* pSender, const TArgs& args)
			{
				NotifyAsyncParams params(pSender, args);
				{
					typename Poco::FastMutex::ScopedLock lock(_mutex);

					// thread-safeness: 
					// copy should be faster and safer than blocking until
					// execution ends
					// make a copy of the strategy here to guarantee that
					// between notifyAsync and the execution of the method no changes can occur

					params.ptrStrat = SharedPtr<TStrategy>(new TStrategy(_strategy));
					params.enabled = _enabled;
				}
				ActiveResult<TArgs> result = _executeAsync(params);
				return result;
			}

			/// Enables the event.
			void enable()
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				_enabled = true;
			}

			/// Disables the event. notify and notifyAsnyc will be ignored,
			/// but adding/removing delegates is still allowed.
			void disable()
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				_enabled = false;
			}

			bool isEnabled() const
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				return _enabled;
			}

			/// Removes all delegates.
			void clear()
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				_strategy.clear();
			}

			/// Checks if any delegates are registered at the delegate.
			bool empty() const
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				return _strategy.empty();
			}

		protected:
			struct NotifyAsyncParams
			{
				Poco::SharedPtr<TStrategy> ptrStrat;
				const void* pSender;
				TArgs       args;
				bool        enabled;

				/// Default constructor reduces the need for TArgs to have an empty constructor, only copy constructor is needed.
				NotifyAsyncParams(const void* pSend, const TArgs& a) :ptrStrat(), pSender(pSend), args(a), enabled(true)
				{
				}
			};

			Poco::ActiveMethod<TArgs, NotifyAsyncParams, TEventAbstract> _executeAsync;

			TArgs executeAsyncImpl(const NotifyAsyncParams& par)
			{
				if (!par.enabled)
				{
					return par.args;
				}

				NotifyAsyncParams params = par;
				TArgs retArgs(params.args);
				params.ptrStrat->notify(params.pSender, retArgs);
				return retArgs;
			}

			TStrategy _strategy; /// The strategy used to notify observers.
			bool      _enabled;  /// Stores if an event is enabled. Notfies on disabled events have no effect
			/// but it is possible to change the observers.
			mutable Poco::FastMutex _mutex;
		};

	} // namespace evt

} // namespace eve



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

			EVE_DISABLE_COPY(TEventAbstract);

		public:
			TEventAbstract() :
				_executeAsync(this, &TEventAbstract::executeAsyncImpl),
				_enabled(true)
			{}

			TEventAbstract(const TStrategy& strat) :
				_executeAsync(this, &TEventAbstract::executeAsyncImpl),
				_strategy(strat),
				_enabled(true)
			{}

			virtual ~TEventAbstract()
			{}

			/// Adds a delegate to the event. 
			///
			/// Exact behavior is determined by the TStrategy.
			void operator += (const TDelegate& aDelegate)
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				_strategy.add(aDelegate);
			}

			/// Removes a delegate from the event.
			///
			/// If the delegate is not found, this function does nothing.
			void operator -= (const TDelegate& aDelegate)
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				_strategy.remove(aDelegate);
			}

			/// Shortcut for notify(pSender, args);
			void operator () (const void* pSender)
			{
				notify(pSender);
			}

			/// Shortcut for notify(args).
			void operator () ()
			{
				notify(0);
			}

			/// Sends a notification to all registered delegates. The order is 
			/// determined by the TStrategy. This method is blocking. While executing,
			/// the list of delegates may be modified. These changes don't
			/// influence the current active notifications but are activated with
			/// the next notify. If a delegate is removed during a notify(), the
			/// delegate will no longer be invoked (unless it has already been
			/// invoked prior to removal). If one of the delegates throws an exception, 
			/// the notify method is immediately aborted and the exception is propagated
			/// to the caller.
			void notify(const void* pSender)
			{
				Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

				if (!_enabled) return;

				// thread-safeness: 
				// copy should be faster and safer than blocking until execution ends
				TStrategy strategy(_strategy);
				lock.unlock();
				strategy.notify(pSender);
			}

			/// Sends a notification to all registered delegates. The order is 
			/// determined by the TStrategy. This method is not blocking and will
			/// immediately return. The delegates are invoked in a seperate thread.
			/// Call activeResult.wait() to wait until the notification has ended.
			/// While executing, other objects can change the delegate list. These changes don't
			/// influence the current active notifications but are activated with
			/// the next notify. If a delegate is removed during a notify(), the
			/// delegate will no longer be invoked (unless it has already been
			/// invoked prior to removal). If one of the delegates throws an exception, 
			/// the execution is aborted and the exception is propagated to the caller.
			Poco::ActiveResult<void> notifyAsync(const void* pSender)
			{
				NotifyAsyncParams params(pSender);
				{
					typename Poco::FastMutex::ScopedLock lock(_mutex);

					// thread-safeness: 
					// copy should be faster and safer than blocking until execution ends.
					// make a copy of the strategy here to guarantee that.
					// between notifyAsync and the execution of the method no changes can occur.

					params.ptrStrat = SharedPtr<TStrategy>(new TStrategy(_strategy));
					params.enabled = _enabled;
				}
				ActiveResult<void> result = _executeAsync(params);
				return result;
			}

			/// Enables the event.
			void enable()
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				_enabled = true;
			}

			/// Disables the event. notify and notifyAsnyc will be ignored,
			/// but adding/removing delegates is still allowed.
			void disable()
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				_enabled = false;
			}

			bool isEnabled() const
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				return _enabled;
			}

			/// Removes all delegates.
			void clear()
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				_strategy.clear();
			}

			/// Checks if any delegates are registered at the delegate.
			bool empty() const
			{
				typename Poco::FastMutex::ScopedLock lock(_mutex);
				return _strategy.empty();
			}

		protected:
			struct NotifyAsyncParams
			{
				Poco::SharedPtr<TStrategy> ptrStrat;
				const void* pSender;
				bool        enabled;

				/// Default constructor reduces the need for TArgs to have an empty constructor, only copy constructor is needed.
				NotifyAsyncParams(const void* pSend) :ptrStrat(), pSender(pSend), enabled(true)
				{
				}
			}; // struct NotifyAsyncParams

			Poco::ActiveMethod<void, NotifyAsyncParams, TEventAbstract> _executeAsync;

			void executeAsyncImpl(const NotifyAsyncParams& par)
			{
				if (!par.enabled)
				{
					return;
				}

				NotifyAsyncParams params = par;
				params.ptrStrat->notify(params.pSender);
				return;
			}

			TStrategy _strategy; //!< The strategy used to notify observers.
			bool      _enabled;  //!< Stores if an event is enabled. Notifies on disabled events have no effect
			/// but it is possible to change the observers.
			mutable Poco::FastMutex _mutex;

		}; // class TEventAbstract

	} // namespace evt

} // namespace eve

#endif // __EVE_EVT_TABSTRACT_EVENT_H__

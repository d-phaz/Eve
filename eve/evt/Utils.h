
#ifndef __EVT_EVENT_H__
#error "EventUtils should not be directly included, please include evt/Event.h"
#endif

#pragma once
#ifndef __EVT_UTILS_H__
#define __EVT_UTILS_H__

#ifdef BUILD_USE_POCO

// External header
#include <cstdint>

// POCO header
#include "Poco/PriorityEvent.h"
#include "Poco/PriorityDelegate.h"

// Evt header
#ifndef __EVT_DELEGATE_H__ 
#include "evt/Delegate.h"
#endif


namespace evt
{

	/** \! Define TEvent as a POCO FIFOEvent
	* to create your own events use: TEvent<argType> myEvent */
	template <typename ArgumentsType>
	class TEvent
		: public Poco::PriorityEvent<ArgumentsType> 
	{
	public:
		TEvent( void )
			: Poco::PriorityEvent<ArgumentsType>()
		{}

		/* \! Allow copy of events, by copying everything except the mutex. */
		TEvent(const TEvent<ArgumentsType> & p_ref)
			: Poco::PriorityEvent<ArgumentsType>()
		{
			p_ref._mutex.lock();
			this->_mutex.lock();
			this->_strategy = p_ref._strategy;
			this->_mutex.unlock();
			p_ref._mutex.unlock();

			this->_enabled = p_ref._enabled;
		}

		TEvent<ArgumentsType> & operator=(const TEvent<ArgumentsType> & p_ref)
		{
			if(&p_ref == this) return *this;

			p_ref._mutex.lock();
			this->_mutex.lock();
			this->_strategy = p_ref._strategy;
			this->_mutex.unlock();
			p_ref._mutex.unlock();

			this->_enabled = p_ref._enabled;
		
			return *this;
		}

	};


	enum EventOrder{
		EVENT_ORDER_BEFORE_APP	=0,
		EVENT_ORDER_APP			=100,
		EVENT_ORDER_AFTER_APP	=200
	};


	///////////////////////////////////////////////////////////////////////////////////////////////
	//		ADD LISTENERS
	///////////////////////////////////////////////////////////////////////////////////////////////

	/** \! Register any method of any class to an event.
	* the method must provide one of the following
	* signatures:
	*     void method(ArgumentsType & p_args)
	*     void method(const void * p_pSender, ArgumentsType &p_args)
	* ie:
	*     add_listener(addon.newIntEvent, this, &Class::method) */

	//=============================================================================================
	template <class EventType, typename ArgumentsType, class ListenerClass>
	static void add_listener( EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, ArgumentsType&), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
		p_event += Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class EventType, typename ArgumentsType, class ListenerClass>
	static void add_listener( EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
		p_event += Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class ListenerClass>
	static void add_listener( evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
		p_event += Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class ListenerClass>
	static void add_listener( evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
		p_event += Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class EventType, typename ArgumentsType, class ListenerClass>
	static void add_listener( EventType & p_event, ListenerClass  * p_pListener, bool (ListenerClass::*listenerMethod)(const void*, ArgumentsType&), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= evt::Delegate<ListenerClass,ArgumentsType,true>(p_pListener, listenerMethod, prio);
		p_event += evt::Delegate<ListenerClass,ArgumentsType,true>(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class EventType, typename ArgumentsType, class ListenerClass>
	static void add_listener( EventType & p_event, ListenerClass  * p_pListener, bool (ListenerClass::*listenerMethod)(ArgumentsType&), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= evt::Delegate<ListenerClass,ArgumentsType,false>(p_pListener, listenerMethod, prio);
		p_event += evt::Delegate<ListenerClass,ArgumentsType,false>(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class ListenerClass>
	static void add_listener( evt::TEvent<void> & p_event, ListenerClass  * p_pListener, bool (ListenerClass::*listenerMethod)(const void*), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= evt::Delegate<ListenerClass,void,true>(p_pListener, listenerMethod, prio);
		p_event += evt::Delegate<ListenerClass,void,true>(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class ListenerClass>
	static void add_listener( evt::TEvent<void> & p_event, ListenerClass  * p_pListener, bool (ListenerClass::*listenerMethod)(), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= evt::Delegate<ListenerClass,void,false>(p_pListener, listenerMethod, prio);
		p_event += evt::Delegate<ListenerClass,void,false>(p_pListener, listenerMethod, prio);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//		REMOVE LISTENERS
	///////////////////////////////////////////////////////////////////////////////////////////////

	/** Unregister any method of any class to an event.
	* the method must provide one the following
	* signatures:
	*     void method(ArgumentsType & p_args)
	*     void method(const void * p_pSender, ArgumentsType &p_args)
	* ie:
	*     add_listener(addon.newIntEvent, this, &Class::method) */

	//=============================================================================================
	template <class EventType, typename ArgumentsType, class ListenerClass>
	static void remove_listener( EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, ArgumentsType&), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class EventType, typename ArgumentsType, class ListenerClass>
	static void remove_listener( EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int32_t prio=EVENT_ORDER_AFTER_APP ) 
	{
		p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class ListenerClass>
	static void remove_listener( evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class ListenerClass>
	static void remove_listener( evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class EventType, typename ArgumentsType, class ListenerClass>
	static void remove_listener( EventType & p_event, ListenerClass  * p_pListener, bool (ListenerClass::*listenerMethod)(const void*, ArgumentsType&), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= evt::Delegate<ListenerClass,ArgumentsType,true>(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class EventType, typename ArgumentsType, class ListenerClass>
	static void remove_listener( EventType & p_event, ListenerClass  * p_pListener, bool (ListenerClass::*listenerMethod)(ArgumentsType&), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= evt::Delegate<ListenerClass,ArgumentsType,false>(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class ListenerClass>
	static void remove_listener( evt::TEvent<void> & p_event, ListenerClass  * p_pListener, bool (ListenerClass::*listenerMethod)(const void*), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= evt::Delegate<ListenerClass,void,true>(p_pListener, listenerMethod, prio);
	}

	//=============================================================================================
	template <class ListenerClass>
	static void remove_listener( evt::TEvent<void> & p_event, ListenerClass  * p_pListener, bool (ListenerClass::*listenerMethod)(), int32_t prio=EVENT_ORDER_AFTER_APP )
	{
		p_event -= evt::Delegate<ListenerClass,void,false>(p_pListener, listenerMethod, prio);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//		NOTIFY EVENTS
	///////////////////////////////////////////////////////////////////////////////////////////////

	/** \! Notifies an event so all the registered listeners get called
	* ie:
	*	evt::notify_event( p_intEvent, p_intArgument, this )
	*
	* or in case there's no sender:
	*	evt::notify_event( p_intEvent, p_intArgument ) 
	*
	* or in case there is no sender and no argument
	*	evt::natify_event( p_event ) */

	//=============================================================================================
	template <class EventType, typename ArgumentsType, typename SenderType>
	static void notify_event( EventType & p_event, ArgumentsType & p_args, SenderType * p_pSender )
	{
		p_event.notify( p_pSender, p_args );
	}

	//=============================================================================================
	template <class EventType, typename ArgumentsType>
	static void notify_event( EventType & p_event, ArgumentsType & p_args )
	{
		p_event.notify( NULL, p_args );
	}

	//=============================================================================================
	template <class EventType, typename ArgumentsType, typename SenderType>
	static void notify_event( EventType & p_event, const ArgumentsType & p_args, SenderType * p_pSender )
	{
		p_event.notify( p_pSender, p_args );
	}

	//=============================================================================================
	template <class EventType, typename ArgumentsType>
	static void notify_event( EventType & p_event, const ArgumentsType & p_args )
	{
		p_event.notify( NULL, p_args );
	}

	//=============================================================================================
	template <typename SenderType>
	static void notify_event( evt::TEvent<void> & p_event, SenderType * p_pSender )
	{
		p_event.notify( p_pSender );
	}

	//=============================================================================================
	template <class EventType>
	static void notify_event( EventType & p_event)
	{
		p_event.notify( NULL );
	}

} // namespace evt


#endif // BUILD_USE_POCO

#endif // __EVT_UTILS_H__

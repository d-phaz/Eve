
#pragma once
#ifndef __EVE_EVT_SERVER_H__
#define __EVE_EVT_SERVER_H__


#include <Poco/PriorityEvent.h>
#include <Poco/PriorityDelegate.h>

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_EVT_TEVENT_H__
#include "eve/evt/TEvent.h"
#endif


namespace eve
{
	namespace evt
	{
		/**
		* \enum eve::evtEventOrder 
		* \brief Provides event order depending on application events. 
		*/
		enum EventOrder
		{
			orderBeforeApp	= 0,
			orderApp		= 100,
			orderAfterApp	= 200
		};


		///////////////////////////////////////////////////////////////////////////////////////////
		//		ADD LISTENERS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \brief Register any method of any class to an event.
		* The method must provide the following signature: void method(const void * p_pSender, ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType, class ListenerClass>
		static void add_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, ArgumentsType&), int32_t prio = orderAfterApp);
		/**
		* \brief Register any method of any class to an event.
		* The method must provide the following signature: void method(const void * p_pSender, const ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType, class ListenerClass>
		static void add_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, const ArgumentsType&), int32_t prio = orderAfterApp);
		/**
		* \brief Register any method of any class to an event.
		* The method must provide the following signature: void method(ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType, class ListenerClass>
		static void add_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int32_t prio = orderAfterApp);
		/**
		* \brief Register any method of any class to an event.
		* The method must provide the following signature: void method(const ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType, class ListenerClass>
		static void add_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const ArgumentsType&), int32_t prio = orderAfterApp);
		/**
		* \brief Register any method of any class to an event.
		* The method must provide the following signature:  void method(const void * p_pSender)
		*/
		template <class ListenerClass>
		static void add_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*), int32_t prio = orderAfterApp);
		/**
		* \brief Register any method of any class to an event.
		* The method must provide the following signature:  void method(void)
		*/
		template <class ListenerClass>
		static void add_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(void), int32_t prio = orderAfterApp);


		///////////////////////////////////////////////////////////////////////////////////////////
		//		REMOVE LISTENERS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \brief Unregister any method of any class from an event.
		* The method must provide the following signature: void method(const void * p_pSender, ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType, class ListenerClass>
		static void remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, ArgumentsType&), int32_t prio = orderAfterApp);
		/**
		* \brief Unregister any method of any class from an event.
		* The method must provide the following signature: void method(const void * p_pSender, const ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType, class ListenerClass>
		static void remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, const ArgumentsType&), int32_t prio = orderAfterApp);
		/**
		* \brief Unregister any method of any class from an event.
		* The method must provide the following signature: void method(ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType, class ListenerClass>
		static void remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int32_t prio = orderAfterApp);
		/**
		* \brief Unregister any method of any class from an event.
		* The method must provide the following signature: void method(const ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType, class ListenerClass>
		static void remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const ArgumentsType&), int32_t prio = orderAfterApp);
		/**
		* \brief Unregister any method of any class from an event.
		* The method must provide the following signature: void method(const void * p_pSender)
		*/
		template <class ListenerClass>
		static void remove_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*), int32_t prio = orderAfterApp);
		/**
		* \brief Unregister any method of any class from an event.
		* The method must provide the following signature: void method(void)
		*/
		template <class ListenerClass>
		static void remove_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(void), int32_t prio = orderAfterApp);


		///////////////////////////////////////////////////////////////////////////////////////////
		//		NOTIFY EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \brief Notifies an event so all the registered listeners get called.
		* Registered listener(s) method must provide the following signature: void method(const void * p_pSender, ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType, class SenderType>
		static void notify_event(EventType & p_event, ArgumentsType & p_args, SenderType * p_pSender);
		/**
		* \brief Notifies an event so all the registered listeners get called.
		* Registered listener(s) method must provide the following signature: void method(const void * p_pSender, const ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType, class SenderType>
		static void notify_event(EventType & p_event, const ArgumentsType & p_args, SenderType * p_pSender);
		/**
		* \brief Notifies an event so all the registered listeners get called.
		* Registered listener(s) method must provide the following signature: void method(ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType>
		static void notify_event(EventType & p_event, ArgumentsType & p_args);
		/**
		* \brief Notifies an event so all the registered listeners get called.
		* Registered listener(s) method must provide the following signature: void method(const ArgumentsType &p_args)
		*/
		template <class EventType, class ArgumentsType>
		static void notify_event(EventType & p_event, const ArgumentsType & p_args);
		/**
		* \brief Notifies an event so all the registered listeners get called.
		* Registered listener(s) method must provide the following signature: void method(const void * p_pSender)
		*/
		template <class SenderType>
		static void notify_event(evt::TEvent<void> & p_event, SenderType * p_pSender);
		/**
		* \brief Notifies an event so all the registered listeners get called.
		* Registered listener(s) method must provide the following signature: void method(void)
		*/
		template <class EventType>
		static void notify_event(EventType & p_event);

	} // namespace evt

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		ADD LISTENERS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::add_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, ArgumentsType&), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::add_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, const ArgumentsType&), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::add_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::add_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const ArgumentsType&), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class ListenerClass>
void eve::evt::add_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class ListenerClass>
void eve::evt::add_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(void), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//		REMOVE LISTENERS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, ArgumentsType&), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, const ArgumentsType&), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const ArgumentsType&), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class ListenerClass>
void eve::evt::remove_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class ListenerClass>
void eve::evt::remove_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(void), int32_t prio)
{
	p_event -= Poco::priorityDelegate(p_pListener, listenerMethod, prio);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		NOTIFY EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template <class EventType, class ArgumentsType, class SenderType>
void eve::evt::notify_event(EventType & p_event, ArgumentsType & p_args, SenderType * p_pSender)
{
	p_event.notify(p_pSender, p_args);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class SenderType>
void eve::evt::notify_event(EventType & p_event, const ArgumentsType & p_args, SenderType * p_pSender)
{
	p_event.notify(p_pSender, p_args);
}

//=================================================================================================
template <class EventType, class ArgumentsType>
void eve::evt::notify_event(EventType & p_event, ArgumentsType & p_args)
{
	p_event.notify(NULL, p_args);
}

//=================================================================================================
template <class EventType, class ArgumentsType>
void eve::evt::notify_event(EventType & p_event, const ArgumentsType & p_args)
{
	p_event.notify(NULL, p_args);
}

//=================================================================================================
template <class SenderType>
void eve::evt::notify_event(evt::TEvent<void> & p_event, SenderType * p_pSender)
{
	p_event.notify(p_pSender);
}

//=================================================================================================
template <class EventType>
void eve::evt::notify_event(EventType & p_event)
{
	p_event.notify(NULL);
}

#endif // __EVE_EVT_SERVER_H__


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
#ifndef __EVE_EVT_SERVER_H__
#define __EVE_EVT_SERVER_H__

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
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::add_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, const ArgumentsType&), int32_t prio)
{
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::add_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int32_t prio)
{
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::add_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const ArgumentsType&), int32_t prio)
{
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class ListenerClass>
void eve::evt::add_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*), int32_t prio)
{
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class ListenerClass>
void eve::evt::add_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(void), int32_t prio)
{
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
	p_event += eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//		REMOVE LISTENERS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, ArgumentsType&), int32_t prio)
{
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*, const ArgumentsType&), int32_t prio)
{
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int32_t prio)
{
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class EventType, class ArgumentsType, class ListenerClass>
void eve::evt::remove_listener(EventType & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const ArgumentsType&), int32_t prio)
{
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class ListenerClass>
void eve::evt::remove_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(const void*), int32_t prio)
{
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
}

//=================================================================================================
template <class ListenerClass>
void eve::evt::remove_listener(evt::TEvent<void> & p_event, ListenerClass  * p_pListener, void (ListenerClass::*listenerMethod)(void), int32_t prio)
{
	p_event -= eve::evt::priorityDelegate(p_pListener, listenerMethod, prio);
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


#pragma once
#ifndef __SYSTEM_EVENT_LISTENER_H__
#define __SYSTEM_EVENT_LISTENER_H__


#include <deque>


#ifndef __NATIVE_SYSTEM_H__
#include "Native_system.h"
#endif

#ifndef __NATIVE_TYPES_H__
#include "Native_types.h"
#endif

#ifndef __SYSTEM_EVENT_H__
#include "system/shared/SystemEvent.h"
#endif



namespace NativeT {
	class Mutex;
}


/**
* @class SystemEventListener
*
* @brief read and dispatch events from system message pump
* @note abstract base event reader class
*/
class SystemEventListener
{

	//////////////////////////////////////
	//				DATAS				//
	//////////////////////////////////////

protected:
	std::deque<evt::Event> *	m_dequeFirst;		//<! first event queue
	std::deque<evt::Event> *	m_dequeSecond;		//<! secon event queue

	std::deque<evt::Event> *	m_dequeFront;		//<! front event queue shared pointer
	std::deque<evt::Event> *	m_dequeBack;		//<! back event queue shared pointer
	
	NativeT::Mutex *			m_pMutex;			//<! queue protection Mutex

	bool						m_bSwapped;			//<! deque swapped state


	//////////////////////////////////////
	//				METHOD				//
	//////////////////////////////////////

	NATIVE_DISABLE_COPY(SystemEventListener)

protected:
	/** SystemEventListener class constructor. */
    SystemEventListener( void );


	/** Alloc and init class members. */
	void init( void );


public:
	/** Create and return new SystemEventListener pointer. */
    static SystemEventListener * create_ptr( void );


	/** SystemEventListener class destructor. */
	virtual ~SystemEventListener( void );


	/** Swap event deque. */
	void eventSwap( void );


	/** Add event at the back of the deque. */
	void eventPushBack( evt::Event p_event );

	/** Get front event and remove it from deque. */
	evt::Event eventGet( void );

	/** Get active deque empty state. */
	bool eventEmpty( void );
};

#endif // __SYSTEM_EVENT_LISTENER_H__

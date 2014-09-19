
#pragma once
#ifndef __SYSTEM_EVENT_HANDLER_H__
#define __SYSTEM_EVENT_HANDLER_H__

// External header
#include <hash_map>
#include <algorithm>
#include <Windows.h>

// Thread header
#ifndef __NATIVE_MUTEX_H__
#include "Native_Mutex.h"
#endif

// Native header
#ifndef __NATIVE_GLOBALMACRO_H__
#include "Native_GlobalMacro.h"
#endif


class SystemNode;


/**
* @class SystemEventHandler
* 
* @brief dispatch the wndProc to target event readers
*/
class SystemEventHandler
{


	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		Utilities
	///////////////////////////////////////////////////////////////////////////////////////////////////

public:
#ifdef _MSC_VER
	typedef stdext::hash_map< HWND, SystemEventHandler* > HandlerMap;
#else // Cygwin does not want to instantiate a hash with key=HWND
	typedef stdext::hash_map< void*, SystemEventHandler* > HandlerMap;
#endif


	//////////////////////////////////////
	//				DATAS				//
	//////////////////////////////////////

private:
	static HandlerMap 		m_map_handlers;
	static NativeT::Mutex	m_event_haldler_mutex;

private:
    SystemNode *		m_pNode;
    HWND				m_Hwnd;
    WNDPROC				m_PrevWndProc;


	//////////////////////////////////////
	//				METHOD				//
	//////////////////////////////////////

	NATIVE_DISABLE_COPY( SystemEventHandler )

public:
	/** \! Register an event handler */
	static void registerHandler( HWND hWnd, SystemEventHandler * handler );
	/** \! Unregister an event handler */
	static void deregisterHandler( HWND hWnd );

	/** \! Get event handler based on window handle */
	static SystemEventHandler * getEventHandler( HWND hWnd );


private:
	/**
	* @brief static wndProc, used to intercept and dispatch events
	* @note static function
	*/
    static LRESULT CALLBACK wndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	/**
	* @brief handler dedicated wndProc
	*/
    LRESULT CALLBACK _wndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );


protected:
	/** SystemEventHandler class constructor. */
	SystemEventHandler( void );

	/** Alloc and init class members. */
	bool init( SystemNode * p_pNode );

public:
	/** \! Create, init and return new SystemEventHandler pointer. */
	static SystemEventHandler * create_ptr( SystemNode * p_pNode );

	/**  SystemEventHandler class destructor. */
	virtual ~SystemEventHandler( void );
};

#endif // __SYSTEM_EVENT_HANDLER_H__


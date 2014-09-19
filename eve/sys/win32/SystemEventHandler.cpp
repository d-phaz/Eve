
// Main header
#include "SystemEventHandler.h"

// External header
#include <windowsx.h>

// Messaging header
#ifndef __NATIVE_MESSAGING_H__
#include "Native_Messaging.h"
#endif

// System header
#ifndef __SYSTEM_EVENT_H__
#include "system/shared/SystemEvent.h"
#endif

#ifndef __SYSTEM_EVENT_READER_H__
#include "SystemEventReader.h"
#endif

#ifndef __SYSTEM_NODE_H__
#include "SystemNode.h"
#endif

#ifndef __SYSTEM_WINDOW_H__
#include "SystemWindow.h"
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//		Static
///////////////////////////////////////////////////////////////////////////////////////////////////

SystemEventHandler::HandlerMap  SystemEventHandler::m_map_handlers;

NativeT::Mutex SystemEventHandler::m_event_haldler_mutex;


//=================================================================================================
void SystemEventHandler::registerHandler( HWND hWnd, SystemEventHandler* handler )
{
m_event_haldler_mutex.Lock();

#ifndef NDEBUG
	NATIVE_ASSERT( m_map_handlers.find( hWnd ) == m_map_handlers.end( ));
#endif

    m_map_handlers[hWnd] = handler;

m_event_haldler_mutex.Unlock();
}

//=================================================================================================
void SystemEventHandler::deregisterHandler( HWND hWnd )
{
m_event_haldler_mutex.Lock();

#ifndef NDEBUG
	NATIVE_ASSERT( m_map_handlers.find( hWnd ) != m_map_handlers.end( ));
#endif

	m_map_handlers.erase( hWnd );

m_event_haldler_mutex.Unlock();
}

//=================================================================================================
SystemEventHandler * SystemEventHandler::getEventHandler( HWND hWnd )
{
	SystemEventHandler * ptr_ret = NULL;

    if( m_map_handlers.find( hWnd ) != m_map_handlers.end() )
	{
        ptr_ret = m_map_handlers[hWnd];
	}

	return ptr_ret;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SystemEventHandler class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
SystemEventHandler * SystemEventHandler::create_ptr( SystemNode * p_pNode )
{
	SystemEventHandler * ptr = new SystemEventHandler();

	if( !ptr->init(p_pNode) )
	{
		delete ptr;
		ptr = NULL;
	}

#ifndef NDEBUG
	NATIVE_ASSERT( (ptr!=NULL) );
#endif

	return ptr;
}



//=================================================================================================
SystemEventHandler::SystemEventHandler( void )
	
	// Members init
	: m_pNode			( NULL )
	, m_Hwnd			( 0 )
	, m_PrevWndProc		( NULL )
{}

//=================================================================================================
SystemEventHandler::~SystemEventHandler( void )
{
    SetWindowLongPtr( m_Hwnd, GWLP_WNDPROC, (LONG_PTR)m_PrevWndProc );
    deregisterHandler( m_Hwnd );
}



//=================================================================================================
bool SystemEventHandler::init( SystemNode * p_pNode )
{
#ifndef NDEBUG
	NATIVE_ASSERT( (p_pNode!=NULL) );
#endif

	bool breturn = true;

	m_pNode = p_pNode;
	m_Hwnd = m_pNode->getWindow()->m_Hwnd;
	if( !m_Hwnd )
	{
		native_error_msg( "SystemEventHandler constructor()", "target window handle invalid \n" );
		breturn = false;
	}

	registerHandler( m_Hwnd, this );

#pragma warning(push)
#pragma warning(disable: 4312)
	m_PrevWndProc = (WNDPROC)SetWindowLongPtr( m_Hwnd, GWLP_WNDPROC, (LONG_PTR)wndProc );
#pragma warning(pop) 

	// Avoid WndProc recursion
	if( m_PrevWndProc == wndProc ) {
		m_PrevWndProc = DefWindowProc;
	}

	return breturn;
}



//=================================================================================================
LRESULT CALLBACK SystemEventHandler::wndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    SystemEventHandler* handler = getEventHandler( hWnd );
    if( !handler )
    {
		native_error_msg( "SystemEventHandler::wndProc()", "unregistered window message target. \n" );
        return DefWindowProc( hWnd, uMsg, wParam, lParam );
    }

    return handler->_wndProc( hWnd, uMsg, wParam, lParam );
}

//=================================================================================================
LRESULT CALLBACK SystemEventHandler::_wndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	LRESULT L_result = NULL; 
	std::pair<LRESULT, bool> result;

#ifndef NDEBUG
	NATIVE_ASSERT( m_pNode != NULL );
#endif

	result = m_pNode->getEventReader()->handleEvent( *m_pNode->getEventListener(), hWnd, message, wParam, lParam );
	
	L_result = result.first;
    if( !result.second ) {
        L_result = CallWindowProc( m_PrevWndProc, hWnd, message, wParam, lParam );
	}

	return L_result;
}

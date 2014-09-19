
// Main header
#include "SystemEventReader.h"

// External header
#include <map>

// System header
#ifndef __SYSTEM_EVENT_LISTENER_H__
#include "system/win32/SystemEventListener.h"
#endif

#ifndef __SYSTEM_EVENT_H__
#include "system/shared/SystemEvent.h"
#endif

#ifndef __SYSTEM_EVENT_HANDLER_H__
#include "system/win32/SystemEventHandler.h"
#endif

#ifndef __SYSTEM_MOUSE_H__
#include "system/shared/SystemMouse.h"
#endif

#ifndef __SYSTEM_KEYBOARD_H__
#include "system/win32/SystemKeyboard.h"
#endif

#ifndef __SYSTEM_KEYMAP_H__
#include "system/win32/SystemKeymap.h"
#endif

#ifndef __SYSTEM_ERROR_H__
#include "system/win32/SystemError.h"
#endif

#ifndef __SYSTEM_NODE_H__
#include "system/win32/SystemNode.h"
#endif


#undef KEY_MOD_SHIFT
#undef KEY_MOD_CONTROL


///////////////////////////////////////////////////////////////////////////////////////////////////
//		SystemEventReader class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
SystemEventReader::SystemEventReader( void )

	// members init
    : m_bSizeMove			( false )
    , m_bResizing			( false )
    , m_bDirty				( false )
    , m_width				( 0 )
	, m_height				( 0 )
    , m_bMouseinitialized	( false )
    , m_bMouseInside		( false )
    , m_bMouseHidden		( false )
	, m_bMouseDown			( false )
	, m_prevClick			( -1 )
	, m_prevTime			()
{}

//=================================================================================================
SystemEventReader::~SystemEventReader( void )
{}



//=================================================================================================
uint32_t SystemEventReader::wparam2unicode( WPARAM wparam )
{
	uint16_t lo = wparam & 0xFFFF;
	uint16_t hi = (wparam & 0xFFFF0000) >> 16;
	uint32_t codepoint = 0;

	// Convert from UTF-16 to Unicode codepoint
	if(lo < 0xD8000 || lo > 0xDFFF) codepoint = lo;
	else codepoint = ((lo & 0x3FF) << 10) | (hi & 0x3FF) + 0x10000;

	return codepoint;
}



//=================================================================================================
std::pair<LRESULT, bool> SystemEventReader::handleEvent( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	LRESULT L_result = TRUE;

	bool validity = true;

    switch(message)
    {
        case WM_MOUSEMOVE: 
			L_result = handleMotion( p_listener, hwnd, message, wparam, lparam );
			break;

		case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_XBUTTONDOWN:
        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
			L_result = handleMouseDown( p_listener, hwnd, message, wparam, lparam );
			break;

		case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
        case WM_XBUTTONUP:
			L_result = handleMouseUp( p_listener, hwnd, message, wparam, lparam );
			break;
		
		case WM_MOUSELEAVE: 
			L_result = handleLeave( p_listener, hwnd, message, wparam, lparam );
			break;


		case WM_KEYDOWN: 
        case WM_KEYUP: 
        case WM_SYSKEYDOWN: 
        case WM_SYSKEYUP: 
			L_result = handleKey( p_listener, hwnd, message, wparam, lparam );
			break;

		case WM_CHAR:
			L_result = handleChar( p_listener, hwnd, message, wparam, lparam );
			break;


        case WM_ENTERSIZEMOVE: 
			L_result = handleEnterSizeMove( p_listener, hwnd, message, wparam, lparam );
			break;
        case WM_EXITSIZEMOVE:
			L_result = handleExitSizeMove( p_listener, hwnd, message, wparam, lparam );
			break;
		/*case WM_SIZING:
			L_result = handleSizing(window, hwnd, message, wparam, lparam);
			break;*/
        case WM_SIZE:
			L_result = handleSize( p_listener, hwnd, message, wparam, lparam );
			break;


        case WM_PAINT: 
			L_result = handlePaint( p_listener, hwnd, message, wparam, lparam );
			break;

        case WM_ERASEBKGND:
			L_result = handleEraseBkgnd( p_listener, hwnd, message, wparam, lparam );
			break;

        case WM_GETMINMAXINFO:
			L_result = handleGetMinMaxInfo( p_listener, hwnd, message, wparam, lparam );
			break;

		
		//// not sure that's in use !!!
		//case WM_MOVE :		
		//case WM_MOVING :	
		//	L_result = handleIdle(window, hwnd, message, wparam, lparam);
		//	break;
		//// not sure that's in use !!!


		case WM_DROPFILES:
			L_result = handleDrop( p_listener, hwnd, message, wparam, lparam );
			break;


		case WM_CLOSE:
			L_result = handleClose( p_listener, hwnd, message, wparam, lparam );
			break;


		case WM_SETFOCUS:
        case WM_KILLFOCUS:
			L_result = handleFocus( p_listener, hwnd, message, wparam, lparam );
			break;


        default:
			validity = false;
			break;
    }
	return std::pair<LRESULT, bool>(L_result, validity);
}



//=================================================================================================
LRESULT SystemEventReader::handleIdle( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	//evt::Event event;
 //   event.expose.type.eventType = evt::EXPOSE;
 //   event.expose.x = 0;
 //   event.expose.y = 0;
 //   event.expose.m_width = m_width;
 //   event.expose.m_height = m_height;
 //   p_listener.eventPushBack( event );

	return TRUE;
}



//=================================================================================================
LRESULT SystemEventReader::handleEnterSizeMove(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    m_bSizeMove = true;
    m_bResizing = false;
    m_bDirty = false;

	////// //
	//uint32_t w = LOWORD(lparam),
	//			 h = HIWORD(lparam);

	//m_width = w;
	//m_height = h;
	//// propagate ResizeEvent
 //   evt::Event event;
 //   event.resize.type.eventType = evt::RESIZE;
 //   event.resize.m_width = m_width;
 //   event.resize.m_height = m_height;
 //   p_listener.eventPushBack( event );
	//// //


    return TRUE;
}



//=================================================================================================
LRESULT SystemEventReader::handleExitSizeMove(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if(m_bResizing)
    {
		RECT rect;
		::GetClientRect( hwnd, &rect );

		m_width  = rect.right;
		m_height = rect.bottom;

        // propagate ResizeEvent
        evt::Event et;
		et.resize.type.eventType = evt::RESIZE;
		et.resize.width = m_width;
		et.resize.height = m_height;
        p_listener.eventPushBack( et );
    }

    /*
    if(m_bDirty)
    {
        // propagate ExposeEvent
        evt::Event event;
        event.expose.type.eventType = evt::EXPOSE;
        event.expose.x = 0;
        event.expose.y = 0;
        event.expose.width = m_width;
        event.expose.height = m_height;
        p_listener.eventPushBack( event );
    }
    */

    m_bSizeMove = false;

    return TRUE;
}



//=================================================================================================
LRESULT SystemEventReader::handleSizing( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	RECT rect;
	::GetClientRect( hwnd, &rect );

	m_width = rect.right - rect.left;
	m_height = rect.bottom - rect.top;

    // Propagate ResizeEvent
    evt::Event et;
    et.resize.type.eventType = evt::RESIZE;
	et.resize.width = m_width;
	et.resize.height = m_height;
    p_listener.eventPushBack( et );

	return 0; // should return 0 if WM_SIZING processed
}



//=================================================================================================
LRESULT SystemEventReader::handleSize(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    uint32_t w = LOWORD(lparam),
					h = HIWORD(lparam);

    m_width = w;
    m_height = h;

    if(m_bSizeMove)
	{
		m_bResizing = true;
	}
    else
    {
		// propagate ResizeEvent
		evt::Event et;
		et.resize.type.eventType = evt::RESIZE;
		et.resize.width = w;
		et.resize.height = h;
		p_listener.eventPushBack( et );
    }

    return 0; // should return 0 if WM_SIZE processed
}



//=================================================================================================
LRESULT SystemEventReader::handlePaint(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    // ValidateRect prevents Windows from resending WM_PAINT
    RECT rect, *ptr = 0;
    if( ::GetUpdateRect(hwnd, &rect, FALSE) )
    {
        ::ValidateRect( hwnd, &rect );
        ptr = &rect;
    } 

    if( m_bSizeMove )
    {
        m_bDirty = true;
    } 
	else
    {
        // propagate ExposeEvent
        evt::Event et;
        et.expose.type.eventType = evt::EXPOSE;
        et.expose.x = ptr ? rect.left : 0;
        et.expose.y = ptr ? rect.top : 0;
        et.expose.width = ptr ? (rect.right - rect.left) : m_width;
        et.expose.height = ptr ? (rect.bottom - rect.top) : m_height;
		p_listener.eventPushBack( et );
    }

    return 0; // should return 0 if WM_PAINT processed
}



//=================================================================================================
LRESULT SystemEventReader::handleEraseBkgnd(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if( m_bSizeMove ) 
		m_bDirty = true;

    return TRUE;
}



//=================================================================================================
LRESULT SystemEventReader::handleKey(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    bool filter;

    keyboard::Symbol translated = keymap::translateKeyEvent(hwnd, message, wparam, lparam, filter);

    if(!filter)
    {
        bool state = (message == WM_KEYDOWN || message == WM_SYSKEYDOWN);
		/*if( !state )
			keyboard::Utils::SPECIAL_KEY = 0;*/

        bool repeat = state && ((HIWORD(lparam) & KF_REPEAT) ? true : false);

        evt::Event evt;
        evt.key.type.eventType = state ? evt::KEY_DOWN : evt::KEY_UP;
        evt.key.symbol = translated;
        evt.key.keymod = keymap::getKeyModState();
        evt.key.repeat = repeat;

        p_listener.eventPushBack( evt );
    }

    return 0;
}



//=================================================================================================
LRESULT SystemEventReader::handleChar( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	evt::Event et;
	et.text.type.eventType = evt::TEXT_INPUT;
    et.text.unicode = wparam2unicode(wparam);

    p_listener.eventPushBack( et );

	return 0;
}



//=================================================================================================
LRESULT SystemEventReader::handleMouseDown(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	// Create event
	evt::Event et;
	
	POINT pt;
	pt.x = LOWORD(lparam);
	pt.y = HIWORD(lparam);
	::ScreenToClient( hwnd, &pt );

    et.button.x = (int32_t)pt.x;
    et.button.y = (int32_t)pt.y;

    et.button.button  = keymap::mapButton(message, wparam);
    et.button.buttons = keymap::mapButtons(wparam);
    //et.button.keymod = native_system::mapKeyMod(wparam) | (native_system::getKeyModState() &~(keyboard::KEY_MOD_SHIFT | keyboard::KEY_MOD_CONTROL));
	
	
	// Test double click
	struct timeb t;
	ftime(&t);
	time_t timebuffer = (t.time - m_prevTime.time) * 1000 + t.millitm - m_prevTime.millitm;
	
	// Double click
	if( et.button.button == m_prevClick && timebuffer <= ::GetDoubleClickTime() )
	{
		// Set event type
		et.button.type.eventType = evt::BUTTON_DOUBLE;
		// Reset prev click
		m_prevClick = -1;
	}
	// Mouse down
	else
	{
		// Retrieve double click datas
		m_prevClick = et.button.button;
		m_prevTime  = t;
		
		// Update mouse down state
		m_bMouseDown = true;
		// Set event type
		et.button.type.eventType = evt::BUTTON_DOWN;
	}
	
	// Push event in queue
    p_listener.eventPushBack( et );

	// Should return zero if processed
	return 0; 
}



//=================================================================================================
LRESULT SystemEventReader::handleMouseUp( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	m_bMouseDown = false;

	evt::Event et;
	et.button.type.eventType = evt::BUTTON_UP;
    et.button.x = LOWORD(lparam);
    et.button.y = HIWORD(lparam);
    et.button.button = keymap::mapButton(message, wparam);
    et.button.buttons = keymap::mapButtons(wparam);
    //et.button.keymod = native_system::mapKeyMod(wparam) | (native_system::getKeyModState() &  ~(keyboard::KEY_MOD_SHIFT | keyboard::KEY_MOD_CONTROL));
    p_listener.eventPushBack( et );

	return 0; // should return zero if processed
}



//=================================================================================================
LRESULT SystemEventReader::handleMotion(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    uint32_t x = LOWORD(lparam);
    uint32_t y = HIWORD(lparam);

    if( !m_bMouseInside )
    {
        if( !m_bMouseinitialized )
        {
            m_bMouseinitialized = true;
        } 
		else
        {
            TRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_LEAVE;
            tme.hwndTrack = hwnd;
        }

        m_bMouseInside = true;

        // Propagate MouseOver event
        evt::Event et;
        et.mouseover.type.eventType = evt::MOUSE_ENTER;
        et.mouseover.x = x;
        et.mouseover.y = y;
        p_listener.eventPushBack( et );
    }

    keyboard::KeyMod keymod = keymap::mapKeyMod(wparam) | (keymap::getKeyModState() &~(keyboard::KEY_MOD_SHIFT | keyboard::KEY_MOD_CONTROL));

    evt::Event et;
	et.motion.type.eventType = (m_bMouseDown) ? evt::MOTION : evt::PASSIVE_MOTION;
    et.motion.x = x;
    et.motion.y = y;
    et.motion.buttons = keymap::mapButtons(wparam);
    et.motion.keymod = keymod;
    p_listener.eventPushBack( et );

    return 0; // should return zero if processed
}



//=================================================================================================
LRESULT SystemEventReader::handleFocus( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	evt::Event et;
	et.focus.type.eventType = (message == WM_SETFOCUS) ? evt::FOCUS_GOT : evt::FOCUS_LOST;
    p_listener.eventPushBack( et );

	if( et.focus.type.eventType == evt::FOCUS_LOST )
		m_bMouseDown = false;

	return 0;
}



//=================================================================================================
LRESULT SystemEventReader::handleLeave(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    m_bMouseInside = false;
	m_bMouseDown = false;

    if(!m_bMouseinitialized)
    {
        m_bMouseinitialized = true;
    } else
    {
        // Propagate MouseLeave event
        evt::Event ev;
		ev.mouseover.type.eventType = evt::MOUSE_LEAVE;
		ev.mouseover.x = 0;
		ev.mouseover.y = 0;
        p_listener.eventPushBack( ev );
    }

    return 0;
}



//=================================================================================================
LRESULT SystemEventReader::handleGetMinMaxInfo(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    MINMAXINFO *ptr = (MINMAXINFO*)(lparam); // previously reinterpret_cast

    RECT rect;
	::GetClientRect( hwnd, &rect );

	m_width = rect.right - rect.left;
	m_height = rect.bottom - rect.top;

	uint32_t bounds[][2] = { {m_width, m_height}, {m_width, m_height} };

    LONG style	 = ::GetWindowLong(hwnd, GWL_STYLE);
    LONG exstyle = ::GetWindowLong(hwnd, GWL_EXSTYLE);

    for(int i = 0; i < 2; ++i)
    {
        if(!bounds[i][0] || !bounds[i][1]) continue;

        RECT rect;
        ::SetRect( &rect, 0, 0, bounds[i][0], bounds[i][1] );
		::AdjustWindowRectEx(&rect, style, false, exstyle);

        bounds[i][0] = rect.right - rect.left;
        bounds[i][1] = rect.bottom - rect.top;
    }

    uint32_t minW = bounds[0][0], minH = bounds[0][1], maxW = bounds[1][0], maxH = bounds[1][1];

    LRESULT result = 0;

    if(minW != 0 && minH != 0)
    {
        /*ptr->ptMinTrackSize.x = minW;
        ptr->ptMinTrackSize.y = minH;*/
        result = TRUE;
    }

    if(maxW != 0 && maxH != 0)
    {
        /*ptr->ptMaxSize.x = ptr->ptMaxTrackSize.x = maxW;
        ptr->ptMaxSize.y = ptr->ptMaxTrackSize.y = maxH;*/
        result = TRUE;
    }

    return result;
}



//=================================================================================================
LRESULT SystemEventReader::handleDrop(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	HDROP query = (HDROP) wparam;

	POINT pt;
	DragQueryPoint( query, &pt ); // get mouse position on drag

	uint32_t n = 0;
	uint32_t count = ::DragQueryFileW( query, 0xFFFFFFFF, 0, 0 ); // get files infos

	evt::Event ev;
	ev.filedrop.type.eventType = evt::DROP_FILES;
	ev.filedrop.numberOfFiles = count;
	ev.filedrop.filesname = ( wchar_t** )malloc( count*sizeof( wchar_t* ));
	ev.filedrop.x = pt.x;
	ev.filedrop.y = pt.y;

	while ( n < count ) 
	{
		uint32_t nChar = ::DragQueryFileW( query, n, NULL, 0 );
		
		ev.filedrop.filesname[n] = (wchar_t*) malloc((nChar + 1) * sizeof(wchar_t));

		::DragQueryFileW( query, n, ev.filedrop.filesname[n], nChar + 1 );

		n++;
	}

	::DragFinish( query );

	p_listener.eventPushBack( ev );

	return 0;
}



//=================================================================================================
LRESULT SystemEventReader::handleClose(SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	evt::Event evt;
	evt.close.type.eventType = evt::CLOSE;
	p_listener.eventPushBack( evt );

	return TRUE;
}

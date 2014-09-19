
// Main class header
#include "SystemWindow.h"

// Messaging header
#ifndef __NATIVE_MESSAGING_H__
#include "Native_Messaging.h"
#endif

// Thread header
#ifndef __NATIVE_SCOPED_MUTEX_H__
#include "Native_ScopedMutex.h"
#endif


// System headers
#ifndef _NATIVE_system_h_
#include "Native_System.h"
#endif

#ifndef __SYSTEM_ERROR_H__
#include "system/win32/SystemError.h"
#endif

#ifndef __SYSTEM_CURSOR_H__
#include "system/shared/SystemCursor.h"
#endif

#ifndef __SYSTEM_NODE_H__
#include "system/win32/SystemNode.h"
#endif




///////////////////////////////////////////////////////////////////////////////////////////////////
//		Statics
///////////////////////////////////////////////////////////////////////////////////////////////////

NativeT::Lock SystemWindow::m_paccess_lock = NativeT::Lock();



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SystemWindow class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
SystemWindow * SystemWindow::create_ptr
	( 
	int32_t p_nodalId, 
	SystemNode * p_pNodeParent, 
	int32_t p_x, 
	int32_t p_y, 
	uint32_t p_width, 
	uint32_t p_height, 
	bool p_bsetScaledOnOutput 
	)
{
	SystemWindow * ptr = new SystemWindow( p_nodalId, p_pNodeParent, p_x, p_y, p_width, p_height, p_bsetScaledOnOutput );

	ptr->init();

	return ptr;
}



//=================================================================================================
SystemWindow::SystemWindow
	( 
	int32_t p_nodalId, 
	SystemNode * p_pNodeParent, 
	int32_t p_x, 
	int32_t p_y, 
	uint32_t p_width, 
	uint32_t p_height, 
	bool p_bsetScaledOnOutput
	)

	// Members initialisation
	: m_NodalId				( p_nodalId )
	, m_pNodeParent			( p_pNodeParent )
	, m_X					( p_x )
	, m_Y					( p_y )
	, m_Width				( p_width )
	, m_Height				( p_height )
	, m_minWidth			( p_width )
	, m_minHeight			( p_height )
	, m_maxWidth			( 0 )
	, m_maxHeight			( 0 )

	, m_Hwnd				( NULL )
	, m_Atom				( 0 )
	, m_Hinstance			( GetModuleHandle( 0 ) )

	, m_Cursor				( cursor::CURSOR_INHERIT )
	, m_bScaledOnOutput		( false )

	, m_Style				( 0 )
	, m_ExStyle				( 0 )
	, m_StyleFullscreen		( 0 )
	, m_ExStyleFullscreen	( 0 )
	, m_bsetScaledOnOutput  ( p_bsetScaledOnOutput )
	, m_title				( "SystemWindow" )
	, m_titleChar			( NULL )
{
	// Stock coordinates
	m_beforeScaleCoordinates.x		= m_X;
	m_beforeScaleCoordinates.y		= m_Y;
	m_beforeScaleCoordinates.width	= m_Width;
	m_beforeScaleCoordinates.height = m_Height;
}



//=================================================================================================
SystemWindow::~SystemWindow( void )
{
	// Destroy system window
    try
    {
        if( !DestroyWindow( m_Hwnd ) )
        {
			std::string err = "Can't destroy window: ";
			err += native_system::getErrorMsg();
            native_error_msg( "SystemWindow::~SystemWindow", err.c_str() );
        }
    } 
	catch( std::exception & e )
    {
		native_error_msg( "SystemWindow::~SystemWindow()", "DestroyWindow() failed with error %s.", e.what() );
    }

	// Title as char array
	if( m_titleChar )
	{
		delete[] m_titleChar;
		m_titleChar = NULL;
	}
}



//=================================================================================================
void SystemWindow::init( void )
{
	//NONCLIENTMETRICS ncmetr;
	//ncmetr.cbSize = sizeof(NONCLIENTMETRICS);
	//::SystemParametersInfo( SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncmetr, 0 );

	//// Style
	//m_Style					= WS_POPUP;
	//m_ExStyle				= WS_EX_APPWINDOW;
	//m_StyleFullscreen		= WS_POPUP;
	//m_ExStyleFullscreen		= WS_EX_APPWINDOW;

	m_Style					= WS_OVERLAPPEDWINDOW;
	m_ExStyle				= WS_EX_OVERLAPPEDWINDOW;
	m_StyleFullscreen		= WS_POPUP;
	m_ExStyleFullscreen		= WS_EX_APPWINDOW;



	// WND CLASS //

	// Generate per-instance unique classname string
    WCHAR classname[sizeof(SystemWindow*) * 2 + 2]; // we add 2 chars to the window class name 
    genClassNameStr(this, classname);

    // Get native_system module handle
    m_Hinstance = GetModuleHandle(0);
    if( !m_Hinstance ) {
		 throw NATIVERUNTIME::RunTimeException("Could not get native_system module handle: " + native_system::getErrorMsg());
	}

    // Load cursor
    HCURSOR hcursor = LoadCursor(0, IDC_ARROW);
    if( !hcursor ) {
		throw NATIVERUNTIME::RunTimeException("Could not load native_system default cursor" + native_system::getErrorMsg());
	}

    WNDCLASSEXW klass;
    klass.cbSize		= sizeof(WNDCLASSEXW);
    klass.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    klass.lpfnWndProc	= DefWindowProc;
    klass.cbClsExtra	= 0;
    klass.cbWndExtra	= sizeof(SystemWindow*);
    klass.hInstance		= m_Hinstance;
    klass.hIcon			= 0;
    klass.hIconSm		= 0;
    klass.hCursor		= hcursor;
    klass.hbrBackground = 0;
    klass.lpszMenuName	= 0;
    klass.lpszClassName = classname;

    m_Atom = RegisterClassExW(&klass);
    if( !m_Atom ) {
		throw NATIVERUNTIME::RunTimeException( "Can't register native_system window class: " + native_system::getErrorMsg() );
	}



	// CREATE WINDOW //

	RECT rect;
	if( !SetRect(&rect, m_X, m_Y, m_X+m_Width, m_Y+m_Height) ) {
        throw NATIVERUNTIME::RunTimeException("Can't initialize window bounds rectangle");
	}

	if( !AdjustWindowRectEx( &rect, m_Style, false, m_ExStyle ) ) {
		throw NATIVERUNTIME::RunTimeException("Can't adjust window rectangle" + native_system::getErrorMsg());
	}

	// Update values based on styled rect
	m_X = rect.left;
	m_Y = rect.top;
	m_minWidth = m_Width = rect.right - rect.left;
	m_minHeight = m_Height = rect.bottom - rect.top;

    WCHAR t_title = 0;

	// Create window handle
	m_Hwnd = ::CreateWindowExW
		( 
		m_ExStyle,
		classname,
		&t_title,
		m_Style,
		m_X, 
		m_Y, 
		m_Width, 
		m_Height,
		NULL,
		0,
		m_Hinstance,
		0 
		);
	if( !m_Hwnd ) 
	{
		native_error_msg( "SystemWindow::init", native_system::getErrorMsg().c_str() );
		throw NATIVERUNTIME::RunTimeException("Can't create SystemWindow: " + native_system::getErrorMsg());
	}

    try
    {
        SetLastError(0);
        if( !SetWindowLongPtr( m_Hwnd, 0, reinterpret_cast<LONG_PTR>(this)) )
        {
            DWORD err = GetLastError();
			if( err != 0 ) {
				throw NATIVERUNTIME::RunTimeException("Can't set native_system Window user data: " + native_system::getErrorMsg(err));
			}
        }

        // TrackMouseEvent to recieve WM_MOUSELEAVE events
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = m_Hwnd;

		if( !TrackMouseEvent(&tme) ) {
			throw NATIVERUNTIME::RunTimeException("Can't track mouse events: " + native_system::getErrorMsg());
		}
    } 
	catch(...)
    {
        if( !DestroyWindow(m_Hwnd) )
        {
			std::string err = "Can't destroy window: ";
			err += native_system::getErrorMsg();
			native_error_msg( "SystemWindow::init", err.c_str() );
        }

        throw;
    }

	// Scaled on output property
	if( m_bsetScaledOnOutput ) {
		scaleOnOutput();
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		UTILITIES
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void SystemWindow::updateMaxSize( void )
{
	// Initialize windowed size for restoration
    RECT windowRect;
	if( !GetWindowRect(m_Hwnd, &windowRect) ) {
		throw NATIVERUNTIME::RunTimeException("Can't set full screen mode, GetWindowRect failed: " + native_system::getErrorMsg());
	}


	// detect on which monitor to set full screen
	HMONITOR hMonitor;
	MONITORINFO mi;
	RECT        rc;

	// get the nearest monitor to the passed rect. 
	hMonitor = MonitorFromRect( &windowRect, MONITOR_DEFAULTTONEAREST );

	// get the work area or entire monitor rect. 
	mi.cbSize = sizeof(mi);
	if( !GetMonitorInfo(hMonitor, &mi) ) {
		throw NATIVERUNTIME::RunTimeException("Can't set full screen,  GetMonitorInfo failed: " + native_system::getErrorMsg());
	}

	rc = mi.rcMonitor;


	m_maxWidth  = rc.right - rc.left;
	m_maxHeight = rc.bottom - rc.top;
}



//=================================================================================================
void SystemWindow::setActive( void )
{
	SetActiveWindow( m_Hwnd );
}



//=================================================================================================
void SystemWindow::setForeground( void )
{
	SetForegroundWindow( m_Hwnd );
}



//=================================================================================================
void SystemWindow::show( void )
{
	ShowWindowAsync( m_Hwnd, SW_SHOWNORMAL );
}



//=================================================================================================
void SystemWindow::hide( void )
{
    ShowWindowAsync( m_Hwnd, SW_HIDE );
}



//=================================================================================================
void SystemWindow::minimize( void )
{
	ShowWindowAsync( m_Hwnd, SW_SHOWMINIMIZED );
}



//=================================================================================================
void SystemWindow::restore( void )
{
	ShowWindowAsync( m_Hwnd, SW_RESTORE );
}



//=================================================================================================
void SystemWindow::close( void )
{
	CloseWindow( m_Hwnd );
}



//=================================================================================================
void SystemWindow::push( void )
{
	SetWindowPos( m_Hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );
}



//=================================================================================================
void SystemWindow::pop( void )
{
	// previously : HWND_TOP
	SetWindowPos( m_Hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );
}



//=================================================================================================
void SystemWindow::resize(uint32_t width, uint32_t height)
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );

	LONG style = GetWindowLong(m_Hwnd, GWL_STYLE);
	if( !style ) {
		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());
	}

	LONG exstyle = GetWindowLong(m_Hwnd, GWL_EXSTYLE);
	if( !exstyle ) {
		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());
	}

	RECT rect;
	if( !SetRect(&rect, 0, 0, width, height) ) {
		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for resizing");
	}

	if( !AdjustWindowRectEx(&rect, style, false, exstyle) ) {
		throw NATIVERUNTIME::RunTimeException("Can't adjust window bounds rectangle: " + native_system::getErrorMsg());
	}

	m_minWidth = m_Width  = rect.right - rect.left;
	m_minHeight = m_Height = rect.bottom - rect.top;

	if(!SetWindowPos( m_Hwnd,
						0, // HWND hWndInsertAfter
						0, 0, // x, y (ignored because of SWP_NOMOVE)
						rect.right - rect.left,
						rect.bottom - rect.top,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE) )
	{
		throw NATIVERUNTIME::RunTimeException("Can't resize native_system window: " + native_system::getErrorMsg());
	}
}



//=================================================================================================
void SystemWindow::scaleOnOutput(void)
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );

	if( !m_bScaledOnOutput )
	{
		// Stock before scale coordinates
		m_beforeScaleCoordinates.x		= m_X;
		m_beforeScaleCoordinates.y		= m_Y;
		m_beforeScaleCoordinates.width	= m_Width;
		m_beforeScaleCoordinates.height = m_Height;


		// Initialize windowed size for restoration
        RECT windowRect;
		if(!GetWindowRect(m_Hwnd, &windowRect))
			throw NATIVERUNTIME::RunTimeException("Can't set full screen mode, GetWindowRect failed: " + native_system::getErrorMsg());

		if(!GetClientRect(m_Hwnd, &m_WindowedRect))
			throw NATIVERUNTIME::RunTimeException("Can't set full screen,  GetClientRect failed: " + native_system::getErrorMsg());


		// detect on which monitor to set full screen
		HMONITOR hMonitor;
		MONITORINFO mi;
		RECT        rc;

		// get the nearest monitor to the passed rect. 
		hMonitor = MonitorFromRect( &windowRect, MONITOR_DEFAULTTONEAREST );

		// get the work area or entire monitor rect. 
		mi.cbSize = sizeof(mi);
		if( !GetMonitorInfo(hMonitor, &mi) ) {
			throw NATIVERUNTIME::RunTimeException("Can't set full screen,  GetMonitorInfo failed: " + native_system::getErrorMsg());
		}

		rc = mi.rcMonitor;


		m_Width = rc.right - rc.left;
		m_Height = rc.bottom - rc.top;

		m_X = rc.left;
		m_Y = rc.top;


		hide();

		if(!SetWindowLong(m_Hwnd, GWL_STYLE, m_StyleFullscreen))
			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowLong failed: " + native_system::getErrorMsg());

		if(!SetWindowLong(m_Hwnd, GWL_EXSTYLE, m_ExStyleFullscreen))
			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowLong failed: " + native_system::getErrorMsg());


		if(!SetWindowPos( m_Hwnd,
							HWND_TOPMOST,
							m_X, 
							m_Y,
							m_Width, 
							m_Height,
							SWP_FRAMECHANGED | SWP_SHOWWINDOW)) 
		{
			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowPos failed: " + native_system::getErrorMsg());
		}

		m_bScaledOnOutput = true;
	}
	else
	{
		// Update window rect based on coordinates befor scale
		m_WindowedRect.left = m_beforeScaleCoordinates.x;
		m_WindowedRect.right = m_beforeScaleCoordinates.x + m_beforeScaleCoordinates.width;
		m_WindowedRect.top = m_beforeScaleCoordinates.y;
		m_WindowedRect.bottom = m_beforeScaleCoordinates.y + m_beforeScaleCoordinates.height;
		

		if(!AdjustWindowRectEx(&m_WindowedRect, m_Style, false, m_ExStyle))
			throw NATIVERUNTIME::RunTimeException("Can't switch to windowed mode, AdjustWindowRectEx failed: " + native_system::getErrorMsg());
			
		m_Width = m_WindowedRect.right - m_WindowedRect.left;
		m_Height = m_WindowedRect.bottom - m_WindowedRect.top;

		m_X = m_WindowedRect.left;
		m_Y = m_WindowedRect.top;

		hide();

		if( !SetWindowLong(m_Hwnd, GWL_STYLE, m_Style) )
			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowLong failed: " + native_system::getErrorMsg());

		if( !SetWindowLong(m_Hwnd, GWL_EXSTYLE, m_ExStyle) )
			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowLong failed: " + native_system::getErrorMsg());

		if( !SetWindowPos(m_Hwnd,
							HWND_NOTOPMOST,
							m_X, 
							m_Y,
							m_Width, 
							m_Height,
							SWP_FRAMECHANGED | SWP_SHOWWINDOW) )
		{
			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowPos failed: " + native_system::getErrorMsg());
		}

		m_bScaledOnOutput = false;
	}
}



//=================================================================================================
void SystemWindow::fixOnOutput( void )
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );

	// Initialize windowed size for restoration
    RECT windowRect;
	if(!GetWindowRect(m_Hwnd, &windowRect))
		throw NATIVERUNTIME::RunTimeException("Can't set full screen mode, GetWindowRect failed: " + native_system::getErrorMsg());

    // detect on which monitor to set fullscreen
	HMONITOR	hMonitor;
	MONITORINFO mi;
	RECT        rc;

	// get the nearest monitor to the passed rect. 
	hMonitor = MonitorFromRect( &windowRect, MONITOR_DEFAULTTONEAREST );

	// get the work area or entire monitor rect. 
	mi.cbSize = sizeof(mi);
	if( !GetMonitorInfo(hMonitor, &mi) )
		throw NATIVERUNTIME::RunTimeException("Can't set full screen,  GetMonitorInfo failed: " + native_system::getErrorMsg());

	rc = mi.rcMonitor;

	m_X = rc.left;
	m_Y = rc.top;

	// Hide the window before changes
	//hide();

	// Apply changes
	if(!SetWindowPos( m_Hwnd,
						HWND_TOPMOST,
						m_X, 
						m_Y,
						m_Width, 
						m_Height,
						SWP_FRAMECHANGED | SWP_SHOWWINDOW))
	{
		throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowPos failed: " + native_system::getErrorMsg());
	}

	//m_bScaledOnOutput = true;
}



//=================================================================================================
void SystemWindow::warpMouse( int32_t p_deportX, int32_t p_deportY )
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );

	if( !::SetCursorPos( this->getPositionX() + p_deportX, this->getPositionY() + p_deportY) ) {
		throw NATIVERUNTIME::RunTimeException("Can't set cursor position, SetCursorPos failed: " + native_system::getErrorMsg());
	}
}



//=================================================================================================
void SystemWindow::repaint(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    RECT rect, *ptr = 0;

    if(width != 0 && height != 0)
    {
		if(!SetRect(&rect, x, y, width, height))
			throw NATIVERUNTIME::RunTimeException("Can't repaint SystemWindow, SetRect failed: " + native_system::getErrorMsg());
        ptr = &rect;
    }

	if(!RedrawWindow(m_Hwnd, ptr, 0, RDW_INVALIDATE))
		throw NATIVERUNTIME::RunTimeException("Can't repaint SystemWindow, RedrawWindow failed: " + native_system::getErrorMsg());
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET /SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void SystemWindow::setWidth( const uint32_t & width )
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );

	LONG style = GetWindowLong(m_Hwnd, GWL_STYLE);
	if(!style)
		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());

	LONG exstyle;
	exstyle = GetWindowLong(m_Hwnd, GWL_EXSTYLE);
	if(!exstyle)
		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());

    RECT rect;
	if(!SetRect(&rect, 0, 0, width, m_Height))
		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for resizing");

	if(!AdjustWindowRectEx(&rect, style, false, exstyle))
		throw NATIVERUNTIME::RunTimeException("Can't adjust window bounds rectangle: " + native_system::getErrorMsg());

	m_Width  = rect.right - rect.left;

    if(!SetWindowPos( m_Hwnd,
						0, // HWND hWndInsertAfter
						0, 0, // x, y (ignored because of SWP_NOMOVE)
						rect.right - rect.left,
						rect.bottom - rect.top,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE))
	{
		throw NATIVERUNTIME::RunTimeException("Can't resize native_system window: " + native_system::getErrorMsg());
	}
}



//=================================================================================================-
void SystemWindow::setHeight( const uint32_t & height )
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );

    LONG style = GetWindowLong(m_Hwnd, GWL_STYLE);
	if(!style)
		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());

	LONG exstyle = GetWindowLong(m_Hwnd, GWL_EXSTYLE);
	if(!exstyle)
		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());

    RECT rect;
	if(!SetRect(&rect, 0, 0, m_Width, height))
		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for resizing");

	if(!AdjustWindowRectEx(&rect, style, false, exstyle))
		throw NATIVERUNTIME::RunTimeException("Can't adjust window bounds rectangle: " + native_system::getErrorMsg());

	m_Height = rect.bottom - rect.top;

    if(!SetWindowPos( m_Hwnd,
						0, // HWND hWndInsertAfter
						0, 0, // x, y (ignored because of SWP_NOMOVE)
						rect.right - rect.left,
						rect.bottom - rect.top,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE))
	{
		throw NATIVERUNTIME::RunTimeException("Can't resize native_system window: " + native_system::getErrorMsg());
	}
}



//=================================================================================================
void SystemWindow::getSize(uint32_t &width, uint32_t &height)
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );

    RECT rect;
	if(!GetClientRect(m_Hwnd, &rect))
		throw NATIVERUNTIME::RunTimeException("Can't get native_system window client area size: " + native_system::getErrorMsg());

    uint32_t w = rect.right - rect.left;
    uint32_t h = rect.bottom - rect.top;

    width = w;
    height = h;
}
//=================================================================================================
const uint32_t SystemWindow::getWidth( void )
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );

    RECT rect;
	if(!GetClientRect(m_Hwnd, &rect))
		throw NATIVERUNTIME::RunTimeException("Can't get native_system window client area size: " + native_system::getErrorMsg());

    m_Width = rect.right - rect.left;

	return m_Width;
}
//=================================================================================================
const uint32_t SystemWindow::getHeight( void )
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );

    RECT rect;
	if(!GetClientRect(m_Hwnd, &rect))
		throw NATIVERUNTIME::RunTimeException("Can't get native_system window client area size: " + native_system::getErrorMsg());

    m_Height = rect.bottom - rect.top;

	return m_Height;
}



//=================================================================================================
int32_t SystemWindow::getPositionX( void )
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );
	RECT rect;

#ifndef NDEBUG
    if(!
#endif
		GetWindowRect(m_Hwnd, &rect)
#ifndef NDEBUG		
		)
		throw NATIVERUNTIME::RunTimeException("Can't get system window client area size: " + native_system::getErrorMsg());
#else
		;
#endif

	m_X = rect.left;

	return rect.left;
}

//=================================================================================================
int32_t SystemWindow::getPositionY( void )
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );
	RECT rect;

#ifndef NDEBUG
    if(!
#endif
		GetWindowRect(m_Hwnd, &rect)
#ifndef NDEBUG		
		)
		throw NATIVERUNTIME::RunTimeException("Can't get system window client area size: " + native_system::getErrorMsg());
#else
		;
#endif

	m_Y = rect.top;

	return rect.top;
}



//=================================================================================================
void SystemWindow::setPosition( const int32_t & p_x, const int32_t & p_y )
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );
	
	if( !SetRect(&m_WindowedRect, p_x, p_y, p_x+m_Width, p_y+m_Height) )
		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for positioning");

	if( !AdjustWindowRectEx(&m_WindowedRect, m_Style, false, m_ExStyle) )
		throw NATIVERUNTIME::RunTimeException("Can't adjust native_system window bounds rectangle: " + native_system::getErrorMsg());
	
			
	if( SetWindowPos( m_Hwnd,
						0, // HWND hWndInsertAfter
						p_x, 
						p_y, 
						m_Width,
						m_Height,
						SWP_FRAMECHANGED | SWP_NOZORDER) )
	{
		m_X = p_x;
		m_Y = p_y;
	}
#ifndef NDEBUG
	else {
		throw NATIVERUNTIME::RunTimeException("Can't change position of native_system window: " + native_system::getErrorMsg());
	}
#endif
}

//=================================================================================================
void SystemWindow::setPositionX( const int32_t & p_x )
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );
	
	if( !SetRect(&m_WindowedRect, p_x, m_Y, p_x+m_Width, m_Y+m_Height) )
		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for positioning");

	if( !AdjustWindowRectEx(&m_WindowedRect, m_Style, false, m_ExStyle) )
		throw NATIVERUNTIME::RunTimeException("Can't adjust native_system window bounds rectangle: " + native_system::getErrorMsg());
	
			
	if( SetWindowPos( m_Hwnd,
						0, // HWND hWndInsertAfter
						p_x, 
						m_Y, 
						m_Width,
						m_Height,
						SWP_FRAMECHANGED | SWP_NOZORDER) )
	{
		m_X = p_x;
	}
#ifndef NDEBUG
	else {
		throw NATIVERUNTIME::RunTimeException("Can't change position of native_system window: " + native_system::getErrorMsg());
	}
#endif
}

//=================================================================================================
void SystemWindow::setPositionY( const int32_t & p_y )
{
	NativeT::ScopedMutex<> mutex( m_paccess_lock );
	
	if( !SetRect(&m_WindowedRect, m_X, p_y, m_X+m_Width, p_y+m_Height) )
		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for positioning");

	if( !AdjustWindowRectEx(&m_WindowedRect, m_Style, false, m_ExStyle) )
		throw NATIVERUNTIME::RunTimeException("Can't adjust native_system window bounds rectangle: " + native_system::getErrorMsg());
	
			
	if( SetWindowPos( m_Hwnd,
						0, // HWND hWndInsertAfter
						m_X, 
						p_y, 
						m_Width,
						m_Height,
						SWP_FRAMECHANGED | SWP_NOZORDER) )
	{
		m_Y = p_y;
	}
#ifndef NDEBUG
	else {
		throw NATIVERUNTIME::RunTimeException("Can't change position of native_system window: " + native_system::getErrorMsg());
	}
#endif
}



//=================================================================================================
Vec2i SystemWindow::clientToScreen( const uint32_t & p_x, const uint32_t & p_y )
{
	Vec2i v_return = Vec2i::zero();

	POINT pt;
	pt.x = p_x;
	pt.y = p_y;
	if( ::ClientToScreen( m_Hwnd, &pt ) )
	{
		v_return.x = pt.x;
		v_return.y = pt.y;
	}
	else
	{
		native_error_msg( "SystemWindow::clientToScreen()", "can't get client window position %s \n", native_system::getErrorMsg() );
	}

	return v_return;
}



//=================================================================================================
void SystemWindow::setTitle( const std::string & p_title)
{
    if( !p_title.empty() )
	{
		// Grab title as std::string
		m_title = p_title;

		// Grab title as char array
		m_titleChar = new char[ p_title.size()+1 ];
		strcpy( m_titleChar, p_title.c_str() );

		const size_t size = strlen(p_title.c_str()) + 1;
		wchar_t * unicodeTitle = new wchar_t[ size ];
		mbstowcs( unicodeTitle, p_title.c_str(), size );

		// Set window title
		if( !SetWindowTextW(m_Hwnd, unicodeTitle) )
			throw NATIVERUNTIME::RunTimeException("Can't set window title: " + native_system::getErrorMsg());

		// Free memory
		delete unicodeTitle;
	}
}



//=================================================================================================
void SystemWindow::setDragAcceptFiles( const bool & p_bStatus )
{
	SetLastError(0);

	if( p_bStatus ) 
	{
		/*
		ChangeWindowMessageFilterEx( m_Hwnd, WM_DROPFILES, MSGFLT_ALLOW, NULL );
		ChangeWindowMessageFilterEx( m_Hwnd, WM_COPYDATA , MSGFLT_ALLOW, NULL );
		ChangeWindowMessageFilterEx( m_Hwnd, 0x0049      , MSGFLT_ALLOW, NULL );
		*/

		DragAcceptFiles( m_Hwnd, TRUE );
	}
	else { 
		DragAcceptFiles( m_Hwnd, FALSE );
	}

	DWORD err = GetLastError();
	if( err != 0 ) {
		throw NATIVERUNTIME::RunTimeException( "Can't set native_system SystemWindow drag accept files " + native_system::getErrorMsg(err) );
	}
}

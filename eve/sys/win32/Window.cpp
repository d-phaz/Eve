
// Main header
#include "eve/sys/win32/Window.h"

#ifndef __EVE_THREADING_INCLUDES_H__
#include "eve/thr/Includes.h"
#endif


//=================================================================================================
char getHexChar(uint32_t idx)
{
	if (idx >= 16)
		return '!';

	return (char)((idx < 10) ? '0' + idx : 'a' + (idx - 10));
}
//=================================================================================================
void genClassNameStr(const void *ptr, wchar_t *out)
{
	static char clnme = 0;
	clnme += 1;

	size_t size = sizeof(const void*);
	const unsigned char *begin = reinterpret_cast<const unsigned char *>(&ptr);

	for (const unsigned char *ptr = begin;
		ptr != begin + size;
		++ptr)
	{
		*(out++) = getHexChar(*ptr & 0x0f);
		*(out++) = getHexChar((*ptr & 0xf0) >> 4);
	}

	*(out++) = clnme;
	*(out++) = 0;
}



LONG eve::sys::Window::m_styleFullscreen	= WS_POPUP;
LONG eve::sys::Window::m_exStyleFullscreen	= WS_EX_APPWINDOW;


//=================================================================================================
eve::sys::Window * eve::sys::Window::create_ptr(int32_t p_x, int32_t p_y, uint32_t p_width, uint32_t p_height)
{
	eve::sys::Window * ptr = new eve::sys::Window(p_x, p_y, p_width, p_height);
	ptr->init();
	return ptr;
}

//=================================================================================================
eve::sys::Window::Window(int32_t p_x, int32_t p_y, uint32_t p_width, uint32_t p_height)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_x(p_x)
	, m_y(p_y)
	, m_width(p_width)
	, m_height(p_height)
	, m_title(0)

	, m_handle(0)
	, m_atom(0)
	, m_hinstance(0)

	, m_windowedRect()
	, m_bScaledOnOutput(false)
	, m_style(0)
	, m_exStyle(0)

	, m_pFence(nullptr)
{}



//=================================================================================================
void eve::sys::Window::init(void)
{
	// Create fence.
	m_pFence = EVE_CREATE_PTR(eve::thr::SpinLock);

	// Stock coordinates.
	m_windowedRect.left		= m_x;
	m_windowedRect.right	= m_x + m_width;
	m_windowedRect.top		= m_y;
	m_windowedRect.bottom	= m_y + m_height;


	// Window style
	m_style		= WS_OVERLAPPEDWINDOW;
	m_exStyle	= WS_EX_OVERLAPPEDWINDOW;

	// Get thick and title bar size (aka non client metrics).
	//NONCLIENTMETRICS ncmetr;
	//ncmetr.cbSize = sizeof(NONCLIENTMETRICS);
	//::SystemParametersInfo( SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncmetr, 0 );

	// Generate per-instance unique classname string
	wchar_t classname[sizeof(eve::sys::Window*) * 2 + 2]; // we add 2 chars to the window class name 
	genClassNameStr(this, classname);

	// Get system module handle
	m_hinstance = ::GetModuleHandleW(0);
	if (!m_hinstance) 
	{
		EVE_LOG_ERROR("Could not get system module handle: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	// Load cursor.
	HCURSOR hcursor = ::LoadCursorW(0, IDC_ARROW);
	if (!hcursor) 
	{
		EVE_LOG_ERROR("Could not load system default cursor: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	// System window class informations.
	WNDCLASSEXW windowClass;
	windowClass.cbSize			= sizeof(WNDCLASSEXW);
	windowClass.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // CS_CLASSDC
	windowClass.lpfnWndProc		= ::DefWindowProcW;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= sizeof(eve::sys::Window*);
	windowClass.hInstance		= m_hinstance;
	windowClass.hIcon			= 0;
	windowClass.hIconSm			= 0;
	windowClass.hCursor			= hcursor;
	windowClass.hbrBackground	= 0;
	windowClass.lpszMenuName	= 0;
	windowClass.lpszClassName	= classname;

	// Register window class.
	m_atom = ::RegisterClassExW(&windowClass);
	if (!m_atom) 
	{
		EVE_LOG_ERROR("Can't register system window class: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	// Adjust window client rect.
	if (!::AdjustWindowRectEx(&m_windowedRect, m_style, false, m_exStyle)) 
	{
		EVE_LOG_ERROR("Can't adjust window rectangle: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
	
	// Create window handle
	wchar_t t_title = 0;
	m_handle = ::CreateWindowExW(m_exStyle,
								 classname,
								 &t_title,
								 m_style,
								 m_x,
								 m_y,
								 m_width,
								 m_height,
								 NULL,
								 0,
								 m_hinstance,
								 0);
	if (!m_handle)
	{
		EVE_LOG_ERROR("Can't create system Window: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}


	//if (::SetWindowLongPtrW(m_handle, 0, reinterpret_cast<LONG_PTR>(this)) == 0)
	//{
	//	EVE_LOG_ERROR("Can't set system Window user data: %s", eve::mess::get_error_msg().c_str());
	//	EVE_ASSERT_FAILURE;
	//}

	// Track mouse event to receive WM_MOUSELEAVE events.
	TRACKMOUSEEVENT tme;
	tme.cbSize		= sizeof(TRACKMOUSEEVENT);
	tme.dwFlags		= TME_LEAVE;
	tme.hwndTrack	= m_handle;

	if (!::TrackMouseEvent(&tme)) 
	{
		EVE_LOG_ERROR("Can't track system Window mouse events: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
}

//=================================================================================================
void eve::sys::Window::release(void)
{
	// Destroy system window
	try
	{
		if (!::DestroyWindow(m_handle))
		{
			std::string err = "Can't destroy window: ";
			err += eve::mess::get_error_msg();
			EVE_LOG_ERROR("DestroyWindow() failed with error %s.", err.c_str());
		}
	}
	catch (std::exception & e)
	{
		EVE_LOG_ERROR( "DestroyWindow() failed with error %s.", e.what() );
	}

	// Title as char array
	if (m_title)
	{
		delete[] m_title;
		m_title = 0;
	}

	// Release fence.
	EVE_RELEASE_PTR(m_pFence);
}








//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
////		UTILITIES
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
////=================================================================================================
//void SystemWindow::updateMaxSize( void )
//{
//	// Initialize windowed size for restoration
//    RECT windowRect;
//	if( !GetWindowRect(m_Hwnd, &windowRect) ) {
//		throw NATIVERUNTIME::RunTimeException("Can't set full screen mode, GetWindowRect failed: " + native_system::getErrorMsg());
//	}
//
//
//	// detect on which monitor to set full screen
//	HMONITOR hMonitor;
//	MONITORINFO mi;
//	RECT        rc;
//
//	// get the nearest monitor to the passed rect. 
//	hMonitor = MonitorFromRect( &windowRect, MONITOR_DEFAULTTONEAREST );
//
//	// get the work area or entire monitor rect. 
//	mi.cbSize = sizeof(mi);
//	if( !GetMonitorInfo(hMonitor, &mi) ) {
//		throw NATIVERUNTIME::RunTimeException("Can't set full screen,  GetMonitorInfo failed: " + native_system::getErrorMsg());
//	}
//
//	rc = mi.rcMonitor;
//
//
//	m_maxWidth  = rc.right - rc.left;
//	m_maxHeight = rc.bottom - rc.top;
//}
//
//
//
////=================================================================================================
//void SystemWindow::setActive( void )
//{
//	SetActiveWindow( m_Hwnd );
//}
//
//
//
////=================================================================================================
//void SystemWindow::setForeground( void )
//{
//	SetForegroundWindow( m_Hwnd );
//}
//
//
//
////=================================================================================================
//void SystemWindow::show( void )
//{
//	ShowWindowAsync( m_Hwnd, SW_SHOWNORMAL );
//}
//
//
//
////=================================================================================================
//void SystemWindow::hide( void )
//{
//    ShowWindowAsync( m_Hwnd, SW_HIDE );
//}
//
//
//
////=================================================================================================
//void SystemWindow::minimize( void )
//{
//	ShowWindowAsync( m_Hwnd, SW_SHOWMINIMIZED );
//}
//
//
//
////=================================================================================================
//void SystemWindow::restore( void )
//{
//	ShowWindowAsync( m_Hwnd, SW_RESTORE );
//}
//
//
//
////=================================================================================================
//void SystemWindow::close( void )
//{
//	CloseWindow( m_Hwnd );
//}
//
//
//
////=================================================================================================
//void SystemWindow::push( void )
//{
//	SetWindowPos( m_Hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );
//}
//
//
//
////=================================================================================================
//void SystemWindow::pop( void )
//{
//	// previously : HWND_TOP
//	SetWindowPos( m_Hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );
//}
//
//
//
////=================================================================================================
//void SystemWindow::resize(uint32_t width, uint32_t height)
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//
//	LONG style = GetWindowLong(m_Hwnd, GWL_STYLE);
//	if( !style ) {
//		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());
//	}
//
//	LONG exstyle = GetWindowLong(m_Hwnd, GWL_EXSTYLE);
//	if( !exstyle ) {
//		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());
//	}
//
//	RECT rect;
//	if( !SetRect(&rect, 0, 0, width, height) ) {
//		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for resizing");
//	}
//
//	if( !AdjustWindowRectEx(&rect, style, false, exstyle) ) {
//		throw NATIVERUNTIME::RunTimeException("Can't adjust window bounds rectangle: " + native_system::getErrorMsg());
//	}
//
//	m_minWidth = m_Width  = rect.right - rect.left;
//	m_minHeight = m_Height = rect.bottom - rect.top;
//
//	if(!SetWindowPos( m_Hwnd,
//						0, // HWND hWndInsertAfter
//						0, 0, // x, y (ignored because of SWP_NOMOVE)
//						rect.right - rect.left,
//						rect.bottom - rect.top,
//						SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE) )
//	{
//		throw NATIVERUNTIME::RunTimeException("Can't resize native_system window: " + native_system::getErrorMsg());
//	}
//}
//
//
//
////=================================================================================================
//void SystemWindow::scaleOnOutput(void)
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//
//	if( !m_bScaledOnOutput )
//	{
//		// Stock before scale coordinates
//		m_beforeScaleCoordinates.x		= m_X;
//		m_beforeScaleCoordinates.y		= m_Y;
//		m_beforeScaleCoordinates.width	= m_Width;
//		m_beforeScaleCoordinates.height = m_Height;
//
//
//		// Initialize windowed size for restoration
//        RECT windowRect;
//		if(!GetWindowRect(m_Hwnd, &windowRect))
//			throw NATIVERUNTIME::RunTimeException("Can't set full screen mode, GetWindowRect failed: " + native_system::getErrorMsg());
//
//		if(!GetClientRect(m_Hwnd, &m_WindowedRect))
//			throw NATIVERUNTIME::RunTimeException("Can't set full screen,  GetClientRect failed: " + native_system::getErrorMsg());
//
//
//		// detect on which monitor to set full screen
//		HMONITOR hMonitor;
//		MONITORINFO mi;
//		RECT        rc;
//
//		// get the nearest monitor to the passed rect. 
//		hMonitor = MonitorFromRect( &windowRect, MONITOR_DEFAULTTONEAREST );
//
//		// get the work area or entire monitor rect. 
//		mi.cbSize = sizeof(mi);
//		if( !GetMonitorInfo(hMonitor, &mi) ) {
//			throw NATIVERUNTIME::RunTimeException("Can't set full screen,  GetMonitorInfo failed: " + native_system::getErrorMsg());
//		}
//
//		rc = mi.rcMonitor;
//
//
//		m_Width = rc.right - rc.left;
//		m_Height = rc.bottom - rc.top;
//
//		m_X = rc.left;
//		m_Y = rc.top;
//
//
//		hide();
//
//		if(!SetWindowLong(m_Hwnd, GWL_STYLE, m_StyleFullscreen))
//			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowLong failed: " + native_system::getErrorMsg());
//
//		if(!SetWindowLong(m_Hwnd, GWL_EXSTYLE, m_ExStyleFullscreen))
//			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowLong failed: " + native_system::getErrorMsg());
//
//
//		if(!SetWindowPos( m_Hwnd,
//							HWND_TOPMOST,
//							m_X, 
//							m_Y,
//							m_Width, 
//							m_Height,
//							SWP_FRAMECHANGED | SWP_SHOWWINDOW)) 
//		{
//			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowPos failed: " + native_system::getErrorMsg());
//		}
//
//		m_bScaledOnOutput = true;
//	}
//	else
//	{
//		// Update window rect based on coordinates befor scale
//		m_WindowedRect.left = m_beforeScaleCoordinates.x;
//		m_WindowedRect.right = m_beforeScaleCoordinates.x + m_beforeScaleCoordinates.width;
//		m_WindowedRect.top = m_beforeScaleCoordinates.y;
//		m_WindowedRect.bottom = m_beforeScaleCoordinates.y + m_beforeScaleCoordinates.height;
//		
//
//		if(!AdjustWindowRectEx(&m_WindowedRect, m_Style, false, m_ExStyle))
//			throw NATIVERUNTIME::RunTimeException("Can't switch to windowed mode, AdjustWindowRectEx failed: " + native_system::getErrorMsg());
//			
//		m_Width = m_WindowedRect.right - m_WindowedRect.left;
//		m_Height = m_WindowedRect.bottom - m_WindowedRect.top;
//
//		m_X = m_WindowedRect.left;
//		m_Y = m_WindowedRect.top;
//
//		hide();
//
//		if( !SetWindowLong(m_Hwnd, GWL_STYLE, m_Style) )
//			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowLong failed: " + native_system::getErrorMsg());
//
//		if( !SetWindowLong(m_Hwnd, GWL_EXSTYLE, m_ExStyle) )
//			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowLong failed: " + native_system::getErrorMsg());
//
//		if( !SetWindowPos(m_Hwnd,
//							HWND_NOTOPMOST,
//							m_X, 
//							m_Y,
//							m_Width, 
//							m_Height,
//							SWP_FRAMECHANGED | SWP_SHOWWINDOW) )
//		{
//			throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowPos failed: " + native_system::getErrorMsg());
//		}
//
//		m_bScaledOnOutput = false;
//	}
//}
//
//
//
////=================================================================================================
//void SystemWindow::fixOnOutput( void )
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//
//	// Initialize windowed size for restoration
//    RECT windowRect;
//	if(!GetWindowRect(m_Hwnd, &windowRect))
//		throw NATIVERUNTIME::RunTimeException("Can't set full screen mode, GetWindowRect failed: " + native_system::getErrorMsg());
//
//    // detect on which monitor to set fullscreen
//	HMONITOR	hMonitor;
//	MONITORINFO mi;
//	RECT        rc;
//
//	// get the nearest monitor to the passed rect. 
//	hMonitor = MonitorFromRect( &windowRect, MONITOR_DEFAULTTONEAREST );
//
//	// get the work area or entire monitor rect. 
//	mi.cbSize = sizeof(mi);
//	if( !GetMonitorInfo(hMonitor, &mi) )
//		throw NATIVERUNTIME::RunTimeException("Can't set full screen,  GetMonitorInfo failed: " + native_system::getErrorMsg());
//
//	rc = mi.rcMonitor;
//
//	m_X = rc.left;
//	m_Y = rc.top;
//
//	// Hide the window before changes
//	//hide();
//
//	// Apply changes
//	if(!SetWindowPos( m_Hwnd,
//						HWND_TOPMOST,
//						m_X, 
//						m_Y,
//						m_Width, 
//						m_Height,
//						SWP_FRAMECHANGED | SWP_SHOWWINDOW))
//	{
//		throw NATIVERUNTIME::RunTimeException("Can't set full screen, SetWindowPos failed: " + native_system::getErrorMsg());
//	}
//
//	//m_bScaledOnOutput = true;
//}
//
//
//
////=================================================================================================
//void SystemWindow::warpMouse( int32_t p_deportX, int32_t p_deportY )
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//
//	if( !::SetCursorPos( this->getPositionX() + p_deportX, this->getPositionY() + p_deportY) ) {
//		throw NATIVERUNTIME::RunTimeException("Can't set cursor position, SetCursorPos failed: " + native_system::getErrorMsg());
//	}
//}
//
//
//
////=================================================================================================
//void SystemWindow::repaint(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
//{
//    RECT rect, *ptr = 0;
//
//    if(width != 0 && height != 0)
//    {
//		if(!SetRect(&rect, x, y, width, height))
//			throw NATIVERUNTIME::RunTimeException("Can't repaint SystemWindow, SetRect failed: " + native_system::getErrorMsg());
//        ptr = &rect;
//    }
//
//	if(!RedrawWindow(m_Hwnd, ptr, 0, RDW_INVALIDATE))
//		throw NATIVERUNTIME::RunTimeException("Can't repaint SystemWindow, RedrawWindow failed: " + native_system::getErrorMsg());
//}
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
////		GET /SET
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
////=================================================================================================
//void SystemWindow::setWidth( const uint32_t & width )
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//
//	LONG style = GetWindowLong(m_Hwnd, GWL_STYLE);
//	if(!style)
//		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());
//
//	LONG exstyle;
//	exstyle = GetWindowLong(m_Hwnd, GWL_EXSTYLE);
//	if(!exstyle)
//		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());
//
//    RECT rect;
//	if(!SetRect(&rect, 0, 0, width, m_Height))
//		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for resizing");
//
//	if(!AdjustWindowRectEx(&rect, style, false, exstyle))
//		throw NATIVERUNTIME::RunTimeException("Can't adjust window bounds rectangle: " + native_system::getErrorMsg());
//
//	m_Width  = rect.right - rect.left;
//
//    if(!SetWindowPos( m_Hwnd,
//						0, // HWND hWndInsertAfter
//						0, 0, // x, y (ignored because of SWP_NOMOVE)
//						rect.right - rect.left,
//						rect.bottom - rect.top,
//						SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE))
//	{
//		throw NATIVERUNTIME::RunTimeException("Can't resize native_system window: " + native_system::getErrorMsg());
//	}
//}
//
//
//
////=================================================================================================-
//void SystemWindow::setHeight( const uint32_t & height )
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//
//    LONG style = GetWindowLong(m_Hwnd, GWL_STYLE);
//	if(!style)
//		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());
//
//	LONG exstyle = GetWindowLong(m_Hwnd, GWL_EXSTYLE);
//	if(!exstyle)
//		throw NATIVERUNTIME::RunTimeException("Can't resize window, unable to query window style: " + native_system::getErrorMsg());
//
//    RECT rect;
//	if(!SetRect(&rect, 0, 0, m_Width, height))
//		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for resizing");
//
//	if(!AdjustWindowRectEx(&rect, style, false, exstyle))
//		throw NATIVERUNTIME::RunTimeException("Can't adjust window bounds rectangle: " + native_system::getErrorMsg());
//
//	m_Height = rect.bottom - rect.top;
//
//    if(!SetWindowPos( m_Hwnd,
//						0, // HWND hWndInsertAfter
//						0, 0, // x, y (ignored because of SWP_NOMOVE)
//						rect.right - rect.left,
//						rect.bottom - rect.top,
//						SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE))
//	{
//		throw NATIVERUNTIME::RunTimeException("Can't resize native_system window: " + native_system::getErrorMsg());
//	}
//}
//
//
//
////=================================================================================================
//void SystemWindow::getSize(uint32_t &width, uint32_t &height)
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//
//    RECT rect;
//	if(!GetClientRect(m_Hwnd, &rect))
//		throw NATIVERUNTIME::RunTimeException("Can't get native_system window client area size: " + native_system::getErrorMsg());
//
//    uint32_t w = rect.right - rect.left;
//    uint32_t h = rect.bottom - rect.top;
//
//    width = w;
//    height = h;
//}
////=================================================================================================
//const uint32_t SystemWindow::getWidth( void )
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//
//    RECT rect;
//	if(!GetClientRect(m_Hwnd, &rect))
//		throw NATIVERUNTIME::RunTimeException("Can't get native_system window client area size: " + native_system::getErrorMsg());
//
//    m_Width = rect.right - rect.left;
//
//	return m_Width;
//}
////=================================================================================================
//const uint32_t SystemWindow::getHeight( void )
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//
//    RECT rect;
//	if(!GetClientRect(m_Hwnd, &rect))
//		throw NATIVERUNTIME::RunTimeException("Can't get native_system window client area size: " + native_system::getErrorMsg());
//
//    m_Height = rect.bottom - rect.top;
//
//	return m_Height;
//}
//
//
//
////=================================================================================================
//int32_t SystemWindow::getPositionX( void )
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//	RECT rect;
//
//#ifndef NDEBUG
//    if(!
//#endif
//		GetWindowRect(m_Hwnd, &rect)
//#ifndef NDEBUG		
//		)
//		throw NATIVERUNTIME::RunTimeException("Can't get system window client area size: " + native_system::getErrorMsg());
//#else
//		;
//#endif
//
//	m_X = rect.left;
//
//	return rect.left;
//}
//
////=================================================================================================
//int32_t SystemWindow::getPositionY( void )
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//	RECT rect;
//
//#ifndef NDEBUG
//    if(!
//#endif
//		GetWindowRect(m_Hwnd, &rect)
//#ifndef NDEBUG		
//		)
//		throw NATIVERUNTIME::RunTimeException("Can't get system window client area size: " + native_system::getErrorMsg());
//#else
//		;
//#endif
//
//	m_Y = rect.top;
//
//	return rect.top;
//}
//
//
//
////=================================================================================================
//void SystemWindow::setPosition( const int32_t & p_x, const int32_t & p_y )
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//	
//	if( !SetRect(&m_WindowedRect, p_x, p_y, p_x+m_Width, p_y+m_Height) )
//		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for positioning");
//
//	if( !AdjustWindowRectEx(&m_WindowedRect, m_Style, false, m_ExStyle) )
//		throw NATIVERUNTIME::RunTimeException("Can't adjust native_system window bounds rectangle: " + native_system::getErrorMsg());
//	
//			
//	if( SetWindowPos( m_Hwnd,
//						0, // HWND hWndInsertAfter
//						p_x, 
//						p_y, 
//						m_Width,
//						m_Height,
//						SWP_FRAMECHANGED | SWP_NOZORDER) )
//	{
//		m_X = p_x;
//		m_Y = p_y;
//	}
//#ifndef NDEBUG
//	else {
//		throw NATIVERUNTIME::RunTimeException("Can't change position of native_system window: " + native_system::getErrorMsg());
//	}
//#endif
//}
//
////=================================================================================================
//void SystemWindow::setPositionX( const int32_t & p_x )
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//	
//	if( !SetRect(&m_WindowedRect, p_x, m_Y, p_x+m_Width, m_Y+m_Height) )
//		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for positioning");
//
//	if( !AdjustWindowRectEx(&m_WindowedRect, m_Style, false, m_ExStyle) )
//		throw NATIVERUNTIME::RunTimeException("Can't adjust native_system window bounds rectangle: " + native_system::getErrorMsg());
//	
//			
//	if( SetWindowPos( m_Hwnd,
//						0, // HWND hWndInsertAfter
//						p_x, 
//						m_Y, 
//						m_Width,
//						m_Height,
//						SWP_FRAMECHANGED | SWP_NOZORDER) )
//	{
//		m_X = p_x;
//	}
//#ifndef NDEBUG
//	else {
//		throw NATIVERUNTIME::RunTimeException("Can't change position of native_system window: " + native_system::getErrorMsg());
//	}
//#endif
//}
//
////=================================================================================================
//void SystemWindow::setPositionY( const int32_t & p_y )
//{
//	NativeT::ScopedMutex<> mutex( m_paccess_lock );
//	
//	if( !SetRect(&m_WindowedRect, m_X, p_y, m_X+m_Width, p_y+m_Height) )
//		throw NATIVERUNTIME::RunTimeException("Can't set window rectangle for positioning");
//
//	if( !AdjustWindowRectEx(&m_WindowedRect, m_Style, false, m_ExStyle) )
//		throw NATIVERUNTIME::RunTimeException("Can't adjust native_system window bounds rectangle: " + native_system::getErrorMsg());
//	
//			
//	if( SetWindowPos( m_Hwnd,
//						0, // HWND hWndInsertAfter
//						m_X, 
//						p_y, 
//						m_Width,
//						m_Height,
//						SWP_FRAMECHANGED | SWP_NOZORDER) )
//	{
//		m_Y = p_y;
//	}
//#ifndef NDEBUG
//	else {
//		throw NATIVERUNTIME::RunTimeException("Can't change position of native_system window: " + native_system::getErrorMsg());
//	}
//#endif
//}
//
//
//
////=================================================================================================
//Vec2i SystemWindow::clientToScreen( const uint32_t & p_x, const uint32_t & p_y )
//{
//	Vec2i v_return = Vec2i::zero();
//
//	POINT pt;
//	pt.x = p_x;
//	pt.y = p_y;
//	if( ::ClientToScreen( m_Hwnd, &pt ) )
//	{
//		v_return.x = pt.x;
//		v_return.y = pt.y;
//	}
//	else
//	{
//		native_error_msg( "SystemWindow::clientToScreen()", "can't get client window position %s \n", native_system::getErrorMsg() );
//	}
//
//	return v_return;
//}
//
//
//
////=================================================================================================
//void SystemWindow::setTitle( const std::string & p_title)
//{
//    if( !p_title.empty() )
//	{
//		// Grab title as std::string
//		m_title = p_title;
//
//		// Grab title as char array
//		m_titleChar = new char[ p_title.size()+1 ];
//		strcpy( m_titleChar, p_title.c_str() );
//
//		const size_t size = strlen(p_title.c_str()) + 1;
//		wchar_t * unicodeTitle = new wchar_t[ size ];
//		mbstowcs( unicodeTitle, p_title.c_str(), size );
//
//		// Set window title
//		if( !SetWindowTextW(m_Hwnd, unicodeTitle) )
//			throw NATIVERUNTIME::RunTimeException("Can't set window title: " + native_system::getErrorMsg());
//
//		// Free mem
//		delete unicodeTitle;
//	}
//}
//
//
//
////=================================================================================================
//void SystemWindow::setDragAcceptFiles( const bool & p_bStatus )
//{
//	SetLastError(0);
//
//	if( p_bStatus ) 
//	{
//		/*
//		ChangeWindowMessageFilterEx( m_Hwnd, WM_DROPFILES, MSGFLT_ALLOW, NULL );
//		ChangeWindowMessageFilterEx( m_Hwnd, WM_COPYDATA , MSGFLT_ALLOW, NULL );
//		ChangeWindowMessageFilterEx( m_Hwnd, 0x0049      , MSGFLT_ALLOW, NULL );
//		*/
//
//		DragAcceptFiles( m_Hwnd, TRUE );
//	}
//	else { 
//		DragAcceptFiles( m_Hwnd, FALSE );
//	}
//
//	DWORD err = GetLastError();
//	if( err != 0 ) {
//		throw NATIVERUNTIME::RunTimeException( "Can't set native_system SystemWindow drag accept files " + native_system::getErrorMsg(err) );
//	}
//}

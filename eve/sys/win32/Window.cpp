
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



LONG eve::sys::Window::m_style_fullscreen	 = WS_POPUP;
LONG eve::sys::Window::m_ex_style_fullscreen = WS_EX_APPWINDOW;


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
	, m_bFullScreen(false)
	, m_style(0)
	, m_exStyle(0)

	, m_pFence(nullptr)
{}



//=================================================================================================
void eve::sys::Window::init(void)
{
	// Create fence.
	m_pFence = EVE_CREATE_PTR(eve::thr::SpinLock);

	// Window style
	m_style		= WS_OVERLAPPEDWINDOW;
	m_exStyle	= WS_EX_OVERLAPPEDWINDOW;

	// Stock coordinates.
	m_windowedRect.left		= m_x;
	m_windowedRect.right	= m_x + m_width;
	m_windowedRect.top		= m_y;
	m_windowedRect.bottom	= m_y + m_height;

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
	
	// Create window handle
	wchar_t t_title = 0;
	m_handle = ::CreateWindowExW(m_exStyle, classname, &t_title, m_style,
								 m_x, m_y, m_width, m_height,
								 NULL, 0, m_hinstance, 0);
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

	// Show the window.
	::ShowWindow(m_handle, SW_SHOWNORMAL);
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
		EVE_RELEASE_PTR_C(m_title);
	}

	// Release fence.
	EVE_RELEASE_PTR(m_pFence);
}



//=================================================================================================
void eve::sys::Window::show(void)
{
	m_pFence->lock();
	::ShowWindowAsync(m_handle, SW_SHOWNORMAL);
	m_pFence->unlock();
}

//=================================================================================================
void eve::sys::Window::hide(void)
{
	m_pFence->lock();
	::ShowWindowAsync(m_handle, SW_HIDE);
	m_pFence->unlock();
}



//=================================================================================================
void eve::sys::Window::minimize(void)
{
	m_pFence->lock();
	::ShowWindowAsync(m_handle, SW_SHOWMINIMIZED);
	m_pFence->unlock();
}

//=================================================================================================
void eve::sys::Window::restore(void)
{
	m_pFence->lock();
	::ShowWindowAsync(m_handle, SW_RESTORE);
	m_pFence->unlock();
}



//=================================================================================================
void eve::sys::Window::close(void)
{
	m_pFence->lock();
	::CloseWindow(m_handle);
	m_pFence->unlock();
}



//=================================================================================================
void eve::sys::Window::push(void)
{
	m_pFence->lock();
	::SetWindowPos(m_handle, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	m_pFence->unlock();
}

//=================================================================================================
void eve::sys::Window::pop(void)
{
	m_pFence->lock();
	::SetWindowPos(m_handle, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	m_pFence->unlock();
}



//=================================================================================================
void eve::sys::Window::toggleFullScreen(void)
{
	m_pFence->lock();

	// Full Screen
	if (!m_bFullScreen)
	{
		// Initialize windowed size for restoration
		RECT windowRect;
		if (!::GetWindowRect(m_handle, &windowRect))
		{
			EVE_LOG_ERROR("Can't set full screen mode, GetWindowRect failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		// Detect on which monitor to set full screen
		HMONITOR	hMonitor;
		MONITORINFO mi;
		RECT        rc;

		// Get the nearest monitor to the passed rect. 
		hMonitor = ::MonitorFromRect(&windowRect, MONITOR_DEFAULTTONEAREST);

		// Get the work area or entire monitor rect. 
		mi.cbSize = sizeof(mi);
		if (!::GetMonitorInfo(hMonitor, &mi)) 
		{
			EVE_LOG_ERROR("Can't set full screen mode, GetMonitorInfo failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		rc			= mi.rcMonitor;
		m_x			= rc.left;
		m_y			= rc.top;
		m_width		= rc.right  - rc.left;
		m_height	= rc.bottom - rc.top;
		
		if (!::SetWindowLong(m_handle, GWL_STYLE, m_style_fullscreen))
		{
			EVE_LOG_ERROR("Can't set full screen mode, SetWindowLong failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		if (!::SetWindowLong(m_handle, GWL_EXSTYLE, m_ex_style_fullscreen))
		{
			EVE_LOG_ERROR("Can't set full screen mode, SetWindowLong failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		if (!::SetWindowPos(m_handle, HWND_TOPMOST,
							m_x, m_y, m_width, m_height,
							SWP_FRAMECHANGED))
		{
			EVE_LOG_ERROR("Can't set full screen mode, SetWindowPos failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		m_bFullScreen = true;
	}
	// Windowed
	else
	{
		m_x			= m_windowedRect.left;
		m_y			= m_windowedRect.top;
		m_width		= m_windowedRect.right  - m_windowedRect.left;
		m_height	= m_windowedRect.bottom - m_windowedRect.top;
		
		if (!::SetWindowLong(m_handle, GWL_STYLE, m_style))
		{
			EVE_LOG_ERROR("Can't switch to windowed mode, SetWindowLong failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		if (!::SetWindowLong(m_handle, GWL_EXSTYLE, m_exStyle))
		{
			EVE_LOG_ERROR("Can't switch to windowed mode, SetWindowLong failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		if (!::SetWindowPos(m_handle, HWND_NOTOPMOST,
							m_x, m_y, m_width, m_height,
							SWP_FRAMECHANGED))
		{
			EVE_LOG_ERROR("Can't switch to windowed mode, SetWindowPos failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		m_bFullScreen = false;
	}

	m_pFence->unlock();
}



//=================================================================================================
void eve::sys::Window::warpMouse(int32_t p_deportX, int32_t p_deportY)
{
	m_pFence->lock();

	if (!::SetCursorPos(m_x + p_deportX, m_y + p_deportY)) 
	{
		EVE_LOG_ERROR("Can't set cursor position, SetCursorPos failed: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	m_pFence->unlock();
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		 GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::sys::Window::setDragAcceptFiles(bool p_bStatus)
{
	m_pFence->lock();

	SetLastError(0);
	if (p_bStatus)
	{
		::DragAcceptFiles(m_handle, TRUE);
	}
	else 
	{
		::DragAcceptFiles(m_handle, FALSE);
	}

	DWORD err = ::GetLastError();
	if (err != 0) 
	{
		EVE_LOG_ERROR("Can't register whether window accepts dropped files, DragAcceptFiles failed: %s", eve::mess::get_error_msg(err).c_str());
		EVE_ASSERT_FAILURE;
	}

	m_pFence->unlock();
}



//=================================================================================================
void eve::sys::Window::setActive(void)
{
	m_pFence->lock();
	::SetActiveWindow(m_handle);
	m_pFence->unlock();
}

//=================================================================================================
void eve::sys::Window::setForeground(void)
{
	m_pFence->lock();
	::SetForegroundWindow(m_handle);
	m_pFence->unlock();
}



//=================================================================================================
void eve::sys::Window::setSize(uint32_t p_width, uint32_t p_height)
{
	m_pFence->lock();

	if (!m_bFullScreen)
	{
		m_width					= p_width;
		m_height				= p_height;
		m_windowedRect.right	= m_x + m_width;
		m_windowedRect.bottom	= m_y + m_height;

		if (!::SetWindowPos(m_handle, 0,
							0, 0, m_width, m_height,
							SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE))
		{
			EVE_LOG_ERROR("Can't set Window size, SetWindowPos failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
	}
	else
	{
		EVE_LOG_ERROR("Can't set Window size while in full screen mode.");
	}

	m_pFence->unlock();
}

//=================================================================================================
void eve::sys::Window::setWidth(uint32_t p_width)
{
	m_pFence->lock();

	if (!m_bFullScreen)
	{
		m_width					= p_width;
		m_windowedRect.right	= m_x + m_width;

		if (!::SetWindowPos(m_handle, 0,
							0, 0, m_width, m_height,
							SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE))
		{
			EVE_LOG_ERROR("Can't set Window width, SetWindowPos failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
	}
	else
	{
		EVE_LOG_ERROR("Can't set Window width while in full screen mode.");
	}

	m_pFence->unlock();
}

//=================================================================================================-
void eve::sys::Window::setHeight(uint32_t p_height)
{
	m_pFence->lock();

	if (!m_bFullScreen)
	{
		m_height				= p_height;
		m_windowedRect.bottom	= m_y + m_height;

		if (!::SetWindowPos(m_handle, 0,
							0, 0, m_width, m_height,
							SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE))
		{
			EVE_LOG_ERROR("Can't set Window height, SetWindowPos failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
	}
	else
	{
		EVE_LOG_ERROR("Can't set Window height while in full screen mode.");
	}

	m_pFence->unlock();
}



//=================================================================================================
void eve::sys::Window::setPosition(int32_t p_x, int32_t p_y)
{
	m_pFence->lock();

	if (!m_bFullScreen)
	{
		m_x						= p_x;
		m_y						= p_y;
		m_windowedRect.left		= m_x;
		m_windowedRect.right	= m_x + m_width;
		m_windowedRect.top		= m_y;
		m_windowedRect.bottom	= m_y + m_height;

		if (!::SetWindowPos(m_handle, 0,
							m_x, m_y, m_width, m_height,
							SWP_FRAMECHANGED | SWP_NOZORDER))
		{
			EVE_LOG_ERROR("Can't set Window position, SetWindowPos failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
	}
	else
	{
		EVE_LOG_ERROR("Can't set Window position while in full screen mode.");
	}

	m_pFence->unlock();
}

//=================================================================================================
void eve::sys::Window::setPositionX(int32_t p_x )
{
	m_pFence->lock();

	if (!m_bFullScreen)
	{
		m_x						= p_x;
		m_windowedRect.left		= m_x;
		m_windowedRect.right	= m_x + m_width;

		if (!::SetWindowPos(m_handle, 0,
							m_x, m_y, m_width, m_height,
							SWP_FRAMECHANGED | SWP_NOZORDER))
		{
			EVE_LOG_ERROR("Can't set Window position, SetWindowPos failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
	}
	else
	{
		EVE_LOG_ERROR("Can't set Window position while in full screen mode.");
	}

	m_pFence->unlock();
}

//=================================================================================================
void eve::sys::Window::setPositionY(int32_t p_y )
{
	m_pFence->lock();

	if (!m_bFullScreen)
	{
		m_y						= p_y;
		m_windowedRect.top		= m_y;
		m_windowedRect.bottom	= m_y + m_height;

		if (!::SetWindowPos(m_handle, 0,
							m_x, m_y, m_width, m_height,
							SWP_FRAMECHANGED | SWP_NOZORDER))
		{
			EVE_LOG_ERROR("Can't set Window position, SetWindowPos failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
	}
	else
	{
		EVE_LOG_ERROR("Can't set Window position while in full screen mode.");
	}

	m_pFence->unlock();
}



//=================================================================================================
void eve::sys::Window::setTitle( const std::string & p_title)
{
    if( !p_title.empty() )
	{
		// Grab title as char array
		if (m_title)
		{
			EVE_RELEASE_PTR_C(m_title);
		}
		m_title = (char*)malloc(sizeof(char) * (p_title.size()+1));
		strcpy(m_title, p_title.c_str());

		const size_t size = strlen(p_title.c_str()) + 1;
		wchar_t * unicodeTitle = (wchar_t*)malloc(sizeof(wchar_t) * size);
		mbstowcs( unicodeTitle, p_title.c_str(), size );

		// Set window title
		if (!::SetWindowTextW(m_handle, unicodeTitle))
		{
			EVE_LOG_ERROR("Can't set Window title, SetWindowText failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		// Free mem
		free(unicodeTitle);
	}
}

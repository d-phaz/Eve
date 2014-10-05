
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
	, m_title()

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
	// Window style
	m_style		= WS_OVERLAPPEDWINDOW;
	m_exStyle	= WS_EX_OVERLAPPEDWINDOW;

	// Generate per-instance unique classname
	wchar_t classname[sizeof(eve::sys::Window*) * 2 + 2]; // we add 2 chars to the window class name 
	genClassNameStr(this, classname);

	// Get system module handle
	m_hinstance = ::GetModuleHandleW(0);
	if (!m_hinstance) 
	{
		EVE_LOG_ERROR( "Could not get system module handle: %s", eve::mess::get_error_msg().c_str());
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

	// Window client area
	if (::SetRect(&m_windowedRect, m_x, m_y, m_x + m_width, m_y + m_height) == 0) 
	{
		EVE_LOG_ERROR("Can't initialize window bounds rectangle, error: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	if (::AdjustWindowRectEx(&m_windowedRect, m_style, false, m_exStyle) == 0)
	{
		EVE_LOG_ERROR("Can't initialize window bounds rectangle, error: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
	// Update values based on styled rect
	m_x			= m_windowedRect.left;
	m_y			= m_windowedRect.top;
	m_width		= m_windowedRect.right - m_windowedRect.left;
	m_height	= m_windowedRect.bottom - m_windowedRect.top;

	
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
	
	//// Set window user data.
	//LONG_PTR ret	= ::SetWindowLongPtrW(m_handle, 0, reinterpret_cast<LONG_PTR>(this));
	//DWORD err		= ::GetLastError();
	//if (ret == 0 && err != 0)
	//{
	//	EVE_LOG_ERROR("Can't set system Window user data: %s", eve::mess::get_error_msg(err).c_str());
	//	EVE_ASSERT_FAILURE;
	//}

	// Track mouse event to receive WM_MOUSELEAVE events.
	TRACKMOUSEEVENT tme;
	tme.cbSize		= sizeof(TRACKMOUSEEVENT);
	tme.dwFlags		= TME_LEAVE;
	tme.hwndTrack	= m_handle;

	if (::TrackMouseEvent(&tme) == 0) 
	{
		EVE_LOG_ERROR("Can't track system Window mouse events: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}


	// Create fence.
	m_pFence = EVE_CREATE_PTR(eve::thr::SpinLock);

	// Activate drag and drop.
	this->setDragAcceptFiles(true);
}

//=================================================================================================
void eve::sys::Window::release(void)
{
	// Release fence.
	EVE_RELEASE_PTR(m_pFence);

	// Destroy system window.
	if (::DestroyWindow(m_handle) == 0)
	{
		EVE_LOG_ERROR("DestroyWindow() failed with error %s.", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
}



//=================================================================================================
void eve::sys::Window::show(void)
{
	m_pFence->lock();
	::ShowWindow(m_handle, SW_SHOWNORMAL);
	m_pFence->unlock();
}

//=================================================================================================
void eve::sys::Window::hide(void)
{
	m_pFence->lock();
	::ShowWindow(m_handle, SW_HIDE);
	m_pFence->unlock();
}



//=================================================================================================
void eve::sys::Window::minimize(void)
{
	m_pFence->lock();
	::ShowWindow(m_handle, SW_SHOWMINIMIZED);
	m_pFence->unlock();
}

//=================================================================================================
void eve::sys::Window::restore(void)
{
	m_pFence->lock();
	::ShowWindow(m_handle, SW_RESTORE);
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
		if (::GetWindowRect(m_handle, &m_windowedRect) == 0)
		{
			EVE_LOG_ERROR("Can't set full screen mode, GetWindowRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		// Detect on which monitor to set full screen
		HMONITOR	hMonitor;
		MONITORINFO mi;
		RECT        rc;
		// Get the nearest monitor to the passed rect. 
		hMonitor = ::MonitorFromRect(&m_windowedRect, MONITOR_DEFAULTTONEAREST);
		// Get the work area or entire monitor rect. 
		mi.cbSize = sizeof(mi);
		if (!::GetMonitorInfo(hMonitor, &mi)) 
		{
			EVE_LOG_ERROR("Can't set full screen mode, GetMonitorInfo() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Update size and position from monitor rect.
		rc			= mi.rcMonitor;
		m_x			= rc.left;
		m_y			= rc.top;
		m_width		= rc.right  - rc.left;
		m_height	= rc.bottom - rc.top;
		
		// Set window style to full-screen style (no title bar, no thick-frame, no border)
		if (::SetWindowLongW(m_handle, GWL_STYLE, m_style_fullscreen) == 0)
		{
			EVE_LOG_ERROR("Can't set full screen mode, SetWindowLongW() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		if (::SetWindowLongW(m_handle, GWL_EXSTYLE, m_ex_style_fullscreen) == 0)
		{
			EVE_LOG_ERROR("Can't set full screen mode, SetWindowLongW() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		// Update window.
		if (::SetWindowPos(m_handle, HWND_TOP,
						   m_x, m_y, m_width, m_height,
						   SWP_FRAMECHANGED | SWP_SHOWWINDOW) == 0)
		{
			EVE_LOG_ERROR("Can't set full screen mode, SetWindowPos() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		m_bFullScreen = true;
	}
	// Windowed
	else
	{
		// Before scale values.
		m_x			= m_windowedRect.left;
		m_y			= m_windowedRect.top;
		m_width		= m_windowedRect.right  - m_windowedRect.left;
		m_height	= m_windowedRect.bottom - m_windowedRect.top;
		
		// Set window style back to windowed style.
		if (::SetWindowLongW(m_handle, GWL_STYLE, m_style) == 0)
		{
			EVE_LOG_ERROR("Can't switch to windowed mode, SetWindowLongW failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		if (::SetWindowLongW(m_handle, GWL_EXSTYLE, m_exStyle) == 0)
		{
			EVE_LOG_ERROR("Can't switch to windowed mode, SetWindowLongW failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		// Update window.
		if (::SetWindowPos(m_handle, HWND_TOP,
						   m_x, m_y, m_width, m_height,
						   SWP_FRAMECHANGED | SWP_SHOWWINDOW) == 0)
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

	if (::SetCursorPos(m_x + p_deportX, m_y + p_deportY) == 0) 
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

	::SetLastError(0);
	p_bStatus ? ::DragAcceptFiles(m_handle, TRUE) : ::DragAcceptFiles(m_handle, FALSE);

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
		// Create rect.
		RECT tRect;
		if (::SetRect(&tRect, 0, 0, p_width, p_height) == 0) 
		{
			EVE_LOG_ERROR("Can't set size, SetRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Adjust rect to windowed style.
		if (::AdjustWindowRectEx(&tRect, m_style, false, m_exStyle) == 0)
		{
			EVE_LOG_ERROR("Can't set size, AdjustWindowRectEx() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		// Update window.
		if (::SetWindowPos(m_handle, 0,
						   0, 0, tRect.right - tRect.left, tRect.bottom - tRect.top,
						   SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE) == 0)
		{
			EVE_LOG_ERROR("Can't set Window size, SetWindowPos() failed: %s", eve::mess::get_error_msg().c_str());
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
		// Grab active client rect.
		RECT tRect;
		if (::GetClientRect(m_handle, &tRect) == 0)
		{
			EVE_LOG_ERROR("Can't set Window width, GetClientRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Create new sized rect.
		RECT tNewRect;
		if (::SetRect(&tNewRect, 0, 0, p_width, tRect.bottom-tRect.top) == 0)
		{
			EVE_LOG_ERROR("Can't set Window width, SetRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Adjust rect to windowed style.
		if (::AdjustWindowRectEx(&tNewRect, m_style, false, m_exStyle) == 0)
		{
			EVE_LOG_ERROR("Can't set width, AdjustWindowRectEx() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		// Update window.
		if (::SetWindowPos(m_handle, 0,
						   0, 0, tNewRect.right, tNewRect.bottom,
						   SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE) == 0)
		{
			EVE_LOG_ERROR("Can't set Window width, SetWindowPos() failed: %s", eve::mess::get_error_msg().c_str());
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
		// Grab active client rect.
		RECT tRect;
		if (::GetClientRect(m_handle, &tRect) == 0)
		{
			EVE_LOG_ERROR("Can't set Window height, GetClientRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Create new sized rect.
		RECT tNewRect;
		if (::SetRect(&tNewRect, 0, 0, tRect.right-tRect.left, p_height) == 0)
		{
			EVE_LOG_ERROR("Can't set Window height, SetRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Adjust rect to windowed style.
		if (::AdjustWindowRectEx(&tNewRect, m_style, false, m_exStyle) == 0)
		{
			EVE_LOG_ERROR("Can't set height, AdjustWindowRectEx() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		// Update window.
		if (::SetWindowPos(m_handle, 0,
						   0, 0, tNewRect.right, tNewRect.bottom,
						   SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE) == 0)
		{
			EVE_LOG_ERROR("Can't set Window height, SetWindowPos() failed: %s", eve::mess::get_error_msg().c_str());
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
void eve::sys::Window::getSize(uint32_t &p_width, uint32_t &p_height)
{
	m_pFence->lock();

	RECT tRect;
	if (::GetClientRect(m_handle, &tRect) == 0)
	{
		EVE_LOG_ERROR("Can't get Window size, GetClientRect() failed: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	m_pFence->unlock();

	p_width  = tRect.right - tRect.left;
	p_height = tRect.bottom - tRect.top;
}
//=================================================================================================
const uint32_t eve::sys::Window::getWidth(void)	
{
	m_pFence->lock();
	RECT tRect;
	if (::GetClientRect(m_handle, &tRect) == 0)
	{
		EVE_LOG_ERROR("Can't get Window width, GetClientRect() failed: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
	m_pFence->unlock();

	return (tRect.right - tRect.left);
}
//=================================================================================================
const uint32_t eve::sys::Window::getHeight(void) 
{
	m_pFence->lock();
	RECT tRect;
	if (::GetClientRect(m_handle, &tRect) == 0)
	{
		EVE_LOG_ERROR("Can't get Window height, GetClientRect() failed: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
	m_pFence->unlock();

	return (tRect.bottom - tRect.top);
}



//=================================================================================================
void eve::sys::Window::setPosition(int32_t p_x, int32_t p_y)
{
	m_pFence->lock();

	if (!m_bFullScreen)
	{
		// Grab active client rect.
		RECT tRect;
		if (::GetClientRect(m_handle, &tRect) == 0)
		{
			EVE_LOG_ERROR("Can't set Window position, GetClientRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Create new sized rect.
		RECT tNewRect;
		if (::SetRect(&tNewRect, p_x, p_y, tRect.right-tRect.left, tRect.bottom-tRect.top) == 0)
		{
			EVE_LOG_ERROR("Can't set Window position, SetRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Adjust rect to windowed style.
		if (::AdjustWindowRectEx(&tNewRect, m_style, false, m_exStyle) == 0)
		{
			EVE_LOG_ERROR("Can't set position, AdjustWindowRectEx() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		// Update window.
		if (::SetWindowPos(m_handle, 0,
						   tNewRect.left, tNewRect.top, tNewRect.right - tNewRect.left, tNewRect.bottom - tNewRect.top,
						   SWP_FRAMECHANGED | SWP_NOZORDER) == 0)
		{
			EVE_LOG_ERROR("Can't set Window position, SetWindowPos() failed: %s", eve::mess::get_error_msg().c_str());
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
		// Grab active client rect.
		RECT tRect;
		if (::GetClientRect(m_handle, &tRect) == 0)
		{
			EVE_LOG_ERROR("Can't set Window position, GetClientRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Create new sized rect.
		RECT tNewRect;
		if (::SetRect(&tNewRect, p_x, tRect.top, tRect.right - tRect.left, tRect.bottom - tRect.top) == 0)
		{
			EVE_LOG_ERROR("Can't set Window position, SetRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Adjust rect to windowed style.
		if (::AdjustWindowRectEx(&tNewRect, m_style, false, m_exStyle) == 0)
		{
			EVE_LOG_ERROR("Can't set position, AdjustWindowRectEx() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		// Update window.
		if (::SetWindowPos(m_handle, 0,
						   tNewRect.left, tNewRect.top, tNewRect.right - tNewRect.left, tNewRect.bottom - tNewRect.top,
						   SWP_FRAMECHANGED | SWP_NOZORDER) == 0)
		{
			EVE_LOG_ERROR("Can't set Window position, SetWindowPos() failed: %s", eve::mess::get_error_msg().c_str());
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
		// Grab active client rect.
		RECT tRect;
		if (::GetClientRect(m_handle, &tRect) == 0)
		{
			EVE_LOG_ERROR("Can't set Window position, GetClientRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Create new sized rect.
		RECT tNewRect;
		if (::SetRect(&tNewRect, tRect.left, p_y, tRect.right - tRect.left, tRect.bottom - tRect.top) == 0)
		{
			EVE_LOG_ERROR("Can't set Window position, SetRect() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
		// Adjust rect to windowed style.
		if (::AdjustWindowRectEx(&tNewRect, m_style, false, m_exStyle) == 0)
		{
			EVE_LOG_ERROR("Can't set position, AdjustWindowRectEx() failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}

		// Update window.
		if (::SetWindowPos(m_handle, 0,
						   tNewRect.left, tNewRect.top, tNewRect.right - tNewRect.left, tNewRect.bottom - tNewRect.top,
						   SWP_FRAMECHANGED | SWP_NOZORDER) == 0)
		{
			EVE_LOG_ERROR("Can't set Window position, SetWindowPos() failed: %s", eve::mess::get_error_msg().c_str());
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
void eve::sys::Window::getPosition(int32_t & p_x, int32_t & p_y)
{
	m_pFence->lock();
	RECT tRect;
	if (::GetClientRect(m_handle, &tRect) == 0)
	{
		EVE_LOG_ERROR("Can't get Window position, GetClientRect() failed: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
	m_pFence->unlock();

	p_x = tRect.left;
	p_y = tRect.top;
}

//=================================================================================================
const int32_t eve::sys::Window::getPositionX(void) 
{
	m_pFence->lock();
	RECT tRect;
	if (::GetClientRect(m_handle, &tRect) == 0)
	{
		EVE_LOG_ERROR("Can't get Window position, GetClientRect() failed: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
	m_pFence->unlock();

	return tRect.left;
}

//=================================================================================================
const int32_t eve::sys::Window::getPositionY(void) 
{
	m_pFence->lock();
	RECT tRect;
	if (::GetClientRect(m_handle, &tRect) == 0)
	{
		EVE_LOG_ERROR("Can't get Window position, GetClientRect() failed: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
	m_pFence->unlock();

	return tRect.top;
}



//=================================================================================================
void eve::sys::Window::setTitle(const std::wstring & p_title)
{
    if( !p_title.empty() )
	{
		// Grab title as char array
		m_title = std::wstring(p_title);

		// Set window title
		if (!::SetWindowTextW(m_handle, m_title.c_str()))
		{
			EVE_LOG_ERROR("Can't set Window title, SetWindowText failed: %s", eve::mess::get_error_msg().c_str());
			EVE_ASSERT_FAILURE;
		}
	}
}

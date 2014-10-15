
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
#include "eve/sys/win32/MessagePump.h"

#ifndef __EVE_SYSTEM_EVENT_H__ 
#include "eve/sys/shared/Event.h"
#endif

#ifndef __EVE_SYSTEM_KEYBOARD_H__
#include "eve/sys/win32//Keyboard.h"
#endif

#ifndef __EVE_SYSTEM_MOUSE_H__
#include "eve/sys/shared/Mouse.h"
#endif


eve::sys::MessagePump::HandlerMap eve::sys::MessagePump::m_handlers_map;


//=================================================================================================
eve::sys::MessagePump * eve::sys::MessagePump::create_ptr(HWND p_handle)
{
	eve::sys::MessagePump * ptr = new eve::sys::MessagePump(p_handle);
	ptr->init();
	return ptr;
}

//=================================================================================================
eve::sys::MessagePump::MessagePump(HWND p_handle)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_handle(p_handle)
	, m_pEvent(nullptr)
{}



//=================================================================================================
void eve::sys::MessagePump::init(void)
{
	// Event manager.
	m_pEvent = EVE_CREATE_PTR(eve::sys::Event);

	// Register as event handler.
	eve::sys::MessagePump::register_handler(m_handle, this);

	// Stock previous window procedure and set new one.
	m_prevWndProc = (WNDPROC)::SetWindowLongPtrW(m_handle, GWLP_WNDPROC, (LONG_PTR)eve::sys::MessagePump::wndProc);

	// Avoid window procedure recursion.
	EVE_ASSERT(m_prevWndProc != eve::sys::MessagePump::wndProc);
}

//=================================================================================================
void eve::sys::MessagePump::release(void)
{
	// Event manager.
	EVE_RELEASE_PTR(m_pEvent);

	// Set default window procedure back.
	::SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)m_prevWndProc);
	m_prevWndProc = 0;

	// Unregister from handler map.
	eve::sys::MessagePump::unregister_handler(m_handle);
	m_handle = 0;
}



//=================================================================================================
void eve::sys::MessagePump::register_handler(HWND p_hWnd, eve::sys::MessagePump * p_pHandler)
{
	eve::sys::MessagePump::HandlerMap::const_iterator it = m_handlers_map.find(p_hWnd);
	EVE_ASSERT(it == m_handlers_map.end());

	m_handlers_map[p_hWnd] = p_pHandler;
}

//=================================================================================================
void eve::sys::MessagePump::unregister_handler(HWND p_hWnd)
{
	eve::sys::MessagePump::HandlerMap::const_iterator it = m_handlers_map.find(p_hWnd);
	EVE_ASSERT(it != m_handlers_map.end());

	m_handlers_map.erase(it);
}

//=================================================================================================
eve::sys::MessagePump * eve::sys::MessagePump::get_handler(HWND p_hWnd)
{
	eve::sys::MessagePump::HandlerMap::const_iterator it = m_handlers_map.find(p_hWnd);
	EVE_ASSERT(it != m_handlers_map.end());

	eve::sys::MessagePump * ptr = it->second;
	return ptr;
}



//=================================================================================================
uint32_t eve::sys::MessagePump::wparam2unicode(WPARAM p_wParam)
{
	uint16_t lo  = p_wParam & 0xFFFF;
	uint16_t hi  = (p_wParam & 0xFFFF0000) >> 16;
	uint32_t ret = 0;
	
	// Convert from UTF-16 to Unicode code point
	if (lo < 0xD8000 || lo > 0xDFFF)
	{
		ret = lo;
	}
	else
	{
		ret = ((lo & 0x3FF) << 10) | (hi & 0x3FF) + 0x10000;
	}
	
	return ret;
}



//=================================================================================================
LRESULT CALLBACK eve::sys::MessagePump::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	eve::sys::MessagePump * handler = eve::sys::MessagePump::get_handler(hWnd);
	//if (!handler)
	//{
	//	EVE_LOG_ERROR("Unregistered window message target.");
	//	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	//}

	return handler->cb_wndProc(hWnd, uMsg, wParam, lParam);
}

//=================================================================================================
LRESULT CALLBACK eve::sys::MessagePump::cb_wndProc(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Handle event here.
	std::pair<LRESULT, bool> result = this->handleEvent(p_hWnd, p_uMsg, p_wParam, p_lParam);
	LRESULT L_result = result.first;
	
	// If event was not handled fall back to default system handler method.
	if (!result.second) 
	{
		L_result = ::CallWindowProcW(m_prevWndProc, p_hWnd, p_uMsg, p_wParam, p_lParam);
	}

	return L_result;
}



//=================================================================================================
std::pair<LRESULT, bool> eve::sys::MessagePump::handleEvent(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	LRESULT res = TRUE;
	bool handled = true;

	switch (p_uMsg)
    {
        case WM_MOUSEMOVE:		res = this->handleMouseMotion(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_LBUTTONDOWN:	
		case WM_MBUTTONDOWN:	
		case WM_RBUTTONDOWN:	
		case WM_XBUTTONDOWN:
        case WM_MOUSEWHEEL:		
		case WM_MOUSEHWHEEL:	res = this->handleMouseDown(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_LBUTTONUP:	
		case WM_MBUTTONUP:	
		case WM_RBUTTONUP:	
		case WM_XBUTTONUP:		res = this->handleMouseUp(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_LBUTTONDBLCLK:	
		case WM_MBUTTONDBLCLK:	
		case WM_RBUTTONDBLCLK:	
		case WM_XBUTTONDBLCLK:	res = this->handleMouseDoubleClick(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_KEYDOWN:		res = this->handleKeyDown(p_hWnd, p_uMsg, p_wParam, p_lParam); break;
		//case WM_SYSKEYDOWN:	res = this->handleKeyDown(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_KEYUP:			res = this->handleKeyUp(p_hWnd, p_uMsg, p_wParam, p_lParam); break;
		//case WM_SYSKEYUP:		res = this->handleKeyUp(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_DEADCHAR:	
		case WM_SYSDEADCHAR:
		case WM_CHAR:			res = this->handleChar(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_PAINT:			res = this->handlePaint(p_hWnd, p_uMsg, p_wParam, p_lParam); break;
		case WM_ERASEBKGND:		res = this->handleEraseBackground(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_DROPFILES:		res = this->handleDrop(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_ENTERSIZEMOVE:	res = this->handleEnterSizeMove(p_hWnd, p_uMsg, p_wParam, p_lParam); break;
		case WM_EXITSIZEMOVE:	res = this->handleExitSizeMove(p_hWnd, p_uMsg, p_wParam, p_lParam); break;
		case WM_SIZING:			res = this->handleSizing(p_hWnd, p_uMsg, p_wParam, p_lParam); break;
		case WM_SIZE:			res = this->handleSize(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_MOVE:			res = this->handleMove(p_hWnd, p_uMsg, p_wParam, p_lParam); break;
		case WM_MOVING:			res = this->handleMoving(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_SETFOCUS:		res = this->handleFocusGot(p_hWnd, p_uMsg, p_wParam, p_lParam); break;
		case WM_KILLFOCUS:		res = this->handleFocusLost(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_CLOSE:			res = this->handleClose(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		case WM_COMPACTING:		res = this->handleCompacting(p_hWnd, p_uMsg, p_wParam, p_lParam); break;

		default:				handled = false;	break;
    }
	return std::pair<LRESULT, bool>(res, handled);
}



//=================================================================================================
LRESULT eve::sys::MessagePump::handlePaint(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	// ValidateRect prevents Windows from resending WM_PAINT
	RECT rect, *ptr = 0;
	if (::GetUpdateRect(p_hWnd, &rect, FALSE))
	{
		::ValidateRect(p_hWnd, &rect);
		ptr = &rect;
	}

	return 0;
}

//=================================================================================================
LRESULT eve::sys::MessagePump::handleEraseBackground(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Block further system actions.
	return TRUE;
}



//=================================================================================================
LRESULT eve::sys::MessagePump::handleKeyDown(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	bool filter;	
	eve::sys::Key translated = eve::sys::translate_key(p_hWnd, p_uMsg, p_wParam, p_lParam, filter);
	if(!filter) {
		m_pEvent->notifyKeyPressed(translated);
	}

	return 0;
}

//=================================================================================================
LRESULT eve::sys::MessagePump::handleKeyUp(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	bool filter;
	eve::sys::Key translated = eve::sys::translate_key(p_hWnd, p_uMsg, p_wParam, p_lParam, filter);
	if (!filter) {
		m_pEvent->notifyKeyReleased(translated);
	}

	return 0;
}

//=================================================================================================
LRESULT eve::sys::MessagePump::handleChar(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	m_pEvent->notifyKeyInput(this->wparam2unicode(p_wParam));
	return 0;
}



//=================================================================================================
LRESULT eve::sys::MessagePump::handleMouseDown(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Keep mouse tracking even if out of the window.
	::SetCapture(p_hWnd);	

	int32_t x = LOWORD(p_lParam);
	int32_t y = HIWORD(p_lParam);

	eve::sys::MouseButton btn;
	switch (p_uMsg)
	{
	case WM_LBUTTONDOWN:		btn = eve::sys::btn_Left;		break;
	case WM_MBUTTONDOWN:		btn = eve::sys::btn_Middle;		break;
	case WM_RBUTTONDOWN:		btn = eve::sys::btn_Right;		break;
	case WM_XBUTTONDOWN:		btn = eve::sys::btn_X;			break;
	case WM_MOUSEWHEEL:			btn = GET_WHEEL_DELTA_WPARAM(p_wParam) < 0 ? eve::sys::btn_WheelDown  : eve::sys::btn_WheelUp;		break;
	case WM_MOUSEHWHEEL:		btn = GET_WHEEL_DELTA_WPARAM(p_wParam) < 0 ? eve::sys::btn_ScrollLeft : eve::sys::btn_ScrollRight;	break;
	default:					btn = eve::sys::btn_Unused;		break;
	}

	m_pEvent->notifyMouseDown(btn, x, y);

	return 0;
}

//=================================================================================================
LRESULT eve::sys::MessagePump::handleMouseUp(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Release out of the window mouse tracking.
	::ReleaseCapture();
	
	int32_t x = LOWORD(p_lParam);
	int32_t y = HIWORD(p_lParam);

	eve::sys::MouseButton btn;
	switch (p_uMsg)
	{
	case WM_LBUTTONUP:		btn = eve::sys::btn_Left;		break;
	case WM_MBUTTONUP:		btn = eve::sys::btn_Middle;		break;
	case WM_RBUTTONUP:		btn = eve::sys::btn_Right;		break;
	case WM_XBUTTONUP:		btn = eve::sys::btn_X;			break;
	default:				btn = eve::sys::btn_Unused;		break;
	}

	m_pEvent->notifyMouseUp(btn, x, y);

	return 0;
}

//=================================================================================================
LRESULT eve::sys::MessagePump::handleMouseDoubleClick(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	int32_t x = LOWORD(p_lParam);
	int32_t y = HIWORD(p_lParam);

	eve::sys::MouseButton btn;
	switch (p_uMsg)
	{
	case WM_LBUTTONDBLCLK:		btn = eve::sys::btn_Left;		break;
	case WM_MBUTTONDBLCLK:		btn = eve::sys::btn_Middle;		break;
	case WM_RBUTTONDBLCLK:		btn = eve::sys::btn_Right;		break;
	case WM_XBUTTONDBLCLK:		btn = eve::sys::btn_X;			break;
	default:					btn = eve::sys::btn_Unused;		break;
	}

	m_pEvent->notifyMouseDoubleClick(btn, x, y);

	return 0;
}

//=================================================================================================
LRESULT eve::sys::MessagePump::handleMouseMotion(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	int32_t x = LOWORD(p_lParam);
	int32_t y = HIWORD(p_lParam);

	eve::sys::MouseButton btn;
	switch (p_wParam)
	{
	case MK_LBUTTON:		btn = eve::sys::btn_Left;		break;
	case MK_MBUTTON:		btn = eve::sys::btn_Middle;		break;
	case MK_RBUTTON:		btn = eve::sys::btn_Right;		break;
	default:				btn = eve::sys::btn_Unused;		break;
	}

	if (btn == eve::sys::btn_Unused)
	{
		m_pEvent->notifyMousePassiveMotion(x, y);
	}
	else
	{
		m_pEvent->notifyMouseMotion(btn, x, y);
	}

	return 0;
}



//=================================================================================================
LRESULT eve::sys::MessagePump::handleFocusGot(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	m_pEvent->notifyWindowFocusGot();
	return 0;
}

//=================================================================================================
LRESULT eve::sys::MessagePump::handleFocusLost(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	m_pEvent->notifyWindowFocusLost();
	return 0;
}



//=================================================================================================
LRESULT eve::sys::MessagePump::handleEnterSizeMove(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Nothing to do for now.
	return 0;
}

//=================================================================================================
LRESULT eve::sys::MessagePump::handleExitSizeMove(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Nothing to do for now.
	return 0;
}

//=================================================================================================
LRESULT eve::sys::MessagePump::handleSizing(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Windows system message pump sends WM_SIZE and WM_SIZING events together.
	// WM_SIZING is invalidated and we deal with size change(s) in handleSize()
	return TRUE;
}

//=================================================================================================
LRESULT eve::sys::MessagePump::handleSize(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	int32_t width  = (int32_t)LOWORD(p_lParam); 
	int32_t height = (int32_t)HIWORD(p_lParam);
	m_pEvent->notifyWindowResize(width, height);

	return 0;
}



//=================================================================================================
LRESULT eve::sys::MessagePump::handleMoving(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Windows system message pump sends WM_MOVE and WM_MOVING events together.
	// WM_MOVING is invalidated and we deal with window move(s) in handleMove()
	return TRUE;
}

//=================================================================================================
LRESULT eve::sys::MessagePump::handleMove(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	int32_t xPos = (int32_t)LOWORD(p_lParam);
	int32_t yPos = (int32_t)HIWORD(p_lParam);
	m_pEvent->notifyWindowMove(xPos, yPos);

	return 0;
}



//=================================================================================================
LRESULT eve::sys::MessagePump::handleDrop(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	HDROP query = (HDROP)p_wParam;
	
	// Get mouse position on drop.
	POINT pt;
	::DragQueryPoint( query, &pt ); 
	
	// Get file(s) info.
	uint32_t count = ::DragQueryFileW( query, 0xFFFFFFFF, 0, 0 );
	
	// Files vector.
	std::vector<std::wstring> vecFiles;
	vecFiles.reserve(count);

	uint32_t n = 0;
	wchar_t * name = 0;
	while ( n < count ) 
	{
		uint32_t nChar = ::DragQueryFileW( query, n, NULL, 0 );
			
		name = (wchar_t*)malloc((nChar + 1) * sizeof(wchar_t));
		::DragQueryFileW(query, n, name, nChar + 1);

		vecFiles.push_back(std::wstring(name));
		free(name);

		n++;
	}
	
	::DragFinish( query );
	
	m_pEvent->notifyFileDropped(pt.x, pt.y, count, vecFiles);

	return 0;
}



//=================================================================================================
LRESULT eve::sys::MessagePump::handleCompacting(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	EVE_LOG_WARNING("System detected more than 12.5 percent of system time over a 30 to 60 second interval is being spent compacting memory. \nSystem memory is low.");
	return 0;
}



//=================================================================================================
LRESULT eve::sys::MessagePump::handleClose(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	m_pEvent->notifyWindowClose();
	return 0;
}

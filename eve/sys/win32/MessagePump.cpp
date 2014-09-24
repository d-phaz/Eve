
// Main header
#include "eve/sys/win32/MessagePump.h"

#ifndef __EVE_THREADING_INCLUDES_H__
#include "eve/thr/Includes.h"
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
{}



//=================================================================================================
void eve::sys::MessagePump::init(void)
{
	// Register as event handler.
	eve::sys::MessagePump::register_handler(m_handle, this);

	// Stock previous window procedure and set new one.
	m_prevWndProc = (WNDPROC)::SetWindowLongPtrW(m_handle, GWLP_WNDPROC, (LONG_PTR)eve::sys::MessagePump::wndProc);

	// Avoid window procedure recursion
	EVE_ASSERT(m_prevWndProc != eve::sys::MessagePump::wndProc);
}

//=================================================================================================
void eve::sys::MessagePump::release(void)
{
	// Set default window procedure back.
	::SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)m_prevWndProc);

	// Unregister from handler map.
	eve::sys::MessagePump::unregister_handler(m_handle);
}



//=================================================================================================
void eve::sys::MessagePump::register_handler(HWND hWnd, eve::sys::MessagePump* handler)
{
	EVE_ASSERT(m_handlers_map.find(hWnd) == m_handlers_map.end());
	m_handlers_map[hWnd] = handler;
}

//=================================================================================================
void eve::sys::MessagePump::unregister_handler(HWND hWnd)
{
	EVE_ASSERT(m_handlers_map.find(hWnd) != m_handlers_map.end());
	m_handlers_map.erase(hWnd);
}

//=================================================================================================
eve::sys::MessagePump * eve::sys::MessagePump::get_handler(HWND p_hWnd)
{
	EVE_ASSERT(m_handlers_map.find(p_hWnd) != m_handlers_map.end())

	eve::sys::MessagePump * ptr = m_handlers_map[p_hWnd];
	return ptr;
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
LRESULT CALLBACK eve::sys::MessagePump::cb_wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT L_result = 0;
	std::pair<LRESULT, bool> result;

	//result = m_pNode->getEventReader()->handleEvent(*m_pNode->getEventListener(), hWnd, message, wParam, lParam);

	//L_result = result.first;
	//if (!result.second) {
		L_result = ::CallWindowProcW(m_prevWndProc, hWnd, message, wParam, lParam);
	//}

	return L_result;
}

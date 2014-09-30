
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

	// Avoid window procedure recursion.
	EVE_ASSERT(m_prevWndProc != eve::sys::MessagePump::wndProc);
}

//=================================================================================================
void eve::sys::MessagePump::release(void)
{
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
	EVE_ASSERT(it != m_handlers_map.end())

	eve::sys::MessagePump * ptr = it->second;
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
LRESULT CALLBACK eve::sys::MessagePump::cb_wndProc(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	LRESULT L_result = 0;
	std::pair<LRESULT, bool> result;

	// Handle event here.
	result = this->handleEvent(p_hWnd, p_uMsg, p_wParam, p_lParam);
	L_result = result.first;
	
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
	return std::pair<LRESULT, bool>(0, false);
}


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

#pragma once
#ifndef __EVE_SYSTEM_MESSAGE_PUMP_H__
#define __EVE_SYSTEM_MESSAGE_PUMP_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif


namespace eve
{
	namespace sys
	{
		/** 
		* \class eve::sys::MessagePump
		*
		* \brief Manage event translation and dispatch.
		* Message pump events are linked to window handle (aka HWND).
		*
		* \note extends eve::mem::Pointer
		*/
		class MessagePump final
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:
			/** \brief Handler map containing HWN and eve::sys::Window pointer pairs type definition. */
			typedef stdext::hash_map<HWND, eve::sys::MessagePump*> HandlerMap;
			static HandlerMap				m_handlers_map;			//!< Static handler map.

		private:
			WNDPROC							m_prevWndProc;			//!< Previous window procedure called by message pump.
			HWND							m_handle;				//!< System window handle.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(MessagePump);
			EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(MessagePump);

		public:
			/**
			* \brief Create and return new pointer.
			* \param p_handle linked system window handle.
			*/
			static MessagePump * create_ptr(HWND p_handle);


		private:
			/** 
			* \brief Class constructor.
			* \param p_handle linked system window handle.
			*/
			MessagePump(HWND p_handle);


		private:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		private:
			/** \! Register an event handler */
			static void register_handler(HWND p_hWnd, MessagePump * p_pHandler);
			/** \! Unregister an event handler */
			static void unregister_handler(HWND p_hWnd);

			/** \! Get event handler based on window handle */
			static MessagePump * get_handler(HWND p_hWnd);


		private:
			/** \brief Static window procedure used to intercept and dispatch events, this method requires this exact signature. */
			static LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			/** \brief Handler dedicated window procedure. */
			LRESULT CALLBACK cb_wndProc(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);


		private:
			/** \brief System event handler. */
			std::pair<LRESULT, bool> handleEvent(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			

			LRESULT handleEnterSizeMove(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleExitSizeMove(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleSizing(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleSize(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);

			LRESULT handlePaint(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleEraseBkgnd(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			
			LRESULT handleKey(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleChar(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			
			LRESULT handleMouseDown(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleMouseUp(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleMouseMotion(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleMouseEnter(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleMouseLeave(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);

			LRESULT handleFocus(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleGetMinMaxInfo(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleDrop(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleClose(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			LRESULT handleIdle(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);

		}; // class MessagePump

	} // namespace sys

} // namespace eve

#endif // __EVE_SYSTEM_MESSAGE_PUMP_H__

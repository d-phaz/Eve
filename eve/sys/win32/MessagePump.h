
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

#ifndef __EVE_SYSTEM_EVENT_H__ 
#include "eve/sys/shared/Event.h"
#endif

#ifndef __EVE_MEMORY_POINTER_H__
#include "eve/mem/Pointer.h"
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

		private:
			eve::sys::Event *				m_pEvent;				//!< Manage listeners and dispatch message pump events.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(MessagePump);
			EVE_PUBLIC_DESTRUCTOR(MessagePump);

		public:
			/**
			* \brief Create and return new pointer.
			* \param p_handle linked system window handle.
			*/
			static MessagePump * create_ptr(HWND p_handle);


		public:
			/** 
			* \brief Class constructor.
			* \param p_handle linked system window handle.
			*/
			explicit MessagePump(HWND p_handle);


		public:
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
			/** \brief Convert WPARAM to unicode character. */
			uint32_t wparam2unicode(WPARAM p_wParam);


		private:
			/** \brief Static window procedure used to intercept and dispatch events, this method requires this exact signature. */
			static LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			/** \brief Handler dedicated window procedure. */
			LRESULT CALLBACK cb_wndProc(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);


		private:
			/** \brief System event handler. */
			std::pair<LRESULT, bool> handleEvent(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);


			/** \brief System paint message handler; does nothing except catch message and prevent further action. */
			LRESULT handlePaint(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief System erase background handler; does nothing except catch message and prevent further action. */
			LRESULT handleEraseBackground(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);


			/** \brief Keyboard key up event handler. */
			LRESULT handleKeyDown(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief Keyboard key down event handler. */
			LRESULT handleKeyUp(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief Keyboard char key pressed event handler (text input). */
			LRESULT handleChar(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);

			
			/** \brief Mouse down event handler. */
			LRESULT handleMouseDown(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief Mouse wheel event handler. */
			LRESULT handleMouseWheel(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief Mouse up event handler. */
			LRESULT handleMouseUp(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief Mouse double click event handler. */
			LRESULT handleMouseDoubleClick(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief Mouse move event handler. */
			LRESULT handleMouseMotion(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);


			/** \brief Focus gained event handler. */
			LRESULT handleFocusGot(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief Focus lost event handler. */
			LRESULT handleFocusLost(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);


			/** \brief Window enter size move event handler. */
			LRESULT handleEnterSizeMove(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief Window exit size move event handler. */
			LRESULT handleExitSizeMove(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief Window sizing event handler. */
			LRESULT handleSizing(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief Window size changed event handler. */
			LRESULT handleSize(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);


			/** \brief Window moving event handler. */
			LRESULT handleMoving(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);
			/** \brief Window moved event handler. */
			LRESULT handleMove(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);


			/** \brief File dropped event handler. */
			LRESULT handleDrop(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);


			/** \brief System compacting cause running out of memory event handler. */
			LRESULT handleCompacting(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);


			/** \brief Window close event handler. */
			LRESULT handleClose(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);


		public:
			/**
			* \brief Register listener class to events.
			* Listener class must provide event handler methods using the following signatures:
			*		void cb_evtFileDrop(eve::evt::FileEventArgs & p_args)
			*		void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtTextInput(eve::evt::TextEventArgs & p_args)
			*		void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMotion(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg)
			*		void cb_evtWindowFocusGot(void)
			*		void cb_evtWindowFocusLost(void)
			*		void cb_evtWindowClose(void)
			*/
			template<class ListenerClass>
			void registerListener(ListenerClass * p_pListener);
			/**
			* \brief Unregister listener class to events.
			* Listener class must provide event handler methods using the following signatures:
			*		void cb_evtFileDrop(eve::evt::FileEventArgs & p_args)
			*		void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtTextInput(eve::evt::TextEventArgs & p_args)
			*		void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMotion(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg)
			*		void cb_evtWindowFocusGot(void)
			*		void cb_evtWindowFocusLost(void)
			*		void cb_evtWindowClose(void)
			*/
			template<class ListenerClass>
			void unregisterListener(ListenerClass * p_pListener);

		}; // class MessagePump

	} // namespace sys

} // namespace eve


//=================================================================================================
template<class ListenerClass>
void eve::sys::MessagePump::registerListener(ListenerClass * p_pListener)
{
	m_pEvent->registerEvents(p_pListener);
}

//=================================================================================================
template<class ListenerClass>
void eve::sys::MessagePump::unregisterListener(ListenerClass * p_pListener)
{
	m_pEvent->unregisterEvents(p_pListener);
}

#endif // __EVE_SYSTEM_MESSAGE_PUMP_H__

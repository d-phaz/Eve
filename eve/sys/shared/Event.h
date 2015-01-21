
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
#ifndef __EVE_SYSTEM_EVENT_H__ 
#define __EVE_SYSTEM_EVENT_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif

#ifndef __EVE_EVT_INCLUDES_H__
#include "eve/evt/Includes.h"
#endif


namespace eve
{
	namespace sys
	{
		/** 
		* \class eve::sys::Event
		*
		* \brief User interaction and other system message pump event types, server, notifications.
		*
		* \note extends eve::mem::Pointer
		*/
		class Event final
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:
			eve::evt::FileEvent 								m_fileDropped;			//!< File dropped event.

			eve::evt::KeyEvent 									m_keyPressed;			//!< Key pressed event.
			eve::evt::KeyEvent 									m_keyReleased;			//!< Key released event.
			eve::evt::TextEvent 								m_textInput;			//!< Text input event.

			eve::evt::MouseEvent 								m_mousePassiveMotion;	//!< Mouse passive motion (no mouse button pressed) event.
			eve::evt::MouseEvent 								m_mouseMotion;			//!< Mouse motion (mouse button pressed) event.
			eve::evt::MouseEvent 								m_mouseDown;			//!< Mouse button pressed event.
			eve::evt::MouseEvent								m_mouseDoubleClick;		//!< Mouse double click event.
			eve::evt::MouseEvent 								m_mouseUp;				//!< Mouse button released event.

			eve::evt::TEvent<eve::evt::ResizeEventArgs> 		m_windowResized;		//!< Window resized event.
			eve::evt::TEvent<eve::evt::MoveEventArgs> 			m_windowMoved;			//!< Window moved event.
			eve::evt::TEvent<eve::evt::EventArgs>				m_windowFocusGot;		//!< Window gain focus event.
			eve::evt::TEvent<eve::evt::EventArgs>				m_windowFocusLost;		//!< Window lost focus event.
			eve::evt::TEvent<eve::evt::EventArgs>				m_windowClose;			//!< Window closed event.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Event);
			EVE_PROTECT_DESTRUCTOR(Event);

		private:
			/** \brief Class constructor. */
			explicit Event(void);


		private:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


			///////////////////////////////////////////////////////////////////////////////////////////
			//		FILE EVENTS
			///////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Enable file events dispatch. */
			void enableEventsFile(void);
			/** \brief Disable file events dispatch. */
			void disableEventsFile(void);

			/** \brief Notify file dropped event to all listeners. */
			void notifyFileDropped(int32_t p_x, int32_t p_y, uint32_t p_count, std::vector<std::wstring> & p_files);

			/**
			* \brief Register listener class to file events.
			* Listener class must provide file event handler methods using the following signatures:
			*		void cb_evtFileDrop(eve::evt::FileEventArgs & p_args)
			*/
			template<class ListenerClass>
			void registerEventsFile(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);
			/**
			* \brief Unregister listener class from file events.
			* Listener class must provide file event handler methods using the following signatures:
			*		void cb_evtFileDrop(eve::evt::FileEventArgs & p_args)
			*/
			template<class ListenerClass>
			void unregisterEventsFile(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);


			///////////////////////////////////////////////////////////////////////////////////////////
			//		KEY EVENTS
			///////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \! Enable key events dispatch. */
			void enableEventsKey(void);
			/** \! Disable key events dispatch. */
			void disableEventsKey(void);

			/** \brief Notify key pressed event to all listeners. */
			void notifyKeyPressed(eve::sys::Key p_key, eve::sys::KeyModifier p_modifier, bool p_bRepeat);
			/** \brief Notify key released event to all listeners. */
			void notifyKeyReleased(eve::sys::Key p_key, eve::sys::KeyModifier p_modifier);

			/**
			* \brief Register listener class to key events.
			* Listener class must provide key event handler methods using the following signatures:
			*		void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args)
			*/
			template<class ListenerClass>
			void registerEventsKey(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);
			/**
			* \brief Unregister listener class from key events.
			* Listener class must provide key event handler methods using the following signatures:
			*		void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args)
			*/
			template<class ListenerClass>
			void unregisterEventsKey(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);


			///////////////////////////////////////////////////////////////////////////////////////////
			//		TEXT EVENTS
			///////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \! Enable text events dispatch. */
			void enableEventsText(void);
			/** \! Disable text events dispatch. */
			void disableEventsText(void);

			/** \brief Notify text input event to all listeners. */
			void notifyTextInput(wchar_t p_text, eve::sys::KeyModifier p_modifier, bool p_bRepeat);

			/**
			* \brief Register listener class to text events.
			* Listener class must provide text event handler methods using the following signatures:
			*		void cb_evtTextInput(eve::evt::TextEventArgs & p_args)
			*/
			template<class ListenerClass>
			void registerEventsText(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);
			/**
			* \brief Unregister listener class from text events.
			* Listener class must provide text event handler methods using the following signatures:
			*		void cb_evtTextInput(eve::evt::TextEventArgs & p_args)
			*/
			template<class ListenerClass>
			void unregisterEventsText(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);


			///////////////////////////////////////////////////////////////////////////////////////////
			//		MOUSE EVENTS
			///////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \! Enable mouse events dispatch. */
			void enableEventsMouse(void);
			/** \! Disable mouse events dispatch. */
			void disableEventsMouse(void);

			/** \brief Notify mouse down event to all listeners. */
			void notifyMouseDown(int32_t p_button, int32_t x, int32_t y);
			/** \brief Notify mouse up event to all listeners. */
			void notifyMouseUp(int32_t p_button, int32_t x, int32_t y);
			/** \brief Notify mouse double click event to all listeners. */
			void notifyMouseDoubleClick(int32_t p_button, int32_t x, int32_t y);
			/** \brief Notify mouse motion (mouse button pressed) event to all listeners. */
			void notifyMouseMotion(int32_t p_button, int32_t x, int32_t y);
			/** \brief Notify mouse passive motion (no mouse button pressed) event to all listeners. */
			void notifyMousePassiveMotion(int32_t x, int32_t y);

			/**
			* \brief Register listener class to mouse events.
			* Listener class must provide mouse event handler methods using the following signatures:
			*		void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMotion(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args)
			*/
			template<class ListenerClass>
			void registerEventsMouse(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);
			/**
			* \brief Unregister listener class from mouse events.
			* Listener class must provide mouse event handler methods using the following signatures:
			*		void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMotion(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args)
			*/
			template<class ListenerClass>
			void unregisterEventsMouse(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);


			///////////////////////////////////////////////////////////////////////////////////////////
			//		WINDOW EVENTS
			///////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \! Enable window events dispatch. */
			void enableEventsWindow(void);
			/** \! Disable window events dispatch. */
			void disableEventsWindow(void);

			/** \brief Notify window resize event to all listeners.*/
			void notifyWindowResize(uint32_t p_width, uint32_t p_height);
			/** \brief Notify window move event to all listeners.*/
			void notifyWindowMove(int32_t p_x, int32_t p_y);
			/** \brief Notify window gain focus event to all listeners.*/
			void notifyWindowFocusGot(void);
			/** \brief Notify window lost focus event to all listeners.*/
			void notifyWindowFocusLost(void);
			/** \brief Notify window close event to all listeners.*/
			void notifyWindowClose(void);

			/**
			* \brief Register listener class to window events.
			* Listener class must provide window event handler methods using the following signatures:
			*		void cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg)
			*		void cb_evtWindowMove(eve::evt::ResizeEventArgs & p_arg)
			*		void cb_evtWindowFocusGot(eve::evt::EventArgs & p_arg)
			*		void cb_evtWindowFocusLost(eve::evt::EventArgs & p_arg)
			*		void cb_evtWindowClose(eve::evt::EventArgs & p_arg)
			*/
			template<class ListenerClass>
			void registerEventsWindow(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);
			/**
			* \brief Unregister listener class to window events.
			* Listener class must provide window event handler methods using the following signatures:
			*		void cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg)
			*		void cb_evtWindowMove(eve::evt::ResizeEventArgs & p_arg)
			*		void cb_evtWindowFocusGot(eve::evt::EventArgs & p_arg)
			*		void cb_evtWindowFocusLost(eve::evt::EventArgs & p_arg)
			*		void cb_evtWindowClose(eve::evt::EventArgs & p_arg)
			*/
			template<class ListenerClass>
			void unregisterEventsWindow(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);



			///////////////////////////////////////////////////////////////////////////////////////////
			//		ALL EVENTS
			///////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \! Enable events dispatch. */
			void enableEvents(void);
			/** \! Disable events dispatch. */
			void disableEvents(void);

			/**
			* \brief Register listener class to events.
			* Listener class must provide event handler methods using the following signatures:
			*		void cb_evtFileDrop(eve::evt::FileEventArgs & p_args)
			*		void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtKeyInput(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMotion(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg)
			*		void cb_evtWindowMove(eve::evt::ResizeEventArgs & p_arg)
			*		void cb_evtWindowFocusGot(eve::evt::EventArgs & p_arg)
			*		void cb_evtWindowFocusLost(eve::evt::EventArgs & p_arg)
			*		void cb_evtWindowClose(eve::evt::EventArgs & p_arg)
			*/
			template<class ListenerClass>
			void registerEvents(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);
			/**
			* \brief Unregister listener class to events.
			* Listener class must provide event handler methods using the following signatures:
			*		void cb_evtFileDrop(eve::evt::FileEventArgs & p_args)
			*		void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtKeyInput(eve::evt::KeyEventArgs & p_args)
			*		void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtMotion(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args)
			*		void cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg)
			*		void cb_evtWindowMove(eve::evt::ResizeEventArgs & p_arg)
			*		void cb_evtWindowFocusGot(eve::evt::EventArgs & p_arg)
			*		void cb_evtWindowFocusLost(eve::evt::EventArgs & p_arg)
			*		void cb_evtWindowClose(eve::evt::EventArgs & p_arg)
			*/
			template<class ListenerClass>
			void unregisterEvents(ListenerClass * p_pListener, int32_t p_prio = eve::evt::orderApp);

		}; // class Event 

	} // namespace evt

} // namespace eve


////////////////////////////////////////////////////////////////////////////////////////////////////
//		FILE EVENTS
////////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::registerEventsFile(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(m_fileDropped, p_pListener, &ListenerClass::cb_evtFileDrop, p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::unregisterEventsFile(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(m_fileDropped, p_pListener, &ListenerClass::cb_evtFileDrop, p_prio);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		KEY EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::registerEventsKey(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(m_keyPressed,	p_pListener, &ListenerClass::cb_evtKeyDown,		p_prio);
	eve::evt::add_listener(m_keyReleased,	p_pListener, &ListenerClass::cb_evtKeyUp,		p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::unregisterEventsKey(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(m_keyPressed,		p_pListener, &ListenerClass::cb_evtKeyDown,		p_prio);
	eve::evt::remove_listener(m_keyReleased,	p_pListener, &ListenerClass::cb_evtKeyUp,		p_prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		TEXT EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::registerEventsText(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(m_textInput, p_pListener, &ListenerClass::cb_evtTextInput, p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::unregisterEventsText(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(m_textInput, p_pListener, &ListenerClass::cb_evtTextInput, p_prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		MOUSE EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::registerEventsMouse(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(m_mouseDown,				p_pListener, &ListenerClass::cb_evtMouseDown,			p_prio);
	eve::evt::add_listener(m_mouseUp,				p_pListener, &ListenerClass::cb_evtMouseUp,				p_prio);
	eve::evt::add_listener(m_mouseDoubleClick,		p_pListener, &ListenerClass::cb_evtMouseDoubleClick,	p_prio);
	eve::evt::add_listener(m_mouseMotion,			p_pListener, &ListenerClass::cb_evtMotion,				p_prio);
	eve::evt::add_listener(m_mousePassiveMotion,	p_pListener, &ListenerClass::cb_evtPassiveMotion,		p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::unregisterEventsMouse(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(m_mouseDown,				p_pListener, &ListenerClass::cb_evtMouseDown,			p_prio);
	eve::evt::remove_listener(m_mouseUp,				p_pListener, &ListenerClass::cb_evtMouseUp,				p_prio);
	eve::evt::remove_listener(m_mouseDoubleClick,		p_pListener, &ListenerClass::cb_evtMouseDoubleClick,	p_prio);
	eve::evt::remove_listener(m_mouseMotion,			p_pListener, &ListenerClass::cb_evtMotion,				p_prio);
	eve::evt::remove_listener(m_mousePassiveMotion,		p_pListener, &ListenerClass::cb_evtPassiveMotion,		p_prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		WINDOW EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::registerEventsWindow(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(m_windowResized,		p_pListener, &ListenerClass::cb_evtWindowResize,		p_prio);
	eve::evt::add_listener(m_windowMoved,		p_pListener, &ListenerClass::cb_evtWindowMove,			p_prio);
	eve::evt::add_listener(m_windowFocusGot,	p_pListener, &ListenerClass::cb_evtWindowFocusGot,		p_prio);
	eve::evt::add_listener(m_windowFocusLost,	p_pListener, &ListenerClass::cb_evtWindowFocusLost,		p_prio);
	eve::evt::add_listener(m_windowClose,		p_pListener, &ListenerClass::cb_evtWindowClose,			p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::unregisterEventsWindow(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(m_windowResized,		p_pListener, &ListenerClass::cb_evtWindowResize,		p_prio);
	eve::evt::remove_listener(m_windowMoved,		p_pListener, &ListenerClass::cb_evtWindowMove,			p_prio);
	eve::evt::remove_listener(m_windowFocusGot,		p_pListener, &ListenerClass::cb_evtWindowFocusGot,		p_prio);
	eve::evt::remove_listener(m_windowFocusLost,	p_pListener, &ListenerClass::cb_evtWindowFocusLost,		p_prio);
	eve::evt::remove_listener(m_windowClose,		p_pListener, &ListenerClass::cb_evtWindowClose,			p_prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		ALL EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::registerEvents(ListenerClass * p_pListener, int32_t p_prio)
{
	this->registerEventsFile(p_pListener, p_prio);
	this->registerEventsKey(p_pListener, p_prio);
	this->registerEventsText(p_pListener, p_prio);
	this->registerEventsMouse(p_pListener, p_prio);
	this->registerEventsWindow(p_pListener, p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::sys::Event::unregisterEvents(ListenerClass * p_pListener, int32_t p_prio)
{
	this->unregisterEventsFile(p_pListener, p_prio);
	this->unregisterEventsKey(p_pListener, p_prio);
	this->unregisterEventsText(p_pListener, p_prio);
	this->unregisterEventsMouse(p_pListener, p_prio);
	this->unregisterEventsWindow(p_pListener, p_prio);
}

#endif // __EVE_EVT_EVENT_H__

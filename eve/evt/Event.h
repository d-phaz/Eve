
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
#ifndef __EVE_EVT_EVENT_H__ 
#define __EVE_EVT_EVENT_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_EVT_TEVENT_H__
#include "eve/evt/TEvent.h"
#endif

#ifndef __EVE_EVT_SERVER_H__
#include "eve/evt/Server.h"
#endif


namespace eve
{
	namespace evt
	{
		/************************************************************************/
		/*		                                                                */
		/* NOTE:                                                                */
		/*	Events managed here are global events.								*/
		/*	These events should only be used in single window application(s).   */
		/*		                                                                */
		/*		                                                                */
		/************************************************************************/



		/** 
		* \class eve::evt::Args
		* \brief Empty base event argument(s) class.
		*/
		class Args
		{};



		///////////////////////////////////////////////////////////////////////////////////////////
		//		KEY EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::KeyEventArgs
		* \brief key and text input event arguments.
		* \note extends eve::evt::Args
		*/
		class KeyEventArgs
			: public eve::evt::Args
		{
		public:
			uint8_t		key;
		};

		/** \brief Key event type definition. */
		typedef eve::evt::TEvent<eve::evt::KeyEventArgs> KeyEvent;
		
		/** 
		* \class eve::evt::EvtKey
		* \brief Stock global static key events.
		*/
		class EvtKey
		{
		public:
			static KeyEvent 		keyPressed;				//!< Key pressed event.
			static KeyEvent 		keyReleased;			//!< Key released event.
			static KeyEvent 		keyInput;				//!< Text input event.
		};

		/** \! Enable key events dispatch. */
		void enable_events_key(void);
		/** \! Disable key events dispatch. */
		void disable_events_key(void);

		/** \brief Notify key pressed event to all listeners. */
		void notify_key_pressed(uint8_t p_key);
		/** \brief Notify key released event to all listeners. */
		void notify_key_released(uint8_t p_key);
		/** \brief Notify text input event to all listeners. */
		void notify_key_input(uint8_t p_key);

		/**
		* \brief Register listener class to key events.
		* Listener class must provide key event handler methods using the following signatures:
		*		void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
		*		void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args)
		*		void cb_evtKeyInput(eve::evt::KeyEventArgs & p_args)
		*/
		template<class ListenerClass>
		void register_events_key(ListenerClass * listener, int32_t prio = orderAfterApp);
		/**
		* \brief Unregister listener class from key events.
		* Listener class must provide key event handler methods using the following signatures:
		*		void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
		*		void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args)
		*		void cb_evtKeyInput(eve::evt::KeyEventArgs & p_args)
		*/
		template<class ListenerClass>
		void unregister_events_key(ListenerClass * listener, int32_t prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		MOUSE EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::MouseEventArgs
		* \brief Mouse event arguments.
		* \note extends eve::evt::Args
		*/
		class MouseEventArgs
			: public eve::evt::Args
		{
		public:
			int32_t		button;
			int32_t		x;
			int32_t		y;
		};

		/** \brief Mouse event type definition. */
		typedef eve::evt::TEvent<eve::evt::MouseEventArgs> MouseEvent;

		/**
		* \class eve::evt::EvtMouse
		* \brief Stock global static mouse events.
		*/
		class EvtMouse
		{
		public:
			static MouseEvent 		mousePassiveMotion;		//!< Mouse passive motion (no mouse button pressed) event.
			static MouseEvent 		mouseMotion;			//!< Mouse motion (mouse button pressed) event.
			static MouseEvent 		mouseDown;				//!< Mouse button pressed event.
			static MouseEvent		mouseDoubleClick;		//!< Mouse double click event.
			static MouseEvent 		mouseUp;				//!< Mouse button released event.
		};

		/** \! Enable mouse events dispatch. */
		void enable_events_mouse(void);
		/** \! Disable mouse events dispatch. */
		void disable_events_mouse(void);

		/** \brief Notify mouse down event to all listeners. */
		void notify_mouse_down(int32_t p_button, int32_t x, int32_t y);
		/** \brief Notify mouse up event to all listeners. */
		void notify_mouse_up(int32_t p_button, int32_t x, int32_t y);
		/** \brief Notify mouse double click event to all listeners. */
		void notify_mouse_double_click(int32_t p_button, int32_t x, int32_t y);
		/** \brief Notify mouse motion (mouse button pressed) event to all listeners. */
		void notify_mouse_motion(int32_t x, int32_t y);
		/** \brief Notify mouse passive motion (no mouse button pressed) event to all listeners. */
		void notify_mouse_passive_motion(int32_t x, int32_t y);

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
		void register_events_mouse(ListenerClass * listener, int32_t prio = orderAfterApp);
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
		void unregister_events_mouse(ListenerClass * listener, int32_t prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		TOUCH EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::TouchEventArgs
		* \brief Touch event arguments.
		* \note extends eve::evt::Args
		*/
		class TouchEventArgs
			: public eve::evt::Args
		{
		public:
			enum Type
			{
				down,
				up,
				move,
				doubleTap,
				cancel
			}			type;

			int32_t		id;
			int32_t		time;
			int32_t		numTouches;
			float		width;
			float		height;
			float		angle;
			float		minoraxis;
			float		majoraxis;
			float		pressure;
			float		xspeed;
			float		yspeed;
			float		xaccel;
			float		yaccel;
		}; 

		/** \brief Touch event type definition. */
		typedef eve::evt::TEvent<eve::evt::TouchEventArgs> TouchEvent;
		
		/**
		* \class eve::evt::EvtTouch
		* \brief Stock global static touch events.
		*/
		class EvtTouch
		{
		public:
			static TouchEvent		touchDown;				//!< Touch down event.
			static TouchEvent		touchUp;				//!< Touch up event.
			static TouchEvent		touchDoubleTap;			//!< Touch double tap event.
			static TouchEvent		touchMoved;				//!< Touch move event.
			static TouchEvent		touchCanceled;			//!< Touch canceled event.
		};
		
		/** \! Enable touch events dispatch. */
		void enable_events_touch(void);
		/** \! Disable touch events dispatch. */
		void disable_events_touch(void);

		/**
		* \brief Register listener class to touch events.
		* Listener class must provide touch event handler methods using the following signatures:
		*		void cb_evtTouchDown(eve::evt::TouchEventArgs & p_args)
		*		void cb_evtTouchUp(eve::evt::TouchEventArgs & p_args)
		*		void cb_evtTouchDoubleTap(eve::evt::TouchEventArgs & p_args)
		*		void cb_evtTouchMoved(eve::evt::TouchEventArgs & p_args)
		*/
		template<class ListenerClass>
		void register_events_touch(ListenerClass * listener, int32_t prio = orderAfterApp);
		/**
		* \brief Unregister listener class to touch events.
		* Listener class must provide touch event handler methods using the following signatures:
		*		void cb_evtTouchDown(eve::evt::TouchEventArgs & p_args)
		*		void cb_evtTouchUp(eve::evt::TouchEventArgs & p_args)
		*		void cb_evtTouchDoubleTap(eve::evt::TouchEventArgs & p_args)
		*		void cb_evtTouchMoved(eve::evt::TouchEventArgs & p_args)
		*		void cb_evtTouchCanceled(eve::evt::TouchEventArgs & p_args)
		*/
		template<class ListenerClass>
		void unregister_events_touch(ListenerClass * listener, int32_t prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		WINDOW EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::ResizeEventArgs
		* \brief Window resize event arguments.
		* \note extends eve::evt::Args
		*/
		class ResizeEventArgs
			: public eve::evt::Args
		{
		public:
			int32_t width;
			int32_t height;
		};

		/**
		* \class eve::evt::EvtWindow
		* \brief Stock global static window events.
		*/
		class EvtWindow
		{
		public:
			static eve::evt::TEvent<eve::evt::ResizeEventArgs> 		windowResized;			//!< Window resized event.
			static eve::evt::TEvent<void>							windowFocusGot;			//!< Window gain focus event.
			static eve::evt::TEvent<void>							windowFocusLost;		//!< Window lost focus event.
			static eve::evt::TEvent<void>							windowClose;			//!< Window closed event.
		};

		/** \! Enable window events dispatch. */
		void enable_events_window(void);
		/** \! Disable window events dispatch. */
		void disable_events_window(void);

		/** \brief Notify window resize event to all listeners.*/
		void notify_window_resize(uint32_t p_width, uint32_t p_height);
		/** \brief Notify window gain focus event to all listeners.*/
		void notify_window_focus_got(void);
		/** \brief Notify window lost focus event to all listeners.*/
		void notify_window_focus_lost(void);
		/** \brief Notify window close event to all listeners.*/
		void notify_window_close(void);

		/**
		* \brief Register listener class to window events.
		* Listener class must provide window event handler methods using the following signatures:
		*		void cb_evtWindowReshape(eve::evt::ResizeEventArgs & p_arg)
		*		void cb_evtWindowFocusGot(void)
		*		void cb_evtWindowFocusLost(void)
		*		void cb_evtWindowClose(void)
		*/
		template<class ListenerClass>
		void register_events_window(ListenerClass * listener, int32_t prio = orderAfterApp);
		/**
		* \brief Unregister listener class to window events.
		* Listener class must provide window event handler methods using the following signatures:
		*		void cb_evtWindowReshape(eve::evt::ResizeEventArgs & p_arg)
		*		void cb_evtWindowFocusGot(void)
		*		void cb_evtWindowFocusLost(void)
		*		void cb_evtWindowClose(void)
		*/
		template<class ListenerClass>
		void unregister_events_window(ListenerClass * listener, int32_t prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		APPLICATION EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		* \class eve::evt::EvtApp
		* \brief Stock global static application events.
		*/
		class EvtApp
		{
		public:
			static eve::evt::TEvent<void>							appExit;				//!< Application exit event.
		};

		/** \! Enable application events dispatch. */
		void enable_events_application(void);
		/** \! Disable application events dispatch. */
		void disable_events_application(void);

		/** \brief Notify application exit event to all listeners.*/
		void notify_application_exit(void);

		/**
		* \brief Register listener class to application events.
		* Listener class must provide application event handler methods using the following signatures:
		*		void cb_evtApplicationExit(void)
		*/
		template<class ListenerClass>
		void register_events_application(ListenerClass * listener, int32_t prio = orderAfterApp);
		/**
		* \brief Unregister listener class to application events.
		* Listener class must provide application event handler methods using the following signatures:
		*		void cb_evtApplicationExit(void)
		*/
		template<class ListenerClass>
		void unregister_events_application(ListenerClass * listener, int32_t prio = orderAfterApp);

	} // namespace evt

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		KEY EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_key(ListenerClass * listener, int32_t prio)
{
	eve::evt::add_listener(eve::evt::EvtKey::keyPressed,	listener, &ListenerClass::cb_evtKeyDown,	prio);
	eve::evt::add_listener(eve::evt::EvtKey::keyReleased,	listener, &ListenerClass::cb_evtKeyUp,		prio);
	eve::evt::add_listener(eve::evt::EvtKey::keyInput,		listener, &ListenerClass::cb_evtKeyInput,	prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_key(ListenerClass * listener, int32_t prio)
{
	eve::evt::remove_listener(eve::evt::EvtKey::keyPressed,		listener, &ListenerClass::cb_evtKeyDown,	prio);
	eve::evt::remove_listener(eve::evt::EvtKey::keyReleased,	listener, &ListenerClass::cb_evtKeyUp,		prio);
	eve::evt::remove_listener(eve::evt::EvtKey::keyInput,		listener, &ListenerClass::cb_evtKeyInput,	prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		MOUSE EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_mouse(ListenerClass * listener, int32_t prio)
{
	eve::evt::add_listener(eve::evt::EvtMouse::mouseDown,			listener, &ListenerClass::cb_evtMouseDown,			prio);
	eve::evt::add_listener(eve::evt::EvtMouse::mouseUp,				listener, &ListenerClass::cb_evtMouseUp,			prio);
	eve::evt::add_listener(eve::evt::EvtMouse::mouseDoubleClick,	listener, &ListenerClass::cb_evtMouseDoubleClick,	prio);
	eve::evt::add_listener(eve::evt::EvtMouse::mouseMotion,			listener, &ListenerClass::cb_evtMotion,				prio);
	eve::evt::add_listener(eve::evt::EvtMouse::mousePassiveMotion,	listener, &ListenerClass::cb_evtPassiveMotion,		prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_mouse(ListenerClass * listener, int32_t prio)
{
	eve::evt::remove_listener(eve::evt::EvtMouse::mouseDown,			listener, &ListenerClass::cb_evtMouseDown,			prio);
	eve::evt::remove_listener(eve::evt::EvtMouse::mouseUp,				listener, &ListenerClass::cb_evtMouseUp,			prio);
	eve::evt::remove_listener(eve::evt::EvtMouse::mouseDoubleClick,		listener, &ListenerClass::cb_evtMouseDoubleClick,	prio);
	eve::evt::remove_listener(eve::evt::EvtMouse::mouseMotion,			listener, &ListenerClass::cb_evtMotion,				prio);
	eve::evt::remove_listener(eve::evt::EvtMouse::mousePassiveMotion,	listener, &ListenerClass::cb_evtPassiveMotion,		prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		TOUCH EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_touch(ListenerClass * listener, int32_t prio)
{
	eve::evt::add_listener(eve::evt::EvtTouch::touchDown,		listener, &ListenerClass::cb_evtTouchDown,		prio);
	eve::evt::add_listener(eve::evt::EvtTouch::touchUp,			listener, &ListenerClass::cb_evtTouchUp,		prio);
	eve::evt::add_listener(eve::evt::EvtTouch::touchDoubleTap,	listener, &ListenerClass::cb_evtTouchDoubleTap, prio);
	eve::evt::add_listener(eve::evt::EvtTouch::touchMoved,		listener, &ListenerClass::cb_evtTouchMoved,		prio);
	eve::evt::add_listener(eve::evt::EvtTouch::touchCanceled,	listener, &ListenerClass::cb_evtTouchCanceled,	prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_touch(ListenerClass * listener, int32_t prio)
{
	eve::evt::remove_listener(eve::evt::EvtTouch::touchDown,		listener, &ListenerClass::cb_evtTouchDown,		prio);
	eve::evt::remove_listener(eve::evt::EvtTouch::touchUp,			listener, &ListenerClass::cb_evtTouchUp,		prio);
	eve::evt::remove_listener(eve::evt::EvtTouch::touchDoubleTap,	listener, &ListenerClass::cb_evtTouchDoubleTap, prio);
	eve::evt::remove_listener(eve::evt::EvtTouch::touchMoved,		listener, &ListenerClass::cb_evtTouchMoved,		prio);
	eve::evt::remove_listener(eve::evt::EvtTouch::touchCanceled,	listener, &ListenerClass::cb_evtTouchCanceled,	prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		WINDOW EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_window(ListenerClass * listener, int32_t prio)
{
	eve::evt::add_listener(eve::evt::EvtWindow::windowResized,		listener, &ListenerClass::cb_evtWindowReshape,		prio);
	eve::evt::add_listener(eve::evt::EvtWindow::windowFocusGot,		listener, &ListenerClass::cb_evtWindowFocusGot,		prio);
	eve::evt::add_listener(eve::evt::EvtWindow::windowFocusLost,	listener, &ListenerClass::cb_evtWindowFocusLost,	prio);
	eve::evt::add_listener(eve::evt::EvtWindow::windowClose,		listener, &ListenerClass::cb_evtWindowClose,		prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_window(ListenerClass * listener, int32_t prio)
{
	eve::evt::remove_listener(eve::evt::EvtWindow::windowResized,		listener, &ListenerClass::cb_evtWindowReshape,		prio);
	eve::evt::remove_listener(eve::evt::EvtWindow::windowFocusGot,		listener, &ListenerClass::cb_evtWindowFocusGot,		prio);
	eve::evt::remove_listener(eve::evt::EvtWindow::windowFocusLost,		listener, &ListenerClass::cb_evtWindowFocusLost,	prio);
	eve::evt::remove_listener(eve::evt::EvtWindow::windowClose,			listener, &ListenerClass::cb_evtWindowClose,		prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		APPLICATION EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void register_events_application(ListenerClass * listener, int32_t prio)
{
	eve::evt::add_listener(eve::evt::EvtApp::appExit, listener, &ListenerClass::cb_evtApplicationExit, prio);
}

//=================================================================================================
template<class ListenerClass>
void unregister_events_application(ListenerClass * listener, int32_t prio)
{
	eve::evt::remove_listener(eve::evt::EvtApp::appExit, listener, &ListenerClass::cb_evtApplicationExit, prio);
}

#endif // __EVE_EVT_EVENT_H__

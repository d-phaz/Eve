
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

#ifndef __EVE_SYSTEM_KEYBOARD_H__
#include "eve/sys/win32/Keyboard.h"
#endif


namespace eve
{
	namespace evt
	{
		/************************************************************************************************/
		/*																								*/
		/* NOTE:																						*/
		/*	Events managed here are global events.														*/
		/*	User interaction events listed here should only be used in single window application(s).	*/
		/*																								*/
		/*																								*/
		/************************************************************************************************/


		/**
		* \class eve::evt::EventArgs
		* \brief Base event arguments class.
		*/
		class EventArgs
		{
		public:
			int64_t		time;

			/** \brief Default constructor. */
			EventArgs(void);
			/** \brief Copy constructor. */
			EventArgs(const EventArgs & p_other);
			/** \brief Assignment operator. */
			EventArgs & operator = (const EventArgs & p_other);
		};


		///////////////////////////////////////////////////////////////////////////////////////////
		//		FILE EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::FileEventArgs
		* \brief File drop event arguments.
		* \note extends eve::evt::EventArgs.
		*/
		class FileEventArgs
			: public EventArgs
		{
		public:
			int32_t						x;
			int32_t						y;
			uint32_t					count;
			std::vector<std::wstring>	files;

			/** \brief Default constructor. */
			FileEventArgs(void);
			/** \brief Copy constructor. */
			FileEventArgs(const FileEventArgs & p_other);
			/** \brief Assignment operator. */
			FileEventArgs & operator = (const FileEventArgs & p_other);
		};

		/** \brief File event type definition. */
		typedef eve::evt::TEvent<eve::evt::FileEventArgs> FileEvent;

		/**
		* \class eve::evt::EvtFile
		* \brief Stock global static file events.
		*/
		class EvtFile
		{
		public:
			static FileEvent 		fileDropped;			//!< File dropped event.
		};

		/** \brief Enable file events dispatch. */
		void enable_events_file(void);
		/** \brief Disable file events dispatch. */
		void disable_events_file(void);

		/** \brief Notify file dropped event to all listeners. */
		void notify_file_dropped(int32_t p_x, int32_t p_y, uint32_t p_count, std::vector<std::wstring> & p_files);

		/**
		* \brief Register listener class to file events.
		* Listener class must provide file event handler methods using the following signatures:
		*		void cb_evtFileDrop(eve::evt::FileEventArgs & p_args)
		*/
		template<class ListenerClass>
		void register_events_file(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);
		/**
		* \brief Unregister listener class from file events.
		* Listener class must provide file event handler methods using the following signatures:
		*		void cb_evtFileDrop(eve::evt::FileEventArgs & p_args)
		*/
		template<class ListenerClass>
		void unregister_events_file(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		KEY EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::KeyEventArgs
		* \brief key event arguments.
		* \note extends eve::evt::EventArgs.
		*/
		class KeyEventArgs
			: public EventArgs
		{
		public:
			eve::sys::Key			key;
			eve::sys::KeyModifier	modifier;
			bool					repeat;

			/** \brief Default constructor. */
			KeyEventArgs(void);
			/** \brief Copy constructor. */
			KeyEventArgs(const KeyEventArgs & p_other);
			/** \brief Assignment operator. */
			KeyEventArgs & operator = (const KeyEventArgs & p_other);
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
		};

		/** \brief Enable key events dispatch. */
		void enable_events_key(void);
		/** \brief Disable key events dispatch. */
		void disable_events_key(void);

		/** \brief Notify key pressed event to all listeners. */
		void notify_key_pressed(eve::sys::Key p_key, eve::sys::KeyModifier p_modifier, bool p_bRepeat);
		/** \brief Notify key released event to all listeners. */
		void notify_key_released(eve::sys::Key p_key, eve::sys::KeyModifier p_modifier);

		/**
		* \brief Register listener class to key events.
		* Listener class must provide key event handler methods using the following signatures:
		*		void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
		*		void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args)
		*/
		template<class ListenerClass>
		void register_events_key(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);
		/**
		* \brief Unregister listener class from key events.
		* Listener class must provide key event handler methods using the following signatures:
		*		void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
		*		void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args)
		*/
		template<class ListenerClass>
		void unregister_events_key(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		TEXT EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::TextEventArgs
		* \brief Text input event arguments.
		* \note extends eve::evt::EventArgs.
		*/
		class TextEventArgs
			: public EventArgs
		{
		public:
			wchar_t					text;
			eve::sys::KeyModifier	modifier;
			bool					repeat;

			/** \brief Default constructor. */
			TextEventArgs(void);
			/** \brief Copy constructor. */
			TextEventArgs(const TextEventArgs & p_other);
			/** \brief Assignment operator. */
			TextEventArgs & operator = (const TextEventArgs & p_other);
		};

		/** \brief Text event type definition. */
		typedef eve::evt::TEvent<eve::evt::TextEventArgs> TextEvent;

		/**
		* \class eve::evt::EvtText
		* \brief Stock global static text events.
		*/
		class EvtText
		{
		public:
			static TextEvent 		textInput;				//!< Text input event.
		};

		/** \brief Enable text events dispatch. */
		void enable_events_text(void);
		/** \brief Disable text events dispatch. */
		void disable_events_text(void);

		/** \brief Notify text input event to all listeners. */
		void notify_text_input(wchar_t p_text, eve::sys::KeyModifier p_modifier, bool p_bRepeat);

		/**
		* \brief Register listener class to text events.
		* Listener class must provide text event handler methods using the following signatures:
		*		void cb_evtTextInput(eve::evt::TextEventArgs & p_args)
		*/
		template<class ListenerClass>
		void register_events_text(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);
		/**
		* \brief Unregister listener class from text events.
		* Listener class must provide text event handler methods using the following signatures:
		*		void cb_evtTextInput(eve::evt::TextEventArgs & p_args)
		*/
		template<class ListenerClass>
		void unregister_events_text(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		MOUSE EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::MouseEventArgs
		* \brief Mouse event arguments.
		* \note extends eve::evt::EventArgs.
		*/
		class MouseEventArgs
			: public EventArgs
		{
		public:
			int32_t		button;
			int32_t		x;
			int32_t		y;

			/** \brief Default constructor. */
			MouseEventArgs(void);
			/** \brief Copy constructor. */
			MouseEventArgs(const MouseEventArgs & p_other);
			/** \brief Assignment operator. */
			MouseEventArgs & operator = (const MouseEventArgs & p_other);
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
			static MouseEvent 		mouseWheel;				//!< Mouse wheel event.
			static MouseEvent		mouseDoubleClick;		//!< Mouse double click event.
			static MouseEvent 		mouseUp;				//!< Mouse button released event.
		};

		/** \brief Enable mouse events dispatch. */
		void enable_events_mouse(void);
		/** \brief Disable mouse events dispatch. */
		void disable_events_mouse(void);

		/** \brief Notify mouse down event to all listeners. */
		void notify_mouse_down(int32_t p_button, int32_t x, int32_t y);
		/** \brief Notify mouse wheel event to all listeners. */
		void notify_mouse_wheel(int32_t p_button, int32_t x, int32_t y);
		/** \brief Notify mouse up event to all listeners. */
		void notify_mouse_up(int32_t p_button, int32_t x, int32_t y);
		/** \brief Notify mouse double click event to all listeners. */
		void notify_mouse_double_click(int32_t p_button, int32_t x, int32_t y);
		/** \brief Notify mouse motion (mouse button pressed) event to all listeners. */
		void notify_mouse_motion(int32_t p_button, int32_t x, int32_t y);
		/** \brief Notify mouse passive motion (no mouse button pressed) event to all listeners. */
		void notify_mouse_passive_motion(int32_t x, int32_t y);

		/**
		* \brief Register listener class to mouse events.
		* Listener class must provide mouse event handler methods using the following signatures:
		*		void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
		*		void cb_evtMouseWheel(eve::evt::MouseEventArgs & p_args)
		*		void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args)
		*		void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args)
		*		void cb_evtMotion(eve::evt::MouseEventArgs & p_args)
		*		void cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args)
		*/
		template<class ListenerClass>
		void register_events_mouse(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);
		/**
		* \brief Unregister listener class from mouse events.
		* Listener class must provide mouse event handler methods using the following signatures:
		*		void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
		*		void cb_evtMouseWheel(eve::evt::MouseEventArgs & p_args)
		*		void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args)
		*		void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args)
		*		void cb_evtMotion(eve::evt::MouseEventArgs & p_args)
		*		void cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args)
		*/
		template<class ListenerClass>
		void unregister_events_mouse(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		TOUCH EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::TouchEventArgs
		* \brief Touch event arguments.
		* \note extends eve::evt::EventArgs.
		*/
		class TouchEventArgs
			: public EventArgs
		{
		public:
			enum Type
			{
				unknown,
				down,
				up,
				move,
				doubleTap,
				cancel
			}			type;

			int32_t		id;
			int32_t		duration;
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

			/** \brief Default constructor. */
			TouchEventArgs(void);
			/** \brief Copy constructor. */
			TouchEventArgs(const TouchEventArgs & p_other);
			/** \brief Assignment operator. */
			TouchEventArgs & operator = (const TouchEventArgs & p_other);
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
		
		/** \brief Enable touch events dispatch. */
		void enable_events_touch(void);
		/** \brief Disable touch events dispatch. */
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
		void register_events_touch(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);
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
		void unregister_events_touch(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		WINDOW EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::ResizeEventArgs
		* \brief Window resize event arguments.
		* \note extends eve::evt::EventArgs.
		*/
		class ResizeEventArgs
			: public EventArgs
		{
		public:
			int32_t width;
			int32_t height;

			/** \brief Default constructor. */
			ResizeEventArgs(void);
			/** \brief Copy constructor. */
			ResizeEventArgs(const ResizeEventArgs & p_other);
			/** \brief Assignment operator. */
			ResizeEventArgs & operator = (const ResizeEventArgs & p_other);
		};

		/**
		* \class eve::evt::MoveEventArgs
		* \brief Window move event arguments.
		* \note extends eve::evt::EventArgs.
		*/
		class MoveEventArgs
			: public EventArgs
		{
		public:
			int32_t x;
			int32_t y;

			/** \brief Default constructor. */
			MoveEventArgs(void);
			/** \brief Copy constructor. */
			MoveEventArgs(const MoveEventArgs & p_other);
			/** \brief Assignment operator. */
			MoveEventArgs & operator = (const MoveEventArgs & p_other);
		};

		/**
		* \class eve::evt::EvtWindow
		* \brief Stock global static window events.
		*/
		class EvtWindow
		{
		public:
			static eve::evt::TEvent<eve::evt::ResizeEventArgs> 		windowResized;			//!< Window resized event.
			static eve::evt::TEvent<eve::evt::MoveEventArgs> 		windowMoved;			//!< Window moved event.
			static eve::evt::TEvent<eve::evt::EventArgs>			windowFocusGot;			//!< Window gain focus event.
			static eve::evt::TEvent<eve::evt::EventArgs>			windowFocusLost;		//!< Window lost focus event.
			static eve::evt::TEvent<eve::evt::EventArgs>			windowClose;			//!< Window closed event.
		};

		/** \brief Enable window events dispatch. */
		void enable_events_window(void);
		/** \brief Disable window events dispatch. */
		void disable_events_window(void);

		/** \brief Notify window resize event to all listeners.*/
		void notify_window_resize(int32_t p_width, int32_t p_height);
		/** \brief Notify window move event to all listeners.*/
		void notify_window_move(int32_t p_x, int32_t p_y);
		/** \brief Notify window gain focus event to all listeners.*/
		void notify_window_focus_got(void);
		/** \brief Notify window lost focus event to all listeners.*/
		void notify_window_focus_lost(void);
		/** \brief Notify window close event to all listeners.*/
		void notify_window_close(void);

		/**
		* \brief Register listener class to window events.
		* Listener class must provide window event handler methods using the following signatures:
		*		void cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg)
		*		void cb_evtWindowMove(eve::evt::MoveEventArgs & p_arg)
		*		void cb_evtWindowFocusGot(eve::evt::EventArgs & p_arg)
		*		void cb_evtWindowFocusLost(eve::evt::EventArgs & p_arg)
		*		void cb_evtWindowClose(eve::evt::EventArgs & p_arg)
		*/
		template<class ListenerClass>
		void register_events_window(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);
		/**
		* \brief Unregister listener class to window events.
		* Listener class must provide window event handler methods using the following signatures:
		*		void cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg)
		*		void cb_evtWindowMove(eve::evt::MoveEventArgs & p_arg)
		*		void cb_evtWindowFocusGot(eve::evt::EventArgs & p_arg)
		*		void cb_evtWindowFocusLost(eve::evt::EventArgs & p_arg)
		*		void cb_evtWindowClose(eve::evt::EventArgs & p_arg)
		*/
		template<class ListenerClass>
		void unregister_events_window(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		TIME EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::EvtTime
		* \brief Stock global static time events.
		* \note extends eve::evt::EventArgs.
		*/
		class EvtTime
		{
		public:
			static eve::evt::TEvent<EventArgs>						newTime;			//!< New time event.
		};

		/** \brief Enable time events dispatch. */
		void enable_events_time(void);
		/** \brief Disable time events dispatch. */
		void disable_events_time(void);

		/** \brief Notify time event to all listeners.*/
		void notify_time(int64_t p_time);

		/**
		* \brief Register listener class to time events.
		* Listener class must provide time event handler methods using the following signatures:
		*		void cb_evtTime(eve::evt:TimeEventArgs & p_arg)
		*/
		template<class ListenerClass>
		void register_events_time(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);
		/**
		* \brief Unregister listener class to time events.
		* Listener class must provide time event handler methods using the following signatures:
		*		void cb_evtTime(eve::evt:TimeEventArgs & p_arg)
		*/
		template<class ListenerClass>
		void unregister_events_time(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		FRAME EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \class eve::evt::FrameEventArgs
		* \brief New frame event arguments.
		* \note extends eve::evt::EventArgs.
		*/
		class FrameEventArgs
			: public EventArgs
		{
		public:
			int64_t frame;

			/** \brief Default constructor. */
			FrameEventArgs(void);
			/** \brief Copy constructor. */
			FrameEventArgs(const FrameEventArgs & p_other);
			/** \brief Assignment operator. */
			FrameEventArgs & operator = (const FrameEventArgs & p_other);
		};

		/**
		* \class eve::evt::EvtFrame
		* \brief Stock global static frame events.
		*/
		class EvtFrame
		{
		public:
			static eve::evt::TEvent<FrameEventArgs>					newFrame;			//!< New frame event.
		};

		/** \brief Enable frame events dispatch. */
		void enable_events_frame(void);
		/** \brief Disable frame events dispatch. */
		void disable_events_frame(void);

		/** \brief Notify frame event to all listeners.*/
		void notify_frame(int64_t p_frame);

		/**
		* \brief Register listener class to frame events.
		* Listener class must provide frame event handler methods using the following signatures:
		*		void cb_evtFrame(eve::evt:FrameEventArgs & p_arg)
		*/
		template<class ListenerClass>
		void register_events_frame(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);
		/**
		* \brief Unregister listener class to frame events.
		* Listener class must provide frame event handler methods using the following signatures:
		*		void cb_evtFrame(eve::evt:FrameEventArgs & p_arg)
		*/
		template<class ListenerClass>
		void unregister_events_frame(ListenerClass * p_pListener, int32_t p_prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		APPLICATION EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////
		
		/**
		* \class eve::evt::EvtApp
		* \brief Stock global static application events.
		*/
		class EvtApp
			: public EventArgs
		{
		public:
			static eve::evt::TEvent<EventArgs>						appExit;				//!< Application exit event.
			static eve::evt::TEvent<EventArgs>						appTerminate;			//!< Application terminate event.
		};

		/** \brief Enable application events dispatch. */
		void enable_events_application(void);
		/** \brief Disable application events dispatch. */
		void disable_events_application(void);

		/** \brief Notify application exit event to all listeners.*/
		void notify_application_exit(void);
		/** \brief Notify application terminate event to all listeners.*/
		void notify_application_terminate(void);

		/**
		* \brief Register listener class to application events.
		* Listener class must provide application event handler methods using the following signatures:
		*		void cb_evtApplicationExit(eve::evt::EventArgs & p_arg)
		*		void cb_evtApplicationTerminate(eve::evt::EventArgs & p_arg)
		*/
		template<class ListenerClass>
		void register_events_application(ListenerClass * p_pListener, int32_t p_prio = orderApp);
		/**
		* \brief Unregister listener class to application events.
		* Listener class must provide application event handler methods using the following signatures:
		*		void cb_evtApplicationExit(eve::evt::EventArgs & p_arg)
		*		void cb_evtApplicationTerminate(eve::evt::EventArgs & p_arg)
		*/
		template<class ListenerClass>
		void unregister_events_application(ListenerClass * p_pListener, int32_t p_prio = orderApp);

	} // namespace evt

} // namespace eve


////////////////////////////////////////////////////////////////////////////////////////////////////
//		FILE EVENTS
////////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_file(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(eve::evt::EvtFile::fileDropped, p_pListener, &ListenerClass::cb_evtFileDrop, p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_file(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(eve::evt::EvtFile::fileDropped, p_pListener, &ListenerClass::cb_evtFileDrop, p_prio);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		KEY EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_key(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(eve::evt::EvtKey::keyPressed,	p_pListener, &ListenerClass::cb_evtKeyDown,		p_prio);
	eve::evt::add_listener(eve::evt::EvtKey::keyReleased,	p_pListener, &ListenerClass::cb_evtKeyUp,		p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_key(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(eve::evt::EvtKey::keyPressed,		p_pListener, &ListenerClass::cb_evtKeyDown,		p_prio);
	eve::evt::remove_listener(eve::evt::EvtKey::keyReleased,	p_pListener, &ListenerClass::cb_evtKeyUp,		p_prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		TEXT EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_text(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(eve::evt::EvtText::textInput, p_pListener, &ListenerClass::cb_evtTextInput, p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_text(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(eve::evt::EvtText::textInput, p_pListener, &ListenerClass::cb_evtTextInput, p_prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		MOUSE EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_mouse(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(eve::evt::EvtMouse::mouseDown,			p_pListener, &ListenerClass::cb_evtMouseDown,			p_prio);
	eve::evt::add_listener(eve::evt::EvtMouse::mouseWheel,			p_pListener, &ListenerClass::cb_evtMouseWheel,			p_prio);
	eve::evt::add_listener(eve::evt::EvtMouse::mouseUp,				p_pListener, &ListenerClass::cb_evtMouseUp,				p_prio);
	eve::evt::add_listener(eve::evt::EvtMouse::mouseDoubleClick,	p_pListener, &ListenerClass::cb_evtMouseDoubleClick,	p_prio);
	eve::evt::add_listener(eve::evt::EvtMouse::mouseMotion,			p_pListener, &ListenerClass::cb_evtMotion,				p_prio);
	eve::evt::add_listener(eve::evt::EvtMouse::mousePassiveMotion,	p_pListener, &ListenerClass::cb_evtPassiveMotion,		p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_mouse(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(eve::evt::EvtMouse::mouseDown,			p_pListener, &ListenerClass::cb_evtMouseDown,			p_prio);
	eve::evt::remove_listener(eve::evt::EvtMouse::mouseWheel,			p_pListener, &ListenerClass::cb_evtMouseWheel,			p_prio);
	eve::evt::remove_listener(eve::evt::EvtMouse::mouseUp,				p_pListener, &ListenerClass::cb_evtMouseUp,				p_prio);
	eve::evt::remove_listener(eve::evt::EvtMouse::mouseDoubleClick,		p_pListener, &ListenerClass::cb_evtMouseDoubleClick,	p_prio);
	eve::evt::remove_listener(eve::evt::EvtMouse::mouseMotion,			p_pListener, &ListenerClass::cb_evtMotion,				p_prio);
	eve::evt::remove_listener(eve::evt::EvtMouse::mousePassiveMotion,	p_pListener, &ListenerClass::cb_evtPassiveMotion,		p_prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		TOUCH EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_touch(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(eve::evt::EvtTouch::touchDown,		p_pListener, &ListenerClass::cb_evtTouchDown,		p_prio);
	eve::evt::add_listener(eve::evt::EvtTouch::touchUp,			p_pListener, &ListenerClass::cb_evtTouchUp,			p_prio);
	eve::evt::add_listener(eve::evt::EvtTouch::touchDoubleTap,	p_pListener, &ListenerClass::cb_evtTouchDoubleTap,	p_prio);
	eve::evt::add_listener(eve::evt::EvtTouch::touchMoved,		p_pListener, &ListenerClass::cb_evtTouchMoved,		p_prio);
	eve::evt::add_listener(eve::evt::EvtTouch::touchCanceled,	p_pListener, &ListenerClass::cb_evtTouchCanceled,	p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_touch(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(eve::evt::EvtTouch::touchDown,		p_pListener, &ListenerClass::cb_evtTouchDown,		p_prio);
	eve::evt::remove_listener(eve::evt::EvtTouch::touchUp,			p_pListener, &ListenerClass::cb_evtTouchUp,			p_prio);
	eve::evt::remove_listener(eve::evt::EvtTouch::touchDoubleTap,	p_pListener, &ListenerClass::cb_evtTouchDoubleTap,	p_prio);
	eve::evt::remove_listener(eve::evt::EvtTouch::touchMoved,		p_pListener, &ListenerClass::cb_evtTouchMoved,		p_prio);
	eve::evt::remove_listener(eve::evt::EvtTouch::touchCanceled,	p_pListener, &ListenerClass::cb_evtTouchCanceled,	p_prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		WINDOW EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_window(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(eve::evt::EvtWindow::windowResized,		p_pListener, &ListenerClass::cb_evtWindowResize,		p_prio);
	eve::evt::add_listener(eve::evt::EvtWindow::windowMoved,		p_pListener, &ListenerClass::cb_evtWindowMove,			p_prio);
	eve::evt::add_listener(eve::evt::EvtWindow::windowFocusGot,		p_pListener, &ListenerClass::cb_evtWindowFocusGot,		p_prio);
	eve::evt::add_listener(eve::evt::EvtWindow::windowFocusLost,	p_pListener, &ListenerClass::cb_evtWindowFocusLost,		p_prio);
	eve::evt::add_listener(eve::evt::EvtWindow::windowClose,		p_pListener, &ListenerClass::cb_evtWindowClose,			p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_window(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(eve::evt::EvtWindow::windowResized,		p_pListener, &ListenerClass::cb_evtWindowResize,		p_prio);
	eve::evt::remove_listener(eve::evt::EvtWindow::windowMoved,			p_pListener, &ListenerClass::cb_evtWindowMove,			p_prio);
	eve::evt::remove_listener(eve::evt::EvtWindow::windowFocusGot,		p_pListener, &ListenerClass::cb_evtWindowFocusGot,		p_prio);
	eve::evt::remove_listener(eve::evt::EvtWindow::windowFocusLost,		p_pListener, &ListenerClass::cb_evtWindowFocusLost,		p_prio);
	eve::evt::remove_listener(eve::evt::EvtWindow::windowClose,			p_pListener, &ListenerClass::cb_evtWindowClose,			p_prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		TIME EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_time(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(eve::evt::EvtTime::newTime, p_pListener, &ListenerClass::cb_evtTime, p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_time(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(eve::evt::EvtTime::newTime, p_pListener, &ListenerClass::cb_evtTime, p_prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		TIME EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_frame(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(eve::evt::EvtFrame::newFrame, p_pListener, &ListenerClass::cb_evtFrame, p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_frame(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(eve::evt::EvtFrame::newFrame, p_pListener, &ListenerClass::cb_evtFrame, p_prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		APPLICATION EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_application(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::add_listener(eve::evt::EvtApp::appExit,		p_pListener, &ListenerClass::cb_evtApplicationExit, p_prio);
	eve::evt::add_listener(eve::evt::EvtApp::appTerminate,	p_pListener, &ListenerClass::cb_evtApplicationTerminate, p_prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_application(ListenerClass * p_pListener, int32_t p_prio)
{
	eve::evt::remove_listener(eve::evt::EvtApp::appExit,	  p_pListener, &ListenerClass::cb_evtApplicationExit, p_prio);
	eve::evt::remove_listener(eve::evt::EvtApp::appTerminate, p_pListener, &ListenerClass::cb_evtApplicationTerminate, p_prio);
}

#endif // __EVE_EVT_EVENT_H__

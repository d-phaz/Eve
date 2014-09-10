
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

		static eve::evt::TEvent<eve::evt::KeyEventArgs> 		keyPressed;				//!< Key pressed event.
		static eve::evt::TEvent<eve::evt::KeyEventArgs> 		keyReleased;			//!< Key released event.
		static eve::evt::TEvent<eve::evt::KeyEventArgs> 		keyInput;				//!< Text input event.

		/** \! Enable key events dispatch. */
		static void enable_events_key(void);
		/** \! Disable key events dispatch. */
		static void disable_events_key(void);

		/** \brief Notify key pressed event to all listeners. */
		static void notify_key_pressed(uint8_t p_key);
		/** \brief Notify key released event to all listeners. */
		static void notify_key_released(uint8_t p_key);
		/** \brief Notify text input event to all listeners. */
		static void notify_key_input(uint8_t p_key);

		/**
		* \brief Register listener class to key events.
		* Listener class must provide key event handler methods using the following signatures:
		*		void cb_evtKeyDown(void)
		*		void cb_evtKeyUp(void)
		*		void cb_evtKeyInput(void)
		*/
		template<class ListenerClass>
		void register_events_key(ListenerClass * listener, int32_t prio = orderAfterApp);
		/**
		* \brief Unregister listener class from key events.
		* Listener class must provide key event handler methods using the following signatures:
		*		void cb_evtKeyDown(void)
		*		void cb_evtKeyUp(void)
		*		void cb_evtKeyInput(void)
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

		static eve::evt::TEvent<eve::evt::MouseEventArgs> 		mousePassiveMotion;		//!< Mouse passive motion (no mouse button pressed) event.
		static eve::evt::TEvent<eve::evt::MouseEventArgs> 		mouseMotion;			//!< Mouse motion (mouse button pressed) event.
		static eve::evt::TEvent<eve::evt::MouseEventArgs> 		mouseDown;				//!< Mouse button pressed event.
		static eve::evt::TEvent<eve::evt::MouseEventArgs>		mouseDoubleClick;		//!< Mouse double click event.
		static eve::evt::TEvent<eve::evt::MouseEventArgs> 		mouseUp;				//!< Mouse button released event.

		/** \! Enable mouse events dispatch. */
		static void enable_events_mouse(void);
		/** \! Disable mouse events dispatch. */
		static void disable_events_mouse(void);

		/** \brief Notify mouse down event to all listeners. */
		static void notify_mouse_down(int32_t p_button, int32_t x, int32_t y);
		/** \brief Notify mouse up event to all listeners. */
		static void notify_mouse_up(int32_t p_button, int32_t x, int32_t y);
		/** \brief Notify mouse double click event to all listeners. */
		static void notify_mouse_double_click(int32_t p_button, int32_t x, int32_t y);
		/** \brief Notify mouse motion (mouse button pressed) event to all listeners. */
		static void notify_mouse_motion(int32_t x, int32_t y);
		/** \brief Notify mouse passive motion (no mouse button pressed) event to all listeners. */
		static void notify_mouse_passive_motion(int32_t x, int32_t y);

		/**
		* \brief Register listener class to mouse events.
		* Listener class must provide mouse event handler methods using the following signatures:
		*		void cb_evtMouseDown(void)
		*		void cb_evtMouseUp(void)
		*		void cb_evtMouseDoubleClick(void)
		*		void cb_evtMotion(void)
		*		void cb_evtPassiveMotion(void)
		*/
		template<class ListenerClass>
		void register_events_mouse(ListenerClass * listener, int32_t prio = orderAfterApp);
		/**
		* \brief Unregister listener class from mouse events.
		* Listener class must provide mouse event handler methods using the following signatures:
		*		void cb_evtMouseDown(void)
		*		void cb_evtMouseUp(void)
		*		void cb_evtMouseDoubleClick(void)
		*		void cb_evtMotion(void)
		*		void cb_evtPassiveMotion(void)
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

		static eve::evt::TEvent<eve::evt::TouchEventArgs>		touchDown;				//!< Touch down event.
		static eve::evt::TEvent<eve::evt::TouchEventArgs>		touchUp;				//!< Touch up event.
		static eve::evt::TEvent<eve::evt::TouchEventArgs>		touchDoubleTap;			//!< Touch double tap event.
		static eve::evt::TEvent<eve::evt::TouchEventArgs>		touchMoved;				//!< Touch move event.
		static eve::evt::TEvent<eve::evt::TouchEventArgs>		touchCanceled;			//!< Touch canceled event.

		/** \! Enable touch events dispatch. */
		static void enable_events_touch(void);
		/** \! Disable touch events dispatch. */
		static void disable_events_touch(void);

		/**
		* \brief Register listener class to touch events.
		* Listener class must provide touch event handler methods using the following signatures:
		*		void cb_evtTouchDown(void)
		*		void cb_evtTouchUp(void)
		*		void cb_evtTouchDoubleTap(void)
		*		void cb_evtTouchMoved(void)
		*/
		template<class ListenerClass>
		void register_events_touch(ListenerClass * listener, int32_t prio = orderAfterApp);
		/**
		* \brief Unregister listener class to touch events.
		* Listener class must provide touch event handler methods using the following signatures:
		*		void cb_evtTouchDown(void)
		*		void cb_evtTouchUp(void)
		*		void cb_evtTouchDoubleTap(void)
		*		void cb_evtTouchMoved(void)
		*		void cb_evtTouchCanceled(void)
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

		static eve::evt::TEvent<eve::evt::ResizeEventArgs> 		windowResized;			//!< Window resized event.
		static eve::evt::TEvent<void>							windowFocusGot;			//!< Window gain focus event.
		static eve::evt::TEvent<void>							windowFocusLost;		//!< Window lost focus event.
		static eve::evt::TEvent<void>							windowClose;			//!< Window closed event.

		/** \! Enable window events dispatch. */
		static void enable_events_window(void);
		/** \! Disable window events dispatch. */
		static void disable_events_window(void);

		/** \brief Notify window resize event to all listeners.*/
		static void notify_window_resize(uint32_t p_width, uint32_t p_height);
		/** \brief Notify window gain focus event to all listeners.*/
		static void notify_window_focus_got(void);
		/** \brief Notify window lost focus event to all listeners.*/
		static void notify_window_focus_lost(void);
		/** \brief Notify window close event to all listeners.*/
		static void notify_window_close(void);

		/**
		* \brief Register listener class to window events.
		* Listener class must provide window event handler methods using the following signatures:
		*		void cb_evtWindowReshape(void)
		*		void cb_evtWindowFocusGot(void)
		*		void cb_evtWindowFocusLost(void)
		*		void cb_evtWindowClose(void)
		*/
		template<class ListenerClass>
		void register_events_window(ListenerClass * listener, int32_t prio = orderAfterApp);
		/**
		* \brief Unregister listener class to window events.
		* Listener class must provide window event handler methods using the following signatures:
		*		void cb_evtWindowReshape(void)
		*		void cb_evtWindowFocusGot(void)
		*		void cb_evtWindowFocusLost(void)
		*		void cb_evtWindowClose(void)
		*/
		template<class ListenerClass>
		void unregister_events_window(ListenerClass * listener, int32_t prio = orderAfterApp);



		///////////////////////////////////////////////////////////////////////////////////////////
		//		APPLICATION EVENTS
		///////////////////////////////////////////////////////////////////////////////////////////

		static eve::evt::TEvent<void>							appExit;				//!< Application exit event.

		/** \! Enable application events dispatch. */
		static void enable_events_application(void);
		/** \! Disable application events dispatch. */
		static void disable_events_application(void);

		/** \brief Notify application exit event to all listeners.*/
		static void notify_application_exit(void);

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
	eve::evt::add_listener(eve::evt::keyPressed,	listener, &ListenerClass::cb_evtKeyDown,	prio);
	eve::evt::add_listener(eve::evt::keyReleased,	listener, &ListenerClass::cb_evtKeyUp,		prio);
	eve::evt::add_listener(eve::evt::keyInput,		listener, &ListenerClass::cb_evtKeyInput,	prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_key(ListenerClass * listener, int32_t prio)
{
	eve::evt::remove_listener(eve::evt::keyPressed,		listener, &ListenerClass::cb_evtKeyDown,	prio);
	eve::evt::remove_listener(eve::evt::keyReleased,	listener, &ListenerClass::cb_evtKeyUp,		prio);
	eve::evt::remove_listener(eve::evt::keyInput,		listener, &ListenerClass::cb_evtKeyInput,	prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		MOUSE EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_mouse(ListenerClass * listener, int32_t prio)
{
	eve::evt::add_listener(eve::evt::mouseDown,				listener, &ListenerClass::cb_evtMouseDown,			prio);
	eve::evt::add_listener(eve::evt::mouseUp,				listener, &ListenerClass::cb_evtMouseUp,			prio);
	eve::evt::add_listener(eve::evt::mouseDoubleClick,		listener, &ListenerClass::cb_evtMouseDoubleClick,	prio);
	eve::evt::add_listener(eve::evt::mouseMotion,			listener, &ListenerClass::cb_evtMotion,				prio);
	eve::evt::add_listener(eve::evt::mousePassiveMotion,	listener, &ListenerClass::cb_evtPassiveMotion,		prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_mouse(ListenerClass * listener, int32_t prio)
{
	eve::evt::remove_listener(eve::evt::mouseDown,			listener, &ListenerClass::cb_evtMouseDown,			prio);
	eve::evt::remove_listener(eve::evt::mouseUp,			listener, &ListenerClass::cb_evtMouseUp,			prio);
	eve::evt::remove_listener(eve::evt::mouseDoubleClick,	listener, &ListenerClass::cb_evtMouseDoubleClick,	prio);
	eve::evt::remove_listener(eve::evt::mouseMotion,		listener, &ListenerClass::cb_evtMotion,				prio);
	eve::evt::remove_listener(eve::evt::mousePassiveMotion, listener, &ListenerClass::cb_evtPassiveMotion,		prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		TOUCH EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_touch(ListenerClass * listener, int32_t prio)
{
	eve::evt::add_listener(eve::evt::touchDown,			listener, &ListenerClass::cb_evtTouchDown,		prio);
	eve::evt::add_listener(eve::evt::touchUp,			listener, &ListenerClass::cb_evtTouchUp,		prio);
	eve::evt::add_listener(eve::evt::touchDoubleTap,	listener, &ListenerClass::cb_evtTouchDoubleTap, prio);
	eve::evt::add_listener(eve::evt::touchMoved,		listener, &ListenerClass::cb_evtTouchMoved,		prio);
	eve::evt::add_listener(eve::evt::touchCanceled,		listener, &ListenerClass::cb_evtTouchCanceled,	prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_touch(ListenerClass * listener, int32_t prio)
{
	eve::evt::remove_listener(eve::evt::touchDown,		listener, &ListenerClass::cb_evtTouchDown,		prio);
	eve::evt::remove_listener(eve::evt::touchUp,		listener, &ListenerClass::cb_evtTouchUp,		prio);
	eve::evt::remove_listener(eve::evt::touchDoubleTap, listener, &ListenerClass::cb_evtTouchDoubleTap, prio);
	eve::evt::remove_listener(eve::evt::touchMoved,		listener, &ListenerClass::cb_evtTouchMoved,		prio);
	eve::evt::remove_listener(eve::evt::touchCanceled,	listener, &ListenerClass::cb_evtTouchCanceled,	prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		WINDOW EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void eve::evt::register_events_window(ListenerClass * listener, int32_t prio)
{
	eve::evt::add_listener(eve::evt::windowResized,		listener, &ListenerClass::cb_evtWindowReshape,		prio);
	eve::evt::add_listener(eve::evt::windowFocusGot,	listener, &ListenerClass::cb_evtWindowFocusGot,		prio);
	eve::evt::add_listener(eve::evt::windowFocusLost,	listener, &ListenerClass::cb_evtWindowFocusLost,	prio);
	eve::evt::add_listener(eve::evt::windowClose,		listener, &ListenerClass::cb_evtWindowClose,		prio);
}

//=================================================================================================
template<class ListenerClass>
void eve::evt::unregister_events_window(ListenerClass * listener, int32_t prio)
{
	eve::evt::remove_listener(eve::evt::windowResized,		listener, &ListenerClass::cb_evtWindowReshape,		prio);
	eve::evt::remove_listener(eve::evt::windowFocusGot,		listener, &ListenerClass::cb_evtWindowFocusGot,		prio);
	eve::evt::remove_listener(eve::evt::windowFocusLost,	listener, &ListenerClass::cb_evtWindowFocusLost,	prio);
	eve::evt::remove_listener(eve::evt::windowClose,		listener, &ListenerClass::cb_evtWindowClose,		prio);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		APPLICATION EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<class ListenerClass>
void register_events_application(ListenerClass * listener, int32_t prio)
{
	eve::evt::add_listener(eve::evt::appExit, listener, &ListenerClass::cb_evtApplicationExit, prio);
}

//=================================================================================================
template<class ListenerClass>
void unregister_events_application(ListenerClass * listener, int32_t prio)
{
	eve::evt::remove_listener(eve::evt::appExit, listener, &ListenerClass::cb_evtApplicationExit, prio);
}

#endif // __EVE_EVT_EVENT_H__

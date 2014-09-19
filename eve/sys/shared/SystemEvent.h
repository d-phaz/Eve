
/************************************************
 *                                              *
 *  CAUTION :                                   *
 *  this header is shared between target        *
 *  system compilations (Windows, OSX, LINUX)   *
 *                                              *
 ************************************************/


#pragma once
#ifndef __SYSTEM_EVENT_H__
#define __SYSTEM_EVENT_H__

// Native types
#ifndef __NATIVE_TYPES_H__
#include "Native_types.h"
#endif

// System header
#ifndef __SYSTEM_KEYBOARD_H__
#include "system/win32/SystemKeyboard.h"
#endif

#ifndef __SYSTEM_MOUSE_H__
#include "system/shared/SystemMouse.h"
#endif


class SystemWindow;

namespace evt
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//	System event types enum
	///////////////////////////////////////////////////////////////////////////////////////////////

	enum SystemEventType 
	{
		NO_EVENT = 0,

		KEY_DOWN,
		KEY_UP,
		TEXT_INPUT,

		BUTTON_DOWN,
		BUTTON_UP,
		BUTTON_DOUBLE,
		MOTION,
		PASSIVE_MOTION,
		MOUSE_ENTER,
		MOUSE_LEAVE,

		EXPOSE,
		RESIZE,
		FOCUS_GOT,
		FOCUS_LOST,
		SHOW,
		HIDE,

		CLOSE,
		DROP_FILES
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	//	EventType structure
	///////////////////////////////////////////////////////////////////////////////////////////////

	typedef struct 
	{
		// Shared
		SystemEventType						eventType;
	} EventType;



	///////////////////////////////////////////////////////////////////////////////////////////////
	//	System Events
	///////////////////////////////////////////////////////////////////////////////////////////////

	struct AnyEvent
	{
		EventType type;
		int32_t x, y, a, b, c;
	};


	struct KeyEvent
	{
		EventType type;
		keyboard::Symbol symbol;
		keyboard::KeyMod keymod;
		bool repeat;
	};


	struct ButtonEvent
	{
		EventType type;
		int32_t x, y;
		mouse::Button button;
		mouse::ButtonMask buttons;
		//keyboard::KeyMod keymod;
	};


	struct TextEvent
	{
		EventType type;
		int32_t unicode;
	};


	struct ExposeEvent
	{
		EventType type;
		int32_t x, y;
		int32_t width, height;
	};

	struct MotionEvent
	{
		EventType type;
		int32_t x, y;
		mouse::ButtonMask buttons;
		keyboard::KeyMod keymod;
	};

	struct MouseOverEvent
	{
		EventType type;
		int32_t x, y;
	};

	struct ResizeEvent
	{
		EventType type;
		int32_t width, height;
	};

	typedef AnyEvent CloseEvent;
	typedef AnyEvent FocusEvent;
	typedef AnyEvent ShowEvent;

	struct FileDropEvent
	{
		EventType type;
		wchar_t** filesname;
		int32_t numberOfFiles;
		int32_t x, y;
	};

	


	///////////////////////////////////////////////////////////////////////////////////////////////
	//	Event type union
	///////////////////////////////////////////////////////////////////////////////////////////////

	union Event
	{
		EventType			type;

		// System
		AnyEvent			any;
		KeyEvent			key;
		ButtonEvent			button;
		TextEvent			text;
		CloseEvent			close;
		ExposeEvent			expose;
		FocusEvent			focus;
		MotionEvent			motion;
		MouseOverEvent		mouseover;
		ResizeEvent			resize;
		ShowEvent			show;
		FileDropEvent		filedrop;
	};

}	// namespace evt 

#endif // __SYSTEM_EVENT_H__

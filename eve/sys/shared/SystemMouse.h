
/************************************************
 *                                              *
 *  CAUTION :                                   *
 *  this header is shared between target        *
 *  system compilations (Windows, OSX, LINUX)   *
 *                                              *
 ************************************************/

#pragma once
#ifndef __SYSTEM_MOUSE_H__
#define __SYSTEM_MOUSE_H__



/// Mouse button enumerations and utility functions
namespace mouse
{
	/// Mouse button enumeration
	enum Button {
		/// Unknown mouse button
		UNKNOWN = 1,
		/// Left mouse button
		BUTTON_LEFT = 2, 
		/// Middle mouse button
		BUTTON_MIDDLE = 3,
		/// Right mouse button
		BUTTON_RIGHT = 4,
		/// Mouse wheel up
		WHEEL_UP = 5,
		/// Mouse wheel down
		WHEEL_DOWN = 6,
		/// Scroll left
		SCROLL_LEFT = 7,
		/// Scroll right
		SCROLL_RIGHT = 8,
		/// X UIButton
		BUTTON_X = 9,
		/// Y UIButton
		BUTTON_Y = 10
	};

	// Mouse button state enum
	enum ButtonState
	{
		/// Unknown state
		UNKNOWN_STATE = 1,
		// Down state
		DOWN = 2,
		// Up state
		UP = 3,
		// Double Click state
		DBLE_CLICK = 4
	};
		
	/// Get a string representation of a button
	const char  * buttonName(Button button);
		
	/// Mouse button mask type
	typedef unsigned char ButtonMask;
		
	/// Left mouse button mask
	const ButtonMask MASK_LEFT = 1 << 0;
	/// Middle mouse button mask
	const ButtonMask MASK_MIDDLE = 1 << 1;
	/// Right mouse button mask
	const ButtonMask MASK_RIGHT = 1 << 2;

} // namespace mouse

#endif // __SYSTEM_MOUSE_H__

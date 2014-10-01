
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
#include "eve/sys/win32/Keyboard.h"

namespace
{
	WPARAM reverse_keymap[eve::sys::Key::key_Num_Keys] = 
	{
		0,                  // UNKNOWN
		0, 0, 0, 0, 0,      // 0x01 - 0x07 unused (total: 7)
		0, 0,

		VK_BACK,            // BACKSPACE
		VK_TAB,             // TAB
		0,                  // LINEFEED
		VK_CLEAR,           // CLEAR

		0,                  // 0x0c unused

		VK_RETURN,          // RETURN,

		0, 0, 0, 0, 0,      // 0x0e - 0x1a unused (total: 13)
		0, 0, 0, 0, 0,
		0, 0, 0,

		VK_ESCAPE,          // ESCAPE

		0, 0, 0, 0,     // 0x1c - 0x1f unused (total: 4)

		VK_SPACE,           // SPACE
		0,                  // EXCLAIM
		0,                  // DOUBLEQUOTE
		0,                  // HASH
		0,                  // DOLLAR

		0,                  // 0x25 unused

		0,                  // AMPERSAND
		0,                  // QUOTE
		0,                  // LEFTPAREN
		0,                  // RIGHTPAREN
		0,                  // ASTERISK
		0,                  // PLUS
		0,                  // COMMA
		0,                  // MINUS
		0,                  // PERIOD
		0,                  // SLASH

		0x30,                // KEY_0
		0x31,                // KEY_1
		0x32,                // KEY_2
		0x33,                // KEY_3
		0x34,                // KEY_4
		0x35,                // KEY_5
		0x36,                // KEY_6
		0x37,                // KEY_7
		0x38,                // KEY_8
		0x39,                // KEY_9

		0,                  // COLON
		0,                  // SEMICOLON
		0,                  // LESS
		0,                  // EQUALS
		0,                  // GREATER
		0,                  // QUESTION
		0,                  // AT

		0, //'A',                // KEY_A
		0, //'B',                // KEY_B
		0, //'C',                // KEY_C
		0, //'D',                // KEY_D
		0, //'E',                // KEY_E
		0, //'F',                // KEY_F
		0, //'G',                // KEY_G
		0, //'H',                // KEY_H
		0, //'I',                // KEY_I
		0, //'J',                // KEY_J
		0, //'K',                // KEY_K
		0, //'L',                // KEY_L
		0, //'M',                // KEY_M
		0, //'N',                // KEY_N
		0, //'O',                // KEY_O
		0, //'P',                // KEY_P
		0, //'Q',                // KEY_Q
		0, //'R',                // KEY_R
		0, //'S',                // KEY_S
		0, //'T',                // KEY_T
		0, //'U',                // KEY_U
		0, //'V',                // KEY_V
		0, //'W',                // KEY_W
		0, //'X',                // KEY_X
		0, //'Y',                // KEY_Y
		0, //'Z',                // KEY_Z

		0,                  // LEFTBRACKET
		0,                  // BACKSLASH
		0,                  // RIGHTBRACKET
		0,                  // CARET
		0,                  // UNDERSCORE
		0,                  // BACKQUOTE

		0, 0, 0, 0, 0,      // 0x61 - 0x7e unused (total: 30)
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,

		VK_DELETE,          // DELETE

		// END OF ASCII

		0, 0, 0, 0, 0,      // 0x80 - 0x9f unused (total: 32)
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0,

		// International unicode characters 0xa0 - 0xff
		// Unused for now (total: 96)
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0,

		VK_NUMPAD0,         // KEYPAD_0
		VK_NUMPAD1,         // KEYPAD_1
		VK_NUMPAD2,         // KEYPAD_2
		VK_NUMPAD3,         // KEYPAD_3
		VK_NUMPAD4,         // KEYPAD_4
		VK_NUMPAD5,         // KEYPAD_5
		VK_NUMPAD6,         // KEYPAD_6
		VK_NUMPAD7,         // KEYPAD_7
		VK_NUMPAD8,         // KEYPAD_8
		VK_NUMPAD9,         // KEYPAD_9

		VK_DECIMAL,			// KEYPAD_SEPARATOR
		VK_DIVIDE,          // KEYPAD_DIVIDE
		VK_MULTIPLY,        // KEYPAD_MULTIPLY
		VK_ADD,             // KEYPAD_PLUS
		VK_SUBTRACT,        // KEYPAD_MINUS
		VK_RETURN,          // KEYPAD_ENTER

		VK_UP,              // UP
		VK_DOWN,            // DOWN
		VK_LEFT,            // LEFT
		VK_RIGHT,           // RIGHT
		VK_INSERT,          // INSERT
		VK_HOME,            // HOME
		VK_END,             // END
		VK_PRIOR,           // PAGEUP
		VK_NEXT,            // PAGEDOWN

		VK_F1,              // F1
		VK_F2,              // F2
		VK_F3,              // F3
		VK_F4,              // F4
		VK_F5,              // F5
		VK_F6,              // F6
		VK_F7,              // F7
		VK_F8,              // F8
		VK_F9,              // F9
		VK_F10,             // F10
		VK_F11,             // F10
		VK_F12,             // F12
		VK_F13,             // F13
		VK_F14,             // F14
		VK_F15,             // F15
		VK_F16,             // F16
		VK_F17,             // F17
		VK_F18,             // F18
		VK_F19,             // F19
		VK_F20,             // F20
		VK_F21,             // F21
		VK_F22,             // F22
		VK_F23,             // F23
		VK_F24,             // F24

		VK_NUMLOCK,			// NUMLOCK
		VK_CAPITAL,			// CAPSLOCK
		VK_SCROLL,          // SCROLLLOCK
		VK_SHIFT,           // LSHIFT
		0,                  // RSHIFT
		VK_CONTROL,			// LCTRL
		0,                  // RCRTL
		VK_MENU,            // LALT
		0,                  // RALT
		VK_LWIN,            // LSUPER
		VK_RWIN,            // RSUPER

		0,                  // ALTGR
		0,                  // COMPOSE
		VK_RMENU,           // MENU

		0,                  // SYS_REQ
		VK_PAUSE,           // PAUSE
		VK_SNAPSHOT,        // PRINT

		0,                  // DEAD_GRAVE
		0,                  // DEAD_ACUTE
		0,                  // DEAD_CIRCUMFLEX
		0,                  // DEAD_TILDE
		0,                  // DEAD_MACRON
		0,                  // DEAD_BREVE
		0,                  // DEAD_ABOVEDOT
		0,                  // DEAD_DIAERESIS
		0,                  // DEAD_ABOVERING

		0                   // TERMINATOR
	};

	typedef std::map<WPARAM, eve::sys::Key> Keymap;

	const struct Mapper
	{
		Mapper()
		{
			for (uint32_t i = 0; i < uint32_t(eve::sys::key_Num_Keys); ++i)
			{
				WPARAM wparam = reverse_keymap[i];
				if (wparam)
					map[wparam] = eve::sys::Key(i);
			}
		}

		Keymap map;
	} mapper;


	eve::sys::Key mapVirtualKeyCode(WPARAM vCode)
	{
		const Keymap & map = mapper.map;
		Keymap::const_iterator itr = map.find(vCode);

		if (itr == map.end()) return eve::sys::key_Unused;
		
		return itr->second;
	}
}


//=================================================================================================
eve::sys::Key eve::sys::translate_key(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam, bool & p_bFilter)
{
	p_bFilter = false;

	// Handle Keypad and Numlock
	if (!(HIWORD(p_lParam) & 0x100))
	{
		UINT mapped = ::MapVirtualKeyW(HIWORD(p_lParam) & 0xFF, MAPVK_VSC_TO_VK);

		switch (mapped)
		{
		case VK_INSERT:     return	eve::sys::key_Pad_0;
		case VK_END:        return	eve::sys::key_Pad_1;
		case VK_DOWN:       return	eve::sys::key_Pad_2;
		case VK_NEXT:       return	eve::sys::key_Pad_3;
		case VK_LEFT:       return	eve::sys::key_Pad_4;
		case VK_CLEAR:      return	eve::sys::key_Pad_5;
		case VK_RIGHT:      return	eve::sys::key_Pad_6;
		case VK_HOME:       return	eve::sys::key_Pad_7;
		case VK_UP:         return	eve::sys::key_Pad_8;
		case VK_PRIOR:      return	eve::sys::key_Pad_9;
		case VK_DIVIDE:     return	eve::sys::key_Pad_Divide;
		case VK_MULTIPLY:   return	eve::sys::key_Pad_Multiply;
		case VK_SUBTRACT:   return	eve::sys::key_Pad_Minus;
		case VK_ADD:        return	eve::sys::key_Pad_Plus;
		case VK_DELETE:     return	eve::sys::key_Pad_Separator;
		//case VK_SPACE:	return keyboard::SPACE;
		default:            break;
		}
	}


	if (p_wParam == VK_SHIFT)
	{
		UINT scancode = MapVirtualKeyW(VK_RSHIFT, MAPVK_VK_TO_VSC);
		if (((p_lParam & 0x01ff0000) >> 16) == scancode)
		{
			return eve::sys::key_ShiftRight;
		}
		return eve::sys::key_ShiftLeft;
	}
	else if(p_wParam == VK_CONTROL)
	{
	    if(p_lParam & 0x01000000)
			return eve::sys::key_CtrlRight;

	    if(p_uMsg == WM_SYSKEYUP)
	    {
	        // WM_SYSKEYUP following the release of AltGR
	        p_bFilter = true;
			return eve::sys::key_Unused;
	    }

	    // Detect AltGR
	    LONG msgtime = ::GetMessageTime();
	    MSG msg;
	    if(::PeekMessage(&msg, p_hWnd, WM_KEYFIRST, WM_KEYLAST, PM_NOREMOVE))
	    {
	        if( (msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN) 
			 && msg.wParam == VK_MENU 
	         && (msg.lParam & 0x01000000) 
			 && msg.time == msgtime)
	        {
	            p_bFilter = true;
				return eve::sys::key_Unused; // next message is RALT down
	        }
	    }

		return eve::sys::key_CtrlLeft;
	} 
	else if (p_wParam == VK_MENU)
	{
		if (p_lParam & 0x01000000)
			return eve::sys::key_AltRight;
		return eve::sys::key_AltLeft;
	}
	else if (p_wParam == VK_RETURN)
	{
		if (p_lParam & 0x01000000)
			return eve::sys::key_Pad_Enter;

		return eve::sys::key_Return;
	}

	UINT charcode = ::MapVirtualKeyW(static_cast<UINT>(p_wParam), MAPVK_VK_TO_CHAR);
	if ((charcode >= 0x20 && charcode < 0x40) ||	// some ASCII characters
		(charcode >= 0xa0 && charcode <= 0xff))		// Latin-1 supplement
	{
		p_bFilter = true;
		//return static_cast<keyboard::Symbol>(charcode);
		return eve::sys::key_Unused;
	}


	eve::sys::Key key = mapVirtualKeyCode(p_wParam);
	if (!key)
	{
		p_bFilter = true;
		return eve::sys::key_Unused;
	}
	else
	{
		return key;
	}
}



//=================================================================================================
bool eve::sys::get_key_state_ctrl(void)			{ return (::GetKeyState(VK_CONTROL) == 1);	}
bool eve::sys::get_key_state_alt(void)			{ return (::GetKeyState(VK_MENU) == 1);		}
bool eve::sys::get_key_state_shift(void)		{ return (::GetKeyState(VK_SHIFT) == 1);	}

//=================================================================================================
bool eve::sys::get_async_key_state_ctrl(void)	{ return (::GetAsyncKeyState(VK_CONTROL) & 0x8000); }
bool eve::sys::get_async_key_state_alt(void)	{ return (::GetAsyncKeyState(VK_MENU) & 0x8000);	}
bool eve::sys::get_async_key_state_shift(void)	{ return (::GetAsyncKeyState(VK_SHIFT) & 0x8000);	}

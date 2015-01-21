
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
#ifndef __EVE_SYSTEM_KEYBOARD_H__
#define __EVE_SYSTEM_KEYBOARD_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif


namespace eve
{
	namespace sys
	{
		/**
		* \brief eve::sys::Key symbol enumeration.
		* 
		* \note Keys representing the Latin-1 supplement characters (Unicode 0xa0-0xff) are usually
		* mapped to lower case characters, for example aDIARESIS instead of ADIARESIS.
		*
		* \note the numeric values of the enumerated may change, use symbols instead
		*/
		enum Key
		{
			// Unknown key.
			key_Unknown = 0,

			// Retrieve ctrl pressed keys (faster).
			key_ctrl_a = 1,
			key_ctrl_b = 2,
			key_ctrl_c = 3,
			key_ctrl_d = 4,
			key_ctrl_e = 5,
			key_ctrl_f = 6,
			key_ctrl_g = 7,
			key_ctrl_h = 8,
			key_ctrl_i = 9,
			key_ctrl_j = 10,
			key_ctrl_k = 11,
			key_ctrl_l = 12,
			key_ctrl_m = 13,
			key_ctrl_n = 14,
			key_ctrl_o = 15,
			key_ctrl_p = 16,
			key_ctrl_q = 17,
			key_ctrl_r = 18,
			key_ctrl_s = 19,
			key_ctrl_t = 20,
			key_ctrl_u = 21,
			key_ctrl_v = 22,
			key_ctrl_w = 23,
			key_ctrl_x = 24,
			key_ctrl_y = 25,
			key_ctrl_z = 26,

			key_ctrl_space = 32,

			// 0x01 - 0x07 unused (total: 7)


			// Backspace
			key_Backspace	= 0x08,
			// Tabulator
			key_Tab			= 0x09,
			// Line feed
			key_LineFeed	= 0x0a,
			// Clear
			key_Clear		= 0x0b,
			// 0x0c unused
			// Return/Enter key
			key_Return		= 0x0d,
			// 0x0e - 0x1a unused (total: 13)
			// The Escape key
			key_Escape		= 0x1b,
			// 0x1c - 0x1f unused (total: 4)
			// The space bar
			kye_Space		= 0x20,
			// Exclamation sign
			kye_Exclaim		= 0x21,
			// Double quotes
			kye_DoubleQuote = 0x22,
			// Hash sign (#)
			kye_Hash		= 0x23,
			// Dollar sign
			kye_Dollar		= 0x24,

			// 0x25 unused

			// Ampersand
			kye_Ampersand = 0x26,
			// Quote
			key_Quote = 0x27,
			// Left parenthesis
			key_LeftParenthesis = 0x28,
			// Right parenthesis
			key_RightParenthesis = 0x29,
			// Asterisk
			key_Asterisk = 0x2a,
			// Plus
			key_Plus = 0x2b,
			// Comma
			key_Comma = 0x2c,
			// Minus
			key_Minus = 0x2d,
			// Period
			key_Period = 0x2e,
			// Slash
			key_Slash = 0x2f,

			// Number 
			key_0 = 0x30,
			key_1 = 0x31,
			key_2 = 0x32,
			key_3 = 0x33,
			key_4 = 0x34,
			key_5 = 0x35,
			key_6 = 0x36,
			key_7 = 0x37,
			key_8 = 0x38,
			key_9 = 0x39,

			// Colon
			key_Colon = 0x3a,
			// Semicolon
			key_SemiColon = 0x3b,
			// Less than
			key_Less = 0x3c,
			// Equals
			key_Equals = 0x3d,
			// Greater than
			key_Greater = 0x3e,
			// Question mark
			key_QuestionMark = 0x3f,
			// At sign (@)
			key_At = 0x40,

			key_A = 0x41,
			key_B = 0x42,
			key_C = 0x43,
			key_D = 0x44,
			key_E = 0x45,
			key_F = 0x46,
			key_G = 0x47,
			key_H = 0x48,
			key_I = 0x49,
			key_J = 0x4a,
			key_K = 0x4b,
			key_L = 0x4c,
			key_M = 0x4d,
			key_N = 0x4e,
			key_O = 0x4f,
			key_P = 0x50,
			key_Q = 0x51,
			key_R = 0x52,
			key_S = 0x53,
			key_T = 0x54,
			key_U = 0x55,
			key_V = 0x56,
			key_W = 0x57,
			key_X = 0x58,
			key_Y = 0x59,
			key_Z = 0x5a,

			// Left bracket
			key_LeftBracket = 0x5b,
			// Backslash
			key_BackSlash = 0x5c,
			// Right bracket
			key_RightBracket = 0x5d,
			// Caret
			key_Caret = 0x5e,
			// Underscore
			key_Underscore = 0x5f,
			// Back quote
			key_BackQuote = 0x60,

			// 0x61 - 0x7e unused (total: 30)

			// Delete
			key_Delete = 0x7f,

			// END OF ASCII

			// 0x80 - 0x9f unused (total: 32)

			// International unicode characters 0xa0 - 0xff
			// no-break space
			key_NoBreakSpace = 0xa0,
			// inverted exclamation mark
			key_ExclamationMarkInverted = 0xa1,
			// cent sign
			key_Cent = 0xa2,
			// pound sign
			key_Sterling = 0xa3,
			// currency sign
			key_Currency = 0xa4,
			// yen sign
			key_Yen = 0xa5,
			// broken bar
			key_BrokenBar = 0xa6,
			// section sign
			key_Section = 0xa7,
			// diaeresis
			key_Diaeresis = 0xa8,
			// copyright sign
			key_Copyright = 0xa9,
			// feminine ordinal indicator
			key_OrdFeminine = 0xaa,
			// left-pointing double angle quotation mark
			key_GuillemotLeft = 0xab,
			// not sign
			key_NotSign = 0xac,
			// soft hyphen
			key_Hyphen = 0xad,
			// registered sign
			key_Registered = 0xae,
			// macron
			key_Macron = 0xaf,
			// degree sign
			key_Degree = 0xb0,
			// plus-minus sign
			key_PlusMinus = 0xb1,
			// superscript two
			key_TwoSuperior = 0xb2,
			// superscript three
			key_ThreeSuperior = 0xb3,
			// acute accent
			key_Acute = 0xb4,
			// micro sign
			key_Mu = 0xb5,
			// pilcrow sign
			key_Paragraph = 0xb6,
			// middle dot
			key_PeriodCentered = 0xb7,
			// cedilla
			key_Cedilla = 0xb8,
			// superscript one
			key_OneSuperior = 0xb9,
			// masculine ordinal indicator
			key_Masculine = 0xba,
			// right-pointing double angle quotation mark
			key_GuillemotRight = 0xbb,
			// vulgar fraction one quarter
			key_OneQuarter = 0xbc,
			// vulgar fraction one half
			key_OneHalf = 0xbd,
			// vulgar fraction three quarters
			key_ThreeQuarter = 0xbe,
			// inverted question mark
			key_QuestionMarkInverted = 0xbf,
			
			// Latin capital letter a with grave
			key_A_grave = 0xc0,
			// Latin capital letter a with acute
			key_A_acute = 0xc1,
			// Latin capital letter a with circumflex
			key_A_circumflex = 0xc2,
			// Latin capital letter a with tilde
			key_A_tilde = 0xc3,
			// Latin capital letter a with diaeresis
			key_A_diaeresis = 0xc4,
			// Latin capital letter a with ring above
			key_A_ring = 0xc5,
			// Latin capital letter ae
			key_Ae = 0xc6,

			// Latin capital letter c with cedilla
			key_C_cedilla = 0xc7,

			// Latin capital letter e with grave
			key_E_grave = 0xc8,
			// Latin capital letter e with acute
			key_E_acute = 0xc9,
			// Latin capital letter e with circumflex
			key_E_circumflex = 0xca,
			// Latin capital letter e with diaeresis
			key_E_diaeresis = 0xcb,

			// Latin capital letter i with grave
			key_I_grave = 0xcc,
			// Latin capital letter i with acute
			key_I_acute = 0xcd,
			// Latin capital letter i with circumflex
			key_I_circumflex = 0xce,
			// Latin capital letter i with diaeresis
			key_I_diaeresis = 0xcf,

			// Latin capital letter eth
			key_Eth = 0xd0,

			// Latin capital letter n with tilde
			key_N_tilde = 0xd1,

			// Latin capital letter o with grave
			key_O_grave = 0xd2,
			// Latin capital letter o with acute
			key_O_acute = 0xd3,
			// Latin capital letter o with circumflex
			key_O_circumflex = 0xd4,
			// Latin capital letter o with tilde
			key_O_tilde = 0xd5,
			// Latin capital letter o with diaeresis
			key_O_diaeresis = 0xd6,

			// multiplication sign
			key_Multiply = 0xd7,

			// Latin capital letter o with stroke
			key_O_slash = 0xd8,

			// Latin capital letter u with grave
			key_U_grave = 0xd9,
			// Latin capital letter u with acute
			key_U_acute = 0xda,
			// Latin capital letter u with circumflex
			key_U_circumflex = 0xdb,
			// Latin capital letter u with diaeresis
			key_U_diaeresis = 0xdc,

			// Latin capital letter y with acute
			key_Y_acute = 0xdd,
			// Latin capital letter thorn
			key_Thorn = 0xde,

			// Latin small letter sharp s
			key_S_sharp = 0xdf,

			// Latin small letter a with grave
			key_a_Grave = 0xe0,
			// Latin small letter a with acute
			key_a_Cute = 0xe1,
			// Latin small letter a with circumflex
			key_a_Circumflex = 0xe2,
			// Latin small letter a with tilde
			key_a_Tilde = 0xe3,
			// Latin small letter a with diaeresis
			key_a_Diaeresis = 0xe4,
			// Latin small letter a with ring above
			key_a_Ring = 0xe5,
			// Latin small letter ae
			key_ae = 0xe6,

			// Latin small letter c with cedilla
			key_c_Cedilla = 0xe7,

			// Latin small letter e with grave
			key_e_Grave = 0xe8,
			// Latin small letter e with acute
			key_e_Acute = 0xe9,
			// Latin small letter e with circumflex
			key_e_Circumflex = 0xea,
			// Latin small letter e with diaeresis
			key_e_Diaeresis = 0xeb,

			// Latin small letter i with grave
			key_i_Grave = 0xec,
			// Latin small letter i with acute
			key_i_Acute = 0xed,
			// Latin small letter i with circumflex
			key_i_Circumflex = 0xee,
			// Latin small letter i with diaeresis
			key_i_Diaeresis = 0xef,

			// Latin small letter eth
			key_eth = 0xf0,

			// Latin small letter n with tilde
			key_n_Tilde = 0xf1,

			// Latin small letter o with grave
			key_o_Grave = 0xf2,
			// Latin small letter o with acute
			key_o_Acute = 0xf3,
			// Latin small letter o with circumflex
			key_o_Circumflex = 0xf4,
			// Latin small letter o with tilde
			key_o_Tilde = 0xf5,
			// Latin small letter o with diaeresis
			key_o_Diaeresis = 0xf6,

			// division sign
			key_Division = 0xf7,

			// Latin small letter o with stroke
			key_o_Slash = 0xf8,

			// Latin small letter u with grave
			key_u_Grave = 0xf9,
			// Latin small letter u with acute
			key_u_Acute = 0xfa,
			// Latin small letter u with circumflex
			key_u_Circumflex = 0xfb,
			// Latin small letter u with diaeresis
			key_u_Diaeresis = 0xfc,

			// Latin small letter y with acute
			key_y_Acute = 0xfd,
			// Latin small letter thorn
			key_t_horn = 0xfe,
			// Latin small letter y with diaeresis
			key_y_Diaeresis = 0xff,

			key_Pad_0 = 0x100,
			key_Pad_1 = 0x101,
			key_Pad_2 = 0x102,
			key_Pad_3 = 0x103,
			key_Pad_4 = 0x104,
			key_Pad_5 = 0x105,
			key_Pad_6 = 0x106,
			key_Pad_7 = 0x107,
			key_Pad_8 = 0x108,
			key_Pad_9 = 0x109,

			// Keypad comma
			key_Pad_Separator = 0x10a,
			// Keypad divide
			key_Pad_Divide = 0x10b,
			// Keypad multiply
			key_Pad_Multiply = 0x10c,
			// Keypad plus
			key_Pad_Plus = 0x10d,
			// Keypad minus
			key_Pad_Minus = 0x10e,
			// Keypad enter
			key_Pad_Enter = 0x10f,

			// The up arrow
			key_Up = 0x110,
			// The down arrow
			key_Down = 0x111,
			// The left arrow
			key_Left = 0x112,
			// The right arrow
			key_Right = 0x113,
			//	Insert
			key_Insert = 0x114,
			// Home
			key_Home = 0x115,
			// End
			key_End = 0x116,
			// Page up
			key_PageUp = 0x117,
			// Page down
			key_PageDown = 0x118,

			// Function keys
			key_F1  = 0x119,
			key_F2  = 0x11a,
			key_F3  = 0x11b,
			key_F4  = 0x11c,
			key_F5  = 0x11d,
			key_F6  = 0x11e,
			key_F7  = 0x11f,
			key_F8  = 0x120,
			key_F9  = 0x121,
			key_F10 = 0x122,
			key_F11 = 0x123,
			key_F12 = 0x124,
			key_F13 = 0x125,
			key_F14 = 0x126,
			key_F15 = 0x127,
			key_F16 = 0x128,
			key_F17 = 0x129,
			key_F18 = 0x12a,
			key_F19 = 0x12b,
			key_F20 = 0x12c,
			key_F21 = 0x12d,
			key_F22 = 0x12e,
			key_F23 = 0x12f,
			key_F24 = 0x130,

			// Num Lock
			key_NumLock = 0x131,
			// Caps Lock
			key_CapsLock = 0x132,
			// Scroll Lock
			key_ScrollLock = 0x133,

			// Left shift
			key_ShiftLeft = 0x134,
			// Right shift
			key_ShiftRight = 0x135,
			// Left control
			key_CtrlLeft = 0x136,
			// Right control
			key_CtrlRight = 0x137,
			// Left ALT
			key_AltLeft = 0x138,
			// Right ALT
			key_AltRight = 0x139,
			// Left Super key
			key_SuperLeft = 0x140,
			// Right Super key
			key_SuperRight = 0x141,

			// AltGR
			key_AltGr = 0x142,
			// Multi key compose
			key_Compose = 0x143,
			// Menu key (usually between right Super and Control)
			key_Menu = 0x144,

			// System request
			key_SystemRequest = 0x145,
			// Pause
			key_Pause = 0x146,
			// Print screen
			key_Print = 0x147,

			// Dead grave accent
			key_DeadGrave = 0x148,
			// Dead acute accent
			key_DeadAcute = 0x149,
			// Dead circumflex
			key_DeadCircumflex = 0x14a,
			// Dead tilde
			key_DeadTilde = 0x14b,
			// Dead macron
			key_DeadMacron = 0x14c,
			// Dead breve
			key_DeadBreve = 0x14d,
			// Dead dot above letter
			key_DeadAboveDot = 0x14e,
			// Dead diaeresis
			key_DeadDiaeresis = 0x14f,
			// Dead ring above letter
			key_DeadAboveRing = 0x150,

			key_Num_Keys // Terminator
		};

		/** \brief Get key name from key symbol enum. */
		const wchar_t * get_key_name(Key p_key);

		
		/** \brief Get key symbol from WPARAM. */
		Key map_key_code(WPARAM p_code);
		/** \brief Convert system key event to eve::sys::Key. */
		Key translate_key(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam, bool & p_bFilter);


		/** 
		* \def eve::sys::KeyModifier
		* \brief Keyboard modifier mask type. 
		*/
		typedef int32_t KeyModifier;
		const KeyModifier KEY_MODIFIER_SHIFT_MASK		= 1 << 0;		//!< Specifies SHIFT key mask.
		const KeyModifier KEY_MODIFIER_CONTROL_MASK		= 1 << 1;		//!< Specifies CONTROL key mask.
		const KeyModifier KEY_MODIFIER_ALT_MASK			= 1 << 2;		//!< Specifies ALT key mask.
		const KeyModifier KEY_MODIFIER_SUPER_MASK		= 1 << 3;		//!< Specifies SUPER key mask.
		const KeyModifier KEY_MODIFIER_ALT_GR_MASK		= 1 << 4;		//!< Specifies ALT_GR key mask.
		const KeyModifier KEY_MODIFIER_NUM_LOCK_MASK	= 1 << 5;		//!< Specifies NUM_LOCK key mask.
		const KeyModifier KEY_MODIFIER_CAPS_LOCK_MASK	= 1 << 6;		//!< Specifies CAPS_LOCK key mask.


		/** \brief Get ctrl key pressed state at the time a key is pressed. */
		bool get_key_state_ctrl(void);
		/** \brief Get alt key pressed state at the time a key is pressed. */
		bool get_key_state_alt(void);
		/** \brief Get shift key pressed state at the time a key is pressed. */
		bool get_key_state_shift(void);


		/** \brief Get ctrl key pressed state at the time the function is called. */
		bool get_async_key_state_ctrl(void);
		/** \brief Get alt key pressed state at the time the function is called. */
		bool get_async_key_state_alt(void);
		/** \brief Get shift key pressed state at the time the function is called. */
		bool get_async_key_state_shift(void);


		/** \brief Retrieve ctrl pressed state from modifier. */
		bool modifier_crtl(KeyModifier p_mod);
		/** \brief Retrieve ctrl pressed state from modifier. */
		bool modifier_alt(KeyModifier p_mod);
		/** \brief Retrieve ctrl pressed state from modifier. */
		bool modifier_shift(KeyModifier p_mod);


		/** \brief Test if modifier(s) is/are pressed at event time. */
		KeyModifier get_key_modifier_state(void);
		/** \brief Test modifier key from WPARAM. */
		KeyModifier map_key_modifier(WPARAM p_wParam);

	} // namespace sys

} // namespace eve

#endif // __EVE_SYSTEM_KEYBOARD_H__

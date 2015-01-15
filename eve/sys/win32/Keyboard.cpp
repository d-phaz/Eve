
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
	static const wchar_t * symbol_names[eve::sys::key_Num_Keys + 1] =
	{
		EVE_TXT("Null"),

		EVE_TXT("CTRL_A SOH"),
		EVE_TXT("CTRL_B STX"),
		EVE_TXT("CTRL_C ETX"),
		EVE_TXT("CTRL_D EOT"),
		EVE_TXT("CTRL_E ENQ"),
		EVE_TXT("CTRL_F ACK"),
		EVE_TXT("CTRL_G bell"),
		EVE_TXT("CTRL_H Backspace"),
		EVE_TXT("CTRL_I Tab"),
		EVE_TXT("CTRL_J Line feed"),
		EVE_TXT("CTRL_K VT CLEAR"),
		EVE_TXT("CTRL_L FF"),
		EVE_TXT("CTRL_M CR Return"),
		EVE_TXT("CTRL_N SO"),
		EVE_TXT("CTRL_O SI"),
		EVE_TXT("CTRL_P DLE"),
		EVE_TXT("CTRL_Q DC1"),
		EVE_TXT("CTRL_R DC2"),
		EVE_TXT("CTRL_S DC3"),
		EVE_TXT("CTRL_T DC4"),
		EVE_TXT("CTRL_U NAK"),
		EVE_TXT("CTRL_V SYN"),
		EVE_TXT("CTRL_W ETB"),
		EVE_TXT("CTRL_X CAN"),
		EVE_TXT("CTRL_Y EM"),
		EVE_TXT("CTRL_Z SUB"),

		EVE_TXT("ESC Escape"),
		EVE_TXT("FS"),
		EVE_TXT("GS"),
		EVE_TXT("RS"),
		EVE_TXT("US"),

		EVE_TXT("Space"),
		EVE_TXT("Exclamation"),
		EVE_TXT("Double quote"),
		EVE_TXT("Hash"),
		EVE_TXT("Dollar"),

		EVE_TXT("Percent"),
		EVE_TXT("Ampersand"),
		EVE_TXT("Quote"),
		EVE_TXT("Left parenthesis"),
		EVE_TXT("Right parenthesis"),
		EVE_TXT("Asterisk"),
		EVE_TXT("Plus"),
		EVE_TXT("Comma"),
		EVE_TXT("Minus"),
		EVE_TXT("Period"),
		EVE_TXT("Slash"),

		EVE_TXT("0"),
		EVE_TXT("1"),
		EVE_TXT("2"),
		EVE_TXT("3"),
		EVE_TXT("4"),
		EVE_TXT("5"),
		EVE_TXT("6"),
		EVE_TXT("7"),
		EVE_TXT("8"),
		EVE_TXT("9"),

		EVE_TXT("Colon"),
		EVE_TXT("Semicolon"),
		EVE_TXT("Less"),
		EVE_TXT("Equals"),
		EVE_TXT("Greater"),
		EVE_TXT("Question"),
		EVE_TXT("@"),

		EVE_TXT("A"),
		EVE_TXT("B"),
		EVE_TXT("C"),
		EVE_TXT("D"),
		EVE_TXT("E"),
		EVE_TXT("F"),
		EVE_TXT("G"),
		EVE_TXT("H"),
		EVE_TXT("I"),
		EVE_TXT("J"),
		EVE_TXT("K"),
		EVE_TXT("L"),
		EVE_TXT("M"),
		EVE_TXT("N"),
		EVE_TXT("O"),
		EVE_TXT("P"),
		EVE_TXT("Q"),
		EVE_TXT("R"),
		EVE_TXT("S"),
		EVE_TXT("T"),
		EVE_TXT("U"),
		EVE_TXT("V"),
		EVE_TXT("W"),
		EVE_TXT("X"),
		EVE_TXT("Y"),
		EVE_TXT("Z"),

		EVE_TXT("Left bracket"),
		EVE_TXT("Backslash"),
		EVE_TXT("Right bracket"),
		EVE_TXT("Caret"),
		EVE_TXT("Underscore"),
		EVE_TXT("Backquote"),

		EVE_TXT("a"),
		EVE_TXT("b"),
		EVE_TXT("c"),
		EVE_TXT("d"),
		EVE_TXT("e"),          // 0x61 - 0x7e
		EVE_TXT("f"),
		EVE_TXT("g"),
		EVE_TXT("h"),
		EVE_TXT("i"),
		EVE_TXT("j"),
		EVE_TXT("k"),
		EVE_TXT("l"),
		EVE_TXT("m"),
		EVE_TXT("n"),
		EVE_TXT("o"),
		EVE_TXT("p"),
		EVE_TXT("q"),
		EVE_TXT("r"),
		EVE_TXT("s"),
		EVE_TXT("t"),
		EVE_TXT("u"),
		EVE_TXT("v"),
		EVE_TXT("w"),
		EVE_TXT("x"),
		EVE_TXT("y"),
		EVE_TXT("z"),

		EVE_TXT("Left acolade"),
		EVE_TXT("|"),
		EVE_TXT("right acolade"),
		EVE_TXT("tilde"),

		EVE_TXT("Delete"),                      

		// END OF ASCII

		0, 0, 0, 0, 0,          // 0x80 - 0x9f unused (total: 32)
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0,

		// International unicode characters 0xa0 - 0xff
		// Characters in utf-8          
		EVE_TXT("\xc2\xa0"),                     // NOBREAKSPACE
		EVE_TXT("\xc2\xa1"),                     // EXCLAMDOWN
		EVE_TXT("\xc2\xa2"),                     // CENT
		EVE_TXT("\xc2\xa3"),                     // STERLING
		EVE_TXT("\xc2\xa4"),                     // CURRENCY
		EVE_TXT("\xc2\xa5"),                     // YEN
		EVE_TXT("\xc2\xa6"),                     // BROKENBAR
		EVE_TXT("\xc2\xa7"),                     // SECTION
		EVE_TXT("\xc2\xa8"),                     // DIAERESIS
		EVE_TXT("\xc2\xa9"),                     // COPYRIGHT
		EVE_TXT("\xc2\xaa"),                     // ORDFEMININE
		EVE_TXT("\xc2\xab"),                     // GUILLEMOTLEFT
		EVE_TXT("\xc2\xac"),                     // NOTSIGN
		EVE_TXT("\xc2\xad"),                     // HYPHEN
		EVE_TXT("\xc2\xae"),                     // REGISTERED
		EVE_TXT("\xc2\xaf"),                     // MACRON
		EVE_TXT("\xc2\xb0"),                     // DEGREE
		EVE_TXT("\xc2\xb1"),                     // PLUSMINUS
		EVE_TXT("\xc2\xb2"),                     // TWOSUPERIOR
		EVE_TXT("\xc2\xb3"),                     // THREESUPERIOR
		EVE_TXT("\xc2\xb4"),                     // ACUTE
		EVE_TXT("\xc2\xb5"),                     // MU
		EVE_TXT("\xc2\xb6"),                     // PARAGRAPH
		EVE_TXT("\xc2\xb7"),                     // PERIODCENTERED
		EVE_TXT("\xc2\xb8"),                     // CEDILLA
		EVE_TXT("\xc2\xb9"),                     // ONESUPERIOR
		EVE_TXT("\xc2\xba"),                     // MASCULINE
		EVE_TXT("\xc2\xbb"),                     // GUILLEMOTRIGHT
		EVE_TXT("\xc2\xbc"),                     // ONEQUARTER
		EVE_TXT("\xc2\xbd"),                     // ONEHALF
		EVE_TXT("\xc2\xbe"),                     // THREEQUARTERS
		EVE_TXT("\xc2\xbf"),                     // QUESTIONDOWN
		EVE_TXT("\xc3\x80"),                     // AGRAVE
		EVE_TXT("\xc3\x81"),                     // AACUTE
		EVE_TXT("\xc3\x82"),                     // ACIRCUMFLEX
		EVE_TXT("\xc3\x83"),                     // ATILDE
		EVE_TXT("\xc3\x84"),                     // ADIAERESIS
		EVE_TXT("\xc3\x85"),                     // ARING
		EVE_TXT("\xc3\x86"),                     // AE
		EVE_TXT("\xc3\x87"),                     // CCEDILLA
		EVE_TXT("\xc3\x88"),                     // EGRAVE
		EVE_TXT("\xc3\x89"),                     // EACUTE
		EVE_TXT("\xc3\x8a"),                     // ECIRCUMFLEX
		EVE_TXT("\xc3\x8b"),                     // EDIAERESIS
		EVE_TXT("\xc3\x8c"),                     // IGRAVE
		EVE_TXT("\xc3\x8d"),                     // IACUTE
		EVE_TXT("\xc3\x8e"),                     // ICIRCUMFLEX
		EVE_TXT("\xc3\x8f"),                     // IDIAERESIS
		EVE_TXT("\xc3\x90"),                     // ETH
		EVE_TXT("\xc3\x91"),                     // NTILDE
		EVE_TXT("\xc3\x92"),                     // OGRAVE
		EVE_TXT("\xc3\x93"),                     // OACUTE
		EVE_TXT("\xc3\x94"),                     // OCIRCUMFLEX
		EVE_TXT("\xc3\x95"),                     // OTILDE
		EVE_TXT("\xc3\x96"),                     // ODIAERESIS
		EVE_TXT("\xc3\x97"),                     // MULTIPLY
		EVE_TXT("\xc3\x98"),                     // OSLASH
		EVE_TXT("\xc3\x99"),                     // UGRAVE
		EVE_TXT("\xc3\x9a"),                     // UACUTE
		EVE_TXT("\xc3\x9b"),                     // UCIRCUMFLEX
		EVE_TXT("\xc3\x9c"),                     // UDIAERESIS
		EVE_TXT("\xc3\x9d"),                     // YACUTE
		EVE_TXT("\xc3\x9e"),                     // THORN
		EVE_TXT("\xc3\x9f"),                     // SSHARP
		EVE_TXT("\xc3\xa0"),                     // aGRAVE
		EVE_TXT("\xc3\xa1"),                     // aACUTE
		EVE_TXT("\xc3\xa2"),                     // aCIRCUMFLEX
		EVE_TXT("\xc3\xa3"),                     // aTILDE
		EVE_TXT("\xc3\xa4"),                     // aDIAERESIS
		EVE_TXT("\xc3\xa5"),                     // aRING
		EVE_TXT("\xc3\xa6"),                     // ae
		EVE_TXT("\xc3\xa7"),                     // cCEDILLA
		EVE_TXT("\xc3\xa8"),                     // eGRAVE
		EVE_TXT("\xc3\xa9"),                     // eACUTE
		EVE_TXT("\xc3\xaa"),                     // eCIRCUMFLEX
		EVE_TXT("\xc3\xab"),                     // eDIAERESIS
		EVE_TXT("\xc3\xac"),                     // iGRAVE
		EVE_TXT("\xc3\xad"),                     // iACUTE
		EVE_TXT("\xc3\xae"),                     // iCIRCUMFLEX
		EVE_TXT("\xc3\xaf"),                     // iDIAERESIS
		EVE_TXT("\xc3\xb0"),                     // eth
		EVE_TXT("\xc3\xb1"),                     // nTILDE
		EVE_TXT("\xc3\xb2"),                     // oGRAVE
		EVE_TXT("\xc3\xb3"),                     // oACUTE
		EVE_TXT("\xc3\xb4"),                     // oCIRCUMFLEX
		EVE_TXT("\xc3\xb5"),                     // oTILDE
		EVE_TXT("\xc3\xb6"),                     // oDIAERESIS
		EVE_TXT("\xc3\xb7"),                     // DIVISION
		EVE_TXT("\xc3\xb8"),                     // oSLASH
		EVE_TXT("\xc3\xb9"),                     // uGRAVE
		EVE_TXT("\xc3\xba"),                     // uACUTE
		EVE_TXT("\xc3\xbb"),                     // uCIRCUMFLEX
		EVE_TXT("\xc3\xbc"),                     // uDIAERESIS
		EVE_TXT("\xc3\xbd"),                     // yACUTE
		EVE_TXT("\xc3\xbe"),                     // thorn
		EVE_TXT("\xc3\xbf"),                     // yDIAERESIS

		EVE_TXT("Keypad 0"),
		EVE_TXT("Keypad 1"),
		EVE_TXT("Keypad 2"),
		EVE_TXT("Keypad 3"),
		EVE_TXT("Keypad 4"),
		EVE_TXT("Keypad 5"),
		EVE_TXT("Keypad 6"),
		EVE_TXT("Keypad 7"),
		EVE_TXT("Keypad 8"),
		EVE_TXT("Keypad 9"),
		EVE_TXT("Keypad separator"),
		EVE_TXT("Keypad divide"),
		EVE_TXT("Keypad multiply"),
		EVE_TXT("Keypad plus"),
		EVE_TXT("Keypad minus"),
		EVE_TXT("Keypad enter"),

		EVE_TXT("Up"),
		EVE_TXT("Down"),
		EVE_TXT("Left"),
		EVE_TXT("Right"),
		EVE_TXT("Insert"),
		EVE_TXT("Home"),
		EVE_TXT("End"),
		EVE_TXT("Page Up"),
		EVE_TXT("Page Down"),

		EVE_TXT("F1"),
		EVE_TXT("F2"),
		EVE_TXT("F3"),
		EVE_TXT("F4"),
		EVE_TXT("F5"),
		EVE_TXT("F6"),
		EVE_TXT("F7"),
		EVE_TXT("F8"),
		EVE_TXT("F9"),
		EVE_TXT("F10"),
		EVE_TXT("F11"),
		EVE_TXT("F12"),
		EVE_TXT("F13"),
		EVE_TXT("F14"),
		EVE_TXT("F15"),
		EVE_TXT("F16"),
		EVE_TXT("F17"),
		EVE_TXT("F18"),
		EVE_TXT("F19"),
		EVE_TXT("F20"),
		EVE_TXT("F21"),
		EVE_TXT("F22"),
		EVE_TXT("F23"),
		EVE_TXT("F24"),

		EVE_TXT("Num Lock"),             
		EVE_TXT("Caps Lock"),            
		EVE_TXT("Scroll Lock"),          
		EVE_TXT("Left shift"),           
		EVE_TXT("Right shift"),          
		EVE_TXT("Left CTRL"),            
		EVE_TXT("Right CTRL"),           
		EVE_TXT("Left ALT"),             
		EVE_TXT("Right ALT"),            
		EVE_TXT("Left Super"),           
		EVE_TXT("Right Super"),          

		EVE_TXT("Alt Gr"),                       
		EVE_TXT("Compose"),                      
		EVE_TXT("Menu"),                         

		EVE_TXT("System request"),       
		EVE_TXT("Pause"),                
		EVE_TXT("Print screen"),         

		EVE_TXT("Dead grave"),           
		EVE_TXT("Dead acute"),           
		EVE_TXT("Dead circumflex"),      
		EVE_TXT("Dead tilde"),           
		EVE_TXT("Dead macron"),          
		EVE_TXT("Dead breve"),           
		EVE_TXT("Dead abovedot"),        
		EVE_TXT("Dead diaeresis"),       
		EVE_TXT("Dead abovering"),       

		0 // terminator
	};

	const wchar_t * get_key_name(eve::sys::Key p_key)
	{
		if (p_key < eve::sys::key_Num_Keys && symbol_names[p_key] != 0) return symbol_names[p_key];
		return EVE_TXT("");
	}



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

		if (itr == map.end()) return eve::sys::key_Unknown;
		
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
			return eve::sys::key_Unknown;
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
				return eve::sys::key_Unknown; // next message is RALT down
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
		return eve::sys::key_Unknown;
	}


	eve::sys::Key key = mapVirtualKeyCode(p_wParam);
	if (!key)
	{
		p_bFilter = true;
		return eve::sys::key_Unknown;
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
bool eve::sys::get_async_key_state_ctrl(void)	{ return ((::GetAsyncKeyState(VK_CONTROL) & 0x8000)	!= 0); }
bool eve::sys::get_async_key_state_alt(void)	{ return ((::GetAsyncKeyState(VK_MENU) & 0x8000)	!= 0); }
bool eve::sys::get_async_key_state_shift(void)	{ return ((::GetAsyncKeyState(VK_SHIFT) & 0x8000)	!= 0); }

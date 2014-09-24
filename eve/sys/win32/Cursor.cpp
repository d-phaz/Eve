
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
#include "eve/sys/win32/Cursor.h"

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif


/** \brief Set the cursor and change it for target window class. */
#define MAP_CURSOR(a, b, c) \
    case a: \
	::SetCursor((HCURSOR)::LoadImageW(NULL, b, IMAGE_CURSOR, 0, 0, LR_SHARED));  \
	::SetClassLongPtrW(c, GCLP_HCURSOR, (LONG)(LONG_PTR)::LoadImageW(NULL, b, IMAGE_CURSOR, 0, 0, LR_SHARED)); \
	break;


//=============================================================================================
void eve::sys::set_cursor(eve::sys::Cursor p_cursorType)
{
	// Grab current window
	POINT point;
	::GetCursorPos(&point);
	HWND handle = ::WindowFromPoint(point);

	switch (p_cursorType)
	{
		MAP_CURSOR(cursor_None,				 NULL,			handle);
		MAP_CURSOR(cursor_Inherit,			 IDC_CROSS,		handle);
		MAP_CURSOR(cursor_Arrow,			 IDC_ARROW,		handle);
		MAP_CURSOR(cursor_Info,				 IDC_HELP,		handle);
		MAP_CURSOR(cursor_Wait,				 IDC_WAIT,		handle);
		MAP_CURSOR(cursor_Cross,			 IDC_CROSS,		handle);
		MAP_CURSOR(cursor_Text,				 IDC_IBEAM,		handle);
		MAP_CURSOR(cursor_UpDown,			 IDC_SIZENS,	handle);
		MAP_CURSOR(cursor_LeftRight,		 IDC_SIZEWE,	handle);
		MAP_CURSOR(cursor_CornerTopLeft,	 IDC_SIZENWSE,	handle);
		MAP_CURSOR(cursor_CornerTopRight,	 IDC_SIZENESW,	handle);
		MAP_CURSOR(cursor_CornerBottomLeft,  IDC_SIZENWSE,	handle);
		MAP_CURSOR(cursor_CornerBottomRight, IDC_SIZENESW,	handle);
		MAP_CURSOR(cursor_Cycle,			 IDC_SIZEALL,	handle);

	default:
		break;
	}
}
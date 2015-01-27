
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
#ifndef __EVE_SYSTEM_CURSOR_H__
#define __EVE_SYSTEM_CURSOR_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MATH_INCLUDES_H__
#include "eve/math/Includes.h"
#endif


namespace eve
{
	namespace sys
	{
		/** \brief Cursor type enumeration. */
		enum Cursor
		{
			cursor_Unused,
			cursor_None ,
			cursor_Inherit,
			cursor_Arrow,
			cursor_Info,
			cursor_Wait,
			cursor_Cross,
			cursor_Text,
			cursor_UpDown,
			cursor_LeftRight,
			cursor_CornerTopLeft,
			cursor_CornerTopRight,
			cursor_CornerBottomLeft,
			cursor_CornerBottomRight,
			cursor_Cycle
		};

		/** \brief Set cursor. Cursor is applied to window at mouse position. */
		void set_cursor(eve::sys::Cursor p_cursorType);


		/** \brief Get cursor position in screen coordinates. */
		void get_cursor_position(int32_t * p_x, int32_t * p_y);
		/** \brief Get cursor position in screen coordinates. */
		eve::vec2i get_cursor_position(void);

		/** \brief Set cursor position. */
		void setCursorPosition(int32_t p_x, int32_t p_y);
		/** \brief Set cursor position. */
		void setCursorPosition(const eve::vec2i & p_position);

	} // namespace sys

} // namespace eve

#endif // __EVE_SYSTEM_CURSOR_H__

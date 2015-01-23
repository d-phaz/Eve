
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
#include "eve/sys/win32/WindowRoot.h"

#ifndef __EVE_THREADING_INCLUDES_H__
#include "eve/thr/Includes.h"
#endif


//=================================================================================================
eve::sys::WindowRoot * eve::sys::WindowRoot::create_ptr(int32_t p_x
													  , int32_t p_y
													  , uint32_t p_width
													  , uint32_t p_height
													  , eve::sys::WindowType p_type)
{
	eve::sys::WindowRoot * ptr = new eve::sys::WindowRoot(p_x, p_y, p_width, p_height, p_type);
	ptr->init();
	return ptr;
}

//=================================================================================================
eve::sys::WindowRoot * eve::sys::WindowRoot::create_ptr_scaled_on_main_work_area(eve::sys::WindowType p_type)
{
	uint32_t border		= eve::sys::Window::get_border_thickness();
	uint32_t titleBar	= eve::sys::Window::get_title_bar_height();
	uint32_t width		= eve::sys::get_work_area_width() - (border * 2);
	uint32_t height		= eve::sys::get_work_area_height() - (titleBar + (border * 2));
	return eve::sys::WindowRoot::create_ptr(border, titleBar + border, width, height, p_type);
}



//=================================================================================================
eve::sys::WindowRoot::WindowRoot(int32_t p_x
							   , int32_t p_y
							   , uint32_t p_width
							   , uint32_t p_height
							   , eve::sys::WindowType p_type)
	// Inheritance
	: eve::sys::Window(p_x, p_y, p_width, p_height, p_type)
{}



//=================================================================================================
void eve::sys::WindowRoot::init(void)
{
	// Call parent class.
	eve::sys::Window::init();
}

//=================================================================================================
void eve::sys::WindowRoot::release(void)
{
	// Call parent class.
	eve::sys::Window::release();
}

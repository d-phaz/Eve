
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
#include "eve/sys/win32/WindowChild.h"

#ifndef __EVE_THREADING_INCLUDES_H__
#include "eve/thr/Includes.h"
#endif


//=================================================================================================
eve::sys::WindowChild * eve::sys::WindowChild::create_ptr(int32_t p_x, int32_t p_y, uint32_t p_width, uint32_t p_height, HWND p_parent)
{
	eve::sys::WindowChild * ptr = new eve::sys::WindowChild(p_x, p_y, p_width, p_height, p_parent);
	ptr->init();
	return ptr;
}

//=================================================================================================
eve::sys::WindowChild::WindowChild(int32_t p_x, int32_t p_y, uint32_t p_width, uint32_t p_height, HWND p_parent)
	// Inheritance
	: eve::sys::Window(p_x, p_y, p_width, p_height, eve::sys::WindowType_Child, p_parent)
{}



//=================================================================================================
void eve::sys::WindowChild::init(void)
{
	// Call parent class.
	eve::sys::Window::init();
}

//=================================================================================================
void eve::sys::WindowChild::release(void)
{
	// Call parent class.
	eve::sys::Window::release();
}

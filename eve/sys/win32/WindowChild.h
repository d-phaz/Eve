
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
#ifndef __EVE_SYSTEM_WINDOW_CHILD_H__
#define __EVE_SYSTEM_WINDOW_CHILD_H__

#ifndef __EVE_SYSTEM_WINDOW_H__
#include "eve/sys/win32/Window.h"
#endif


namespace eve
{
	namespace sys
	{
		/** 
		* \class eve::sys::WindowChild
		*
		* \brief Creates and manage system child window.
		* Child window is linked to its parent by the HWND.
		*
		* \note extends eve::sys::Window
		*/
		class WindowChild final
			: public eve::sys::Window
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(WindowChild);
			EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(WindowChild);

		public:
			/**
			* \brief Create and return new pointer.
			* \param p_x is the Window position on X-axis.
			* \param p_y is the Window position on Y-axis.
			* \param p_width is the Window width.
			* \param p_height is the Window height.
			* \param p_parent parent window handle.
			*/
			static eve::sys::WindowChild * create_ptr(int32_t p_x, int32_t p_y, uint32_t p_width, uint32_t p_height, HWND p_parent);


		private:
			/** 
			* \brief Class constructor.
			* \param p_x is the Window position on X-axis.
			* \param p_y is the Window position on Y-axis.
			* \param p_width is the Window width.
			* \param p_height is the Window height.
			* \param p_parent parent window handle.
			*/
			explicit WindowChild(int32_t p_x, int32_t p_y, uint32_t p_width, uint32_t p_height, HWND p_parent);


		private:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;

		}; // class WindowChild

	} // namespace sys

} // namespace eve

#endif // __EVE_SYSTEM_WINDOW_CHILD_H__

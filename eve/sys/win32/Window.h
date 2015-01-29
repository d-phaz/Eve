
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
#ifndef __EVE_SYSTEM_WINDOW_H__
#define __EVE_SYSTEM_WINDOW_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif

#ifndef __EVE_SYSTEM_DISPLAY_H__
#include "eve/sys/win32/Display.h"
#endif


namespace eve{ namespace thr{ class SpinLock;  } }


namespace eve
{
	namespace sys
	{
		/** 
		* \enum eve::sys::WindowType
		* \brief enumerate supported window types.
		*/
		enum WindowType
		{
			WindowType_Unknown = 0,

			WindowType_App,
			WindowType_Child,
			WindowType_Output,

			//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
			_WindowType_Force32Bit = INT_MAX

		}; // enum WindowType


		/** 
		* \class eve::sys::Window
		*
		* \brief Creates and manage system window.
		* Message pump events are linked to window handle (aka HWND),
		* event translation and dispatch is done here.
		*
		* \note extends eve::mem::Pointer
		*/
		class Window
			: public eve::mem::Pointer
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			int32_t							m_x;					//!< Window position on X-axis.
			int32_t							m_y;					//!< Window position on Y-axis.
			uint32_t						m_width;				//!< Window width, should never be negative.
			uint32_t						m_height;				//!< Window height, should never be negative.
			eve::sys::WindowType			m_type;					//!< Specifies window type used to create window style.
			HWND							m_parent;				//!< Specifies parent window handle.
			std::wstring					m_title;				//!< Window title.

			HWND							m_handle;				//!< System window handle.
			ATOM							m_atom;					//!< System window atom.
			HINSTANCE						m_hinstance;			//!< System window instance handle.

			RECT							m_windowedRect;			//!< Window rect when not in full screen mode.
			bool							m_bFullScreen;			//!< Window scaled on output state (full screen).
			LONG							m_style;				//!< Window system style.
			LONG							m_exStyle;				//!< Window system extended style.
			static LONG						m_style_fullscreen;		//!< Window system style when full screen is enabled.
			static LONG						m_ex_style_fullscreen;	//!< Window system extended style when full screen is enabled.

			eve::thr::SpinLock *			m_pFence;				//!< Window style change protection fence as spin lock.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Window);
			EVE_PUBLIC_DESTRUCTOR(Window);

		public:
			/**
			* \brief Create and return new pointer.
			* \param p_x is the Window position on X-axis.
			* \param p_y is the Window position on Y-axis.
			* \param p_width is the Window width.
			* \param p_height is the Window height.
			* \param p_parent parent window handle.
			*/
			static eve::sys::Window * create_ptr(int32_t p_x
											   , int32_t p_y
											   , uint32_t p_width
											   , uint32_t p_height
											   , eve::sys::WindowType p_type
											   , HWND p_parent = nullptr);


		public:
			/** 
			* \brief Class constructor. 
			* \param p_x is the Window position on X-axis.
			* \param p_y is the Window position on Y-axis.
			* \param p_width is the Window width.
			* \param p_height is the Window height.
			* \param p_type window type, used to create window style.
			* \param p_parent parent window handle.
			*/
			explicit Window(int32_t p_x
						  , int32_t p_y
						  , uint32_t p_width
						  , uint32_t p_height
						  , eve::sys::WindowType p_type
						  , HWND p_parent = nullptr);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;

			
		public:			
			/** \brief Show window.	*/
			void show(void);			
			/** \brief Hide window. */
			void hide(void);
			
			/** \brief Minimize window. */
			void minimize(void);			
			/** \brief Restore window size and position (before minimize values). */
			void restore(void);
			
			/** \brief Minimizes (but does not destroy) window. */
			void close(void);
			
			/** \brief Push window, set the window at display bottom. */
			void push(void);			
			/** \brief Pop window, set the window at display top. */
			void pop(void);


			/**
			* \brief Scale the size of the window on output size and align it on top left corner if windowed.
			* Set window back to before full screen size and position.
			* \note Change window style.
			*/
			void toggleFullScreen(void);
			
				
			/**
			* \brief Move the mouse pointer inside this window.
			* The coordinates are relative to the window client area. If the
			* given coordinates are outside the client area, no change is performed.
			* 
			* \param p_deportX horizontal deport inside window (window zero is top/left)
			* \param p_deportY vertical deport inside window (window zero is top/left)
			*/
			void warpMouse(int32_t p_deportX, int32_t p_deportY);
			
				
			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get system window handle. */
			const HWND getHandle(void) const;

				
		public:
			/** \brief Registers whether window accepts dropped files. */
			void setDragAcceptFiles(bool p_bStatus);


			/** \brief Set window active. */
			void setActive(void);

			/** \brief Set window foreground. */
			void setForeground(void);

			
			/** \brief Get window size. */
			void getSize(uint32_t & p_width, uint32_t & p_height);
			/** \brief Get window width. */
			const uint32_t getWidth(void);
			/** \brief Get window height. */
			const uint32_t getHeight(void);
			
			/** \brief Resize window to desired \p_width and \p_height. */
			void setSize(uint32_t p_width, uint32_t p_height);
			/** \brief Set window width. */
			void setWidth(uint32_t p_width);
			/** \brief Set window height. */
			void setHeight(uint32_t p_height);
			
			
			/** \brief Get window position. */
			void getPosition(int32_t & p_x, int32_t & p_y);
			/** \brief Get window position on X-axis. */
			const int32_t getPositionX(void);
			/** \brief Get window position on Y-axis. */
			const int32_t getPositionY(void);			
				
			/** \brief Set window position. */
			void setPosition(int32_t p_x, int32_t p_y);
			/** \brief Set window position on X-axis. */
			void setPositionX(int32_t p_x);
			/** \brief Set window position on Y-axis. */
			void setPositionY( int32_t p_y );
			
				
			/** \brief Set window title (UTF-8). */
			void setTitle( const std::wstring & p_title );


		public:
			/** \brief Get title bar height. */
			static uint32_t get_title_bar_height(void);

			/** \brief get window border thickness. */
			static uint32_t get_border_thickness(void);

		}; // class Window

	} // namespace sys

} // namespace eve

//=================================================================================================
inline const HWND eve::sys::Window::getHandle(void) const		{ return m_handle; }

#endif // __EVE_SYSTEM_WINDOW_H__

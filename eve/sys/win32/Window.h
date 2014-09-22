
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


namespace eve{ namespace thr{ class SpinLock;  } }


namespace eve
{
	namespace sys
	{
		/** 
		* \class eve::sys::Window
		* \brief Creates and manage system window.
		* \note extends eve::mem::Pointer
		*/
		class Window final
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:
			int32_t					m_x;					//!< Window position on X-axis.
			int32_t					m_y;					//!< Window position on Y-axis.
			uint32_t				m_width;				//!< Window width, should never be negative.
			uint32_t				m_height;				//!< Window height, should never be negative.
			char *					m_title;				//!< Window title as char pointer.

			HWND					m_handle;				//!< System window handle.
			ATOM					m_atom;					//!< System window atom.
			HINSTANCE				m_hinstance;			//!< System window instance handle.

			RECT					m_windowedRect;			//!< Window rect when not in full screen mode.
			bool					m_bScaledOnOutput;		//!< Window scaled on output state (full screen).
			LONG					m_style;				//!< Window system style.
			LONG					m_exStyle;				//!< Window system extended style.
			static LONG				m_styleFullscreen;		//!< Window system style when full screen is enabled.
			static LONG				m_exStyleFullscreen;	//!< Window system extended style when full screen is enabled.

			eve::thr::SpinLock *	m_pFence;				//!< Window style change protection fence as spin lock.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Window);
			EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(Window);

		public:
			/**
			* \brief Create and return new pointer.
			* \param p_x is the Window position on X-axis.
			* \param p_y is the Window position on Y-axis.
			* \param p_width is the Window width.
			* \param p_height is the Window height.
			*/
			static Window * create_ptr(int32_t p_x, int32_t p_y, uint32_t p_width, uint32_t p_height);


		protected:
			/** 
			* \brief Class constructor. 
			* \param p_x is the Window position on X-axis.
			* \param p_y is the Window position on Y-axis.
			* \param p_width is the Window width.
			* \param p_height is the Window height.
			*/
			Window(int32_t p_x, int32_t p_y, uint32_t p_width, uint32_t p_height);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		}; // class Window


	} // namespace sys


} // namespace eve

#endif // __EVE_SYSTEM_WINDOW_H__




//
/////////////////////////////////////////////////////////////////////////////////////////////////////
////		SystemWindow class
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
///**
//* @class SystemWindow
//* @brief Windows system window 
//*/
//class SystemWindow
//{
//
//	//////////////////////////////////////
//	//									//
//	//			  UTILITIES				//
//	//									//
//	//////////////////////////////////////
//
//private:
//	typedef struct struct_BeforeScaleCoordinates
//	{
//		uint32_t x;
//		uint32_t y;
//		uint32_t width;
//		uint32_t height;
//	} Struct_BeforeScaleCoordinates;
//
//	Struct_BeforeScaleCoordinates m_beforeScaleCoordinates;
//
//
//	//////////////////////////////////////
//	//									//
//	//				DATAS				//
//	//									//
//	//////////////////////////////////////
//
//public:
//	int32_t					m_NodalId;
//	SystemNode *			m_pNodeParent;
//
//	int32_t					m_X;
//	int32_t					m_Y;
//	uint32_t				m_Width;
//	uint32_t				m_Height;
//	uint32_t				m_minWidth;
//	uint32_t				m_minHeight;
//	uint32_t				m_maxWidth;
//	uint32_t				m_maxHeight;
//	std::string				m_title;
//
//	HWND					m_Hwnd;
//	ATOM					m_Atom;
//	HINSTANCE				m_Hinstance;
//
//	RECT					m_WindowedRect;
//	bool					m_bsetScaledOnOutput;
//	bool					m_bScaledOnOutput;
//	LONG					m_Style;
//	LONG					m_ExStyle;
//	LONG					m_StyleFullscreen;
//	LONG					m_ExStyleFullscreen;
//
//	static NativeT::Lock	m_paccess_lock;
//	char *					m_titleChar;
//
//
//
//	//////////////////////////////////////
//	//									//
//	//				METHOD				//
//	//									//
//	//////////////////////////////////////
//
//	NATIVE_DISABLE_COPY(SystemWindow);
//
//protected:
//	/**
//	* @brief SystemWindow class constructor
//	*
//	* @param p_nodalId window node id
//	* @param p_pNodeParent parent system node as SystemNode pointer
//	* @param p_x window position on X-axis as int32_t
//	* @param p_y window position on Y-axis as int32_t
//	* @param p_width widow width as uint32_t
//	* @param p_height window height as uint32_t
//	* @param p_bsetScaledOnOutput is window scaled on monitor (default to false)
//	*/
//	SystemWindow
//		(	
//		int32_t p_nodalId, 
//		SystemNode * p_pNodeParent, 
//		int32_t p_x, 
//		int32_t p_y, 
//		uint32_t p_width, 
//		uint32_t p_height, 
//		bool p_bsetScaledOnOutput=false
//		);
//
//
//public:
//	/** Create and return new SystemWindow pointer. */
//	static SystemWindow * create_ptr
//		(	
//		int32_t p_nodalId, 
//		SystemNode * p_pNodeParent, 
//		int32_t p_x, 
//		int32_t p_y, 
//		uint32_t p_width, 
//		uint32_t p_height, 
//		bool p_bsetScaledOnOutput=false
//		);
//
//
//	/**
//	* @brief SystemWindow class destructor
//	*/
//	virtual ~SystemWindow( void );
//
//
//	/**
//	* @brief initialisation function
//	* @note virtual function
//	*/
//	virtual void init( void ); 
//
//	
//	///////////////////////////////////////////////////////////////////////////////////////////////
//	//		UTILITIES
//	///////////////////////////////////////////////////////////////////////////////////////////////
//
//	/**
//	* @brief updates max width and height values
//	*/
//	void updateMaxSize( void );
//
//	/** 
//	* @brief set window active
//	*/
//	void setActive( void );
//
//	/**  
//	* @brief set foreground
//	*/
//	void setForeground(void);
//
//	/** 
//	* @brief show window
//	*/
//	void show( void );
//
//	/** 
//	* @brief hide window
//	*/
//	void hide( void );
//
//	/**
//	* @brief minimize window
//	*/
//	void minimize( void );
//
//	/**
//	* @brief restore window to its size and position after it was menimized
//	*/
//	void restore( void );
//
//	/**
//	* @brief close window
//	*/
//	void close( void );
//
//	/**
//	* @brief push window, set the window in bottom of display
//	*/
//	void push( void );
//
//	/**
//	* @brief pop window, set the window on top of display
//	*/
//	void pop( void );
// 
//	/**
//	* @brief scale the size of the window on output size and align it on top left corner
//	* @note this doesn't affect window style
//	*/
//	void scaleOnOutput( void );
//
//	/**
//	* @brief align window on top left corner
//	* @note this doesn't affect window style
//	*/
//	void fixOnOutput( void );
//
//	/**
//	* @brief resize window to desired width and height
//	* @param p_width the new width of the window
//	* @param p_height the new height of the window
//	*/
//	void resize( uint32_t p_width, uint32_t p_height);
//
//	
//	/**
//	* @brief move the mouse pointer inside this window
//	*
//	* @note The coordinates are relative to the window client area. If the
//	* given coordinates are outside the client area, no moving is
//	* performed.
//	* 
//	* @param p_deportX horizontal deport inside window (window zero is top/left)
//	* @param p_deportY vertical deport inside window (window zero is top/left)
//	*/
//	void warpMouse( int32_t p_deportX, int32_t p_deportY );
//
//
//	/**
//	* @brief equest window repaint,
//	*
//	* Ask the windowing system to be repainted. The windowing
//	* system will respond and an ExposeEvent will be generated
//	* when appropriate.
//	* 
//	* If the width or the height of the dirty rectangle
//	* area is zero, the entire window be repainted.
//	* 
//	* @param p_x the left side of the dirty rectangle (default to zero)
//	* @param p_y the top side of the dirty rectangle (default to zero)
//	* @param p_width the width of the dirty rectangle (default to zero)
//	* @param p_height the height of the dirty rectangle (default to zero)
//	* @see mwm_window::ExposeEvent
//	*/
//	void repaint( uint32_t p_x=0, uint32_t p_y=0, uint32_t p_width=0, uint32_t p_height=0 );
//
//	
//	///////////////////////////////////////////////////////////////////////////////////////////////
//	//		GET / SET
//	///////////////////////////////////////////////////////////////////////////////////////////////
//
//	/**
//	* @brief get the size of the window
//	* @param p_width the width of the window gets written here
//	* @param p_height the height of the window gets written here
//	*/
//	void getSize( uint32_t & p_width, uint32_t & p_height );
//	/**
//	* @brief get window width
//	* @return width as uint32_t
//	*/
//	const uint32_t getWidth( void );
//	/**
//	* @brief get window height
//	* @return height as uint32_t
//	*/
//	const uint32_t getHeight( void );
//
// 
//	/**
//	* @brief set the width of the window
//	* @param p_width the new width of the window
//	*/
//	void setWidth( const uint32_t & p_width );
//	/**
//	* @brief set the height of the window
//	* @param p_height the new height of the window
//	*/
//	void setHeight( const uint32_t & p_height );
//
//	
//	/**
//	* @brief get the position of the window on X-axis
//	* @return window position on X-axis as int32_t
//	*/
//	int32_t getPositionX( void );
//	/**
//	* @brief get the y position of the window on Y-axis 
//	* @return window position on Y-axis as int32_t
//	*/
//	int32_t getPositionY( void );
//
//	
//	/**
//	* @brief set the position of the window
//	* @param p_x the new position of the window on X-axis
//	* @param p_y the new position of the window on Y-axis
//	*/
//	void setPosition( const int32_t & p_x, const int32_t & p_y );
//	/**
//	* @brief set window position on X-axis
//	* @param p_x the new position of the window on X-axis
//	*/
//	void setPositionX( const int32_t & p_x );
//	/**
//	* @brief set window position on Y-axis
//	* @param p_y the new position of the window on X-axis
//	*/
//	void setPositionY( const int32_t & p_y );
//
//	
//	/** \! Convert client coordinates to screen coordinates. */
//	Vec2i clientToScreen( const uint32_t & p_x, const uint32_t & p_y );
//
//	
//	/**
//	* @brief set the title of the window (UTF-8)
//	* @param p_title the new title of the window, encoded in UTF-8
//	*/
//	void setTitle( const std::string & p_title );
//
//	
//	/**
//	* @brief set the window draggable status
//	* @param p_bStatus true if window accepts the dragged files
//	*/
//	void setDragAcceptFiles( const bool & p_bStatus );
//};

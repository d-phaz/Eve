
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
#ifndef __EVE_SYSTEM_NODE_H__
#define __EVE_SYSTEM_NODE_H__

#ifndef __EVE_THREADING_THREAD_H__
#include "eve/thr/Thread.h"
#endif 

namespace eve
{
	namespace sys
	{

	} // namespace sys

} // namespace eve


#endif // __EVE_SYSTEM_NODE_H__



// External header
#include <string>

// Native types
#ifndef __NATIVE_TYPES_H__
#include "Native_types.h"
#endif

// Thread header
#ifndef __NATIVE_THREAD_H__
#include "Native_Thread.h"
#endif

// System header
#ifndef __SYSTEM_CURSOR_H__
#include "system/shared/SystemCursor.h"
#endif

// Math header
#ifndef __TVECTOR_H__
#include "math/TVector.h"
#endif



class SystemContext;
class SystemWindow;

class SystemNodeControl;

class SystemEventListener;
class SystemEventHandler;
class SystemEventReader;



/**
* @class SystemNode 
*
* @brief base system node class
*
* @note extends NativeT::Thread class
* @note 1 node = 1 thread
*/
class SystemNode 
	: public NativeT::Thread
{

	//////////////////////////////////////
	//			FRIEND CLASS			//
	//////////////////////////////////////

	friend class SystemWindow;
	friend class SystemContext;
	friend class SystemEventHandler;



	//////////////////////////////////////
	//				DATAS				//
	//////////////////////////////////////

protected:
	SystemWindow *					m_pSystemWindow;
	SystemContext *					m_pContext;
	SystemEventHandler *			m_pEventHandler;
	SystemEventReader *				m_pEventReader;
	SystemEventListener *			m_pEventListener;

	uint32_t						m_windowWidth;
	uint32_t						m_windowHeight;

	int32_t							m_X;
	int32_t							m_Y;
    
    SystemNode *                    m_pNodeMaster;


	
	//////////////////////////////////////
	//				METHOD				//
	//////////////////////////////////////

	NATIVE_DISABLE_COPY(SystemNode)


protected:
	/**
	* @brief SystemNode class constructor
	* 
	* @param p_x node window position on X-axis as uint32_t 
	* @param p_y node window position on Y-axis as uint32_t
	* @param p_windowWidth node window width as uint32_t
	* @param p_windowHeight node window height as uint32_t
    * @param p_pNodeMaster parent node as SystemNode pointer (default to NULL)
	*/
	SystemNode
		( 
		int32_t p_x, 
		int32_t p_y, 
		uint32_t p_windowWidth, 
		uint32_t p_windowHeight,
        SystemNode * p_pNodeMaster=NULL
		);


	/**
	* @brief SystemNode class destructor
	*/
	virtual ~SystemNode( void );


public:
	/** \! Create, init and return new SystemView pointer immediately, do not start thread. 
	* Example :
	*	SystemNode * ptr = SystemNode::create_ptr_wait();*/
	static SystemNode * create_ptr
		( 
		int32_t p_x, 
		int32_t p_y, 
		uint32_t p_windowWidth, 
		uint32_t p_windowHeight,
		SystemNode * p_pNodeMaster=NULL
		);

	/** \! Create, init and return new SystemView pointer once its thread is started. 
	* Example :
	*	SystemNode * ptr = SystemNode::create_ptr_wait();*/
	static SystemNode * create_ptr_wait
		( 
		int32_t p_x, 
		int32_t p_y, 
		uint32_t p_windowWidth, 
		uint32_t p_windowHeight,
		SystemNode * p_pNodeMaster=NULL
		);

	/** \! Release and delete pointer class members once its thread is stopped. 
	* Example :
	*	SystemView::release_ptr_wait( ptr );
	*/
	static void release_ptr_wait( SystemNode * pPtr );


	/**
    * @brief initialization function
    * @note virtual function
    */
    virtual void init( void );
	/**
	* @brief release function
	* @note virtual function
	*/
	virtual void release( void );


	/** Thread run. */
	virtual void Run( void );


	/** Thread stop
	* Stops the thread immediately by sending WM_QUIT message
	*/
	void Stop( void );


	///////////////////////////////////////////////////////////////////////////////////////////////
	//		WINDOW UTILITIES
	///////////////////////////////////////////////////////////////////////////////////////////////

	/** \! Convert client coordinates to screen coordinates. */
	Vec2i clientToScreen( const uint32_t & p_x, const uint32_t & p_y );


	/** Show system window. */
	void windowShow( void );

	/** Hide system window. */
	void windowHide( void );


	/** Set system window foreground. */
	void setWindowForeground( void );


	/**
	* @brief scale the size of the system window on output size and align it on top left corner
	* @note this doesn't affect window style
	*/
	void scaleWindowOnOutput( void );
	/**
     * @brief scale system window on it's actual display 
     * (only control window will use this so we only set the window position, not the size)
     */
    void scaleWindowOnDisplay( void );
    
    
    /**
     * @brief minimize system window
     */
    void minimizeWindow( void );


	/**
	* @brief get the system window position on X-axis
	* @return window position on X-axis as uint32_t
	*/
	const uint32_t getWindowPositionX( void ) const;
	/**
	* @brief get the system window position on Y-axis 
	* @return window position on Y-axis as uint32_t
	*/
	const uint32_t getWindowPositionY( void ) const;
	/**
	* @brief set system window position
	* @param p_x position on X-axis as int
	* @param p_y position on Y-axis as int
	*/
	void setWindowPosition( const int & p_x, const int & p_y );
	/**
	* @brief set system window position on X-axis
	* @param p_x position on X-axis as int
	*/
	void setWindowPositionX( const int & p_x );
	/**
	* @brief set system window position on Y-axis
	* @param p_y position on Y-axis as int
	*/
	void setWindowPositionY( const int & p_y );


	/**
	* @brief get system window width
	* @return width as uint32_t
	*/
	const uint32_t getWindowWidth( void ) const;
	/**
	* @brief get system window height
	* @return height as uint32_t
	*/
	const uint32_t geWindowHeight( void ) const;


	/**
	* @brief set system window width
	* @param p_width the new width of the window
	*/
	void setWindowWidth( const uint32_t & p_width );
	/**
	* @brief set system window height
	* @param p_height the new height of the window
	*/
	void setWindowHeight( const uint32_t & p_height );
	/**
	* @brief set system window size
	* @param p_width the new width of the window
	* @param p_height the new height of the window
	*/
	void setWindowSize( const uint32_t & p_width, const uint32_t & p_height );


	/**
	* @brief set system window title (UTF-8)
	* @param p_title the new title of the window, encoded in UTF-8
	*/
	void setWindowTitle( const std::string & p_title );


	/**
	* @brief set system window draggable status
	* @param p_bStatus true if window accepts the dragged files
	*/
	void setWindowDragAcceptFiles( const bool & p_bStatus );

	/**
	* @brief set window cursor
	* @param p_pNode target window system node as SystemNode pointer
	* @param p_cursorType cursor type as system::cursor::State enum
	* @note static function
	*/
	static void setWindowCursor( SystemNode * p_pNode, const cursor::State & p_cursorType );


	///////////////////////////////////////////////////////////////////////////////////////////////
	//		CONTEXT UTILITIES
	///////////////////////////////////////////////////////////////////////////////////////////////

	/**
	* @brief make context current
	* @return true on success, false otherwise
	*/
	bool contextMakeCurrent( void );
	/**
	* @brief release context
	* @return true on success, false otherwise
	*/
	bool contextDoneCurrent( void );


	/**
	* @brief swap OpenGL context buffers
	*/
	void contextSwapBuffers( void );


	///////////////////////////////////////////////////////////////////////////////////////////////
	//		GET / SET
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	/**
	* @brief get event reader
	* @return reader as SystemEventReader pointer
	*/
	SystemEventReader * getEventReader( void ) const;
	/**
	* @brief get event listener
	* @return listener as SystemEventListener pointer
	*/
	SystemEventListener * getEventListener( void ) const;


	/**
	* @brief get system window
	* @return window as SystemWindow pointer
	*/
	SystemWindow * getWindow( void ) const;


	/**
	* @brief get OpenGL context
	* @return context as SystemContext pointer
	*/
	SystemContext * getContext( void ) const;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
inline SystemEventReader * SystemNode::getEventReader( void ) const
{
	return m_pEventReader;
}

//=================================================================================================
inline SystemEventListener * SystemNode::getEventListener( void ) const
{
	return m_pEventListener;
}



//=================================================================================================
inline SystemWindow * SystemNode::getWindow( void ) const
{
	return m_pSystemWindow;
}



//=================================================================================================
inline SystemContext * SystemNode::getContext( void ) const
{
	return m_pContext;
}

#endif // __SYSTEM_NODE_H__

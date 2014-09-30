
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

// Main class header
#include "eve/sys/win32/Node.h"

// External header
#include <assert.h>

// OpenGL header
#ifndef __OGL_EXTERNAL_H__
#include "gl/OGLExternal.h"
#endif

#ifndef __GL_UTILITIES_H__
#include "gl/Utilities.h"
#endif

// Messaging header
#ifndef __NATIVE_MESSAGING_H__
#include "Native_Messaging.h"
#endif

// System header
#ifndef __SYSTEM_WINDOW_H__
#include "SystemWindow.h"
#endif

#ifndef __SYSTEM_CONTEXT_H__
#include "SystemContext.h"
#endif

#ifndef __SYSTEM_EVENT_HANDLER_H__
#include "SystemEventHandler.h"
#endif

#ifndef __SYSTEM_EVENT_READER_CONTROL_H__
#include "SystemEventReader.h"
#endif 

#ifndef __SYSTEM_EVENT_LISTENER_H__
#include "SystemEventListener.h"
#endif

#ifndef __SYSTEM_EVENT_H__
#include "SystemEvent.h"
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SystemNode class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
SystemNode * SystemNode::create_ptr
	( 
	int32_t p_x, 
	int32_t p_y, 
	uint32_t p_windowWidth, 
	uint32_t p_windowHeight,
	SystemNode * p_pNodeMaster
	)
{
	SystemNode * ptr = new SystemNode( p_x, p_y, p_windowWidth, p_windowHeight, p_pNodeMaster );

	return ptr;
}

//=================================================================================================
SystemNode * SystemNode::create_ptr_wait
	( 
	int32_t p_x, 
	int32_t p_y, 
	uint32_t p_windowWidth, 
	uint32_t p_windowHeight,
	SystemNode * p_pNodeMaster
	)
{
	SystemNode * ptr = new SystemNode( p_x, p_y, p_windowWidth, p_windowHeight, p_pNodeMaster );

	ptr->Start();

	while( !ptr->started() )
	{}

	return ptr;
}

//=================================================================================================
void SystemNode::release_ptr_wait( SystemNode * pPtr )
{
#ifndef NDEBUG
	assert( (pPtr!=NULL) );
#endif

	pPtr->Stop();
	pPtr->Join();

	delete pPtr;
}



//=================================================================================================
SystemNode::SystemNode
	( 
	int32_t p_x, 
	int32_t p_y, 
	uint32_t p_windowWidth, 
	uint32_t p_windowHeight,
    SystemNode * p_pNodeMaster
	)

	// Inheritance
	: NativeT::Thread()

	// Members initialization
	, m_windowWidth			( p_windowWidth )
	, m_windowHeight		( p_windowHeight )
	, m_X					( p_x )
	, m_Y					( p_y )
    , m_pNodeMaster         ( p_pNodeMaster )

	, m_pSystemWindow		( NULL )
	, m_pContext			( NULL )
	, m_pEventHandler		( NULL )
	, m_pEventReader		( NULL )
	, m_pEventListener		( NULL )
{}



//=================================================================================================
SystemNode::~SystemNode( void )
{
	// Do not delete -> shared pointer
	m_pNodeMaster = NULL;
}



//=================================================================================================
void SystemNode::init( void )
{
    // Order of object initialization is very important !!! do not change it !!!
	
	// Window
	m_pSystemWindow = SystemWindow::create_ptr
		( 
		0, 
		(m_pNodeMaster!=NULL) ? m_pNodeMaster : this, 
		m_X, 
		m_Y, 
		m_windowWidth, 
		m_windowHeight
		);


	// GL context
	m_pContext = new SystemContext();
	if( !m_pContext->init( 0, this, (m_pNodeMaster!=NULL) ? m_pNodeMaster->getContext() : NULL ) )
	{
		// Log error
		native_error_msg( "SystemNodeControl::init()", "context initialization failed due to OpenGL driver issue. \n" );
	}


	// Show system window
	m_pSystemWindow->show();

	// GL full extensions initialization for this context
	gl::init();

	// Init OpenGL drawing flags
    glClearColor( 0.0F, 0.0F, 0.0F, 0.0F );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc( GL_LESS ); 

	// Clear window display with black
	glClear( GL_COLOR_BUFFER_BIT );
	
	// Swap layer buffer
	m_pContext->swapBuffers();
	// Release context
	m_pContext->doneCurrent();

	
	// create event listener
	m_pEventListener = SystemEventListener::create_ptr();
	// Create message reader 
	m_pEventReader = new SystemEventReader();
	// Create message pump handler 
	m_pEventHandler = SystemEventHandler::create_ptr( this );
}



//=================================================================================================
void SystemNode::release( void )
{
	// Event handler
	if( m_pEventHandler != NULL )
	{
		delete m_pEventHandler;
		m_pEventHandler = NULL;
	}

	// Event reader
	if( m_pEventReader != NULL )
	{
		delete m_pEventReader;
		m_pEventReader = NULL;
	}

	// Event listener
	if( m_pEventListener != NULL )
	{
		delete m_pEventListener;
		m_pEventListener = NULL;
	}

	// OpenGL Context
	if( m_pContext != NULL )
	{
		m_pContext->release();
		delete m_pContext;
		m_pContext = NULL;
	}

	// Window
	if( m_pSystemWindow != NULL )
	{
		delete m_pSystemWindow;
		m_pSystemWindow = NULL;
	}
}



//=================================================================================================
void SystemNode::Run( void )
{

	// Now we're ready to receive and process Windows messages.
    bool bGotMsg;
    MSG msg;
    msg.message = WM_NULL;
 
    while( this->running() )
    {
        // Grab new message
        bGotMsg = ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0 );
		// Test message
        if( bGotMsg && msg.message != WM_NULL )
        {
            // Translate and dispatch the message
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
			msg.message = WM_NULL;
        }
        else {
             // Wait some ms, so the thread doesn't soak up CPU
            ::WaitForSingleObject( ::GetCurrentThread(), 20 );
        }

		// Free up CPU
		Sleep( 5 );
    }
}



//=================================================================================================
void SystemNode::Stop( void ) 
{
	Thread::Stop();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		WINDOW UTILITIES
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
Vec2i SystemNode::clientToScreen( const uint32_t & p_x, const uint32_t & p_y )
{
	return m_pSystemWindow->clientToScreen( p_x, p_y );
}



//=================================================================================================
void SystemNode::windowShow( void )
{
	m_pSystemWindow->show();
	m_pSystemWindow->pop();
}



//=================================================================================================
void SystemNode::windowHide( void )
{
	m_pSystemWindow->push();
	m_pSystemWindow->hide();
}



//=================================================================================================
void SystemNode::setWindowForeground( void )
{
	m_pSystemWindow->setForeground();
}



//=================================================================================================
void SystemNode::scaleWindowOnOutput( void )
{
	m_pSystemWindow->scaleOnOutput();
}

//=================================================================================================
void SystemNode::scaleWindowOnDisplay( void )
{
	m_pSystemWindow->fixOnOutput();
}
    
    

//=================================================================================================
void SystemNode::minimizeWindow( void )
{
	m_pSystemWindow->minimize();
}



//=================================================================================================
const uint32_t SystemNode::getWindowPositionX( void ) const
{
	return m_pSystemWindow->getPositionX();
}
//=================================================================================================
const uint32_t SystemNode::getWindowPositionY( void ) const
{
	return m_pSystemWindow->getPositionY();
}
//=================================================================================================
void SystemNode::setWindowPosition( const int & p_x, const int & p_y )
{
	m_pSystemWindow->setPosition( p_x, p_y );
}
//=================================================================================================
void SystemNode::setWindowPositionX( const int & p_x )
{
	m_pSystemWindow->setPositionX( p_x );
}
//=================================================================================================
void SystemNode::setWindowPositionY( const int & p_y )
{
	m_pSystemWindow->setPositionY( p_y );
}



//=================================================================================================
const uint32_t SystemNode::getWindowWidth( void ) const
{
	return m_pSystemWindow->getWidth();
}
//=================================================================================================
const uint32_t SystemNode::geWindowHeight( void ) const
{
	return m_pSystemWindow->getHeight();
}
//=================================================================================================
void SystemNode::setWindowWidth( const uint32_t & p_width )
{
	m_pSystemWindow->setWidth( p_width );
}
//=================================================================================================
void SystemNode::setWindowHeight( const uint32_t & p_height )
{
	m_pSystemWindow->setHeight( p_height );
}
//=================================================================================================
void SystemNode::setWindowSize( const uint32_t & p_width, const uint32_t & p_height )
{
	m_pSystemWindow->resize( p_width, p_height );
}



//=================================================================================================
void SystemNode::setWindowTitle( const std::string & p_title )
{
	m_pSystemWindow->setTitle( p_title );
}



//=================================================================================================
void SystemNode::setWindowDragAcceptFiles( const bool & p_bStatus )
{
	m_pSystemWindow->setDragAcceptFiles( p_bStatus );
}



//=================================================================================================
void SystemNode::setWindowCursor( SystemNode * p_pNode, const cursor::State & p_cursorType )
{

	switch( p_cursorType )
	{
		MAP_CURSOR( cursor::CURSOR_INHERIT,             IDC_CROSS     , p_pNode->getWindow()->m_Hwnd ); // Define as MWM param -> ToDo
		MAP_CURSOR( cursor::CURSOR_WAIT,                IDC_WAIT      , p_pNode->getWindow()->m_Hwnd );

		MAP_CURSOR( cursor::CURSOR_RIGHT_ARROW,         IDC_ARROW     , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_LEFT_ARROW,          IDC_ARROW     , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_INFO,                IDC_HELP      , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_DESTROY,             IDC_CROSS     , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_HELP,                IDC_HELP      , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_CYCLE,               IDC_SIZEALL   , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_SPRAY,               IDC_CROSS     , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_TEXT,                IDC_IBEAM     , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_CROSSHAIR,           IDC_CROSS     , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_UP_DOWN,             IDC_SIZENS    , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_LEFT_RIGHT,          IDC_SIZEWE    , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_TOP_SIDE,            IDC_ARROW     , p_pNode->getWindow()->m_Hwnd ); /* XXX ToDo */
		MAP_CURSOR( cursor::CURSOR_BOTTOM_SIDE,         IDC_ARROW     , p_pNode->getWindow()->m_Hwnd ); /* XXX ToDo */
		MAP_CURSOR( cursor::CURSOR_LEFT_SIDE,           IDC_ARROW     , p_pNode->getWindow()->m_Hwnd ); /* XXX ToDo */
		MAP_CURSOR( cursor::CURSOR_RIGHT_SIDE,          IDC_ARROW     , p_pNode->getWindow()->m_Hwnd ); /* XXX ToDo */
		MAP_CURSOR( cursor::CURSOR_TOP_LEFT_CORNER,     IDC_SIZENWSE  , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_TOP_RIGHT_CORNER,    IDC_SIZENESW  , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_BOTTOM_RIGHT_CORNER, IDC_SIZENWSE  , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_BOTTOM_LEFT_CORNER,  IDC_SIZENESW  , p_pNode->getWindow()->m_Hwnd );
		ZAP_CURSOR( cursor::CURSOR_NONE,                NULL          , p_pNode->getWindow()->m_Hwnd );
		MAP_CURSOR( cursor::CURSOR_FULL_CROSSHAIR,      IDC_CROSS     , p_pNode->getWindow()->m_Hwnd ); /* XXX ToDo */

	default:
		break;
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		CONTEXT UTILITIES
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
bool SystemNode::contextMakeCurrent( void )
{
	return m_pContext->makeCurrent();
}



//=================================================================================================
bool SystemNode::contextDoneCurrent( void )
{
	return m_pContext->doneCurrent();
}



//=================================================================================================
void SystemNode::contextSwapBuffers( void )
{
	m_pContext->swapBuffers();
}

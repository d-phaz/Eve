
// Main header
#include "system/shared/SystemViewOutput.h"

// External header
#include <algorithm>

// Core header
#ifndef __CORE_RENDERER_H__
#include "core/Renderer.h"
#endif

// System header
#ifndef __SYSTEM_NODE_H__
#include "system/win32/SystemNode.h"
#endif

#ifndef __SYSTEM_EVENT_LISTENER_H__
#include "system/win32/SystemEventListener.h"
#endif

#ifndef __SYSTEM_UTILS_H__
#include "native/system/SystemUtils.h"
#endif

// Event header
#ifndef __EVT_EVENT_H__ 
#include "evt/Event.h"
#endif

// OpenGL header
#ifndef __OGL_EXTERNAL_H__
#include "gl/OGLExternal.h"
#endif

#ifndef __GL_ENGINE_H__
#include "gl/Engine.h"
#endif




///////////////////////////////////////////////////////////////////////////////////////////////////
//		Statics
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
SystemViewOutput * SystemViewOutput::create_ptr
	( 
	int32_t p_x,
	int32_t p_y,
	uint32_t p_width, 
	uint32_t p_height,
	SystemNode * p_pSystemNodeMaster
	)
{
	SystemViewOutput * ptr = new SystemViewOutput( p_x, p_y, p_width, p_height, p_pSystemNodeMaster );

	return ptr;
}

//=================================================================================================
SystemViewOutput * SystemViewOutput::create_ptr_wait
	( 
	int32_t p_x,
	int32_t p_y,
	uint32_t p_width, 
	uint32_t p_height,
	SystemNode * p_pSystemNodeMaster
	)
{
	SystemViewOutput * ptr = new SystemViewOutput( p_x, p_y, p_width, p_height, p_pSystemNodeMaster );

	ptr->Start();

	while( !ptr->started() )
	{}

	return ptr;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SystemViewOutput class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
SystemViewOutput::SystemViewOutput
	( 
	int32_t p_x,
	int32_t p_y,
	uint32_t p_width, 
	uint32_t p_height,
	SystemNode * p_pSystemNodeMaster
	)

	// Inheritance
	: SystemView
		( 
		p_x,
		p_y,
		p_width, 
		p_height,
		p_pSystemNodeMaster
		)

	// Members init
	, m_mouseButton			( mouse::UNKNOWN )
	, m_clickPosX			( 0 )
	, m_clickPosY			( 0 )
	, m_windowInitialPosX	( 0 )
	, m_windowInitialPosY	( 0 )
{}

//=================================================================================================
SystemViewOutput::~SystemViewOutput( void )
{}



//=================================================================================================
void SystemViewOutput::release( void )
{
	// Call parent class
	SystemView::release();


	m_mouseButton		= mouse::UNKNOWN;
	m_clickPosX			= 0;
	m_clickPosY			= 0;
	m_windowInitialPosX	= 0;
	m_windowInitialPosY	= 0;
}



//=================================================================================================
void SystemViewOutput::processEvent( void )
{
	switch( m_eventCurrent.type.eventType )
	{
	case evt::MOTION:
		this->cb_motion( m_eventCurrent.motion.x, m_eventCurrent.motion.y );
		break;


	case evt::BUTTON_DOWN:
		this->cb_mouseDown( m_eventCurrent.button.button, m_eventCurrent.button.x, m_eventCurrent.button.y );
		break;

	case evt::BUTTON_UP:
	case evt::MOUSE_LEAVE:
		this->cb_mouseUp( m_eventCurrent.button.button, m_eventCurrent.button.x, m_eventCurrent.button.y );
		break;

	case evt::BUTTON_DOUBLE:
		this->cb_mouseDoubleClick( m_eventCurrent.button.button, m_eventCurrent.button.x, m_eventCurrent.button.y );
		break;


	case evt::RESIZE:
		this->cb_reshape( m_eventCurrent.resize.width, m_eventCurrent.resize.height );
		break;
	}
}



//=================================================================================================
void SystemViewOutput::cb_keyboardDown( uint8_t p_key )
{
	// Nothing to do for now -> kept for future use
}

//=================================================================================================
void SystemViewOutput::cb_keyboardUp( uint8_t p_key )
{
	// Nothing to do for now -> kept for future use
}

//=================================================================================================
void SystemViewOutput::cb_textInput( uint8_t p_key )
{
	// Nothing to do for now -> kept for future use
}



//=================================================================================================
void SystemViewOutput::cb_mouseEnter( void )
{
	// Nothing to do for now -> kept for future use
}

//=================================================================================================
void SystemViewOutput::cb_mouseLeave( void )
{
	// Nothing to do for now -> kept for future use
}



//=================================================================================================
void SystemViewOutput::cb_mouseDown( int32_t p_button, int32_t p_x, int32_t p_y )
{
	m_mouseButton = p_button;

	switch( m_mouseButton )
	{
	case mouse::BUTTON_LEFT:
		{
			Vec2i pt = cursor::getCursorPosition();

			m_clickPosX = pt.x;
			m_clickPosY = pt.y;

			m_windowInitialPosX = m_pSystemNode->getWindowPositionX();
			m_windowInitialPosY = m_pSystemNode->getWindowPositionY();
		}
		break;

	case mouse::BUTTON_RIGHT:
		m_pSystemNode->scaleWindowOnOutput();
		break;
	}
}

//=================================================================================================
void SystemViewOutput::cb_mouseUp( int32_t p_button, int32_t p_x, int32_t p_y )
{
	m_mouseButton = mouse::UNKNOWN;
}

//=================================================================================================
void SystemViewOutput::cb_mouseDoubleClick( int32_t p_button, int32_t p_x, int32_t p_y )
{
	m_pSystemNode->scaleWindowOnOutput();
}



//=================================================================================================
void SystemViewOutput::cb_motion( int32_t p_x, int32_t p_y )
{
	if( m_mouseButton == mouse::BUTTON_LEFT )
	{
		// Grab cursor position
		Vec2i pt = cursor::getCursorPosition();
		// Update window position
		m_pSystemNode->setWindowPosition
			( 
			m_windowInitialPosX + (pt.x-m_clickPosX),
#if defined( NATIVE_OS_WIN32 )
			m_windowInitialPosY + (pt.y-m_clickPosY)
#elif defined( NATIVE_OS_DARWIN )
			m_windowInitialPosY - (pt.y-m_clickPosY)
#endif
			);
	}
}

//=================================================================================================
void SystemViewOutput::cb_passiveMotion( int32_t p_x, int32_t p_y )
{
	// Nothing to do for now -> kept for future use
}



//=================================================================================================
void SystemViewOutput::cb_reshape( int32_t p_w, int32_t p_h )
{
	if( p_w > 0 && p_h > 0 ) // if false -> reshape comes from a "minimize window" event, so do not update
	{
		//// Call render engines
		//for( m_renderersItr  = m_pVecRenderers->begin(); 
		//	m_renderersItr != m_pVecRenderers->end(); 
		//	m_renderersItr++ )
		//{
		//	(*m_renderersItr)->resize( p_w, p_h );
		//}
	}
}



//=================================================================================================
void SystemViewOutput::cb_focusGot( void )
{
	// Nothing to do for now -> kept for future use
}

//=================================================================================================
void SystemViewOutput::cb_focusLost( void )
{
	// Nothing to do for now -> kept for future use
}



//=================================================================================================
void SystemViewOutput::cb_close( void )
{
	// Nothing to do for now -> kept for future use
}

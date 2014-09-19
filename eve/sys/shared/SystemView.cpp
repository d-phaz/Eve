
// Main header
#include "system/shared/SystemView.h"

// External header
#include <algorithm>

// Core header
#ifndef __CORE_APP_H__
#include "core/App.h"
#endif

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

SystemView * SystemView::m_p_main_view = NULL;



//=================================================================================================
SystemView * SystemView::create_ptr
	( 
	int32_t p_x,
	int32_t p_y,
	int32_t p_width, 
	int32_t p_height
	)
{
	SystemView * ptr = new SystemView( p_x, p_y, p_width, p_height, NULL );

	return ptr;
}

//=================================================================================================
SystemView * SystemView::create_ptr_wait
	( 
	int32_t p_x,
	int32_t p_y,
	int32_t p_width, 
	int32_t p_height
	)
{
	SystemView * ptr = new SystemView( p_x, p_y, p_width, p_height, NULL );

	ptr->Start();

	while( !ptr->started() )
	{}

	return ptr;
}

//=================================================================================================
void SystemView::release_ptr_wait( SystemView * pPtr )
{
#ifndef NDEBUG
	assert( (pPtr!=NULL) );
#endif

	pPtr->Stop();
	pPtr->Join();

	delete pPtr;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SystemView class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
SystemView::SystemView
	( 
	int32_t p_x,
	int32_t p_y,
	int32_t p_width, 
	int32_t p_height,
	SystemNode * p_pSystemNodeMaster
	)

	// Inheritance
	: NativeT::Thread()

	// Members initialization
	, m_x						( p_x )
	, m_y						( p_y )
	, m_width					( p_width )
	, m_height					( p_height )

	, m_pSystemNode				( NULL )
	, m_pSystemNodeMaster		( p_pSystemNodeMaster )
	, m_pSystemEventListener	( NULL )

	, m_pVecRenderers			( NULL )
{}

//=================================================================================================
SystemView::~SystemView( void )
{}



//=================================================================================================
void SystemView::init( void )
{
	m_pSystemNode			= SystemNode::create_ptr_wait( m_x, m_y, m_width, m_height, m_pSystemNodeMaster ); 
	m_pSystemEventListener	= m_pSystemNode->getEventListener();

	m_pVecRenderers			= new std::vector<core::Renderer*>();
}

//=================================================================================================
void SystemView::release( void )
{
	// Release renderer vector (content is shared)
	m_pVecRenderers->clear();
	delete m_pVecRenderers;
	m_pVecRenderers = NULL;


	// Activate OpenGL context.
	gl::Engine::context_make_current( m_pSystemNode );

	// Process queues.
	gl::Engine::process_queues();

	// Swap layer buffer
	m_pSystemNode->contextSwapBuffers();

	// Release OpenGL context activation.
	gl::Engine::context_done_current( m_pSystemNode );


	// Release system node
	SystemNode::release_ptr_wait( m_pSystemNode );
	m_pSystemNode = NULL;


	// Do not delete this -> shared pointers
	m_pSystemNodeMaster		= NULL;
	m_pSystemEventListener	= NULL;
}

//=================================================================================================
void SystemView::Run( void )
{
	// Launch Thread main loop
	while( this->running() )
	{
		m_pSystemEventListener->eventSwap();
		while( !m_pSystemEventListener->eventEmpty() ) 
		{
			m_eventCurrent = m_pSystemEventListener->eventGet();
			this->processEvent();
		}

		// Display callback -> called as many times as possible
		this->cb_display();

		// Micro sleep
		//u_sleep( 1000ULL );
		// Milli sleep
		this->m_sleep( 10 );
	}
}


//=================================================================================================
void SystemView::processEvent( void )
{
	switch( m_eventCurrent.type.eventType )
	{
	case evt::PASSIVE_MOTION:
		this->cb_passiveMotion( m_eventCurrent.motion.x, m_eventCurrent.motion.y );
		break;
	case evt::MOTION:
		this->cb_motion( m_eventCurrent.motion.x, m_eventCurrent.motion.y );
		break;


	case evt::BUTTON_DOWN:
		this->cb_mouseDown( m_eventCurrent.button.button, m_eventCurrent.button.x, m_eventCurrent.button.y );
		break;
	case evt::BUTTON_UP:
		this->cb_mouseUp( m_eventCurrent.button.button, m_eventCurrent.button.x, m_eventCurrent.button.y );
		break;
	case evt::BUTTON_DOUBLE:
		this->cb_mouseDoubleClick( m_eventCurrent.button.button, m_eventCurrent.button.x, m_eventCurrent.button.y );
		break;


	case evt::KEY_DOWN: // aka special key
		this->cb_keyboardDown( m_eventCurrent.key.symbol );
		break;
	case evt::TEXT_INPUT:
		this->cb_textInput( m_eventCurrent.text.unicode );
		break;


	case evt::RESIZE:
		this->cb_reshape( m_eventCurrent.resize.width, m_eventCurrent.resize.height );
		break;


	case evt::FOCUS_GOT:
		this->cb_focusGot();
		break;
	case evt::FOCUS_LOST:
		this->cb_focusLost();
		break;


	case evt::CLOSE:
		this->cb_close();
		break;
	}
}



//=================================================================================================
void SystemView::cb_keyboardDown( uint8_t p_key )
{
	// Event dispatch
	evt::notify_key_pressed( p_key );
}

//=================================================================================================
void SystemView::cb_keyboardUp( uint8_t p_key )
{
	// Event dispatch
	evt::notify_key_released( p_key );
}

//=================================================================================================
void SystemView::cb_textInput( uint8_t p_key )
{
	// Event dispatch
	evt::notify_text_input( p_key );
}



//=================================================================================================
void SystemView::cb_mouseEnter( void )
{
	// Nothing to do for now -> kept for future use
}

//=================================================================================================
void SystemView::cb_mouseLeave( void )
{
	// Nothing to do for now -> kept for future use
}



//=================================================================================================
void SystemView::cb_mouseDown( int32_t p_button, int32_t p_x, int32_t p_y )
{
	// Event dispatch
	evt::notify_mouse_down( p_button, p_x, p_y );
}

//=================================================================================================
void SystemView::cb_mouseUp( int32_t p_button, int32_t p_x, int32_t p_y )
{
	// Event dispatch
	evt::notify_mouse_up( p_button, p_x, p_y );
}

//=================================================================================================
void SystemView::cb_mouseDoubleClick( int32_t p_button, int32_t p_x, int32_t p_y )
{
	// Event dispatch
	evt::notify_mouse_double_click( p_button, p_x, p_y );
}



//=================================================================================================
void SystemView::cb_motion( int32_t p_x, int32_t p_y )
{
	// Event dispatch
	evt::notify_mouse_motion( p_x, p_y );
}

//=================================================================================================
void SystemView::cb_passiveMotion( int32_t p_x, int32_t p_y )
{
	// Event dispatch
	evt::notify_mouse_passive_motion( p_x, p_y );
}



//=================================================================================================
void SystemView::cb_reshape( int32_t p_w, int32_t p_h )
{
	// Event dispatch
	if( p_w > 0 && p_h > 0 ) // if false -> reshape comes from a "minimize window" event, so do not update
	{
		m_width  = p_w;
		m_height = p_h;

		evt::notify_window_resize( (uint32_t)p_w, (uint32_t)p_h );
	}
}



//=================================================================================================
void SystemView::cb_focusGot( void )
{
	// Event dispatch
	evt::notify_focus_got();
}

//=================================================================================================
void SystemView::cb_focusLost( void )
{
	// Event dispatch
	evt::notify_focus_lost();
}



//=================================================================================================
void SystemView::cb_close( void )
{
	// Event dispatch
	evt::notify_close();
}



//=================================================================================================
void SystemView::cb_idle( void )
{
	// Event dispatch
	evt::notify_idle();
}



//=================================================================================================
void SystemView::cb_display( void )
{
	// Activate OpenGL context.
	gl::Engine::context_make_current( m_pSystemNode );

	// Process queues.
	gl::Engine::process_queues();


	// Call render engines
	std::vector<core::Renderer*>::iterator itr		 = m_pVecRenderers->begin();
	std::vector<core::Renderer*>::const_iterator itrE = m_pVecRenderers->end();
	for( ; itr!=itrE; itr++ )
	{
		(*itr)->cb_display();
	}


	// Swap layer buffer
	m_pSystemNode->contextSwapBuffers();

	// Release OpenGL context activation.
	gl::Engine::context_done_current( m_pSystemNode );
}



//=================================================================================================
bool SystemView::registerRenderer( core::Renderer * p_pRenderer )
{
	std::vector<core::Renderer*>::iterator itr = std::find( m_pVecRenderers->begin(), m_pVecRenderers->end(), p_pRenderer );

	bool breturn = (itr==m_pVecRenderers->end());

	if( breturn )
	{
		gl::Engine::lock();
		m_pVecRenderers->push_back( p_pRenderer );
		gl::Engine::unlock();
	}

	return breturn;
}

//=================================================================================================
bool SystemView::unregisterRenderer( core::Renderer * p_pRenderer )
{
	std::vector<core::Renderer*>::iterator itr = std::find( m_pVecRenderers->begin(), m_pVecRenderers->end(), p_pRenderer );

	bool breturn = (itr!=m_pVecRenderers->end());

	if( breturn )
	{
		gl::Engine::lock();
		m_pVecRenderers->erase( itr );
		gl::Engine::unlock();
	}

	return breturn;
}

//=================================================================================================
bool SystemView::releaseRenderer( core::Renderer * p_pRenderer )
{
	std::vector<core::Renderer*>::iterator itr = std::find( m_pVecRenderers->begin(), m_pVecRenderers->end(), p_pRenderer );

	bool breturn = (itr!=m_pVecRenderers->end());

	if( breturn )
	{
		gl::Engine::lock();

		core::Renderer * rder = (*itr);
		m_pVecRenderers->erase( itr );
		core::Renderer::release_ptr( rder );

		gl::Engine::unlock();
	}

	return breturn;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
const int32_t SystemView::getPositionX( void ) const
{
	return m_pSystemNode->getWindowPositionX();
}

//=================================================================================================
const int32_t SystemView::getPositionY( void ) const
{
	return m_pSystemNode->getWindowPositionY();
}


#pragma once
#ifndef __SYSTEM_VIEW_H__
#define __SYSTEM_VIEW_H__


// Thread header
#ifndef __NATIVE_THREAD_H__
#include "thread/win32/Native_Thread.h"
#endif

// External header
#include <cstdint>
#include <vector>

// System header
#ifndef __SYSTEM_EVENT_H__
#include "System/shared/SystemEvent.h"
#endif


namespace core
{
	class Controller;
	class Renderer;
}

class SystemNode;
class SystemEventListener;


/**
* @class SystemView
*
* Threaded view, manages event dispatch via dedicated callbacks 
* and system dependent window / OpenGL context / event reader 
*/
class SystemView
    : public NativeT::Thread
{

	//////////////////////////////////////
	//				DATAS				//
	//////////////////////////////////////

protected:
	static SystemView *							m_p_main_view;

protected:
	int32_t										m_x;						//<! View position on X-axis (in screen coordinates)
	int32_t										m_y;						//<! View position on Y-axis (in screen coordinates)
	int32_t										m_width;					//<! View width (in screen coordinates)
	int32_t										m_height;					//<! View height (in screen coordinates)

	SystemNode *								m_pSystemNode;				//<! System node pointer containing event reader / window / OpenGL context.
	SystemNode *								m_pSystemNodeMaster;		//<! Convenience shared master system node pointer.
	
	SystemEventListener *						m_pSystemEventListener;		//<! Convenience shared event listener pointer.	
	evt::Event									m_eventCurrent;				//<! Current system event (event to dispatch).

	std::vector<core::Renderer*> *				m_pVecRenderers;			//<! Display renderer vector.
	
	//////////////////////////////////////
	//				METHODS				//
	//////////////////////////////////////

	NATIVE_DISABLE_COPY(SystemView);

public:
	/** \! Create, init and return new SystemView pointer, do not start thread. 
	* Example :
	*	SystemView * ptr = SystemView::create_ptr();
	*	ptr->Start();
	*/
	static SystemView * create_ptr
		( 
		int32_t p_x = 50,
		int32_t p_y = 50,
		int32_t p_width = 800, 
		int32_t p_height = 600
		);

	/** \! Create, init and return new SystemView pointer once its thread is started. 
	* Example :
	*	SystemView * ptr = SystemView::create_ptr_wait();
	*/
	static SystemView * create_ptr_wait
		( 
		int32_t p_x = 50,
		int32_t p_y = 50,
		int32_t p_width = 800, 
		int32_t p_height = 600
		);

	/** \! Release and delete pointer class members once its thread is stopped. 
	* Example :
	*	SystemView::release_ptr_wait( ptr );
	*	ptr = NULL;
	*/
	static void release_ptr_wait( SystemView * pPtr );

protected:
	/** SystemView class constructor. */
	SystemView
		( 
		int32_t p_x = 50,
		int32_t p_y = 50,
		int32_t p_width = 800, 
		int32_t p_height = 600,
		SystemNode * p_pSystemNodeMaster = NULL
		);

	/** SystemView class destructor */
	virtual ~SystemView( void );

    
protected:
    /** Thread initialization function, init members inside thread run. */
	virtual void init( void );
    
	/** Thread release function, release members inside thread run before exit. */
	virtual void release( void );

	/** Thread main run. */
	virtual void Run( void );



protected:
    /** Process system incoming user events. */
    void processEvent( void );



protected:
	/** \! Keyboard down event callback. */
	virtual void cb_keyboardDown( uint8_t p_key );

	/** \! Keyboard up event callback. */
	virtual void cb_keyboardUp( uint8_t p_key );

	/** \! Text input event callback. */
	virtual void cb_textInput( uint8_t p_key );


	/** \! Mouse enter event callback. */
	virtual void cb_mouseEnter( void );

	/** \! Mouse leave event callback. */
	virtual void cb_mouseLeave( void );


	/** \! Mouse down event callback. */
	virtual void cb_mouseDown( int32_t p_button, int32_t p_x, int32_t p_y );

	/** \! Mouse up event callback. */
	virtual void cb_mouseUp( int32_t p_button, int32_t p_x, int32_t p_y );

	/** \! Mouse double click callback. */
	virtual void cb_mouseDoubleClick( int32_t p_button, int32_t p_x, int32_t p_y );

	
	/** \! Mouse move while pressed event callback. */
	virtual void cb_motion( int32_t p_x, int32_t p_y );

	/** \! Mouse move event callback. */
	virtual void cb_passiveMotion( int32_t p_x, int32_t p_y );


	/** \! Window resize/reshape event callback. */
	virtual void cb_reshape( int32_t p_w, int32_t p_h );


	/** \! Window gain focus event callback. */
	virtual void cb_focusGot( void );

	/** \! Window lost focus event callback. */
	virtual void cb_focusLost( void );


	/** \! Close event callback. */
	virtual void cb_close( void );


	/** \! Idle event callback. */
	virtual void cb_idle( void );


	/** \! Main display callback. */
	virtual void cb_display( void );


public:
	/** \! Register a renderer pointer. 
	* Return false if controller already registered. */
	bool registerRenderer( core::Renderer * p_pRenderer );

	/** \! Unregister a renderer pointer. 
	* Return false if controller not registered. */
	bool unregisterRenderer( core::Renderer * p_pRenderer );

	/** \! Unregister and release  a renderer pointer. 
	* Return false if controller not registered. */
	bool releaseRenderer( core::Renderer * p_pRenderer );
	


	///////////////////////////////////////////////////////////////////////////////////////////////
	//		GET / SET
	///////////////////////////////////////////////////////////////////////////////////////////////

public:
	/** \! Set main view. */
	static void set_main_view( SystemView * p_pView );
	/** \! Get main view. */
	static SystemView * get_main_view( void );


public:
	/** Get system node. Please use with caution. */
	SystemNode * getSystemNode( void ) const;


	/** \! Get position on X-axis. */
	const int32_t getPositionX( void ) const;
	/** \! Get position on Y-axis. */
	const int32_t getPositionY( void ) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
inline void SystemView::set_main_view( SystemView * p_pView )
{
	m_p_main_view = p_pView;
}

//=================================================================================================
inline SystemView * SystemView::get_main_view( void )
{
	return m_p_main_view;
}



//=================================================================================================
inline SystemNode * SystemView::getSystemNode( void ) const
{
	return m_pSystemNode;
}

#endif // __SYSTEM_VIEW_H__

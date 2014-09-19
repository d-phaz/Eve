
#pragma once
#ifndef __SYSTEM_VIEW_OUTPUT_H__
#define __SYSTEM_VIEW_OUTPUT_H__


// Parent header
#include "System/shared/SystemView.h"


/**
* @class SystemViewOutput
*
* Threaded view, manages event dispatch via dedicated callbacks 
* and system dependent window / OpenGL context / event reader 
* for output windows
*/
class SystemViewOutput
    : public SystemView
{

	//////////////////////////////////////
	//				DATAS				//
	//////////////////////////////////////

private:
	int32_t				m_mouseButton;

	int32_t				m_clickPosX;
	int32_t				m_clickPosY;

	int32_t				m_windowInitialPosX;
	int32_t				m_windowInitialPosY;

	
	//////////////////////////////////////
	//				METHODS				//
	//////////////////////////////////////

	NATIVE_DISABLE_COPY(SystemViewOutput)

protected:
	/** SystemViewOutput class constructor. */
	SystemViewOutput
		( 
		int32_t p_x,
		int32_t p_y,
		uint32_t p_width, 
		uint32_t p_height,
		SystemNode * p_pSystemNodeMaster
		);

	/** SystemViewOutput class destructor */
	virtual ~SystemViewOutput( void );


public:
	/** \! Create, init and return new SystemViewOutput pointer, do not start thread. */
	static SystemViewOutput * create_ptr
		( 
		int32_t p_x,
		int32_t p_y,
		uint32_t p_width, 
		uint32_t p_height,
		SystemNode * p_pSystemNodeMaster
		);

	/** \! Create, init and return new SystemViewOutput pointer once its thread is started. */
	static SystemViewOutput * create_ptr_wait
		( 
		int32_t p_x,
		int32_t p_y,
		uint32_t p_width, 
		uint32_t p_height,
		SystemNode * p_pSystemNodeMaster
		);



protected:
	/** Thread release function, release members inside thread run before exit. */
	virtual void release( void );


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
};

#endif // __SYSTEM_VIEW_OUTPUT_H__

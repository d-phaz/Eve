
#pragma once
#ifndef __SYSTEM_VIEW_MAIN_H__
#define __SYSTEM_VIEW_MAIN_H__


// Parent header
#include "System/shared/SystemView.h"


/**
* @class SystemViewMain
*
* Threaded view, manages event dispatch via dedicated callbacks 
* and system dependent window / OpenGL context / event reader.
* 
* Main (aka master) application view containing user interface
*/
class SystemViewMain
    : public SystemView
{

	//////////////////////////////////////
	//				DATAS				//
	//////////////////////////////////////

protected:

	
	//////////////////////////////////////
	//				METHODS				//
	//////////////////////////////////////

	NATIVE_DISABLE_COPY(SystemViewMain);

public:
	/** \! Create, init and return new SystemViewMain pointer once its thread is started. */
	static SystemViewMain * create_ptr_wait( void );


protected:
	/** SystemViewMain class constructor. */
	SystemViewMain
		( 
		int32_t p_x,
		int32_t p_y,
		int32_t p_width, 
		int32_t p_height
		);

	/** SystemViewMain class destructor */
	virtual ~SystemViewMain( void );



protected:
	/** Thread initialization function, init members inside thread run. */
	virtual void init( void );

	/** Thread release function, release members inside thread run before exit. */
	virtual void release( void );


protected:
	/** \! Close event callback. */
	virtual void cb_close( void );
};

#endif // __SYSTEM_VIEW_MAIN_H__

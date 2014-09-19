
// Main header
#include "system/shared/SystemViewMain.h"

#ifndef __SYSTEM_UTILS_H__
#include "native/system/SystemUtils.h"
#endif

#ifndef __EVT_EVENT_H__ 
#include "evt/Event.h"
#endif

#ifndef __GL_ENGINE_H__
#include "gl/Engine.h"
#endif

#ifndef __GL_ENVIRONMENT_H__
#include "gl/Environment.h"
#endif

#ifndef __GL_VIEWPORT_MANAGER_H__
#include "gl/ViewportManager.h"
#endif

#ifndef __GL_SHADER_MANAGER_H__
#include "gl/shader/ShaderManager.h"
#endif

#ifndef __SCENE_BRIDGE_H__
#include "scene/Bridge.h"
#endif




///////////////////////////////////////////////////////////////////////////////////////////////////
//		Statics
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
SystemViewMain * SystemViewMain::create_ptr_wait( void )
{
	SystemViewMain * ptr = new SystemViewMain( 0, 0, NATIVESYSTEM::getMainDisplayWidth(), NATIVESYSTEM::getMainDisplayHeight() );

	ptr->Start();

	while( !ptr->started() )
	{}

	return ptr;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SystemViewMain class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
SystemViewMain::SystemViewMain
	( 
	int32_t p_x,
	int32_t p_y,
	int32_t p_width, 
	int32_t p_height
	)

	// Inheritance
	: SystemView
		( 
		p_x,
		p_y,
		p_width, 
		p_height
		)

	// Members init
{}

//=================================================================================================
SystemViewMain::~SystemViewMain( void )
{}



//=================================================================================================
void SystemViewMain::init( void )
{
	// Call parent class
	SystemView::init();

	gl::Environment::create_instance();
	gl::ViewportManager::create_instance( m_width, m_height );
	gl::ShaderManager::create_instance();

	scene::Bridge::create_instance();

	// Stock main view as this
	SystemView::set_main_view( this );

	// //
	evt::controlEventArgs eventArgs;
	eventArgs.m_eventType	= evt::add_sceneFromPath;
	eventArgs.m_path		= "C:\\Users\\aleister_doe\\Desktop\\import\\untitled_spot.dae"; //romzy\\zombie_running_1.dae";
	scene::Bridge::get_instance()->newControlEventMessage( eventArgs );

	eventArgs.m_eventType	= evt::scene_activate;
	eventArgs.m_valueSize_t = 0;
	scene::Bridge::get_instance()->newControlEventMessage( eventArgs );
	// //
}

//=================================================================================================
void SystemViewMain::release( void )
{
	scene::Bridge::release_instance();

	gl::ShaderManager::release_instance();
	gl::ViewportManager::release_instance();
	gl::Environment::release_instance();

	// Call parent class
	SystemView::release();
}



//=================================================================================================
void SystemViewMain::cb_close( void )
{
	evt::notify_app_exit();
}

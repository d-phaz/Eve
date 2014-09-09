
// Main header
#include "evt/Event.h"



///////////////////////////////////////////////////////////////////////////////////////////////////
//		evt::CoreEvents class
///////////////////////////////////////////////////////////////////////////////////////////////////

evt::TEvent<evt::KeyEventArgs> 			evt::CoreEvents::keyPressed;
evt::TEvent<evt::KeyEventArgs> 			evt::CoreEvents::keyReleased;
evt::TEvent<evt::KeyEventArgs> 			evt::CoreEvents::textInput;

evt::TEvent<evt::MouseEventArgs> 		evt::CoreEvents::mousePassiveMotion;
evt::TEvent<evt::MouseEventArgs> 		evt::CoreEvents::mouseMotion;
evt::TEvent<evt::MouseEventArgs> 		evt::CoreEvents::mouseDown;
evt::TEvent<evt::MouseEventArgs>		evt::CoreEvents::mouseDoubleClick;
evt::TEvent<evt::MouseEventArgs> 		evt::CoreEvents::mouseUp;
evt::TEvent<evt::Args>					evt::CoreEvents::mouseEnter;
evt::TEvent<evt::Args>					evt::CoreEvents::mouseLeave;

evt::TEvent<evt::TouchEventArgs>		evt::CoreEvents::touchDown;
evt::TEvent<evt::TouchEventArgs>		evt::CoreEvents::touchUp;
evt::TEvent<evt::TouchEventArgs>		evt::CoreEvents::touchMoved;
evt::TEvent<evt::TouchEventArgs>		evt::CoreEvents::touchDoubleTap;
evt::TEvent<evt::TouchEventArgs>		evt::CoreEvents::touchCancelled;

evt::TEvent<evt::ResizeEventArgs> 		evt::CoreEvents::windowResized;

evt::TEvent<void>						evt::CoreEvents::focusGot;
evt::TEvent<void>						evt::CoreEvents::focusLost;

evt::TEvent<void>						evt::CoreEvents::idle;
evt::TEvent<void>						evt::CoreEvents::display;

evt::TEvent<void>						evt::CoreEvents::close;

evt::TEvent<void>						evt::CoreEvents::applicationExit;



evt::TEvent<evt::ResizeEventArgs> 		evt::CoreEvents::pluginResized;
evt::TEvent<evt::ResizeEventArgs> 		evt::CoreEvents::setSizeDashboard;


//=================================================================================================
void evt::CoreEvents::disable( void )
{
	keyPressed.disable();
	keyReleased.disable();
	textInput.disable();
	mouseEnter.disable();
	mouseLeave.disable();
	mouseMotion.disable();
	mouseUp.disable();
	mouseDown.disable();
	mousePassiveMotion.disable();
	touchDown.disable();
	touchUp.disable();
	touchMoved.disable();
	touchDoubleTap.disable();
	touchCancelled.disable();
	windowResized.disable();
	focusGot.disable();
	focusLost.disable();
	idle.disable();
	display.disable();
	close.disable();
	applicationExit.disable();


	pluginResized.disable();
	setSizeDashboard.disable();
}

//=================================================================================================
void evt::CoreEvents::enable( void )
{
	keyPressed.enable();
	keyReleased.enable();
	textInput.enable();
	mouseEnter.enable();
	mouseLeave.enable();
	mouseMotion.enable();
	mouseUp.enable();
	mouseDown.enable();
	mousePassiveMotion.enable();
	touchDown.enable();
	touchUp.enable();
	touchMoved.enable();
	touchDoubleTap.enable();
	touchCancelled.enable();
	focusGot.enable();
	focusLost.enable();
	idle.enable();
	display.enable();
	close.enable();
	applicationExit.enable();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		Event notification
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void evt::notify_key_pressed( uint8_t key )
{
	static evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = key;
	evt::notify_event( CoreEvents::keyPressed, keyEventArgs );
}

//=================================================================================================
void evt::notify_key_released( uint8_t key )
{
	static evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = key;
	evt::notify_event( CoreEvents::keyReleased, keyEventArgs );
}

//=================================================================================================
void evt::notify_text_input( uint8_t key )
{
	static evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = key;
	evt::notify_event( CoreEvents::textInput, keyEventArgs );
}

//=================================================================================================
void evt::notify_key_event( const evt::KeyEventArgs & p_args )
{
	switch( p_args.type )
	{
	case evt::KeyEventArgs::TextInput:
		evt::notify_text_input( p_args.key );
		break;

	case evt::KeyEventArgs::Pressed:
		evt::notify_key_pressed( p_args.key );
		break;

	case evt::KeyEventArgs::Released:
		evt::notify_key_released( p_args.key );
		break;
	}
}



//=================================================================================================
void evt::notify_mouse_down( int32_t button, int32_t x, int32_t y )
{
	static evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	mouseEventArgs.type		= evt::MouseEventArgs::Pressed;
	evt::notify_event( CoreEvents::mouseDown, mouseEventArgs );
}

//=================================================================================================
void evt::notify_mouse_up( int32_t button, int32_t x, int32_t y )
{
	static evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	mouseEventArgs.type		= evt::MouseEventArgs::Pressed;
	evt::notify_event( CoreEvents::mouseUp, mouseEventArgs );
}

//=================================================================================================
void evt::notify_mouse_double_click( int32_t button, int32_t x, int32_t y )
{
	static evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	mouseEventArgs.type		= evt::MouseEventArgs::DoubleClick;
	evt::notify_event( CoreEvents::mouseDoubleClick, mouseEventArgs );
}

//=================================================================================================
void evt::notify_mouse_motion( int32_t x, int32_t y )
{
	static evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	mouseEventArgs.type = evt::MouseEventArgs::Motion;
	evt::notify_event( CoreEvents::mouseMotion, mouseEventArgs );
}

//=================================================================================================
void evt::notify_mouse_passive_motion( int32_t x, int32_t y )
{
	static evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.x = x;
	mouseEventArgs.y = y;
	mouseEventArgs.type = evt::MouseEventArgs::PassiveMotion;
	evt::notify_event( CoreEvents::mousePassiveMotion, mouseEventArgs );
}

//=================================================================================================
void evt::notify_mouse_event( const evt::MouseEventArgs & p_args )
{
	switch( p_args.type )
	{
	case evt::MouseEventArgs::PassiveMotion:
		evt::notify_mouse_passive_motion( p_args.x, p_args.y );
		break;

	case evt::MouseEventArgs::Motion:
		evt::notify_mouse_motion( p_args.x, p_args.y );
		break;

	case evt::MouseEventArgs::Pressed:
		evt::notify_mouse_down( p_args.button, p_args.x, p_args.y );
		break;

	case evt::MouseEventArgs::Released:
		evt::notify_mouse_up( p_args.button, p_args.x, p_args.y );
		break;

	case evt::MouseEventArgs::DoubleClick:
		evt::notify_mouse_double_click( p_args.button, p_args.x, p_args.y );
		break;
	}
}



//=================================================================================================
void evt::notify_window_resize( uint32_t p_width, uint32_t p_height )
{
	static evt::ResizeEventArgs resizeEventArgs;

	resizeEventArgs.width  = p_width;
	resizeEventArgs.height = p_height;
	evt::notify_event( CoreEvents::windowResized, resizeEventArgs );
}

//=================================================================================================
void evt::notify_window_resize_event( const evt::ResizeEventArgs & p_args )
{
	evt::notify_window_resize( p_args.width, p_args.height );
}



//=================================================================================================
void evt::notify_focus_got( void )
{
	static evt::Args args;
	evt::notify_event( CoreEvents::focusGot );
}

//=================================================================================================
void evt::notify_focus_lost( void )
{
	evt::notify_event( CoreEvents::focusLost );
}



//=================================================================================================
void evt::notify_idle( void )
{
	evt::notify_event( CoreEvents::idle );
}



//=================================================================================================
void evt::notify_display( void )
{
	evt::notify_event( CoreEvents::display );
}



//=================================================================================================
void evt::notify_close( void )
{
	evt::notify_event( CoreEvents::close );
}



//=================================================================================================
void evt::notify_app_exit( void )
{
	evt::notify_event( CoreEvents::applicationExit );
}



//=================================================================================================
void evt::notify_plugin_resize( int32_t p_width, int32_t p_height )
{
	static evt::ResizeEventArgs resizeEventArgs;

	resizeEventArgs.width  = p_width;
	resizeEventArgs.height = p_height;
	evt::notify_event( CoreEvents::pluginResized, resizeEventArgs );
}
//=================================================================================================
void evt::notify_plugin_resize_event( const evt::ResizeEventArgs & p_args )
{
	evt::notify_plugin_resize( p_args.width, p_args.height );
}

//=================================================================================================
void evt::notify_set_size_dashboard( int32_t p_width, int32_t p_height )
{
	static evt::ResizeEventArgs resizeEventArgs;

	resizeEventArgs.width  = p_width;
	resizeEventArgs.height = p_height;
	evt::notify_event( CoreEvents::setSizeDashboard, resizeEventArgs );
}
//=================================================================================================
void evt::notify_set_size_dashboard_event( const evt::ResizeEventArgs & p_args )
{
	evt::notify_set_size_dashboard( p_args.width, p_args.height );
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		EventListenner class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
evt::EventListenner::EventListenner(void)
{}

//=================================================================================================
evt::EventListenner::~EventListenner(void)
{}



//=================================================================================================
void evt::EventListenner::newVideoEventMessage( evt::VideoEventArgs & p_eventArgs)
{}

//=================================================================================================
void evt::EventListenner::newControlEventMessage( evt::controlEventArgs & p_eventArgs)
{}

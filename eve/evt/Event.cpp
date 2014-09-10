
// Main header
#include "evt/Event.h"



///////////////////////////////////////////////////////////////////////////////////////////////////
//		eve::evt::CoreEvents class
///////////////////////////////////////////////////////////////////////////////////////////////////

eve::evt::TEvent<eve::evt::KeyEventArgs> 			eve::evt::CoreEvents::keyPressed;
eve::evt::TEvent<eve::evt::KeyEventArgs> 			eve::evt::CoreEvents::keyReleased;
eve::evt::TEvent<eve::evt::KeyEventArgs> 			eve::evt::CoreEvents::textInput;

eve::evt::TEvent<eve::evt::MouseEventArgs> 			eve::evt::CoreEvents::mousePassiveMotion;
eve::evt::TEvent<eve::evt::MouseEventArgs> 			eve::evt::CoreEvents::mouseMotion;
eve::evt::TEvent<eve::evt::MouseEventArgs> 			eve::evt::CoreEvents::mouseDown;
eve::evt::TEvent<eve::evt::MouseEventArgs>			eve::evt::CoreEvents::mouseDoubleClick;
eve::evt::TEvent<eve::evt::MouseEventArgs> 			eve::evt::CoreEvents::mouseUp;
eve::evt::TEvent<eve::evt::Args>					eve::evt::CoreEvents::mouseEnter;
eve::evt::TEvent<eve::evt::Args>					eve::evt::CoreEvents::mouseLeave;

eve::evt::TEvent<eve::evt::TouchEventArgs>			eve::evt::CoreEvents::touchDown;
eve::evt::TEvent<eve::evt::TouchEventArgs>			eve::evt::CoreEvents::touchUp;
eve::evt::TEvent<eve::evt::TouchEventArgs>			eve::evt::CoreEvents::touchMoved;
eve::evt::TEvent<eve::evt::TouchEventArgs>			eve::evt::CoreEvents::touchDoubleTap;
eve::evt::TEvent<eve::evt::TouchEventArgs>			eve::evt::CoreEvents::touchCancelled;

eve::evt::TEvent<eve::evt::ResizeEventArgs> 		eve::evt::CoreEvents::windowResized;

eve::evt::TEvent<void>								eve::evt::CoreEvents::focusGot;
eve::evt::TEvent<void>								eve::evt::CoreEvents::focusLost;

eve::evt::TEvent<void>								eve::evt::CoreEvents::idle;
eve::evt::TEvent<void>								eve::evt::CoreEvents::display;

eve::evt::TEvent<void>								eve::evt::CoreEvents::close;

eve::evt::TEvent<void>								eve::evt::CoreEvents::applicationExit;


//=================================================================================================
void eve::evt::CoreEvents::disable( void )
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
}

//=================================================================================================
void eve::evt::CoreEvents::enable( void )
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
void eve::evt::notify_key_pressed( uint8_t key )
{
	static eve::evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = key;
	eve::evt::notify_event( CoreEvents::keyPressed, keyEventArgs );
}

//=================================================================================================
void eve::evt::notify_key_released( uint8_t key )
{
	static eve::evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = key;
	eve::evt::notify_event( CoreEvents::keyReleased, keyEventArgs );
}

//=================================================================================================
void eve::evt::notify_text_input( uint8_t key )
{
	static eve::evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = key;
	eve::evt::notify_event( CoreEvents::textInput, keyEventArgs );
}

//=================================================================================================
void eve::evt::notify_key_event( const eve::evt::KeyEventArgs & p_args )
{
	switch( p_args.type )
	{
	case eve::evt::KeyEventArgs::TextInput:
		eve::evt::notify_text_input( p_args.key );
		break;

	case eve::evt::KeyEventArgs::Pressed:
		eve::evt::notify_key_pressed( p_args.key );
		break;

	case eve::evt::KeyEventArgs::Released:
		eve::evt::notify_key_released( p_args.key );
		break;
	}
}



//=================================================================================================
void eve::evt::notify_mouse_down( int32_t button, int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	mouseEventArgs.type		= eve::evt::MouseEventArgs::Pressed;
	eve::evt::notify_event( CoreEvents::mouseDown, mouseEventArgs );
}

//=================================================================================================
void eve::evt::notify_mouse_up( int32_t button, int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	mouseEventArgs.type		= eve::evt::MouseEventArgs::Pressed;
	eve::evt::notify_event( CoreEvents::mouseUp, mouseEventArgs );
}

//=================================================================================================
void eve::evt::notify_mouse_double_click( int32_t button, int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	mouseEventArgs.type		= eve::evt::MouseEventArgs::DoubleClick;
	eve::evt::notify_event( CoreEvents::mouseDoubleClick, mouseEventArgs );
}

//=================================================================================================
void eve::evt::notify_mouse_motion( int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	mouseEventArgs.type = eve::evt::MouseEventArgs::Motion;
	eve::evt::notify_event( CoreEvents::mouseMotion, mouseEventArgs );
}

//=================================================================================================
void eve::evt::notify_mouse_passive_motion( int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.x = x;
	mouseEventArgs.y = y;
	mouseEventArgs.type = eve::evt::MouseEventArgs::PassiveMotion;
	eve::evt::notify_event( CoreEvents::mousePassiveMotion, mouseEventArgs );
}

//=================================================================================================
void eve::evt::notify_mouse_event( const eve::evt::MouseEventArgs & p_args )
{
	switch( p_args.type )
	{
	case eve::evt::MouseEventArgs::PassiveMotion:
		eve::evt::notify_mouse_passive_motion( p_args.x, p_args.y );
		break;

	case eve::evt::MouseEventArgs::Motion:
		eve::evt::notify_mouse_motion( p_args.x, p_args.y );
		break;

	case eve::evt::MouseEventArgs::Pressed:
		eve::evt::notify_mouse_down( p_args.button, p_args.x, p_args.y );
		break;

	case eve::evt::MouseEventArgs::Released:
		eve::evt::notify_mouse_up( p_args.button, p_args.x, p_args.y );
		break;

	case eve::evt::MouseEventArgs::DoubleClick:
		eve::evt::notify_mouse_double_click( p_args.button, p_args.x, p_args.y );
		break;
	}
}



//=================================================================================================
void eve::evt::notify_window_resize( uint32_t p_width, uint32_t p_height )
{
	static eve::evt::ResizeEventArgs resizeEventArgs;

	resizeEventArgs.width  = p_width;
	resizeEventArgs.height = p_height;
	eve::evt::notify_event( CoreEvents::windowResized, resizeEventArgs );
}

//=================================================================================================
void eve::evt::notify_window_resize_event( const eve::evt::ResizeEventArgs & p_args )
{
	eve::evt::notify_window_resize( p_args.width, p_args.height );
}



//=================================================================================================
void eve::evt::notify_focus_got( void )
{
	static eve::evt::Args args;
	eve::evt::notify_event( CoreEvents::focusGot );
}

//=================================================================================================
void eve::evt::notify_focus_lost( void )
{
	eve::evt::notify_event( CoreEvents::focusLost );
}



//=================================================================================================
void eve::evt::notify_idle( void )
{
	eve::evt::notify_event( CoreEvents::idle );
}



//=================================================================================================
void eve::evt::notify_display( void )
{
	eve::evt::notify_event( CoreEvents::display );
}



//=================================================================================================
void eve::evt::notify_close( void )
{
	eve::evt::notify_event( CoreEvents::close );
}



//=================================================================================================
void eve::evt::notify_app_exit( void )
{
	eve::evt::notify_event( CoreEvents::applicationExit );
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		EventListenner class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::evt::EventListenner::EventListenner(void)
{}

//=================================================================================================
eve::evt::EventListenner::~EventListenner(void)
{}

//=================================================================================================
void eve::evt::EventListenner::newControlEventMessage( eve::evt::controlEventArgs & p_eventArgs)
{}

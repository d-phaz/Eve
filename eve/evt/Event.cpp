
// Main header
#include "evt/Event.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//		KEY EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

eve::evt::TEvent<eve::evt::KeyEventArgs> 		keyPressed;			
eve::evt::TEvent<eve::evt::KeyEventArgs> 		keyReleased;		
eve::evt::TEvent<eve::evt::KeyEventArgs> 		keyInput;			

//=================================================================================================
void eve::evt::enable_events_key(void)
{
	eve::evt::keyPressed.enable();
	eve::evt::keyReleased.enable();
	eve::evt::keyInput.enable();
}

//=================================================================================================
void disable_events_key(void)
{
	eve::evt::keyPressed.disable();
	eve::evt::keyReleased.disable();
	eve::evt::keyInput.disable();
}



//=================================================================================================
void eve::evt::notify_key_pressed(uint8_t p_key)
{
	static eve::evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = p_key;
	eve::evt::notify_event(eve::evt::keyPressed, keyEventArgs);
}

//=================================================================================================
void eve::evt::notify_key_released(uint8_t p_key)
{
	static eve::evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = p_key;
	eve::evt::notify_event(eve::evt::keyReleased, keyEventArgs);
}

//=================================================================================================
void eve::evt::notify_key_input( uint8_t p_key )
{
	static eve::evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = p_key;
	eve::evt::notify_event(eve::evt::keyInput, keyEventArgs);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		MOUSE EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

eve::evt::TEvent<eve::evt::MouseEventArgs> 		mousePassiveMotion;	
eve::evt::TEvent<eve::evt::MouseEventArgs> 		mouseMotion;		
eve::evt::TEvent<eve::evt::MouseEventArgs> 		mouseDown;			
eve::evt::TEvent<eve::evt::MouseEventArgs>		mouseDoubleClick;	
eve::evt::TEvent<eve::evt::MouseEventArgs> 		mouseUp;			

//=================================================================================================
void eve::evt::enable_events_mouse(void)
{
	eve::evt::mousePassiveMotion.enable();		
	eve::evt::mouseMotion.enable();
	eve::evt::mouseDown.enable();
	eve::evt::mouseDoubleClick.enable();
	eve::evt::mouseUp.enable();
}

//=================================================================================================
void eve::evt::disable_events_mouse(void)
{
	eve::evt::mousePassiveMotion.disable();
	eve::evt::mouseMotion.disable();
	eve::evt::mouseDown.disable();
	eve::evt::mouseDoubleClick.disable();
	eve::evt::mouseUp.disable();
}



//=================================================================================================
void eve::evt::notify_mouse_down( int32_t p_button, int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= p_button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	eve::evt::notify_event(eve::evt::mouseDown, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_up( int32_t p_button, int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= p_button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	eve::evt::notify_event(eve::evt::mouseUp, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_double_click( int32_t p_button, int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= p_button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	eve::evt::notify_event(eve::evt::mouseDoubleClick, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_motion( int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	eve::evt::notify_event(eve::evt::mouseMotion, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_passive_motion( int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.x = x;
	mouseEventArgs.y = y;
	eve::evt::notify_event(eve::evt::mousePassiveMotion, mouseEventArgs);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		TOUCH EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

eve::evt::TEvent<eve::evt::TouchEventArgs>		touchDown;			
eve::evt::TEvent<eve::evt::TouchEventArgs>		touchUp;			
eve::evt::TEvent<eve::evt::TouchEventArgs>		touchDoubleTap;		
eve::evt::TEvent<eve::evt::TouchEventArgs>		touchMoved;			
eve::evt::TEvent<eve::evt::TouchEventArgs>		touchCanceled;		

//=================================================================================================
void eve::evt::enable_events_touch(void)
{
	eve::evt::touchDown.enable();
	eve::evt::touchUp.enable();
	eve::evt::touchDoubleTap.enable();
	eve::evt::touchMoved.enable();
	eve::evt::touchCanceled.enable();
}

//=================================================================================================
void eve::evt::disable_events_touch(void)
{
	eve::evt::touchDown.disable();
	eve::evt::touchUp.disable();
	eve::evt::touchDoubleTap.disable();
	eve::evt::touchMoved.disable();
	eve::evt::touchCanceled.disable();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		WINDOW EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

eve::evt::TEvent<eve::evt::ResizeEventArgs> 	windowResized;		
eve::evt::TEvent<void>							windowFocusGot;		
eve::evt::TEvent<void>							windowFocusLost;	
eve::evt::TEvent<void>							windowClose;		

//=================================================================================================
void eve::evt::enable_events_window(void)
{
	eve::evt::windowResized.enable();
	eve::evt::windowFocusGot.enable();
	eve::evt::windowFocusLost.enable();
	eve::evt::windowClose.enable();
}

//=================================================================================================
void eve::evt::disable_events_window(void)
{
	eve::evt::windowResized.disable();
	eve::evt::windowFocusGot.disable();
	eve::evt::windowFocusLost.disable();
	eve::evt::windowClose.disable();
}



//=================================================================================================
void eve::evt::notify_window_resize(uint32_t p_width, uint32_t p_height)
{
	static eve::evt::ResizeEventArgs resizeEventArgs;

	resizeEventArgs.width  = p_width;
	resizeEventArgs.height = p_height;
	eve::evt::notify_event(eve::evt::windowResized, resizeEventArgs);
}

//=================================================================================================
void eve::evt::notify_window_focus_got(void)
{
	eve::evt::notify_event(eve::evt::windowFocusGot);
}

//=================================================================================================
void eve::evt::notify_window_focus_lost(void)
{
	eve::evt::notify_event(eve::evt::windowFocusLost);
}

//=================================================================================================
void eve::evt::notify_window_close(void)
{
	eve::evt::notify_event(eve::evt::windowClose);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		APPLICATION EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

eve::evt::TEvent<void>							appExit;			

//=================================================================================================
void eve::evt::enable_events_application(void)
{
	eve::evt::appExit.enable();
}

//=================================================================================================
void eve::evt::disable_events_application(void)
{
	eve::evt::appExit.disable();
}



//=================================================================================================
void eve::evt::notify_application_exit(void)
{
	eve::evt::notify_event(eve::evt::appExit);
}

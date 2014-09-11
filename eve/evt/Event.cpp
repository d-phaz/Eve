
// Main header
#include "evt/Event.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//		KEY EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

eve::evt::TEvent<eve::evt::KeyEventArgs> 		eve::evt::EvtKey::keyPressed;
eve::evt::TEvent<eve::evt::KeyEventArgs> 		eve::evt::EvtKey::keyReleased;
eve::evt::TEvent<eve::evt::KeyEventArgs> 		eve::evt::EvtKey::keyInput;

//=================================================================================================
void eve::evt::enable_events_key(void)
{
	eve::evt::EvtKey::keyPressed.enable();
	eve::evt::EvtKey::keyReleased.enable();
	eve::evt::EvtKey::keyInput.enable();
}

//=================================================================================================
void disable_events_key(void)
{
	eve::evt::EvtKey::keyPressed.disable();
	eve::evt::EvtKey::keyReleased.disable();
	eve::evt::EvtKey::keyInput.disable();
}



//=================================================================================================
void eve::evt::notify_key_pressed(uint8_t p_key)
{
	static eve::evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = p_key;
	eve::evt::notify_event(eve::evt::EvtKey::keyPressed, keyEventArgs);
}

//=================================================================================================
void eve::evt::notify_key_released(uint8_t p_key)
{
	static eve::evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = p_key;
	eve::evt::notify_event(eve::evt::EvtKey::keyReleased, keyEventArgs);
}

//=================================================================================================
void eve::evt::notify_key_input( uint8_t p_key )
{
	static eve::evt::KeyEventArgs keyEventArgs;

	keyEventArgs.key = p_key;
	eve::evt::notify_event(eve::evt::EvtKey::keyInput, keyEventArgs);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		MOUSE EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

eve::evt::TEvent<eve::evt::MouseEventArgs> 		eve::evt::EvtMouse::mousePassiveMotion;
eve::evt::TEvent<eve::evt::MouseEventArgs> 		eve::evt::EvtMouse::mouseMotion;
eve::evt::TEvent<eve::evt::MouseEventArgs> 		eve::evt::EvtMouse::mouseDown;
eve::evt::TEvent<eve::evt::MouseEventArgs>		eve::evt::EvtMouse::mouseDoubleClick;
eve::evt::TEvent<eve::evt::MouseEventArgs> 		eve::evt::EvtMouse::mouseUp;

//=================================================================================================
void eve::evt::enable_events_mouse(void)
{
	eve::evt::EvtMouse::mousePassiveMotion.enable();
	eve::evt::EvtMouse::mouseMotion.enable();
	eve::evt::EvtMouse::mouseDown.enable();
	eve::evt::EvtMouse::mouseDoubleClick.enable();
	eve::evt::EvtMouse::mouseUp.enable();
}

//=================================================================================================
void eve::evt::disable_events_mouse(void)
{
	eve::evt::EvtMouse::mousePassiveMotion.disable();
	eve::evt::EvtMouse::mouseMotion.disable();
	eve::evt::EvtMouse::mouseDown.disable();
	eve::evt::EvtMouse::mouseDoubleClick.disable();
	eve::evt::EvtMouse::mouseUp.disable();
}



//=================================================================================================
void eve::evt::notify_mouse_down( int32_t p_button, int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= p_button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	eve::evt::notify_event(eve::evt::EvtMouse::mouseDown, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_up( int32_t p_button, int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= p_button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	eve::evt::notify_event(eve::evt::EvtMouse::mouseUp, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_double_click( int32_t p_button, int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.button	= p_button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	eve::evt::notify_event(eve::evt::EvtMouse::mouseDoubleClick, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_motion( int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;
	eve::evt::notify_event(eve::evt::EvtMouse::mouseMotion, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_passive_motion( int32_t x, int32_t y )
{
	static eve::evt::MouseEventArgs mouseEventArgs;

	mouseEventArgs.x = x;
	mouseEventArgs.y = y;
	eve::evt::notify_event(eve::evt::EvtMouse::mousePassiveMotion, mouseEventArgs);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		TOUCH EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

eve::evt::TEvent<eve::evt::TouchEventArgs>		eve::evt::EvtTouch::touchDown;
eve::evt::TEvent<eve::evt::TouchEventArgs>		eve::evt::EvtTouch::touchUp;
eve::evt::TEvent<eve::evt::TouchEventArgs>		eve::evt::EvtTouch::touchDoubleTap;
eve::evt::TEvent<eve::evt::TouchEventArgs>		eve::evt::EvtTouch::touchMoved;
eve::evt::TEvent<eve::evt::TouchEventArgs>		eve::evt::EvtTouch::touchCanceled;

//=================================================================================================
void eve::evt::enable_events_touch(void)
{
	eve::evt::EvtTouch::touchDown.enable();
	eve::evt::EvtTouch::touchUp.enable();
	eve::evt::EvtTouch::touchDoubleTap.enable();
	eve::evt::EvtTouch::touchMoved.enable();
	eve::evt::EvtTouch::touchCanceled.enable();
}

//=================================================================================================
void eve::evt::disable_events_touch(void)
{
	eve::evt::EvtTouch::touchDown.disable();
	eve::evt::EvtTouch::touchUp.disable();
	eve::evt::EvtTouch::touchDoubleTap.disable();
	eve::evt::EvtTouch::touchMoved.disable();
	eve::evt::EvtTouch::touchCanceled.disable();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		WINDOW EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

eve::evt::TEvent<eve::evt::ResizeEventArgs> 	eve::evt::EvtWindow::windowResized;
eve::evt::TEvent<void>							eve::evt::EvtWindow::windowFocusGot;
eve::evt::TEvent<void>							eve::evt::EvtWindow::windowFocusLost;
eve::evt::TEvent<void>							eve::evt::EvtWindow::windowClose;

//=================================================================================================
void eve::evt::enable_events_window(void)
{
	eve::evt::EvtWindow::windowResized.enable();
	eve::evt::EvtWindow::windowFocusGot.enable();
	eve::evt::EvtWindow::windowFocusLost.enable();
	eve::evt::EvtWindow::windowClose.enable();
}

//=================================================================================================
void eve::evt::disable_events_window(void)
{
	eve::evt::EvtWindow::windowResized.disable();
	eve::evt::EvtWindow::windowFocusGot.disable();
	eve::evt::EvtWindow::windowFocusLost.disable();
	eve::evt::EvtWindow::windowClose.disable();
}



//=================================================================================================
void eve::evt::notify_window_resize(uint32_t p_width, uint32_t p_height)
{
	static eve::evt::ResizeEventArgs resizeEventArgs;

	resizeEventArgs.width  = p_width;
	resizeEventArgs.height = p_height;
	eve::evt::notify_event(eve::evt::EvtWindow::windowResized, resizeEventArgs);
}

//=================================================================================================
void eve::evt::notify_window_focus_got(void)
{
	eve::evt::notify_event(eve::evt::EvtWindow::windowFocusGot);
}

//=================================================================================================
void eve::evt::notify_window_focus_lost(void)
{
	eve::evt::notify_event(eve::evt::EvtWindow::windowFocusLost);
}

//=================================================================================================
void eve::evt::notify_window_close(void)
{
	eve::evt::notify_event(eve::evt::EvtWindow::windowClose);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		APPLICATION EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

eve::evt::TEvent<void>							eve::evt::EvtApp::appExit;

//=================================================================================================
void eve::evt::enable_events_application(void)
{
	eve::evt::EvtApp::appExit.enable();
}

//=================================================================================================
void eve::evt::disable_events_application(void)
{
	eve::evt::EvtApp::appExit.disable();
}



//=================================================================================================
void eve::evt::notify_application_exit(void)
{
	eve::evt::notify_event(eve::evt::EvtApp::appExit);
}

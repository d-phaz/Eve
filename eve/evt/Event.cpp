
/*
 Copyright (c) 2014, The eve Project
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of the {organization} nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Main header
#include "eve/evt/Event.h"

#ifndef __EVE_APPLICATION_APP_H__
#include "eve/app/App.h"
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
//		COMMON
////////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::evt::EventArgs::EventArgs(void)
	: time(EveAppElapsedTime)
{}

//=================================================================================================
eve::evt::EventArgs::EventArgs(const eve::evt::EventArgs & p_other)
	: time(p_other.time)
{}

//=================================================================================================
eve::evt::EventArgs & eve::evt::EventArgs::operator = (const eve::evt::EventArgs & p_other)
{
	this->time = p_other.time;
	return *this;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//		FILE EVENTS
////////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::evt::FileEventArgs::FileEventArgs(void)
	: eve::evt::EventArgs()
	, x(0)
	, y(0)
	, count(0)
	, files()
{}

//=================================================================================================
eve::evt::FileEventArgs::FileEventArgs(const eve::evt::FileEventArgs & p_other)
	: eve::evt::EventArgs(p_other)
	, x(p_other.x)
	, y(p_other.y)
	, count(p_other.count)
	, files(p_other.files)
{}

//=================================================================================================
eve::evt::FileEventArgs & eve::evt::FileEventArgs::operator = (const eve::evt::FileEventArgs & p_other)
{
	this->time	= p_other.time;
	this->x		= p_other.x;
	this->y		= p_other.y;
	this->count = p_other.count;
	this->files = p_other.files;
	return *this;
}



//=================================================================================================
eve::evt::FileEvent		eve::evt::EvtFile::fileDropped;

//=================================================================================================
void eve::evt::enable_events_file(void)
{
	eve::evt::EvtFile::fileDropped.enable();
}

//=================================================================================================
void eve::evt::disable_events_file(void)
{
	eve::evt::EvtFile::fileDropped.disable();
}



//=================================================================================================
void eve::evt::notify_file_dropped(int32_t p_x, int32_t p_y, uint32_t p_count, std::vector<std::wstring> & p_files)
{
	eve::evt::FileEventArgs fileEventArgs;
	fileEventArgs.x = p_x;
	fileEventArgs.y = p_y;
	fileEventArgs.count = p_count;
	fileEventArgs.files = p_files;

	eve::evt::notify_event(eve::evt::EvtFile::fileDropped, fileEventArgs);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		KEY EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::evt::KeyEventArgs::KeyEventArgs(void)
	: eve::evt::EventArgs()
	, key(0)
{}

//=================================================================================================
eve::evt::KeyEventArgs::KeyEventArgs(const eve::evt::KeyEventArgs & p_other)
	: eve::evt::EventArgs(p_other)
	, key(p_other.key)
{}

//=================================================================================================
eve::evt::KeyEventArgs & eve::evt::KeyEventArgs::operator = (const eve::evt::KeyEventArgs & p_other)
{
	this->time	= p_other.time;
	this->key	= p_other.key;
	return *this;
}



//=================================================================================================
eve::evt::KeyEvent 		eve::evt::EvtKey::keyPressed;
eve::evt::KeyEvent 		eve::evt::EvtKey::keyReleased;
eve::evt::KeyEvent 		eve::evt::EvtKey::keyInput;

//=================================================================================================
void eve::evt::enable_events_key(void)
{
	eve::evt::EvtKey::keyPressed.enable();
	eve::evt::EvtKey::keyReleased.enable();
	eve::evt::EvtKey::keyInput.enable();
}

//=================================================================================================
void eve::evt::disable_events_key(void)
{
	eve::evt::EvtKey::keyPressed.disable();
	eve::evt::EvtKey::keyReleased.disable();
	eve::evt::EvtKey::keyInput.disable();
}



//=================================================================================================
void eve::evt::notify_key_pressed(uint8_t p_key)
{
	eve::evt::KeyEventArgs keyEventArgs;
	keyEventArgs.key = p_key;

	eve::evt::notify_event(eve::evt::EvtKey::keyPressed, keyEventArgs);
}

//=================================================================================================
void eve::evt::notify_key_released(uint8_t p_key)
{
	eve::evt::KeyEventArgs keyEventArgs;
	keyEventArgs.key = p_key;

	eve::evt::notify_event(eve::evt::EvtKey::keyReleased, keyEventArgs);
}

//=================================================================================================
void eve::evt::notify_key_input( uint8_t p_key )
{
	eve::evt::KeyEventArgs keyEventArgs;
	keyEventArgs.key = p_key;

	eve::evt::notify_event(eve::evt::EvtKey::keyInput, keyEventArgs);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		MOUSE EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::evt::MouseEventArgs::MouseEventArgs(void)
	: eve::evt::EventArgs()
	, x(0)
	, y(0)
	, button(0)
{}

//=================================================================================================
eve::evt::MouseEventArgs::MouseEventArgs(const eve::evt::MouseEventArgs & p_other)
	: eve::evt::EventArgs(p_other)
	, x(p_other.x)
	, y(p_other.y)
	, button(p_other.button)
{}

//=================================================================================================
eve::evt::MouseEventArgs & eve::evt::MouseEventArgs::operator = (const eve::evt::MouseEventArgs & p_other)
{
	this->time		= p_other.time;
	this->x			= p_other.x;
	this->y			= p_other.y;
	this->button		= p_other.button;
	return *this;
}



//=================================================================================================
eve::evt::MouseEvent 		eve::evt::EvtMouse::mousePassiveMotion;
eve::evt::MouseEvent 		eve::evt::EvtMouse::mouseMotion;
eve::evt::MouseEvent 		eve::evt::EvtMouse::mouseDown;
eve::evt::MouseEvent		eve::evt::EvtMouse::mouseDoubleClick;
eve::evt::MouseEvent 		eve::evt::EvtMouse::mouseUp;

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
	eve::evt::MouseEventArgs mouseEventArgs;
	mouseEventArgs.button	= p_button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;

	eve::evt::notify_event(eve::evt::EvtMouse::mouseDown, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_up( int32_t p_button, int32_t x, int32_t y )
{
	eve::evt::MouseEventArgs mouseEventArgs;
	mouseEventArgs.button	= p_button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;

	eve::evt::notify_event(eve::evt::EvtMouse::mouseUp, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_double_click( int32_t p_button, int32_t x, int32_t y )
{
	eve::evt::MouseEventArgs mouseEventArgs;
	mouseEventArgs.button	= p_button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;

	eve::evt::notify_event(eve::evt::EvtMouse::mouseDoubleClick, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_motion(int32_t p_button, int32_t x, int32_t y)
{
	eve::evt::MouseEventArgs mouseEventArgs;
	mouseEventArgs.button	= p_button;
	mouseEventArgs.x		= x;
	mouseEventArgs.y		= y;

	eve::evt::notify_event(eve::evt::EvtMouse::mouseMotion, mouseEventArgs);
}

//=================================================================================================
void eve::evt::notify_mouse_passive_motion(int32_t x, int32_t y)
{
	eve::evt::MouseEventArgs mouseEventArgs;
	mouseEventArgs.x = x;
	mouseEventArgs.y = y;
	
	eve::evt::notify_event(eve::evt::EvtMouse::mousePassiveMotion, mouseEventArgs);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		TOUCH EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::evt::TouchEventArgs::TouchEventArgs(void)
	: eve::evt::EventArgs()
	, type(eve::evt::TouchEventArgs::Type::unknown)
	, id(0)
	, duration(0)
	, numTouches(0)
	, width(0.0f)
	, height(0.0f)
	, angle(0.0f)
	, minoraxis(0.0f)
	, majoraxis(0.0f)
	, pressure(0.0f)
	, xspeed(0.0f)
	, yspeed(0.0f)
	, xaccel(0.0f)
	, yaccel(0.0f)
{}

//=================================================================================================
eve::evt::TouchEventArgs::TouchEventArgs(const eve::evt::TouchEventArgs & p_other)
	: eve::evt::EventArgs(p_other)
	, type(p_other.type)
	, id(p_other.id)
	, duration(p_other.duration)
	, numTouches(p_other.numTouches)
	, width(p_other.width)
	, height(p_other.height)
	, angle(p_other.angle)
	, minoraxis(p_other.minoraxis)
	, majoraxis(p_other.majoraxis)
	, pressure(p_other.pressure)
	, xspeed(p_other.xspeed)
	, yspeed(p_other.yspeed)
	, xaccel(p_other.xaccel)
	, yaccel(p_other.yaccel)
{}

//=================================================================================================
eve::evt::TouchEventArgs & eve::evt::TouchEventArgs::operator = (const eve::evt::TouchEventArgs & p_other)
{
	this->time			= p_other.time;
	this->type			= p_other.type;
	this->id				= p_other.id;
	this->duration		= p_other.duration;
	this->numTouches		= p_other.numTouches;
	this->width			= p_other.width;
	this->height			= p_other.height;
	this->angle			= p_other.angle;
	this->minoraxis		= p_other.minoraxis;
	this->majoraxis		= p_other.majoraxis;
	this->pressure		= p_other.pressure;
	this->xspeed			= p_other.xspeed;
	this->yspeed			= p_other.yspeed;
	this->xaccel			= p_other.xaccel;
	this->yaccel			= p_other.yaccel;
	return *this;
}

eve::evt::TouchEvent		eve::evt::EvtTouch::touchDown;
eve::evt::TouchEvent		eve::evt::EvtTouch::touchUp;
eve::evt::TouchEvent		eve::evt::EvtTouch::touchDoubleTap;
eve::evt::TouchEvent		eve::evt::EvtTouch::touchMoved;
eve::evt::TouchEvent		eve::evt::EvtTouch::touchCanceled;

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

//=================================================================================================
eve::evt::ResizeEventArgs::ResizeEventArgs(void)
	: eve::evt::EventArgs()
	, width(0)
	, height(0)
{}

//=================================================================================================
eve::evt::ResizeEventArgs::ResizeEventArgs(const eve::evt::ResizeEventArgs & p_other)
	: eve::evt::EventArgs(p_other)
	, width(p_other.width)
	, height(p_other.height)
{}

//=================================================================================================
eve::evt::ResizeEventArgs & eve::evt::ResizeEventArgs::operator = (const eve::evt::ResizeEventArgs & p_other)
{
	this->time		= p_other.time;
	this->width		= p_other.width;
	this->height		= p_other.height;
	return *this;
}




//=================================================================================================
eve::evt::MoveEventArgs::MoveEventArgs(void)
	: x(0)
	, y(0)
{}

//=================================================================================================
eve::evt::MoveEventArgs::MoveEventArgs(const eve::evt::MoveEventArgs & p_other)
	: x(p_other.x)
	, y(p_other.y)
{}

//=================================================================================================
eve::evt::MoveEventArgs & eve::evt::MoveEventArgs::operator = (const eve::evt::MoveEventArgs & p_other)
{
	this->x  = p_other.x;
	this->y = p_other.y;
	return *this;
}



//=================================================================================================
eve::evt::TEvent<eve::evt::ResizeEventArgs> 	eve::evt::EvtWindow::windowResized;
eve::evt::TEvent<eve::evt::MoveEventArgs> 		eve::evt::EvtWindow::windowMoved;
eve::evt::TEvent<eve::evt::EventArgs>			eve::evt::EvtWindow::windowClose;
eve::evt::TEvent<eve::evt::EventArgs>			eve::evt::EvtWindow::windowFocusGot;
eve::evt::TEvent<eve::evt::EventArgs>			eve::evt::EvtWindow::windowFocusLost;

//=================================================================================================
void eve::evt::enable_events_window(void)
{
	eve::evt::EvtWindow::windowResized.enable();
	eve::evt::EvtWindow::windowMoved.enable();
	eve::evt::EvtWindow::windowFocusGot.enable();
	eve::evt::EvtWindow::windowFocusLost.enable();
	eve::evt::EvtWindow::windowClose.enable();
}

//=================================================================================================
void eve::evt::disable_events_window(void)
{
	eve::evt::EvtWindow::windowResized.disable();
	eve::evt::EvtWindow::windowMoved.disable();
	eve::evt::EvtWindow::windowFocusGot.disable();
	eve::evt::EvtWindow::windowFocusLost.disable();
	eve::evt::EvtWindow::windowClose.disable();
}



//=================================================================================================
void eve::evt::notify_window_resize(int32_t p_width, int32_t p_height)
{
	eve::evt::ResizeEventArgs resizeEventArgs;
	resizeEventArgs.width  = p_width;
	resizeEventArgs.height = p_height;

	eve::evt::notify_event(eve::evt::EvtWindow::windowResized, resizeEventArgs);
}

//=================================================================================================
void notify_window_move(int32_t p_x, int32_t p_y)
{
	eve::evt::MoveEventArgs moveEventArgs;
	moveEventArgs.x = p_x;
	moveEventArgs.y = p_y;

	eve::evt::notify_event(eve::evt::EvtWindow::windowMoved, moveEventArgs);
}

//=================================================================================================
void eve::evt::notify_window_focus_got(void)
{
	eve::evt::EventArgs args;
	eve::evt::notify_event(eve::evt::EvtWindow::windowFocusGot, args);
}

//=================================================================================================
void eve::evt::notify_window_focus_lost(void)
{
	eve::evt::EventArgs args;
	eve::evt::notify_event(eve::evt::EvtWindow::windowFocusLost, args);
}

//=================================================================================================
void eve::evt::notify_window_close(void)
{
	eve::evt::EventArgs args;
	eve::evt::notify_event(eve::evt::EvtWindow::windowClose, args);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		TIME EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::evt::TEvent<eve::evt::EventArgs> eve::evt::EvtTime::newTime;

//=================================================================================================
void eve::evt::enable_events_time(void)
{
	eve::evt::EvtTime::newTime.enable();
}

//=================================================================================================
void eve::evt::disable_events_time(void)
{
	eve::evt::EvtTime::newTime.disable();
}



//=================================================================================================
void eve::evt::notify_time(int64_t p_time)
{
	eve::evt::EventArgs args;

	eve::evt::notify_event(eve::evt::EvtTime::newTime, args);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		FRAME EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::evt::FrameEventArgs::FrameEventArgs(void)
	: eve::evt::EventArgs()
	, frame(0)
{}

//=================================================================================================
eve::evt::FrameEventArgs::FrameEventArgs(const eve::evt::FrameEventArgs & p_other)
	: eve::evt::EventArgs(p_other)
	, frame(p_other.frame)
{}

//=================================================================================================
eve::evt::FrameEventArgs & eve::evt::FrameEventArgs::operator = (const eve::evt::FrameEventArgs & p_other)
{
	this->time	= p_other.time;
	this->frame = p_other.frame;
	return *this;
}



//=================================================================================================
eve::evt::TEvent<eve::evt::FrameEventArgs> eve::evt::EvtFrame::newFrame;

//=================================================================================================
void eve::evt::enable_events_frame(void)
{
	eve::evt::EvtFrame::newFrame.enable();
}

//=================================================================================================
void eve::evt::disable_events_frame(void)
{
	eve::evt::EvtFrame::newFrame.disable();
}



//=================================================================================================
void eve::evt::notify_frame(int64_t p_frame)
{
	eve::evt::FrameEventArgs args;
	args.frame = p_frame;

	eve::evt::notify_event(eve::evt::EvtFrame::newFrame, args);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		APPLICATION EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::evt::TEvent<eve::evt::EventArgs>					eve::evt::EvtApp::appExit;

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
	eve::evt::EventArgs args;
	eve::evt::notify_event(eve::evt::EvtApp::appExit, args);
}

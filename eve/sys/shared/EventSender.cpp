
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
#include "eve/sys/shared/EventSender.h"


//=================================================================================================
eve::sys::EventSender::EventSender(void)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_fileDropped()

	, m_keyPressed()
	, m_keyReleased()
	, m_textInput()
	
	, m_mousePassiveMotion()
	, m_mouseMotion()
	, m_mouseDown()
	, m_mouseWheel()
	, m_mouseDoubleClick()
	, m_mouseUp()
	
	, m_windowResized()
	, m_windowMoved()
	, m_windowFocusGot()
	, m_windowFocusLost()
	, m_windowClose()
{}


//=================================================================================================
void eve::sys::EventSender::init(void)
{
	this->enableEvents();
}

//=================================================================================================
void eve::sys::EventSender::release(void)
{
	this->disableEvents();
}



//=================================================================================================
void eve::sys::EventSender::enableEventsFile(void)
{
	m_fileDropped.enable();
}

//=================================================================================================
void eve::sys::EventSender::disableEventsFile(void)
{
	m_fileDropped.disable();
}

//=================================================================================================
void eve::sys::EventSender::notifyFileDropped(int32_t p_x, int32_t p_y, uint32_t p_count, std::vector<std::wstring> & p_files)
{
	eve::evt::FileEventArgs fileEventArgs;
	fileEventArgs.x		= p_x;
	fileEventArgs.y		= p_y;
	fileEventArgs.count = p_count;
	fileEventArgs.files = p_files;

	eve::evt::notify_event(m_fileDropped, fileEventArgs);
}



//=================================================================================================
void eve::sys::EventSender::enableEventsKey(void)
{
	m_keyPressed.enable();
	m_keyReleased.enable();
}

//=================================================================================================
void eve::sys::EventSender::disableEventsKey(void)
{
	m_keyPressed.disable();
	m_keyReleased.disable();
}

//=================================================================================================
void eve::sys::EventSender::notifyKeyPressed(eve::sys::Key p_key, eve::sys::KeyModifier p_modifier, bool p_bRepeat)
{
	eve::evt::KeyEventArgs keyEventArgs;
	keyEventArgs.key	  = p_key;
	keyEventArgs.modifier = p_modifier;
	keyEventArgs.repeat	  = p_bRepeat;

	eve::evt::notify_event(m_keyPressed, keyEventArgs);
}

//=================================================================================================
void eve::sys::EventSender::notifyKeyReleased(eve::sys::Key p_key, eve::sys::KeyModifier p_modifier)
{
	eve::evt::KeyEventArgs keyEventArgs;
	keyEventArgs.key	  = p_key;
	keyEventArgs.modifier = p_modifier;

	eve::evt::notify_event(m_keyReleased, keyEventArgs);
}



//=================================================================================================
void eve::sys::EventSender::enableEventsText(void)
{
	m_textInput.enable();
}

//=================================================================================================
void eve::sys::EventSender::disableEventsText(void)
{
	m_textInput.disable();
}

//=================================================================================================
void eve::sys::EventSender::notifyTextInput(wchar_t p_text, eve::sys::KeyModifier p_modifier, bool p_bRepeat)
{
	eve::evt::TextEventArgs args;
	args.text	  = p_text;
	args.modifier = p_modifier;
	args.repeat	  = p_bRepeat;

	eve::evt::notify_event(m_textInput, args);
}



//=================================================================================================
void eve::sys::EventSender::enableEventsMouse(void)
{
	m_mousePassiveMotion.enable();
	m_mouseMotion.enable();
	m_mouseDown.enable();
	m_mouseWheel.enable();
	m_mouseDoubleClick.enable();
	m_mouseUp.enable();
}

//=================================================================================================
void eve::sys::EventSender::disableEventsMouse(void)
{
	m_mousePassiveMotion.disable();
	m_mouseMotion.disable();
	m_mouseDown.disable();
	m_mouseWheel.disable();
	m_mouseDoubleClick.disable();
	m_mouseUp.disable();
}

//=================================================================================================
void eve::sys::EventSender::notifyMouseDown(int32_t p_button, int32_t x, int32_t y)
{
	eve::evt::MouseEventArgs mouseEventArgs;
	mouseEventArgs.button = p_button;
	mouseEventArgs.x = x;
	mouseEventArgs.y = y;

	eve::evt::notify_event(m_mouseDown, mouseEventArgs);
}

//=================================================================================================
void eve::sys::EventSender::notifyMouseWheel(int32_t p_button, int32_t x, int32_t y)
{
	eve::evt::MouseEventArgs mouseEventArgs;
	mouseEventArgs.button = p_button;
	mouseEventArgs.x = x;
	mouseEventArgs.y = y;

	eve::evt::notify_event(m_mouseWheel, mouseEventArgs);
}

//=================================================================================================
void eve::sys::EventSender::notifyMouseUp(int32_t p_button, int32_t x, int32_t y)
{
	eve::evt::MouseEventArgs mouseEventArgs;
	mouseEventArgs.button = p_button;
	mouseEventArgs.x = x;
	mouseEventArgs.y = y;

	eve::evt::notify_event(m_mouseUp, mouseEventArgs);
}

//=================================================================================================
void eve::sys::EventSender::notifyMouseDoubleClick(int32_t p_button, int32_t x, int32_t y)
{
	eve::evt::MouseEventArgs mouseEventArgs;
	mouseEventArgs.button = p_button;
	mouseEventArgs.x = x;
	mouseEventArgs.y = y;

	eve::evt::notify_event(m_mouseDoubleClick, mouseEventArgs);
}

//=================================================================================================
void eve::sys::EventSender::notifyMouseMotion(int32_t p_button, int32_t x, int32_t y)
{
	eve::evt::MouseEventArgs mouseEventArgs;
	mouseEventArgs.button = p_button;
	mouseEventArgs.x = x;
	mouseEventArgs.y = y;

	eve::evt::notify_event(m_mouseMotion, mouseEventArgs);
}

//=================================================================================================
void eve::sys::EventSender::notifyMousePassiveMotion(int32_t x, int32_t y)
{
	eve::evt::MouseEventArgs mouseEventArgs;
	mouseEventArgs.x = x;
	mouseEventArgs.y = y;

	eve::evt::notify_event(m_mousePassiveMotion, mouseEventArgs);
}



//=================================================================================================
void eve::sys::EventSender::enableEventsWindow(void)
{
	m_windowResized.enable();
	m_windowMoved.enable();
	m_windowFocusGot.enable();
	m_windowFocusLost.enable();
	m_windowClose.enable();
}

//=================================================================================================
void eve::sys::EventSender::disableEventsWindow(void)
{
	m_windowResized.disable();
	m_windowMoved.disable();
	m_windowFocusGot.disable();
	m_windowFocusLost.disable();
	m_windowClose.disable();
}

//=================================================================================================
void eve::sys::EventSender::notifyWindowResize(uint32_t p_width, uint32_t p_height)
{
	eve::evt::ResizeEventArgs resizeEventArgs;
	resizeEventArgs.width = p_width;
	resizeEventArgs.height = p_height;

	eve::evt::notify_event(m_windowResized, resizeEventArgs);
}

//=================================================================================================
void  eve::sys::EventSender::notifyWindowMove(int32_t p_x, int32_t p_y)
{
	eve::evt::MoveEventArgs moveEventArgs;
	moveEventArgs.x = p_x;
	moveEventArgs.y = p_y;

	eve::evt::notify_event(m_windowMoved, moveEventArgs);
}

//=================================================================================================
void eve::sys::EventSender::notifyWindowFocusGot(void)
{
	eve::evt::EventArgs args;
	eve::evt::notify_event(m_windowFocusGot, args);
}

//=================================================================================================
void eve::sys::EventSender::notifyWindowFocusLost(void)
{
	eve::evt::EventArgs args;
	eve::evt::notify_event(m_windowFocusLost, args);
}

//=================================================================================================
void eve::sys::EventSender::notifyWindowClose(void)
{
	eve::evt::EventArgs args;
	eve::evt::notify_event(m_windowClose, args);
}



//=================================================================================================
void eve::sys::EventSender::enableEvents(void)
{
	this->enableEventsFile();
	this->enableEventsKey();
	this->enableEventsMouse();
	this->enableEventsWindow();
}

//=================================================================================================
void eve::sys::EventSender::disableEvents(void)
{
	this->disableEventsFile();
	this->disableEventsKey();
	this->disableEventsMouse();
	this->disableEventsWindow();
}

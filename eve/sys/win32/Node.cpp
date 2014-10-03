
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

// Main class header
#include "eve/sys/win32/Node.h"

#ifndef __EVE_SYSTEM_MESSAGE_PUMP_H__
#include "eve/sys/win32/MessagePump.h"
#endif

#ifndef __EVE_SYSTEM_RENDER_H__
#include "eve/sys/shared/Render.h"
#endif

#ifndef __EVE_SYSTEM_WINDOW_H__
#include "eve/sys/win32/Window.h"
#endif


//=================================================================================================
eve::sys::Node::Node(void)
	// Inheritance
	: eve::thr::Thread()

	// Members init
	, m_pWindow(nullptr)
	, m_pRender(nullptr)
	, m_pMessagePump(nullptr)
{}



//=================================================================================================
void eve::sys::Node::init(void)
{
	// Call parent class
	eve::thr::Thread::init();

	// Start execution
	this->start();
}

//=================================================================================================
void eve::sys::Node::release(void)
{
	// Call parent class
	eve::thr::Thread::release();
}



//=================================================================================================
void eve::sys::Node::initThreadedData(void)
{
	m_pWindow = eve::sys::Window::create_ptr(50, 50, 800, 600);

	m_pRender = EVE_CREATE_PTR(eve::sys::Render);
	m_pRender->start();

	m_pMessagePump = eve::sys::MessagePump::create_ptr(m_pWindow->getHandle());
	m_pMessagePump->registerListener(this);
}

//=================================================================================================
void eve::sys::Node::releaseThreadedData(void)
{
	m_pMessagePump->unregisterListener(this);
	EVE_RELEASE_PTR(m_pMessagePump);

	m_pRender->stop();
	EVE_RELEASE_PTR(m_pRender);

	EVE_RELEASE_PTR(m_pWindow);
}



//=================================================================================================
void eve::sys::Node::run(void)
{
	bool bGotMsg;
	MSG msg;
	msg.message = WM_NULL;

	do 
	{		
		// Grab new message.
		bGotMsg = (::PeekMessageW(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);

		// Test message.
		if (bGotMsg && msg.message != WM_NULL)
		{
			// Translate and dispatch message.
			{
				::TranslateMessage(&msg);
				::DispatchMessageW(&msg);
			}
			msg.message = WM_NULL;
		}
		else
		{
			// Wait some ms, so the thread doesn't soak up CPU.
			::WaitForSingleObject(::GetCurrentThread(), 5);
		}

		// Free up CPU
		::Sleep(5);

	} while (this->running());
}



//=================================================================================================
bool eve::sys::Node::registerRenderer(eve::core::Renderer * p_pRenderer)
{
	return m_pRender->registerRenderer(p_pRenderer, m_pWindow->getHandle());;
}

//=================================================================================================
bool eve::sys::Node::unregisterRenderer(eve::core::Renderer * p_pRenderer)
{
	return m_pRender->unregisterRenderer(p_pRenderer);
}

//=================================================================================================
bool eve::sys::Node::releaseRenderer(eve::core::Renderer * p_pRenderer)
{
	return m_pRender->releaseRenderer(p_pRenderer);
}

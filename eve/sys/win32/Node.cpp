
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

#ifndef __EVE_CORE_RENDERER_H__
#include "eve/core/Renderer.h"
#endif

#ifndef __EVE_SYSTEM_MESSAGE_PUMP_H__
#include "eve/sys/win32/MessagePump.h"
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
	, m_pMessagePump(nullptr)
	, m_pVecRenderers(nullptr)
{}



//=================================================================================================
void eve::sys::Node::init(void)
{
	// Call parent class
	eve::thr::Thread::init();

	// Render engines.
	m_pVecRenderers = new std::vector<eve::core::Renderer*>();

	// Register to application events.
	eve::evt::register_events_application(this);

	// Start execution
	this->start();
}

//=================================================================================================
void eve::sys::Node::release(void)
{
	// Unregister to application events.
	eve::evt::unregister_events_application(this);

	// Render engines.
	eve::core::Renderer * re = nullptr;
	while (!m_pVecRenderers->empty())
	{
		re = m_pVecRenderers->back();
		m_pVecRenderers->pop_back();

		EVE_RELEASE_PTR(re);
	}
	EVE_RELEASE_PTR_CPP(m_pVecRenderers);

	// Call parent class
	eve::thr::Thread::release();
}



//=================================================================================================
void eve::sys::Node::initThreadedData(void)
{
	m_pWindow = eve::sys::Window::create_ptr(50, 50, 800, 600);

	m_pMessagePump = eve::sys::MessagePump::create_ptr(m_pWindow->getHandle());
	m_pMessagePump->registerListener(this);
	m_pMessagePump->start();
}

//=================================================================================================
void eve::sys::Node::releaseThreadedData(void)
{
	m_pMessagePump->stop();
	m_pMessagePump->unregisterListener(this);
	EVE_RELEASE_PTR(m_pMessagePump);

	EVE_RELEASE_PTR(m_pWindow);
}



//=================================================================================================
void eve::sys::Node::run(void)
{
	do {
		m_pFence->lock();

		for (auto & itr : (*m_pVecRenderers))
		{
			itr->cb_beforeDisplay();
			itr->cb_display();
			itr->cb_afterDisplay();
		}

		m_pFence->unlock();

	} while (this->running());
}



//=================================================================================================
bool eve::sys::Node::registerRenderer(eve::core::Renderer * p_pRenderer)
{
	m_pFence->lock();

	std::vector<eve::core::Renderer*>::iterator itr = std::find(m_pVecRenderers->begin(), m_pVecRenderers->end(), p_pRenderer);
	bool breturn = (itr == m_pVecRenderers->end());
	if (breturn)
	{
		m_pVecRenderers->push_back(p_pRenderer);
		p_pRenderer->registerToHandle(m_pWindow->getHandle());
	}

	m_pFence->unlock();

	return breturn;
}

//=================================================================================================
bool eve::sys::Node::unregisterRenderer(eve::core::Renderer * p_pRenderer)
{
	m_pFence->lock();

	std::vector<eve::core::Renderer*>::iterator itr = std::find(m_pVecRenderers->begin(), m_pVecRenderers->end(), p_pRenderer);
	bool breturn = (itr != m_pVecRenderers->end());
	if (breturn)
	{
		m_pVecRenderers->erase(itr);
	}

	m_pFence->unlock();

	return breturn;
}

//=================================================================================================
bool eve::sys::Node::releaseRenderer(eve::core::Renderer * p_pRenderer)
{
	m_pFence->lock();

	std::vector<eve::core::Renderer*>::iterator itr = std::find(m_pVecRenderers->begin(), m_pVecRenderers->end(), p_pRenderer);
	bool breturn = (itr != m_pVecRenderers->end());
	if (breturn)
	{
		eve::core::Renderer * rder = (*itr);
		m_pVecRenderers->erase(itr);
		EVE_RELEASE_PTR(rder);
	}

	m_pFence->unlock();

	return breturn;
}

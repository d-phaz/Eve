
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
#include "eve/sys/shared/Render.h"

#ifndef __EVE_CORE_RENDERER_H__
#include "eve/core/Renderer.h"
#endif

#ifndef __EVE_OPENGL_CORE_CONTEXT_H__
#include "eve/ogl/core/win32/Context.h"
#endif


//=================================================================================================
eve::sys::Render * eve::sys::Render::create_ptr(HWND p_handle)
{
	eve::sys::Render * ptr = new eve::sys::Render(p_handle);
	ptr->init();
	return ptr;
}



//=================================================================================================
eve::sys::Render::Render(HWND p_handle)
	// Inheritance
	: eve::thr::Thread()

	// Members init
	, m_handle(p_handle)
	, m_pContext(nullptr)
	, m_pVecRenderers(nullptr)
	, m_pTimerRender(nullptr)
{}



//=================================================================================================
void eve::sys::Render::init(void)
{
	// Call parent class
	eve::thr::Thread::init();

	// Create OpenGL context for target window handle.
	m_pContext = eve::ogl::SubContext::create_ptr(m_handle);

	// Render engines.
	m_pVecRenderers = new std::list<eve::core::Renderer*>();

	// Timer.
	m_pTimerRender = eve::time::Timer::create_ptr(false);
}

//=================================================================================================
void eve::sys::Render::release(void)
{
	// Timer.
	EVE_RELEASE_PTR(m_pTimerRender)

	// Render engines.
	m_pContext->makeCurrent();
	eve::core::Renderer * rdr = nullptr;
	while (!m_pVecRenderers->empty())
	{
		rdr = m_pVecRenderers->back();
		m_pVecRenderers->pop_back();

		EVE_RELEASE_PTR(rdr);
	}
	EVE_RELEASE_PTR_CPP(m_pVecRenderers);
	m_pContext->swapBuffers();
	m_pContext->doneCurrent();

	// Release context.
	EVE_RELEASE_PTR_SAFE(m_pContext);

	// Call parent class
	eve::thr::Thread::release();
}



//=================================================================================================
void eve::sys::Render::initThreadedData(void)
{
	// Nothing to do for now.
}

//=================================================================================================
void eve::sys::Render::releaseThreadedData(void)
{
	// Nothing to do for now.
}



//=================================================================================================
void eve::sys::Render::run(void)
{
	m_pTimerRender->start();

	do
	{
		
		if (m_pTimerRender->getTimeNextFrame() < 10)
		{
			// Launch render.
			m_pFence->lock();
			m_pContext->makeCurrent();

			for (auto && itr : (*m_pVecRenderers))
			{
				itr->cb_beforeDisplay();
				itr->cb_display();
				itr->cb_afterDisplay();
			}

			m_pContext->swapBuffers();
			m_pContext->doneCurrent();
			m_pFence->unlock();	

			m_pTimerRender->updateFPS(true);
		}
		m_pTimerRender->updateFPS(false);
		this->setRunWait(static_cast<uint32_t>(m_pTimerRender->getTimeNextFrame()));

	} while (this->running());
}



//=================================================================================================
bool eve::sys::Render::registerRendererBack(eve::core::Renderer * p_pRenderer)
{
	m_pFence->lock();

	std::list<eve::core::Renderer*>::iterator itr = std::find(m_pVecRenderers->begin(), m_pVecRenderers->end(), p_pRenderer);
	bool breturn = (itr == m_pVecRenderers->end());
	if (breturn)
	{
		m_pVecRenderers->push_back(p_pRenderer);
	}

	m_pFence->unlock();

	return breturn;
}

//=================================================================================================
bool eve::sys::Render::registerRendererFront(eve::core::Renderer * p_pRenderer)
{
	m_pFence->lock();

	std::list<eve::core::Renderer*>::iterator itr = std::find(m_pVecRenderers->begin(), m_pVecRenderers->end(), p_pRenderer);
	bool breturn = (itr == m_pVecRenderers->end());
	if (breturn)
	{
		m_pVecRenderers->push_front(p_pRenderer);
	}

	m_pFence->unlock();

	return breturn;
}

//=================================================================================================
bool eve::sys::Render::unregisterRenderer(eve::core::Renderer * p_pRenderer)
{
	m_pFence->lock();

	std::list<eve::core::Renderer*>::iterator itr = std::find(m_pVecRenderers->begin(), m_pVecRenderers->end(), p_pRenderer);
	bool breturn = (itr != m_pVecRenderers->end());
	if (breturn)
	{
		m_pVecRenderers->erase(itr);
	}

	m_pFence->unlock();

	return breturn;
}

//=================================================================================================
bool eve::sys::Render::releaseRenderer(eve::core::Renderer * p_pRenderer)
{
	m_pFence->lock();

	std::list<eve::core::Renderer*>::iterator itr = std::find(m_pVecRenderers->begin(), m_pVecRenderers->end(), p_pRenderer);
	bool breturn = (itr != m_pVecRenderers->end());
	if (breturn)
	{
		eve::core::Renderer * rder = (*itr);
		m_pVecRenderers->erase(itr);


		// Delete pointer in active OpenGL context.
		m_pContext->makeCurrent();
		
		EVE_RELEASE_PTR(rder);

		m_pContext->swapBuffers();
		m_pContext->doneCurrent();
	}

	m_pFence->unlock();

	return breturn;
}

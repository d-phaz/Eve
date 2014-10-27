
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

// Main header.
#include "eve/ogl/core/Renderer.h"

#ifndef __EVE_OPENGL_CONTEXT_H__
#include "eve/ogl/core/win32/Context.h"
#endif

#ifndef __EVE_OPENGL_OBJECT_H__
#include "eve/ogl/core/Object.h"
#endif

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 


//=================================================================================================
eve::ogl::Renderer::Renderer(void)

	// Inheritance
	: eve::core::Renderer()

	// Members init
	, m_pContext(nullptr)

	, m_pQueueInit(nullptr)
	, m_pQueueUpdate(nullptr)
	, m_pQueueRelease(nullptr)
	, m_pQueueFence(nullptr)
{}



//=================================================================================================
void eve::ogl::Renderer::init(void)
{
	m_pQueueInit		= new std::deque<eve::ogl::Object *>();
	m_pQueueUpdate		= new std::deque<eve::ogl::Object *>();
	m_pQueueRelease		= new std::deque<eve::ogl::Object *>();
	m_pQueueFence		= EVE_CREATE_PTR(eve::thr::SpinLock);
}

//=================================================================================================
void eve::ogl::Renderer::release(void)
{
	// Force queues process.
	m_pContext->makeCurrent();
	this->processQueues();
	m_pContext->swapBuffers();
	m_pContext->doneCurrent();

	// Empty and release queues
	m_pQueueInit->clear();
	EVE_RELEASE_PTR_CPP(m_pQueueInit);
	m_pQueueUpdate->clear();
	EVE_RELEASE_PTR_CPP(m_pQueueUpdate);
	m_pQueueRelease->clear();
	EVE_RELEASE_PTR_CPP(m_pQueueRelease);

	// Release fence.
	EVE_RELEASE_PTR(m_pQueueFence);

	// Release context.
	EVE_RELEASE_PTR(m_pContext);
}



//=================================================================================================
void eve::ogl::Renderer::registerToHandle(void * p_handle)
{
	// Create OpenGL context for target window handle.
	m_pContext = eve::ogl::SubContext::create_ptr(reinterpret_cast<HWND>(p_handle));
}



//=================================================================================================
void eve::ogl::Renderer::putInQueueInit(eve::ogl::Object * p_pObject)
{
	EVE_ASSERT(p_pObject);

	m_pQueueFence->lock();
	m_pQueueInit->push_back(p_pObject);
	m_pQueueFence->unlock();
}

//=================================================================================================
void eve::ogl::Renderer::putInQueueUpdate(eve::ogl::Object * p_pObject)
{
	EVE_ASSERT(p_pObject);

	m_pQueueFence->lock();
	m_pQueueUpdate->push_back(p_pObject);
	m_pQueueFence->unlock();
}

//=================================================================================================
void eve::ogl::Renderer::putInQueueRelease(eve::ogl::Object * p_pObject)
{
	EVE_ASSERT(p_pObject);

	m_pQueueFence->lock();
	m_pQueueRelease->push_back(p_pObject);
	m_pQueueFence->unlock();
}



//=================================================================================================
void eve::ogl::Renderer::processQueues(void)
{
	m_pQueueFence->lock();

	while (!m_pQueueInit->empty())
	{
		m_pQueueInit->front()->oglInit();
		m_pQueueInit->pop_front();
	}
	while (!m_pQueueUpdate->empty())
	{
		m_pQueueUpdate->front()->oglUpdate();
		m_pQueueUpdate->pop_front();
	}
	while (!m_pQueueRelease->empty())
	{
		eve::ogl::Object * obj = m_pQueueRelease->front();
		m_pQueueRelease->pop_front();
		obj->oglRelease();
		EVE_RELEASE_PTR(obj);
	}

	m_pQueueFence->unlock();
}

//=================================================================================================
void eve::ogl::Renderer::clearQueues(void)
{
	m_pQueueFence->lock();

	m_pQueueInit->clear();
	m_pQueueUpdate->clear();
	m_pQueueRelease->clear();

	m_pQueueFence->unlock();
}



//=================================================================================================
void eve::ogl::Renderer::cb_beforeDisplay(void)
{
	m_pContext->makeCurrent();
	this->processQueues();
}

//=================================================================================================
void eve::ogl::Renderer::cb_afterDisplay(void)
{
	m_pContext->swapBuffers();
	m_pContext->doneCurrent();
}


//=================================================================================================
void eve::ogl::Renderer::cb_display(void)
{

}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		CREATE
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::ogl::Fbo * eve::ogl::Renderer::create(eve::ogl::FormatFbo & p_format)
{
	return EVE_OGL_CREATE(eve::ogl::Fbo, p_format, this);
}

//=================================================================================================
eve::ogl::Pbo * eve::ogl::Renderer::create(eve::ogl::FormatPbo & p_format)
{
	return EVE_OGL_CREATE(eve::ogl::Pbo, p_format, this);
}

//=================================================================================================
eve::ogl::Shader * eve::ogl::Renderer::create(eve::ogl::FormatShader & p_format)
{
	return EVE_OGL_CREATE(eve::ogl::Shader, p_format, this);
}

//=================================================================================================
eve::ogl::Texture * eve::ogl::Renderer::create(eve::ogl::FormatTex & p_format)
{
	return EVE_OGL_CREATE(eve::ogl::Texture, p_format, this);
}

//=================================================================================================
eve::ogl::Uniform * eve::ogl::Renderer::create(eve::ogl::FormatUniform & p_format)
{
	return EVE_OGL_CREATE(eve::ogl::Uniform, p_format, this);
}

//=================================================================================================
eve::ogl::Vao * eve::ogl::Renderer::create(eve::ogl::FormatVao & p_format)
{
	return EVE_OGL_CREATE(eve::ogl::Vao, p_format, this);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::ogl::Renderer::setSize(uint32_t p_width, uint32_t p_height)
{
	// Call parent class
	eve::core::Renderer::setSize(p_width, p_height);

	// Propagate to FBOs
}

//=================================================================================================
void eve::ogl::Renderer::setWidth(uint32_t p_width)
{
	// Call parent class
	eve::core::Renderer::setWidth(p_width);

	// Propagate to FBOs
}

//=================================================================================================
void eve::ogl::Renderer::setHeight(uint32_t p_height)
{
	// Call parent class
	eve::core::Renderer::setHeight(p_height);

	// Propagate to FBOs
}

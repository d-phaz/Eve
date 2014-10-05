
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
#include "eve/ogl/Renderer.h"

#ifndef __EVE_OPENGL_CONTEXT_H__
#include "eve/ogl/win32/Context.h"
#endif


//=================================================================================================
eve::ogl::Renderer::Renderer(void)

	// Inheritance
	: eve::core::Renderer()

	// Members init
	, m_pContext(nullptr)
{}



//=================================================================================================
void eve::ogl::Renderer::init(void)
{
	
}

//=================================================================================================
void eve::ogl::Renderer::release(void)
{
	EVE_RELEASE_PTR(m_pContext);
}



//=================================================================================================
void eve::ogl::Renderer::registerToHandle(void * p_handle)
{
	// Create OpenGL context for target window handle.
	m_pContext = eve::ogl::SubContext::create_ptr(reinterpret_cast<HWND>(p_handle));
}



//=================================================================================================
void eve::ogl::Renderer::cb_beforeDisplay(void)
{
	m_pContext->makeCurrent();

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

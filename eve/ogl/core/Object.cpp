
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
#include "eve/ogl/core/Object.h"

#ifndef __EVE_OPENGL_CORE_RENDER_H__
#include "eve/ogl/core/Renderer.h"
#endif


//=================================================================================================
eve::ogl::Object::Object(void)
	// Inheritance
	: eve::mem::Pointer()
	// members init
	, m_pRenderer(nullptr)
{}



//=================================================================================================
void eve::ogl::Object::linkToRenderer(eve::ogl::Renderer * p_pRenderer)
{
	EVE_ASSERT(p_pRenderer);
	m_pRenderer = p_pRenderer;
}



//=================================================================================================
void eve::ogl::Object::requestOglInit(void)
{
	EVE_ASSERT(m_pRenderer);
	m_pRenderer->putInQueueInit(this);
}

//=================================================================================================
void eve::ogl::Object::requestOglUpdate(void)
{
	EVE_ASSERT(m_pRenderer);
	m_pRenderer->putInQueueUpdate(this);
}

//=================================================================================================
void eve::ogl::Object::requestRelease(void)
{
	EVE_ASSERT(m_pRenderer);
	m_pRenderer->putInQueueRelease(this);
}

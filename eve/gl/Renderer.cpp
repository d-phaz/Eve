
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
#include "eve/gl/Renderer.h"

#ifndef __EVE_OPENGL_CONTEXT_H__
#include "eve/gl/win32/Context.h"
#endif


//=================================================================================================
eve::gl::Renderer::Renderer(void)

	// Inheritance
	: eve::core::Renderer()
{}



//=================================================================================================
void eve::gl::Renderer::init(void)
{
	static bool master_context_ready = false;
	if (!master_context_ready)
	{
		eve::gl::Context::create_instance();
	}
}

//=================================================================================================
void eve::gl::Renderer::release(void)
{
	eve::gl::Context::release_instance();
}



//=================================================================================================
void eve::gl::Renderer::registerToHandle(void * p_handle)
{

}



//=================================================================================================
void eve::gl::Renderer::cb_beforeDisplay(void)
{

}

//=================================================================================================
void eve::gl::Renderer::cb_afterDisplay(void)
{

}


//=================================================================================================
void eve::gl::Renderer::cb_display(void)
{

}

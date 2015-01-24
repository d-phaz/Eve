
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
#include "eve/core/Renderer.h"


//=================================================================================================
eve::core::Renderer::Renderer(void)
	// Inheritance
	: eve::mem::Pointer()
	// Members init
	, m_width(0)
	, m_height(0)
	, m_pFence(nullptr)
{}



//=================================================================================================
void eve::core::Renderer::init(void)
{
	m_pFence = EVE_CREATE_PTR(eve::thr::SpinLock);
}

//=================================================================================================
void eve::core::Renderer::release(void)
{
	EVE_RELEASE_PTR(m_pFence);
}



//=================================================================================================
void eve::core::Renderer::cb_beforeDisplay(void)
{
	m_pFence->lock();
}

//=================================================================================================
void eve::core::Renderer::cb_afterDisplay(void)
{
	m_pFence->unlock();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::core::Renderer::setSize(uint32_t p_width, uint32_t p_height)
{
	m_width  = p_width;
	m_height = p_height;
}

//=================================================================================================
void eve::core::Renderer::setWidth(uint32_t p_width)
{
	m_width = p_width;
}

//=================================================================================================
void eve::core::Renderer::setHeight(uint32_t p_height)
{
	m_height = p_height;
}


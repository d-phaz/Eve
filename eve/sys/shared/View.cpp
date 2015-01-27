
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
#include "eve/sys/shared/View.h"

#ifndef __EVE_SYSTEM_MESSAGE_PUMP_H__
#include "eve/sys/win32/MessagePump.h"
#endif


//=================================================================================================
eve::sys::View::View(void)
	// Inheritance.
	: eve::sys::Node()
	// Members init.
	, m_pRender(nullptr)
{}



//=================================================================================================
void eve::sys::View::initThreadedData(void)
{
	// Call parent class.
	eve::sys::Node::initThreadedData();

	m_pRender = eve::sys::Render::create_ptr(m_pWindow->getHandle());
	m_pRender->start();
}

//=================================================================================================
void eve::sys::View::releaseThreadedData(void)
{
	m_pRender->stop();
	EVE_RELEASE_PTR(m_pRender);

	// Call parent class.
	eve::sys::Node::releaseThreadedData();
}



//=================================================================================================
bool eve::sys::View::registerRenderer(eve::core::Renderer * p_pRenderer)
{
	return m_pRender->registerRendererBack(p_pRenderer);
}

//=================================================================================================
bool eve::sys::View::unregisterRenderer(eve::core::Renderer * p_pRenderer)
{
	return m_pRender->unregisterRenderer(p_pRenderer);
}

//=================================================================================================
bool eve::sys::View::releaseRenderer(eve::core::Renderer * p_pRenderer)
{
	return m_pRender->releaseRenderer(p_pRenderer);
}

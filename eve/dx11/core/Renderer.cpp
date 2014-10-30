
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
#include "eve/dx11/core/Renderer.h"

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 

#include "eve/dx11/core/RenderTargetStack.h"

//=================================================================================================
eve::dx11::Renderer::Renderer(void)
	: eve::core::Renderer()
{
	this->m_p_swapChain = NULL;
	this->m_pRenderCallBack = NULL;
}



//=================================================================================================
void eve::dx11::Renderer::init(void)
{

}

//=================================================================================================
void eve::dx11::Renderer::release(void)
{
	delete m_p_swapChain;
	m_p_swapChain = 0;
}

void eve::dx11::Renderer::AttachDevice(eve::dx11::Device* device, eve::dx11::Context* context)
{
	this->m_p_device = device;
	this->m_p_context = context;
}

void eve::dx11::Renderer::AttachCallBack(eve::dx11::RenderCallBack* callback)
{
	this->m_pRenderCallBack = callback;
}

void eve::dx11::Renderer::DetachCallBack()
{
	this->m_pRenderCallBack = NULL;
}

//=================================================================================================
void eve::dx11::Renderer::registerToHandle(void * p_handle)
{
	if (m_p_swapChain)
	{
		return;
	}

	this->m_p_swapChain = new eve::dx11::SwapChain();
	this->m_p_swapChain->Init(this->m_p_device,reinterpret_cast<HWND>(p_handle));
}

void eve::dx11::Renderer::cb_beforeDisplay(void)
{
	this->m_p_context->GetRenderTargetStack()->Push(this->m_p_swapChain);

	if (this->m_pRenderCallBack)
	{
		this->m_pRenderCallBack->cb_Update();
	}
}

void eve::dx11::Renderer::cb_afterDisplay(void)
{
	this->m_p_context->GetRenderTargetStack()->Pop();
	this->m_p_swapChain->Present();
}

void eve::dx11::Renderer::cb_display(void)
{
	if (this->m_pRenderCallBack)
	{
		this->m_pRenderCallBack->cb_Render();
	}
}


void eve::dx11::Renderer::setSize(uint32_t p_width, uint32_t p_height)
{
	// Call parent class
	eve::core::Renderer::setSize(p_width, p_height);
}

void eve::dx11::Renderer::setWidth(uint32_t p_width)
{
	// Call parent class
	eve::core::Renderer::setWidth(p_width);
}

void eve::dx11::Renderer::setHeight(uint32_t p_height)
{
	// Call parent class
	eve::core::Renderer::setHeight(p_height);
}

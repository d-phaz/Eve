
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
#include "eve/dx11/core/RenderTargetStack.h"

eve::dx11::RenderTargetState::RenderTargetState()
{
	//ZeroMemory(&this->m_pRenderViews,8*sizeof(void*));
	this->Init(NULL, 0);
	this->m_bOwned= false;	
}

eve::dx11::RenderTargetState::RenderTargetState(eve::dx11::RenderTarget* renderTarget)
{
	this->Init(&renderTarget, 1);	
}

eve::dx11::RenderTargetState::RenderTargetState(eve::dx11::RenderTarget** renderTargets, int renderTargetCount)
{
	this->Init(renderTargets, renderTargetCount);	
}

void eve::dx11::RenderTargetState::Init(eve::dx11::RenderTarget** renderTargets, int renderTargetCount)
{

	ZeroMemory(&this->m_pRenderViews,D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT*sizeof(void*));
	this->m_pDepthStencilView = NULL;
	this->m_NumViews = renderTargetCount;

	for (uint32_t i = 0; i < renderTargetCount; i++)
	{
		this->m_pRenderViews[i] = renderTargets[i]->GetRenderView();
	}

	uint32_t width = 0, height = 0;

	if (renderTargetCount > 0)
	{
		width = renderTargets[0]->GetWidth();
		height = renderTargets[0]->GetHeight();
	}

	this->m_viewPort.TopLeftX = 0;
	this->m_viewPort.TopLeftY = 0;
	this->m_viewPort.Width = width;
	this->m_viewPort.Height = height;
	this->m_viewPort.MaxDepth = 1.0f;
	this->m_viewPort.MinDepth = 0.0f;
}

void eve::dx11::RenderTargetState::Apply(eve::dx11::Context* context)
{
	context->GetContext()->OMSetRenderTargets(this->m_NumViews, &this->m_pRenderViews[0] ,this->m_pDepthStencilView);
	context->GetContext()->RSSetViewports(1, &this->m_viewPort);
}

eve::dx11::RenderTargetStack::RenderTargetStack()
{
	this->m_pContext = NULL;
	this->m_stack = NULL;
	this->nullState = NULL;
}

void eve::dx11::RenderTargetStack::Init(eve::dx11::Context* context)
{
	this->m_pContext = context;
	uint32_t size = sizeof(eve::dx11::RenderTargetState*);
	
	eve::dx11::RenderTargetState* state = new eve::dx11::RenderTargetState();

	this->m_stack = new std::stack<eve::dx11::RenderTargetState*>();
	this->nullState = new eve::dx11::RenderTargetState();
}

void eve::dx11::RenderTargetStack::Push(eve::dx11::RenderTarget* renderTarget)
{
	eve::dx11::RenderTargetState* state = new eve::dx11::RenderTargetState(renderTarget);
	state->m_bOwned = true;

	this->m_stack->push(state);
	this->Apply();
}


void eve::dx11::RenderTargetStack::Push(eve::dx11::RenderTargetState* state)
{
	this->m_stack->push(state);
	this->Apply();
}

void eve::dx11::RenderTargetStack::Pop()
{
	if (this->m_stack->empty())
	{
		//Should warn here, pop should not happen on empty stack
	}
	else
	{
		RenderTargetState* state= this->m_stack->top();
		state->Apply(this->m_pContext);

		if (state->m_bOwned)
		{
			delete state;
		}

		this->m_stack->pop();
	}
}

void eve::dx11::RenderTargetStack::Apply()
{
	if (this->m_stack->empty())
	{
		this->nullState->Apply(this->m_pContext);
	}
	else
	{
		RenderTargetState* state= this->m_stack->top();
		state->Apply(this->m_pContext);
	}
}

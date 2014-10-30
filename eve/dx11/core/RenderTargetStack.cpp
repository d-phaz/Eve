#include "eve/dx11/core/RenderTargetStack.h"

eve::dx11::RenderTargetState::RenderTargetState()
{
	//ZeroMemory(&this->m_pRenderViews,8*sizeof(void*));
	this->Init(NULL, 0);	
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
		this->Apply();
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
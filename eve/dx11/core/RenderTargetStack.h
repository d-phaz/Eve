#pragma once
#ifndef __EVE_DIRECTX11_RENDERTARGETSTACK_H__
#define __EVE_DIRECTX11_RENDERTARGETSTACK_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

#ifndef __EVE_DIRECTX11_RENDERTARGET_H__
	#include "RenderTarget.h"
#endif

namespace eve 
{
	namespace dx11
	{
		/**
		* \class eve::dx11::RenderTargetState
		*
		* \brief single structure to bind the whole render targets in one go
		* \note This element does not own resources, just tells how to bind them, so do not release elements
		*/
		class RenderTargetState
		{
			public:
				RenderTargetState();
				RenderTargetState(eve::dx11::RenderTarget* renderTarget);
				RenderTargetState(eve::dx11::RenderTarget** renderTargets, int renderTargetCount);

				void Apply(eve::dx11::Context* context); //Apply the state content to the context
			private:
				void Init(eve::dx11::RenderTarget** renderTargets, int renderTargetCount);
				ID3D11RenderTargetView* m_pRenderViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]; //Maximum of 8 render targets
				uint32_t m_NumViews;
				ID3D11DepthStencilView* m_pDepthStencilView;
				D3D11_VIEWPORT m_viewPort;
		};

		/**
		* \class eve::dx11::RenderTargetStack
		*
		* \brief allows to keep track of render target push, restores previous state once operation is completed
		*
		*/
		class RenderTargetStack
		{
			friend class eve::dx11::Context;
			public:
				RenderTargetStack();

				void Push(eve::dx11::RenderTarget* renderTarget); //Push a single render target

				void Push(eve::dx11::RenderTargetState* state);
				void Pop();
				void Apply();

			private:
				void Init(eve::dx11::Context* context);
				eve::dx11::Context* m_pContext;
				eve::dx11::RenderTargetState* nullState; //If stack is empty, set the render targets to null*/
				std::stack<eve::dx11::RenderTargetState*>* m_stack;
		};
	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_RENDERTARGETSTACK_H__
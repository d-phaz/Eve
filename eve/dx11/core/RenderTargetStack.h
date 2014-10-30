
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

#pragma once
#ifndef __EVE_DIRECTX11_RENDERTARGETSTACK_H__
#define __EVE_DIRECTX11_RENDERTARGETSTACK_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

#ifndef __EVE_DIRECTX11_RENDERTARGET_H__
	#include "RenderTarget.h"
#endif

namespace eve { namespace dx11 { class RenderTargetStack; } }

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
			friend class RenderTargetStack;
			public:
				RenderTargetState();
				RenderTargetState(eve::dx11::RenderTarget* renderTarget);
				RenderTargetState(eve::dx11::RenderTarget** renderTargets, int renderTargetCount);

				void Apply(eve::dx11::Context* context); //Apply the state content to the context
			protected:
				bool m_bOwned;
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


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
#ifndef __EVE_DIRECTX11_SWAPCHAIN_H__
#define __EVE_DIRECTX11_SWAPCHAIN_H__

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
		* \class eve::dx11::SwapChain
		*
		* \brief SwapChain is the resource responsible to draw on the screen
		*
		*/
		class SwapChain : public RenderTarget
		{
			public:
				SwapChain();
				~SwapChain();
				void Init(eve::dx11::Device* device, HWND windowHandle);
				void Resize();
				void Present();
				EVE_FORCE_INLINE void EnableVerticalSync(bool enable) { this->m_bEnableVSync = enable; }

			public: //Render Target overrides
				virtual ID3D11RenderTargetView* GetRenderView() override { return this->m_p_renderView; } ;
				virtual const D3D11_RENDER_TARGET_VIEW_DESC& GetRenderViewDesc() override { return this->mRenderViewDesc; };
				virtual uint32_t GetWidth() override { return this->mTextureDesc.Width; };
				virtual uint32_t GetHeight() override { return this->mTextureDesc.Height; };

			private:
				eve::dx11::Device* m_pDevice;
				bool m_bEnableVSync;
				IDXGISwapChain* m_p_swapChain;

				ID3D11Texture2D* m_p_texture;
				D3D11_TEXTURE2D_DESC mTextureDesc;

				ID3D11RenderTargetView* m_p_renderView;
				D3D11_RENDER_TARGET_VIEW_DESC mRenderViewDesc;

			private:
				void InitTextureAndView();
		};
	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_SWAPCHAIN_H__

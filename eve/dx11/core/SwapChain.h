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
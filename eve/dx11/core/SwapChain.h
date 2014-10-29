#pragma once
#ifndef __EVE_DIRECTX11_SWAPCHAIN_H__
#define __EVE_DIRECTX11_SWAPCHAIN_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
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
		class SwapChain
		{
			public:
				SwapChain();
				~SwapChain();
				void Init(eve::dx11::Device* device, HWND windowHandle);
				void Present();
				EVE_FORCE_INLINE void EnableVerticalSync(bool enable) { this->m_bEnableVSync = enable; }

			private:
				bool m_bEnableVSync;
				IDXGISwapChain* m_p_swapChain;
				ID3D11Texture2D* m_p_texture;
				ID3D11RenderTargetView* m_p_renderView;
		};
	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_SWAPCHAIN_H__
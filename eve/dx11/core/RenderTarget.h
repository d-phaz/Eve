#pragma once
#ifndef __EVE_DIRECTX11_RENDERTARGET_H__
#define __EVE_DIRECTX11_RENDERTARGET_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

#ifndef __EVE_DIRECTX11_CONTEXT_H__
	#include "Context.h"
#endif

namespace eve 
{
	namespace dx11
	{
		/**
		* \class eve::dx11::RenderTarget
		*
		* \brief DirectX11 RenderTarget (pure virtual)
		*/
		class RenderTarget
		{
			public:
				virtual ID3D11RenderTargetView* GetRenderView() = 0;
				virtual const D3D11_RENDER_TARGET_VIEW_DESC& GetRenderViewDesc() = 0;
				virtual uint32_t GetWidth() = 0;
				virtual uint32_t GetHeight() = 0;
		};
	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_RENDERTARGET_H__
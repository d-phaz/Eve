#pragma once
#ifndef __EVE_DIRECTX11_INDEXBUFFER_H__
#define __EVE_DIRECTX11_INDEXBUFFER_H__

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
		* \class eve::dx11::IndexBuffer
		*
		* \brief DirectX11 IndexBuffer
		* Index buffer to attach geometry to render context
		*/
		class IndexBuffer
		{
			public:
				IndexBuffer();
				void Bind(eve::dx11::Context* context);

				void Draw(eve::dx11::Context* context);
				void DrawInstanced(eve::dx11::Context* context, uint32_t instanceCount);
			private:
				void Release();
				uint32_t m_IndicesCount;
				eve::dx11::IndexBufferFormat elementFormat;
				ID3D11Buffer* m_pBuffer;
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_INDEXBUFFER_H__
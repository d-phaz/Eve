#pragma once
#ifndef __EVE_DIRECTX11_RAWBUFFER_H__
#define __EVE_DIRECTX11_RAWBUFFER_H__

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
		* \class eve::dx11::RawBuffer
		*
		* \brief DirectX11 RawBuffer
		* Raw buffers are used as ByteAddressBuffer in DX11 Pipeline
		*/
		class RawBuffer
		{
			public:
				RawBuffer();
			protected:
				void Release();

			private:
				ID3D11Buffer* m_pBuffer;
				ID3D11ShaderResourceView* m_pShaderView;
				ID3D11UnorderedAccessView* m_pUnorderedView;
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_RAWBUFFER_H__
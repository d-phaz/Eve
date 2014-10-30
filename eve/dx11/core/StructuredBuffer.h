#pragma once
#ifndef __EVE_DIRECTX11_STRUCTUREDBUFFER_H__
#define __EVE_DIRECTX11_STRUCTUREDBUFFER_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

namespace eve 
{
	namespace dx11
	{
		/**
		* \class eve::dx11::StructuredBuffer
		*
		* \brief StructuredBuffer resource type for DirectX11 pipeline.
		*/
		class StructuredBuffer
		{
			public:
				StructuredBuffer();

			protected:
				void InitDynamic(eve::dx11::Device* device, uint32_t elementCount, uint32_t elementSize);
				void InitWriteable(eve::dx11::Device* device, uint32_t elementCount, uint32_t elementSize);
				void InitAppend(eve::dx11::Device* device, uint32_t elementCount, uint32_t elementSize);
				void InitCounter(eve::dx11::Device* device, uint32_t elementCount, uint32_t elementSize);
				void Release();

			private:
				D3D11_BUFFER_DESC GetWriteableDesc(uint32_t elementCount, uint32_t elementSize);
				void Init(eve::dx11::Device* device, const D3D11_BUFFER_DESC& bufferDesc, bool createUAV, eve::dx11::StructuredBufferMode uavMode);
				ID3D11UnorderedAccessView* m_pUnorderedView;
				ID3D11ShaderResourceView* m_pShaderView;
				ID3D11Buffer* m_pBuffer;
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_STRUCTUREDBUFFER_H__
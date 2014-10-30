
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


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
#ifndef __EVE_DIRECTX11_FORMATS_H__
#define __EVE_DIRECTX11_FORMATS_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

#ifndef __EVE_DIRECTX11_ENUMS_H__
	#include "Enums.h"
#endif


namespace eve 
{
	namespace dx11
	{
		D3D11_CPU_ACCESS_FLAG GetCpuAccessFlag(eve::dx11::ResourceUsage format);
		D3D11_BIND_FLAG GetExcludeBindFlag(eve::dx11::ResourceUsage format); //Returns a list of bind flags to remove from usage
		
		bool AllowResourceView(eve::dx11::ResourceUsage format);
		bool AllowUnorderedView(eve::dx11::ResourceUsage format);
		
		/**
		* \class eve::dx11::ResourceUsageFormat
		*
		* \brief Contains presets for resource usage, and allows to set description accordingly
		*
		*/
		class ResourceUsageFormat
		{
			public:
				eve::dx11::ResourceUsage Usage;
			public:
				void SetBufferDesc(D3D11_BUFFER_DESC* bufferDesc);
				void SetTexture1DDesc(D3D11_TEXTURE1D_DESC* texture1dDesc);
				void SetTexture2DDesc(D3D11_TEXTURE2D_DESC* texture2dDesc);
				void SetTexture3DDesc(D3D11_TEXTURE3D_DESC* texture3dDesc);
		};

		class StructuredBufferFormat
		{
			public:
				uint32_t elementCount;
				uint32_t elementSize;
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_FORMATS_H__

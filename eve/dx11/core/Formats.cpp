
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

// Main header
#include "eve/dx11/core/Formats.h"

D3D11_CPU_ACCESS_FLAG eve::dx11::GetCpuAccessFlag(eve::dx11::ResourceUsage format)
{
	switch (format)
	{
		case eve::dx11::ResourceUsage::Default:
			return (D3D11_CPU_ACCESS_FLAG)0;
		case eve::dx11::ResourceUsage::Immutable:
			return (D3D11_CPU_ACCESS_FLAG)0;		
		case eve::dx11::ResourceUsage::Dynamic:
			return D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		case eve::dx11::ResourceUsage::Staging:
			return D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
		default:
			return (D3D11_CPU_ACCESS_FLAG)0;
	}
}

D3D11_BIND_FLAG eve::dx11::GetExcludeBindFlag(eve::dx11::ResourceUsage format)
{
	switch (format)
	{
		case eve::dx11::ResourceUsage::Default:
			return (D3D11_BIND_FLAG)0;
		case eve::dx11::ResourceUsage::Immutable:
			return (D3D11_BIND_FLAG)(D3D11_BIND_RENDER_TARGET | D3D11_BIND_UNORDERED_ACCESS); //No gpu write on immutables		
		case eve::dx11::ResourceUsage::Dynamic:
			return (D3D11_BIND_FLAG)(D3D11_BIND_RENDER_TARGET | D3D11_BIND_UNORDERED_ACCESS);
		case eve::dx11::ResourceUsage::Staging:
			return (D3D11_BIND_FLAG)0xFFFFFFFF; //Staging can't be bound anywhere
		default:
			return (D3D11_BIND_FLAG)0;
	}
}

bool eve::dx11::AllowResourceView(eve::dx11::ResourceUsage format)
{
	return format != eve::dx11::ResourceUsage::Staging;
}

bool eve::dx11::AllowUnorderedView(eve::dx11::ResourceUsage format)
{
	return format == eve::dx11::ResourceUsage::Default;
}

void eve::dx11::ResourceUsageFormat::SetBufferDesc(D3D11_BUFFER_DESC* bufferDesc)
{
	bufferDesc->Usage = (D3D11_USAGE)this->Usage;
	bufferDesc->CPUAccessFlags = eve::dx11::GetCpuAccessFlag(this->Usage);
	bufferDesc->BindFlags &= ~eve::dx11::GetExcludeBindFlag(this->Usage);
}

void eve::dx11::ResourceUsageFormat::SetTexture1DDesc(D3D11_TEXTURE1D_DESC* texture1dDesc)
{
	texture1dDesc->Usage = (D3D11_USAGE)this->Usage;
	texture1dDesc->CPUAccessFlags = eve::dx11::GetCpuAccessFlag(this->Usage);
	texture1dDesc->BindFlags &= ~eve::dx11::GetExcludeBindFlag(this->Usage);
}

void eve::dx11::ResourceUsageFormat::SetTexture2DDesc(D3D11_TEXTURE2D_DESC* texture2dDesc)
{
	texture2dDesc->Usage = (D3D11_USAGE)this->Usage;
	texture2dDesc->CPUAccessFlags = eve::dx11::GetCpuAccessFlag(this->Usage);
	texture2dDesc->BindFlags &= ~eve::dx11::GetExcludeBindFlag(this->Usage);
}

void eve::dx11::ResourceUsageFormat::SetTexture3DDesc(D3D11_TEXTURE3D_DESC* texture3dDesc)
{
	texture3dDesc->Usage = (D3D11_USAGE)this->Usage;
	texture3dDesc->CPUAccessFlags = eve::dx11::GetCpuAccessFlag(this->Usage);
	texture3dDesc->BindFlags &= ~eve::dx11::GetExcludeBindFlag(this->Usage);
}

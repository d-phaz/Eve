
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
#include "eve/dx11/core/StructuredBuffer.h"

eve::dx11::StructuredBuffer::StructuredBuffer()
{
	this->m_pBuffer = NULL;
	this->m_pShaderView = NULL;
	this->m_pUnorderedView = NULL;
}

void eve::dx11::StructuredBuffer::Release()
{
	EVE_SAFE_RELEASE(this->m_pUnorderedView);
	EVE_SAFE_RELEASE(this->m_pShaderView);
	EVE_SAFE_RELEASE(this->m_pBuffer);
}

void eve::dx11::StructuredBuffer::InitDynamic(eve::dx11::Device* device, uint32_t elementCount, uint32_t elementSize)
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
	bufferDesc.ByteWidth = elementCount * elementSize;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bufferDesc.StructureByteStride = elementSize;
	bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

	this->Init(device, bufferDesc, false, eve::dx11::StructuredBufferMode::Default);
}

D3D11_BUFFER_DESC eve::dx11::StructuredBuffer::GetWriteableDesc(uint32_t elementCount, uint32_t elementSize)
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS;
	bufferDesc.ByteWidth = elementCount * elementSize;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bufferDesc.StructureByteStride = elementSize;
	bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	return bufferDesc;
}

void eve::dx11::StructuredBuffer::InitWriteable(eve::dx11::Device* device, uint32_t elementCount, uint32_t elementSize)
{
	D3D11_BUFFER_DESC bufferDesc = this->GetWriteableDesc(elementCount, elementSize);
	this->Init(device, bufferDesc, true, eve::dx11::StructuredBufferMode::Default);
}

void eve::dx11::StructuredBuffer::InitAppend(eve::dx11::Device* device, uint32_t elementCount, uint32_t elementSize)
{
	D3D11_BUFFER_DESC bufferDesc = this->GetWriteableDesc(elementCount, elementSize);
	this->Init(device, bufferDesc, true, eve::dx11::StructuredBufferMode::Append);
}

void eve::dx11::StructuredBuffer::InitCounter(eve::dx11::Device* device, uint32_t elementCount, uint32_t elementSize)
{
	D3D11_BUFFER_DESC bufferDesc = this->GetWriteableDesc(elementCount, elementSize);
	this->Init(device, bufferDesc, true, eve::dx11::StructuredBufferMode::Counter);
}

void eve::dx11::StructuredBuffer::Init(eve::dx11::Device* device, const D3D11_BUFFER_DESC& bufferDesc, bool createUAV, eve::dx11::StructuredBufferMode uavMode)
{
	device->GetDevice()->CreateBuffer(&bufferDesc,NULL, &this->m_pBuffer);

	//Shader view not allowed for saging buffers
	if ((bufferDesc.Usage & D3D11_USAGE::D3D11_USAGE_STAGING) != D3D11_USAGE::D3D11_USAGE_STAGING)
	{
		device->GetDevice()->CreateShaderResourceView(this->m_pBuffer, NULL, &this->m_pShaderView);
	}

	if (createUAV)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC unorderedViewDesc;
		ZeroMemory(&unorderedViewDesc,sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
		unorderedViewDesc.Format = DXGI_FORMAT_UNKNOWN;
		unorderedViewDesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_BUFFER;
		unorderedViewDesc.Buffer.NumElements = bufferDesc.ByteWidth / bufferDesc.StructureByteStride;
		unorderedViewDesc.Buffer.Flags = (uint32_t)uavMode;

		device->GetDevice()->CreateUnorderedAccessView(this->m_pBuffer,&unorderedViewDesc, &this->m_pUnorderedView);
	}
}

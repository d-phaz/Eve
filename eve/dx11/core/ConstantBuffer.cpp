
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
#include "eve/dx11/core/ConstantBuffer.h"

eve::dx11::ConstantBuffer::ConstantBuffer()
{
	m_p_buffer = NULL;
}

void eve::dx11::ConstantBuffer::Init(eve::dx11::Device* device, uint32_t size)
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.ByteWidth = size;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

	HRESULT hr = device->GetDevice()->CreateBuffer(&bufferDesc, NULL, &this->m_p_buffer);
}

void eve::dx11::ConstantBuffer::Release()
{
	EVE_SAFE_RELEASE(this->m_p_buffer);
}

template <typename T> 
void eve::dx11::ConstantBuffer::Update(eve::dx11::Context* context, T& value)
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	HRESULT hr = context->GetContext()->Map(this->m_p_buffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &subResource);

	memcpy(subResource.pData, value, sizeof(T));

	context->GetContext()->Unmap(this->m_p_buffer, 0);
}


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
#include "eve/dx11/core/IndexBuffer.h"

eve::dx11::IndexBuffer::IndexBuffer()
{
	this->m_pBuffer = NULL;
	this->m_IndicesCount = 0;
}


void eve::dx11::IndexBuffer::Bind(eve::dx11::Context* context)
{
	//As a side note, null index buffer is totally allowed, so we don't check if buffer is null
	context->GetContext()->IASetIndexBuffer(this->m_pBuffer, (DXGI_FORMAT)this->elementFormat,0);
}

void eve::dx11::IndexBuffer::Draw(eve::dx11::Context* context)
{
	context->GetContext()->DrawIndexed(this->m_IndicesCount, 0, 0);
}

void eve::dx11::IndexBuffer::DrawInstanced(eve::dx11::Context* context, uint32_t instanceCount)
{
	context->GetContext()->DrawIndexedInstanced(this->m_IndicesCount, instanceCount, 0, 0, 0);
}

void eve::dx11::IndexBuffer::Release()
{
	EVE_SAFE_RELEASE(this->m_pBuffer);
}

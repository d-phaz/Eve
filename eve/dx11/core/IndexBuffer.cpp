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
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

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
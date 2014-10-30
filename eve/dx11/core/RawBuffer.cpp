#include "eve/dx11/core/RawBuffer.h"

eve::dx11::RawBuffer::RawBuffer()
{
	this->m_pBuffer = NULL;
	this->m_pShaderView = NULL;
	this->m_pUnorderedView = NULL;
}

void eve::dx11::RawBuffer::Release()
{
	EVE_SAFE_RELEASE(this->m_pUnorderedView);
	EVE_SAFE_RELEASE(this->m_pShaderView);
	EVE_SAFE_RELEASE(this->m_pBuffer);
}
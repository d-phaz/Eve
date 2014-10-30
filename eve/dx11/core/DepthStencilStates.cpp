#include "eve/dx11/core/DepthStencilStates.h"

eve::dx11::DepthStencilStates::DepthStencilStates()
{
	this->m_pDisabled = NULL;
	this->m_pLessRO = NULL;
	this->m_pLessRW = NULL;
}

void eve::dx11::DepthStencilStates::Init(eve::dx11::Device* device)
{
	ID3D11Device* d = device->GetDevice();

	D3D11_DEPTH_STENCIL_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	d->CreateDepthStencilState(&depthDesc, &this->m_pDisabled);

	depthDesc.DepthEnable = TRUE;
	depthDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	
	d->CreateDepthStencilState(&depthDesc, &this->m_pLessRO);

	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;

	d->CreateDepthStencilState(&depthDesc, &this->m_pLessRW);
}

void eve::dx11::DepthStencilStates::Release()
{
	EVE_SAFE_RELEASE(this->m_pDisabled);
	EVE_SAFE_RELEASE(this->m_pLessRO);
	EVE_SAFE_RELEASE(this->m_pLessRW);
}
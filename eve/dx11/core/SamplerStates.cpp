#include "eve/dx11/core/SamplerStates.h"

eve::dx11::SamplerStates::SamplerStates()
{
	this->m_pLinearClamp = NULL;
	this->m_pLinearWrap = NULL;
	this->m_pPointClamp = NULL;
}


void eve::dx11::SamplerStates::Init(eve::dx11::Device* device)
{
	ID3D11Device* d = device->GetDevice();

	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

	D3D11_TEXTURE_ADDRESS_MODE addressMode = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;

	samplerDesc.AddressU = addressMode;
	samplerDesc.AddressV = addressMode;
	samplerDesc.AddressW = addressMode;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
	samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
	samplerDesc.MaxAnisotropy = 0;
	samplerDesc.MaxLOD = FLT_MAX;
	samplerDesc.MinLOD = FLT_MIN;
	samplerDesc.MipLODBias = 0;
	
	d->CreateSamplerState(&samplerDesc, &this->m_pPointClamp);

	samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	d->CreateSamplerState(&samplerDesc, &this->m_pLinearClamp);

	addressMode = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressU = addressMode;
	samplerDesc.AddressV = addressMode;
	samplerDesc.AddressW = addressMode;

	d->CreateSamplerState(&samplerDesc, &this->m_pLinearWrap);
	

}

void eve::dx11::SamplerStates::Release()
{
	EVE_SAFE_RELEASE(this->m_pLinearClamp);
	EVE_SAFE_RELEASE(this->m_pLinearWrap);
	EVE_SAFE_RELEASE(this->m_pPointClamp);
}
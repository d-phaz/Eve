#include "eve/dx11/core/RasterizerStates.h"

eve::dx11::RasterizerStates::RasterizerStates()
{
	this->m_p_backCull = NULL;
	this->m_p_frontCull = NULL;
	this->m_p_lineAlpha = NULL;
	this->m_p_lineQuad = NULL;
	this->m_p_noCull = NULL;
	this->m_p_wireFrame = NULL;
}

void eve::dx11::RasterizerStates::Init(eve::dx11::Device* device)
{
	ID3D11Device* d = device->GetDevice();

	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDesc.AntialiasedLineEnable = FALSE;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = EVE_FRONTFACE_CCW;
	rasterizerDesc.MultisampleEnable = FALSE;
	rasterizerDesc.ScissorEnable = FALSE;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	d->CreateRasterizerState(&rasterizerDesc, &this->m_p_backCull);

	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
	d->CreateRasterizerState(&rasterizerDesc, &this->m_p_frontCull);

	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	d->CreateRasterizerState(&rasterizerDesc, &this->m_p_noCull);

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	d->CreateRasterizerState(&rasterizerDesc, &this->m_p_wireFrame);

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	
	rasterizerDesc.AntialiasedLineEnable = TRUE;
	d->CreateRasterizerState(&rasterizerDesc, &this->m_p_lineAlpha);

	rasterizerDesc.MultisampleEnable = TRUE;
	d->CreateRasterizerState(&rasterizerDesc, &this->m_p_lineQuad);
}

void eve::dx11::RasterizerStates::Release()
{
	EVE_SAFE_RELEASE(this->m_p_backCull);
	EVE_SAFE_RELEASE(this->m_p_frontCull);
	EVE_SAFE_RELEASE(this->m_p_noCull);
	EVE_SAFE_RELEASE(this->m_p_wireFrame);
	EVE_SAFE_RELEASE(this->m_p_lineAlpha);
	EVE_SAFE_RELEASE(this->m_p_lineQuad);
}

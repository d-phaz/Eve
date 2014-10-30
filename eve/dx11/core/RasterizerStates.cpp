
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


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
#include "eve/dx11/core/SwapChain.h"

eve::dx11::SwapChain::SwapChain()
{
	this->m_pDevice = NULL;
	this->m_p_texture = NULL;
	this->m_p_renderView = NULL;
	this->m_p_swapChain = NULL;
	this->m_bEnableVSync = false;
}

eve::dx11::SwapChain::~SwapChain()
{
	EVE_SAFE_RELEASE(this->m_p_texture);
	EVE_SAFE_RELEASE(this->m_p_renderView);
	EVE_SAFE_RELEASE(this->m_p_swapChain);
}

void eve::dx11::SwapChain::Init(eve::dx11::Device* device, HWND windowHandle)
{
	if (this->m_p_swapChain)
	{
		return; //Already initialized
	}

	this->m_pDevice = device;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc,sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.OutputWindow = windowHandle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	HRESULT hr = device->GetFactory()->CreateSwapChain(device->GetDevice(), &swapChainDesc, &this->m_p_swapChain);

	this->InitTextureAndView();
}

void eve::dx11::SwapChain::InitTextureAndView()
{
	ID3D11Texture2D* texture;
	this->m_p_swapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(void**)(&texture));
	ULONG res = texture->Release();
	
	this->m_p_texture = texture;
	this->m_p_texture->GetDesc(&this->mTextureDesc);

	this->m_pDevice->GetDevice()->CreateRenderTargetView(texture, NULL, &this->m_p_renderView);
	this->m_p_renderView->GetDesc(&this->mRenderViewDesc);
}

void eve::dx11::SwapChain::Resize()
{
	EVE_SAFE_RELEASE(this->m_p_renderView);
	EVE_SAFE_RELEASE(this->m_p_texture);

	this->m_p_swapChain->ResizeBuffers(0,0,0,DXGI_FORMAT::DXGI_FORMAT_UNKNOWN,0);

	this->InitTextureAndView();
}

void eve::dx11::SwapChain::Present()
{
	this->m_p_swapChain->Present(this->m_bEnableVSync ? 1 : 0, 0);
}

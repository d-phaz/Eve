
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
#include "eve/dx11/core/Device.h"

eve::dx11::Device::Device()
{
	this->m_p_device = NULL;
	this->m_p_immediateContext = NULL;
	this->m_p_factory = NULL;
}

void eve::dx11::Device::Init()
{
	if (this->m_p_device)
	{
		return;
	}

	unsigned int flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	#ifdef _DEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	D3D_FEATURE_LEVEL levels[] = 
	{
		D3D_FEATURE_LEVEL_11_1, //Windows 8 only : add define to allow to choose
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	D3D_FEATURE_LEVEL level;

	ID3D11Device* device;
	ID3D11DeviceContext* immediateContext;

	HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, flags, &levels[0],ARRAYSIZE(levels), 
		D3D11_SDK_VERSION, &device, &level, &immediateContext);

	if (FAILED(hr))
	{
		EVE_LOG_ERROR("Unable to create device, error code:%d", hr);
	}

	this->m_p_device = device;
	this->m_p_immediateContext = immediateContext;

	/*device->QueryInterface(__uuidof(ID3D11Device2),(void**)(&this->m_p_device));
	immediateContext->QueryInterface(__uuidof(ID3D11DeviceContext2),(void**)(&this->m_p_immediateContext));*/
	this->m_featureLevel = (eve::dx11::FeatureLevel)level;

	IDXGIDevice1* dxgidevice;
	device->QueryInterface(__uuidof(IDXGIDevice1),(void**)(&dxgidevice));

	IDXGIAdapter* adapter;
	dxgidevice->GetAdapter(&adapter);

	IDXGIAdapter1* adapter1 = (IDXGIAdapter1*)adapter;
	adapter1->GetParent(__uuidof(IDXGIFactory1),(void**)(&this->m_p_factory));
}

void eve::dx11::Device::dxRelease()
{
	EVE_SAFE_RELEASE(this->m_p_immediateContext);
	EVE_SAFE_RELEASE(this->m_p_device);
	EVE_SAFE_RELEASE(this->m_p_factory);
}

eve::dx11::Device::~Device()
{
	this->dxRelease();
}

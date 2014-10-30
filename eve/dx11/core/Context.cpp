
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
#include "eve/dx11/core/Context.h"

#include "eve/dx11/core/RenderTargetStack.h"

eve::dx11::Context::Context()
{
	this->m_p_context = 0;
	this->m_RenderTargetStack = 0;
}

eve::dx11::Context::~Context()
{
	EVE_SAFE_RELEASE(this->m_p_context);
	delete this->m_RenderTargetStack;
}

void eve::dx11::Context::Init(eve::dx11::Device* device)
{
	this->m_numUAVForDevice = 0;
	this->m_p_context = device->GetImmediateContext();
	this->m_p_context->AddRef();

	//Attach max UAV count to device context
	switch (device->m_featureLevel)
	{
		case eve::dx11::FeatureLevel::f11_1:
			this->m_numUAVForDevice = 64;
			break;
		case eve::dx11::FeatureLevel::f11:
			this->m_numUAVForDevice = 8;
			break;
		case eve::dx11::FeatureLevel::f10_1:
			this->m_numUAVForDevice = 1; //This is also hardware dependent, most 10.1 devices support at least one compute
			break;
	}

	this->m_tesselationSupport = device->m_featureLevel >= eve::dx11::FeatureLevel::f11;


	ZeroMemory(&this->m_p_nullShaderViews,MAX_DX11_SRV_SLOTS*sizeof(void*));
	ZeroMemory(&this->m_p_nullUnorderedViews,MAX_DX11_UAV_SLOTS*sizeof(void*));

	//Create render target stack
	this->m_RenderTargetStack = new eve::dx11::RenderTargetStack();
	this->m_RenderTargetStack->Init(this);

}

void eve::dx11::Context::CleanShaderViews(eve::dx11::ShaderStage stages)
{

}

void eve::dx11::Context::CleanAllViews()
{
	this->CleanPipelineShaderViews();
	this->CleanComputeShaderStage();
}

void eve::dx11::Context::CleanPipelineShaderViews()
{
	this->m_p_context->VSSetShaderResources(0, MAX_DX11_SRV_SLOTS, this->m_p_nullShaderViews);
	this->m_p_context->PSSetShaderResources(0, MAX_DX11_SRV_SLOTS, this->m_p_nullShaderViews);

	if (this->m_tesselationSupport)
	{
		this->m_p_context->HSSetShaderResources(0, MAX_DX11_SRV_SLOTS, this->m_p_nullShaderViews);
		this->m_p_context->DSSetShaderResources(0, MAX_DX11_SRV_SLOTS, this->m_p_nullShaderViews);
	}

	this->m_p_context->GSSetShaderResources(0, MAX_DX11_SRV_SLOTS, this->m_p_nullShaderViews);
}

void eve::dx11::Context::CleanComputeShaderStage()
{
	if (this->m_numUAVForDevice > 0)
	{
		this->m_p_context->CSSetShaderResources(0, MAX_DX11_SRV_SLOTS, this->m_p_nullShaderViews);
		this->m_p_context->CSSetUnorderedAccessViews(0, this->m_numUAVForDevice, this->m_p_nullUnorderedViews,NULL);
	}
}	

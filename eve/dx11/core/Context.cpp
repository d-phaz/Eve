#include "eve/dx11/core/Context.h"

eve::dx11::Context::Context()
{
	this->m_p_context = 0;
}

eve::dx11::Context::~Context()
{
	EVE_SAFE_RELEASE(this->m_p_context);
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
	ZeroMemory(&this->m_p_nullUnorderedViews,MAX_DX11_SRV_SLOTS*sizeof(void*));
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
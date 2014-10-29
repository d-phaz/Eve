#include "eve/dx11/core/Context.h"

eve::dx11::Context::Context()
{

}

eve::dx11::Context::~Context()
{

}

void eve::dx11::Context::Init(eve::dx11::Device* device)
{
	this->m_p_context = device->GetImmediateContext();

	ZeroMemory(&this->m_p_nullShaderViews,128*sizeof(void*));
	ZeroMemory(&this->m_p_nullUnorderedViews,128*sizeof(void*));
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
	this->m_p_context->VSSetShaderResources(0, MAX_DX11_SRV_SLOT, this->m_p_nullShaderViews);
	this->m_p_context->PSSetShaderResources(0, MAX_DX11_SRV_SLOT, this->m_p_nullShaderViews);

	this->m_p_context->HSSetShaderResources(0, MAX_DX11_SRV_SLOT, this->m_p_nullShaderViews);
	this->m_p_context->DSSetShaderResources(0, MAX_DX11_SRV_SLOT, this->m_p_nullShaderViews);

	this->m_p_context->GSSetShaderResources(0, MAX_DX11_SRV_SLOT, this->m_p_nullShaderViews);
}

void eve::dx11::Context::CleanComputeShaderStage()
{
	this->m_p_context->CSSetShaderResources(0, MAX_DX11_SRV_SLOT, this->m_p_nullShaderViews);
	this->m_p_context->CSSetUnorderedAccessViews(0, this->numUAVForDevice, this->m_p_nullUnorderedViews,NULL);
}	
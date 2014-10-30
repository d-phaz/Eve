
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
#include "eve/dx11/core/ShaderCompiler.h"

#ifndef __EVE_STRING_UTILS_H__
#include "eve/str/Utils.h"
#endif

eve::dx11::ShaderCompileResult::ShaderCompileResult()
{
	this->m_bIsCompiled = false;
	this->m_pErrorMessage = NULL;
	this->m_pShaderByteCode = NULL;
}

void eve::dx11::ShaderCompileResult::Init(ID3DBlob* byteCode, ID3DBlob* errorMessage, HRESULT compilationResult)
{
	this->m_pShaderByteCode = byteCode;
	this->m_bIsCompiled = compilationResult >= 0;
	this->m_pErrorMessage = errorMessage;
}

void eve::dx11::ShaderCompileResult::Release()
{
	EVE_SAFE_RELEASE(this->m_pErrorMessage);
	EVE_SAFE_RELEASE(this->m_pShaderByteCode);
}


eve::dx11::ShaderCompileResult eve::dx11::ShaderCompiler::CompileShader(ShaderCompileArgs args)
{
	ID3DBlob* byteCode;
	ID3DBlob* errorMessage;

	std::string target = GetShaderTarget(args.featureLevel, args.shaderType);

	HRESULT hr = D3DCompile(eve::str::to_string(args.code).c_str(), args.code.size(),NULL, NULL, NULL, 
	eve::str::to_string(args.entrypoint).c_str(), target.c_str(), 0 ,0 ,&byteCode,&errorMessage);
	
	eve::dx11::ShaderCompileResult result;
	result.Init(byteCode, errorMessage, hr);
	return result;
}

eve::dx11::ShaderCompileResult eve::dx11::ShaderCompiler::CompileEffect(std::wstring code)
{
	ID3DBlob* byteCode;
	ID3DBlob* errorMessage;

	HRESULT hr = D3DCompile(eve::str::to_string(code).c_str(), code.size(),NULL, NULL, NULL, 
	NULL, "fx_5_0", 0 ,0 ,&byteCode,&errorMessage);
	
	eve::dx11::ShaderCompileResult result;
	result.Init(byteCode, errorMessage, hr);
	return result;
}

std::string eve::dx11::GetShaderTarget(eve::dx11::FeatureLevel featureLevel, eve::dx11::ShaderStage shaderType)
{
	return GetShaderType(shaderType) + GetShaderProfile(featureLevel);
}

std::string eve::dx11::GetShaderType(eve::dx11::ShaderStage shaderType)
{
	std::string type;
	switch (shaderType)
	{
		case eve::dx11::ShaderStage::Compute:
			type = "cs_";
			break;
		case eve::dx11::ShaderStage::Domain:
			type = "ds_";
			break;
		case eve::dx11::ShaderStage::Geometry:
			type = "gs_";
			break;
		case eve::dx11::ShaderStage::Hull:
			type = "hs_";
			break;
		case eve::dx11::ShaderStage::Pixel:
			type = "ps_";
			break;
		case eve::dx11::ShaderStage::Vertex:
			type = "vs_";
			break;
	}
	return type;
}

std::string eve::dx11::GetShaderProfile(eve::dx11::FeatureLevel featureLevel)
{
	std::string profile;

	switch (featureLevel)
	{
		case eve::dx11::FeatureLevel::f11_1:
			profile = "5_0";
			break;
		case eve::dx11::FeatureLevel::f11:
			profile = "5_0";
			break;
		case eve::dx11::FeatureLevel::f10_1:
			profile = "4_1";
			break;
		case eve::dx11::FeatureLevel::f10:
			profile = "4_0";
			break;
		case eve::dx11::FeatureLevel::f09_3:
			profile = "4_0_level_9_3";
			break;
		case eve::dx11::FeatureLevel::f09_2:
			profile = "4_0_level_9_2";
			break;
		case eve::dx11::FeatureLevel::f09_1:
			profile = "4_0_level_9_1";
			break;
	}

	return profile;
}

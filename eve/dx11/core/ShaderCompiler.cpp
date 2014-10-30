#include "eve/dx11/core/ShaderCompiler.h"

#include "eve/str/Utils.h"

void eve::dx11::ShaderCompiler::Compile(ShaderCompileArgs args)
{
	ID3DBlob* blob;
	ID3DBlob* errorMsg;

	std::string target = GetShaderTarget(args.featureLevel, args.shaderType);

	HRESULT result = D3DCompile(eve::str::to_string(args.code).c_str(), args.code.size(),NULL, NULL, NULL, eve::str::to_string(args.entrypoint).c_str(), target.c_str(), 0 ,0 ,&blob,&errorMsg);
	
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
#pragma once
#ifndef __EVE_DIRECTX11_SHADERCOMPILER_H__
#define __EVE_DIRECTX11_SHADERCOMPILER_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

namespace eve 
{
	namespace dx11
	{
		std::string GetShaderTarget(eve::dx11::FeatureLevel featureLevel, eve::dx11::ShaderStage shaderType);
		std::string GetShaderType(eve::dx11::ShaderStage shaderType);
		std::string GetShaderProfile(eve::dx11::FeatureLevel featureLevel);

		class ShaderCompileArgs
		{
			public:
				std::wstring code;
				std::wstring entrypoint;
				eve::dx11::ShaderStage shaderType;
				eve::dx11::FeatureLevel featureLevel;
		};

		class ShaderCompiler
		{
			public:
				static void Compile(ShaderCompileArgs args);
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_SHADERCOMPILER_H__
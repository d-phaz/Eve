#pragma once
#ifndef __EVE_DIRECTX11_SHADERCOMPILER_H__
#define __EVE_DIRECTX11_SHADERCOMPILER_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

namespace eve { namespace dx11 { class ShaderCompiler; } }

namespace eve 
{
	namespace dx11
	{
		std::string GetShaderTarget(eve::dx11::FeatureLevel featureLevel, eve::dx11::ShaderStage shaderType);
		std::string GetShaderType(eve::dx11::ShaderStage shaderType);
		std::string GetShaderProfile(eve::dx11::FeatureLevel featureLevel);

		/**
		* \class eve::dx11::ShaderCompileArgs
		*
		* \brief Arguments sent to shader compiler to describe compiler options
		*/
		class ShaderCompileArgs
		{
			public:
				std::wstring code;
				std::wstring entrypoint;
				eve::dx11::ShaderStage shaderType;
				eve::dx11::FeatureLevel featureLevel;
		};

		/**
		* \class eve::dx11::ShaderCompileResult
		*
		* \brief Returned by shader compiler, contains bytecode (if compilation was successfull),
		* and eventual error/warning messages
		*/
		class ShaderCompileResult
		{
			friend class eve::dx11::ShaderCompiler;
			public:
				ShaderCompileResult();
				EVE_FORCE_INLINE ID3DBlob* GetShaderByteCode() { return this->m_pShaderByteCode; }
				EVE_FORCE_INLINE ID3DBlob* GetErrorMessage() { return this->m_pErrorMessage; }
				EVE_FORCE_INLINE bool IsCompiled() { return this->m_bIsCompiled; }
				void Release();
			private:
				ID3DBlob* m_pShaderByteCode;
				ID3DBlob* m_pErrorMessage;
				bool m_bIsCompiled;
				
			protected:
				void Init(ID3DBlob* byteCode, ID3DBlob* errorMessage, HRESULT compilationResult);


		};

		/**
		* \class eve::dx11::ShaderCompiler
		*
		* \brief Used to compile shader bytecode from source
		*/
		class ShaderCompiler
		{
			public:
				static ShaderCompileResult CompileShader(ShaderCompileArgs args);
				static ShaderCompileResult CompileEffect(std::wstring code);
				
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_SHADERCOMPILER_H__
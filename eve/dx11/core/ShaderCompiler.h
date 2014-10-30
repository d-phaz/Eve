
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
		* \brief Returned by shader compiler, contains bytecode (if compilation was successful),
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
		* \brief Used to compile shader byte code from source
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

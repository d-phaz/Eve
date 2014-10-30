
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
#ifndef __EVE_DIRECTX11_CONTEXT_H__
#define __EVE_DIRECTX11_CONTEXT_H__

#ifndef __EVE_DIRECTX11_ENUMS_H__
	#include "Enums.h"
#endif

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

namespace eve { namespace dx11 { class RenderTargetStack; } }

namespace eve 
{
	namespace dx11
	{
		/**
		* \class eve::dx11::Context
		*
		* \brief DirectX11 Context
		* Context wraps ID3D11DeviceContext, responsible to submit commands to gpu
		*
		*/
		class Context
		{
			public:
				Context();
				virtual ~Context();

				void Init(eve::dx11::Device* device);

				/** \brief Cleans shader views on specified stages */
				void CleanShaderViews(eve::dx11::ShaderStage stages);
				/** \brief Cleans all views on all stages */
				void CleanAllViews();
				/** \brief Cleans shader views on pipeline shader stages only (excludes compute) */
				void CleanPipelineShaderViews();
				/** \brief Cleans both shader views and unordered views on compute shader stage */
				void CleanComputeShaderStage();		
				
				EVE_FORCE_INLINE ID3D11DeviceContext* GetContext() { return this->m_p_context; }			
				EVE_FORCE_INLINE eve::dx11::RenderTargetStack* GetRenderTargetStack() { return this->m_RenderTargetStack; }	

			private:
				eve::dx11::RenderTargetStack* m_RenderTargetStack;

				ID3D11DeviceContext* m_p_context;
				ID3D11ShaderResourceView* m_p_nullShaderViews[MAX_DX11_SRV_SLOTS];
				ID3D11UnorderedAccessView* m_p_nullUnorderedViews[MAX_DX11_UAV_SLOTS]; //Maximum number of UAV is 64 for now, so set array to maximum size

				uint32_t m_numUAVForDevice; //Depending on feature level this is 0, 1, 8 or 64 (also HW dependent)
				bool m_tesselationSupport; //Min of feature level 11
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_CONTEXT_H__

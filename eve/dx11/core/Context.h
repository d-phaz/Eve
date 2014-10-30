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
#pragma once
#ifndef __EVE_DIRECTX11_CONTEXT_H__
#define __EVE_DIRECTX11_CONTEXT_H__

#ifndef __EVE_DIRECTX11_ENUMS_H__
	#include "Enums.h"
#endif

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

namespace eve 
{
	namespace dx11
	{
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

			private:
				ID3D11DeviceContext* m_p_context;
				ID3D11ShaderResourceView* m_p_nullShaderViews[MAX_DX11_SRV_SLOTS];
				ID3D11UnorderedAccessView* m_p_nullUnorderedViews[MAX_DX11_UAV_SLOTS]; //Maximum number of UAV is 64 for now, so set array to maximum size

				unsigned int m_numUAVForDevice; //Depending on feature level this is 0, 1, 8 or 64 (also HW dependent)
				bool m_tesselationSupport; //Min of feature level 11
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_CONTEXT_H__
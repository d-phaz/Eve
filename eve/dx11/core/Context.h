#pragma once
#ifndef __EVE_DIRECTX11_CONTEXT_H__
#define __EVE_DIRECTX11_CONTEXT_H__

#ifndef __EVE_DIRECTX11_ENUMS_H__
	#include "Enums.h"
#endif

namespace eve 
{
	namespace dx11
	{
		class Context
		{
			public:
				/** \brief Cleans shader views on specified stages */
				void CleanShaderViews(ShaderStage stages);
				/** \brief Cleans shader views on all stages */
				void CleanShaderViews();
				/** \brief Cleans shader views on pipeline shader stages only (excludes compute) */
				void CleanPipelineShaderViews();
				/** \brief Cleans both shader views and unordered views on compute shader stage */
				void CleanComputeShaderStage();				

			private:
				ID3D11ShaderResourceView* m_p_nullShaderViews[128];
				ID3D11UnorderedAccessView* m_p_nullUnorderedViews[64]; //Maximum number of UAV is 64 for now, so set array to maximum size
				unsigned int numUAVForDevice; //Depending on feature level this is 0, 1, 8 or 64 (also HW dependent)
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_CONTEXT_H__
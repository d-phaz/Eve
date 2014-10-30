#pragma once
#ifndef __EVE_DIRECTX11_SAMPLERSTATES_H__
#define __EVE_DIRECTX11_SAMPLERSTATES_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

#ifndef __EVE_DIRECTX11_CONTEXT_H__
	#include "Context.h"
#endif

namespace eve 
{
	namespace dx11
	{
		class SamplerStates
		{
			public:
				SamplerStates();
				EVE_FORCE_INLINE ID3D11SamplerState* LinearClamp() { return this->m_pLinearClamp; }
				EVE_FORCE_INLINE ID3D11SamplerState* LinearWrap() { return this->m_pLinearWrap; }
				EVE_FORCE_INLINE ID3D11SamplerState* PointClamp() { return this->m_pPointClamp; }
			private:
				void Init(eve::dx11::Device* device);
				void Release();

				ID3D11SamplerState* m_pLinearClamp;
				ID3D11SamplerState* m_pLinearWrap;
				ID3D11SamplerState* m_pPointClamp;
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_SAMPLERSTATES_H__
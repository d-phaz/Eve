#pragma once
#ifndef __EVE_DIRECTX11_DEPTHSTENCILSTATES_H__
#define __EVE_DIRECTX11_DEPTHSTENCILSTATES_H__

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
		/**
		* \class eve::dx11::DepthStencilStates
		*
		* \brief DirectX11 DepthStencilStates
		* Depth stencil states presets 
		*/
		class DepthStencilStates
		{
			public:
				DepthStencilStates();
				EVE_FORCE_INLINE void Disable(eve::dx11::Context* context) 
				{ 
					context->GetContext()->OMSetDepthStencilState(this->m_pDisabled, 0);
				}

				EVE_FORCE_INLINE void SetLessReadWrite(eve::dx11::Context* context) 
				{ 
					context->GetContext()->OMSetDepthStencilState(this->m_pLessRW, 0);
				}

				EVE_FORCE_INLINE void SetLessReadOnly(eve::dx11::Context* context) 
				{ 
					context->GetContext()->OMSetDepthStencilState(this->m_pLessRO, 0);
				}

			private:
				void Init(eve::dx11::Device* device);
				void Release();
				ID3D11DepthStencilState* m_pDisabled;
				ID3D11DepthStencilState* m_pLessRW;
				ID3D11DepthStencilState* m_pLessRO;
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_DEPTHSTENCILSTATES_H__
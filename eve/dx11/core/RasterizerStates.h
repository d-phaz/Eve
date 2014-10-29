#pragma once
#ifndef __EVE_DIRECTX11_RASTERIZERSTATES_H__
#define __EVE_DIRECTX11_RASTERIZERSTATES_H__

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
		* \class eve::dx11::RasterizerStates
		*
		* \brief Rasterizer states presets 
		*
		*/
		class RasterizerStates
		{
			public:
				EVE_FORCE_INLINE ID3D11RasterizerState* SetBackCull(eve::dx11::Context* context) 
				{ 
					context->GetContext()->RSSetState(this->m_p_backCull);
				}

				EVE_FORCE_INLINE ID3D11RasterizerState* SetFrontCull(eve::dx11::Context* context) 
				{ 
					context->GetContext()->RSSetState(this->m_p_frontCull);
				}

				EVE_FORCE_INLINE ID3D11RasterizerState* SetNoCull(eve::dx11::Context* context) 
				{ 
					context->GetContext()->RSSetState(this->m_p_noCull);
				}
				EVE_FORCE_INLINE ID3D11RasterizerState* SetWireFrame(eve::dx11::Context* context) 
				{ 
					context->GetContext()->RSSetState(this->m_p_wireFrame);
				}

			protected:
				EVE_FORCE_INLINE ID3D11RasterizerState* BackCull() { return this->m_p_backCull; }
				EVE_FORCE_INLINE ID3D11RasterizerState* FrontCull() { return this->m_p_frontCull; }
				EVE_FORCE_INLINE ID3D11RasterizerState* NoCull() { return this->m_p_noCull; }
				EVE_FORCE_INLINE ID3D11RasterizerState* WireFrame() { return this->m_p_noCull; }

			private:
				void Init(eve::dx11::Device* device);
				void Release();

				ID3D11RasterizerState* m_p_backCull;
				ID3D11RasterizerState* m_p_frontCull;
				ID3D11RasterizerState* m_p_noCull;
				ID3D11RasterizerState* m_p_wireFrame;
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_RASTERIZERSTATES_H__
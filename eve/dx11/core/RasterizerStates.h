
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
				RasterizerStates();
				EVE_FORCE_INLINE void SetBackCull(eve::dx11::Context* context) 
				{ 
					context->GetContext()->RSSetState(this->m_p_backCull);
				}

				EVE_FORCE_INLINE void SetFrontCull(eve::dx11::Context* context) 
				{ 
					context->GetContext()->RSSetState(this->m_p_frontCull);
				}

				EVE_FORCE_INLINE void SetNoCull(eve::dx11::Context* context) 
				{ 
					context->GetContext()->RSSetState(this->m_p_noCull);
				}

				EVE_FORCE_INLINE void SetWireFrame(eve::dx11::Context* context) 
				{ 
					context->GetContext()->RSSetState(this->m_p_wireFrame);
				}

				EVE_FORCE_INLINE void SetLineAlpha(eve::dx11::Context* context) 
				{ 
					context->GetContext()->RSSetState(this->m_p_lineAlpha);
				}

				EVE_FORCE_INLINE void SetLineQuadrilateral(eve::dx11::Context* context) 
				{ 
					context->GetContext()->RSSetState(this->m_p_lineQuad);
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
				ID3D11RasterizerState* m_p_lineAlpha;
				ID3D11RasterizerState* m_p_lineQuad;
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_RASTERIZERSTATES_H__

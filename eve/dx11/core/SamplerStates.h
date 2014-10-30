
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
		/**
		* \class eve::dx11::SamplerStates
		*
		* \brief DirectX11 SamplerStates
		* Sampler states presets. In that case we assign them differently, since as opposite
		* as other states, they are bound to shader pipleline slots
		*/
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

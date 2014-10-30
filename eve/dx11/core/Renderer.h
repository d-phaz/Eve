
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
#ifndef __EVE_DIRECTX11_RENDER_H__
#define __EVE_DIRECTX11_RENDER_H__

#ifndef __EVE_CORE_RENDERER_H__
#include "eve/core/Renderer.h"
#endif

#ifndef __EVE_DIRECTX11_SWAPCHAIN_H__
	#include "SwapChain.h"
#endif

namespace eve { namespace thr { class SpinLock;  } }

namespace eve
{
	namespace dx11
	{

		/**
		* \class eve::dx11::RenderCallBack
		*
		* \brief Pure virtual class to send callbacks on render
		*
		* \note extends eve::core::Renderer
		*/
		class RenderCallBack
		{
			public:
				virtual void cb_Update() = 0;
				virtual void cb_Render() = 0;
		};

		/**
		* \class eve::sys::Renderer
		*
		* \brief DirectX11 render engine.
		*
		* \note extends eve::core::Renderer
		*/
		class Renderer
			: public eve::core::Renderer
		{
			friend class eve::mem::Pointer;
		protected:
			EVE_DISABLE_COPY(Renderer);
			EVE_PROTECT_DESTRUCTOR(Renderer);

		protected:
			/** \class constructor. */
			explicit Renderer(void);

			
		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			void AttachDevice(eve::dx11::Device* device, eve::dx11::Context* context);
			void AttachCallBack(eve::dx11::RenderCallBack* callback);
			void DetachCallBack();
			/** \brief Register renderer to window handle. (pure virtual) */
			virtual void registerToHandle(void * p_handle) override;

			void Clear(bool clear) { this->m_b_clear = clear; }
			void SetClearColor(float r, float g, float b, float a)
			{
				m_f_clearcolor[0] = r;
				m_f_clearcolor[1] = g;
				m_f_clearcolor[2] = b;
				m_f_clearcolor[3] = a;
			}

			EVE_FORCE_INLINE eve::dx11::SwapChain* GetSwapChain() { return this->m_p_swapChain; }

		protected:
			eve::dx11::SwapChain* m_p_swapChain;
			eve::dx11::Device* m_p_device;
			eve::dx11::Context* m_p_context;


		private:
			bool m_b_clear;
			float m_f_clearcolor[4];
			RenderCallBack* m_pRenderCallBack;
			eve::thr::SpinLock * m_pRenderLock;

		public:
			/** \brief Before display callback. (pure virtual) */
			virtual void cb_beforeDisplay(void) override;
			/** \brief After display callback. (pure virtual) */
			virtual void cb_afterDisplay(void) override;

			/** \brief Draw on screen callback. (pure virtual) */
			virtual void cb_display(void) override; // = 0;

		public:
			/** \brief Set render size. */
			virtual void setSize(uint32_t p_width, uint32_t p_height);
			/** \brief Set render width. */
			virtual void setWidth(uint32_t p_width);
			/** \brief Set render height. */
			virtual void setHeight(uint32_t p_height);

		}; // class Renderer

	} // namespace core

} // namespace eve

#endif // __EVE_DIRECTX11_RENDER_H__

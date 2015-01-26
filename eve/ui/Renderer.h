
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
#ifndef __EVE_UI_RENDERER_H__
#define __EVE_UI_RENDERER_H__


#ifndef __EVE_OPENGL_CORE_RENDER_H__
#include "eve/ogl/core/Renderer.h"
#endif

#ifndef __EVE_MATH_TYPES_H__
#include "eve/math/Types.h"
#endif


namespace eve { namespace ui { class Frame; } }


namespace eve
{
	namespace ui
	{
		/**
		* \class eve::ui::Renderer
		* \brief UI render engine.
		* \note extends eve::ogl::Renderer.
		*/
		class Renderer
			: public eve::ogl::Renderer
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			int32_t								m_viewX;						//!< Specifies viewport position on X axis.
			int32_t								m_viewY;						//!< Specifies viewport position on Y axis.
			int32_t								m_viewWidth;					//!< Specifies viewport width.
			int32_t								m_viewHeight;					//!< Specifies viewport height.

			eve::math::TMatrix44<float>			m_matrixProjection;				//!< Specifies projection matrix.

		protected:
			eve::ui::Frame *					m_pFrame;						//!< Specifies linked frame shared pointer.

		protected:
			eve::ogl::Shader *					m_pShaderColored;				//!< Specifies colored object shader.
			eve::ogl::Shader *					m_pShaderTextured;				//!< Specifies textured object shader.

			eve::ogl::Uniform *					m_pUniformMatrices;				//!< Specifies uniform buffer containing matrices.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Renderer);
			EVE_PUBLIC_DESTRUCTOR(Renderer);

		public:
			/** \brief Create and return new pointer. */
			static eve::ui::Renderer * create_ptr(eve::ui::Frame * p_pFrame, int32_t p_width, int32_t p_height);
			/** \brief Create and return new pointer. */
			static eve::ui::Renderer * create_ptr(eve::ui::Frame * p_pFrame, const eve::vec2i & p_size);

		public:
			/** \brief Class constructor. */
			explicit Renderer(eve::ui::Frame * p_pFrame, int32_t p_width, int32_t p_height);
			/** \brief Class constructor. */
			explicit Renderer(eve::ui::Frame * p_pFrame, const eve::vec2i & p_size);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		protected:
			/** \brief Compute matrices. */
			void calcMatrices(void);


		public:
			/** \brief Translate viewport on both axis. */
			void viewTranslate(int32_t p_x, int32_t p_y);
			/** \brief Translate viewport on both axis. */
			void viewTranslate(const eve::vec2i & p_value);
			/** \brief Translate viewport on X axis. */
			void viewTranslateX(int32_t p_value);
			/** \brief Translate viewport on Y axis. */
			void viewTranslateY(int32_t p_value);


		public:
			/** \brief Draw on screen callback. (pure virtual) */
			virtual void cb_display(void) override;

		}; // class Renderer

	} // namespace ui

} // namespace eve

#endif // __EVE_UI_RENDERER_H__

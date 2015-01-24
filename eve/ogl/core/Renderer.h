
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
#ifndef __EVE_OPENGL_CORE_RENDER_H__
#define __EVE_OPENGL_CORE_RENDER_H__

#ifndef __EVE_CORE_RENDERER_H__
#include "eve/core/Renderer.h"
#endif

#ifndef __EVE_GEOMETRY_INCLUDES_H__
#include "eve/geom/Includes.h"
#endif

#ifndef __EVE_OPENGL_CORE_CONTEXT_H__
#include "eve/ogl/core/win32/Context.h"
#endif

#ifndef __EVE_OPENGL_CORE_FBO_H__
#include "eve/ogl/core/Fbo.h"
#endif

#ifndef __EVE_OPENGL_CORE_PBO_H__
#include "eve/ogl/core/Pbo.h"
#endif

#ifndef __EVE_OPENGL_CORE_TEXTURE_H__
#include "eve/ogl/core/Texture.h"
#endif

#ifndef __EVE_OPENGL_CORE_SHADER_H__
#include "eve/ogl/core/Shader.h"
#endif

#ifndef __EVE_OPENGL_CORE_SHADER_MANAGER_H__
#include "eve/ogl/core/ShaderManager.h"
#endif

#ifndef __EVE_OPENGL_CORE_UNIFORM_H__
#include "eve/ogl/core/Uniform.h"
#endif

#ifndef __EVE_OPENGL_CORE_VAO_H__
#include "eve/ogl/core/Vao.h"
#endif


namespace eve { namespace thr { class SpinLock;  } }


namespace eve
{
	namespace ogl
	{
		/**
		* \class eve::sys::Renderer
		*
		* \brief OpenGL render engine.
		*
		* \note extends eve::core::Renderer
		*/
		class Renderer
			: public eve::core::Renderer
		{

			friend class eve::mem::Pointer;
			friend class eve::ogl::Object;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:				
			std::deque<eve::ogl::Object *> *            m_pQueueInit;			//<! OpenGL objects initialization queue.
			std::deque<eve::ogl::Object *> *            m_pQueueUpdate;			//<! OpenGL objects update queue.
			std::deque<eve::ogl::Object *> *            m_pQueueRelease;		//<! OpenGL objects release queue.
			eve::thr::SpinLock *						m_pQueueFence;			//!< Init/Update/Release queues fence.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

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


		protected:
			/** \brief Put target object in initialization queue. */
			void putInQueueInit(eve::ogl::Object * p_pObject);
			/** \brief Put target object in update queue. */
			void putInQueueUpdate(eve::ogl::Object * p_pObject);
			/** \brief Put target object in release queue. */
			void putInQueueRelease(eve::ogl::Object * p_pObject);


		public:
			/** \brief Process queued operations. */
			void processQueues(void);


		public:
			/** \brief Before display callback. */
			virtual void cb_beforeDisplay(void) override;
			/** \brief After display callback. */
			virtual void cb_afterDisplay(void) override;

			/** \brief Draw on screen callback. (pure virtual) */
			virtual void cb_display(void) override = 0;


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		CREATE
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Create and return new eve::ogl::Fbo pointer based on eve::ogl::FormatFbo. */
			eve::ogl::Fbo *		create(eve::ogl::FormatFbo & p_format);
			/** \brief Create and return new eve::ogl::Pbo pointer based on eve::ogl::FormatPbo. */
			eve::ogl::Pbo *		create(eve::ogl::FormatPbo & p_format);
			/** \brief Create and return new eve::ogl::Shader pointer based on eve::ogl::FormatShader. */
			eve::ogl::Shader *	create(eve::ogl::FormatShader & p_format);
			/** \brief Create and return new eve::ogl::ShaderManager pointer based on eve::ogl::FormatShaderAdvanced. */
			eve::ogl::ShaderManager * create(eve::ogl::FormatShaderAdvanced & p_format);
			/** \brief Create and return new eve::ogl::Texture pointer based on eve::ogl::FormatTex. */
			eve::ogl::Texture * create(eve::ogl::FormatTex & p_format);
			/** \brief Create and return new eve::ogl::Uniform pointer based on eve::ogl::FormatUniform. */
			eve::ogl::Uniform * create(eve::ogl::FormatUniform & p_format);
			/** \brief Create and return new eve::ogl::Vao pointer based on eve::ogl::FormatVao. */
			eve::ogl::Vao *		create(eve::ogl::FormatVao & p_format);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

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

#endif // __EVE_OPENGL_CORE_RENDER_H__

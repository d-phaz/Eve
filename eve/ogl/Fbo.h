
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
#ifndef __EVE_OPENGL_FBO_H__
#define __EVE_OPENGL_FBO_H__

#ifndef __EVE_OPENGL_OBJECT_H__
#include "eve/ogl/Object.h"
#endif


namespace eve
{
	namespace ogl
	{
		/**
		* \class eve::ogl::FormatFBO
		*
		* \brief OpenGL frame buffer object format class.
		* Used to create OpenGL frame buffer object based on properties.
		*
		* \note extends eve::ogl::Format
		*/
		class FormatFBO final
			: public eve::ogl::Format
		{
		public:
			uint32_t		width;				//!< FBO texture(s) width.
			uint32_t		height;				//!< FBO texture(s) height.

			GLenum			texDataType;		//!< Texture data type.
			GLenum			depthDataType;		//!< Depth texture data type.

			size_t			texNum;				//!< FBO texture(s) amount.
			bool			bHasDepth;			//!< FBO depth texture creation required state.

		public:
			/** \brief Class constructor. */
			FormatFBO(void);
			/** \brief Class destructor. */
			virtual ~FormatFBO(void);

			/** \brief Copy constructor. */
			FormatFBO(const eve::ogl::FormatFBO & p_other);
			/** \brief Assignation operator. */
			const eve::ogl::FormatFBO & operator = (const eve::ogl::FormatFBO & p_other);

		}; // class FormatFBO


		/** 
		* \class eve::ogl::Fbo
		*
		* \brief Create and manage multiple texture Frame Buffer Object.
		* 
		* Texture creation is ordered, they are created on:
		*		GL_COLOR_ATTACHMENT0
		*		GL_COLOR_ATTACHMENT1
		*		GL_COLOR_ATTACHMENT2
		*		etc...
		*
		* Depth texture is created on GL_DEPTH_ATTACHMENT.
		*
		* Default texture data type is GL_UNSIGNED_BYTE.
		*
		* All texture use LINEAR filtering and are clamped to edges on ST axes.
		*
		* \note extends eve::ogl::Object
		*/
		class Fbo final
			: public eve::ogl::Object
		{

			friend class eve::mem::Pointer;
			friend class eve::ogl::Renderer;
			friend class eve::ogl::Object;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			GLuint					m_id;					//!< Specifies OpenGL unique FBO ID.

			uint32_t				m_width;				//!< FBO texture(s) width.
			uint32_t				m_height;				//!< FBO texture(s) height.

			GLenum					m_texDataType;			//!< Texture data type.
			GLenum					m_depthDataType;		//!< Depth texture data type.

			GLuint *				m_pSlotTextureIds;		//!< OpenGL texture(s) ID(s).
			size_t					m_slotNum;				//!< Total amount of texture slots (including depth).						

			size_t					m_texNum;				//!< Texture amount (no depth included).
			bool					m_bHasDepth;			//!< Does FBO has depth texture?

			float *					m_black;				//!< Black color (0, 0, 0, 0), used to clear buffer.
			GLenum					m_layers;				//!< Layers to clean, can be GL_COLOR and/or GL_DEPTH 


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Fbo);
			EVE_PROTECT_DESTRUCTOR(Fbo);
			
		private:
			/** \brief Class constructor. */
			explicit Fbo(void);


		protected:
			/**
			* \brief Get attributes from eve::ogl::Format. (pure virtual)
			* Object attributes MUST be retrieved before init() call.
			*/
			virtual void setAttributes(eve::ogl::Format * p_format);


		protected:
			/** \brief Alloc and init non OpenGL class members. (pure virtual) */
			virtual void init(void);
			/** \brief Release and delete non OpenGL class members. (pure virtual) */
			virtual void release(void);


		protected:
			/** \brief Init OpenGL components. */
			virtual void oglInit(void);
			/** \brief Update OpenGL components. (only FBO size can be updated here) */
			virtual void oglUpdate(void);
			/** \brief Deallocate and release OpenGL components. */
			virtual void oglRelease(void);


		public:
			/** \brief Bind (activate) FBO. */
			void bind(void);
			/** \brief Unbind (deactivate) FBO. */
			static void unbind(void);


			/** \brief Write data to FBO in selected texture slot(s). */
			void write(GLsizei p_slotsAmount, GLenum * p_pTargetSlots);
			/** \brief Write data to FBO in selected texture slot. */
			void write(GLenum p_slot);


			/** \brief Bind (activate) FBO and write data in selected texture slot(s). */
			void bindAndWrite(GLsizei p_slotsAmount, GLenum * p_pTargetSlots);
			/** \brief Bind (activate) FBO and write data in selected texture slot. */
			void bindAndWrite(GLenum p_targetSlot);


			/** \brief Bind (activate) target texture. */
			void bindTexture(GLenum p_activeIndex, GLuint p_targetSlot);
			/** \brief Bind (activate) depth texture. */
			void bindDepthTexture(void);
			/** \brief Unbind (deactivate) target texture. */
			static void unbindTexture(GLenum p_activeIndex);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get OpenGL FBO unique id. */
			virtual const GLuint getId(void) const override;
			/** \brief Get target slot OpenGL texture id. */
			const GLuint getTextureId(uint32_t p_id);


		public:
			/** \brief Get FBO size. */
			void getSize(uint32_t & p_width, uint32_t & p_height);
			/** \brief Get FBO width. */
			const uint32_t getWidth(void) const;
			/** \brief Get FBO height. */
			const uint32_t getHeight(void) const;

			/** \brief Set FBO and texture(s) size. */
			void setSize(uint32_t p_width, uint32_t p_height);
			/** \brief Set FBO and texture(s) width. */
			void setWidth(uint32_t p_width);
			/** \brief Set FBO and texture(s) height. */
			void setHeight(uint32_t p_height);

		}; // class Fbo

	} // namespace ogl

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
inline const GLuint eve::ogl::Fbo::getId(void) const				{ return m_id; }
inline const GLuint eve::ogl::Fbo::getTextureId( uint32_t p_id )	{ return m_pSlotTextureIds[ p_id ]; }


//=================================================================================================
inline void eve::ogl::Fbo::getSize(uint32_t & p_width, uint32_t & p_height)
{
	p_width  = m_width;
	p_height = m_height;
}
inline const uint32_t eve::ogl::Fbo::getWidth(void) const  { return m_width;  }
inline const uint32_t eve::ogl::Fbo::getHeight(void) const { return m_height; }

#endif // __EVE_OPENGL_FBO_H__

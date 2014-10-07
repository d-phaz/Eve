
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
#ifndef __EVE_OPENGL_TEXTURE_H__
#define __EVE_OPENGL_TEXTURE_H__

#ifndef __EVE_OPENGL_OBJECT_H__
#include "eve/ogl/Object.h"
#endif


namespace eve
{
	namespace ogl
	{
		/**
		* \class eve::ogl::FormatTex
		*
		* \brief OpenGL texture format class.
		* Used to create OpenGL texture based on properties.
		*
		* Default texture format is GL_RGBA (4 channels).
		* Default texture data type is GL_UNSIGNED_BYTE.
		*
		* By default texture use LINEAR filtering and are clamped to edges on ST axes.
		*
		* \note extends eve::ogl::Format
		*/
		class FormatTex final
			: public eve::ogl::Format
		{
		public:
			GLenum				format;				//!< Specifies the format of the texel data. The following symbolic values are accepted: GL_ALPHA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA.
			GLsizei				width;				//!< Specifies the width of the texture image. All implementations support 2D texture images that are at least 64 texels wide.
			GLsizei				height;				//!< Specifies the height of the texture image. All implementations support 2D texture images that are at least 64 texels high.
			GLenum				type;				//!< Specifies the data type of the texel data. The following symbolic values are accepted: GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_5_5_5_1.
			
			GLint				filter;				//!< Specifies the filter used to interpolate texels.
			GLint				wrap;				//!< Specifies texture wrap mode.

		public:
			/** \brief Class constructor. */
			FormatTex(void);
			/** \brief Class destructor. */
			virtual ~FormatTex(void);

			/** \brief Copy constructor. */
			FormatTex(const eve::ogl::FormatTex & p_other);
			/** \brief Assignation operator. */
			const eve::ogl::FormatTex & operator = (const eve::ogl::FormatTex & p_other);

		}; // class FormatFBO


		/** 
		* \class eve::ogl::Texture
		*
		* \brief Create and manage OpenGL TexImage2D object.
		*
		* Default texture format is GL_RGBA (4 channels).
		* Default texture data type is GL_UNSIGNED_BYTE.
		*
		* By default texture use LINEAR filtering and are clamped to edges on ST axes.
		*
		* \note extends eve::ogl::Object
		*/
		class Texture final
			: public eve::ogl::Object
		{

			friend class eve::mem::Pointer;
			friend class eve::ogl::Renderer;
			friend class eve::ogl::Object;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			GLuint						m_id;		//!< Specifies OpenGL unique texture ID.

			GLenum						m_format;	//!< Specifies the format of the texel data. The following symbolic values are accepted: GL_ALPHA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA.
			GLsizei						m_width;	//!< Specifies the width of the texture image. All implementations support 2D texture images that are at least 64 texels wide.
			GLsizei						m_height;	//!< Specifies the height of the texture image. All implementations support 2D texture images that are at least 64 texels high.
			GLenum						m_type;		//!< Specifies the data type of the texel data. The following symbolic values are accepted: GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_5_5_5_1.
			std::shared_ptr<GLvoid>		m_pData;	//!< Specifies a pointer to the image data in memory.

			GLint						m_filter;	//!< Specifies the filter used to interpolate texels.
			GLint						m_wrap;		//!< Specifies texture wrap mode.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Texture);
			EVE_PROTECT_DESTRUCTOR(Texture);
			
		private:
			/** \brief Class constructor. */
			Texture(void);


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
			/** \brief Bind (activate) texture. */
			void bind(GLenum p_index);
			/** \brief Unbind (deactivate) texture. */
			static void unbind(GLenum p_index);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Set texture data from host memory pointer. */
			void setData(std::shared_ptr<GLvoid> p_pData);


		public:
			/** \brief Get OpenGL texture unique id. (pure virtual) */
			virtual const GLuint getId(void) const override;


		public:
			/** \brief Get FBO size. */
			void getSize(uint32_t & p_width, uint32_t & p_height);
			/** \brief Get FBO width. */
			const uint32_t getWidth(void) const;
			/** \brief Get FBO height. */
			const uint32_t getHeight(void) const;
			
		}; // class Fbo

	} // namespace ogl

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
inline const GLuint eve::ogl::Texture::getId(void) const	{ return m_id; }


//=================================================================================================
inline void eve::ogl::Texture::getSize(uint32_t & p_width, uint32_t & p_height)
{
	p_width  = m_width;
	p_height = m_height;
}
inline const uint32_t eve::ogl::Texture::getWidth(void) const  { return m_width; }
inline const uint32_t eve::ogl::Texture::getHeight(void) const { return m_height; }

#endif // __EVE_OPENGL_TEXTURE_H__

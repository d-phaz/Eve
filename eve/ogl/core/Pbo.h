
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
#ifndef __EVE_OPENGL_CORE_PBO_H__
#define __EVE_OPENGL_CORE_PBO_H__

#ifndef __EVE_OPENGL_CORE_OBJECT_H__
#include "eve/ogl/core/Object.h"
#endif


namespace eve
{
	namespace ogl
	{
		/**
		* \class eve::ogl::FormatPbo
		*
		* \brief OpenGL pixel buffer object format class.
		* Used to create OpenGL pixel buffer object based on properties.
		*
		* \note extends eve::ogl::Format
		*/
		class FormatPbo final
			: public eve::ogl::Format
		{
		public:
			uint32_t					width;				//!< Specifies texture width.
			uint32_t					height;				//!< Specifies texture height.
			uint32_t					numChannels;		//!< Specifies the number of pixel channels (e.g. RGBA = 4).
			std::shared_ptr<GLvoid>		pixels;				//!< Specifies a pointer to the image data in memory.

		public:
			/** \brief Class constructor. */
			FormatPbo(void);
			/** \brief Class destructor. */
			virtual ~FormatPbo(void);

			/** \brief Copy constructor. */
			FormatPbo(const eve::ogl::FormatPbo & p_other);
			/** \brief Assignment operator. */
			const eve::ogl::FormatPbo & operator = (const eve::ogl::FormatPbo & p_other);

		}; // class FormatFbo


		/** 
		* \class eve::ogl::Pbo
		*
		* \brief Pixel buffer object used to stream texture data.
		*
		* \note extends eve::ogl::Object
		*/
		class Pbo final
			: public eve::ogl::Object
		{

			friend class eve::mem::Pointer;
			friend class eve::ogl::Renderer;
			friend class eve::ogl::Object;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			GLuint						m_id;					//!< Specifies OpenGL unique ID.

			uint32_t					m_width;				//!< Specifies texture width.
			uint32_t					m_height;				//!< Specifies texture height.
			uint32_t					m_numChannels;			//!< Specifies the number of pixel channels (e.g. RGBA = 4).
			GLsizeiptr					m_size;					//!< Specifies the memory size used by the PBO.

			std::shared_ptr<GLvoid>		m_pPixels;				//!< Specifies a pointer to the image data in memory.
			void *						m_pOglData;				//!< Specifies device buffer data address.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Pbo);
			EVE_PROTECT_DESTRUCTOR(Pbo);
			
		private:
			/** \brief Class constructor. */
			explicit Pbo(void);


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
			/** \brief Bind (activate). */
			void bind(void);
			/** \brief Unbind (deactivate). */
			static void unbind(void);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get OpenGL FBO unique id. */
			virtual const GLuint getId(void) const override;


		public:
			/** \brief Set texture data from host memory pointer. */
			void setPixels(std::shared_ptr<GLvoid> p_pPixels);
			/** \brief Set texture data from host memory pointer. */
			void setPixels(std::shared_ptr<GLvoid> p_pPixels, uint32_t p_width, uint32_t p_height, uint32_t p_numChannel);


		public:
			/** \brief Get size. */
			void getSize(uint32_t & p_width, uint32_t & p_height);
			/** \brief Get width. */
			const uint32_t getWidth(void) const;
			/** \brief Get height. */
			const uint32_t getHeight(void) const;


		public:
			/** \brief Get number of channels. */
			const uint32_t getNumChannels(void) const;

		}; // class Pbo

	} // namespace ogl

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
EVE_FORCE_INLINE const GLuint eve::ogl::Pbo::getId(void) const				{ return m_id; }


//=================================================================================================
EVE_FORCE_INLINE void eve::ogl::Pbo::getSize(uint32_t & p_width, uint32_t & p_height)
{
	p_width  = m_width;
	p_height = m_height;
}
EVE_FORCE_INLINE const uint32_t eve::ogl::Pbo::getWidth(void) const  { return m_width;  }
EVE_FORCE_INLINE const uint32_t eve::ogl::Pbo::getHeight(void) const { return m_height; }


//=================================================================================================
EVE_FORCE_INLINE const uint32_t eve::ogl::Pbo::getNumChannels(void) const { return m_numChannels; }

#endif // __EVE_OPENGL_CORE_PBO_H__

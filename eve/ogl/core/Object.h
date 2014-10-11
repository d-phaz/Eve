
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
#ifndef __EVE_OPENGL_OBJECT_H__
#define __EVE_OPENGL_OBJECT_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif

#ifndef __EVE_OPENGL_DEBUG_H__
#include "eve/ogl/core/Debug.h"
#endif


namespace eve { namespace ogl { class Renderer; } }


namespace eve
{
	namespace ogl
	{
		/**
		* \class eve::ogl::Format
		*
		* \brief Abstract base OpenGL object format class.
		* Used to create OpenGL object based on properties.
		*/
		class Format
		{
			EVE_DISABLE_COPY(Format);
			EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(Format);

		}; // class Format


		/** 
		* \class eve::ogl::Object
		*
		* \brief Abstract base OpenGL object class.
		* Every OpenGL object (VAO/Texture/PBO/FBO/etc...) MUST inherit from this class.
		*
		* \note extends mem::Pointer
		*/
		class Object
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;
			friend class eve::ogl::Renderer;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			eve::ogl::Renderer *		m_pRenderer;		//!< Parent renderer.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Object);
			EVE_PROTECT_DESTRUCTOR(Object);

		protected:
			/** \brief Class constructor. */
			explicit Object(void);


		protected:
			/** 
			* \brief Get attributes from eve::ogl::Format. (pure virtual)
			* Object attributes MUST be retrieved before init() call.
			*/
			virtual void setAttributes(eve::ogl::Format * p_format) = 0;
			/** 
			* \brief link object to target renderer.
			* Object MUST be linked to a renderer before init() call.
			*/
			void linkToRenderer(eve::ogl::Renderer * p_pRenderer);


		protected:
			/** \brief Alloc and init non OpenGL class members. (pure virtual) */
			virtual void init(void) = 0;
			/** \brief Release and delete non OpenGL class members. (pure virtual) */
			virtual void release(void) = 0;


		protected:
			/** \brief Request OpenGL init. */
			void requestOglInit(void);
			/** \brief Request OpenGL update. */
			void requestOglUpdate(void);
		public:
			/** \brief Request pointer release. */
			void requestRelease(void);


		protected:
			/** \brief Init OpenGL components. */
			virtual void oglInit(void) = 0;
			/** \brief Update OpenGL components. */
			virtual void oglUpdate(void) = 0;
			/** \brief Deallocate and release OpenGL components. */
			virtual void oglRelease(void) = 0;


		public:
			/** \brief Create and return OpenGL object of type TOGLClass. */
			template<class TOGLClass>
			static TOGLClass * create_object(eve::ogl::Format & p_format, eve::ogl::Renderer * p_pRenderer);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get OpenGL object-type unique id. (pure virtual) */
			virtual const GLuint getId(void) const = 0;

		}; // class Object

	} // namespace ogl

} // namespace eve

//=================================================================================================
template<class TOGLClass>
inline TOGLClass * eve::ogl::Object::create_object(eve::ogl::Format & p_format, eve::ogl::Renderer * p_pRenderer)
{
	EVE_ASSERT((std::is_base_of<eve::ogl::Object, TOGLClass>::value));

	TOGLClass * obj = new TOGLClass();
	obj->setAttributes(&p_format);
	obj->linkToRenderer(p_pRenderer);
	obj->init();
	obj->requestOglInit();

	return obj;
}

/** 
* \def EVE_OGL_CREATE
* \brief Convenience macro to create OpenGL object. 
*/
#define EVE_OGL_CREATE(CLASS, FORMAT, RENDERER) eve::ogl::Object::create_object<CLASS>(FORMAT, RENDERER);

#endif // __EVE_OPENGL_OBJECT_H__

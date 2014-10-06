
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
#include "eve/ogl/Debug.h"
#endif


namespace eve { namespace ogl { class Renderer; } }


namespace eve
{
	namespace ogl
	{
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
			Object(void);


		protected:
			/** 
			* \brief link object to target renderer.
			* Object MUST be linked to a renderer before init() call.
			*/
			void linkToRenderer(eve::ogl::Renderer * p_pRenderer);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) = 0;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) = 0;


		protected:
			/** Request OpenGL init. */
			void requestOglInit(void);
			/** Request OpenGL update. */
			void requestOglUpdate(void);
			/** Request pointer release. */
			void requestRelease(void);


		protected:
			/** Init OpenGL components. */
			virtual void oglInit(void) = 0;
			/** Update OpenGL components. */
			virtual void oglUpdate(void) = 0;
			/** \! Deallocate and release class members. */
			virtual void oglRelease(void) = 0;


		public:
			/** \brief Create and return OpenGL object of type TOGLClass. */
			template<class TOGLClass>
			static TOGLClass * create_object(eve::ogl::Renderer * p_pRenderer);

		}; // class Object

	} // namespace ogl

} // namespace eve

//=================================================================================================
template<class TOGLClass>
inline TOGLClass * eve::ogl::Object::create_object(eve::ogl::Renderer * p_pRenderer)
{
	EVE_ASSERT((std::is_base_of<eve::ogl::Object, TOGLClass>::value));

	TOGLClass * obj = new TOGLClass();
	obj->linkToRenderer(p_pRenderer);
	obj->init();
	obj->requestOglInit();

	return obj;
}

/** 
* \def EVE_OGL_CREATE
* \brief Convenience macro to create OpenGL object. 
*/
#define EVE_OGL_CREATE(CLASS, RENDERER) eve::ogl::Object::create_object<CLASS>(RENDERER);

#endif // __EVE_OPENGL_OBJECT_H__

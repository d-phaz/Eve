
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
		* \class eve::ogl::Fbo
		*
		* \brief Create and manage multiple texture Frame Buffer Object.
		*
		* \note extends eve::ogl::Object
		*/
		class Fbo final
			: public eve::ogl::Object
		{

			friend class eve::mem::Pointer;
			friend class eve::ogl::Renderer;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			GLuint					m_glFramebufferId;		//!< OpenGL FBO ID.

			uint32_t				m_width;				//!< FBO texture(s) width.
			uint32_t				m_height;				//!< FBO texture(s) height.

			GLuint *				m_pSlotTextureIds;		//!< OpenGL texture(s) ID(s).
			size_t					m_slotNum;								

			size_t					m_texNum;
			bool					m_bHasDepth;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Fbo);
			EVE_PROTECT_DESTRUCTOR(Fbo);
			
		private:
			/** \brief Class constructor. */
			Fbo(void);


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
			void unbind(void);


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
			/** \brief Get OpenGL FBO id. */
			const GLuint getFboId(void) const;
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
inline const GLuint eve::ogl::Fbo::getFboId(void) const				{ return m_glFramebufferId;			}
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


#pragma once
#ifndef __EVE_OPENGL_FORMAT_H__
#define __EVE_OPENGL_FORMAT_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif


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
			uint32_t		m_width;			//!< FBO texture(s) width.
			uint32_t		m_height;			//!< FBO texture(s) height.

			size_t			m_texNum;			//!< FBO texture(s) amount.
			bool			m_bHasDepth;		//!< FBO depth texture creation required state.

		public:
			/** \brief Class constructor. */
			FormatFBO(void);
			/** \brief Class destructor. */
			virtual ~FormatFBO(void);

			/** \brief Copy constructor. */
			FormatFBO(const eve::ogl::FormatFBO & p_other);
			/** \brief Assignation operator. */
			const FormatFBO & operator = (const FormatFBO & p_other);

		}; // class FormatFBO

	} // namespace ogl

} // namespace eve

#endif // __EVE_OPENGL_FORMAT_H__

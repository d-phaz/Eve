
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
#ifndef __EVE_CORE_RENDERER_H__
#define __EVE_CORE_RENDERER_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif


namespace eve
{
	namespace core
	{
		/**
		* \class eve::core::Renderer
		*
		* \brief Abstract base render engine(s) class.
		*
		* \note extends eve::mem::Pointer
		*/
		class Renderer
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			uint32_t		m_width;				//!< Render width.
			uint32_t		m_height;				//!< Render height.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Renderer);
			EVE_PROTECT_DESTRUCTOR(Renderer);

		protected:
			/** \brief Class constructor. */
			explicit Renderer(void);

			
		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) = 0;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) = 0;


		public:
			/** \brief Register renderer to window handle. (pure virtual) */
			virtual void registerToHandle(void * p_handle) = 0;


		public:
			/** \brief Before display callback. (pure virtual) */
			virtual void cb_beforeDisplay(void) = 0;
			/** \brief After display callback. (pure virtual) */
			virtual void cb_afterDisplay(void) = 0;

			/** \brief Draw on screen callback. (pure virtual) */
			virtual void cb_display(void) = 0;


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////
			
		public:
			/** \brief Get render size. */
			void getSize(uint32_t & p_width, uint32_t & p_height);
			/** \brief Get render width. */
			const uint32_t getWidth(void) const;
			/** \brief Get render height. */
			const uint32_t getHeight(void) const;

			/** \brief Set render size. */
			virtual void setSize(uint32_t p_width, uint32_t p_height);
			/** \brief Set render width. */
			virtual void setWidth(uint32_t p_width);
			/** \brief Set render height. */
			virtual void setHeight(uint32_t p_height);

		}; // class Renderer

	} // namespace ogl

} // namespace eve

//=================================================================================================
inline void eve::core::Renderer::getSize(uint32_t & p_width, uint32_t & p_height)
{
	p_width = m_width;
	p_height = m_height;
}
inline const uint32_t eve::core::Renderer::getWidth(void) const  { return m_width;  }
inline const uint32_t eve::core::Renderer::getHeight(void) const { return m_height; }

#endif // __EVE_CORE_RENDERER_H__

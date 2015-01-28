
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
#ifndef __EVE_SYSTEM_VIEW_H__
#define __EVE_SYSTEM_VIEW_H__

#ifndef __EVE_SYSTEM_NODE_H__
#include "eve/sys/win32/Node.h"
#endif

#ifndef __EVE_SYSTEM_MOUSE_H__
#include "eve/sys/shared/Mouse.h"
#endif

#ifndef __EVE_SYSTEM_RENDER_H__
#include "eve/sys/shared/Render.h"
#endif


namespace eve { namespace core	{ class Renderer; } }


namespace eve
{
	namespace sys
	{
		/** 
		* \class eve::sys::View
		*
		* \brief Base system view class.
		*
		* \note extends eve::sys::Node
		*/
		class View
			: public eve::sys::Node
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			eve::sys::Render *						m_pRender;			//!< Specifies render manager.			


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(View);
			EVE_PUBLIC_DESTRUCTOR(View);

		public:
			/** \brief Class constructor. */
			explicit View(void);


		protected:
			/** \brief Alloc and init threaded data. (pure virtual) */
			virtual void initThreadedData(void) override;
			/** \brief Release and delete threaded data. (pure virtual) */
			virtual void releaseThreadedData(void) override;


		public:
			/**
			* \brief Register a renderer pointer at the back of the container.
			* Node takes ownership of registered renderer, dealloc and delete it in release() method.
			* Return false if renderer is already registered.
			*/
			virtual bool registerRenderer(eve::core::Renderer * p_pRenderer);
			/**
			* \brief Unregister a renderer pointer.
			* Return false if renderer is not registered.
			*/
			bool unregisterRenderer(eve::core::Renderer * p_pRenderer);
			/**
			* \brief Unregister and release a renderer pointer.
			* Return false if renderer is not registered.
			*/
			bool releaseRenderer(eve::core::Renderer * p_pRenderer);

		}; // class View

	} // namespace sys

} // namespace eve

#endif // __EVE_SYSTEM_NODE_H__

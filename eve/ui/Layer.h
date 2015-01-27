
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
#ifndef __EVE_UI_LAYER_H__
#define __EVE_UI_LAYER_H__

#ifndef __EVE_SYSTEM_VIEW_H__
#include "eve/sys/shared/View.h"
#endif

#ifndef __EVE_UI_WIDGET_H__
#include "eve/ui/Widget.h"
#endif


namespace eve { namespace ui { class Renderer; } }


namespace eve
{
	namespace ui
	{
		/** 
		* \class eve::ui::Layer
		*
		* \brief UI view layer.
		* Handles interactive drawable widgets.
		*
		* \note extends eve::sys::View, eve::ui::Widget.
		*/
		class Layer
			: public eve::sys::View
			, public eve::ui::Widget
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			eve::ui::Renderer *			m_pRenderer;		//!< Specifies render engine.
			


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Layer);
			EVE_PUBLIC_DESTRUCTOR(Layer);

		public:
			/** \brief Class constructor. */
			explicit Layer(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);
			/** \brief Class constructor. */
			explicit Layer(const eve::vec2i & p_position, const eve::vec2i & p_size);


		public:
			/** \brief Setup format properties. (pure virtual) */
			virtual void setup(void);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members, propagates to children. (pure virtual) */
			virtual void release(void) override;


		protected:
			/** \brief Alloc and init threaded data. (pure virtual) */
			virtual void initThreadedData(void) override;
			/** \brief Release and delete threaded data. (pure virtual) */
			virtual void releaseThreadedData(void) override;


		public:
			/**
			* \brief Register a renderer pointer at the front of the container.
			* Node takes ownership of registered renderer, dealloc and delete it in release() method.
			* Return false if renderer is already registered.
			*/
			virtual bool registerRenderer(eve::core::Renderer * p_pRenderer) override final;

		}; // class Layer

	} // namespace ui

} // namespace eve

#endif // __EVE_UI_Layer_H__

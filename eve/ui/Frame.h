
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
#ifndef __EVE_UI_FRAME_H__
#define __EVE_UI_FRAME_H__

#ifndef __EVE_UI_LAYER_H__
#include "eve/ui/Layer.h"
#endif


namespace eve
{
	namespace ui
	{
		/** 
		* \class eve::ui::Frame
		*
		* \brief UI view frame. Create user interface child window.
		* Handles interactive drawable widgets.
		*
		* \note extends eve::ui::Layer.
		*/
		class Frame
			: public eve::ui::Layer
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:			


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Frame);
			EVE_PUBLIC_DESTRUCTOR(Frame);

		public:
			/** \brief Class constructor. */
			explicit Frame(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);
			/** \brief Class constructor. */
			explicit Frame(const eve::vec2i & p_position, const eve::vec2i & p_size);


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
			/** \brief Inflate object on both axis (rise its size) and propagate to children. */
			virtual void inflate(int32_t p_width, int32_t p_height) override;
			/** \brief Inflate object on X axis (rise its width) and propagate to children. */
			virtual void inflateX(int32_t p_value) override;
			/** \brief Inflate object on Y axis (rise its height) and propagate to children. */
			virtual void inflateY(int32_t p_value) override;


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Set position. */
			virtual void setPosition(int32_t p_x, int32_t p_y) override;
			/** \brief Set position on X axis. */
			virtual void setPositionX(int32_t p_value) override;
			/** \brief Set position on Y axis. */
			virtual void setPositionY(int32_t p_value) override;


		public:
			/** \brief Set size. */
			virtual void setSize(int32_t p_width, int32_t p_height) override;
			/** \brief Set width */
			virtual void setWidth(int32_t p_value) override;
			/** \brief Set height */
			virtual void setHeight(int32_t p_value) override;

		}; // class Frame

	} // namespace ui

} // namespace eve

#endif // __EVE_UI_FRAME_H__

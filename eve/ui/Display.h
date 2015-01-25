
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
#ifndef __EVE_UI_DISPLAY_H__
#define __EVE_UI_DISPLAY_H__

#ifndef __EVE_SYSTEM_VIEW_H__
#include "eve/sys/shared/View.h"
#endif


namespace eve
{
	namespace ui
	{
		/** 
		* \class eve::ui::Display
		*
		* \brief UI display. Usually used as an output window.
		*
		* \note extends eve::sys::View
		*/
		class Display
			: public eve::sys::View
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Display);
			EVE_PROTECT_DESTRUCTOR(Display);

		protected:
			/** \brief Class constructor. */
			explicit Display(void);


		public:
			/** \brief Setup format properties. (pure virtual) */
			virtual void setup(void);


		protected:
			/** \brief Alloc and init threaded data. (pure virtual) */
			virtual void initThreadedData(void) override;
			/** \brief Release and delete threaded data. (pure virtual) */
			virtual void releaseThreadedData(void) override;


		public:
			/** \brief Mouse down event handler. (pure virtual) */
			virtual void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args) override;
			/** \brief Mouse up event handler. (pure virtual) */
			virtual void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args) override;
			/** \brief Mouse double click event handler. (pure virtual) */
			virtual void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args) override;
			/** \brief Mouse motion (button pressed) event handler. (pure virtual) */
			virtual void cb_evtMotion(eve::evt::MouseEventArgs & p_args) override;

		}; // class Display

	} // namespace ui

} // namespace eve

#endif // __EVE_UI_DISPLAY_H__

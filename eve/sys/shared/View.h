
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




namespace eve
{
	namespace sys
	{
		/** 
		* \class eve::sys::Node
		*
		* \brief Base application view class.
		* Stock and manage render engines.
		*
		* \note extends eve::sys::Node
		*/
		class View
			: public eve::sys::Node
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(View);
			EVE_PROTECT_DESTRUCTOR(View);

		protected:
			/** \brief Class constructor. */
			explicit View(void);


		public:
			/** \brief File drop event handler. (pure virtual) */
			virtual void cb_evtFileDrop(eve::evt::FileEventArgs & p_args) override{}


			/** \brief Key down event handler. (pure virtual) */
			virtual void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args) override{}
			/** \brief Key up event handler. (pure virtual) */
			virtual void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args) override{}
			/** \brief Text input event handler. (pure virtual) */
			virtual void cb_evtKeyInput(eve::evt::KeyEventArgs & p_args) override{}


			/** \brief Mouse down event handler. (pure virtual) */
			virtual void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args) override{}
			/** \brief Mouse up event handler. (pure virtual) */
			virtual void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args) override{}
			/** \brief Mouse double click event handler. (pure virtual) */
			virtual void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args) override{}
			/** \brief Mouse motion (button pressed) event handler. (pure virtual) */
			virtual void cb_evtMotion(eve::evt::MouseEventArgs & p_args) override{}
			/** \brief Mouse passive motion (no button pressed) event handler. (pure virtual) */
			virtual void cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args) override{}


			/** \brief Window resize event handler. (pure virtual) */
			virtual void cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg) override{}
			/** \brief Window move event handler. (pure virtual) */
			virtual void cb_evtWindowMove(eve::evt::MoveEventArgs & p_arg) override{}
			/** \brief Window gain focus event handler. (pure virtual) */
			virtual void cb_evtWindowFocusGot(void) override{}
			/** \brief Window loose focus event handler. (pure virtual) */
			virtual void cb_evtWindowFocusLost(void) override{}
			/** \brief Window close event handler. (pure virtual) */
			virtual void cb_evtWindowClose(void) override{}

		}; // class Node

	} // namespace sys

} // namespace eve

#endif // __EVE_SYSTEM_NODE_H__

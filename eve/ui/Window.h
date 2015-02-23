
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
#ifndef __EVE_UI_WINDOW_H__
#define __EVE_UI_WINDOW_H__

#ifndef __EVE_SYSTEM_VIEW_H__
#include "eve/sys/shared/View.h"
#endif

#ifndef __EVE_UI_OUTPUT_H__
#include "eve/ui/Output.h"
#endif

#ifndef __EVE_UI_VIEW_H__
#include "eve/ui/View.h"
#endif


namespace eve
{
	namespace ui
	{

		/** 
		* \class eve::ui::Window
		*
		* \brief Application interface window class.
		* 
		* Creates user interface window, stock and manages linked views and outputs.
		* Windows can not create widgets except view ones.
		* View overlapping is forbidden.
		* Views handle interactive drawable widgets.
		* Outputs handle drawable widgets as HUD.
		*
		* Same application can use multiple interface windows.
		*
		* \note extends eve::sys::View.
		*/
		class Window
			: public eve::sys::View
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			std::vector<eve::ui::View*> *		m_pVecView;			//!< Specifies view container vector.
			std::vector<eve::ui::Output*> *		m_pVecOutput;		//!< Specifies output container vector.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Window);
			EVE_PUBLIC_DESTRUCTOR(Window);

		public:
			/** \brief Class constructor. */
			explicit Window(void);


		public:
			/** \brief Setup format properties. (pure virtual) */
			virtual void setup(void) override;


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/**
			* \brief Release and delete class members. (pure virtual)
			* Stop this object's thread execution (if any) immediately.
			*/
			virtual void release(void) override;


		protected:
			/** \brief Alloc and init threaded data. (pure virtual) */
			virtual void initThreadedData(void) override;
			/** \brief Release and delete threaded data. (pure virtual) */
			virtual void releaseThreadedData(void) override;


		public:
			/**
			* \brief Add view to window.
			* View is created and returned as a TView pointer.
			* Window takes ownership of newly created view.
			* Template class TView must inherit eve::ui::View.
			* Inheritance is tested in DEBUG mode, not in RELEASE mode.
			*/
			template<class TView>
			TView * addView(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);
			/**
			* \brief Add view to window.
			* View is created and returned as a TView pointer.
			* Window takes ownership of newly created view.
			* Template class TView must inherit eve::ui::View.
			* Inheritance is tested in DEBUG mode, not in RELEASE mode.
			*/
			template<class TView> 
			TView * addView(const eve::vec2i & p_position, const eve::vec2i & p_size);
			/**
			* \brief Unregister and release a view pointer.
			* Return false if view is not registered.
			*/
			bool releaseView(eve::ui::View * p_pView);


		public:
			/**
			* \brief Add output.
			* Output is created and returned as a TOutput pointer.
			* Window takes ownership of newly created output.
			* Template class TOutput must inherit eve::ui::Output.
			* Inheritance is tested in DEBUG mode, not in RELEASE mode.
			*/
			template<class TOutput>
			TOutput * addOutput(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);
			/**
			* \brief Add output to view.
			* Output is created and returned as a TOutput pointer.
			* Window takes ownership of newly created output.
			* Template class TOutput must inherit eve::ui::Output.
			* Inheritance is tested in DEBUG mode, not in RELEASE mode.
			*/
			template<class TOutput>
			TOutput * addOutput(const eve::vec2i & p_position, const eve::vec2i & p_size);
			/**
			* \brief Unregister and release an output pointer.
			* Return false if output is not registered.
			*/
			bool releaseOutput(eve::ui::Output * p_pOutput);


			//
			// Event callbacks are here as fallback in case view event is not triggered.
			// For example, Windows key and text events are triggered in main window, not in child ones.
			//

		public:
			/** \brief File drop event handler. */
			virtual void cb_evtFileDrop(eve::evt::FileEventArgs & p_args) override final;


			/** \brief Key down event handler. */
			virtual void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args) override final;
			/** \brief Key up event handler. */
			virtual void cb_evtKeyUp(eve::evt::KeyEventArgs & p_args) override final;
			/** \brief Text input event handler. */
			virtual void cb_evtTextInput(eve::evt::TextEventArgs & p_args) override final;


			/** \brief Mouse down event handler. */
			virtual void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args) override final;
			/** \brief Mouse wheel event handler. */
			virtual void cb_evtMouseWheel(eve::evt::MouseEventArgs & p_args) override final;
			/** \brief Mouse up event handler. */
			virtual void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args) override final;
			/** \brief Mouse double click event handler. */
			virtual void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args) override final;
			/** \brief Mouse motion (button pressed) event handler. */
			virtual void cb_evtMotion(eve::evt::MouseEventArgs & p_args) override final;
			/** \brief Mouse passive motion (no button pressed) event handler. */
			virtual void cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args) override final;


			/** \brief Window resize event handler. */
			virtual void cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg) override final;
			/** \brief Window move event handler. */
			virtual void cb_evtWindowMove(eve::evt::MoveEventArgs & p_arg) override final;
			/** \brief Window gain focus event handler. */
			virtual void cb_evtWindowFocusGot(eve::evt::EventArgs & p_arg) override final;
			/** \brief Window loose focus event handler. */
			virtual void cb_evtWindowFocusLost(eve::evt::EventArgs & p_arg) override final;
			/** \brief Window close event handler. */
			virtual void cb_evtWindowClose(eve::evt::EventArgs & p_arg) override final;

		}; // class Window

	} // namespace ui

} // namespace eve

//=================================================================================================
template<class TView>
TView * eve::ui::Window::addView(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
{
	EVE_ASSERT((std::is_base_of<eve::ui::View, TView>::value));

	m_pFence->lock();

	TView * ptr = new TView(p_x, p_y, p_width, p_height);
	ptr->setParentNode(this);
	ptr->setup();
	ptr->init();
	m_pVecView->push_back(ptr);

	m_pFence->unlock();

	return ptr;
}

//=================================================================================================
template<class TView>
TView * eve::ui::Window::addView(const eve::vec2i & p_position, const eve::vec2i & p_size)
{
	EVE_ASSERT((std::is_base_of<eve::ui::View, TView>::value));

	m_pFence->lock();

	TView * ptr = new TView(p_position, p_size);
	ptr->setParentNode(this);
	ptr->setup();
	ptr->init();
	m_pVecView->push_back(ptr);

	m_pFence->unlock();

	return ptr;
}



//=================================================================================================
template<class TOutput>
TOutput * eve::ui::Window::addOutput(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
{
	EVE_ASSERT((std::is_base_of<eve::ui::Output, TOutput>::value));

	m_pFence->lock();

	TOutput * ptr = new TOutput(p_x, p_y, p_width, p_height);
	ptr->setup();
	ptr->init();
	m_pVecOutput->push_back(ptr);

	m_pFence->unlock();

	return ptr;
}

//=================================================================================================
template<class TOutput>
TOutput * eve::ui::Window::addOutput(const eve::vec2i & p_position, const eve::vec2i & p_size)
{
	EVE_ASSERT((std::is_base_of<eve::ui::Output, TOutput>::value));

	m_pFence->lock();

	TOutput * ptr = new TOutput(p_position, p_size);
	ptr->setup();
	ptr->init();
	m_pVecOutput->push_back(ptr);

	m_pFence->unlock();

	return ptr;
}

#endif // __EVE_UI_WINDOW_H__

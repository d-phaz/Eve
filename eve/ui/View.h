
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
#ifndef __EVE_UI_VIEW_H__
#define __EVE_UI_VIEW_H__

#ifndef __EVE_SYSTEM_VIEW_H__
#include "eve/sys/shared/View.h"
#endif

#ifndef __EVE_UI_DISPLAY_H__
#include "eve/ui/Display.h"
#endif

#ifndef __EVE_UI_FRAME_H__
#include "eve/ui/Frame.h"
#endif


namespace eve
{
	namespace ui
	{

		// Note: View has no children. -> maybe should not inherit from Widget !!!! and stock position and size in Node ?

		/** 
		* \class eve::ui::View
		*
		* \brief Base application view class.
		* Create user interface window, stock and manages linked frames and outputs.
		*
		* \note extends eve::sys::View.
		*/
		class View
			: public eve::sys::View
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			std::vector<eve::ui::Frame*> *		m_pVecFrame;		//!< Specifies frame containing vector.
			std::vector<eve::ui::Display*> *	m_pVecDisplay;		//!< Specifies display containing vector.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(View);
			EVE_PUBLIC_DESTRUCTOR(View);

		public:
			/** \brief Class constructor. */
			explicit View(void);


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
			* \brief Add frame to view.
			* Frame is created and returned as a TFrame pointer.
			* View takes ownership of newly created frame.
			* Template class TFrame must inherit eve::ui::Frame.
			* Inheritance is tested in DEBUG mode, not in RELEASE mode.
			*/
			template<class TFrame>
			TFrame * addFrame(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);
			/**
			* \brief Add frame to view.
			* Frame is created and returned as a TFrame pointer.
			* View takes ownership of newly created frame.
			* Template class TFrame must inherit eve::ui::Frame.
			* Inheritance is tested in DEBUG mode, not in RELEASE mode.
			*/
			template<class TFrame> 
			TFrame * addFrame(const eve::vec2i & p_position, const eve::vec2i & p_size);
			/**
			* \brief Unregister a frame pointer.
			* Return false if frame is not registered.
			*/
			bool removeFrame(eve::ui::Frame * p_pFrame);
			/**
			* \brief Unregister and release a frame pointer.
			* Return false if frame is not registered.
			*/
			bool releaseFrame(eve::ui::Frame * p_pFrame);


		public:
			/**
			* \brief Add display to view.
			* Display is created and returned as a TDisplay pointer.
			* View takes ownership of newly created display.
			* Template class TDisplay must inherit eve::ui::Display.
			* Inheritance is tested in DEBUG mode, not in RELEASE mode.
			*/
			template<class TDisplay>
			TDisplay * addDisplay(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);
			/**
			* \brief Add display to view.
			* Display is created and returned as a TDisplay pointer.
			* View takes ownership of newly created display.
			* Template class TDisplay must inherit eve::ui::Display.
			* Inheritance is tested in DEBUG mode, not in RELEASE mode.
			*/
			template<class TDisplay>
			TDisplay * addDisplay(const eve::vec2i & p_position, const eve::vec2i & p_size);
			/**
			* \brief Unregister a display pointer.
			* Return false if display is not registered.
			*/
			bool removeDiaplay(eve::ui::Display * p_pDisplay);
			/**
			* \brief Unregister and release a display pointer.
			* Return false if display is not registered.
			*/
			bool releaseDisplay(eve::ui::Display * p_pDisplay);

		}; // class View

	} // namespace ui

} // namespace eve

//=================================================================================================
template<class TFrame>
TFrame * eve::ui::View::addFrame(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
{
	EVE_ASSERT((std::is_base_of<eve::ui::Frame, TFrame>::value));

	m_pFence->lock();

	TFrame * ptr = new TFrame(p_x, p_y, p_width, p_height);
	ptr->setParent(this);
	ptr->setup();
	ptr->init();
	m_pVecFrame->push_back(ptr);

	m_pFence->unlock();

	return ptr;
}

//=================================================================================================
template<class TFrame>
TFrame * eve::ui::View::addFrame(const eve::vec2i & p_position, const eve::vec2i & p_size)
{
	EVE_ASSERT((std::is_base_of<eve::ui::Frame, TFrame>::value));

	m_pFence->lock();

	TFrame * ptr = new TFrame(p_position, p_size);
	ptr->setParent(this);
	ptr->setup();
	ptr->init();
	m_pVecFrame->push_back(ptr);

	m_pFence->unlock();

	return ptr;
}



//=================================================================================================
template<class TDisplay>
TDisplay * eve::ui::View::addDisplay(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
{
	EVE_ASSERT((std::is_base_of<eve::ui::Display, TDisplay>::value));

	m_pFence->lock();

	TDisplay * ptr = new TDisplay(p_x, p_y, p_width, p_height);
	ptr->setup();
	ptr->init();
	m_pVecDisplay->push_back(ptr);

	m_pFence->unlock();

	return ptr;
}

//=================================================================================================
template<class TDisplay>
TDisplay * eve::ui::View::addDisplay(const eve::vec2i & p_position, const eve::vec2i & p_size)
{
	EVE_ASSERT((std::is_base_of<eve::ui::Display, TDisplay>::value));

	m_pFence->lock();

	TDisplay * ptr = new TDisplay(p_position, p_size);
	ptr->setup();
	ptr->init();
	m_pVecDisplay->push_back(ptr);

	m_pFence->unlock();

	return ptr;
}

#endif // __EVE_UI_VIEW_H__

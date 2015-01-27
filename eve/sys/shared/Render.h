
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
#ifndef __EVE_SYSTEM_RENDER_H__
#define __EVE_SYSTEM_RENDER_H__

#ifndef __EVE_THREADING_THREAD_H__
#include "eve/thr/Thread.h"
#endif 

#ifndef __EVE_TIME_TIMER_H__
#include "eve/time/Timer.h"
#endif

namespace eve { namespace core	{ class Renderer; } }
namespace eve { namespace ogl	{ class SubContext; } }


namespace eve
{
	namespace sys
	{
		/** 
		* \class eve::sys::Render
		*
		* \brief Render engines threaded manager.
		* Stock and manage threaded render manager.
		*
		* \note extends eve::thr::Thread
		*/
		class Render final
			: public eve::thr::Thread
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:
			HWND									m_handle;			//!< Specifies system window handle.
			eve::ogl::SubContext *					m_pContext;			//!< Specifies OpenGL context pointer.

			std::vector<eve::core::Renderer*> *		m_pVecRenderers;	//!< Specifies render Engine(s) container.
			
			eve::time::Timer *						m_pTimerRender;		//!< Specifies timer used to compute FPS.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Render);
			EVE_PUBLIC_DESTRUCTOR(Render);

		public:
			/**
			* \brief Create and return new pointer.
			* \param p_handle linked system window handle.
			*/
			static eve::sys::Render * create_ptr(HWND p_handle);


		public:
			/** \brief Class constructor. */
			explicit Render(HWND p_handle);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/**
			* \brief Release and delete class members. (pure virtual)
			* Stop this object's thread execution (if any) immediately.
			*/
			virtual void release(void) override;


		private:
			/** \brief Alloc and init threaded data. (pure virtual) */
			virtual void initThreadedData(void) override;
			/** \brief Release and delete threaded data. (pure virtual) */
			virtual void releaseThreadedData(void) override;

			/** \brief Run is the main loop for this thread (\sa start()). (pure virtual) */
			virtual void run(void) override;


		public:
			/**
			* \brief Register a renderer pointer.
			* Node takes ownership of registered renderer, dealloc and delete it in release() method.
			* Return false if renderer is already registered.
			*/
			bool registerRenderer(eve::core::Renderer * p_pRenderer);
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

		}; // class Node

	} // namespace sys

} // namespace eve

#endif // __EVE_SYSTEM_RENDER_H__

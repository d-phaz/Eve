
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
#ifndef __EVE_THREADING_THREADED_WORK_IO_H__
#define __EVE_THREADING_THREADED_WORK_IO_H__


#ifndef __EVE_THREADING_THREADED_WORK_H__
#include "eve/thr/ThreadedWork.h"
#endif 


namespace eve
{
	namespace thr
	{

		//////////////////////////////////////
		//				TYPES				//
		//////////////////////////////////////

		/** \brief convenience callback type definition. */
		typedef eve::evt::ClassCallback1<ThreadedWork, void, ThreadedWork*> ThreadedWorkCallback;

		/**
		* \class eve::thr::ThreadedWorkIO
		*
		* \brief Thread using workers.
		* Stock workers in a FIFO queue.
		* Switch to next worker right after previous one completion.
		* Worker is released right after its work completion.
		* Start and exit callbacks are used by thread pool(s) to manage active / sleeping status.
		*
		* \note extends thr::Thread
		*/
		class ThreadedWorkIO final
			: public eve::thr::ThreadedWork
		{

			friend class eve::mem::Pointer;


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			eve::thr::ThreadedWorkCallback  *		m_cbStart;			//!< Callback called at startup.
			eve::thr::ThreadedWorkCallback  *		m_cbExit;			//!< Callback called at run exit.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(ThreadedWorkIO);
			EVE_PROTECT_DESTRUCTOR(ThreadedWorkIO);

		public:
			/**
			* \brief Create and return new pointer.
			* \param p_handle linked system window handle.
			*/
			static ThreadedWorkIO * create_ptr(eve::thr::ThreadedWorkCallback * p_cbStart, eve::thr::ThreadedWorkCallback * p_cbExit);


		protected:
			/** \brief Class constructor. */
			ThreadedWorkIO(eve::thr::ThreadedWorkCallback * p_cbStart, eve::thr::ThreadedWorkCallback * p_cbExit);


		private:
			/** \brief Release and delete threaded data. (pure virtual) */
			virtual void releaseThreadedData(void) override;


		private:
			/**
			* \brief Run is the main loop for this thread. (pure virtual)
			* Usually this is called by Start(), but may be called directly for single-threaded applications.
			*/
			virtual void run(void) override;

		}; // class ThreadDummy

	} // namespace thr

} // namespace eve

#endif // __EVE_THREADING_THREADED_WORK_IO_H__


/*
 Copyright (c) 2014, The Eve Project
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
#ifndef __EVE_THREADING_THREAD_DUMMY_H__
#define __EVE_THREADING_THREAD_DUMMY_H__


#ifndef __EVE_THREADING_THREAD_H__
#include "Eve/threading/Thread.h"
#endif 

namespace eve
{
	namespace threading
	{
		class SpinLock;

		/**
		* @class threading::ThreadDummy
		*
		* This class is used for testing purpose only.
		*
		* @note extends threading::Thread
		*/
		class ThreadDummy
			: public eve::threading::Thread
		{

			friend class eve::memory::Pointer;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			eve::threading::SpinLock *		m_pLock;

			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(ThreadDummy)
			EVE_PROTECT_DESTRUCTOR(ThreadDummy)

		protected:
			/** Class constructor. */
			ThreadDummy(void);


		protected:
			/** In thread initialization function. (pure virtual) */
			virtual void inThreadInit(void) override;
			/** In thread release function. (pure virtual) */
			virtual void inThreadRelease(void) override;


		public:
			/**
			* Run is the main loop for this thread. (pure virtual)
			* Usually this is called by Start(), but may be called directly for single-threaded applications.
			*/
			virtual void run(void) override;

		}; // class ThreadDummy

	} // namespace threading

} // namespace eve

#endif // __EVE_THREADING_THREAD_DUMMY_H__

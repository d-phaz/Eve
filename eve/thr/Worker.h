
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
#ifndef __EVE_THREADING_WORKER_H__
#define __EVE_THREADING_WORKER_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_EVT_INCLUDES_H__
#include "eve/evt/Includes.h"
#endif


namespace eve
{
	namespace thr
	{

		/**
		* \class eve::thr::Worker
		*
		* \brief Abstract base thread worker class.
		* Workers are the ONLY thread level stored data and should be the basis for any engine.
		*
		* \note extends mem::Pointer
		*/
		class Worker
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Worker);
			EVE_PROTECT_DESTRUCTOR(Worker);

		protected:
			/** \brief Class constructor. */
			Worker(void);


		public:
			/** \brief Called once before the work is launched. Usually used to init required data. (pure virtual) */
			virtual void beforeWork(void) = 0;
			/** \brief Called once after the work is done. Usually used to release used data.. (pure virtual) */
			virtual void afterWork(void) = 0;

			/** 
			* \brief Main schedule work method. (pure virtual) 
			* \return false to exit work loop.
			*/
			virtual bool work(void) = 0;

		}; // Class Worker

	} // namespace thr

} // namespace eve

#endif // __EVE_THREADING_WORKER_H__

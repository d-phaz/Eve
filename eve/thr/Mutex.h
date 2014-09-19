
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
#ifndef __EVE_THREADING_MUTEX_H__
#define __EVE_THREADING_MUTEX_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_THREADING_FENCE_H__
#include "eve/thr/Fence.h"
#endif

namespace eve
{
	namespace thr
	{

		/**
		* \class eve::thr::Mutex
		* \brief provides base native Mutex
		* \note extends eve::thr::Fence
		*/
		class Mutex
			: public eve::thr::Fence
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			void *		m_mutex;		///< Mutex handle


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Mutex)
			EVE_PROTECT_DESTRUCTOR(Mutex)

		protected:
			/** \brief Class constructor. */
			Mutex(void);


		protected:
			/** \brief Alloc and init class members, initialize base mutex. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members, making sure mutex is unlocked. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Lock the mutex variable. */
			virtual void lock(void) override;
			/** \brief Unlock the mutex variable. */
			virtual void unlock(void) override;

		}; // class Mutex

	} // namespace thr

} // namespace eve

#endif // __EVE_THREADING_MUTEX_H__

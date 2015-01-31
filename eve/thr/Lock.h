
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
#ifndef __EVE_THREADING_LOCK_H__
#define __EVE_THREADING_LOCK_H__  

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_THREADING_FENCE_H__
#include "eve/thr/Fence.h"
#endif


namespace eve
{
	namespace thr
	{

		/** 
		* \class eve::thr::Lock
		* \brief lock using critical section.
		* \note extends eve::thr::Fence
		*/
		class Lock
			: public eve::thr::Fence
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:
#if defined(EVE_OS_WIN)
			CRITICAL_SECTION		m_criticalSections;
#elif defined(EVE_OS_DARWIN)
			pthread_mutex_t			m_mutex;		
#endif


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Lock);
			EVE_PUBLIC_DESTRUCTOR(Lock);
        
		public:
			/** \brief Class constructor. */
			explicit Lock(void);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Acquire the lock. */
			virtual void lock(void) override;
			/** \brief Release the lock. */
			virtual void unlock(void) override;

		}; // class Lock

	} // namespace thr

} // namespace eve

#endif // __EVE_THREADING_LOCK_H__

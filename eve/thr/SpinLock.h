
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
#ifndef __EVE_THREADING_SPIN_LOCK_H__
#define __EVE_THREADING_SPIN_LOCK_H__

#include <atomic>
#include <thread>

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
		 * \class eve::thr::SpinLock
		 *
		 * \brief A fast lock for non-contented mem access.
		 * Readers or writers will starve on high contention.
		 *
		 * \note extends eve::thr::Fence
		 */
		class SpinLock final
			: public eve::thr::Fence
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:
			//std::atomic_flag	m_state; // kept for future use

			volatile uint32_t	m_dest;
			uint32_t			m_exchange;
			uint32_t			m_compare;
			uint32_t			m_iter;
			bool				m_bMultiProc;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(SpinLock)
			EVE_PROTECT_DESTRUCTOR(SpinLock)
			
		private:
			/** \brief Class constructor. */
			SpinLock(void);


		private:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Acquire the lock exclusively. */
			virtual void lock(void) override;
			/** \brief Release an exclusive lock. */
			virtual void unlock(void) override;

		}; // class SpinLock

	} // namespace thr

} // namespace eve

#endif //__EVE_THREADING_SPIN_LOCK_H__

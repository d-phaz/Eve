
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
#ifndef __EVE_THREADING_SCOPED_FENCE_H__
#define __EVE_THREADING_SCOPED_FENCE_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif


namespace eve
{
	namespace thr
	{

		/**
		* \class eve::thr::ScopedFence
		* \brief Scoped fence class, lock the fence in the constructor and unlock it in the destructor.
		* Used fence is NOT deleted after destructor call.
		* \note extends mem::Pointer
		*/
		template<class TFence>
		class ScopedFence
		{

			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		private:
			TFence *		m_pFence;

			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(ScopedFence);

		public:
			/** \brief Class constructor. */
			ScopedFence(TFence * p_pFence);
			/** \brief Class destructor. */
			virtual ~ScopedFence(void);


		public:
			/** \brief Unlock the fence and set it to null.*/
			virtual void unlock(void);

		}; // class Mutex

	} // namespace thr

} // namespace eve


//=================================================================================================
template<class TFence>
eve::thr::ScopedFence<TFence>::ScopedFence(TFence * p_pFence)
	: m_pFence(p_pFence)
{
	EVE_ASSERT(m_pFence);
	m_pFence->lock();
}

//=================================================================================================
template<class TFence>
eve::thr::ScopedFence<TFence>::~ScopedFence(void)
{
	if (m_pFence)
	{
		m_pFence->unlock();
		m_pFence = nullptr;
	}
}

//=================================================================================================
template<class TFence>
void eve::thr::ScopedFence<TFence>::unlock(void)
{
	m_pFence->unlock();
	m_pFence = nullptr;
}

#endif // __EVE_THREADING_SCOPED_FENCE_H__

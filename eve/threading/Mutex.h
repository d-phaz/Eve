
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
#ifndef __EVE_THREADING_MUTEX_H__
#define __EVE_THREADING_MUTEX_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "memory/Includes.h"
#endif


namespace eve
{
	namespace threading
	{

		/**
		* @class threading::Mutex
		* @brief provides base native Mutex
		* @note extends memory::Pointer
		*/
		class Mutex
			: public eve::memory::Pointer
		{

			friend class eve::memory::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			void *		m_mutex;		//<! Mutex handle


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Mutex)
			EVE_PROTECT_DESTRUCTOR(Mutex)

		public:		
			/** Mutex class constructor. */
			Mutex(void);


		protected:
			/** Alloc and init class members, initialize base mutex. (pure virtual) */
			virtual void init(void);
			/** Release and delete class members, making sure mutex is unlocked. (pure virtual) */
			virtual void release(void);


		public:
			/** Lock the mutex variable. */
			void lock(void);
			/** Unlock the mutex variable. */
			void unlock(void);

		}; // class Mutex

	} // namespace threading

} // namespace eve

#endif // __EVE_THREADING_MUTEX_H__

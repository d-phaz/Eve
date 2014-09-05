
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
#ifndef __EVE_THREADING_LOCK_H__
#define __EVE_THREADING_LOCK_H__  

#ifndef __EVE_CORE_INCLUDES_H__
#include "core/Includes.h"
#endif


namespace eve
{
	namespace threading
	{

		/** 
		* @class threading::Lock
		* @brief lock using critical section
		*/
		class Lock
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:
			CRITICAL_SECTION		m_criticalSections;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////
        
		public:
			/** Construct a new lock. */
			Lock(void);
			/** Destruct the lock. */
			virtual ~Lock(void);


			/** Acquire the lock. */
			void lock(void);
			/** Release the lock. */
			void unlock(void);

		}; // class Lock

	} // namespace threading

} // namespace eve

#endif // __EVE_THREADING_LOCK_H__

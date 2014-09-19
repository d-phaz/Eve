
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
#ifndef __EVE_THREADING_UTILS_H__
#define __EVE_THREADING_UTILS_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

namespace eve
{
	namespace thr
	{
		/**
		* \brief Sleep thread for given amount of milliseconds.
		* \param p_milliseconds milliseconds amount to sleep.
		*/
		void sleep_milli(const int32_t p_milliseconds);
		/**
		* \brief Sleep thread for given amount of iterations, switch hand to other threads.
		* \param p_iters iterations amount.
		*/
		void sleep_iter(uint32_t p_iters);
		/**
		* \brief Sleep thread for given amount of micro seconds, switch hand to other threads.
		* \param p_ticks target ticks amount.
		*/
		void sleep_micro(uint64_t p_ticks);


		/**
		* \brief Get current thread ID.
		* \return id as DWORD.
		*/
		DWORD current_thread_ID(void);
		/** 
		* \brief Get current thread handle (void*).
		* \return handle as HANDLE (void*).
		*/
		HANDLE current_thread_handle(void);
		/**
		* \brief Compare thread ID (inLeft == inRight) and return true if they are equal. 
		* On some Operating System(s) DWORD is a struct so == will not work.
		*/
		bool equal_ID(DWORD inLeft, DWORD inRight);
		/**
		* \brief Return a zeroed out thread ID. On some Operating System(s) DWORD is a struct so == 0 will not work.
		*/
		DWORD zero_ID(void);

	} // namespace thr

} // namespace eve

#endif // __EVE_THREADING_UTILS_H__

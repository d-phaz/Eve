
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

// Main header
#include "Eve/threading/Utils.h"




//=================================================================================================
namespace eve 
{
	namespace threading
	{
		/** 
		 * \struct eve::threading::SleepEvent
		 * \brief simple system event HANDLE used by sleep method.
		 */
		struct SleepEvent
		{
			SleepEvent()
			: handle(::CreateEventW(0, 0, 0, 0))
			{
				EVE_ASSERT(handle)
			}

			HANDLE handle;
		};
	}
}
static eve::threading::SleepEvent sleepEvent;

//=================================================================================================
void eve::threading::sleep_milli(const int32_t p_milliseconds)
{
	if (p_milliseconds >= 10)
	{
		::Sleep(p_milliseconds);
	}
	else
	{
		// unlike Sleep() this is guaranteed to return to the current thread after
		// the time expires, so we'll use this for short waits, which are more likely
		// to need to be accurate
		::WaitForSingleObject(sleepEvent.handle, p_milliseconds);
	}
}

//=================================================================================================
void eve::threading::sleep_iter(uint32_t p_iters)
{
	for (uint32_t i = 0; i < p_iters; i++)
	{
		::SwitchToThread();
		//std::this_thread::yield();
	}
}

//=================================================================================================
void eve::threading::sleep_micro(uint64_t p_ticks)
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER currentTime;
	LARGE_INTEGER endTime;

	::QueryPerformanceCounter(&endTime);

	// Ticks in microseconds (1/1000 ms)
	::QueryPerformanceFrequency(&frequency);
	endTime.QuadPart += (p_ticks * frequency.QuadPart) / (1000ULL * 1000ULL);

	do
	{
		::SwitchToThread();
		//std::this_thread::yield();

		::QueryPerformanceCounter(&currentTime);

	} while (currentTime.QuadPart < endTime.QuadPart);
}



//=================================================================================================
DWORD eve::threading::current_thread_ID(void)
{
	return ::GetCurrentThreadId();
}

//=================================================================================================
bool eve::threading::equal_ID(DWORD inLeft, DWORD inRight)
{
	return(memcmp(&inLeft, &inRight, sizeof(inLeft)) == 0);
}

//=================================================================================================
DWORD eve::threading::zero_ID(void)
{
	DWORD a;
	memset(&a, 0, sizeof(a));
	return a;
}

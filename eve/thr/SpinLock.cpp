
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

// Main header
#include "eve/thr/SpinLock.h"

#ifndef __EVE_SYSTEM_INFO_H__
#include "eve/sys/win32/Info.h"
#endif

#ifndef __EVE_MESSAGING_SERVER_H__
#include "eve/mess/Server.h"
#endif


#define YIELD_ITERATION 30
#define SLEEP_ITERATION 40


//=================================================================================================
eve::thr::SpinLock::SpinLock(void)
	// Inheritance
	: eve::thr::Fence()
	// Members init
	//, m_state() // kept for future use

	, m_dest(0)
	, m_exchange(100)
	, m_compare(0)
	, m_iter(0)
	, m_bMultiProc(false)
{}



//=================================================================================================
void eve::thr::SpinLock::init(void)
{
	m_bMultiProc = (eve::sys::get_logical_processor_num() > 1);
	//m_state.clear(); // kept for future use
}

//=================================================================================================
void eve::thr::SpinLock::release(void)
{
	//m_state.clear(); // kept for future use
}



//=================================================================================================
void eve::thr::SpinLock::lock(void)
{
	m_iter = 0;
	while (true)
	{
		// A thread already owning the lock shouldn't be allowed to wait to acquire the lock - re-entrant safe
		if (m_dest == eve::thr::current_thread_ID())
			break;
		/*
		Spinning in a loop of interlocked calls can reduce the available memory bandwidth and slow down the rest of the system. 
		Interlocked calls are expensive in their use of the system memory bus. 
		It is better to see if the 'm_dest' value is what it is expected and then retry interlock.
		*/
		if (::InterlockedCompareExchange(&m_dest, m_exchange, m_compare) == 0)
		{
			// Assign CurrentThreadId to m_dest to make it re-entrant safe.
			m_dest = eve::thr::current_thread_ID();
			// lock acquired 
			break;
		}

		// Spin wait to acquire 
		while (m_dest != m_compare)
		{
			if (m_iter >= YIELD_ITERATION)
			{
				// Sleep(0) will result in a context switch if a higher priority thread is in ready state.
				if (m_iter + YIELD_ITERATION >= SLEEP_ITERATION) 
				{
					::Sleep(0);
				}

				if (m_iter >= YIELD_ITERATION && m_iter < SLEEP_ITERATION)
				{
					m_iter = 0;
					::SwitchToThread();
				}
			}

			// Yield processor on multi-processor but if on single processor then give other thread the CPU.
			m_iter++;
			if (m_bMultiProc) 
			{ 
				::YieldProcessor(/*no op*/); 
			}
			else 
			{ 
				::SwitchToThread(); 
			}
		}
	}

	// while (m_state.test_and_set(std::memory_order_acquire)) // kept for future use
}

//=================================================================================================
void eve::thr::SpinLock::unlock(void)
{
#if !defined(NDEBUG)
	if (m_dest != eve::thr::current_thread_ID())
	{
		EVE_LOG_ERROR("Unexpected thread-id in release");
	}
#endif
	// lock released
	::InterlockedCompareExchange(&m_dest, m_compare, eve::thr::current_thread_ID());


	//m_state.clear(std::memory_order_release); // kept for future use
}

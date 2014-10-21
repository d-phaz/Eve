
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
#include "eve/time/Clock.h"


//=================================================================================================
eve::time::Clock::Clock(void)

	// Inheritance
	: eve::thr::Thread()

	// Members init
	, m_pTimer(nullptr)
	, m_intervalPeriod(0)
	, m_intervalSleep(0)

	, m_event()
{}



//=================================================================================================
void eve::time::Clock::init(void)
{
	// Call parent class.
	eve::thr::Thread::init();

	m_pTimer = EVE_CREATE_PTR(eve::time::Timer);
}

//=================================================================================================
void eve::time::Clock::release(void)
{
	EVE_RELEASE_PTR(m_pTimer);

	// Call parent class.
	eve::thr::Thread::release();
}



//=================================================================================================
void eve::time::Clock::initThreadedData(void)
{
	// Launch timer.
	m_pTimer->restart();
}

//=================================================================================================
void eve::time::Clock::releaseThreadedData(void)
{
	// Nothing to do for now.
}



//=================================================================================================
void eve::time::Clock::run(void)
{
	do
	{		
		m_pFence->lock();
		
		// Dispatch event.
		eve::evt::notify_event(m_event);
		// Compute elapsed time
		m_intervalSleep = (m_intervalPeriod + m_intervalSleep) - m_pTimer->getElapsedTime();
		
		m_pFence->unlock();


		// Restart timer.
		m_pTimer->restart();

		// Sleep for varying interval.
		if (m_intervalSleep > 0)
		{
			eve::thr::sleep_micro(m_intervalSleep * 1000);
		}

	} while (this->running());
}



//=================================================================================================
void eve::time::Clock::restart(void)
{
	if (!this->started())
	{
		this->start();
	}
#if !defined(NDEBUG)
	else
	{
		EVE_LOG_WARNING("Clock already running");
	}
#endif
}

//=================================================================================================
void eve::time::Clock::restart(int64_t p_milliseconds)
{
	if (!this->started())
	{
		m_intervalPeriod = p_milliseconds;
		this->start();
	}
#if !defined(NDEBUG)
	else
	{
		EVE_LOG_WARNING("Clock already running");
	}
#endif
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::time::Clock::setPeriodicInterval(int64_t p_milliseconds)
{
	EVE_ASSERT(p_milliseconds > 0);

	m_pFence->lock();
	m_intervalPeriod = p_milliseconds;
	m_pFence->unlock();
}

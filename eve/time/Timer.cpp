
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
#include "eve/time/Timer.h"


//=================================================================================================
eve::time::Timer * eve::time::Timer::create_ptr(bool p_start)
{
	eve::time::Timer * ptr = EVE_CREATE_PTR(eve::time::Timer);

	if (p_start) {
		ptr->start();
	}

	return ptr;
}



//=================================================================================================
eve::time::Timer::Timer(void)
	// Inheritance
	: eve::mem::Pointer()
	// members init
	, m_milliStartTime(0)
	, m_milliEndTime(0)
	, m_milliElapsed(0)
	, m_invFrequency(1.0)
	, m_bRunning(false)
{}

//=================================================================================================
eve::time::Timer::Timer(const Timer & p_other)
	// Inheritance
	: eve::mem::Pointer()
	// members init
	, m_milliStartTime(p_other.m_milliStartTime)
	, m_milliEndTime(p_other.m_milliEndTime)
	, m_milliElapsed(p_other.m_milliElapsed)
	, m_invFrequency(p_other.m_invFrequency)
	, m_bRunning(false)
{
	if (p_other.m_bRunning)
	{
		start();
	}
}

//=================================================================================================
eve::time::Timer & eve::time::Timer::operator = (const eve::time::Timer & p_other)
{
	if (&p_other != this)
	{
		m_milliStartTime = p_other.m_milliStartTime;
		m_milliEndTime = p_other.m_milliEndTime;
		m_milliElapsed = p_other.m_milliElapsed;
		m_invFrequency = p_other.m_invFrequency;

		if (p_other.m_bRunning) {
			this->start();
		}
	}

	return *this;
}



//=================================================================================================
void eve::time::Timer::init(void)
{
#if defined(EVE_OS_WIN)
	const MMRESULT res = ::timeBeginPeriod(1);
	EVE_ASSERT(res == TIMERR_NOERROR);

	// The frequency of the performance counter is fixed at system boot and is consistent across all processors. 
	// Therefore, the frequency need only be queried upon application initialization, and the result can be cached.
	::LARGE_INTEGER nativeFreq;
	::QueryPerformanceFrequency(&nativeFreq);

	m_invFrequency = 1.0000 / nativeFreq.QuadPart;

#elif defined(EVE_OS_DARWIN)
	uint64_t numerator;
	uint64_t denominator;

	mach_timebase_info_data_t timebase;
	mach_timebase_info(&timebase);

	if (timebase.numer % 1000000 == 0)
	{
		numerator   = timebase.numer / 1000000;
		denominator = timebase.denom;
	}
	else
	{
		numerator   = timebase.numer;
		denominator = timebase.denom * 1000000ULL;
	}

	m_invFrequency = numerator / static_cast<double>(denominator);

#elif defined(EVE_OS_LINUX)
	// Nothing to do for now.

#endif
}

//=================================================================================================
void eve::time::Timer::release(void)
{
#if defined(EVE_OS_WIN)
	const MMRESULT res = ::timeEndPeriod(1);
	EVE_ASSERT(res == TIMERR_NOERROR);

#elif defined(EVE_OS_DARWIN)
	// Nothing to do for now.

#elif defined(EVE_OS_LINUX)
	// Nothing to do for now.

#endif
}



//=================================================================================================
void eve::time::Timer::start(void)
{
#if defined(EVE_OS_WIN)
	::LARGE_INTEGER rawTime;
	::QueryPerformanceCounter(&rawTime);
	m_milliStartTime = static_cast<int64_t>(rawTime.QuadPart * m_invFrequency);

#elif defined(EVE_OS_DARWIN)
	m_milliStartTime = static_cast<int64_t>(mach_absolute_time() * m_invFrequency);

#elif defined(EVE_OS_LINUX)
	timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	m_milliStartTime = static_cast<int64_t>(t.tv_sec * 1000 + t.tv_nsec / 1000000);

#endif

	m_bRunning = true;
}

//=================================================================================================
void eve::time::Timer::stop(void)
{
#if defined(EVE_OS_WIN)
	::LARGE_INTEGER rawTime;
	::QueryPerformanceCounter(&rawTime);
	m_milliEndTime = static_cast<int64_t>(rawTime.QuadPart * m_invFrequency);

#elif defined(EVE_OS_DARWIN)
	m_milliEndTime = static_cast<int64_t>(mach_absolute_time() * m_invFrequency);

#elif defined(EVE_OS_LINUX)
	timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	m_milliEndTime = static_cast<int64_t>(t.tv_sec * 1000 + t.tv_nsec / 1000000);

#endif

	m_bRunning = false;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
int64_t eve::time::Timer::getElapsedTime(void)
{
	if (this->isStopped())
	{
		m_milliElapsed = m_milliEndTime - m_milliStartTime;
	}
	else
	{
#if defined(EVE_OS_WIN)
		::LARGE_INTEGER rawTime;
		::QueryPerformanceCounter(&rawTime);
		m_milliElapsed = static_cast<int64_t>((rawTime.QuadPart * m_invFrequency) - m_milliStartTime);

#elif defined(EVE_OS_DARWIN)
		m_milliElapsed = static_cast<int64_t>((mach_absolute_time() * m_invFrequency) - m_milliStartTime);

#elif defined(EVE_OS_LINUX)
		timespec t;
		clock_gettime(CLOCK_MONOTONIC, &t);
		m_milliElapsed = static_cast<int64_t>((t.tv_sec * 1000 + t.tv_nsec / 1000000) - m_milliStartTime);

#endif
	}

	return m_milliElapsed;
}


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

#ifndef __EVE_MATH_INCLUDES_H__
#include "eve/math/Includes.h"
#endif


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
	, m_startTime(0)
	, m_endTime(0)
	, m_elapsed(0)
	, m_oldTime(0)
	, m_invFrequency(1.0)
	, m_bRunning(false)
	, m_fFPS(0.0f)
	, m_fTargetFPS(60.0f)
	, m_fTime1(0.0f)
	, m_fTime2(0.0f)
	, m_fDiffTimeNextFrame(0)
	, m_fDiffTime(0.0f)
	, m_iFramesElapsed(0)
	, m_iFramesCompuation(3)
{}

//=================================================================================================
eve::time::Timer::Timer(const Timer & p_other)
	// Inheritance
	: eve::mem::Pointer()
	// members init
	, m_startTime(p_other.m_startTime)
	, m_endTime(p_other.m_endTime)
	, m_elapsed(p_other.m_elapsed)
	, m_invFrequency(p_other.m_invFrequency)
	, m_oldTime(p_other.m_oldTime)
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
		m_startTime		= p_other.m_startTime;
		m_endTime		= p_other.m_endTime;
		m_elapsed		= p_other.m_elapsed;
		m_invFrequency	= p_other.m_invFrequency;

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
	// The frequency of the performance counter is fixed at system boot and is consistent across all processors. 
	// Therefore, the frequency need only be queried upon application initialization, and the result can be cached.
	::LARGE_INTEGER nativeFreq;
	if (::QueryPerformanceFrequency(&nativeFreq) == 0)
	{
		EVE_LOG_ERROR("Unable to retrieve time, QueryPerformanceFrequency() failed, %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
	m_invFrequency = (1.0 / static_cast<double>(nativeFreq.QuadPart));
	m_i64PerformanceTimerStart = eve::time::Timer::query_absolute_time();
	 

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

	timespec t;
	if( clock_gettime(CLOCK_MONOTONIC, &t) != 0 )
	{
		EVE_LOG_ERROR("Unable to retrieve time, clock_gettime() failed, %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
	m_i64PerformanceTimerStart = static_cast<int64_t>(t.tv_sec * 1000 + t.tv_nsec / 1000000);

#elif defined(EVE_OS_LINUX)
	m_invFrequency = 0.001;

#endif
}

//=================================================================================================
void eve::time::Timer::release(void)
{
#if defined(EVE_OS_WIN)
	// Nothing to do for now.

#elif defined(EVE_OS_DARWIN)
	// Nothing to do for now.

#elif defined(EVE_OS_LINUX)
	// Nothing to do for now.

#endif
}



//=================================================================================================
int64_t eve::time::Timer::query_absolute_time(void)
{
#if defined(EVE_OS_WIN)
	::LARGE_INTEGER rawTime;
	if (::QueryPerformanceCounter(&rawTime) == 0) 
	{
		EVE_LOG_ERROR("Unable to retrieve time, QueryPerformanceCounter() failed, %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	return static_cast<int64_t>(rawTime.QuadPart);

#elif defined(EVE_OS_DARWIN)
	return static_cast<int64_t>(mach_absolute_time())

#elif defined(EVE_OS_LINUX)
	timespec t;
	if( clock_gettime(CLOCK_MONOTONIC, &t) != 0 )
	{
		EVE_LOG_ERROR("Unable to retrieve time, clock_gettime() failed, %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
	int64_t ret = static_cast<int64_t>(t.tv_sec * 1000 + t.tv_nsec / 1000000);
	return (ret / 1000);

#endif
}



//=================================================================================================
void eve::time::Timer::start(void)
{
	m_startTime = eve::time::Timer::query_absolute_time();
	m_bRunning = true;
}

//=================================================================================================
void eve::time::Timer::stop(void)
{
	m_endTime = eve::time::Timer::query_absolute_time();
	m_bRunning = false;
}

//=================================================================================================
int64_t eve::time::Timer::restart(void)
{
	m_endTime	= eve::time::Timer::query_absolute_time();
	m_elapsed	= static_cast<int64_t>((m_endTime - m_startTime) * 1000.0 * m_invFrequency);
	m_startTime = m_endTime;
	m_bRunning	= true;

	return m_elapsed;
}



//=================================================================================================
void eve::time::Timer::updateFPS(bool p_bincreaseFrame)
{
	//increase the number of frames that have passed
	if (p_bincreaseFrame)
		m_iFramesElapsed++;

	if (p_bincreaseFrame && m_iFramesElapsed % m_iFramesCompuation == 1)
	{
		m_fTime1 = static_cast<float>(getTime());
	}

	else if (!p_bincreaseFrame || m_iFramesElapsed % m_iFramesCompuation == 0)
	{
		if (p_bincreaseFrame)
			m_fTime1 = m_fTime2;

		m_fTime2 = static_cast<float>(getTime());
		m_fDiffTime = eve::math::abs(m_fTime2 - m_fTime1) / 1000;

	}

	if (m_fDiffTime > 0.0f)
	{
		m_fFPS = m_iFramesCompuation / (m_fDiffTime);
		m_fDiffTimeNextFrame = static_cast<int64_t>((m_iFramesCompuation / m_fTargetFPS - m_fDiffTime) * 1000);

		if (m_fDiffTimeNextFrame <= 0)
			m_fDiffTimeNextFrame = 0;
	}
	else
		m_fFPS = 0.0f;

	/*m_fTime2   = GetTime( )/1000;
	m_fDiffTime= ( float )fabs( m_fTime2-m_fTime1 );
	if (m_fDiffTime > 1.0f)
	{
	m_fTime1 = m_fTime2;
	m_fFPS= m_iFramesElapsed / ( m_fDiffTime );
	m_iFramesElapsed = 0;
	}
	*/
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
const int64_t eve::time::Timer::getElapsedTime(void) 
{
	if (this->isStopped())
	{
		m_elapsed = static_cast<int64_t>((m_endTime - m_startTime) * 1000.0 * m_invFrequency);
	}
	else
	{
		m_elapsed = static_cast<int64_t>((eve::time::Timer::query_absolute_time() - m_startTime) * 1000.0 * m_invFrequency);
	}

	return m_elapsed;
}



//=================================================================================================
const int64_t eve::time::Timer::getTime(void)  const
{

	return static_cast<int64_t>((query_absolute_time() - m_i64PerformanceTimerStart) * 1000 * m_invFrequency);

}


//=================================================================================================
const int64_t eve::time::Timer::getDiffTime(void) 
{
	if (this->isStopped())
	{
		m_elapsed = static_cast<int64_t>((m_endTime - m_startTime) * 1000.0 * m_invFrequency);
	}
	else
	{
		m_elapsed = static_cast<int64_t>((eve::time::Timer::query_absolute_time() - m_startTime) * 1000.0 * m_invFrequency);
	}

	return m_elapsed;
}

//=================================================================================================
const int64_t eve::time::Timer::getDiffTimeDelta(void) 
{
	int64_t timeDiff;
	if (this->isStopped())
	{
		m_elapsed = static_cast<int64_t>((m_endTime - m_startTime) * 1000.0 * m_invFrequency);
		timeDiff = m_elapsed;
	}
	else
	{
		m_elapsed = static_cast<int64_t>((eve::time::Timer::query_absolute_time() - m_startTime) * 1000.0 * m_invFrequency);
		timeDiff = m_elapsed - m_oldTime;
		m_oldTime = m_elapsed;
	}

	return timeDiff;
}

//=================================================================================================
const int64_t eve::time::Timer::getDiffTimeDeltaWithoutactualisation(void) 
{
	int64_t timeDiff;
	if (this->isStopped())
	{
		m_elapsed = static_cast<int64_t>((m_endTime - m_startTime) * 1000.0 * m_invFrequency);
		timeDiff = m_elapsed;
	}
	else
	{
		m_elapsed = static_cast<int64_t>((eve::time::Timer::query_absolute_time() - m_startTime) * 1000.0 * m_invFrequency);
		timeDiff = m_elapsed - m_oldTime;
	}

	return timeDiff;
}

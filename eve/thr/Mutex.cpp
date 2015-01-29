
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
#include "eve/thr/Mutex.h"


//=============================================================================================
eve::thr::Mutex::Mutex(void)
	// Inheritance
	: eve::thr::Fence()
	// Members init
	, m_mutex(0)
{}



//=================================================================================================
void eve::thr::Mutex::init(void)
{
#if defined(EVE_OS_WIN)
	m_mutex = ::CreateMutexW(NULL, false, NULL);

#elif defined(EVE_OS_DARWIN)
	if (pthread_mutex_init(&m_mutex, 0) != 0)
	{
		EVE_LOG_ERROR("Unable to create mutex pthread_mutex_init() failed.");
		EVE_ASSERT_FAILURE;
	}

#endif
}

//=================================================================================================
void eve::thr::Mutex::release(void)
{
#if defined(EVE_OS_WIN)
	::CloseHandle(m_mutex);

#elif defined(EVE_OS_DARWIN)
	if (pthread_mutex_destroy(&m_mutex) != 0) 
	{
		EVE_LOG_ERROR("Unable to release mutex pthread_mutex_destroy() failed.");
		EVE_ASSERT_FAILURE;
	}

#endif
}



//=============================================================================================
void eve::thr::Mutex::lock(void)
{
#if defined(EVE_OS_WIN)
	::WaitForSingleObjectEx(m_mutex, INFINITE, FALSE);

#elif defined(EVE_OS_DARWIN)
	if (pthread_mutex_lock(&m_mutex) != 0)
	{
		EVE_LOG_ERROR("Unable to lock mutex pthread_mutex_lock() failed.");
		EVE_ASSERT_FAILURE;
	}

#endif
}

//=============================================================================================
void eve::thr::Mutex::unlock(void)
{
#if defined(EVE_OS_WIN)
	::ReleaseMutex(m_mutex);

#elif defined(EVE_OS_DARWIN)
	if (pthread_mutex_unlock(&m_mutex) != 0)
	{
		EVE_LOG_ERROR("Unable to unlock mutex pthread_mutex_unlock() failed.");
		EVE_ASSERT_FAILURE;
	}

#endif
}

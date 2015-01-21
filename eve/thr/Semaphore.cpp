
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
#include "eve/thr/Semaphore.h"

#ifndef __EVE_SYSTEM_INFO_H__
#include "eve/sys/win32/Info.h"
#endif

#ifndef __EVE_MESSAGING_SERVER_H__
#include "eve/mess/Server.h"
#endif


//=================================================================================================
eve::thr::Semaphore::Semaphore(void)
	// Inheritance
	: eve::thr::Fence()
	
	// Members init
	, m_dest(0)
	, m_exchange(100)
	, m_compare(0)
	, m_iter(0)
	, m_bMultiProc(false)
{}

//=================================================================================================
void eve::thr::Semaphore::init(void)
{
	m_hSemaphore = ::CreateSemaphore(NULL,			// No security attributes 
									1L,				// Initial count
									1L,				// Maximum count
									NULL);			// Unnamed semaphore	
}

//=================================================================================================
void eve::thr::Semaphore::release(void)
{
	::CloseHandle(m_hSemaphore);
}



//=================================================================================================
void eve::thr::Semaphore::lock(void)
{
	DWORD dwWaitResult;

	// Try to enter the semaphore gate.
	dwWaitResult = ::WaitForSingleObject(m_hSemaphore, INFINITE);

	switch (dwWaitResult)
	{
		// The semaphore object was signaled.
	case WAIT_OBJECT_0:
		break;

		// The semaphore was non-signaled, so a time-out occurred.
	case WAIT_FAILED:
	case WAIT_TIMEOUT:
		EVE_LOG_ERROR("WaitForSingleObject() failed with error: %s", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE;
		break;
	}

}

//=================================================================================================
void eve::thr::Semaphore::unlock(void)
{
	if (!::ReleaseSemaphore(m_hSemaphore,  // handle to semaphore
							1,            // increase count by one
							NULL))       // not interested in previous count
	{
		EVE_LOG_ERROR("ReleaseSemaphore() failed with error: %s", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE;
	}
}



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
#include "eve/thr/Thread.h"

#include <process.h>

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 

#ifndef __EVE_THREADING_UTILS_H__
#include "eve/thr/Utils.h"
#endif


//=================================================================================================
eve::thr::Thread::Thread( void )

	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_hThread( nullptr )
	, m_hShutdownEvent( 0 )
	, m_StartEvent( 0 )
	, m_runWait( 10 )
	, m_threadID( eve::thr::zero_ID() )

	, m_pFence(nullptr)
{}



//=================================================================================================
void eve::thr::Thread::init(void)
{
	m_pFence			= EVE_CREATE_PTR(eve::thr::SpinLock);

	m_hShutdownEvent	= ::CreateEvent(NULL, TRUE, FALSE, NULL);
	m_StartEvent		= ::CreateEvent(NULL, TRUE, FALSE, NULL);


	// Spawn new thread. Thread is suspended until start() is called.
	m_hThread = (HANDLE)_beginthreadex(
		NULL,							// LPSECURITY_ATTRIBUTES lpThreadAttributes,	// pointer to security attributes
		0,								// DWORD dwStackSize,							// initial thread stack size
		&eve::thr::Thread::routine,		// LPTHREAD_START_ROUTINE lpStartAddress,		// pointer to thread function
		this,							// LPVOID lpParameter,							// argument for new thread
		CREATE_SUSPENDED,				// DWORD dwCreationFlags,						// creation flags
		(unsigned*)&m_threadID			// LPDWORD lpThreadId							// pointer to receive thread ID
		);
	EVE_ASSERT(m_hThread);

	//m_hThread = new std::thread(run_wrapper, this);
	//m_threadID = m_hThread->get_id();
	//EVE_ASSERT(m_hThread);
}

//=================================================================================================
void eve::thr::Thread::release(void)
{	
	this->stop();
	this->detach();

	::CloseHandle(m_hShutdownEvent);
	::CloseHandle(m_StartEvent);

	EVE_RELEASE_PTR(m_pFence);
}



//=================================================================================================
void eve::thr::Thread::start(void)
{
	EVE_ASSERT(!eve::thr::equal_ID(m_threadID, eve::thr::zero_ID()));
	
	// Resume thread execution
	if (::ResumeThread(m_hThread) == (DWORD)-1)
	{
		EVE_LOG_ERROR("Unable to resume thread, error is %s", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE
	}
}



//=================================================================================================
uint32_t eve::thr::Thread::routine(void * p_pThread)
{
	EVE_ASSERT(p_pThread);

	// Grab and cast thread pointer.
	eve::thr::Thread * objectPtr = reinterpret_cast<eve::thr::Thread*>(p_pThread);

	// Alloc and init threaded data.
	objectPtr->initThreadedData();
	// Since initialized, set status to started.
	objectPtr->setStarted();

	// Run thread (pure virtual function).
	objectPtr->run();

	// Release and delete threaded data.
	objectPtr->releaseThreadedData();
	// Since we're out of run loop set status to not started.
	objectPtr->resetStarted();

	// No error occurred so return 0 (zero).
	return 0;
}



//=================================================================================================
bool eve::thr::Thread::join(void)
{
	bool bReturn = false;

	if (!eve::thr::equal_ID(m_threadID, eve::thr::zero_ID()))
	{
		DWORD exitCode;
		do
		{
			if(::GetExitCodeThread(m_hThread, &exitCode) != 0)
			{
				if (exitCode == STILL_ACTIVE)
				{
					if (::WaitForSingleObject(m_hThread, INFINITE) != WAIT_OBJECT_0) 
					{
						EVE_LOG_ERROR("Cannot join thread WaitForSingleObject() failed, error: %s", eve::mess::get_error_msg());
						EVE_ASSERT_FAILURE;
					}
				}
				else
				{
					bReturn = true;
					break;
				}
			}
			else
			{
				bReturn = false;
				EVE_LOG_ERROR("Unable to retrieve thread exit code GetExitCodeThread() failed, error: %s", eve::mess::get_error_msg());
				EVE_ASSERT_FAILURE;
				break;
			}
		} while (true);
	} 
	// Thread already terminated
	else {
		bReturn = true;
	}

	return bReturn;
}

//=================================================================================================
void eve::thr::Thread::stop(void)
{
	EVE_ASSERT(m_hThread)

	if (!eve::thr::equal_ID(m_threadID, eve::thr::zero_ID()))
	{
		// Signal the thread to exit.
		::SetEvent(m_hShutdownEvent);
		// Thread may be suspended, so resume before shutting down.
		::ResumeThread(m_hThread);

		// Join thread (wait for loop completion).
		this->join();

		// Reset the shutdown event.
		::ResetEvent(m_hShutdownEvent);
	}
}

//=================================================================================================
void eve::thr::Thread::detach( void )
{
	EVE_ASSERT(m_hThread);

	// Close thread handle (aka detach).
	::CloseHandle(m_hThread);
	m_hThread = 0;
	// Reset thread ID.
	m_threadID = eve::thr::zero_ID();
	
	// Kept for future use
	//m_hThread->detach();
	//delete m_hThread;
	//m_hThread = nullptr;	
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::thr::Thread::setStarted(void)
{
	::SetEvent(m_StartEvent);
}

//=================================================================================================
void eve::thr::Thread::resetStarted(void)
{
	::SetEvent(m_StartEvent);
}



//=================================================================================================
bool eve::thr::Thread::getPriority( priorities & p_priority ) 
{

	bool result = true;

	// Convert to one of the priority values
	switch( ::GetThreadPriority(m_hThread) ) 
	{
		case THREAD_PRIORITY_ERROR_RETURN:		result = false;

		case THREAD_PRIORITY_IDLE:				p_priority = IdlePriority;			break;
		case THREAD_PRIORITY_LOWEST:			p_priority = LowestPriority;		break;
		case THREAD_PRIORITY_BELOW_NORMAL:		p_priority = LowPriority;			break;
		case THREAD_PRIORITY_NORMAL:			p_priority = NormalPriority;		break;
		case THREAD_PRIORITY_ABOVE_NORMAL:		p_priority = HighPriority;			break;
		case THREAD_PRIORITY_HIGHEST:			p_priority = HighestPriority;		break;
		case THREAD_PRIORITY_TIME_CRITICAL:		p_priority = TimeCriticalPriority;	break;
	}

	return result;
}

//=================================================================================================
bool eve::thr::Thread::setPriority( priorities p_priority )
{
	bool ret = !(this->started());

	if (ret)
	{
		int32_t prio;
		switch (p_priority)
		{
		case IdlePriority:			prio = THREAD_PRIORITY_IDLE;						break;
		case LowestPriority:		prio = THREAD_PRIORITY_LOWEST;						break;
		case LowPriority:			prio = THREAD_PRIORITY_BELOW_NORMAL;				break;
		case NormalPriority:		prio = THREAD_PRIORITY_NORMAL;						break;
		case HighPriority:			prio = THREAD_PRIORITY_ABOVE_NORMAL;				break;
		case HighestPriority:		prio = THREAD_PRIORITY_HIGHEST;						break;
		case TimeCriticalPriority:	prio = THREAD_PRIORITY_TIME_CRITICAL;				break;

		case InheritPriority:
		default:					prio = ::GetThreadPriority(::GetCurrentThread());	break;
		}

		ret = (::SetThreadPriority(m_hThread, prio) != THREAD_PRIORITY_ERROR_RETURN);
		EVE_ASSERT(ret)
	}

	return ret;
}



//=================================================================================================
bool eve::thr::Thread::running( void )
{
	bool bret = false;
	
	if( WAIT_TIMEOUT == ::WaitForSingleObject(m_hShutdownEvent, m_runWait) ) 
	{
		bret = true;
	}
	
	return bret;
}



//=================================================================================================
bool eve::thr::Thread::started( void )
{
	bool bret = false;

	if( WAIT_OBJECT_0 == ::WaitForSingleObject( m_StartEvent, 200000 ) ) 
	{
		bret = true;
	}

	return bret;
}



//=================================================================================================
bool eve::thr::Thread::setRunWait(uint32_t p_wait)
{
	bool ret = !(this->started());
	if (ret) {
		m_runWait = p_wait;
	}
	return ret;
}

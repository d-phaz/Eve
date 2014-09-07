
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
#include "Eve/threading/Thread.h"

#include <process.h>

#ifndef __EVE_THREADING_UTILS_H__
#include "Eve/threading/Utils.h"
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
//		eve::threading::Thread class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::threading::Thread::Thread( void )

	// Inheritance
	: eve::memory::Pointer()

	// Members init
	, m_hThread			( nullptr )
	, m_hShutdownEvent	( 0 )
	, m_StartEvent		( 0 )
	, m_runWait			( 5 ) // milliseconds
	, m_threadID		( eve::threading::zero_ID() )
{}



//=================================================================================================
void eve::threading::Thread::init(void)
{
	m_hShutdownEvent	= ::CreateEvent(NULL, TRUE, FALSE, NULL);
	m_StartEvent		= ::CreateEvent(NULL, TRUE, FALSE, NULL);
}

//=================================================================================================
void eve::threading::Thread::release(void)
{
	this->stop();
	
	::CloseHandle(m_hShutdownEvent);
	::CloseHandle(m_StartEvent);
}



//=================================================================================================
uint32_t eve::threading::Thread::run_wrapper(void * p_pThread)
{
	EVE_ASSERT(p_pThread)

	// Grab and cast thread pointer.
	eve::threading::Thread * objectPtr = reinterpret_cast<eve::threading::Thread*>(p_pThread);

	// Initialize object local data.
	objectPtr->inThreadInit();
	// Since initialized, set status to started.
	objectPtr->setStarted();

	// Run thread (pure virtual function).
	objectPtr->run();

	// Uninitialize object local data.
	objectPtr->inThreadRelease();
	// Since we're out of run loop set status to not started.
	objectPtr->resetStarted();

	// No error occurred so return 0 (zero).
	return 0;
}



//=================================================================================================
void eve::threading::Thread::start(priorities p_priority)
{
	if (eve::threading::equal_ID(m_threadID, eve::threading::zero_ID()))
	{
		// Spawn new thread. Thread is suspended until priority is set.
		m_hThread = (std::thread*)_beginthreadex(
			NULL,							// LPSECURITY_ATTRIBUTES lpThreadAttributes,	// pointer to security attributes
			0,								// DWORD dwStackSize,							// initial thread stack size
			run_wrapper,					// LPTHREAD_START_ROUTINE lpStartAddress,		// pointer to thread function
			this,							// LPVOID lpParameter,							// argument for new thread
			CREATE_SUSPENDED,				// DWORD dwCreationFlags,						// creation flags
			(unsigned*)&m_threadID			// LPDWORD lpThreadId							// pointer to receive thread ID
			);
		EVE_ASSERT(m_hThread);

		// Set thread priority
		if (!setPriority(p_priority))
		{
			// LOG GetLastError
			EVE_ASSERT_FAILURE
		}

		if (::ResumeThread(m_hThread) == (DWORD)-1)
		{
			// LOG GetLastError.
			EVE_ASSERT_FAILURE
		}


		//m_hThread = new std::thread(run_wrapper, this);
		//m_threadID = m_hThread->get_id();
		//EVE_ASSERT(m_hThread);
	}
}



//=================================================================================================
void eve::threading::Thread::stop(void)
{
	EVE_ASSERT( m_hThread )
	
	this->terminate();
	this->complete();
	this->close();
}



//=================================================================================================
void eve::threading::Thread::terminate(void)
{
	if( m_hThread )
	{
		if (!eve::threading::equal_ID(m_threadID, eve::threading::zero_ID()))
		{
			// Signal the thread to exit
			::SetEvent( m_hShutdownEvent );
			// thread may be suspended, so resume before shutting down
			::ResumeThread( m_hThread );

			DWORD oldTID = m_threadID;

			// exit thread
			if (eve::threading::equal_ID(eve::threading::current_thread_ID(), oldTID))
			{
				// Wait for the thread to exit. If it doesn't shut down
				// on its own, force it closed with Terminate thread
				if( WAIT_TIMEOUT == ::WaitForSingleObject(m_hThread, 1000) ) 
				{
					::ExitThread( 0 );
				}
			} 
			else 
			{
				// this is a somewhat dangerous function; it's not
				// suggested to Stop() threads a lot.
				if( WAIT_TIMEOUT == ::WaitForSingleObject(m_hThread, 1000) ) 
				{
					if (::TerminateThread(m_hThread, 0) == 0)
					{
						// LOG GetLastError
						EVE_ASSERT_FAILURE
					}
				}
			}

			//// Close the handle and NULL it out
			//::CloseHandle( m_hThread );
			//m_hThread = NULL;
			//m_threadID = eve::threading::zero_ID();

			// Reset the shutdown event
			::ResetEvent( m_hShutdownEvent );
		}
	}
} // end Stop




//=================================================================================================
bool eve::threading::Thread::complete(void)
{
	bool bReturn = false;

	if (!eve::threading::equal_ID(m_threadID, eve::threading::zero_ID()))
	{
		DWORD exitCode;

		while (true)
		{
			if( ::GetExitCodeThread(m_hThread, &exitCode) != 0)
			{
				if (exitCode != STILL_ACTIVE)
				{
					bReturn = true;
					break;
				}
				else
				{
					::WaitForSingleObject( m_hThread, INFINITE );
					bReturn = true;
				}
			}
			else
			{
				bReturn = false;
				// log something here
				break;
			}
		} //while (true)
	} 
	// Thread already terminated
	else {
		bReturn = true;
	}

	return bReturn;
} 

//=================================================================================================
void eve::threading::Thread::close( void )
{
	if(m_hThread)
	{
		::CloseHandle(m_hThread);
		m_hThread = 0;
		
		//m_hThread->detach();
		//delete m_hThread;
		//m_hThread = nullptr;
	}
	m_threadID = eve::threading::zero_ID();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
bool eve::threading::Thread::getPriority( priorities & p_priority ) 
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
bool eve::threading::Thread::setPriority( priorities p_priority )
{
	bool ret = false;

	int32_t prio;
	switch( p_priority )
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

	return ret;
}



//=================================================================================================
bool eve::threading::Thread::running( void )
{
	bool bret = false;
	
	if( WAIT_TIMEOUT == ::WaitForSingleObject(m_hShutdownEvent, m_runWait) ) 
	{
		bret = true;
	}
	
	return bret;
}



//=================================================================================================
bool eve::threading::Thread::started( void )
{
	bool bret = false;

	if( WAIT_OBJECT_0 == ::WaitForSingleObject( m_StartEvent, 200000 ) ) 
	{
		bret = true;
	}

	return bret;
}

//=================================================================================================
void eve::threading::Thread::setStarted( void )
{
	::SetEvent( m_StartEvent );
}

//=================================================================================================
void eve::threading::Thread::resetStarted( void )
{
	::SetEvent( m_StartEvent );
}

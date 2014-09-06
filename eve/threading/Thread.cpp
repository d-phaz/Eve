
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

#ifndef __EVE_THREADING_MUTEX_H__
#include "Eve/threading/Mutex.h"
#endif

#ifndef __EVE_THREADING_LOCK_H__
#include "Eve/threading/Lock.h"
#endif 

#ifndef __EVE_THREADING_CONDITION_H__
#include "Eve/threading/Condition.h"
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//		Static
///////////////////////////////////////////////////////////////////////////////////////////////////

int32_t eve::threading::Thread::m_thread_number = 0;

eve::threading::Condition * eve::threading::Thread::m_num_cond = EVE_CREATE_PTR( eve::threading::Condition );



///////////////////////////////////////////////////////////////////////////////////////////////////
//		eve::threading::Thread class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::threading::Thread::Thread( void )

	// Inheritance
	: eve::memory::Pointer()

	// Members init
	, m_mutex			( nullptr )
	, m_hThread			( 0 )
	, m_hShutdownEvent(0)
	, m_StartEvent(0)
	, m_waiters			( 0 )
	, m_runWait			( 5 ) // milliseconds
	, m_threadID		( zero_ID() )

	, m_bRunning		( false )
	, m_bDeleteSelf		( false )
	, m_returnCode		( -1 )
	, m_priority		( Thread::InheritPriority )	
{}



//=================================================================================================
void eve::threading::Thread::init(void)
{
	m_mutex = EVE_CREATE_PTR( eve::threading::Mutex );

	m_hShutdownEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	m_StartEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
}

//=================================================================================================
void eve::threading::Thread::release(void)
{
	Stop();
	::CloseHandle(m_hThread);
	::CloseHandle(m_hShutdownEvent);
	::CloseHandle(m_StartEvent);
	m_threadID = zero_ID();

	EVE_RELEASE_PTR(m_mutex);
}



//=================================================================================================
uint32_t eve::threading::Thread::run_wrapper(void * p_pThread)
{
	EVE_ASSERT(p_pThread)

	// Grab and cast thread pointer
	eve::threading::Thread * objectPtr = (eve::threading::Thread *)p_pThread;

	// Initialize object local data
	objectPtr->inThreadInit();
	// Since initialized, set status to started
	objectPtr->setStarted();

	// Run thread (pure virtual function)
	objectPtr->Run();

	// Since we're out of run loop set status to not started
	objectPtr->resetStarted();
	// Uninitialize object local data
	objectPtr->inThreadRelease();


	// set TID to zero, then delete it
	// the zero TID causes Stop() in the destructor not to do anything
	objectPtr->m_threadID = zero_ID();
	// Delete pointer if asked for
	if (objectPtr->m_bDeleteSelf)
	{
		delete objectPtr;
		objectPtr = NULL;
	}


	// decrement thread count and send condition signal
	// do this after the object is destroyed, otherwise NT complains
	m_num_cond->lock();
	m_thread_number--;
	m_num_cond->signal();
	m_num_cond->unlock();


	return NULL;
}



//=================================================================================================
void eve::threading::Thread::Start(void)
{
	if (equal_ID(m_threadID, zero_ID()))
	{
		// increment thread count
		m_num_cond->lock();
		m_thread_number++;
		m_num_cond->unlock();

		Thread* ptr = this;

		// Win32 threads -- spawn new thread
		// Win32 has a thread handle in addition to the thread ID
		m_hThread = (HANDLE)_beginthreadex(
			NULL,								// LPSECURITY_ATTRIBUTES lpThreadAttributes,	// pointer to security attributes
			0,									// DWORD dwStackSize,							// initial thread stack size
			run_wrapper,						// LPTHREAD_START_ROUTINE lpStartAddress,		// pointer to thread function
			static_cast<LPVOID>(ptr),			// LPVOID lpParameter,							// argument for new thread
			0,									// DWORD dwCreationFlags,						// creation flags
			(unsigned*)&m_threadID				// LPDWORD lpThreadId							// pointer to receive thread ID
			);

		EVE_ASSERT(m_hThread);
	}
}



//=================================================================================================
void eve::threading::Thread::Stop(void)
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
		if ( !equal_ID(m_threadID, zero_ID()) ) 
		{
			// decrement thread count
			m_num_cond->lock();
			m_thread_number--;
			m_num_cond->signal();
			m_num_cond->unlock();

			// Signal the thread to exit
			::SetEvent( m_hShutdownEvent );

			// thread may be suspended, so resume before shutting down
			::ResumeThread( m_hThread );

			DWORD oldTID = m_threadID;

			// exit thread
			if( equal_ID(current_thread_ID(), oldTID) ) 
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
					::TerminateThread( m_hThread, 0 );
				}
			}

			// Close the handle and NULL it out
			::CloseHandle( m_hThread );
			m_hThread = NULL;
			m_threadID = zero_ID();

			// Reset the shutdown event
			::ResetEvent( m_hShutdownEvent );
		}
	}
} // end Stop




//=================================================================================================
bool eve::threading::Thread::complete(void)
{
	bool bReturn = false;

	if( !equal_ID(m_threadID, zero_ID()) ) 
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
void eve::threading::Thread::join_all( void ) 
{
	m_num_cond->lock();
	while ( m_thread_number > 0 ) 
	{
		m_num_cond->wait();
	}
	m_num_cond->unlock();
} 

//=================================================================================================
void eve::threading::Thread::close( void )
{
	if(m_hThread)
	{
		::CloseHandle(m_hThread);
		m_hThread = 0;
	}
	m_threadID = zero_ID();
}




//=================================================================================================
struct SleepEvent
{
	SleepEvent()
		: handle ( ::CreateEvent(0, 0, 0, 0) )
		// #endif
	{}

	HANDLE handle;
};
static SleepEvent sleepEvent;

//=================================================================================================
void eve::threading::Thread::m_sleep( const int32_t p_milliseconds )
{
	if( p_milliseconds >= 10 ) 
	{
		::Sleep( p_milliseconds );
	}
	else 
	{
		// unlike Sleep() this is guaranteed to return to the current thread after
		// the time expires, so we'll use this for short waits, which are more likely
		// to need to be accurate
		::WaitForSingleObject( sleepEvent.handle, p_milliseconds );
	}
}

//=================================================================================================
void eve::threading::Thread::u_sleep( uint32_t p_iters )
{
	for( uint32_t i=0; i<p_iters; i++ ) {
		::SwitchToThread();
	}
}

//=================================================================================================
void eve::threading::Thread::u_sleep( uint64_t p_ticks )
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER currentTime;
	LARGE_INTEGER endTime;

	::QueryPerformanceCounter( &endTime );

	// Ticks in microseconds (1/1000 ms)
	::QueryPerformanceFrequency(&frequency);
	endTime.QuadPart += (p_ticks * frequency.QuadPart) / (1000ULL * 1000ULL);

	do
	{
		::SwitchToThread();
		::QueryPerformanceCounter( &currentTime );

	} while( currentTime.QuadPart < endTime.QuadPart );
}



//=================================================================================================
DWORD eve::threading::Thread::current_thread_ID( void )
{
	return ::GetCurrentThreadId();
}

//=================================================================================================
bool eve::threading::Thread::equal_ID( DWORD inLeft, DWORD inRight ) 
{
	return(memcmp(&inLeft, &inRight, sizeof(inLeft)) == 0);
}

//=================================================================================================
DWORD eve::threading::Thread::zero_ID( void ) 
{
	DWORD a;
	memset( &a, 0, sizeof(a));
	return a;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
int32_t eve::threading::Thread::get_number_user_threads( void ) 
{
	return m_thread_number;
}



//=================================================================================================
void eve::threading::Thread::setDaemon( void ) 
{
	m_num_cond->lock();
	m_thread_number--;
	m_num_cond->signal();
	m_num_cond->unlock();
}



//=================================================================================================
bool eve::threading::Thread::getPriority( priorities & p_priority ) 
{

	bool result = true;

	// Convert to one of the m_priority values
	switch( ::GetThreadPriority(m_hThread) ) 
	{
	case THREAD_PRIORITY_ERROR_RETURN:
		result = false;
	case THREAD_PRIORITY_IDLE : 
		p_priority =  IdlePriority;
		break;

	case THREAD_PRIORITY_LOWEST :
		p_priority = LowestPriority;
		break;

	case THREAD_PRIORITY_BELOW_NORMAL :
		p_priority = LowPriority ;
		break;

	case THREAD_PRIORITY_NORMAL :
		p_priority = NormalPriority;
		break;

	case THREAD_PRIORITY_ABOVE_NORMAL :
		p_priority = HighPriority;
		break;

	case THREAD_PRIORITY_HIGHEST :
		p_priority = HighestPriority ;
		break;

	case THREAD_PRIORITY_TIME_CRITICAL :
		p_priority = TimeCriticalPriority;
		break;
	}
	return result;
}

//=================================================================================================
bool eve::threading::Thread::setPriority( priorities p_priority )
{
	bool result;
	// Convert
	int32_t prio;
	switch (p_priority) 
	{
	case IdlePriority:
		prio = THREAD_PRIORITY_IDLE;
		break;

	case LowestPriority:
		prio = THREAD_PRIORITY_LOWEST;
		break;

	case LowPriority:
		prio = THREAD_PRIORITY_BELOW_NORMAL;
		break;

	case NormalPriority:
		prio = THREAD_PRIORITY_NORMAL;
		break;

	case HighPriority:
		prio = THREAD_PRIORITY_ABOVE_NORMAL;
		break;

	case HighestPriority:
		prio = THREAD_PRIORITY_HIGHEST;
		break;

	case TimeCriticalPriority:
		prio = THREAD_PRIORITY_TIME_CRITICAL;
		break;

	case InheritPriority:
	default:
		prio = ::GetThreadPriority( ::GetCurrentThread() );
		break;
	}

	
	result = (::SetThreadPriority(m_hThread, prio) != THREAD_PRIORITY_ERROR_RETURN);
	return result;
}



//=================================================================================================
bool eve::threading::Thread::running( void )
{
	bool b_return = false;
	if( WAIT_TIMEOUT == ::WaitForSingleObject(m_hShutdownEvent, (DWORD)m_runWait) ) {
		b_return = true;
	}
	return b_return;
}



//=================================================================================================
bool eve::threading::Thread::started( void )
{
	bool b_return = false;

	if( WAIT_OBJECT_0 == ::WaitForSingleObject( m_StartEvent, 200000 ) ) {
		b_return = true;
	}

	return b_return;
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


//=================================================================================================
void eve::threading::Thread::setDeleteSelfAfterRun(void)
{
	m_bDeleteSelf = true;
}
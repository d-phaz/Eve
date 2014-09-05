

// Main header
#include "Native_ThreadSimple.h"



///////////////////////////////////////////////////////////////////////////////////////////////////
//		Static
///////////////////////////////////////////////////////////////////////////////////////////////////

int32_t NativeT::Thread::m_thread_number = 0;

NativeT::Condition NativeT::Thread::m_num_cond;



///////////////////////////////////////////////////////////////////////////////////////////////////
//		NativeT::Thread class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
NativeT::Thread::Thread( int32_t p_runWait )

	// Members init
	: m_mutex			()
	, m_hThread			( NULL )
	, m_hShutdownEvent	( ::CreateEvent(NULL, TRUE, FALSE, NULL) )
	, m_StartEvent		( ::CreateEvent(NULL, TRUE, FALSE, NULL) ) 
	, m_waiters			( 0 )
	, m_runWait			( p_runWait )
	, m_threadID		( zero_ID() )

	, m_bRunning		( false )
	, m_bDeleteSelf		( false )
	, m_returnCode		( -1 )
	, m_priority		( Thread::InheritPriority )	
{}

//=================================================================================================
NativeT::Thread::~Thread( void ) 
{
	Stop();
	::CloseHandle( m_hThread );
	::CloseHandle( m_hShutdownEvent );
	::CloseHandle( m_StartEvent );
	m_threadID = zero_ID();
}



//=================================================================================================
uint32_t NativeT::Thread::Run_Wrapper(void * p_pThread)
{
	//#ifndef NDEBUG
	//	assert( p_pThread!=NULL );
	//#endif

	// Grab and cast thread pointer
	Thread * objectPtr = (Thread *)p_pThread;

	// Initialize object local data
	objectPtr->init();
	// Since initialized, set status to started
	objectPtr->setStarted();

	// Run thread (pure virtual function)
	objectPtr->Run();

	// Uninitialize object local data
	objectPtr->release();
	// Since we're out of run loop set status to not started
	objectPtr->resetStarted();


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
	m_num_cond.Lock();
	m_thread_number--;
	m_num_cond.Signal();
	m_num_cond.Unlock();


	return NULL;
}




//=================================================================================================
void NativeT::Thread::Start(void)
{
	if (equal_ID(m_threadID, zero_ID()))
	{
		// increment thread count
		m_num_cond.Lock();
		m_thread_number++;
		m_num_cond.Unlock();

		Thread* ptr = this;

		// Win32 threads -- spawn new thread
		// Win32 has a thread handle in addition to the thread ID
		m_hThread = (HANDLE)_beginthreadex(
			NULL,							// LPSECURITY_ATTRIBUTES lpThreadAttributes,	// pointer to security attributes
			0,								// DWORD dwStackSize,							// initial thread stack size
			(THREAD_START_ROUTINE)
			Run_Wrapper,					// LPTHREAD_START_ROUTINE lpStartAddress,		// pointer to thread function
			static_cast<LPVOID>(ptr),		//LPVOID lpParameter,							// argument for new thread
			0,								//DWORD dwCreationFlags,						// creation flags
			(unsigned*)&m_threadID			// LPDWORD lpThreadId							// pointer to receive thread ID
			);
		//#ifndef NDEBUG	 
		//		assert( m_hThread != 0 );
		//#endif
	}
}



//=================================================================================================
void NativeT::Thread::Stop( void ) 
{
	if( m_hThread )
	{
		if ( !equal_ID(m_threadID, zero_ID()) ) 
		{
			// decrement thread count
			m_num_cond.Lock();
			m_thread_number--;
			m_num_cond.Signal();
			m_num_cond.Unlock();

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
void NativeT::Thread::Pause( void )
{
	Stop();
}




//=================================================================================================
bool NativeT::Thread::Join( void ) 
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
void NativeT::Thread::join_all( void ) 
{
	m_num_cond.Lock();
	while ( m_thread_number > 0 ) 
	{
		m_num_cond.Wait();
	}
	m_num_cond.Unlock();
} 

//=================================================================================================
void NativeT::Thread::detach( void )
{
	if(m_hThread)
	{
		::CloseHandle(m_hThread);
		m_hThread = 0;
	}
	m_threadID = 0;
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
void NativeT::Thread::m_sleep( const int32_t p_milliseconds )
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
void NativeT::Thread::u_sleep( uint32_t p_iters )
{
	for( uint32_t i=0; i<p_iters; i++ ) {
		::SwitchToThread();
	}
}

//=================================================================================================
void NativeT::Thread::u_sleep( uint64_t p_ticks )
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
DWORD NativeT::Thread::current_thread_ID( void )
{
	return ::GetCurrentThreadId();
}

//=================================================================================================
bool NativeT::Thread::equal_ID( DWORD inLeft, DWORD inRight ) 
{
	return(memcmp(&inLeft, &inRight, sizeof(inLeft)) == 0);
}

//=================================================================================================
DWORD NativeT::Thread::zero_ID( void ) 
{
	DWORD a;
	memset( &a, 0, sizeof(a));
	return a;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
int32_t NativeT::Thread::get_number_user_threads( void ) 
{
	return m_thread_number;
}



//=================================================================================================
void NativeT::Thread::setDaemon( void ) 
{
	m_num_cond.Lock();
	m_thread_number--;
	m_num_cond.Signal();
	m_num_cond.Unlock();
}



//=================================================================================================
bool NativeT::Thread::getPriority( priorities & p_priority ) 
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
bool NativeT::Thread::setPriority( priorities p_priority )
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
bool NativeT::Thread::running( void )
{
	bool b_return = false;
	if( WAIT_TIMEOUT == ::WaitForSingleObject(m_hShutdownEvent, (DWORD)m_runWait) ) {
		b_return = true;
	}
	return b_return;
}



//=================================================================================================
bool NativeT::Thread::started( void )
{
	bool b_return = false;

	if( WAIT_OBJECT_0 == ::WaitForSingleObject( m_StartEvent, 200000 ) ) {
		b_return = true;
	}

	return b_return;
}

//=================================================================================================
void NativeT::Thread::setStarted( void )
{
	::SetEvent( m_StartEvent );
}

//=================================================================================================
void NativeT::Thread::resetStarted( void )
{
	::SetEvent( m_StartEvent );
}

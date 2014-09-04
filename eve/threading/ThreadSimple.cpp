

// Main header
#include "Native_ThreadSimple.h"



///////////////////////////////////////////////////////////////////////////////////////////////////
//		Static
///////////////////////////////////////////////////////////////////////////////////////////////////

int32_t NativeT::ThreadSimple::m_thread_number = 0;

NativeT::Condition NativeT::ThreadSimple::m_num_cond;



///////////////////////////////////////////////////////////////////////////////////////////////////
//		NativeT::ThreadSimple class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
NativeT::ThreadSimple::ThreadSimple( int32_t p_runWait )

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
	, m_priority		( ThreadSimple::InheritPriority )	
{}

//=================================================================================================
NativeT::ThreadSimple::~ThreadSimple( void ) 
{
	Stop();
	::CloseHandle( m_hThread );
	::CloseHandle( m_hShutdownEvent );
	::CloseHandle( m_StartEvent );
	m_threadID = zero_ID();
}



//=================================================================================================
void NativeT::ThreadSimple::Stop( void ) 
{
	if( NULL != m_hThread )
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
void NativeT::ThreadSimple::Pause( void )
{
	Stop();
}




//=================================================================================================
bool NativeT::ThreadSimple::Join( void ) 
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
void NativeT::ThreadSimple::join_all( void ) 
{
	m_num_cond.Lock();
	while ( m_thread_number > 0 ) 
	{
		m_num_cond.Wait();
	}
	m_num_cond.Unlock();
} 

//=================================================================================================
void NativeT::ThreadSimple::detach( void )
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
void NativeT::ThreadSimple::m_sleep( const int32_t p_milliseconds )
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
void NativeT::ThreadSimple::u_sleep( uint32_t p_iters )
{
	for( uint32_t i=0; i<p_iters; i++ ) {
		::SwitchToThread();
	}
}

//=================================================================================================
void NativeT::ThreadSimple::u_sleep( uint64_t p_ticks )
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
void NativeT::ThreadSimple::yield( void ) 
{
	static NativeT::YieldOps yielder;
	yielder();
}



//=================================================================================================
DWORD NativeT::ThreadSimple::current_thread_ID( void )
{
	return ::GetCurrentThreadId();
}

//=================================================================================================
bool NativeT::ThreadSimple::equal_ID( DWORD inLeft, DWORD inRight ) 
{
	return(memcmp(&inLeft, &inRight, sizeof(inLeft)) == 0);
}

//=================================================================================================
DWORD NativeT::ThreadSimple::zero_ID( void ) 
{
	DWORD a;
	memset( &a, 0, sizeof(a));
	return a;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
int32_t NativeT::ThreadSimple::get_number_user_threads( void ) 
{
	return m_thread_number;
}



//=================================================================================================
void NativeT::ThreadSimple::setDaemon( void ) 
{
	m_num_cond.Lock();
	m_thread_number--;
	m_num_cond.Signal();
	m_num_cond.Unlock();
}



//=================================================================================================
bool NativeT::ThreadSimple::getPriority( priorities & p_priority ) 
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
bool NativeT::ThreadSimple::setPriority( priorities p_priority )
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
bool NativeT::ThreadSimple::running( void )
{
	bool b_return = false;
	if( WAIT_TIMEOUT == ::WaitForSingleObject(m_hShutdownEvent, (DWORD)m_runWait) ) {
		b_return = true;
	}
	return b_return;
}



//=================================================================================================
bool NativeT::ThreadSimple::started( void )
{
	bool b_return = false;

	if( WAIT_OBJECT_0 == ::WaitForSingleObject( m_StartEvent, 200000 ) ) {
		b_return = true;
	}

	return b_return;
}

//=================================================================================================
void NativeT::ThreadSimple::setStarted( void )
{
	::SetEvent( m_StartEvent );
}

//=================================================================================================
void NativeT::ThreadSimple::resetStarted( void )
{
	::SetEvent( m_StartEvent );
}


// Main header
#include "Native_Thread.h"

// External header
#include <process.h>



///////////////////////////////////////////////////////////////////////////////////////////////////
//		NativeT::Thread class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
NativeT::Thread::Thread( int32_t p_runWait )

	// Inheritance
	: ThreadSimple(p_runWait)
{}

//=================================================================================================
NativeT::Thread::~Thread( void ) 
{}




//=================================================================================================
void NativeT::Thread::Start( void ) 
{
    if ( equal_ID( m_threadID, zero_ID() ) ) 
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
uint32_t NativeT::Thread::Run_Wrapper( void * p_pThread ) 
{
//#ifndef NDEBUG
//	assert( p_pThread!=NULL );
//#endif

	// Grab and cast thread pointer
	Thread * objectPtr = (Thread *) p_pThread;

	// Initialize object local data
	objectPtr->init();			
	// Since initialized, set status to started
	objectPtr->setStarted();		

	// Run thread (pure virtual function)
    objectPtr->Run();	
					
	// Uninitialize object local datas
	objectPtr->uninit();	
	// Since we're out of run loop set status to not started
	objectPtr->resetStarted();	


    // set TID to zero, then delete it
    // the zero TID causes Stop() in the destructor not to do anything
    objectPtr->m_threadID = zero_ID();
	// Delete pointer if asked for
    if( objectPtr->m_bDeleteSelf ) 
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

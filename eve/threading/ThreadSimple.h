
#pragma once
#ifndef __NATIVE_THREAD_SIMPLE_H_
#define __NATIVE_THREAD_SIMPLE_H_


///////////////////////////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////////////////////////

// External header
#include <cstdint>

#ifndef __NATIVE_SYSTEM_H__
	#include "NATIVE_System.h"
#endif

#ifndef __NATIVE_MUTEX_H__
	#include "Native_Mutex.h"
#endif

#ifndef __NATIVE_LOCK_H__
	#include "Native_Lock.h"
#endif 

#ifndef __NATIVE_CONDITION_H__
	#include "Native_Condition.h"
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// Type Definitions
///////////////////////////////////////////////////////////////////////////////////////////////////

typedef unsigned(__stdcall *THREAD_START_ROUTINE)(void*);



///////////////////////////////////////////////////////////////////////////////////////////////////
// NativeT namespace
///////////////////////////////////////////////////////////////////////////////////////////////////
namespace NativeT 
{

	class YieldOps 
	{
	public:
		typedef BOOL (*Yield)(void);
		Yield _fnYield;

	public:
		YieldOps( void ) 
			: _fnYield		( NULL ) 
		{
			OSVERSIONINFO v;
			v.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

			if( ::GetVersionEx(&v) && (v.dwPlatformId == VER_PLATFORM_WIN32_NT) ) 
			{
				// Uses GetModuleHandle() so the reference count on the dll is
				// not affected. There is a warning about race conditions involving
				// this function being called as FreeLibrary() completes; however 
				// nearly all win32 applications load this particular and will keep it
				// in memory until the process exits.
				//wchar_t * dll = toUnicode("Kernel32.dll");
				HINSTANCE hInst = ::GetModuleHandleW( L"Kernel32.dll" );
				//delete dll;
				if(hInst != NULL) {
					_fnYield = (Yield)::GetProcAddress(hInst, "SwitchToThread");
				}

				// REMIND: possibly need to use _T() macro for these strings
			}

		}

		bool operator()() 
		{
			// Attempt to yield using the best function available
			if( !_fnYield || !_fnYield() ) { 
				::Sleep(0);  
			}

			return true;
		}

	};

	

	/**
	* @class NativeT::ThreadSimple
	*
	* @brief base thread class
	*/
	class ThreadSimple 
	{

	public:
		enum priorities 
		{
			IdlePriority,

			LowestPriority,
			LowPriority,
			NormalPriority,
			HighPriority,
			HighestPriority,

			TimeCriticalPriority,

			InheritPriority
		};

		//////////////////////////////////////
		//				DATAS				//
		//////////////////////////////////////
	
	public:
		mutable Mutex		m_mutex;
		HANDLE				m_hThread;
		HANDLE				m_hShutdownEvent;
		HANDLE				m_StartEvent;
		int32_t				m_waiters;
		int32_t				m_runWait;

	protected:
		DWORD				m_threadID;
		bool				m_bRunning;
		bool				m_bDeleteSelf;

		int32_t				m_returnCode;
		priorities			m_priority;

		
		static int32_t		m_thread_number;	//<! count of threads, used in joinall
		static Condition	m_num_cond;			//<! count of conditions, used in joinall


		//////////////////////////////////////
		//				METHOD				//
		//////////////////////////////////////

	private:
		// Suppress copying
		ThreadSimple(const ThreadSimple &);
		const ThreadSimple & operator=(const ThreadSimple &);


	public:
		/**
		* @brief ThreadSimple class constructor
		*
		* @param p_runWait run wait time in milliseconds (default to 5)
		*/
		ThreadSimple( int32_t p_runWait=5 );
		/**
		* @brief ThreadSimple class destructor.
		* Stop this object's thread execution (if any) immediately.
		*/
		virtual ~ThreadSimple( void );


		/**
		* @brief run is the main loop for this thread
		* usually this is called by Start(), but may be called
		* directly for single-threaded applications.
		*
		* @note pure virtual function
		*/
		virtual void Run( void ) = 0;

		
		/**
		* @brief Start the object's thread execution. Increments thread
		* count, spawns new thread, and stores thread m_threadID.
		*
		* @note pure virtual function
		*/
		virtual void Start( void ) = 0;
		/**
		* @brief Stop the thread immediately. Decrements thread count and
		* resets the thread m_threadID.
		* @note virtual function
		*/
		virtual void Stop( void );
		/**
		* @brief pause thread execution
		* @note OSX compatibility compliance (calls Stop)
		*/
		void Pause( void );


		/**
		* @brief Wait for this object's thread execution (if any) to complete.
		*/
		virtual bool Join( void );
		/**
		* @brief wait for all threads to complete
		*/
		/**
		* @brief Wait for all thread object's execution to complete. Depends on the
		* thread count being accurate and the threads sending a condition
		* signal when they terminate.
		*
		* @note static function
		*/
		static void join_all( void );
		/**
		* @brief guarantees resources consumed by thread are released when thread terminates,
		* after this join can no-longer be used
		*/
		virtual void detach( void );
		

		/**
		* @brief sleep thread for given amount of milliseconds
		* @param p_milliseconds milliseconds amount to sleep
		*
		* @note static function
		*/
		static void m_sleep( const int32_t p_milliseconds );
		/**
		* @brief (micro)sleep thread for given amount of iterations, switch hand to other threads
		* @param p_iters iterations amount
		*
		* @note static function
		*/
		static void u_sleep( uint32_t p_iters );
		/**
		* @brief (micro)sleep thread for given amount of micro seconds, switch hand to other threads
		* @param p_ticks target ticks amount
		*
		* @note static function
		*/
		static void u_sleep( uint64_t p_ticks );


		/**
		* @brief Detect OS at runtime and attempt to locate the SwitchToThreadSimple
		* function, which will assist in making the spin lock implementation
		* which use ThreadSimpleOps::yield() a bit fairer.
		*
		* @note static function
		*/
		static void yield( void );

		
		/**
		* @brief get current thread ID
		* @return id as DWORD
		*/
		static DWORD current_thread_ID( void );
		/**
		* @brief Compare the thread m_threadID's (inLeft == inRight); return true if they
		* are equal. On some OS's DWORD is a struct so == will not work.
		*
		* @note static function
		*/
		static bool equal_ID( DWORD inLeft, DWORD inRight );
		/**
		* @brief Return a zero'd out thread m_threadID. On some OS's DWORD is a struct
		* so == 0 will not work.
		*
		* @note static function
		*/
		static DWORD zero_ID( void );


		///////////////////////////////////////////////////////////////////////////////////////////
		//		GET / SET
		///////////////////////////////////////////////////////////////////////////////////////////

	public:
		/**
		* @brief returns the number of user (i.e. not daemon) threads as int32_t
		*
		* @note static function
		*/
		static int32_t get_number_user_threads( void );


		/**
		* @brief set a thread to be daemon, so joinall won't wait on it
		* this simply decrements the thread count that joinall uses,
		* which is not a thorough solution, but works for the moment
		*/
		virtual void setDaemon( void );


		/**
		* @brief set thread deletion after run property
		*/
		virtual void setDeleteSelfAfterRun( void );


		/**
		* @brief get thread priority
		*
		* @param p_priority target reference to stock thread priority value
		* @return true if successfull, false otherwise
		*/
		virtual bool getPriority( priorities & p_priority );
		/**
		* @brief Set the m_priority for the native thread if supported by the system.
		*
		* @param p_priority target priority as priorities enum
		* @return true if successfull, false otherwise
		*/
		virtual bool setPriority( priorities p_priority );


		/**
		* @brief get thread running state
		* @return true if thread is running, false otherwise
		*/
		virtual bool running( void );


		/**
		* @brief get thread started state
		* @return true if thread started, false otherwise
		*/
		virtual bool started( void );

	protected:
		/**
		* @brief set thread started state
		*/
		virtual void setStarted ( void );
		/**
		* @brief reset thread started state
		*/
		virtual void resetStarted ( void );
	};

} //namespace NativeThread



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
inline void NativeT::ThreadSimple::setDeleteSelfAfterRun( void )
{
	m_bDeleteSelf = true;
}

#endif // __NATIVE_THREAD_SIMPLE_H_

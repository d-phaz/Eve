

#pragma once
#ifndef __THREADING_MUTEX_H__
#define __THREADING_MUTEX_H__


///////////////////////////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __NATIVE_SYSTEM_H__
#include "Native_System.h"
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
// NativeT namespace
///////////////////////////////////////////////////////////////////////////////////////////////////
namespace NativeT 
{

	/**
	* @class NativeT::Mutex
	*
	* @brief provides base native Mutex
	*/
	class Mutex 
	{
		//////////////////////////////////////
		//				DATAS				//
		//////////////////////////////////////

	protected:
		HANDLE					m_mutex;		//<! native Win32 Mutex handle



		//////////////////////////////////////
		//				METHOD				//
		//////////////////////////////////////

	public:
		
		/**
		* @brief Mutex class constructor : initialise base mutex
		*/
		Mutex( void ) 
		{
#ifdef UNICODE
			m_mutex = CreateMutexW( NULL, false, NULL );
#else //UNICODE
			m_mutex = CreateMutexA( NULL, false, NULL );
#endif //UNICODE
		}
		/**
		* @brief Mutex class destructor : destroy, making sure mutex is unlocked
		*/
		virtual ~Mutex( void ) 
		{
			CloseHandle( m_mutex );
		}


		/**
		* @brief lock the mutex variable
		*/
		void Lock( void )
		{
			WaitForSingleObject( m_mutex, INFINITE );
		}
		/**
		* @brief unlock the mutex variable
		*/
		void Unlock( void ) 
		{
			ReleaseMutex( m_mutex );
		}
	}; 

} // namespace NativeT

#endif // __THREADING_MUTEX_H__

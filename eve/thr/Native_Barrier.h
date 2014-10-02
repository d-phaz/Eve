
#pragma once
#ifndef __NATIVE_BARRIER_H__
#define __NATIVE_BARRIER_H__


///////////////////////////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __NATIVE_CONDITION_H__
#include "thread/win32/Native_Condition.h"
#endif

#ifndef __NATIVE_MUTEX_H__
#include "thread/win32/Native_Mutex.h"
#endif

#define _REENTRANT



///////////////////////////////////////////////////////////////////////////////////////////////////
// NativeT namespace
///////////////////////////////////////////////////////////////////////////////////////////////////
namespace NativeT 
{

	// The following structure defines a subbarrier in a barrier.
	// It consists of a lock and a condition variable for waiters at
	// this subbarrier and the number of running threads associated
	// with this subbarrier.
	typedef  struct 
	{
		NativeT::Condition  wait_cv;		// condition variable for waiters at barrier 
		NativeT::Mutex		wait_lk;		// mutex for waiters at barrier 
		int					runners;		// number of running threads 
	} _sb;


	/**
	* @class Barrier
	*/
	class Barrier 
	{
		//////////////////////////////////////
		//				DATAS				//
		//////////////////////////////////////

	private:
		int		maxcnt;       //<! maximun number of runners
		_sb		sb[2];        //<! two sub-barriers
		_sb		*CurrentSb;   //<! ptr to current sub-barrier


		//////////////////////////////////////
		//				METHOD				//
		//////////////////////////////////////

	public:
		/**
		* @brief Barrier class constructor : Initialize a barrier for given number of threads.
		* @param "p_count" is the number of threads involved
		*/
		Barrier( int p_count );	
		/**
		* @brief Barrier class destructor
		*/
		virtual ~Barrier( void ); 


		/**
		* @brief Wait untill all threads reach this barrier. The last thread switches
		* "CurrentSb" point to another sub barrier before waking up all waiting threads.
		*/
		void Wait( void );
		/**
		* @brief signal barrier
		*/
		void Signal( void );
	};

} // namespace NativeT 

#endif // __NATIVE_BARRIER_H__

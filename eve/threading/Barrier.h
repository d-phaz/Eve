
#pragma once
#ifndef __EVE_THREADING_BARRIER_H__
#define __EVE_THREADING_BARRIER_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "core/Includes.h"
#endif


#ifndef __THREADING_CONDITION_H__
#include "threading/Condition.h"
#endif

#ifndef __THREADING_MUTEX_H__
#include "threading/Mutex.h"
#endif


namespace eve
{

	namespace threading 
	{

		// The following structure defines a sub-barrier in a barrier.
		// It consists of a lock and a condition variable for waiters at
		// this sub-barrier and the number of running threads associated
		// with this sub-barrier.
		typedef  struct 
		{
			threading::Condition  wait_cv;		// condition variable for waiters at barrier 
			threading::Mutex	  wait_lk;		// mutex for waiters at barrier 
			int32_t				  runners;		// number of running threads 
		} _sb;


		/**
		* @class threading::Barrier
		*/
		class Barrier 
		{
			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:
			int32_t	m_maxCnt;       //<! maximum number of runners
			_sb		m_pSb[2];       //<! two sub-barriers
			_sb	*	m_pCurrentSb;   //<! pointer to current sub-barrier


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			/**
			* @brief Barrier class constructor : Initialize a barrier for given number of threads.
			* @param "p_count" is the number of threads involved
			*/
			Barrier( int32_t p_count );	
			/**
			* @brief Barrier class destructor
			*/
			virtual ~Barrier( void ); 


			/**
			* @brief Wait untill all threads reach this barrier. 
			* The last thread switches "CurrentSb" point to another sub barrier before waking up all waiting threads.
			*/
			void Wait( void );
			/**
			* @brief signal barrier
			*/
			void Signal( void );

		}; // class Barrier

	} // namespace threading 

} // namespace eve

#endif // __EVE_THREADING_BARRIER_H__

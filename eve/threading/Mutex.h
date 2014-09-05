
#pragma once
#ifndef __EVE_THREADING_MUTEX_H__
#define __EVE_THREADING_MUTEX_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "core/Includes.h"
#endif


namespace eve
{
	namespace threading
	{

		/**
		* @class threading::Mutex
		* @brief provides base native Mutex
		*/
		class Mutex 
		{
			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			void *		m_mutex;		//<! Mutex handle


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:		
			/** Mutex class constructor : initialize base mutex. */
			Mutex(void);
			/** Mutex class destructor : destroy, making sure mutex is unlocked. */
			virtual ~Mutex(void);


			/** Lock the mutex variable. */
			void lock(void);
			/** Unlock the mutex variable. */
			void unlock(void);

		}; // class Mutex

	} // namespace threading

} // namespace eve

#endif // __EVE_THREADING_MUTEX_H__

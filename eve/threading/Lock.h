
#pragma once
#ifndef __EVE_THREADING_LOCK_H__
#define __EVE_THREADING_LOCK_H__  

#ifndef __EVE_CORE_INCLUDES_H__
#include "core/Includes.h"
#endif


namespace eve
{
	namespace threading
	{

		namespace detail { class Lock; }


		/** 
		* @class threading::Lock
		* @brief lock (mutex) primitive
		*/
		class Lock
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:
			detail::Lock * const p_pImpl;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////
        
		public:
			/** Construct a new lock. */
			Lock(void);
			/** Destruct the lock. */
			virtual ~Lock(void);


			/** Acquire the lock. */
			void set(void);
			/** Release the lock. */
			void unset(void);

			/** 
			* Attempt to acquire the lock.
			* This method implements an atomic test-and-set operation.
			* @return true if the lock was set, false if it was not set.
			*/
			bool trySet(void);

			/** 
			* Test if the lock is set.
			* @return true if the lock was set, false if it was not set.
			*/
			bool isSet(void);

		}; // class Lock

	} // namespace threading

} // namespace eve

#endif // __EVE_THREADING_LOCK_H__

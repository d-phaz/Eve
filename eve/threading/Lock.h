

#pragma once
#ifndef __NATIVE_LOCK_H__
#define __NATIVE_LOCK_H__  


namespace NativeT
{
	class ScopedLock;
	class ScopedUnlock;

	namespace detail { class Lock; }

	/** 
	* @class NativeT::Lock
	* @brief lock (mutex) primitive
	*/
	class Lock
	{

		//////////////////////////////////////
		//				DATAS				//
		//////////////////////////////////////

	private:
		detail::Lock* const p_pImpl;


		//////////////////////////////////////
		//				METHOD				//
		//////////////////////////////////////
        
	public:
		/** Construct a new lock. */
		Lock( void );

		/** Destruct the lock. */
		~Lock( void );

		/** Acquire the lock. */
		void set( void );

		/** Release the lock. */
		void unset( void );

		/** Acquire the lock shared with other readers. */
		void setRead( void ) { set(); }

		/** Release a shared read lock.  */
		void unsetRead( void ) { unset(); }

		/** 
		* Attempt to acquire the lock.
		*
		* This method implements an atomic test-and-set operation.
		*
		* @return <code>true</code> if the lock was set, <code>false</code> if
		*         it was not set.
		*/
		bool trySet( void );

		/** 
		* Test if the lock is set.
		* 
		* @return <code>true</code> if the lock is set, <code>false</code> if
		*         it is not set.
		*/
		bool isSet( void );

		//==============================================================================
		/** Provides the type of scoped lock to use with this type of critical section object. */
		typedef ScopedLock      ScopedLockType;

		/** Provides the type of scoped unlocker to use with this type of critical section object. */
		typedef ScopedUnlock    ScopedUnlockType;
	};


} // namespace NativeT

#endif // __NATIVE_LOCK_H__

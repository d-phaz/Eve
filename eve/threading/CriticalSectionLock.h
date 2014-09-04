
#pragma once
#ifndef __NATIVE_CRITICAL_LOCK_H__
#define __NATIVE_CRITICAL_LOCK_H__


#ifndef __NATIVE_SYSTEM_H__
	#include "Native_system.h"
#endif

#ifndef __NATIVE_LOCKABLE_H__
	#include "Native_Lockable.h"
#endif



#ifdef NATIVE_OS_WIN32
	extern "C"
	{
		WINBASEAPI	BOOL WINAPI TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
	};
#endif



#include <memory.h>


class ScopedLock;
class ScopedUnlock;

//==============================================================================
/**
    Prevents multiple threads from accessing shared objects at the same time.

    @see ScopedLock, Thread, InterProcessLock
*/
class CriticalSection
{
public:
    //==============================================================================
    /**
        Creates a CriticalSection object
    */
    CriticalSection( void ) throw();

    /** Destroys a CriticalSection object.

        If the critical section is deleted whilst locked, its subsequent behaviour
        is unpredictable.
    */
    virtual ~CriticalSection( void ) throw();

    //==============================================================================
    /** Locks this critical section.

        If the lock is currently held by another thread, this will wait until it
        becomes free.

        If the lock is already held by the caller thread, the method returns immediately.

        @see exit, ScopedLock
    */
    void enter( void ) const throw();

    /** Attempts to lock this critical section without blocking.

        This method behaves identically to CriticalSection::enter, except that the caller thread
        does not wait if the lock is currently held by another thread but returns false immediately.

        @returns false if the lock is currently held by another thread, true otherwise.
        @see enter
    */
    bool tryEnter( void ) const throw();

    /** Releases the lock.

        If the caller thread hasn't got the lock, this can have unpredictable results.

        If the enter() method has been called multiple times by the thread, each
        call must be matched by a call to exit() before other threads will be allowed
        to take over the lock.

        @see enter, ScopedLock
    */
    void exit( void ) const throw();


    //==============================================================================
    /** Provides the type of scoped lock to use with this type of critical section object. */
    typedef ScopedLock      ScopedLockType;

    /** Provides the type of scoped unlocker to use with this type of critical section object. */
    typedef ScopedUnlock    ScopedUnlockType;


private:
    //==============================================================================
#ifdef NATIVE_OS_WIN32
  #if HAVE_64_BIT
    // To avoid including windows.h in the public includes, we'll just allocate a
    // block of memory here that's big enough to be used internally as a windows critical
    // section object.
    unsigned __int8 internal [44];
  #else
    unsigned char internal [24];
  #endif
#else
    mutable pthread_mutex_t internal;
#endif
    CriticalSection (const CriticalSection&);
    CriticalSection& operator= (const CriticalSection&);
};


//==============================================================================
/**
    A class that can be used in place of a real CriticalSection object.

    This is currently used by some templated classes, and should get
    optimised out by the compiler.

    @see Array, OwnedArray, ReferenceCountedArray
*/
class DummyCriticalSection
{
public:
    inline DummyCriticalSection( void ) throw()         {}
    inline ~DummyCriticalSection( void ) throw()        {}

    inline void enter( void ) const throw()             {}
    inline void exit( void ) const throw()              {}

    //==============================================================================
    /** A dummy scoped-lock type to use with a dummy critical section. */
    struct ScopedLockType
    {
        ScopedLockType (const DummyCriticalSection&) throw() {}
    };

    /** A dummy scoped-unlocker type to use with a dummy critical section. */
    typedef ScopedLockType ScopedUnlockType;

private:
    DummyCriticalSection (const DummyCriticalSection&);
    DummyCriticalSection& operator= (const DummyCriticalSection&);
};


#endif //__NATIVE_CRITICAL_LOCK_H__

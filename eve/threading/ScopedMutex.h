#ifndef NATIVE_SCOPEDMUTEX_H
#define NATIVE_SCOPEDMUTEX_H

#include "Native_Lock.h"       // used in inline method
#include "Native_lockable.h"    // used in inline method

namespace NativeT
{
    class WriteOp;
    class ReadOp;

    /** @cond IGNORE */
    template< class L, class T > struct ScopedMutexLocker {};
    template< class L > struct ScopedMutexLocker< L, WriteOp >
    {
        static inline void set( L& lock ) { lock.set(); }
        static inline void unset( L& lock ) { lock.unset(); }
    };
    template< class L > struct ScopedMutexLocker< L, ReadOp >
    {
        static inline void set( L& lock ) { lock.setRead(); }
        static inline void unset( L& lock ) { lock.unsetRead(); }
    };
    /** @endcond */

    /**
     * A scoped mutex.
     * 
     * The mutex is automatically set upon creation, and released when the
     * scoped mutex is destroyed, e.g., when the scope is left. The scoped mutex
     * does nothing if a 0 pointer for the lock is passed.
     */
    template< class L = Lock, class T = WriteOp >
    class ScopedMutex
    {
        typedef ScopedMutexLocker< L, T > LockTraits;

    public:
        /** 
         * Construct a new scoped mutex and set the given lock.
         *
         * Providing no Lock (0) is allowed, in which case the scoped mutex does
         * nothing.
         *
         * @param lock the mutex to set and unset, or 0.
         */
        ScopedMutex( L* lock ) : _lock( lock )
            { if( lock ) LockTraits::set( *lock ); }

        /** Construct a new scoped mutex and set the given lock. @version 1.0 */
        ScopedMutex( L& lock ) : _lock( &lock )
            { LockTraits::set( lock ); }

        /** Destruct the scoped mutex and unset the mutex. @version 1.0 */
        ~ScopedMutex( void ) { leave(); }

        /** Leave and unlock the mutex immediately. @version 1.0 */
        void leave( void ) { if( _lock ) LockTraits::unset( *_lock ); _lock = 0; }

    private:
        ScopedMutex();
        L* _lock;
    };
} //NativeT

#endif //NATIVE_SCOPEDMUTEX_H
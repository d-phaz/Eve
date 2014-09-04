
#pragma once
#ifndef __NATIVE_LOCKABLE_H__
#define __NATIVE_LOCKABLE_H__

#include "Native_Lock.h"
#include <iostream>

namespace NativeT 
{

    /**
     * A convenience structure to hold data together with a lock for access.
     * 
     * Locking the data still has to be done manually, e.g, using a ScopedMutex.
     */
    template< class D, class L = Lock > class Lockable
    {
    public:
        /** Construct a new lockable data structure */
        explicit Lockable( void ) {}

        /** Construct and initialize a new data structure */
        explicit Lockable( const D& value ) : data( value ) {}

        /** Access the held data. */
        D* operator->( void ) { return &data; }

        /** Access the held data. */
        const D* operator->( void ) const { return &data; }

        /** Access the held data. */
        D& operator *( void ) { return data; }

        /** Access the held data. */
        const D& operator*( void ) const { return data; }

        /** @return true if the data is equal to the rhs object.*/ 
        bool operator == ( const D& rhs ) const { return ( data == rhs ); }

        /** Assign another value to the data. */
        Lockable& operator = ( const D& rhs ) { data = rhs; return *this; }

        D data;
        mutable L lock;
    };

    /** Print the data to the given output stream. */
    template< class D, class L >
    inline std::ostream& operator << ( std::ostream& os,
                                       const Lockable<D, L>& l )
    {
        //os << disableFlush << "<" << l.lock.isSet() << " " << l.data << ">"
        //   << enableFlush;
        return os;
    }
} // namespace NativeT 

#endif //__NATIVE_LOCKABLE_H__ 

#pragma once
#ifndef __SYSTEM_RUN_LOOP_WORKER_H__
#define __SYSTEM_RUN_LOOP_WORKER_H__

// Native header
#include "Native_GlobalMacro.h"


/**
 * @class SystemRunLoopWorker
 *
 * @brief abstract run loop worker base class, 
 *        each thread using a worker must use an inherited class from SystemRunLoopWorker
 */
class SystemRunLoopWorker
{
    
    NATIVE_DISABLE_COPY( SystemRunLoopWorker );
    
    
protected:
    /**
     * @brief SystemRunLoopWorker class constructor
     */
    SystemRunLoopWorker( void );
    
    
public:
    /**
     * @brief SystemRunLoopWorker class destructor
     */
    virtual ~SystemRunLoopWorker( void );
    
    
    /**
     * @brief main work process
     * @note pure virtual function
     */
    virtual bool processWork( void ) = 0;
    /**
     * @brief secondary work process, idle
     * @note pure virtual function
     */
    virtual bool processIdle( void ) = 0;

};


#endif  // __SYSTEM_RUN_LOOP_WORKER_H__


#pragma once
#ifndef __SYSTEM_RUN_LOOP_H__
#define __SYSTEM_RUN_LOOP_H__

// Native header
#include "Native_GlobalMacro.h"


class SystemRunLoopWorker;


/**
 * @class SystemRunLoop
 *
 * @brief abstract run loop base class
 *
 * @note contains shared worker pointer as SystemRunLoopWorker
 */
class SystemRunLoop
{
    
    //////////////////////////////////////
	//									//
	//				DATAS				//
	//									//
	//////////////////////////////////////
    
protected:
    SystemRunLoopWorker *           m_spWorker;     //<! Worker shared pointer
    
    
    
    //////////////////////////////////////
	//									//
	//				METHOD				//
	//									//
	//////////////////////////////////////
    
    NATIVE_DISABLE_COPY( SystemRunLoop );
    
    
protected:
    /**
     * @brief SystemRunLoop class constructor
     * @param p_pWorker shared worker SystemRunLoopWorker pointer
     */
    SystemRunLoop( SystemRunLoopWorker * p_pWorker );
    
    
public:
    /**
     * @brief SystemRunLoop class destructor
     */
    virtual ~SystemRunLoop( void );
    
    
    /**
     * @brief main run loop process
     * @note pure virtual function
     */
    virtual void Run( void ) = 0;
    /**
     * @brief exit run loop
     * @note pure virtual function
     */
    virtual void Quit( void ) = 0;

};


#endif  // __SYSTEM_RUN_LOOP_H__

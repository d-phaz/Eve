
// Main header
#include "SystemRunLoop.h"



//===========================================================================================
SystemRunLoop::SystemRunLoop( SystemRunLoopWorker * p_pWorker )

    : m_spWorker                ( p_pWorker )
{}



//===========================================================================================
SystemRunLoop::~SystemRunLoop( void )
{
    // Do not delete -> shared pointer
    m_spWorker = NULL;
}

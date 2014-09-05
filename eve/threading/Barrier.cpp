
// Main header
#include "threading/Barrier.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//		eve::threading::Barrier class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::threading::Barrier::Barrier(int32_t count)
{
    m_maxCnt = count;
    m_pCurrentSb = &m_pSb[ 0 ];

	// construct two sub-barriers
	_sb *curSb = &m_pSb[ 0 ];
	curSb->runners = count;

	_sb *curSb = &m_pSb[1];
	curSb->runners = count;
}

//=================================================================================================
eve::threading::Barrier::~Barrier( void ) 
{}



//=================================================================================================
void eve::threading::Barrier::Wait( void ) 
{
    _sb *TempSb = m_pCurrentSb;		// ptr to a sub-barrier
	TempSb->wait_lk.Lock();

    if (TempSb->runners == 1) 
	{  	
		// last thread reaching barrier
        if (m_maxCnt != 1)
		{
				// reset counter
                TempSb->runners = m_maxCnt;
				// wake up all waiting threads
				TempSb->wait_cv.Broadcast();
				
				// switch the current sub-barrier
                m_pCurrentSb = (m_pCurrentSb == &m_pSb[0]) ? &m_pSb[1] : &m_pSb[0];
        }
		TempSb->wait_lk.Unlock();    // release lock
    } 
	else 
	{	

		// not the last thread
        TempSb->runners--;       	// wait
		   
        // while (TempSb->runners != m_maxCnt)
                TempSb->wait_cv.Wait();
		TempSb->wait_lk.Unlock();    // release lock
    }
}



//=================================================================================================
void eve::threading::Barrier::Signal( void ) 
{
	m_pCurrentSb->wait_cv.Broadcast();
}


// Main header
#include "thread/shared/Native_Barrier.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//		NativeT::Barrier class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
NativeT::Barrier::Barrier(int count)
{
    maxcnt = count;
    CurrentSb = &sb[0];
    for (int i = 0; i < 2; ++i)
	{		// construct two subbarriers
        _sb *CurrentSb = &sb[i];
        CurrentSb->runners = count;
    }
}

//=================================================================================================
NativeT::Barrier::~Barrier( void ) 
{}



//=================================================================================================
void NativeT::Barrier::Wait( void ) 
{
    _sb *TempSb = CurrentSb;		// ptr to a subbarrier
	TempSb->wait_lk.Lock();

    if (TempSb->runners == 1) 
	{  	
		// last thread reaching barrier
        if (maxcnt != 1)
		{
				// reset counter
                TempSb->runners = maxcnt;
				// wake up all waiting threads
				TempSb->wait_cv.Broadcast();
				
				// switch the current subbarrier
                CurrentSb = (CurrentSb == &sb[0]) ? &sb[1] : &sb[0];
        }
		TempSb->wait_lk.Unlock();    // release lock
    } 
	else 
	{	

		// not the last thread
        TempSb->runners--;       	// wait
		   
        // while (TempSb->runners != maxcnt)
                TempSb->wait_cv.Wait();
		TempSb->wait_lk.Unlock();    // release lock
    }
}



//=================================================================================================
void NativeT::Barrier::Signal( void ) 
{
	CurrentSb->wait_cv.Broadcast();
}

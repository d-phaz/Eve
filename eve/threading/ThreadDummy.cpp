
/*
 Copyright (c) 2014, The eve Project
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of the {organization} nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Main header
#include "eve/threading/ThreadDummy.h"

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/threading/SpinLock.h"
#endif 


//=================================================================================================
eve::threading::ThreadDummy::ThreadDummy(void)

	// Inheritance
	: eve::threading::Thread()
{}



//=================================================================================================
void eve::threading::ThreadDummy::init(void)
{
	// Call parent class
	eve::threading::Thread::init();

	m_pLock = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
void eve::threading::ThreadDummy::release(void)
{
	EVE_RELEASE_PTR(m_pLock);

	// Call parent class
	eve::threading::Thread::release();
}

//=================================================================================================
void eve::threading::ThreadDummy::run(void)
{
	static int32_t id = 0;
	++id;

	int32_t i = 0;
	while ( i < 1000/*running()*/ )
	{
		m_pLock->lock();

		printf("thread: %i value: %i\n", id, i);
		++i;

		m_pLock->unlock();
	}
}

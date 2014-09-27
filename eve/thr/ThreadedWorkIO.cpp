
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
#include "eve/thr/ThreadedWorkIO.h"


//=================================================================================================
eve::thr::ThreadedWorkIO::ThreadedWorkIO(eve::thr::ThreadedWorkCallback * p_cbStart, eve::thr::ThreadedWorkCallback * p_cbExit)

	// Inheritance
	: eve::thr::ThreadedWork()

	// Members init
	, m_cbStart(p_cbStart)
	, m_cbExit(p_cbExit)
{
	EVE_ASSERT(m_cbStart);
	EVE_ASSERT(m_cbExit);
}



//=================================================================================================
void eve::thr::ThreadedWorkIO::releaseThreadedData(void)
{
	// Release callbacks
	EVE_RELEASE_PTR_CPP(m_cbStart);
	EVE_RELEASE_PTR_CPP(m_cbExit);

	// Call parent class
	eve::thr::ThreadedWork::releaseThreadedData();
}



//=================================================================================================
void eve::thr::ThreadedWorkIO::run(void)
{
	// Start callback.
	m_cbStart->execute(this);
	
	// Call parent class
	eve::thr::ThreadedWork::run();

	// Exit callback.
	m_cbExit->execute(this);
}


/*
 Copyright (c) 2014, The Eve Project
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
#include "threading/Lock.h"


//=============================================================================================
namespace eve
{
	namespace threading
	{
		namespace detail
		{
			class Lock
			{
			public:
				CRITICAL_SECTION cs;
				bool m_bIsLocked;


				Lock(void)
					: m_bIsLocked(false)
				{}

			}; // class Lock

		} // namespace detail
	} // namespace threading
} // namespace eve



//=============================================================================================
eve::threading::Lock::Lock(void)
	: m_criticalSections	()
{
	memset(&m_criticalSections, 0, sizeof(CRITICAL_SECTION));
	InitializeCriticalSection(&m_criticalSections);
}
	
//=============================================================================================
eve::threading::Lock::~Lock(void)
{
	DeleteCriticalSection(&m_criticalSections);
}


	
//=============================================================================================
void eve::threading::Lock::lock(void)
{
	EnterCriticalSection(&m_criticalSections);
}
	
//=============================================================================================
void eve::threading::Lock::unlock(void)
{
	LeaveCriticalSection(&m_criticalSections);
}

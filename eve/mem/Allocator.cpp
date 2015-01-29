
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
#include "eve/mem/Allocator.h"


//=================================================================================================
void eve::mem::check_heap(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line)
{
#if defined(EVE_OS_WIN)
	int32_t	heapstatus = _heapchk();
	switch (heapstatus)
	{
	case _HEAPEMPTY:	EVE_LOG_INFO("Heap is empty in function %s in file %s at line %d.", p_pFunction, p_pFile, p_line);
	case _HEAPOK:		break;

	case _HEAPBADBEGIN:	EVE_LOG_ERROR("Bad start of heap in function %s in file %s at line %d.", p_pFunction, p_pFile, p_line);			EVE_ASSERT_FAILURE;	break;
	case _HEAPBADNODE:	EVE_LOG_ERROR("Bad node in heap in function %s in file %s at line %d.", p_pFunction, p_pFile, p_line);			EVE_ASSERT_FAILURE;	break;
	default:			EVE_LOG_ERROR("heap_check() call error in function %s in file %s at line %d.", p_pFunction, p_pFile, p_line);	EVE_ASSERT_FAILURE;	break;
	}

#else
	
	// Do nothing.
#endif
}



//=================================================================================================
void eve::mem::check_memory(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line)
{
#if defined(EVE_OS_WIN)
	if (::_CrtCheckMemory() == FALSE)
	{
		EVE_LOG_ERROR("Memory problem detected in function %s in file %s at line %d.", p_pFunction, p_pFile, p_line);
		EVE_ASSERT_FAILURE;
	}

#else

	// Do nothing.
#endif
}

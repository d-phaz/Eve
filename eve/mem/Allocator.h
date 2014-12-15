
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

#pragma once
#ifndef __EVE_MEMORY_ALLOCATOR_H__
#define __EVE_MEMORY_ALLOCATOR_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif


namespace eve
{
	namespace mem
	{
		/** 
		* \brief Aligned memory allocation.
		* \param p_alignment must be an integer power of 2.
		*/
		void * align_malloc(size_t p_alignment, size_t p_size);
		/** \brief Free aligned memory. */
		void align_free(void * p_pPtr);		

	} // namespace mem

} // namespace eve


//=================================================================================================
EVE_FORCE_INLINE void * eve::mem::align_malloc(size_t p_alignment, size_t p_size)
{
#if defined(EVE_OS_WIN)
	return _aligned_malloc(p_size, p_alignment);

#elif defined(EVE_OS_DARWIN)
	void * ptr = nullptr;
	if (posix_memalign(&ptr, p_alignment, p_size) != 0)
	{
		EVE_LOG_ERROR("Unable to allocate memory, size:%d, alignment:%d", p_size, p_alignment)
	}
	return ptr;

#elif defined(EVE_OS_LINUX)
	void * ptr = nullptr;
	if (posix_memalign(&ptr, p_alignment, p_size) != 0)
	{
		EVE_LOG_ERROR("Unable to allocate memory, size:%d, alignment:%d", p_size, p_alignment)
	}
	return ptr;

#endif
}

//=================================================================================================
EVE_FORCE_INLINE void eve::mem::align_free(void * p_pPtr)
{
#if defined(EVE_OS_WIN)
	_aligned_free(p_pPtr);

#elif defined(EVE_OS_DARWIN)
	free(p_pPtr);

#elif defined(EVE_OS_LINUX)
	free(p_pPtr);

#endif
}



/** \def EVE_DECLARE_ALIGNED_ALLOCATOR \brief Convenience macro to declare class or struct aligned allocation operators. */
#define EVE_DECLARE_ALIGNED_ALLOCATOR \
	EVE_FORCE_INLINE void* operator new(size_t sizeInBytes)		{ return eve::mem::align_malloc(16, sizeInBytes);	}   \
	EVE_FORCE_INLINE void  operator delete(void* ptr)			{ eve::mem::align_free(ptr);						}   \
	EVE_FORCE_INLINE void* operator new(size_t, void* ptr)		{ return ptr;										}   \
	EVE_FORCE_INLINE void  operator delete(void*, void*)		{													}   \
	EVE_FORCE_INLINE void* operator new[](size_t sizeInBytes)	{ return eve::mem::align_malloc(16, sizeInBytes);	}   \
	EVE_FORCE_INLINE void  operator delete[](void* ptr)			{ eve::mem::align_free(ptr);						}   \
	EVE_FORCE_INLINE void* operator new[](size_t, void* ptr)	{ return ptr;										}   \
	EVE_FORCE_INLINE void  operator delete[](void*, void*)		{													}   \


/** \def EVE_ALIGN \brief Convenience macro to declare class or struct aligned. */
#if defined(EVE_OS_WIN)
#if defined(__MINGW32__) || defined(__CYGWIN__) || (defined (_MSC_VER) && _MSC_VER < 1300)
#define EVE_ALIGN(ALIGNMENT, TYPE) TYPE
#else
#define EVE_ALIGN(ALIGNMENT, TYPE) __declspec(align(ALIGNMENT)) TYPE
#endif
#elif defined(EVE_OS_DARWIN) || defined(EVE_OS_LINUX)
#define EVE_ALIGN(ALIGNMENT, TYPE) TYPE __attribute__ ((aligned (ALIGNMENT)))
#endif


/** \def EVE_ALIGNED16 \brief Convenience macro to declare class or struct has 16 Byte memory alignment. */
#define EVE_ALIGNED16(TYPE) EVE_ALIGN(16, TYPE)
/** \def EVE_ALIGNED64 \brief Convenience macro to declare class or struct has 64 Byte memory alignment. */
#define EVE_ALIGNED64(TYPE) EVE_ALIGN(64, TYPE)
/** \def EVE_ALIGNED128 \brief Convenience macro to declare class or struct has 128 Byte memory alignment. */
#define EVE_ALIGNED128(TYPE) EVE_ALIGN(128, TYPE)

#endif // __EVE_MEMORY_ALLOCATOR_H__

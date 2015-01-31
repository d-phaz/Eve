
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
		/** \brief Check heap state, log it and create error assertion. */
		void check_heap(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line);
		/** \brief Check memory state, log it and create error assertion. */
		void check_memory(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line);


		/** \brief C-style memory allocation. */
		static void * malloc(size_t p_size);
		/** \brief Allocates a block of memory for an array of p_num elements, each of them p_size bytes long, and initializes all its bits to zero. */
		static void * calloc(size_t p_num, size_t p_size);
		/** \brief Changes the p_size of the memory block pointed to by p_pPtr. The function may move the memory block to a new location (whose address is returned by the function). */
		static void * realloc(void * p_pPtr, size_t p_size);
		/** \brief Sets the first p_size p_byte of the block of memory pointed by ptr to the specified p_byte (interpreted as an unsigned char). */
		static void memset(void * p_pPtr, int32_t p_byte, size_t p_size);
		/** \brief Copies the values of p_size byte from the location pointed by p_pSrc directly to the memory block pointed by p_pDest. */
		static void memcpy(void * p_pDest, const void * p_pSrc, size_t p_size);
		/** \brief Copies the content of the location pointed by p_pSrc directly to the memory block pointed by p_pDest for p_num elements. */
		template<class T> static void copy(T * p_pDest, T * p_pSrc, size_t p_num);
		/** \brief C-style memory free. */
		static void free(void * p_pPtr);


		/** 
		* \brief Aligned memory allocation.
		* \param p_alignment must be an integer power of 2.
		*/
		static void * align_malloc(size_t p_alignment, size_t p_size);
		/** \brief Free aligned memory. */
		static void align_free(void * p_pPtr);


		/** \brief 16 byte aligned memset. */
		static void align_memset_16(void * p_pPtr, int32_t p_byte, size_t p_size);

	} // namespace mem

} // namespace eve


/**
* \def EVE_MEM_CHECK_HEAP
* \brief Convenience macro to check heap.
*/
#ifndef NDEBUG
#define EVE_MEM_CHECK_HEAP		eve::mem::check_heap(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT_ENFORCE(__FILE__), __LINE__)
#else
#define EVE_MEM_CHECK_HEAP 
#endif
/**
* \def EVE_MEM_CHECK_MEMORY
* \brief Convenience macro to check memory.
*/
#ifndef NDEBUG
#define EVE_MEM_CHECK_MEMORY	eve::mem::check_memory(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT_ENFORCE(__FILE__), __LINE__)
#else
#define EVE_MEM_CHECK_MEMORY 
#endif
/**
* \def EVE_MEM_CHECK
* \brief Convenience macro to check heap and memory.
*/
#ifndef NDEBUG
#define EVE_MEM_CHECK	EVE_MEM_CHECK_HEAP; \
						EVE_MEM_CHECK_MEMORY;
#else
#define EVE_MEM_CHECK 
#endif



//=================================================================================================
EVE_FORCE_INLINE void * eve::mem::malloc(size_t p_size)
{
	void * ptr = std::malloc(p_size);
	EVE_MEM_CHECK;
	return ptr;
}

//=================================================================================================
EVE_FORCE_INLINE void * eve::mem::calloc(size_t p_num, size_t p_size)
{
	void * ptr = std::calloc(p_num, p_size);
	EVE_MEM_CHECK;
	return ptr;
}

//=================================================================================================
EVE_FORCE_INLINE void * eve::mem::realloc(void * p_pPtr, size_t p_size)
{
	EVE_ASSERT(p_pPtr);
	void * ptr = std::realloc(p_pPtr, p_size);
	EVE_MEM_CHECK;
	return ptr;
}

//=================================================================================================
EVE_FORCE_INLINE void eve::mem::memset(void * p_pPtr, int32_t p_byte, size_t p_size)
{
	EVE_ASSERT(p_pPtr);
	std::memset(p_pPtr, p_byte, p_size);
	EVE_MEM_CHECK;
}

//=================================================================================================
EVE_FORCE_INLINE void eve::mem::memcpy(void * p_pDest, const void * p_pSrc, size_t p_size)
{
	EVE_ASSERT(p_pDest);
	EVE_ASSERT(p_pSrc);
	std::memcpy(p_pDest, p_pSrc, p_size);
	EVE_MEM_CHECK;
}

//=================================================================================================
template<class T> EVE_FORCE_INLINE void eve::mem::copy(T * p_pDest, T * p_pSrc, size_t p_num)
{
	EVE_ASSERT(p_pDest);
	EVE_ASSERT(p_pSrc);
	std::copy(p_pSrc, p_pSrc + p_num, p_pDest);
	EVE_MEM_CHECK;
}

//=================================================================================================
EVE_FORCE_INLINE void eve::mem::free(void * p_pPtr)
{
	EVE_ASSERT(p_pPtr);
	std::free(p_pPtr);
	EVE_MEM_CHECK;
}



//=================================================================================================
EVE_FORCE_INLINE void * eve::mem::align_malloc(size_t p_alignment, size_t p_size)
{
#if defined(EVE_OS_WIN)
	void * ptr = _aligned_malloc(p_size, p_alignment);
	EVE_MEM_CHECK;
	return ptr;

#elif defined(EVE_OS_DARWIN)
	void * ptr = nullptr;
	if (posix_memalign(&ptr, p_alignment, p_size) != 0)
	{
		EVE_LOG_ERROR("Unable to allocate memory, size:%d, alignment:%d", p_size, p_alignment)
	}
	EVE_MEM_CHECK;
	return ptr;

#elif defined(EVE_OS_LINUX)
	void * ptr = nullptr;
	if (posix_memalign(&ptr, p_alignment, p_size) != 0)
	{
		EVE_LOG_ERROR("Unable to allocate memory, size:%d, alignment:%d", p_size, p_alignment)
	}
	EVE_MEM_CHECK;
	return ptr;

#endif
}

//=================================================================================================
EVE_FORCE_INLINE void eve::mem::align_free(void * p_pPtr)
{
	EVE_ASSERT(p_pPtr);

#if defined(EVE_OS_WIN)
	_aligned_free(p_pPtr);

#elif defined(EVE_OS_DARWIN)
	free(p_pPtr);

#elif defined(EVE_OS_LINUX)
	free(p_pPtr);

#endif

	EVE_MEM_CHECK;
}



//=================================================================================================
EVE_FORCE_INLINE void eve::mem::align_memset_16(void * p_pPtr, int32_t p_byte, size_t p_size)
{
	EVE_ASSERT((p_size & 0x0F) == 0);
	EVE_ASSERT(((uintptr_t)p_pPtr & 0x0F) == 0);
	std::memset(p_pPtr, p_byte, p_size);
	EVE_MEM_CHECK;
}



/** 
* \def EVE_DECLARE_ALIGNED_ALLOCATOR 
* \brief Convenience macro to declare class or struct aligned allocation operators. 
*/
#define EVE_DECLARE_ALIGNED_ALLOCATOR \
	EVE_FORCE_INLINE void* operator new(size_t sizeInBytes)		{ return eve::mem::align_malloc(16, sizeInBytes);	}   \
	EVE_FORCE_INLINE void  operator delete(void* ptr)			{ eve::mem::align_free(ptr);						}   \
	EVE_FORCE_INLINE void* operator new(size_t, void* ptr)		{ return ptr;										}   \
	EVE_FORCE_INLINE void  operator delete(void*, void*)		{													}   \
	EVE_FORCE_INLINE void* operator new[](size_t sizeInBytes)	{ return eve::mem::align_malloc(16, sizeInBytes);	}   \
	EVE_FORCE_INLINE void  operator delete[](void* ptr)			{ eve::mem::align_free(ptr);						}   \
	EVE_FORCE_INLINE void* operator new[](size_t, void* ptr)	{ return ptr;										}   \
	EVE_FORCE_INLINE void  operator delete[](void*, void*)		{													}   \



/** 
* \def EVE_ALIGN 
* \brief Convenience macro to declare class or struct aligned. 
*/
#if defined(EVE_OS_WIN)
#if defined(__MINGW32__) || defined(__CYGWIN__) || (defined (_MSC_VER) && _MSC_VER < 1300)
#define EVE_ALIGN(ALIGNMENT, TYPE) TYPE
#else
#define EVE_ALIGN(ALIGNMENT, TYPE) __declspec(align(ALIGNMENT)) TYPE
#endif
#elif defined(EVE_OS_DARWIN) || defined(EVE_OS_LINUX)
#define EVE_ALIGN(ALIGNMENT, TYPE) TYPE __attribute__ ((aligned (ALIGNMENT)))
#endif

/** 
* \def EVE_ALIGNED16 
* \brief Convenience macro to declare class or struct has 16 Byte memory alignment. 
*/
#define EVE_ALIGNED16(TYPE) EVE_ALIGN(16, TYPE)
/**
* \def EVE_ALIGNED32
* \brief Convenience macro to declare class or struct has 32 Byte memory alignment.
*/
#define EVE_ALIGNED32(TYPE) EVE_ALIGN(32, TYPE)
/** 
* \def EVE_ALIGNED64 
* \brief Convenience macro to declare class or struct has 64 Byte memory alignment. 
*/
#define EVE_ALIGNED64(TYPE) EVE_ALIGN(64, TYPE)
/** 
* \def EVE_ALIGNED128 
* \brief Convenience macro to declare class or struct has 128 Byte memory alignment. 
*/
#define EVE_ALIGNED128(TYPE) EVE_ALIGN(128, TYPE)

#endif // __EVE_MEMORY_ALLOCATOR_H__

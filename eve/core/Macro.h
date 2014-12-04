
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
#ifndef __EVE_CORE_MACRO_H__
#define __EVE_CORE_MACRO_H__


/** 
* \def EVE_FORCE_INLINE
* Convenience macro to enforce inline function declaration.
*/
#if defined(EVE_OS_WIN)
#if defined(__MINGW32__) || defined(__CYGWIN__) || (defined (_MSC_VER) && _MSC_VER < 1300)
#define EVE_FORCE_INLINE inline
#else
#define EVE_FORCE_INLINE __forceinline
#endif
#elif defined(EVE_OS_DARWIN) || defined(EVE_OS_LINUX)
#define EVE_FORCE_INLINE inline __attribute__((always_inline))
#endif



/**
* \def EVE_ASSERT
* \brief Assertion called in DEBUG mode only.
*/
#if !defined(NDEBUG)
#define EVE_ASSERT( expression )	assert(expression)
#else
#define EVE_ASSERT( expression )	
#endif
/**
* \def EVE_ASSERT_FAILURE
* \brief Failure assertion called in DEBUG mode only.
*/
#if !defined(NDEBUG)
#define EVE_ASSERT_FAILURE	assert(0)
#else
#define EVE_ASSERT_FAILURE	
#endif



/**
* \def EVE_TXT
* \brief Convenience macro to use text as ANSI or UNICODE
*/
#if defined(UNICODE) || defined(_UNICODE)
#define EVE_TXT(txt)	L##txt
#else
#define EVE_TXT(txt)	txt
#endif
/** 
* \def EVE_TXT_ENFORCE
* \brief Convenience macro to enforce UNICODE on system provided macro such as __FILE__ or __FUNCTION__. 
*/
#define  EVE_TXT_ENFORCE(txt)	EVE_TXT(txt)



/**
* \def EVE_DISABLE_ASSIGNATION
* \brief Disable assignation operator for target class making them private.
*/
#define EVE_DISABLE_ASSIGNATION( targetClass )			\
private:										\
	void operator=(const targetClass& arg){};
/**
* \def EVE_DISABLE_COPY
* \brief Disable copy constructor and assignation operator for target class making them private.
*/
#define EVE_DISABLE_COPY( targetClass )			\
private:										\
	targetClass(targetClass& arg){};			\
	void operator=(const targetClass& arg){};
/**
* \def EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR
* \brief Make default constructor and destructor protected.
*/
#define EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR( targetClass )		\
protected:														\
	explicit targetClass(void){};								\
	virtual ~targetClass(void){};
/**
* \def EVE_PROTECT_CONSTRUCTOR
* \brief Make default constructor protected.
*/
#define EVE_PROTECT_CONSTRUCTOR( targetClass )		\
protected:											\
	explicit targetClass(void){};
/**
* \def EVE_PROTECT_DESTRUCTOR
* \brief Make destructor protected.
*/
#define EVE_PROTECT_DESTRUCTOR( targetClass )		\
protected:											\
	virtual ~targetClass(void){};


#endif // __EVE_CORE_MACRO_H__

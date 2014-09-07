
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

#pragma once
#ifndef __EVE_CORE_MACRO_H__
#define __EVE_CORE_MACRO_H__


/**
* \macro EVE_DISABLE_COPY
* disable copy constructor and assignation operator for target class making them private
*/
#define EVE_DISABLE_COPY( targetClass )			\
private:										\
	targetClass(targetClass& arg){};			\
	void operator=(const targetClass& arg){};


/**
* \macro EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR
* make default constructor and destructor protected.
*/
#define EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR( targetClass )		\
protected:														\
	targetClass(void){};										\
	virtual ~targetClass(void){};


/**
* \macro EVE_PROTECT_CONSTRUCTOR
* make default constructor protected.
*/
#define EVE_PROTECT_CONSTRUCTOR( targetClass )		\
protected:											\
	targetClass(void){};


/**
* \macro EVE_PROTECT_DESTRUCTOR
* make destructor protected.
*/
#define EVE_PROTECT_DESTRUCTOR( targetClass )		\
protected:											\
	virtual ~targetClass(void){};


/** 
* \macro EVE_ASSERT
* assertion called in DEBUG mode only
*/
#if !defined(NDEBUG)
#define EVE_ASSERT( expression )	assert(expression);
#else
#define EVE_ASSERT( expression )	
#endif


/**
* \macro EVE_ASSERT_FAILURE
* failure assertion called in DEBUG mode only
*/
#if !defined(NDEBUG)
#define EVE_ASSERT_FAILURE	assert(0);
#else
#define EVE_ASSERT_FAILURE	
#endif


#endif // __EVE_CORE_MACRO_H__

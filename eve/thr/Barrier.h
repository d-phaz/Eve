//
///*
// Copyright (c) 2014, The eve Project
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
// 
// * Neither the name of the {organization} nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//*/
//
//#pragma once
//#ifndef __EVE_THREADING_BARRIER_H__
//#define __EVE_THREADING_BARRIER_H__
//
//#ifndef __EVE_THREADING_CONDITION_H__
//#include "eve/thr/Condition.h"
//#endif
//
//#ifndef __EVE_THREADING_MUTEX_H__
//#include "eve/thr/Mutex.h"
//#endif
//
//
//namespace eve
//{
//	namespace thr
//	{
//
//
//	} // namespace thr
//
//} // namespace eve
//
//#endif // __EVE_THREADING_BARRIER_H__
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//// Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//#ifndef __NATIVE_CONDITION_H__
//#include "thread/win32/Native_Condition.h"
//#endif
//
//#ifndef __NATIVE_MUTEX_H__
//#include "thread/win32/Native_Mutex.h"
//#endif
//
//#define _REENTRANT
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//// NativeT namespace
/////////////////////////////////////////////////////////////////////////////////////////////////////
//namespace NativeT 
//{
//
//	// The following structure defines a subbarrier in a barrier.
//	// It consists of a lock and a condition variable for waiters at
//	// this sub-barrier and the number of running threads associated
//	// with this su-bbarrier.
//	typedef  struct 
//	{
//		NativeT::Condition  wait_cv;		// condition variable for waiters at barrier 
//		NativeT::Mutex		wait_lk;		// mutex for waiters at barrier 
//		int					runners;		// number of running threads 
//	} _sb;
//
//
//	/**
//	* @class Barrier
//	*/
//	class Barrier 
//	{
//		//////////////////////////////////////
//		//				DATAS				//
//		//////////////////////////////////////
//
//	private:
//		int		maxcnt;       //<! maximum number of runners
//		_sb		sb[2];        //<! two sub-barriers
//		_sb		*CurrentSb;   //<! ptr to current sub-barrier
//
//
//		//////////////////////////////////////
//		//				METHOD				//
//		//////////////////////////////////////
//
//	public:
//		/**
//		* @brief Barrier class constructor : Initialize a barrier for given number of threads.
//		* @param "p_count" is the number of threads involved
//		*/
//		Barrier( int p_count );	
//		/**
//		* @brief Barrier class destructor
//		*/
//		virtual ~Barrier( void ); 
//
//
//		/**
//		* @brief Wait until all threads reach this barrier. The last thread switches
//		* "CurrentSb" point to another sub barrier before waking up all waiting threads.
//		*/
//		void Wait( void );
//		/**
//		* @brief signal barrier
//		*/
//		void Signal( void );
//	};
//
//} // namespace NativeT 
//
//#endif // __NATIVE_BARRIER_H__

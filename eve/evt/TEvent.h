
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
#ifndef __EVE_EVT_TEVENT_H__
#define __EVE_EVT_TEVENT_H__


#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_EVT_TABSTRACT_EVENT_H__
#include "eve/evt/TEventAbstract.h"
#endif

#ifndef __EVE_EVT_TDELEGATE_H__
#include "eve/evt/TDelegate.h"
#endif

#ifndef __EVE_EVT_TSTRATEGY_H__
#include "eve/evt/TStrategy.h"
#endif

namespace eve
{
	namespace evt
	{
		/**
		* \class eve::evt::TEvent
		*
		* \brief Priority event template class.
		* A TEvent uses internally a TStrategy which invokes delegates in order of priority (lower priorities first).
		* Delegate's are sorted according to the priority value,
		* when two delegates have the same priority, they are invoked in an arbitrary manner.
		* To create your own events use: eve::evt::TEvent<argType> myEvent
		*
		* \note extends eve::evt::TEventAbstract<>
		*/
		template <class TArgs>
		class TEvent
			: public eve::evt::TEventAbstract< TArgs
											 , eve::evt::TStrategy<TArgs, eve::evt::TDelegateAbstract<TArgs>> 
											 , eve::evt::TDelegateAbstract<TArgs> >
		{

			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			/** \brief Class constructor. */
			TEvent(void);
			/** \brief Class destructor. */
			virtual ~TEvent(void);

			/** 
			* \brief Copy constructor.
			* Allow copy of events, by copying everything except the mutex. 
			*/
			TEvent(const TEvent<TArgs> & p_ref);

			/**
			* \brief Assignment operator.
			* Allow copy of events, by copying everything except the mutex.
			*/
			TEvent<TArgs> & operator=(const TEvent<TArgs> & p_ref);

		}; // class TEvent

	} // namespace evt

} // namespace eve


//=================================================================================================
template <class TArgs>
eve::evt::TEvent<TArgs>::TEvent(void)
	// Inheritance
	: eve::evt::TEventAbstract<TArgs,
							   eve::evt::TStrategy<TArgs, eve::evt::TDelegateAbstract<TArgs>>,
							   eve::evt::TDelegateAbstract<TArgs >> ()
{}

//=================================================================================================
template <class TArgs>
eve::evt::TEvent<TArgs>::~TEvent(void)
{}

//=================================================================================================
template <class TArgs>
eve::evt::TEvent<TArgs>::TEvent(const TEvent<TArgs> & p_ref)
	// Inheritance
	: eve::evt::TEventAbstract<TArgs,
							   eve::evt::TStrategy<TArgs, eve::evt::TDelegateAbstract<TArgs>>,
							   eve::evt::TDelegateAbstract<TArgs >> ()
{
	p_ref._mutex.lock();
	this->_mutex.lock();
	this->_strategy = p_ref._strategy;
	this->_mutex.unlock();
	p_ref._mutex.unlock();

	this->_enabled = p_ref._enabled;
}

//=================================================================================================
template <class TArgs>
eve::evt::TEvent<TArgs> & eve::evt::TEvent<TArgs>::operator=(const TEvent<TArgs> & p_ref)
{
	if (&p_ref != this)
	{
		p_ref._mutex.lock();
		this->_mutex.lock();
		this->_strategy = p_ref._strategy;
		this->_mutex.unlock();
		p_ref._mutex.unlock();

		this->_enabled = p_ref._enabled;
	}

	return *this;
}

#endif // __EVE_EVT_TEVENT_H__
